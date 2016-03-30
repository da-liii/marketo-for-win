Install CMake 3.3
Install Visual Studio 2015 community
install Qt 5.6 (including QScript)
install jom http://wiki.qt.io/Jom
install Git (+patch + perl): http://git-scm.com/download/win
install python 3.x (https://www.python.org/downloads/) + add to path
install nsis: http://sourceforge.net/projects/nsis/files/latest/download?source=directory

Optionally install
An nsis editor to change the install script: http://hmne.sourceforge.net/



# visual studio envs
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"

# Qt
set PATH=%PATH%;C:\Qt\5.5\msvc2013\bin

# Git and patch.exe
set PATH=%PATH%;"C:\Program Files\Git\bin"

# patch.exe and perl.exe
set PATH=%PATH%;"C:\Program Files\Git\usr\bin"

# NSIS
set PATH=%PATH%;"C:\Program Files (x86)\NSIS"

# Run Cmake NOTE the -DPERL_EXECUTABLE=... at the end
# CMake does not seem to find perl from the Git binary directory without this help.
cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=..\install\kate ..\ -DPERL_EXECUTABLE="C:\Program Files\Git\usr\bin\perl.exe"

# build
cmake --build . --config Release


#Basically Copy Paste:
mkdir build
cd build
"C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat"
set PATH=%PATH%;C:\Qt\5.5\msvc2013\bin
set PATH=%PATH%;"C:\Program Files (x86)\Git\bin"
set PATH=%PATH%;"C:\Program Files (x86)\NSIS"

# Debug
cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=..\install ..\
cmake --build . --config Debug

# Release
cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=..\release ..\
cmake --build . --config Release


Qt 5.6 MSVC 2015:
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"
set PATH=%PATH%;C:\Qt\5.6\msvc2015\bin
set PATH=%PATH%;"C:\Program Files\Git\bin"
set PATH=%PATH%;"C:\Program Files\Git\usr\bin"
set PATH=%PATH%;"C:\Program Files (x86)\NSIS"
cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=..\release5.6 ..\ -DPERL_EXECUTABLE="C:\Program Files\Git\usr\bin\perl.exe"
cmake --build . --config Release

