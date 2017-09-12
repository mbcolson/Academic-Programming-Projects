CC = gcc
AS = gcc
CFLAGS = -g
LDFLAGS = -g
ASFLAGS = -g
CSRC = main.c
ASSRC = readStudent.S findMinIndex.S selSort.S swapStudent.S
EXE = main
$(EXE): $(CSRC:.c=.o) $(ASSRC:.S=.o)
%.d:	%.c
	 set -e; gcc $(CXXFLAGS) $^ -MM \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@ 

%.d:	%.S
	 set -e; gcc $(CXXFLAGS) $^ -MM \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@ 

clean:
	rm -f $(EXE) $(CSRC:.c=.o) $(ASSRC:.S=.o) $(CSRC:.c=.d) $(ASSRC:.S=.d)

include $(CSRC:.c=.d)
include $(ASSRC:.S=.d)
