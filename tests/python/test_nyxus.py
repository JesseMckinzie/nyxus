import nyxus
import pytest
import time
from pathlib import Path
from test_data import data

"""
class TestImport():
    def test_import(self):
        assert nyxus.__name__ == "nyxus" 
        
class TestNyxus():
        PATH = PATH = Path(__file__).with_name('data')

        def test_gabor_gpu(self):
"""
                
print("before data")
print(data)
for dset in data:
    
    print(dset)
    
    intens = dset[0]
    seg = dset[1]
    
    print()
    print(intens)
    print()
    print(seg)
    
    # cpu gabor
    cpu_nyx = nyxus.Nyxus(["*ALL*"])
    if (nyxus.gpu_is_available()):
        cpu_nyx.using_gpu(False)
    cpu_features = cpu_nyx.featurize_memory(intens, seg)
    print("finished features")
    print(cpu_features)

    if (nyxus.gpu_is_available()):
        # gpu gabor
        gpu_nyx = nyxus.Nyxus(["GABOR"], using_gpu=0)
        gpu_nyx.using_gpu(True)
        gpu_features = gpu_nyx.featurize_memory(intens, seg)
        
        assert gpu_features.equals(cpu_features)
    else:
        print("Gpu not available")
        assert True
                
        