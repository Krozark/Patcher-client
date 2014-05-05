set(HEADERS
)

set(SRC
    main.cpp
)

set(FILES ${HEADERS} ${SRC})

add_executable(${CMAKE_PROJECT_NAME}-test ${FILES})
QT5_USE_MODULES(${CMAKE_PROJECT_NAME}-test Widgets Network Script)
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${LIBS} ${CMAKE_PROJECT_NAME})
