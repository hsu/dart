###############################################
# apps/sensors
project(sensors)
file(GLOB sensors_srcs "*.cpp")
file(GLOB sensors_hdrs "*.h")
add_executable(sensors ${sensors_srcs} ${sensors_hdrs})
target_link_libraries(sensors dart ${DARTExt_LIBRARIES})
set_target_properties(sensors PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
