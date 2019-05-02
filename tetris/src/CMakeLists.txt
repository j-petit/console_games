cmake_minimum_required(VERSION 2.8.9)

project(tetris)

file(GLOB project_sources "*.cpp")

set(sources ../include/game.h ${project_sources})

add_executable(tetris ${sources})
target_include_directories(tetris PRIVATE ../include)
target_link_libraries(tetris ncurses)
target_link_libraries(tetris pthread)

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

SET( CMAKE_BUILD_TYPE Debug)

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

