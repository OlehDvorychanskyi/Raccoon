cmake -S . -B build/MinGW_Release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DRACCOON_TYPE=Editor
cmake -E time cmake --build build/MinGW_Release -j 6
PAUSE