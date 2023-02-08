#include "pybind_vector.h"

pybind_vector::pybind_vector(const py::array_t<unsigned int>& vec) {
    py::buffer_info buffer = vec.request();
    data = static_cast<unsigned int*>(buffer.ptr);
    width = buffer.shape[0];
    height = buffer.shape[1];
}


unsigned int pybind_vector::xy(int i, int j) const {
    if ((i * height + j) >= width * height) {
        throw std::out_of_range("Index out of range for pybind_vector.");
    } 

    return data[(i * height + j)];
}