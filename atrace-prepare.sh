#!/bin/sh

bison -W -v -d -o syscall-parser.tab.c syscall-parser.y
flex -o syscall-parser.yy.c syscall-parser.l
bison -W -v -d -p pp -o param-parser.tab.c param-parser.y
flex --prefix=pp -o param-parser.pp.c param-parser.l
