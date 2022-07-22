from nyxus import Nyxus, Nested

int_path = '/Users/jessemckinzie/Documents/GitHub/nyxus2/data/int'
seg_path = '/Users/jessemckinzie/Documents/GitHub/nyxus2/data/seg'

nyx = Nyxus(["GABOR"])

features = nyx.featurize(int_path, seg_path)
print('----------------')
print(features.columns)
print('----------------')

nest = Nested()

df = nest.find_relations(seg_path, '.*', '_c', '1', '0')

print()
print('df')
print(df)
print('-------------')
print(df.columns)