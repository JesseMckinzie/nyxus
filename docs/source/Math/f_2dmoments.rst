
2D moments
==========

Raw moments
-----------

Raw (spatial) moments :math:`m_{ij}` of a 2-dimensional greyscale image  :math:`I(x,y)`` are calculated as

.. math::
   
   m_{{ij}}=\sum _{x}\sum _{y}x^{i}y^{j}I(x,y)

Spatial moment features are calculated as:

| SPAT_MOMENT_00 :math:`=m_{00}` 
| SPAT_MOMENT_01 :math:`=m_{01}`   
| SPAT_MOMENT_02 :math:`=m_{02}`    
| SPAT_MOMENT_03 :math:`=m_{03}`   
| SPAT_MOMENT_10 :math:`=m_{10}`   
| SPAT_MOMENT_11 :math:`=m_{11}`  
| SPAT_MOMENT_12 :math:`=m_{12}`   
| SPAT_MOMENT_20 :math:`=m_{20}`    
| SPAT_MOMENT_21 :math:`=m_{21}`    
| SPAT_MOMENT_30 :math:`=m_{30}`    

Central moments
---------------

A central moment :math:`\mu_{ij}` is defined as 

.. math::

   \mu_{{ij}}=\sum_{{x}}\sum _{{y}}(x-{\bar  {x}})^{i}(y-{\bar  {y}})^{j}I(x,y)

Central moment features are calculated as: 

| CENTRAL_MOMENT_02 :math:`=\mu_{02}`  
| CENTRAL_MOMENT_03 :math:`=\mu_{03}`   
| CENTRAL_MOMENT_11 :math:`=\mu_{11}`   
| CENTRAL_MOMENT_12 :math:`=\mu_{12}`   
| CENTRAL_MOMENT_20 :math:`=\mu_{20}`   
| CENTRAL_MOMENT_21 :math:`=\mu_{21}`   
| CENTRAL_MOMENT_30 :math:`=\mu_{20}`   

Normalized raw moments
----------------------

Raw (spatial) moments :math:`m_{ij}` of a 2-dimensional greyscale image :math:`I(x,y)` are calculated by

.. math::

   \displaystyle w_{{ij}} = \frac {\mu_{ij}}{\mu_{22}^ {max(i,j)} }

Spatial moment features are calculated as:

| NORM_SPAT_MOMENT_00 :math:`=w_{00}`
| NORM_SPAT_MOMENT_01 :math:`=w_{01}`    
| NORM_SPAT_MOMENT_02 :math:`=w_{02}`    
| NORM_SPAT_MOMENT_03 :math:`=w_{03}`   
| NORM_SPAT_MOMENT_10 :math:`=w_{10}` 
| NORM_SPAT_MOMENT_20 :math:`=w_{20}`  
| NORM_SPAT_MOMENT_30 :math:`=w_{30}`    

Normalized central moments
--------------------------

A normalized central moment :math:`\eta_{ij}` is defined as 

.. math::

   \eta_{{ij}}={\frac  {\mu_{{ij}}}{\mu_{{00}}^{{\left(1+{\frac  {i+j}{2}}\right)}}}}\,

where :math:`\mu _{{ij}}` is central moment.

Normalized central moment features are calculated as:

| NORM_CENTRAL_MOMENT_02 :math:`=\eta_{{02}}`
| NORM_CENTRAL_MOMENT_03 :math:`=\eta_{{03}}`
| NORM_CENTRAL_MOMENT_11 :math:`=\eta_{{11}}`
| NORM_CENTRAL_MOMENT_12 :math:`=\eta_{{12}}`
| NORM_CENTRAL_MOMENT_20 :math:`=\eta_{{20}}`
| NORM_CENTRAL_MOMENT_21 :math:`=\eta_{{21}}`
| NORM_CENTRAL_MOMENT_30 :math:`=\eta_{{30}}`

Hu moments
----------

Hu invariants HU_M1 through HU_M7 are calculated as


.. math::

    &\text{HU_M1} =\eta_{{20}}+\eta _{{02}} \\
    &HU_M2 =(\eta_{{20}}-\eta_{{02}})^{2}+4\eta_{{11}}^{2} \\
    &HU_M3 =(\eta_{{30}}-3\eta_{{12}})^{2}+(3\eta_{{21}}-\eta _{{03}})^{2} \\
    &HU_M4 =(\eta_{{30}}+\eta_{{12}})^{2}+(\eta_{{21}}+\eta _{{03}})^{2} \\
    &HU_M5 =(\eta_{{30}}-3\eta_{{12}})(\eta_{{30}}+\eta_{{12}})[(\eta_{{30}}+\eta_{{12}})^{2}-3(\eta_{{21}}+\eta_{{03}})^{2}]+ \\ 
    &(3\eta_{{21}}-\eta_{{03}})(\eta_{{21}}+\eta_{{03}})[3(\eta_{{30}}+\eta_{{12}})^{2}-(\eta_{{21}}+\eta _{{03}})^{2}] \\
    &HU_M6 =(\eta_{{20}}-\eta_{{02}})[(\eta_{{30}}+\eta_{{12}})^{2}-(\eta_{{21}}+\eta_{{03}})^{2}]+4\eta_{{11}}(\eta_{{30}}+\eta_{{12}})(\eta_{{21}}+\eta_{{03}}) \\
    &HU_M7 =(3\eta_{{21}}-\eta_{{03}})(\eta_{{30}}+\eta_{{12}})[(\eta_{{30}}+\eta_{{12}})^{2}-3(\eta_{{21}}+\eta_{{03}})^{2}]-(\eta_{{30}}-3\eta_{{12}})(\eta_{{21}}+\eta_{{03}})[3(\eta_{{30}}+\eta_{{12}})^{2}-(\eta_{{21}}+\eta _{{03}})^{2}]



| HU_M1 :math:`=\eta_{{20}}+\eta _{{02}}`
| HU_M2 :math:`=(\eta_{{20}}-\eta_{{02}})^{2}+4\eta_{{11}}^{2}`
| HU_M3 :math:`=(\eta_{{30}}-3\eta_{{12}})^{2}+(3\eta_{{21}}-\eta _{{03}})^{2}`
| HU_M4 :math:`=(\eta_{{30}}+\eta_{{12}})^{2}+(\eta_{{21}}+\eta _{{03}})^{2}`
| HU_M5 :math:`=(\eta_{{30}}-3\eta_{{12}})(\eta_{{30}}+\eta_{{12}})[(\eta_{{30}}+\eta_{{12}})^{2}-3(\eta_{{21}}+\eta_{{03}})^{2}]+ &(3\eta_{{21}}-\eta_{{03}})(\eta_{{21}}+\eta_{{03}})[3(\eta_{{30}}+\eta_{{12}})^{2}-(\eta_{{21}}+\eta _{{03}})^{2}]`
| HU_M6 :math:`=(\eta_{{20}}-\eta_{{02}})[(\eta_{{30}}+\eta_{{12}})^{2}-(\eta_{{21}}+\eta_{{03}})^{2}]+4\eta_{{11}}(\eta_{{30}}+\eta_{{12}})(\eta_{{21}}+\eta_{{03}})`
| HU_M7 :math:`=(3\eta_{{21}}-\eta_{{03}})(\eta_{{30}}+\eta_{{12}})[(\eta_{{30}}+\eta_{{12}})^{2}-3(\eta_{{21}}+\eta_{{03}})^{2}]-(\eta_{{30}}-3\eta_{{12}})(\eta_{{21}}+\eta_{{03}})[3(\eta_{{30}}+\eta_{{12}})^{2}-(\eta_{{21}}+\eta _{{03}})^{2}]`

Weighted raw moments
--------------------

Let :math:`W(x,y)` be a 2-dimensional weighted greyscale image such that each pixel of :math:`I` is weighted with respect to its distance to the nearest contour pixel: :math:`W(x,y) = \frac {I(x,y)} {\min_i d^2(x,y,C_i)}` where C - set of 2-dimensional ROI contour pixels, :math:`d^2(.)` - Euclidean distance norm. Weighted raw moments :math:`w_{Mij}`` are defined as

.. math::
   
   w_{Mij}=\sum_{x}\sum _{y}x^{i}y^{j}W(x,y)

Weighted central moments
------------------------

Weighted central moments :math:`w_{\mu ij}` are defined as 

.. math::

   w_{\mu ij} = \sum_{{x}}\sum_{{y}}(x-{\bar  {x}})^{i}(y-{\bar  {y}})^{j}W(x,y)

Weighted Hu moments
-------------------

A normalized weighted central moment :math:`w_{\eta ij}` is defined as 

.. math::
   
   w_{{\eta ij}}={\frac  {w_{{\mu ij}}}{w_{{\mu 00}}^{{\left(1+{\frac  {i+j}{2}}\right)}}}}\,

where :math:`w _{{\mu ij}}` is weighted central moment.
Weighted Hu moments are defined as

| WEIGHTED_HU_M1 :math:`=w_{\eta 20}+w_{\eta 02}` 
| WEIGHTED_HU_M2 :math:`=(w_{\eta 20}-w_{\eta 02})^{2}+4w_{\eta 11}^{2}` 
| WEIGHTED_HU_M3 :math:`=(w_{\eta 30}-3w_{\eta 12})^{2}+(3w_{\eta 21}-w _{\eta 03})^{2}` 
| WEIGHTED_HU_M4 :math:`=(w_{\eta 30}+w_{\eta 12})^{2}+(w_{\eta 21}+w _{\eta 03})^{2}` 
| WEIGHTED_HU_M5 :math:`=(w_{\eta 30}-3w_{\eta 12})(w_{\eta 30}+w_{\eta 12})[(w_{\eta 30}+w_{\eta 12})^{2}-3(w_{\eta 21}+ w_{\eta 03})^{2}]+(3w_{\eta 21}-w_{\eta 03})(w_{\eta 21}+w_{\eta 03})[3(w_{\eta 30}+w_{\eta 12})^{2}-(w_{\eta 21}+w _{\eta 03})^{2}]` 
| WEIGHTED_HU_M6 :math:`=(w_{\eta 20}-w_{\eta 02})[(w_{\eta 30}+w_{\eta 12})^{2}-(w_{\eta 21}+w_{\eta 03})^{2}]+4w_{\eta 11}(w_{\eta 30}+w_{\eta 12})(w_{\eta 21}+w_{\eta 03})` 
| WEIGHTED_HU_M7 :math:`=(3w_{\eta 21}-w_{\eta 03})(w_{\eta 30}+w_{\eta 12})[(w_{\eta 30}+w_{\eta 12})^{2}-3(w_{\eta 21}+w_{\eta 03})^{2}]-(w_{\eta 30}-3w_{\eta 12})(w_{\eta 21}+w_{\eta 03})[3(w_{\eta 30}+w_{\eta 12})^{2}-(w_{\eta 21}+w _{\eta 03})^{2}]` 
