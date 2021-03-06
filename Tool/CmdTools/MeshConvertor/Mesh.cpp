////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      MeshConvertor
//  File name:   Mesh.cpp
//  Created:     2016/08/07 by Albert
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

#include "Mesh.h"

//--------------------------------------------------------------------------
using namespace std;
using namespace DirectX;
//--------------------------------------------------------------------------
void Mesh::Clear() noexcept
{
	m_kName = "";
	m_stFaces = 0;
	m_stVerts = 0;
	m_kIndices.clear();
	m_kAttributes.clear();
	m_kRepeat.clear();
	m_kAdjacency.clear();
	m_kPosition.clear();
	m_kNormals.clear();
	m_kTangent.clear();
	m_kTexcoords.clear();
	m_kColors.clear();
}
//--------------------------------------------------------------------------
void Mesh::Process(float fEpsilon) noexcept
{
	GenerateAdj(fEpsilon);
	ValidateRepeats(fEpsilon);
	RemoveDuplicates(fEpsilon);
	CleanMesh();
	Optimize();
	ComputeTangent();
}
//--------------------------------------------------------------------------
void Mesh::GenerateAdj(float fEpsilon) noexcept
{
	m_kRepeat.resize(m_stVerts);
	m_kAdjacency.resize(m_stVerts);
	VE_ASSERT_ALWAYS(SUCCEEDED(GenerateAdjacencyAndPointReps(
		m_kIndices.data(), m_stFaces, m_kPosition.data(), m_stVerts,
		fEpsilon, m_kRepeat.data(), m_kAdjacency.data())));
}
//--------------------------------------------------------------------------
void Mesh::ValidateRepeats(float fEpsilon) noexcept
{
	for (uint32_t i(0); i < m_kRepeat.size(); ++i)
	{
		if (m_kRepeat[i] == i) continue;

		if (!EqualVertexInSamePosition(i, m_kRepeat[i]))
		{
			m_kRepeat[i] = i;
		}
	}
}
//--------------------------------------------------------------------------
void Mesh::RemoveDuplicates(float fEpsilon) noexcept
{
	std::vector<uint32_t> kIndexRemap(m_kRepeat.size());
	uint32_t idx(0);
	for (uint32_t i(0); i < m_kRepeat.size(); ++i)
	{
		if (m_kRepeat[i] == i)
		{
			kIndexRemap[i] = idx;
			m_kPosition[idx] = m_kPosition[i];
			for (auto& v : m_kNormals)
			{
				v[idx] = v[i];
			}
			for (auto& v : m_kTexcoords)
			{
				v[idx] = v[i];
			}
			for (auto& v : m_kColors)
			{
				v[idx] = v[i];
			}
			++idx;
		}
		else
		{
			VE_ASSERT_ALWAYS(m_kRepeat[i] < i);
			kIndexRemap[i] = kIndexRemap[m_kRepeat[i]];
		}
	}
	m_stVerts = idx;
	m_kPosition.resize(m_stVerts);
	for (auto& v : m_kNormals)
	{
		v.resize(m_stVerts);
	}
	for (auto& v : m_kTexcoords)
	{
		v.resize(m_stVerts);
	}
	for (auto& v : m_kColors)
	{
		v.resize(m_stVerts);
	}
	for (uint32_t i(0); i < m_kIndices.size(); ++i)
	{
		m_kIndices[i] = kIndexRemap[m_kIndices[i]];
	}
	GenerateAdj(fEpsilon);
}
//--------------------------------------------------------------------------
void Mesh::CleanMesh() noexcept
{
	std::vector<uint32_t> dups;
	VE_ASSERT_ALWAYS(SUCCEEDED(Clean(m_kIndices.data(),
		m_stFaces, m_stVerts, m_kAdjacency.data(),
		m_kAttributes.size() ? m_kAttributes.data() : nullptr, dups)));

	if (dups.empty()) return;

	size_t nNewVerts = m_stVerts + dups.size();

	m_kPosition.resize(nNewVerts);
	for (auto& v : m_kNormals)
	{
		v.resize(nNewVerts);
	}
	for (auto& v : m_kTexcoords)
	{
		v.resize(nNewVerts);
	}
	for (auto& v : m_kColors)
	{
		v.resize(nNewVerts);
	}
	
	size_t j = m_stVerts;
	for (auto it = dups.begin(); it != dups.end() && (j < nNewVerts); ++it, ++j)
	{
		VE_ASSERT_ALWAYS(*it < m_stVerts);

		m_kPosition[j] = m_kPosition[*it];
		for (auto& v : m_kNormals)
		{
			v[j] = v[*it];
		}
		for (auto& v : m_kTexcoords)
		{
			v[j] = v[*it];
		}
		for (auto& v : m_kColors)
		{
			v[j] = v[*it];
		}
	}

	m_stVerts = nNewVerts;
}
//--------------------------------------------------------------------------
void Mesh::Optimize(uint32_t vertexCache, uint32_t restart) noexcept
{
	{
		std::vector<uint32_t> remap(m_stFaces);
		if (m_kAttributes.size() == m_stFaces)
		{
			// Note that Clean handles vertex splits due to reuse between attributes
			VE_ASSERT_ALWAYS(SUCCEEDED(AttributeSort(m_stFaces,
				m_kAttributes.data(), remap.data())));

			VE_ASSERT_ALWAYS(SUCCEEDED(ReorderIBAndAdjacency(m_kIndices.data(),
				m_stFaces, m_kAdjacency.data(), remap.data())));

			// Optimize faces for pre-transform vertex cache
			VE_ASSERT_ALWAYS(SUCCEEDED(OptimizeFacesEx(m_kIndices.data(),
				m_stFaces, m_kAdjacency.data(), m_kAttributes.data(),
				remap.data(), vertexCache, restart)));
		}
		else
		{
			// Optimize faces for pre-transform vertex cache
			VE_ASSERT_ALWAYS(SUCCEEDED(OptimizeFaces(m_kIndices.data(),
				m_stFaces, m_kAdjacency.data(), remap.data(),
				vertexCache, restart)));
		}

		VE_ASSERT_ALWAYS(SUCCEEDED(ReorderIBAndAdjacency(m_kIndices.data(),
			m_stFaces, m_kAdjacency.data(), remap.data())));
	}

	// Optimize vertices for post-transform vertex cache
	std::vector<uint32_t> remap(m_stVerts);
	VE_ASSERT_ALWAYS(SUCCEEDED(OptimizeVertices(m_kIndices.data(),
		m_stFaces, m_stVerts, remap.data())));
	
	VE_ASSERT_ALWAYS(SUCCEEDED(FinalizeIB(m_kIndices.data(), m_stFaces,
		remap.data(), m_stVerts)));

	VE_ASSERT_ALWAYS(SUCCEEDED(FinalizeVB(m_kPosition.data(),
		sizeof(XMFLOAT3), m_stVerts, remap.data())));

	for (auto& v : m_kNormals)
	{
		VE_ASSERT_ALWAYS(SUCCEEDED(FinalizeVB(v.data(),
			sizeof(XMFLOAT3), m_stVerts, remap.data())));
	}
	for (auto& v : m_kTexcoords)
	{
		VE_ASSERT_ALWAYS(SUCCEEDED(FinalizeVB(v.data(),
			sizeof(XMFLOAT2), m_stVerts, remap.data())));
	}
	for (auto& v : m_kColors)
	{
		VE_ASSERT_ALWAYS(SUCCEEDED(FinalizeVB(v.data(),
			sizeof(XMFLOAT4), m_stVerts, remap.data())));
	}
}
//--------------------------------------------------------------------------
void Mesh::ComputeTangent() noexcept
{
	if (m_kNormals.size() && m_kTexcoords.size())
	{
		m_kTangent.resize(m_stVerts);
		VE_ASSERT_ALWAYS(SUCCEEDED(ComputeTangentFrame(m_kIndices.data(),
			m_stFaces, m_kPosition.data(), m_kNormals[0].data(),
			m_kTexcoords[0].data(), m_stVerts, m_kTangent.data())));
	}
}
//--------------------------------------------------------------------------
void Mesh::Save(const VeDirectoryPtr& spDest) noexcept
{
	VeMemOStream kOutput;
	kOutput << VE_MAKE_FOURCC('V', 'G', 'E', 'O');
	kOutput << uint32_t(m_stVerts);
	VE_ASSERT_ALWAYS(m_kPosition.size() == m_stVerts);
	kOutput << uint32_t(1 + m_kNormals.size() + (m_kTangent.size() ? 1 : 0)
		+ m_kTexcoords.size() + m_kColors.size());

	kOutput << uint8_t(VE_SN_POSITION);
	kOutput << uint8_t(0);
	kOutput << uint8_t(VE_PF_R32G32B32_FLOAT);
	uint8_t u8Stride = sizeof(XMFLOAT3);
	kOutput << u8Stride;
	kOutput.write(m_kPosition.data(), u8Stride * m_stVerts);

	for (size_t i(0); i < m_kNormals.size(); ++i)
	{
		kOutput << uint8_t(VE_SN_NORMAL);
		kOutput << uint8_t(i);
		kOutput << uint8_t(VE_PF_R32G32B32_FLOAT);
		u8Stride = sizeof(XMFLOAT3);
		kOutput << u8Stride;
		VE_ASSERT_ALWAYS(m_kNormals[i].size() == m_stVerts);
		kOutput.write(m_kNormals[i].data(), u8Stride * m_stVerts);
	}

	if (m_kTangent.size() == m_stVerts)
	{
		kOutput << uint8_t(VE_SN_TANGENT);
		kOutput << uint8_t(0);
		kOutput << uint8_t(VE_PF_R32G32B32A32_FLOAT);
		u8Stride = sizeof(XMFLOAT4);
		kOutput << u8Stride;
		VE_ASSERT_ALWAYS(m_kTangent.size() == m_stVerts);
		kOutput.write(m_kTangent.data(), u8Stride * m_stVerts);
	}

	for (size_t i(0); i < m_kTexcoords.size(); ++i)
	{
		kOutput << uint8_t(VE_SN_TEXCOORD);
		kOutput << uint8_t(i);
		kOutput << uint8_t(VE_PF_R32G32_FLOAT);
		u8Stride = sizeof(XMFLOAT2);
		kOutput << u8Stride;
		VE_ASSERT_ALWAYS(m_kTexcoords[i].size() == m_stVerts);
		kOutput.write(m_kTexcoords[i].data(), u8Stride * m_stVerts);
	}
	
	for (size_t i(0); i < m_kColors.size(); ++i)
	{
		kOutput << uint8_t(VE_SN_COLOR);
		kOutput << uint8_t(i);
		kOutput << uint8_t(VE_PF_R32G32B32A32_FLOAT);
		u8Stride = sizeof(XMFLOAT4);
		kOutput << u8Stride;
		VE_ASSERT_ALWAYS(m_kColors[i].size() == m_stVerts);
		kOutput.write(m_kColors[i].data(), u8Stride * m_stVerts);
	}

	VE_ASSERT_ALWAYS(m_kIndices.size() == m_stFaces * 3);
	bool bHalfIndex = m_stVerts <= 0xFFFF;
	u8Stride = uint8_t(bHalfIndex ? sizeof(uint16_t) : sizeof(uint32_t));
	kOutput << u8Stride;
	kOutput << uint8_t(VE_PT_TRIANGLELIST);
	std::vector<uint32_t> kSubGeometries;
	{
		uint32_t cnt(0);
		int32_t idx(-1);
		for (auto a : m_kAttributes)
		{
			if (a == idx)
			{
				++cnt;
			}
			else
			{
				VE_ASSERT_ALWAYS(int32_t(a) > idx);
				if(cnt) kSubGeometries.push_back(cnt);
				idx = a;
				cnt = 1;
			}
			
		}
		if (cnt) kSubGeometries.push_back(cnt);
	}
	
	kOutput << uint16_t(kSubGeometries.size());
	for (auto c : kSubGeometries)
	{
		kOutput << uint32_t(c);
	}
	
	if (bHalfIndex)
	{
		for (auto idx : m_kIndices)
		{
			kOutput << uint16_t(idx);
		}
	}
	else
	{
		for (auto idx : m_kIndices)
		{
			kOutput << uint32_t(idx);
		}
	}

	char acBuffer[VE_MAX_PATH_LEN];
	VeSprintf(acBuffer, "%s.vgf", m_kName.c_str());
	auto spArch = spDest->OpenArchive(acBuffer,
		VE_ARCH_OPEN_CREATE | VE_ARCH_OPEN_WRITE);
	VE_ASSERT_ALWAYS(spArch->Write(kOutput.data(), kOutput.size()) == kOutput.size());
}
//--------------------------------------------------------------------------
bool Mesh::EqualVertexInSamePosition(uint32_t u32First,
	uint32_t u32Second, float fEpsilon) noexcept
{
	XMFLOAT4 epsi(fEpsilon, fEpsilon, fEpsilon, fEpsilon);
	auto e = XMLoadFloat4(&epsi);
	for (auto& v : m_kNormals)
	{
		auto v1 = XMLoadFloat3(&v[u32First]);
		auto v2 = XMLoadFloat3(&v[u32Second]);
		if (!XMVector3NearEqual(v1, v2, e)) return false;
	}
	for (auto& v : m_kTexcoords)
	{
		auto v1 = XMLoadFloat2(&v[u32First]);
		auto v2 = XMLoadFloat2(&v[u32Second]);
		if (!XMVector2NearEqual(v1, v2, e)) return false;
	}
	for (auto& v : m_kColors)
	{
		auto v1 = XMLoadFloat4(&v[u32First]);
		auto v2 = XMLoadFloat4(&v[u32Second]);
		if (!XMVector4NearEqual(v1, v2, e)) return false;
	}
	return true;
}
//--------------------------------------------------------------------------
