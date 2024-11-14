cmake_minimum_required(VERSION 3.16)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)


add_subdirectory(external/googletest)

include_directories(external/googletest/googletest/include)

set(PROJECT_RESOURCES
    resources.qrc
)

set(PROJECT_SOURCES
        src/main.cpp
        src/Car.cpp
        src/CarThread.cpp
        src/RaceTrack.cpp
        src/RacingGame.cpp
)

set(PROJECT_HEADERS
        include/Car.h
        include/CarThread.h
        include/RaceTrack.h
        include/RacingGame.h
)

set(PROJECT_UI
        ui/RacingGame.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RaceGame
        MANUAL_FINALIZATION
            ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_UI} ${PROJECT_RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RaceGame SHARED
            ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_UI} ${PROJECT_RESOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RaceGame
            ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_UI} ${PROJECT_RESOURCES}
        )
    endif()
endif()

target_link_libraries(RaceGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# --- Add Google Test for Unit Testing ---
# Create an executable for running the tests
add_executable(run_tests
        tests/logic/test_racingGame_class.cpp
        src/RacingGame.cpp
        src/Car.cpp
        src/CarThread.cpp
        src/RaceTrack.cpp
        include/Car.h
        include/CarThread.h
        include/RacingGame.h
        include/RaceTrack.h
)

# Link Google Test and Google Test main libraries to the test executable
target_link_libraries(run_tests gtest gtest_main Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)


# # --- Add QT Test for Unit Testing ---
# # Create an executable for running the tests
# add_executable(run_ui_tests
#         tests/ui/test_ui.cpp
#         src/mainwindow.cpp
#         include/mainwindow.hpp
#         src/Contact.cpp
#         include/Contact.hpp
#         src/ContactList.cpp
#         include/ContactList.hpp
# )

# target_link_libraries(run_ui_tests Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)

# Enable testing with CTest (optional)
enable_testing()

# Add the test to CTest
add_test(NAME run_tests COMMAND run_tests)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.untitled)
endif()
set_target_properties(RaceGame PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RaceGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RaceGame)
endif()
