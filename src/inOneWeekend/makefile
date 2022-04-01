LINK    = @echo linking $@ && g++ 
GCC     = @echo compiling $@ && g++ 
GC      = @echo compiling $@ && gcc 
AR      = @echo generating static library $@ && ar crv
FLAGS   = -g -DDEBUG -W -Wall -fPIC
GCCFLAGS = 
DEFINES = 
HEADER  = -I ../common
LIBS    = 
LINKFLAGS =

#LIBS    += -lrt
#LIBS    += -pthread

OBJECT := main.o \

BIN_PATH = ./

TARGET = main

$(TARGET) : $(OBJECT) 
	$(LINK) $(FLAGS) $(LINKFLAGS) -o $@ $^ $(LIBS)

.cc.o:
	$(GCC) -c $(HEADER) $(FLAGS) $(GCCFLAGS) -o $@ $<

.c.o:
	$(GC) -c $(HEADER) $(FLAGS) -o $@ $<

clean:
	rm -rf $(TARGET) *.o *.so *.a
