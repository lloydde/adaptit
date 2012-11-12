/////////////////////////////////////////////////////////////////////////////
/// \project		adaptit
/// \file			Uuid_AI.cpp
/// \author			Bruce Waters
/// \date_created	5 May 2010
/// \rcs_id $Id$
/// \copyright		2010 Bruce Waters, Bill Martin, SIL International
/// \license		The Common Public License or The GNU Lesser General Public License (see license directory)
/// \description	This is the implementation file for UUID generation within Adapt It.
///                 The Windows and Mac ports use open source third party tools 
///                 provided by the Boost software library. The Linux port uses
///                 UUID code packaged with all Ubuntu distros supported by
///                 Adapt It.
///                                 
///   Boost Software License - Version 1.0 - August 17th, 2003
///   
///   Permission is hereby granted, free of charge, to any person or organization
///   obtaining a copy of the software and accompanying documentation covered by
///   this license (the "Software") to use, reproduce, display, distribute,
///   execute, and transmit the Software, and to prepare derivative works of the
///   Software, and to permit third-parties to whom the Software is furnished to
///   do so, all subject to the following:
///   
///   The copyright notices in the Software and this entire statement, including
///   the above license grant, this restriction and the following disclaimer,
///   must be included in all copies of the Software, in whole or in part, and
///   all derivative works of the Software, unless such copies or derivative
///   works are solely in the form of machine-executable object code generated by
///   a source language processor.
///   
///   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
///   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
///   FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
///   SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
///   FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
///   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
///   DEALINGS IN THE SOFTWARE.
///                 
/////////////////////////////////////////////////////////////////////////////

// the following improves GCC compilation performance
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma implementation "Uuid_AI.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif

#ifndef __WXGTK__
// for Windows and Mac
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include <string>
#else
// for Linux
#include <uuid/uuid.h>
#endif

#include "Uuid_AI.h"

IMPLEMENT_DYNAMIC_CLASS(Uuid_AI, wxObject)

Uuid_AI::Uuid_AI()
{
	// construct the UUID here...
#ifndef __WXGTK__
	//for convenience boost::uuids::random_generator
	//is equivalent to boost::uuids::basic_random_generator<boost::mt19937>
	boost::uuids::random_generator gen;
	u = gen(); // set private uuid member
#endif	
}

Uuid_AI::~Uuid_AI(){}

wxString Uuid_AI::GetUUID()
{
	// return the string representation
#ifndef __WXGTK__
	std::stringstream ss;
	// Windows and Mac version using Boost
	using namespace boost;
	using namespace uuids;
	ss << u; // this needed #include <sstream> to compile it
#ifdef _UNICODE
	wxString uuidStr;
	uuidStr = uuidStr.FromUTF8((ss.str()).c_str());
	uuidStr = uuidStr.Upper();
	return uuidStr;
#else
	// ANSI
	wxString uuidStr;
	uuidStr = (ss.str()).c_str();
	uuidStr = uuidStr.Upper();
	return uuidStr;
#endif
#else
	// linux version uses OSSP UUID that is standard and included
	// in all Ubuntu distros since at least Hardy
	wxString uuidStr;
	uuid_t uu;
	char uus[37];
	uuid_generate(uu);
	uuid_unparse(uu, uus);
	uuidStr = uuidStr.FromUTF8((const char*) uus);
	return uuidStr;
#endif
}
