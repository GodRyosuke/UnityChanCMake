@REM cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles"
@REM cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G "Ninja"
cmake --install build
cmake --build build