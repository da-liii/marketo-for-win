cmake_minimum_required(VERSION 3.3)

project(KateOnWindows)

cmake_policy(SET CMP0054 NEW)

set(KF5Ver 5.15)

include(ExternalProject)


############# EXTERNAL LIBRARIES #################

ExternalProject_Add(ecm
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/extra-cmake-modules-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

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

ExternalProject_Add(LibXml2
    URL ftp://xmlsoft.org/libxml2/libxml2-2.8.0.tar.gz
    URL_MD5 c62106f02ee00b6437f0fb9d370c1093
    PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/libxml2-2.8.0-20110105.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    UPDATE_COMMAND ""
    ALWAYS 0
    DEPENDS iconv zlib
)

ExternalProject_Add(LibXslt
    URL ftp://xmlsoft.org/libxslt/libxslt-1.1.26.tar.gz
    #URL_MD5 9667bf6f9310b957254fdcf6596600b7
    # 4df177de629b2653db322bfb891afa3c0d1fa221
    #  9667bf6f9310b957254fdcf6596600b7
    PATCH_COMMAND patch -p1 -i ${CMAKE_CURRENT_SOURCE_DIR}/patches/libxslt-1.1.26-20101102.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    UPDATE_COMMAND ""
    ALWAYS 0
    DEPENDS LibXml2
)


ExternalProject_Add(SharedMimeInfo
    URL http://heap.kogmbh.net/downloads/k/shared-mime-info-1.0_WITH_glib-2.24.0.tar.bz2
    URL_MD5 bd59d96aecb11d673634f6832496ee50
    PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/shared-mime-info-1.0.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DGLIB_DIR=glib-2.24.0
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    UPDATE_COMMAND ""
    ALWAYS 0
    DEPENDS gettext LibXml2
    BUILD_IN_SOURCE 1
)



ExternalProject_Add(Phonon4Qt5
    URL http://download.kde.org/stable/phonon/4.7.2/phonon-4.7.2.tar.xz
    URL_MD5 a8b722a11a301fc2cda7ff8228209531
    # patch is applied upstream in for the next release from master as of (2015-10-10)
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/Phonon4Qt5_4.7.2_fix_win_build.diff
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DPHONON_BUILD_EXAMPLES=OFF
        -DPHONON_BUILD_TESTS=OFF
        -DPHONON_INSTALL_QT_EXTENSIONS_INTO_SYSTEM_QT=ON
        -DPHONON_BUILD_PHONON4QT5=ON
        -DPHONON_NO_DBUS=ON
    DEPENDS ecm
)


# ExternalProject_Add(DBus
#     URL http://dbus.freedesktop.org/releases/dbus/dbus-1.8.4.tar.gz
#     #PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/dbus-qt5.diff  ${CMAKE_SOURCE_DIR}/patches/dbus_dont_include_afxres.diff
#     CMAKE_ARGS
#         -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
#         -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#         -DPHONON_BUILD_EXAMPLES=OFF
#         -DPHONON_BUILD_TESTS=OFF
#         -DPHONON_INSTALL_QT_EXTENSIONS_INTO_SYSTEM_QT=ON
#         -DPHONON_BUILD_PHONON4QT5=ON
#         -DPHONON_NO_DBUS=ON
#     DEPENDS ecm
# )



############# KF5 LIBRARIES #################

ExternalProject_Add(Config
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kconfig-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(GuiAddons
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kguiaddons-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(I18n
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/ki18n-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
        -DBUILD_WITH_QTSCRIPT=0
    DEPENDS ecm gettext gettext-tools
)

ExternalProject_Add(ItemViews
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kitemviews-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)


ExternalProject_Add(Sonnet
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/sonnet-${KF5Ver}.0.zip
     CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
   DEPENDS ecm
)

ExternalProject_Add(WindowSystem
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kwindowsystem-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(WidgetsAddons
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kwidgetsaddons-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Completion
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kcompletion-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm WidgetsAddons
)

ExternalProject_Add(DBusAddons
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kdbusaddons-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)

ExternalProject_Add(Archive
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/karchive-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm libzip
)


ExternalProject_Add(CoreAddons
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kcoreaddons-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm SharedMimeInfo

    # FIXME create a patch to make SharedMimeInfo optional!!! suggested by David
    # just install the xml...
)


#  DISABLE fo now.....
# ExternalProject_Add(DocTools
#     URL http://download.kde.org/stable/frameworks/${KF5Ver}/kdoctools-${KF5Ver}.0.zip
#     CMAKE_ARGS
#         -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
#         -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
#         -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#         -Wno-dev
#     DEPENDS ecm Archive LibXslt LibXml2 DocBookXML4 DocBookXSL
# )
#
ExternalProject_Add(JobWidgets
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kjobwidgets-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons
)

ExternalProject_Add(Service
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kservice-${KF5Ver}.0.zip
    PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/kf5service-disable-dockbook-syscoca-crash.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Config DBusAddons I18n CoreAddons
    #Crash DocTools
)

ExternalProject_Add(Codecs
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kcodecs-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm
)


ExternalProject_Add(Crash
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kcrash-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons WindowSystem
)

ExternalProject_Add(ConfigWidgets
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kconfigwidgets-${KF5Ver}.0.zip
    PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/kf5configwidgets-disable-docktool-auth.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons Codecs Config GuiAddons I18n WidgetsAddons
    #Auth DocTools
)

ExternalProject_Add(IconThemes
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kiconthemes-${KF5Ver}.0.zip
    # this patch has been committed to master to be part of 5.16
    PATCH_COMMAND patch -p1 -t < ${CMAKE_SOURCE_DIR}/patches/kiconthemes_add_coreaddons_dep.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm I18n CoreAddons Config WidgetsAddons ConfigWidgets ItemViews
)


ExternalProject_Add(TextWidgets
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/ktextwidgets-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Completion Config ConfigWidgets I18n IconThemes Service WidgetsAddons WindowSystem Sonnet
)

ExternalProject_Add(Notifications
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/knotifications-${KF5Ver}.0.zip
     CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
   DEPENDS ecm WindowSystem Service Config IconThemes Codecs CoreAddons Phonon4Qt5
)

ExternalProject_Add(GlobalAccel
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kglobalaccel-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Config CoreAddons Crash DBusAddons WindowSystem
)

ExternalProject_Add(XmlGui
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kxmlgui-${KF5Ver}.0.zip
    # this patch has been committed to master to be part of 5.16
    PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/kf5xmlgui-5.12.0-fix-win-build.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm CoreAddons ItemViews Config GlobalAccel ConfigWidgets I18n IconThemes TextWidgets WidgetsAddons WindowSystem
)

ExternalProject_Add(Bookmarks
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kbookmarks-${KF5Ver}.0.zip
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Config CoreAddons Codecs ConfigWidgets IconThemes WidgetsAddons XmlGui
)

# ExternalProject_Add(Wallet DISABLE for now
#     URL http://download.kde.org/stable/frameworks/${KF5Ver}/kwallet-${KF5Ver}.0.zip
#     #PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/
#     CMAKE_ARGS
#         -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
#         -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
#         -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#         -Wno-dev
#     DEPENDS ecm
# )
#
ExternalProject_Add(KIO
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kio-${KF5Ver}.0.zip
    PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/kf5kio-disable-doctools-solid-trash-help.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Archive Config CoreAddons DBusAddons Service Bookmarks Completion ConfigWidgets IconThemes ItemViews JobWidgets WidgetsAddons WindowSystem
    #Wallet
)

ExternalProject_Add(Init
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kinit-${KF5Ver}.0.zip
    PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/kf5init-disable-docktools-fix-compilation.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    DEPENDS ecm Service KIO I18n WindowSystem Crash Config
)




ExternalProject_Add(Parts
    URL http://download.kde.org/stable/frameworks/${KF5Ver}/kparts-${KF5Ver}.0.zip
     CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
    #INSTALL_COMMAND jom install ALWAYS 0 -j4
   DEPENDS ecm Config CoreAddons I18n IconThemes KIO JobWidgets Notifications Service TextWidgets WidgetsAddons XmlGui
)



ExternalProject_Add(TextEditor
    GIT_REPOSITORY "git://anongit.kde.org/ktexteditor"
    #PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/kf5texteditor-disable-kencodingfiledialog.diff
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
    #PATCH_COMMAND patch -p1 -i ${CMAKE_SOURCE_DIR}/patches/kate_make_compile.diff
    CMAKE_ARGS
        -DECM_DIR:PATH=${CMAKE_INSTALL_PREFIX}/share/ECM/cmake
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Wno-dev
        INSTALL_COMMAND jom install ALWAYS 1 -j4
    DEPENDS ecm Config GuiAddons I18n JobWidgets KIO Parts TextEditor WindowSystem XmlGui IconThemes
    # DocTools Init Activities
)









