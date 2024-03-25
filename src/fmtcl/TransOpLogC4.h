/*****************************************************************************

        TransOpLogC4.h
        Author: Laurent de Soras, 2023

Source:
Arri LogC4 - Logarithmic Color Space - Specification - 2023-05-12
https://www.arri.com/resource/blob/278790/bea879ac0d041a925bed27a096ab3ec2/2022-05-arri-logc4-specification-data.pdf

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (fmtcl_TransOpLogC4_HEADER_INCLUDED)
#define	fmtcl_TransOpLogC4_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtcl/TransOpInterface.h"

#include <array>



namespace fmtcl
{



class TransOpLogC4
:	public TransOpInterface
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	explicit       TransOpLogC4 (bool inv_flag);
	virtual        ~TransOpLogC4 () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

	// TransOpInterface
	double         do_convert (double x) const override;
	LinInfo        do_get_info () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	double         compute_direct (double x) const;
	double         compute_inverse (double x) const;

	const bool     _inv_flag;

	static constexpr double _a = (double (1 << 18) - 16.0) / 117.45;
	static constexpr double _b = (1023.0 - 95.0) / 1023.0;
	static constexpr double _c =           95.0  / 1023.0;
	static const double _s;
	static const double _t;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               TransOpLogC4 ()                               = delete;
	               TransOpLogC4 (const TransOpLogC4 &other)      = delete;
	TransOpLogC4 & operator = (const TransOpLogC4 &other)        = delete;
	bool           operator == (const TransOpLogC4 &other) const = delete;
	bool           operator != (const TransOpLogC4 &other) const = delete;

};	// class TransOpLogC4



}	// namespace fmtcl



//#include "fmtcl/TransOpLogC4.hpp"



#endif	// fmtcl_TransOpLogC4_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
