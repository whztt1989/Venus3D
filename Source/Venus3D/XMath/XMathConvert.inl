//-------------------------------------------------------------------------------------
// XMathConvert.inl -- SIMD C++ Math library
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//  
// Copyright (c) Microsoft Corporation. All rights reserved.
//-------------------------------------------------------------------------------------

#pragma once

/****************************************************************************
*
* Data conversion
*
****************************************************************************/

//------------------------------------------------------------------------------

#ifdef _MSC_VER
#	pragma warning(push)
#	pragma warning(disable:4701)
//	C4701: false positives
#endif

inline XMVECTOR XM_CALLCONV XMConvertVectorIntToFloat
(
	FXMVECTOR    VInt,
	uint32_t     DivExponent
)
{
	assert(DivExponent < 32);
#if defined(_XM_NO_INTRINSICS_)
	float fScale = 1.0f / (float)(1U << DivExponent);
	uint32_t ElementIndex = 0;
	XMVECTOR Result;
	do {
		int32_t iTemp = (int32_t)VInt.vector4_u32[ElementIndex];
		Result.vector4_f32[ElementIndex] = ((float)iTemp) * fScale;
	} while (++ElementIndex < 4);
	return Result;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float fScale = 1.0f / (float)(1U << DivExponent);
	float32x4_t vResult = vcvtq_f32_s32(VInt);
	return vmulq_n_f32(vResult, fScale);
#else // _XM_SSE_INTRINSICS_
	// Convert to floats
	XMVECTOR vResult = _mm_cvtepi32_ps(_mm_castps_si128(VInt));
	// Convert DivExponent into 1.0f/(1<<DivExponent)
	uint32_t uScale = 0x3F800000U - (DivExponent << 23);
	// Splat the scalar value
	__m128i vScale = _mm_set1_epi32(uScale);
	vResult = _mm_mul_ps(vResult, _mm_castsi128_ps(vScale));
	return vResult;
#endif
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMConvertVectorFloatToInt
(
	FXMVECTOR    VFloat,
	uint32_t     MulExponent
)
{
	assert(MulExponent < 32);
#if defined(_XM_NO_INTRINSICS_)
	// Get the scalar factor.
	float fScale = (float)(1U << MulExponent);
	uint32_t ElementIndex = 0;
	XMVECTOR Result;
	do {
		int32_t iResult;
		float fTemp = VFloat.vector4_f32[ElementIndex] * fScale;
		if (fTemp <= -(65536.0f*32768.0f)) {
			iResult = (-0x7FFFFFFF) - 1;
		}
		else if (fTemp > (65536.0f*32768.0f) - 128.0f) {
			iResult = 0x7FFFFFFF;
		}
		else {
			iResult = (int32_t)fTemp;
		}
		Result.vector4_u32[ElementIndex] = (uint32_t)iResult;
	} while (++ElementIndex < 4);
	return Result;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float32x4_t vResult = vmulq_n_f32(VFloat, (float)(1U << MulExponent));
	// In case of positive overflow, detect it
	uint32x4_t vOverflow = vcgtq_f32(vResult, g_XMMaxInt);
	// Float to int conversion
	int32x4_t vResulti = vcvtq_s32_f32(vResult);
	// If there was positive overflow, set to 0x7FFFFFFF
	vResult = vandq_u32(vOverflow, g_XMAbsMask);
	vOverflow = vbicq_u32(vResulti, vOverflow);
	vOverflow = vorrq_u32(vOverflow, vResult);
	return vOverflow;
#else // _XM_SSE_INTRINSICS_
	XMVECTOR vResult = _mm_set_ps1((float)(1U << MulExponent));
	vResult = _mm_mul_ps(vResult, VFloat);
	// In case of positive overflow, detect it
	XMVECTOR vOverflow = _mm_cmpgt_ps(vResult, g_XMMaxInt);
	// Float to int conversion
	__m128i vResulti = _mm_cvttps_epi32(vResult);
	// If there was positive overflow, set to 0x7FFFFFFF
	vResult = _mm_and_ps(vOverflow, g_XMAbsMask);
	vOverflow = _mm_andnot_ps(vOverflow, _mm_castsi128_ps(vResulti));
	vOverflow = _mm_or_ps(vOverflow, vResult);
	return vOverflow;
#endif
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMConvertVectorUIntToFloat
(
	FXMVECTOR     VUInt,
	uint32_t      DivExponent
)
{
	assert(DivExponent < 32);
#if defined(_XM_NO_INTRINSICS_)
	float fScale = 1.0f / (float)(1U << DivExponent);
	uint32_t ElementIndex = 0;
	XMVECTOR Result;
	do {
		Result.vector4_f32[ElementIndex] = (float)VUInt.vector4_u32[ElementIndex] * fScale;
	} while (++ElementIndex < 4);
	return Result;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float fScale = 1.0f / (float)(1U << DivExponent);
	float32x4_t vResult = vcvtq_f32_u32(VUInt);
	return vmulq_n_f32(vResult, fScale);
#else // _XM_SSE_INTRINSICS_
	// For the values that are higher than 0x7FFFFFFF, a fixup is needed
	// Determine which ones need the fix.
	XMVECTOR vMask = _mm_and_ps(VUInt, g_XMNegativeZero);
	// Force all values positive
	XMVECTOR vResult = _mm_xor_ps(VUInt, vMask);
	// Convert to floats
	vResult = _mm_cvtepi32_ps(_mm_castps_si128(vResult));
	// Convert 0x80000000 -> 0xFFFFFFFF
	__m128i iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);
	// For only the ones that are too big, add the fixup
	vMask = _mm_and_ps(_mm_castsi128_ps(iMask), g_XMFixUnsigned);
	vResult = _mm_add_ps(vResult, vMask);
	// Convert DivExponent into 1.0f/(1<<DivExponent)
	uint32_t uScale = 0x3F800000U - (DivExponent << 23);
	// Splat
	iMask = _mm_set1_epi32(uScale);
	vResult = _mm_mul_ps(vResult, _mm_castsi128_ps(iMask));
	return vResult;
#endif
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMConvertVectorFloatToUInt
(
	FXMVECTOR     VFloat,
	uint32_t      MulExponent
)
{
	assert(MulExponent < 32);
#if defined(_XM_NO_INTRINSICS_)
	// Get the scalar factor.
	float fScale = (float)(1U << MulExponent);
	uint32_t ElementIndex = 0;
	XMVECTOR Result;
	do {
		uint32_t uResult;
		float fTemp = VFloat.vector4_f32[ElementIndex] * fScale;
		if (fTemp <= 0.0f) {
			uResult = 0;
		}
		else if (fTemp >= (65536.0f*65536.0f)) {
			uResult = 0xFFFFFFFFU;
		}
		else {
			uResult = (uint32_t)fTemp;
		}
		Result.vector4_u32[ElementIndex] = uResult;
	} while (++ElementIndex < 4);
	return Result;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float32x4_t vResult = vmulq_n_f32(VFloat, (float)(1U << MulExponent));
	// In case of overflow, detect it
	uint32x4_t vOverflow = vcgtq_f32(vResult, g_XMMaxUInt);
	// Float to int conversion
	uint32x4_t vResulti = vcvtq_u32_f32(vResult);
	// If there was overflow, set to 0xFFFFFFFFU
	vResult = vbicq_u32(vResulti, vOverflow);
	vOverflow = vorrq_u32(vOverflow, vResult);
	return vOverflow;
#else // _XM_SSE_INTRINSICS_
	XMVECTOR vResult = _mm_set_ps1(static_cast<float>(1U << MulExponent));
	vResult = _mm_mul_ps(vResult, VFloat);
	// Clamp to >=0
	vResult = _mm_max_ps(vResult, g_XMZero);
	// Any numbers that are too big, set to 0xFFFFFFFFU
	XMVECTOR vOverflow = _mm_cmpgt_ps(vResult, g_XMMaxUInt);
	XMVECTOR vValue = g_XMUnsignedFix;
	// Too large for a signed integer?
	XMVECTOR vMask = _mm_cmpge_ps(vResult, vValue);
	// Zero for number's lower than 0x80000000, 32768.0f*65536.0f otherwise
	vValue = _mm_and_ps(vValue, vMask);
	// Perform fixup only on numbers too large (Keeps low bit precision)
	vResult = _mm_sub_ps(vResult, vValue);
	__m128i vResulti = _mm_cvttps_epi32(vResult);
	// Convert from signed to unsigned pnly if greater than 0x80000000
	vMask = _mm_and_ps(vMask, g_XMNegativeZero);
	vResult = _mm_xor_ps(_mm_castsi128_ps(vResulti), vMask);
	// On those that are too large, set to 0xFFFFFFFF
	vResult = _mm_or_ps(vResult, vOverflow);
	return vResult;
#endif
}

#ifdef _MSC_VER
#	pragma warning(pop)
#endif

/****************************************************************************
*
* Vector and matrix load operations
*
****************************************************************************/

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadInt(const uint32_t* pSource)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_u32[0] = *pSource;
	V.vector4_u32[1] = 0;
	V.vector4_u32[2] = 0;
	V.vector4_u32[3] = 0;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	uint32x4_t zero = vdupq_n_u32(0);
	return vld1q_lane_u32(pSource, zero, 0);
#elif defined(_XM_SSE_INTRINSICS_)
	return _mm_load_ss(reinterpret_cast<const float*>(pSource));
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadFloat(const float* pSource)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = *pSource;
	V.vector4_f32[1] = 0.f;
	V.vector4_f32[2] = 0.f;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float32x4_t zero = vdupq_n_f32(0);
	return vld1q_lane_f32(pSource, zero, 0);
#elif defined(_XM_SSE_INTRINSICS_)
	return _mm_load_ss(pSource);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadInt2
(
	const uint32_t* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_u32[0] = pSource[0];
	V.vector4_u32[1] = pSource[1];
	V.vector4_u32[2] = 0;
	V.vector4_u32[3] = 0;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	uint32x2_t x = vld1_u32(pSource);
	uint32x2_t zero = vdup_n_u32(0);
	return vcombine_u32(x, zero);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(reinterpret_cast<const float*>(pSource));
	__m128 y = _mm_load_ss(reinterpret_cast<const float*>(pSource + 1));
	return _mm_unpacklo_ps(x, y);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadInt2A
(
	const uint32_t* pSource
)
{
	assert(pSource);
	assert(((uintptr_t)pSource & 0xF) == 0);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_u32[0] = pSource[0];
	V.vector4_u32[1] = pSource[1];
	V.vector4_u32[2] = 0;
	V.vector4_u32[3] = 0;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	uint32x2_t x = vld1_u32_ex(pSource, 64);
	uint32x2_t zero = vdup_n_u32(0);
	return vcombine_u32(x, zero);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128i V = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(pSource));
	return _mm_castsi128_ps(V);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadFloat2
(
	const XMFLOAT2* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = pSource->x;
	V.vector4_f32[1] = pSource->y;
	V.vector4_f32[2] = 0.f;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float32x2_t x = vld1_f32(reinterpret_cast<const float*>(pSource));
	float32x2_t zero = vdup_n_f32(0);
	return vcombine_f32(x, zero);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(&pSource->x);
	__m128 y = _mm_load_ss(&pSource->y);
	return _mm_unpacklo_ps(x, y);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadFloat2A
(
	const XMFLOAT2A* pSource
)
{
	assert(pSource);
	assert(((uintptr_t)pSource & 0xF) == 0);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = pSource->x;
	V.vector4_f32[1] = pSource->y;
	V.vector4_f32[2] = 0.f;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float32x2_t x = vld1_f32_ex(reinterpret_cast<const float*>(pSource), 64);
	float32x2_t zero = vdup_n_f32(0);
	return vcombine_f32(x, zero);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128i V = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(pSource));
	return _mm_castsi128_ps(V);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadSInt2
(
	const XMINT2* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = (float)pSource->x;
	V.vector4_f32[1] = (float)pSource->y;
	V.vector4_f32[2] = 0.f;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	int32x2_t x = vld1_s32(reinterpret_cast<const int32_t*>(pSource));
	float32x2_t v = vcvt_f32_s32(x);
	float32x2_t zero = vdup_n_f32(0);
	return vcombine_f32(v, zero);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(reinterpret_cast<const float*>(&pSource->x));
	__m128 y = _mm_load_ss(reinterpret_cast<const float*>(&pSource->y));
	__m128 V = _mm_unpacklo_ps(x, y);
	return _mm_cvtepi32_ps(_mm_castps_si128(V));
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadUInt2
(
	const XMUINT2* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = (float)pSource->x;
	V.vector4_f32[1] = (float)pSource->y;
	V.vector4_f32[2] = 0.f;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	uint32x2_t x = vld1_u32(reinterpret_cast<const uint32_t*>(pSource));
	float32x2_t v = vcvt_f32_u32(x);
	float32x2_t zero = vdup_n_f32(0);
	return vcombine_f32(v, zero);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(reinterpret_cast<const float*>(&pSource->x));
	__m128 y = _mm_load_ss(reinterpret_cast<const float*>(&pSource->y));
	__m128 V = _mm_unpacklo_ps(x, y);
	// For the values that are higher than 0x7FFFFFFF, a fixup is needed
	// Determine which ones need the fix.
	XMVECTOR vMask = _mm_and_ps(V, g_XMNegativeZero);
	// Force all values positive
	XMVECTOR vResult = _mm_xor_ps(V, vMask);
	// Convert to floats
	vResult = _mm_cvtepi32_ps(_mm_castps_si128(vResult));
	// Convert 0x80000000 -> 0xFFFFFFFF
	__m128i iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);
	// For only the ones that are too big, add the fixup
	vMask = _mm_and_ps(_mm_castsi128_ps(iMask), g_XMFixUnsigned);
	vResult = _mm_add_ps(vResult, vMask);
	return vResult;
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadInt3
(
	const uint32_t* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_u32[0] = pSource[0];
	V.vector4_u32[1] = pSource[1];
	V.vector4_u32[2] = pSource[2];
	V.vector4_u32[3] = 0;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	uint32x2_t x = vld1_u32(pSource);
	uint32x2_t zero = vdup_n_u32(0);
	uint32x2_t y = vld1_lane_u32(pSource + 2, zero, 0);
	return vcombine_u32(x, y);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(reinterpret_cast<const float*>(pSource));
	__m128 y = _mm_load_ss(reinterpret_cast<const float*>(pSource + 1));
	__m128 z = _mm_load_ss(reinterpret_cast<const float*>(pSource + 2));
	__m128 xy = _mm_unpacklo_ps(x, y);
	return _mm_movelh_ps(xy, z);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadInt3A
(
	const uint32_t* pSource
)
{
	assert(pSource);
	assert(((uintptr_t)pSource & 0xF) == 0);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_u32[0] = pSource[0];
	V.vector4_u32[1] = pSource[1];
	V.vector4_u32[2] = pSource[2];
	V.vector4_u32[3] = 0;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	// Reads an extra integer which is zero'd
	uint32x4_t V = vld1q_u32_ex(pSource, 128);
	return vsetq_lane_u32(0, V, 3);
#elif defined(_XM_SSE_INTRINSICS_)
	// Reads an extra integer which is zero'd
	__m128i V = _mm_load_si128(reinterpret_cast<const __m128i*>(pSource));
	V = _mm_and_si128(V, g_XMMask3);
	return _mm_castsi128_ps(V);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadFloat3
(
	const XMFLOAT3* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = pSource->x;
	V.vector4_f32[1] = pSource->y;
	V.vector4_f32[2] = pSource->z;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	float32x2_t x = vld1_f32(reinterpret_cast<const float*>(pSource));
	float32x2_t zero = vdup_n_f32(0);
	float32x2_t y = vld1_lane_f32(reinterpret_cast<const float*>(pSource) + 2, zero, 0);
	return vcombine_f32(x, y);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(&pSource->x);
	__m128 y = _mm_load_ss(&pSource->y);
	__m128 z = _mm_load_ss(&pSource->z);
	__m128 xy = _mm_unpacklo_ps(x, y);
	return _mm_movelh_ps(xy, z);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadFloat3A
(
	const XMFLOAT3A* pSource
)
{
	assert(pSource);
	assert(((uintptr_t)pSource & 0xF) == 0);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = pSource->x;
	V.vector4_f32[1] = pSource->y;
	V.vector4_f32[2] = pSource->z;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	// Reads an extra float which is zero'd
	float32x4_t V = vld1q_f32_ex(reinterpret_cast<const float*>(pSource), 128);
	return vsetq_lane_f32(0, V, 3);
#elif defined(_XM_SSE_INTRINSICS_)
	// Reads an extra float which is zero'd
	__m128 V = _mm_load_ps(&pSource->x);
	return _mm_and_ps(V, g_XMMask3);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadSInt3
(
	const XMINT3* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)

	XMVECTOR V;
	V.vector4_f32[0] = (float)pSource->x;
	V.vector4_f32[1] = (float)pSource->y;
	V.vector4_f32[2] = (float)pSource->z;
	V.vector4_f32[3] = 0.f;
	return V;

#elif defined(_XM_ARM_NEON_INTRINSICS_)
	int32x2_t x = vld1_s32(reinterpret_cast<const int32_t*>(pSource));
	int32x2_t zero = vdup_n_s32(0);
	int32x2_t y = vld1_lane_s32(reinterpret_cast<const int32_t*>(pSource) + 2, zero, 0);
	int32x4_t v = vcombine_s32(x, y);
	return vcvtq_f32_s32(v);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(reinterpret_cast<const float*>(&pSource->x));
	__m128 y = _mm_load_ss(reinterpret_cast<const float*>(&pSource->y));
	__m128 z = _mm_load_ss(reinterpret_cast<const float*>(&pSource->z));
	__m128 xy = _mm_unpacklo_ps(x, y);
	__m128 V = _mm_movelh_ps(xy, z);
	return _mm_cvtepi32_ps(_mm_castps_si128(V));
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadUInt3
(
	const XMUINT3* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = (float)pSource->x;
	V.vector4_f32[1] = (float)pSource->y;
	V.vector4_f32[2] = (float)pSource->z;
	V.vector4_f32[3] = 0.f;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	uint32x2_t x = vld1_u32(reinterpret_cast<const uint32_t*>(pSource));
	uint32x2_t zero = vdup_n_u32(0);
	uint32x2_t y = vld1_lane_u32(reinterpret_cast<const uint32_t*>(pSource) + 2, zero, 0);
	uint32x4_t v = vcombine_u32(x, y);
	return vcvtq_f32_u32(v);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(reinterpret_cast<const float*>(&pSource->x));
	__m128 y = _mm_load_ss(reinterpret_cast<const float*>(&pSource->y));
	__m128 z = _mm_load_ss(reinterpret_cast<const float*>(&pSource->z));
	__m128 xy = _mm_unpacklo_ps(x, y);
	__m128 V = _mm_movelh_ps(xy, z);
	// For the values that are higher than 0x7FFFFFFF, a fixup is needed
	// Determine which ones need the fix.
	XMVECTOR vMask = _mm_and_ps(V, g_XMNegativeZero);
	// Force all values positive
	XMVECTOR vResult = _mm_xor_ps(V, vMask);
	// Convert to floats
	vResult = _mm_cvtepi32_ps(_mm_castps_si128(vResult));
	// Convert 0x80000000 -> 0xFFFFFFFF
	__m128i iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);
	// For only the ones that are too big, add the fixup
	vMask = _mm_and_ps(_mm_castsi128_ps(iMask), g_XMFixUnsigned);
	vResult = _mm_add_ps(vResult, vMask);
	return vResult;
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadInt4
(
	const uint32_t* pSource
)
{
	assert(pSource);

#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_u32[0] = pSource[0];
	V.vector4_u32[1] = pSource[1];
	V.vector4_u32[2] = pSource[2];
	V.vector4_u32[3] = pSource[3];
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	return vld1q_u32(pSource);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128i V = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pSource));
	return _mm_castsi128_ps(V);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadInt4A
(
	const uint32_t* pSource
)
{
	assert(pSource);
	assert(((uintptr_t)pSource & 0xF) == 0);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_u32[0] = pSource[0];
	V.vector4_u32[1] = pSource[1];
	V.vector4_u32[2] = pSource[2];
	V.vector4_u32[3] = pSource[3];
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	return vld1q_u32_ex(pSource, 128);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128i V = _mm_load_si128(reinterpret_cast<const __m128i*>(pSource));
	return _mm_castsi128_ps(V);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadFloat4
(
	const XMFLOAT4* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = pSource->x;
	V.vector4_f32[1] = pSource->y;
	V.vector4_f32[2] = pSource->z;
	V.vector4_f32[3] = pSource->w;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	return vld1q_f32(reinterpret_cast<const float*>(pSource));
#elif defined(_XM_SSE_INTRINSICS_)
	return _mm_loadu_ps(&pSource->x);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadFloat4A
(
	const XMFLOAT4A* pSource
)
{
	assert(pSource);
	assert(((uintptr_t)pSource & 0xF) == 0);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = pSource->x;
	V.vector4_f32[1] = pSource->y;
	V.vector4_f32[2] = pSource->z;
	V.vector4_f32[3] = pSource->w;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	return vld1q_f32_ex(reinterpret_cast<const float*>(pSource), 128);
#elif defined(_XM_SSE_INTRINSICS_)
	return _mm_load_ps(&pSource->x);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadSInt4
(
	const XMINT4* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)

	XMVECTOR V;
	V.vector4_f32[0] = (float)pSource->x;
	V.vector4_f32[1] = (float)pSource->y;
	V.vector4_f32[2] = (float)pSource->z;
	V.vector4_f32[3] = (float)pSource->w;
	return V;

#elif defined(_XM_ARM_NEON_INTRINSICS_)
	int32x4_t v = vld1q_s32(reinterpret_cast<const int32_t*>(pSource));
	return vcvtq_f32_s32(v);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128i V = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pSource));
	return _mm_cvtepi32_ps(V);
#endif
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline XMVECTOR XM_CALLCONV XMLoadUInt4
(
	const XMUINT4* pSource
)
{
	assert(pSource);
#if defined(_XM_NO_INTRINSICS_)
	XMVECTOR V;
	V.vector4_f32[0] = (float)pSource->x;
	V.vector4_f32[1] = (float)pSource->y;
	V.vector4_f32[2] = (float)pSource->z;
	V.vector4_f32[3] = (float)pSource->w;
	return V;
#elif defined(_XM_ARM_NEON_INTRINSICS_)
	uint32x4_t v = vld1q_u32(reinterpret_cast<const uint32_t*>(pSource));
	return vcvtq_f32_u32(v);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128i V = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pSource));
	// For the values that are higher than 0x7FFFFFFF, a fixup is needed
	// Determine which ones need the fix.
	XMVECTOR vMask = _mm_and_ps(_mm_castsi128_ps(V), g_XMNegativeZero);
	// Force all values positive
	XMVECTOR vResult = _mm_xor_ps(_mm_castsi128_ps(V), vMask);
	// Convert to floats
	vResult = _mm_cvtepi32_ps(_mm_castps_si128(vResult));
	// Convert 0x80000000 -> 0xFFFFFFFF
	__m128i iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);
	// For only the ones that are too big, add the fixup
	vMask = _mm_and_ps(_mm_castsi128_ps(iMask), g_XMFixUnsigned);
	vResult = _mm_add_ps(vResult, vMask);
	return vResult;
#endif
}



