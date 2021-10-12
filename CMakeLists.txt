SET(NAME "powerslave_ex")
cmake_minimum_required(VERSION 2.6)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)


SET(FFMPEG_VERSION "n2.7.2")



SET(GCC_COMPILE_LINK_FLAGS    "-static -lpng -logg -lvorbisfile -lopenal -lSDL2 -lz -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavutil -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavcodec -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavformat -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libswscale -Llib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libswresample -lavutil -lavcodec -lavformat -lswscale -lswresample -lstdc++ -lpthread -lm")


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


if(!VITA)
	SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
else()
	SET(CMAKE_CXX_COMPILER "/usr/local/vitasdk/bin/arm-vita-eabi-g++")
	add_compile_options( 
		-mtune=cortex-a9 
		-Wl,-q 
		-O2 
		-ftree-vectorize 
		-fomit-frame-pointer 
		-ffast-math 
		-fomit-frame-pointer 
		-mthumb 
		-Wall 
		-Wdisabled-optimization 
		-Wpointer-arith 
		-Wredundant-decls 
		-Wwrite-strings 
		-Wtype-limits 
		-Wundef 
		-Wempty-body 
		-Wno-parentheses 
		-Wno-switch 
		-Wno-format-zero-length 
		-Os 
		-fno-math-errno 
		-fno-signed-zeros 
		-fno-tree-vectorize 
		-Werror=format-security 
		-Werror=return-type 
		-Werror=vla 
		-Wformat 
		-fdiagnostics-color=auto 
		-Wno-maybe-uninitialized 
		-fno-rtti 
		#-fno-exceptions
		)
endif()
add_compile_options(
	-fno-strict-aliasing
	-fpermissive -w
)


include("CMakeFiles/angelscript.cmake")
include("CMakeFiles/powerslave.cmake")

execute_process (
    COMMAND bash -c "make/obj.sh"
    OUTPUT_VARIABLE OBJS
)




