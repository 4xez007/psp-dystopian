TARGET = dystopia
OBJS = main.o world.o

INCDIR =
CFLAGS =
CXXFLAGS =
ASFLAGS =

LIBS = -lpspgu -lpspgum -lpspctrl -lpspdisplay -lm

BUILD_PRX = 1
PSP_EBOOT_TITLE = Dystopia

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_ICON = ICON0.PNG

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
