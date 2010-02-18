GCC_COMPILER = gcc
GCC_COMPILER_FLAGS = -ggdb -Wall -W -pedantic -std=c99

XML_INCS = `xml2-config --cflags`
XML_LIBS = `xml2-config --libs`

MISC_LIBS = -lm -lrt -lpthread
MISC_LIBS =

INCS = $(XML_INCS)
LIBS = $(XML_LIBS) $(MISC_LIBS)

TARGET = fnord2licht
#notify level  - 1..7
NOTE = 1

SRC_DIRS := .
SRC_FILES := $(foreach DIR, $(SRC_DIRS), $(wildcard $(DIR)/*.c))
OBJS := $(patsubst %.c, %.o, $(SRC_FILES))

note : $(TARGET)
	./fnord2licht -a 255 -r 255 -g 255 -b 255 -v -n $(NOTE)

an : $(TARGET)
	./fnord2licht -a 255 -r 255 -g 255 -b 255 -v

aus : $(TARGET)
	./fnord2licht -a 255 -r 0 -g 0 -b 0 -v

all : $(TARGET)
	@echo All done
	./fnord2licht -a 255 -r 255 -g 255 -b 255 -v

$(TARGET) : $(OBJS)
	$(GCC_COMPILER) $(GCC_COMPILER_FLAGS) -o $@ $^ $(LIBS)

%.o : %.c
	$(GCC_COMPILER) $(GCC_COMPILER_FLAGS) -o $@ -c $(INCS) $<

edit:
	vim *.c *.h

clean :
	rm -f $(OBJS) $(TARGET)
	@echo Clean done

.PHONY: clean
