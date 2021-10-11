NAME=powerslave_ex
ifdef VITA
	CXX=/usr/local/vitasdk/bin/arm-vita-eabi-g++
else
	CXX=g++
endif

FLAGS ="-std=gnu++11"

ifdef VITA
	FLAGS+="-Wl,-q -O2 -ftree-vectorize -fomit-frame-pointer -ffast-math -mcpu=cortex-a9 -fomit-frame-pointer -mthumb -pthread -Wdeclaration-after-statement -Wall -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -Wmissing-prototypes -Wno-pointer-to-int-cast -Wstrict-prototypes -Wempty-body -Wno-parentheses -Wno-switch -Wno-format-zero-length -Wno-pointer-sign -Os -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=format-security -Werror=implicit-function-declaration -Werror=missing-prototypes -Werror=return-type -Werror=vla -Wformat -fdiagnostics-color=auto -Wno-maybe-uninitialized -fno-rtti -fno-exceptions"
endif

FLAGS+="-fpermissive"
FLAGS+="-w"



#for GNUC compilers - disable optimizations that have alot of pointer casts
FLAGS+="-fno-strict-aliasing"
FLAGS+="-static"
FFMPEG_VERSION="n2.7.2"

INCL="-Isource"
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
INCL+="-Ilib/angelscript/include"
INCL+="-Ilib/ffmpeg/FFmpeg-$(FFMPEG_VERSION)"



ifdef VITA
	INCL+="-I/usr/local/vitasdk/arm-vita-eabi/include/SDL2"
else
	INCL+="-I/usr/include/SDL2"
endif

LINK="-lGL"



LINK+="-lpng"
LINK+="-logg"
LINK+="-lvorbisfile"
LINK+="-lopenal"
LINK+="-lSDL2"
LINK+="-lz"

LINK+="-lstdc++"
LINK+="-lpthread"
LINK+="-lm"


OBJS=$(shell make/obj.sh)


bin/$(NAME): $(OBJS) lib/angelscript/lib/libangelscript.a lib/ffmpeg/FFmpeg-n2.7.2/libavutil/libavutil.a lib/ffmpeg/FFmpeg-n2.7.2/libavcodec/libavcodec.a lib/ffmpeg/FFmpeg-n2.7.2/libavformat/libavformat.a lib/ffmpeg/FFmpeg-n2.7.2/libswscale/libswscale.a lib/ffmpeg/FFmpeg-n2.7.2/libswresample/libswresample.a

#lib/angelscript/lib/libangelscript.a lib/ffmpeg/FFmpeg-n2.7.2/libavutil/libavutil.a lib/ffmpeg/FFmpeg-n2.7.2/libavcodec/libavcodec.a lib/ffmpeg/FFmpeg-n2.7.2/libavformat/libavformat.a lib/ffmpeg/FFmpeg-n2.7.2/libswscale/libswscale.a lib/ffmpeg/FFmpeg-n2.7.2/libswresample/libswresample.a




	@echo "compiling executable $@"
	@mkdir -p $(@D)/shared game_data
	@$(CXX) -o $@ $^ $(LINK)

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
