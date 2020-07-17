IF(NOT CMAKE_ASM_COMPILER)
  FIND_PROGRAM(CMAKE_ASM_COMPILER NAMES yasm nasm)
ENDIF(NOT CMAKE_ASM_COMPILER)
MARK_AS_ADVANCED(CMAKE_ASM_COMPILER)


# configure variables set in this file for fast reload later on
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/admin/CMakeModules/CMakeASMCompiler.cmake.in 
               ${CMAKE_BINARY_DIR}/CMakeFiles/CMakeASMCompiler.cmake IMMEDIATE)

SET(CMAKE_ASM_COMPILER_ENV_VAR "ASM_COMPILER")
