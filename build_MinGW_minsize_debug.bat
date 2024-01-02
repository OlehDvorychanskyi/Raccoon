cmake -S . -B build/MinGW_MinSizeDebug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DRACCOON_TYPE=Editor
cmake -E time cmake --build build/MinGW_MinSizeDebug -j 6
PAUSE