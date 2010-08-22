/// \file misc/boost/serialization/tuple.hh
/// \brief Provides template specialization functions to handle
/// \a boost::tuple with \a boost::serialization
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

#ifndef __MISC_BOOST_SERIALIZATION_TUPLE_HH__
#define __MISC_BOOST_SERIALIZATION_TUPLE_HH__

# include <boost/tuple/tuple.hpp>
# include <boost/tuple/tuple_comparison.hpp>

namespace boost {
namespace serialization {

// simple
template<class Archive, class FIRST>
inline void serialize( Archive & ar
                     , boost::tuple< FIRST >& t
                     , const unsigned int /* file_version */
)
{
  ar & boost::serialization::make_nvp("first", t.get<0>()   );
}

// double
template<class Archive, class FIRST, class SECOND>
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , t.get<0>()  );
   ar & boost::serialization::make_nvp("second", t.get<1>()  );
}

// triple
template<class Archive, class FIRST, class SECOND, class THIRD>
inline void serialize( Archive & ar
                     , boost::tuple<FIRST, SECOND, THIRD>& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , t.get<0>()  );
   ar & boost::serialization::make_nvp("second", t.get<1>()  );
   ar & boost::serialization::make_nvp("third" , t.get<2>()  );
}


// quadruple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , t.get<0>()  );
   ar & boost::serialization::make_nvp("second", t.get<1>()  );
   ar & boost::serialization::make_nvp("third" , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth", t.get<3>()  );
}

// quintuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
}

// sextuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
}

// septuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
}

// octet
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH, EIGHT
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
   ar & boost::serialization::make_nvp("eighth"  , t.get<7>()  );
}

// 9-tuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT, class NINE
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH, EIGHT, NINE
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
   ar & boost::serialization::make_nvp("eighth"  , t.get<7>()  );
   ar & boost::serialization::make_nvp("ninth"   , t.get<8>()  );
}

// 10-tuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT, class NINE, class TEN
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH, EIGHT
                                   , NINE, TEN
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
   ar & boost::serialization::make_nvp("eighth"  , t.get<7>()  );
   ar & boost::serialization::make_nvp("ninth"   , t.get<8>()  );
   ar & boost::serialization::make_nvp("tenth"   , t.get<9>()  );
}

} // namespace serialization
} // namespace boost

#endif // __MISC_BOOST_SERIALIZATION_TUPLE_HH__
