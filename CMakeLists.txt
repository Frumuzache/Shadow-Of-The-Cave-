cmake_minimum_required(VERSION 3.26)

# ---- Names (keep in sync with CI if you change them) ----
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME} LANGUAGES CXX C)

# ---- Languages / standards ----
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Helper modules (your own) ----
include(cmake/Options.cmake)        # defines DESTINATION_DIR etc.
include(cmake/CompilerFlags.cmake)  # defines set_custom_stdlib_and_sanitizers / set_compiler_flags
include(cmake/CopyHelper.cmake)     # defines copy_files

# ---- SFML 3 (system first, then fallback) ----
# Prefer a system-installed SFML 3; otherwise fetch it.
set(_want_sfml_components Graphics Window System Audio)

find_package(SFML 3 QUIET COMPONENTS ${_want_sfml_components})
if(NOT SFML_FOUND)
  include(FetchContent)
  # Avoid noisy re-configures
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

# ---- Compile options / warnings (portable defaults) ----
if(MSVC)
  target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE /W4 /permissive- /utf-8)
else()
  target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Link SFML (use modern imported targets) ----
target_link_libraries(${MAIN_EXECUTABLE_NAME}
  PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# ---- Your sanitizer / toolchain helpers (apply AFTER target exists) ----
# The second argument 'false' matches your previous usage.
set_custom_stdlib_and_sanitizers(${MAIN_EXECUTABLE_NAME} false)

# Apply your compiler flags; RUN_SANITIZERS defaults to true, but we set it explicitly
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

# ---- Install / runtime assets ----
# Binaries to "bin" (DESTINATION_DIR is defined in cmake/Options.cmake)
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
  install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# Copy runtime files alongside the built executable into ${DESTINATION_DIR}
copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(DIRECTORY assets COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

# If you later need Threads, keep this as an example:
# find_package(Threads REQUIRED)
# target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE Threads::Threads)
