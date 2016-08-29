# cutemarked 在 windows 上的编译
* 在系统的环境变量中添加Qt以及mingw的可执行目录，在我的电脑上是：
  `D:\Qt5_5\5.5\mingw492_32\bin;D:\Qt5_5\Tools\mingw492_32\bin;`。
  注意必须添加到环境目录的最开始部分（若加到最后，可能会被其他环境变量影响）
* 依次执行下列命令

	```
	git clone -q https://github.com/cloose/CuteMarkEd.git E:\projects\cutemarked
	cd E:\projects\cutemarked
	git submodule update --init --recursive
	mkdir build
	cd build
	qmake ..\CuteMarkEd.pro
	mingw32-make
	```

# 本地化使用的前提


* 将 `math_reveal.rcc`文件移动到编译之后的`cutemarked.exe`根目录下。
>`math_reveal.rcc`将 cutemarked 执行所需要的`MathJax`和`reveal`打包成资源文件，因此该文件需要放置到合适的地方。

* 将 `data`文件夹移动到编译之后的`cutemarked.exe`根目录下。
>`data`文件夹存放的是 cutemarked 执行时拼写检查所需要的字典，因此该文件夹需要放置到合适的地方。