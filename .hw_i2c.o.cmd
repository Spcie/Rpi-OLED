cmd_/home/pi/gitcode/Rpi-OLED/hw_i2c.o := gcc -Wp,-MD,/home/pi/gitcode/Rpi-OLED/.hw_i2c.o.d  -nostdinc -isystem /usr/lib/gcc/arm-linux-gnueabihf/6/include -I./arch/arm/include -I./arch/arm/include/generated/uapi -I./arch/arm/include/generated  -I./include -I./arch/arm/include/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -fno-PIE -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fno-ipa-sra -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfp -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -Wno-frame-address -O2 --param=allow-store-data-races=0 -DCC_HAVE_ASM_GOTO -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -Werror=incompatible-pointer-types  -DMODULE  -DKBUILD_BASENAME='"hw_i2c"'  -DKBUILD_MODNAME='"OLED_Dev"' -c -o /home/pi/gitcode/Rpi-OLED/.tmp_hw_i2c.o /home/pi/gitcode/Rpi-OLED/hw_i2c.c

source_/home/pi/gitcode/Rpi-OLED/hw_i2c.o := /home/pi/gitcode/Rpi-OLED/hw_i2c.c

deps_/home/pi/gitcode/Rpi-OLED/hw_i2c.o := \
  /home/pi/gitcode/Rpi-OLED/hw_i2c.h \
  /home/pi/gitcode/Rpi-OLED/hw_gpio.h \

/home/pi/gitcode/Rpi-OLED/hw_i2c.o: $(deps_/home/pi/gitcode/Rpi-OLED/hw_i2c.o)

$(deps_/home/pi/gitcode/Rpi-OLED/hw_i2c.o):
