###
# compile / compiler :
# 	make
#
# clean / nettoyage :
# 	make clean
# delete all files created during compilation /
# supprime tous les fichiers créer à la compilation
###


CC = g++
CFLAGS = -Wall -pedantic 
LIBFLAGS =

PROGRAM =
# add new .cpp files here
SRCS =
OBJS = $(SRCS:.cpp=.o)

###

DEPFILE = .depend
DEPFLAGS = -MM

.PHONY: default
default: all

.PHONY: all
ifeq($(wildcard $(DEPFILE)), )
all: $(DEPFILE)
	make --no-print-directory
else
include $(DEPFILE)

all: $(PROGNAME)
endif


$(PROGRAM) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPFILE) : $(SRCS)
	-rm $(DEPFILE)
	$(CC) $(DEPFLAGS) $^ >> $@


.PHONY: clean
clean:
	-rm $(PROGRAM) $(OBJS) $(DEPFILE)

