////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  Module:      VePower
//  File name:   VeWindow.h
//  Created:     2015/07/26 by Napoleon
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_ALPHA_OPAQUE 255
#define VE_ALPHA_TRANSPARENT 0

enum
{
	VE_PIXELTYPE_UNKNOWN,
	VE_PIXELTYPE_INDEX1,
	VE_PIXELTYPE_INDEX4,
	VE_PIXELTYPE_INDEX8,
	VE_PIXELTYPE_PACKED8,
	VE_PIXELTYPE_PACKED16,
	VE_PIXELTYPE_PACKED32,
	VE_PIXELTYPE_ARRAYU8,
	VE_PIXELTYPE_ARRAYU16,
	VE_PIXELTYPE_ARRAYU32,
	VE_PIXELTYPE_ARRAYF16,
	VE_PIXELTYPE_ARRAYF32
};

enum
{
	VE_BITMAPORDER_NONE,
	VE_BITMAPORDER_4321,
	VE_BITMAPORDER_1234
};

enum
{
	VE_PACKEDORDER_NONE,
	VE_PACKEDORDER_XRGB,
	VE_PACKEDORDER_RGBX,
	VE_PACKEDORDER_ARGB,
	VE_PACKEDORDER_RGBA,
	VE_PACKEDORDER_XBGR,
	VE_PACKEDORDER_BGRX,
	VE_PACKEDORDER_ABGR,
	VE_PACKEDORDER_BGRA
};

enum
{
	VE_ARRAYORDER_NONE,
	VE_ARRAYORDER_RGB,
	VE_ARRAYORDER_RGBA,
	VE_ARRAYORDER_ARGB,
	VE_ARRAYORDER_BGR,
	VE_ARRAYORDER_BGRA,
	VE_ARRAYORDER_ABGR
};

enum
{
	VE_PACKEDLAYOUT_NONE,
	VE_PACKEDLAYOUT_332,
	VE_PACKEDLAYOUT_4444,
	VE_PACKEDLAYOUT_1555,
	VE_PACKEDLAYOUT_5551,
	VE_PACKEDLAYOUT_565,
	VE_PACKEDLAYOUT_8888,
	VE_PACKEDLAYOUT_2101010,
	VE_PACKEDLAYOUT_1010102
};

#define VE_DEFINE_PIXELFOURCC(A, B, C, D) VE_FOURCC(A, B, C, D)

#define VE_DEFINE_PIXELFORMAT(type, order, layout, bits, bytes) \
    ((1 << 28) | ((type) << 24) | ((order) << 20) | ((layout) << 16) | \
     ((bits) << 8) | ((bytes) << 0))

#define VE_PIXELFLAG(X)    (((X) >> 28) & 0x0F)
#define VE_PIXELTYPE(X)    (((X) >> 24) & 0x0F)
#define VE_PIXELORDER(X)   (((X) >> 20) & 0x0F)
#define VE_PIXELLAYOUT(X)  (((X) >> 16) & 0x0F)
#define VE_BITSPERPIXEL(X) (((X) >> 8) & 0xFF)
#define VE_BYTESPERPIXEL(X) \
    (VE_ISPIXELFORMAT_FOURCC(X) ? \
        ((((X) == VE_PIXELFORMAT_YUY2) || \
          ((X) == VE_PIXELFORMAT_UYVY) || \
          ((X) == VE_PIXELFORMAT_YVYU)) ? 2 : 1) : (((X) >> 0) & 0xFF))

#define VE_ISPIXELFORMAT_INDEXED(format)   \
    (!VE_ISPIXELFORMAT_FOURCC(format) && \
     ((VE_PIXELTYPE(format) == VE_PIXELTYPE_INDEX1) || \
      (VE_PIXELTYPE(format) == VE_PIXELTYPE_INDEX4) || \
      (VE_PIXELTYPE(format) == VE_PIXELTYPE_INDEX8)))

#define VE_ISPIXELFORMAT_ALPHA(format)   \
    (!VE_ISPIXELFORMAT_FOURCC(format) && \
     ((VE_PIXELORDER(format) == VE_PACKEDORDER_ARGB) || \
      (VE_PIXELORDER(format) == VE_PACKEDORDER_RGBA) || \
      (VE_PIXELORDER(format) == VE_PACKEDORDER_ABGR) || \
      (VE_PIXELORDER(format) == VE_PACKEDORDER_BGRA)))

#define VE_ISPIXELFORMAT_FOURCC(format)    \
    ((format) && (VE_PIXELFLAG(format) != 1))

#define VE_FOURCC VE_MAKE_ID

enum
{
	VE_PIXELFORMAT_UNKNOWN,
	VE_PIXELFORMAT_INDEX1LSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX1, VE_BITMAPORDER_4321, 0,
		1, 0),
	VE_PIXELFORMAT_INDEX1MSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX1, VE_BITMAPORDER_1234, 0,
		1, 0),
	VE_PIXELFORMAT_INDEX4LSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX4, VE_BITMAPORDER_4321, 0,
		4, 0),
	VE_PIXELFORMAT_INDEX4MSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX4, VE_BITMAPORDER_1234, 0,
		4, 0),
	VE_PIXELFORMAT_INDEX8 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX8, 0, 0, 8, 1),
	VE_PIXELFORMAT_RGB332 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED8, VE_PACKEDORDER_XRGB,
		VE_PACKEDLAYOUT_332, 8, 1),
	VE_PIXELFORMAT_RGB444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XRGB,
		VE_PACKEDLAYOUT_4444, 12, 2),
	VE_PIXELFORMAT_RGB555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XRGB,
		VE_PACKEDLAYOUT_1555, 15, 2),
	VE_PIXELFORMAT_BGR555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XBGR,
		VE_PACKEDLAYOUT_1555, 15, 2),
	VE_PIXELFORMAT_ARGB4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ARGB,
		VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_RGBA4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_RGBA,
		VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_ABGR4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ABGR,
		VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_BGRA4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_BGRA,
		VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_ARGB1555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ARGB,
		VE_PACKEDLAYOUT_1555, 16, 2),
	VE_PIXELFORMAT_RGBA5551 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_RGBA,
		VE_PACKEDLAYOUT_5551, 16, 2),
	VE_PIXELFORMAT_ABGR1555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ABGR,
		VE_PACKEDLAYOUT_1555, 16, 2),
	VE_PIXELFORMAT_BGRA5551 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_BGRA,
		VE_PACKEDLAYOUT_5551, 16, 2),
	VE_PIXELFORMAT_RGB565 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XRGB,
		VE_PACKEDLAYOUT_565, 16, 2),
	VE_PIXELFORMAT_BGR565 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XBGR,
		VE_PACKEDLAYOUT_565, 16, 2),
	VE_PIXELFORMAT_RGB24 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_ARRAYU8, VE_ARRAYORDER_RGB, 0,
		24, 3),
	VE_PIXELFORMAT_BGR24 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_ARRAYU8, VE_ARRAYORDER_BGR, 0,
		24, 3),
	VE_PIXELFORMAT_RGB888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_XRGB,
		VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_RGBX8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_RGBX,
		VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_BGR888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_XBGR,
		VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_BGRX8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_BGRX,
		VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_ARGB8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_ARGB,
		VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_RGBA8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_RGBA,
		VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_ABGR8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_ABGR,
		VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_BGRA8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_BGRA,
		VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_ARGB2101010 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_ARGB,
		VE_PACKEDLAYOUT_2101010, 32, 4),

	VE_PIXELFORMAT_YV12 =
	VE_FOURCC('Y', 'V', '1', '2'),
	VE_PIXELFORMAT_IYUV =
	VE_FOURCC('I', 'Y', 'U', 'V'),
	VE_PIXELFORMAT_YUY2 =
	VE_FOURCC('Y', 'U', 'Y', '2'),
	VE_PIXELFORMAT_UYVY =
	VE_FOURCC('U', 'Y', 'V', 'Y'),
	VE_PIXELFORMAT_YVYU =
	VE_FOURCC('Y', 'V', 'Y', 'U')
};

struct VeDisplayMode
{
	VeUInt32 m_u32Format = 0;
	VeInt32 m_i32Width = 0;
	VeInt32 m_i32Height = 0;
	VeInt32 m_i32RefreshRate = 0;
	VeRefObjectPtr m_spDriverData;
};

struct VeVideoDisplay
{
	VeFixedString m_kName;
	VeVector<VeDisplayMode> m_kDisplayModes;
	VeDisplayMode m_kDesktopMode;
	VeDisplayMode m_kCurrentMode;
	void* m_pvFullscreenWindow = nullptr;
	VeRefObjectPtr m_spDriverData;
};

struct VeWindowUserData
{
	VeChar8* m_pcName = nullptr;
	void* m_pvData = nullptr;
	VeWindowUserData* m_pkNext = nullptr;
};

class VE_POWER_API VeWindow : public VeRefObject
{
public:
	struct Data
	{
		VeRefNode<Data*> m_kNode;
		VeUInt32 m_u32Id = 0;
		VeFixedString m_kTitle;
		void* icon = nullptr;
		VeInt32 x = 0, y = 0;
		VeInt32 w = 0, h = 0;
		VeInt32 min_w = 0, min_h = 0;
		VeInt32 max_w = 0, max_h = 0;
		VeUInt32 m_u32Flags = 0;
		VeUInt32 m_u32LastFullscreenFlags = 0;
		VeRect m_kWindowed;
		VeDisplayMode m_kFullscreenMode;
		VeFloat32 m_f32Brightness = 0;
		VeUInt16* m_pu16Gamma = nullptr;
		VeUInt16* m_pu16SavedGamma = nullptr;
		void* surface = nullptr;
		VE_BOOL m_bSurfaceValid = 0;
		VE_BOOL m_bIsDestorying = 0;
		void* shaper = nullptr;
		VeWindowUserData* m_pkData = nullptr;
		VeRefObjectPtr m_spDriverdata;
	};

	VeWindow() noexcept;

	virtual ~VeWindow() noexcept;

	inline bool IsValid() const noexcept;

	inline VeUInt32 GetID() const noexcept;

	inline const VeChar8* GetTitle() const noexcept;

	inline VeInt32 GetPosX() const noexcept;

	inline VeInt32 GetPosY() const noexcept;

	inline VeInt32 GetWidth() const noexcept;

	inline VeInt32 GetHeight() const noexcept;

	inline VeInt32 GetMinimumWidth() const noexcept;

	inline VeInt32 GetMinimumHeight() const noexcept;

	inline VeInt32 GetMaximumWidth() const noexcept;

	inline VeInt32 GetMaximumHeight() const noexcept;

	inline VeFloat32 GetBrightness() const noexcept;

	bool Create(const VeChar8* pcTitle, VeInt32 x, VeInt32 y,
		VeInt32 w, VeInt32 h, VeUInt32 u32Flags) noexcept;

	bool Create(const void* pvData) noexcept;

	void SetTitle(const VeChar8* pcTitle) noexcept;

	void SetPosition(VeInt32 x, VeInt32 y) noexcept;

	void SetSize(VeInt32 w, VeInt32 h) noexcept;

	void SetMinimumSize(VeInt32 min_w, VeInt32 min_h) noexcept;

	void SetMaximumSize(VeInt32 max_w, VeInt32 max_h) noexcept;

	void Show() noexcept;

	void Hide() noexcept;

	void Raise() noexcept;

	void Maximize() noexcept;

	void Minimize() noexcept;

	void Restore() noexcept;

	void SetBordered(bool bBordered) noexcept;

	void SetFullscreen(VeUInt32 u32Flags) noexcept;

	bool SetBrightness(VeFloat32 f32Brightness) noexcept;

	void SetGrab(bool bGrabbed) noexcept;

	void Destory();

	static VeWindow* Cast(VeWindow::Data* pkData) noexcept;

protected:
	Data m_kData;

};

VeSmartPointer(VeWindow);

#include "VeWindow.inl"
