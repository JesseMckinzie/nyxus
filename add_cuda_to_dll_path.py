import os

def add_cuda_to_path():
    if os.name != "nt":
        return
    path = os.getenv("PATH")
    if not path:
        return 
    path_split = path.split(";")
    for folder in path_split:
        if "cuda" in folder.lower() or "tensorrt" in folder.lower():
            os.add_dll_directory(folder)
            
add_cuda_to_path()