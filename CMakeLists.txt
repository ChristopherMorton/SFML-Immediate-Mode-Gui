cmake_minimum_required(VERSION 2.6)

set(LIBRARY_NAME sfimgui)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

set (LIBRARY_FILES SFML_TextureManager.cpp SFML_WindowEventManager.cpp IMGuiManager.cpp IMCursorManager.cpp IMInstantButton.cpp IMButton.cpp IMImageButton.cpp IMTextButton.cpp IMEdgeButton.cpp IMEdgeTextButton.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)

if(SFML_FOUND)
   include_directories(${SFML_INCLUDE_DIR})

   set(CMAKE_CXX_FLAGS "-g -Wall")

   add_library(${LIBRARY_NAME} ${LIBRARY_FILES})

   add_executable(Test Test.cpp)
   target_link_libraries(Test ${LIBRARY_NAME} ${SFML_LIBRARIES})
endif()
