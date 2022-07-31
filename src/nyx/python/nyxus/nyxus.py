from .backend import initialize_environment, process_data, findrelations_imp
import os
import numpy as np
import pandas as pd
from typing import Optional, List
import filepattern


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
    neighbor_distance: float (optional, default 5.0)
        Any two objects separated by a Euclidean distance (pixel units) greater than this
        value will not be be considered neighbors. This cutoff is used by all features which
        rely on neighbor identification.
    pixels_per_micron: float (optional, default 1.0)
        Specify the image resolution in terms of pixels per micron for unit conversion
        of non-unitless features.
    n_feature_calc_threads: int (optional, default 4)
        Number of threads to use for feature calculation parallelization purposes.
    n_loader_threads: int (optional, default 1)
        Number of threads to use for loading image tiles from disk. Note: image loading
        multithreading is very memory intensive. You should consider optimizing
        `n_feature_calc_threads` before increasing `n_loader_threads`.
    """

    def __init__(
        self,
        features: List[str],
        neighbor_distance: float = 5.0,
        pixels_per_micron: float = 1.0,
        n_feature_calc_threads: int = 4,
        n_loader_threads: int = 1,
    ):
        if neighbor_distance <= 0:
            raise ValueError("Neighbor distance must be greater than zero.")

        if pixels_per_micron <= 0:
            raise ValueError("Pixels per micron must be greater than zero.")

        if n_feature_calc_threads < 1:
            raise ValueError("There must be at least one feature calculation thread.")

        if n_loader_threads < 1:
            raise ValueError("There must be at least one loader thread.")

        initialize_environment(
            features,
            neighbor_distance,
            pixels_per_micron,
            n_feature_calc_threads,
            n_loader_threads,
        )

    def featurize(
        self,
        intensity_dir: str,
        label_dir: Optional[str] = None,
        file_pattern: Optional[str] = ".*",
    ):
        """Extract features from provided images.

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

        header, string_data, numeric_data = process_data(
            intensity_dir, label_dir, file_pattern
        )

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
		
class Nested:
    """Nyxus image feature extraction library / ROI hierarchy analyzer
	
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
            filepattern to filter the parent files e.g. "p{r}_y{c}_r{z}_c1.ome.tif".
        child_file_pattern : str
            filepattern to filter the child files e.g. "p{r}_y{c}_r{z}_c0.ome.tif".
        Returns
        -------
        rel : array
            array of <parent label>,<child label> structure
        """

        if not os.path.exists(label_dir):
            raise IOError (f"Provided label image directory '{label_dir}' does not exist.")
        
        parent_files = []
        child_files = []
        
        fp = filepattern.FilePattern(label_dir, parent_file_pattern)
        for file in fp():
            parent_files.append(str(file[0]['file']))
        
        fp = filepattern.FilePattern(label_dir, child_file_pattern)
        for file in fp():
            child_files.append(str(file[0]['file']))
            
        if (len(parent_files) is 0 or len(child_files) is 0):
            raise ValueError("No files found.")
            
        if (len(parent_files) != len(child_files)):
            raise ValueError("Number of files in parent channel does not match number of files in child channel.")
        
        header, string_data, numeric_data = findrelations_imp(parent_files, child_files)

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
        
        if "Child_Label" in df.columns:
            df["Child_Label"] = df.Child_Label.astype(np.uint32)
            
        if "Parent_Label" in df.columns:
                df["Parent_Label"] = df.Parent_Label.astype(np.uint32)

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
		