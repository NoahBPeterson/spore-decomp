// Slice s00acb1b0: vector/EASTL range helpers (0x145a184 class).
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void  __cdecl FUN_00829110(void* a, void* b, void* c, void* d, void* e);
void* __cdecl FUN_00ac96b0(void* a, void* b, void* c);
void* __cdecl FUN_00f9b050(void* a, void* b, void* c);
void  __cdecl FUN_00c50ad0(void* a, void* b, void* c);
void* __cdecl FUN_00ac9740(void* a, void* b, void* c);
void* __cdecl FUN_00ac89e0(void* a, void* b, void* c);
void* __cdecl FUN_00ac9200(void* src);

// 0x2c-byte element type; its element copy-ctor is 0x00ac9200 (thiscall, ecx = dest).
struct Elem2c { uchar raw[0x2c]; void FUN_00ac9200(Elem2c* src); };
static void Elem2c_ctor(void* dest, void* src) {
    ((Elem2c*)dest)->FUN_00ac9200((Elem2c*)src);
}

// ---- EASTL range helpers (each is a real function in the binary) -----------
// uninitialized_copy(begin, end, outIter) -> updated out-iterator record
void* __cdecl FUN_00ac95f0(void* outIter, void* begin, void* initVal, void* end);
void* __cdecl FUN_00ac94c0(void* outIter, void* begin, void* initVal, void* end, void* extra);
// fill_n
void  __cdecl FUN_00ac9680(void* dest, int n, const void* val);        // 4-stride
void  __cdecl FUN_00ac9560(void* dest, int n, const void* val);        // 0c-stride
// assign(begin, end, val) / move_backward(begin, end, dest)
void* __cdecl FUN_00ac9630(void* begin, void* end, void* val);
void* __cdecl FUN_00ac9510(void* begin, void* end, void* val);
void* __cdecl FUN_00ac8a30(void* begin, void* end, void* dest);
void* __cdecl FUN_00ac97f0(void* begin, void* end, void* dest);
void* __cdecl FUN_00ac89a0(void* begin, void* end, void* dest);
void* __cdecl FUN_00ac95a0(void* begin, void* end, void* dest);        // 0c-stride
void* __cdecl FUN_011e0744(void* begin, void* end, void* dest);        // 4-stride memcpy

// 4-byte refcounted element (EA::AutoRefCount<T>): +0 = object pointer.
struct RefPtr {
    void* mpObject;
};
void __cdecl FUN_00a02c30(void* obj);   // addref  (thiscall-style, ecx = obj)
void __cdecl FUN_00a05270(void* obj);   // release (thiscall-style, ecx = obj)
struct Elem4 { RefPtr p; };

// 0xc-byte element with vtable 0x145a158: +0 vptr, +4 byte, +8 refcounted ptr.
struct ElemC {
    void** vptr;      // +0
    uchar  flag;      // +4
    uchar  pad5[3];
    void*  ref;       // +8
};

// ---------------------------------------------------------------------------
// EASTL string16 (basic_string<wchar_t>) minimal model.
// Layout: { mpBegin, mpEnd, mpCapacity } (+0/+4/+8); SSO marks the begin pointer
// with the low bit.  Length = (end - begin) & ~1 (in bytes) / 2.
// POD on purpose: the originals destroy the temporaries with explicit calls, so
// no automatic (unwinding) destructor may exist or cl emits an SEH prologue.
// ---------------------------------------------------------------------------
struct String16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
};
String16 __cdecl FUN_0093c5a0(const char* s, int len);   // EA::ConvertToString16
String16 __cdecl FUN_00579a90(const wchar_t* s);         // RangeInitialize(empty)
void __cdecl FUN_0056e2d0(String16* out, const String16* src);

static const wchar_t* s16(const String16& s) {
    return s.mpBegin == s.mpEnd ? 0 : (const wchar_t*)((char*)s.mpBegin + ((size_t)s.mpBegin & 1));
}
static void destroy16(String16& s) {
    if (s.mpBegin && (((char*)s.mpEnd - (char*)s.mpBegin) & ~1) > 2)
        operator_delete(s.mpBegin);
    s.mpBegin = 0; s.mpEnd = 0; s.mpCapacity = 0;
}

// The archive/serializer object the container writers drive through its vtable.
struct Archive {
    virtual bool v0(const wchar_t* name);
    virtual bool v1(const wchar_t* name);
    virtual bool v2(const wchar_t* name);
    virtual bool v3(const wchar_t* name);
    virtual bool v4(const wchar_t* name);
};
extern "C" const wchar_t DAT_013f6254[];   // L"map"
extern "C" const wchar_t DAT_013f5890[];   // L"int32_t"
extern "C" void* const DAT_0145a158;       // Element vtable for the 0xc-stride container

bool  __cdecl FUN_00ac8050(Archive* ar, int unused, const void* name);
bool  __cdecl FUN_0057c770(Archive* ar, int unused, const void* value, const wchar_t* type);

// generic thiscall stubs
struct XC {
    void  FUN_00aca9d0(void*);
    void  FUN_00b93c60(uint, void*);
    void  FUN_00a05270();
    void  FUN_00a02c30();
};

// thiscall member functions of the vector-owner class
struct VO {
    int* v;                       // +0 begin
    void* FUN_00acb490(int* src); // 00acb490
    void  FUN_00acb680(uchar* pos, uchar* val);
    void  FUN_00acb7c0(void* a2, void* a3);
    void  FUN_00acb810(uchar* pos, uchar* val);
    void  FUN_00acb930(int a2, int a3, int a4);
    void* FUN_00acbaf0(int* src);
    int*  FUN_00acbd90(int* other);
    int   FUN_00acbed0(int a2, int a3);
    void  FUN_00acbf30(int a2, uint a3, int a4);
    void* FUN_00acaa50(uint n, void* a, void* b);
    void  FUN_00ac8930(void* a, void* b);
};

// free (cdecl) functions
char FUN_00acb1b0(int* obj, int p2, int p3);          // 00acb1b0
char FUN_00acb340(int* obj, int p2, int* p3);         // 00acb340
void* FUN_00acbb20(uchar* p, uchar* end, uchar* out); // 00acbb20
char FUN_00acbc10(int* obj, int p2, int p3);          // 00acbc10

// @ 0x00acb490
void* VO::FUN_00acb490(int* src) {
    int* p = (int*)this;
    int tmp = (int)src;
    p[0] = 0x145a184;
    p[1] = src[1];
    p[2] = src[2];
    p[3] = src[3];
    p[4] = src[4];
    ((XC*)((uchar*)p + 0x14))->FUN_00b93c60((src[6] - src[5]) >> 2, (uchar*)src + 0x20);
    FUN_00829110(&tmp, (void*)src[5], (void*)src[6], (void*)p[5], (void*)tmp);
    p[6] = tmp;
    ((XC*)((uchar*)p + 0x28))->FUN_00b93c60((src[11] - src[10]) >> 2, (uchar*)src + 0x34);
    FUN_00829110(&tmp, (void*)src[10], (void*)src[11], (void*)p[10], (void*)tmp);
    p[0xb] = tmp;
    ((XC*)((uchar*)p + 0x3c))->FUN_00b93c60((src[0x10] - src[0xf]) >> 2, (uchar*)src + 0x48);
    FUN_00829110(&tmp, (void*)src[0xf], (void*)src[0x10], (void*)p[0xf], (void*)tmp);
    p[0x10] = tmp;
    ((XC*)((uchar*)p + 0x50))->FUN_00b93c60((src[0x15] - src[0x14]) >> 2, (uchar*)src + 0x5c);
    FUN_00829110(&tmp, (void*)src[0x14], (void*)src[0x15], (void*)p[0x14], (void*)tmp);
    p[0x15] = tmp;
    return p;
}

// @ 0x00acb680
void VO::FUN_00acb680(uchar* pos, uchar* val) {
    int* v = (int*)this;
    uchar* cur = (uchar*)v[1];
    if (cur != (uchar*)v[2]) {
        if (pos <= val && val < cur) val += 0x14;
        if (cur) memcpy(cur, cur - 0x14, 0x14);
        FUN_00c50ad0(pos, (void*)(v[1] - 0x14), (void*)v[1]);
        memcpy(pos, val, 0x14);
        v[1] += 0x14;
        return;
    }
    int n = (int)(cur - (uchar*)v[0]) / 0x14;
    int cap = n ? n * 2 : 1;
    uchar* mem = cap ? (uchar*)operator_new(cap * 0x14, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    uchar* p1 = (uchar*)FUN_00f9b050((void*)v[0], pos, mem);
    if (p1) memcpy(p1, val, 0x14);
    uchar* p2 = (uchar*)FUN_00f9b050(pos, (void*)v[1], p1 + 0x14);
    void* old = (void*)v[0];
    if (old && *(int*)((char*)old - 4) != 0) operator_delete(old);
    v[0] = (int)mem;
    v[1] = (int)p2;
    v[2] = (int)(mem + cap * 0x14);
}

// @ 0x00acb7c0
void VO::FUN_00acb7c0(void* a2, void* a3) {
    int* p = (int*)this;
    int* it = (int*)FUN_00ac89e0(a3, *(void**)((uchar*)p + 4), a2);
    int* end = *(int**)((uchar*)p + 4);
    for (; it < end; it++) {
        if (*it) ((XC*)*it)->FUN_00a05270();
    }
    int n = (int)((char*)a3 - (char*)a2) >> 2;
    *(int*)((uchar*)p + 4) -= n * 4;
}

// @ 0x00acb810  (vector<0x2c> insert(pos, val))
void VO::FUN_00acb810(uchar* pos, uchar* val) {
    int* v = (int*)this;
    uchar* end = (uchar*)v[1];
    if (end != (uchar*)v[2]) {
        if (pos <= val && val < end) val += 0x2c;
        if (end) ((Elem2c*)end)->FUN_00ac9200((Elem2c*)(end - 0x2c));
        uchar* d = end - 0x2c;
        while (d != pos) {
            d -= 0x2c;
            memcpy(d + 0x2c, d, 0x2c);
        }
        memcpy(pos, val, 0x2c);
        v[1] += 0x2c;
        return;
    }
    int n = (int)(end - (uchar*)v[0]) / 0x2c;
    int cap = n ? n * 2 : 1;
    uchar* mem = cap ? (uchar*)operator_new(cap * 0x2c, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    uchar* p1 = (uchar*)FUN_00ac96b0((void*)v[0], pos, mem);
    if (p1) ((Elem2c*)p1)->FUN_00ac9200((Elem2c*)val);
    uchar* p2 = (uchar*)FUN_00ac96b0(pos, (void*)v[1], p1 + 0x2c);
    void* old = (void*)v[0];
    if (old && *(int*)((char*)old - 4) != 0) operator_delete(old);
    v[0] = (int)mem;
    v[1] = (int)p2;
    v[2] = (int)(mem + cap * 0x2c);
}

// @ 0x00acb930  (vector<EA::AutoRefCount<T>> insert(pos, n, val))
void VO::FUN_00acb930(int a2, int a3, int a4) {
    int* v = (int*)this;
    RefPtr* pos = (RefPtr*)a2;
    int     n   = a3;
    RefPtr* val = (RefPtr*)a4;
    int spare = (v[2] - v[1]) >> 2;
    if ((uint)n > (uint)spare) {
        int size = (v[1] - v[0]) >> 2;
        int cap  = size ? size * 2 : 1;
        int want = size + n;
        int newcap = cap > want ? cap : want;
        RefPtr* mem = newcap ? (RefPtr*)operator_new(newcap * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        memcpy(mem, (void*)v[0], (char*)pos - (char*)v[0]);
        RefPtr* it = (RefPtr*)((char*)mem + ((char*)pos - (char*)v[0]));
        FUN_00ac9680(it, n, val);
        it += n;
        memcpy(it, pos, (char*)v[1] - (char*)pos);
        it = (RefPtr*)((char*)it + ((char*)v[1] - (char*)pos));
        if (v[0] && *(int*)(v[0] - 4) != 0) operator_delete((void*)v[0]);
        v[0] = (int)mem;
        v[1] = (int)it;
        v[2] = (int)(mem + newcap);
        return;
    }
    if (n <= 0) return;

    RefPtr tmp;
    tmp.mpObject = val->mpObject;
    if (tmp.mpObject) ((XC*)tmp.mpObject)->FUN_00a02c30();

    int     after = (v[1] - a2) >> 2;
    RefPtr* end   = (RefPtr*)v[1];
    if (n < after) {
        RefPtr* src = end - n;
        RefPtr* it  = end;
        FUN_00ac95f0(&it, src, end, end);
        v[1] += n * 4;
        FUN_00ac8a30(it, src, end);
        FUN_00ac9630(it, it + n, &tmp);
    } else {
        int m = n - after;
        FUN_00ac9680(end, m, &tmp);
        v[1] += m * 4;
        RefPtr* it = (RefPtr*)v[1];
        FUN_00ac95f0(&it, end - after, end, (RefPtr*)v[1]);
        v[1] += after * 4;
        FUN_00ac9630(it, end, &tmp);
    }
    if (tmp.mpObject) ((XC*)tmp.mpObject)->FUN_00a05270();
}

// @ 0x00acbaf0
void* VO::FUN_00acbaf0(int* src) {
    uchar* d = (uchar*)this;
    *(int*)d = *src;
    *(void**)(d + 4) = (void*)0x145a164;
    *(d + 8) = *(uchar*)((uchar*)src + 8);
    *(d + 9) = *(uchar*)((uchar*)src + 9);
    ((XC*)(d + 0xc))->FUN_00aca9d0((uchar*)src + 0xc);
    return d;
}

// @ 0x00acbd90
int* VO::FUN_00acbd90(int* other) {
    int* v = (int*)this;
    if (other != v) {
        int src0 = *other;
        uint n2 = (other[1] - src0) / 0xc;
        int dst0 = *v;
        if ((uint)((v[2] - dst0) / 0xc) < n2) {
            int mem = (int)FUN_00acaa50(n2, (void*)src0, (void*)other[1]);
            FUN_00ac8930((void*)*v, (void*)v[1]);
            int old = *v;
            if (old && *(int*)(old - 4) != 0) operator_delete((void*)old);
            v[2] = mem + n2 * 0xc;
            *v = mem;
            v[1] = mem + n2 * 0xc;
            return v;
        }
        uint u3 = (v[1] - dst0) / 0xc;
        if (u3 < n2) {
            FUN_00ac9740((void*)src0, (void*)(src0 + u3 * 0xc), (void*)dst0);
            int p = other[1];
            int tmp = p;
            FUN_00ac94c0(&tmp, (void*)(*other + ((v[1] - *v) / 0xc) * 0xc), (void*)p, (void*)v[1], (void*)p);
            v[1] = *v + n2 * 0xc;
            return v;
        }
        int r = (int)FUN_00ac9740((void*)src0, (void*)other[1], (void*)dst0);
        FUN_00ac8930((void*)r, (void*)v[1]);
        v[1] = *v + n2 * 0xc;
    }
    return v;
}

// @ 0x00acbed0
int VO::FUN_00acbed0(int a2, int a3) {
    int* p = (int*)this;
    int* it = (int*)FUN_00ac9740((void*)a3, *(void**)((uchar*)p + 4), (void*)a2);
    int* end = *(int**)((uchar*)p + 4);
    for (; it < end; it += 3) {
        void*** obj = (void***)it;
        ((void (__thiscall*)(void*, int))((*obj)[0]))(obj, 0);
    }
    int n = (a2 - a3) / 0xc;
    *(int*)((uchar*)p + 4) += n * 0xc;
    return a2;
}

// @ 0x00acbf30  (vector<0xc> insert(pos, n, val))
void VO::FUN_00acbf30(int a2, uint a3, int a4) {
    int*  v   = (int*)this;
    ElemC* pos = (ElemC*)a2;
    int    n   = (int)a3;
    ElemC* val = (ElemC*)a4;
    int spare = (int)((uint)(v[2] - v[1]) / 0xc);
    if ((uint)n > (uint)spare) {
        int size = (int)((uint)(v[1] - v[0]) / 0xc);
        int cap  = size * 2;
        if (cap == 0) cap = 1;
        int want = size + n;
        int newcap = cap > want ? cap : want;
        ElemC* mem = newcap ? (ElemC*)operator_new(newcap * 0xc, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        ElemC* it = (ElemC*)FUN_00ac95a0((void*)v[0], pos, mem);
        FUN_00ac9560(it, n, val);
        ElemC* after = (ElemC*)((char*)it + n * 0xc);
        ElemC* stop  = (ElemC*)FUN_00ac95a0(pos, (void*)v[1], after);
        if (v[0] && *(int*)(v[0] - 4) != 0) operator_delete((void*)v[0]);
        v[0] = (int)mem;
        v[1] = (int)stop;
        v[2] = (int)(mem + newcap * 0xc);
        return;
    }
    if (n <= 0) return;

    ElemC tmp;
    tmp.vptr = (void**)&DAT_0145a158;
    tmp.flag = val->flag;
    tmp.ref  = val->ref;
    if (tmp.ref) ((void (__thiscall*)(void*))((void**)tmp.ref)[0])(tmp.ref);

    int    after = (int)((uint)(v[1] - a2) / 0xc);
    ElemC* end   = (ElemC*)v[1];
    if (n < after) {
        ElemC* src = end - n;
        ElemC* it  = end;
        FUN_00ac94c0(&it, src, end, end, src);
        v[1] += n * 0xc;
        FUN_00ac97f0(it, src, end);
        FUN_00ac9510(it, it + n, &tmp);
    } else {
        int m = n - after;
        FUN_00ac9560(end, m, &tmp);
        v[1] += m * 0xc;
        ElemC* it = (ElemC*)v[1];
        FUN_00ac94c0(&it, end - after, end, (ElemC*)v[1], end - after);
        v[1] += after * 0xc;
        FUN_00ac9510(it, end, &tmp);
    }
    if (tmp.ref) ((void (__thiscall*)(void*))((void**)tmp.ref)[1])(tmp.ref);
}

// @ 0x00acb1b0  (serialize a map<string,int>)
char FUN_00acb1b0(int* obj, int p2, int p3) {
    Archive* ar = (Archive*)obj;
    int* ht = (int*)p3;
    if (ht[3] == 0) return 1;
    char ok = 1;
    String16 s = p2 ? FUN_0093c5a0((const char*)p2, -1) : FUN_00579a90(0);
    const wchar_t* nm = s.mpBegin == s.mpEnd ? DAT_013f6254 : s.mpBegin;
    ar->v0(nm);
    int* buckets = (int*)ht[1];
    int* p = buckets;
    int* node = (int*)p[0];
    if (!node) {
        p = buckets + 1;
        while (*p == 0) p++;
        node = (int*)p[0];
    }
    int* endNode = (int*)buckets[ht[2]];
    while (node != endNode) {
        if (ok) {
            ok = 1;
            if (!FUN_00ac8050(ar, 0, node + 1)) ok = 0;
        } else {
            ok = 0;
        }
        node = (int*)node[0x68 / 4];
        if (!node) {
            p++;
            while (*p == 0) p++;
            node = (int*)p[0];
        }
    }
    ar->v1(nm);
    destroy16(s);
    return ok;
}

// @ 0x00acb340  (serialize a vector of 0x20-stride nodes)
char FUN_00acb340(int* obj, int p2, int* p3) {
    Archive* ar = (Archive*)obj;
    if (p3[0] == p3[1]) return 1;
    char ok = 1;
    String16 s = p2 ? FUN_0093c5a0((const char*)p2, -1) : FUN_00579a90(0);
    const wchar_t* nm = s.mpBegin == s.mpEnd ? DAT_013f6254 : s.mpBegin;
    ar->v0(nm);
    uchar* end = (uchar*)p3[1];
    for (uchar* it = (uchar*)p3[0]; it != end; it += 0x20) {
        if (ok) {
            ok = 1;
            if (!FUN_00ac8050(ar, 0, it + 4)) ok = 0;
        } else {
            ok = 0;
        }
    }
    ar->v1(nm);
    destroy16(s);
    return ok;
}

// @ 0x00acbb20
void* FUN_00acbb20(uchar* p, uchar* end, uchar* out) {
    if (p != end) {
        uchar* o = out;
        do {
            if (o) {
                *(int*)o = *(int*)p;
                *(void**)(o + 4) = (void*)0x145a164;
                *(o + 8) = *(p + 8);
                *(o + 9) = *(p + 9);
                ((XC*)(o + 0xc))->FUN_00aca9d0(p + 0xc);
            }
            p += 0x20; o += 0x20;
        } while (p != end);
        return o;
    }
    return out;
}

// @ 0x00acbc10  (serialize a hashtable's values)
char FUN_00acbc10(int* obj, int p2, int p3) {
    Archive* ar = (Archive*)obj;
    int* ht = (int*)p3;
    if (ht[3] == 0) return 1;
    char ok = 1;
    String16 s = p2 ? FUN_0093c5a0((const char*)p2, -1) : FUN_00579a90(0);
    const wchar_t* nm = s.mpBegin == s.mpEnd ? DAT_013f6254 : s.mpBegin;
    ar->v0(nm);
    int* buckets = (int*)ht[1];
    int* p = buckets;
    int* node = (int*)p[0];
    if (!node) {
        p = buckets + 1;
        while (*p == 0) p++;
        node = (int*)p[0];
    }
    int* endNode = (int*)buckets[ht[2]];
    while (node != endNode) {
        if (ok) {
            ok = 1;
            if (!FUN_0057c770(ar, 0, node + 1, DAT_013f5890)) ok = 0;
        } else {
            ok = 0;
        }
        node = (int*)node[8 / 4];
        if (!node) {
            p++;
            while (*p == 0) p++;
            node = (int*)p[0];
        }
    }
    ar->v1(nm);
    destroy16(s);
    return ok;
}
