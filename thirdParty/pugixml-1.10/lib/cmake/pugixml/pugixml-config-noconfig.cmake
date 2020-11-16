#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pugixml-static" for configuration ""
set_property(TARGET pugixml-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(pugixml-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libpugixml-static.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS pugixml-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_pugixml-static "${_IMPORT_PREFIX}/lib/libpugixml-static.a" )

# Import target "pugixml-shared" for configuration ""
set_property(TARGET pugixml-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(pugixml-shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libpugixml-shared.so.1.10"
  IMPORTED_SONAME_NOCONFIG "libpugixml-shared.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS pugixml-shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_pugixml-shared "${_IMPORT_PREFIX}/lib/libpugixml-shared.so.1.10" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
