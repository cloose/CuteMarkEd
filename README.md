## CuteMarkEd

### DESCRIPTION

A Qt-based, free and open source markdown editor with live HTML preview, math expressions, code syntax highlighting and syntax highlighting of markdown document.

![screenshot](http://cloose.github.io/CuteMarkEd/images/screenshot_06.png)

### DOWNLOAD

[Sources](https://github.com/cloose/CuteMarkEd/archive/v0.9.2.tar.gz)  
[MS Windows (Installer)](http://dl.bintray.com/cloose/CuteMarkEd/cutemarked-0.9.2.msi)  
[MS Windows (ZIP file)](http://dl.bintray.com/cloose/CuteMarkEd/cutemarked-0.9.2.zip)  
[OpenSUSE 12.3 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[OpenSUSE 13.1 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 19 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 20 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  

### NEWS

#### Version 0.9.2

New Features:

* `NEW` Added Spanish translation created by moguman
* `NEW` Added Portuguese (Brazil) translation created by cassiocardoso
* `NEW` Added Russian translation created by maxbart

Improvements:

* `IMPROVED` Updated the [fontawesome](http://fontawesome.io/) icons to version 4.0.3

#### Version 0.9.1 - Linux only

Fixes:

* `FIXED` Build problem on Linux caused by using the system-provided discount library.

#### Version 0.9.0

New Features:

* `NEW` Added a snippets system, that can be activated with the shortcut <kbd>Ctrl+Space</kbd>. We provide several built-in snippets but the system can be extended with user-defined snippets. This powerful functionality can be used to autocomplete Markdown syntax, for inserting repetitive text blocks or even to provide often used document templates. (#81)
* `NEW` Added _"Go to Line"_ menu item (#114)
* `NEW` Added options _"case sensitive"_, _"whole words only"_ and _"use regular expressions"_ to find/replace functionality (#63)
* `NEW` Support for adding the selected word to an user dictionary (#78)
* `NEW` Option to change width of tab characters (#102)
* `NEW` Option for superscript Markdown extension (#92)
* `NEW` Option to control word wrap in Markdown editor (#46)
* `NEW` Added Japanese translation created by k0ta0uchi (#94)
* `NEW` Support for additional Markdown converters (#87)

Improvements:

* `IMPROVED` Updated the code highlighting library [highlight.js](http://highlightjs.org/) to version 7.5 (#90)
* `IMPROVED` Improved perceived performance while typing in long Markdown documents (#100)

Fixes:

* `FIXED` Changed shortcuts for Blockquote to <kbd>Ctrl+Shift+Q</kbd> and for Insert Image to <kbd>Ctrl+Shift+I</kbd> to prevent ambiguous shortcuts on Linux (#115)



### DEPENDENCIES

* Qt 5.x (LGPL v2.1)
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

We use [Transifex](https://www.transifex.com/projects/p/cutemarked) for the translations. Currently we have translations for Chinese, Czech, German and Greek. We are always interested in more translations.


### LINKS

[http://www.ohloh.net/p/CuteMarkEd](http://www.ohloh.net/p/CuteMarkEd)  
[http://freecode.com/projects/cutemarked](http://freecode.com/projects/cutemarked)  
[http://qt-apps.org/content/show.php/CuteMarkEd?content=158801](http://qt-apps.org/content/show.php/CuteMarkEd?content=158801)  
[http://www.heise.de/download/cutemarked-1191267.html](http://www.heise.de/download/cutemarked-1191267.html)  
[http://www.softpedia.com/get/Programming/File-Editors/CuteMarkEd.shtml](http://www.softpedia.com/get/Programming/File-Editors/CuteMarkEd.shtml)

[![CuteMarkEd - Download - heise online](http://www.heise.de/software/icons/download_logo1.png)](http://www.heise.de/download/cutemarked-1191267.html)
