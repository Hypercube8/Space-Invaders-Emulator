cd ../space-invaders-emulator/wasm
emcc src/*.c -Iinclude -o ../index.html -s USE_SDL=3 -s FULL_ES3=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 --embed-file shaders
cd ..
cd ..