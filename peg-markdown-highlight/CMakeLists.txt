### peg-markdown-highlight library ###

set(peg-markdown-highlight_SRCS
    pmh_parser.cpp
    pmh_styleparser.cpp
)

add_library(peg-markdown-highlight STATIC ${peg-markdown-highlight_SRCS})


