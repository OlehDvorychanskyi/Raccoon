cmake -S . -B build/Templates/Windows -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DRACCOON_TYPE=Game -DBUILD_TEMPLATES=True
cmake -E time cmake --build build/Templates/Windows -j 6
PAUSE