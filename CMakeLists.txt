SET(NAME "powerslave_ex")
cmake_minimum_required(VERSION 2.6)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)


SET(FFMPEG_VERSION "n2.7.2")

SET(GCC_VITA_COMPILE_FLAGS "-Wl,-q -O2 -ftree-vectorize -fomit-frame-pointer -ffast-math -mcpu=cortex-a9 -mthumb -fomit-frame-pointer -pthread -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wno-parentheses -Wno-switch -Wno-format-zero-length -Os -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=format-security -Werror=return-type -Werror=vla -Wformat -fdiagnostics-color=auto -Wno-maybe-uninitialized -Wempty-body -Wclass-memaccess -fno-rtti -fexceptions")


SET(GCC_COMPILE_LINK_FLAGS    "-lpng -logg -lvorbisfile -lopenal -lSDL2 -lz -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavutil -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavcodec -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavformat -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libswscale -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libswresample -lavutil -lavcodec -lavformat -lswscale -lswresample -lstdc++ -lpthread -lm")


macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)


set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

project(Powerslave)

use_cxx11()

set(POWERSLAVE_SOURCE
        source/framework/*.cpp
        source/game/*.cpp
	source/main.cpp
	source/math/*.cpp  
	source/movie/*.cpp
	source/opengl/*.cpp
	source/renderer/*.cpp
	source/script/*.cpp
	source/system/*.cpp
	source/tools/*.cpp
)

#set(POWERSLAVE_HEADERS
#        source/framework/*.h
#        source/game/*.h
#        source/*.h
#        source/math/*.h
#        source/movie/*.h
#        source/opengl/*.h
#        source/renderer/*.h
#        source/script/*.h
#        source/system/*.h
#        source/tools/*.h
#)




if(!VITA)
	SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
        SET(CMAKE_CXX_FLAGS "-fno-strict-aliasing")
else()
	SET(CMAKE_CXX_COMPILER "/usr/local/vitasdk/bin/arm-vita-eabi-g++")
	SET(CMAKE_CXX_FLAGS "${GCC_VITA_COMPILE_FLAGS} -fno-strict-aliasing")
endif()





include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/source
	${CMAKE_CURRENT_SOURCE_DIR}/source/game
	${CMAKE_CURRENT_SOURCE_DIR}/source/math
	${CMAKE_CURRENT_SOURCE_DIR}/source/movie
	${CMAKE_CURRENT_SOURCE_DIR}/source/opengl
	${CMAKE_CURRENT_SOURCE_DIR}/source/renderer
	${CMAKE_CURRENT_SOURCE_DIR}/source/script
	${CMAKE_CURRENT_SOURCE_DIR}/source/objects
        ${CMAKE_CURRENT_SOURCE_DIR}/source/al
        ${CMAKE_CURRENT_SOURCE_DIR}/source/system
        ${CMAKE_CURRENT_SOURCE_DIR}/source/sdl
        ${CMAKE_CURRENT_SOURCE_DIR}/source/tools
	${CMAKE_CURRENT_SOURCE_DIR}/source/tools/mapEditor
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/angelscript/sdk/angelscript/include
	${CMAKE_CURRENT_SOURCE_DIR}/source/lib/ffmpeg/FFmpeg-${FFMPEG_VERSION}
       )




execute_process (
    COMMAND bash -c "make/obj.sh"
    OUTPUT_VARIABLE OBJS
)

if(!VITA)
	file(WRITE "Compile" "cd lib/angelscript/sdk/angelscript/projects/gcc\n")
else()
        file(WRITE "Compile" "cd lib/angelscript/sdk/angelscript/projects/cmake/build_vita\n")
endif()



set(ANGELSCRIPT_SOURCE
        lib/angelscript/source/as_atomic.cpp
        lib/angelscript/source/as_builder.cpp
        lib/angelscript/source/as_bytecode.cpp
        lib/angelscript/source/as_callfunc.cpp
        lib/angelscript/source/as_callfunc_x86.cpp
        lib/angelscript/source/as_callfunc_x64_gcc.cpp
        lib/angelscript/source/as_callfunc_x64_msvc.cpp
        lib/angelscript/source/as_callfunc_x64_mingw.cpp
        lib/angelscript/source/as_compiler.cpp
        lib/angelscript/source/as_configgroup.cpp
        lib/angelscript/source/as_context.cpp
        lib/angelscript/source/as_datatype.cpp
        lib/angelscript/source/as_gc.cpp
        lib/angelscript/source/as_generic.cpp
        lib/angelscript/source/as_globalproperty.cpp
        lib/angelscript/source/as_memory.cpp
        lib/angelscript/source/as_module.cpp
        lib/angelscript/source/as_objecttype.cpp
        lib/angelscript/source/as_outputbuffer.cpp
        lib/angelscript/source/as_parser.cpp
        lib/angelscript/source/as_restore.cpp
        lib/angelscript/source/as_scriptcode.cpp
        lib/angelscript/source/as_scriptengine.cpp
        lib/angelscript/source/as_scriptfunction.cpp
        lib/angelscript/source/as_scriptnode.cpp
        lib/angelscript/source/as_scriptobject.cpp
        lib/angelscript/source/as_string.cpp
        lib/angelscript/source/as_string_util.cpp
        lib/angelscript/source/as_thread.cpp
        lib/angelscript/source/as_tokenizer.cpp
        lib/angelscript/source/as_typeinfo.cpp
        lib/angelscript/source/as_variablescope.cpp
)

if(MSVC AND CMAKE_CL_64)
            enable_language(ASM_MASM)
            if(CMAKE_ASM_MASM_COMPILER_WORKS)
                            set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} lib/angelscript/source/as_callfunc_x64_msvc_asm.asm)
            else()
                            message(FATAL ERROR "MSVC x86_64 target requires a working assembler")
            endif()
endif()

if(ANDROID)
        enable_language(ASM)
        if(CMAKE_ASM_COMPILER_WORKS)
                set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} lib/angelscript/source/as_callfunc_arm.cpp lib/angelscript/source/as_callfunc_arm_gcc.S)
        else()
                message(FATAL ERROR "Android target requires a working assembler")
        endif(CMAKE_ASM_COMPILER_WORKS)
endif()

set(ANGELSCRIPT_HEADERS
        lib/angelscript/include/angelscript.h
        lib/angelscript/source/as_array.h
        lib/angelscript/source/as_builder.h
        lib/angelscript/source/as_bytecode.h
        lib/angelscript/source/as_callfunc.h
        lib/angelscript/source/as_compiler.h
        lib/angelscript/source/as_config.h
        lib/angelscript/source/as_configgroup.h
        lib/angelscript/source/as_context.h
        lib/angelscript/source/as_criticalsection.h
        lib/angelscript/source/as_datatype.h
        lib/angelscript/source/as_debug.h
        lib/angelscript/source/as_generic.h
        lib/angelscript/source/as_map.h
        lib/angelscript/source/as_memory.h
        lib/angelscript/source/as_module.h
        lib/angelscript/source/as_objecttype.h
        lib/angelscript/source/as_outputbuffer.h
        lib/angelscript/source/as_parser.h
        lib/angelscript/source/as_property.h
        lib/angelscript/source/as_restore.h
        lib/angelscript/source/as_scriptcode.h
        lib/angelscript/source/as_scriptengine.h
        lib/angelscript/source/as_scriptfunction.h
        lib/angelscript/source/as_scriptnode.h
        lib/angelscript/source/as_scriptobject.h
        lib/angelscript/source/as_string.h
        lib/angelscript/source/as_string_util.h
        lib/angelscript/source/as_texts.h
        lib/angelscript/source/as_thread.h
        lib/angelscript/source/as_tokendef.h
        lib/angelscript/source/as_tokenizer.h
        lib/angelscript/source/as_typeinfo.h
        lib/angelscript/source/as_variablescope.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/angelscript/include)

add_definitions("-D_CRT_SECURE_NO_WARNINGS -DANGELSCRIPT_EXPORT -D_LIB")

# Fix x64 issues on Linux
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND NOT APPLE)
        add_definitions(-fPIC)
endif()

add_library(Angelscript STATIC ${ANGELSCRIPT_SOURCE} ${ANGELSCRIPT_HEADERS})
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/lib/angelscript/lib)

find_package(Threads)
target_link_libraries(Angelscript ${CMAKE_THREAD_LIBS_INIT})

if(MSVC)
        set_target_properties(Angelscript PROPERTIES COMPILE_FLAGS "/MP")
endif(MSVC)

set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/angelscript/bin)

#add_subdirectory(lib/angelscript/../samples/game/projects/cmake/ ./game)





