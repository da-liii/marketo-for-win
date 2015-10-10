Install CMake 3.3
Install Visual Studio 2013 community
install Qt 5.5 (including QScript)
install jom http://wiki.qt.io/Jom
install Git: http://git-scm.com/download/win
install python 3.x (https://www.python.org/downloads/) + add to path
install perl: http://strawberryperl.com/
      1) disable "patch.exe" from Strawberry perl (C:\Strawberry\c\bin\patch.exe)
      2) rename Staberry\c\include (wrong libxml version)

# visual studio envs
"C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat"

# Qt
set PATH=%PATH%;C:\Qt\Qt5.5.0\5.5\msvc2013\bin

# Git and patch.exe
set PATH=%PATH%;"C:\Program Files (x86)\Git\bin"

cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=..\install\kate ..\

cmake --build . --config Release



c:\Qt\Qt5.5.0\5.5\msvc2013\bin\windeployqt.exe e:\devel\kate\windows\install\kate\bin\kate.exe
c:\Qt\Qt5.5.0\5.5\msvc2013\bin\windeployqt.exe e:\devel\kate\windows\install\kate\bin\kio_http_cache_cleaner.exe  # Qt5Network
Qt5Scriptd.dll
Qt5PrintSupportd.dll





"C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat"
set PATH=%PATH%;C:\Qt\5.5\msvc2013\bin
set PATH=%PATH%;"C:\Program Files (x86)\Git\bin"
cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=..\install ..\
cmake --build . --config Debug

