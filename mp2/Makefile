EXENAME = testimage
OBJS = png.o rgbapixel.o image.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall
LD = clang++
LDFFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME) testscene

$(EXENAME) : testimage.o $(OBJS)
	$(LD) testimage.o $(OBJS) $(LDFFLAGS) -o $(EXENAME)

testimage.o : testimage.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS)testimage.cpp

png.o : png.cpp
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

image.o : image.cpp
	$(CXX) $(CXXFLAGS) image.cpp


testscene : testscene.o scene.o $(OBJS)
	$(LD) $(LDFFLAGS) testscene.o scene.o $(OBJS) -o testscene

testscene.o : testscene.cpp scene.h png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testscene.cpp

scene.o : scene.h png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) scene.cpp

clean :
	-rm -f *.o $(EXENAME)
