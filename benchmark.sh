#!/bin/bash
start=`date +%s`

size="1000"
output="parquet"

./build/nyxus --features=*all_intensity* --intDir=/Users/jmckinzie/Documents/GitHub/nyxus/benchmark_data/data${size}/int --segDir=/Users/jmckinzie/Documents/GitHub/nyxus/benchmark_data/data${size}/seg --outDir=cli_out --filePattern=.* --outputType=${output}
end=`date +%s`

runtime=$((end-start))
echo total runtime: $runtime
