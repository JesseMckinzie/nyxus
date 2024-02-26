import sys
from pathlib import Path
import os
import shutil

path = path = str(Path(__file__).parent.resolve())

print("the full path is: ")
print(path)

#path = os.path.dirname(path)

if not path.endswith('\\'):
    path += '\\'

shutil.copytree('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin', path + 'tests\\python\\bin')
