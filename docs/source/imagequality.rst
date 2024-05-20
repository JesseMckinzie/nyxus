Image Quality features
======================

Image quality features are available in Nyxus in the ImageQuality class to determine how blurry an image is. 
These features are available in the `IMAGE_QUALITY` feature group. 

The ImageQuality class is used similarly to Nyxus,

.. code-block:: python 
     
   from nyxus import ImageQuality
     
   int_path = 'path/to/intensity'
   seg_path = 'path/to/segmentation'

   imq = ImageQuality(['*ALL_IMQ*'])

   features = imq.feature_directory(int_path, seg_path)

The output will be a pandas DataFrame, just like in the Nyxus class.

The following features are included in the ImageQaulity class:

.. list-table::
   :header-rows: 1

   * - Image Quality feature code
     - Description
   * - FOCUS_SCORE
     - Uses edge detection to highlight regions where intesnity changes rapidly. Higher focus score means lower blurriness
   * - LOCAL_FOCUS_SCORE
     - Tiles image into non-overlapping regions and calculates the FOCUS_SCORE for each region. Higher local focus score means lower blurriness
   * - GLCM_DIS
     - Blurry images low dissimilarity
   * - GLCM_CORRELATION
     - Blurry images have a high correlation
   * - POWER_SPECTRUM
     - The slope of the image log-log power spectrum. A low score means a blurry image
   * - SATURATION
     - Percent of pixels at minimum and maximum pixel values
   * - SHARPNESS
     - Uses median-filtered image as indicator of edge scharpness. Values range from 0 to sqrt(2). Low scores indicate blurriness.