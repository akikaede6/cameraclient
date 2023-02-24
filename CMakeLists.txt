cmake_minimum_required(VERSION 3.5)

project(CameraClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Multimedia MultimediaWidgets)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)

set(PROJECT_SOURCES
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/camerademo.h
        ui/camerademo.cpp
        ui/mcudemo.h
        ui/mcudemo.cpp
        ui/videoplayer.h
        ui/videoplayer.cpp
        ui/ConfigClient.h
        ui/ConfigClient.cpp
        ipc/cameraSubscriberListener.h
        ipc/cameraSubscriberListener.cpp
        ipc/mcusubscriberlistener.h
        ipc/mcusubscriberlistener.cpp
        ipc/Data/CameraStream.idl
        ipc/Data/CameraStream.cxx
        ipc/Data/CameraStream.h
        ipc/Data/CameraStreamPubSubTypes.cxx
        ipc/Data/CameraStreamPubSubTypes.h
        ipc/Data/BstDemo397Tx.idl
        ipc/Data/BstDemo397Tx.cxx
        ipc/Data/BstDemo397Tx.h
        ipc/Data/BstDemo397TxPubSubTypes.cxx
        ipc/Data/BstDemo397TxPubSubTypes.h
        ipc/Data/BstDemo397Rx.idl
        ipc/Data/BstDemo397Rx.cxx
        ipc/Data/BstDemo397Rx.h
        ipc/Data/BstDemo397RxPubSubTypes.cxx
        ipc/Data/BstDemo397RxPubSubTypes.h
        model/cameramanager.cpp
        model/cameramanager.h
        model/cameramodel.cpp
        model/cameramodel.h
        decode/decode.h
        decode/decode.cpp
        widget/viewbutton.h
        widget/viewbutton.cpp
        widget/waitingspinnerwidget.cpp
        widget/waitingspinnerwidget.h
        FileManagement/FileManager.cpp
        FileManagement/FileManager.h
        FileManagement/FileWriter.cpp
        FileManagement/FileWriter.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CameraClient
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CameraClient APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CameraClient SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CameraClient
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CameraClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS} framework::dds PkgConfig::LIBAV Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)

set_target_properties(CameraClient PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CameraClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CameraClient)
endif()

add_subdirectory(ipc/DDS)
