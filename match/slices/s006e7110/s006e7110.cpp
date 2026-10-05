// slice s006e7110 -- render/dispatch + bounding-volume helper cluster.
// Flags: /O2 /MD /Gy /EHsc /TP (SSE scalar; some x87 float).
#include "types.h"

struct Inner7c {
    char F7(int, int, int, int, int, int, int);       // 0x0076bc50
    void F12(int, int, int, int, int, int, int, int, // 0x0076ba30
             int, int, int, int);
    void FF(float);                                   // 0x00776450
    void FI(int);                                     // 0x006f4280 / 0x0076cd30
    int  Fp(int, int);                                // 0x... vtable +0x10
    void Fq(int, int, float);                         // vtable +0x18/+0x1c
};

class Host3 {
public:
    uint32_t pad[0x120];

    void Method7110(int);                                    // 0x006e7110
    __declspec(noinline) void Method7270(void*, void*);      // 0x006e7270
    void DispatchList(unsigned char* list, int arg);         // 0x006e73d0
    char Method7450(unsigned char flags);                    // 0x006e7450
    void Method7880(int arg);                                // 0x006e7880
    void Method78b0(void* a, void* b, int c);                // 0x006e78b0
    void Method79b0(int, int, int, int, int, int, int, int,
                    int, int, float, float);                 // 0x006e79b0
    void SetFlag(int index, unsigned char v);                // 0x006e7aa0
    void Method7ac0(void* arg);                              // 0x006e7ac0
    void Method7b50(void* arg);                              // 0x006e7b50
    char Method7c60();                                       // 0x006e7c60
    char Method7c80(int, int, int, int, int, int);           // 0x006e7c80
    void Method7cc0(int, int, int, int);                     // 0x006e7cc0
    void Method7d00(float);                                  // 0x006e7d00
    void Method7d40(int, uint32_t*, float);                 // 0x006e7d40
    void Method7da0();                                       // 0x006e7da0
    void Method7dd0(int, float*, float);                     // 0x006e7dd0
    void Method7ed0(int, uint32_t*, float);                 // 0x006e7ed0
    void Method7f30();                                       // 0x006e7f30
    int  Method7fa0(int index, int value);                   // 0x006e7fa0
    void Method8000(int index, float* v, float w);           // 0x006e8000
    void Method8090(int index, int a, float b);              // 0x006e8090
};

typedef int(__thiscall* VGet)(void*, int, int);
typedef void(__thiscall* VSet)(void*, int, float*, float);
typedef void(__thiscall* VSet2)(void*, int, int, float);

extern "C" char  FUN_007c4fd0();
extern "C" void  FUN_007c3c10();
extern "C" int   FUN_007c4180(void*, void*);
extern "C" void* FUN_0067dd50();
extern "C" void  FUN_007a8550(const wchar_t*);
extern "C" void  FUN_007a85a0(float);
extern "C" void  FUN_007a82a0(int);
extern "C" void  FUN_007a85e0(void*);
extern "C" void  FUN_007a82d0(float);
extern "C" void  FUN_007a91b0(int, int, int);
extern "C" void* FUN_0067dd40();
extern "C" void  FUN_0067ddf0();
extern "C" void* FUN_0067dda0();
extern "C" void* FUN_0067dd70();
extern "C" void* FUN_0067dcc0();
extern "C" char  FUN_007c3cc0();
extern "C" void* operator_new(unsigned int, const char*, int, int, int, int);
extern "C" void  FUN_00776730();
extern "C" void  FUN_00776920();
extern "C" void  FUN_0076c660();
extern "C" void  FUN_007c3f70();
extern "C" void  FUN_0076acd0();
extern "C" void  FUN_007a84d0();
extern "C" int   rw_VertexDescriptor_AreEqual(int, int);
extern int* g_1618d10;

volatile int g_host3Sink;

extern const char g_matName7cc0[];

// ===========================================================================
// Bodies
// ===========================================================================

// @ 0x006e7110  SP::cEffectsModel::DispatchWithAdditionalMaterial (partial)
void Host3::Method7110(int)
{
}

// @ 0x006e7270  SP::cEffectsRenderer::RenderBoundingBoxes (partial)
void Host3::Method7270(void*, void*)
{
    g_host3Sink = 1;
}

// @ 0x006e73d0
void Host3::DispatchList(unsigned char* list, int arg)
{
    if (*list != 0) {
        int i = 0;
        unsigned char* p = list;
        do {
            Method7270(*(void**)(p + 4), (void*)arg);
            ++i;
            p += 4;
        } while (i < (int)(unsigned char)*list);
    }
}

// @ 0x006e7450  (partial skeleton)
char Host3::Method7450(unsigned char)
{
    return 0;
}

// @ 0x006e7880
void Host3::Method7880(int arg)
{
    Inner7c* a = *(Inner7c**)((char*)this + 0x35c);
    if (a != 0) {
        a->FI(arg);
    }
    Inner7c* b = *(Inner7c**)((char*)this + 0x24);
    if (b != 0) {
        b->FI(arg);
    }
}

// @ 0x006e78b0  (partial skeleton)
void Host3::Method78b0(void*, void*, int)
{
}

// @ 0x006e79b0  (partial skeleton)
void Host3::Method79b0(int, int, int, int, int, int, int, int, int, int, float, float)
{
}

// @ 0x006e7aa0
void Host3::SetFlag(int index, unsigned char v)
{
    *(unsigned char*)(*(int*)((char*)this + 0x224) + index * 0xc0) = v;
}

// @ 0x006e7ac0
void Host3::Method7ac0(void* arg)
{
    int* p = (int*)arg;
    p[0x68 / 4] = 0;
    int* list = (int*)p[0x28 / 4];
    int* first = (int*)list[2];
    if (first != (int*)list[3]) {
        int obj = *first;
        if (*(unsigned int*)(obj + 0x18) < *(unsigned int*)((char*)this + 0x15c)) {
            int desc = **(int**)(obj + 0x24);
            int count = (*(int*)((char*)g_1618d10 + 0x30d58) - *(int*)((char*)g_1618d10 + 0x30d54)) >> 2;
            if (count > 0) {
                int i = 0;
                while (rw_VertexDescriptor_AreEqual(desc, *(int*)(*(int*)((char*)g_1618d10 + 0x30d54) + i * 4)) == 0) {
                    ++i;
                    if (count <= i) {
                        return;
                    }
                }
                p[0x68 / 4] = *(int*)(*(int*)((char*)g_1618d10 + 0x30d68) + i * 4);
            }
        }
    }
}

// @ 0x006e7b50  (partial skeleton)
void Host3::Method7b50(void*)
{
}

// @ 0x006e7c60
char Host3::Method7c60()
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        return p->F7(0, 0, 0, 0, 0, 0, 1);
    }
    return 0;
}

// @ 0x006e7c80
char Host3::Method7c80(int a, int b, int c, int d, int e, int f)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        return p->F7(a, b, c, d, e, f, 1);
    }
    return 0;
}

// @ 0x006e7cc0
void Host3::Method7cc0(int a, int b, int c, int d)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        p->F12(a, b, c, d, 0, 0, 0, (int)g_matName7cc0, 0, 0, 0, 0);
    }
}

// @ 0x006e7d00
void Host3::Method7d00(float v)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x360);
    if (p != 0) {
        p->FF(v);
    }
}

// @ 0x006e7d40
void Host3::Method7d40(int index, uint32_t* v, float w)
{
    if (index >= 0) {
        if (index < (*(int*)((char*)this + 0x4c) - *(int*)((char*)this + 0x48)) / 0x70) {
            char* e = (char*)(*(int*)((char*)this + 0x48) + index * 0x70);
            *(uint32_t*)(e + 0x4c) = v[0];
            *(uint32_t*)(e + 0x50) = v[1];
            *(uint32_t*)(e + 0x54) = v[2];
            *(float*)(e + 0x58) = w;
        }
    }
}

// @ 0x006e7da0
void Host3::Method7da0()
{
    int* p = *(int**)((char*)this + 0x28);
    if (p != 0) {
        int n = p[1] - 1;
        p[1] = p[1] - 1;
        if (n == 0) {
            p[1] = 1;
            typedef void(__thiscall* Fn)(void*, int);
            Fn fn = (Fn)((void**)*p)[0];
            fn(p, 1);
        }
    }
}

// @ 0x006e7dd0  (partial skeleton)
void Host3::Method7dd0(int, float*, float)
{
}

// @ 0x006e7ed0
void Host3::Method7ed0(int index, uint32_t* v, float w)
{
    if (index >= 0) {
        if (index < (*(int*)((char*)this + 0x178) - *(int*)((char*)this + 0x174)) / 0x70) {
            char* e = (char*)(*(int*)((char*)this + 0x174) + index * 0x70);
            *(uint32_t*)(e + 0x4c) = v[0];
            *(uint32_t*)(e + 0x50) = v[1];
            *(uint32_t*)(e + 0x54) = v[2];
            *(float*)(e + 0x58) = w;
        }
    }
}

// @ 0x006e7f30  (partial skeleton)
void Host3::Method7f30()
{
}

// @ 0x006e7fa0
int Host3::Method7fa0(int index, int value)
{
    char* e = (char*)(*(int*)((char*)this + 0x1b8) + index * 0x68);
    void* p = *(void**)(e + 0x60);
    if (p != 0) {
        VGet fn = (VGet)((void**)(*(void**)p))[0x10 / 4];
        return fn(p, index, value);
    }
    if (index >= 0) {
        int count = (*(int*)((char*)this + 0x1bc) - *(int*)((char*)this + 0x1b8)) / 0x68;
        if (index < count) {
            *(char*)(e + 0x50) = (char)value;
        }
    }
    return (int)this;
}

// @ 0x006e8000
void Host3::Method8000(int index, float* v, float w)
{
    char* e = (char*)(*(int*)((char*)this + 0x1b8) + index * 0x68);
    void* p = *(void**)(e + 0x60);
    if (p != 0) {
        VSet fn = (VSet)((void**)(*(void**)p))[0x18 / 4];
        fn(p, index, v, w);
        return;
    }
    if (index >= 0) {
        int count = (*(int*)((char*)this + 0x1bc) - *(int*)((char*)this + 0x1b8)) / 0x68;
        if (index < count) {
            *(float*)(e + 4) = v[0];
            *(float*)(e + 8) = v[1];
            *(float*)(e + 0xc) = v[2];
            *(float*)((char*)(*(int*)((char*)this + 0x1b8) + index * 0x68) + 0x10) = w;
        }
    }
}

// @ 0x006e8090
void Host3::Method8090(int index, int a, float b)
{
    void* p = *(void**)(*(int*)((char*)this + 0x1b8) + index * 0x68 + 0x60);
    if (p != 0) {
        VSet2 fn = (VSet2)((void**)(*(void**)p))[0x1c / 4];
        fn(p, index, a, b);
    }
}
