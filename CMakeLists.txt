SET(NAME "powerslave_ex")
cmake_minimum_required(VERSION 2.6)
SET(FFMPEG_VERSION "n2.7.2")

SET(GCC_VITA_COMPILE_FLAGS "-Wl,-q -O2 -ftree-vectorize -fomit-frame-pointer -ffast-math -mcpu=cortex-a9 -fomit-frame-pointer -mthumb -pthread -Wdeclaration-after-statement -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -Wmissing-prototypes -Wno-pointer-to-int-cast -Wstrict-prototypes -Wempty-body -Wno-parentheses -Wno-switch -Wno-format-zero-length -Wno-pointer-sign -Os -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=format-security -Werror=implicit-function-declaration -Werror=missing-prototypes -Werror=return-type -Werror=vla -Wformat -fdiagnostics-color=auto -Wno-maybe-uninitialized fno-rtti -fno-exceptionsi")


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
        SET(CMAKE_CXX_FLAGS "-fno-strict-aliasing")
elseif()
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




#bin/${NAME}: $(OBJS) lib/angelscript/sdk/angelscript/lib/libangelscript.a
add_custom_command ( OUTPUT test COMMAND bash -c "${OBJS} lib/angelscript/sdk/angelscript/lib/libangelscript.a")


#removed $@ before .o ... adds adds all of a shell scripts cli
#removed $^
add_custom_command ( OUTPUT APPEND test COMMAND bash -c "${CXX} $^ -o ${OBJS} lib/angelscript/sdk/angelscript/lib/libangelscript.a $^ ${LINK}")

	#@echo "compiling executable $@"
	#@mkdir -p $(@D)/shared game_data
	#@$(CXX) -o $@ $^ $(LINK)







	#       @cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavutil/libavutil.so $(@D)/shared
	#	@cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavcodec/libavcodec.so $(@D)/shared
	#       @cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavformat/libavformat.so $(@D)/shared
       	#	@cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libswscale/libswscale.so $(@D)/shared
	#        @cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libswresample/libswresample.so $(@D)/shared
	#        @cp -R game_data/powerslave_ex/* bin/
	#        @cp make/run.sh $(@D)







	#add_subdirectory(../../../samples/game/projects/cmake/ ./game)
