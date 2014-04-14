cd ..
cd mm
flex.exe -olex.mm.cpp mm.lpp
bison.exe -d -v -b mm mm.ypp