// \file misc/task/worker.hxx
//
// Started on  Sun Aug 15 14:05:31 2010 Tristan Carel
// Last update Sun Aug 22 23:45:31 2010 Tristan Carel
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

/*------------------------.
| Public member functions |
`------------------------*/

template <typename TaskFunctor>
std::shared_future<typename misc::traits::function<TaskFunctor>::return_type>
worker::operator() (TaskFunctor f)
{
  return run<typename misc::traits::function<TaskFunctor>::return_type> (f);
}



/*-------------------------.
| Private member functions |
`-------------------------*/

template <typename ResultType>
std::shared_future<ResultType>
worker::run (std::function<ResultType (void)> f)
{
  auto promise = std::make_shared<std::promise<ResultType> > ();
  std::shared_future<ResultType> result = promise->get_future ();

  this->push (runner<ResultType> (promise, f));
  return result;
}

} // namespace task
} // namespace misc

#endif // ndef __MISC_TASK_WORKER_HXX__
