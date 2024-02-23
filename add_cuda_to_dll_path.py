from pathlib import Path
import shutil

path = str(Path(__file__).parent.resolve())


shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cufft64_10.dll', path)
shutil.copyfile('C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin\\cudart64_110.dll', path)