cmake_minimum_required(VERSION 3.22)

project(USnake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

message(STATUS "Qt6_FOUND: ${Qt6_FOUND}")
message(STATUS "Qt6Core_FOUND: ${Qt6Core_FOUND}")
message(STATUS "Qt6Gui_FOUND: ${Qt6Gui_FOUND}")
message(STATUS "Qt6Widgets_FOUND: ${Qt6Widgets_FOUND}")
message(STATUS "Qt6LinguistTools_FOUND: ${Qt6LinguistTools_FOUND}")

message(STATUS "Qt6Core_DIR: ${Qt6Core_DIR}")
message(STATUS "Qt6Gui_DIR: ${Qt6Gui_DIR}")
message(STATUS "Qt6Widgets_DIR: ${Qt6Widgets_DIR}")
message(STATUS "Qt6LinguistTools_DIR: ${Qt6LinguistTools_DIR}")

include(${Qt6LinguistTools_DIR}/Qt6LinguistToolsMacros.cmake)

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



# 指定需要翻译的 .ts 文件
# 文件名通常遵循 "项目名_语言代码.ts" 的约定
set(TRANSLATION_FILES
        translations/USnake_en_US.ts
        translations/USnake_zh_CN.ts
        translations/USnake_zh_TW.ts
)

# 使用 qt_add_translations 命令生成 .qm 文件
# qt6_add_translations(TARGET USnake TS_FILES ${TRANSLATION_FILES})

# 将生成的 .qm 文件安装到应用程序的翻译目录下
install(FILES ${USnake_TRANSLATIONS}
        DESTINATION "${CMAKE_INSTALL_PREFIX}/translations"
)

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
