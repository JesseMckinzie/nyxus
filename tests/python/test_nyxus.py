import nyxus
import pytest
import time
from pathlib import Path
from test_download_data import download
from . import test_data

class TestImport():
    def test_import(self):
        assert nyxus.__name__ == "nyxus" 
        
class TestNyxus():
        PATH = PATH = Path(__file__).with_name('data')

        def test_gabor_gpu(self):
                
                for dset in test_data.data:
                    
                    intens = dset[0]
                    seg = dset[1]
                    
                    # cpu gabor
                    cpu_nyx = nyxus.Nyxus(["GABOR"])
                    if (nyxus.gpu_is_available()):
                        cpu_nyx.using_gpu(False)
                    cpu_features = cpu_nyx.featurize_memory(intens, seg)
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
                
        