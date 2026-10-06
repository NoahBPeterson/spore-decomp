// Slice s00931460: EA::IO::FileStream (Win32 file stream), EA::IO::File / Directory helpers and the
// path-validity check that precedes them (MSVC 2008 SP1, /O2 /GS- without exception tables).
#include "types.h"
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <direct.h>
#include <sys/stat.h>

// ---------------------------------------------------------------------------------------------
// eastl::fixed_string<wchar_t, 260> as laid out in the original (pointers, allocator pad, buffer)
// ---------------------------------------------------------------------------------------------
struct FixedPathString {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAllocPad;    // +0x0c
    wchar_t* mpFixed;      // +0x10  the in-object buffer
    wchar_t  mBuffer[260]; // +0x14

    FixedPathString() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 260;
        mpFixed = mBuffer;
        mBuffer[0] = 0;
    }
    void assign(const wchar_t* b, const wchar_t* e);           // 0x0088c3d0
    void make_lower();                                         // 0x005e8e80
    void erase(unsigned pos, unsigned n);                      // 0x008e3a70
    void DeallocateSelf() {
        wchar_t* b = mpBegin;
        if ((int)((int)mpCapacity - (int)b & 0xfffffffeU) > 2 && b && b != mpFixed)
            operator delete[](b);
    }
};
bool operator==(const FixedPathString& s, const wchar_t* p);   // 0x006ab760
wchar_t* PathSearch(wchar_t* first, wchar_t* last, const wchar_t* first2, const wchar_t* last2);  // 0x00930ba0
extern const wchar_t* kTempPathPrefix[23];  // 0x0154e028
extern const wchar_t kReservedSubstring[];   // 0x0143e664

static inline unsigned CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p)
        ++p;
    return (unsigned)(p - s);
}

static __forceinline int StrLenDo(const wchar_t* s) { return (int)wcslen(s); }

// @ 0x00931460  path-name validity check (mode 2..5 additionally rejects reserved device prefixes)
bool __cdecl CheckPathName(const wchar_t* name, int mode) {
    FixedPathString s1;
    s1.assign(name, name + CharStrlen(name));
    unsigned len = (unsigned)(s1.mpEnd - s1.mpBegin);
    if (len > 0x100) {
        s1.DeallocateSelf();
        return true;
    }
    for (unsigned i = 0; i < len; ++i) {
        wchar_t c = s1.mpBegin[i];
        if (c == '<' || c == '>' || c == ':' || c == '\\' || c == '/' || c == '"' || c == '|' || c == '*' || c == '?') {
            s1.DeallocateSelf();
            return false;
        }
    }
    if (mode == 2 || mode == 3 || mode == 4 || mode == 5) {
        FixedPathString s2;
        s2.assign(s1.mpBegin, s1.mpEnd);
        s2.make_lower();
        if (s2.mpEnd - s2.mpBegin != 0) {
            for (wchar_t* p = s2.mpBegin; p != s2.mpEnd; ++p) {
                if (*p == '.') {
                    if (p != s2.mpEnd) {
                        unsigned idx = (unsigned)(p - s2.mpBegin);
                        if (idx != (unsigned)-1)
                            s2.erase(idx, (unsigned)-1);
                    }
                    break;
                }
            }
        }
        for (unsigned i = 0; i < 0x5c; i += 4) {
            if (s2 == *(const wchar_t**)((char*)kTempPathPrefix + i)) {
                s2.DeallocateSelf();
                s1.DeallocateSelf();
                return false;
            }
        }
        s2.DeallocateSelf();
    }
    wchar_t* b = s1.mpBegin;
    wchar_t* e = s1.mpEnd;
    wchar_t* hit = PathSearch(b, e, kReservedSubstring, kReservedSubstring + CharStrlen(kReservedSubstring));
    if (hit != e && (hit - b) != -1) {
        s1.DeallocateSelf();
        return true;
    }
    s1.DeallocateSelf();
    return false;
}

// @ 0x00931770  ensure a trailing '\\' on a wide string (returns true if one was appended)
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void push_back(wchar_t c);   // 0x004f6510
};
bool EnsureTrailingBackslash(WString* s) {
    wchar_t* b = s->mpBegin;
    if (b != s->mpEnd) {
        unsigned c = b[(s->mpEnd - b) - 1];
        if (c == '\\' || c == '/' || c == ':')
            return false;
    }
    s->push_back('\\');
    return true;
}

// ---------------------------------------------------------------------------------------------
// EA::IO::EAIStream / FileStream
// ---------------------------------------------------------------------------------------------
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

// @ 0x009317c0  Release (reference count at +0x210; destroys through the deleting destructor)
int FileStream::Release() {
    if (mnRefCount > 1)
        return --mnRefCount;
    delete this;
    return 0;
}

// @ 0x009317e0  SetPath(const char*)  (UTF-8, only while closed)
void FileStream::SetPath8(const char* path) {
    if (mhFile == INVALID_HANDLE_VALUE && path)
        MultiByteToWideChar(65001, 0, path, -1, mpPath16, 260);
}

// @ 0x00931810  SetPath(const wchar_t*)
void FileStream::SetPath16(const wchar_t* path) {
    if (mhFile == INVALID_HANDLE_VALUE && path)
        wcsncpy(mpPath16, path, 260);
}

// @ 0x00931840  GetPath(char*, size)  (UTF-8)
unsigned FileStream::GetPath8(char* dst, unsigned size) {
    if (dst && size) {
        int n = WideCharToMultiByte(65001, 0, mpPath16, -1, dst, size, 0, 0);
        return n - 1;
    }
    char tmp[260];
    return GetPath8(tmp, 260);
}

// @ 0x009318a0  GetPath(wchar_t*, size)
unsigned FileStream::GetPath16(wchar_t* dst, unsigned size) {
    if (dst && size) {
        wcsncpy(dst, mpPath16, size);
        dst[size - 1] = 0;
    }
    return (unsigned)wcslen(mpPath16);
}

// @ 0x009318f0  EA::IO::FileStream::Open(accessFlags, creationDisposition, sharing, usageHints)
bool FileStream::Open(unsigned access, int cd, unsigned sharing, unsigned hints) {
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

// @ 0x00931a70  Close
bool FileStream::Close() {
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

// @ 0x00931ad0  GetState: maps the last Win32 error to an EA::IO state code
unsigned FileStream::GetState() {
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

// @ 0x00931b70  GetSize (lazily cached)
int FileStream::GetSize() {
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

// @ 0x00931bc0  SetSize: truncate/extend at the given position
bool FileStream::SetSize(int size) {
    if (mhFile != INVALID_HANDLE_VALUE) {
        if (SetFilePointer(mhFile, size, 0, 0) != 0xffffffff && SetEndOfFile(mhFile))
            return true;
        mnLastError = GetLastError();
    }
    return false;
}

// @ 0x00931c10  GetPosition(type): 0 = from start, 2 = remaining
int FileStream::GetPosition(int type) {
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

// @ 0x00931c70  SetPosition(pos, type)
bool FileStream::SetPosition(int pos, int type) {
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

// @ 0x00931cd0  GetAvailable: bytes remaining (negated distance from the end)
int FileStream::GetAvailable() {
    return -GetPosition(2);
}

// @ 0x00931ce0  Read
unsigned FileStream::Read(void* dst, unsigned size) {
    if (mhFile != INVALID_HANDLE_VALUE) {
        if (ReadFile(mhFile, dst, size, (LPDWORD)&size, 0))
            return size;
        mnLastError = GetLastError();
    }
    return 0xffffffff;
}

// @ 0x00931d30  Write
bool FileStream::Write(const void* src, unsigned size) {
    if (mhFile != INVALID_HANDLE_VALUE) {
        if (WriteFile(mhFile, src, size, (LPDWORD)&size, 0))
            return true;
        mnLastError = GetLastError();
    }
    return false;
}

// @ 0x00931d70  Flush
bool FileStream::Flush() {
    bool ok = false;
    if (mhFile != INVALID_HANDLE_VALUE) {
        ok = FlushFileBuffers(mhFile) != 0;
        if (!ok)
            mnLastError = GetLastError();
    }
    return ok;
}

// @ 0x00931da0  FileStream::FileStream(const char* utf8Path)
FileStream::FileStream(const char* path) {
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

// @ 0x00931e10  FileStream::FileStream(const wchar_t* path)
FileStream::FileStream(const wchar_t* path) {
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

// @ 0x00931e70 (non-deleting body) / 0x00931ec0 (scalar deleting destructor)  ~FileStream
FileStream::~FileStream() {
    Close();
}

// ---------------------------------------------------------------------------------------------
// EA::IO::File
// ---------------------------------------------------------------------------------------------
namespace File {

// @ 0x00931f20  Create(path, truncate)
bool Create(const wchar_t* path, bool truncate) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = 12;
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = 0;
    HANDLE h = CreateFileW(path, 0x80000000, 3, &sa, 4, 0x80, 0);
    if (h != INVALID_HANDLE_VALUE) {
        if (truncate) {
            SetFilePointer(h, 0, 0, 0);
            SetEndOfFile(h);
        }
        CloseHandle(h);
        return true;
    }
    return false;
}

// @ 0x00931fa0  Exists
bool Exists(const wchar_t* path) {
    if (path && *path) {
        DWORD a = GetFileAttributesW(path);
        if (a != 0xffffffff && (a & 0x10) == 0)
            return true;
        return false;
    }
    return false;
}

// @ 0x00931fd0  Remove
bool Remove(const wchar_t* path) {
    return DeleteFileW(path) != 0;
}

// @ 0x00931ff0  Move(from, to, overwrite)
bool Move(const wchar_t* from, const wchar_t* to, bool overwrite) {
    if (!overwrite && to && *to) {
        DWORD a = GetFileAttributesW(to);
        if (a != 0xffffffff && (a & 0x10) == 0)
            return false;
    }
    return MoveFileExW(from, to, 3) != 0;
}

// @ 0x00932030  Copy(from, to, overwrite)
bool Copy(const wchar_t* from, const wchar_t* to, bool overwrite) {
    return CopyFileW(from, to, overwrite == 0) != 0;
}

// @ 0x00932060  GetSize via FindFirstFile
unsigned GetSize(const wchar_t* path) {
    WIN32_FIND_DATAW fd;
    DWORD size = 0xffffffff;
    HANDLE h = FindFirstFileW(path, &fd);
    if (h != INVALID_HANDLE_VALUE) {
        size = fd.nFileSizeLow;
        FindClose(h);
    }
    return size;
}

// @ 0x009320a0  SetAttributes(path, mask, set)
bool SetAttributes(const wchar_t* path, int mask, bool set) {
    DWORD orig = GetFileAttributesW(path);
    DWORD a = orig;
    if (mask & 2) {
        if (set)
            a &= 0xfffffffe;
        else
            a |= 1;
    }
    if (mask & 8)
        return false;
    if (mask & 0x10)
        return false;
    if (mask & 0x20) {
        if (set)
            a |= 0x20;
        else
            a &= 0xffffffdf;
    }
    if (mask & 0x40) {
        if (set)
            a |= 2;
        else
            a &= 0xfffffffd;
    }
    if (mask & 0x80) {
        if (set)
            a |= 4;
        else
            a &= 0xfffffffb;
    }
    if (a == orig)
        return true;
    return SetFileAttributesW(path, a) != 0;
}

// @ 0x00932130  GetTime(path, type)  (1 = creation, 2 = modification, 4 = access)
int64_t GetTime(const wchar_t* path, int type) {
    struct _stat64i32 st;
    if (_wstat64i32(path, &st) == 0) {
        if (type == 1)
            return st.st_ctime;
        if (type == 2)
            return st.st_mtime;
        if (type == 4)
            return st.st_atime;
    }
    return 0;
}

}  // namespace File

// ---------------------------------------------------------------------------------------------
// EA::IO drive / directory helpers
// ---------------------------------------------------------------------------------------------
extern wchar_t gTempPath[];   // 0x01668f28 cached temp path (empty until first use)
bool EnsureTrailingPathSeparator(wchar_t* path, int len);

// @ 0x00932190  EA::IO::GetDriveFreeSpace (temp-directory path getter, cached)
int GetTempDirectoryPath(wchar_t* out) {
    if (gTempPath[0]) {
        const wchar_t* s = gTempPath;
        wchar_t* d = out;
        do {
        } while ((*d++ = *s++) != 0);
        return (int)wcslen(out);
    }
    DWORD n = GetTempPathW(0x100, out);
    if (n != 0) {
        n = GetLongPathNameW(out, out, 0x100);
        if (EnsureTrailingPathSeparator(out, -1))
            n = n + 1;
        return n;
    }
    return -1;
}

// @ 0x00932220  GetDriveSerialNumber(path, out) -> 10 chars "XXXX-XXXX" or 0
int GetDriveSerialNumber(const wchar_t* path, wchar_t* out) {
    wchar_t volume[260];
    DWORD serial;
    DWORD flags;
    if (GetVolumePathNameW(path, volume, 260) &&
        GetVolumeInformationW(volume, 0, 0, &serial, 0, &flags, 0, 0)) {
        wsprintfW(out, L"%04X-%04X", serial >> 16, serial & 0xffff);
        return 10;
    }
    *out = 0;
    return 0;
}

namespace Directory {

// @ 0x009322b0  Exists
bool Exists(const wchar_t* path) {
    if (path && *path) {
        DWORD a = GetFileAttributesW(path);
        if (a != 0xffffffff && (a & 0x10))
            return true;
        return false;
    }
    return false;
}

}  // namespace Directory

// @ 0x009322e0  Directory::Create(path)
bool DirectoryCreate(const wchar_t* path) {
    wchar_t tmp[260];
    if (*path != 0) {
        unsigned last = path[wcslen(path) - 1];
        if (last == '\\' || last == '/' || last == ':') {
            tmp[wcslen(path)] = 0;
            return CreateDirectoryW(path, 0) != 0;
        }
        return CreateDirectoryW(path, 0) != 0;
    }
    return false;
}

// @ 0x00932370  EA::IO::Directory::GetCurrentWorkingDirectory
int GetCurrentWorkingDirectory(wchar_t* out) {
    if (_wgetcwd(out, 0xff)) {
        EnsureTrailingPathSeparator(out, -1);
        return StrLenDo(out);
    }
    return -1;
}
