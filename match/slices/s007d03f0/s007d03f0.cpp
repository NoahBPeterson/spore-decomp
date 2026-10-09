// Slice s007d03f0 (w2g5 slice 9).  Region: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
// SP::cGameModelDescription ctor/dtor, cSPTransform copy/assign helpers, RBTree
// nuke/clone/insert helpers, and EA::IO serialization.
#include "types.h"

extern "C" void* __cdecl EAlloc(uint32_t, const char*, int, int, const char*, int);
extern "C" void  __cdecl EFree(void*);
inline void* operator new(unsigned int, void* p) { return p; }

void WU16(void*, const void*, int, int);   // 0x0093a9d0
void WU32(void*, const void*, int, int);   // 0x0093aa70
void WB(void*, const void*, int);          // 0x0093a9a0

extern "C" void* __cdecl RBTreeIncrement(void* node);                                // 0x00921580
extern "C" void  __cdecl RBTreeInsert(void* node, void* parent, void* anchor, int f); // 0x009216a0
extern "C" void  __cdecl FUN_007d08e0(void* b, void* e);
extern "C" void  __cdecl FUN_007d0d00();
extern "C" void  __cdecl FUN_0053bd00(void*, void*);
extern "C" void* __cdecl FUN_004aa350(void* self, int n, const void* src);
extern "C" void* __cdecl VecDoInsert(void* dst, const void* src, unsigned size);

void Ser360(void* stream, char* p);   // 0x007d0360
void* Ser2B0(void*, int*);            // 0x007d02b0

struct Matrix3 {
    float m[9];
    void Assign(const Matrix3& o);   // 0x0041cb40 thiscall
};

static float g_1485720 = 1.0f;
extern const float g_1636f68, g_1636f6c, g_1636f70;
extern const Matrix3 g_16370e8;
extern const float g_1636ef4, g_1636ef8, g_1636efc;
static void* s_vt_1411f04[1];
static void* s_vt_13ef094[1];
static void* s_vt_1411f48[1];
extern char g_empty1[];
extern char g_empty2[];

struct SVec {
    float* b; float* e; float* c; char alloc[4];
    SVec& operator=(const SVec& o);   // external
};
struct cSPTransform {
    char pad[0x38];
    cSPTransform& operator=(const cSPTransform& o);   // external 0x00537dc0
};
struct TreeThing {
    TreeThing& operator=(const TreeThing& o);   // external 0x007d0b80
};

// ===========================================================================
// 0x007d03f0  RBTree serialization loop
// ===========================================================================
void SerTree(void* stream, char* tree)
{
    uint32_t v = *(uint32_t*)(tree + 0x14);
    WU32(stream, &v, 1, 0);
    for (char* n = *(char**)(tree + 8); n != tree + 4; n = (char*)RBTreeIncrement(n)) {
        v = *(uint32_t*)(n + 0x10);
        WU32(stream, &v, 1, 0);
    }
}

// ===========================================================================
// 0x007d0450  response list serialization
// ===========================================================================
void* SerResp(void* stream, int* vec)
{
    int n = (vec[1] - vec[0]) / 0x2c;
    WU32(stream, &n, 1, 0);
    if (n != 0) {
        int i = 0;
        do {
            Ser360(stream, (char*)vec[0] + i);
            i += 0x2c;
            n = n - 1;
        } while (n != 0);
    }
    return stream;
}

// ===========================================================================
// 0x007d04b0  dialog-list serialization
// ===========================================================================
void SerDlg(void* stream, int* vec)
{
    uint32_t n = (uint32_t)((vec[1] - vec[0]) / 0x68);
    WU32(stream, &n, 1, 0);
    if (n != 0) {
        int off = 0;
        do {
            char* e = (char*)vec[0] + off;
            uint8_t b = *(uint8_t*)e;
            WB(stream, &b, 1);
            uint32_t v = *(uint32_t*)(e + 4);
            WU32(stream, &v, 1, 0);
            uint16_t h = *(uint16_t*)(e + 8);
            WU16(stream, &h, 1, 0);
            uint32_t v2 = *(uint32_t*)(e + 0x18);
            WU32(stream, &v2, 1, 0);
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, e + 0x1c, 0x24);
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, e + 0xc, 0xc);
            SerTree(stream, e + 0x4c);
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, e + 0x40, 0xc);
            off += 0x68;
            n--;
        } while (n != 0);
    }
}

// ===========================================================================
// 0x007d05b0  RBTreeInsert wrapper
// ===========================================================================
struct RBTreeW {
    void* Insert(void* out, void* parent, int* value, char flag);
};
void* RBTreeW::Insert(void* out, void* parent, int* value, char flag)
{
    int insertLeft;
    if (flag == 0 && parent != (char*)this + 4 && *value >= *(int*)((char*)parent + 0x10))
        insertLeft = 1;
    else
        insertLeft = 0;
    int* node = (int*)EAlloc(0x14, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if ((int*)((char*)node + 0x10) != 0)
        *(int*)((char*)node + 0x10) = *value;
    RBTreeInsert(node, parent, (char*)this + 4, insertLeft);
    void* o = out;
    ((int*)this)[5] = ((int*)this)[5] + 1;
    *(void**)o = node;
    return o;
}

// ===========================================================================
// 0x007d0670  LayoutWorld::LayoutWorld
// ===========================================================================
struct LayoutWorld {
    char pad0[8];
    uint16_t f8;
    uint16_t fa;
    float fc, f10, f14, f18;
    Matrix3 m1c;
    char pad40[0x50 - 0x40];
    void* p50;
    void* p54;
    void* p58;
    uint8_t b5c;
    char pad5d[3];
    uint32_t f60;
    LayoutWorld();
};
LayoutWorld::LayoutWorld()
{
    fa = 0;
    f8 = 0;
    fc = g_1636f68;
    f10 = g_1636f6c;
    f14 = g_1636f70;
    f18 = g_1485720;
    m1c.Assign(g_16370e8);
    p54 = 0;
    p58 = 0;
    b5c = 0;
    p54 = (char*)this + 0x50;
    p50 = (char*)this + 0x50;
    p58 = 0;
    b5c = 0;
    f60 = 0;
}

// ===========================================================================
// 0x007d06f0  dialog-list serialization (top level)
// ===========================================================================
void Ser6F0(void* stream, char* p)
{
    uint32_t v;
    v = *(uint32_t*)(p + 0xc);   WU32(stream, &v, 1, 0);
    v = *(uint32_t*)(p + 0x10);  WU32(stream, &v, 1, 0);
    ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, p + 0x14, 0xc);
    v = 0; WU32(stream, &v, 1, 0);
    v = 0; WU32(stream, &v, 1, 0);
    v = 0; WU32(stream, &v, 1, 0);
    v = 0; WU32(stream, &v, 1, 0);
    SerResp(stream, (int*)(p + 0x30));
    Ser2B0(stream, (int*)(p + 0x44));
    SerDlg(stream, (int*)(p + 0x58));
    FUN_0053bd00(stream, p + 0x6c);
    v = 0; WU32(stream, &v, 1, 0);
    uint8_t b = 0; WB(stream, &b, 1);
    b = 0; WB(stream, &b, 1);
    v = 0; WU32(stream, &v, 1, 0);
}

// ===========================================================================
// 0x007d0920  clone tree
// ===========================================================================
void* CloneTree(int* src, void* parent)
{
    int* n = (int*)EAlloc(0x14, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if ((int*)((char*)n + 0x10) != 0)
        *(int*)((char*)n + 0x10) = src[4];
    n[0] = 0;
    n[1] = 0;
    n[2] = (int)parent;
    *((char*)n + 0xc) = (char)src[3];
    if (*src != 0) {
        void* r = CloneTree((int*)*src, n);
        n[0] = (int)r;
    }
    void* cur = n;
    for (int* c = (int*)src[1]; c != 0; c = (int*)c[1]) {
        int* m = (int*)EAlloc(0x14, "App", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        if ((int*)((char*)m + 0x10) != 0)
            *(int*)((char*)m + 0x10) = c[4];
        m[0] = 0;
        m[1] = 0;
        m[2] = (int)cur;
        *((char*)m + 0xc) = (char)c[3];
        *((void**)cur + 1) = m;
        if (*c != 0) {
            void* r = CloneTree((int*)*c, m);
            m[0] = (int)r;
        }
        cur = m;
    }
    return n;
}

// ===========================================================================
// 0x007d0a00  nuke range (returns end)
// ===========================================================================
struct RBTree {
    void DoNukeSubtree(void* node);   // 0x009a9600 thiscall
};
struct Item68 {
    char pad0[0x4c];
    RBTree tree;
    char pad50[8];
    void* root;
};
void* NukeRange(Item68* begin, Item68* end, char* out)
{
    for (; begin != end; begin = (Item68*)((char*)begin + 0x68)) {
        void** n = (void**)begin->root;
        RBTree& tree = begin->tree;
        while (n != 0) {
            tree.DoNukeSubtree(*n);
            void* next = n[1];
            EFree(n);
            n = (void**)next;
        }
        out += 0x68;
    }
    return out;
}

// ===========================================================================
// 0x007d0b30  nuke range (stdcall)
// ===========================================================================
void __stdcall NukeRange2(Item68* begin, Item68* end)
{
    while (begin < end) {
        void** n = (void**)begin->root;
        RBTree& tree = begin->tree;
        while (n != 0) {
            tree.DoNukeSubtree(*n);
            void* next = n[1];
            EFree(n);
            n = (void**)next;
        }
        begin = (Item68*)((char*)begin + 0x68);
    }
}

// ===========================================================================
// 0x007d0c10 / 0x007d0c80  read helpers (partial)
// ===========================================================================
void ReadC10(void* stream)
{
    (void)stream;
}
void ReadC80(void* stream, char* p)
{
    (void)stream; (void)p;
}

// ===========================================================================
// 0x007d0d60  operator=
// ===========================================================================
struct S0D60 {
    uint8_t b0;
    char pad1[3];
    int f4;
    uint16_t f8, fa;
    float fc, f10, f14, f18;
    Matrix3 m1c;
    float f40, f44, f48;
    TreeThing t4c;
    S0D60& operator=(const S0D60& o);
};
S0D60& S0D60::operator=(const S0D60& o)
{
    b0 = o.b0;
    f4 = o.f4;
    f8 = o.f8;
    fa = o.fa;
    fc = o.fc;
    f10 = o.f10;
    f14 = o.f14;
    f18 = o.f18;
    m1c.Assign(o.m1c);
    f40 = o.f40;
    f44 = o.f44;
    f48 = o.f48;
    t4c = o.t4c;
    return *this;
}

// ===========================================================================
// 0x007d0f60  cGameModelDescription::~cGameModelDescription
// ===========================================================================
struct cGameModelDescription {
    void* vftable;
    int mRefCount;
    int mStateID;
    int mFlags;
    float mSize;
    float mCX, mCY, mCZ;
    float mAlpha;
    int mInstanceID;
    int mGroupID;
    int mWorldID;
    void* a30; void* a34; void* a38;
    char pad3c[4];
    void* a40;
    void* a44; void* a48; void* a4c;
    char pad50[4];
    void* a54;
    void* a58; void* a5c; void* a60;
    char pad64[8];
    void* a6c; void* a70; void* a74;
    char pad78[8];
    int a80;
    uint8_t a84, a85;
    char pad86[2];
    int a88;
    cGameModelDescription();
    ~cGameModelDescription();
};
cGameModelDescription::~cGameModelDescription()
{
    void* p6c = a6c;
    if (p6c && *(int*)((char*)p6c - 4) != 0)
        EFree(p6c);
    FUN_007d0d00();
    void* p44 = a44;
    if (p44 && *(int*)((char*)p44 - 4) != 0)
        EFree(p44);
    FUN_007d08e0(a30, a34);
    void* p30 = a30;
    if (p30 && *(int*)((char*)p30 - 4) != 0)
        EFree(p30);
    *(uint32_t*)this = (uint32_t)s_vt_13ef094;
}

// ===========================================================================
// 0x007d1010  cGameModelDescription::cGameModelDescription
// ===========================================================================
cGameModelDescription::cGameModelDescription()
{
    mRefCount = 0;
    mStateID = 0xebb8e524;
    *(uint32_t*)this = (uint32_t)s_vt_1411f04;
    mFlags = 0;
    mSize = g_1485720;
    mCX = g_1636ef4;
    mCY = g_1636ef8;
    mCZ = g_1636efc;
    mAlpha = g_1485720;
    mInstanceID = 0;
    mGroupID = 0;
    mWorldID = 0;
    a30 = 0; a34 = 0; a38 = 0;
    a44 = 0; a48 = 0; a4c = 0;
    a58 = 0; a5c = 0; a60 = 0;
    a6c = 0; a70 = 0; a74 = 0;
    a80 = 0;
    a84 = 0;
    a85 = 0;
    a88 = 0;
}

// ===========================================================================
// 0x007d10d0  read vector (partial)
// ===========================================================================
void ReadVec(void* stream, int* vec)
{
    (void)stream; (void)vec;
}

// ===========================================================================
// 0x007d1140  copy ctor (partial)
// ===========================================================================
struct S1140 {
    float f0, f4;
    SVec v8;
    float f1c;
    float f20;
    int f24;
    uint8_t f28;
    char pad29[3];
    S1140(const S1140& o);
};
S1140::S1140(const S1140& o)
{
    f0 = o.f0;
    f4 = o.f4;
    v8 = o.v8;
    f1c = o.f1c;
    f20 = o.f20;
    f24 = o.f24;
    f28 = o.f28;
}

// ===========================================================================
// 0x007d12c0  copy range (assign)
// ===========================================================================
struct S2C {
    int a, b;
    SVec v;
    char pad18[4];
    float f1c, f20;
    int f24;
    uint8_t f28;
    char pad29[3];
};
S2C* CopyRange12C0(S2C* first, S2C* last, S2C* dst)
{
    while (first != last) {
        dst->a = first->a;
        dst->b = first->b;
        dst->v = first->v;
        dst->f1c = first->f1c;
        dst->f20 = first->f20;
        dst->f24 = first->f24;
        dst->f28 = first->f28;
        first = (S2C*)((char*)first + 0x2c);
        dst = (S2C*)((char*)dst + 0x2c);
    }
    return dst;
}

// ===========================================================================
// 0x007d1320  copy range (cSPTransform)
// ===========================================================================
struct S68 {
    uint8_t b0;
    char pad1[3];
    int f4;
    cSPTransform t8;
    int f40, f44, f48;
    TreeThing t4c;
};
char* CopyRange1320(char* first, char* last, char* dst)
{
    while (first != last) {
        S68* d = (S68*)dst;
        S68* s = (S68*)first;
        d->b0 = s->b0;
        d->f4 = s->f4;
        d->t8 = s->t8;
        d->f40 = s->f40;
        d->f44 = s->f44;
        d->f48 = s->f48;
        d->t4c = s->t4c;
        first += 0x68;
        dst += 0x68;
    }
    return dst;
}

// ===========================================================================
// 0x007d1380  assign range (stride 0x2c)
// ===========================================================================
void AssignRange1380(S2C* first, S2C* last, S2C* src)
{
    while (first != last) {
        first->a = src->a;
        first->b = src->b;
        first->v = src->v;
        first->f1c = src->f1c;
        first->f20 = src->f20;
        first->f24 = src->f24;
        first->f28 = src->f28;
        first = (S2C*)((char*)first + 0x2c);
    }
}

// ===========================================================================
// 0x007d1450  copy backward (stride 0x2c)
// ===========================================================================
S2C* CopyBack1450(S2C* first, S2C* last, S2C* dst)
{
    while (last != first) {
        last = (S2C*)((char*)last - 0x2c);
        dst = (S2C*)((char*)dst - 0x2c);
        dst->a = last->a;
        dst->b = last->b;
        dst->v = last->v;
        dst->f1c = last->f1c;
        dst->f20 = last->f20;
        dst->f24 = last->f24;
        dst->f28 = last->f28;
    }
    return dst;
}

// ===========================================================================
// 0x007d14b0  assign range (stride 0x68)
// ===========================================================================
void AssignRange14B0(char* first, char* last, char* src)
{
    while (first != last) {
        S68* d = (S68*)first;
        S68* s = (S68*)src;
        d->b0 = s->b0;
        d->f4 = s->f4;
        d->t8 = s->t8;
        d->f40 = s->f40;
        d->f44 = s->f44;
        d->f48 = s->f48;
        d->t4c = s->t4c;
        first += 0x68;
    }
}

// ===========================================================================
// 0x007d1510  copy backward (stride 0x68)
// ===========================================================================
char* CopyBack1510(char* first, char* last, char* dst)
{
    while (last != first) {
        last -= 0x68;
        dst -= 0x68;
        S68* d = (S68*)dst;
        S68* s = (S68*)last;
        d->b0 = s->b0;
        d->f4 = s->f4;
        d->t8 = s->t8;
        d->f40 = s->f40;
        d->f44 = s->f44;
        d->f48 = s->f48;
        d->t4c = s->t4c;
    }
    return dst;
}

// ===========================================================================
// 0x007d1570  (841 bytes, unknown) -- partial
// ===========================================================================
void FUN_007d1570(int self, int a, int b)
{
    (void)self; (void)a; (void)b;
}

// ===========================================================================
// 0x007d18c0  GameModelEffect::GameModelEffect
// ===========================================================================
struct AppProps { AppProps(); };   // 0x0083cdd0
struct GameModelEffect : AppProps {
    GameModelEffect();
    char pad4[0x34];
    int f34;
    char desc[0x8c];
    int fc4;
    void* pc8;
    void* pcc;
    void* pd0;
};
GameModelEffect::GameModelEffect()
{
    *(uint32_t*)this = (uint32_t)s_vt_1411f48;
    f34 = 0x30bac64;
    new (desc) cGameModelDescription();
    fc4 = 0;
    pc8 = &g_empty1;
    pcc = &g_empty1;
    pd0 = &g_empty2;
}

// ===========================================================================
// 0x007d1910  cGameModelSizeCommand::Execute (partial)
// ===========================================================================
void FUN_007d1910(int self, void* args)
{
    (void)self; (void)args;
}

// ===========================================================================
// 0x007d1970  command Execute
// ===========================================================================
struct V3 { int a, b, c; };
struct cArguments { void** MainArguments(int); };   // 0x00838320 thiscall
struct ObjV {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual V3 Get(const void* in);   // slot 44
};
void FUN_007d1970(int self, cArguments* args)
{
    ObjV* obj = *(ObjV**)(self + 4);
    void** a = args->MainArguments(1);
    V3 v = obj->Get(*a);
    *(V3*)(*(int*)(self + 0xc) + 0x18) = v;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
