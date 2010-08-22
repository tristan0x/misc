// File    async_read.cc
// Made by Tristan Carel
// Mail    <tristan.carel@gmail.com>
//
// Started on  Wed Aug 18 22:35:27 2010 Tristan Carel
// Last update Sat Aug 21 12:02:19 2010 Tristan Carel
//

#include <fstream>
#include <valarray>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <iostream>

#include <misc/io/async_read.hh>
#include <misc/stlext/pprint.hh>

#include <boost/timer.hpp>

#define FILE_SIZE 1024 * 1024 * 20
#define ASYNC_BLOCK_SIZE 1024

/**
 *  \brief Generate a random 20M file.
 *  read it with async_read and ensure content read is
 *  the same than the one written.
 */
bool check_validity ()
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
    auto ite = buffer2.begin ();
    misc::async_read reader (infile, ASYNC_BLOCK_SIZE);
    misc::async_read::buffer_type block_buffer;
    while (reader.get (block_buffer))
    {
      std::for_each (block_buffer->begin (), block_buffer->end (),
                     [&] (char c) { *ite++ = c; });
      reader.reuse (block_buffer);
    }
  }

  return buffer1 == buffer2;
}

void do_stuff (std::vector<char>& buffer)
{
//  std::cout << "  doing stuff..." << std::endl;
  usleep (500 * 1000);
}

bool evaluate_performance ()
{
  double sync_wait_duration = 0;
  double long async_wait_duration = 0;
  std::vector<char> buffer (1024 * 1024);
  {
    std::cout << "Reading file synchronously" << std::endl;
    std::ifstream infile ("file.in",  std::ios::in | std::ios::binary);
    do
    {
      boost::timer duration;
      infile.read (&buffer[0], 1024 * 1024);
      sync_wait_duration += duration.elapsed ();
      do_stuff (buffer);
    }
    while (!(infile.eof () && infile.fail ()));
  }

  {
    std::cout << "Reading file asynchronously" << std::endl;
    std::ifstream infile ("file.in", std::ios::in | std::ios::binary);
    misc::async_read reader (infile, 1024 * 1024);
    misc::async_read::buffer_type buffer;
    do
    {
      boost::timer duration;
      reader.get (buffer);
      async_wait_duration += duration.elapsed ();
      do_stuff (*buffer);
      reader.reuse (buffer);
    }
    while (!reader.terminated ());
  }

  std::cout << "Sync time wait : " << sync_wait_duration << std::endl
            << "Async time wait: " << async_wait_duration << std::endl;
  return true;
}

int main ()
{
  return (check_validity ()
          && evaluate_performance ()) ? EXIT_SUCCESS : EXIT_FAILURE;
}


