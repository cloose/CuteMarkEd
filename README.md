## CuteMarkEd

### DESCRIPTION

A Qt-based, free and open source markdown editor with live HTML preview, math expressions, code syntax highlighting and syntax highlighting of markdown document.

![screenshot](http://cloose.github.io/CuteMarkEd/images/screenshot_06.png)

### DOWNLOAD

[Sources](https://github.com/cloose/CuteMarkEd/archive/v0.10.0.tar.gz)  
[MS Windows (Installer)](http://dl.bintray.com/cloose/CuteMarkEd/cutemarked-0.10.0.msi)  
[MS Windows (ZIP file)](http://dl.bintray.com/cloose/CuteMarkEd/cutemarked-0.10.0.zip)  
[OpenSUSE 12.3 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[OpenSUSE 13.1 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 19 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 20 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  

### NEWS

#### Version 0.10.1 (Linux only)

This release fixes some problems on Linux and hopefully makes the packaging for Linux easier.

Improvements:

* `IMPROVED` Added support for dictionaries installed by the package system.

Fixes:

* `FIXED` User snippets and user dictionaries are now saved to disk.
* `FIXED` Application binary is now installed to /usr/bin
* `FIXED` Link to system installed hoedown library

#### Version 0.10.0

Highlights:

The 0.10.0 release offers support to create presentations. The feature is still
experimental and needs more work. Your feedback is very appreciated.

![screenshot](http://cloose.github.io/CuteMarkEd/images/20140721-cutemarked-presentation.png)

New Features:

* `NEW` Added (experimental) support to create presentations using [reveal.js](http://lab.hakim.se/reveal-js/#/) (#122).
* `NEW` Added a file explorer view which allows to easily switch between multiple documents (#79)
* `NEW` Added context menu item to copy preview content as HTML (#133)
* `NEW` _Windows only_: Added support for showing recent files in taskbar jump list (#145)

Improvements:

* `IMPROVED` Updated the Qt library to version 5.2 (#145)


### DEPENDENCIES

* [Qt 5.2](http://qt-project.org) (LGPL v2.1)
* [Discount 2.1.7](http://www.pell.portland.or.us/~orc/Code/discount/) (3-clause BSD)
* [PEG Markdown Highlight](http://hasseg.org/peg-markdown-highlight/) (MIT License)
* [hunspell 1.3.2](http://hunspell.sourceforge.net/) (LGPL v2.1)

### BUILD

##### Instructions

https://github.com/cloose/CuteMarkEd/wiki/Build-Instructions

##### Status

[![Build Status](https://travis-ci.org/cloose/CuteMarkEd.png)](https://travis-ci.org/cloose/CuteMarkEd)
[![Stories in Ready](https://badge.waffle.io/cloose/CuteMarkEd.png?label=ready)](https://waffle.io/cloose/CuteMarkEd)

### HELP NEEDED

##### Packages

We really need help packaging CuteMarkEd. Especially for Linux and Mac OS X. For Linux there is already an [openSUSE Build Service project](https://build.opensuse.org/package/show/home:cloose1974/CuteMarkEd), but it's outdated. Please contact me if you like to help.

##### Translations

We use [Transifex](https://www.transifex.com/projects/p/cutemarked) for the translations. Currently we have translations like Chinese, Czech, German or Greek. But we are always interested in more translations.


### LINKS

[http://www.ohloh.net/p/CuteMarkEd](http://www.ohloh.net/p/CuteMarkEd)  
[http://freecode.com/projects/cutemarked](http://freecode.com/projects/cutemarked)  
[http://qt-apps.org/content/show.php/CuteMarkEd?content=158801](http://qt-apps.org/content/show.php/CuteMarkEd?content=158801)  
[http://www.heise.de/download/cutemarked-1191267.html](http://www.heise.de/download/cutemarked-1191267.html)  
[http://www.softpedia.com/get/Programming/File-Editors/CuteMarkEd.shtml](http://www.softpedia.com/get/Programming/File-Editors/CuteMarkEd.shtml)

[![CuteMarkEd - Download - heise online](http://www.heise.de/software/icons/download_logo1.png)](http://www.heise.de/download/cutemarked-1191267.html)
