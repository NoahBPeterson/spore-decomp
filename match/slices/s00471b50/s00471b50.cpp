// s00471b50 -- /Od /Ob1 region.

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

// @ 0x00471ec0
void F_00471ec0() {}

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
