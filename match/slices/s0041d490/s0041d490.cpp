// Small helpers around 0x0041d490: cCreatureAbility ctor/dtor, fixed-capacity
// vector/string headers, smart-pointer assign/reset, Vector3 arithmetic.
// Built without optimization: /Od /Ob1 /arch:SSE.

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    void Set(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
};

// ---- creature ability --------------------------------------------------
struct AbilityBlock { float v[8]; };   // 32 bytes, copied as two 16-byte rows

struct AbilityBlockCopy {              // FUN_0041d7b0 body (copy two Vec4 rows)
    AbilityBlockCopy* CopyRows(const float* src);
};

extern void* vtbl_cCreatureAbility[];
void __cdecl EASTL_allocator_deallocate(void* p);

struct cCreatureAbility {
    void*          vptr;      // 0
    unsigned short mId;       // 4
    unsigned short mSize;     // 6
    void*          mData;     // 8
    float          mBlock[8]; // 0xc (two rows of 4 floats)

    cCreatureAbility(const float* src);
    cCreatureAbility* Destroy(unsigned flags);
};

// @ 0x0041d7b0
AbilityBlockCopy* AbilityBlockCopy::CopyRows(const float* src)
{
    float* dst;
    const float* s;
    int rows;
    rows = 2;
    s = src;
    dst = (float*)this;
    while (--rows >= 0) {
        dst[0] = s[0];
        dst[1] = s[1];
        dst[2] = s[2];
        dst[3] = s[3];
        dst += 4;
        s += 4;
    }
    return this;
}

// @ 0x0041d490
cCreatureAbility::cCreatureAbility(const float* src)
{
    int u1, u2, u3;
    vptr = vtbl_cCreatureAbility;
    mId = 0x21c;
    mSize = 0x20;
    mData = 0;
    ((AbilityBlockCopy*)mBlock)->CopyRows(src);
    vptr = vtbl_cCreatureAbility;
    mData = this ? (void*)mBlock : (void*)0;
}

// @ 0x0041d780
cCreatureAbility* cCreatureAbility::Destroy(unsigned flags)
{
    vptr = vtbl_cCreatureAbility;
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

// ---- fixed-capacity containers ------------------------------------------
struct PoolAlloc { int tag; char* pool; };

// Header with begin/end/cap, allocator at +0xc and inline storage at +0x18.
struct FixedVecHdr {
    char* b; char* e; char* c;
    PoolAlloc a;
    int pad;
};

// @ 0x0041d590
struct FixedVec8 : FixedVecHdr {
    char buf[8];
    FixedVec8();
};
FixedVec8::FixedVec8()
{
    char* storage = buf;
    int* pad;
    b = 0; e = 0; c = 0;
    PoolAlloc* al = &a;
    al->pool = storage;
    e = buf;
    b = e;
    c = b + 8;
}

// String-like containers: base init (external) then begin/end/cap point at inline storage.
struct Alloc { int x; };
struct StrBaseW { char* b; char* e; char* c; int a0, a1; void BaseInit(Alloc*); };
struct StrBaseA { char* b; char* e; char* c; int a0, a1; void BaseInit(Alloc*); };

struct WStr768 : StrBaseW { unsigned short buf[0x180]; WStr768* Init(); };
struct WStr512 : StrBaseW { unsigned short buf[0x100]; WStr512* Init(); };
struct WStr1024 : StrBaseW { unsigned short buf[0x200]; WStr1024* Init(); };
struct Str512 : StrBaseA { char buf[0x200]; Str512* Init(); };

// @ 0x0041d600
WStr768* WStr768::Init()
{
    unsigned short* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = (char*)buf;
    b = e;
    c = b + 0x300;
    *(unsigned short*)b = 0;
    { int pad; }
    return this;
}

// @ 0x0041d660
WStr512* WStr512::Init()
{
    unsigned short* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = (char*)buf;
    b = e;
    c = b + 0x200;
    *(unsigned short*)b = 0;
    { int pad; }
    return this;
}

// @ 0x0041d6c0
WStr1024* WStr1024::Init()
{
    unsigned short* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = (char*)buf;
    b = e;
    c = b + 0x400;
    *(unsigned short*)b = 0;
    { int pad; }
    return this;
}

// @ 0x0041d720
Str512* Str512::Init()
{
    char* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = buf;
    b = e;
    c = b + 0x200;
    *b = 0;
    { int pad; }
    return this;
}

// ---- fixed vector headers without allocator ------------------------------
struct FixedHdr2 { char* b; char* e; char* c; int pad[2]; int count; };

struct FixedVec192 : FixedHdr2 { char buf[0xc0]; void Init(); };
struct FixedVec1536 : FixedHdr2 { char buf[0x600]; void Init(); };
struct FixedVec896 : FixedHdr2 { char buf[0x380]; void Init(); };

// @ 0x0041d830
void FixedVec192::Init()
{
    count = 0;
    b = buf;
    e = b;
    c = b + 0xc0;
}

// @ 0x0041da70
void FixedVec1536::Init()
{
    count = 0;
    b = buf;
    e = b;
    c = b + 0x600;
}

// @ 0x0041dab0
void FixedVec896::Init()
{
    count = 0;
    b = buf;
    e = b;
    c = b + 0x380;
}

// @ 0x0041d510  (pool-backed vector with 0xc00-byte capacity, then external init(arg))
struct PoolVec3072 : FixedVecHdr {
    char buf[0xc00];
    PoolVec3072(int arg);
    void ExtInit(int);
};
PoolVec3072::PoolVec3072(int arg)
{
    char* storage = buf;
    int* pad;
    b = 0; e = 0; c = 0;
    PoolAlloc* al = &a;
    al->pool = storage;
    e = buf;
    b = e;
    c = b + 0xc00;
    ExtInit(arg);
    { int bigpad[0x12]; } { int more; }
}

// ---- smart pointer helpers ------------------------------------------------
struct IObject { virtual void v0(); virtual void v1(); virtual void v2(); };

struct OwnPtrV1 { IObject* p; OwnPtrV1* Reset(); };
// @ 0x0041d870
OwnPtrV1* OwnPtrV1::Reset()
{
    if (p) {
        IObject* o = p;
        p = 0;
        o->v1();
    }
    return this;
}

struct OwnPtrV2 { IObject* p; OwnPtrV2* Reset(); };
// @ 0x0041da30
OwnPtrV2* OwnPtrV2::Reset()
{
    if (p) {
        IObject* o = p;
        p = 0;
        o->v2();
    }
    return this;
}

extern "C" long _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedIncrement)

struct ThreadedObject { int vt; long rc; void Release(); };
struct DefaultRefCounted { int vt; int rc; void Release(); int AddRef() { int pad[3]; return rc++ + 1; } };

struct ThreadedRef { ThreadedObject* p; ThreadedRef* Assign(ThreadedObject* n); };
// @ 0x0041d8b0
ThreadedRef* ThreadedRef::Assign(ThreadedObject* n)
{
    if (n != p) {
        ThreadedObject* old = p;
        if (n)
            _InterlockedIncrement(&n->rc);
        p = n;
        if (old)
            old->Release();
    }
    { int pad[3]; }
    return this;
}

struct RcRef { DefaultRefCounted* p; RcRef* Reset(); };
// @ 0x0041d900
RcRef* RcRef::Reset()
{
    if (p) {
        DefaultRefCounted* o = p;
        p = 0;
        o->Release();
    }
    { int pad[3]; }
    return this;
}

void __fastcall ExtDestroy(void* obj);
struct ExtRef { void* p; ExtRef* Reset(); };
// @ 0x0041d940
ExtRef* ExtRef::Reset()
{
    if (p) {
        void* o = p;
        p = 0;
        ExtDestroy(o);
    }
    return this;
}

struct RcHolder { int vt; DefaultRefCounted rc; };  // refcounted base at +4
struct RcHolderRef { RcHolder* p; RcHolderRef* Assign(RcHolder* n); RcHolderRef* Reset(); };
// @ 0x0041d980
RcHolderRef* RcHolderRef::Assign(RcHolder* n)
{
    if (n != p) {
        RcHolder* old = p;
        if (n) {
            n->rc.AddRef();
        }
        p = n;
        if (old)
            old->rc.Release();
    }
    
    return this;
}

// @ 0x0041d9f0
RcHolderRef* RcHolderRef::Reset()
{
    if (p) {
        RcHolder* o = p;
        p = 0;
        o->rc.Release();
    }
    { int pad[3]; }
    return this;
}

// ---- misc -------------------------------------------------------------------
void __cdecl ExtCopy(int a, int b, int c);
// @ 0x0041daf0
int __cdecl Unchecked_idl0(int a, int b, int c)
{
    ExtCopy(a, b, c);
    return a;
}

// @ 0x0041db10
Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r(a.x - b.x, a.y - b.y, a.z - b.z);
    return r;
}

// @ 0x0041dba0
Vector3* ScaleInPlace(Vector3* v, const float* s)
{
    v->Set(v->x * *s, v->y * *s, v->z * *s);
    return v;
}

// @ 0x0041dc10
Vector3 operator+(const Vector3& a, const Vector3& b)
{
    Vector3 r(a.x + b.x, a.y + b.y, a.z + b.z);
    return r;
}

// @ 0x0041dca0
Vector3 operator*(const Vector3& a, const float& s)
{
    Vector3 r(a.x * s, a.y * s, a.z * s);
    return r;
}

// @ 0x0041dd30
bool operator!=(const Vector3& a, const Vector3& b)
{
    return !(a.x == b.x && a.y == b.y && a.z == b.z);
}
