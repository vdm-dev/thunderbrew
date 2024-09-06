file(GLOB PRIVATE_SOURCES "*.cpp")

add_library(cursor STATIC
    ${PRIVATE_SOURCES}
)

target_include_directories(cursor
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(cursor
    PRIVATE
        storm
        gx
        ui
)
