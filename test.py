from nyxus import Nyxus
import numpy as np
import dask.array as da


nyx = Nyxus(["*ALL*"])

intens = [
    [[1, 4, 4, 1, 1],
        [1, 4, 6, 1, 1],
        [4, 1, 6, 4, 1],
        [4, 4, 6, 4, 1]],
                   
    [[1, 4, 4, 1, 1],
    [1, 1, 6, 1, 1],
    [1, 1, 3, 1, 1],
    [4, 4, 6, 1, 1]]
]

seg = [
    [[1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1]],
                
    [[1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1],
    [0, 1, 1, 1, 1],
    [1, 1, 1, 1, 1]]
]

dask_intens = da.from_array(intens)
dask_seg = da.from_array(seg)

features = nyx.featurize_dask(intens, seg)

print(features)
