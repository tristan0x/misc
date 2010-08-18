/// \file misc/io/async_read.hh
//
// Started on  Tue Aug 17 22:59:43 2010 Tristan Carel
// Last update Wed Aug 18 23:26:44 2010 Tristan Carel
//
// Copyright 2010  Tristan Carel <tristan.carel@gmail.com>
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#ifndef   __MISC_IO_ASYNC_READ_HH__
# define   __MISC_IO_ASYNC_READ_HH__

# include <fstream>
# include <vector>

# include <misc/task/worker.hh>


namespace misc {

struct async_read
{
  typedef std::vector<char> buffer_type;

  inline
  async_read (std::ifstream& stream, long block_size = 4096,
              size_t max_pending_buffers = 10);
  virtual ~async_read ();

  /**
   *  \brief Read a block in the stream
   *  \return true if eof is reached, false otherwise
   */
  inline
  bool get (buffer_type& buffer);
  inline
  bool eof () const;

private:
  void block_reader ();

  std::ifstream& stream_;
  const long block_size_;
  containers::tbb_queue<buffer_type> pending_blocks_;
  std::mutex mutex_;
  std::condition_variable control_;
  const size_t max_pending_buffers_;
  std::thread reader_;
};

} // namespace misc

# include <misc/io/async_read.hxx>

#endif // ndef __MISC_IO_ASYNC_READ_HH__
