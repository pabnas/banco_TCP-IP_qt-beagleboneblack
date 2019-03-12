TARGET = ../bin/Cliente

INCLUDE_DIRS = -I../include

CXX = g++
##CXX = arm-linux-gnueabihf-g++
CXXFLAGS += -O2 -DLINUX -Wall $(INCLUDE_DIRS)
#CXXFLAGS += -O2 -DDEBUG -DLINUX -Wall $(INCLUDE_DIRS)

LFLAGS += -lpthread -lrt -lm 

OBJECTS = main2.o tcpstream.o tcpacceptor.o tcpconnector.o TCP_IP.o lcd.o Teclado.o BlackCore.o BlackGPIO.o BlackADC.o BlackDirectory.o serialib.o BlackMutex.o 

all:	$(TARGET)

clean:
	rm -f *.a *.o $(TARGET) core *~ *.so *.lo
	clear

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(CFLAGS) $(INCLUDE_LIBS) $(LFLAGS)

  
