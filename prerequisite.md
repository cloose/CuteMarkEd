# cutemarked �� windows �ϵı���
* ��ϵͳ�Ļ������������Qt�Լ�mingw�Ŀ�ִ��Ŀ¼�����ҵĵ������ǣ�
  `D:\Qt5_5\5.5\mingw492_32\bin;D:\Qt5_5\Tools\mingw492_32\bin;`��
  ע�������ӵ�����Ŀ¼���ʼ���֣����ӵ���󣬿��ܻᱻ������������Ӱ�죩
* ����ִ����������

	```
	git clone -q https://github.com/cloose/CuteMarkEd.git E:\projects\cutemarked
	cd E:\projects\cutemarked
	git submodule update --init --recursive
	mkdir build
	cd build
	qmake ..\CuteMarkEd.pro
	mingw32-make
	```

# ���ػ�ʹ�õ�ǰ��


* �� `math_reveal.rcc`�ļ��ƶ�������֮���`cutemarked.exe`��Ŀ¼�¡�
>`math_reveal.rcc`�� cutemarked ִ������Ҫ��`MathJax`��`reveal`�������Դ�ļ�����˸��ļ���Ҫ���õ����ʵĵط���

* �� `data`�ļ����ƶ�������֮���`cutemarked.exe`��Ŀ¼�¡�
>`data`�ļ��д�ŵ��� cutemarked ִ��ʱƴд�������Ҫ���ֵ䣬��˸��ļ�����Ҫ���õ����ʵĵط���