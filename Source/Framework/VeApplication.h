////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      Framework
//  File name:   VeApplication.h
//  Created:     2016/07/23 by Albert
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

#include <Venus3D.h>

VeSmartPointer(VeApplication);

class VeApplication : public VeRefObject
{
public:
	inline void Quit() noexcept;

	virtual void Init() noexcept;

	virtual void Term() noexcept;	

	virtual void ProcessEvents() noexcept;

	virtual void Update() noexcept;

	virtual void Render() noexcept;

	virtual void Loop() noexcept;

	virtual void Go() noexcept;

	virtual void OnInit() noexcept {}

	virtual void OnTerm() noexcept {}

	virtual void OnUpdate() noexcept {}

	virtual void OnRender() noexcept {}

	static const char* Name() noexcept;

	static uint32_t Version() noexcept;

	static VeApplicationPtr Create() noexcept;

protected:
	VeApplication() noexcept;

	virtual ~VeApplication() noexcept;

	vtd::string m_kCaption;
	VeRendererPtr m_spRenderer;
	VeRenderWindowPtr m_spWindow;
	bool m_bLoop = true;

};

#include "VeApplication.inl"
