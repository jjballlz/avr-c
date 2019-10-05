MCU=atmega328p
PORT=/dev/ttyUSB0
F_CPU=16000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=${F_CPU} -mmcu=${MCU}
TARGET=main
SRCS=main.c

all:
	${CC} ${CFLAGS} -c -o ${TARGET}.o ${SRCS}
	${CC} -mmcu=${MCU} ${TARGET}.o -o ${TARGET}.bin
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.bin ${TARGET}.hex

flash:
	avrdude -C/etc/avrdude.conf -v -carduino -p${MCU} -P${PORT} -b115200 -Uflash:w:${TARGET}.hex:i

clean:
	rm -f *.bin *.hex *.o
