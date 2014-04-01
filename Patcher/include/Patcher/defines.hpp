#ifndef DEFINES_HPP
#define DEFINES_HPP

#define MAJOR_VERSION 0 //major version number (0..9999)
#define MINOR_VERSION 1 //minor version number (0..99)
#define PATCH_VERSION 0 //patch version number (0..99)

#define VERSION ((MAJOR_VERSION*100*100)+(MINOR_VERSION*100)+PATCH_VERSION)
#define LOG(sock,func,msg) std::cerr<<"[id:"<<sock.id()<<"] "<< func<<"()"<<" => "<<msg <<std::endl;

#endif
