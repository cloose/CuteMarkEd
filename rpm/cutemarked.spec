%if 0%{?suse_version}
%define _qt5_qmake qmake
%endif
%if 0%{?suse_version} >= 1310
%define _qt5_qmake qmake-qt5
%endif
%define lrelease lrelease
%if 0%{?fedora_version}
%define  debug_package %{nil}
%endif

Name:                   cutemarked
Summary:                Qt-based Markdown editor
Group:                  Productivity/Text/Editors
Version:                0.9.0
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
BuildRequires:          libqt5-qttools-devel
BuildRequires:          libmarkdown-devel
BuildRequires:          pkgconfig(hunspell)
%if 0%{?suse_version}
BuildRequires:          update-desktop-files
%endif
%if 0%{?fedora_version}
BuildRequires:          desktop-file-utils
BuildRequires:          pkgconfig(gstreamer-0.10) pkgconfig(gstreamer-app-0.10)
BuildRequires:          pkgconfig(sqlite3)
%endif

%description
A Qt-based Markdown editor with live HTML preview and syntax highlighting of markdown document.

%package plugin-fontawesome
Summary:                Qt Iconengine - Fontawesome plugin
Group:                  Qt/Qt
License:                BSD-3-Clause

%description plugin-fontawesome
This package provides the fontawesome iconengine plugin
 
%prep
%setup -q -n %{name}-%{version}

%build
%{_qt5_qmake} 
make

%install
make INSTALL_ROOT="%buildroot" install

%if 0%{?fedora_version}
mkdir $RPM_BUILD_ROOT%{_bindir}
mv $RPM_BUILD_ROOT%{_qt5_bindir}/cutemarked $RPM_BUILD_ROOT%{_bindir}/cutemarked
%endif

%if 0%{?suse_version} >= 1310
mkdir $RPM_BUILD_ROOT%{_bindir}
mv $RPM_BUILD_ROOT%{_libdir}/qt5/bin/cutemarked $RPM_BUILD_ROOT%{_bindir}/cutemarked
%endif

%files 
%defattr(-,root,root,755)
%_bindir/cutemarked
%{_datadir}/applications/%{name}.desktop

%files plugin-fontawesome
%defattr(-,root,root,-)
%{_libdir}/qt5/plugins/iconengines/libfontawesomeicon.so


%changelog

* Thu Jan 25 2014 Christian Looses <christian.loose@hamburg.de> 0.9.0-1
- New minor version 0.9.0 released

* Thu Nov 19 2013 Christian Looses <christian.loose@hamburg.de> 0.8.1-1
- New patch version 0.8.1 released

* Thu Nov 08 2013 Christian Looses <christian.loose@hamburg.de> 0.8.0-1
- New minor version 0.8.0 released

* Thu Jul 04 2013 Christian Looses <christian.loose@hamburg.de> 0.6.1-1
- New patch version 0.6.1 released

* Tue Jun 25 2013 Christian Looses <christian.loose@hamburg.de> 0.6.0-1
- New minor version 0.6.0 released

* Fri Jun 14 2013 Christian Looses <christian.loose@hamburg.de> 0.5.0-1
- New minor version 0.5.0 released

* Fri Jun 07 2013 Christian Looses <christian.loose@hamburg.de> 0.4.1-2
- New patch version 0.4.1 released

* Thu May 30 2013 Christian Looses <christian.loose@hamburg.de> 0.4.1-1
- First Linux packages

* Tue Apr 30 2013 Christian Looses <christian.loose@hamburg.de> 0.1.0-1
- Initial release
