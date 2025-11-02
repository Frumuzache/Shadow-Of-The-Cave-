include(${CMAKE_CURRENT_LIST_DIR}/DetectLibcpp.cmake)

function(set_custom_stdlib_and_sanitizers target add_apple_asan)
    # --- Hard guard: do nothing for imported/alias or missing targets ---
    if(NOT TARGET "${target}")
      return()
    endif()
    get_target_property(_is_imported "${target}" IMPORTED)
    if(_is_imported)
      # e.g. SFML::System, SFML::Graphics, etc. --> skip
      return()
    endif()
    get_target_property(_is_alias "${target}" ALIASED_TARGET)
    if(_is_alias)
      return()
    endif()

    # Generator expression you used; assume it's defined elsewhere.
    # If not, define a local default:
    if(NOT DEFINED debug_mode)
      set(debug_mode "<CONFIG:Debug>")
    endif()

    # -------------------- MSVC branch --------------------
    if(MSVC)
        # Workaround you already had for VS modules:
        set_target_properties(${target} PROPERTIES VS_USER_PROPS "${CMAKE_SOURCE_DIR}/disable_modules.props")
        target_compile_options(${target} PRIVATE /experimental:module-)

        # Use the DLL runtime (/MD, /MDd). This is REQUIRED for MSVC ASan.
        # Do it per-target so we don't affect third-party libs.
        set_property(TARGET ${target} PROPERTY
          MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

        if(USE_ASAN)
            # Compile + link flags for AddressSanitizer (MSVC)
            target_compile_options(${target} PRIVATE "$<${debug_mode}:/fsanitize=address>")
            target_link_options(${target}    PRIVATE "$<${debug_mode}:/fsanitize=address;/INCREMENTAL:NO>")

            # /RTC1 (Run-Time Checks) conflicts with ASan; strip it in Debug for this target.
            # Easiest per-target approach: explicitly disable RTC via compile options.
            # (There isn't a direct /RTC-; we ensure it's not added by setting options ourselves.)
            # If your toolchain injects /RTC1, also consider removing it globally or at parent scope.
            target_compile_options(${target} PRIVATE "$<${debug_mode}:/Zi>")
        endif()
        return()
    endif()

    # -------------------- Clang (non-Windows) stdlib choice --------------------
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND NOT WIN32)
        detect_libcpp()
        if(HAS_LIBCPP)
            target_compile_options(${target} PRIVATE -stdlib=libc++)
            target_link_options(${target}    PRIVATE -stdlib=libc++)
        else()
            target_compile_options(${target} PRIVATE -stdlib=libstdc++)
            target_link_options(${target}    PRIVATE -stdlib=libstdc++)
        endif()
    endif()

    # -------------------- Apple / Unix sanitizers --------------------
    if(APPLE)
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND add_apple_asan MATCHES true)
            if(USE_ASAN)
                target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
                target_link_options(${target}    PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            endif()
        endif()
    elseif(UNIX)
        if(USE_ASAN)
            target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            target_link_options(${target}    PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
        elseif(USE_MSAN)
            target_compile_options(${target} PRIVATE
              "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins>")
            target_link_options(${target} PRIVATE
              "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins;-Wl,-rpath,tools/llvm-project/build/lib>")
        endif()
    endif()
endfunction()
