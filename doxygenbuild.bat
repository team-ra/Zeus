@echo OFF
SET ROOTDIR=%cd%
echo %ROOTDIR%
doxygen
cd ./docs/latex
make
dir
copy refman.pdf refmannew.pdf