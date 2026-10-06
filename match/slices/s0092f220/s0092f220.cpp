// Slice s0092f220: EA::IO file-watching / path utilities (MSVC 2008 SP1, /O2 /MD /Gy /EHsc /TP).
// Reconstructed from the annotated disassembly and Ghidra decompilation. Real names from the 2008
// dev-build PDB are used where known (EA::IO::FilePath::SafeReplace, EnsureTrailingPathSeparator,
// ConcatenatePathComponents, EA::IO::DirectoryIterator::ReadRecursive, ...).
#include "types.h"

typedef void* HANDLE;
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned int UINT;

struct OVERLAPPED_ {
    uint32_t Internal;
    uint32_t InternalHigh;
    uint32_t Offset;
    uint32_t OffsetHigh;
    void*    hEvent;
};

extern "C" __declspec(dllimport) HANDLE __stdcall CreateEventA(void*, BOOL, BOOL, const char*);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileW(const unsigned short*, DWORD, DWORD, void*, DWORD, DWORD, HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall SetEvent(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall CancelIo(HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjectsEx(DWORD, const HANDLE*, BOOL, DWORD, BOOL);
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD, const HANDLE*, BOOL, DWORD);
extern "C" __declspec(dllimport) HANDLE __stdcall FindFirstChangeNotificationW(const unsigned short*, BOOL, DWORD);
extern "C" __declspec(dllimport) BOOL __stdcall FindNextChangeNotification(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall FindCloseChangeNotification(HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall GetLongPathNameW(const unsigned short*, unsigned short*, DWORD);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned);
extern "C" void* __cdecl operator new[](unsigned);

extern "C" void FUN_004228e0(void*, unsigned);
extern "C" unsigned FUN_00922930();
extern "C" void FUN_005f8840(void*);
extern "C" void FUN_005f96c0(void*);
extern "C" void FUN_0092e9f0(void* self, int);
extern "C" void WString_Assign(void* self, const unsigned short*, const unsigned short*);
extern "C" void WString_insert(void*, const unsigned short*, const unsigned short*);
extern "C" void WString_append(void*, const unsigned short*, int, unsigned short);
extern "C" void WString_insert2(void*, const void*, unsigned);
extern "C" int  EA_Text_WildcardMatch(const unsigned short*, const unsigned short*, int);
extern "C" void* Deque_Push(void*);
extern "C" int* Deque_Last(void*);
bool EnsureTrailingPathSeparator(unsigned short* path, int length);
int  ConcatenatePathComponents(unsigned short* dst, const unsigned short* c1, const unsigned short* c2);

// Global function table / pointer used to decide between overlapped ReadDirectoryChangesW and
// FindFirstChangeNotificationW. Values are unknown; only their presence matters for behavior.
extern void* g_pfnTable;             // 0x01668f20
extern void* g_pfnReadDirectory;     // 0x00fcc210 (function pointer)
extern char  g_threadName[];         // 0x0143e524
extern char  g_vtbl_143e540;         // primary vtable
extern char  g_vtbl_13fc474;         // base vtable

namespace EA { namespace IO {

// ---------------------------------------------------------------------------------------------
// EA::IO::FilePath (PDB: wchar_t mPath[520], size 0x410). Only the path helpers are used here.
// ---------------------------------------------------------------------------------------------
struct FilePath {
    unsigned short mPath[520];
    bool SafeReplace(const unsigned short* a, const unsigned short* b,
                     const unsigned short* c, const unsigned short* d,
                     unsigned short e, unsigned short f);
};

}} // namespace EA::IO

using EA::IO::FilePath;

// EA::IO::DirectoryIterator (PDB: size 0x10).
namespace EA { namespace IO {
struct DirectoryIterator {
    uint32_t mnListSize;            // +0
    int      mnRecursionIndex;      // +4
    unsigned short* mpBaseDirectory;// +8
    uint32_t mBaseDirectoryLength;  // +0xc

    uint32_t ReadRecursive(const unsigned short* pDir, void* pList, const unsigned short* pFilter,
                           uint32_t flags, char c6, char c7, uint32_t maxDepth, void* p9);
    int FillEntries(const unsigned short*, void*, int, int, int, void*);
};
}} // namespace EA::IO
using EA::IO::DirectoryIterator;

// ---------------------------------------------------------------------------------------------
// File-watch service object (vtable 0x0143e540, base vtable 0x013fc474). Real class name unknown;
// field offsets come from the disassembly.
// ---------------------------------------------------------------------------------------------
struct ThreadRef {
    void* mpData;                    // +0
    void  Init();                    // 0x00743B50
    int   WaitStatus(void* out);     // 0x00922A10
    void  Release();                 // 0x00922E10
    void  Notify(const void* n, int);        // 0x00922940
    void* StartThread(void*, void*, void*, void*); // 0x009231A0
};

struct ThreadParams {
    uint32_t f0, f1, f2, f3;
    unsigned char f4;
    void* f5;
    void InitParams();               // 0x00922900
};

struct FileWatcher {
    void*         m_vtbl;            // +0x000
    bool          m_bActive;         // +0x004
    unsigned short m_path[0x101];    // +0x006 (compiler pads +0x005)
    uint32_t      m_flags;           // +0x208
    uint32_t      m_shareMode;       // +0x20c
    void*         m_callback;        // +0x210
    void*         m_callbackData;    // +0x214
    HANDLE        m_hChange;         // +0x218
    HANDLE        m_hEvent;          // +0x21c
    ThreadRef     m_thread;          // +0x220
    HANDLE        m_hFile;           // +0x224
    OVERLAPPED_   m_ov;              // +0x228
    bool          m_bRunning;        // +0x23c

    FileWatcher* Construct();
    bool  SetFlags(uint32_t f);
    bool  SetShareMode(uint32_t f);
    bool  SetPath(const unsigned short* p);
    short* Reset0();
    bool  Stop();                    // 0x0092F5F0
    void  Worker(uint32_t filter);   // 0x0092F650
    void  Watch(uint32_t mode, const unsigned short* path); // 0x0092F8B0
    bool  Close();                   // 0x0092F9E0
    bool  Start();                   // 0x0092FAF0
    uint32_t Arm(uint32_t);          // 0x0092FBE0
    void  Destroy();                 // 0x0092FC50
    FileWatcher* DestroyScalar(unsigned char flags); // 0x0092FC80
};

// ---------------------------------------------------------------------------------------------
// @ 0x0092F220  EA::IO::DirectoryIterator::ReadRecursive
// ---------------------------------------------------------------------------------------------
uint32_t DirectoryIterator::ReadRecursive(const unsigned short* pDir, void* pList,
        const unsigned short* pFilter, uint32_t flags, char c6, char c7,
        uint32_t maxDepth, void* p9) {
    uint32_t oldIndex = mnRecursionIndex;
    int newIndex = oldIndex + 1;
    mnRecursionIndex = newIndex;
    if (oldIndex == 0) {
        mnListSize = 0;
        mpBaseDirectory = (unsigned short*)pDir;
        unsigned short* p = (unsigned short*)pDir;
        while (*p++) {}
        uint32_t len = (uint32_t)((char*)p - (char*)(pDir + 1)) >> 1;
        mBaseDirectoryLength = len;
        if (len == 0 || (pDir[len - 1] != '\\' && pDir[len - 1] != '/' && pDir[len - 1] != ':')) {
            mBaseDirectoryLength = len + 1;
        }
    }
    if ((flags & 2) != 0 && (c6 != 0 || newIndex > 1)) {
        if (mnListSize >= maxDepth) goto done;
        int n = FillEntries(pDir, 0, 0, 2, maxDepth - mnListSize, p9);
        // iterate a deque<Entry> whose live range is pList[0x18] .. pList[0x20]
        int* pFirst = *(int**)((char*)pList + 0x18);
        int* pLast  = *(int**)((char*)pList + 0x20);
        FUN_0092e9f0((char*)&n /*placeholder self*/, -n);
        if (pFirst != *(int**)((char*)pList + 0x18)) {
            do {
                mnListSize++;
                int* pEntry = pFirst;
                int elemCount = (*(int*)((char*)pEntry + 8) - *(int*)((char*)pEntry + 4));
                unsigned short* dst = (unsigned short*)*(int*)((char*)pEntry + 4);
                const unsigned short* q = pDir;
                while (*q) ++q;
                // string insert at dst with [pDir, q)
                extern void WString_insert(void*, const unsigned short*, const unsigned short*);
                WString_insert(&dst, pDir, q);
                int added = ((*(int*)((char*)pEntry + 8) - *(int*)((char*)pEntry + 4)) >> 1) - (elemCount >> 1);
                if (added != 0) {
                    unsigned short last = dst[added - 1];
                    if (last != '\\' && last != '/' && last != ':') {
                        extern void WString_append(void*, const unsigned short*, int, unsigned short);
                        WString_append(&dst, dst + added, 1, '\\');
                    }
                }
                if (c7 == 0) FUN_004228e0(0, mBaseDirectoryLength);
                pFirst += 0x30 / 4;
                if ((char*)pFirst == (char*)pLast) {
                    pLast = (int*)((char*)pLast + 4);
                    pFirst = (int*)*pLast;
                    pLast = (int*)((char*)pFirst + 0xc0);
                }
            } while ((char*)pFirst != (char*)*(int**)((char*)pList + 0x18));
        }
    }
    if (mnListSize < maxDepth) {
        // recursive scan built on a local deque
        char localDeque[0x18];
        int loc0 = *(int*)((char*)pList + 0x28);
        int loc1 = *(int*)((char*)pList + 0x2c);
        (void)loc0; (void)loc1;
        FUN_005f8840(localDeque);
        FillEntries(pDir, localDeque, 0, 1, 0x100000, p9);
        unsigned short buf[0x100];
        int* it = *(int**)(localDeque + 0x10);
        int* end = *(int**)(localDeque + 0x14);
        if (it != end) {
            do {
                if (mnListSize >= maxDepth) break;
                ConcatenatePathComponents(buf, pDir, *(const unsigned short**)((char*)it + 4));
                if ((flags & 1) != 0 &&
                    (pFilter == 0 || EA_Text_WildcardMatch(*(const unsigned short**)((char*)it + 4), pFilter, 1))) {
                    mnListSize++;
                    void* e = Deque_Push(localDeque);
                    (void)e;
                    int* out = Deque_Last(localDeque);
                    out[0] = 1;
                    unsigned short* q = buf;
                    while (*q) ++q;
                    void* s = (char*)out + 4;
                    WString_Assign(s, buf, q);
                    out[6] = *(int*)((char*)it + 0x18);
                    out[7] = *(int*)((char*)it + 0x1c);
                    out[8] = *(int*)((char*)it + 0x20);
                    out[9] = *(int*)((char*)it + 0x24);
                    out[10] = *(int*)((char*)it + 0x28);
                    out[11] = *(int*)((char*)it + 0x2c);
                    if (c7 == 0) FUN_004228e0(0, mBaseDirectoryLength);
                }
                ReadRecursive(buf, pList, pFilter, flags, 1, c7, maxDepth, p9);
                it = (int*)((char*)it + 0x30);
                if (it == end) {
                    int* nx = (int*)((char*)end + 4);
                    it = (int*)*nx;
                    end = (int*)((char*)it + 0xc0);
                }
            } while (it != *(int**)(localDeque + 0x14));
        }
        FUN_005f96c0(localDeque);
    }
done:
    uint32_t r = mnListSize;
    mnRecursionIndex--;
    return r;
}

// Placeholder declarations for the two EASTL string helpers used above.
extern "C" int  EA_Text_WildcardMatch(const unsigned short*, const unsigned short*, int);

// ---------------------------------------------------------------------------------------------
// @ 0x0092F5F0
// ---------------------------------------------------------------------------------------------
bool FileWatcher::Stop() {
    bool result = false;
    if (m_thread.WaitStatus(0) == 1) {
        m_bRunning = false;
        SetEvent(m_hEvent);
        m_thread.Notify(g_threadName, 0);
        CloseHandle(m_hEvent);
        m_hEvent = 0;
        result = true;
    }
    return result;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092F650  overlapped ReadDirectoryChangesW worker
// ---------------------------------------------------------------------------------------------
void FileWatcher::Worker(uint32_t bWatchSubtree) {
    uint32_t share = m_shareMode;
    (void)operator new[](0x1fff);
    m_hChange = CreateEventA(0, 0, 0, 0);
    if (m_hChange == 0) return;
    m_ov.hEvent = m_hChange;   // +0x238 mirrors +0x218
    uint32_t notify = share & 1;
    while (m_bRunning) {
        DWORD bytesReturned = 0;
        BOOL ok = ((BOOL(__stdcall*)(HANDLE, void*, DWORD, BOOL, DWORD, DWORD*, OVERLAPPED_*, void*))
                   g_pfnReadDirectory)(m_hFile, m_path, 0x2000, notify, bWatchSubtree,
                                       &bytesReturned, &m_ov, 0);
        if (!ok) break;
        if (WaitForMultipleObjectsEx(2, &m_hChange, 0, 0xffffffff, 0) != 0) break;
        if (!m_bRunning) break;
        char* p = (char*)m_path;
        while (p) {
            // queue entry (path + attributes) to the callback
            uint32_t attr = *(uint32_t*)(p + 4);
            uint32_t flags = ((m_flags & 0x20) != 0) ? 0x28 : 8;
            if (attr == 1 || attr == 5) flags = 2;
            else if (attr == 2 || attr == 4) flags = 1;
            if (m_callback) {
                ((void(__cdecl*)(FileWatcher*, const unsigned short*, const unsigned short*, uint32_t, void*))m_callback)
                    (this, m_path, (unsigned short*)(p + 0xc), flags, m_callbackData);
            }
            uint32_t sz = *(uint32_t*)p;
            if (sz == 0) break;
            p += sz;
        }
    }
    CancelIo(m_hFile);
    CloseHandle(m_hChange);
    m_hChange = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092F8B0
// ---------------------------------------------------------------------------------------------
void FileWatcher::Watch(uint32_t mode, const unsigned short* path) {
    uint32_t share = m_shareMode;
    m_hChange = FindFirstChangeNotificationW(path, share & 1, mode);
    if (m_hChange == (HANDLE)-1) return;
    uint32_t recurse = (share >> 1) & 1;
    while (m_bRunning && WaitForMultipleObjects(2, &m_hChange, 0, 0xffffffff) == 0) {
        if (m_callback) {
            ((void(__cdecl*)(FileWatcher*, const unsigned short*, int, uint32_t, void*))m_callback)
                (this, m_path, 0, m_flags, m_callbackData);
        }
        if (recurse != 0) break;
        if (!FindNextChangeNotification(m_hChange)) break;
        if (!m_bRunning) break;
    }
    FindCloseChangeNotification(m_hChange);
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092F960
// ---------------------------------------------------------------------------------------------
FileWatcher* FileWatcher::Construct() {
    m_vtbl = &g_vtbl_143e540;
    m_bActive = false;
    m_flags = 0;
    m_shareMode = 4;
    m_callback = 0;
    m_callbackData = 0;
    m_thread.Init();
    m_hFile = 0;
    m_bRunning = false;
    m_path[0] = 0;
    m_ov.Internal = 0;
    m_ov.InternalHigh = 0;
    m_ov.Offset = 0;
    m_ov.OffsetHigh = 0;
    m_ov.hEvent = 0;
    m_hChange = 0;
    m_hEvent = 0;
    return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092F9E0
// ---------------------------------------------------------------------------------------------
bool FileWatcher::Close() {
    if (m_bActive) {
        m_bActive = false;
        if (m_thread.WaitStatus(0) == 1) Stop();
        if (m_hFile) { CloseHandle(m_hFile); m_hFile = 0; }
        CloseHandle(m_hChange);
        m_hChange = 0;
        CloseHandle(m_hEvent);
        m_hEvent = 0;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FA50
// ---------------------------------------------------------------------------------------------
bool FileWatcher::SetPath(const unsigned short* p) {
    bool result = false;
    if (m_thread.WaitStatus(0) != 1) {
        unsigned short* d = m_path;
        while ((*d++ = *p++) != 0) {}
        result = true;
    }
    return result;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FA90
// ---------------------------------------------------------------------------------------------
bool FileWatcher::SetFlags(uint32_t f) {
    bool result = false;
    if (m_thread.WaitStatus(0) != 1) {
        m_flags = f;
        result = true;
    }
    return result;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FAC0
// ---------------------------------------------------------------------------------------------
bool FileWatcher::SetShareMode(uint32_t f) {
    bool result = false;
    if (m_thread.WaitStatus(0) != 1) {
        m_shareMode = f;
        result = true;
    }
    return result;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FAF0
// ---------------------------------------------------------------------------------------------
bool FileWatcher::Start() {
    if (m_thread.WaitStatus(0) == 1) return false;
    if (m_flags == 0) return false;
    if (m_path[0] == 0) return false;
    if (g_pfnTable != 0 && g_pfnReadDirectory != 0 && m_hFile == 0) {
        m_hFile = CreateFileW(m_path, 1, 7, 0, 3, 0x42000000, 0);
    }
    m_hEvent = CreateEventA(0, 0, 0, 0);
    if (g_pfnTable != 0 && g_pfnReadDirectory != 0 && m_hFile == 0) return false;
    m_bRunning = true;
    ThreadParams params;
    params.InitParams();
    unsigned threadId = FUN_00922930();
    m_thread.StartThread(&params, 0, (void*)threadId, this);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FBE0
// ---------------------------------------------------------------------------------------------
uint32_t FileWatcher::Arm(uint32_t) {
    uint32_t f = m_flags;
    uint32_t mode = (f & 3) ? 1 : 0;
    if (f & 4)  mode |= 2;
    if (f & 8)  mode |= 0x10;
    if (f & 0x10) mode |= 4;
    if (f & 0x20) mode |= 8;
    if (f != 0) {
        if (g_pfnTable != 0) {
            Worker(mode);
            return 0;
        }
        if (m_path != 0 && m_path[0] != 0) {
            Watch(mode, m_path);
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FC50
// ---------------------------------------------------------------------------------------------
void FileWatcher::Destroy() {
    m_vtbl = &g_vtbl_143e540;
    Close();
    m_thread.Release();
    m_vtbl = &g_vtbl_13fc474;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FC80
// ---------------------------------------------------------------------------------------------
FileWatcher* FileWatcher::DestroyScalar(unsigned char flags) {
    m_vtbl = &g_vtbl_143e540;
    Close();
    m_thread.Release();
    m_vtbl = &g_vtbl_13fc474;
    if (flags & 1) operator delete(this);
    return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FCC0
// ---------------------------------------------------------------------------------------------
short* FileWatcher::Reset0() {
    *(short*)this = 0;
    return (short*)this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FCD0  EA::IO::FilePath::SafeReplace
// ---------------------------------------------------------------------------------------------
bool FilePath::SafeReplace(const unsigned short* arg0, const unsigned short* arg1,
                           const unsigned short* arg2, const unsigned short* arg3,
                           unsigned short ch0, unsigned short ch1) {
    if (arg1 == 0) {
        const unsigned short* p = arg0;
        while (*p++) {}
        arg1 = arg0 + ((p - (arg0 + 1)));
    }
    if (arg3 == 0) {
        const unsigned short* p = arg2;
        while (*p++) {}
        arg3 = arg2 + ((p - (arg2 + 1)));
    }
    int n2 = (int)(arg3 - arg2);
    const unsigned short* p1 = arg1;
    while (*p1++) {}
    int n1 = (int)(p1 - (arg1 + 1));
    if (n2 != 0) {
        if (*arg2 == ch0) ch0 = 0;
        if (arg3[-1] == ch1) ch1 = 0;
    }
    unsigned extra = (ch0 != 0) ? 1 : 0;
    if (ch1 != 0) extra++;
    int base = (int)((arg0 - mPath) ) ;
    if ((int)(extra + n1 + base + 1 + n2) > 0x208) return false;
    unsigned short* dst = (unsigned short*)arg0 + extra + n2;
    memmove(dst, arg1, n1 * 2 + 2);
    if (ch0) { *(unsigned short*)arg0 = ch0; arg0++; }
    extern void WString_insert2(void*, const void*, unsigned);
    WString_insert2((void*)&arg0, arg2, n2 * 2);
    if (ch1) dst[-1] = ch1;
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FE00  EA::IO::EnsureTrailingPathSeparator
// ---------------------------------------------------------------------------------------------
bool EnsureTrailingPathSeparator(unsigned short* path, int length) {
    if (length == -1) {
        unsigned short* p = path;
        while (*p++) {}
        length = (int)(p - (path + 1));
    }
    if (length != 0) {
        unsigned int c = path[length - 1];
        if (c == '\\' || c == '/' || c == ':') return false;
    }
    path[length] = '\\';
    path[length + 1] = 0;
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FE60  EA::IO::ConcatenatePathComponents
// ---------------------------------------------------------------------------------------------
int ConcatenatePathComponents(unsigned short* dst, const unsigned short* c1, const unsigned short* c2) {
    unsigned short* p = dst;
    if (c1) {
        const unsigned short* start = c1;
        while ((*p++ = *c1++) != 0) {}
        --p;
        if (*start != 0) {
            unsigned int c = p[-1];
            if (p == dst || (c != '\\' && c != '/' && c != ':')) *p++ = '\\';
        }
    }
    if (c2) {
        while ((*p++ = *c2++) != 0) {}
        return (int)(--p - dst);
    }
    *p = 0;
    return (int)(p - dst);
}

// ---------------------------------------------------------------------------------------------
// @ 0x0092FEE0  strip trailing path component(s); switch on component kind
// ---------------------------------------------------------------------------------------------
int StripPathComponent(unsigned short* path, int component) {
    unsigned short* p = path;
    switch (component) {
    case 1: {
        unsigned short* last = path;
        while (*p) {
            if (*p == '\\' || *p == '/' || *p == ':') {
                if (*p == ':' && (p[1] == 0 || ((p[1] == '\\' || p[1] == '/' || p[1] == ':') && p[2] == 0))) {
                    *path = 0;
                    return 0;
                }
            }
            ++p;
        }
        (void)last;
        return (int)(p - path);
    }
    case 2: case 4: case 8: case 0x10: {
        unsigned short* prev = path - 1;
        unsigned short* cur = path;
        unsigned short* cut = prev;
        while (*cur) {
            unsigned short c = *cur;
            if (c == '\\' || c == '/' || c == ':') {
                cut = cur;
            }
            prev = cur;
            ++cur;
        }
        if (component < 8 && prev + 1 == cur) cut = prev;
        cut[1] = 0;
        return (int)(cut + 1 - path);
    }
    case 0x20: {
        unsigned short* prev = path - 1;
        unsigned short* cur = path;
        unsigned short* cut = prev;
        while (*cur) {
            if (*cur == '\\' || *cur == '/' || *cur == ':') {
                cur++;
                continue;
            }
            if (*cur == '.') cut = cur;
            prev = cur;
            ++cur;
        }
        if (prev < cut) { *cut = 0; prev = cut; }
        return (int)(prev - path);
    }
    default: {
        unsigned short* start = path + 1;
        while (*path++) {}
        return (int)(path - start);
    }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00930070  EA::IO::SplitPathPtrs
// ---------------------------------------------------------------------------------------------
void SplitPathPtrs(unsigned short* path, void** pFile, void** pExt, void** pEnd) {
    unsigned short* firstSep = 0;
    unsigned short* lastSep = 0;
    unsigned short* dot = 0;
    unsigned short* p = path;
    while (*p) {
        if (*p == '\\' || *p == '/' || *p == ':') {
            if (firstSep == 0) firstSep = p;
            lastSep = p;
            dot = 0;
        }
        if (*p == '.') dot = p;
        ++p;
    }
    *pFile = path;
    if (path[0] == '\\' && path[1] == '\\') {
        p = path + 2;
        int seps = 0;
        while (*p) {
            if (*p == '\\') {
                if (++seps == 2) break;
            } else if (*p == '/' || *p == ':') {
                break;
            }
            ++p;
        }
        *pFile = p;
        if (lastSep && lastSep < p) lastSep = *p ? p : 0;
        if (dot && dot < p) dot = 0;
    } else if (firstSep && *firstSep == ':') {
        *pFile = firstSep + 1;
    }
    *pExt = *pFile;
    if (lastSep) *pExt = lastSep + 1;
    if (dot) {
        *pEnd = dot;
        return;
    }
    unsigned short* e = (unsigned short*)*pFile;
    while (*e) ++e;
    *pEnd = e;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00930070 continuation helper names referenced above
// ---------------------------------------------------------------------------------------------
