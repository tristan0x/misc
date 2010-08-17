/// \file misc/stlext/iterator.hh
/// \brief STL extensions
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

#ifndef __CPP_UTILS_STLEXT_ITERATOR_HH__
# define __CPP_UTILS_STLEXT_ITERATOR_HH__

# include <type_traits>

# include <boost/function_output_iterator.hpp>

namespace misc {
namespace stlext {

  /** \brief Act like \a std::back_inserter but with an extra predicate
   *  that must be true to insert the data in the output container.
   *
   *  Ex: you want to run a functor on vector's elements and don't
   *      want to keep the result if it's null
   *
   *  \code
   *  class Data;
   *  class Functor;
   *
   *  std::vector<Data> v;
   *  std::vector<Functor::result_type> res;
   *  // [...]
   *  Functor f;
   *  std::transform (v.begin (), v.end (),
   *                  stlext::back_inserter_if
   *                    (res, boost::lambda::_1 != NULL), f);
   *  \endcode
   *
   *  Only results different than NULL are inserted in the vector res;
   */

  template <typename _Container, typename _Predicate>
  class back_inserter_if_function
  {
  public:
    typedef typename std::add_reference<_Container>::type container_reference;
    back_inserter_if_function (container_reference container,
                               _Predicate predicate)
      : container_ (container),
        predicate_ (predicate)
    { }

    void operator() (typename _Container::const_reference element)
    {
      if (predicate_ (element))
        container_.push_back (element);
    }

  private:
    container_reference container_;
    _Predicate predicate_;
  };



  /** \brief Helper function to create a back_inserter_if output iterator
   *  \param[out] container Container where results are back_inserted.
   *  \param[in] predicate A unary functor
   */
  template <typename _Container, typename _UnaryFunctor>
  boost::function_output_iterator
  <
    back_inserter_if_function<_Container, _UnaryFunctor>
  >
  back_inserter_if (_Container & container, _UnaryFunctor predicate)
  {
    return boost::make_function_output_iterator
      (back_inserter_if_function<_Container, _UnaryFunctor>
       (container, predicate));
  }

} // namespace stlext
} // namespace misc

#endif // !__CPP_UTILS_STLEXT_ITERATOR_HH__
