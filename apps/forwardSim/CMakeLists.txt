###############################################
# apps/forwardSim
project(forwardSim)
file(GLOB forwardSim_srcs "*.cpp")
file(GLOB forwardSim_hdrs "*.h")
add_executable(forwardSim ${forwardSim_srcs} ${forwardSim_hdrs})
target_link_libraries(forwardSim dart_dynamics dart_simulation dart_utils dart_yui dart_math dart_constraint dart_lcpsolver dart_common ${DARTExt_LIBRARIES})
set_target_properties(forwardSim PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
