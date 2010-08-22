/// \file misc/task/worker.hh
//
// Started on  Sun Aug 15 13:39:21 2010 Tristan Carel
// Last update Tue Aug 17 22:57:25 2010 Tristan Carel
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

#ifndef   __MISC_TASK_WORKER_HH__
# define   __MISC_TASK_WORKER_HH__

# include <thread>
# include <mutex>
# include <condition_variable>
# include <future>

# include <functional>
# include <utility>

# include <vector>

# include <misc/containers/tbb_queue.hh>
# include <misc/traits/function.hh>

namespace misc {
namespace task {

/** \brief Asynchronous task runner
 */
class worker
{
public:
  /// threads pool is started in the constructor
  worker (size_t threads_count = 1);
  ~worker ();

  /// start threads pool
  void start_threads ();
  /// stop threads pool
  void stop_threads ();

  /** \brief execute a task asynchronously
   *  \param f the functor to run, can be anything whose returned type
   *  can be identified by \a std::result_of
   *  \returns get a std::future instance to get task intel
   *  (exception, return value)
   */
  template <typename TaskFunctor>
  std::shared_future<typename misc::traits::function<TaskFunctor>::return_type>
  operator() (TaskFunctor f);

private:
  /// Internal task type
  typedef std::function<void (void)> task_type;
  /// Internal task queue type
  typedef containers::tbb_queue<task_type> tasks_queue_type;
  /// Internal thread type
  typedef std::unique_ptr<std::thread> thread_ptr;

  /// creates std::promise instance and returns associated std::future.
  /// register task internaly
  template <typename ResultType>
  std::shared_future<ResultType> run (std::function<ResultType (void)> f);

  /// queue task in internal container
  void push (task_type f);

  /// Thread loop
  void process ();

  tasks_queue_type pending_tasks_;
  std::mutex mutex_;
  std::condition_variable control_;
  const size_t threads_count_;
  std::vector<thread_ptr> working_threads_;
  volatile bool terminated_;
};

} // namespace task
} // namespace misc

# include <misc/task/worker.hxx>

#endif // ndef __MISC_TASK_WORKER_HH__
