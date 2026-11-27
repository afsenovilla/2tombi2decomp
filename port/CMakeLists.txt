# Native port of Tomba! 2 (stage 1, milestone P0).  Separate from the matching build: it reads src/ and the matching
# build's outputs (build/*.elf, asm/) and never writes them.  Adapted from Tombi-Decomp's port/ (MIT, same author).
# See docs/PORT.md.
#
#   python3 tools/build.py                    # once: the port takes retail addresses from build/main.elf, asm/main
#   cmake -S port -B build/port -G Ninja
#   cmake --build build/port
#   build/port/tomba2 --frames 600 --dump-frames build/port/frames     # from the repo root: game/usa/MAIN.EXE + files
cmake_minimum_required(VERSION 3.16)
project(tomba2_port C ASM)

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(GEN ${CMAKE_CURRENT_BINARY_DIR}/gen)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# 1. preprocess + split the game sources into ${GEN}/src (re-run on every configure)
set(PORT_PROGS main CACHE STRING "programs whose C is compiled into the port")
execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_t2.py sources ${GEN} ${PORT_PROGS}
                RESULT_VARIABLE gen_rc)
if(gen_rc)
  message(FATAL_ERROR "gen_t2.py sources failed")
endif()
include(${GEN}/sources.cmake)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
             ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_t2.py ${ROOT}/src/main/main.c ${ROOT}/build/main.elf)

# 2. target: i386, freestanding (the game's structures hold 32-bit pointers; the game's libc names must not meet a
#    host libc)
set(PORT_ARCH_FLAGS -m32 -march=i686 -fno-pic -fno-pie -fno-stack-protector -fcf-protection=none
    -fno-asynchronous-unwind-tables -ffreestanding -fno-builtin)
# semantics of the original compiler: unsigned char, wrapping signed arithmetic, no type-based alias analysis
set(PORT_GAME_FLAGS -O1 -w -std=gnu89 -funsigned-char -fwrapv -fno-strict-aliasing -fno-delete-null-pointer-checks
    -fno-omit-frame-pointer)

add_library(game OBJECT ${PORT_GAME_SOURCES})
target_include_directories(game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(game PRIVATE ${PORT_ARCH_FLAGS} ${PORT_GAME_FLAGS})

file(GLOB PORT_RUNTIME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/runtime/*.c ${CMAKE_CURRENT_SOURCE_DIR}/shims/*.c)
add_library(portrt OBJECT ${PORT_RUNTIME_SOURCES})
target_include_directories(portrt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(portrt PRIVATE ${PORT_ARCH_FLAGS} -O2 -Wall -Wno-unused-function -Wno-builtin-declaration-mismatch)

# 3. resolve symbols against the retail image: retail data addresses, call thunks, the address tables
file(GENERATE OUTPUT ${GEN}/objects.txt
     CONTENT "$<JOIN:$<TARGET_OBJECTS:game>,\n>\n$<JOIN:$<TARGET_OBJECTS:portrt>,\n>\n")
add_custom_command(OUTPUT ${GEN}/syms.ld ${GEN}/thunks.S ${GEN}/funcmap.c
                   COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_t2.py link ${GEN} ${CMAKE_NM} ${GEN}/objects.txt
                   DEPENDS game portrt $<TARGET_OBJECTS:game> $<TARGET_OBJECTS:portrt> ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_t2.py
                   COMMENT "Resolving game symbols against the matching build")
set_source_files_properties(${GEN}/thunks.S PROPERTIES GENERATED TRUE COMPILE_OPTIONS "-m32")
set_source_files_properties(${GEN}/funcmap.c PROPERTIES GENERATED TRUE)

add_executable(tomba2 ${GEN}/thunks.S ${GEN}/funcmap.c $<TARGET_OBJECTS:game> $<TARGET_OBJECTS:portrt>)
target_include_directories(tomba2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(tomba2 PRIVATE ${PORT_ARCH_FLAGS} -O1)
set_target_properties(tomba2 PROPERTIES LINKER_LANGUAGE C LINK_DEPENDS ${GEN}/syms.ld)
target_link_options(tomba2 PRIVATE -m32 -nostdlib -static -no-pie -Wl,--build-id=none -Wl,-z,noexecstack
                    -Wl,--allow-multiple-definition ${GEN}/syms.ld)

# 4. the window: a separate host-native SDL2 process (tomba2 --window forks it); the headless game needs no SDL.
#    From Tombi-Decomp's port/ (MIT, same author).  Windows: -DPORT_SDL2_MINGW=DIR names the i686-w64-mingw32 folder
#    of SDL2-devel-2.x-mingw.tar.gz; tomba2-view.exe needs its bin/SDL2.dll next to it.
if(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(PORT_SDL2_MINGW "" CACHE PATH "SDL2 mingw development folder (.../i686-w64-mingw32)")
  if(PORT_SDL2_MINGW AND EXISTS ${PORT_SDL2_MINGW}/include/SDL2/SDL.h)
    set(SDL2_FOUND 1)
    set(SDL2_INCLUDE_DIRS ${PORT_SDL2_MINGW}/include/SDL2)
    set(SDL2_LIBRARIES -L${PORT_SDL2_MINGW}/lib -lmingw32 -lSDL2main -lSDL2 -mwindows)
  endif()
else()
  find_package(SDL2 QUIET)
endif()
if(SDL2_FOUND)
  add_executable(tomba2-view tools/view/tomba2_view.c)
  target_include_directories(tomba2-view PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(tomba2-view PRIVATE ${SDL2_LIBRARIES})
  target_compile_options(tomba2-view PRIVATE -O2 -Wall)
  message(STATUS "SDL2 found: building tomba2-view (tomba2 --window)")
else()
  message(STATUS "SDL2 not found: no tomba2-view; the game still builds (headless)")
endif()
