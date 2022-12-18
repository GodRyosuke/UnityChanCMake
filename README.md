# UnityChanをAssimpで表示する
CMakeを使ってUnityChanを表示させるプログラム。ビルドツールはNinjaを使用。

## Prerequests
MinGW, Ninjaのインストール。Pathを通しておくこと。

Assimp, SDL2のインストールは、ほとんどがVisual Studio向けなので、次のようにする。
例えば、Assimpについては、[このサイト](https://github.com/assimp/assimp/releases/tag/v5.2.5)からソースコードをダウンロード。次に、下記のコマンドを実行。
```bash
cd /path/to/assimp/
mkdir build
cd build
cmake -S .. -B . -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/install
cmake --build .
cmake --install .
```
SDL2においてもほぼ同じようにできる。$必ずReleaseですること！$


## Build
Ninjaでビルドした。
```bash
mkdir build
cd build
cmake -S .. -B . -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

## Launch
buildディレクトリにあるUnityChanCMake.exeを実行。