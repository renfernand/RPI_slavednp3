#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "opendnp3::opendnp3" for configuration "Release"
set_property(TARGET opendnp3::opendnp3 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(opendnp3::opendnp3 PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libopendnp3.so"
  IMPORTED_SONAME_RELEASE "libopendnp3.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS opendnp3::opendnp3 )
list(APPEND _IMPORT_CHECK_FILES_FOR_opendnp3::opendnp3 "${_IMPORT_PREFIX}/lib/libopendnp3.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
