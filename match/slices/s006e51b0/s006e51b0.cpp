// slice s006e51b0 -- tail of SPGraphicsCubeMapCapture.obj + out-of-line template helpers.
// Flags: /O2 /MD /Gy /EHsc /TP (/arch:SSE2 for the float routine; x87 used for sqrt).
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" __declspec(nothrow) void* __cdecl memset(void*, int, unsigned int);
extern "C" __declspec(dllimport) int __cdecl fprintf(void*, const char*, ...);
extern "C" __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl fclose(void*);
#include <math.h>
#pragma function(memcpy)

// ===========================================================================
// Shared 12-byte element.
struct Float3 {
    float x, y, z;
};

// ---------------------------------------------------------------------------
// @ 0x006e54d0
// Dispatch `count` sprite refs through a 32-byte function table indexed by the
// entry's first uint16.  The trailing two arguments are part of the caller's
// calling sequence (soft-state id, dirty flag) and are ignored here.
typedef void(__cdecl* SpriteDispatchFn)(unsigned short, unsigned short, int);

struct SpriteDispatchSlot {
    SpriteDispatchFn fn;
    char pad[28];
};

struct SpriteRef {
    unsigned short type;   // +0
    unsigned short f1;     // +2
    unsigned short f2;     // +4
    unsigned short f3;     // +6
    unsigned short f4;     // +8
    unsigned short f5;     // +10
};

extern SpriteDispatchSlot g_spriteDispatch[];   // 0x016fa604

void ShaderDispatch(int count, SpriteRef* refs, bool flag, int softState, bool dirty)
{
    for (int i = 0; i < count; ++i) {
        g_spriteDispatch[refs[i].type].fn(refs[i].f3, refs[i].f2, flag);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e5760
// Fill `count` 12-byte elements with *value, tolerating a null destination.
void FillFloat3N(Float3* dst, unsigned int count, const Float3* value)
{
    Float3* p = dst;
    while (count > 0) {
        if (p) {
            *p = *value;
        }
        --count;
        ++p;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e5790
// Zero a 3-dword element (used as the element constructor callback).
void __fastcall ZeroTriple(uint32_t* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e57a0
// Refcounted release for the shader-state object; runs the destructor and frees
// when the count reaches zero.
struct ShaderState;
extern "C" void ShaderStateUnlockHook();
__declspec(noinline) void __fastcall ShaderState_Destroy(ShaderState* self);
void operator_delete(void*);

int __fastcall ShaderState_Release(ShaderState* self)
{
    int n = *(int*)((char*)self + 0x3c) - 1;
    ShaderStateUnlockHook();
    if (n == 0) {
        ShaderState_Destroy(self);
        operator_delete(self);
    }
    return n;
}

// ===========================================================================
// Complete bodies of the remaining functions.
// ===========================================================================

void __cdecl operator delete[](void*);   // 0xf47380
// Out-of-line allocator entry points (operator new / delete[]).
void* operator new(unsigned int n, const char* name, int a, int b, int c, int d);   // 0xf473a0
extern void* __cdecl AllocatorAllocate(unsigned int n, const char* name, int flags, int dflags,
                                       const char* file, int line);              // 0xf473a0
static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---------------------------------------------------------------------------
// Vector of 12-byte sprite refs, the element type of the shader-state arrays.
struct SprVec {
    SpriteRef *b, *e, *c;     // begin / end / capacity
    int al[2];                // allocator
    SprVec() { b = 0; e = 0; c = 0; }          // 0x6e5790-style element constructor
    ~SprVec();                                 // 0x7a41a0
    void __thiscall Resize(unsigned int n);    // 0x6e5cd0
    SpriteRef* begin() { return b; }
    SpriteRef* end() { return e; }
    static __forceinline SpriteRef* CopyF(SpriteRef* f, SpriteRef* l, SpriteRef* d)
    {
        for (; f != l; ++f, ++d) {
            *d = *f;
        }
        return d;
    }
    __forceinline SpriteRef* erase(SpriteRef* first, SpriteRef* last)
    {
        SpriteRef* i = CopyF(last, e, first);
        e -= (last - first);
        return first;
    }
    void clear() { erase(begin(), end()); }
};

// Release hook of a shader resource: virtual slot 2, called as stdcall(obj).
struct Res {
    void** vtbl;
    void Release() { ((void(__stdcall*)(Res*))vtbl[2])(this); }
};

// ---------------------------------------------------------------------------
// Stream + D3D device interfaces (only the slots used here).
struct Stream {
    void** vtbl;
    int Read(void* dst, int n) { return ((int(__fastcall*)(Stream*, int, void*, int))vtbl[12])(this, 0, dst, n); }
};
struct Dev {
    void** vtbl;
    void SetVertexShader(Res* s) { ((long(__stdcall*)(Dev*, Res*))vtbl[0x170 / 4])(this, s); }
    void SetPixelShader(Res* s) { ((long(__stdcall*)(Dev*, Res*))vtbl[0x1ac / 4])(this, s); }
    void CreateVertexShader(const void* fn, Res** out) { ((long(__stdcall*)(Dev*, const void*, Res**))vtbl[0x16c / 4])(this, fn, out); }
    void CreatePixelShader(const void* fn, Res** out) { ((long(__stdcall*)(Dev*, const void*, Res**))vtbl[0x1a8 / 4])(this, fn, out); }
};

extern "C" int __cdecl ReadInt32(Stream* s, void* p, int n, int endian);       // 0x93a780
extern "C" int __cdecl ReadUInt16(Stream* s, void* p, int n, int endian);      // 0x93a700
extern "C" bool __cdecl ReadExact(Stream* s, void* p, int n);                  // 0x93a6c0

// Fixed-capacity byte vector (eastl::fixed_vector<uint8_t, 256>).
struct ByteVec {
    unsigned char *b, *e, *c;     // +0 / +4 / +8
    int al;                       // +0xc
    unsigned char* buf;           // +0x10 inline storage start
    int pad;
    unsigned char data[256];      // +0x18
    ByteVec() { b = data; e = data; c = data + 256; buf = data; }
    ~ByteVec()
    {
        if (b && b != buf) {
            operator delete[](b);
        }
    }
    void __thiscall FillInsert(unsigned char* pos, unsigned int n, const unsigned char* val);   // 0x6e5a30
    void Resize(unsigned int len)
    {
        unsigned char zero;
        unsigned int size = e - b;
        if (len > size) {
            zero = 0;
            FillInsert(e, len - size, &zero);
        } else {
            unsigned char* first = b + len;
            unsigned char* last = e;
            memcpy(first, last, e - last);
            e += first - last;
        }
    }
};

// @ 0x006e5a30  vector<uint8_t>::DoInsertValues (fill insert of n copies)
void __thiscall ByteVec::FillInsert(unsigned char* pos, unsigned int n, const unsigned char* val)
{
    if ((unsigned int)(c - e) >= n) {
        if (n) {
            unsigned char v = *val;
            unsigned char* oldEnd = e;
            unsigned int after = oldEnd - pos;
            if (n < after) {
                unsigned char* mid = oldEnd - n;
                memcpy(oldEnd, mid, oldEnd - mid);
                e += n;
                memmove(pos + n, pos, mid - pos);
                memset(pos, v, n);
            } else {
                unsigned int extra = n - after;
                if (extra) memset(oldEnd, v, extra);
                e += extra;
                memcpy(e, pos, after);
                e += after;
                memset(pos, v, after);
            }
        }
    } else {
        unsigned int size = e - b;
        unsigned int cap = size * 2;
        if (size == 0) cap = 1;
        unsigned int need = size + n;
        if (need < cap) need = cap;
        unsigned char* nb = 0;
        if (need) {
            nb = (unsigned char*)AllocatorAllocate(need, "Graphics", 0, 0, kAllocFile, 0xd1);
        }
        unsigned int before = pos - b;
        memcpy(nb, b, before);
        unsigned char* p = nb + before;
        unsigned char v = *val;
        if (n) memset(p, v, n);
        p += n;
        unsigned int after = e - pos;
        memcpy(p, pos, after);
        p += after;
        if (b && b != buf) {
            operator delete[](b);
        }
        b = nb;
        e = p;
        c = nb + need;
    }
}

// ---------------------------------------------------------------------------
// Vector of Float3: DoInsertValues fill-insert, with the EASTL copy helpers.
struct Float3Vec {
    Float3 *b, *e, *c;
    int al[2];
    void __thiscall FillInsert(Float3* pos, unsigned int n, const Float3* val);   // 0x6e5870
};
extern Float3* __cdecl CopyRange(Float3* first, Float3* last, Float3* dest);                           // 0xa11310
extern void __cdecl UninitCopyImpl(Float3** result, Float3* a, Float3* b, Float3* c, Float3* d);     // 0x898b80
extern void __cdecl CopyBackward(Float3* first, Float3* last, Float3* destEnd);                        // 0xabced0
extern void __cdecl FillRange(Float3* first, Float3* last, const Float3* val);                         // 0xa177f0

// @ 0x006e5870
void __thiscall Float3Vec::FillInsert(Float3* pos, unsigned int n, const Float3* val)
{
    if ((unsigned int)(c - e) >= n) {
        if (n) {
            Float3 tmp = *val;
            Float3* oldEnd = e;
            unsigned int after = oldEnd - pos;
            if (n < after) {
                Float3* mid = oldEnd - n;
                UninitCopyImpl(&pos, mid, oldEnd, oldEnd, pos);
                e += n;
                CopyBackward(pos, mid, oldEnd);
                FillRange(pos, pos + n, &tmp);
            } else {
                unsigned int extra = n - after;
                FillFloat3N(oldEnd, extra, &tmp);
                e += extra;
                Float3* start = pos;
                UninitCopyImpl(&pos, start, oldEnd, e, start);
                e += after;
                FillRange(start, oldEnd, &tmp);
            }
        }
    } else {
        unsigned int size = e - b;
        unsigned int cap = size * 2;
        if (size == 0) cap = 1;
        unsigned int need = size + n;
        if (need < cap) need = cap;
        Float3* nb = 0;
        if (need) {
            nb = (Float3*)AllocatorAllocate(need * 12, "Graphics", 0, 0, kAllocFile, 0xd1);
        }
        Float3* p = CopyRange(b, pos, nb);
        FillFloat3N(p, n, val);
        Float3* q = CopyRange(pos, e, p + n);
        if (b && ((int*)b)[-1] != 0) {
            operator delete[](b);
        }
        b = nb;
        e = q;
        c = nb + need;
    }
}

// ---------------------------------------------------------------------------
// Shader state object (hardware vertex/pixel shader pairs plus sprite tables).
struct ShaderState {
    char    pad0[0x14];
    void*   dispatchCb;       // +0x14  SP::DirectShaderDispatchCallback
    char    pad1[0x20];
    int     f38, f3c, f40, f44;   // f3c: refcount
    Res*    vs[16];               // +0x48
    Res*    ps[16];               // +0x88
    SprVec  tabA[16];             // +0xc8
    SprVec  tabB[16];             // +0x208

    Res* GetVS(int i) { return vs[i]; }
    Res* GetPS(int i) { return ps[i]; }
    ShaderState();                // 0x6e57d0
    ~ShaderState();               // 0x6e56b0
    void Reset();                 // 0x6e5bd0
    bool __thiscall BaseRead(Stream* s, int a, int b);   // 0x777840 SP::cShaderBase::Read
    bool Read(Stream* s, int a, int b);                  // 0x6e5d50
};

// @ 0x006e57d0
ShaderState::ShaderState() : f38(0), f3c(0), f40(0), f44(0)
{
    memset(vs, 0, sizeof(vs));
    memset(ps, 0, sizeof(ps));
}

// @ 0x006e56b0
ShaderState::~ShaderState()
{
    for (int i = 0; i < 16; ++i) {
        if (GetVS(i)) GetVS(i)->Release();
        if (GetPS(i)) GetPS(i)->Release();
    }
}

// @ 0x006e5bd0
void ShaderState::Reset()
{
    for (int i = 0; i < 16; ++i) {
        if (vs[i]) {
            vs[i]->Release();
            vs[i] = 0;
        }
        if (ps[i]) {
            ps[i]->Release();
            ps[i] = 0;
        }
        tabA[i].clear();
        tabB[i].clear();
    }
}

// ShaderState::Read (0x006e5d50): read a shader blob: per-id vertex shader, pixel shader and two sprite tables
int SP_DirectShaderDispatchCallback();

static void ReadTable(Stream* s, SprVec* v, int count)
{
    v->Resize(count);
    for (int i = 0, off = 0; i < count; ++i, off += 12) {
        ReadUInt16(s, (char*)v->b + off, 1, 0);
        ReadUInt16(s, (char*)v->b + off + 2, 1, 0);
        ReadUInt16(s, (char*)v->b + off + 4, 1, 0);
        ReadUInt16(s, (char*)v->b + off + 6, 1, 0);
        ReadInt32(s, (char*)v->b + off + 8, 1, 0);
    }
}

extern Dev* g_d3dDevice;   // 0x16f89d0

// @ 0x006e5d50
bool ShaderState::Read(Stream* s, int a, int b)
{
    if (!BaseRead(s, a, b)) {
        return false;
    }
    ByteVec buf;
    dispatchCb = (void*)SP_DirectShaderDispatchCallback;
    unsigned char op;
    ReadExact(s, &op, 1);
    while (op != 0xff) {
        int len;
        ReadInt32(s, &len, 1, 0);
        buf.Resize(len);
        s->Read(buf.b, len);
        g_d3dDevice->CreateVertexShader(buf.b, &vs[op]);
        ReadInt32(s, &len, 1, 0);
        buf.Resize(len);
        s->Read(buf.b, len);
        g_d3dDevice->CreatePixelShader(buf.b, &ps[op]);
        ReadInt32(s, &len, 1, 0);
        tabA[op].Resize(len);
        for (int i = 0, off = 0; i < len; ++i, off += 12) {
            ReadUInt16(s, (char*)tabA[op].b + off, 1, 0);
            ReadUInt16(s, (char*)tabA[op].b + off + 2, 1, 0);
            ReadUInt16(s, (char*)tabA[op].b + off + 4, 1, 0);
            ReadUInt16(s, (char*)tabA[op].b + off + 6, 1, 0);
            ReadInt32(s, (char*)tabA[op].b + off + 8, 1, 0);
        }
        ReadInt32(s, &len, 1, 0);
        tabB[op].Resize(len);
        for (int i = 0, off = 0; i < len; ++i, off += 12) {
            ReadUInt16(s, (char*)tabB[op].b + off, 1, 0);
            ReadUInt16(s, (char*)tabB[op].b + off + 2, 1, 0);
            ReadUInt16(s, (char*)tabB[op].b + off + 4, 1, 0);
            ReadUInt16(s, (char*)tabB[op].b + off + 6, 1, 0);
            ReadInt32(s, (char*)tabB[op].b + off + 8, 1, 0);
        }
        ReadExact(s, &op, 1);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006e5520  SP::DirectShaderDispatchCallback
struct TexBind {
    int   slot;     // +0
    int** tex;      // +4: pointer to a texture handle, or null
    int   pad[2];
};
struct TexBindList {
    int     count;
    TexBind items[1];   // +4
};
struct CurShader {
    int pad;
    int index;      // +4
};

extern CurShader*   g_curShader;       // 0x16f6dac
extern ShaderState* g_activeShader;    // 0x16f6568
extern Res*         g_curVS;           // 0x16f6564
extern Res*         g_curPS;           // 0x16f89cc
extern int          g_softState;       // 0x16f9110
extern unsigned int g_shaderDirty[64]; // 0x16f89f8
extern unsigned int g_rasterDelta;     // 0x16f8b00
extern TexBindList* g_texBinds;        // 0x16f6ddc
extern void __cdecl ActiveState_SetTexture(int slot, int tex);   // 0x11f1280
extern void __cdecl FUN_011f7850();
extern void __cdecl FUN_011f6920();

int SP_DirectShaderDispatchCallback()
{
    int idx = 0;
    if (g_curShader) {
        idx = g_curShader->index;
    }
    ShaderState* ss = g_activeShader;
    if (!ss->vs[idx] || !ss->ps[idx]) {
        idx = 0;
    }
    Res* v = ss->vs[idx];
    bool vsChanged = g_curVS != v;
    if (g_curVS != v) {
        g_d3dDevice->SetVertexShader(v);
        g_curVS = v;
    }
    Res* p = ss->ps[idx];
    bool psChanged = g_curPS != p;
    if (g_curPS != p) {
        g_d3dDevice->SetPixelShader(p);
        g_curPS = p;
    }
    SprVec* ta = &ss->tabA[idx];
    ShaderDispatch(ta->e - ta->b, ta->b, true, g_softState, vsChanged);
    SprVec* tb2 = &ss->tabB[idx];
    ShaderDispatch(tb2->e - tb2->b, tb2->b, false, g_softState, psChanged);
    for (int k = 0; k < 64; ++k) {
        g_shaderDirty[k] = 0;
    }
    FUN_011f7850();
    FUN_011f6920();
    TexBindList* tb = g_texBinds;
    if (tb) {
        for (int i = 0; i < tb->count; ++i) {
            int slot = tb->items[i].slot;
            if (tb->items[i].tex) {
                ActiveState_SetTexture(slot, **tb->items[i].tex);
                g_rasterDelta |= 1 << slot;
            } else {
                ActiveState_SetTexture(slot, 0);
                g_rasterDelta |= 1 << slot;
            }
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// SP::SHFromCubeMap (0x006e51b0)
// Project a cube map onto spherical-harmonic coefficients (6 prefiltered faces) and
// optionally dump the coefficients to "<dir><name>.txt".
struct Vec4 { float v[4]; };
struct CoeffRef { const void* p; int i; };

struct CubeFace {
    char pad[0x12];
    unsigned char face;
    void __thiscall FillSpriteTexture(void* pixels, unsigned int bytes, int zero);   // 0x11f0440
};
extern void __cdecl PrefilterCube(Vec4* coeffs, int size, int face, void* pixels, float x, float y, float z, int extra);   // 0x6e2b50

struct VObj { void** vtbl; };
extern VObj* __cdecl GetRenderer();       // 0x67dd50
extern VObj* __cdecl GetModelManager();   // 0x67dd80
extern int   __cdecl FUN_00688cf0(int a);

extern char g_sentinel;   // 0x1667bac (shared empty-string sentinel)
struct EStr {
    char *b, *e, *c;
    EStr() { b = &g_sentinel; e = &g_sentinel; c = &g_sentinel + 1; }
    ~EStr()
    {
        if (c - b > 1 && b) {
            operator delete[](b);
        }
    }
};
extern EStr __cdecl ConvertToString8(int v);                               // 0x93c440
extern int __cdecl StrSprintf(EStr* self, const char* fmt, ...);           // 0x472fe0

// @ 0x006e51b0
void SP_SHFromCubeMap(CubeFace* tex, int size, char dump, const char* name, int extra,
                      float x, float y, float z)
{
    static const int faceMap[6] = { 5, 1, 4, 0, 3, 2 };
    __declspec(align(16)) Vec4 coeffs[25];
    memset(coeffs, 0, sizeof(coeffs));

    // The original sums the squares on the x87 stack (double precision) before fsqrt and
    // rounds only the root to float; the double arithmetic here reproduces that.
    float root = (float)sqrt((double)x * x + ((double)y * y + (double)z * z) + (double)1e-08f);
    float inv = 1.0f / root;
    x = inv * x;
    y = y * inv;
    z = z * inv;

    if (tex) {
        unsigned int bytes = size * size * 4;
        for (int f = 0; f < 6; ++f) {
            void* pix = operator new(bytes, "Graphics", 0, 0, 0, 0);
            tex->face = (unsigned char)faceMap[f];
            tex->FillSpriteTexture(pix, bytes, 0);
            PrefilterCube(coeffs, size, f, pix, x, y, z, extra);
            if (pix) {
                operator delete[](pix);
            }
        }
    }

    VObj* rr = GetRenderer();
    ((void(__fastcall*)(VObj*, int, int))rr->vtbl[0x58 / 4])(rr, 0, 0xd);
    VObj* mm = GetModelManager();
    VObj* sub = ((VObj*(__fastcall*)(VObj*, int))mm->vtbl[0x20 / 4])(mm, 0);
    ((void(__fastcall*)(VObj*, int, int))sub->vtbl[0x144 / 4])(sub, 0, 0);

    if (dump) {
        EStr dir = ConvertToString8(FUN_00688cf0(-1));
        EStr path;
        StrSprintf(&path, "%s%s.txt", dir.b, name);
        void* f = fopen(path.b, "w");
        if (f) {
            fprintf(f, "\n         Lighting Coefficients\n\n");
            fprintf(f, "(l,m)       RED        GREEN     BLUE\n");
            int running = 0;
            int m0 = 0;
            int l = 0;
            do {
                int l1 = l + 1;
                if (m0 < l1) {
                    const Vec4* row = &coeffs[running];
                    running += l1 - m0;
                    for (int m = m0; m < l1; ++m, ++row) {
                        CoeffRef r0 = { row, 0 };
                        CoeffRef r1 = { row, 1 };
                        CoeffRef r2 = { row, 2 };
                        fprintf(f, "  setc ct_%d%d (%9.6f, %9.6f, %9.6f)\n", l, m + l, r0, r1, r2);
                    }
                }
                m0--;
                l = l1;
            } while (m0 > -5);
            fclose(f);
        }
    }
}
