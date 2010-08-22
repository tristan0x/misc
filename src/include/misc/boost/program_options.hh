/// \file misc/boost/program_options.hh
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

#ifndef __MISC_BOOST_PROGRAM_OPTION_HH_
# define __MISC_BOOST_PROGRAM_OPTION_HH_

# include <boost/program_options/cmdline.hpp>
# include <boost/program_options/parsers.hpp>
# include <boost/program_options/variables_map.hpp>

namespace misc {
namespace boost {

/**
 *  \brief Parse process command line using \a boost::program_options
 */
inline
void
parse (const boost::program_options::options_description& options,
       int& argc, char* argv[]. boost::program_options::variables_map& vm)
{
  boost::program_options::parsed_options parsed = 
    boost::program_options::command_line_parser (argc, argv)
    .options (options)
    .allow_unregistered ().run ();

  store (parsed, vm);
  notify (vm);
}

} // namespace boost
} // namespace misc
