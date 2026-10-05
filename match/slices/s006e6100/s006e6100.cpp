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
    void SetMode(int mode);                                   // 0x006e69e0
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

// globals (all relocation-masked)
extern uint32_t g_activeColor[4];
extern int   g_colorIsWhite;
extern int   g_softStateDirty;
extern uint32_t g_globalColorBits[4];
extern unsigned int g_samplerDirty[64];
extern unsigned int g_samplerState[1024];
extern float g_fillValue;

// ===========================================================================
// Bodies
// ===========================================================================

// @ 0x006e6100  SP::cDirectShader::Write  (partial skeleton)
char ShaderHost::Write(void*)
{
    return 0;
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

// @ 0x006e6600  rw::graphics::EmbeddedState::SetDeviceState  (partial skeleton)
void* EmbeddedState_SetDeviceState()
{
    return 0;
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
void ShaderHost::SetMode(int mode)
{
    Manager* m = (Manager*)FUN_0067dd50();
    if (mode != 6 && mode != 5) {
        VirtualFn1 fn = (VirtualFn1)((void**)m->vtbl)[0x58 / 4];
        if (fn(m, 0x16) != 0) {
            *(char*)((char*)this + 0x368) = (char)mode;
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
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        char r = FUN_006f4170();
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

// @ 0x006e6df0
void Normalize3(float* out, const float* in)
{
    float inv = 1.0f / sqrtf((in[0] * in[0] + in[1] * in[1] + in[2] * in[2]) + 1e-08f);
    out[0] = in[0] * inv;
    out[1] = inv * in[1];
    out[2] = inv * in[2];
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

// @ 0x006e6ee0  (partial skeleton)
void BuildMatrix4x4(void*, int, int, int)
{
}

// @ 0x006e7020  (partial skeleton)
void WriteScaledMatrix(float, float, float, float, float, float, float, float,
                       float, float, float, float, float, float, float*)
{
}
