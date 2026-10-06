// Slice s0091f520 - EA::Debug::ReportWriter diagnostic writers + related helpers.
// Optimized (/O2, no /GS cookies). Some functions carry SEH; those are approximated.
#include "types.h"

// ---------------------------------------------------------------- CRT / Win32 (IAT)
extern "C" {
__declspec(dllimport) int   __cdecl sprintf(char*, const char*, ...);
__declspec(dllimport) int   __cdecl fclose(void*);
__declspec(dllimport) int   __cdecl isprint(int);
__declspec(dllimport) void  __stdcall GetSystemInfo(void*);
__declspec(dllimport) void  __stdcall GetSystemTime(void*);
__declspec(dllimport) int   __stdcall SystemTimeToFileTime(const void*, void*);
__declspec(dllimport) void* __stdcall LoadLibraryA(const char*);
__declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
__declspec(dllimport) void* __stdcall GetCurrentProcess();
__declspec(dllimport) int   __stdcall VirtualQuery(const void*, void*, unsigned);
__declspec(dllimport) __int64 __cdecl _mktime64(void*);
__declspec(dllimport) __int64 __cdecl _time64(__int64*);
}
unsigned long __cdecl __readfsdword(unsigned);
#pragma intrinsic(__readfsdword)
void* __cdecl op_delete(void*);                       // 0x00f47380
void* __cdecl op_new(unsigned, const char*, int, int, const char*, int); // 0x00f473a0

// ---------------------------------------------------------------- fixed typing
struct FILE;
typedef unsigned long DWORD;
typedef unsigned short WORD;

struct tm {
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst;
};
struct SYSTEMTIME {
    WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
};
struct FILETIME { DWORD dwLowDateTime, dwHighDateTime; };
struct MODULEINFO {
    void*    lpBaseOfDll;   // +0
    uint32_t SizeOfImage;   // +4
    void*    EntryPoint;    // +8
};
struct MEMORY_BASIC_INFORMATION {
    void*  BaseAddress;      // +0
    void*  AllocationBase;   // +4
    DWORD  AllocationProtect;
    DWORD  RegionSize;       // +0xc  (page size read at local_b4+4 later; see wrapper)
};

// ---------------------------------------------------------------- interfaces
// Diagnostic report writer (vtable slots 0x18..0x34 used).
struct ReportWriter {
    virtual void v00();                              // 0x00
    virtual void v04();                              // 0x04
    virtual int  v08(int, int);                      // 0x08
    virtual int  v0c(int);                           // 0x0c
    virtual int  v10(int, int*);                     // 0x10
    virtual int  v14(int);                           // 0x14
    virtual void v18(const char*);                   // 0x18
    virtual void v1c(const char*);                   // 0x1c
    virtual void v20(const char*, int);              // 0x20
    virtual void v24(const char*, ...);              // 0x24 (variadic -> cdecl, this first)
    virtual void v28(const char*, const char*);      // 0x28
    virtual void v2c();                              // 0x2c
    virtual int  v30();                              // 0x30
    virtual void v34(const char*, int);              // 0x34

    bool WriteMemoryView(uint8_t* base, int len, uint8_t* mark, const char* label); // 0x0091f520
    bool WriteStackMemoryView(unsigned lo, int len);                                 // 0x0091fe60
    bool WriteRegisterMemoryView(int* ctx);                                          // 0x0091fbd0
    bool WriteRegisterValues(int* ctx);                                              // 0x0091fa10
};

// generic object manager used by the small virtual forwarders
struct Mgr {
    virtual void m00();                    // 0x00
    virtual void m04();                    // 0x04
    virtual int  m08(int, int);            // 0x08
    virtual int  m0c(int);                 // 0x0c
    virtual int  m10();                    // 0x10
    virtual int  m14(int);                 // 0x14
    virtual int  m18();                    // 0x18
    virtual int  m1c(int, int, int);       // 0x1c
    virtual int  m20();                    // 0x20
    virtual int  m24(int, int, int);       // 0x24

    int Create(int a1, int a2, Mgr* a3);            // 0x009200d0
    int Factory24(int a1, int a2, int a3, int a4);  // 0x00920110
    int Factory1c(int a1, int a2, int a3, int a4);  // 0x00920240
};

extern DWORD g_pageSize;   // 0x01667b80

// ---------------------------------------------------------------- file writer
struct FileReportWriter {
    virtual ~FileReportWriter();
    char pad[0x100];
    FILE* mFile;   // +0x104
};
FileReportWriter::~FileReportWriter()
{
    if (mFile) fclose(mFile);
}

// ---------------------------------------------------------------- simple forwarders
// @ 0x009200b0
int __stdcall CallRefCtor(Mgr* p)
{
    if (p != 0) {
        int r = p->m0c(1);
        if (r != 0) return r;
    }
    return 0;
}

// @ 0x009200d0
int Mgr::Create(int a1, int a2, Mgr* a3)
{
    if (a3 == 0)
        a3 = (Mgr*)m14(a1);
    if (a3 != 0)
        return a3->m08(a1, a2);
    return 0;
}

// @ 0x00920110
int Mgr::Factory24(int a1, int a2, int a3, int a4)
{
    Mgr* p = (Mgr*)m24(a1, a3, a4);
    if (p != 0) {
        int r = p->m0c(a2);
        if (r != 0) return r;
        p->m00();
        p->m04();
    }
    return 0;
}

// @ 0x00920240
int Mgr::Factory1c(int a1, int a2, int a3, int a4)
{
    Mgr* p = (Mgr*)m1c(a1, a3, a4);
    if (p != 0) {
        int r = p->m0c(a2);
        if (r != 0) return r;
        p->m00();
        p->m04();
    }
    return 0;
}

// ---------------------------------------------------------------- register dumps
// @ 0x0091fbd0
bool ReportWriter::WriteRegisterMemoryView(int* ctx)
{
    unsigned u;
    u = *(unsigned*)((char*)ctx + 0xb0);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "eax ");
    u = *(unsigned*)((char*)ctx + 0xa4);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "ebx ");
    u = *(unsigned*)((char*)ctx + 0xac);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "ecx ");
    u = *(unsigned*)((char*)ctx + 0xa8);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "edx ");
    u = *(unsigned*)((char*)ctx + 0xa0);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "esi ");
    u = *(unsigned*)((char*)ctx + 0x9c);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "edi ");
    u = *(unsigned*)((char*)ctx + 0xb4);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "ebp ");
    return true;
}

// @ 0x0091fa10
bool ReportWriter::WriteRegisterValues(int* ctx)
{
    char buf[96];
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xb8)); v28("eip", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xb0)); v28("eax", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xa4)); v28("ebx", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xac)); v28("ecx", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xa8)); v28("edx", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xa0)); v28("esi", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0x9c)); v28("edi", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xb4)); v28("ebp", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xc0)); v28("efl", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xc4)); v28("esp", buf);
    return true;
}

// ---------------------------------------------------------------- process / time
// @ 0x0091ff50
void GetUptime(unsigned* out)
{
    tm t;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_yday = 0;
    t.tm_isdst = 0;
    t.tm_mon = 0;
    t.tm_year = 0x69;
    t.tm_mday = 1;
    t.tm_wday = 6;
    __int64 a = _mktime64(&t);
    __int64 b = _time64(0);
    *out = (unsigned)((int)b - (int)a) & 0x7fffffff;
}

// @ 0x0091ffd0
void GetTickCount100ns(uint32_t* out)
{
    SYSTEMTIME now;
    FILETIME nowFt, epochFt;
    GetSystemTime(&now);
    SYSTEMTIME epoch;
    epoch.wYear = 0x7d5;
    epoch.wMonth = 1;
    epoch.wDayOfWeek = 6;
    epoch.wDay = 1;
    epoch.wHour = 0;
    epoch.wMinute = 0;
    epoch.wSecond = 0;
    epoch.wMilliseconds = 0;
    SystemTimeToFileTime(&now, &nowFt);
    SystemTimeToFileTime(&epoch, &epochFt);
    __int64 diff = *(__int64*)&nowFt - *(__int64*)&epochFt;
    diff = diff / 10;
    out[1] = (uint32_t)(diff >> 32) & 0x0fffffff;
    out[0] = (uint32_t)diff;
}

// ---------------------------------------------------------------- stack memory view
// @ 0x0091fe60
bool ReportWriter::WriteStackMemoryView(unsigned lo, int len)
{
    unsigned stackLo = __readfsdword(4);
    unsigned stackHi = __readfsdword(8);
    unsigned a = lo - len;
    unsigned start = (a <= stackHi) ? stackHi : a;
    unsigned b = lo + len;
    unsigned end = (stackLo <= b) ? stackLo : b;
    start &= 0xfffffff0;
    end = (end + 0xf) & 0xfffffff0;
    if (stackHi <= lo && lo < stackLo && start < end) {
        WriteMemoryView((uint8_t*)start, (int)(end - start), (uint8_t*)lo, 0);
        return true;
    }
    v20("Stack pointer appears to point to invalid memory.\r\n", 0);
    return true;
}

// ---------------------------------------------------------------- module list
struct SYSTEM_INFO2 {
    uint32_t dwOemId, dwPageSize;
};

// @ 0x0091f520  (hex/ASCII memory dump; SEH-free reconstruction)
bool ReportWriter::WriteMemoryView(uint8_t* base, int len, uint8_t* mark, const char* label)
{
    if (g_pageSize == 0) {
        SYSTEM_INFO2 si;
        GetSystemInfo(&si);
        g_pageSize = si.dwPageSize;
    }
    int labelLen = 0;
    if (label) {
        const char* p = label;
        do { } while (*p++);
        labelLen = (int)(p - label - 1);
    }
    uint8_t* line = (uint8_t*)((unsigned)base & 0xfffffff0);
    int lineNo = 0;
    uint32_t pageLeft = 0;
    bool readable = true;
    char hex[64];
    char ascii[20];
    while (line < base + len) {
        sprintf(hex, "%08x |", (unsigned)line);
        uint8_t* q = line;
        while (q < line + 0x10) {
            if (pageLeft == 0) {
                MEMORY_BASIC_INFORMATION mbi;
                if (VirtualQuery(q, &mbi, 0x1c) == 0)
                    readable = false;
                else if (mbi.AllocationProtect == 0x1000 && (mbi.RegionSize & 0x66) != 0)
                    readable = true;
                else
                    readable = false;
                pageLeft = g_pageSize - ((unsigned)q % g_pageSize);
            }
            int off = (int)(q - line);
            char arrow;
            if (q == mark) arrow = '<';
            else arrow = (q != mark + 1) ? ' ' : '>';
            if ((unsigned)q < (unsigned)base || (unsigned)q >= (unsigned)base + len) {
                sprintf(hex + off * 3, "    ");
                ascii[off] = ' ';
            } else if (!readable) {
                sprintf(hex + off * 3, "%c??", arrow);
                ascii[off] = '?';
            } else {
                sprintf(hex + off * 3, "%c%02x", arrow, *q);
                ascii[off] = isprint(*q) ? (char)*q : '.';
            }
            --pageLeft;
            ++q;
        }
        ascii[0x10] = 0;
        if (label) {
            if (lineNo == 0) v24(label, 0);
            else for (int i = 0; i < labelLen; i++) v34("\r\n", 1);
        }
        v20(hex, 0);
        line += 0x10;
        ++lineNo;
    }
    return true;
}

// @ 0x0091f7c0  (psapi module enumeration)
typedef int (__stdcall *EnumProcessModules_t)(void*, void**, unsigned, unsigned*);
typedef int (__stdcall *GetModuleFileNameExA_t)(void*, void*, char*, unsigned);
typedef int (__stdcall *GetModuleBaseNameA_t)(void*, void*, char*, unsigned);
typedef int (__stdcall *GetModuleInformation_t)(void*, void*, void*, unsigned);

bool ReportWriter_WriteModuleList(ReportWriter* self)
{
    void* h = LoadLibraryA("psapi.dll");
    if (!h) {
        self->v20("Failed to load psapi.dll.\r\n", 0);
        return false;
    }
    EnumProcessModules_t      epm = (EnumProcessModules_t)GetProcAddress(h, "EnumProcessModules");
    GetModuleFileNameExA_t    gmf = (GetModuleFileNameExA_t)GetProcAddress(h, "GetModuleFileNameExA");
    GetModuleBaseNameA_t      gmb = (GetModuleBaseNameA_t)GetProcAddress(h, "GetModuleBaseNameA");
    GetModuleInformation_t    gmi = (GetModuleInformation_t)GetProcAddress(h, "GetModuleInformation");
    (void)gmf; (void)gmb; (void)gmi;
    void* proc = GetCurrentProcess();
    void* mods[256];
    unsigned needed = 0;
    if (!epm(proc, mods, sizeof(mods), &needed)) {
        self->v20("Failed to enumerate modules.\r\n", 0);
        return true;
    }
    unsigned count = needed >> 2;
    if (count > 0x100) {
        self->v20("Module count exceeds our enumeration limit of 256. Only 256 will be displayed.\r\n", 0);
        count = 0x100;
    }
    for (unsigned i = 0; i < count; ++i) {
        char baseName[0x104];
        char path[0x104];
        char out[0x200];
        MODULEINFO mi;
        if (!gmi(proc, mods[i], &mi, sizeof(mi))) {
            mi.lpBaseOfDll = 0; mi.SizeOfImage = 0; mi.EntryPoint = 0;
        }
        if (!gmb(proc, mods[i], baseName, 0x104)) {
            baseName[0] = 0;
        }
        if (!gmf(proc, mods[i], path, 0x104)) {
            path[0] = 0;
        }
        sprintf(out, "base 0x%08x size 0x%08x entry 0x%08x %-48s %s",
                (unsigned)mi.lpBaseOfDll, mi.SizeOfImage, (unsigned)mi.EntryPoint, baseName, path);
        self->v20(out, 1);
    }
    return true;
}

// @ 0x0091fca0  (callstack dump)
extern "C" unsigned __cdecl CS_GetCallstack(uint32_t*, int, void*); // 0x0091b3d0
extern "C" void*    __cdecl CS_a1c0();                              // 0x0091a1c0
extern "C" void     __cdecl CS_b2f0(void*);                          // 0x0091b2f0
extern "C" unsigned __cdecl CS_b0f0(int, uint32_t, void*, void*, int); // 0x0091b0f0
extern "C" void     __cdecl CS_b580(uint32_t, char*, int);           // 0x0091b580
extern "C" void     __cdecl CS_dtor(void*);                          // 0x0091b090

bool ReportWriter_WriteCallStack(ReportWriter* self, int* ctx)
{
    uint32_t frame[3];
    frame[0] = *(uint32_t*)((char*)ctx + 0xb8);
    frame[1] = *(uint32_t*)((char*)ctx + 0xb4);
    frame[2] = *(uint32_t*)((char*)ctx + 0xc4);
    uint32_t addrs[0x80];
    unsigned n = CS_GetCallstack(addrs, 0x80, frame);
    if (n == 0) {
        self->v20("Callstack not available\r\n", 0);
        return true;
    }
    void* cache = CS_a1c0();
    char repc[0x400];
    CS_b2f0(repc);
    if (cache == 0) cache = repc;
    for (unsigned i = 0; i < n; ++i) {
        char line[0x200];
        uint32_t flags = CS_b0f0(0xf, addrs[i], &frame[0], &frame[1], 1);
        self->v18("Callstack entry");
        CS_b580(addrs[i], line, 0x200);
        self->v20(line, 1);
        if (flags & 8) self->v20((const char*)frame[0], 1);
        if (flags & 1) self->v24("%s: %d\r\n", frame[0], frame[1]);
        if (flags & 2) self->v24("%s + %d\r\n", frame[2], frame[1]);
        if (flags & 4) self->v20((const char*)frame[1], 1);
        self->v1c("Callstack entry");
    }
    CS_dtor(repc);
    return true;
}

// ---------------------------------------------------------------- EASTL hashtable (12-byte key)
struct HTNode {
    uint32_t k0, k1, k2;
    HTNode*  next;   // +0xc
};
struct HTable {
    uint32_t pad0;          // +0
    HTNode** buckets;       // +4
    uint32_t bucketCount;   // +8
    uint32_t count;         // +0xc
    uint32_t pad10;         // +0x10
};
extern "C" void __cdecl HT_PreRehash(void*, uint32_t, uint32_t, int); // 0x00921440
extern "C" void __cdecl HT_EraseKey(HTNode*);                          // 0x00920290
extern "C" void __cdecl EastlHashDoFreeNodes(void*, void*);            // 0x007611f0
extern "C" void __cdecl Sub_93dc70(void*, void*);                      // 0x0093dc70
extern "C" void __cdecl Sub_922310(void*);                             // 0x00922310

// @ 0x00920410
void __fastcall HT_Destroy(HTNode** self)
{
    self[0] = (HTNode*)0x0143d824;
    EastlHashDoFreeNodes(self[0x4b], self[0x4c]);
    self[0x4d] = 0;
    if ((uint32_t)self[0x4c] > 1)
        op_delete(self[0x4b]);
    Sub_93dc70(self[0x43], self[0x44]);
    self[0x45] = 0;
    if ((uint32_t)self[0x44] > 1)
        op_delete(self[0x43]);
    Sub_922310((char*)self + 8);
}

// @ 0x00920490
HTNode* HT_Insert(HTable* self, HTNode** out, uint32_t* key)
{
    uint8_t rehash[8];
    HT_PreRehash(rehash, self->bucketCount, self->count, 1);
    if (rehash[0] != 0)
        HT_EraseKey((HTNode*)*(uint32_t*)&rehash[4]);
    uint32_t first = key[0];
    HTNode* node = (HTNode*)op_new(0x10, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (node) { node->k0 = key[0]; node->k1 = key[1]; node->k2 = key[2]; }
    node->next = 0;
    uint32_t slot = first % self->bucketCount;
    HTNode* cur = self->buckets[slot];
    if (cur) {
        for (;;) {
            if (*key == cur->k0) {
                node->next = cur->next;
                cur->next = node;
                goto done;
            }
            cur = cur->next;
            if (!cur) break;
        }
    }
    node->next = self->buckets[slot];
    self->buckets[slot] = node;
done:
    self->count++;
    *out = node;
    out[1] = (HTNode*)&self->buckets[slot];
    return (HTNode*)out;
}

// @ 0x00920560  (string-keyed find)
struct HTStrNode {
    void*          key;    // +0
    uint32_t       a, b, c;
    HTStrNode*     next;   // +0x10
};
struct HTStr {
    uint32_t    pad0;
    HTStrNode** buckets;   // +4
    uint32_t    bucketCount; // +8
};
struct HTStrIter { HTStrNode* node; HTStrNode** slot; };

void HTStr_Find(HTStr* self, HTStrIter* out, void** pkey)
{
    const uint8_t* s = (const uint8_t*)*pkey;
    uint32_t h = 0x811c9dc5;
    uint8_t c = *s;
    while (c != 0) {
        s++;
        h = h * 0x1000193 ^ c;
        c = *s;
    }
    uint32_t slot = h % self->bucketCount;
    HTStrNode** slotPtr = &self->buckets[slot];
    HTStrNode* cur = self->buckets[slot];
    while (cur) {
        if (*pkey == cur->key) goto found;
        cur = cur->next;
    }
    slotPtr = &self->buckets[self->bucketCount];
    cur = *slotPtr;
found:
    out->node = cur;
    out->slot = slotPtr;
}

// ---------------------------------------------------------------- misc structs/helpers
extern "C" __declspec(dllimport) int __cdecl strcmp(const char*, const char*);

// @ 0x00920160  (name lookup over a handle table)
struct NTbl {
    virtual void  n00();                        // 0x00
    virtual int   n04(void*, int);              // 0x04
    virtual int   n08(int, int);                // 0x08
    virtual void* n0c(int);                     // 0x0c
    virtual int   n10(const char*, void*);      // 0x10
};

int MgrFindByName(NTbl* self, const char* name, int, NTbl* tbl)
{
    unsigned found = 0;
    unsigned handles[0x80];
    if (tbl == 0) {
        tbl = (NTbl*)self->n10(name, &found);
    } else {
        unsigned n = (unsigned)tbl->n04(handles, 0x80);
        if (n != 0) {
            unsigned i = 0;
            do {
                const char* nm = (const char*)tbl->n0c((int)handles[i]);
                if (strcmp(name, nm) == 0) { found = handles[i]; break; }
                ++i;
            } while (i < n);
            if (i == n) return 0;
        }
    }
    if (tbl == 0) return 0;
    return tbl->n08((int)found, 0);
}