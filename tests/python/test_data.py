import numpy as np

intens = np.array([
       [[1, 4, 4, 1, 1],
        [1, 4, 6, 1, 1],
        [4, 1, 6, 4, 1],
        [4, 4, 6, 4, 1]],
                   
       [[1, 4, 4, 1, 1],
        [1, 1, 6, 1, 1],
        [1, 1, 3, 1, 1],
        [4, 4, 6, 1, 1]],
       
       [[1, 4, 4, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 6, 1, 1],
        [1, 1, 6, 1, 1]],
       
       [[1, 4, 4, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 6, 1, 1]],
])

seg = np.array([
       [[1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1]],
                
       [[1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [0, 1, 1, 1, 1],
        [1, 1, 1, 1, 1]],
       
       [[1, 1, 1, 0, 0],
        [1, 1, 1, 1, 1],
        [1, 1, 0, 1, 1],
        [1, 1, 1, 1, 1]],
                
       [[1, 1, 1, 0, 0],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1]]
       
])
