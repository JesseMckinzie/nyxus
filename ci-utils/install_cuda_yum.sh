#!/bin/bash
# Usage: $bash install_cuda_yum.sh --major_version <VERSION>
# Defaults:
#   $major_version = 12

#yum-config-manager --add-repo https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-rhel7.repo &&

# install nvcc
yum clean all
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-nvcc-11-3-11.3.109-1.x86_64.rpm -o cuda-nvcc-11-3-11.3.109-1.x86_64.rpm


echo "Installing nvcc version 11.3"
yum -y localinstall cuda-nvcc-11-3-11.3.109-1.x86_64.rpm

# install dependencies for cuda toolkit

# Requires: cuda-samples-11-3 >= 11.3.58
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-samples-11-3-11.3.58-1.x86_64.rpm -o cuda-samples-11-3-11.3.58-1.x86_64.rpm
echo "Installing cuda samples"
yum -y localinstall cuda-samples-11-3-11.3.58-1.x86_64.rpm

# Requires: cuda-tools-11-3 >= 11.3.1
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-tools-11-3-11.3.1-1.x86_64.rpm -o cuda-tools-11-3-11.3.1-1.x86_64.rpm
echo "Installing cuda tools"
yum -y localinstall cuda-tools-11-3-11.3.1-1.x86_64.rpm

# Requires: cuda-documentation-11-3 >= 11.3.111
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-documentation-11-3-11.3.111-1.x86_64.rpm -o cuda-documentation-11-3-11.3.111-1.x86_64.rpm
echo "Installing cuda documentation"
yum -y localinstall cuda-documentation-11-3-11.3.111-1.x86_64.rpm

# Requires: cuda-compiler-11-3 >= 11.3.1
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-compiler-11-3-11.3.1-1.x86_64.rpm -o cuda-compiler-11-3-11.3.1-1.x86_64.rpm
echo "Installing cuda compiler"
yum -y localinstall cuda-compiler-11-3-11.3.1-1.x86_64.rpm

# Requires: cuda-libraries-11-3 >= 11.3.1
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-libraries-11-3-11.3.1-1.x86_64.rpm -o cuda-libraries-11-3-11.3.1-1.x86_64.rpm
echo "Installing cuda libraries"
yum -y localinstall cuda-libraries-11-3-11.3.1-1.x86_64.rpm

# Requires: cuda-libraries-devel-11-3 >= 11.3.1
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-libraries-devel-11-3-11.3.1-1.x86_64.rpm -o cuda-libraries-devel-11-3-11.3.1-1.x86_64.rpm
echo "Installing cuda libraries devel"
yum -y localinstall cuda-libraries-devel-11-3-11.3.1-1.x86_64.rpm

# Requires: cuda-nvml-devel-11-3 >= 11.3.58
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-nvml-devel-11-3-11.3.58-1.x86_64.rpm -o cuda-nvml-devel-11-3-11.3.58-1.x86_64.rpm
echo "Installing cuda nvml"
yum -y localinstall cuda-nvml-devel-11-3-11.3.58-1.x86_64.rpm

# Install cuda toolkit
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-toolkit-11-3-11.3.1-1.x86_64.rpm -o cuda-toolkit-11-3-11.3.1-1.x86_64.rpm
echo "Installing CUDA toolkit 11.3"
yum -y localinstall cuda-toolkit-11-3-11.3.1-1.x86_64.rpm

ls -al /usr/local
export PATH=$PATH:/usr/local/cuda/bin
nvcc --version