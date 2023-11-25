cmake -S . -B build/VS2022_Release -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake -E time cmake --build build/VS2022_Release -j 6
PAUSE