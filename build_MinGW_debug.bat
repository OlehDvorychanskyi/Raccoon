cmake -S . -B build/MinGW_Debug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake -E time cmake --build build/MinGW_Debug
PAUSE