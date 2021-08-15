/*****************************************************************************

        Transfer.h
        Author: Laurent de Soras, 2021

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://www.wtfpl.net/ for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (fmtcavs_Transfer_HEADER_INCLUDED)
#define fmtcavs_Transfer_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "avsutl/PlaneProcCbInterface.h"
#include "avsutl/PlaneProcessor.h"
#include "avsutl/VideoFilterBase.h"
#include "fmtcl/TransCurve.h"
#include "fmtcl/TransLut.h"

#include <array>



namespace fmtcavs
{



class Transfer
:	public avsutl::VideoFilterBase
,	public avsutl::PlaneProcCbInterface
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	typedef avsutl::VideoFilterBase Inherited;

	enum Param
	{
		Param_CLIP_SRC = 0, // 0
		Param_TRANSS,
		Param_TRANSD,
		Param_CONT,
		Param_GCOR,
		Param_BITS,
		Param_FLT,
		Param_FULLS,
		Param_FULLD,
		Param_LOGCEIS,
		Param_LOGCEID, // 10
		Param_CPUOPT,
		Param_BLACKLVL,
		Param_PLANES,

		Param_NBR_ELT,
	};

	explicit       Transfer (::IScriptEnvironment &env, const ::AVSValue &args);
	virtual        ~Transfer () = default;

	// VideoFilterBase
	::PVideoFrame __stdcall
						GetFrame (int n, ::IScriptEnvironment *env_ptr) override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

	// PlaneProcCbInterface
	void           do_process_plane (::PVideoFrame &dst_sptr, int n, ::IScriptEnvironment &env, int plane_index, int plane_id, void *ctx_ptr) override;

	static constexpr int _max_nbr_planes_proc = 3;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	FmtAvs         get_output_colorspace (::IScriptEnvironment &env, const ::AVSValue &args, const FmtAvs &fmt_src);

	::PClip        _clip_src_sptr;
	const ::VideoInfo
	               _vi_src;

	std::unique_ptr <avsutl::PlaneProcessor>
	               _plane_proc_uptr;

	std::unique_ptr <fmtcl::TransLut>
	               _lut_uptr;

	bool           _fulls_flag = true;
	bool           _fulld_flag = true;
	fmtcl::TransCurve
	               _curve_s    = fmtcl::TransCurve_INVALID;
	fmtcl::TransCurve
	               _curve_d    = fmtcl::TransCurve_INVALID;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               Transfer ()                               = delete;
	               Transfer (const Transfer &other)          = delete;
	               Transfer (Transfer &&other)               = delete;
	Transfer &     operator = (const Transfer &other)        = delete;
	Transfer &     operator = (Transfer &&other)             = delete;
	bool           operator == (const Transfer &other) const = delete;
	bool           operator != (const Transfer &other) const = delete;

}; // class Transfer



}  // namespace fmtcavs



//#include "fmtcavs/Transfer.hpp"



#endif   // fmtcavs_Transfer_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
