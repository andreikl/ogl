call "D:\Programs\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
call "C:\Program Files (x86)\VS Professional 2013\VC\vcvarsall.bat"
rem start cmake-gui.exe
cmake -G "Visual Studio 12 2013 Win64" %cd%/..
