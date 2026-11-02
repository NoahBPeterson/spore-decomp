// src/game/SPEngine/SPGraphicsFragmentVS.cpp -- migrated from slice(s) s006ff170, s006fe430, s006fd520 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFragmentVS.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char*** g_namesBegin_1628b14;
extern char*** g_namesEnd_1628b18;
extern void*   g_16f6dac;
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// ---- items of slice s006fd520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int g_shaderDataDirty[]; // 0x16f89f8
extern unsigned char g_mgr_1624568[];    // 0x1624568 (pointer stored as bytes)
extern void*  g_shaderFns[];             // 0x16fa604
void* __cdecl FUN_006fcb90(int n, void* first, int b);
struct ShaderRec {
    char pad00[0x10];
    unsigned short field10;   // +0x10
    unsigned short field12;   // +0x12
    unsigned short field14;   // +0x14
    char pad16[2];
    unsigned int   field18;   // +0x18
};
struct ShaderMgr {
    char pad00[0x28];
    int          count;    // +0x28
    ShaderRec**  recs;     // +0x2c
    char pad30[0xac - 0x30];
    void**       objects;  // +0xac
    char padb0[0x12c - 0xb0];
    unsigned int field12c; // +0x12c
};
struct Block130 { unsigned int d[0x4c]; };
struct V1c { char* begin; char* end; };
// ---- items of slice s006fd520 end

// ---- items of slice s006fe430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_eastlAllocator;                            // 0x13ebb38
extern unsigned char g_fragInfoTable;     // 0x1624710, stride 0x44
extern unsigned int  g_15345b0;           // 0x15345b0
extern unsigned char g_15345ac;           // 0x15345ac
extern void*         g_1624568;           // 0x1624568 currently-selected vertex shader
extern void*         g_16f6564;           // 0x16f6564 m_vertexShader
extern unsigned int  g_16f8cf8;           // 0x16f8cf8
extern void*         g_16f89d0;           // 0x16f89d0 d3d9 device
extern int* g_v1_begin;   // 0x1628b14
extern int* g_v1_end;     // 0x1628b18
extern int* g_v1_cap;     // 0x1628b1c
extern int* g_v2_begin;   // 0x16246fc
extern int* g_v2_end;     // 0x1624700
extern int* g_v2_cap;     // 0x1624704
extern char* g_vs_begin;  // 0x1628c20
extern char* g_vs_end;    // 0x1628c24
void* __cdecl FUN_011e073e(void* p, int a, unsigned size);   // operator_new[]
void* __cdecl FUN_011e0744(void* a, void* b, unsigned c);    // vector DoInsertValue
void  __cdecl FUN_00928dc0();
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl EASTL_allocator_allocate(unsigned size, const char* area, int a, int b,
                                       void* allocator, int line);   // 0x00f473a0
char* __cdecl FUN_006fe2d0(char* first, char* last, char* dst);   // 0x006fe2d0 copy
void  __cdecl FUN_006faa30(char* dst, unsigned n, void* value);   // 0x006faa30 fill_n
void  __cdecl FUN_006fa800(void* out, char* first, char* last, char* dst, unsigned n);  // 0x006fa800
void  __cdecl FUN_006fe310(char* first, char* src, char* last);   // 0x006fe310 move forward
void  __cdecl FUN_006fa7d0(char* first, char* last, void* value); // 0x006fa7d0 fill
void __cdecl EA_WriteUint32(void* stream, const void* p, int n, int flag);
void __cdecl EA_WriteUint16(void* stream, const void* p, int n, int flag);   // 0x0093a9d0 (equiv t2)
void __cdecl EA_operator_shl(void* stream, const void* p, int n);   // 0x0093a9a0 (equiv t3)
void __cdecl FUN_0093adb0(void* stream, const void* p, unsigned n, int flag);
bool  __cdecl FUN_006fe350(void* e);
void  __cdecl FUN_006fe3c0(int a, int b);
struct FragElem {              // 0x1c
    const char*      sBegin;   // +0x00
    const char*      sEnd;     // +0x04
    char             pad08[8];
    unsigned short   w10;      // +0x10
    unsigned short   w12;      // +0x12
    unsigned short   w14;      // +0x14
    unsigned short   w16;      // +0x16
    unsigned int     d18;      // +0x18
};
struct FragInfo {              // 0x44
    int              f00;      // +0x00
    const char*      nameBegin;// +0x04
    const char*      nameEnd;  // +0x08
    const char*      nameCap;  // +0x0c
    char             pad10[4];
    const char*      uniBegin; // +0x14
    const char*      uniEnd;   // +0x18
    const char*      uniCap;   // +0x1c
    char             pad20[4];
    FragElem*        vecBegin; // +0x24
    FragElem*        vecEnd;   // +0x28
    FragElem*        vecCap;   // +0x2c
    char             pad30[8];
    int              f38;      // +0x38
    int              f3c;      // +0x3c
    unsigned char    b40;      // +0x40
    unsigned char    b41;      // +0x41
    unsigned char    b42;      // +0x42
};
struct Vec4 {                  // 4-byte-element vector with out-of-line grow
    void* begin;
    void* end;
    void* cap;
    void Grow(void* pos, const void* value);
};
struct Vec130 {                // 0x130-byte-element vector
    char* begin;   // +0x00
    char* end;     // +0x04
    char* cap;     // +0x08
    __declspec(noinline) void Insert(char* pos, unsigned n, void* value);  // 0x6fe600 (not byte-exact)
    void Destroy(char* first, char* last);            // 0x6fae30
    void Reserve(unsigned n);                         // 0x6faae0
    void Resize(unsigned n);                          // 0x6ff060
    int Size() const { return (int)(end - begin) / 0x130; }
};
namespace {

struct EString {
    char* begin;   // +0x00
    char* end;     // +0x04
    char* cap;     // +0x08
    void assign(const char* first, const char* last);
};
struct VecStub24 {
    char pad[0x14];
    void CopyFrom(void* src);
};
struct cVertexFragmentInfo {
    int f00;                    // +0x00
    EString name;               // +0x04
    char pad10[4];
    EString uni;                // +0x14
    char pad20[4];
    VecStub24 vec;              // +0x24
    int f38;                    // +0x38
    int f3c;                    // +0x3c
    unsigned char b40;          // +0x40
    unsigned char b41;          // +0x41
    unsigned char b42;          // +0x42
    cVertexFragmentInfo& operator=(const cVertexFragmentInfo& o);
};

} // namespace
int  __cdecl BinaryFindPixelShader(const char* key, const void* begin, unsigned count); // 0x006fdab0
void __cdecl PixelFrag_PushBack();                                                    // 0x006fb0e0
// ---- items of slice s006fe430 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_006fe8f0(int a, int b);  // 0x006fe8f0 (stays in the slice: not this object's)

// callees this slice defines outside this object (rewrite.py held_callee_protos)
__declspec(noinline) char* __cdecl SP_TextCopy(char* d, const char* s);  // 0x006fd9a0 (stays in the slice: not this object's)

// ---- items of slice s006ff170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_0047d240();                               // 0x0047d240 thiscall(void*, int) string set-capacity
extern "C" void FUN_006fc540();                               // 0x006fc540 thiscall(void*, unsigned) vector set-capacity
extern char g_vertexFragTable;     // 0x1624710, 256 SP::cVertexFragmentInfo records of 0x44
extern unsigned   g_15345b0;       // 0x15345b0 record-count high-water mark
int __cdecl FUN_0093a9a0(void* io, const void* p, int n);        // 0x0093a9a0 write block
int __cdecl FUN_0093aa70(void* io, const void* p, int n, int f); // 0x0093aa70 write uint32
int __cdecl FUN_0093a9d0(void* io, const void* p, int n, int f); // 0x0093a9d0 write uint16
int __cdecl FUN_0093a6c0(void* io, void* p, int n);              // 0x0093a6c0 read block
int __cdecl FUN_0093a780(void* io, void* p, int n, int f);       // 0x0093a780 read uint32
int __cdecl FUN_0093a700(void* io, void* p, int n, int f);       // 0x0093a700 read uint16
void __cdecl FUN_006ff060(void* vec, unsigned n);   // 0x006ff060 Vec130::Resize
void __cdecl FUN_004c10e0();                        // 0x004c10e0 vector<u8>::DoInsertValues
void __cdecl FUN_00f47380(void* p);                       // 0x00f47380 operator delete[]
struct FragElem_s006f_f170 {                   // 0x1c
    char*    mpBegin;               // +0x00
    char*    mpEnd;                 // +0x04
    char*    mpCap;                 // +0x08
    unsigned mField0C;              // +0x0c
    unsigned short mField10;        // +0x10
    unsigned short mField12;        // +0x12
    unsigned short mField14;        // +0x14
    unsigned short mField16;        // +0x16
    unsigned mField18;              // +0x18
};
struct VsRecord {                   // 0x130
    unsigned char mBlob[0x20];      // +0x00 opaque 0x20-byte block
    void*         mpShader;         // +0x20 vertex-shader object (0x777720 / 0x777740)
    unsigned      mField24;         // +0x24
    int           mCount;           // +0x28
    FragElem_s006f_f170*     mpElems[0x20];    // +0x2c
    unsigned      mFieldAC[0x20];   // +0xac
    int           mField12C;        // +0x12c
};
struct StackAllocator {
    unsigned  mnDefaultBlockSize;   // +0x00
    void*     mpCurrentBlock;       // +0x04
    char*     mpCurrentBlockEnd;    // +0x08
    char*     mpCurrentObjectBegin; // +0x0c
    char*     mpCurrentObjectEnd;   // +0x10
    bool AllocateNewBlock(unsigned size);   // 0x00928ba0
    // Bump-allocate `n` bytes out of the current block, growing the chain if it does not fit.
    __forceinline void* Allocate(unsigned n) {
        n = (n + 7) & ~7u;
        if (mpCurrentBlockEnd - mpCurrentObjectBegin - (int)n < 0) {
            if (!AllocateNewBlock(n)) return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + n;
        mpCurrentObjectEnd = p + n;
        return p;
    }
};
extern StackAllocator g_fragAllocator;      // 0x1628b98
struct VecU8 {
    unsigned char* mpBegin;         // +0x00
    unsigned char* mpEnd;           // +0x04
    unsigned char* mpCap;           // +0x08
    unsigned char* erase(unsigned char* first, unsigned char* last) {
        memcpy(first, last, (unsigned)(mpEnd - last));
        mpEnd -= last - first;
        return first;
    }
    void resize(unsigned n) {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        if (n <= size) {
            erase(mpBegin + n, mpEnd);
        } else {
            unsigned char v = 0;
            ((void(__thiscall*)(void*, unsigned char*, unsigned, const void*))FUN_004c10e0)
                (this, mpEnd, (unsigned)(mpBegin - mpEnd) + n, &v);
        }
    }
    ~VecU8() {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            FUN_00f47380(mpBegin);
    }
};
struct IO {
    int Put(unsigned short v) { return FUN_0093a9d0(this, &v, 1, 0); }
    int Put(unsigned v)       { return FUN_0093aa70(this, &v, 1, 0); }
    int Put(const unsigned* p, int n) { return FUN_0093aa70(this, p, n, 0); }
    int Write(const void* p, int n)   { return FUN_0093a9a0(this, p, n); }
};
namespace {
struct EString_s006f_f170 {                    // 0x0c
    char* begin;                    // +0x00
    char* end;                      // +0x04
    char* cap;                      // +0x08
    EString_s006f_f170() : begin((char*)0x01667bac), end((char*)0x01667bac), cap((char*)0x01667bad) {}
};
struct CFragVec {                   // 0x14
    void* mpBegin;                  // +0x00
    void* mpEnd;                    // +0x04
    void* mpCap;                    // +0x08
    void* mField0C;                 // +0x0c
    void* mField10;                 // +0x10
    CFragVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
};
struct cVertexFragmentInfo_s006f_f170 {        // 0x44
    int           f00;              // +0x00
    EString_s006f_f170       name;             // +0x04
    int           pad10;            // +0x10 (left uninitialised, as in retail)
    EString_s006f_f170       uni;              // +0x14
    int           pad20;            // +0x20 (left uninitialised, as in retail)
    CFragVec      vec;              // +0x24
    int           f38;              // +0x38
    int           f3c;              // +0x3c
    unsigned char b40;              // +0x40
    unsigned char b41;              // +0x41
    unsigned char b42;              // +0x42
    cVertexFragmentInfo_s006f_f170() : f00(0), f38(0), f3c(0), b40(0), b41(0), b42(0) {}
    // Real member functions defined in another TU: C++ linkage, so cl must assume they may
    // throw and therefore emits the retail __ehhandler frame around the temporary.
    cVertexFragmentInfo_s006f_f170& operator=(const cVertexFragmentInfo_s006f_f170& o);   // 0x006ff100
    ~cVertexFragmentInfo_s006f_f170();                                         // 0x006fe830
};
} // namespace
// ---- items of slice s006ff170 end

// @ 0x006fdb90
void __cdecl GenerateInputStruct(char* d, unsigned flags)
{
    d = SP_TextCopy(d, "\nstruct cVertIn\n{\n");
    if ((flags & 3) != 0)
        d = SP_TextCopy(d, "float4 position : POSITION0;\n");
    if ((flags & 4) != 0)
        d = SP_TextCopy(d, "float4 normal : NORMAL0;\n");
    if ((flags & 0x18) != 0)
        d = SP_TextCopy(d, "float4 color : COLOR0;\n");
    for (unsigned i = 0; i < 8; i++) {
        if ((flags & (1u << (i + 6))) != 0) {
            d += sprintf(d, "float4 texcoord%d : TEXCOORD%d;\n", i, i);
        }
    }
    if ((flags & 0x4000) != 0)
        d = SP_TextCopy(d, "int4 indices : BLENDINDICES0;\n");
    if ((flags & 0x8000) != 0)
        d = SP_TextCopy(d, "float4 weights : BLENDWEIGHT0;\n");
    if ((flags & 0x20000) != 0)
        d = SP_TextCopy(d, "float4 position2 : POSITION1;\n");
    if ((flags & 0x40000) != 0)
        d = SP_TextCopy(d, "float4 normal2 : NORMAL1;\n");
    if ((flags & 0x400000) != 0)
        d = SP_TextCopy(d, "int4 indices2 : BLENDINDICES1;\n");
    if ((flags & 0x800000) != 0)
        d = SP_TextCopy(d, "float4 weights2 : BLENDWEIGHT1;\n");
    if ((flags & 0x80000) != 0)
        d = SP_TextCopy(d, "float4 tangent : TANGENT0;\n");
    if ((flags & 0x100000) != 0)
        d = SP_TextCopy(d, "float4 binormal : BINORMAL0;\n");
    if ((flags & 0x20) != 0)
        d = SP_TextCopy(d, "float4 color1 : COLOR1;\n");
    if ((flags & 0x200000) != 0)
        d = SP_TextCopy(d, "float fog : FOG;\n");
    if ((flags & 0x10000) != 0)
        d = SP_TextCopy(d, "float pointSize : PSIZE;\n");
    SP_TextCopy(d, "};\n\n");
}

// @ 0x006fdd50
void __cdecl GenerateCurrentStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes)
{
    d = SP_TextCopy(d, "struct cVertCurrent\n{\n");
    d = SP_TextCopy(d, "float4 position;\n");
    if ((flags & 4) != 0)
        d = SP_TextCopy(d, "float4 normal;\n");
    if ((flags & 0x18) != 0)
        d = SP_TextCopy(d, "float4 color;\n");
    for (unsigned i = 0; i < ntex; i++) {
        d += sprintf(d, "float%d texcoord%d;\n", sizes[i], i);
    }
    if ((flags & 0x4000) != 0)
        d = SP_TextCopy(d, "int4 indices;\n");
    if ((flags & 0x8000) != 0)
        d = SP_TextCopy(d, "float4 weights;\n");
    if ((flags & 0x20000) != 0)
        d = SP_TextCopy(d, "float4 position2;\n");
    if ((flags & 0x40000) != 0)
        d = SP_TextCopy(d, "float4 normal2;\n");
    if ((flags & 0x400000) != 0)
        d = SP_TextCopy(d, "int4 indices2;\n");
    if ((flags & 0x800000) != 0)
        d = SP_TextCopy(d, "float4 weights2;\n");
    if ((flags & 0x80000) != 0)
        d = SP_TextCopy(d, "float4 tangent;\n");
    if ((flags & 0x100000) != 0)
        d = SP_TextCopy(d, "float4 binormal;\n");
    if ((flags & 0x20) != 0)
        d = SP_TextCopy(d, "float4 color1;\n");
    if ((flags & 0x200000) != 0)
        d = SP_TextCopy(d, "float fog;\n");
    if ((flags & 0x10000) != 0)
        d = SP_TextCopy(d, "float pointSize;\n");
    SP_TextCopy(d, "};\n\n");
}

// @ 0x006fdef0
void __cdecl GenerateOutputStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes)
{
    d = SP_TextCopy(d, "struct cVertOut\n{\n");
    d = SP_TextCopy(d, "float4 position : POSITION;\n");
    if ((flags & 0x18) != 0)
        d = SP_TextCopy(d, "float4 diffuse : COLOR0;\n");
    for (unsigned i = 0; i < ntex; i++) {
        d += sprintf(d, "float%d texcoord%d : TEXCOORD%d;\n", sizes[i], i, i);
    }
    if ((flags & 0x20) != 0)
        d = SP_TextCopy(d, "float4 color1 : COLOR1;\n");
    if ((flags & 0x200000) != 0)
        d = SP_TextCopy(d, "float fog : FOG;\n");
    if ((flags & 0x10000) != 0)
        d = SP_TextCopy(d, "float pointSize : PSIZE;\n");
    SP_TextCopy(d, "};\n\n");
}

// @ 0x006fdfc0
char* __cdecl GenerateFillCurrentStruct(char* d, unsigned flags, int ntex)
{
    if ((flags & 3) != 0)
        d = SP_TextCopy(d, "Current.position = In.position;\n");
    if ((flags & 4) != 0)
        d = SP_TextCopy(d, "Current.normal = In.normal;\n");
    if ((flags & 0x18) != 0)
        d = SP_TextCopy(d, "Current.color = In.color;\n");
    for (int i = 0; i < ntex; i++) {
        if ((flags & (1u << (i + 6))) == 0)
            break;
        d += sprintf(d, "Current.texcoord%d = In.texcoord%d;\n", i, i);
    }
    if ((flags & 0x4000) != 0)
        d = SP_TextCopy(d, "Current.indices = In.indices;\n");
    if ((flags & 0x8000) != 0)
        d = SP_TextCopy(d, "Current.weights = In.weights;\n");
    if ((flags & 0x20000) != 0)
        d = SP_TextCopy(d, "Current.position2 = In.position2;\n");
    if ((flags & 0x40000) != 0)
        d = SP_TextCopy(d, "Current.normal2 = In.normal2;\n");
    if ((flags & 0x400000) != 0)
        d = SP_TextCopy(d, "Current.indices2 = In.indices2;\n");
    if ((flags & 0x800000) != 0)
        d = SP_TextCopy(d, "Current.weights2 = In.weights2;\n");
    if ((flags & 0x80000) != 0)
        d = SP_TextCopy(d, "Current.tangent = In.tangent;\n");
    if ((flags & 0x100000) != 0)
        d = SP_TextCopy(d, "Current.binormal = In.binormal;\n");
    if ((flags & 0x20) != 0)
        d = SP_TextCopy(d, "Current.color1 = In.color1;\n");
    if ((flags & 0x200000) != 0)
        d = SP_TextCopy(d, "Current.fog = In.fog;\n");
    if ((flags & 0x10000) != 0)
        d = SP_TextCopy(d, "Current.pointSize = In.pointSize;\n");
    return d;
}

// @ 0x006fe170
char* __cdecl GenerateFillOutputStruct(char* d, unsigned flags, unsigned ntex)
{
    d = SP_TextCopy(d, "\n");
    d = SP_TextCopy(d, "Out.position = Current.position;\n");
    if ((flags & 0x18) != 0)
        d = SP_TextCopy(d, "Out.diffuse = Current.color;\n");
    for (unsigned i = 0; i < ntex; i++) {
        d += sprintf(d, "Out.texcoord%d = Current.texcoord%d;\n", i, i);
    }
    if ((flags & 0x20) != 0)
        d = SP_TextCopy(d, "Out.color1 = Current.color1;\n");
    if ((flags & 0x200000) != 0)
        d = SP_TextCopy(d, "Out.fog = Current.fog;\n");
    if ((flags & 0x10000) != 0)
        d = SP_TextCopy(d, "Out.pointSize = Current.pointSize;\n");
    return d;
}

// @ 0x006fe230
void __cdecl FUN_006fe230(unsigned mask, char flag)
{
    ShaderMgr* m = (ShaderMgr*)g_mgr_1624568;
    if (flag)
        mask |= m->field12c;
    if ((m->field12c & mask) == 0)
        return;
    if (m->count <= 0)
        return;
    for (int i = 0; i < m->count; i++) {
        ShaderRec* s = m->recs[i];
        unsigned int x = s->field18 & mask;
        if (x == 0)
            continue;
        if (x == 8 && flag == 0 &&
            (g_shaderDataDirty[s->field12 >> 5] & (1u << (s->field12 & 0x1f))) == 0)
            continue;
        void* fn = g_shaderFns[(unsigned)s->field10 * 8];
        ((void(__cdecl*)(void*, unsigned short, int))fn)(m->objects[i], s->field14, 1);
    }
}

// @ 0x006fe310
Block130* __cdecl FUN_006fe310(Block130* first, Block130* last, Block130* dest)
{
    while (last != first) {
        --last;
        --dest;
        *dest = *last;
    }
    return dest;
}

// @ 0x006fe350
bool __cdecl FUN_006fe350(void* name)
{
    char*** begin = g_namesBegin_1628b14;
    int n = (int)(g_namesEnd_1628b18 - begin);
    for (int i = 0; i < n; i++) {
        if (strcmp(begin[i][0], *(char**)name) == 0)
            return true;
    }
    return false;
}

// @ 0x006fe3c0
void __cdecl FUN_006fe3c0(int a, int b)
{
    int idx = 0;
    int g = (int)(size_t)g_16f6dac;
    if (g != 0) {
        idx = *(int*)(g + 4);
        V1c* v = (V1c*)(a + 0x48 + idx * 0x14);
        if (v->begin == v->end)
            idx = 0;
    }
    V1c* v = (V1c*)(a + 0x48 + idx * 0x14);
    int first = (int)v->begin;
    int n = ((int)v->end - first) / 0x1c;
    char* r = (char*)FUN_006fcb90(n, (void*)first, b);
    r[b] = 0;
}

// @ 0x006fe430
void __cdecl FUN_006fe430(void* stream)
{
    unsigned char* p = (unsigned char*)0x0162477C;
    do {
        int v = *(int*)(p + 0x10);
        EA_WriteUint32(stream, &v, 1, 0);
        v = *(int*)(p + 0x14);
        EA_WriteUint32(stream, &v, 1, 0);
        unsigned char c = *(unsigned char*)(p + 0x19);
        EA_operator_shl(stream, &c, 1);
        c = *(unsigned char*)(p + 0x1a);
        EA_operator_shl(stream, &c, 1);
        c = *(unsigned char*)(p + 0x18);
        EA_operator_shl(stream, &c, 1);
        v = *(int*)(p - 0x28);
        EA_WriteUint32(stream, &v, 1, 0);
        FUN_0093adb0(stream, *(void**)(p - 0x24),
                     *(int*)(p - 0x20) - *(int*)(p - 0x24), 0);
        FUN_0093adb0(stream, *(void**)(p - 0x14),
                     *(int*)(p - 0x10) - *(int*)(p - 0x14), 0);
        v = (*(int*)(p) - *(int*)(p - 4)) / 0x1c;
        EA_WriteUint32(stream, &v, 1, 0);
        v = (*(int*)(p) - *(int*)(p - 4)) / 0x1c;
        if (v > 0) {
            int off = 0;
            do {
                unsigned char* e = (unsigned char*)(*(int*)(p - 4) + off);
                FUN_0093adb0(stream, *(void**)e, *(int*)(e + 4) - *(int*)e, 0);
                unsigned short u = *(unsigned short*)(e + 0x10);
                EA_WriteUint16(stream, &u, 1, 0);
                u = *(unsigned short*)(e + 0x12);
                EA_WriteUint16(stream, &u, 1, 0);
                u = *(unsigned short*)(e + 0x14);
                EA_WriteUint16(stream, &u, 1, 0);
                u = *(unsigned short*)(e + 0x16);
                EA_WriteUint16(stream, &u, 1, 0);
                unsigned int d = *(unsigned int*)(e + 0x18);
                EA_WriteUint32(stream, &d, 1, 0);
                off += 0x1c;
            } while (--v);
        }
        p += 0x44;
    } while ((int)p < 0x1628B38);
}

// @ 0x006fe600
__declspec(noinline) void Vec130::Insert(char* pos, unsigned n, void* value)
{
    if (n > (unsigned)((cap - end) / 0x130)) {
        unsigned count = (unsigned)((end - begin) / 0x130);
        unsigned newCap = count != 0 ? count * 2 : 1;
        unsigned total = count + n;
        if (newCap > total)
            total = newCap;
        char* p = 0;
        if (total != 0)
            p = (char*)EASTL_allocator_allocate(total * 0x130, "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
        char* mid = FUN_006fe2d0(begin, pos, p);
        FUN_006faa30(mid, n, value);
        char* newEnd = FUN_006fe2d0(pos, end, mid + n * 0x130);
        char* old = begin;
        if (old != 0 && ((int*)old)[-1] != 0)
            EASTL_allocator_deallocate(old);
        begin = p;
        end = newEnd;
        cap = p + total * 0x130;
    } else if (n != 0) {
        char temp[0x130];
        memcpy(temp, value, 0x130);
        char* oldEnd = end;
        unsigned count = (unsigned)((oldEnd - pos) / 0x130);
        if (n < count) {
            char* dst = oldEnd - n * 0x130;
            char* scratch;
            FUN_006fa800(&scratch, dst, oldEnd, oldEnd, (unsigned)dst);
            end = oldEnd + n * 0x130;
            FUN_006fe310(pos, dst, oldEnd);
            FUN_006fa7d0(pos, pos + n * 0x130, temp);
        } else {
            unsigned extra = n - count;
            FUN_006faa30(oldEnd, extra, temp);
            end = oldEnd + extra * 0x130;
            char* scratch;
            FUN_006fa800(&scratch, pos, oldEnd, end, extra);
            end += count * 0x130;
            FUN_006fa7d0(pos, oldEnd, temp);
        }
    }
}

// @ 0x006fe7f0
void* __fastcall FUN_006fe7f0(char* p)
{
    *(int*)(p + 0x00) = 0;
    *(void**)(p + 0x0c) = (void*)0x01667BAD;
    *(void**)(p + 0x04) = (void*)0x01667BAC;
    *(void**)(p + 0x08) = (void*)0x01667BAC;
    *(void**)(p + 0x14) = (void*)0x01667BAC;
    *(void**)(p + 0x18) = (void*)0x01667BAC;
    *(void**)(p + 0x1c) = (void*)0x01667BAD;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x38) = 0;
    *(int*)(p + 0x3c) = 0;
    *(unsigned char*)(p + 0x40) = 0;
    *(unsigned char*)(p + 0x41) = 0;
    *(unsigned char*)(p + 0x42) = 0;
    return p;
}

// @ 0x006fe830
void __fastcall FUN_006fe830(char* p)
{
    void* a = *(void**)(p + 0x24);
    void* b = *(void**)(p + 0x28);
    ((Vec130*)(p + 0x24))->Destroy((char*)a, (char*)b);
    void* q = *(void**)(p + 0x24);
    if (q && ((int*)q)[-1]) EASTL_allocator_deallocate(q);
    q = *(void**)(p + 0x14);
    if ((int)(*(int*)(p + 0x1c) - (int)q) > 1 && q) EASTL_allocator_deallocate(q);
    q = *(void**)(p + 0x04);
    if ((int)(*(int*)(p + 0x0c) - (int)q) > 1 && q) EASTL_allocator_deallocate(q);
}

// @ 0x006fe890
void __cdecl FUN_006fe890()
{
    int* b1 = g_v1_begin;
    int* e1 = g_v1_end;
    FUN_011e0744(b1, e1, 0);
    g_v1_end = (int*)g_v1_end - (e1 - b1);
    int* b2 = g_v2_begin;
    int* e2 = g_v2_end;
    FUN_011e0744(b2, e2, 0);
    g_v2_end = (int*)g_v2_end - (e2 - b2);
}

// @ 0x006fe8f0
void __cdecl FUN_006fe8f0(int a, int b)
{
    if (g_v1_end < g_v1_cap) {
        int* pos = g_v1_end;
        g_v1_end = g_v1_end + 1;
        if (pos)
            *pos = a;
    } else {
        ((Vec4*)&g_v1_begin)->Grow(g_v1_end, &a);
    }
    if (g_v2_end < g_v2_cap) {
        int* pos = g_v2_end;
        g_v2_end = g_v2_end + 1;
        if (pos)
            *pos = b;
    } else {
        ((Vec4*)&g_v2_begin)->Grow(g_v2_end, &b);
    }
}

// @ 0x006fe960
char* AddFragmentDeclarations(char* buf, int idx, int* reg)
{
    FragInfo* fi = (FragInfo*)((char*)&g_fragInfoTable + idx * 0x44);
    if (fi->vecBegin != fi->vecEnd) {
        int count = (int)((char*)fi->vecEnd - (char*)fi->vecBegin) / 0x1c;
        if (count > 0) {
            int off = 0;
            do {
                FragElem* e = (FragElem*)((char*)fi->vecBegin + off);
                if (!FUN_006fe350(e)) {
                    FUN_006fe8f0((int)e, *reg);
                    buf += sprintf(buf, "extern uniform %s : register(c%d);\n", e->sBegin, *reg);
                    *reg += e->w14;
                }
                off += 0x1c;
            } while (--count);
        }
    }
    if (fi->uniBegin != fi->uniEnd)
        buf += sprintf(buf, "\n%s\n\n", fi->uniBegin);
    return buf;
}

// @ 0x006fea30
void __cdecl FUN_006fea30(int a1, int a2)
{
    (void)a1; (void)a2;
}

// @ 0x006fec40
__declspec(noinline) int __cdecl FUN_006fec40(void* a1, void* a2)
{
    const char* key = (const char*)a2;
    int count = (int)((g_vs_end - g_vs_begin) / 0x130);
    int idx = BinaryFindPixelShader(key, (const void*)g_vs_begin, (unsigned)count);
    if (idx < 0) {
        if (g_15345b0 != 0 && (int)g_15345b0 <= count) {
            int victim = 0;
            for (int i = 1; i < count; i++) {
                if (*(unsigned*)(g_vs_begin + i * 0x130 + 0x24) <
                    *(unsigned*)(g_vs_begin + victim * 0x130 + 0x24))
                    victim = i;
            }
            char* slot = g_vs_begin + victim * 0x130;
            void* obj = *(void**)(slot + 0x20);
            if (obj != 0) {
                ((void(__stdcall*)(void*))(*(void***)obj)[2])(obj);
                *(void**)(slot + 0x20) = 0;
            }
            memmove(slot, slot + 0x130, (size_t)((count - victim - 1) * 0x130));
            g_vs_end -= 0x130;
            count = (int)((g_vs_end - g_vs_begin) / 0x130);
            idx = BinaryFindPixelShader(key, (const void*)g_vs_begin, (unsigned)count);
        }
        idx = -1 - idx;
        PixelFrag_PushBack();
        if (idx < count)
            memmove(g_vs_begin + idx * 0x130 + 0x130, g_vs_begin + idx * 0x130,
                    (size_t)((count - idx) * 0x130));
        g_1624568 = g_vs_begin + idx * 0x130;
        FUN_011e073e(g_1624568, 0, 0x130);
        if (g_15345ac != 0)
            FUN_006fea30((int)a1, (int)a2);
        char* rec = (char*)g_1624568;
        *(unsigned*)(rec + 0x24) = g_16f8cf8;
        memcpy(rec, a2, 0x20);
        int n1 = (int)(g_v1_end - g_v1_begin);
        *(unsigned*)(rec + 0x28) = (unsigned)n1;
        FUN_011e0744(rec + 0x2c, g_v1_begin, (unsigned)(n1 * 4));
        FUN_011e0744(rec + 0xac, g_v2_begin, (unsigned)((int)(g_v2_end - g_v2_begin) * 4));
        for (int i = 0; i < *(int*)(rec + 0x28); i++)
            *(unsigned*)(rec + 0x12c) |= *(unsigned*)(*(int*)(rec + 0x2c + i * 4) + 0x18);
        return *(int*)(rec + 0x20);
    }
    g_1624568 = g_vs_begin + idx * 0x130;
    char* rec = (char*)g_1624568;
    *(unsigned*)(rec + 0x24) = g_16f8cf8;
    return *(int*)(rec + 0x20);
}

// @ 0x006feee0
bool __cdecl FUN_006feee0(void* a1, const char* name)
{
    const char* nm = name;
    void* cur = g_1624568;
    int shader;
    if (cur != 0 && strcmp((const char*)cur, nm) == 0) {
        *(unsigned int*)((char*)cur + 0x24) = g_16f8cf8;
        shader = *(int*)((char*)g_1624568 + 0x20);
    } else {
        shader = FUN_006fec40(a1, (void*)nm);
    }
    bool changed = (g_16f6564 != (void*)shader);
    if (changed) {
        void* dev = g_16f89d0;
        void* fn = (*(void***)dev)[0x170 / 4];
        ((void(__stdcall*)(void*, void*))fn)(dev, (void*)shader);
        g_16f6564 = (void*)shader;
    }
    return changed;
}

// @ 0x006fef70
void __cdecl FUN_006fef70(int a)
{
    char buf[32];
    FUN_006fe3c0(a, (int)buf);
    FUN_006feee0((void*)a, buf);
}

// @ 0x006fefa0
void __cdecl FUN_006fefa0()
{
    ((Vec130*)0x01628C20)->Destroy(g_vs_begin, g_vs_end);
    unsigned int n = g_15345b0;
    if (n == 0)
        n = 0x200;
    ((Vec130*)0x01628C20)->Reserve(n);
    g_1624568 = 0;
}

// @ 0x006fefe0
void __cdecl FUN_006fefe0()
{
    int count = (int)(g_vs_end - g_vs_begin) / 0x130;
    if (count > 0) {
        int off = 0;
        do {
            void** slot = (void**)(g_vs_begin + off + 0x20);
            void* obj = *slot;
            if (obj) {
                void* fn = (*(void***)obj)[2];
                ((void(__stdcall*)(void*))fn)(obj);
                *slot = 0;
                g_vs_begin = *(char**)0x01628C20;
            }
            off += 0x130;
        } while (--count);
    }
    ((Vec130*)0x01628C20)->Destroy(g_vs_begin, g_vs_end);
    FUN_00928dc0();
}

// @ 0x006ff060
void Vec130::Resize(unsigned n)
{
    if ((unsigned)Size() < n) {
        char temp[0x130];
        FUN_011e073e(temp, 0, 0x130);
        // out-of-line call: keeping the member pointer volatile stops cl from
        // deleting the call to the partial Insert stub (it must reach 0x6fe600)
        void (Vec130::*volatile ins)(char*, unsigned, void*) = &Vec130::Insert;
        (this->*ins)(end, n - Size(), temp);
    } else {
        Destroy(begin + n * 0x130, end);
    }
}

// @ 0x006ff100
cVertexFragmentInfo& cVertexFragmentInfo::operator=(const cVertexFragmentInfo& o)
{
    const cVertexFragmentInfo* s = &o;
    f00 = s->f00;
    if (&s->name != &name)
        name.assign(s->name.begin, s->name.end);
    if (&s->uni != &uni)
        uni.assign(s->uni.begin, s->uni.end);
    vec.CopyFrom((void*)&s->vec);
    f38 = s->f38;
    f3c = s->f3c;
    b40 = s->b40;
    b41 = s->b41;
    b42 = s->b42;
    return *this;
}

// @ 0x006ff3f0
void __cdecl FUN_006ff3f0(void* stream)
{
    IO* io = (IO*)stream;
    unsigned version;
    unsigned count;
    FUN_0093a780(io, &version, 1, 0);
    FUN_0093a780(io, &count, 1, 0);
    ((void(__thiscall*)(void*, unsigned))FUN_006ff060)(&g_vs_begin, count);
    if ((int)(count + 0x10) > (int)g_15345b0)
        g_15345b0 = count + 0x10;
    VecU8 buf;
    buf.mpBegin = 0;
    buf.mpEnd = 0;
    buf.mpCap = 0;
    unsigned n = (unsigned)((g_vs_end - g_vs_begin) / 0x130);
    if ((int)n > 0) {
        unsigned off = 0;
        do {
            VsRecord* r = (VsRecord*)(g_vs_begin + off);
            FUN_0093a6c0(io, r->mBlob, 0x20);
            unsigned sz;
            FUN_0093a780(io, &sz, 1, 0);
            r->mpShader = 0;
            if (sz != 0) {
                buf.resize(sz);
                FUN_0093a6c0(io, buf.mpBegin, (int)sz);
                void* dev = g_16f89d0;
                void** vtbl = *(void***)dev;
                ((void(__cdecl*)(void*, void*, void**))vtbl[0x16c / 4])
                    (dev, buf.mpBegin, &r->mpShader);
            }
            FUN_0093a780(io, &r->mCount, 1, 0);
            {
                char* base = (char*)g_fragAllocator.Allocate((unsigned)r->mCount * 0x1c);
                int cnt = r->mCount;
                if (cnt > 0) {
                    int i = 0;
                    FragElem_s006f_f170* e = (FragElem_s006f_f170*)base;
                    FragElem_s006f_f170** slot = r->mpElems;
                    do {
                        FUN_0093a700(io, &e->mField10, 1, 0);
                        FUN_0093a700(io, &e->mField12, 1, 0);
                        FUN_0093a700(io, &e->mField14, 1, 0);
                        FUN_0093a700(io, &e->mField16, 1, 0);
                        FUN_0093a780(io, &e->mField18, 1, 0);
                        *slot = e;
                        ++slot;
                        ++e;
                        ++i;
                    } while (i < cnt);
                }
            }
            FUN_0093a780(io, r->mFieldAC, r->mCount, 0);
            FUN_0093a780(io, &r->mField12C, 1, 0);
            off += 0x130;
        } while (--n != 0);
    }
}

// @ 0x006ff680
void __cdecl FUN_006ff680(int idx)
{
    cVertexFragmentInfo_s006f_f170* dst = (cVertexFragmentInfo_s006f_f170*)(&g_vertexFragTable + (unsigned)idx * 0x44);
    {
        cVertexFragmentInfo_s006f_f170 tmp;    // default constructor inlined (empty-string sentinels)
        *dst = tmp;
    }
    ((void(__thiscall*)(void*, int))FUN_0047d240)((char*)dst + 4, 0);
    ((void(__thiscall*)(void*, int))FUN_0047d240)((char*)dst + 0x14, 0);
    ((void(__thiscall*)(void*, unsigned))FUN_006fc540)((char*)dst + 0x24, 0);
}
