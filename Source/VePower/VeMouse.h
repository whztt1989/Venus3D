////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  Module:      VePower
//  File name:   VeMouse.h
//  Created:     2015/08/09 by Napoleon
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_BUTTON(X)       (1 << ((X)-1))
#define VE_BUTTON_LEFT     1
#define VE_BUTTON_MIDDLE   2
#define VE_BUTTON_RIGHT    3
#define VE_BUTTON_X1       4
#define VE_BUTTON_X2       5
#define VE_BUTTON_LMASK    VE_BUTTON(VE_BUTTON_LEFT)
#define VE_BUTTON_MMASK    VE_BUTTON(VE_BUTTON_MIDDLE)
#define VE_BUTTON_RMASK    VE_BUTTON(VE_BUTTON_RIGHT)
#define VE_BUTTON_X1MASK   VE_BUTTON(VE_BUTTON_X1)
#define VE_BUTTON_X2MASK   VE_BUTTON(VE_BUTTON_X2)

class VE_POWER_API VeCursor : public VeRefObject
{
public:
	struct Data
	{
		VeRefNode<Data*> m_kNode;
		void* m_pvDriverdata = nullptr;
	};

	VeCursor() noexcept;

	virtual ~VeCursor() noexcept;

	static VeCursor* Cast(VeCursor::Data* pkData) noexcept;

protected:
	friend class VeMouse;

	Data m_kData;

};

VeSmartPointer(VeCursor);

struct VeMouseClickState
{
	VeInt32 m_i32LastX = 0;
	VeInt32 m_i32LastY = 0;
	VeUInt32 m_u32LastTimeStamp = 0;
	VeUInt8 m_u8ClickCount = 0;
};

typedef VeUInt32 VeMouseID;

enum VeSystemCursor
{
	VE_SYSTEM_CURSOR_ARROW,
	VE_SYSTEM_CURSOR_IBEAM,
	VE_SYSTEM_CURSOR_WAIT,
	VE_SYSTEM_CURSOR_CROSSHAIR,
	VE_SYSTEM_CURSOR_WAITARROW,
	VE_SYSTEM_CURSOR_SIZENWSE,
	VE_SYSTEM_CURSOR_SIZENESW,
	VE_SYSTEM_CURSOR_SIZEWE,
	VE_SYSTEM_CURSOR_SIZENS,
	VE_SYSTEM_CURSOR_SIZEALL,
	VE_SYSTEM_CURSOR_NO,
	VE_SYSTEM_CURSOR_HAND,
	VE_NUM_SYSTEM_CURSORS
};

class VE_POWER_API VeMouse : public VeRefObject
{
public:
	VeMouse() noexcept;

	virtual ~VeMouse() noexcept;

	inline VeWindowPtr GetFocus() noexcept;

	inline VeCursorPtr GetCursor() noexcept;

	inline VeCursorPtr GetDefaultCursor() noexcept;

	void SetCursor(VeCursor::Data* pkCursor) noexcept;

	void WarpInWindow(VeWindow::Data* pkWindow, VeInt32 x, VeInt32 y) noexcept;

public:
	void Init() noexcept;

	void Term() noexcept;

	void SetDoubleClickTime(VeUInt32 u32Interval) noexcept;

	void SetDefaultCursor(VeCursor::Data* pkCursor) noexcept;

	void SetMouseFocus(VeWindow::Data* pkWindow) noexcept;

	void SendMouseMotion(VeWindow::Data* pkWindow, VeMouseID u32MouseID,
		VeInt32 i32Relative, VeInt32 x, VeInt32 y) noexcept;

	void SendMouseButton(VeWindow::Data* pkWindow, VeMouseID u32MouseID,
		VeUInt8 u8State, VeUInt8 u8Button) noexcept;

protected:
	bool UpdateMouseFocus(VeWindow::Data* pkWindow, VeInt32 x, VeInt32 y,
		VeUInt32 u32ButtonState) noexcept;

	void PrivateSendMouseMotion(VeWindow::Data* pkWindow, VeMouseID u32mouseID,
		VeInt32 i32Relative, VeInt32 x, VeInt32 y) noexcept;

	VeMouseClickState* GetMouseClickState(VeUInt8 u8Button) noexcept;

	virtual void _Init() noexcept {}

	virtual void _Term() noexcept {}

	virtual bool _CreateCursor(VeCursor::Data* pkCur,
		const VeSurfacePtr& spSurface,
		VeInt32 i32HotX, VeInt32 i32HotY) noexcept { return false; }

	virtual bool _CreateSystemCursor(VeCursor::Data* pkCur,
		VeSystemCursor eCursor) noexcept { return false; }

	virtual void _ShowCursor(VeCursor::Data* pkCur) noexcept {}

	virtual void _MoveCursor(VeCursor::Data* pkCur) noexcept {}

	virtual void _FreeCursor(VeCursor::Data* pkCur) noexcept {}

	virtual void _WarpMouse(VeWindow::Data* pkWindow, VeInt32 x, VeInt32 y) noexcept;

	virtual bool _SetRelativeMouseMode(bool bEnabled) noexcept { return false; }

	VeMouseID m_u32MouseID = 0;
	VeWindow::Data* m_pkFocus = nullptr;
	VeInt32 m_i32PosX = 0;
	VeInt32 m_i32PosY = 0;
	VeInt32 m_i32XDelta = 0;
	VeInt32 m_i32YDelta = 0;
	VeInt32 m_i32LastX = 0;
	VeInt32 m_i32LastY = 0;
	VeUInt32 m_u32ButtonState = 0;
	VeUInt32 m_u32DoubleClickTime = 500;
	VeUInt32 m_u32DoubleClickRadius = 1;
	VE_BOOL m_bRelativeMode = VE_FALSE;
	VE_BOOL m_bRelativeModeWarp = VE_FALSE;
	VeVector<VeMouseClickState> m_kClickStateList;
	VeRefList<VeCursor::Data*> m_kCursorList;
	VeCursorPtr m_spDefCursor;
	VeCursorPtr m_spCurCursor;
	VE_BOOL m_bCursorShown = VE_FALSE;
	VeRefObjectPtr m_spDriverdata;

};

VeSmartPointer(VeMouse);

#include "VeMouse.inl"
