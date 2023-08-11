from .backend import (
    initialize_environment,
    featurize_directory_imp,
    featurize_montage_imp,
    featurize_fname_lists_imp,
    findrelations_imp,
    use_gpu,
    gpu_available,
    blacklist_roi_imp,
    clear_roi_blacklist_imp,
    roi_blacklist_get_summary_imp,
    customize_gabor_feature_imp,
    set_if_ibsi_imp,
    set_environment_params_imp,
    get_params_imp, 
    create_arrow_file_imp, 
    get_arrow_file_imp, 
    get_parquet_file_imp, 
    create_parquet_file_imp, 
    get_arrow_table_imp,
    arrow_is_enabled_imp,
    )

import os
import numpy as np
import pandas as pd
from typing import Optional, List

if arrow_is_enabled_imp():
    import pyarrow as pa

class Nyxus:
    """Nyxus image feature extraction library

    Scalably extracts features from images.

    Parameters
    ----------
    features : list[str]
        List of features to be calculated. Individual features can be
        provided or pre-specified feature groups. Valid groups include:
            *ALL*
            *ALL_INTENSITY*
            *ALL_MORPHOLOGY*
            *BASIC_MORPHOLOGY*
            *ALL_GLCM*
            *ALL_GLRM*
            *ALL_GLSZM*
            *ALL_GLDM*
            *ALL_NGTDM*
            *ALL_BUT_GABOR*
            *ALL_BUT_GLCM*
        Both individual features and feature groups are case sensitive.
    neighbor_distance: int (optional, default 5)
        Any two objects separated by a Euclidean distance (pixel units) greater than this
        value will not be be considered neighbors. This cutoff is used by all features which
        rely on neighbor identification.
    pixels_per_micron: float (optional, default 1.0)
        Specify the image resolution in terms of pixels per micron for unit conversion
        of non-unitless features.
    coarse_gray_depth: int (optional, default 256)
        Custom number of levels in grayscale denoising used in texture features.
    n_feature_calc_threads: int (optional, default 4)
        Number of threads to use for feature calculation parallelization purposes.
    n_loader_threads: int (optional, default 1)
        Number of threads to use for loading image tiles from disk. Note: image loading
        multithreading is very memory intensive. You should consider optimizing
        `n_feature_calc_threads` before increasing `n_loader_threads`.
    using_gpu: int (optional, default -1)
        Id of the gpu to use. To find available gpus along with ids, using nyxus.get_gpu_properties().
        The default value of -1 uses cpu calculations. Note that the gpu features only support a single 
        thread for feature calculation. 
    ibsi: bool (optional, default false)
       IBSI available features will be IBSI compliant when true.
    gabor_kersize: int (optional, default 16)
        Size of filter kernel's side
    gabor_gamma: float (optional, default 0.1)
        Aspect ratio of the Gaussian factor
    gabor_sig2lam: float (optional, deafult 0.8)
        Spatial frequency bandwidth.
    gabor_f0: float (optional, default 0.1)
        frequency of the baseline lowpass filter as denominator of `\pi`.
    gabor_theta: float (optional, default 45): 
        Orientation of the Gaussian in degrees 0-180.
    gabor_thold: float (optional, 0.025)
        lower threshold of the filtered image to baseline ratio. 
    gabor_freqs: list[int] (optional, default [1,2,4,8,16,32,64])
        comma-separated denominators of `\pi` as frequencies of Gabor filter's harmonic factor.
    """

    def __init__(
        self,
        features: List[str],
        neighbor_distance: int = 5,
        pixels_per_micron: float = 1.0,
        coarse_gray_depth: int = 256, 
        n_feature_calc_threads: int = 4,
        n_loader_threads: int = 1,
        using_gpu: int = -1,
        ibsi: bool = False,
        gabor_kersize: int = 16,
        gabor_gamma: float = 0.1,
        gabor_sig2lam: float = 0.8,
        gabor_f0: float = 0.1,
        gabor_theta: float = 45,
        gabor_thold: float = 0.025,
        gabor_freqs: List[int] = [1,2,4,8,16,32,64]
        ):

        if neighbor_distance <= 0:
            raise ValueError("Neighbor distance must be greater than zero.")

        if pixels_per_micron <= 0:
            raise ValueError("Pixels per micron must be greater than zero.")

        if coarse_gray_depth <= 0:
            raise ValueError("Custom number of grayscale levels (parameter coarse_gray_depth, default=256) must be non-negative.")

        if n_feature_calc_threads < 1:
            raise ValueError("There must be at least one feature calculation thread.")

        if n_loader_threads < 1:
            raise ValueError("There must be at least one loader thread.")
        
        if(using_gpu > -1 and n_feature_calc_threads != 1):
            print("Gpu features only support a single thread. Defaulting to one thread.")
            n_feature_calc_threads = 1
            
        if(using_gpu > -1 and not gpu_available()):
            print("No gpu available.")
            using_gpu = -1
    

        initialize_environment(
            features,
            neighbor_distance,
            pixels_per_micron,
            coarse_gray_depth, 
            n_feature_calc_threads,
            n_loader_threads,
            using_gpu,
            ibsi)
        
        
        self.set_gabor_feature_params(
            kersize=gabor_kersize,
            gamma=gabor_gamma,
            sig2lam=gabor_sig2lam,
            f0=gabor_f0,
            theta=gabor_theta,
            thold=gabor_thold,
            freqs=gabor_freqs
        )
        
        # list of valid outputs that are used throughout featurize functions
        self._valid_output_types = ['pandas', 'arrow', 'arrowipc', 'parquet']

    def featurize_directory(
        self,
        intensity_dir: str,
        label_dir: Optional[str] = None,
        file_pattern: Optional[str] = ".*",
        output_type: Optional[str] = "pandas",
        output_path: Optional[str] = ""
    ):
        """Extract features from all the images satisfying the file pattern of provided image directories.

        Extracts all the requested features _at the image level_ from the images
        present in `intensity_dir`. If `label_dir` is specified, features will be
        extracted for each unique label present in the label images. The file names
        of the label images are expected to match those of the intensity images.

        Parameters
        ----------
        intensity_dir : str
            Path to directory containing intensity images.
        label_dir : str (optional, default None)
            Path to directory containing label images.
        file_pattern: str (optional, default ".*")
            Regular expression used to filter the images present in both
            `intensity_dir` and `label_dir`

        Returns
        -------
        df : pd.DataFrame
            Pandas DataFrame containing the requested features with one row per label
            per image.
        """
        if not os.path.exists(intensity_dir):
            raise IOError(
                f"Provided intensity image directory '{intensity_dir}' does not exist."
            )

        if label_dir is not None and not os.path.exists(label_dir):
            raise IOError(
                f"Provided label image directory '{label_dir}' does not exist."
            )

        if label_dir is None:
            label_dir = intensity_dir

        if (output_type not in self._valid_output_types):
            raise  ValueError(f'Invalid output type {output_type}. Valid output types are {self._valid_output_types}.')
            
        if (output_type == 'pandas'):
            
            header, string_data, numeric_data = featurize_directory_imp (intensity_dir, label_dir, file_pattern, True)

            df = pd.concat(
                [
                    pd.DataFrame(string_data, columns=header[: string_data.shape[1]]),
                    pd.DataFrame(numeric_data, columns=header[string_data.shape[1] :]),
                ],
                axis=1,
            )

            # Labels should always be uint.
            if "label" in df.columns:
                df["label"] = df.label.astype(np.uint32)

            return df
        
        else:
            
            featurize_directory_imp(intensity_dir, label_dir, file_pattern, False)
            
            output_type = output_type.lower() # ignore case of output type
            
            if (output_type == 'arrow' or output_type == 'arrowipc'):
                
                self.create_arrow_file(output_path)
                
                return self.get_arrow_ipc_file()
                
            elif (output_type == 'parquet'):
                
                self.create_parquet_file(output_path)
                
                return self.get_parquet_file()
            
            
    
    def featurize(
        self,
        intensity_images: np.ndarray,
        label_images: np.ndarray,
        intensity_names: list = [],
        label_names: list = [],
        output_type: Optional[str] = "pandas",
        output_path: Optional[str] = ""
        
    ):
        """Extract features from a single image pair in a 2D np.array or for all the images in a 3D np.array.

        Extracts all the requested features _at the image level_ from the images
        in `intensity_images`. Features will be extracted for each unique label 
        present in the label images. The name of resulting features in df will be
        autogenerated if no intensity and label names are provided. Note that if
        names are provided, the number of names must be the same as the number of images.

        Parameters
        ----------
        intensity_images : np.ndarray
            2D image or 3D collection of intensity images.
        label_images : np.ndarray
            2D image or 3D collection of label images.
        intensity_names (optional): list
            names for the images in for the DataFrame output. 
        label_names (optional): list
            names for the labels in for the DataFrame output. 
            
        Returns
        -------
        df : pd.DataFrame
            Pandas DataFrame containing the requested features with one row per label
            per image.
        """
        
        # verify argument types
        if not isinstance(intensity_images, np.ndarray):
            raise ValueError("intensity_images parameter must be numpy.ndarray")

        if not isinstance(label_images, np.ndarray):
            raise ValueError("label_images parameter must be numpy.ndarray")
        
        if (output_type not in self._valid_output_types):
            raise  ValueError(f'Invalid output type {output_type}. Valid output types are {self._valid_output_types}.')
        
        # verify dimensions of images are the same
        if(intensity_images.ndim == 2):
            if(label_images.ndim != 2):
                raise ValueError("Both intensity and label arrays must be the same dimension")
            
            intensity_images = np.array([intensity_images])
            label_images = np.array([label_images])
            
        elif(intensity_images.ndim == 3):
            if(label_images.ndim != 3):
                raise ValueError("Both intensity and label arrays must be the same dimension")
            
        else:
            raise ValueError("Intensity and label arrays must be 2D or 3D")
            
        
        if(intensity_images.shape != label_images.shape):
            raise ValueError("Intensity and label image arrays must have the same number of images with matching dimensions")
        
        if (intensity_names == []):
            int_name = "Intensity"
            
            for i in range(intensity_images.shape[0]):
                intensity_names.append(int_name + str(i))
        
        
        if (label_names == []):
            seg_name = "Segmentation"
            
            for i in range(label_images.shape[0]):
                label_names.append(seg_name + str(i))
                
        if (intensity_images.shape[0] != len(intensity_names)):
            raise ValueError("Number of image names must be the same as the number of images.")
        
        if (label_images.shape[0] != len(label_names)):
            raise ValueError("Number of segmentation names must be the same as the number of images.")
        
    
        if (output_type == 'pandas'):
                
            header, string_data, numeric_data, error_message = featurize_montage_imp (intensity_images, label_images, intensity_names, label_names, True)
            
            self.error_message = error_message
            if(error_message != ''):
                print(error_message)

            df = pd.concat(
                [
                    pd.DataFrame(string_data, columns=header[: string_data.shape[1]]),
                    pd.DataFrame(numeric_data, columns=header[string_data.shape[1] :]),
                ],
                axis=1,
            )

            # Labels should always be uint.
            if "label" in df.columns:
                df["label"] = df.label.astype(np.uint32)

            return df
            
        else:
            
            error_message = featurize_montage_imp (intensity_images, label_images, intensity_names, label_names, False)
            
            self.error_message = error_message
            if(error_message != ''):
                print(error_message)
            
            output_type = output_type.lower() # ignore case of output type
            
            if (output_type == 'arrow' or output_type == 'arrowipc'):
                
                self.create_arrow_file(output_path)
                
                return self.get_arrow_ipc_file()
                
            elif (output_type == 'parquet'):
                
                self.create_parquet_file(output_path)
                
                return self.get_parquet_file()
    
    def using_gpu(self, gpu_on: bool):
        use_gpu(gpu_on)

    def featurize_files (
        self,
        intensity_files: list,
        mask_files: list,
        output_type: Optional[str] = "pandas",
        output_path: Optional[str] = ""):
        """Extract features from image file pairs passed as lists

        Extracts all the requested features _at the image level_ from the intensity images
        present in list `intensity_files` with respect to region of interest masks presented in 
        list `mask_files`. Multiple 

        Parameters
        ----------
        intensity_files : list of intensity image file paths
        mask_files : list of mask image file paths

        Returns
        -------
        df : pd.DataFrame
            Pandas DataFrame containing the requested features with one row per label
            per image.
        """

        if intensity_files is None:
            raise IOError ("The list of intensity file paths is empty")

        if mask_files is None:
            raise IOError ("The list of segment file paths is empty")
        
        if (output_type not in self._valid_output_types):
            raise  ValueError(f'Invalid output type {output_type}. Valid output types are {self._valid_output_types}.')

        if (output_type == 'pandas'):
            
            header, string_data, numeric_data = featurize_fname_lists_imp (intensity_files, mask_files, True)

            df = pd.concat(
                [
                    pd.DataFrame(string_data, columns=header[: string_data.shape[1]]),
                    pd.DataFrame(numeric_data, columns=header[string_data.shape[1] :]),
                ],
                axis=1,
            )

            # Labels should always be uint.
            if "label" in df.columns:
                df["label"] = df.label.astype(np.uint32)

            return df
        
        else:
            
            featurize_fname_lists_imp (intensity_files, mask_files, False)
            
            output_type = output_type.lower() # ignore case of output type
            
            if (output_type == 'arrow' or output_type == 'arrowipc'):
                
                self.create_arrow_file(output_path)
                
                return self.get_arrow_ipc_file()
                
            elif (output_type == 'parquet'):
                
                self.create_parquet_file(output_path)
                
                return self.get_parquet_file()


    def blacklist_roi(self, blacklist:str):
        """Defines the application-wide ROI blacklist

        Defines a set of ROI labels that need to be skipped during feature extraction and in the output. Examples: 
        '27,28,30' - defines a global blacklist of ROI labels 27, 28, and 30
        'file1.ome.tif:5,6,7;file2.ome.tif:11,12,13,14' - defines 2 file-specific blacklists

        Parameters
        ----------
        blacklist : blacklist definition (string)

        Returns
        -------
        None

        """        
        if blacklist is None:
            raise IOError ("ROI blacklist argument is empty")

        if len(blacklist.strip()) == 0:
            raise IOError ("ROI blacklist argument is non-informative")

        blacklist_roi_imp (blacklist)

    def clear_roi_blacklist(self):
        """Clears the ROI blacklist

        Parameters
        ----------
        None

        Returns
        -------
        None

        """
        clear_roi_blacklist_imp ()

    def roi_blacklist_get_summary (self):
        """Returns a human-friendly text of the summary of the application-wide ROI blacklist

        Parameters
        ----------
        None

        Returns
        -------
        text of blacklist summary (string)

        """ 
        s = roi_blacklist_get_summary_imp()
        s = s.strip()
        if len(s) == 0:
            return None
        return s
    
    def set_gabor_feature_params (self, **kwargs):
        """Sets parameters of feature GABOR

        Keyword args:
        * kersize (int): size of filter kernel's side. Example: customize_gabor_feature(kersize=16)
        * gamma (float): aspect ratio of the Gaussian factor. Example: customize_gabor_feature(gamma=0.1)
        * sig2lam (float): spatial frequency bandwidth. Example: customize_gabor_feature(sig2lam=0.8)
        * f0 (float): frequency of the baseline lowpass filter as denominator of `\pi`. Example: customize_gabor_feature(f0=0.1)
        * theta (float): orientation of the Gaussian in degrees 0-180. Example: customize_gabor_feature(theta=1.5708)
        * thold (float): lower threshold of the filtered image to baseline ratio. Example: customize_gabor_feature(thold=0.025)
        * freqs (list[int]): list of denominators of `\pi` as frequencies of Gabor filter's harmonic factor. Example: customize_gabor_feature(freqs="1,2,4,8,16,32,64")
        """

        params = [
            'kersize',
            'gamma',
            'sig2lam',
            'f0',
            'theta',
            'thold',
            'freqs'
        ]
        
        for key in kwargs:
            if key not in params:
                raise ValueError(f"Invalid Gabor parameter {key}. The valid parameters are: {params}")
    
        kersize = str(kwargs.get ('kersize', ""))
        gamma = str(kwargs.get ('gamma', ""))
        sig2lam = str(kwargs.get ('sig2lam', ""))
        f0 = str(kwargs.get ('f0', ""))
        theta = str(kwargs.get ('theta', ""))
        thold = str(kwargs.get ('thold', ""))
        freqs = kwargs.get ('freqs', [])

        if len(kersize)==0 and len(gamma)==0 and len(sig2lam)==0 and len(f0)==0 and len(theta)==0 and len(thold)==0 and len(freqs)==0:
            raise IOError ("Illegal arguments passed to set_gabor_feature_params()")
        
        if (freqs == []):
            freqs = ""
        else:
            freqs = ",".join(str(i) for i in freqs)

        customize_gabor_feature_imp (kersize, gamma, sig2lam, f0, theta, thold, freqs)

    
    def set_environment_params (self, **params):
        """Sets parameters of the environment for Nyxus
        
        Keyword args:
        *neighbor_distance: int 
            Any two objects separated by a Euclidean distance (pixel units) greater than this
            value will not be be considered neighbors. This cutoff is used by all features which
            rely on neighbor identification.
        * pixels_per_micron: float
            Specify the image resolution in terms of pixels per micron for unit conversion
            of non-unitless features.
        * coarse_gray_depth: int 
            Custom number of levels in grayscale denoising used in texture features.
        * n_feature_calc_threads: int (optional, default 4)
            Number of threads to use for feature calculation parallelization purposes.
        * n_loader_threads: int )
            Number of threads to use for loading image tiles from disk. Note: image loading
            multithreading is very memory intensive. You should consider optimizing
            `n_feature_calc_threads` before increasing `n_loader_threads`.
        * using_gpu: int 
            Id of the gpu to use. To find available gpus along with ids, using nyxus.get_gpu_properties().
            The default value of -1 uses cpu calculations. Note that the gpu features only support a single 
            thread for feature calculation. 
        
        """
        
        valid_params = [
            'features',
            'neighbor_distance',
            'pixels_per_micron',
            'coarse_gray_depth',
            'n_feature_calc_threads',
            'n_loader_threads',
            'using_gpu'
        ]
        
        for key in params:
            if key not in valid_params:
                raise ValueError(f'Invalid environment parameter {key}. Value parameters are {params}')
        
        features = params.get('features', [])
        neighbor_distance = params.get ('neighbor_distance', -1)
        pixels_per_micron = params.get ('pixels_per_micron', -1)
        coarse_gray_depth = params.get ('coarse_gray_depth', 0)
        n_reduce_threads = params.get ('n_feature_calc_threads', 0)
        n_loader_threads = params.get ('n_loader_threads', 0)
        using_gpu =params.get ('using_gpu', -2)
        
        set_environment_params_imp(features, 
                                   neighbor_distance, 
                                   pixels_per_micron,
                                   coarse_gray_depth,
                                   n_reduce_threads,
                                   n_loader_threads,
                                   using_gpu)
        
    def set_params(self, **params):
        """Sets parameters of the Nyxus class

        Keyword args:
        
        * features: List[str],
        * neighbor_distance
        * pixels_per_micron
        * coarse_gray_depth
        * n_feature_calc_threads
        * n_loader_threads
        * using_gpu
        * ibsi: bool
    
        * gabor_kersize (int): size of filter kernel's side. Example: set_params(gabor_kersize=16)
        * gabor_gamma (float): aspect ratio of the Gaussian factor. Example: set_params(gabor_gamma=0.1)
        * gabor_sig2lam (float): spatial frequency bandwidth. Example: set_params(gabor_sig2lam=0.8)
        * gabor_f0 (float): frequency of the baseline lowpass filter as denominator of `\pi`. Example: set_params(gabor_f0=0.1)
        * gabor_theta (float): orientation of the Gaussian in degrees 0-180. Example: set_params(gabor_theta=1.5708)
        * gabor_thold (float): lower threshold of the filtered image to baseline ratio. Example: set_params(gabor_thold=0.025)
        * gabor_freqs (str): comma-separated denominators of `\pi` as frequencies of Gabor filter's harmonic factor. Example: set_params(gabor_freqs="1,2,4,8,16,32,64")
        """
        
        available_environment_params = [
            "features",
            "neighbor_distance",
            "pixels_per_micron",
            "coarse_gray_depth",
            "n_feature_calc_threads",
            "n_loader_threads",
            "using_gpu",
            "ibsi"
        ]
        
        environment_params = {}
        
        gabor_params = {}
        
        
        for key, value in params.items():
            if key.startswith("gabor_"):
                gabor_params[key[len("gabor_"):]] = value
            
            elif (key == "ibsi"):
                set_if_ibsi_imp(value)
            
            else:
                if (key not in available_environment_params):
                    raise ValueError(f"Invalid parameter {key}.")
                else:
                    environment_params[key] = value
                
                
        if (len(gabor_params) > 0):
            self.set_gabor_feature_params(**gabor_params)
        
        if (len(environment_params) > 0):
            self.set_environment_params(**environment_params)
    
    def get_params(self, *args):
        """Returns the parameters of a Nyxus object. If no args are supplied, all parameters will be returned.
        
        Valid parameters are:
        
        * features: List[str],
        * neighbor_distance
        * pixels_per_micron
        * coarse_gray_depth
        * n_feature_calc_threads
        * n_loader_threads
        * using_gpu
        * ibsi: bool
    
        * gabor_kersize (int): size of filter kernel's side. Example: set_params(gabor_kersize=16)
        * gabor_gamma (float): aspect ratio of the Gaussian factor. Example: set_params(gabor_gamma=0.1)
        * gabor_sig2lam (float): spatial frequency bandwidth. Example: set_params(gabor_sig2lam=0.8)
        * gabor_f0 (float): frequency of the baseline lowpass filter as denominator of `\pi`. Example: set_params(gabor_f0=0.1)
        * gabor_theta (float): orientation of the Gaussian in degrees 0-180. Example: set_params(gabor_theta=1.5708)
        * gabor_thold (float): lower threshold of the filtered image to baseline ratio. Example: set_params(gabor_thold=0.025)
        * gabor_freqs (str): comma-separated denominators of `\pi` as frequencies of Gabor filter's harmonic factor. Example: set_params(gabor_freqs="1,2,4,8,16,32,64")
        
        Parameters
        ----------
            args: Strings containing parameter names to get the value of. (Optional)

        Returns:
            dict: A dictionary mapping the parameter name to the value
        """
        vars = list(args)
        
        return get_params_imp(vars)
        
        
    def create_arrow_file(self, path: str="NyxusFeatures.arrow"):
        """Creates an Arrow IPC file containing the features.
        
        This method must be called after calling one of the featurize methods.

        Parameters
        ----------
        path: Path to write the arrow file to. (Optional, default "NyxusFeatures.arrow")

        Returns
        -------
        None

        """
        create_arrow_file_imp(path)

    
    def get_arrow_ipc_file(self):
        """Returns the path to the Arrow IPC file.

        Parameters
        ----------
        None

        Returns
        -------
        Path to the Arrow IPC file (string)

        """
        
        return get_arrow_file_imp()
    
    def create_parquet_file(self, path: str="NyxusFeatures.parquet"):
        """Creates a Parquet file containing the features.
        
        This method must be called after calling one of the featurize methods.

        Parameters
        ----------
        path: Path to write the parquet file to. (Optional, default "NyxusFeatures.parquet")

        Returns
        -------
        None

        """
        
        create_parquet_file_imp(path)
    
    def get_parquet_file(self):
        """Returns the path to the Arrow IPC file.

        Parameters
        ----------
        None

        Returns
        -------
        Path to the Parquet file (string)

        """
        
        return get_parquet_file_imp()
    
    def get_arrow_memory_mapping(self):
        """Returns a memory mapping to the Arrow IPC file.
        
        This method creates a memory mapping between the Arrow IPC file on disk to allow
        for random access. This method does not consume addition RAM.

        Parameters
        ----------
        None

        Returns
        -------
        MemoryMappedFile 

        """
        
        if arrow_is_enabled_imp():
            arrow_file_path = self.get_arrow_ipc_file()
            
            if (arrow_file_path == ""):
                self.create_arrow_file()
                arrow_file_path = self.get_arrow_ipc_file()
            
            with pa.memory_map(arrow_file_path, 'rb') as source:
                array = pa.ipc.open_file(source).read_all()
            
            return array
        else:
            raise RuntimeError("Apache arrow is not enabled. Please rebuild Nyxus with Arrow support to enable this functionality.")
    
    
    def get_arrow_table(self):
        """Returns an arrow table containing the feature calculations.

        Parameters
        ----------
        None

        Returns
        -------
        pyarrow.Table 

        """
        
        return get_arrow_table_imp()
    
    def arrow_is_enabled(self):
        """Returns true if arrow support is enabled.

        Parameters
        ----------
        None

        Returns
        -------
        bool: If arrow support is enabled 
        """
        
        return arrow_is_enabled_imp()
    


class Nested:
    """Nyxus image feature extraction library / ROI hierarchy analyzer
    
    Valid aggregate functions are any functions available in pandas.DatFrame.aggregate,
    e.g. min, max, count, std. Lambda functions can also be passed. To provide a name to
    the aggregate function, pass in a list of tuples where the first element in the name
    and the second is the function, e.g. aggregate=[('nanmean', lambda x: np.nanmean(x))]. 
    
    Parameters
    ----------
        aggregate : list
            List of aggregate functions. Any aggregate function from Pandas can be used
            along with lambda functions.
	
	Example
	-------
	from nyxus import Nested, Nyxus
    
    int_path = '/home/data/6234838c6b123e21c8b736f5/tissuenet_tif/int'
    seg_path = '/home/data/6234838c6b123e21c8b736f5/tissuenet_tif/seg'
    
    nyx = Nyxus(["*ALL*"])
    
    features = nyx.featurize(int_path, seg_path, file_pattern='p[0-9]_y[0-9]_r[0-9]_c0\.ome\.tif')
 
	nn = Nested()
	
	parent_filepattern = 'p{r}_y{c}_r{z}_c1.ome.tif'
    child_filepattern = 'p{r}_y{c}_r{z}_c0.ome.tif'
    
	rels = nn.find_relations (seg_path, parent_filepattern, child_filepattern)
 
    df = nn.featurize(rels, features)
    """

    def __init__(self, aggregate: Optional[list] = []):
        
        self.aggregate = aggregate
    
    
    def find_relations(
        self,
        label_dir: str,
        parent_file_pattern: str, 
        child_file_pattern: str):
    
        """Finds parent-child relationships.

        Find parent-child relationships of parent files matching the parent_file_pattern
        and child files matching the child_file_pattern.

        Parameters
        ----------
        label_dir : str 
            Path to directory containing label images.
        parent_file_pattern: str 
            Regex filepattern to filter the parent files e.g. "p.*_c1\.ome\.tif".
        child_file_pattern : str
            Regex filepattern to filter the child files e.g. "p.*_c0\.ome\.tif".
        Returns
        -------
        rel : array
            array of <parent label>,<child label> structure
        """

        if not os.path.exists(label_dir):
            raise IOError (f"Provided label image directory '{label_dir}' does not exist.")

        header, string_data, numeric_data = findrelations_imp(label_dir, parent_file_pattern, child_file_pattern)

        df = pd.concat(
            [
                pd.DataFrame(string_data, columns=header[: string_data.shape[1]]),
                pd.DataFrame(numeric_data, columns=header[string_data.shape[1] :]),
            ],
            axis=1,
        )

        # Labels should always be uint.
        if "label" in df.columns:
            df["label"] = df.label.astype(np.uint32)

        return df
	
    def featurize(self, parent_child_map: pd.DataFrame, child_features: pd.DataFrame):
        """Join child ROI features to the parent-child map.

        Joins parent-child map from the find_relations method with the features from Nyxus. 
        When aggregate functions are provided from the constructor this method will apply 
        the aggregate functions to the joined DataFrame. When aggregate functions are not 
        provided, this method will return a pivoted DataFrame where the columns are grouped by
        the child labels and the rows are the ROI labels.

        Parameters
        ----------
        parent_child_map : pd.DataFrame
            Map of parent child relations from the find_relations method.
        child_features: pd.DataFrame
            Features of the child channel ROIs from Nyxus.find_relations method.

        Returns
        -------
        pd.DataFrame
            DataFrame containing aggregated features for each ROI when aggregate functions are provided.
            Pivoted DataFrame containing features the child ROI for each label when no aggregate functions are provided.
        """
        
        joined_df = parent_child_map.merge(child_features, left_on=['Child_Label'], right_on=['label'])
        
        feature_columns = list(joined_df.columns)[6:]

        if(self.aggregate == []):
            joined_df.apply(lambda x: x) # convert group_by object to dataframe
        
            return joined_df.pivot_table(index='label', columns='Child_Label', values=feature_columns)
        
        agg_features = {}
        for col in feature_columns:
            agg_features[col] = self.aggregate
            
        return joined_df.groupby(by='label').agg(agg_features)
    