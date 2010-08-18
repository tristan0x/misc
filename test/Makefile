## File    Makefile
## Made by Tristan Carel
## Mail    <tristan.carel@gmail.com>
##
## Started on  Sat Dec 12 13:42:15 2009 Tristan Carel
## Last update Wed Aug 18 23:25:29 2010 Tristan Carel

INCLUDE = -I..

all: iterators pprint

iterators: iterators.cc
	$(CXX) -I../misc iterators.cc -o $@

pprint: pprint.cc ../src/stl_tools/pprint.hpp
	$(CXX) -I../misc pprint.cc -o $@

worker: worker.o
	$(CXX) worker.o -ltbb -o $@

async_read: async_read.o
	$(CXX) -g async_read.o -ltbb -o $@

.cc.o: $<
	$(CXX) -g -c $(INCLUDE) -std=c++0x -pthread -Wall $< -o  $@

tests: test
	./test
