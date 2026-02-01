project(ass1-modules)

project_add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
        Image.ixx
)

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OpenCV_LIBS}
)