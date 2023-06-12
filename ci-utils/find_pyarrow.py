import pyarrow as pa
import platform
path=pa.get_library_dirs()[0] + '/libarrow_python'
operating_system = platform.system()

file = ''
if operating_system == 'Linux':
    path += '.so'
elif operating_system == 'Darwin':
    path += '.dylib'
elif operating_system == 'Windows':
    path = pa.get_libraries() + '\libarrow_python.dll'
    


print(path)