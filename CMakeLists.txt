# Thanks to KDE on Windows for the emerge scripts that showed the tips and tricks
# how to compile frameworks on windows.
#
# The patches to the KF5 dependencies are copied from emerge:
# git://anongit.kde.org/emerge.git
#

cmake_minimum_required(VERSION 3.3)

project(KateOnWindows)

cmake_policy(SET CMP0054 NEW)

set(KF5Ver 5.15)

include(ExternalProject)


############# EXTERNAL LIBRARIES #################

ExternalProject_Add(zlib
    URL http://downloads.sourceforge.net/sourceforge/libpng/zlib-1.2.8.tar.gz
    URL_HASH SHA256=36658cb768a54c1d4dec43c3116c27ed893e88b02ecfcb44f2166f9c0b7f2a0d
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/zlib-1.2.8-20130901.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

ExternalProject_Add(libmdcpp
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/libmdcpp
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBOOST_ROOT=C:/local/boost_1_60_0
        -DBOOST_LIBRARYDIR=C:/local/boost_1_60_0/lib64-msvc-14.0
)

ExternalProject_Add(libzip
    URL http://www.nih.at/libzip/libzip-0.11.1.tar.xz
    URL_HASH SHA256=65338688f157784c80824d222f779505416d066c701409f6aef6b886bcd856a4
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/libzip-0.11.1-20130907.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    DEPENDS zlib
)

ExternalProject_Add(gettext-tools
    URL http://downloads.sourceforge.net/sourceforge/kde-windows/gettext-tools-0.18.1.1_1-bin.tar.bz2
    URL_HASH SHA256=844f3da9dac4a28dde290896fb552917947606c508e3b1f4fc0a479de90167b5
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/gettext-tools-prefix/src/gettext-tools/bin ${CMAKE_INSTALL_PREFIX}/bin
)

ExternalProject_Add(libintl-lite
    GIT_REPOSITORY "https://github.com/j-jorge/libintl-lite.git"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)


ExternalProject_Add(png2ico
    URL http://www.winterdrache.de/freeware/png2ico/data/png2ico-win-2002-12-08.zip
    URL_HASH SHA256=09cafe3f62a7827634ab4fcba630774ab0984bbffaab1489bd6fbb21c30818cb
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/png2ico-prefix/src/png2ico/png2ico.exe ${CMAKE_INSTALL_PREFIX}/bin/
)

ExternalProject_Add(hunspell
    URL https://github.com/hunspell/hunspell/archive/v1.3.4.zip
    URL_HASH SHA256=32b4100b9906153e77b735df2a4195725f8c3bf0a61d3925961c537240a5e41a
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/hunspell_add_cmakelists.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS
)

############# KF5 LIBRARIES #################

ExternalProject_Add(ecm
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/ecm
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    DEPENDS hunspell png2ico libintl-lite gettext-tools libzip zlib # force building of deps fist
)

ExternalProject_Add(Config
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kconfig
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(GuiAddons
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kguiaddons
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(I18n
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/ki18n
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
        -DBUILD_WITH_QTSCRIPT=0
    DEPENDS ecm libintl-lite gettext-tools
)

ExternalProject_Add(ItemViews
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kitemviews
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Sonnet
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/sonnet
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm hunspell
)

ExternalProject_Add(WindowSystem
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kwindowsystem
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(WidgetsAddons
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kwidgetsaddons
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Completion
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kcompletion
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm WidgetsAddons
)

ExternalProject_Add(DBusAddons
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kdbusaddons
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Archive
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/karchive
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm libzip I18n # I18n to force building first
)


ExternalProject_Add(CoreAddons
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kcoreaddons
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)


ExternalProject_Add(JobWidgets
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kjobwidgets
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons
)

ExternalProject_Add(Crash
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kcrash
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons WindowSystem
)

ExternalProject_Add(Service
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kservice
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_TESTING=0
        -Wno-dev
    DEPENDS ecm Config DBusAddons I18n CoreAddons Crash
)

ExternalProject_Add(Codecs
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kcodecs
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)


ExternalProject_Add(Auth
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kauth
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons
)

ExternalProject_Add(ConfigWidgets
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kconfigwidgets
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons Codecs Config GuiAddons I18n WidgetsAddons Auth
)

ExternalProject_Add(IconThemes
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kiconthemes
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm I18n CoreAddons Config WidgetsAddons ConfigWidgets ItemViews
)


ExternalProject_Add(TextWidgets
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/ktextwidgets
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Completion Config ConfigWidgets I18n IconThemes Service WidgetsAddons WindowSystem Sonnet
)

ExternalProject_Add(XmlGui
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kxmlgui
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
        -DFORCE_DISABLE_KGLOBALACCEL=1
    DEPENDS ecm CoreAddons ItemViews Config ConfigWidgets I18n IconThemes TextWidgets WidgetsAddons WindowSystem
)

ExternalProject_Add(Bookmarks
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kbookmarks
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Config CoreAddons Codecs ConfigWidgets IconThemes WidgetsAddons XmlGui
)

ExternalProject_Add(Attica
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/attica
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Solid
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/solid
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(KIO
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kio
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/001-kio-workaround-leading-slash-on-toDisplayString.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Archive Config CoreAddons DBusAddons Service Bookmarks Completion ConfigWidgets IconThemes ItemViews JobWidgets WidgetsAddons WindowSystem Solid
    #Wallet
)


ExternalProject_Add(Parts
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kparts
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    #INSTALL_COMMAND jom install ALWAYS 0 -j4
   DEPENDS ecm Config CoreAddons I18n IconThemes KIO JobWidgets Service TextWidgets WidgetsAddons XmlGui
)



ExternalProject_Add(TextEditor
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/ktexteditor
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DPERL_EXECUTABLE=${PERL_EXECUTABLE}
        -Wno-dev
    #INSTALL_COMMAND jom install ALWAYS 0 -j4
    DEPENDS ecm Archive Config GuiAddons I18n KIO Parts Sonnet IconThemes
)

ExternalProject_Add(BreezeIcons
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/breeze-icons
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    #INSTALL_COMMAND jom install ALWAYS 0 -j4
    DEPENDS ecm
)


ExternalProject_Add(marketo
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/marketo
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
        #INSTALL_COMMAND jom install ALWAYS 1 -j4
    #DEPENDS libmdcpp ecm CoreAddons I18n TextEditor XmlGui
)

ExternalProject_Add(IconRcc
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/icon-rcc
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -Wno-dev
    DEPENDS marketo
)

ExternalProject_Add(Deploy
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/deploy
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -Wno-dev
    DEPENDS IconRcc
)


ExternalProject_Add(Installer
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/installer
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    INSTALL_COMMAND echo done
    DEPENDS Deploy
)