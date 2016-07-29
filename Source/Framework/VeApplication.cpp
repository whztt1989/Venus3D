////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      Framework
//  File name:   VeApplication.cpp
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

#include "stdafx.h"

//--------------------------------------------------------------------------
VeApplication::VeApplication(const char* pcName,
	uint32_t u32Version) noexcept
	: m_kName(pcName), m_u32Version(u32Version)
{

}
//--------------------------------------------------------------------------
VeApplication::~VeApplication() noexcept
{
	
}
//--------------------------------------------------------------------------
void VeApplication::Init() noexcept
{
	m_spRenderer = VeRenderer::Create(VE_RENDER_D3D12);
	VE_ASSERT(m_spRenderer);
	VE_TRY_CALL(m_spRenderer->Init());
	m_spWindow = m_spRenderer->CreateRenderWindow("D3D12", 1024, 768);
	VE_ASSERT(m_spWindow);
	OnInit();
}
//--------------------------------------------------------------------------
void VeApplication::Term() noexcept
{
	OnTerm();
	m_spWindow = nullptr;
	VE_TRY_CALL(m_spRenderer->Term());
	m_spRenderer = nullptr;
}
//--------------------------------------------------------------------------
void VeApplication::ProcessEvents() noexcept
{
	VE_ASSERT(venus3d.GetVideo());
	venus3d.GetVideo()->PumpEvents();
}
//--------------------------------------------------------------------------
void VeApplication::Update() noexcept
{
	venus3d.GetTime().Update();
	OnUpdate();
}
//--------------------------------------------------------------------------
void VeApplication::Render() noexcept
{
	m_spWindow->Begin();
	OnRender();	
	m_spWindow->End();
}
//--------------------------------------------------------------------------
void VeApplication::Loop() noexcept
{
	while (m_bLoop)
	{
		ProcessEvents();
		if (m_spWindow && m_spWindow->IsValid())
		{
			Update();
			Render();
		}
		else
		{
			Quit();
		}
	}
}
//--------------------------------------------------------------------------
void VeApplication::Go() noexcept
{
	Init();
	Loop();
	Term();
}
//--------------------------------------------------------------------------
