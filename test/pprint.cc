// File    pprint.cc
// Made by Tristan Carel
// Mail    <tristan.carel@gmail.com>
//
// Started on  Sun Dec 13 12:40:04 2009 Tristan Carel
// Last update Sun Dec 13 12:48:04 2009 Tristan Carel
//
// Copyright (C) 2009 Tristan Carel
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//

#include <stl_tools/pprint.hpp>

#include <vector>
#include <iostream>
#include <cstdio>

#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

static
bool test_pprint ()
{
  std::vector<long> vl;
  vl += 1, 2, 3;

  std::cout << stl_tools::pprint<long> (42) << std::endl;
            //<< stl_tools::pprint<long> (vl) << std::endl;

  return true;
}

int main ()
{
  if (test_pprint ())
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
