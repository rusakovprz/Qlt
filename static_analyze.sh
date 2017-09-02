#!/bin/sh

#--enable=warning --enable=performance --enable=portability
#CPPCHECKOPTIONS += --enable=information
#CPPCHECKOPTIONS += --enable=unusedFunction
#CPPCHECKOPTIONS += --enable=style
#CPPCHECKOPTIONS += --enable=all

mkdir -p ./cppcheck_report/
cppcheck ./src/ --enable=warning --enable=performance --enable=portability --xml 2>./cppcheck_report/cppcheck.error
cppcheck-htmlreport --title=deviceConfig --report-dir=cppcheck_report --file=./cppcheck_report/cppcheck.error


qmake examples/qlt_examples.pro
make clean
scan-build -o clang_report make

