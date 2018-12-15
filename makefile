CXX=g++
LINK_INC:=-I./include/   $(LINK_INC)
LINK_LIB:=./lib/libcryptopp.a$(LINK_LIB)


TARGET = test


all:${TARGET}

$(TARGET):aesTool.o main.o
	$(CXX)  -o $@ $^ $(LINK_INC) $(LINK_LIB)

aesTool.o:aesTool.cpp
	$(CXX)  -c aesTool.cpp $(LINK_INC)

main.o:main.cpp
	$(CXX)  -c main.cpp $(LINK_INC)


clean:
	rm -rf *.o

