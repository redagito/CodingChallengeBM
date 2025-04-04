FILE(GLOB_RECURSE LIB_SOURCE_FILES *.cpp)
FILE(GLOB_RECURSE LIB_HEADER_FILES *.h)

add_library(libEncodingSimulation STATIC ${LIB_SOURCE_FILES} ${LIB_HEADER_FILES})

target_include_directories(libEncodingSimulation PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(libEncodingSimulation ${CMAKE_DL_LIBS})

set_target_properties(libEncodingSimulation PROPERTIES OUTPUT_NAME libEncodingSimulation)
