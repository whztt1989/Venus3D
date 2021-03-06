////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      Vulkan
//  File name:   VulkanRenderer.cpp
//  Created:     2016/07/28 by Albert
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
#ifdef VE_ENABLE_VULKAN
#	if defined(BUILD_PLATFORM_WIN)
#		define VK_USE_PLATFORM_WIN32_KHR
#	elif defined(BUILD_PLATFORM_LINUX)
#		define VK_USE_PLATFORM_XLIB_KHR
#	endif
#	include "vulkan_loader.h"
#endif
#include "VulkanRenderer.h"
#include "VulkanRenderWindow.h"

//--------------------------------------------------------------------------
#ifdef VE_ENABLE_VULKAN
//--------------------------------------------------------------------------
#ifdef THROW
#	undef THROW
#endif
#define THROW(...) VE_THROW("VulkanRenderer Error", __VA_ARGS__)
//--------------------------------------------------------------------------
VK_LOADER_GLOBAL;
//--------------------------------------------------------------------------
VeRTTIImpl(VulkanRenderer);
//--------------------------------------------------------------------------
VulkanRenderer::VulkanRenderer() noexcept
{

}
//--------------------------------------------------------------------------
VulkanRenderer::~VulkanRenderer() noexcept
{

}
//--------------------------------------------------------------------------
void VulkanRenderer::Init()
{
	VK_LOADER_LOAD_ALL(LIB_VULKAN);
	if (!VK_LOADER_HAS_LOADED())
	{
		THROW("Failed to load " LIB_VULKAN ".");
	}

	InitInstance();
	InitDevice();
}
//--------------------------------------------------------------------------
void VulkanRenderer::Term()
{
	for (auto pkWindow : m_kRenderWindowList)
	{
		pkWindow->Term();
	}
	VE_ASSERT(m_kRenderWindowList.empty());

	TermDevice();
	TermInstance();
	VK_LOADER_UNLOAD_ALL();
}
//--------------------------------------------------------------------------
void VulkanRenderer::InitInstance()
{
	uint32_t u32LayerCount;
	if (vkEnumerateInstanceLayerProperties(&u32LayerCount, nullptr) != VK_SUCCESS)
	{
		THROW("Failed to enumerate instance layer properties");
	}
	VeDyanmicStack<VkLayerProperties> kLayers(u32LayerCount);
	if (vkEnumerateInstanceLayerProperties(&u32LayerCount, kLayers) != VK_SUCCESS)
	{
		THROW("Failed to enumerate instance layer properties");
	}
	if (u32LayerCount > 1)
	{
		for (uint32_t i(1); i < u32LayerCount; ++i)
		{
			VeCoreLogI("Ignored layer ", kLayers[i].layerName, ": ", kLayers[i].description);
		}
		u32LayerCount = 1;
	}
	VeDyanmicStack<const char*> kLayerNames(u32LayerCount);
	for (uint32_t i(0); i < u32LayerCount; ++i)
	{
		kLayerNames[i] = kLayers[i].layerName;
	}

	VkApplicationInfo kAppInfo =
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		NULL,
		venus3d.GetInitData().m_pcAppName,
		venus3d.GetInitData().m_u32AppVersion,
		Venus3D::ENGINE_NAME,
		Venus3D::ENGINE_VERSION,
		VK_MAKE_VERSION(1, 0, 2),
	};

	const char* apcExtNames[] =
	{
		VK_KHR_SURFACE_EXTENSION_NAME,
#		if defined(VK_USE_PLATFORM_WIN32_KHR)
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#		endif
	};

	VkInstanceCreateInfo kCreateInfo =
	{
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		NULL,
		0,
		&kAppInfo,
		u32LayerCount,
		kLayerNames,
		sizeof(apcExtNames) / sizeof(const char*),
		apcExtNames
	};
	if (vkCreateInstance(&kCreateInfo, nullptr, &m_hVulkan) != VK_SUCCESS)
	{
		THROW("Failed to create instance");
	}
	VE_ASSERT(m_hVulkan);
}
//--------------------------------------------------------------------------
void VulkanRenderer::TermInstance()
{
	vkDestroyInstance(m_hVulkan, nullptr);
	m_hVulkan = nullptr;
}

//--------------------------------------------------------------------------
void VulkanRenderer::InitDevice()
{
	uint32_t u32GPUCount;
	if (vkEnumeratePhysicalDevices(m_hVulkan, &u32GPUCount, nullptr) != VK_SUCCESS)
	{
		THROW("Failed to enumerate physical devices");
	}
	m_kDeviceList.resize(u32GPUCount);
	VeDyanmicStack<VkPhysicalDevice> kGPUList(u32GPUCount);
	if (vkEnumeratePhysicalDevices(m_hVulkan, &u32GPUCount, kGPUList.data()) != VK_SUCCESS)
	{
		THROW("Failed to enumerate physical devices");
	}
	for (uint32_t i(0); i < u32GPUCount; ++i)
	{
		auto& kDevice = m_kDeviceList[i];
		kDevice.m_hGPU = kGPUList[i];
		uint32_t u32QueueCount;
		vkGetPhysicalDeviceQueueFamilyProperties(kDevice.m_hGPU, &u32QueueCount, nullptr);
		kDevice.m_kQueueList.resize(u32QueueCount);
		vkGetPhysicalDeviceQueueFamilyProperties(kDevice.m_hGPU, &u32QueueCount, kDevice.m_kQueueList.data());

		//VkDeviceCreateInfo deviceCreateInfo = {};

		
	}
}
//--------------------------------------------------------------------------
void VulkanRenderer::TermDevice()
{
	m_kDeviceList.clear();
}
//--------------------------------------------------------------------------
void VulkanRenderer::BeginSyncCopy() noexcept
{

}
//--------------------------------------------------------------------------
void VulkanRenderer::EndSyncCopy() noexcept
{

}
//--------------------------------------------------------------------------
VeRenderWindowPtr VulkanRenderer::CreateRenderWindow(
	const VeWindowPtr& spWindow) noexcept
{
	VulkanRenderWindow* pkRenderWindow = VE_NEW VulkanRenderWindow(spWindow);
	VE_ASSERT(pkRenderWindow);
	pkRenderWindow->Init(*this);
	return pkRenderWindow;
}
//--------------------------------------------------------------------------
VeRendererPtr CreateVulkanRenderer() noexcept
{
	return nullptr;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
