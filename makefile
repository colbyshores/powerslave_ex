NAME=powerslave_ex
CXX=clang
FLAGS ="-std=c++11"
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

INCL+="-I/usr/include/SDL2"

LINK ="-lm"
LINK+="-lpthread"
LINK+="-lstdc++"
LINK+="-lGL"
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
	@cp -rT game_data bin/
	@mkdir $(@D)/mods
	@mkdir $(@D)/saves
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
