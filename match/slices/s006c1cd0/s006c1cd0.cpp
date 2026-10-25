// Slice s006c1cd0 — SP::cAnimationBaker baked-animation records, arena resource
// and small sort/compare helpers (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <string.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

struct Key16 { u32 k0, k1, k2, k3; };

// 16-byte key less-than, inlined (same predicate as KeyLess @ 0x006c26f0)
#define KEY_LESS(x, y) ((x)[1] < (y)[1] || ((x)[1] == (y)[1] && ((x)[0] < (y)[0] || ((x)[0] == (y)[0] && ((x)[3] < (y)[3] || ((x)[3] == (y)[3] && (x)[2] < (y)[2]))))))
// same predicate with the left key held in scalars (a0..a3), right key as a pointer
#define LESS6(a0, a1, a2, a3, b) ((a1) < (b)[1] || ((a1) == (b)[1] && ((a0) < (b)[0] || ((a0) == (b)[0] && ((a3) < (b)[3] || ((a3) == (b)[3] && (a2) < (b)[2]))))))

// ---------------------------------------------------------------------------
// external helpers (masked relocations)
// ---------------------------------------------------------------------------
extern u32   sub_928a30(u32, u32, int,int,int,int,int,int);   // create render object
extern void  sub_9276c0(void*, u32);                          // cLocalLightInfo dtor
extern const float g_colScale;                                // 0x140a658 (= 1/127)
extern void* g_lightManager;                                  // 0x16c8b44

struct LightMgr { void Destroy(u32 p); };
extern void  sub_11fb220(u32);                                // free
struct Arena {
    void Release();                                           // 0x011e40a0 (rw::core::arena::Arena::Release)
};
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
u32* InsertionSort6(u32* first, u32* last)
{
    if (first == last)
        return last;
    u32* cur = first + 6;
    if (cur == last)
        return last;
    u32* hole;
    do {
        u32 k0 = cur[0], k1 = cur[1], k2 = cur[2], k3 = cur[3], k4 = cur[4], k5 = cur[5];
        hole = cur;
        while (hole != first) {
            u32* prev = hole - 6;
            if (!LESS6(k0, k1, k2, k3, prev))
                break;
            hole[0] = prev[0]; hole[1] = prev[1]; hole[2] = prev[2];
            hole[3] = prev[3]; hole[4] = prev[4]; hole[5] = prev[5];
            hole = prev;
        }
        hole[0] = k0; hole[1] = k1; hole[2] = k2;
        hole[3] = k3; hole[4] = k4; hole[5] = k5;
        cur += 6;
    } while (cur != last);
    return hole;
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
    bool (*const volatile keyLess)(const u32*, const u32*) = KeyLess;
    if (KEY_LESS(a, b)) {
        if (keyLess(b, c))
            return b;
        if (keyLess(a, c))
            return c;
        return a;
    }
    if (keyLess(a, c))
        return a;
    if (keyLess(b, c))
        return c;
    return b;
}

// ---------------------------------------------------------------------------
// @ 0x006c2a00  sift-up insert of one 6-dword record
// ---------------------------------------------------------------------------
u32* SiftUp(u32* base, int lower, int pos, u32 k0, u32 k1, u32 k2, u32 k3, u32 k4, u32 k5)
{
    u32 kk[6] = { k0, k1, k2, k3, k4, k5 };
    int i = pos;
    int parent = (i - 1) >> 1;
    while (i > lower) {
        u32* p = base + parent * 6;
        if (!KEY_LESS(p, kk))
            break;
        u32* d = base + i * 6;
        d[0] = p[0]; d[1] = p[1]; d[2] = p[2];
        d[3] = p[3]; d[4] = p[4]; d[5] = p[5];
        i = parent;
        parent = (i - 1) >> 1;
    }
    u32* d = base + i * 6;
    d[0] = kk[0]; d[1] = kk[1]; d[2] = kk[2];
    d[3] = kk[3]; d[4] = kk[4]; d[5] = kk[5];
    return d;
}

// ---------------------------------------------------------------------------
// @ 0x006c2bc0  sift-down then insert
// ---------------------------------------------------------------------------
u32* SiftDown(u32* base, int lower, int count, int pos, u32 k0, u32 k1, u32 k2, u32 k3, u32 k4, u32 k5)
{
    int child = pos * 2 + 2;
    while (child < count) {
        u32* c = base + child * 6;
        u32* p = base + (child - 1) * 6;
        if (KEY_LESS(c, p))
            --child;
        u32* s = base + child * 6;
        u32* d = base + pos * 6;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
        pos = child;
        child = pos * 2 + 2;
    }
    if (child == count) {
        u32* s = base + (child - 1) * 6;
        u32* d = base + pos * 6;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
        pos = child - 1;
    }
    return SiftUp(base, lower, pos, k0, k1, k2, k3, k4, k5);
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
    if (field18 != 0) {
        ((Arena*)field18)->Release();
    }
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
// animation-bake / arena-resource helpers
// ---------------------------------------------------------------------------
typedef void* (__thiscall* BakeFrameAtFn)(void* ctl, u32 frame);
typedef void  (__thiscall* EmbeddedSetTransformFn)(void* self, const float* m, int a, int b);
typedef void  (__thiscall* FixedVectorInsertFn)(void* vec, int* pos, const int* value);
typedef void  (__thiscall* ArenaAddObjectFn)(void* arena, void* a, u32 handle, void* b);

extern void* rwSectionInitCombined(void* out, int count, void* data, int a, int b);     // 0x011e4dd0
extern void* rwArenaSectionsInitialize(void* arr, int count, void* data, int a, int b); // 0x011e4e70
extern void* arenaGetResourceDescriptor(void* out, int size, int a, u32 magic,
                                        void* sections, void* desc, void* mgr);         // 0x011e3190
extern void* arenaInitialize(void* arr, int size, int a, u32 magic,
                             void* sections, void* desc, void* mgr);                    // 0x011e3f20
extern void  arenaFinalize(void* p);                                                    // 0x011e3ed0
extern void  ehVectorCtor(void* p, int elemSize, int count, void* ctorFn);              // 0x011e0b85
extern void  ehVectorDtor(void* p, int elemSize, int count, void* dtorFn);              // 0x011e0b22
extern void* sub_f473a0(u32 size, const char* name, int a, int b, int c, int d);        // 0x00f473a0
extern void  sub_f47380(void* p);                                                       // 0x00f47380

struct BakePair {
    void* state;   // +0x00
    u32   frame;   // +0x04
};

struct BakeContext {
    char       rsv00[8];
    BakePair*  pairs;     // +0x08
    char       rsv0c[4];
    u32**      flagsPtr;  // +0x10
};

struct BakeFrameCtl {
    char rsv00[0x14];
    u32  frameCount;      // +0x14
};

// ---------------------------------------------------------------------------
// @ 0x006c1cd0  animation-bake driver: inverse-bind matrices + transform stack
// ---------------------------------------------------------------------------
void AnimationBakeDriver(BakeContext* ctx, BakeFrameCtl* ctl, const float* xf)
{
    float inv[256][16];
    float stack[64][16];

    const u32 count = ctl->frameCount;
    BakePair* const pairs = ctx->pairs;
    BakePair* const pairEnd = pairs + count;
    const u32* const flags = *ctx->flagsPtr;
    BakePair* curPair = pairs;

    float cur[16];
    for (int k = 0; k < 16; ++k)
        cur[k] = xf[k];

    bool done = false;

    if (count != 0) {
        // inverse bind-pose matrix for every frame (back to front fills the array)
        for (u32 n = count; n != 0; --n) {
            const u32 fi = n - 1;
            const float* q = (const float*)((BakeFrameAtFn)0x011fda50)(ctl, fi);
            const float x = q[0] * 1.4142135f;
            const float y = q[1] * 1.4142135f;
            const float z = q[2] * 1.4142135f;
            const float w = q[3] * 1.4142135f;
            const float xx = (0.0f - x) * x + 0.5f;
            const float yy = (0.0f - y) * y + 0.5f;
            const float zz = (0.0f - z) * z + 0.5f;
            const float t1 = w * z + y * x;
            const float t2 = y * x - w * z;
            const float s  = yy + xx;
            float* m = inv[fi];
            m[0]  = zz + yy;
            m[1]  = t1;
            m[2]  = x * z - w * y;
            m[3]  = t2;
            m[4]  = t2;
            m[5]  = xx + zz;
            m[6]  = w * x + z * y;
            m[7]  = t1;
            m[8]  = w * y + x * z;
            m[9]  = z * y - w * x;
            m[10] = s;
            m[11] = s;
            m[12] = q[4];
            m[13] = q[5];
            m[14] = q[6];
            m[15] = q[7];
        }
    }

    if (count != 0) {
        float* sp = &stack[0][0];
        for (u32 i = 0; i < count; ++i) {
            if (done)
                return;

            const float* m = inv[i];
            float r[16];
            for (int col = 0; col < 4; ++col) {
                r[0 + col]  = m[1] * cur[4 + col] + m[0] * cur[0 + col] + m[2] * cur[8 + col];
                r[4 + col]  = m[5] * cur[4 + col] + m[4] * cur[0 + col] + m[6] * cur[8 + col];
                r[8 + col]  = m[9] * cur[4 + col] + m[8] * cur[0 + col] + m[10] * cur[8 + col];
                r[12 + col] = (m[13] * cur[4 + col] + m[12] * cur[0 + col] + m[14] * cur[8 + col])
                              + cur[12 + col];
            }

            while (curPair->frame == i) {
                if (curPair->state != 0)
                    ((EmbeddedSetTransformFn)0x011edc10)(curPair->state, r, 3, 1);
                ++curPair;
                if (curPair >= pairEnd) {
                    done = true;
                    break;
                }
            }

            switch (flags[i] & 3) {
            case 0:
                for (int k = 0; k < 16; ++k)
                    cur[k] = r[k];
                break;
            case 1:
                sp -= 16;
                for (int k = 0; k < 16; ++k)
                    cur[k] = sp[k];
                break;
            case 2:
                for (int k = 0; k < 16; ++k)
                    sp[k] = cur[k];
                sp += 16;
                for (int k = 0; k < 16; ++k)
                    cur[k] = r[k];
                break;
            default:
                break;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// baked arena resource: Resource + arena/sections + two render-object sets
// ---------------------------------------------------------------------------
struct BakedArenaResource : PropertyList {   // PropertyList = 0x20 bytes
    u32 field20;      // +0x20  sections
    u32 arr24[4];     // +0x24  resource render objects
    u32 arr34[4];     // +0x34  section render objects
};

// ---------------------------------------------------------------------------
// @ 0x006c22b0  anonymous namespace cBakedArenaResource constructor
// ---------------------------------------------------------------------------
void* BakeResourceCtor(void* self, void* p2, int count, void* frames, int unique,
                       const char* name)
{
    BakedArenaResource* r = (BakedArenaResource*)self;

    // base PropertyList construction (inlined)
    r->vtbl = (void*)0x13ebcdc;
    r->field04 = 0;
    r->f08 = 0; r->f0c = 0; r->f10 = 0; r->f14 = 0;
    r->vtbl = (void*)0x140a5bc;
    r->field1c = p2;
    if (p2 != 0)
        ((void(__thiscall*)(void*))(*(void***)p2)[0])(p2);
    r->f18 = 0;

    r->vtbl = (void*)0x140a5a8;
    r->field20 = 0;
    for (int i = 0; i < 4; ++i) {
        r->arr24[i] = 0;
        r->arr34[i] = 0;
    }

    struct { void* vf; } mgr;
    mgr.vf = (void*)0x140a578;
    int mgrData = ((int(__cdecl*)(void*))*(void**)0x140a57c)(&mgr);

    u8 secBuffer[32];
    rwSectionInitCombined(secBuffer, unique, frames, 0, 0);
    CreateRenderObjects(r->arr34, (u32*)secBuffer);
    void* sections = rwArenaSectionsInitialize(r->arr34, unique, frames, 0, 0);
    r->field20 = (u32)sections;

    u32 descArgs[8];
    ehVectorCtor(descArgs, 8, 4, (void*)0x00c2e4e0);
    descArgs[0] = 0;
    descArgs[1] = 1;

    u8 descBuffer[32];
    arenaGetResourceDescriptor(descBuffer, count * 4, 1, 0xcafed00d,
                               (void*)r->field20, descArgs, (void*)(mgrData + 4));
    CreateRenderObjects(r->arr24, (u32*)descBuffer);
    void* arena = arenaInitialize(r->arr24, count * 4, 1, 0xcafed00d,
                                  (void*)r->field20, descArgs, (void*)(mgrData + 4));
    r->f18 = (u32)arena;
    arenaFinalize(arena);

    ehVectorDtor(descBuffer, 8, 4, (void*)0x00c2e4e0);
    ehVectorDtor(descArgs, 8, 4, (void*)0x00c2e4e0);
    ehVectorDtor(secBuffer, 8, 4, (void*)0x00c2e4e0);
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x006c24b0  assemble and register the baked animation resource
// ---------------------------------------------------------------------------
struct BakedFrameRec {
    u32 d[14];   // 0x38 bytes
};

u32 sub_6c24b0(void* a, void* b, void* c, int count, int d, int e, const char* name)
{
    BakedFrameRec* recs = (BakedFrameRec*)c;

    struct BakedVec {
        int* begin;
        int* end;
        int* capEnd;
        int  buffer[18];
    } frames;
    frames.begin = frames.buffer;
    frames.end = frames.buffer;
    frames.capEnd = frames.buffer + 18;

    void* frameArg = (void*)d;
    int unique = e;

    if (e < 0) {
        for (int i = 0; i < count; ++i) {
            int value = (int)recs[i].d[0];
            bool found = false;
            for (int* it = frames.begin; it != frames.end; ++it) {
                if (*it == value) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (frames.end < frames.capEnd) {
                    if (frames.end != 0)
                        *frames.end = value;
                    ++frames.end;
                } else {
                    ((FixedVectorInsertFn)0x0060a600)(&frames, frames.end, &value);
                }
            }
        }
        unique = (int)(frames.end - frames.begin);
        frameArg = frames.begin;
    }

    BakedArenaResource* res = 0;
    void* mem = sub_f473a0(0x44, "Graphics", 0, 0, 0, 0);
    if (mem != 0)
        res = (BakedArenaResource*)BakeResourceCtor(mem, b, count, frameArg, unique, name);

    void* arena = (void*)res->f18;

    for (int i = 0; i < count; ++i) {
        u8 buf[0x38];
        memcpy(buf, &recs[i], 0x38);
        ((ArenaAddObjectFn)0x011e3300)(arena, buf + 8, *(u32*)buf, buf + 0x18);
        ehVectorDtor(buf + 0x18, 8, 4, (void*)0x00c2e4e0);
    }

    *(BakedArenaResource**)a = res;
    ((void(__thiscall*)(void*))(*(void***)res)[0])(res);

    if (frames.begin != 0 && frames.begin != frames.buffer)
        sub_f47380(frames.begin);

    return 0;
}

