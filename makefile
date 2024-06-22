.SUFFIXES : .cpp

CC = g++

CXXFLAGS = -g -std=c++11

OBJS = HWK4.o

TARGET = HWK4

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

.cpp.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<
clean:
	rm -f $(OBJS) $(TARGET) core
zipIt:
	zip -r HWK4.cpp makefile
