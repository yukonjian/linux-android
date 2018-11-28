CC=/opt/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-gcc

OBJS=lcdtest.c
LDFLAGS=-pie -fPIE

all:lcdtest

lcdtest: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f lcdtest *.o
