CXXFLAGS := -std=c++17 -O2 -Iheaders $(shell pkg-config --cflags allegro-5)
LDLIBS   := $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 \
            allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 \
            allegro_memfile-5) -lm

compile:
	@mkdir -p exe
	g++ $(CXXFLAGS) src/*.cpp src/Snake/*.cpp -o exe/snake $(LDLIBS)

run:
	./exe/snake

clean:
	rm -rf exe

.PHONY: compile run clean