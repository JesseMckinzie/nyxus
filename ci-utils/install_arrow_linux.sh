mkdir -p $Z5_INSTALL_DIR
mkdir -p $Z5_INSTALL_DIR/include

curl -L https://github.com/apache/arrow/archive/refs/tags/apache-arrow-12.0.0.zip -o  arrow-apache-arrow-12.0.0.zip
unzip arrow-apache-arrow-12.0.0.zip
cd arrow-apache-arrow-12.0.0/
python3 -m venv pyarrow-dev
source ./pyarrow-dev/bin/activate
pip install -r python/requirements-build.txt
mkdir dist
export ARROW_HOME=$(pwd)/dist
export LD_LIBRARY_PATH=$(pwd)/dist/lib:$LD_LIBRARY_PATH
export CMAKE_PREFIX_PATH=$ARROW_HOME:$CMAKE_PREFIX_PATH
cd cpp/
mkdir build
cd build/
cmake -DCMAKE_INSTALL_PREFIX=$ARROW_HOME \
        -DCMAKE_INSTALL_LIBDIR=lib \
        -DCMAKE_BUILD_TYPE=Release \
        -DARROW_BUILD_TESTS=ON \
        -DARROW_COMPUTE=ON \
        -DARROW_CSV=ON \
        -DARROW_DATASET=ON \
        -DARROW_FILESYSTEM=ON \
        -DARROW_HDFS=ON \
        -DARROW_JSON=ON \
        -DARROW_PARQUET=ON \
        -DARROW_WITH_BROTLI=ON \
        -DARROW_WITH_BZ2=ON \
        -DARROW_WITH_LZ4=ON \
        -DARROW_WITH_SNAPPY=ON \
        -DARROW_WITH_ZLIB=ON \
        -DARROW_WITH_ZSTD=ON \
        -DPARQUET_REQUIRE_ENCRYPTION=ON \
        -DARROW_ACERO=ON \
        .. 
make -j4
make install
cd ../../
cd python/
export PYARROW_WITH_PARQUET=1
export PYARROW_WITH_DATASET=1
export PYARROW_PARALLEL=4
python setup.py build_ext --inplace
cd ../../