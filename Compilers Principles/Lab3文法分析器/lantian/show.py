
import pickle
f = open('./table.pkl', 'rb')
info = pickle.load(f);
print(info)