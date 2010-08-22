/// \file misc/boost/valarray.hh
/// \brief Provides template specialization functions
/// to handle \a std::valarray with \a boost::serialization
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

#ifndef __MISC_BOOST_SERIALIZATION_VALARRAY_HH__
#define __MISC_BOOST_SERIALIZATION_VALARRAY_HH__

# include <valarray>

# include <boost/serialization/map.hpp>
# include <boost/serialization/set.hpp>

namespace boost {
namespace serialization {

template <class Archive, typename T>
inline void
load(Archive& archive, std::valarray<T>& object, unsigned int)
{
    unsigned int size = 0;
    archive & size;
    object.resize (size);
    for (unsigned int i = 0; i < object.size (); ++i)
      archive & object[i];
}



template <class Archive, typename T>
inline void
save(Archive& archive, const std::valarray<T>& object, unsigned int)
{
    size_t size = object.size ();
    archive & size;
    for (unsigned int i = 0; i < object.size (); ++i)
    {
        double v = object[i];
        archive & v;
    }
}



template <class Archive, typename T>
inline void
serialize(Archive& archive, std::valarray<T>& object, unsigned int file_version)
{
    boost::serialization::split_free (archive, object, file_version);
}

} // namespace serialization
} // namespace boost

#endif // __MISC_BOOST_SERIALIZATION_VALARRAY_HH__
