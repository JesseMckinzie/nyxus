from .nyxus import Nyxus
from .nyxus import Nyxus3D
from .nyxus import Nested
from .functions import gpu_is_available, get_gpu_properties, gpu_is_enabled

from . import _version
__version__ = _version.get_versions()['version']
