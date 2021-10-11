NAME=powerslave_ex
#CC=/usr/local/vitasdk/bin/arm-vita-eabi-gcc
CXX=/usr/local/vitasdk/bin/arm-vita-eabi-g++



FLAGS ="-std=gnu++11"

#ifdef VITA
+FLAGS ="-Wl,-q -O2 -ftree-vectorize -fomit-frame-pointer -ffast-math -mcpu=cortex-a9 -fomit-frame-pointer -mthumb -pthread -Wdeclaration-after-statement -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -Wmissing-prototypes -Wno-pointer-to-int-cast -Wstrict-prototypes -Wempty-body -Wno-parentheses -Wno-switch -Wno-format-zero-length -Wno-pointer-sign -Os -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=format-security -Werror=implicit-function-declaration -Werror=missing-prototypes -Werror=return-type -Werror=vla -Wformat -fdiagnostics-color=auto -Wno-maybe-uninitialized fno-rtti -fno-exceptionsi"
#endif

FLAGS+="-fpermissive"
FLAGS+="-w"



#for GNUC compilers - disable optimizations that have alot of pointer casts
FLAGS+="-fno-strict-aliasing"
FLAGS+="-static"
FFMPEG_VERSION="n2.7.2"

INCL ="-Isource"
INCL+="-Isource/framework"
INCL+="-Isource/game"
INCL+="-Isource/math"
INCL+="-Isource/movie"
INCL+="-Isource/opengl"
INCL+="-Isource/renderer"
INCL+="-Isource/script"
INCL+="-Isource/script/objects"
INCL+="-Isource/script/al"
INCL+="-Isource/system"
INCL+="-Isource/system/sdl"
INCL+="-Isource/tools"
INCL+="-Isource/tools/mapEditor"
INCL+="-Ilib/angelscript/sdk/angelscript/include"
INCL+="-Ilib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)"

#ifdef VITA
	INCL+="-I/usr/local/vitasdk/arm-vita-eabi/include/"
#else
#	INCL+="-I/usr/include/SDL2"
#endif

#Modification 10/8/21 to link with vita sdk GL implementation
#LINK+="-lGL"
#ifdef VITA
	LINK+="/usr/local/vitasdk/arm-vita-eabi/lib/libvitaGL.a"
#else
	#LINK+="-lGL"
#endif


LINK+="-lpng"
LINK+="-logg"
LINK+="-lvorbisfile"
LINK+="-lopenal"
LINK+="-lSDL2"
LINK+="-lz"

LINK+="-Llib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavutil"
LINK+="-Llib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavcodec"
LINK+="-Llib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavformat"
LINK+="-Llib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libswscale"
LINK+="-Llib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libswresample"
LINK+="-lavutil"
LINK+="-lavcodec"
LINK+="-lavformat"
LINK+="-lswscale"
LINK+="-lswresample"


LINK+="-lstdc++"
LINK+="-lpthread"
LINK ="-lm"

OBJS=$(shell make/obj.sh)

bin/$(NAME): $(OBJS) lib/angelscript/sdk/angelscript/lib/libangelscript.a
	@echo "compiling executable $@"
	@mkdir -p $(@D)/shared game_data
	@$(CXX) -o $@ $^ $(LINK)
	@cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavutil/libavutil.so $(@D)/shared
	@cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavcodec/libavcodec.so $(@D)/shared
	@cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libavformat/libavformat.so $(@D)/shared
	@cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libswscale/libswscale.so $(@D)/shared
	@cp lib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)/libswresample/libswresample.so $(@D)/shared
	@cp -R game_data/powerslave_ex/* bin/
	@cp make/run.sh $(@D)

obj/%.o: %.cpp
	@echo "building object $@"
	@mkdir -p $(@D)
	@$(CXX) $(INCL) $(FLAGS) -c -o $@ $<

lib:
	@./make/lib.sh

run: bin/$(NAME)
	@./bin/run.sh

clean:
	@echo "cleaning"
	rm -rf bin obj
