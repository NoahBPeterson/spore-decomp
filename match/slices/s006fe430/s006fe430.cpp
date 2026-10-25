// Slice s006fe430: vertex-fragment declaration serialization, generated-vertex-shader string
// assembly, shader selection and the cVertexFragmentInfo table support routines.
// Region 0x6fe430-0x6ff170. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <stdio.h>
#include <string.h>

// ---- external callees -------------------------------------------------------------------
void* __cdecl FUN_011e073e(void* p, int a, unsigned size);   // operator_new[]
void* __cdecl FUN_011e0744(void* a, void* b, unsigned c);    // vector DoInsertValue
void  __cdecl FUN_00928dc0();
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl EASTL_allocator_allocate(unsigned size, const char* area, int a, int b,
                                       void* allocator, int line);   // 0x00f473a0
extern unsigned char g_eastlAllocator;                            // 0x13ebb38

// EASTL vector<0x130-block> range helpers (defined elsewhere)
char* __cdecl FUN_006fe2d0(char* first, char* last, char* dst);   // 0x006fe2d0 copy
void  __cdecl FUN_006faa30(char* dst, unsigned n, void* value);   // 0x006faa30 fill_n
void  __cdecl FUN_006fa800(void* out, char* first, char* last, char* dst, unsigned n);  // 0x006fa800
void  __cdecl FUN_006fe310(char* first, char* src, char* last);   // 0x006fe310 move forward
void  __cdecl FUN_006fa7d0(char* first, char* last, void* value); // 0x006fa7d0 fill

// EA::IO helpers
void __cdecl EA_WriteUint32(void* stream, const void* p, int n, int flag);
void __cdecl EA_WriteUint16(void* stream, const void* p, int n, int flag);   // 0x0093a9d0 (equiv t2)
void __cdecl EA_operator_shl(void* stream, const void* p, int n);   // 0x0093a9a0 (equiv t3)
void __cdecl FUN_0093adb0(void* stream, const void* p, unsigned n, int flag);

// slice-26 callees (declared, not defined here)
char* __cdecl SP_TextCopy(char* d, const char* s);                                   // 0x006fd9a0
char* __cdecl SP_TextCopySubstitute(char* d, const char* s, int a3, int a4, int a5, int a6); // 0x006fd9c0
char* __cdecl GenerateInputStruct(char* d, unsigned flags);                          // 0x006fdb90
char* __cdecl GenerateCurrentStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes); // 0x006fdd50
char* __cdecl GenerateOutputStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes);  // 0x006fdef0
char* __cdecl GenerateFillCurrentStruct(char* d, unsigned flags, int ntex);          // 0x006fdfc0
char* __cdecl GenerateFillOutputStruct(char* d, unsigned flags, unsigned ntex);      // 0x006fe170
void* __cdecl VSProfileFromVersion(unsigned version);                  // 0x007776c0
int   __cdecl D3DXCompileShader(const char* src, unsigned length, const void* defines,
                                void* includes, const char* entry, void* profile,
                                unsigned flags, void** shader, void** errors,
                                void* pool);                           // 0x011e1fd4
extern const char g_str140bb6c[];                                      // 0x140bb6c "main"
bool  __cdecl FUN_006fe350(void* e);
void  __cdecl FUN_006fe3c0(int a, int b);

// ---- globals ----------------------------------------------------------------------------
extern unsigned char g_fragInfoTable;     // 0x1624710, stride 0x44
extern const char*   g_str1534e44;        // 0x1534e44 -> "cVertOut main(...)"
extern const char*   g_str1534e40;        // 0x1534e40 -> "\nreturn Out;\n}\n"
extern unsigned int  g_15345b0;           // 0x15345b0
extern unsigned char g_15345ac;           // 0x15345ac
extern void*         g_1624568;           // 0x1624568 currently-selected vertex shader
extern char          g_1620300;           // 0x1620300 shader text buffer
extern void*         g_16f6564;           // 0x16f6564 m_vertexShader
extern unsigned int  g_16f8cf8;           // 0x16f8cf8
extern void*         g_16f89d0;           // 0x16f89d0 d3d9 device

// vector globals (begin/end/cap dwords)
extern int* g_v1_begin;   // 0x1628b14
extern int* g_v1_end;     // 0x1628b18
extern int* g_v1_cap;     // 0x1628b1c
extern int* g_v2_begin;   // 0x16246fc
extern int* g_v2_end;     // 0x1624700
extern int* g_v2_cap;     // 0x1624704
extern char* g_vs_begin;  // 0x1628c20
extern char* g_vs_end;    // 0x1628c24

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

// @ 0x006fe430
void __cdecl FUN_006fe430(void* stream) {
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
__declspec(noinline) void Vec130::Insert(char* pos, unsigned n, void* value) {
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
void* __fastcall FUN_006fe7f0(char* p) {
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
void __fastcall FUN_006fe830(char* p) {
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
void __cdecl FUN_006fe890() {
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
void __cdecl FUN_006fe8f0(int a, int b) {
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

// @ 0x006ff100
cVertexFragmentInfo& cVertexFragmentInfo::operator=(const cVertexFragmentInfo& o) {
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

// @ 0x006fe960
char* AddFragmentDeclarations(char* buf, int idx, int* reg) {
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
} // namespace

// ---- vertex-shader generator context (first argument of GenerateVertexShader) ----
struct VSGenCtx {
    char           pad00[0x0e];  // +0x00
    unsigned short w0e;          // +0x0e shader model version
    char           pad10[0x34];  // +0x10
    unsigned char  b44;          // +0x44 flags (bit 0 = software/pixel-1-1 mode)
};

// @ 0x006fea30
void __cdecl FUN_006fea30(int a1, int a2) {
    VSGenCtx* gen = (VSGenCtx*)a1;
    const unsigned char* frags = (const unsigned char*)a2;
    char* buf = &g_1620300;
    unsigned maskLo = 0;                       // union of the 0x38 words of the used fragments
    unsigned maskHi = 0;                       // union of the 0x3c words
    unsigned used = 0;                         // sampler count
    unsigned char slots[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned reg = 0;
    FUN_006fe890();
    for (int i = 0; i < 0x20; i++) {
        unsigned fi = frags[i];
        if (fi == 0)
            break;
        unsigned char* rec = &g_fragInfoTable + fi * 0x44;
        maskLo |= *(unsigned*)(rec + 0x38);
        maskHi |= *(unsigned*)(rec + 0x3c);
        if (rec[0x40] != 0 || *(int*)(rec + 0x14) != *(int*)(rec + 0x18))
            buf = AddFragmentDeclarations(buf, (int)fi, (int*)&reg);
        unsigned nreg = rec[0x41];
        for (unsigned k = 0; k < nreg; k++) {
            if (used >= 8) {
                used = 8;
                break;
            }
            slots[used] = rec[0x42];
            ++used;
        }
    }
    char* p = GenerateInputStruct(buf, maskLo);
    p = GenerateCurrentStruct(p, maskHi | maskLo, used, slots);
    p = GenerateOutputStruct(p, maskHi, used, slots);
    p = SP_TextCopy(p, g_str1534e44);
    p = GenerateFillCurrentStruct(p, maskLo, (int)used);
    reg = 0;
    int idx = 0;
    do {
        unsigned fi = frags[idx];
        if (fi == 0)
            break;
        p = SP_TextCopySubstitute(p, *(const char**)(&g_fragInfoTable + fi * 0x44 + 4), 0, (int)reg, 0, 0);
        ++idx;
        reg += (unsigned char)(&g_fragInfoTable)[fi * 0x44 + 0x41];
    } while (idx < 0x20);
    p = GenerateFillOutputStruct(p, maskHi, reg);
    char* end = SP_TextCopy(p, g_str1534e40);
    *end = 0;
    unsigned version = gen->w0e;
    unsigned profileVersion = version != 0 ? (version | 0xfffe0000u) : 0;
    void* profile = VSProfileFromVersion(profileVersion);
    unsigned flags = (gen->b44 & 1) != 0 ? 0x32 : 0x12;
    void* shaderBlob = 0;
    void* errorBlob = 0;
    int hr = D3DXCompileShader(&g_1620300, (unsigned)(end - &g_1620300), 0, 0, g_str140bb6c,
                               profile, flags, &shaderBlob, &errorBlob, 0);
    if (errorBlob != 0)
        ((void(__stdcall*)(void*))(*(void***)errorBlob)[2])(errorBlob);
    if (hr >= 0) {
        void* device = g_16f89d0;
        void** devvt = *(void***)device;
        unsigned* table = (unsigned*)((void* (__stdcall*)(void*, void*))(*(void***)shaderBlob)[3])(shaderBlob, buf + 0x20);
        ((void(__stdcall*)(void*, unsigned*))devvt[0x16c / 4])(device, table);
        ((void(__stdcall*)(void*))(*(void***)shaderBlob)[2])(shaderBlob);
    }
}

// ---- pixel/vs cache lookups ----
int  __cdecl BinaryFindPixelShader(const char* key, const void* begin, unsigned count); // 0x006fdab0
void __cdecl PixelFrag_PushBack();                                                    // 0x006fb0e0

// @ 0x006fec40
__declspec(noinline) int __cdecl FUN_006fec40(void* a1, void* a2) {
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
bool __cdecl FUN_006feee0(void* a1, const char* name) {
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
void __cdecl FUN_006fef70(int a) {
    char buf[32];
    FUN_006fe3c0(a, (int)buf);
    FUN_006feee0((void*)a, buf);
}

// @ 0x006fefa0
void __cdecl FUN_006fefa0() {
    ((Vec130*)0x01628C20)->Destroy(g_vs_begin, g_vs_end);
    unsigned int n = g_15345b0;
    if (n == 0)
        n = 0x200;
    ((Vec130*)0x01628C20)->Reserve(n);
    g_1624568 = 0;
}

// @ 0x006fefe0
void __cdecl FUN_006fefe0() {
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
void Vec130::Resize(unsigned n) {
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
// --- equivalence checker address annotations
    void EASTL_allocator_deallocate(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
