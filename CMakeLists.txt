cmake_minimum_required(VERSION 3.3)

project(KateOnWindows)

cmake_policy(SET CMP0054 NEW)

set(KF5Ver 5.15)

include(ExternalProject)


############# EXTERNAL LIBRARIES #################

ExternalProject_Add(zlib
    URL http://downloads.sourceforge.net/sourceforge/libpng/zlib-1.2.8.tar.gz
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/zlib-1.2.8-20130901.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

ExternalProject_Add(libzip
    URL http://www.nih.at/libzip/libzip-0.11.1.tar.xz
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/libzip-0.11.1-20130907.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    DEPENDS zlib
)

ExternalProject_Add(iconv
    URL https://github.com/win-iconv/win-iconv/archive/0.0.6.tar.gz
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

ExternalProject_Add(gettext
    URL http://ftp.gnu.org/pub/gnu/gettext/gettext-0.18.tar.gz
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/gettext-0.18-20150423.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    DEPENDS iconv
)

ExternalProject_Add(gettext-tools
    URL http://downloads.sourceforge.net/sourceforge/kde-windows/gettext-tools-0.18.1.1_1-bin.tar.bz2
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/gettext-tools-prefix/src/gettext-tools/bin ${CMAKE_INSTALL_PREFIX}/bin
)


############# KF5 LIBRARIES #################

ExternalProject_Add(ecm
    GIT_REPOSITORY "git://anongit.kde.org/extra-cmake-modules"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

ExternalProject_Add(Config
    GIT_REPOSITORY "git://anongit.kde.org/kconfig"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(GuiAddons
    GIT_REPOSITORY "git://anongit.kde.org/kguiaddons"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(I18n
    GIT_REPOSITORY "git://anongit.kde.org/ki18n"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
        -DBUILD_WITH_QTSCRIPT=0
    DEPENDS ecm gettext gettext-tools
)

ExternalProject_Add(ItemViews
    GIT_REPOSITORY "git://anongit.kde.org/kitemviews"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)


ExternalProject_Add(Sonnet
    GIT_REPOSITORY "git://anongit.kde.org/sonnet"
     CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
   DEPENDS ecm
)

ExternalProject_Add(WindowSystem
    GIT_REPOSITORY "git://anongit.kde.org/kwindowsystem"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(WidgetsAddons
    GIT_REPOSITORY "git://anongit.kde.org/kwidgetsaddons"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Completion
    GIT_REPOSITORY "git://anongit.kde.org/kcompletion"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm WidgetsAddons
)

ExternalProject_Add(DBusAddons
    GIT_REPOSITORY "git://anongit.kde.org/kdbusaddons"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Archive
    GIT_REPOSITORY "git://anongit.kde.org/karchive"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm libzip
)


ExternalProject_Add(CoreAddons
    GIT_REPOSITORY "git://anongit.kde.org/kcoreaddons"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)


ExternalProject_Add(JobWidgets
    GIT_REPOSITORY "git://anongit.kde.org/kjobwidgets"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons
)

ExternalProject_Add(Service
    GIT_REPOSITORY "git://anongit.kde.org/kservice"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Config DBusAddons I18n CoreAddons
    #Crash DocTools
)

ExternalProject_Add(Codecs
    GIT_REPOSITORY "git://anongit.kde.org/kcodecs"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)


ExternalProject_Add(Crash
    GIT_REPOSITORY "git://anongit.kde.org/kcrash"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons WindowSystem
)

ExternalProject_Add(Auth
    GIT_REPOSITORY "git://anongit.kde.org/kauth"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons
)

ExternalProject_Add(ConfigWidgets
    GIT_REPOSITORY "git://anongit.kde.org/kconfigwidgets"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons Codecs Config GuiAddons I18n WidgetsAddons Auth
)

ExternalProject_Add(IconThemes
    GIT_REPOSITORY "git://anongit.kde.org/kiconthemes"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm I18n CoreAddons Config WidgetsAddons ConfigWidgets ItemViews
)


ExternalProject_Add(TextWidgets
    GIT_REPOSITORY "git://anongit.kde.org/ktextwidgets"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Completion Config ConfigWidgets I18n IconThemes Service WidgetsAddons WindowSystem Sonnet
)

ExternalProject_Add(GlobalAccel
    GIT_REPOSITORY "git://anongit.kde.org/kglobalaccel"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Config CoreAddons Crash DBusAddons WindowSystem
)

ExternalProject_Add(XmlGui
    GIT_REPOSITORY "git://anongit.kde.org/kxmlgui"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons ItemViews Config GlobalAccel ConfigWidgets I18n IconThemes TextWidgets WidgetsAddons WindowSystem
)

ExternalProject_Add(Bookmarks
    GIT_REPOSITORY "git://anongit.kde.org/kbookmarks"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Config CoreAddons Codecs ConfigWidgets IconThemes WidgetsAddons XmlGui
)

ExternalProject_Add(ThreadWeaver
    GIT_REPOSITORY "git://anongit.kde.org/threadweaver"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(ItemModels
    GIT_REPOSITORY "git://anongit.kde.org/kitemmodels"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Attica
    GIT_REPOSITORY "git://anongit.kde.org/attica"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)
ExternalProject_Add(Solid
    GIT_REPOSITORY "git://anongit.kde.org/solid"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)
ExternalProject_Add(KIO
    GIT_REPOSITORY "git://anongit.kde.org/kio"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Archive Config CoreAddons DBusAddons Service Bookmarks Completion ConfigWidgets IconThemes ItemViews JobWidgets WidgetsAddons WindowSystem Solid
    #Wallet
)

ExternalProject_Add(NewStuff
    GIT_REPOSITORY "git://anongit.kde.org/knewstuff"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Attica Archive Completion Config CoreAddons I18n IconThemes KIO ItemViews Service TextWidgets WidgetsAddons XmlGui
)


ExternalProject_Add(Parts
    GIT_REPOSITORY "git://anongit.kde.org/kparts"
     CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    #INSTALL_COMMAND jom install ALWAYS 0 -j4
   DEPENDS ecm Config CoreAddons I18n IconThemes KIO JobWidgets Service TextWidgets WidgetsAddons XmlGui
)



ExternalProject_Add(TextEditor
    GIT_REPOSITORY "git://anongit.kde.org/ktexteditor"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    #INSTALL_COMMAND jom install ALWAYS 0 -j4
    DEPENDS ecm Archive Config GuiAddons I18n KIO Parts Sonnet IconThemes

    )


ExternalProject_Add(Kate
    GIT_REPOSITORY "git://anongit.kde.org/kate"
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
        #INSTALL_COMMAND jom install ALWAYS 1 -j4
    DEPENDS ecm Config GuiAddons I18n JobWidgets KIO Parts TextEditor WindowSystem XmlGui IconThemes ItemViews ItemModels NewStuff
)









