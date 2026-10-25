// Slice s009323c0 -- EA framework filesystem helpers, hashing (CRC/FNV) and EA::IO::IniFile.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-  (no GS cookie on the 260-wchar stack buffers).
#include "types.h"

extern "C" {
__declspec(dllimport) unsigned int __stdcall GetFileAttributesW(const wchar_t*);
__declspec(dllimport) int __stdcall RemoveDirectoryW(const wchar_t*);
__declspec(dllimport) int __stdcall DeleteFileW(const wchar_t*);
__declspec(dllimport) int __cdecl tolower(int);
__declspec(dllimport) int __cdecl toupper(int);
__declspec(dllimport) unsigned short __cdecl towlower(unsigned short);
__declspec(dllimport) unsigned short __cdecl towupper(unsigned short);
}

bool CreateDirectoryPath(const wchar_t* dir);

namespace EA { namespace IO {
bool IsFilePathSeparator(wchar_t c);
bool GetDriveFreeSpace(wchar_t* out);
}}

extern "C" {
__declspec(dllimport) unsigned int __stdcall GetTempPathW(unsigned int, wchar_t*);
__declspec(dllimport) unsigned int __stdcall GetWindowsDirectoryW(wchar_t*, unsigned int);
__declspec(dllimport) void* __stdcall GetModuleHandleA(const char*);
__declspec(dllimport) unsigned int __stdcall GetModuleFileNameW(void*, wchar_t*, unsigned int);
__declspec(dllimport) unsigned int __stdcall GetFullPathNameW(const wchar_t*, unsigned int, wchar_t*, wchar_t**);
__declspec(dllimport) int __stdcall SHGetFolderPathW(void*, int, void*, unsigned int, wchar_t*);
__declspec(dllimport) int __stdcall CopyFileW(const wchar_t*, const wchar_t*, int);
__declspec(dllimport) __int64 __cdecl _time64(__int64*);
}

extern "C" uint32_t g_folderTable[];
extern void FreeMem(void*);
__declspec(dllimport) int __cdecl Snprintf16(wchar_t*, int, const wchar_t*, ...);
int __cdecl DetectEncoding(const void*, unsigned, int, int);
bool DeleteDirectoryContents(wchar_t* path, uint32_t len);
bool __cdecl MakeOneDirectory(const wchar_t*);                   // 0x009322e0
void __cdecl FUN_00930dd0(const wchar_t* path, const wchar_t** outDir,
                          const wchar_t** outName, const wchar_t** outExt);
wchar_t* __cdecl FUN_00930a30(const wchar_t* src, wchar_t* dst, wchar_t sep);
int __cdecl ConcatenatePathComponents(wchar_t*, const wchar_t*, const wchar_t*);   // 0x0092fe60

namespace EA { namespace IO {
bool FileExists(const wchar_t* path);
}}
namespace EA { namespace Thread {
void ThreadSleep(uint32_t* ms);
}}

struct FileStream {
    void Construct(const wchar_t* path);
    void Destroy();
    bool Open(int a, int b, int c, int d);
    void CloseStream();
};

// ---------------------------------------------------------------------------
// Hashing
// ---------------------------------------------------------------------------
extern "C" uint32_t g_crc32Table[256];   // 0x01669530
extern "C" uint64_t g_crc64Table[256];   // 0x0154e288

// @ 0x00932D00
void InitCRC32Table() {
    for (int i = 0; i < 256; i++) {
        uint32_t crc = (uint32_t)i << 24;
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80000000)
                crc = (crc << 1) ^ 0x04c11db7;
            else
                crc = crc << 1;
        }
        g_crc32Table[i] = crc;
    }
}

// @ 0x00932DA0
uint32_t CRC32(const uint8_t* p, int len, uint32_t crc, bool finalize) {
    if (g_crc32Table[1] == 0)
        InitCRC32Table();
    const uint8_t* end = p + len;
    for (; p < end; p++) {
        crc = (crc << 8) ^ g_crc32Table[(crc >> 24) ^ *p];
    }
    if (finalize)
        crc = ~crc;
    return crc;
}

// @ 0x00932DF0
uint64_t CRC64(const uint8_t* p, int len, uint64_t crc, bool finalize) {
    const uint8_t* end = p + len;
    for (; p < end; p++) {
        uint32_t idx = ((uint32_t)(crc >> 56) ^ (uint32_t)*p) & 0xff;
        crc = (crc << 8) ^ g_crc64Table[idx];
    }
    if (finalize)
        crc = ~crc;
    return crc;
}

// @ 0x00932E50
uint32_t FNV1(const uint8_t* p, int len, uint32_t hash) {
    const uint8_t* end = p + len;
    for (; p < end; p++) {
        hash = hash * 0x01000193 ^ (uint32_t)*p;
    }
    return hash;
}

// @ 0x00932E80
uint32_t FNV1_String8(const char* str, uint32_t hash, int mode) {
    uint32_t c;
    switch (mode) {
    case 0: while ((c = (uint8_t)*str++) != 0) hash = hash * 0x01000193 ^ c; break;
    case 1: while ((c = (uint8_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)tolower((unsigned char)c); break;
    case 2: while ((c = (uint8_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)toupper((unsigned char)c); break;
    }
    return hash;
}

// @ 0x00932F30
uint32_t FNV1_String16(const wchar_t* str, uint32_t hash, int mode) {
    uint32_t c;
    switch (mode) {
    case 0: while ((c = (uint16_t)*str++) != 0) hash = hash * 0x01000193 ^ c; break;
    case 1: while ((c = (uint16_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)(uint16_t)towlower((uint16_t)c); break;
    case 2: while ((c = (uint16_t)*str++) != 0) hash = hash * 0x01000193 ^ (uint32_t)(uint16_t)towupper((uint16_t)c); break;
    }
    return hash;
}

// ---------------------------------------------------------------------------
// EA::IO::IniFile
// ---------------------------------------------------------------------------
struct IStream {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual uint32_t s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual uint32_t s9(int);
    virtual void s10(int, int);
    virtual void s11();
    virtual uint32_t s12(void*, unsigned int);
    virtual void s13();
    virtual void s14();
    virtual void s15(const wchar_t*);
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual bool s19(unsigned int, int, int, int);
};

class EA_IO_IniFile {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual uint32_t v19();

    wchar_t  mPath[260];         // +0x004
    char     mFileStream[0x22c]; // +0x20c
    void*    mpStream;           // +0x438
    uint32_t m43c;               // +0x43c
    uint8_t  m440;               // +0x440
    uint8_t  m441;               // +0x441
    uint8_t  m442;               // +0x442
    uint8_t  m443;               // +0x443
    char     m444[0x1c];         // +0x444
    char     m460[0x1c];         // +0x460

    int GetOption(int option);
    void SetOption(int option, int value);
    bool SetPath(const wchar_t* path);
    bool SetStream(void* stream);
    bool Open(uint32_t flags);
    int  GetEncoding();
};

// @ 0x00932FF0
int EA_IO_IniFile::GetOption(int option) {
    int b = 0;
    if (option == 1)
        b = m441 != 0;
    return b;
}

// @ 0x00933010
void EA_IO_IniFile::SetOption(int option, int value) {
    if (option == 1) {
        bool b = value != 0;
        if (m441 != b) {
            m441 = b;
            if (!b)
                v7();
        }
    }
}

// @ 0x00933040
bool EA_IO_IniFile::SetPath(const wchar_t* path) {
    if (path != 0 && *path != 0) {
        if (m442 == 0)
            mpStream = 0;
        if (mpStream == 0) {
            const wchar_t* s = path;
            wchar_t* d = mPath;
            while ((*d++ = *s++) != 0)
                ;
            ((IStream*)(void*)mFileStream)->s15(path);
            mpStream = mFileStream;
            return true;
        }
    }
    return false;
}

// @ 0x009330C0
bool EA_IO_IniFile::SetStream(void* stream) {
    if (stream != 0 && m442 == 0 && mpStream != 0) {
        ((IStream*)mpStream)->s6();
        mpStream = 0;
    }
    if (mpStream == 0) {
        mpStream = stream;
        mPath[0] = 0;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// EA::IO directory helpers
// ---------------------------------------------------------------------------

// @ 0x00932AE0
bool EnsureDirectoryExists(const wchar_t* dir) {
    if (dir == 0 || *dir == 0)
        return false;
    unsigned int a = GetFileAttributesW(dir);
    if (a != 0xffffffff && (a & 0x10) != 0)
        return true;
    return CreateDirectoryPath(dir);
}

// ---------------------------------------------------------------------------
// More filesystem helpers / temp files
// ---------------------------------------------------------------------------

// @ 0x009323C0
int GetSystemPath(int type, wchar_t* buf, bool checkExists) {
    if (type == 1) {
        bool ok = GetTempPathW(0x104, buf) != 0;
        if (!ok)
            return -1;
    } else if (type == 2) {
        bool ok = GetWindowsDirectoryW(buf, 0x104) != 0;
        if (!ok)
            return -1;
    } else if (type == 5) {
        wchar_t modbuf[260];
        void* h = GetModuleHandleA(0);
        if (GetModuleFileNameW(h, modbuf, 0x104) == 0)
            return -1;
        wchar_t* tail;
        if (GetFullPathNameW(modbuf, 0x104, buf, &tail) == 0)
            return -1;
        *tail = 0;
    } else {
        uint32_t flags = checkExists ? 0x8000 : 0;
        uint32_t csidl = g_folderTable[type * 2];
        if (csidl == 0 || SHGetFolderPathW(0, csidl | flags, 0, 0, buf) < 0) {
            csidl = g_folderTable[type * 2 + 1];
            if (csidl == 0)
                return -1;
            if (SHGetFolderPathW(0, csidl | flags, 0, 0, buf) < 0)
                return -1;
        }
        const wchar_t* p = buf;
        while (*p)
            p++;
        int len = (int)(p - buf);
        if (len != 0 && !EA::IO::IsFilePathSeparator(buf[len - 1])) {
            if (len > 0x102)
                return -1;
            buf[len] = L'\\';
            buf[len + 1] = 0;
        }
    }
    if (checkExists) {
        if (buf == 0 || buf[0] == 0)
            return -1;
        unsigned int a = GetFileAttributesW(buf);
        if (a == 0xffffffff || (a & 0x10) == 0)
            return -1;
    }
    const wchar_t* p = buf;
    while (*p)
        p++;
    return (int)(p - buf);
}

// @ 0x00932580
bool CreateTempFileW(wchar_t* path, const wchar_t* dir, const wchar_t* prefix,
                     const wchar_t* suffix) {
    __int64 t = _time64(0);
    if (prefix == 0)
        prefix = L"temp";
    if (suffix == 0)
        suffix = L".tmp";
    if (dir == 0) {
        wchar_t tmp[260];
        if (EA::IO::GetDriveFreeSpace(tmp) == 0)
            return false;
        dir = tmp;
    }
    char fsbuf[0x22c];
    for (uint32_t i = 0; i < 5000; i++) {
        int n = Snprintf16(path, 0x104, L"%ls%ls%lld%ls", dir, prefix, t, suffix);
        if (n >= 0x104)
            return false;
        FileStream* fs = (FileStream*)fsbuf;
        fs->Construct(path);
        if (fs->Open(3, 1, 1, 0)) {
            fs->CloseStream();
            fs->Destroy();
            return true;
        }
        fs->Destroy();
        t--;
    }
    return false;
}

// @ 0x00932890
uint32_t RemoveDirectoryRecursive(const wchar_t* path, char recursive) {
    wchar_t buf[260];
    if (recursive != 0) {
        const wchar_t* s = path;
        wchar_t* d = buf;
        while ((*d++ = *s++) != 0)
            ;
        const wchar_t* q = buf;
        while (*q)
            q++;
        return DeleteDirectoryContents(buf, (int)(q - buf));
    }
    const wchar_t* p = path;
    while (*p)
        p++;
    wchar_t c = p[-1];
    if (c != L'\\' && c != L'/' && c != L':') {
        int r = RemoveDirectoryW(path);
        return (uint32_t)(r != 0);
    }
    const wchar_t* q = path;
    while (*q)
        q++;
    int r = RemoveDirectoryW(path);
    return (uint32_t)(r != 0);
}

// @ 0x009332D0
class StackArrayChar256 {
public:
    char  mBuf[0x100];   // +0x000
    char* mpData;        // +0x100
    char* mpEnd;         // +0x104
    int   mnSize;        // +0x108
    char* Init(char* p, int n);
};

char* StackArrayChar256::Init(char* p, int n) {
    char* old = mpData;
    if (old == p)
        return old;
    if (p == 0)
        return old;
    if (n == 0)
        return old;
    if (old != (char*)this && mpEnd != old) {
        FreeMem(old);
        mpData = (char*)this;
    }
    mpData = p;
    mnSize = n;
    return p;
}

// @ 0x00933250
int EA_IO_IniFile::GetEncoding() {
    uint8_t buf[0x80];
    int enc = 8;
    int saved = ((IStream*)mpStream)->s9(0);
    uint32_t n = ((IStream*)mpStream)->s12(buf, 0x80);
    if (n != 0xffffffff && n >= 2)
        enc = DetectEncoding(buf, n, 0, 0);
    ((IStream*)mpStream)->s10(saved, 0);
    return enc;
}

// @ 0x00933120
bool EA_IO_IniFile::Open(uint32_t flags) {
    if (mpStream == 0)
        return false;
    uint32_t access = flags;
    if (flags & 2)
        access |= 1;
    if (((IStream*)mpStream)->s4() == access) {
        m440 = (uint8_t)((access >> 1) & 1);
    } else {
        if ((void*)((char*)this + 0x20c) != mpStream)
            return false;
        __int64 start = _time64(0) + 3;
        for (;;) {
            __int64 now = _time64(0);
            if (now >= start)
                return false;
            uint32_t ms = 250;
            EA::Thread::ThreadSleep(&ms);
            if (((IStream*)mpStream)->s19(access, (flags & 2) ? 3 : 2,
                                          ~(access >> 1) & 1, 0)) {
                m440 = (uint8_t)((access >> 1) & 1);
                break;
            }
            if (!EA::IO::FileExists(mPath))
                return false;
        }
    }
    m43c = v19();
    return true;
}

// ---------------------------------------------------------------------------
// Recursive directory routines.  They run on the eastl::deque<Entry> that
// EA::IO::DirectoryIterator::Read fills; only the container types are declared
// here (their bodies live in other translation units).
// ---------------------------------------------------------------------------
struct ICoreAllocator;

struct WString {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAlloc;       // +0x0c
};

struct Entry {
    int      mType;      // +0x00  1 = directory, 2 = file
    WString  mName;      // +0x04
    int      mPad;       // +0x14
    int64_t  mTimes[3];  // +0x18  create / write / access, seconds
};

struct DequeIter {
    Entry*  mpCurrent;          // +0x00
    Entry*  mpBegin;            // +0x04
    Entry*  mpEnd;              // +0x08
    Entry** mpCurrentArrayPtr;  // +0x0c

    DequeIter& operator++() {
        if (++mpCurrent == mpEnd) {
            ++mpCurrentArrayPtr;
            mpBegin = *mpCurrentArrayPtr;
            mpEnd = mpBegin + 4;
            mpCurrent = mpBegin;
        }
        return *this;
    }
    bool operator!=(const DequeIter& other) const { return mpCurrent != other.mpCurrent; }
    Entry& operator*() const { return *mpCurrent; }
};

struct Deque {
    Entry**         mpPtrArray;      // +0x00
    unsigned        mnPtrArraySize;  // +0x04
    DequeIter       mItBegin;        // +0x08
    DequeIter       mItEnd;          // +0x18
    ICoreAllocator* mpAllocator;     // +0x28
    const char*     mpName;          // +0x2c

    void DoInit(unsigned n);            // 0x005f8840
    void InitAlloc(ICoreAllocator* a);  // 0x005f9680
    void Destroy();                     // 0x005f96c0
};

struct DirectoryIterator {
    uint32_t mnListSize;            // +0x00
    int      mnRecursionIndex;      // +0x04
    wchar_t* mpBaseDirectory;       // +0x08
    uint32_t mBaseDirectoryLength;  // +0x0c

    unsigned Read(const wchar_t* dir, Deque* list, const wchar_t* pattern,   // 0x0092ef40
                  unsigned flags, unsigned maxCount, bool wantTimes);
};

extern "C" ICoreAllocator* __cdecl GetDefaultAllocatorX();       // 0x00925cb0
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);   // 0x011e0744

static inline bool IsPathSeparator(wchar_t c) {
    return c == L'\\' || c == L'/' || c == L':';
}

// @ 0x009326B0  DeleteDirectoryContents
bool DeleteDirectoryContents(wchar_t* path, uint32_t len) {
    DirectoryIterator it = {};
    ICoreAllocator* alloc = GetDefaultAllocatorX();
    Deque list;
    list.mpPtrArray = 0;
    list.mnPtrArraySize = 0;
    list.mItBegin = DequeIter();
    list.mItEnd = DequeIter();
    list.mpAllocator = alloc;
    list.mpName = 0;
    list.DoInit(0);

    bool ok = true;
    if (it.Read(path, &list, 0, 3, 0x100000, 0)) {
        if (len != 0 && !IsPathSeparator(path[len - 1]) && len < 0x103) {
            path[len] = L'\\';
            len++;
        }
        for (DequeIter i = list.mItBegin; i != list.mItEnd; ++i) {
            Entry& e = *i;
            uint32_t n = (uint32_t)(e.mName.mpEnd - e.mName.mpBegin);
            if (len + n < 0x104) {
                memcpy(path + len, e.mName.mpBegin, n * 2);
                path[len + n] = 0;
                if (e.mType == 1) {
                    if (!DeleteDirectoryContents(path, len + n))
                        ok = false;
                } else if (!DeleteFileW(path)) {
                    ok = false;
                }
            } else {
                ok = false;
            }
        }
    }
    path[len] = 0;
    bool result = false;
    if (RemoveDirectoryRecursive(path, 0))
        result = ok;
    list.Destroy();
    return result;
}

// @ 0x00932B20  EA::IO::Directory::CopyTree
bool CopyDirectoryTree(const wchar_t* src, const wchar_t* dst, char recursive, int overwrite) {
    wchar_t sPath[260];
    wchar_t dPath[260];
    FUN_00930a30(src, sPath, L'\\');
    FUN_00930a30(dst, dPath, L'\\');
    if (sPath[0] == 0)
        return false;
    uint32_t a = GetFileAttributesW(sPath);
    if (a == 0xffffffff || (a & 0x10) == 0)
        return false;
    if (dPath[0] == 0)
        return false;
    uint32_t b = GetFileAttributesW(dPath);
    if (!(b != 0xffffffff && (b & 0x10) != 0)) {
        if (!CreateDirectoryPath(dPath))
            return false;
    }

    DirectoryIterator it = {};
    ICoreAllocator* alloc = GetDefaultAllocatorX();
    Deque list;
    list.InitAlloc(alloc);

    bool ok = it.Read(sPath, &list, 0, 2 + (recursive != 0), 0x100000, 0) != 0;
    if (ok) {
        for (DequeIter i = list.mItBegin; i != list.mItEnd; ++i) {
            Entry& e = *i;
            wchar_t sFile[260];
            wchar_t dFile[260];
            ConcatenatePathComponents(sFile, sPath, e.mName.mpBegin);
            ConcatenatePathComponents(dFile, dPath, e.mName.mpBegin);
            if (e.mType == 1 && recursive != 0) {
                if (!CopyDirectoryTree(sFile, dFile, (char)overwrite, 1))
                    ok = false;
            } else if (e.mType == 2) {
                if (!CopyFileW(sFile, dFile, overwrite == 0))
                    ok = false;
            }
        }
    }
    list.Destroy();
    return ok;
}

// @ 0x00932960  EA::IO::Directory::CreatePath
bool CreateDirectoryPath(const wchar_t* path) {
    wchar_t buf[260];
    const wchar_t* s = path;
    wchar_t* d = buf;
    while ((*d++ = *s++) != 0)
        ;

    const wchar_t* pDir;
    const wchar_t* pName;
    const wchar_t* pExt;
    FUN_00930dd0(buf, &pDir, &pName, &pExt);

    wchar_t* pEnd = (wchar_t*)pDir;
    if (*pDir != 0) {
        do {
            pEnd++;
        } while (*pEnd != 0);
        if (pEnd > pDir && IsPathSeparator(pEnd[-1]))
            pEnd--;
    }

    // Walk back to the deepest existing directory, blanking each separator so
    // the truncation is visible in buf.
    wchar_t* p = pEnd;
    if (pDir < pEnd) {
        for (;;) {
            if (buf[0] != 0) {
                uint32_t a = GetFileAttributesW(buf);
                if (a != 0xffffffff && (a & 0x10) != 0)
                    break;
            }
            if (p <= pDir)
                break;
            bool found = false;
            do {
                wchar_t c = p[-1];
                p--;
                if (IsPathSeparator(c)) {
                    found = true;
                    break;
                }
            } while (p > pDir);
            if (!found)
                break;
            while (p > pDir && IsPathSeparator(p[-1]))
                p--;
            *p = 0;
            if (p <= pDir)
                break;
        }
    }

    bool result = true;
    if (p == pDir && *p != 0) {
        result = MakeOneDirectory(buf);
        if (!result)
            return result;
    }
    // Re-create the blanked components one by one, restoring each separator.
    wchar_t* f = p;
    for (;;) {
        if (f >= pEnd)
            return result;
        if (*f == 0) {
            *f = L'\\';
            if (f >= pEnd)
                return result;
            if (!MakeOneDirectory(buf)) {
                result = false;
                for (; f > p; f--) {
                    if (*f == L'\\') {
                        *f = 0;
                        RemoveDirectoryRecursive(buf, 0);
                    }
                }
                return result;
            }
        } else {
            f++;
        }
    }
}
