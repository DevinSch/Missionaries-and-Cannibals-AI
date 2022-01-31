# Generic Makefile
# Note. Comments are preceded with #.

CCC=g++
# list all warnings
CCCFLAGS= -Wall -g -std=c++11 -lX11

# all is called a target, after the colon you have dependencies
# ie. "the target all is dependent on the executables
all : Problem1

# the target <excecutable1> is dependent on the list of dependencies
# the line following  is the required executable (don't need to adjust it)
# Note: executable lines, ie. $(CCC) ..., must always begin with a tab.
# $^ = this target
# $@ = this/these dependencies

Problem1 : Problem1.o
	$(CCC) $(CCCFLAGS) $^ -o $@

# if there is more than one problem to do on an assignment you can compile
# all the questions at the same time
# <executable2> : <executable2> dependencies spaces between (usually .o files)
#	$(CCC) $(CCCFLAGS) $^ -o $@

# default rule compiling .cc to .o
# all .o file targets are dependent on the corresponding .cc files
# $< = the corresponding .cc file
%.o : %.cc
	$(CCC) -c $(CCCFLAGS) $<

# If you are using .h files you need to indicate that the .o file targets
# are dependent on corresponding .h files
# Ex. file.o : file.h
Problem1.o : People.h

# Clean out your directory but keep executables with command "clean".  Gets rid
# of files you don't need anymore
clean:
	rm -f *.o *~ *% *# .#*

# Clean out your directory including executables with command "clean-all"
clean-all: clean
	rm -f Problem1
