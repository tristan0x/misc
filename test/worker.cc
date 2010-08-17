// File    test.cc
// Made by Tristan Carel
// Mail    <tristan.carel@gmail.com>
//
// Started on  Sun Aug 15 15:24:46 2010 Tristan Carel
// Last update Tue Aug 17 01:23:05 2010 Tristan Carel
//
// Copyright (C) 2010 Tristan Carel
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

#include <misc/task/worker.hh>
#include <misc/traits/boost.hh>

#include <iostream>

void throws ()
{
  throw 0;
}

int add (int l, int r)
{
  return l + r;
}


struct foo
{
  void bar ()
  {
    std::cout << "foo::bar !" << std::endl;
  }
};

int main ()
{
  try
  {
    misc::task::worker worker1;
    foo f;

    std::shared_future<void> job1 (worker1 (throws));
    std::shared_future<int> job2 (worker1 (std::bind(add, 1, 2)));
    std::shared_future<int> job3 (worker1 (boost::bind(add, 1, 2)));

    std::shared_future<void> job4 (worker1 (boost::bind(&foo::bar, f)));
    std::shared_future<void> job5 (worker1 (std::bind(&foo::bar, f)));

    auto lambda_exp = [&]()->void { f.bar (); };
    //std::shared_future<void> job6 (worker1 (lambda_exp));

    try
    {
      job1.get ();
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error occured: " << e.what () << std::endl;
    }
    catch (const int& i)
    {
      std::cerr << "Has been thrown: " << i << std::endl;
    }

    std::cout << job2.get () << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error occured: " << e.what () << std::endl;
  }
}


