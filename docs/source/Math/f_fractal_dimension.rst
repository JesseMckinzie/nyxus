
Fractal dimension features
==========================

Suppose :math:`A` is a shape's area and :math:`P` is its perimeter, and we are determining :math:`D`.

FRACT_DIM_BOXCOUNT
------------------

The underlying relation is :math:`n = b^{-D}`. The feature is calculated as the slope :math:`-D` of the plot :math:`\text {log} \: n` against :math:`\text {log} \: b`.

FRACT_DIM_PERIMETER
-------------------

The underlying relation is :math:`n = P^{2/D}`. The feature is calculated as the slope of the plot :math:`\text {log} \: A` against :math:`\text {log} \: P`.
