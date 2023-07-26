# Basic pybind11 test in C++
- The example compiles a Python pyd file that is used by `main.py` to run a function in C++ from Python
- Expects Python 3+ and x64 targets

# Prerequisites
- Python with numpy installed: `pip install numpy`
- Visual Studio 2022
- premake5
- Windows or MacOS 
    - MacOS untested, premake-file prepared but might have to be modified.

# Quickstart
- see `premake5.lua` for how the Python includes and libs are resolved.
- run `premake5 vs2022` in the terminal to generate the visual studio solution. (`premake5 xcode4` on Mac)
- open `temp/pybind11 tests.sln`.
- open `pybind_test.cpp` in the solution project `python_pyd` and try to understand how the PYBIND11_MODULE macro works.
- build the project (shortcut F7).
- execute `python main_pyd.py` in the terminal inside the python folder.
- you can also open `main.cpp` in the solution project `cpp_main` to run the python interpreter from C++.

# Please note!
    The .pyd-file is copied to the same folder as main.py (the root). This means that the module is only available from there. If you want the module to be available globally on your computer, then you have to copy it to one of the default python interpreter search paths.

Relevant threads to read:
- https://stackoverflow.com/questions/45054860/extending-c-to-python-using-pybind11
- https://stackoverflow.com/questions/49582252/pybind-numpy-access-2d-nd-arrays