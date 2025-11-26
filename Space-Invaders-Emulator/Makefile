ifdef EMSCRIPTEN
	CMAKE = emcmake cmake
	CC = emcc
	OUTPUT = app.html
	CFLAGS += --shell-file minimal.html -sUSE_SDL=3 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sALLOW_MEMORY_GROWTH=1
else
	CMAKE = cmake
	CC = gcc
	OUTPUT = app
	LDLIBS += -lsdl3 -lGLESv3
endif

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BUILD_DIR = build

SRCS = $(SRC_DIR)/*.c 
CPPFLAGS += -Ilib/cimgui
LDFLAGS += -Llib
LDLIBS += -lcimgui_sdl

all: $(BUILD_DIR)/$(OUTPUT) 

$(LIB_DIR)/cimgui/project/build/CMakeCache.txt:
	mkdir -p $(LIB_DIR)/cimgui/project/build
	mkdir $(LIB_DIR)/cimgui/project/lists
	cp CMakeLists.txt $(LIB_DIR)/cimgui/project/lists
	cd $(LIB_DIR)/cimgui/project/build && $(CMAKE) ../lists

$(LIB_DIR)/libcimgui_sdl.a: $(LIB_DIR)/cimgui/project/build/CMakeCache.txt
	cd $(LIB_DIR)/cimgui/project/build && cmake --build .
	mv $(LIB_DIR)/cimgui/project/build/libcimgui_sdl.a $(LIB_DIR)

$(BUILD_DIR)/$(OUTPUT): $(LIB_DIR)/libcimgui_sdl.a
	$(CC) $(SRCS) -o $(BUILD_DIR)/$(OUTPUT) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

ifdef EMSCRIPTEN
run:
	python -m http.server --directory $(BUILD_DIR)
endif

clean:
	rm -rf $(BUILD_DIR)/*

lclean: clean
	rm -f $(LIB_DIR)/libcimgui_sdl.a
	
fclean: lclean
	rm -rf $(LIB_DIR)/cimgui/project

re: fclean all

.PHONY: run clean lclean fclean re