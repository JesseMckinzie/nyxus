def add_cuda_to_path():
    if os.name != "nt":
        return
    path = os.getenv("PATH")
    if not path:
        return 
    path_split = path.split(";")
    for folder in path_split:
        if "cuda" in folder.lower() or "tensorrt" in folder.lower():
            os.add_dll_directory(folder)
            
add_cuda_to_path()

from .nyxus import Nyxus
from .nyxus import Nyxus3D
from .nyxus import Nested
from .functions import gpu_is_available, get_gpu_properties

from . import _version
__version__ = _version.get_versions()['version']

import os

