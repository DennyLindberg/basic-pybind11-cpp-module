import numpy as np
import pybind_test

factorialResult = pybind_test.factorial(5)

a = np.ones((10,3)) * 2
b = np.ones((10,3)) * 3 
addResult = pybind_test.add_arrays(a, b)

print(factorialResult)
print(addResult)