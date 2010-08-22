// \file misc/task/runner.hh
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

#ifndef   __MISC_TASK_RUNNER_HH__
# define   __MISC_TASK_RUNNER_HH__

# include <utility>
# include <functional>
# include <future>

namespace misc {
namespace task {

  /**
   *  \brief Execute a functor and store result
   *  and exception status in a \a std::promise element
   */
  template <typename ResultType>
  struct runner
  {
    typedef std::shared_ptr<std::promise<ResultType> > promise_type;
    typedef std::function<ResultType (void)> function_type;

    runner (const promise_type& promise, function_type f)
      : promise_ (promise),
        f_ (f)
    {
    }

    void operator() ()
    {
      try
      {
        promise_->set_value (f_ ());
      }
      catch (...)
      {
        promise_->set_exception (std::current_exception ());
      }
    }
  private:
    promise_type promise_;
    function_type f_;
  };



  /**
   *  \brief Template specialization when the functor
   *  return type is void.
   */
  template <>
  struct runner<void>
  {
    typedef std::shared_ptr<std::promise<void> > promise_type;
    typedef std::function<void (void)> function_type;

    runner (const promise_type& promise, function_type f)
      : promise_ (promise),
        f_ (f)
    {
    }

    void operator () ()
    {
      try
      {
        f_ ();
      }
      catch (...)
      {
        promise_->set_exception (std::current_exception ());
      }
    }
  private:
    promise_type promise_;
    function_type f_;
  };

} // namespace task
} // namespace misc

#endif // ndef __MISC_TASK_RUNNER_HH__
