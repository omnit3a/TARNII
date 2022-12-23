CC=gcc
CCFLAGS=-o $(OUTFILE) -I$(HDRDIR)
CCINPUT=$(INFILES)

SRCDIR=src
INFILES=$(SRCDIR)/*.c
HDRDIR=include

OUTDIR=bin
OUTFILE=$(OUTDIR)/tarnii-emu

all: clean
	clear
	$(CC) $(CCINPUT) $(CCFLAGS)
	
clean:
	rm -rf $(OUTFILE)
