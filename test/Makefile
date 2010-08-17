## File    Makefile
## Made by Tristan Carel
## Mail    <tristan.carel@gmail.com>
##
## Started on  Sat Dec 12 13:42:15 2009 Tristan Carel
## Last update Tue Aug 17 22:57:47 2010 Tristan Carel
##
## Copyright (C) 2009 Tristan Carel
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##

INCLUDE = -I..

all: iterators pprint

iterators: iterators.cc
	$(CXX) -I../misc iterators.cc -o $@

pprint: pprint.cc ../src/stl_tools/pprint.hpp
	$(CXX) -I../misc pprint.cc -o $@

worker: worker.o
	$(CXX) worker.o -ltbb -o $@

.cc.o: $<
	$(CXX) -c $(INCLUDE) -std=c++0x -pthread -Wall $< -o  $@

tests: test
	./test
