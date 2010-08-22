// \file misc/task/worker.cc
//
// Started on  Sun Aug 22 23:42:54 2010 Tristan Carel
// Last update Sun Aug 22 23:43:38 2010 Tristan Carel
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

#ifndef   __MISC_TASK_WORKER_HXX__
# define   __MISC_TASK_WORKER_HXX__

# include <misc/task/worker.hh>
# include <misc/task/runner.hh>

namespace misc {
namespace task {

/*--------------.
| Ctors & Dtors |
`--------------*/

  worker::worker (size_t threads_count /* = 1*/)
    : threads_count_ (threads_count),
      terminated_ (true)
  {
    start_threads ();
  }



  worker::~worker ()
  {
    stop_threads ();
  }



  void worker::start_threads ()
  {
    std::lock_guard<std::mutex> lock (mutex_);

    if (!terminated_)
      throw std::runtime_error ("worker threads already running");

    for (size_t i = 0; i < threads_count_; ++i)
      working_threads_.push_back
        (thread_ptr (new std::thread ([&] { this->process (); })));
    terminated_ = false;
  }



  void worker::stop_threads ()
  {
    if (terminated_)
      throw std::runtime_error ("worker threads already terminated");

    push ([&]
           {
             std::lock_guard<std::mutex> lock (mutex_);
             terminated_ = true;
             control_.notify_all ();
           });

    for (auto thread = working_threads_.begin ();
         thread != working_threads_.end (); ++thread)
      (*thread)->join ();
  }



  /*----------------.
  | private methods |
  `----------------*/

  void worker::push (task_type f)
  {
    pending_tasks_.push (f);
    control_.notify_all ();
  }



  void worker::process ()
  {
    task_type task;
    auto wait_condition = [&] { return !pending_tasks_.empty () || terminated_; };

    do
      {
        {
          std::unique_lock<std::mutex> lock (mutex_);
          control_.wait (lock, wait_condition);
        }

        if (!terminated_ && !pending_tasks_.empty ())
        {
          pending_tasks_.try_pop (task);
          task ();
        }
      }
    while (!terminated_);
  }

} // namespace task
} // namespace misc

#endif // ndef __MISC_TASK_WORKER_HXX__
