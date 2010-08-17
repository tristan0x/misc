// File    iterators.cc
// Made by Tristan Carel
// Mail    <tristan.carel@gmail.com>
//
// Started on  Sat Dec 12 13:24:59 2009 Tristan Carel
// Last update Sat Dec 12 13:53:03 2009 Tristan Carel
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

#include <stl_tools/iterators.hpp>

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

#include <boost/lambda/lambda.hpp>
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

template <typename _Container>
std::ostream& operator<< (std::ostream& ostr, const _Container & container)
{
  std::copy (container.begin (), container.end (),
             std::ostream_iterator<typename _Container::value_type> (ostr, ", "));
  return ostr;
}

bool test_back_inserter_if ()
{
  std::vector<long> v;
  v += 1, 2, 3, 4, 5;

  std::vector<long> res;

  std::transform (v.begin (), v.end (),
                  stl_tools::back_inserter_if (res, !(boost::lambda::_1 % 2)),
                  boost::lambda::_1 * 3);

  std::cout << v << std::endl
            << res << std::endl;
}


int main ()
{
  bool success = true;

  success = test_back_inserter_if ();

  if (success)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
