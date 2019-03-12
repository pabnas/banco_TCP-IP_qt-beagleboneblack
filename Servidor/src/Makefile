TARGET = ../bin/Servidor

INCLUDE_DIRS = -I../include
INCLUDE_LIBS = -L../lib

CXX = g++
CXXFLAGS += -O2 -DLINUX -Wall $(INCLUDE_DIRS)
#CXXFLAGS += -O2 -DDEBUG -DLINUX -Wall $(INCLUDE_DIRS)

LFLAGS += -lpthread -lrt -lm 

OBJECTS = main.o Comandos_generales.o tcpstream.o tcpacceptor.o tcpconnector.o TCP_IP_server.o

all: $(TARGET)

clean:
	rm -f *.a *.o $(TARGET) core *~ *.so *.lo
	clear
liba:
	g++ -O2 -DLINUX -Wall -I../include   -c -o Comandos_generales.o Comandos_generales.cpp
	g++ -O2 -DLINUX -Wall -I../include   -c -o operaciones.o operaciones.cpp
	ar rcs ../lib/liboperaciones.a $(LIBOBJECTS)
	ranlib ../lib/liboperaciones.a

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(CFLAGS) $(INCLUDE_LIBS) $(LFLAGS)

  
