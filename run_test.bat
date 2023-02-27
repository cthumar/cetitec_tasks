cmake -G "MinGW Makefiles" -S . -B build
cmake --build build
cd build && ctest
cd..