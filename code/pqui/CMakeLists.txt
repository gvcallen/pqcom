cmake_minimum_required(VERSION 3.16)

project(pqui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets SerialPort)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

set(PROJECT_SOURCES
    src/main.cpp    
    src/MainWindow.cpp
    src/Serial.cpp
)

set(PROJECT_INCLUDE
    include/MainWindow.h
    include/Suncq.h
    include/Serial.h
)

set(PROJECT_UI
    ui/MainWindow.ui
)

qt_add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_INCLUDE}
    ${PROJECT_UI}
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE include
)

target_link_libraries(pqui PRIVATE Qt6::Widgets Qt6::SerialPort)

set_target_properties(pqui PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)