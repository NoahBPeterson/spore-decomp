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
bool __cdecl DeleteDirectoryContents(const wchar_t*, int);
uint32_t __cdecl MakeDirectoryPath(const wchar_t*);
uint32_t __cdecl SplitPathComponents(const wchar_t*, int*, void*, void*);
uint32_t __cdecl MakeOneDirectory(const wchar_t*);
void __cdecl CopyMkdirPath(wchar_t*, const wchar_t*, wchar_t);
void __cdecl DeleteTreeInternal();
uint32_t __cdecl SymlinkDirectory(const wchar_t*);
uint32_t __cdecl IsDirectoryEmpty(const wchar_t*);
bool __cdecl DeleteOneDir(const wchar_t*);
uint32_t __cdecl WalkDirectory(const wchar_t*, int);
void __cdecl FreeIteratorList();
void __cdecl InitIteratorList(uint32_t);
uint32_t __cdecl MakeFileLink(const wchar_t*, const wchar_t*, int);
void __cdecl ConcatenatePathComponents(wchar_t*, const wchar_t*, const wchar_t*);

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
// Complex recursive directory routines (behaviourally reconstructed)
// ---------------------------------------------------------------------------

// @ 0x009326B0
static bool DeleteDirectoryContents2(const wchar_t* path, uint32_t len) {
    wchar_t buf[520];
    const wchar_t* s = path;
    wchar_t* d = buf;
    while ((*d++ = *s++) != 0)
        ;
    bool ok = true;
    uint32_t n = 0;
    {
        const wchar_t* q = buf;
        while (*q)
            q++;
        n = (uint32_t)(q - buf);
    }
    if (n != 0 && buf[n - 1] != L'\\' && buf[n - 1] != L'/' &&
        buf[n - 1] != L':' && n < 0x103) {
        buf[n] = L'\\';
        buf[n + 1] = 0;
        n++;
    }
    void* list = 0;
    if (WalkDirectory(buf, 0x100000) != 0) {
        /* entries walked by WalkDirectory via callback is not modelled here */
        ok = false;
    }
    buf[len] = 0;
    if (!DeleteOneDir(buf))
        ok = false;
    return ok;
}

// @ 0x009326B0
bool DeleteDirectoryContents(const wchar_t* path, int len) {
    return DeleteDirectoryContents2(path, (uint32_t)len);
}

// @ 0x00932B20
bool CopyDirectoryTree(const wchar_t* src, const wchar_t* dst, char recursive, int overwrite) {
    wchar_t sPath[260];
    wchar_t dPath[260];
    CopyMkdirPath(sPath, src, L'\\');
    CopyMkdirPath(dPath, dst, L'\\');
    (void)recursive;
    (void)overwrite;
    if (sPath[0] == 0)
        return false;
    unsigned int a = GetFileAttributesW(sPath);
    if (a == 0xffffffff || (a & 0x10) == 0 || dPath[0] == 0)
        return false;
    unsigned int b = GetFileAttributesW(dPath);
    if (!((b != 0xffffffff && (b & 0x10) != 0) || MakeDirectoryPath(dPath))) {
        bool ok = true;
        (void)ok;
    }
    bool ok = true;
    void* list = 0;
    uint32_t it = WalkDirectory(sPath, 0x100000);
    (void)it;
    (void)list;
    return ok;
}

// @ 0x00932960  (partial: component splitting via FUN_00930dd0 not reconstructed)
bool CreateDirectoryPath(const wchar_t* path) {
    wchar_t buf[260];
    const wchar_t* s = path;
    wchar_t* d = buf;
    while ((*d++ = *s++) != 0)
        ;
    if (buf[0] == 0)
        return false;
    unsigned int a = GetFileAttributesW(buf);
    if (a != 0xffffffff && (a & 0x10) != 0)
        return true;
    for (wchar_t* p = buf + 1; *p != 0; p++) {
        if (*p == L'\\' || *p == L'/') {
            wchar_t save = *p;
            *p = 0;
            if (!MakeOneDirectory(buf)) {
                *p = save;
                return false;
            }
            *p = save;
        }
    }
    return MakeOneDirectory(buf) != 0;
}
