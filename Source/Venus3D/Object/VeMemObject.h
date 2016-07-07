////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      Object
//  File name:   VeMemObject.h
//  Created:     2016/07/08 by Albert
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

class VENUS_API VeMemObject
{
public:

#ifdef VE_MEM_DEBUG

	static void* operator new (size_t stSize, const char* pcSourceFile, int32_t i32SourceLine, const char* pcFunction) noexcept;

	static void* operator new[](size_t stSize, const char* pcSourceFile, int32_t i32SourceLine, const char* pcFunction) noexcept;

	static void operator delete (void* pvMem, const char* pcSourceFile, int32_t i32SourceLine, const char* pcFunction) noexcept;

	static void operator delete[](void* pvMem, const char* pcSourceFile, int32_t i32SourceLine, const char* pcFunction) noexcept;

	static void PushDeleteCallParams(const char* pcSourceFile, int32_t i32SourceLine, const char* pcFunction) noexcept;

	static void PopDeleteCallParams() noexcept;

#endif

	static void* operator new (size_t stSize) noexcept;

	static void* operator new[](size_t stSize) noexcept;

	static void* operator new (size_t stSize, void* pvMemory) noexcept;

	static void operator delete (void* pvMem) noexcept;

	static void operator delete[](void* pvMem) noexcept;

};