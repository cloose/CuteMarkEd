%if 0%{?suse_version}
%define _qt5_qmake /usr/%_lib/qt5/bin/qmake
%endif
%define lrelease lrelease
%if 0%{?fedora_version}
%define  debug_package %{nil}
%endif

Name:                   cutemarked
Summary:                Qt-based Markdown editor
Group:                  Productivity/Text/Editors
Version:                0.11.3
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
BuildRequires:          libmarkdown-devel
BuildRequires:          pkgconfig(hunspell)
%if 0%{?suse_version}
BuildRequires:          update-desktop-files
BuildRequires:          pkgconfig(Qt5Test)
BuildRequires:          pkgconfig(Qt5PrintSupport)
BuildRequires:          libqt5-qttools-devel
%endif
%if 0%{?fedora_version}
BuildRequires:          desktop-file-utils
BuildRequires:          pkgconfig(gstreamer-0.10) pkgconfig(gstreamer-app-0.10)
BuildRequires:          pkgconfig(sqlite3)
BuildRequires:          qt5-qttools-devel
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

%files 
%defattr(-,root,root,755)
%_bindir/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.*

%files plugin-fontawesome
%defattr(-,root,root,-)
%{_libdir}/qt5/plugins/iconengines/libfontawesomeicon.so
/usr/%_lib/qt5/plugins/iconengines


%changelog

* Mon Mar 28 2016 Christian Loose <christian.loose@hamburg.de> 0.11.3-1
- New patch version 0.11.3 released

* Fri Jan 01 2016 Christian Loose <christian.loose@hamburg.de> 0.11.2-1
- New patch version 0.11.2 released

* Mon Jul 06 2015 Christian Loose <christian.loose@hamburg.de> 0.11.1-1
- New patch version 0.11.1 released

* Sun Apr 26 2015 Christian Loose <christian.loose@hamburg.de> 0.11.0-1
- New minor version 0.11.0 released

* Wed Mar 11 2015 antoine Barbeyer (local build) <antoine.barbeyer@no-spam.com> - 0.10.2-2
- minor fix in spec file to build in fedora 21

* Fri Mar 06 2015 Christian Loose <christian.loose@hamburg.de> 0.10.2-1
- New patch version 0.10.2 released

* Sun Aug 24 2014 Christian Loose <christian.loose@hamburg.de> 0.10.1-1
- New patch version 0.10.1 released

* Wed Jul 23 2014 Christian Loose <christian.loose@hamburg.de> 0.10.0-1
- New minor version 0.10.0 released

* Mon Apr 07 2014 Christian Loose <christian.loose@hamburg.de> 0.9.2-1
- New patch version 0.9.2 released

* Fri Jan 31 2014 Christian Loose <christian.loose@hamburg.de> 0.9.1-1
- New patch version 0.9.1 released

* Sat Jan 25 2014 Christian Loose <christian.loose@hamburg.de> 0.9.0-1
- New minor version 0.9.0 released

* Tue Nov 19 2013 Christian Loose <christian.loose@hamburg.de> 0.8.1-1
- New patch version 0.8.1 released

* Fri Nov 08 2013 Christian Loose <christian.loose@hamburg.de> 0.8.0-1
- New minor version 0.8.0 released

* Thu Jul 04 2013 Christian Loose <christian.loose@hamburg.de> 0.6.1-1
- New patch version 0.6.1 released

* Tue Jun 25 2013 Christian Loose <christian.loose@hamburg.de> 0.6.0-1
- New minor version 0.6.0 released

* Fri Jun 14 2013 Christian Loose <christian.loose@hamburg.de> 0.5.0-1
- New minor version 0.5.0 released

* Fri Jun 07 2013 Christian Loose <christian.loose@hamburg.de> 0.4.1-2
- New patch version 0.4.1 released

* Thu May 30 2013 Christian Loose <christian.loose@hamburg.de> 0.4.1-1
- First Linux packages

* Tue Apr 30 2013 Christian Loose <christian.loose@hamburg.de> 0.1.0-1
- Initial release
