
Tested on ubunutu 9.04 and 9.10

requirements:

gcc and stuff

libfltk1.1
libfltk1.1-dev
libglut3
libglut3-dev
libboost1.37 and -dev (or higher version)
 
On Ubuntu or similar:
sudo apt-get install build-essential libfltk1.1 libfltk1.1-dev libglut3 libglut3-dev libboost1.37-dev


compile:

BOAZ:::: DON'T INCLUDE Flu_File_Chooser.cpp in the libflu build, it has some const char* problems


cd Libraries/xml/
make
cd ../../Src/
make



Not implemented: 
- Serial communication

