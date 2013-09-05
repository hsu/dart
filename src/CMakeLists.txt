project(dart)

# Enable multi-threaded compilation.
# We do this here and not in the root folder since the example apps
# do not have enough source files to benefit from this.
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

add_subdirectory(collision)
add_subdirectory(dynamics)
add_subdirectory(integration)
add_subdirectory(kinematics)
add_subdirectory(lcpsolver)
add_subdirectory(math)
# add_subdirectory(optimizer)
# add_subdirectory(planning)
add_subdirectory(renderer)
add_subdirectory(robotics)
add_subdirectory(simulation)
add_subdirectory(utils)
add_subdirectory(yui)

# Library 
add_library(dart SHARED collision dynamics integration kinematics lcpsolver math renderer robotics simulation utils yui)
set_target_properties(dart PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(dart dart_collision dart_dynamics dart_integration dart_kinematics dart_lcpsolver dart_math dart_renderer dart_robotics dart_simulation dart_utils dart_yui)
target_link_libraries(dart ${DARTExt_LIBRARIES})
set_target_properties(dart PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
if(MSVC)
    set_target_properties(${target} PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE "/LTCG")
endif()

install(DIRECTORY ./ DESTINATION include/dart
        FILES_MATCHING PATTERN "*.h*" 
        PATTERN "*CMake*" EXCLUDE)
        
install(TARGETS dart DESTINATION lib)
