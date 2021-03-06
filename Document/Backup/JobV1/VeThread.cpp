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
VeThreadHandle VeCreateThread(VeThreadCallback pfuncThreadProc,
	void* pvParam, int32_t i32Priority, size_t stStackSize) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	VeThreadHandle hRes = (VeThreadHandle)_beginthreadex(NULL,
		(unsigned int)stStackSize, pfuncThreadProc, pvParam, 0, NULL);
	SetThreadPriority(hRes, i32Priority);
	return hRes;
#else
	VeThreadHandle hThread(0);
	pthread_attr_t kAttr;
	pthread_attr_init(&kAttr);
	sched_param kParam;
	pthread_attr_getschedparam(&kAttr, &kParam);
	kParam.sched_priority = i32Priority;
	pthread_attr_setschedparam(&kAttr, &kParam);
	pthread_attr_setstacksize(&kAttr, stStackSize ? stStackSize : 4096);
	pthread_create(&hThread, &kAttr, pfuncThreadProc, pvParam);
	return hThread;
#endif
}
//--------------------------------------------------------------------------
bool VeJoinThread(VeThreadHandle hThread) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	return WaitForSingleObject(hThread, UINT32_MAX) == WAIT_OBJECT_0;
#else
	return hThread ? VE_SUCCEEDED(pthread_join(hThread, NULL)) : true;
#endif
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
void VeSuspendThread(VeThreadHandle hThread) noexcept
{
#	ifdef BUILD_PLATFORM_WIN
	VE_ASSERT_NE(SuspendThread(hThread), -1);
#   else
	VE_ASSERT_EQ(pthread_kill(hThread, SUSPEND_SIG), 0);
#	endif
}
//--------------------------------------------------------------------------
void VeResumeThread(VeThreadHandle hThread) noexcept
{
#	ifdef BUILD_PLATFORM_WIN
	VE_ASSERT_NE(ResumeThread(hThread), -1);
#   else
	VE_ASSERT_EQ(pthread_kill(hThread, RESUME_SIG), 0);
#	endif
}
//--------------------------------------------------------------------------
bool VeIsThreadActive(VeThreadHandle hThread) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	DWORD dwCode(0);
	return (GetExitCodeThread(hThread, &dwCode) && dwCode == STILL_ACTIVE);
#else
	return hThread ? (pthread_kill(hThread, 0) != ESRCH) : false;
#endif
}
//--------------------------------------------------------------------------
VeThreadID VeGetLocalThread() noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	return GetCurrentThreadId();
#else
	return pthread_self();
#endif
}
//--------------------------------------------------------------------------
void VeSleep(uint32_t u32Millisecond) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	Sleep(u32Millisecond);
#else
	timespec kTimeSpec;
	kTimeSpec.tv_sec = u32Millisecond / 1000;
	kTimeSpec.tv_nsec = (u32Millisecond % 1000) * 1000000;
	nanosleep(&kTimeSpec, 0);
#endif
}
//--------------------------------------------------------------------------
bool VeThreadEventInit(VeThreadEvent* phEvent, bool bInitState) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	return ((*phEvent = CreateEvent(NULL, FALSE, bInitState, NULL)) != NULL);
#else
	phEvent->m_u32State = bInitState;
	pthread_mutex_init(&phEvent->m_kMutex, NULL);
	return pthread_cond_init(&phEvent->m_kCond, NULL) == 0;
#endif
}
//--------------------------------------------------------------------------
void VeThreadEventTerm(VeThreadEvent* phEvent) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	if (*phEvent) CloseHandle(*phEvent);
	*phEvent = NULL;
#else
	pthread_mutex_destroy(&phEvent->m_kMutex);
	pthread_cond_destroy(&phEvent->m_kCond);
#endif
}
//--------------------------------------------------------------------------
void VeThreadEventWait(VeThreadEvent* phEvent) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	WaitForSingleObject(*phEvent, INFINITE);
#else
	if (phEvent->m_u32State == 0)
	{
		pthread_mutex_lock(&phEvent->m_kMutex);
		pthread_cond_wait(&phEvent->m_kCond, &phEvent->m_kMutex);
		pthread_mutex_unlock(&phEvent->m_kMutex);
	}
#endif
}
//--------------------------------------------------------------------------
void VeThreadEventWait(VeThreadEvent* phEvent, uint32_t u32Milliseconds) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	WaitForSingleObject(*phEvent, u32Milliseconds);
#else
	if (phEvent->m_u32State == 0)
	{
		timeval kNow;
		timespec kOutTime;
		gettimeofday(&kNow, NULL);
		kOutTime.tv_sec = kNow.tv_sec + u32Milliseconds / 1000;
		kOutTime.tv_nsec = kNow.tv_usec * 1000
			+ (u32Milliseconds % 1000) * 1000000;
		pthread_mutex_lock(&phEvent->m_kMutex);
		pthread_cond_timedwait(&phEvent->m_kCond,
			&phEvent->m_kMutex, &kOutTime);
		pthread_mutex_unlock(&phEvent->m_kMutex);
	}
#endif
}
//--------------------------------------------------------------------------
void VeThreadEventSet(VeThreadEvent* phEvent) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	SetEvent(*phEvent);
#else
	if (phEvent->m_u32State == 0)
	{
		pthread_mutex_lock(&phEvent->m_kMutex);
		phEvent->m_u32State = 1;
		pthread_cond_broadcast(&phEvent->m_kCond);
		pthread_mutex_unlock(&phEvent->m_kMutex);
	}
#endif
}
//--------------------------------------------------------------------------
void VeThreadEventReset(VeThreadEvent* phEvent) noexcept
{
#ifdef  BUILD_PLATFORM_WIN
	ResetEvent(*phEvent);
#else
	if (phEvent->m_u32State == 1)
	{
		pthread_mutex_lock(&phEvent->m_kMutex);
		phEvent->m_u32State = 0;
		pthread_mutex_unlock(&phEvent->m_kMutex);
	}
#endif
}
//--------------------------------------------------------------------------
void VeThreadInitForSuspend() noexcept
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
uint32_t VeThreadHardwareConcurrency() noexcept
{
	return std::thread::hardware_concurrency();
}
//--------------------------------------------------------------------------
VeThread::VeThread(int32_t i32Priority, size_t stStackSize) noexcept
{
	m_u32State.store(0, std::memory_order_relaxed);
	m_pkParams = VE_NEW ThreadParams();
	m_pkParams->m_kEvent.set();
	m_pkParams->m_pkThis = this;
	m_hThread = VeCreateThread(Callback, m_pkParams, i32Priority, stStackSize);
	VE_ASSERT(m_hThread);
}
//--------------------------------------------------------------------------
VeThread::~VeThread() noexcept
{
	uint32_t check(0);
	while (m_u32State.compare_exchange_weak(check, 2, std::memory_order_relaxed));
	m_pkParams->m_kEventLoop.set();
	VeJoinThread(m_hThread);
	m_pkParams = nullptr;
}
//--------------------------------------------------------------------------
#ifdef VE_USE_THREAD_LOCAL
static thread_local VeThreadLocalSingleton* s_pkSingleton = nullptr;
#else
#ifdef VE_MEM_DEBUG
struct VeDeleteCallParams
{
	const char* m_pcSourceFile;
	int32_t m_i32SourceLine;
	const char* m_pcFunction;
};
pthread_key_t g_keyDeleteStack;
#endif
static pthread_key_t s_keySingleton;
#endif
//--------------------------------------------------------------------------
void VeThread::Init() noexcept
{
#	ifndef VE_USE_THREAD_LOCAL
#	ifdef VE_MEM_DEBUG
	assert_eq(pthread_key_create(&g_keyDeleteStack, nullptr), 0);
#	endif
	assert_eq(pthread_key_create(&s_keySingleton, nullptr), 0);
#	endif
	InitPerThread();
}
//--------------------------------------------------------------------------
void VeThread::Term() noexcept
{
	TermPerThread();
#	ifndef VE_USE_THREAD_LOCAL
	assert_eq(pthread_key_delete(s_keySingleton), 0);
#	ifdef VE_MEM_DEBUG
	assert_eq(pthread_key_delete(g_keyDeleteStack), 0);
#	endif
#	endif
}
//--------------------------------------------------------------------------
void VeThread::InitPerThread() noexcept
{
#	ifdef VE_USE_THREAD_LOCAL
	s_pkSingleton = VE_NEW VeThreadLocalSingleton();
#	else
#	ifdef VE_MEM_DEBUG
	assert_eq(pthread_setspecific(g_keyDeleteStack, new vtd::vector<VeDeleteCallParams>()), 0);
#	endif
	assert_eq(pthread_setspecific(s_keySingleton, VE_NEW VeThreadLocalSingleton()), 0);
#	endif
}
//--------------------------------------------------------------------------
void VeThread::TermPerThread() noexcept
{
#	ifdef VE_USE_THREAD_LOCAL
	VE_SAFE_DELETE(s_pkSingleton);
#	else
	VE_DELETE((VeThreadLocalSingleton*)pthread_getspecific(s_keySingleton));
#	ifdef VE_MEM_DEBUG
	delete (vtd::vector<VeDeleteCallParams>*)pthread_getspecific(g_keyDeleteStack);
#	endif
#	endif
}
//--------------------------------------------------------------------------
VeThreadLocalSingleton* VeThread::GetThreadLocalSingleton() noexcept
{
#	ifdef VE_USE_THREAD_LOCAL
	return s_pkSingleton;
#	else
	return (VeThreadLocalSingleton*)pthread_getspecific(s_keySingleton);
#	endif 
}
//--------------------------------------------------------------------------
VeThreadCallbackResult VeThread::Callback(void* pvParam) noexcept
{
	VeThread::InitPerThread();
	ThreadParams* pkParams = (ThreadParams*)pvParam;
	VeThread* pkClass = pkParams->m_pkThis;
	while (true)
	{
		pkParams->m_kEventLoop.wait();
		switch (pkClass->m_u32State.load(std::memory_order_relaxed))
		{
		case 1:
			pkClass->m_pfuncEntry(pkClass->m_pvData);
			pkClass->m_u32State.store(0, std::memory_order_relaxed);
			pkParams->m_kEventLoop.reset();
			pkParams->m_kEvent.set();
			continue;
		}
		break;
	}
	VE_DELETE(pkParams);
	VeThread::TermPerThread();
	return 0;
}
//--------------------------------------------------------------------------
