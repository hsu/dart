###############################################
# apps/cubes
project(cubes)
file(GLOB cubes_srcs "*.cpp")
file(GLOB cubes_hdrs "*.h")
add_executable(cubes ${cubes_srcs} ${cubes_hdrs})
target_link_libraries(cubes dart_constraint dart_collision dart_utils dart_simulation dart_yui dart_dynamics dart_math dart_common dart_lcpsolver ${DARTExt_LIBRARIES})
set_target_properties(cubes PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
