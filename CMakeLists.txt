cmake_minimum_required(VERSION 3.22)

project(USnake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(/usr/lib/cmake/Qt6LinguistTools/Qt6LinguistToolsMacros.cmake)

set(PROJECT_SOURCES
        mainwindow.ui

        src/main.cc
        src/mainwindow.cc
        src/gamecontroller.cc
        src/gamewidget.cc

        include/mainwindow.h
        include/gamecontroller.h
        include/gamewidget.h
)

include_directories(${PROJECT_SOURCE_DIR}/include)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(USnake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET USnake APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(USnake SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(USnake
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(USnake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.USnake)
endif()
set_target_properties(USnake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS USnake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(USnake)
endif()

set(TRANSLATION_FILES
        translations/USnake_en_US.ts
        translations/USnake_zh_CN.ts
        translations/USnake_zh_TW.ts
)

qt_add_translations(USnake
        TS_FILES ${TRANSLATION_FILES}
        QM_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/translations
)
