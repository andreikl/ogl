call "D:\Programs\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
call "C:\Program Files (x86)\VS Professional 2013\VC\vcvarsall.bat"
rem start cmake-gui.exe -G "Visual Studio 14 2015 Win64" %cd%/..
cmake -G "Visual Studio 14 2015 Win64" %cd%/..
