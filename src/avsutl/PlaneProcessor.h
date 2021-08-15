/*****************************************************************************

        PlaneProcessor.h
        Author: Laurent de Soras, 2021

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://www.wtfpl.net/ for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (avsutl_PlaneProcessor_HEADER_INCLUDED)
#define avsutl_PlaneProcessor_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "avsutl/CsPlane.h"
#include "avsutl/PlaneProcMode.h"
#include "fstb/fnc.h"
#include "avisynth.h"

#include <array>
#include <string>

#include <cstdint>



namespace avsutl
{



class PlaneProcCbInterface;

class PlaneProcessor
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	static constexpr int _max_nbr_planes = CsPlane::_max_nbr_planes;

	enum ClipIdx
	{
		ClipIdx_INVALID = -1,

		ClipIdx_DST     = 0,
		ClipIdx_SRC1,
		ClipIdx_SRC2,
		ClipIdx_SRC3,

		ClipIdx_NBR_ELT
	};

	enum ClipType
	{
		ClipType_UNKNOWN = -1,

		ClipType_NORMAL = 0,
		ClipType_STACKED_16,
		ClipType_INTERLEAVED_16,
		ClipType_MSB,
		ClipType_LSB,

		ClipType_NBR_ELT
	};

	enum FmtChkFlag
	{
		FmtChkFlag_CS_TYPE    = 1 <<  0, // RGB/YUV
		FmtChkFlag_CS_LAYOUT  = 1 <<  1, // Planar/interleaved
		FmtChkFlag_CS_SUBSPL  = 1 <<  2, // Chroma subsampling
		FmtChkFlag_CS_FORMAT  = 1 <<  3, // Data format and bitdepth
		FmtChkFlag_CS_NBRCOMP = 1 <<  4, // Number of components (planar or not)

		FmtChkFlag_CS_ALL     = (1 << 8) - 1,

		FmtChkFlag_W          = 1 <<  8,
		FmtChkFlag_H          = 1 <<  9,
		FmtChkFlag_NBR_FRAMES = 1 << 10,

		FmtChkFlag_ALL        = -1
	};

	explicit       PlaneProcessor (const ::VideoInfo &vi, PlaneProcCbInterface &cb, bool manual_flag);
	virtual        ~PlaneProcessor () = default;

	void           set_proc_mode (const std::array <double, _max_nbr_planes> &pm_arr);
	void           set_proc_mode (std::string pmode);
	void           set_proc_mode (int plane_index, double mode);
	double         get_proc_mode (int plane_index) const noexcept;

	void           set_dst_clip_info (ClipType type);
	void           set_clip_info (ClipIdx index, ::PClip clip_sptr, ClipType type);

	int            get_nbr_planes () const;

	void           process_frame (::PVideoFrame &dst_sptr, int n, ::IScriptEnvironment &env, void *ctx_ptr);
	const ::VideoInfo &
	               use_vi (ClipIdx index) const;
	int            get_plane_id (int plane_index, ClipIdx index) const;
	int            get_width (const ::PVideoFrame &frame_sptr, int plane_id, ClipIdx clip_idx) const;
	int            get_height (const ::PVideoFrame &frame_sptr, int plane_id) const;
	int            get_height16 (const ::PVideoFrame &frame_sptr, int plane_id) const;

	// For manual operations
	bool           is_manual () const;
	PlaneProcMode  get_mode (int plane_index) const;
	double         get_fill_val (int plane_index) const;
	void           fill_plane (::PVideoFrame &dst_sptr, int n, double val, int plane_index);
	void           copy_plane (::PVideoFrame &dst_sptr, ClipIdx clip_idx, int n, int plane_index, ::IScriptEnvironment &env);

	static int     get_nbr_planes (const ::VideoInfo &vi);
	static int     get_bytes_per_component (const ::VideoInfo &vi);
	static int     get_min_w (const ::VideoInfo &vi);
	static int     get_min_h (const ::VideoInfo &vi, bool stack16_flag);
	static int     compute_plane_w (const ::VideoInfo &vi, int plane_index, int w);
	static int     compute_plane_h (const ::VideoInfo &vi, int plane_index, int h);
	static void    check_same_format (::IScriptEnvironment *env_ptr, const ::VideoInfo &vi, const ::PClip tst_sptr, const char *fnc_name_0, const char *arg_name_0, int flags = FmtChkFlag_ALL);
	static bool    check_stack16_width (const ::VideoInfo &vi, int width = -1);
	static bool    check_stack16_height (const ::VideoInfo &vi, int height = -1);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	class ClipInfo
	{
	public:
		ClipType       _type = ClipType_UNKNOWN;
		::PClip        _clip_sptr; // Not valid for the destination clip
	};

	void           fill (::PVideoFrame &dst_sptr, int n, int plane_index, ClipType type, float val);
	void           fill_frame_part (::PVideoFrame &dst_sptr, int n, int plane_index, float val, bool stacked_flag, int part);
	void           copy (::PVideoFrame &dst_sptr, int n, int plane_index, ClipType type_dst, ClipIdx src_idx, ::IScriptEnvironment &env);
	void           copy_n_to_n (::PVideoFrame &dst_sptr, ClipIdx src_idx, int n, int plane_index, ::IScriptEnvironment &env);
	void           copy_8_to_stack16 (::PVideoFrame &dst_sptr, ClipIdx src_idx, int n, int plane_index, ::IScriptEnvironment &env, int part);
	void           copy_stack16_to_8 (::PVideoFrame &dst_sptr, ClipIdx src_idx, int n, int plane_index, ::IScriptEnvironment &env, int part);

	static bool    have_same_height (ClipType t1, ClipType t2);
	static bool    is_stacked (ClipType type);

	const ::VideoInfo & // For the destination clip. May changed during the filter setup.
	               _vi;
	PlaneProcCbInterface &
	               _cb;
	int            _nbr_planes = 0;
	std::array <double, _max_nbr_planes>
	               _proc_mode_arr { fstb::make_array <_max_nbr_planes> (
							double (PlaneProcMode_PROCESS)
	               ) };
	std::array <ClipInfo, ClipIdx_NBR_ELT>
	               _clip_info_arr;
	bool           _manual_flag = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               PlaneProcessor ()                               = delete;
	               PlaneProcessor (const PlaneProcessor &other)    = delete;
	               PlaneProcessor (PlaneProcessor &&other)         = delete;
	PlaneProcessor &
	               operator = (const PlaneProcessor &other)        = delete;
	PlaneProcessor &
	               operator = (PlaneProcessor &&other)             = delete;
	bool           operator == (const PlaneProcessor &other) const = delete;
	bool           operator != (const PlaneProcessor &other) const = delete;

}; // class PlaneProcessor



}  // namespace avsutl



//#include "avsutl/PlaneProcessor.hpp"



#endif   // avsutl_PlaneProcessor_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
