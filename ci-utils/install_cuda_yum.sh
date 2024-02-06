#!/bin/bash
# Usage: $bash install_cuda_yum.sh --major_version <VERSION>
# Defaults:
#   $major_version = 12

#yum-config-manager --add-repo https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-rhel7.repo &&
yum clean all
curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-nvcc-11-3-11.3.109-1.x86_64.rpm -o cuda-nvcc-11-3-11.3.109-1.x86_64.rpm


echo "Installing nvcc version 11.3"
yum -y localinstall cuda-nvcc-11-3-11.3.109-1.x86_64.rpm

curl -L https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-toolkit-11-3-11.3.1-1.x86_64.rpm -o cuda-toolkit-11-3-11.3.1-1.x86_64.rpm

echo "Installing CUDA toolkit 11.3"
yum -y localinstall cuda-toolkit-11-3-11.3.1-1.x86_64.rpm

ls -al /usr/local
export PATH=$PATH:/usr/local/cuda/bin
nvcc --version