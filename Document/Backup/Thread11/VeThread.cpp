////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      ASync
//  File name:   VeThread.cpp
//  Created:     2016/07/11 by Albert
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
VeThread::VeThread() noexcept
{
	m_u32State.store(0, std::memory_order_relaxed);
	m_kJoin.Set();
	m_kCore = std::thread([this]() noexcept
	{
		Callback();
	});
}
//--------------------------------------------------------------------------
VeThread::VeThread(const std::function<void()>& kEntry) noexcept
{
	SetEntry(kEntry);
}
//--------------------------------------------------------------------------
VeThread::~VeThread() noexcept
{
	while (IsRunning())
		;
	m_u32State.store(2, std::memory_order_relaxed);
	m_kLoop.Set();
	m_kCore.join();
}
//--------------------------------------------------------------------------
void VeThread::Start() noexcept
{
	uint32_t u32Stop(0);
	if (m_u32State.compare_exchange_weak(u32Stop, 1u, std::memory_order_relaxed))
	{
		m_kLoop.Set();
		m_kJoin.Reset();
	}
}
//--------------------------------------------------------------------------
void VeThread::StartEntry(const std::function<void()>& kEntry) noexcept
{
	uint32_t u32Stop(0);
	if (m_u32State.compare_exchange_weak(u32Stop, 1u, std::memory_order_relaxed))
	{
		m_kEntry = kEntry;
		m_kLoop.Set();
		m_kJoin.Reset();
	}
}
//--------------------------------------------------------------------------
void VeThread::SetEntry(const std::function<void()>& kEntry) noexcept
{
	if (m_u32State.load(std::memory_order_relaxed) == 0)
	{
		m_kEntry = kEntry;
	}
}
//--------------------------------------------------------------------------
void VeThread::Join() noexcept
{
	m_kJoin.Wait();
}
//--------------------------------------------------------------------------
#ifndef BUILD_PLATFORM_WIN
//--------------------------------------------------------------------------
#define RESUME_SIG SIGUSR2
#define SUSPEND_SIG SIGUSR1
//--------------------------------------------------------------------------
static sigset_t wait_mask;
static __thread int suspended;
//--------------------------------------------------------------------------
void resume_handler(int) noexcept
{
    suspended = 0;
}
//--------------------------------------------------------------------------
void suspend_handler(int) noexcept
{
    if (suspended) return;
    suspended = 1;
    do sigsuspend(&wait_mask); while (suspended);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
void VeThread::Suspend() noexcept
{
#	ifdef BUILD_PLATFORM_WIN
    SuspendThread(m_kCore.native_handle());
#   else
    pthread_kill(m_kCore.native_handle(), SUSPEND_SIG);
#	endif
}
//--------------------------------------------------------------------------
void VeThread::Resume() noexcept
{
#	ifdef BUILD_PLATFORM_WIN
    ResumeThread(m_kCore.native_handle());
#   else
    pthread_kill(m_kCore.native_handle(), RESUME_SIG);
#	endif
}
//--------------------------------------------------------------------------
void VeThread::Init()
{
#	ifndef BUILD_PLATFORM_WIN
    struct sigaction sa;
    sigfillset(&wait_mask);
    sigdelset(&wait_mask, SUSPEND_SIG);
    sigdelset(&wait_mask, RESUME_SIG);
    sigfillset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = resume_handler;
    sigaction(RESUME_SIG, &sa, nullptr);
    sa.sa_handler = suspend_handler;
    sigaction(SUSPEND_SIG, &sa, nullptr);
#	endif
}
//--------------------------------------------------------------------------
void VeThread::Term()
{
#	ifndef BUILD_PLATFORM_WIN
	
#	endif
}
//--------------------------------------------------------------------------
void VeThread::Callback() noexcept
{
	do
	{
		m_kLoop.Wait();
		if (m_u32State.load(std::memory_order_relaxed) == 1)
		{
			m_kEntry();
			m_u32State.store(0, std::memory_order_relaxed);
			m_kLoop.Reset();
			m_kJoin.Set();
		}
	} while (m_u32State.load(std::memory_order_relaxed) < 2);
}
//--------------------------------------------------------------------------
