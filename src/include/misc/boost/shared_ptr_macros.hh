/// \file misc/boost/shared_ptr_macros.hh
//
// Started on  Sun Aug 15 13:39:21 2010 Tristan Carel
// Last update Mon Aug 16 23:51:03 2010 Tristan Carel
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

#ifndef __MISC_BOOST_SHARED_PTR_MACROS_HH__
# define __MISC_BOOST_SHARED_PTR_MACROS_HH__

# include <boost/weak_ptr.hpp>
# include <boost/shared_ptr.hpp>

/**
 *  \brief Declare all Boost ptr from an existing class.
 */
#define ADD_SHARED_PTR(Class)                             \
  typedef boost::shared_ptr<Class> Class##Ptr;            \
  typedef boost::weak_ptr<Class> Class##WeakPtr;          \
  typedef boost::weak_ptr<Class> Class##ConstWeakPtr;     \
  typedef boost::shared_ptr<Class const> Class##ConstPtr


/**
 *  \brief Add forward declaration of a class and all
 *  associated ptr types.
 */
#define FORWARD_DECLARE(Class)                  \
class Class;                                    \
ADD_SHARED_PTR(Class)


/**
 *  \brief Same than \a FORWARD_DECLARE but for a struct
 */
#define FORWARD_DECLARE_AS_STRUCT(Struct)       \
struct Struct;                                  \
ADD_SHARED_PTR(Struct)


/**
 *  \brief Import class from another namespace
 */
#define USING_DIRECTIVE_WITH_SHARED_PTR(Class)	\
using Class;                                    \
using Class##Ptr;                               \
using Class##WeakPtr;                           \
using Class##ConstWeakPtr;                      \
using Class##ConstPtr


#endif // !__MISC_BOOST_SHARED_PTR_MACROS_HH__
