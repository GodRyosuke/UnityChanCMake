# UnityChanをAssimpで表示する
CMakeを使ってUnityChanを表示させるプログラム。ビルドツールはNinjaを使用して開発したが、MinGWでもビルドできる。
開発環境は、Windows 10である。

## Prerequests
MinGW(Ninja)のインストール。Pathを通しておくこと。

ネットでビルド済みのAssimp, SDL2データは、ほとんどがVisual Studio向けなので、次のようにする。
例えば、Assimpについては、[このサイト](https://github.com/assimp/assimp/releases/tag/v5.2.5)からソースコードをダウンロード。次に、下記のコマンドを実行。
```bash
cd /path/to/assimp/
mkdir build
cd build
cmake -S .. -B . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/install
cmake --build .
cmake --install .
```
SDL2においてもほぼ同じようにできる。$必ずReleaseですること！$
Ninjaを使う場合、-G "MinGW Makefiles"のところを、-G "Ninja"にすればよい。

## Build
```bash
mkdir build
cd build
cmake -S .. -B . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

## Launch
buildディレクトリにあるUnityChanCMake.exeを実行。

## キー入力
マウス：カメラの視点切り替え

w, a, s, d: カメラの移動

i: 走るアニメーションに移行

q, ESC: プログラム修了

## 参考
Game Programing C++
https://github.com/gameprogcpp/code

OGL DEV
https://github.com/emeiri/ogldev

Assimp
https://github.com/assimp/assimp

UnityChan
https://unity-chan.com/
