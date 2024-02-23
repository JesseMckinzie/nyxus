import sys
import os
from pathlib import Path
import shutil

path = str(Path(__file__).parent.resolve())

if not path.endswith('\\'):
    path += '\\'
    
print("the paths are:")
print(path + 'cufft64_10.dll')
print(path + 'cudart64_110.dll')

shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cufft64_10.dll', path + 'cufft64_10.dll')
shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cudart64_110.dll', path + 'cudart64_110.dll')