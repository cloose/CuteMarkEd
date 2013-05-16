## CuteMarkEd


### DESCRIPTION

A Qt-based Markdown editor with live HTML preview and syntax highlighting of markdown document.

![screenshot](https://raw.github.com/cloose/CuteMarkEd/develop/images/screenshot_03.png)

### DOWNLOAD

[Sources](https://bitbucket.org/cloose/cutemarked/downloads/cutemarked-src-0.3.0.tar.gz)  
[MS Windows (ZIP file)](https://bitbucket.org/cloose/cutemarked/downloads/cutemarked-0.3.0.zip)

### NEWS

#### Version 0.3.0

* `NEW`  Print HTML function 
* `NEW`  Added several new functions for text formatting (strong, emphasize, strikethrough and inline code)
* `NEW`  Use [Kevin Burke's Markdown.css](http://kevinburke.bitbucket.org/markdowncss/) as default style for the live preview
* `NEW`  Synchronize scrollbars of markdown editor and live preview  
* `NEW` Support for displaying math expressions in HTML using [MathJax](http://www.mathjax.org/)
* `NEW` Support for code syntax highlighting using [Highlight.js](http://softwaremaniacs.org/soft/highlight/en/)
* `NEW` Support for non-latin languages

* `IMPROVED` Add icons to main menu

* `FIX`  Blocking UI when inserting big text using copy&paste


#### Version 0.2.0

* `NEW`  Add table of contents view with jump to header function  
* `NEW`  New default theme for syntax highlighting of the markdown document
* `NEW`  German translation  
* `NEW`  Copy HTML source to clipboard function added to edit menu  

* `FIX`  Behavior of splitter during window resize


#### Version 0.1.0

First release with basic functionality working. 

### DEPENDENCIES

* Qt 5.x (LGPL v2.1)
* [Discount 2.1.6](http://www.pell.portland.or.us/~orc/Code/discount/) (3-clause BSD)
* [PEG Markdown Highlight](http://hasseg.org/peg-markdown-highlight/) (MIT License)
