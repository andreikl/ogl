call "D:\Programs\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
rem start cmake-gui.exe
rem set CMAKE_SOURCE_DIR="%cd%"
rem set CMAKE_BINARY_DIR="%cd%/build"
cmake -G "Visual Studio 14 2015 Win64" %cd%/..