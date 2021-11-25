/*****************************************************************************

        ContFirCustom.h
        Author: Akarin, 2011

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#if ! defined (fmtcl_ContFirCustom_HEADER_INCLUDED)
#define	fmtcl_ContFirCustom_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma once
	#pragma warning (4 : 4250)
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
#include <functional>

#include "fmtcl/ContFirInterface.h"



namespace fmtcl
{



class ContFirCustom
:	public ContFirInterface
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	explicit       ContFirCustom (const std::function<double(double)> &, double);
	virtual        ~ContFirCustom () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

	// ContFirInterface
	virtual double do_get_support () const;
	virtual double do_get_val (double x) const;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	std::function<double(double)> _kernel;
	double _support;


/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               ContFirCustom ();
	               ContFirCustom (const ContFirCustom &other);
	ContFirCustom & operator = (const ContFirCustom &other);
	bool           operator == (const ContFirCustom &other) const;
	bool           operator != (const ContFirCustom &other) const;

};	// class ContFirCustom



}	// namespace fmtcl



//#include "fmtcl/ContFirCustom.hpp"



#endif	// fmtcl_ContFirCustom_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
