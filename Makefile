CC = g++
LINKER = g++
CPPFLAGS = -std=c++11 -O2
LFLAGS = -lstdc++

OBJS = main.o chaos.o Stopwatch.o Matrix.o Particles.o Integration.o Protocol.o
TARGET = Glassius.out
#Rules

$(TARGET): $(OBJS)
		$(CC) $(LFLAGS) $(OBJS) -o $@

cpp.o:
		$(CC) $(CPPFLAGS) $<

clean:
		rm -f *.o
