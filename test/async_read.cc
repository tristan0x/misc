// File    async_read.cc
// Made by Tristan Carel
// Mail    <tristan.carel@gmail.com>
//
// Started on  Wed Aug 18 22:35:27 2010 Tristan Carel
// Last update Wed Aug 18 23:33:52 2010 Tristan Carel
//

#include <fstream>
#include <valarray>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <iostream>

#include <misc/io/async_read.hh>
#include <misc/stlext/pprint.hh>

#define FILE_SIZE 1024 * 1024 * 20
#define ASYNC_BLOCK_SIZE 1024

int main ()
{
  std::cout << "generating " << misc::stlext::humanize_number (FILE_SIZE)
            << " random file" << std::endl;
  std::srand (getpid ());
  std::vector<char> buffer1 (FILE_SIZE);
  std::vector<char> buffer2 (FILE_SIZE);
  std::generate (buffer1.begin (), buffer1.end (), rand);

  {
    std::ofstream outfile ("file.in", std::ios::out | std::ios::binary);
    outfile.write (&buffer1[0], FILE_SIZE);
  }

  {
    std::cout << "reading it with misc::async_read instance" << std::endl;
    std::ifstream infile ("file.in", std::ios::in | std::ios::binary);
    std::vector<char> block_buffer (ASYNC_BLOCK_SIZE);
    auto ite = buffer2.begin ();
    misc::async_read reader (infile, ASYNC_BLOCK_SIZE);
    while (reader.get (block_buffer))
      std::for_each (block_buffer.begin (), block_buffer.end (),
                     [&] (char c) { *ite++ = c; });
  }

  return (buffer1 == buffer2? EXIT_SUCCESS: EXIT_FAILURE);
}


