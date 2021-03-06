////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      Video
//  File name:   VeSurface.h
//  Created:     2016/07/08 by Albert
//  Description:
// -------------------------------------------------------------------------
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
// -------------------------------------------------------------------------
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
// -------------------------------------------------------------------------
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_SWSURFACE       0
#define VE_PREALLOC        0x00000001
#define VE_RLEACCEL        0x00000002
#define VE_DONTFREE        0x00000004

#define VE_MUSTLOCK(S) (((S)->flags & VE_RLEACCEL) != 0)

VeSmartPointer(VeSurface);

class VENUS_API VeSurface : public VeRefObject
{
	VeNoCopy(VeSurface);
public:
	inline bool SetPalette(const VePalettePtr& spPalette) noexcept;

	inline int32_t GetWidth() noexcept;

	inline int32_t GetHeight() noexcept;

	inline int32_t GetPitch() noexcept;

	inline VePixelFormatPtr GetFormat() noexcept;

	void* GetBuffer() noexcept;
	
	static VeSurfacePtr CreateRGBSurface(uint32_t u32Flags,
		int32_t i32Width, int32_t i32Height, int32_t i32Depth,
		uint32_t u32Rmask, uint32_t u32Gmask, uint32_t u32Bmask,
		uint32_t u32Amask) noexcept;

protected:
	VeSurface() noexcept;

	virtual ~VeSurface() noexcept;

	int32_t CalculatePitch() noexcept;

	uint32_t m_u32Flags = 0;
	VePixelFormatPtr m_spFormat;
	int32_t m_i32Width = 0;
	int32_t m_i32Height = 0;
	int32_t m_i32Pitch = 0;
	VeBlobPtr m_spPixels;

};

#include "VeSurface.inl"
