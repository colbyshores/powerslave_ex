set(POWERSLAVE_SOURCE
	#source/framework
	${PROJECT_SOURCE_DIR}/source/framework/actions.cpp
	${PROJECT_SOURCE_DIR}/source/framework/binFile.cpp
	${PROJECT_SOURCE_DIR}/source/framework/cmd.cpp
	${PROJECT_SOURCE_DIR}/source/framework/console.cpp
	${PROJECT_SOURCE_DIR}/source/framework/cvar.cpp
	${PROJECT_SOURCE_DIR}/source/framework/defs.cpp
	${PROJECT_SOURCE_DIR}/source/framework/dict.cpp
	${PROJECT_SOURCE_DIR}/source/framework/kpf.cpp
	${PROJECT_SOURCE_DIR}/source/framework/kstring.cpp
	${PROJECT_SOURCE_DIR}/source/framework/memHeap.cpp
	${PROJECT_SOURCE_DIR}/source/framework/object.cpp
	${PROJECT_SOURCE_DIR}/source/framework/parser.cpp
	${PROJECT_SOURCE_DIR}/source/framework/session.cpp
	${PROJECT_SOURCE_DIR}/source/framework/unzip.cpp

	#source/game
	${PROJECT_SOURCE_DIR}/source/game/actionDef.cpp
	${PROJECT_SOURCE_DIR}/source/game/actor.cpp
	${PROJECT_SOURCE_DIR}/source/game/actorFactory.cpp
	${PROJECT_SOURCE_DIR}/source/game/ai.cpp
	${PROJECT_SOURCE_DIR}/source/game/cmodel.cpp
	${PROJECT_SOURCE_DIR}/source/game/dlightObj.cpp
	${PROJECT_SOURCE_DIR}/source/game/game.cpp
	${PROJECT_SOURCE_DIR}/source/game/gameObject.cpp
	${PROJECT_SOURCE_DIR}/source/game/hud.cpp
	${PROJECT_SOURCE_DIR}/source/game/inventoryMenu.cpp
	${PROJECT_SOURCE_DIR}/source/game/localization.cpp
	${PROJECT_SOURCE_DIR}/source/game/menu.cpp
	${PROJECT_SOURCE_DIR}/source/game/menuPanel.cpp
	${PROJECT_SOURCE_DIR}/source/game/mover.cpp
	${PROJECT_SOURCE_DIR}/source/game/overWorld.cpp
	${PROJECT_SOURCE_DIR}/source/game/pickup.cpp
	${PROJECT_SOURCE_DIR}/source/game/playerCmd.cpp
	${PROJECT_SOURCE_DIR}/source/game/player.cpp
	${PROJECT_SOURCE_DIR}/source/game/playLoop.cpp
	${PROJECT_SOURCE_DIR}/source/game/projectile.cpp
	${PROJECT_SOURCE_DIR}/source/game/pWeapon.cpp
	${PROJECT_SOURCE_DIR}/source/game/spring.cpp
	${PROJECT_SOURCE_DIR}/source/game/spriteAnim.cpp
	${PROJECT_SOURCE_DIR}/source/game/sprite.cpp
	${PROJECT_SOURCE_DIR}/source/game/titlescreen.cpp
	${PROJECT_SOURCE_DIR}/source/game/travelObject.cpp
	${PROJECT_SOURCE_DIR}/source/game/world.cpp

	#source/
	${PROJECT_SOURCE_DIR}/source/main.cpp

	#source/math
	${PROJECT_SOURCE_DIR}/source/math/angle.cpp
	${PROJECT_SOURCE_DIR}/source/math/bounds.cpp
	${PROJECT_SOURCE_DIR}/source/math/mathlib.cpp
	${PROJECT_SOURCE_DIR}/source/math/matrix.cpp
	${PROJECT_SOURCE_DIR}/source/math/plane.cpp
	${PROJECT_SOURCE_DIR}/source/math/pluecker.cpp
	${PROJECT_SOURCE_DIR}/source/math/quaternion.cpp
	${PROJECT_SOURCE_DIR}/source/math/random.cpp
	${PROJECT_SOURCE_DIR}/source/math/vector.cpp

	#source/movie
	${PROJECT_SOURCE_DIR}/source/movie/movie.cpp

	#source/opengl
	${PROJECT_SOURCE_DIR}/source/opengl/glcontext.cpp


	#source/renderer
	${PROJECT_SOURCE_DIR}/source/renderer/cpuVertexList.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/fbo.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/image.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderBackend.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderDynLight.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderFont.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderPortal.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderPostProcess.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderScene.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderScreen.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderUtils.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/renderView.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/shaderProg.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/textureManager.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/textureObject.cpp
	${PROJECT_SOURCE_DIR}/source/renderer/vertexBuffer.cpp

	#source/script
	${PROJECT_SOURCE_DIR}/source/script/scriptSystem.cpp

	#source/tools
	${PROJECT_SOURCE_DIR}/source/tools/dataConvert.cpp
	${PROJECT_SOURCE_DIR}/source/tools/spriteMake.cpp
)

set(POWERSLAVE_HEADERS
	#source/framework
	${PROJECT_SOURCE_DIR}/source/framework/actions.h
	${PROJECT_SOURCE_DIR}/source/framework/array.h
	${PROJECT_SOURCE_DIR}/source/framework/binFile.h
	${PROJECT_SOURCE_DIR}/source/framework/cmd.h
	${PROJECT_SOURCE_DIR}/source/framework/console.h
	${PROJECT_SOURCE_DIR}/source/framework/cvar.h
	${PROJECT_SOURCE_DIR}/source/framework/defs.h
	${PROJECT_SOURCE_DIR}/source/framework/dict.h
	${PROJECT_SOURCE_DIR}/source/framework/hashlist.h
	${PROJECT_SOURCE_DIR}/source/framework/kpf.h
	${PROJECT_SOURCE_DIR}/source/framework/kstring.h
	${PROJECT_SOURCE_DIR}/source/framework/linkedlist.h
	${PROJECT_SOURCE_DIR}/source/framework/memHeap.h
	${PROJECT_SOURCE_DIR}/source/framework/msort.h
	${PROJECT_SOURCE_DIR}/source/framework/object.h
	${PROJECT_SOURCE_DIR}/source/framework/parser.h
	${PROJECT_SOURCE_DIR}/source/framework/queue.h
	${PROJECT_SOURCE_DIR}/source/framework/sdNodes.h
	${PROJECT_SOURCE_DIR}/source/framework/session.h
	${PROJECT_SOURCE_DIR}/source/framework/stack.h
	${PROJECT_SOURCE_DIR}/source/framework/unzip.h

	#source/game
	${PROJECT_SOURCE_DIR}/source/game/actionDef.h
	${PROJECT_SOURCE_DIR}/source/game/actorFactory.h
	${PROJECT_SOURCE_DIR}/source/game/actor.h
	${PROJECT_SOURCE_DIR}/source/game/ai.h
	${PROJECT_SOURCE_DIR}/source/game/cmodel.h
	${PROJECT_SOURCE_DIR}/source/game/dlightObj.h
	${PROJECT_SOURCE_DIR}/source/game/game.h
	${PROJECT_SOURCE_DIR}/source/game/gameObject.h
	${PROJECT_SOURCE_DIR}/source/game/hud.h
	${PROJECT_SOURCE_DIR}/source/game/inventoryMenu.h
	${PROJECT_SOURCE_DIR}/source/game/localization.h
	${PROJECT_SOURCE_DIR}/source/game/menu.h
	${PROJECT_SOURCE_DIR}/source/game/menuPanel.h
	${PROJECT_SOURCE_DIR}/source/game/mover.h
	${PROJECT_SOURCE_DIR}/source/game/overWorld.h
	${PROJECT_SOURCE_DIR}/source/game/pickup.h
	${PROJECT_SOURCE_DIR}/source/game/playerCmd.h
	${PROJECT_SOURCE_DIR}/source/game/player.h
	${PROJECT_SOURCE_DIR}/source/game/playLoop.h
	${PROJECT_SOURCE_DIR}/source/game/projectile.h
	${PROJECT_SOURCE_DIR}/source/game/pWeapon.h
	${PROJECT_SOURCE_DIR}/source/game/spring.h
	${PROJECT_SOURCE_DIR}/source/game/spriteAnim.h
	${PROJECT_SOURCE_DIR}/source/game/sprite.h
	${PROJECT_SOURCE_DIR}/source/game/titlescreen.h
	${PROJECT_SOURCE_DIR}/source/game/travelObject.h
	${PROJECT_SOURCE_DIR}/source/game/world.h

	#source/
	${PROJECT_SOURCE_DIR}/source/filter.h
	${PROJECT_SOURCE_DIR}/source/kexlib.h

	#source/math
	${PROJECT_SOURCE_DIR}/source/math/mathlib.h

	#source/movie
	${PROJECT_SOURCE_DIR}/source/movie/movie.h

	#source/opengl
	${PROJECT_SOURCE_DIR}/source/opengl/dgl.h
	${PROJECT_SOURCE_DIR}/source/opengl/glcontext.h

	#source/renderer
	${PROJECT_SOURCE_DIR}/source/renderer/cpuVertexList.h
	${PROJECT_SOURCE_DIR}/source/renderer/fbo.h
	${PROJECT_SOURCE_DIR}/source/renderer/image.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderBackend.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderFont.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderMain.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderPostProcess.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderScene.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderScreen.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderUtils.h
	${PROJECT_SOURCE_DIR}/source/renderer/renderView.h
	${PROJECT_SOURCE_DIR}/source/renderer/shaderProg.h
	${PROJECT_SOURCE_DIR}/source/renderer/textureManager.h
	${PROJECT_SOURCE_DIR}/source/renderer/textureObject.h
	${PROJECT_SOURCE_DIR}/source/renderer/vertexBuffer.h

	#source/script
	${PROJECT_SOURCE_DIR}/source/script/scriptSystem.h

	#source/system
	${PROJECT_SOURCE_DIR}/source/system/endian.h
	${PROJECT_SOURCE_DIR}/source/system/input.h
	${PROJECT_SOURCE_DIR}/source/system/joystick.h
	${PROJECT_SOURCE_DIR}/source/system/keyboard.h
	${PROJECT_SOURCE_DIR}/source/system/mouse.h
	${PROJECT_SOURCE_DIR}/source/system/sound.h
	${PROJECT_SOURCE_DIR}/source/system/system.h
	${PROJECT_SOURCE_DIR}/source/system/thread.h
	${PROJECT_SOURCE_DIR}/source/system/timer.h

	#source/tools
	${PROJECT_SOURCE_DIR}/source/tools/spriteMake.h
)


include_directories(ANGELSCRIPT_DIR "${PROJECT_SOURCE_DIR}/lib/angelscript/sdk/angelscript/include")
include_directories(FFMPEG_DIR "${PROJECT_SOURCE_DIR}/lib/ffmpeg/FFmpeg-${FFMPEG_VERSION}")

find_library(ANGELSCRIPT_LIB
	     NAMES libangelscript.a
	     HINTS ${PROJECT_SOURCE_DIR}/lib/angelscript/lib/
	     )



find_library(AVUTIL_LIB
             NAMES libavutil.a
             HINTS  ${PROJECT_SOURCE_DIR}/lib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavutil/
             )

find_library(AVCODEC_LIB
             NAMES libavcodec.a
             HINTS ${PROJECT_SOURCE_DIR}/lib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavcodec/
             )

find_library(AVFORMAT_LIB
             NAMES libavformat.a
             HINTS ${PROJECT_SOURCE_DIR}/lib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libavformat/
             )

find_library(SWSCALE_LIB
             NAMES libswscale.a
             HINTS ${PROJECT_SOURCE_DIR}/lib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libswscale/
             )
find_library(SWRESAMPLE_LIB
             NAMES libswresample.a
             HINTS ${PROJECT_SOURCE_DIR}/lib/ffmpeg/FFmpeg-${FFMPEG_VERSION}/libswresample/
             )



 
 message(STATUS "debug- ${ANGELSCRIPT_LIB}")


add_executable(powerslave_ex ${POWERSLAVE_SOURCE} ${POWERSLAVE_HEADERS} ${FFMPEG_DIR} ${ANGELSCRIPT_DIR})


target_link_libraries(powerslave_ex ${ANGELSCRIPT_LIB})

target_link_libraries(powerslave_ex ${AVUTIL_LIB})
target_link_libraries(powerslave_ex ${AVCODEC_LIB})
target_link_libraries(powerslave_ex ${AVFORMAT_LIB})
target_link_libraries(powerslave_ex ${SWSCALE_LIB})
target_link_libraries(powerslave_ex ${SWRESAMPLE_LIB})
