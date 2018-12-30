CFLAGS := -Wattributes -std=gnu99 -DHAVE_CONFIG_H  -DNDEBUG -DX_DISPLAY_MISSING -g -O2 -Wall -Wextra -Wno-deprecated-declarations -Wmissing-prototypes -Wshadow -Wpointer-arith -Wstrict-prototypes -Wcast-qual -Wwrite-strings -ffunction-sections -fdata-sections -fvisibility=hidden
LDFLAGS :=  --sysroot=/home/tangb/buildroot/buildroot-2018.08-rc1/output/host/arm-buildroot-linux-gnueabihf/sysroot -L/home/tangb/my-demo/mxa_services/mpc -mfloat-abi=hard -std=gnu99 -Wpointer-arith -Wstrict-prototypes -Wcast-qual -Wwrite-strings -ffunction-sections -fdata-sections -fvisibility=hidden -Wl,--gc-sections -lpthread -lmpdclient -lasound -lblkid 
##-L/home/tangb/buildroot/buildroot-2018.08-rc1/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/
C_INCLUDE_PATH := -I/home/tangb/my-imx6/03_tools/gcc-linaro-5.3-2016.02-x86_-linux-gnueabihf64_arm/arm-linux-gnueabihf/libc/usr/include -I./. -I./mpc -I/home/tangb/buildroot/buildroot-2018.08-rc1/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/

CROSS_COMPILE = arm-linux-gnueabihf-
# CROSS_COMPILE :=
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)gcc
CXX             = $(CROSS_COMPILE)g++
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump
RANLIB          = $(CROSS_COMPILE)ranlib
SIZE            = $(CROSS_COMPILE)size

default: bootloader

bl: $(obj)
	$(CC)  $(LDFLAGS) $(C_INCLUDE_PATH) -o bl_app bl_app.c
clean:
	-rm -f loader
	-rm -f *.o *~r
