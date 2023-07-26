#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

int factorial(int i) 
{
	return (i < 2)? 1 : i*factorial(i-1);
}

// Example taken from https://stackoverflow.com/questions/49582252/pybind-numpy-access-2d-nd-arrays
py::array_t<double> add_arrays(py::array_t<double> input1, py::array_t<double> input2) 
{
	auto buf1 = input1.request(); 
	auto buf2 = input2.request();
	if (buf1.size != buf2.size)
	{
		throw std::runtime_error("Input shapes must match");
	}

	/*  allocate the buffer */
	py::array_t<double> result = py::array_t<double>(buf1.size);

	auto buf3 = result.request();
	double	*ptr1 = (double *)buf1.ptr,
			*ptr2 = (double *)buf2.ptr,
			*ptr3 = (double *)buf3.ptr;
	py::ssize_t X = buf1.shape[0];
	py::ssize_t Y = buf1.shape[1];

	for (py::ssize_t idx = 0; idx < X; idx++)
	{
		for (py::ssize_t idy = 0; idy < Y; idy++)
		{
			py::ssize_t index = idx*Y + idy;
			ptr3[index] = ptr1[index] + ptr2[index];
		}
	}

	// reshape array to match input shape
	result.resize({ X,Y });
	return result;
}

PYBIND11_MODULE(pybind_test, m) {
	m.doc() = "pybind11 example plugin";

	m.def("factorial", &factorial, "Computes n! = n*(n-1)*...*(n-n+1)");
	m.def("add_arrays", &add_arrays, "Add two NumPy arrays");
}
