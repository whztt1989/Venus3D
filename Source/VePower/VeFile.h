////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  Module:      VePower
//  File name:   VeFile.h
//  Created:     2015/03/10 by Napoleon
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VE_PLATFORM_WIN
#	define VeGetCwd _getcwd
#	define VeChDir _chdir
#	define VeMkDir _mkdir
#	define VeRmDir _rmdir
#	define VeAccess _access
#else
#	define VeGetCwd getcwd
#	define VeChDir chdir
#	define VeMkDir(name) mkdir(name,S_IRWXU)
#	define VeRmDir rmdir
#	define VeAccess access
#endif

#define VE_A_NORMAL 0x00
#define VE_A_RDONLY 0x01
#define VE_A_HIDDEN 0x02
#define VE_A_SYSTEM 0x04
#define VE_A_SUBDIR 0x10
#define VE_A_ARCH   0x20

class VE_POWER_API VeFileIStream : public VeBinaryIStream
{
	VeNoCopy(VeFileIStream);
	VeRTTIDecl(VeFileIStream, VeBinaryIStream);
public:
	VeFileIStream(const VeChar8* pcFileName,
		VeSizeT stCache = 32768) noexcept;

	virtual ~VeFileIStream() noexcept;

	virtual VeSizeT Read(void* pvBuffer, VeSizeT stBytes) noexcept;

	virtual VeResult Seek(VePtrDiff pdOffset, VeWhence eWhence) noexcept;

	virtual VeSizeT Tell() noexcept;

	virtual void* Skip(VeSizeT stBytes) noexcept;

	virtual void Restart() noexcept;

	virtual VeSizeT RemainingLength() const noexcept;

	virtual VeChar8 Peek() noexcept;

	virtual void Finish() noexcept;

	void CacheReload() noexcept;

private:
	void UpdateLenth() noexcept;

	bool IsCached() noexcept;

	VeSizeT Cached() noexcept;

	const VeSizeT m_stCacheSize;
	FILE* m_pkFile = nullptr;
	VeByte* m_pbyCache = nullptr;
	VeSizeT m_stFileSize = 0;
	VeSizeT m_stPointer = 0;
	VeSizeT m_stCachePointer = 0;
	VeSizeT m_stCacheUse = 0;

};

VeSmartPointer(VeFileIStream);

class VE_POWER_API VeFileOStream : public VeBinaryOStream
{
	VeNoCopy(VeFileOStream);
	VeRTTIDecl(VeFileOStream, VeBinaryOStream);
public:
	VeFileOStream(const VeChar8* pcFileName,VeSizeT stCache = 32768,
		bool bAppend = false) noexcept;

	virtual ~VeFileOStream() noexcept;

	virtual VeSizeT Write(const void* pvBuffer, VeSizeT stBytes) noexcept;

	virtual VeSizeT Size() const noexcept;

private:
	bool HasCacheUse() noexcept;

	VeSizeT CacheUse() noexcept;

	VeSizeT CacheCanUse() noexcept;

	VeByte* Cache() noexcept;

	void WriteBackCache() noexcept;
	
	const VeSizeT m_stCacheSize;
	FILE* m_pkFile = nullptr;
	VeByte* m_pbyCache = nullptr;
	VeSizeT m_stFileSize = 0;
	VeSizeT m_stCachePointer = 0;

};

VeSmartPointer(VeFileOStream);

class VE_POWER_API VeFilePath : public VeDirectory
{
	VeNoCopy(VeFilePath);
	VeRTTIDecl(VeFilePath, VeDirectory);
public:
	class VE_POWER_API ReadTask : public VeRefObject
	{
		VeNoCopy(ReadTask);
	public:
		ReadTask(const VeChar8* pcFullPath,
			ReadCallback kCallback) noexcept;

	protected:
		VeRefNode<VeRefObject*> m_kNode;
		VeFixedString m_kFullPath;		
		ReadCallback m_kCallback;
		VeMemoryIStreamPtr m_spData;

	};

	class VE_POWER_API WriteTask : public VeRefObject
	{
		VeNoCopy(WriteTask);
	public:
		WriteTask(const VeChar8* pcFullPath,
			const VeMemoryOStreamPtr& spContent,
			WriteCallback kCallback, bool bAppend) noexcept;

	protected:
		VeRefNode<VeRefObject*> m_kNode;
		VeFixedString m_kFullPath;
		VeMemoryOStreamPtr m_spData;		
		WriteCallback m_kCallback;
		VeResult m_eResult;

	};

	struct PathInfo
	{
		VeSizeT m_stAttrib;
		VeTimeT m_stLastModTime;
	};

	VeFilePath(const VeChar8* pcPath = "") noexcept;

	virtual ~VeFilePath() noexcept;

	static inline const VeChar8* GetTypeName() noexcept;

	virtual const VeChar8* GetType() noexcept override;

	virtual const VeChar8* GetName() noexcept override;

	virtual bool Access(VeUInt32 u32Flag) const noexcept override;

	virtual bool HasFile(const VeChar8* pcFile) const noexcept override;

	virtual bool HasSubDir(const VeChar8* pcDir) const noexcept override;

	virtual void FindFileList(const VeChar8* pcDesc,
		VeVector<VeFixedString>& kOut) const noexcept override;

	virtual VeDirectoryPtr Open(const VeChar8* pcPath,
		bool bTryCreate = true) const noexcept override;

	virtual VeBinaryIStreamPtr OpenIStream(
		const VeChar8* pcFile) const noexcept override;

	virtual VeBinaryOStreamPtr OpenOStream(
		const VeChar8* pcFile) const noexcept override;

	virtual void ReadAsync(const VeChar8* pcFile,
		ReadCallback kCallback) const noexcept override;

	virtual void WriteAsync(const VeChar8* pcFile,
		const VeMemoryOStreamPtr& spContent, WriteCallback kCallback,
		bool bAppend = false) const noexcept override;

	static bool TestPath(const VeChar8* pcPath, PathInfo& kOutput) noexcept;

	static bool CreatePath(const VeChar8* pcPath) noexcept;

	static VeDirectoryPtr Create(const VeChar8* pcPath,
		bool bTryCreate = true) noexcept;

	static VeBinaryIStreamPtr CreateIStream(const VeChar8* pcPath) noexcept;

	static VeBinaryOStreamPtr CreateOStream(const VeChar8* pcPath) noexcept;

private:
	VeFixedString m_kPath;

};

VeSmartPointer(VeFilePath);

#include "VeFile.inl"
