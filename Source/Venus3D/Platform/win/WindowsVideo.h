////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      Video
//  File name:   WindowsVideo.h
//  Created:     2016/07/24 by Albert
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

class WindowsVideo : public VeDesktopVideo
{
	VeNoCopy(WindowsVideo);
	VeRTTIDecl(WindowsVideo, VeDesktopVideo);
public:
	WindowsVideo() noexcept;

	virtual ~WindowsVideo() noexcept;
	
	virtual void Init() override;

	virtual void Term() override;

	virtual void PumpEvents() noexcept override;

	virtual int32_t MessageBoxSync(const char* pcCaption,
		const char* pcText, uint32_t u32Flags) noexcept override;

	virtual VeDesktopWindowPtr Create(const char* pcTitle, int32_t w, int32_t h,
		int32_t x, int32_t y, uint32_t u32Flags) noexcept override;

	static LPWSTR UTF8ToWSTR(const char* pcStr) noexcept;

protected:
	friend class WindowsWindow;
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam) noexcept;

	HINSTANCE m_hInstance = nullptr;
	HINSTANCE m_hPrevInstance = nullptr;
	LPWSTR m_wstrClassName = nullptr;
	int32_t m_i32CmdShow = SW_SHOW;

};
