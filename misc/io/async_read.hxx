/// \file misc/io/async_read.hxx
//
// Started on  Wed Aug 18 22:20:25 2010 Tristan Carel
// Last update Wed Aug 18 23:27:22 2010 Tristan Carel
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

#ifndef   __MISC_IO_ASYNC_READ_HXX__
# define   __MISC_IO_ASYNC_READ_HXX__

namespace misc {

async_read::async_read (std::ifstream& stream, long block_size /* = 4096 */,
                        size_t max_pending_buffers /* = 10 */ )
: stream_ (stream),
  block_size_ (block_size),
  max_pending_buffers_ (max_pending_buffers),
  reader_ (std::bind (&async_read::block_reader, this))
{
};

async_read::~async_read ()
{
  reader_.join ();
}

bool async_read::get (std::vector<char>& buffer)
{
  {
    std::unique_lock<std::mutex> lock (mutex_);
    control_.wait (lock, [&] { return !pending_blocks_.empty () || eof (); });
  }

  if (!pending_blocks_.empty ())
  {
    pending_blocks_.pop (buffer);
    control_.notify_all ();
  }

  return !(pending_blocks_.empty () && eof ());
}

bool async_read::eof () const
{
  return stream_.eof () && stream_.fail ();
}

void async_read::block_reader ()
{
  do
  {
    {
      std::unique_lock<std::mutex> lock (mutex_);
      control_.wait (lock,
                     [&]
                     {
                       return pending_blocks_.size () < max_pending_buffers_;
                     });
    }

    buffer_type buffer (block_size_);
    stream_.read (&buffer[0], block_size_);
    pending_blocks_.push (buffer);
    control_.notify_all ();
  }
  while (!eof ());
}

} // namespace misc

#endif // !__MISC_IO_ASYNC_READ_HXX__
