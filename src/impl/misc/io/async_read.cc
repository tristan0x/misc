/// \file src/impl/async_read.cc
//
// Started on  Sun Aug 22 12:31:31 2010 Tristan Carel
// Last update Sun Aug 22 12:38:46 2010 Tristan Carel
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

#include <misc/io/async_read.hh>

namespace misc {

/*--------------.
| Ctors & Dtors |
`--------------*/

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



/*------------------------.
| Public member functions |
`------------------------*/

bool async_read::get (buffer_type& buffer)
{
  {
    std::unique_lock<std::mutex> lock (mutex_);
    control_.wait (lock, [&] { return !pending_blocks_.empty () || eof (); });
  }

  if (!pending_blocks_.empty ())
  {
#if 0
    buffer_type result;
    pending_blocks_.pop (result);

    // prevent a full buffer copy, thank you rvalues !
    std::swap (buffer, *result);
#endif // 0

    pending_blocks_.try_pop (buffer);

    control_.notify_all ();
  }

  return !terminated ();
}



void async_read::reuse (const buffer_type& buffer)
{
  usable_blocks_.push (buffer);
}




bool async_read::terminated () const
{
  return pending_blocks_.empty () && eof ();
}



/*-------------------------.
| Private member functions |
`-------------------------*/

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
                       return !usable_blocks_.empty () ||
                         pending_blocks_.size () < max_pending_buffers_;
                     });
    }

    buffer_type buffer;
    if (!usable_blocks_.empty ())
      usable_blocks_.try_pop (buffer);
    else
    {
      buffer.reset (new buffer_type::element_type (block_size_));
    }

    stream_.read (&(*buffer)[0], block_size_);

    // resize last buffer to number of bytes read.
    if (eof ())
      buffer->resize (stream_.gcount ());

    pending_blocks_.push (buffer);
    control_.notify_all ();
  }
  while (!eof ());
}

} // namespace misc
