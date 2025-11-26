# OpenGLES-SDL3-WASM
An example of an OpenGLES app that uses SDL3 for windowing and can make either web or native builds.
## Setup
If it isn't already there, clone cimgui into its respective directory.
```
git clone --recursive https://github.com/cimgui/cimgui.git lib/cimgui
```
If you are planning to make a web build, you will also need the Emscripten SDK. Run the emscripten.sh file in order to set up your enviroment to use Emscripten tools.
```
git clone https://github.com/emscripten-core/emsdk.git emsdk
cd scripts
. emscripten.sh
cd ..
```
## Building
Run the ```Makefile``` using ```make``` for Linux builds, and ```emmake make``` for web builds. <br><br/> 
```make``` - Creates all the core dependencies and builds the app.  
```make clean``` - Removes the build files for recompilation.  
```make lclean``` - Removes ```libcimgui.a``` for recompilation.  
```make fclean``` - Calls ```clean```, ```lclean```, and ```fclean``` simultaneously.  
```make re``` - Runs ```fclean``` then builds the project. <br><br/>
```emmake make run``` - Only works with web builds, starts up a simple http server. 
## Details
This example just starts up a simple *cimgui* app that has *SDL3* for windowing and *OpenGL* as a backend. The *OpenGL* implementation used is *OpenGLES 3.0* which gives interoperability with *WebGL 2.0*. Refer to the *SDL3*, *cimgui*, and *Khronos* docs for more information.  
## Links
- [SDL3 Wiki](https://wiki.libsdl.org/SDL3/FrontPage)
- [Khronos registry](https://registry.khronos.org/OpenGL-Refpages/es3.0/)
- [cimgui](https://github.com/cimgui/cimgui)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [Emscripten docs](https://emscripten.org/)