# Basic pybind11 test in C++

# Prerequisites
- Python with numpy installed: `pip install numpy`
- Visual Studio 2017
- premake5
- Windows or MacOS 
    - MacOS untested, premake-file prepared but might have to be modified.

# Quickstart
- run `premake5 vs2017` in the terminal to generate the visual studio solution. (`premake5 xcode4` on Mac)
- open `temp/pybind11 tests.sln`.
- open `pybind_test.cpp` in the solution and try to understand how the PYBIND11_MODULE macro works.
- build the project (shortcut F7).
- open `main.py` in the root folder and run it as you would any Python script.

# Please note!
    The .pyd-file is copied to the same folder as main.py (the root). This means that the module is only available from there. If you want the module to be available globally on your computer, then you have to copy it to one of the default python interpreter search paths.

Relevant threads to read:
- https://stackoverflow.com/questions/45054860/extending-c-to-python-using-pybind11
- https://stackoverflow.com/questions/49582252/pybind-numpy-access-2d-nd-arrays