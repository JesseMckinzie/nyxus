import sys
import os
import shutil

path = str(sys.executable)

path = os.path.dirname(path)

if not path.endswith('\\'):
    path += '\\'

shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cufft64_10.dll', path + 'cufft64_10.dll')
shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cudart64_110.dll', path + 'cudart64_110.dll')