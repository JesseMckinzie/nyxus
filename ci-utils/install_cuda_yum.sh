#!/bin/bash
# Usage: $bash install_cuda_yum.sh --major_version <VERSION>
# Defaults:
#   $major_version = 12

yum-config-manager --add-repo https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-rhel7.repo &&
yum clean all


echo "Installing CUDA version 11.3"
yum -y install cuda-toolkit-11-3-1-11.3.1


ls -al /usr/local
export PATH=$PATH:/usr/local/cuda/bin
nvcc --version