# Windows Build Scripts for Marketo
## Requirements
1. 64 bit Windows
2. Install CMake 3.3
3. Install Visual Studio 2015 community(**NOTE**: please install c++ support)
4. install Qt 5.6 (including QScript)
5. install jom http://wiki.qt.io/Jom
6. install Git (+patch + perl): http://git-scm.com/download/win
7. install python 3.x (https://www.python.org/downloads/) + add to path
8. install nsis: [http://sourceforge.net/projects/nsis/files/latest/download?source=directory](http://sourceforge.net/projects/nsis/files/latest/download?source=directory)
   and install the NSIS Inetc plugin (Ascii version dll)

Optionally install
An nsis editor to change the install script: http://hmne.sourceforge.net/

## Build
``` bash
git clone https://github.com/sadhen/marketo-for-win.git
git submodule init
git submodule update
mkdir build
cd build

"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
set PATH=%PATH%;"C:\Qt\Qt5.6.0\5.6\msvc2015_64\bin"
set PATH=%PATH%;"C:\Program Files\Git\bin"
set PATH=%PATH%;"C:\Program Files\Git\usr\bin"
set PATH=%PATH%;"C:\Program Files (x86)\NSIS"

# Run Cmake NOTE the -DPERL_EXECUTABLE=... at the end
# CMake does not seem to find perl from the Git binary directory without this help.
cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=..\install\kate ..\ -DPERL_EXECUTABLE="C:\Program Files\Git\usr\bin\perl.exe"

# build
cmake --build . --config Release
```

## TroubleShooting
1. Encoding Problem: [http://stackoverflow.com/questions/16746966/how-can-handle-foreign-words-in-c-code](http://stackoverflow.com/questions/16746966/how-can-handle-foreign-words-in-c-code)
