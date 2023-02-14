#pragma once

#include <exception>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class pybind_vector {
        unsigned int * data;

    public:
        int width;
        int height; 

        pybind_vector(const py::array_t<unsigned int>& vec);
        unsigned int xy(int i, int j) const; 


        ~pybind_vector() {
            delete data;
        }

};