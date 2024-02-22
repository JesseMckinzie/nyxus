import os

def add_cuda_to_path():
    if os.name != "nt":
        return
    os.add_dll_directory("C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.8\\bin")
            

add_cuda_to_path()
