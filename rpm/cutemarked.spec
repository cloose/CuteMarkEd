%define qmake qmake
%define lrelease lrelease

Name:                   cutemarked
Summary:                Qt-based Markdown editor
Group:                  Productivity/Text/Editors
Version:                0.4.1
Release:                1
License:                GPL-2.0+
Url:                    http://github.com/cloose/CuteMarkEd
Source0:                %{name}-%{version}.tar.gz
BuildRoot:              %{_tmppath}/%{name}-%{version}-build

Requires:               cutemarked-plugin-fontawesome

BuildRequires:          libstdc++-devel 
BuildRequires:          gcc-c++ 
BuildRequires:          make
BuildRequires:          pkgconfig
BuildRequires:          pkgconfig(Qt5Core)
BuildRequires:          pkgconfig(Qt5Gui)
BuildRequires:          pkgconfig(Qt5Network)
BuildRequires:          pkgconfig(Qt5WebKitWidgets)
BuildRequires:          libqt5-qttools
BuildRequires:          libmarkdown-devel
BuildRequires:          update-desktop-files

%description
A Qt-based Markdown editor with live HTML preview and syntax highlighting of markdown document.

%package plugin-fontawesome
Summary:                Qt Iconengine - Fontawesome plugin
Group:                  Qt/Qt

%description plugin-fontawesome
This package provides the fontawesome iconengine plugin
 
%prep
%setup -q -n %{name}-%{version}

%build
%{qmake} 
make

%install
make INSTALL_ROOT="%buildroot" install

%files 
%defattr(-,root,root,755)
%_bindir/cutemarked
%{_datadir}/applications/%{name}.desktop

%files plugin-fontawesome
%defattr(-,root,root,-)
%{_libdir}/qt5/plugins/iconengines/libfontawesomeicon.so


%changelog

* Fri Jun 07 2013 Christian Looses <christian.loose@hamburg.de> 0.4.1-2
- New minor version 0.4.1 released

* Mon May 30 2013 Christian Looses <christian.loose@hamburg.de> 0.4.1-1
- First Linux packages

* Mon Apr 30 2013 Christian Looses <christian.loose@hamburg.de> 0.1.0-1
- Initial release
