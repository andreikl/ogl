call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat"
rem start cmake-gui.exe -G "Visual Studio 14 2015 Win64" %cd%/..
cmake -G "Visual Studio 14 2015 Win64" %cd%/..
