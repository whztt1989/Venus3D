////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  Module:      VePower
//  File name:   VeSystem.cpp
//  Created:     2015/03/03 by Napoleon
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPch.h"

//--------------------------------------------------------------------------
extern VeVideoDevicePtr CreateVideoDevice() noexcept;
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_KEYBOARD
extern VeKeyboardPtr CreateKeyboard() noexcept;
#endif
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_MOUSE
extern VeMousePtr CreateMouse() noexcept;
#endif
//--------------------------------------------------------------------------
static const VeChar8* s_apcLogTypeNames[VeLog::TYPE_MAX] =
{
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR"
};
//--------------------------------------------------------------------------
static void OutputDebug(VeLog::Type eType, const VeChar8* pcTag,
	const VeChar8* pcText) noexcept
{
#ifdef VE_PLATFORM_ANDROID

	const android_LogPriority aeLogTypeMap[VeLog::TYPE_MAX] =
	{
		ANDROID_LOG_DEBUG,
		ANDROID_LOG_INFO,
		ANDROID_LOG_WARN,
		ANDROID_LOG_ERROR
	};
	__android_log_print(aeLogTypeMap[eType], pcTag, "%s", pcText);

#else

#	ifdef VE_PLATFORM_WIN
	VeChar8 acLogBuffer[VE_LOG_BUFFER_SIZE + 64];
	VeSprintf(acLogBuffer, "%s,%s: %s\n", s_apcLogTypeNames[eType], pcTag, pcText);
	OutputDebugStringA(acLogBuffer);
#	else
	printf("%s,%s: %s\n", s_apcLogTypeNames[eType], pcTag, pcText);
#	endif

#endif
}
//--------------------------------------------------------------------------
static void OutputConsole(VeLog::Type eType, const VeChar8* pcTag,
	const VeChar8* pcText) noexcept
{
#ifdef VE_PLATFORM_ANDROID

	const android_LogPriority aeLogTypeMap[VeLog::TYPE_MAX] =
	{
		ANDROID_LOG_DEBUG,
		ANDROID_LOG_INFO,
		ANDROID_LOG_WARN,
		ANDROID_LOG_ERROR
	};
	__android_log_print(aeLogTypeMap[eType], pcTag, "%s", pcText);

#else

	printf("%s,%s: %s\n", s_apcLogTypeNames[eType], pcTag, pcText);

#endif
}
//--------------------------------------------------------------------------
static void OutputLuaDebug(VeLog::Type eType, const VeChar8* pcTag,
	const VeChar8* pcText) noexcept
{
	VeChar8 acLogBuffer[VE_LOG_BUFFER_SIZE + 64];
	VeSprintf(acLogBuffer, "%s,%s: %s", s_apcLogTypeNames[eType], pcTag, pcText);
	if (ve_lua)
	{
		venus::call_function("print", acLogBuffer);
	}
}
//--------------------------------------------------------------------------
VeSystem::VeSystem(Type eType, const VeChar8* pcPakName) noexcept
	: m_eType(eType), m_kPakName(pcPakName), CORE("Venus3D", m_kLog)
	, USER(m_kPakName, m_kLog)
{
	switch (eType)
	{
	case TYPE_DEFAULT:
		m_kLog.SetTarget(&OutputDebug);
		break;
	case TYPE_CONSOLE:
		m_kLog.SetTarget(&OutputConsole);
		break;
	case TYPE_LUA_DEBUG:
		m_kLog.SetTarget(&OutputLuaDebug);
		break;
	default:
		break;
	}
	m_spLua = VE_NEW VeLua();
	m_spMainStack = VE_NEW VeStackAllocator(VE_STACK_SIZE);
}
//--------------------------------------------------------------------------
VeSystem::~VeSystem() noexcept
{
	for (auto obj : m_kObjCollector)
	{
		obj->DecRefCount();
	}
	m_spMainStack = nullptr;
	m_spLua = nullptr;
}
//--------------------------------------------------------------------------
const VePoolAllocatorPtr& VeSystem::GetPoolAllocator(
	VeSizeT stUnitSize) noexcept
{
	stUnitSize = (stUnitSize + 0xF) & (~0xF);
	VePoolAllocatorPtr& spRes = m_kAllocatorMap[stUnitSize];
	if (!spRes)
	{
		spRes = VE_NEW VePoolAllocator(stUnitSize);
	}
	return spRes;
}
//--------------------------------------------------------------------------
void VeSystem::Init() noexcept
{
	InitEventQueue();
	InitVideo();
	InitInputSystem();
}
//--------------------------------------------------------------------------
void VeSystem::Term() noexcept
{
	TermInputSystem();
	TermVideo();
	TermEventQueue();
}
//--------------------------------------------------------------------------
void VeSystem::InitTime() noexcept
{
	m_spTime = VE_NEW VeTime();
}
//--------------------------------------------------------------------------
void VeSystem::TermTime() noexcept
{
	m_spTime = nullptr;
}
//--------------------------------------------------------------------------
void VeSystem::InitEventQueue() noexcept
{
	m_spEventQueue = VE_NEW VeEventQueue();
	m_spEventQueue->Init();
}
//--------------------------------------------------------------------------
void VeSystem::TermEventQueue() noexcept
{
	m_spEventQueue->Term();
	m_spEventQueue = nullptr;
}
//--------------------------------------------------------------------------
void VeSystem::InitVideo() noexcept
{
	if (!m_spVideo)
	{
		m_spVideo = CreateVideoDevice();
		VE_ASSERT(m_spVideo);
		m_spVideo->Init();
	}
}
//--------------------------------------------------------------------------
void VeSystem::TermVideo() noexcept
{
	if (m_spVideo)
	{
		m_spVideo->Term();
		m_spVideo = nullptr;
	}
}
//--------------------------------------------------------------------------
void VeSystem::InitInputSystem() noexcept
{
#	ifdef VE_ENABLE_KEYBOARD
	if (!m_spKeyboard)
	{
		m_spKeyboard = CreateKeyboard();
		VE_ASSERT(m_spKeyboard);
		m_spKeyboard->Init();
	}
#	endif
#	ifdef VE_ENABLE_MOUSE
	if (!m_spMouse)
	{
		m_spMouse = CreateMouse();
		VE_ASSERT(m_spMouse);
		m_spMouse->Init();
	}
#	endif
}
//--------------------------------------------------------------------------
void VeSystem::TermInputSystem() noexcept
{
#	ifdef VE_ENABLE_KEYBOARD
	if (m_spKeyboard)
	{
		m_spKeyboard->Term();
		m_spKeyboard = nullptr;
	}
#	endif
#	ifdef VE_ENABLE_MOUSE
	if (m_spMouse)
	{
		m_spMouse->Term();
		m_spMouse = nullptr;
	}
#	endif
}
//--------------------------------------------------------------------------
