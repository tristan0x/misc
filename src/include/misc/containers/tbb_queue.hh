/// \file misc/containers/tbb_queue.hh
/// \brief Wrapper for intel threads building block
/// concurrent queue
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

#ifndef __MISC_CONTAINERS_QUEUE_HH__
# define __MISC_CONTAINERS_QUEUE_HH__

# include <tbb/concurrent_queue.h>

namespace misc {
namespace containers {

/// \brief Dummy queue interface using fast non-blocking TBB
template <class T>
class tbb_queue
{
public:
  typedef T element_type;

  /// \brief Push an element in the queue.
  void push (const element_type& e);

  /** \brief Attempt to dequeue an item
   *  Does not wait for an item to become available
   *  \return True if successful, false otherwise.
   */
  bool try_pop (element_type& e);

  /// \return true if the queue is empty, false otherwise.
  bool empty () const;

  /// \return number of pushes minus numbers of pops
  size_t size () const;

private:
  typedef tbb::concurrent_queue<element_type> queue_type;

  /// non-blocking queue
  queue_type queue_;
  /// \a queue_type::size() member variable is not thread safe
  mutable std::mutex mutex_;
};

} // namespace containers
} // namespace misc

# include <misc/containers/tbb_queue.hxx>

#endif // !__MISC_CONTAINERS_QUEUE_HH__
