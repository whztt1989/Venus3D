//-------------------------------------------------------------------------------------
// XMath.h -- SIMD C++ Math library
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//  
// Copyright (c) Microsoft Corporation. All rights reserved.
//-------------------------------------------------------------------------------------

#pragma once

#ifndef __cplusplus
#error DirectX Math requires C++
#endif

#define DIRECTX_MATH_VERSION 309

#if defined(_MSC_VER) && (_MSC_VER < 1800)
#error DirectX Math Visual C++ 2013 or later.
#endif

#define _XM_VECTORCALL_ 1

#ifdef _MSC_VER
#	if _XM_VECTORCALL_
#		define XM_CALLCONV __vectorcall
#	else
#		define XM_CALLCONV __fastcall
#	endif
#else
#	if _XM_VECTORCALL_
#		define XM_CALLCONV __attribute__((vectorcall))
#	else
#		define XM_CALLCONV __attribute__((fastcall))
#	endif
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1800)
#define XM_CTOR_DEFAULT {}
#else
#define XM_CTOR_DEFAULT =default;
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define XM_CONSTEXPR
#else
#define XM_CONSTEXPR constexpr
#endif

#ifndef XM_DEPRECATED
#define XM_DEPRECATED __declspec(deprecated("This is deprecated and will be removed in a future version."))
#endif

#if !defined(_XM_F16C_INTRINSICS_) && defined(__AVX2__) && !defined(_XM_NO_INTRINSICS_)
#define _XM_F16C_INTRINSICS_
#endif

#if defined(_XM_F16C_INTRINSICS_) && !defined(_XM_AVX_INTRINSICS_)
#define _XM_AVX_INTRINSICS_
#endif

#if !defined(_XM_AVX_INTRINSICS_) && defined(__AVX__) && !defined(_XM_NO_INTRINSICS_)
#define _XM_AVX_INTRINSICS_
#endif

#if defined(_XM_AVX_INTRINSICS_) && !defined(_XM_SSE4_INTRINSICS_)
#define _XM_SSE4_INTRINSICS_
#endif

#if defined(_XM_SSE4_INTRINSICS_) && !defined(_XM_SSE3_INTRINSICS_)
#define _XM_SSE3_INTRINSICS_
#endif

#if defined(_XM_SSE3_INTRINSICS_) && !defined(_XM_SSE_INTRINSICS_)
#define _XM_SSE_INTRINSICS_
#endif

#if !defined(_XM_ARM_NEON_INTRINSICS_) && !defined(_XM_SSE_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
#if defined(_M_IX86) || defined(_M_X64)
#define _XM_SSE_INTRINSICS_
#elif defined(_M_ARM) || defined(_M_ARM64)
#define _XM_ARM_NEON_INTRINSICS_
#elif !defined(_XM_NO_INTRINSICS_)
#error X Math does not support this target
#endif
#endif // !_XM_ARM_NEON_INTRINSICS_ && !_XM_SSE_INTRINSICS_ && !_XM_NO_INTRINSICS_

// C4514/4820: Off by default noise
#include <math.h>
#include <float.h>
#ifndef __APPLE__
#	include <malloc.h>
#endif

#ifndef _XM_NO_INTRINSICS_
#ifdef _MSC_VER
#	include <intrin.h>
#endif

#ifdef _XM_SSE_INTRINSICS_
#include <xmmintrin.h>
#include <emmintrin.h>

#ifdef _XM_SSE3_INTRINSICS_
#include <pmmintrin.h>
#endif

#ifdef _XM_SSE4_INTRINSICS_
#include <smmintrin.h>
#endif

#ifdef _XM_AVX_INTRINSICS_
#include <immintrin.h>
#endif

#elif defined(_XM_ARM_NEON_INTRINSICS_)
#ifdef _M_ARM64
#include <arm64_neon.h>
#else
#include <arm_neon.h>
#endif
#endif
#endif // !_XM_NO_INTRINSICS_

#include <assert.h>

#ifndef _XM_NO_ROUNDF_
#ifdef _MSC_VER
#include <yvals.h>
#if defined(_CPPLIB_VER) && ( _CPPLIB_VER < 610 )
#define _XM_NO_ROUNDF_
#endif
#endif
#endif

// C4005/4668: Old header issue
#include <stdint.h>

/****************************************************************************
*
* Conditional intrinsics
*
****************************************************************************/

#if defined(_XM_SSE_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)

#if defined(_XM_NO_MOVNT_)
#define XM_STREAM_PS( p, a ) _mm_store_ps( p, a )
#define XM_SFENCE()
#else
#define XM_STREAM_PS( p, a ) _mm_stream_ps( p, a )
#define XM_SFENCE() _mm_sfence()
#endif

#if defined(_XM_AVX_INTRINSICS_)
#define XM_PERMUTE_PS( v, c ) _mm_permute_ps( v, c )
#else
#define XM_PERMUTE_PS( v, c ) _mm_shuffle_ps( v, v, c )
#endif

#endif // _XM_SSE_INTRINSICS_ && !_XM_NO_INTRINSICS_

/****************************************************************************
*
* Constant definitions
*
****************************************************************************/

constexpr float XM_PI = 3.141592654f;
constexpr float XM_2PI = 6.283185307f;
constexpr float XM_1DIVPI = 0.318309886f;
constexpr float XM_1DIV2PI = 0.159154943f;
constexpr float XM_PIDIV2 = 1.570796327f;
constexpr float XM_PIDIV4 = 0.785398163f;

constexpr uint32_t XM_SELECT_0 = 0x00000000;
constexpr uint32_t XM_SELECT_1 = 0xFFFFFFFF;

constexpr uint32_t XM_PERMUTE_0X = 0;
constexpr uint32_t XM_PERMUTE_0Y = 1;
constexpr uint32_t XM_PERMUTE_0Z = 2;
constexpr uint32_t XM_PERMUTE_0W = 3;
constexpr uint32_t XM_PERMUTE_1X = 4;
constexpr uint32_t XM_PERMUTE_1Y = 5;
constexpr uint32_t XM_PERMUTE_1Z = 6;
constexpr uint32_t XM_PERMUTE_1W = 7;

constexpr uint32_t XM_SWIZZLE_X = 0;
constexpr uint32_t XM_SWIZZLE_Y = 1;
constexpr uint32_t XM_SWIZZLE_Z = 2;
constexpr uint32_t XM_SWIZZLE_W = 3;

constexpr uint32_t XM_CRMASK_CR6 = 0x000000F0;
constexpr uint32_t XM_CRMASK_CR6TRUE = 0x00000080;
constexpr uint32_t XM_CRMASK_CR6FALSE = 0x00000020;
constexpr uint32_t XM_CRMASK_CR6BOUNDS = XM_CRMASK_CR6FALSE;

constexpr size_t XM_CACHE_LINE_SIZE = 64;

/****************************************************************************
*
* Macros
*
****************************************************************************/

// Unit conversion

inline XM_CONSTEXPR float XMConvertToRadians(float fDegrees) { return fDegrees * (XM_PI / 180.0f); }
inline XM_CONSTEXPR float XMConvertToDegrees(float fRadians) { return fRadians * (180.0f / XM_PI); }

// Condition register evaluation proceeding a recording (R) comparison

inline bool XMComparisonAllTrue(uint32_t CR) { return (((CR)& XM_CRMASK_CR6TRUE) == XM_CRMASK_CR6TRUE); }
inline bool XMComparisonAnyTrue(uint32_t CR) { return (((CR)& XM_CRMASK_CR6FALSE) != XM_CRMASK_CR6FALSE); }
inline bool XMComparisonAllFalse(uint32_t CR) { return (((CR)& XM_CRMASK_CR6FALSE) == XM_CRMASK_CR6FALSE); }
inline bool XMComparisonAnyFalse(uint32_t CR) { return (((CR)& XM_CRMASK_CR6TRUE) != XM_CRMASK_CR6TRUE); }
inline bool XMComparisonMixed(uint32_t CR) { return (((CR)& XM_CRMASK_CR6) == 0); }
inline bool XMComparisonAllInBounds(uint32_t CR) { return (((CR)& XM_CRMASK_CR6BOUNDS) == XM_CRMASK_CR6BOUNDS); }
inline bool XMComparisonAnyOutOfBounds(uint32_t CR) { return (((CR)& XM_CRMASK_CR6BOUNDS) != XM_CRMASK_CR6BOUNDS); }

/****************************************************************************
*
* Data types
*
****************************************************************************/

//------------------------------------------------------------------------------
#if defined(_XM_NO_INTRINSICS_)
struct __vector4
{
	union
	{
		float       vector4_f32[4];
		uint32_t    vector4_u32[4];
	};
};
#endif // _XM_NO_INTRINSICS_

//------------------------------------------------------------------------------
// Vector intrinsic: Four 32 bit floating point components aligned on a 16 byte 
// boundary and mapped to hardware vector registers
#if defined(_XM_SSE_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
typedef __m128 XMVECTOR;
#elif defined(_XM_ARM_NEON_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
typedef float32x4_t XMVECTOR;
#else
typedef __vector4 XMVECTOR;
#endif

// Fix-up for (1st-3rd) XMVECTOR parameters that are pass-in-register for x86, ARM, ARM64, and vector call; by reference otherwise
#if ( defined(_M_IX86) || defined(_M_ARM) || defined(_M_ARM64) || defined(__ARM_ARCH) || _XM_VECTORCALL_ ) && !defined(_XM_NO_INTRINSICS_)
typedef const XMVECTOR FXMVECTOR;
#else
typedef const XMVECTOR& FXMVECTOR;
#endif

// Fix-up for (4th) XMVECTOR parameter to pass in-register for ARM, ARM64, and x64 vector call; by reference otherwise
#if ( defined(_M_ARM) || defined(_M_ARM64) || defined(__ARM_ARCH) || (_XM_VECTORCALL_ && !defined(_M_IX86) ) ) && !defined(_XM_NO_INTRINSICS_)
typedef const XMVECTOR GXMVECTOR;
#else
typedef const XMVECTOR& GXMVECTOR;
#endif

// Fix-up for (5th & 6th) XMVECTOR parameter to pass in-register for ARM64 and vector call; by reference otherwise
#if ( defined(_M_ARM64) || _XM_VECTORCALL_ ) && !defined(_XM_NO_INTRINSICS_)
typedef const XMVECTOR HXMVECTOR;
#else
typedef const XMVECTOR& HXMVECTOR;
#endif

// Fix-up for (7th+) XMVECTOR parameters to pass by reference
typedef const XMVECTOR& CXMVECTOR;

//------------------------------------------------------------------------------
// Conversion types for constants
struct alignas(16) XMVECTORF32
{
	union
	{
		float f[4];
		XMVECTOR v;
	};

	inline operator XMVECTOR() const { return v; }
	inline operator const float*() const { return f; }
#if !defined(_XM_NO_INTRINSICS_) && defined(_XM_SSE_INTRINSICS_)
	inline operator __m128i() const { return _mm_castps_si128(v); }
	inline operator __m128d() const { return _mm_castps_pd(v); }
#endif
};

struct alignas(16) XMVECTORI32
{
	union
	{
		int32_t i[4];
		XMVECTOR v;
	};

	inline operator XMVECTOR() const { return v; }
#if !defined(_XM_NO_INTRINSICS_) && defined(_XM_SSE_INTRINSICS_)
	inline operator __m128i() const { return _mm_castps_si128(v); }
	inline operator __m128d() const { return _mm_castps_pd(v); }
#endif
};

struct alignas(16) XMVECTORU8
{
	union
	{
		uint8_t u[16];
		XMVECTOR v;
	};

	inline operator XMVECTOR() const { return v; }
#if !defined(_XM_NO_INTRINSICS_) && defined(_XM_SSE_INTRINSICS_)
	inline operator __m128i() const { return _mm_castps_si128(v); }
	inline operator __m128d() const { return _mm_castps_pd(v); }
#endif
};

struct alignas(16) XMVECTORU32
{
	union
	{
		uint32_t u[4];
		XMVECTOR v;
	};

	inline operator XMVECTOR() const { return v; }
#if !defined(_XM_NO_INTRINSICS_) && defined(_XM_SSE_INTRINSICS_)
	inline operator __m128i() const { return _mm_castps_si128(v); }
	inline operator __m128d() const { return _mm_castps_pd(v); }
#endif
};

//------------------------------------------------------------------------------
// Vector operators
/*XMVECTOR    XM_CALLCONV     operator+ (FXMVECTOR V);
XMVECTOR    XM_CALLCONV     operator- (FXMVECTOR V);

XMVECTOR&   XM_CALLCONV     operator+= (XMVECTOR& V1, FXMVECTOR V2);
XMVECTOR&   XM_CALLCONV     operator-= (XMVECTOR& V1, FXMVECTOR V2);
XMVECTOR&   XM_CALLCONV     operator*= (XMVECTOR& V1, FXMVECTOR V2);
XMVECTOR&   XM_CALLCONV     operator/= (XMVECTOR& V1, FXMVECTOR V2);

XMVECTOR&   operator*= (XMVECTOR& V, float S);
XMVECTOR&   operator/= (XMVECTOR& V, float S);

XMVECTOR    XM_CALLCONV     operator+ (FXMVECTOR V1, FXMVECTOR V2);
XMVECTOR    XM_CALLCONV     operator- (FXMVECTOR V1, FXMVECTOR V2);
XMVECTOR    XM_CALLCONV     operator* (FXMVECTOR V1, FXMVECTOR V2);
XMVECTOR    XM_CALLCONV     operator/ (FXMVECTOR V1, FXMVECTOR V2);
XMVECTOR    XM_CALLCONV     operator* (FXMVECTOR V, float S);
XMVECTOR    XM_CALLCONV     operator* (float S, FXMVECTOR V);
XMVECTOR    XM_CALLCONV     operator/ (FXMVECTOR V, float S);*/

//------------------------------------------------------------------------------
// Matrix type: Sixteen 32 bit floating point components aligned on a
// 16 byte boundary and mapped to four hardware vector registers

struct XMMATRIX;

// Fix-up for (1st) XMMATRIX parameter to pass in-register for ARM64 and vector call; by reference otherwise
#if ( defined(_M_ARM64) || _XM_VECTORCALL_ ) && !defined(_XM_NO_INTRINSICS_)
typedef const XMMATRIX FXMMATRIX;
#else
typedef const XMMATRIX& FXMMATRIX;
#endif

// Fix-up for (2nd+) XMMATRIX parameters to pass by reference
typedef const XMMATRIX& CXMMATRIX;

#ifdef _XM_NO_INTRINSICS_
struct XMMATRIX
#else
struct alignas(16) XMMATRIX
#endif
{
#ifdef _XM_NO_INTRINSICS_
	union
	{
		XMVECTOR c[4];
		struct
		{
			float _11, _21, _31, _41;
			float _12, _22, _32, _42;
			float _13, _23, _33, _43;
			float _14, _24, _34, _44;
		};
		float m[4][4];
	};
#else
	XMVECTOR c[4];
#endif

	XMMATRIX() XM_CTOR_DEFAULT
#if defined(_MSC_VER) && _MSC_VER >= 1900
		constexpr XMMATRIX(FXMVECTOR C0, FXMVECTOR C1, FXMVECTOR C2, CXMVECTOR C3) : c{ C0,C1,C2,C3 } {}
#else
		XMMATRIX(FXMVECTOR C0, FXMVECTOR C1, FXMVECTOR C2, CXMVECTOR C3) { c[0] = C0; c[1] = C1; c[2] = C2; c[3] = C3; }
#endif
	XMMATRIX(float m00, float m10, float m20, float m30,
		float m01, float m11, float m21, float m31,
		float m02, float m12, float m22, float m32,
		float m03, float m13, float m23, float m33);
	explicit XMMATRIX(const float *pArray);

#ifdef _XM_NO_INTRINSICS_
	float       operator() (size_t Row, size_t Column) const { return m[Column][Row]; }
	float&      operator() (size_t Row, size_t Column) { return m[Column][Row]; }
#endif

	XMMATRIX&   operator= (const XMMATRIX& M) { c[0] = M.c[0]; c[1] = M.c[1]; c[2] = M.c[2]; c[3] = M.c[3]; return *this; }

	XMMATRIX    operator+ () const { return *this; }
	XMMATRIX    operator- () const;

	XMMATRIX&   XM_CALLCONV     operator+= (FXMMATRIX M);
	XMMATRIX&   XM_CALLCONV     operator-= (FXMMATRIX M);
	XMMATRIX&   XM_CALLCONV     operator*= (FXMMATRIX M);
	XMMATRIX&   operator*= (float S);
	XMMATRIX&   operator/= (float S);

	XMMATRIX    XM_CALLCONV     operator+ (FXMMATRIX M) const;
	XMMATRIX    XM_CALLCONV     operator- (FXMMATRIX M) const;
	XMMATRIX    XM_CALLCONV     operator* (FXMMATRIX M) const;
	XMMATRIX    operator* (float S) const;
	XMMATRIX    operator/ (float S) const;

	friend XMMATRIX     XM_CALLCONV     operator* (float S, FXMMATRIX M);
};
