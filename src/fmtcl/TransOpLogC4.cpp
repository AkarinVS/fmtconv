/*****************************************************************************

        TransOpLogC4.cpp
        Author: Laurent de Soras, 2023

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtcl/TransOpLogC4.h"
#include "fstb/def.h"

#include <cmath>



namespace fmtcl
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



TransOpLogC4::TransOpLogC4 (bool inv_flag)
:	_inv_flag (inv_flag)
{
	// Nothing
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



double	TransOpLogC4::do_convert (double x) const
{
	return (_inv_flag) ? compute_inverse (x) : compute_direct (x);
}



TransOpInterface::LinInfo	TransOpLogC4::do_get_info () const
{
	return { Type::OETF, Range::UNDEF, compute_inverse (1.0), 1.0, 0.0, 0.0 };
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



double	TransOpLogC4::compute_direct (double x) const
{
	const auto     y =
		  (x < _t)
		? (x - _t) / _s
		: (log2 (_a * x + 64) - 6) * _b / 14 + _c;

	return y;
}

double	TransOpLogC4::compute_inverse (double x) const
{
	const auto     y =
		  (x < 0)
		? x * _s + _t
		: (exp2 ((x - _c) * 14 / _b + 6) - 64) / _a;

	return y;
}



constexpr double	TransOpLogC4::_a;
constexpr double	TransOpLogC4::_b;
constexpr double	TransOpLogC4::_c;
const double	TransOpLogC4::_s = (7 * fstb::LN2 * exp2 (7 - 14 * _c / _b)) / (_a * _b);
const double	TransOpLogC4::_t = (exp2 (-14 * _c / _b + 6) - 64) / _a;



}	// namespace fmtcl



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
