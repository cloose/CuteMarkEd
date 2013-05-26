## CuteMarkEd


### DESCRIPTION

A Qt-based, free and open source markdown editor with live HTML preview, math expressions, code syntax highlighting and syntax highlighting of markdown document.

![screenshot](https://raw.github.com/cloose/CuteMarkEd/develop/images/screenshot_04.png)

### DOWNLOAD

[Sources](https://github.com/cloose/CuteMarkEd/archive/v0.4.0.tar.gz)  
[MS Windows (ZIP file)](http://dl.bintray.com/cloose/CuteMarkEd#cutemarked-0.4.0.zip)

### NEWS

#### Version 0.4.0

* `NEW` Added search & replace command to markdown editor
* `NEW` New CSS styles 'Clearness' and 'Clearness Dark'
* `NEW` Document statistics with line, word and character count
* `NEW` 'Center Paragraph' formatting command

* `IMPROVED` 'Export to PDF' function with selection of paper size and orientation
* `IMPROVED` Handling of links to local resource in HTML preview

* `FIX` Use fixed-pitch font for markdown editor on MS Windows
* `FIX` Missing character in HTML preview when markdown document did not end with a line break
* `FIX` `<style>` elements are not parsed anymore but included in the generated HTML


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

### BUILD STATUS

[![Build Status](https://travis-ci.org/cloose/CuteMarkEd.png)](https://travis-ci.org/cloose/CuteMarkEd)

### LINKS

[http://www.ohloh.net/p/CuteMarkEd](http://www.ohloh.net/p/CuteMarkEd)  
[http://freecode.com/projects/cutemarked](http://freecode.com/projects/cutemarked)
