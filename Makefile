###
# compile / compiler :
# 	make
#
# clean / nettoyage :
# 	make clean
###


CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11
LIBFLAGS = -lncurses

PROGRAM = line-and-column
# add new .cpp files here
SRCS = main.cpp color.cpp form.cpp board.cpp main_game.cpp config_load.cpp \
       main_window.cpp game_window.cpp menu_window.cpp \
       global_log.cpp option.cpp


OBJS = $(SRCS:.cpp=.o)

###

DEPFILE = .depend
DEPFLAGS = -MM

.PHONY: default
default: all

.PHONY: all
ifeq ($(wildcard $(DEPFILE)), )
all: $(DEPFILE)
	make --no-print-directory
else
include $(DEPFILE)

all: $(PROGRAM)
endif


$(PROGRAM) : $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBFLAGS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPFILE) : $(SRCS)
	-rm $(DEPFILE)
	$(CC) $(DEPFLAGS) $^ >> $@


.PHONY: clean
clean:
	-rm $(PROGRAM) $(OBJS) $(DEPFILE)

