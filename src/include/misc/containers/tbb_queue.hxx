/// \file misc/containers/tbb_queue.hxx
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

#ifndef __MISC_CONTAINERS_QUEUE_HXX__
# define __MISC_CONTAINERS_QUEUE_HXX__

# include <misc/containers/tbb_queue.hh>

namespace misc {
namespace containers {

template <class T>
void tbb_queue<T>::push (const element_type& e)
{
  queue_.push (e);
}



template <class T>
bool tbb_queue<T>::try_pop (element_type& e)
{
  return queue_.try_pop (e);
}



template <class T>
size_t tbb_queue<T>::size () const
{
  std::unique_lock<std::mutex> l (mutex_);
  return queue_.unsafe_size ();
}



template <class T>
bool tbb_queue<T>::empty () const
{
  return queue_.empty ();
}

} // namespace containers
} // namespace misc

#endif // !__MISC_CONTAINERS_QUEUE_HXX__
