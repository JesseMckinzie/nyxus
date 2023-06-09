import pyarrow as pa
import platform
path=pa.get_library_dirs()[0] + '/libarrow_python'

operating_system = platform.system()

file = ''
if operating_system == 'linux':
    file = '.so'
elif operating_system == 'darwin':
    file = '.dylib'
elif operating_system == 'windows':
    file = '.dll'

path += file

print(path)