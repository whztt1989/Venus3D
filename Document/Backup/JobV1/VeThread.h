////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      ASync
//  File name:   VeThread.h
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

#pragma once

#ifdef BUILD_PLATFORM_WIN

typedef CRITICAL_SECTION VeThreadMutex;
typedef HANDLE VeThreadEvent;
typedef HANDLE VeThreadHandle;
typedef DWORD VeThreadID;
typedef unsigned int VeThreadCallbackResult;
typedef CONDITION_VARIABLE VeConditionVariable;

#define VeThreadMutexInit(x) InitializeCriticalSection(&(x))
#define VeThreadMutexTerm(x) DeleteCriticalSection(&(x))
#define VeThreadMutexLock(x) EnterCriticalSection(&(x))
#define VeThreadMutexUnlock(x) LeaveCriticalSection(&(x))

#define VeConditionVariableInit(x) InitializeConditionVariable(&(x))
#define VeConditionVariableTerm(x)
#define VeConditionVariableWait(x,m) SleepConditionVariableCS(&(x),&(m),INFINITE)
#define VeConditionVariableWakeOne(x) WakeConditionVariable(&(x))
#define VeConditionVariableWakeAll(x) WakeAllConditionVariable(&(x))

#define VE_THREAD_PRIORITY_IDLE THREAD_BASE_PRIORITY_IDLE
#define VE_THREAD_PRIORITY_LOWEST THREAD_PRIORITY_LOWEST
#define VE_THREAD_PRIORITY_BELOW_NORMAL THREAD_PRIORITY_BELOW_NORMAL
#define VE_THREAD_PRIORITY_NORMAL THREAD_PRIORITY_NORMAL
#define VE_THREAD_PRIORITY_ABOVE_NORMAL THREAD_PRIORITY_ABOVE_NORMAL
#define VE_THREAD_PRIORITY_HIGHEST THREAD_PRIORITY_HIGHEST
#define VE_THREAD_PRIORITY_TIME_CRITICAL THREAD_PRIORITY_TIME_CRITICAL

#else

typedef pthread_mutex_t VeThreadMutex;
typedef struct
{
	pthread_cond_t m_kCond;
	pthread_mutex_t m_kMutex;
	uint32_t m_u32State;
} VeThreadEvent;
typedef pthread_t VeThreadHandle;
typedef pthread_t VeThreadID;
typedef void* VeThreadCallbackResult;
typedef pthread_cond_t VeConditionVariable;

#define VeThreadMutexInit(x) pthread_mutex_init(&(x), NULL)
#define VeThreadMutexTerm(x) pthread_mutex_destroy(&(x))
#define VeThreadMutexLock(x) pthread_mutex_lock(&(x))
#define VeThreadMutexUnlock(x) pthread_mutex_unlock(&(x))

#define VeConditionVariableInit(x) pthread_cond_init(&(x), NULL)
#define VeConditionVariableTerm(x) pthread_cond_destroy(&(x))
#define VeConditionVariableWait(x,m) pthread_cond_wait(&(x),&(m))
#define VeConditionVariableWakeOne(x) pthread_cond_signal(&(x))
#define VeConditionVariableWakeAll(x) pthread_cond_broadcast(&(x))

#define VE_THREAD_PRIORITY_IDLE 99
#define VE_THREAD_PRIORITY_LOWEST 88
#define VE_THREAD_PRIORITY_BELOW_NORMAL 64
#define VE_THREAD_PRIORITY_NORMAL 32
#define VE_THREAD_PRIORITY_ABOVE_NORMAL 24
#define VE_THREAD_PRIORITY_HIGHEST 2
#define VE_THREAD_PRIORITY_TIME_CRITICAL 1

#endif

enum VeThreadResult
{
	VE_THREAD_WAIT_SUCCEED,
	VE_THREAD_WAIT_TIMEOUT,
	VE_THREAD_WAIT_ABANDON,
	VE_THREAD_WAIT_FAILED
};

typedef VeThreadCallbackResult(VE_CALLBACK * VeThreadCallback)(void* pvParam);

VENUS_API VeThreadHandle VeCreateThread(VeThreadCallback pfuncThreadProc, void* pvParam, int32_t i32Priority = VE_THREAD_PRIORITY_NORMAL, size_t stStackSize = 32768) noexcept;

VENUS_API bool VeJoinThread(VeThreadHandle hThread) noexcept;

VENUS_API void VeSuspendThread(VeThreadHandle hThread) noexcept;

VENUS_API void VeResumeThread(VeThreadHandle hThread) noexcept;

VENUS_API bool VeIsThreadActive(VeThreadHandle hThread) noexcept;

VENUS_API VeThreadID VeGetLocalThread() noexcept;

VENUS_API void VeSleep(uint32_t u32Millisecond) noexcept;

VENUS_API bool VeThreadEventInit(VeThreadEvent* phEvent, bool bInitState = false) noexcept;

VENUS_API void VeThreadEventTerm(VeThreadEvent* phEvent) noexcept;

VENUS_API void VeThreadEventWait(VeThreadEvent* phEvent) noexcept;

VENUS_API void VeThreadEventWait(VeThreadEvent* phEvent, uint32_t u32Milliseconds) noexcept;

VENUS_API void VeThreadEventSet(VeThreadEvent* phEvent) noexcept;

VENUS_API void VeThreadEventReset(VeThreadEvent* phEvent) noexcept;

VENUS_API void VeThreadInitForSuspend() noexcept;

VENUS_API uint32_t VeThreadHardwareConcurrency() noexcept;

struct VeThreadLocalSingleton;

class VENUS_API VeThread : public VeMemObject
{
	VeNoCopy(VeThread);
public:
	class mutex
	{
		VeNoCopy(mutex);
	public:
		mutex() noexcept
		{
			VeThreadMutexInit(m_hMutex);
		}

		~mutex() noexcept
		{
			VeThreadMutexTerm(m_hMutex);
		}

		void lock() noexcept
		{
			VeThreadMutexLock(m_hMutex);
		}

		void unlock() noexcept
		{
			VeThreadMutexUnlock(m_hMutex);
		}

	private:
		VeThreadMutex m_hMutex;
	};

	class event
	{
		VeNoCopy(event);
	public:
		event() noexcept
		{
			VeThreadEventInit(&m_kEvent, false);
		}

		~event() noexcept
		{
			VeThreadEventTerm(&m_kEvent);
		}

		void wait() noexcept
		{
			VeThreadEventWait(&m_kEvent);
		}

		void wait(uint32_t _Milliseconds) noexcept
		{
			VeThreadEventWait(&m_kEvent, _Milliseconds);
		}

		void set() noexcept
		{
			VeThreadEventSet(&m_kEvent);
		}

		void reset() noexcept
		{
			VeThreadEventReset(&m_kEvent);
		}

	private:
		VeThreadEvent m_kEvent;

	};

	typedef void(*Entry)(void*);

	VeThread(int32_t i32Priority = VE_THREAD_PRIORITY_NORMAL, size_t stStackSize = 32768) noexcept;

	virtual ~VeThread() noexcept;

	inline bool IsRunning() noexcept;

	inline void Start(Entry pfuncEntry, void* pvData) noexcept;

	inline void Restart() noexcept;

	inline void Join() noexcept;

	inline void Suspend() noexcept;

	inline void Resume() noexcept;

	static void Init() noexcept;

	static void Term() noexcept;

	static void InitPerThread() noexcept;

	static void TermPerThread() noexcept;

	static VeThreadLocalSingleton* GetThreadLocalSingleton() noexcept;

private:
	typedef VeThread* ThisPointer;

	struct ThreadParams : VeMemObject
	{
		event m_kEvent;
		event m_kEventLoop;
		VeThread* m_pkThis;
	};	
	
	VeThreadHandle m_hThread;
	ThreadParams* m_pkParams;
	std::atomic<uint32_t> m_u32State;
	Entry m_pfuncEntry = nullptr;
	void* m_pvData = nullptr;
	
	static VeThreadCallbackResult VE_CALLBACK Callback(void* pvParam) noexcept;

};

#include "VeThread.inl"
