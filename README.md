## CuteMarkEd

### DESCRIPTION

A Qt-based, free and open source markdown editor with live HTML preview, math expressions, code syntax highlighting and syntax highlighting of markdown document.

![screenshot](images/screenshot_06.png)

### DOWNLOAD

[Sources](https://github.com/cloose/CuteMarkEd/archive/v0.8.1.tar.gz)  
[MS Windows (Installer)](https://github.com/cloose/CuteMarkEd/releases/download/v0.8.1/cutemarked-0.8.1.msi)  
[MS Windows (ZIP file)](https://github.com/cloose/CuteMarkEd/releases/download/v0.8.1/cutemarked-0.8.1.zip)  
[OpenSUSE 12.3 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[OpenSUSE 13.1 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  
[Fedora 19 (RPM)](https://build.opensuse.org/project/show?project=home%3Acloose1974)  

### NEWS

#### Version 0.8.1

New Features:

* `NEW` Added French translation created by etienne-gauvin

Fixes:

* `FIXED` Do not crash application if *Find Next* or *Find Previous* actions are used with a previously performed search

#### Version 0.8.0

New Features:

* `NEW` [Tool to insert a table in the markdown document](http://www.christian-loose.de/wordpress/2013/10/cutemarked-v0-8-0-preview-table-tool/)
* `NEW` [Tool to insert an image link in the markdown document](http://www.christian-loose.de/wordpress/2013/11/cutemarked-v0-8-0-preview-image-tool/)
* `NEW` Support for Markdown Extra-style footnotes
* `NEW` Menu item to switch between vertical and horizontal layout
* `NEW` Added style Byword Dark

Improvements:

* `IMPROVED` Added possibility to insert markdown markup (like bold, italic) without selection
* `IMPROVED` Added support for code highlighting without internet connection
* `IMPROVED` Added option to include javascript and CSS needed for code highlighting in the exported HTML

Fixes:

* `FIXED` Resolved problems with adding symbols using <kbd>Alt</kbd> with numpad key by changing shortcuts for styles from <kbd>Alt</kbd>+<kbd>1-6</kbd> to  <kbd>Ctrl</kbd>+<kbd>1-6</kbd>
* `FIXED` Several encoding problems were fixed.
  * German umlauts in table of contents
  * exported HTML was not marked as UTF-8
  * non-ascii characters with markdown markup like italic


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