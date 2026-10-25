// slice s006e6100 -- shader/global-state and vector helper cluster.
// Flags: /O2 /MD /Gy /EHsc /TP (x87 for float math; SSE scalar moves).
#include "types.h"
#include <math.h>

// ===========================================================================
// Stub types.
struct Inner {
    void F2(int, float);            // 0x006f40b0
    void F1(float);                 // 0x006f3f00
    void F3(int, float, int);       // 0x006f4a10
};

class ShaderHost {
public:
    uint32_t pad[0x100];            // 0x400-byte object

    char HandleMessage2(int msg, int extra);                  // 0x006e6810
    void CallF2(int a, float b);                              // 0x006e69a0
    void CallF1(float b);                                     // 0x006e6930
    void CallF3(int a, float b, int c);                       // 0x006e6970
    void SetMode(int mode, int value);                        // 0x006e69e0
    int  ComputeSize(int a, int b, int c);                    // 0x006e6a20
    int  ResetCounter();                                      // 0x006e6b40
    void SetParams(int a, int b, char c1, char c2, char c3);  // 0x006e6b70
    void CallIface(int v);                                    // 0x006e6c20
    bool IsDone();                                            // 0x006e6c60
    void TailVirtual();                                       // 0x006e6c80
    char Write(void* stream);                                 // 0x006e6100
};

// manager returned by FUN_0067dd50 / FUN_0067dd60
struct Manager {
    void* vtbl;
};

extern "C" void* FUN_0067dd50();
extern "C" void* FUN_0067dd60();

extern "C" int  FUN_006dde90(int, int, int, int);
extern "C" void FUN_006ddee0();

typedef int(__thiscall* VirtualFn1)(void*, int);
typedef void(__thiscall* VirtualFn2)(void*, int, int);
typedef void(__thiscall* VirtualFn3)(void*, int, int, int);

extern "C" char FUN_006f4170();

// cRenderInstanceSet::IsRangeEmpty: __thiscall member, `this` in ecx.
struct RenderSet { char FUN_006f4170(); };

// globals (all relocation-masked)
extern uint32_t g_activeColor[4];
extern int   g_colorIsWhite;
extern int   g_softStateDirty;
extern uint32_t g_globalColorBits[4];
extern unsigned int g_samplerDirty[64];
extern unsigned int g_samplerState[1024];
extern float g_fillValue;   // 0x01533c74 (equiv t3)

// ===========================================================================
// Bodies
// ===========================================================================

// @ 0x006e6100  SP::cDirectShader::Write  (serialization)
extern "C" char FUN_00777760(void* self, void* stream);          // 0x00777760
extern "C" char FUN_00777740(const void* name);                  // 0x00777740 -> length
extern "C" void FUN_00777720(const void* name, int n, void* buf);// 0x00777720 -> copy
extern "C" void StreamWrite(void* stream, const void* p, int n);// 0x93a9a0 operator<<
extern "C" void WriteUint32(void* stream, const void* v, int a, int b);  // 0x93aa70
extern "C" void WriteUint16(void* stream, const void* v, int a, int b);  // 0x93a9d0
extern "C" void* eastl_alloc(unsigned int, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  eastl_free(void*);                              // 0xf47380
extern "C" void  FUN_006e5a30(char*, int, char*);                // 0x006e5a30

// cDirectShader retail layout: a 16-slot name table at +0x48 (dword stride)
// paired with 16 0x14-byte records at +0x20c, and two 0xc-byte vectors.
struct ShaderNameSlot {
    const void* pName;         // +0x00
    unsigned int pad[4];
    const void* pName2;        // +0x40 -> this+0x40 within the 0x44 stride? (see body)
};

char ShaderHost::Write(void* stream)
{
    if (!FUN_00777760(this, stream))
        return 0;

    // scratch string buffer (vector<char>): [begin, end, cap]
    char* bufBegin = 0;
    char* bufEnd = 0;
    char* bufCap = 0;

    unsigned char* base = (unsigned char*)this;
    for (int slot = 0; slot < 0x10; ++slot) {
        const void* name = *(const void**)(base + 0x48 + slot * 4);
        if (name == 0)
            continue;

        ShaderNameSlot* rec = (ShaderNameSlot*)(base + 0x20c + slot * 0x14);

        // write slot index
        {
            char idx = (char)slot;
            StreamWrite(stream, &idx, 1);
        }

        // --- first name ---
        int len = FUN_00777740(name);
        if ((int)(bufEnd - bufBegin) < len) {
            char z = 0;
            FUN_006e5a30(bufBegin, len, &z);
            bufEnd = bufBegin + len;
        } else {
            bufEnd = bufBegin + len;
        }
        FUN_00777720(name, len, bufBegin);
        WriteUint32(stream, &len, 1, 0);
        StreamWrite(stream, bufBegin, len);

        // --- second name (rec+0x40) ---
        const void* name2 = *(const void**)((unsigned char*)rec + 0x40);
        int len2 = FUN_00777740(name2);
        if ((int)(bufEnd - bufBegin) < len2) {
            char z = 0;
            FUN_006e5a30(bufBegin, len2, &z);
            bufEnd = bufBegin + len2;
        } else {
            bufEnd = bufBegin + len2;
        }
        FUN_00777720(name2, len2, bufBegin);
        WriteUint32(stream, &len2, 1, 0);
        StreamWrite(stream, bufBegin, len2);

        // --- vector at this+0xc8 (0xc-byte records) ---
        {
            unsigned char* v = (unsigned char*)this;
            unsigned int count = (*(unsigned int*)(v + 0xcc) - *(unsigned int*)(v + 0xc8)) / 0xc;
            WriteUint32(stream, &count, 1, 0);
            const unsigned char* p = *(const unsigned char**)(v + 0xc8);
            for (unsigned int i = 0; i < count; ++i, p += 0xc) {
                unsigned int w0 = *(const unsigned short*)(p + 0);
                unsigned int w1 = *(const unsigned short*)(p + 2);
                unsigned int w2 = *(const unsigned short*)(p + 4);
                unsigned int w3 = *(const unsigned short*)(p + 6);
                unsigned int d4 = *(const unsigned int*)(p + 8);
                WriteUint16(stream, &w0, 1, 0);
                WriteUint16(stream, &w1, 1, 0);
                WriteUint16(stream, &w2, 1, 0);
                WriteUint16(stream, &w3, 1, 0);
                WriteUint32(stream, &d4, 1, 0);
            }
        }

        // --- vector at this+0x208 (0xc-byte records) ---
        {
            unsigned char* v = (unsigned char*)this;
            unsigned int count = (*(unsigned int*)(v + 0x20c) - *(unsigned int*)(v + 0x208)) / 0xc;
            WriteUint32(stream, &count, 1, 0);
            const unsigned char* p = *(const unsigned char**)(v + 0x208);
            for (unsigned int i = 0; i < count; ++i, p += 0xc) {
                unsigned int w0 = *(const unsigned short*)(p + 0);
                unsigned int w1 = *(const unsigned short*)(p + 2);
                unsigned int w2 = *(const unsigned short*)(p + 4);
                unsigned int w3 = *(const unsigned short*)(p + 6);
                unsigned int d4 = *(const unsigned int*)(p + 8);
                WriteUint16(stream, &w0, 1, 0);
                WriteUint16(stream, &w1, 1, 0);
                WriteUint16(stream, &w2, 1, 0);
                WriteUint16(stream, &w3, 1, 0);
                WriteUint32(stream, &d4, 1, 0);
            }
        }
    }

    {
        unsigned char term = 0xff;
        StreamWrite(stream, &term, 1);
    }

    if (bufBegin != 0)
        eastl_free(bufBegin);
    return 1;
}

// @ 0x006e6500
void SetActiveColor(const float* c)
{
    g_activeColor[0] = ((const uint32_t*)c)[0];
    g_activeColor[1] = ((const uint32_t*)c)[1];
    g_activeColor[2] = ((const uint32_t*)c)[2];
    g_activeColor[3] = ((const uint32_t*)c)[3];
    if (1.0f == c[0] && 1.0f == c[1] && 1.0f == c[2] && 1.0f == c[3]) {
        g_colorIsWhite = 1;
    } else {
        g_colorIsWhite = 0;
    }
}

// @ 0x006e6570
void SetGlobalColor(const float* c)
{
    g_softStateDirty |= 0x10;
    g_globalColorBits[0] = *(const uint32_t*)&c[0];
    g_globalColorBits[1] = *(const uint32_t*)&c[1];
    g_globalColorBits[2] = *(const uint32_t*)&c[2];
    g_globalColorBits[3] = *(const uint32_t*)&c[3];
}

// @ 0x006e65a0
void SetSamplerState(int index, int sampler, unsigned int value)
{
    g_samplerDirty[index] |= 1u << (sampler - 1);
    g_samplerState[sampler + index * 14] = value;
}

// @ 0x006e65e0
void __stdcall CallManager3(int a, int b)
{
    Manager* m = (Manager*)FUN_0067dd60();
    VirtualFn3 fn = (VirtualFn3)((void**)m->vtbl)[0x20 / 4];
    fn(m, a, b, 0);
}

// @ 0x006e6600  rw::graphics::EmbeddedState::SetDeviceState
extern "C" void* operator_new_graphics(unsigned int, const char*, int, int, int, int); // 0xf473a0
extern "C" void  operator_delete_graphics(void*);                                       // 0xf47380
extern "C" void  Raster_SetMipLevelData(void*, void*, int);                             // 0x11f0270

void* EmbeddedState_SetDeviceState()
{
    void* mgr = FUN_0067dd60();
    typedef void*(__thiscall* CreateRasterFn)(void*, int, int, int, int, int, int);
    CreateRasterFn create = (CreateRasterFn)(*(void***)mgr)[0x40 / 4];
    void* raster = create(mgr, 0x100, 0x100, 1, 8, 0x15, 0);

    unsigned int* pixels = (unsigned int*)operator_new_graphics(0x40000, "Graphics", 0, 0, 0, 0);

    int rowBase = -0x100;
    unsigned int* dst = pixels;
    for (int rows = 0x100; rows != 0; --rows) {
        for (int col = 0; col < 0x100; ++col) {
            int a = col < 0 ? -col : col;
            int t = rowBase + col;
            int b = t < 0 ? -t : t;
            if (a >= 0x40 && b >= 0x40)
                dst[col] = 0xffffff;
            else if (a >= 0x10 && b >= 0x10)
                dst[col] = 0xffffffff;
            else
                dst[col] = 0xffff0000;
        }
        dst += 0x100;
        rowBase += 1;
    }

    if (((*(unsigned char*)((char*)raster + 4)) & 1) == 0) {
        void* m2 = FUN_0067dd60();
        typedef void(__thiscall* Fn)(void*, void*);
        Fn f = (Fn)(*(void***)m2)[0x34 / 4];
        f(m2, raster);
    }
    Raster_SetMipLevelData(*(void**)raster, pixels, 0);
    operator_delete_graphics(pixels);
    return raster;
}

// @ 0x006e6710
void GetPair(int type, int* out1, int* out2)
{
    switch (type) {
    case 0:
        *out1 = 3; *out2 = 2; break;
    case 2:
        *out1 = 3; *out2 = 6; break;
    case 3:
        *out1 = 3; *out2 = 7; break;
    case 4:
        *out1 = 3; *out2 = 8; break;
    case 5:
        *out1 = 2; *out2 = 0; break;
    case 6:
        *out1 = 2; *out2 = 2; break;
    case 7:
        *out1 = 2; *out2 = 3; break;
    case 8:
        *out1 = 4; *out2 = 2; break;
    default:
        *out1 = 3; *out2 = 2; break;
    }
}

// @ 0x006e6810
char ShaderHost::HandleMessage2(int msg, int)
{
    if (msg == 0x6694879) {
        if (*(char*)((char*)this + 0x354) != 0) {
            Manager* m = (Manager*)FUN_0067dd50();
            VirtualFn2 fn = (VirtualFn2)((void**)m->vtbl)[0x60 / 4];
            fn(m, 0x16, 2);
        }
        return 1;
    }
    return 0;
}

// @ 0x006e6840
void __stdcall GetLayout(int type, unsigned char* out)
{
    switch (type) {
    case 0:
    case 6:
    case 7:
    case 8:
        out[1] = 0x0c; out[2] = 0x10; out[0] = 0; break;
    case 2:
    case 3:
        out[1] = 0x10; out[2] = 0x20; out[3] = 0x24; out[0] = 0; break;
    case 4:
        out[1] = 0x10; out[2] = 0x20; out[3] = 0x2c; out[4] = 0x30; out[0] = 0; break;
    case 5:
        out[1] = 0x0c; out[0] = 0; break;
    case 9:
        out[1] = 0x40; out[0] = 0; break;
    default:
        break;
    }
}

// @ 0x006e68e0
int __stdcall FindKnownValue(int* p)
{
    for (;;) {
        switch (*p) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 0x20:
            return *p;
        default:
            ++p;
            break;
        }
    }
}

// @ 0x006e6930
void ShaderHost::CallF1(float b)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F1(b);
    }
}

// @ 0x006e6970
void ShaderHost::CallF3(int a, float b, int c)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F3(a, b, c);
    }
}

// @ 0x006e69a0
void ShaderHost::CallF2(int a, float b)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F2(a, b);
    }
}

// @ 0x006e69e0
void ShaderHost::SetMode(int mode, int value)
{
    Manager* m = (Manager*)FUN_0067dd50();
    if (mode != 6 && mode != 5) {
        VirtualFn1 fn = (VirtualFn1)((void**)m->vtbl)[0x58 / 4];
        if (fn(m, 0x16) != 0) {
            *(char*)((char*)this + 0x368) = (char)value;
        }
    }
}

// @ 0x006e6a20
int ShaderHost::ComputeSize(int a, int b, int c)
{
    switch (*(int*)((char*)this + 0x164)) {
    case 0:
    case 2:
    case 3:
    case 4: {
        int r = FUN_006dde90(a * 4, b, c, *(int*)((char*)this + 0x368));
        int q = (r + (r >> 31 & 3)) >> 2;
        *(int*)((char*)this + 0x160) = q * 4;
        return q;
    }
    case 5:
    case 6:
    case 7: {
        int r = FUN_006dde90(a, b, c, *(int*)((char*)this + 0x368));
        *(int*)((char*)this + 0x160) = r;
        return r;
    }
    case 8: {
        int r = FUN_006dde90(a * 2, b, c, *(int*)((char*)this + 0x368));
        int q = (r - (r >> 31)) >> 1;
        *(int*)((char*)this + 0x160) = q * 2;
        return q;
    }
    default:
        return 0;
    }
}

// @ 0x006e6b40
int ShaderHost::ResetCounter()
{
    FUN_006ddee0();
    *(int*)((char*)this + 0x160) = 0;
    if (*(int*)((char*)this + 0x164) != 0) {
        *(int*)((char*)this + 0x374) = *(int*)((char*)this + 0x374) + 1;
        return 0;
    }
    *(int*)((char*)this + 0x370) = *(int*)((char*)this + 0x370) + 1;
    return 0;
}

// @ 0x006e6b70
void ShaderHost::SetParams(int a, int b, char c1, char c2, char c3)
{
    *(int*)((char*)this + 0x1f8) = a;
    *(char*)((char*)this + 0x1f4) = 1;
    *(int*)((char*)this + 0x1fc) = b;
    *(int*)((char*)this + 0x200) = 0;
    if (c1 != 0) {
        *(int*)((char*)this + 0x200) = 1;
    }
    if (c2 != 0) {
        *(int*)((char*)this + 0x200) = *(int*)((char*)this + 0x200) | 2;
    }
    if (c3 != 0) {
        *(int*)((char*)this + 0x200) = *(int*)((char*)this + 0x200) | 4;
    }
}

// @ 0x006e6c20
void ShaderHost::CallIface(int v)
{
    Manager* o = *(Manager**)((char*)this + 0x25c);
    VirtualFn3 fn = (VirtualFn3)((void**)o->vtbl)[0xa8 / 4];
    fn(o, 0, v, 0);
}

// @ 0x006e6c60
bool ShaderHost::IsDone()
{
    RenderSet* p = *(RenderSet**)((char*)this + 0x35c);
    if (p != 0) {
        char r = p->FUN_006f4170();
        return r == 0;
    }
    return false;
}

// @ 0x006e6c80
void ShaderHost::TailVirtual()
{
    void* p = *(void**)((char*)this + 0);
    if (p != 0) {
        void* self = (char*)p + 8;
        typedef void(__thiscall* Fn)(void*);
        Fn fn = (Fn)((void**)(*(void**)self))[0xc / 4];
        fn(self);
    }
}

// @ 0x006e6ca0
void SortPairsA(uint32_t* begin, uint32_t* end)
{
    uint32_t* p = begin;
    if (p != end) {
        while ((p = p + 2) != end) {
            uint32_t v1 = *p;
            uint32_t v2 = p[1];
            uint32_t* q = p;
            while (q != begin && q[-2] < v1) {
                *q = q[-2];
                q[1] = q[-1];
                q -= 2;
            }
            *q = v1;
            q[1] = v2;
        }
    }
}

// @ 0x006e6cf0
void SortPairsB(uint32_t* begin, uint32_t* end)
{
    for (uint32_t* p = begin; p != end; p += 2) {
        uint32_t v1 = *p;
        uint32_t v2 = p[1];
        uint32_t* q = p;
        uint32_t prev = q[-2];
        while (prev < v1) {
            *q = q[-2];
            q[1] = q[-1];
            q -= 2;
            prev = *q;
        }
        *q = v1;
        q[1] = v2;
    }
}

// @ 0x006e6d40
struct HeapPair { uint32_t key; uint32_t value; };

void SiftUp(HeapPair* table, int limit, int index, uint32_t key, uint32_t value)
{
    int parent = (index - 1) >> 1;
    while (limit < index && key < table[parent].key) {
        table[index] = table[parent];
        index = parent;
        parent = (index - 1) >> 1;
    }
    table[index].key = key;
    table[index].value = value;
}

// @ 0x006e6d90
void FillSix(float* p)
{
    float v = g_fillValue;
    float nv = -v;
    p[0] = v;
    p[1] = v;
    p[2] = v;
    p[3] = nv;
    p[4] = nv;
    p[5] = nv;
}

// The vc71 <math.h> sqrtf is a double-precision wrapper; the retail module takes the
// root inline with x87 fsqrt, so use a small primitive helper instead.
static double Normalize3_Sqrt(double f)
{
    __asm fld f
    __asm fsqrt
    __asm fstp f
    return f;
}

// @ 0x006e6df0
float* Normalize3(float* out, const float* in)
{
    double sum = (double)in[0] * in[0] + (double)in[1] * in[1] + (double)in[2] * in[2];
    double inv = 1.0 / Normalize3_Sqrt(sum + 1e-08f);
    out[0] = (float)(in[0] * inv);
    out[1] = (float)(inv * in[1]);
    out[2] = (float)(inv * in[2]);
    return out;
}

// @ 0x006e6e30
void MaxVector3(float* out, const float* a, const float* b)
{
    out[0] = (b[0] > a[0]) ? b[0] : a[0];
    out[1] = (b[1] > a[1]) ? b[1] : a[1];
    out[2] = (b[2] > a[2]) ? b[2] : a[2];
}

// @ 0x006e6e90
void AbsArray9(const float* in, float* out)
{
    for (int i = 0; i < 9; ++i) {
        out[i] = fabsf(in[i]);
    }
}

// @ 0x006e6ee0
// Six basis rows are expanded from the 6-float source matrix `m` into a
// 24-float table, then 6 output records (0x10 bytes each) are emitted.
extern "C" char FUN_006ddcc0(int, int, void*, void*);        // 0x006ddcc0
extern "C" void FUN_006ddd40(int, void*, void*);             // 0x006ddd40

void BuildMatrix4x4(float* m, void* a2, int a3, void* a4)
{
    float tab[24];
    tab[0]  = m[0];
    tab[1]  = m[1];
    tab[2]  = m[2];
    tab[3]  = m[3];
    tab[4]  = m[4];
    tab[5]  = m[5];
    tab[6]  = tab[1];
    tab[7]  = tab[2];
    tab[8]  = tab[0];
    tab[9]  = tab[2];
    tab[10] = tab[3];
    tab[11] = tab[4];
    tab[12] = tab[2];
    tab[13] = tab[0];
    tab[14] = tab[1];
    tab[15] = tab[3];
    tab[16] = tab[1];
    tab[17] = tab[5];
    tab[18] = tab[0];
    tab[19] = tab[4];
    tab[20] = tab[5];
    tab[21] = tab[3];
    tab[22] = tab[4];
    tab[23] = tab[5];

    char ok = FUN_006ddcc0(0, 0x18, (void*)&m, tab);
    if (ok != 0) {
        static const int kRows[6] = { 0, 1, 2, 3, 4, 5 };
        float* out = m;
        for (int r = 0; r < 6; ++r) {
            int base = kRows[r] * 3;
            out[0] = tab[base + 0];
            out[1] = tab[base + 1];
            out[2] = tab[base + 2];
            *(int*)(out + 3) = a3;
            out += 4;
        }
        FUN_006ddd40(1, a2, a4);
    }
}

// @ 0x006e7020
void WriteScaledMatrix(float f0, float f1, float f2, float f3, float f4, float f5,
                       float f6, float f7, float f8, float f9, float f10, float f11,
                       float f12, float* out)
{
    // f3 is the uniform scale; out[] is the 16-float matrix.
    out[0]  = f4 * f3;
    out[1]  = f5 * f3;
    out[4]  = f7 * f3;
    out[2]  = f6 * f3;
    out[5]  = f8 * f3;
    out[6]  = f9 * f3;
    out[8]  = f10 * f3;
    out[9]  = f11 * f3;
    out[10] = f12 * f3;
    out[12] = f0;
    out[13] = f1;
    out[14] = f2;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
