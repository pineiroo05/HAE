#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Generic.Conversions" for configuration "Release"
set_property(TARGET Generic.Conversions APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Generic.Conversions PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "MikroC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/lib_platform.a"
  )

list(APPEND _cmake_import_check_targets Generic.Conversions )
list(APPEND _cmake_import_check_files_for_Generic.Conversions "${_IMPORT_PREFIX}/lib/lib_platform.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
