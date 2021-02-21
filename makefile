# Author : Maulik Gohil (2768911)
# Change Log:
#	2020-02-10 > Created this file for just ep_crt et_crt
#	2020-02-11 > Addred commands for para_mma

all: ep_crt et_crt para_mm

ep_crt: ep.o timing.o
	gcc ep.o timing.o -o ep_crt

et_crt: et.o timing.o
	gcc et.o timing.o -lpthread -o et_crt

para_mm: para_mm.o timing.o
	gcc para_mm.o timing.o -lpthread -o para_mm

clear: ep_crt et_crt para_mm
	rm *.o ep_crt et_crt para_mm
