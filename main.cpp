#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <iostream>

namespace py = pybind11;

std::string python_code = R"(
import time
print("\n\nPython time {}".format(time.ctime()))
)";

int main(int argc, wchar_t** argv)
{
	Py_Initialize();

	std::cout << "C++ Call Python Code";
	PyRun_SimpleString(python_code.c_str());

	std::cout << "\nC++ Start Python Interpreter\n\n";
	Py_Main(argc, argv); // call this instead to have an interactive interpreter

	Py_Finalize();

	return 0;
}