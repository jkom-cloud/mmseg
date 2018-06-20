# MMSEG: A Word Identification System for Mandarin Chinese Text
#  Based On Two Variations of the Maximum Matching Algorithm  
#                        Chih-Hao Tsai                        
#
# MAKEFILE for mmseg and libmmseg.so                                      

###################################################################
# Modified By Zhaohong Lu
###################################################################
CC	= g++
CPPFLAGS= -Ofast -march=native -funroll-loops -fPIC -std=c++11 -lm -Wall -Wno-unused #-pipe
CPPSHRFLAGS= -Ofast -march=native -funroll-loops -fPIC -std=c++11 -lm -Wall -Wno-unused -shared
LDFLAGS := -L.

all: LIBMMSEG EXEMMSEG

###################################################################
LIBSRC  = src/Mmseg.cpp src/MmsegWrapper.cpp
EXESRC	= src/main.cpp 
###################################################################
LIBMMSEG: $(LIBSRC)
	$(CC) $(CPPSHRFLAGS) $(LIBSRC) -o ./libs/libmmseg.so

EXEMMSEG: $(EXESRC)
	$(CC) $(CPPFLAGS) $(LIBSRC) $(EXESRC) $(LDFLAGS) -o ./bin/mmseg
###################################################################

clean:
	rm -f ./libs/*.o ./libs/*.so ./bin/mmseg

# END of Makefile
