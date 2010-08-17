/// \file misc/stlext/pprint.hh
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

#ifndef __MISC_STLEXT_PPRINT_HH_
# define __MISC_STLEXT_PPRINT_HH_

# include <string>

# include <boost/numeric/conversion/converter.hpp>
# include <boost/format.hpp>

namespace misc {
namespace stlext {

template <class Int>
std::string humanize_number(const Int& i, const char* unit = "")
{
  size_t stage = 0;

	// allez hop, on est anal sur la conversion vers le double...
	boost::numeric::converter<double, Int> IntToDouble;
	double val = IntToDouble(i);

	while (val >= 1024.0)
	{
		val /= 1024.0;
		stage++;
	}

	// on affiche 2 chiffres après la virgule
	std::ostringstream output;
	output << boost::format("%1$4.2f") % val;

	switch (stage)
	{

	case 1:
		// Kilo
		output << " k";
		break;

	case 2:
		// Mega
		output << " M";
		break;

	case 3:
		// Giga
		output << " G";
		break;

	case 4:
		// Teta
		output << " T";
		break;

	case 5:
		// Peta
		output << " P";
		break;

	case 6:
		// Exa !!1!!!
		output << " E";
		break;

	}

	// on rajoute l'unité le cas échéant
	if (unit)
	{
		// on sait jamais si quelqu'un nous passe NULL...
		output << unit;
	}

	return output.str();


} // namespace stlext
} // namespace misc

#endif // !__MISC_STLEXT_PPRINT_HH_
