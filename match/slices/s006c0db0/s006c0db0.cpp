// Slice s006c0db0 — rw::graphics::BlendShape arena accessors, EASTL vector
// helpers and SP::cAnimationBaker::GetBakedAnimations (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <string.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ---------------------------------------------------------------------------
// external helpers (masked relocations)
// ---------------------------------------------------------------------------
extern void  sub_11e0b22(void*, u32, u32, void*);          // ??_M vector dtor iterator
extern void  sub_11e0b85(void*, u32, u32, void*, void*);   // ??_L vector ctor iterator
extern void* sub_11e0744(void*, void*, u32);               // memcpy-ish
extern void* sub_11e22c0(u32);                             // ArenaTypeRegGetType
extern u32   sub_11e23a0(void*);                           // Arena::GetNumExportedObjects
extern void  sub_11e28e0(void*, int, void*);               // Arena::GetExportedObjectByIndex
extern void  sub_931da0(void*, int);                       // FileStream ctor
extern void  sub_931e70(void*);                            // FileStream dtor
extern void  sub_93bd50(void*, const char*);               // MemoryStream ctor
extern void  sub_93bde0(void*);                            // MemoryStream dtor
extern void  sub_93bb40(void*, int, float);                // set stream param
extern bool  sub_93be30(void*, const void*, u32, u32, int, void*); // MemoryStream::SetData
extern void  sub_8dcbf0(void*);                            // IStream base dtor
extern void  sub_f47380(void*);                            // allocator deallocate
extern void* sub_f473a0(u32, const char*, int, int, const char*, int); // allocator allocate
extern void* sub_f25ea0(void*, void*, void*);              // eastl uninitialized copy
extern void* sub_11fd860(int);                             // some global query
extern void  sub_acfe0(u32, u32);                          // FUN_006acfe0
extern void  sub_b4b60(u32, u32);                          // FUN_006b4b60
extern u32   sub_b1f90(u32, int, int);                     // SP::GetSaveArea
extern void  sub_ac040(u32, int);                          // SP::SetCachingType
extern u32   sub_928a30(u32, u32, int,int,int,int,int,int);
extern u32   sub_6c24b0(void*, void*, void*, int, int, int, const char*);
extern void* EAGetManager();
extern void* IDGenerator();

// ---------------------------------------------------------------------------
// BlendShape accessors (struct at `this`)
// ---------------------------------------------------------------------------
struct BlendShape {
    u32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c;
    u32 mfc0();          // 006c0fc0
    u32 mfd0(int n);     // 006c0fd0
    u32 mff0(int n);     // 006c0ff0
    u32 m1020(int n);    // 006c1020
    u32 m1040(int n);    // 006c1040
    u32 m1060(int n);    // 006c1060
    u32 m1080(int n);    // 006c1080
    u32 m10a0(int n);    // 006c10a0
    u32 m10c0(int n);    // 006c10c0
    u32 m1120();         // 006c1120
    u32 m1140();         // 006c1140
    u32 m1160(int n);    // 006c1160
};

// @ 0x006c0fc0
u32 BlendShape::mfc0()
{
    return (f3c & 1) + f3c;
}

// @ 0x006c0fd0
u32 BlendShape::mfd0(int n)
{
    return f2c + f3c * n * 4;
}

// @ 0x006c0ff0
u32 BlendShape::mff0(int n)
{
    if (f20 != 0)
        return f20 + f34 * n * 4;
    return f24 + f34 * n * 4;
}

// @ 0x006c1020
u32 BlendShape::m1020(int n)
{
    return f34 * n * 0x10 + f14;
}

// @ 0x006c1040
u32 BlendShape::m1040(int n)
{
    return f34 * n * 0x10 + f18;
}

// @ 0x006c1060
u32 BlendShape::m1060(int n)
{
    return f34 * n * 0x10 + f1c;
}

// @ 0x006c1080
u32 BlendShape::m1080(int n)
{
    return (n + 1) * f34 * 0x10 + f04;
}

// @ 0x006c10a0
u32 BlendShape::m10a0(int n)
{
    return (n + 1) * f34 * 0x10 + f08;
}

// @ 0x006c10c0
u32 BlendShape::m10c0(int n)
{
    return (n + 1) * f34 * 0x10 + f0c;
}

// @ 0x006c1120
u32 BlendShape::m1120()
{
    if (f20 == 0 && f24 == 0)
        return 0;
    return 1;
}

// @ 0x006c1140
u32 BlendShape::m1140()
{
    if (f28 != 0 && f2c != 0)
        return 1;
    return 0;
}

// @ 0x006c1160
u32 BlendShape::m1160(int n)
{
    return f28 + ((f3c & 1) + f3c) * n * 2;
}

// ---------------------------------------------------------------------------
// @ 0x006c0fa0  ctor of an 8-byte element {int,int}
// ---------------------------------------------------------------------------
struct Pair8 { int a, b; void Init(); };
void Pair8::Init() { a = 0; b = 1; }

// ---------------------------------------------------------------------------
// @ 0x006c0db0  PFRecordWrite constructor from an in-memory blob
// ---------------------------------------------------------------------------
struct PFRecordWrite {
    void* vtbl0;                 // +0x00
    int   refcount;              // +0x04
    u32   type;                  // +0x08
    u32   keyInst, keyType, keyGroup; // +0x0c
    void* parent;                // +0x18
    int   access;                // +0x1c
    void* vtbl20;                // +0x20
    char  mem[0x24];             // +0x24  MemoryStream
    char  file[0x228];           // +0x48  FileStream
    u8    triedCreate;           // +0x270
    u8    pad271[3];
    u32   field274;              // +0x274
    int   openCount;             // +0x278

    void* Ctor(u32 a, u32 b, u32 c, u32* key, void* parent);
    void  Dtor();
};

// @ 0x006c0db0
void* PFRecordWrite::Ctor(u32 a, u32 b, u32 c, u32* key, void* parent_)
{
    vtbl0 = (void*)0x13effa8;
    refcount = 0;
    vtbl0 = (void*)0x140a2e0;
    type = 0x6492fe5;
    keyInst = key[0];
    keyType = key[1];
    keyGroup = key[2];
    parent = parent_;
    access = 3;
    vtbl20 = (void*)0x13f3a68;
    vtbl0 = (void*)0x140a364;
    vtbl20 = (void*)0x140a328;
    sub_93bd50(mem, "ResourceMan/PFRecordWrite");
    sub_931da0(file, 0);
    triedCreate = 0;
    openCount = 1;
    ((void(__thiscall*)(void*))(*(void***)mem)[4 / 4])(mem);
    ((void(__thiscall*)(void*))(*(void***)file)[4 / 4])(file);
    sub_93bb40(mem, 1, 1.0f);
    void* alloc = ((void*(__thiscall*)(void*))(*(void***)parent)[0x48 / 4])(parent);
    sub_93be30(mem, (const void*)a, b, c, 1, alloc);
    return this;
}

// @ 0x006c0ed0  PFRecordWrite destructor
void PFRecordWrite::Dtor()
{
    vtbl0 = (void*)0x140a364;
    vtbl20 = (void*)0x140a328;
    if (access != 0)
        ((void(__thiscall*)(void*, void*))(*(void***)parent)[0x3c / 4])(parent, this);
    sub_8dcbf0(this);
    sub_931e70(file);
    sub_93bde0(mem);
    vtbl20 = (void*)0x13f3a68;
    vtbl0 = (void*)0x13effb8;
}

// ---------------------------------------------------------------------------
// @ 0x006c1180  arena pointer fixup
// ---------------------------------------------------------------------------
u32 FixupArena(int* p)
{
    if (*p == 0x40) {
        memmove(p + 1, p, 0x3c);
        *p = 1;
        memmove(p + 4, p + 3, 0x30);
        p[3] = 0;
        memmove(p + 8, p + 7, 0x20);
        p[7] = 0;
    }
    if (*p != 1)
        return 0;
    if (p[1] != 0) p[1] = p[1] + (int)p;
    if (p[2] != 0) p[2] = p[2] + (int)p;
    if (p[3] != 0) p[3] = p[3] + (int)p;
    if (p[4] != 0) p[4] = p[4] + (int)p;
    if (p[8] != 0) p[8] = p[8] + (int)p;
    if (p[5] != 0) p[5] = p[5] + (int)p;
    if (p[6] != 0) p[6] = p[6] + (int)p;
    if (p[7] != 0) p[7] = p[7] + (int)p;
    if (p[9] != 0) p[9] = p[9] + (int)p;
    if (p[10] != 0) p[10] = p[10] + (int)p;
    if (p[11] != 0) p[11] = p[11] + (int)p;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x006c12a0  RegisterArenaReadCallbacks
// ---------------------------------------------------------------------------
void RegisterArenaReadCallbacks()
{
    u32* t = (u32*)sub_11e22c0(0x200af);
    t[1] = 0;
    t[2] = 0;
    t[3] = 0x6c1180;
    t[4] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x006c12e0 / 006c1320 / 006c1350  vector iterator helpers
// ---------------------------------------------------------------------------
u32 VecDtorRange(u32 first, u32 last, u32 out)
{
    if (first == last)
        return out;
    do {
        sub_11e0b22((void*)(first + 0x18), 8, 4, (void*)0xc2e4e0);
        first += 0x38;
        out += 0x38;
    } while (first != last);
    return out;
}

u32 VecCtorCopy(u32 dst, u32 src)
{
    sub_11e0b85((void*)dst, 8, 4, (void*)0x6c0fa0, (void*)0xc2e4e0);
    *(u32*)dst = *(u32*)src;
    *(u32*)(dst + 4) = *(u32*)(src + 4);
    return dst;
}

void VecDtorRange2(u32 first, u32 last)
{
    while (first < last) {
        sub_11e0b22((void*)(first + 0x18), 8, 4, (void*)0xc2e4e0);
        first += 0x38;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c1380  eastl vector<0x38> clear/destroy
// ---------------------------------------------------------------------------
void VecClear38(int* v)
{
    VecDtorRange2(v[0], v[1]);
    int p = v[0];
    if (p != 0 && p != v[4])
        sub_f47380((void*)p);
}

// ---------------------------------------------------------------------------
// @ 0x006c13f0  eastl vector<0x38> insert
// ---------------------------------------------------------------------------
void VecInsert38(int* v, u32 pos, u32 val)
{
    u32* end = (u32*)v[1];
    if (end != (u32*)v[2]) {
        if (pos <= val && val < (u32)end)
            val += 0x38;
        if (end != 0) {
            u32* src = end - 0xe;
            for (int i = 0; i < 0xe; ++i)
                end[i] = src[i];
        }
        u32* dst = (u32*)v[1];
        u32* src = dst - 0xe;
        while (src != (u32*)pos) {
            src -= 0xe;
            dst -= 0xe;
            for (int i = 0; i < 0xe; ++i)
                dst[i] = src[i];
        }
        for (int i = 0; i < 0xe; ++i)
            ((u32*)pos)[i] = ((u32*)val)[i];
        v[1] += 0x38;
        return;
    }
    int count = ((int)end - v[0]) / 0x38;
    int cnt;
    if (count == 0) cnt = 1;
    else { cnt = count * 2; if (cnt == 0) { cnt = 0; goto alloc_done; } }
    {
        void* p = sub_f473a0(cnt * 0x38,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0x13eb8a4, 0, 0, 0xd1);
        cnt = (int)p;
    }
alloc_done:
    {
        u32 old = v[0];
        u32 p = (u32)sub_f25ea0((void*)old, (void*)pos, (void*)cnt);
        VecDtorRange(old, (u32)pos, p);
        if (p != 0) {
            u32* d = (u32*)p;
            for (int i = 0; i < 0xe; ++i)
                d[i] = ((u32*)val)[i];
        }
        u32 tail = (u32)sub_f25ea0((void*)pos, (void*)v[1], (void*)(p + 0x38));
        VecDtorRange(pos, v[1], p + 0x38);
        u32 oldp = v[0];
        if (oldp != 0 && oldp != v[4])
            sub_f47380((void*)oldp);
        v[1] = tail;
        v[0] = cnt;
        v[2] = cnt + count * 0;   // capacity base; end computed by caller layout
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c1570  eastl vector<4> insert
// ---------------------------------------------------------------------------
void VecInsert4(int* v, u32 pos, u32 val)
{
    u32* end = (u32*)v[1];
    if (end != (u32*)v[2]) {
        if (pos <= val && val < (u32)end)
            val += 4;
        if (end != 0)
            *(u32*)end = end[-1];
        u32 s = (v[1] - 4) - pos;
        memmove((void*)((v[1]) + ((int)s >> 2) * -4), (void*)pos, s);
        *(u32*)pos = *(u32*)val;
        v[1] += 4;
        return;
    }
    int n = ((int)end - v[0]) >> 2;
    int cap;
    if (n == 0) cap = 1;
    else { cap = n * 2; if (cap == 0) { cap = 0; goto alloc_done; } }
    cap = (int)sub_f473a0(cap * 4,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0x13eb8a4, 0, 0, 0xd1);
alloc_done:
    {
        u32 s = pos - v[0];
        u32 p = (u32)sub_11e0744((void*)cap, (void*)v[0], s);
        u32* slot = (u32*)(p + (s >> 2) * 4);
        if (slot != 0)
            *slot = *(u32*)val;
        u32 oldend = v[1];
        u32 q = (u32)sub_11e0744(slot + 1, (void*)pos, oldend - pos);
        u32 old = v[0];
        if (old != 0 && old != v[4])
            sub_f47380((void*)old);
        v[0] = cap;
        v[1] = q + ((oldend - pos) >> 2) * 4;
        v[2] = cap + cap * 0;  // placeholder (capacity set from local)
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c1680  arena skin-sink collection -> FUN_006c24b0
// ---------------------------------------------------------------------------
void CollectArenaObjects(int self, u32* out, u32 a3)
{
    void* arena = *(void**)(self + 0x18);
    for (int i = 0; i < (int)sub_11e23a0(arena); ++i) {
        char obj[0x38];
        sub_11e0b85(obj + 0x18, 8, 4, (void*)0x6c0fa0, (void*)0xc2e4e0);
        *(u32*)(obj + 0x18) = 0;
        *(u32*)(obj + 0x1c) = 1;
        sub_11e28e0(arena, i, obj);
        sub_11e0b22(obj + 0x18, 8, 4, (void*)0xc2e4e0);
    }
    sub_acfe0(a3, out[0]);
    sub_b4b60(out[0], sub_b1f90(0x49a3d83, 0, 0));
}

// ---------------------------------------------------------------------------
// @ 0x006c1ae0  SP::cAnimationBaker::GetBakedAnimations
// ---------------------------------------------------------------------------
struct cAnimationBaker {
    char pad00[8];
    u32 f08, f0c, f10;
    void GetBakedAnimations();
};

void cAnimationBaker::GetBakedAnimations()
{
    u32 a = f08, b = f0c, c = f10;
    void* handle = 0;
    if (((c & 0xc0000000) == 0x40000000) && ((c & 0xff0000) == 0x600000) && ((c & 0x1f000000) == 0)) {
        c = (c & 0xe1ffffff) | 0x1000000;
        void* mgr = EAGetManager();
        if (handle != 0) {
            handle = 0;
            ((void(__thiscall*)(void*))(*(void***)handle)[4 / 4])(handle);
        }
        bool ok = ((bool(__thiscall*)(void*, u32*, void**))(*(void***)mgr)[0xc / 4])(mgr, &a, &handle);
        if (ok && b != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))(*(void***)(void*)b)[0xc / 4])((void*)b, 0x2f4e681b);
            if (p != 0) {
                *(u32*)c = (u32)p;
                ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
                goto done;
            }
        }
    } else {
        void* g = IDGenerator();
        ((void(__thiscall*)(void*))(*(void***)g)[4 / 4])(g);
    }
    CollectArenaObjects((int)this, (u32*)c, (u32)&a);
done:
    if (*(u32*)c != 0)
        sub_ac040(*(u32*)c, 9);
    if (b != 0)
        ((void(__thiscall*)(void*))(*(void***)(void*)b)[4 / 4])((void*)b);
}

// ---------------------------------------------------------------------------
// @ 0x006c1c30
// ---------------------------------------------------------------------------
int StateFromGlobal(u32* p)
{
    u32 v = **(u32**)((char*)p + 0x28);
    if (v == 1)
        return 0;
    if (v == 3) {
        u8* q = (u8*)sub_11fd860(0);
        if (q != 0) {
            if (q[8] == 1 && q[9] == 6)
                return 1;
            if (q[8] == 0 && q[9] == 1)
                return 2;
        }
    }
    return 3;
}

// ---------------------------------------------------------------------------
// @ 0x006c1c80
// ---------------------------------------------------------------------------
void MakeStream(u32* out, u32* in)
{
    u32 v = sub_928a30(in[0], in[1], 0, 0, 0, 0, 0, 0);
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    out[0] = v;
}
