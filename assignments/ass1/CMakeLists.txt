project(ass1)

project_add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}-modules
    ${OpenCV_LIBS}
)

add_subdirectory(src)