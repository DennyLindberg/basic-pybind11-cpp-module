#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/embed.h>

#include <iostream>
#include <filesystem>
#include <fstream>

namespace py = pybind11;
namespace fs = std::filesystem;

bool load_python_file(const std::string& filePathStr, std::string& output)
{
	fs::path filePath = fs::current_path().parent_path() / filePathStr;

	output = "";
	if (!std::filesystem::exists(filePath))
	{
		std::cout << "File does not exist" << std::endl;
		return false;
	}

	std::ifstream InputFileStream(filePath.c_str());
	if (InputFileStream && InputFileStream.is_open())
	{
		output.assign((std::istreambuf_iterator<char>(InputFileStream)), std::istreambuf_iterator< char >());
		return true;
	}

	std::cout << "Could not open file for input stream" << std::endl;
	return false;
}

int main(int argc, wchar_t** argv)
{
	// https://pybind11.readthedocs.io/en/stable/advanced/embedding.html

	py::scoped_interpreter guard{};

	py::print("py::print: Hello world from C++");
	
	py::exec(R"(
import time
print("\n\npy::exec: Inline code time: {}".format(time.ctime()))
)");

	std::string file_contents = "";
	if (load_python_file("python/main_from_cpp.py", file_contents))
	{
		py::print("py::exec executing file...");
		py::exec(file_contents);
	}

	return 0;
}