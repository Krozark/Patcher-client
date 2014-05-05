cmake_minimum_required (VERSION 2.8.8)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# project name
project (Patcher)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)



# add an option for building the API documentation
set_option(BUILD_DOC TRUE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

# add an option for building the API documentation
set_option(BUILD_EXEMPLES TRUE BOOL "TRUE to generate the API exemples, FALSE to ignore it")

############ QT ####################
if(WIN32)
	set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.2.1/5.2.1/mingw48_32")
endif()
# Appeler automatique le moc quand nécessaire
SET(CMAKE_AUTOMOC ON)
# Les fichiers générés par le moc sont générés dans le dossier bin, dire à CMake de toujours 	
# inclure les entêtes de ce dossier
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# Le module QtWidgets trouve ses propres dépendances
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5Script REQUIRED)

######### END Qt ##########################

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)


find_library(MONITORING_LIB Monitoring)
set(LIBS ${MONITORING_LIB})

#set(includepath "-I${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DEFINES "")
set(WARNING "-Wall")
set(FLAGS "-o3 -std=c++0x")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/exemples )

# add the subdirectories
add_subdirectory(src/${CMAKE_PROJECT_NAME})
#build exemples
#build doc
if(BUILD_DOC)
    add_subdirectory(doc)
endif()

if(BUILD_EXEMPLES)
    add_subdirectory(exemples)
endif()
