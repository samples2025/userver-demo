# Сборка
Для запуска сборки, открыть проект в VSCode, в devcontainer, и выполнить:
```
mkdir build
cmake -S./ -B./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build
```
или
```
./build.sh
```
