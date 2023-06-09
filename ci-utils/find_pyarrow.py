import pyarrow as pa
import platform
path=pa.get_library_dirs()[0] + '/libarrow_python'

operating_system = platform.system()

print(operating_system)

file = ''
if operating_system == 'Linux':
    file = '.so'
elif operating_system == 'Darwin':
    file = '.dylib'
elif operating_system == 'Windows':
    file = '.dll'

path += file

print(path)