## CuteMarkEd

### DESCRIPTION

A Qt-based, free and open source markdown editor with live HTML preview, math expressions, code syntax highlighting and syntax highlighting of markdown document.

![screenshot](http://cloose.github.io/CuteMarkEd/images/screenshot_06.png)

### DOWNLOAD

[Sources](https://github.com/cloose/CuteMarkEd/archive/v0.11.3.tar.gz)  
[MS Windows (Installer)](http://dl.bintray.com/cloose/CuteMarkEd/cutemarked-0.11.3.msi)  
[MS Windows (ZIP file)](http://dl.bintray.com/cloose/CuteMarkEd/cutemarked-0.11.3.zip)  
[OpenSUSE 13.2 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 20 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 21 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 22 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 23 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  

### NEWS

#### Version 0.11.3

Improvements:

* `IMPROVED` Update Russian translation

Fixes:

* `FIXED` Missing links in exported PDF file (#275)
* `FIXED` Use of non-native line endings when a file is saved (#97)
* `FIXED` Corrupt files on system crashes or running out of disk space (#285)
* `FIXED` Accessing all drives although the file explorer is not visible (#273)
* `FIXED` Relative paths in recently used files menu (#256)
 
#### Version 0.11.2

Improvements:

* `IMPROVED` Added Hungarian translation

Fixes:

* `FIXED` Editor pane jumping up and down during editing (#232)
* `FIXED` Missing mermaid CSS for styling in preview (#241)
* `FIXED` Correct order of HTML Preview/Source menu item (#242)
* `FIXED` Retrieval of last used style on application start on Linux (#257)
* `FIXED` Crash when switching between markdown converters (#260)

#### Version 0.11.1

Improvements:

* `IMPROVED` Updated French translation

Fixes:

* `FIXED` Custom shortcuts not working (#224)
* `FIXED` Disappearing spell checker highlighting (#228)
* `FIXED` Wrong german quotes snippet (#229)

#### Version 0.11.0

Highlights:

The 0.11.0 release offers support to create flowchart and sequence diagrams using [mermaid](https://github.com/knsv/mermaid). 

![screenshot](http://cloose.github.io/CuteMarkEd/images/20150426-cutemarked-diagrams.png)

The snippet completer was extended to also auto complete words from the document:

![screenshot](http://cloose.github.io/CuteMarkEd/images/20150426-cutemarked-word-completion.png)

New Features:

* `NEW` Added support to create diagrams using [mermaid](https://github.com/knsv/mermaid) (#215).
* `NEW` Added auto completion for words extracted from the document (#194)
* `NEW` Added option to ignore YAML header in editor and preview (#136, #139)
* `NEW` Added possibility to change keyboard shortcuts to the options dialog (#144)
* `NEW` Added zoom to HTML preview and the option to change the default font family and size for the HTML preview (#169)
* `NEW` Added synchronization of the current slide between editor and preview in presentation
mode (#184)

Improvements:

* `IMPROVED` More mnemonics in main menu and option dialog (#104)
* `IMPROVED` Also support file extension .mdown (#155)
* `IMPROVED` Save last used style on application exit (#159)
* `IMPROVED` Find/Replace widget can be closed with ESC key (#162) 

Fixes:

* `FIXED` Build with MSVC 2013 and MacOSX
* `FIXED` Parallel build with e.g. make -j2

### DEPENDENCIES

* [Qt 5.4](http://qt-project.org) (LGPL v2.1)
* [Discount 2.1.7](http://www.pell.portland.or.us/~orc/Code/discount/) (3-clause BSD)
* [PEG Markdown Highlight](http://hasseg.org/peg-markdown-highlight/) (MIT License)
* [hunspell 1.3.2](http://hunspell.sourceforge.net/) (LGPL v2.1)

### BUILD

##### Instructions

https://github.com/cloose/CuteMarkEd/wiki/Build-Instructions

##### Status

| Linux | Windows |
| ----- | ------- |
| [![Build Status](https://travis-ci.org/cloose/CuteMarkEd.png)](https://travis-ci.org/cloose/CuteMarkEd) | [![](https://ci.appveyor.com/api/projects/status/github/cloose/CuteMarkEd)](https://ci.appveyor.com/project/cloose/cutemarked) |

[![Stories in Ready](https://badge.waffle.io/cloose/CuteMarkEd.png?label=ready)](https://waffle.io/cloose/CuteMarkEd)

### HELP NEEDED

##### Packages

We really need help packaging CuteMarkEd. Especially for Linux and Mac OS X. For Linux there is already an [openSUSE Build Service project](https://build.opensuse.org/package/show/home:cloose1974/CuteMarkEd), but it's outdated. Please contact me if you like to help.

##### Translations

We use [Transifex](https://www.transifex.com/projects/p/cutemarked) for the translations. Currently we have translations like Chinese, Czech, German or Greek. But we are always interested in more translations.


### LINKS

[![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/cloose/CuteMarkEd?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)  
[Mailing List](https://groups.google.com/forum/#!forum/cutemarked)

[http://www.ohloh.net/p/CuteMarkEd](http://www.ohloh.net/p/CuteMarkEd)  
[http://freecode.com/projects/cutemarked](http://freecode.com/projects/cutemarked)  
[http://qt-apps.org/content/show.php/CuteMarkEd?content=158801](http://qt-apps.org/content/show.php/CuteMarkEd?content=158801)  
[http://www.heise.de/download/cutemarked-1191267.html](http://www.heise.de/download/cutemarked-1191267.html)  
[http://www.softpedia.com/get/Programming/File-Editors/CuteMarkEd.shtml](http://www.softpedia.com/get/Programming/File-Editors/CuteMarkEd.shtml)

[![CuteMarkEd - Download - heise online](http://www.heise.de/software/icons/download_logo1.png)](http://www.heise.de/download/cutemarked-1191267.html)
