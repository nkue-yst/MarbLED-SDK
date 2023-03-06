# 人工大理石透過型LEDタッチディスプレイのためのソフトウェアライブラリ＆ランタイム
![poster](https://user-images.githubusercontent.com/39930174/223172410-72b69af8-baf7-4b31-95a5-40dde126c700.png)

# ビルド
以下の手順によって`app`ディレクトリ下アプリケーションプログラム、アプリケーションを実行・切り替えるためのランタイムをビルドすることができます。
```
$ git clone https://github.com/nkue-yst/TouchLED-Middleware.git
$ git submodule update --init
$ mkdir build && cd build
$ cmake && make -j5
```

# アプリケーションプログラム
- `./app/AppGenerator <AppName>` を実行すると .dll(.so形式)のアプリケーションファイルを作成するための雛形が記述された`AppName.gen.hpp`、`AppName.gen.cpp`が自動生成されます。
- 生成された`AppName.gen.cpp`をコンパイル（cmake, makeでビルド）することによってランタイムの起動時にアプリケーションとしてロードされます。

# ランタイム
- `src/BaseApp.cpp`をビルドすることによって実行ファイル`TLL_BaseApp`が生成されます。
- RaspberryPiやアプリ開発用PC（Linux, WSL環境のみ対応）などで`TLL_BaseApp`を実行するとランタイムが起動します。
- また、起動時に`build/app/`ディレクトリ下に生成されているアプリケーションファイル（`.so`ファイル）を自動的にロードします。
- ランタイムプログラムの実行中に`build/app/AppRunner/`下に生成された`Run_<AppName>`を他ウィンドウなどで実行することで、その名前のアプリケーションに切り替えることができます。

# 使用可能API一覧
（提供API修正中のため整理中）
