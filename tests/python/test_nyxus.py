import pyarrow.parquet as pq
import nyxus
import pytest
import numpy as np
import pandas as pd
import math
from pathlib import Path
from test_data import intens, seg
import os
import shutil
import time

class TestImport():
    def test_import(self):
        assert nyxus.__name__ == "nyxus"  
        
class TestNyxus():
        PATH = PATH = Path(__file__).with_name('data')
        
        @classmethod
        def setup_class(cls):
            os.mkdir('TestNyxusOut')

        @classmethod 
        def teardown_class(cls):
            shutil.rmtree('TestNyxusOut')
            try:
                os.remove('NyxusFeatures.arrow')
            except:
                print('No .arrow file to delete')
                
            try:
                os.remove('NyxusFeatures.parquet')
            except:
                print('No .parquet file to delete')
            

        def test_gabor_gpu(self):
            # cpu gabor
            cpu_nyx = nyxus.Nyxus(["GABOR"])
            if (nyxus.gpu_is_available()):
                cpu_nyx.using_gpu(False)
            cpu_features = cpu_nyx.featurize(intens, seg)
            
            assert cpu_nyx.error_message == ''

            if (nyxus.gpu_is_available()):
                # gpu gabor
                gpu_nyx = nyxus.Nyxus(["GABOR"], using_gpu=0)
                gpu_nyx.using_gpu(True)
                gpu_features = gpu_nyx.featurize(intens, seg)
                
                assert gpu_features.equals(cpu_features)
            else:
                print("Gpu not available")
                assert True

        def test_gabor_customization (self):
            nyx = nyxus.Nyxus (["GABOR"])
            assert nyx is not None

            # test ability to digest valid parameters
            try:
                nyx.set_gabor_feature_params(kersize=16)
                nyx.set_gabor_feature_params(gamma=0.1)
                nyx.set_gabor_feature_params(sig2lam=0.8)
                nyx.set_gabor_feature_params(f0=0.1)
                nyx.set_gabor_feature_params(thold=0.025)
                nyx.set_gabor_feature_params(freqs=[1], thetas=[30])
                nyx.set_gabor_feature_params(freqs=[1,2,4,8,16,32,64], thetas=[15, 30, 45, 75, 90, 105, 115])
            except Exception as exc:
                assert False, f"set_gabor_feature_params(valid argument) raised an exception {exc}"

            # test ability to intercept invalid values
            with pytest.raises (Exception):
                nyx.set_gabor_feature_params(kersize=16.789)
            with pytest.raises (Exception):
                nyx.set_gabor_feature_params(gamma="notAnumber")
            with pytest.raises (Exception):
                nyx.set_gabor_feature_params(sig2lam="notAnumber")
                nyx.set_gabor_feature_params(f0="notAnumber")
                nyx.set_gabor_feature_params(thetas="notAnumber")
                nyx.set_gabor_feature_params(thold="notAnumber")
            with pytest.raises (Exception):
                nyx.set_gabor_feature_params(freqs=["notAnumber"])
            with pytest.raises (Exception):
                nyx.set_gabor_feature_params(freqs="notAList")
        
        def test_get_default_params(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            
            assert 0 == 1
            assert nyx is not None
            
            # actual
            a = nyx.get_params()
            
            # expected
            e = {
                'coarse_gray_depth': 256,
                'features': ['*ALL*'],
                'gabor_f0': 0.1,
                'gabor_freqs': [4.0, 16.0, 32.0, 64.0],
                'gabor_thetas': [0.0, 45.0, 90.0, 135.0],
                'gabor_gamma': 0.1,
                'gabor_kersize': 16,
                'gabor_sig2lam': 0.8,
                'gabor_thold': 0.025,
                'ibsi': 0,
                'n_feature_calc_threads': 4,
                'n_loader_threads': 1, 
                'neighbor_distance': 5, 
                'pixels_per_micron': 1.0
                }
            
            for key in a:
                
                if (isinstance(a[key], float)):
                    assert a[key] == pytest.approx(e[key])
                else:
                    assert a[key] == e[key]

        def test_get_params(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            params = nyx.get_params('coarse_gray_depth', 'features', 'gabor_f0')
            
            result = {'coarse_gray_depth': 256, 
                      'features': ['*ALL*'], 
                      'gabor_f0': 0.1}
            
            assert len(params) == 3
            
            for key in params:
                
                if (isinstance(params[key], float)):
                    assert params[key] == pytest.approx(result[key])
                else:
                    assert params[key] == pytest.approx(result[key])

        def test_set_params(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None

            new_values ={'coarse_gray_depth': 512, 
                        'features': ['*ALL*'], 
                        'gabor_f0': 0.1, 
                        'gabor_freqs': [1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0], 
                        'gabor_thetas': [0, 30, 60, 90, 120, 150, 180],
                        'gabor_gamma': 0.1, 
                        'gabor_kersize': 16, 
                        'gabor_sig2lam': 0.8, 
                        'gabor_thold': 0.025, 
                        'ibsi': 0, 
                        'n_loader_threads': 1, 
                        'n_feature_calc_threads': 4, 
                        'neighbor_distance': 5, 
                        'pixels_per_micron': 1.0}
            
            nyx.set_params(
                **new_values
            )
            
            params = nyx.get_params()
            
            for key in params:
                    
                if (isinstance(params[key], float)):
                    assert params[key] == pytest.approx(new_values[key])
                else:
                    assert params[key] == pytest.approx(new_values[key])   

        def test_set_single_param(self):
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            nyx.set_params (coarse_gray_depth = 125)
            actual = nyx.get_params()
            expected = {'coarse_gray_depth': 125}
            assert actual['coarse_gray_depth'] == expected['coarse_gray_depth']
            
        
        def test_set_environment_all(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            nyx.set_environment_params(
                features = ["GABOR"],
                neighbor_distance = 2,
                pixels_per_micron = 2,
                coarse_gray_depth = 2,
                n_feature_calc_threads = 2,
                n_loader_threads = 2
            )

            # actual
            a = nyx.get_params()

            # expected
            e = {
                'features': ["GABOR"],
                'neighbor_distance': 2,
                'pixels_per_micron': 2,
                'coarse_gray_depth': 2,
                'n_feature_calc_threads': 2,
                'n_loader_threads': 2
            }
                
            # compare
            for key in e:
                if (isinstance(e[key], float)):
                    assert e[key] == pytest.approx(a[key])
                else:
                    assert e[key] == a[key]
  
        def test_constructor_with_gabor(self):
            
            nyx = nyxus.Nyxus (
                ["*ALL*"],
                gabor_kersize = 1,
                gabor_gamma = 1,
                gabor_sig2lam = 1,
                gabor_f0 = 1,
                gabor_thold = 1,
                gabor_thetas = [10, 20, 30, 40, 50],
                gabor_freqs = [1, 2, 3, 4, 5])
            
            assert nyx is not None
            
            params = nyx.get_params()
            
            result = {'coarse_gray_depth': 256, 
                      'features': ['*ALL*'], 
                      'gabor_f0': 1, 
                      'gabor_freqs': [1, 2, 3, 4, 5], 
                      'gabor_gamma': 1, 
                      'gabor_kersize': 1, 
                      'gabor_sig2lam': 1, 
                      'gabor_thetas': [10, 20, 30, 40, 50], 
                      'gabor_thold': 1, 
                      'ibsi': 0, 
                      'n_loader_threads': 1, 
                      'n_feature_calc_threads': 4, 
                      'neighbor_distance': 5, 
                      'pixels_per_micron': 1.0}
            
            for key in params:
                
                if (isinstance(params[key], float)):
                    assert params[key] == pytest.approx(result[key])
                else:
                    assert params[key] == pytest.approx(result[key])    
            
                
        def test_in_memory_2d(self):
                
            cpu_nyx = nyxus.Nyxus(["*ALL_GLCM*"], ibsi=True)
            
            names = ["test_name_1"]

            cpu_features = cpu_nyx.featurize(intens[0], seg[0], names, names)
            
            assert cpu_nyx.error_message == ''
            
        def test_in_memory_3d(self):
            
            cpu_nyx = nyxus.Nyxus([
                "GLCM_ASM", "GLCM_CONTRAST", "GLCM_CORRELATION", "GLCM_DIFAVE", 
                "GLCM_DIFENTRO", "GLCM_DIFVAR", "GLCM_ENERGY", "GLCM_ENTROPY",
                "GLCM_HOM1", "GLCM_INFOMEAS1", "GLCM_INFOMEAS2", "GLCM_IDM", 
                "GLCM_SUMAVERAGE", "GLCM_SUMENTROPY", "GLCM_SUMVARIANCE", "GLCM_VARIANCE"], 
            ibsi=True)
            
            names = ["test_name_1", "test_name_2", "test_name_3", "test_name_4"]

            cpu_features = cpu_nyx.featurize(intens, seg, names, names)
            
            assert cpu_nyx.error_message == ''

            print(cpu_features)

            means = cpu_features.mean(numeric_only=True)

            mean_values = means.tolist()

            mean_values.pop(0)

            averaged_results = []

            i = 0
            while (i < len(mean_values)):
                averaged_results.append(sum(mean_values[i:i+4])/4)
                i += 4
                
            print(averaged_results)
                
            # check IBSI values
            assert pytest.approx(averaged_results[0], 0.01) == 0.368 # angular2ndmoment
            assert pytest.approx(averaged_results[1], 0.01) == 5.28 # contrast 
            assert pytest.approx(averaged_results[2], 0.01) == -0.0121 # correlation
            assert pytest.approx(averaged_results[4], 0.01) == 1.40 # difference entropy
            assert pytest.approx(averaged_results[5], 0.1) == 2.90 # difference variance#

        @pytest.mark.arrow
        def test_make_arrow_ipc(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            features = nyx.featurize(intens, seg)
            
            if (not nyx.arrow_is_enabled()):
                
                with pytest.raises (Exception):
                    nyx.create_arrow_file()
                    
                with pytest.raises (Exception):
                    arrow_array = nyx.get_arrow_memory_mapping()
                return
            
            nyx.create_arrow_file()
            
            arrow_array = nyx.get_arrow_memory_mapping()
            
            for col in features:
                column_list = features[col].tolist()
                arrow_list = arrow_array[col]
                
                for i in range(len(column_list)):
                    feature_value = column_list[i]
                    arrow_value = arrow_list[i].as_py()
                    
                    #skip nan values
                    if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                        if (not math.isnan(arrow_value)):
                            assert False

                        continue
                    assert feature_value == arrow_value
            
            path = nyx.get_arrow_ipc_file()
        
        @pytest.mark.arrow
        def test_arrow_ipc(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            arrow_path = nyx.featurize(intens, seg, output_type="arrow", output_path='TestNyxusOut')
            
            if (not nyx.arrow_is_enabled()):
                
                with pytest.raises (Exception):
                    nyx.create_arrow_file()
                    
                with pytest.raises (Exception):
                    arrow_array = nyx.get_arrow_memory_mapping()
                return

            features = nyx.featurize(intens, seg)
            
            arrow_array = nyx.get_arrow_memory_mapping()
            
            for col in features:
                column_list = features[col].tolist()
                arrow_list = arrow_array[col]
                
                for i in range(len(column_list)):
                    feature_value = column_list[i]
                    arrow_value = arrow_list[i].as_py()
                    
                    #skip nan values
                    if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                        if (not math.isnan(arrow_value)):
                            assert False

                        continue
                    assert feature_value == arrow_value
        
        @pytest.mark.arrow
        def test_arrow_ipc_no_path(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            arrow_path = nyx.featurize(intens, seg, output_type="arrow")
            
            assert arrow_path == 'NyxusFeatures.arrow'
            
            if (not nyx.arrow_is_enabled()):
                
                with pytest.raises (Exception):
                    nyx.create_arrow_file()
                    
                with pytest.raises (Exception):
                    arrow_array = nyx.get_arrow_memory_mapping()
                return

            features = nyx.featurize(intens, seg)
            
            arrow_array = nyx.get_arrow_memory_mapping()
            
            for col in features:
                column_list = features[col].tolist()
                arrow_list = arrow_array[col]
                
                for i in range(len(column_list)):
                    feature_value = column_list[i]
                    arrow_value = arrow_list[i].as_py()
                    
                    #skip nan values
                    if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                        if (not math.isnan(arrow_value)):
                            assert False

                        continue
                    assert feature_value == arrow_value
        
        @pytest.mark.arrow
        def test_arrow_ipc_no_create(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            features = nyx.featurize(intens, seg)
            
            if (not nyx.arrow_is_enabled()):
                with pytest.raises (Exception):
                    arrow_array = nyx.get_arrow_memory_mapping()
                
                return
            
            arrow_array = nyx.get_arrow_memory_mapping()
            
            for col in features:
                column_list = features[col].tolist()
                arrow_list = arrow_array[col]
                
                for i in range(len(column_list)):
                    feature_value = column_list[i]
                    arrow_value = arrow_list[i].as_py()
                    
                    #skip nan values
                    if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                        if (not math.isnan(arrow_value)):
                            assert False

                        continue
                    assert feature_value == arrow_value
                    
            path = nyx.get_arrow_ipc_file()
            
        @pytest.mark.arrow         
        def test_arrow_ipc_path(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            features = nyx.featurize(intens, seg)
            
            if (not nyx.arrow_is_enabled()):
                with pytest.raises (Exception):
                    nyx.create_arrow_file()
                return
            
            nyx.create_arrow_file()
            
            path = nyx.get_arrow_ipc_file()
            
            assert path == 'NyxusFeatures.arrow'
            
        @pytest.mark.arrow  
        def test_arrow_ipc_path_no_create(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            if (not nyx.arrow_is_enabled()):
                assert True
                return
            
            features = nyx.featurize(intens, seg)
            
            if (not nyx.arrow_is_enabled()):
                with pytest.raises (Exception):
                    path = nyx.get_arrow_ipc_file()
                return
                    
            path = nyx.get_arrow_ipc_file()
            
            assert path == 'NyxusFeatures.arrow'

        
        @pytest.mark.arrow        
        def test_parquet_writer(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
        
            
            if (not nyx.arrow_is_enabled()):
                with pytest.raises (Exception):
                     nyx.create_parquet_file()
            
                with pytest.raises (Exception):
                    parquet_file = nyx.get_parquet_file()
                    
                return
            
            features = nyx.featurize(intens, seg)

            parquet_file = nyx.featurize(intens, seg, output_type="parquet", output_path='TestNyxusOut')
            
            # Read the Parquet file into a Pandas DataFrame
            parquet_df = pq.read_table(parquet_file).to_pandas()
                
            
            for col in features:
                column_list = features[col].tolist()
                arrow_list = parquet_df[col].tolist()
                
                for i in range(len(column_list)):
                    feature_value = column_list[i]
                    arrow_value = arrow_list[i]
                    
                    #skip nan values
                    if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                        if (not math.isnan(arrow_value)):
                            assert False

                        continue
                    assert feature_value == arrow_value
                    
        @pytest.mark.arrow     
        def test_parquet_writer(self):
                
                nyx = nyxus.Nyxus (["*ALL*"])
                assert nyx is not None
            
                
                if (not nyx.arrow_is_enabled()):
                    with pytest.raises (Exception):
                        nyx.create_parquet_file()
                
                    with pytest.raises (Exception):
                        parquet_file = nyx.get_parquet_file()
                        
                    return
                
                features = nyx.featurize(intens, seg)

                parquet_file = nyx.featurize(intens, seg, output_type="parquet")
                
                assert parquet_file == "NyxusFeatures.parquet"
                
                # Read the Parquet file into a Pandas DataFrame
                parquet_df = pq.read_table(parquet_file).to_pandas()
                    
                
                for col in features:
                    column_list = features[col].tolist()
                    arrow_list = parquet_df[col].tolist()
                    
                    for i in range(len(column_list)):
                        feature_value = column_list[i]
                        arrow_value = arrow_list[i]
                        
                        #skip nan values
                        if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                            if (not math.isnan(arrow_value)):
                                assert False

                            continue
                        assert feature_value == arrow_value
        
        @pytest.mark.arrow
        def test_arrow_ipc_get_table(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            arrow_path = nyx.featurize(intens, seg, output_type="arrow")
            
            assert arrow_path == 'NyxusFeatures.arrow'
            
            if (not nyx.arrow_is_enabled()):
                
                with pytest.raises (Exception):
                    nyx.create_arrow_file()
                    
                with pytest.raises (Exception):
                    arrow_array = nyx.get_arrow_memory_mapping()
                return

            features = nyx.featurize(intens, seg)
            
            arrow_table = nyx.get_arrow_table(arrow_path)
            
            arrow_df = arrow_table.to_pandas()
            
            for col in features:
                column_list = features[col].tolist()
                arrow_list = arrow_df[col].tolist()
                
                for i in range(len(column_list)):
                    feature_value = column_list[i]
                    arrow_value = arrow_list[i]
                    
                    #skip nan values
                    if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                        if (not math.isnan(arrow_value)):
                            assert False

                        continue
                    assert feature_value == arrow_value
                    
        @pytest.mark.arrow
        def test_parquet_get_table(self):
            
            nyx = nyxus.Nyxus (["*ALL*"])
            assert nyx is not None
            
            arrow_path = nyx.featurize(intens, seg, output_type="parquet")
            
            assert arrow_path == 'NyxusFeatures.parquet'
            
            if (not nyx.arrow_is_enabled()):
                
                with pytest.raises (Exception):
                    nyx.create_arrow_file()
                    
                with pytest.raises (Exception):
                    arrow_array = nyx.get_arrow_memory_mapping()
                return

            features = nyx.featurize(intens, seg)
            
            arrow_table = nyx.get_arrow_table(arrow_path)
            
            arrow_df = arrow_table.to_pandas()
            
            for col in features:
                column_list = features[col].tolist()
                arrow_list = arrow_df[col].tolist()
                
                for i in range(len(column_list)):
                    feature_value = column_list[i]
                    arrow_value = arrow_list[i]
                    
                    #skip nan values
                    if (isinstance(feature_value, (int, float)) and math.isnan(feature_value)):
                        if (not math.isnan(arrow_value)):
                            assert False

                        continue
                    assert feature_value == arrow_value