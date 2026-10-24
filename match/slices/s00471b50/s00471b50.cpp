// s00471b50 -- /Od /Ob1 region.

#include <math.h>

typedef unsigned int uint32_t;
template <int N> inline void ScratchSlots()
{
    uint32_t s[N];
    (void)s;
}

class ThreadedObject {
public:
    void Release();
};

// @ 0x00472520
struct RefHolderA {
    ThreadedObject* p;
    ~RefHolderA();
};

RefHolderA::~RefHolderA()
{
    ScratchSlots<3>();
    if (p)
        p->Release();
}

class DefaultRefCounted {
public:
    void Release();
};

// @ 0x00472540
struct RefHolderB {
    DefaultRefCounted* p;
    ~RefHolderB();
};

RefHolderB::~RefHolderB()
{
    ScratchSlots<3>();
    if (p)
        p->Release();
}

// @ 0x00472640 -- index into a strided element array
struct StridedArr {
    int pad0;
    int off;
    unsigned short pad8;
    unsigned short stride;
    int get(int);
};

int StridedArr::get(int i)
{
    return i * stride + off;
}

extern int vtbl60[];

struct S60 {
    void* vt;
    unsigned short a, b;
    void* self;
};

// @ 0x00472660
S60* __fastcall Init72660(S60* p)
{
    p->vt = vtbl60;
    p->a = 0x218;
    p->b = 1;
    p->self = 0;
    p->vt = vtbl60;
    p->self = p ? (void*)((char*)p + 0xc) : 0;
    return p;
}

struct S61 {
    void* vt;
    unsigned short a, b;
    void* self;
};

// @ 0x004726d0
S61* __fastcall Init726d0(S61* p)
{
    p->vt = vtbl60;
    p->a = 0x238;
    p->b = 1;
    p->self = 0;
    p->vt = vtbl60;
    p->self = p ? (void*)((char*)p + 0xc) : 0;
    return p;
}

struct S62 {
    void* vt;
    unsigned short a, b;
    void* self;
};

// @ 0x00472a00
S62* __fastcall Init72a00(S62* p)
{
    p->vt = vtbl60;
    p->a = 0x21e;
    p->b = 0x10;
    p->self = 0;
    p->vt = vtbl60;
    p->self = p ? (void*)((char*)p + 0xc) : 0;
    return p;
}

// ---- not yet reproduced -----------------------------------------------------

// @ 0x00471b50
void F_00471b50() {}

// ---- helpers of the 0x00471ec0 element scan (all real image functions) ------
void  F_00409c00();     // 0x409c00 __thiscall: 0x18-byte box ctor (min/max, +0..+0x14)
void  F_00409930();     // 0x409930 __thiscall: 0x38-byte bound-record ctor
void  F_00402ab0();     // 0x402ab0 __thiscall: 0x24-byte 3x3 matrix ctor (no-op)
void  F_00409dd0();     // 0x409dd0 __thiscall: accumulate a bound record into a box
void  F_0043f050();     // 0x43f050 __thiscall: union a box into a box
void  F_00511140();     // 0x511140 __thiscall: copy a box out to the caller's object
void* F_0041de20(void* dest, void* a, void* b);   // 0x41de20 cdecl: fills dest, returns dest
void* F_00401010();     // 0x401010 cdecl: singleton getter (0x15d0c04)
void  F_004721e0();     // 0x4721e0 __thiscall: copy-construct a 0x1d8-byte element

typedef void  (__thiscall* TSelf0)(void* self);
typedef void  (__thiscall* TSelf1)(void* self, void* arg);
typedef bool  (__thiscall* TSix)(void* self, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6);

struct Box18 { float v[6]; };            // +0x00 min xyz, +0x0c max xyz
struct Mat3_ { float m[9]; };            // 0x24 bytes
struct BoundRec {                        // 0x38 bytes
    unsigned short flags;                // +0x00
    unsigned short count;                // +0x02
    float x, y, z;                       // +0x04
    float w;                             // +0x10
    Mat3_ mat;                           // +0x14
};
struct Elem1d8 { int w[0x76]; };         // 0x1d8 opaque bytes (an int array keeps /GS quiet)

// @ 0x00471ec0
// Walks the 0x1d8-byte element array at arg1+0x98, asks the editor singleton
// (0x401010, vtable slot 0x54) to classify each element, accumulates the accepted
// ones into a bound record and unions the result into the box that is finally
// copied out to *self.  *out keeps a running sum of the box volumes.
void* F_00471ec0(void* self, unsigned char* arg1, float* out)
{
    Box18 box;
    ((TSelf0)F_00409c00)(&box);
    if (out != 0)
        *out = 0.0f;
    unsigned char* arr = arg1 + 0x98;
    int count = (*(int*)(arr + 4) - *(int*)arr) / 0x1d8;
    for (int i = 0; i < count; ++i) {
        Elem1d8 e;
        char* ep = (char*)&e;
        ((TSelf1)F_004721e0)(&e, (unsigned char*)*(void**)arr + i * 0x1d8);
        Box18 b;
        ((TSelf0)F_00409c00)(&b);
        void* p = F_00401010();
        bool ok = ((TSix)(*(void***)p)[0x54 / 4])(p, *(void**)(ep + 4), *(void**)(ep + 0),
                                                  ep + 0x94, *(void**)(ep + 0x90), &b, &b.v[3]);
        if (!ok)
            continue;
        BoundRec r;
        ((TSelf0)F_00409930)(&r);
        *(int*)&r.x = *(int*)(ep + 0x14);
        *(int*)&r.y = *(int*)(ep + 0x18);
        *(int*)&r.z = *(int*)(ep + 0x1c);
        r.flags |= 4;
        ++r.count;
        Mat3_ hidden;
        Mat3_* q = (Mat3_*)F_0041de20(&hidden, ep + 0x5c, ep + 0x38);
        Mat3_ tmp;
        ((TSelf0)F_00402ab0)(&tmp);
        tmp = *q;
        r.mat = tmp;
        r.flags |= 2;
        ++r.count;
        *(int*)&r.w = *(int*)(ep + 0x10);
        ++r.count;
        ((TSelf1)F_00409dd0)(&b, &r);
        ((TSelf1)F_0043f050)(&box, &b);
        if (out != 0) {
            float d0 = fabsf(b.v[3] - b.v[0]);
            float d1 = fabsf(b.v[4] - b.v[1]);
            float d2 = fabsf(b.v[5] - b.v[2]);
            *out = d0 * d1 * d2 + *out;
        }
    }
    ((TSelf1)F_00511140)(self, &box);
    return self;
}

// @ 0x004721e0
void F_004721e0() {}

// @ 0x00472860
void F_00472860() {}

// @ 0x004728e0
void F_004728e0() {}

// @ 0x00472990
void F_00472990() {}

// @ 0x00472a00
void F_00472a00() {}

// @ 0x00472aa0
void F_00472aa0() {}
