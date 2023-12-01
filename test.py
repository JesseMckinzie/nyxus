from nyxus import Nyxus
nyx = Nyxus(["*ALL*"])

intensityDir = "data/int/"

maskDir = "data/seg/"

features = nyx.featurize_directory (intensityDir, maskDir, output_type="arrowipc", output_path="/Users/jmckinzie/Documents/GitHub/nyxus/tmp/")