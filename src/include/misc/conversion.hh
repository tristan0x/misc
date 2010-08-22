/// \file misc/conversion.hh
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

#ifndef __MISC_CONVERSION_HH__
# define __MISC_CONVERSION_HH__

# include <stdexcept>

# include <boost/lexical_cast.hpp>
# include <boost/numeric/conversion/converter.hpp>

namespace misc {

  /** Safe lexical conversion of input i.e string -> obj or obj -> string
   *  \param[in] input Object to convert
   *  \param[out] output Reference where conversion is written
   *  \return true if the conversion is successful, false otherwise
   */
  template <typename Input, typename Output>
  bool safe_lexical_conversion(const Input& input, Output& output)
  {
    bool success = true;

    try
    {
       output = boost::lexical_cast<Output> (input);
    }
    catch (const boost::bad_lexical_cast&)
    {
       success = false;
    }

    return success;
  }


   /** Perform a safe conversion between 2 numeric types.
    *
    *  \param[in] input The numeric value to convert
    *  \param[out] output Reference where result is written
    *  \return true if the conversion is successful, false otherwise
    *  (range error, round error)
    */
   template <typename Input, typename Output>
   bool safe_numeric_conversion(const Input& input, Output& output)
   {
      bool success = true;

      boost::numeric::converter<Output, Input> numericConverter;
      try
      {
         output = numericConverter (input);
      }
      catch (const std::exception&)
      {
         success = false;
      }
      return success;
   }

} // namespace misc

#endif // !__MISC_CONVERSION_HH__
