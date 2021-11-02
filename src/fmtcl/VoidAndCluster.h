/*****************************************************************************

        VoidAndCluster.h
        Author: Laurent de Soras, 2015

Reference:
Robert Ulichney,
The Void-And-Cluster Method for Dither Array Generation
Proc. SPIE, Human Vision, Visual Processing, and Digital Display IV,
vol. 1913, pp. 332-343, Feb. 1-4, 1993

*** TO DO: implement:
Hakan Ancin, Anoop K. Bhattacharjya, Joseph Shou-Pyng Shu,
New void-and-cluster method for improved halftone uniformity,
Journal of Electronic Imaging 8(1), January 1999,
https://doi.org/10.1117/1.482701 ***

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (fmtcl_VoidAndCluster_HEADER_INCLUDED)
#define	fmtcl_VoidAndCluster_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma warning (4 : 4250)
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtcl/MatrixWrap.h"

#include <cstdint>

#include <memory>
#include <vector>



namespace fmtcl
{



class VoidAndCluster
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	typedef uint16_t Rank; // May be signed or unsigned.

	               VoidAndCluster () = default;
	virtual			~VoidAndCluster () {}

	void           create_matrix (MatrixWrap <Rank> &vnc);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	static const int  KERNEL_MAX_RAD  = 4;
	static const int  KERNEL_DEF_SIZE = KERNEL_MAX_RAD * 2 + 1;

	class Coord
	{
	public:
		int            _x;
		int            _y;
	};

	typedef MatrixWrap <double> Kernel;
	static constexpr int64_t   _kscale = int64_t (1) << 32;

	void           homogenize_initial_mat (MatrixWrap <Rank> &m) const;
	void           find_cluster_kernel (std::vector <Coord> &pos_arr, const MatrixWrap <Rank> &m, int color, int kw, int kh) const;
	const Coord &  pick_one (std::vector <Coord> &pos_arr, uint32_t seed) const;

	static std::unique_ptr <Kernel>
	               create_gauss_kernel (int w, int h, double sigma);
	static void    generate_initial_mat (MatrixWrap <Rank> &m);
	static int     count_elt (const MatrixWrap <Rank> &m, int val);

	std::unique_ptr <Kernel>
	               _kernel_gauss_uptr;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               VoidAndCluster (const VoidAndCluster &other)    = delete;
	VoidAndCluster &
	               operator = (const VoidAndCluster &other)        = delete;
	bool           operator == (const VoidAndCluster &other) const = delete;
	bool           operator != (const VoidAndCluster &other) const = delete;

};	// class VoidAndCluster



}	// namespace fmtcl



//#include "fmtcl/VoidAndCluster.hpp"



#endif	// fmtcl_VoidAndCluster_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
