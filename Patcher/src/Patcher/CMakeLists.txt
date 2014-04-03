set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

configure_file(${INCROOT}/defines.hpp.in ${INCROOT}/defines.hpp @ONLY)
#ROOT files
set(ROOT_SRC
    ${SRCROOT}/Config.cpp
    ${SRCROOT}/MainWindow.cpp
    ${SRCROOT}/Maj.cpp
    ${SRCROOT}/WebConnection.cpp
)
set(ROOT_HEADER
    ${INCROOT}/Config.hpp
    ${INCROOT}/defines.hpp
    ${INCROOT}/MainWindow.hpp
    ${INCROOT}/Maj.hpp
    ${INCROOT}/WebConnection.hpp
)
set(ROOT_FILES
    ${ROOT_HEADER}
    ${ROOT_SRC}
)

#FILES
set(FILES_HEADER
    ${ROOT_HEADER}
)
set(FILES_SRC
    ${ROOT_SRC}
)

add_executable(${CMAKE_PROJECT_NAME} main.cpp ${FILES_HEADER} ${FILES_SRC})
QT5_USE_MODULES(${CMAKE_PROJECT_NAME} Widgets Network)
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})
# La fonction QT5_USE_MODULE encapsule toutes les routines nécessaires à l'utilisation 	d'un module
#QT5_USE_MODULES(${CMAKE_PROJECT_NAME} Widgets Declarative)

