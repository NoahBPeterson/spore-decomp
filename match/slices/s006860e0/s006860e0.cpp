// Slice s006860e0: SP/EA hashtable + wstring container helpers, SP::cPropertyList
// destructor and record-stream loader (0x006860e0..0x00686d90).
// Module compiled /O2 /MD /Gy /EHsc /TP (no SSE).
#include "types.h"

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void* MemcpyT(void*, const void*, uint32_t);           // 0x011e0744
extern "C" void* MemsetT(void*, int, uint32_t);                   // 0x011e073e
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];
extern "C" char  g_fileEASTL[];
extern "C" void __cdecl ReadInt32(void*, void*, int, int);        // 0x093a780
extern "C" void __cdecl ReadByte2(void*, void*, int, int);        // 0x093a700
extern "C" void __cdecl WStrAssign(void* dst, const wchar_t* first, const wchar_t* last); // 0x0423650
extern "C" void __cdecl WideAppend(void* self, const wchar_t* first, const wchar_t* last); // 0x042f9d0
extern "C" void __cdecl FreeNodesHashtable(void*);                // 0x0685ed0
extern "C" void* __cdecl HashFind(void* out, const void* key);    // 0x0685f30
extern "C" void __cdecl HashInsert(void*, void*, const void*);    // 0x0685f90
extern "C" void __cdecl HashErase(void*, void*, void*);           // 0x06859b0
extern "C" int*  __cdecl GetManager();                            // 0x067dcd0

// ---- wide string (eastl::basic_string<wchar_t>) view, 16 bytes ----
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCap;
    uint32_t mAlloc;
    void assign(const wchar_t* first, const wchar_t* last);  // 0x0423650 (out-of-slice)
    WStr& operator=(const WStr& x) {
        if (&x != this) assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};

// 0x28-byte element: u8 + u32 + two wstrings
struct Elem {
    uint8_t flag;       // +0x00
    uint8_t pad[3];
    uint32_t f4;        // +0x04
    WStr a;             // +0x08
    WStr b;             // +0x18
    __forceinline Elem& operator=(const Elem& x) {
        flag = x.flag; f4 = x.f4; a = x.a; b = x.b;
        return *this;
    }
};

// =====================================================================
// @ 0x006860e0  copy(first,last,dst) of 0x28-byte elements
// =====================================================================
Elem* CopyElems(Elem* first, Elem* last, Elem* dst) {
    if (first != last) {
        do {
            *dst = *first;
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// =====================================================================
// @ 0x00686150  copy_backward(first,last,dstLast) of 0x28-byte elements
// =====================================================================
Elem* CopyBackElems(Elem* first, Elem* last, Elem* dstLast) {
    if (last != first) {
        do {
            --last;
            --dstLast;
            *dstLast = *last;
        } while (last != first);
        return dstLast;
    }
    return dstLast;
}

// =====================================================================
// @ 0x006861d0  hashtable find+erase of a refcounted entry (partial)
// =====================================================================
extern "C" void EraseEntry(void* key) {
    int local_8;
    HashFind(&local_8, &key);
    if (local_8 != *(int*)(*(int*)0x0152b5fc + *(int*)0x0152b600 * 4)) {
        void* p = *(void**)(local_8 + 4);
        ((void (__thiscall*)(void*))VT(p)[0x24 / 4])(p);
        int* rc = (int*)(local_8 + 8);
        *rc = *rc - 1;
        if (*rc == 0) {
            ((void (__thiscall*)(void*))VT(p)[8 / 4])(p);
            HashErase(&local_8, (void*)local_8, 0);
        }
    }
}

// =====================================================================
// @ 0x00686250  fetch wstring of global array element -> out; returns 1
// =====================================================================
bool GetElemWStr(int index, WStr* out) {
    if (index <= *(int*)0x0152b348) {
        WStr* p = (WStr*)(*(char**)0x015fea00 + 8 + index * 0x28);
        if (p->mpBegin != p->mpEnd && p != out) {
            out->assign(p->mpBegin, p->mpEnd);
        }
    }
    return true;
}

// =====================================================================
// @ 0x00686290  fill(first,last,const value&) of 0x28-byte elements
// =====================================================================
void FillElems(Elem* first, Elem* last, const Elem& value) {
    if (first != last) {
        do {
            *first = value;
            ++first;
        } while (first != last);
    }
}

// =====================================================================
// @ 0x00686320  SP::cPropertyList::~cPropertyList
// =====================================================================
struct cPropertyList {
    void* vtbl;                 // +0x00
    volatile int mRef;          // +0x04
    uint32_t f08, f0c, f10, f14;
    uint32_t f18[6];            // +0x18 (mPropertyMap)
    void* mModCount;            // +0x30 (retail: pointer to a refcounted object)
    uint32_t f34;               // +0x34
    bool Read(void* stream);    // 0x006a2f60
    cPropertyList();            // 0x006a1c40 (Editor::cPropertyList ctor, out of slice)
    ~cPropertyList();
};
cPropertyList::~cPropertyList() {
    if (mModCount != 0)
        ((void (__thiscall*)(void*))VT(mModCount)[1])(mModCount);
    FreeNodesHashtable(&f18[0]);
    vtbl = 0;
}

// =====================================================================
// @ 0x00686380  eastl::hash_map<unsigned,pair<Record*,int>>::operator[]
// =====================================================================
struct HashMap {
    uint32_t f0;
    int* buckets;               // +0x04
    int bucketCount;            // +0x08
    int* findOut(int* out, const int* key) { HashFind(out, key); return out; }
    int* operator[](const int* key);
};
int* HashMap::operator[](const int* key) {
    int local_18[6];
    HashFind(local_18, key);
    if (local_18[0] == *(int*)((char*)buckets + bucketCount * 4)) {
        local_18[0] = *key;
        local_18[1] = 0;
        local_18[2] = 0;
        HashInsert(local_18 + 3, local_18, 0);
        local_18[0] = local_18[3];
    }
    return (int*)(local_18[0] + 4);
}

// =====================================================================
// @ 0x006863e0  append a wide c-string to a fixed wide buffer
// =====================================================================
struct WFixed {
    wchar_t* mpBegin;           // +0
    wchar_t* mpEnd;             // +4
    WFixed* Append(const wchar_t* s);
    void append(const wchar_t* first, const wchar_t* last);   // 0x042f9d0 (out-of-slice)
};
WFixed* WFixed::Append(const wchar_t* s) {
    if (mpBegin != s) {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
        const wchar_t* p = s;
        while (*p) ++p;
        int n = (int)(p - s);
        append(s, s + n);
    }
    return this;
}

// =====================================================================
// @ 0x00686430  allocate+zero a flat buffer {begin,end,cap}
// =====================================================================
struct VecBuf { int* b; int* e; int* c; int* Init(uint32_t n, void* tag); };
int* VecBuf::Init(uint32_t n, void* tag) {
    (void)tag;
    void* p = n ? EASTL_alloc6(n, g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
    b = (int*)p;
    e = (int*)p;
    c = (int*)((char*)p + n);
    if (n > 0)
        MemsetT(p, 0, n);
    e = (int*)((char*)b + n);
    return (int*)this;
}

// =====================================================================
// @ 0x00686490  SP::OpenRecordAsStream
// =====================================================================
extern "C" int OpenRecordAsStream(int arg) {
    int* mgr = GetManager();
    if (mgr == 0) return -1;
    int* rec = (int*)((void* (__thiscall*)(void*, int))VT(mgr)[0x58 / 4])(mgr, arg);
    if (rec == 0) return -1;
    char buf[8];
    char ok = ((char (__thiscall*)(void*, int, void*, int, int, int))VT(rec)[0x34 / 4])
                  (rec, arg, buf, 1, 6, 1);
    if (ok) {
        int* ctr = (int*)0x015fe7b8;
        *ctr = *ctr + 1;
        int* slot = ((HashMap*)0x0152b5f8)->operator[](ctr);
        slot[0] = (int)rec;
        slot[1] = 1;
        int v = ((int (__thiscall*)(void*))VT(rec)[0x18 / 4])(rec);
        *(int*)(buf + 4) = v;
        return *ctr;
    }
    return -1;
}

// =====================================================================
// @ 0x00686520  RSA/record decode helper (partial)
// =====================================================================
__declspec(noinline) bool DecodeRecord(void* rd, int arg, uint32_t size, uint8_t flag) {
    // (full body not reconstructed; see partial.txt)
    int i0, i1;
    ReadInt32(rd, &i0, 1, 0);
    ReadInt32(rd, &i1, 1, 0);
    (void)size; (void)flag;
    return false;
}

// =====================================================================
// @ 0x006866f0  load one property-list record (Blessed-content check)
// =====================================================================
void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
bool __cdecl GetPropertyAsUint32(cPropertyList*, uint32_t id, uint32_t* out);      // 0x004af210
struct ResKey { uint32_t instance, type, group; };
bool __cdecl GetPropertyAsKey(cPropertyList*, uint32_t id, ResKey* out);          // 0x006a1250
bool __cdecl GetBoolProperty(cPropertyList*, uint32_t id, bool* out);             // 0x00407190
bool __cdecl GetPropertyAsUint32Array(cPropertyList*, uint32_t id, int* count, uint32_t** out); // 0x006a0840
uint32_t* __cdecl FindU32(uint32_t* first, uint32_t* last, const uint32_t& v);     // 0x005c1cc0
uint32_t __cdecl SPIDFromName(const char*);                                        // 0x00571cf0
void __cdecl FullPath(wchar_t* out, const wchar_t* in, int a, int b);              // 0x00930670
uint32_t __cdecl DriveHash(uint32_t drive);                                        // 0x006b8ca0
uint32_t __cdecl FNV1_String16(const wchar_t* s, uint32_t seed, int a);            // 0x00932f30
bool __cdecl RegGetU32(uint32_t root, const wchar_t* path, const wchar_t* name, uint32_t* out); // 0x006ab6c0
bool __cdecl ISteamApps(uint32_t appId);                                           // 0x006b4f40
int* __cdecl MessageServer();                                                      // 0x0067dcc0
bool __cdecl GetPropertyAsString16(cPropertyList*, uint32_t id, WStr* out);      // 0x006a1400

struct Property { char pad[0x12]; uint16_t type; int* GetInt(); uint32_t* GetUInt(); };      // 0x41e990 / 0x41ea00

// smart pointer to the property list (assignment is out of line, 0x004535d0)
struct PLPtr {
    cPropertyList* p;
    PLPtr() : p(0) {}
    void Assign(cPropertyList* q);
    ~PLPtr() { if (p) ((void (__thiscall*)(void*))VT(p)[1])(p); }
};
// pointer to a record stream; released through vtable slot 2
struct RecPtr {
    void* p;
    RecPtr() : p(0) {}
    void** Addr();                                                                          // 0x00c463d0
    ~RecPtr() { if (p) ((void (__thiscall*)(void*))VT(p)[2])(p); }
};
// request filter (vtable 0x013eb898, base IMsgHandler 0x013eb394) with an owned result array
struct KeyFilter {
    void* vtbl;
    int f4, f8, fc, f10, f14, f18, f1c, f20;
    int* begin; int* end; int* cap;
    KeyFilter() {
        begin = 0; end = 0; cap = 0;
        vtbl = (void*)0x013eb898;
        f4 = -1;
        f8 = *(int*)0x0152b544;
        f10 = -1;
        f14 = 0xb1b104;
    }
    ~KeyFilter() {
        vtbl = (void*)0x013eb394;
        if (begin && begin[-1]) EASTL_dealloc(begin);
    }
};
// empty eastl wide string (SSO-less: begin/end at the shared empty buffer)
struct WStrL : WStr {
    WStrL() { mpBegin = (wchar_t*)0x1667bac; mpEnd = (wchar_t*)0x1667bac; mpCap = (wchar_t*)0x1667bae; }
    ~WStrL();                                                                               // 0x00933960
};

static inline void* RecStream(void* r) { return ((void* (__thiscall*)(void*))VT(r)[0x18 / 4])(r); }
static inline void RecClose(void* r) { ((void (__thiscall*)(void*))VT(r)[0x24 / 4])(r); }
static inline bool SrcOpen(void* src, void* key, void** out) {
    return ((bool (__thiscall*)(void*, void*, void**, int, int, int, int))VT(src)[0x34 / 4])
        (src, key, out, 1, 6, 1, 0);
}

bool ReadPropRecords(void* src, int dflt) {
    PLPtr pl;
    uint32_t key = 0;
    bool ok = false;
    KeyFilter flt;
    int st = ((int (__thiscall*)(void*, void*, void*))VT(src)[0x30 / 4])(src, &flt.begin, &flt);
    bool success = false;
    if (st == 0) {
        success = true;
    } else if (st == 1) {
        RecPtr r1;
        if (SrcOpen(src, flt.begin, &r1.p)) {
            if (DecodeRecord(RecStream(r1.p), 0x1402de0, 0x80, 0)) {
                pl.Assign(new ("App", 0, 0, 0, 0) cPropertyList());
                ok = ((bool (__thiscall*)(void*, void*))VT(pl.p)[0x3c / 4])(pl.p, RecStream(r1.p));
                ResKey K = {0, 0, 0};
                GetPropertyAsUint32(pl.p, 0x6ef59e7, &key);
                if (!GetPropertyAsUint32(pl.p, 0x6ef59e7, &key)) {
                    if (GetPropertyAsKey(pl.p, 0x6ef59e7, &K))
                        key = K.instance;
                }
                if (ok) {
                    bool b;
                    if (*(uint32_t**)0x152b548 != *(uint32_t**)0x152b54c) {
                        if (GetBoolProperty(pl.p, 0x6ef59eb, &b) && b)
                            ok = FindU32(*(uint32_t**)0x152b548, *(uint32_t**)0x152b54c, key) != *(uint32_t**)0x152b54c;
                    }
                    if (ok) {
                        if (*(uint32_t**)0x152b5a0 != *(uint32_t**)0x152b5a4) {
                            uint32_t* arr; int cnt;
                            if (GetPropertyAsUint32Array(pl.p, 0x6ef59e6, &cnt, &arr)) {
                                ok = false;
                                for (int i = 0; i < cnt; i++) {
                                    if (FindU32(*(uint32_t**)0x152b5a0, *(uint32_t**)0x152b5a4, arr[i]) != *(uint32_t**)0x152b5a4) {
                                        ok = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (ok) {
                        if (GetBoolProperty(pl.p, 0x6ef59e8, &b) && b) {
                            ok = false;
                            ResKey B;
                            B.instance = SPIDFromName("Bless");
                            B.type = 0xb1b104;
                            B.group = 0x40004000;
                            RecPtr r2;
                            if (SrcOpen(src, &B, r2.Addr())) {
                                cPropertyList plB;
                                if (DecodeRecord(RecStream(r2.p), 0x1402e60, 0x80, 0) &&
                                    plB.Read(RecStream(r2.p))) {
                                    uint32_t u32 = 0;
                                    WStrL S1;
                                    WStrL S2;
                                    if (GetPropertyAsUint32(&plB, 0x6ef59e8, &u32) &&
                                        GetPropertyAsString16(&plB, 0x6ef59ea, &S1) &&
                                        GetPropertyAsString16(&plB, 0x6ef59e9, &S2)) {
                                        wchar_t buf[260];
                                        FullPath(buf, ((const wchar_t* (__thiscall*)(void*))VT(src)[0x28 / 4])(src), 0, 4);
                                        uint32_t seed = 0x811c9dc5;
                                        if (buf[1] == 0x3a && (buf[2] == 0x5c || buf[2] == 0x2f))
                                            seed = DriveHash(*(uint32_t*)buf);
                                        uint32_t h = FNV1_String16(S1.mpBegin, FNV1_String16(S2.mpBegin, seed, 0), 0) ^ u32;
                                        uint32_t bid;
                                        if (RegGetU32(0x80000002, S1.mpBegin, L"BlessID", &bid))
                                            ok = (h == bid);
                                    }
                                }
                                RecClose(r2.p);
                            } else {
                                if (((bool (__thiscall*)(void*, uint32_t))VT(pl.p)[0x1c / 4])(pl.p, 0x7634d70)) {
                                    void* prop = ((void* (__thiscall*)(void*, uint32_t))VT(pl.p)[0x28 / 4])(pl.p, 0x7634d70);
                                    ok = ISteamApps(*((Property*)prop)->GetUInt());
                                }
                            }
                        }
                    }
                }
            }
            RecClose(r1.p);
        }
        success = ok;
    }
    if (success) {
        int v = dflt;
        if (st == 1 && pl.p) {
            Property* pr;
            if (((bool (__thiscall*)(void*, uint32_t, Property**))VT(pl.p)[0x24 / 4])(pl.p, 0x6ef59e5, &pr) && pr->type == 9)
                v = *pr->GetInt();
        }
        int* mgr = GetManager();
        ((void (__thiscall*)(void*, int, void*, int))VT(mgr)[0x50 / 4])(mgr, 1, src, v);
        if (pl.p) {
            int* ms = MessageServer();
            ((void (__thiscall*)(void*, uint32_t, int, int, int))VT(ms)[0x18 / 4])(ms, 0x6f20a6d, 0, 0, 0);
        }
        return true;
    }
    if (key != 0) {
        for (int i = 0; i <= *(int*)0x0152b348; i++) {
            Elem* a = *(Elem**)0x015fea00;
            if (a[i].flag != 0 && a[i].f4 == key) a[i].flag = 0;
        }
    }
    ((void (__thiscall*)(void*))VT(src)[2])(src);
    return false;
}
extern "C" void ReadPropRecords2(void* self, int* rd) {
    (void)self; (void)rd;
    // (full body not reconstructed; see partial.txt)
}
