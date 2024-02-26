import sys
import os
import shutil

path = str(sys.executable)

print("the full path is: ")
print(path)

path = os.path.dirname(path)

if not path.endswith('\\'):
    path += '\\'

shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin', path)
