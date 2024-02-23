import sys
import shutil

path = str(sys.executable)
print(path)

shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cufft64_10.dll', path)
shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cudart64_110.dll', path)