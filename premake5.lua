-- run premake command to generate a solution file in the temp folder
--  premake5 vs2017
--  premake5 gmake2
--  premake5 xcode4

function queryTerminal(command)
    local success, handle = pcall(io.popen, command)
    if not success then 
        return ""
    end

    result = handle:read("*a")
    handle:close()
    result = string.gsub(result, "\n$", "") -- remove trailing whitespace
    return result
end

function getPythonPath()
    local p = queryTerminal('python -c "import sys; import os; print(os.path.dirname(sys.executable))"')
    
    -- sanitize path before returning it
    p = string.gsub(p, "\\\\", "\\") -- replace double backslash
    p = string.gsub(p, "\\", "/") -- flip slashes
    return p
end

function getPythonLib()
    return queryTerminal("python -c \"import sys; import os; import glob; path = os.path.dirname(sys.executable); libs = glob.glob(path + '/libs/python*'); print(os.path.splitext(os.path.basename(libs[-1]))[0]);\"")
end

pythonPath      = getPythonPath()
pythonIncludePath = pythonPath .. "/include/"
pythonLibPath     = pythonPath .. "/libs/"
pythonLib         = getPythonLib()

if pythonPath == "" or pythonLib == "" then
    error("Failed to find python path!")
else
    print("Python includes: " .. pythonIncludePath)
    print("Python libs: " .. pythonLibPath)
    print("lib: " .. pythonLib)
end

workspace "pybind11"
    location("temp/") -- temporary files (sln, proj, obj, pdb, ilk, etc)
    language "C++"
    architecture "x32"
    staticruntime "on"
    flags       { "MultiProcessorCompile" }

    debugdir("temp")
    includedirs { "include/", pythonIncludePath }

    configurations { "Release"}
        defines { "NDEBUG" }
        symbols "Off"        
        optimize "On"

    if os.host() == "windows" then
        cppdialect "C++17"
        systemversion("latest")
        system      "windows"
        platforms { "win32" }   

        symbolspath '$(TargetName).pdb'
        libdirs     { pythonLibPath }
        links { pythonLib }
        
    else -- MACOSX
        cppdialect "gnu++17"
        system      "macosx"
        platforms { "macosx32" }

        -- MacOS has not been tested! It is possible that the python variables won't work
        -- and one must instead retrieve the framework paths.

        -- /Library/Frameworks/Python.framework
        -- /System/Library/Frameworks/Python.framework

        libdirs { pythonLibPath }
        links { pythonLib }
        buildoptions { "-F /Library/Frameworks" }
        linkoptions  { "-F /Library/Frameworks" }
    end

    filter{}

project "pybind11 testing"
    kind "SharedLib"
    targetdir("temp/build")
    targetname("pybind_test") -- this name must match the module name in the macro PYBIND11_MODULE(group6_pybind_test, m)
    targetextension(".pyd")
    files ({"pybind_test.cpp"})
    postbuildcommands {
        "{COPY} %{cfg.targetdir}/pybind_test.pyd %{cfg.targetdir}/../../"
    }

