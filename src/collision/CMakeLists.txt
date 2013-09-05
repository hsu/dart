# Search all header and source files
file(GLOB_RECURSE dart_srcs *.cpp)
file(GLOB_RECURSE dart_hdrs *.h *.hpp)

# Library 
add_library(dart_collision ${dart_srcs} ${dart_hdrs})
target_link_libraries(dart_collision ${DARTExt_LIBRARIES})
set_target_properties(dart_collision PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
if(MSVC)
    set_target_properties(${target} PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE "/LTCG")
endif()

install(DIRECTORY ./ DESTINATION include/dart/collision
        FILES_MATCHING PATTERN "*.h*" 
        PATTERN "*CMake*" EXCLUDE)
        
install(TARGETS dart_collision DESTINATION lib)
