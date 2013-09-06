# Search all header and source files
file(GLOB_RECURSE dart_srcs *.cpp)
file(GLOB_RECURSE dart_hdrs *.h *.hpp)

# Library 
add_library(dart_planning ${dart_srcs} ${dart_hdrs})
target_link_libraries(dart_planning ${DARTExt_LIBRARIES})
set_target_properties(dart_planning PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
if(MSVC)
    set_target_properties(${target} PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE "/LTCG")
endif()

install(DIRECTORY ./ DESTINATION include/dart/planning 
        FILES_MATCHING PATTERN "*.h*" 
        PATTERN "*CMake*" EXCLUDE)
        
install(TARGETS dart_planning DESTINATION lib)
