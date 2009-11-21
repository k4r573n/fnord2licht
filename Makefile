GCC_COMPILER = gcc
GCC_COMPILER_FLAGS = -ggdb -Wall -W -pedantic -std=c99

XML_INCS = `xml2-config --cflags`
XML_LIBS = `xml2-config --libs`

MISC_LIBS = -lm -lrt -lpthread
MISC_LIBS =

INCS = $(XML_INCS)
LIBS = $(XML_LIBS) $(MISC_LIBS)

TARGET = fnord2licht

SRC_DIRS := .
SRC_FILES := $(foreach DIR, $(SRC_DIRS), $(wildcard $(DIR)/*.c))
OBJS := $(patsubst %.c, %.o, $(SRC_FILES))

all : $(TARGET)
	@echo All done
	./fnord2licht -a 255 -r 255 -g 255 -b 255

$(TARGET) : $(OBJS)
	$(GCC_COMPILER) $(GCC_COMPILER_FLAGS) -o $@ $^ $(LIBS)

%.o : %.c
	$(GCC_COMPILER) $(GCC_COMPILER_FLAGS) -o $@ -c $(INCS) $<

edit:
	vim serial2.c

clean :
	rm -f $(OBJS) $(TARGET)
	@echo Clean done

.PHONY: clean
