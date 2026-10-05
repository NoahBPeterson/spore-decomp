// Slice s006fd520: rw::graphics::ActiveState state flushes, vertex-declaration text
// generators, vertex-shader binary search, and small stream/vector helpers.
// Region 0x6fd520-0x6fe430. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// ---- external callees -------------------------------------------------------------------
void  __cdecl FUN_006fd330(void* dst, unsigned n, void* value);
void  __cdecl FUN_00d73090(void* first, void* last);
void  __cdecl FUN_006fcdc0(void* self, void* stream, int value);
void  __cdecl FUN_0093a6c0(void* stream, const void* data, int n);
void* __cdecl FUN_006fcb90(int n, void* first, int b);
void  __cdecl FUN_006fefe0();
void  __cdecl FUN_006fb960();
void  __cdecl FUN_006fefa0();
void  __cdecl FUN_006fb920();
bool  __cdecl FUN_006fef70(void* shader);
bool  __cdecl FUN_006fb8f0(void* shader);
void  __cdecl FUN_011f1280(int index, void* texture);
void  __cdecl FUN_011f1210();
void  __cdecl FUN_011f7850();
void  __cdecl FUN_011f6920();
void  __cdecl FUN_006fa1b0(unsigned state, bool flag);

// ---- globals ----------------------------------------------------------------------------
extern void*  g_device;            // 0x16f89d0  rw::graphics::ActiveState::m_d3d9Device
extern void*  g_shader;            // 0x16f6568
extern unsigned int g_softStateUpdated;  // 0x16f9110
extern unsigned int g_softStateDelta;    // 0x16f8af8
extern unsigned int g_rasterDelta;       // 0x16f8b00
extern unsigned int g_samplerDelta[];    // 0x16f8cb0
extern int    g_samplerShadow[];         // 0x16f8d08
extern unsigned char g_uvMapping[];      // 0x16f85b4
extern unsigned int g_shaderDataDirty[]; // 0x16f89f8
extern unsigned char g_texTable_16f6ddc[]; // 0x16f6ddc (pointer stored as bytes)

// manager accessed by the shader-state dispatcher
extern unsigned char g_mgr_1624568[];    // 0x1624568 (pointer stored as bytes)
extern void*  g_shaderFns[];             // 0x16fa604

// ---- small helpers ----------------------------------------------------------------------
static inline void** Vt(void* p) { return *(void***)p; }

// @ 0x006fd520
struct Vec1c {
    char* begin;   // +0x00
    char* end;     // +0x04
    int Size() const { return (int)((end - begin) / 0x1c); }
    void Resize(unsigned n);
};

struct Elem1c {
    unsigned char a;      // +0x00
    unsigned char b;      // +0x01
    unsigned short c;     // +0x02
    unsigned short d;     // +0x04
    unsigned short e;     // +0x06
    unsigned int  f;      // +0x08
    unsigned int  g;      // +0x0c
    unsigned int  h;      // +0x10
    unsigned int  i;      // +0x14
    unsigned char stream; // +0x18
    Elem1c() : a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0), i(0) {}
};

void Vec1c::Resize(unsigned n) {
    if ((unsigned)Size() < n) {
        Elem1c temp;
        temp.stream = 0xff;
        FUN_006fd330(end, n - Size(), &temp);
    } else {
        FUN_00d73090(begin + n * 0x1c, end);
    }
}

// @ 0x006fd5d0
struct StreamCtx {
    char pad00[0x48];
    Vec1c decls[1];   // +0x48
    bool ReadDecls(void* stream, unsigned flag, int b);
};

bool StreamCtx::ReadDecls(void* stream, unsigned flag, int b) {
    (void)stream; (void)flag; (void)b;
    return false;
}

// @ 0x006fd730
void __cdecl FUN_006fd730(int stage, int type, int value) {
    if (value != g_samplerShadow[stage * 14 + type]) {
        void* dev = g_device;
        void* fn = Vt(dev)[0x114 / 4];
        ((void(__stdcall*)(void*, int, int, int))fn)(dev, stage, type, value);
        g_softStateUpdated |= 0x2000000;
        g_samplerDelta[stage] |= (type - 1);
        g_samplerShadow[stage * 14 + type] = value;
    }
}

// @ 0x006fd7b0
void __cdecl FUN_006fd7b0() {
    FUN_006fefe0();
    FUN_006fb960();
    FUN_006fefa0();
    FUN_006fb920();
}

// @ 0x006fd7d0
struct TexEntry {
    int           index;   // +0x00
    void**        texture; // +0x04
    unsigned char flags;   // +0x08
    unsigned char s0;      // +0x09
    unsigned char s1;      // +0x0a
    unsigned char s2;      // +0x0b
    unsigned char s3;      // +0x0c
    char          pad0d[3];
};
struct TexTable {
    int      count;   // +0x00
    TexEntry entries[1];
};

int __cdecl FUN_006fd7d0() {
    TexTable* tbl = (TexTable*)g_texTable_16f6ddc;
    if (tbl != 0) {
        bool changed = false;
        int n = tbl->count;
        if (n > 0) {
            TexEntry* e = &tbl->entries[0];
            for (int i = 0; i < n; i++, e++) {
                if (e->texture == 0) {
                    FUN_011f1280(e->index, 0);
                } else {
                    FUN_011f1280(e->index, *e->texture);
                }
                g_rasterDelta |= ((unsigned)1 << (e->index & 0x1f));
                if (e->flags != 0) {
                    if (e->flags & 1) {
                        FUN_006fd730(e->index, 1, e->s0);
                        FUN_006fd730(e->index, 2, e->s0);
                        FUN_006fd730(e->index, 3, e->s0);
                    }
                    if (e->flags & 2) {
                        FUN_006fd730(e->index, 6, e->s1);
                        FUN_006fd730(e->index, 5, e->s1);
                    }
                    if (e->flags & 4) {
                        FUN_006fd730(e->index, 7, e->s2);
                    }
                    if ((e->flags & 8) && g_uvMapping[e->index] != e->s3) {
                        g_uvMapping[e->index] = e->s3;
                        changed = true;
                    }
                }
            }
            if (changed) {
                g_softStateUpdated |= 0x8000;
                g_softStateDelta |= 0x8000;
                FUN_011f1210();
            }
        }
    }
    unsigned int state = g_softStateUpdated;
    void* shader = g_shader;
    bool b0 = false;
    bool b1 = false;
    if ((state & 0x113fcc) != 0) {
        b0 = FUN_006fef70(shader);
        state = g_softStateUpdated;
    }
    if ((state & 0x51800c) != 0) {
        b1 = FUN_006fb8f0(shader);
        state = g_softStateUpdated;
    }
    if (state != 0) {
        FUN_006fa1b0(state, b0);
        state = g_softStateUpdated;
        if (state != 0) {
            FUN_006fa1b0(state, b1);
        }
    }
    unsigned int* d = g_shaderDataDirty;
    for (int k = 0x40; k != 0; k--) {
        *d++ = 0;
    }
    FUN_011f7850();
    FUN_011f6920();
    return 1;
}

// @ 0x006fd990
void __cdecl FUN_006fd990(void* self) {
    *(void**)((char*)self + 0x14) = (void*)&FUN_006fd7d0;
}

// @ 0x006fd9a0
__declspec(noinline) char* __cdecl SP_TextCopy(char* d, const char* s) {
    while (*s)
        *d++ = *s++;
    return d;
}

// @ 0x006fd9c0
__declspec(noinline) char* __cdecl SP_TextCopySubstitute(char* d, const char* s, int a3, int a4, int a5, int a6) {
    char c = *s;
    while (c != '\0') {
        if (c == '<' && s[3] == '>' && isalpha(s[1]) && isdigit(s[2])) {
            int v = s[2] - '0';
            switch (s[1]) {
            case 'v': v += a3; break;
            case 't': v += a4; break;
            case 's': v += a5; break;
            case 'u': if (a6 >= 0) v += a6; break;
            }
            if (v > 10) {
                *d++ = (char)(v / 10) + '0';
                v = v % 10;
            }
            *d++ = (char)v + '0';
            s += 4;
        } else {
            *d = *s;
            ++s;
            ++d;
        }
        c = *s;
    }
    return d;
}

// @ 0x006fdab0
struct ShaderBlob {
    char name[0x130];
};

int __cdecl BinaryFindPixelShader(const char* key, const ShaderBlob* base, unsigned count) {
    int first = 0;
    if (count > 0) {
        unsigned n = count;
        int last = (int)count - 1;
        do {
            if (n <= 1) {
                int c = strcmp(key, base[first].name);
                if (c == 0)
                    return first;
                return (c < 0) ? (-1 - first) : (-2 - first);
            }
            int mid = ((int)(n & 1) - 1) + (int)(n >> 1) + first;
            int c = strcmp(key, base[mid].name);
            if (c == 0)
                return mid;
            if (c < 0)
                last = mid - 1;
            else
                first = mid + 1;
            n = (unsigned)(last - first) + 1;
        } while (n != 0);
    }
    return -1 - first;
}

// @ 0x006fdb90
void __cdecl GenerateInputStruct(char* d, unsigned flags) {
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
void __cdecl GenerateCurrentStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes) {
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
void __cdecl GenerateOutputStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes) {
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
char* __cdecl GenerateFillCurrentStruct(char* d, unsigned flags, int ntex) {
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
char* __cdecl GenerateFillOutputStruct(char* d, unsigned flags, unsigned ntex) {
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

void __cdecl FUN_006fe230(unsigned mask, char flag) {
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
struct Block130 { unsigned int d[0x4c]; };

Block130* __cdecl FUN_006fe310(Block130* first, Block130* last, Block130* dest) {
    while (last != first) {
        --last;
        --dest;
        *dest = *last;
    }
    return dest;
}

// @ 0x006fe350
extern char*** g_namesBegin_1628b14;
extern char*** g_namesEnd_1628b18;
extern void*   g_16f6dac;

bool __cdecl FUN_006fe350(void* name) {
    char*** begin = g_namesBegin_1628b14;
    int n = (int)(g_namesEnd_1628b18 - begin);
    for (int i = 0; i < n; i++) {
        if (strcmp(begin[i][0], *(char**)name) == 0)
            return true;
    }
    return false;
}

// @ 0x006fe3c0
struct V1c { char* begin; char* end; };

void __cdecl FUN_006fe3c0(int a, int b) {
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
