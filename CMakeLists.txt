cmake_minimum_required(VERSION 3.26)

# ---- Names (keep in sync with CI) ----
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME} LANGUAGES CXX C)

# ---- Standards ----
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Your helper modules ----
include(cmake/Options.cmake)        # defines DESTINATION_DIR, etc.
include(cmake/CompilerFlags.cmake)  # may define set_custom_stdlib_and_sanitizers/set_compiler_flags
include(cmake/CopyHelper.cmake)     # defines copy_files

# ---- SFML 3 (system first, then fallback) ----
set(_want_sfml_components Graphics Window System Audio)
find_package(SFML 3 QUIET COMPONENTS ${_want_sfml_components})
if(NOT SFML_FOUND)
  include(FetchContent)
  set(FETCHCONTENT_QUIET OFF)
  set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
  FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
    GIT_SHALLOW    1
  )
  FetchContent_MakeAvailable(sfml)
endif()

# ---- Sources ----
add_executable(${MAIN_EXECUTABLE_NAME}
  main.cpp
  header/Weapon.h
  header/Enemy.h
  header/Player.h
  header/Game.h
  source/Game.cpp
  source/Player.cpp
  source/Enemy.cpp
  header/Entity.h
  source/Entity.cpp
  header/MeleeWeapon.h
  header/RangedWeapon.h
  source/Weapon.cpp
  source/MeleeWeapon.cpp
  header/Level.h
  source/Level.cpp
  header/HUD.h
  source/HUD.cpp
  source/RangedWeapon.cpp
)

# ---- Default warnings (safe baseline) ----
if(MSVC)
  target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE /W4 /permissive- /utf-8)
else()
  target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Link SFML (imported targets) ----
target_link_libraries(${MAIN_EXECUTABLE_NAME}
  PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# ---- Toolchain / sanitizers helpers (guarded) ----
if(COMMAND set_custom_stdlib_and_sanitizers)
  set_custom_stdlib_and_sanitizers(${MAIN_EXECUTABLE_NAME} false)
else()
  message(STATUS "set_custom_stdlib_and_sanitizers() not found; skipping.")
endif()

if(COMMAND set_compiler_flags)
  set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
else()
  message(WARNING "set_compiler_flags() not found; applying default warnings only.")
  if(MSVC)
    target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE /W4 /permissive- /utf-8)
  else()
    target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endif()

# ---- Install / assets ----
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
  install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(DIRECTORY assets COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
