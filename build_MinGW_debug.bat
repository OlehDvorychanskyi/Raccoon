cmake -S . -B build/MinGW_Debug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DRACCOON_TYPE=Editor
cmake -E time cmake --build build/MinGW_Debug -j 6
PAUSE