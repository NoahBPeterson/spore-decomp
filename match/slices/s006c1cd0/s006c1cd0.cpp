// Slice s006c1cd0 — SP::cAnimationBaker baked-animation records, arena resource
// and small sort/compare helpers (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <string.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

struct Key16 { u32 k0, k1, k2, k3; };

// ---------------------------------------------------------------------------
// external helpers (masked relocations)
// ---------------------------------------------------------------------------
extern u32   sub_928a30(u32, u32, int,int,int,int,int,int);   // create render object
extern void  sub_9276c0(void*, u32);                          // cLocalLightInfo dtor
extern const float g_colScale;                                // 0x140a658 (= 1/127)
extern void* g_lightManager;                                  // 0x16c8b44

struct LightMgr { void Destroy(u32 p); };
extern void  sub_11fb220(u32);                                // free
extern void  sub_11e40a0(void*);                              // arena::Arena::Release
extern u32   sub_6c24b0(void*, void*, void*, int, int, int, const char*);
extern u32   sub_6acfe0(u32, u32);
extern u32   sub_6b1f90(u32, int, int);
extern void  sub_6b4b60(u32, u32);

// ---------------------------------------------------------------------------
// @ 0x006c2060
// ---------------------------------------------------------------------------
void CreateRenderObjects(u32* out, u32* in)
{
    for (u32 i = 0; i < 4; ++i) {
        u32 a = in[i * 2];
        if (a == 0) {
            out[i] = 0;
        } else {
            out[i] = sub_928a30(a, in[i * 2 + 1], 0, 0, 0, 0, 0, 0);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c20b0
// ---------------------------------------------------------------------------
void DestroyRenderObjects(u32* arr)
{
    for (u32 i = 0; i < 4; ++i) {
        u32 p = arr[i];
        if (p != 0) {
            ((LightMgr*)g_lightManager)->Destroy(p);
            arr[i] = 0;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c20e0
// ---------------------------------------------------------------------------
void DestroySomeRenderObjects(u32* arr)
{
    for (u32 i = 0; i < 4; ++i) {
        if (i == 1 || i == 3) {
            u32 p = arr[i];
            if (p != 0) {
                ((LightMgr*)g_lightManager)->Destroy(p);
                arr[i] = 0;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c2690  packed 0xRRGGBB -> float3 in [-1,1]
// ---------------------------------------------------------------------------
void UnpackColor(u32 packed, float* out)
{
    float k = 0.0078740157f;
    out[0] = (float)(packed & 0xff) * k - 1.0f;
    out[1] = (float)((packed >> 8) & 0xff) * k - 1.0f;
    out[2] = (float)((packed >> 16) & 0xff) * k - 1.0f;
}

// ---------------------------------------------------------------------------
// @ 0x006c26f0  less-than over a 16-byte key
// ---------------------------------------------------------------------------
bool KeyLess(const u32* a, const u32* b)
{
    if (a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]))
        return true;
    if (a[0] == b[0] && a[1] == b[1]) {
        if (a[3] < b[3])
            return true;
        if (a[3] == b[3] && a[2] < b[2])
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x006c2740  copy four 16-byte keys into `this`
// ---------------------------------------------------------------------------
struct KeyPack {
    Key16 v[4];
    void Assign(const u32* a, const u32* b, const u32* c, const u32* d);
};

void KeyPack::Assign(const u32* a, const u32* b, const u32* c, const u32* d)
{
    ((u32*)&v[0])[0] = a[0]; ((u32*)&v[0])[1] = a[1];
    ((u32*)&v[0])[2] = a[2]; ((u32*)&v[0])[3] = a[3];
    ((u32*)&v[1])[0] = b[0]; ((u32*)&v[1])[1] = b[1];
    ((u32*)&v[1])[2] = b[2]; ((u32*)&v[1])[3] = b[3];
    ((u32*)&v[2])[0] = c[0]; ((u32*)&v[2])[1] = c[1];
    ((u32*)&v[2])[2] = c[2]; ((u32*)&v[2])[3] = c[3];
    ((u32*)&v[3])[0] = d[0]; ((u32*)&v[3])[1] = d[1];
    ((u32*)&v[3])[2] = d[2]; ((u32*)&v[3])[3] = d[3];
}

// ---------------------------------------------------------------------------
// @ 0x006c2ad0  copy a 0x10-byte record and AddRef its pointer member
// ---------------------------------------------------------------------------
struct Rec16 {
    u32 a, b;
    u16 c, d;
    void* p;
    Rec16* CopyFrom(const Rec16* src);
};

Rec16* Rec16::CopyFrom(const Rec16* src)
{
    a = src->a;
    b = src->b;
    c = src->c;
    d = src->d;
    p = src->p;
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006c27b0  insertion sort (6-dword records, 0x18 stride) [first,last)
// ---------------------------------------------------------------------------
void InsertionSort6(u32* first, u32* last)
{
    if (first == last)
        return;
    u32* cur = first + 6;
    if (cur == last)
        return;
    while (true) {
        u32 k0 = cur[0], k1 = cur[1], k2 = cur[2], k3 = cur[3], k4 = cur[4], k5 = cur[5];
        u32* hole = cur;
        while (hole != first) {
            u32* prev = hole - 6;
            if (KeyLess(prev, cur) == false && !(cur[0] == prev[0] && cur[1] == prev[1] &&
                (cur[3] > prev[3] || (cur[3] == prev[3] && cur[2] >= prev[2]))))
                break;
            hole[0] = prev[0]; hole[1] = prev[1]; hole[2] = prev[2];
            hole[3] = prev[3]; hole[4] = prev[4]; hole[5] = prev[5];
            hole = prev;
        }
        hole[0] = k0; hole[1] = k1; hole[2] = k2;
        hole[3] = k3; hole[4] = k4; hole[5] = k5;
        cur += 6;
        if (cur == last)
            break;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c28a0  insertion sort for a single record [first,last); no outer loop
// ---------------------------------------------------------------------------
void InsertionSortOne(u32* first, u32* last)
{
    if (first == last)
        return;
    u32 k0 = first[0], k1 = first[1], k2 = first[2], k3 = first[3], k4 = first[4], k5 = first[5];
    u32* hole = first;
    u32* prev = first - 6;
    while (true) {
        if (!KeyLess(prev, first) && !(first[0] == prev[0] && first[1] == prev[1] &&
            (first[3] > prev[3] || (first[3] == prev[3] && first[2] >= prev[2]))))
            break;
        hole[0] = prev[0]; hole[1] = prev[1]; hole[2] = prev[2];
        hole[3] = prev[3]; hole[4] = prev[4]; hole[5] = prev[5];
        hole = prev;
        prev -= 6;
    }
    hole[0] = k0; hole[1] = k1; hole[2] = k2;
    hole[3] = k3; hole[4] = k4; hole[5] = k5;
}

// ---------------------------------------------------------------------------
// @ 0x006c2970  median-of-three pointer
// ---------------------------------------------------------------------------
u32* Median3(u32* a, u32* b, u32* c)
{
    if (KeyLess(a, b) || (a[0] == b[0] && a[1] == b[1] &&
        ((a[3] < b[3]) || (a[3] == b[3] && a[2] < b[2])))) {
        if (!KeyLess(b, c)) {
            if (!KeyLess(a, c))
                return a;
            return c;
        }
    } else {
        if (KeyLess(a, c))
            return a;
        if (KeyLess(b, c))
            return c;
    }
    return b;
}

// ---------------------------------------------------------------------------
// @ 0x006c2a00  sift-up insert of one 6-dword record
// ---------------------------------------------------------------------------
void SiftUp(u32* base, u32* pos, u32* key)
{
    u32 k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3], k4 = key[4], k5 = key[5];
    int i = (int)((pos - base) / 6);
    while (i > 0) {
        int parent = (i - 1) >> 1;
        u32* p = base + parent * 6;
        if ((p[0] == k0 && p[1] == k1) &&
            (p[3] > k3 || (p[3] == k3 && p[2] >= k2)))
            break;
        u32* d = base + i * 6;
        d[0] = p[0]; d[1] = p[1]; d[2] = p[2];
        d[3] = p[3]; d[4] = p[4]; d[5] = p[5];
        i = parent;
    }
    u32* d = base + i * 6;
    d[0] = k0; d[1] = k1; d[2] = k2; d[3] = k3; d[4] = k4; d[5] = k5;
}

// ---------------------------------------------------------------------------
// @ 0x006c2bc0  sift-down then insert
// ---------------------------------------------------------------------------
void SiftDown(u32* base, u32* key, int pos, int count)
{
    u32 k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3], k4 = key[4], k5 = key[5];
    while (pos * 2 + 2 < count) {
        int child = pos * 2 + 2;
        u32* c = base + child * 6;
        u32* p = base + (child - 1) * 6;
        if (!KeyLess(c, p) && !(c[0] == p[0] && c[1] == p[1] &&
            (c[3] > p[3] || (c[3] == p[3] && c[2] >= p[2]))))
            child = pos * 2 + 1;
        u32* d = base + pos * 6;
        u32* s = base + child * 6;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
        pos = child;
    }
    if (pos * 2 + 2 == count) {
        u32* s = base + (pos * 2 + 1) * 6;
        u32* d = base + pos * 6;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
        pos = pos * 2 + 1;
    }
    SiftUp(base, base + pos * 6, key);
}

// ---------------------------------------------------------------------------
// @ 0x006c2b10  copy a range of 0x10-byte records, AddRef each pointer
// ---------------------------------------------------------------------------
Rec16* CopyRange(Rec16* first, Rec16* last, Rec16* out)
{
    if (first == last)
        return out;
    do {
        if (out != 0) {
            out->a = first->a;
            out->b = first->b;
            out->c = first->c;
            out->d = first->d;
            out->p = first->p;
            if (out->p != 0)
                ((void(__thiscall*)(void*))(*(void***)out->p)[0])(out->p);
        }
        ++first;
        ++out;
    } while (first != last);
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x006c2120  Editor::cEditorResource cleanup
// ---------------------------------------------------------------------------
struct EditorResource {
    void* vtbl;
    char pad04[0x18];
    void* field1c;
    void Cleanup();
};

void EditorResource::Cleanup()
{
    if (field1c != 0)
        ((void(__thiscall*)(void*))(*(void***)field1c)[4 / 4])(field1c);
    vtbl = (void*)0x13eb938;
}

// ---------------------------------------------------------------------------
// @ 0x006c2170  destructor body
// ---------------------------------------------------------------------------
struct EditorResource2 {
    void* vtbl;              // +0x00
    char pad04[0x14];
    void* field18;           // +0x18 arena
    void* field1c;           // +0x1c
    void* field20;           // +0x20
    u32   arr24[4];          // +0x24
    u32   arr34[4];          // +0x34
    void Destroy();
};

void EditorResource2::Destroy()
{
    vtbl = (void*)0x140a5a8;
    if (field18 != 0)
        sub_11e40a0(field18);
    DestroyRenderObjects(arr24);
    if (field20 != 0)
        sub_11fb220((u32)field20);
    DestroyRenderObjects(arr34);
    if (field1c != 0)
        ((void(__thiscall*)(void*))(*(void***)field1c)[4 / 4])(field1c);
    vtbl = (void*)0x13eb938;
}

// ---------------------------------------------------------------------------
// @ 0x006c2240  Editor::cPropertyList ctor
// ---------------------------------------------------------------------------
struct PropertyList {
    void* vtbl;              // +0x00
    u32   field04;           // +0x04
    u32   f08, f0c, f10, f14, f18; // +0x08
    void* field1c;           // +0x1c
    PropertyList(void* p);
};

PropertyList::PropertyList(void* p)
{
    vtbl = (void*)0x13ebcdc;
    field04 = 0;
    f08 = 0; f0c = 0; f10 = 0; f14 = 0; f18 = 0;
    vtbl = (void*)0x140a5bc;
    field1c = p;
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
    f18 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x006c1cd0  animation-bake driver (large; reconstructed skeleton)
// ---------------------------------------------------------------------------
struct BakeContext {
    char pad00[0x18];
    void* field18;
    char pad1c[0x40];
    void* arr5c[4];
    void* arr6c[4];
    void Run();
};

void BakeContext::Run()
{
    if (field18 != 0)
        ((void(__thiscall*)(void*))(*(void***)field18)[0x10 / 4])(field18);
    DestroyRenderObjects((u32*)arr5c);
    DestroyRenderObjects((u32*)arr6c);
}

// ---------------------------------------------------------------------------
// @ 0x006c22b0  anonymous namespace cBakedArenaResource constructor
// ---------------------------------------------------------------------------
void* BakeResourceCtor(void* self, void* a, void* b, void* key, void* name)
{
    (void)a; (void)b; (void)key; (void)name;
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x006c24b0  assemble and register the baked animation resource
// ---------------------------------------------------------------------------
u32 sub_6c24b0(void* a, void* b, void* c, int count, int d, int e, const char* name)
{
    (void)a; (void)b; (void)c; (void)count; (void)d; (void)e; (void)name;
    return 0;
}

