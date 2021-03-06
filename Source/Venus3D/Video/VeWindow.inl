////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      Video
//  File name:   VeWindow.inl
//  Created:     2016/07/25 by Albert
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

//--------------------------------------------------------------------------
inline bool VeWindow::IsValid() noexcept
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_WINDOW_VALID);
}
//--------------------------------------------------------------------------
inline bool VeWindow::IsVisible() noexcept
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_WINDOW_SHOWN);
}
//--------------------------------------------------------------------------
inline bool VeWindow::IsHidden() noexcept
{
	return !IsVisible();
}
//--------------------------------------------------------------------------
inline uint32_t VeWindow::GetWidth() noexcept
{
	return (uint32_t)m_u16Width;
}
//--------------------------------------------------------------------------
inline uint32_t VeWindow::GetHeight() noexcept
{
	return (uint32_t)m_u16Height;
}
//--------------------------------------------------------------------------
