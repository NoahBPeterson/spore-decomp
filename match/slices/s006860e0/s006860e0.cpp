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
    uint32_t f34[8];            // +0x34 mDescriptions
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
extern "C" uint32_t DecodeRecord(void* rd, int arg, uint32_t size, uint8_t flag) {
    // (full body not reconstructed; see partial.txt)
    int i0, i1;
    ReadInt32(rd, &i0, 1, 0);
    ReadInt32(rd, &i1, 1, 0);
    (void)size; (void)flag;
    return 0;
}

// =====================================================================
// @ 0x006866f0  property-list record reader (partial)
// @ 0x00686d90  property-list record reader (partial)
// =====================================================================
extern "C" void ReadPropRecords(void* self, int* rd) {
    (void)self; (void)rd;
    // (full body not reconstructed; see partial.txt)
}
extern "C" void ReadPropRecords2(void* self, int* rd) {
    (void)self; (void)rd;
    // (full body not reconstructed; see partial.txt)
}
