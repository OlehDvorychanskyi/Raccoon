cmake -S . -B build/VS2022_Debug -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug 
cmake -E time cmake --build build/VS2022_Debug -j 6
PAUSE