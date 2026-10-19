// src/game/UTFSpore_Win32/EAFileStream.cpp -- migrated from slice(s) s00931460 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAFileStream.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/PositionType.h"
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <direct.h>
#include <sys/stat.h>

// ---- items of slice s00931460 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace File { unsigned GetSize(const wchar_t* path); }  // 0x00932060 (defined below; used by a stub's inline body)
struct EAIStream {
    virtual ~EAIStream() {}
    virtual int      AddRef() = 0;
    virtual int      Release() = 0;
    virtual int      GetReferenceCount() = 0;
    virtual int      slot4() = 0;
    virtual unsigned GetState() = 0;
    virtual bool     Close() = 0;
    virtual int      GetSize() = 0;
    virtual bool     SetSize(int size) = 0;
    virtual int      GetPosition(int type) = 0;
    virtual bool     SetPosition(int pos, int type) = 0;
    virtual int      GetAvailable() = 0;
    virtual unsigned Read(void* dst, unsigned size) = 0;
    virtual bool     Flush() = 0;
    virtual bool     Write(const void* src, unsigned size) = 0;
    virtual void     SetPath16(const wchar_t* path) = 0;
    virtual void     SetPath8(const char* path) = 0;
    virtual unsigned GetPath16(wchar_t* dst, unsigned size) = 0;
    virtual unsigned GetPath8(char* dst, unsigned size) = 0;
    virtual bool     Open(unsigned access, int cd, unsigned sharing, unsigned hints) = 0;
};
struct FileStream : public EAIStream {
    HANDLE   mhFile;             // +0x004
    wchar_t  mpPath16[260];      // +0x008
    int      mnRefCount;         // +0x210
    int      mnAccessFlags;      // +0x214
    int      mnCD;               // +0x218
    int      mnSharing;          // +0x21c
    int      mnUsageHints;       // +0x220
    int      mnLastError;        // +0x224
    int      mnSize;             // +0x228  cached size (-1 unknown, -2 'compute lazily')

    FileStream(const char* path);
    FileStream(const wchar_t* path);
    virtual ~FileStream();
    virtual int      AddRef();
    virtual int      Release();
    virtual int      GetReferenceCount();
    virtual int      slot4();
    virtual unsigned GetState();
    virtual bool     Close();
    virtual int      GetSize();
    virtual bool     SetSize(int size);
    virtual int      GetPosition(int type);
    virtual bool     SetPosition(int pos, int type);
    virtual int      GetAvailable();
    virtual unsigned Read(void* dst, unsigned size);
    virtual bool     Flush();
    virtual bool     Write(const void* src, unsigned size);
    virtual void     SetPath16(const wchar_t* path);
    virtual void     SetPath8(const char* path);
    virtual unsigned GetPath16(wchar_t* dst, unsigned size);
    virtual unsigned GetPath8(char* dst, unsigned size);
    virtual bool     Open(unsigned access, int cd, unsigned sharing, unsigned hints);
};
// ---- items of slice s00931460 end

// @ 0x009317e0
void FileStream::SetPath8(const char* path)
{
    if (mhFile == INVALID_HANDLE_VALUE && path)
        MultiByteToWideChar(65001, 0, path, -1, mpPath16, 260);
}

// @ 0x00931810
void FileStream::SetPath16(const wchar_t* path)
{
    if (mhFile == INVALID_HANDLE_VALUE && path)
        wcsncpy(mpPath16, path, 260);
}

// @ 0x00931840
unsigned FileStream::GetPath8(char* dst, unsigned size)
{
    if (dst && size) {
        int n = WideCharToMultiByte(65001, 0, mpPath16, -1, dst, size, 0, 0);
        return n - 1;
    }
    char tmp[260];
    return GetPath8(tmp, 260);
}

// @ 0x009318a0
unsigned FileStream::GetPath16(wchar_t* dst, unsigned size)
{
    if (dst && size) {
        wcsncpy(dst, mpPath16, size);
        dst[size - 1] = 0;
    }
    return (unsigned)wcslen(mpPath16);
}

// @ 0x009318f0
bool FileStream::Open(unsigned access, int cd, unsigned sharing, unsigned hints)
{
    if (mhFile == INVALID_HANDLE_VALUE) {
        if (access) {
            DWORD desired = 0;
            DWORD share = 0;
            DWORD attrs = 0;
            unsigned rd = access & 1;
            if (rd)
                desired = 0x80000000;
            unsigned wr = access & 2;
            if (wr)
                desired |= 0x40000000;
            if (sharing & 1)
                share = 1;
            unsigned sh2 = sharing & 2;
            if (sh2)
                share |= 3;
            if (cd == 6)
                cd = (wr != 0) + 3;
            DWORD disposition;
            switch (cd) {
            case 1: disposition = 1; break;
            case 2: disposition = 2; break;
            case 4: disposition = 4; break;
            case 5: disposition = 5; break;
            default: disposition = 3; break;
            }
            if (hints & 1)
                attrs = 0x8000000;
            else if (hints & 2)
                attrs = 0x10000000;
            mhFile = CreateFileW(mpPath16, desired, share, 0, disposition, attrs, 0);
            if (mhFile == INVALID_HANDLE_VALUE) {
                mnLastError = GetLastError();
                return mhFile != INVALID_HANDLE_VALUE;
            }
            mnAccessFlags = access;
            mnCD = cd;
            mnSharing = sharing;
            mnUsageHints = hints;
            mnLastError = 0;
            bool b;
            if (rd && !wr && !sh2)
                b = true;
            else
                b = false;
            mnSize = (!b) - 2;
        }
    }
    return mhFile != INVALID_HANDLE_VALUE;
}

// @ 0x00931a70
bool FileStream::Close()
{
    if (mhFile != INVALID_HANDLE_VALUE) {
        CloseHandle(mhFile);
        mhFile = INVALID_HANDLE_VALUE;
        mnAccessFlags = 0;
        mnCD = 0;
        mnSharing = 0;
        mnUsageHints = 0;
        mnSize = -1;
    }
    return true;
}

// @ 0x00931ad0
unsigned FileStream::GetState()
{
    switch (mnLastError) {
    case 0:
        return (mhFile != INVALID_HANDLE_VALUE) - 1 & 0xfffffffe;
    case 8:
    case 0xe:
        return 0xcfde0002;
    case 2:
        return 0xcfde0004;
    case 3:
    case 0xf:
        return 0xcfde0005;
    case 5:
        return 0xcfde0006;
    case 0x10:
        return 0xcfde0008;
    case 0x13:
        return 0xcfde0007;
    case 0x15:
        return 0xcfde000b;
    case 0x17:
        return 0xcfde000c;
    default:
        return 0xcfde000d;
    }
}

// @ 0x00931b70
int FileStream::GetSize()
{
    if (mhFile != INVALID_HANDLE_VALUE) {
        int cached = mnSize;
        if (cached != -1 && cached != -2)
            return cached;
        DWORD size = GetFileSize(mhFile, 0);
        if (size != 0xffffffff) {
            if (mnSize != -2)
                return size;
            mnSize = size;
            return size;
        }
        mnLastError = GetLastError();
    }
    return -1;
}

// @ 0x00931bc0
bool FileStream::SetSize(int size)
{
    if (mhFile != INVALID_HANDLE_VALUE) {
        if (SetFilePointer(mhFile, size, 0, 0) != 0xffffffff && SetEndOfFile(mhFile))
            return true;
        mnLastError = GetLastError();
    }
    return false;
}

// @ 0x00931c10
int FileStream::GetPosition(int type)
{
    if (type == 0)
        return SetFilePointer(mhFile, 0, 0, 1);
    if (type == 2) {
        DWORD pos = SetFilePointer(mhFile, 0, 0, 1);
        if (pos != 0xffffffff) {
            int size = GetSize();
            if (size != -1)
                pos -= size;
        }
        return pos;
    }
    return 0;
}

// @ 0x00931c70
bool FileStream::SetPosition(int pos, int type)
{
    if (mhFile != INVALID_HANDLE_VALUE) {
        DWORD method;
        switch (type) {
        case 1: method = 1; break;
        case 2: method = 2; break;
        default: method = 0; break;
        }
        if (SetFilePointer(mhFile, pos, 0, method) != 0xffffffff)
            return true;
        mnLastError = GetLastError();
    }
    return false;
}

// @ 0x00931cd0
unsigned int EA::IO::FileStream::GetAvailable() const
{
    return -GetPosition((EA::IO::PositionType)2);
}

// @ 0x00931ce0
unsigned FileStream::Read(void* dst, unsigned size)
{
    if (mhFile != INVALID_HANDLE_VALUE) {
        if (ReadFile(mhFile, dst, size, (LPDWORD)&size, 0))
            return size;
        mnLastError = GetLastError();
    }
    return 0xffffffff;
}

// @ 0x00931d30
bool FileStream::Write(const void* src, unsigned size)
{
    if (mhFile != INVALID_HANDLE_VALUE) {
        if (WriteFile(mhFile, src, size, (LPDWORD)&size, 0))
            return true;
        mnLastError = GetLastError();
    }
    return false;
}

// @ 0x00931d70
bool FileStream::Flush()
{
    bool ok = false;
    if (mhFile != INVALID_HANDLE_VALUE) {
        ok = FlushFileBuffers(mhFile) != 0;
        if (!ok)
            mnLastError = GetLastError();
    }
    return ok;
}

// @ 0x00931da0
FileStream::FileStream(const char* path)
{
    mhFile = INVALID_HANDLE_VALUE;
    mnRefCount = 0;
    mnAccessFlags = 0;
    mnCD = 0;
    mnSharing = 0;
    mnUsageHints = 0;
    mnLastError = 0;
    mnSize = -1;
    if (path)
        MultiByteToWideChar(65001, 0, path, -1, mpPath16, 260);
}

// @ 0x00931e10
FileStream::FileStream(const wchar_t* path)
{
    mhFile = INVALID_HANDLE_VALUE;
    mnSize = -1;
    mnRefCount = 0;
    mnAccessFlags = 0;
    mnCD = 0;
    mnSharing = 0;
    mnUsageHints = 0;
    mnLastError = 0;
    if (path)
        wcsncpy(mpPath16, path, 260);
}

// @ 0x00931e70
FileStream::~FileStream()
{
    Close();
}
