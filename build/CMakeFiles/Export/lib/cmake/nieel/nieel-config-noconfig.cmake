#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "nieel::nieel" for configuration ""
set_property(TARGET nieel::nieel APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(nieel::nieel PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libnieel.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS nieel::nieel )
list(APPEND _IMPORT_CHECK_FILES_FOR_nieel::nieel "${_IMPORT_PREFIX}/lib/libnieel.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
