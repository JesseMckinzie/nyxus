
2D moments
==========

Raw moments
-----------

Raw (spatial) moments $m_{ij}$ of a 2-dimensional greyscale image  $I(x,y)$ are calculated as

Spatial moment features are calculated as:
SPAT_MOMENT\ *00 $=m*\ {00}$    
SPAT_MOMENT\ *01 $=m*\ {01}$    
SPAT_MOMENT\ *02 $=m*\ {02}$    
SPAT_MOMENT\ *03 $=m*\ {03}$    
SPAT_MOMENT\ *10 $=m*\ {10}$    
SPAT_MOMENT\ *11 $=m*\ {11}$    
SPAT_MOMENT\ *12 $=m*\ {12}$    
SPAT_MOMENT\ *20 $=m*\ {20}$    
SPAT_MOMENT\ *21 $=m*\ {21}$    
SPAT_MOMENT\ *30 $=m*\ {30}$    

Central moments
---------------

A central moment $\mu_{ij}$ is defined as 

$$\mu *{{ij}}=\sum *\ {{x}}\sum _{{y}}(x-{\bar  {x}})^{i}(y-{\bar  {y}})^{j}I(x,y)$$

Central moment features are calculated as:\
CENTRAL_MOMENT\ *02 $=\mu*\ {02}$   \
CENTRAL_MOMENT\ *03 $=\mu*\ {03}$   \
CENTRAL_MOMENT\ *11 $=\mu*\ {11}$   \
CENTRAL_MOMENT\ *12 $=\mu*\ {12}$   \
CENTRAL_MOMENT\ *20 $=\mu*\ {20}$   \
CENTRAL_MOMENT\ *21 $=\mu*\ {21}$   \
CENTRAL_MOMENT\ *30 $=\mu*\ {20}$   

Normalized raw moments
----------------------

Raw (spatial) moments $m_{ij}$ of a 2-dimensional greyscale image  I(x,y) are calculated by

$$\displaystyle w\ *{{ij}} = \frac {\mu*\ {ij}}{\mu_{22}^ {max(i,j)} }$$

Spatial moment features are calculated as:\
NORM_SPAT_MOMENT\ *00 $=w*\ {00}$    \
NORM_SPAT_MOMENT\ *01 $=w*\ {01}$    \
NORM_SPAT_MOMENT\ *02 $=w*\ {02}$    \
NORM_SPAT_MOMENT\ *03 $=w*\ {03}$    \
NORM_SPAT_MOMENT\ *10 $=w*\ {10}$    \
NORM_SPAT_MOMENT\ *20 $=w*\ {20}$    \
NORM_SPAT_MOMENT\ *30 $=w*\ {30}$    

Normalized central moments
--------------------------

A normalized central moment $\eta *{ij}$ is defined as 
$$\eta *\ {{ij}}={\frac  {\mu *{{ij}}}{\mu *\ {{00}}^{{\left(1+{\frac  {i+j}{2}}\right)}}}}\,\$$

where $\mu _{{ij}}$ is central moment.

Normalized central moment features are calculated as:\
NORM_CENTRAL_MOMENT\ *02 $=\eta *\ {{02}}$\
NORM_CENTRAL_MOMENT\ *03 $=\eta *\ {{03}}$\
NORM_CENTRAL_MOMENT\ *11 $=\eta *\ {{11}}$\
NORM_CENTRAL_MOMENT\ *12 $=\eta *\ {{12}}$\
NORM_CENTRAL_MOMENT\ *20 $=\eta *\ {{20}}$\
NORM_CENTRAL_MOMENT\ *21 $=\eta *\ {{21}}$\
NORM_CENTRAL_MOMENT\ *30 $=\eta *\ {{30}}$

Hu moments
----------

Hu invariants HU_M1 through HU_M7 are calculated as\

HU\ *M1 $=\eta *\ {{20}}+\eta _{{02}}$\
HU\ *M2 $=(\eta *\ {{20}}-\eta *{{02}})^{2}+4\eta *\ {{11}}^{2}$\
HU\ *M3 $=(\eta *\ {{30}}-3\eta *{{12}})^{2}+(3\eta *\ {{21}}-\eta _{{03}})^{2}$\
HU\ *M4 $=(\eta *\ {{30}}+\eta *{{12}})^{2}+(\eta *\ {{21}}+\eta _{{03}})^{2}$\
HU\ *M5 $=(\eta *\ {{30}}-3\eta *{{12}})(\eta *\ {{30}}+\eta *{{12}})[(\eta *\ {{30}}+\eta *{{12}})^{2}-3(\eta *\ {{21}}+\eta *{{03}})^{2}]+(3\eta *\ {{21}}-\eta *{{03}})(\eta *\ {{21}}+\eta *{{03}})[3(\eta *\ {{30}}+\eta *{{12}})^{2}-(\eta *\ {{21}}+\eta _{{03}})^{2}]$\
HU\ *M6 $=(\eta *\ {{20}}-\eta *{{02}})[(\eta *\ {{30}}+\eta *{{12}})^{2}-(\eta *\ {{21}}+\eta *{{03}})^{2}]+4\eta *\ {{11}}(\eta *{{30}}+\eta *\ {{12}})(\eta *{{21}}+\eta *\ {{03}})$\
HU\ *M7 $=(3\eta *\ {{21}}-\eta *{{03}})(\eta *\ {{30}}+\eta *{{12}})[(\eta *\ {{30}}+\eta *{{12}})^{2}-3(\eta *\ {{21}}+\eta *{{03}})^{2}]-(\eta *\ {{30}}-3\eta *{{12}})(\eta *\ {{21}}+\eta *{{03}})[3(\eta *\ {{30}}+\eta *{{12}})^{2}-(\eta *\ {{21}}+\eta _{{03}})^{2}]$\

Weighted raw moments
--------------------

Let $W(x,y)$ be a 2-dimensional weighted greyscale image such that each pixel of $I$ is weighted with respect to its distance to the nearest contour pixel: $W(x,y) = \frac {I(x,y)} {\min_i d^2(x,y,C\ *i)}$ where C - set of 2-dimensional ROI contour pixels, $d^2(.)$ - Euclidean distance norm. Weighted raw moments $w*\ {Mij}$ are defined as

$$\displaystyle w\ *{Mij}=\sum *\ {x}\sum _{y}x^{i}y^{j}W(x,y)\$$

Weighted central moments
------------------------

Weighted central moments $w\ *{\mu ij}$ are defined as 
$$w*\ {\mu ij} = \sum *{{x}}\sum *\ {{y}}(x-{\bar  {x}})^{i}(y-{\bar  {y}})^{j}W(x,y)$$

Weighted Hu moments
-------------------

A normalized weighted central moment $w *{\eta ij}$ is defined as 
$$w *\ {{\eta ij}}={\frac  {w *{{\mu ij}}}{w *\ {{\mu 00}}^{{\left(1+{\frac  {i+j}{2}}\right)}}}}\,\$$

where $w _{{\mu ij}}$ is weighted central moment.
Weighted Hu moments are defined as

WEIGHTED_HU\ *M1 $=w *\ {\eta 20}+w _{\eta 02}$\
WEIGHTED_HU\ *M2 $=(w *\ {\eta 20}-w *{\eta 02})^{2}+4w *\ {\eta 11}^{2}$\
WEIGHTED_HU\ *M3 $=(w *\ {\eta 30}-3w *{\eta 12})^{2}+(3w *\ {\eta 21}-w _{\eta 03})^{2}$\
WEIGHTED_HU\ *M4 $=(w *\ {\eta 30}+w *{\eta 12})^{2}+(w *\ {\eta 21}+w _{\eta 03})^{2}$\
WEIGHTED_HU\ *M5 $=(w *\ {\eta 30}-3w *{\eta 12})(w *\ {\eta 30}+w *{\eta 12})[(w *\ {\eta 30}+w *{\eta 12})^{2}-3(w *\ {\eta 21}+w *{\eta 03})^{2}]+(3w *\ {\eta 21}-w *{\eta 03})(w *\ {\eta 21}+w *{\eta 03})[3(w *\ {\eta 30}+w *{\eta 12})^{2}-(w *\ {\eta 21}+w _{\eta 03})^{2}]$\
WEIGHTED_HU\ *M6 $=(w *\ {\eta 20}-w *{\eta 02})[(w *\ {\eta 30}+w *{\eta 12})^{2}-(w *\ {\eta 21}+w *{\eta 03})^{2}]+4w *\ {\eta 11}(w *{\eta 30}+w *\ {\eta 12})(w *{\eta 21}+w *\ {\eta 03})$\
WEIGHTED_HU\ *M7 $=(3w *\ {\eta 21}-w *{\eta 03})(w *\ {\eta 30}+w *{\eta 12})[(w *\ {\eta 30}+w *{\eta 12})^{2}-3(w *\ {\eta 21}+w *{\eta 03})^{2}]-(w *\ {\eta 30}-3w *{\eta 12})(w *\ {\eta 21}+w *{\eta 03})[3(w *\ {\eta 30}+w *{\eta 12})^{2}-(w *\ {\eta 21}+w _{\eta 03})^{2}]$
