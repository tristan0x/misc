/// \file misc/traits/stdext.hh
/// \brief Extensions i.e template specializations
/// of some c++ standard library traits.
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

#ifndef __MISC_TRAITS_STDEXT_HH__
# define __MISC_TRAITS_STDEXT_HH__

# include <functional>

namespace std {

/** \brief Template specialization of \a std::result_of
 *  to support std::bind expression wrapping
 *  a function call.
 */
template <typename R, typename... Args>
struct result_of<_Bind<R (*(Args...))(Args...)> >
{
  typedef R type;
};



/** \brief Template specialization of \a std::result_of
 *  to support std::bind expression wrapping
 *  a member function call.
 */
template <typename R, class C, typename... Args>
struct result_of<_Bind<_Mem_fn<R (C::*)(Args...)>(C)> >
{
  typedef R type;
};



/** \brief Template specialization of \a std::result_of
 *  when return type of the function given in template parameter
 *  is void.
 *
 *  \remarks This is a workaround to prevent a declval of an expression
 *  returning void, which leads to a compilation error.
 *
 *  \fixme Make it work with all prototypes.
 */
template <>
struct result_of<void()>
{
  typedef void type;
};

} // namespace std

#endif // !__MISC_TRAITS_STDEXT_HH__
