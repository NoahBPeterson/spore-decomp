// Slice s00c92a90 - SP hot-spot map / tribe / EASTL heap-dom helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef int            int32_t;

// ---------------------------------------------------------------------------
// External callees.  Their call relocations are masked by the checker, so the
// exact symbol names do not affect matching; the calling shape does.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int line); // operator new
extern "C" void  __cdecl FUN_00f47380(void* p);                                                              // operator delete[]
extern "C" const char FUN_00_ALLOC_FILE[];                                                                   // EASTL allocator.h path string

// virtual call: (*obj)->vtable[off]
#define VF(p, off) (*(void**)((char*)(*(void**)p) + (off)))

// ===========================================================================
// cSPVector3 (0xc) and the distance comparator used by the heap helpers.
// ===========================================================================
struct Vec3 {
    float x; // @0x00
    float y; // @0x04
    float z; // @0x08
};
struct CmpPos {
    float x; // @0x00
    float y; // @0x04
    float z; // @0x08
};

// 0x00c92e20 (definition further down) - eastl::adjust_heap<cSPVector3_*,int,cSPVector3,ComparePositions>
extern "C" void __cdecl FUN_00c92e20(Vec3* first, int top, int heapSize, int pos, Vec3 value, CmpPos cmp);
// 0x00c90f50 - eastl::promote_heap<cSPVector3_*,int,cSPVector3,ComparePositions>
extern "C" void __cdecl FUN_00c90f50(Vec3* first, int top, int pos, Vec3 value, CmpPos cmp);

// ===========================================================================
// 0x60-byte hot-spot record (the vector element of cVarList/ HotSpotMap).
// Declared fields cover every offset this slice touches.
// ===========================================================================
struct Rec60 {
    uint32_t f00;      // @0x00  (comparison key)
    uint8_t  pad04[0x28];
    void*    f2c;      // @0x2c
    void*    f30;      // @0x30
    uint8_t  pad34[0x10];
    void*    f44;      // @0x44
    void*    f48;      // @0x48  (owned array pointer, -4 holds a flag)
};

// @ 0x00c92d50 - SP::HotSpotMap::lower_bound(first, last, key)
Rec60* __cdecl FUN_00c92d50(Rec60* first, Rec60* last, uint32_t* key) {
    int n = (int)((char*)last - (char*)first) / 0x60;
    while (n > 0) {
        int half = n >> 1;
        Rec60* mid = (Rec60*)((char*)first + half * 0x60);
        if (mid->f00 < *key) {
            first = (Rec60*)((char*)mid + 0x60);
            half = n + (-1 - half);
        }
        n = half;
    }
    return first;
}

// ---------------------------------------------------------------------------
// 00c92a90 - serialize a range of 0x60-byte cVarList records.
// The target object (p1) exposes a vtable; slots 0x1c/0x20 are used here and
// 0x18 on the sub-stream returned by slot 0x20.
// ---------------------------------------------------------------------------
extern int DAT_0157b7d0;                                              // type descriptor handed to the serializer
extern "C" void __cdecl FUN_0093aa70(void* stream, void* value, int n, int flag); // EA::IO::WriteUint32

class cVarListSerializer {
public:
    void Init(void* list, void* type, int id);  // 0x00692f90
    bool Serialize(void* out);                  // 0x00692900
private:
    unsigned char mData[0x9ec];
};

// @ 0x00c92a90
void __cdecl FUN_00c92a90(void* p1, int** p2) {
    int count = (int)((char*)p2[1] - (char*)p2[0]) / 0x60;
    void* s = ((void*(__thiscall*)(void*))VF(p1, 0x20))(p1);
    void* w = ((void*(__thiscall*)(void*))VF(s, 0x18))(s);
    FUN_0093aa70(w, &count, 1, 0);
    int* cur = p2[0];
    for (; cur != p2[1]; cur += 0x18) {
        void* s2 = ((void*(__thiscall*)(void*))VF(p1, 0x20))(p1);
        count = *cur;
        void* w2 = ((void*(__thiscall*)(void*))VF(s2, 0x18))(s2);
        FUN_0093aa70(w2, &count, 1, 0);
        ((void(__thiscall*)(void*))VF(p1, 0x1c))(p1);
        cVarListSerializer ser;
        ser.Init(cur + 2, &DAT_0157b7d0, 0x1a80d26);
        ser.Serialize(p1);
        ((void(__thiscall*)(void*))VF(p1, 0x1c))(p1);
    }
    ((void(__thiscall*)(void*))VF(p1, 0x1c))(p1);
}

// @ 0x00c92c70 - eastl::deque-like assign over refcounted pointers.
// (first, last, out, blockptr): copies *first..*last into *out.., AddRef at
// vtable+0xbc, Release at vtable+0xc0, skipping the one-past sentinel.
int** __cdecl FUN_00c92c70(int** first, int** last, int** out, int** blockptr) {
    while (first != last) {
        char* b = (char*)*blockptr;
        int* end = b ? (int*)(b + 0xc0) : 0;
        int* cur = *first;
        if (cur != end) {
            int* old = *out;
            if (cur != old) {
                if (cur)
                    ((void(__thiscall*)(int*))VF(cur, 0xbc))(cur);
                *out = cur;
                if (old)
                    ((void(__thiscall*)(int*))VF(old, 0xc0))(old);
            }
            ++out;
        }
        ++first;
    }
    return out;
}

// 0x1c-byte element: 1 tag byte + 6 dwords/floats.
struct Rec1c {
    uint8_t b0;         // @0x00
    uint8_t pad[3];
    float   f4;         // @0x04
    float   f8;         // @0x08
    float   fc;         // @0x0c
    float   f10;        // @0x10
    float   f14;        // @0x14
    float   f18;        // @0x18
};

// @ 0x00c92ce0 - eastl range copy over 0x1c-byte elements.
// (out, first, last, dst, extra): *out = result iterator, returns out.
void* __cdecl FUN_00c92ce0(void* out, void* first, void* last, void* dst, void* extra) {
    Rec1c* d = (Rec1c*)dst;
    Rec1c* f = (Rec1c*)first;
    Rec1c* l = (Rec1c*)last;
    *(void**)out = dst;
    if (f != l) {
        do {
            if (d != 0) {
                d->b0  = f->b0;
                d->f4  = f->f4;
                d->f8  = f->f8;
                d->fc  = f->fc;
                d->f10 = f->f10;
                d->f14 = f->f14;
                d->f18 = f->f18;
            }
            f = (Rec1c*)((char*)f + 0x1c);
            d = (Rec1c*)((char*)d + 0x1c);
        } while (f != l);
        *(void**)out = d;
    }
    return out;
}

// @ 0x00c92f80 - destroy a range of 0x60-byte records; returns the out cursor.
char* __cdecl FUN_00c92f80(char* first, char* last, char* out) {
    char* p = first + 0x44;
    while (first != last) {
        void* a = *(void**)(p + 4);
        if (a != 0 && *(int*)((char*)a - 4) != 0)
            FUN_00f47380(a);
        void* b = *(void**)p;
        if (b)
            ((void(__thiscall*)(void*))VF(b, 4))(b);
        void* c = *(void**)(p - 0x14);
        if (c)
            ((void(__thiscall*)(void*))VF(c, 4))(c);
        void* e = *(void**)(p - 0x18);
        if (e)
            ((void(__thiscall*)(void*))VF(e, 4))(e);
        first += 0x60;
        p += 0x60;
        out += 0x60;
    }
    return out;
}

// @ 0x00c93690 - count-based destroy of a 0x60-byte range.
void __stdcall FUN_00c93690(uint32_t first, uint32_t last) {
    if (first < last) {
        char* p = (char*)first + 0x44;
        uint32_t count = (last - first - 1) / 0x60 + 1;
        do {
            void* a = *(void**)(p + 4);
            if (a != 0 && *(int*)((char*)a - 4) != 0)
                FUN_00f47380(a);
            void* b = *(void**)p;
            if (b)
                ((void(__thiscall*)(void*))VF(b, 4))(b);
            void* c = *(void**)(p - 0x14);
            if (c)
                ((void(__thiscall*)(void*))VF(c, 4))(c);
            void* e = *(void**)(p - 0x18);
            if (e)
                ((void(__thiscall*)(void*))VF(e, 4))(e);
            p += 0x60;
            --count;
        } while (count != 0);
    }
}

// @ 0x00c93640 - find the sentinel slot in a deque block-pointer range.
void __cdecl FUN_00c93640(int** first, int** last, int** blockptr) {
    for (; first != last; ++first) {
        char* b = (char*)*blockptr;
        int* end = b ? (int*)(b + 0xc0) : 0;
        if (*first == end)
            break;
    }
    if (first != last)
        FUN_00c92c70(first + 1, last, first, blockptr);
}

// @ 0x00c93700 - destroy an array of singly-linked cActionCircle lists.
struct ActionCircle {           // SP::cActionCircle prefix; only the dtor is called
    void dtor(void);            // 0x00afbad0 - SP::cActionCircle::~cActionCircle
};

void __stdcall FUN_00c93700(uint32_t array, uint32_t count) {
    for (uint32_t i = 0; i < count; ++i) {
        char* p = *(char**)(array + i * 4);
        while (p != 0) {
            char* next = *(char**)(p + 0x68);
            ((ActionCircle*)(p + 4))->dtor();
            FUN_00f47380(p);
            p = next;
        }
        *(uint32_t*)(array + i * 4) = 0;
    }
}

// ===========================================================================
// Deque of refcounted pointers (0x100-byte blocks) - member helpers.
// ===========================================================================
class Deque {
public:
    int*   mp00;    // @0x00
    int    mn04;    // @0x04
    int**  mpp08;   // @0x08  current
    int*   mp0c;    // @0x0c  block
    int*   mp10;    // @0x10  block end
    int**  mpp14;   // @0x14  block array cursor
    // second sub-object used by FUN_00c92bd0
    int**  mpp18;   // @0x18
    int*   mp1c;    // @0x1c
    int*   mp20;    // @0x20
    int*   mp24;    // @0x24

    void FUN_01044f80(int, int);            // grow (member)
    void FUN_00c92b70(void);                // pop-like
    void FUN_00c92bd0(int** p);             // push-like
};

// @ 0x00c92b70
void __thiscall Deque::FUN_00c92b70(void) {
    int** cur = mpp08;
    if (cur + 1 != (int**)mp10) {
        mpp08 = cur + 1;
        int* v = *cur;
        if (v)
            ((void(__thiscall*)(int*))VF(v, 4))(v);
    } else {
        int* v = *cur;
        if (v)
            ((void(__thiscall*)(int*))VF(v, 4))(v);
        if (mp0c)
            FUN_00f47380(mp0c);
        int** arr = (int**)((char*)mpp14 + 4);
        mpp14 = arr;
        mp0c = (int*)*arr;
        mp10 = (int*)((char*)mp0c + 0x100);
        mpp08 = (int**)mp0c;
    }
}

// @ 0x00c92bd0
void __thiscall Deque::FUN_00c92bd0(int** p) {
    int* v = *p;
    if (v)
        ((void(__thiscall*)(int*))VF(v, 0))(v);
    if ((((int)((char*)mp24 - (char*)mp00) >> 2) + 1) >= mn04)
        FUN_01044f80(1, 1);
    void* blk = FUN_00f473a0(0x100, "Simulator", 0, 0, FUN_00_ALLOC_FILE, 0xd1);
    *(void**)((char*)mp24 + 4) = blk;
    if (mpp18 != 0) {
        *mpp18 = v;
        if (v)
            ((void(__thiscall*)(int*))VF(v, 0))(v);
    }
    mp24 = (int*)((char*)mp24 + 4);
    int* b = *(int**)mp24;
    mp1c = b;
    mp20 = (int*)((char*)b + 0x100);
    mpp18 = (int**)mp1c;
    if (v)
        ((void(__thiscall*)(int*))VF(v, 4))(v);
}

// ===========================================================================
// "Thing" - the object owning the 0x28-byte header built by the two ctors.
// ===========================================================================
struct V4 { uint32_t v0, v1, v2, v3; };
extern "C" void __cdecl FUN_00c908a0(void* local, V4 a, V4 b, V4 c);

class Thing {
public:
    uint32_t f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24; // 0x00..0x27

    void    Init(int, void*);                       // 0x00c8ed30 (member)
    void    FUN_00ca09f0(uint32_t);                 // member
    Thing*  FUN_00c93750(int32_t* p);
    Thing*  FUN_00c93810(int32_t* p);
};

// @ 0x00c93750
Thing* __thiscall Thing::FUN_00c93750(int32_t* p2) {
    uint32_t local[4];
    f00 = 0; f04 = 0; f08 = 0; f0c = 0; f10 = 0;
    f14 = 0; f18 = 0; f1c = 0; f20 = 0; f24 = 0;
    int size = ((((p2[9] - p2[5]) >> 2) - 1) * 0x40)
             + ((p2[6] - p2[7]) >> 2)
             + ((p2[4] - p2[2]) >> 2);
    ((Thing*)this)->FUN_00ca09f0((uint32_t)size);
    V4 s1 = { f08, f0c, f10, f14 };
    V4 s2 = { (uint32_t)p2[6], (uint32_t)p2[7], (uint32_t)p2[8], (uint32_t)p2[9] };
    V4 s3 = { (uint32_t)p2[2], (uint32_t)p2[3], (uint32_t)p2[4], (uint32_t)p2[5] };
    FUN_00c908a0(local, s3, s2, s1);
    return this;
}

// @ 0x00c93810
Thing* __thiscall Thing::FUN_00c93810(int32_t* p2) {
    ((Thing*)this)->Init((int32_t)((p2[1] - p2[0]) / 0x1c), p2 + 3);
    FUN_00c92ce0(&p2, (void*)p2[0], (void*)p2[1], (void*)f00, p2);
    f04 = (uint32_t)p2;
    return this;
}

// ===========================================================================
// eastl heap helpers over Vec3* with ComparePositions.
// ===========================================================================

// @ 0x00c938f0 - eastl::make_heap<Vec3*, ComparePositions>
void __cdecl FUN_00c938f0(Vec3* first, Vec3* last, CmpPos cmp) {
    int n = (int)((char*)last - (char*)first) / 0xc;
    for (int i = (n - 2) >> 1; i >= 0; --i)
        FUN_00c92e20(first, i, n, i, first[i], cmp);
}

// @ 0x00c93980 - eastl::sort_heap<Vec3*, ComparePositions>
void __cdecl FUN_00c93980(Vec3* first, Vec3* last, CmpPos cmp) {
    Vec3* p = last;
    while ((p - first) > 1) {
        --p;
        Vec3 t = *p;
        *p = *first;
        FUN_00c92e20(first, 0, (int)(p - first), 0, t, cmp);
    }
}

// @ 0x00c92e20 - eastl::adjust_heap<Vec3*, int, Vec3, ComparePositions>
void __cdecl FUN_00c92e20(Vec3* first, int top, int heapSize, int pos, Vec3 value, CmpPos cmp) {
    int child = 2 * pos + 2;
    for (; child < heapSize; child = 2 * child + 2) {
        float ax = cmp.x - first[child].x;
        float ay = cmp.y - first[child].y;
        float az = cmp.z - first[child].z;
        float da = ax * ax + ay * ay + az * az;
        float bx = cmp.x - first[child - 1].x;
        float by = cmp.y - first[child - 1].y;
        float bz = cmp.z - first[child - 1].z;
        float db = bx * bx + by * by + bz * bz;
        if (db > da)
            --child;
        first[pos] = first[child];
        pos = child;
    }
    if (child == heapSize) {
        first[pos] = first[child - 1];
        pos = child - 1;
    }
    FUN_00c90f50(first, top, pos, value, cmp);
}