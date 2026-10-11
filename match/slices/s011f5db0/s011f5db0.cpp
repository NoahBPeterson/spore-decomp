// slice s011f5db0 -- RenderWare 4 D3D9 graphics (rwgdrvgraph/D3D9 pixel-shader subsystem).
// DynamicIndexBufferManager internals and the rwg_D3D9 HLSL source generators.
//
// Module flags: /vc71 /O2 /MD /Gy /EHsc /TP  (RenderWare 4 core: VC .NET 2003 / cl 13.10).
// These are RenderWare 4 core functions: single-object codegen cannot reproduce the /LTCG
// cross-call register allocation, so byte-exactness is not the goal here (equivalence only).
#include "types.h"
#include <stdio.h>

typedef unsigned char  byte;
typedef unsigned short u16;

static int ByteCmp(const byte* a, const byte* b, unsigned n) {
    for (unsigned k = 0; k < n; ++k)
        if (a[k] != b[k]) return a[k] < b[k] ? -1 : 1;
    return 0;
}

static int StrCmp(const byte* a, const byte* b) {
    while (*a != 0 && *a == *b) { ++a; ++b; }
    return (int)*a - (int)*b;
}

// ---------------------------------------------------------------------------
// D3D9 COM device access (calls go through the active device's vtable)
// ---------------------------------------------------------------------------
extern void* g_d3d9Device;        // 0x016f89d0 IDirect3DDevice9*
static inline void* VSlot(void* obj, int byteOff) {
    return ((void**)(*(void***)obj))[byteOff / 4];
}
typedef void  (__stdcall* PFN_Release)(void*);
typedef long  (__stdcall* PFN_CreateIndexBuffer)(void*, unsigned, unsigned, unsigned, int, void**, void*);
typedef long  (__stdcall* PFN_SetPixelShader)(void*, const void*);

// ---------------------------------------------------------------------------
// Internal allocator pool (single-object compile only sees the calls)
// ---------------------------------------------------------------------------
class RWSpanPool {
public:
    void  Init(int n, int align);   // 0x011fd530
    void* Alloc();                  // 0x011fd610
    void  Free(void* p);            // 0x011fd6b0
    void  Shutdown();               // 0x011fd5d0
    int   mElemSize;                // +0
    int   mCount;                   // +4
    void* mBase;                    // +8
    int   mCap;                     // +0xc
    void* mFreeList;                // +0x10
};
extern RWSpanPool g_poolTree;     // 0x170a7a0
extern RWSpanPool g_pool[2];      // 0x170a848 / 0x170a85c

// tree node used by FUN_011f5db0
struct TreeNode {
    unsigned short k0;            // +0
    unsigned short k1;            // +2
    void*          list;          // +4
    unsigned       f8;            // +8
    TreeNode*      next;          // +0xc
};
struct RangeItem {
    int        start;             // +0
    int        len;               // +4
    int        key;               // +8
    RangeItem* next;              // +0xc
    RangeItem* prev;              // +0x10
};

// dynamic index-buffer slot
struct IBNode {
    void*    pResource;           // +0
    unsigned mSize;               // +4
    unsigned mValid;              // +8
    unsigned mFieldC;             // +0xc
    IBNode*  pNext;               // +0x10
};
struct IBRec {
    void*    pResource;           // +0
    unsigned mSize;               // +4
    unsigned mValid;              // +8
};

extern TreeNode* g_treeRoot;      // 0x170a798
extern IBNode*   g_head[2];       // 0x170a804 (65) / 0x170a808 (66)
extern IBRec     g_rec[4];        // 0x170a80c
extern unsigned  g_cur65;         // 0x170a83c
extern unsigned  g_cur66;         // 0x170a840
extern int       g_015d07cc;      // 0x015d07cc

// HLSL generator state
extern char  g_psHlslBuffer[];    // 0x171c0c0 D3D9HLSLTextBuffer
extern byte  g_psSamplers[];      // 0x1718b08 D3D9PixelShaderEffectSamplers
extern byte  g_psDefs[];          // 0x1718c08 D3D9PixelShaderEffectDefs (stride 0x10)
extern void* g_16f6568;           // 0x016f6568 active shader state
extern void* g_pixelShader;       // 0x016f89cc m_pixelShader
extern void* g_savedPixelShader;  // 0x170ed50 saved pixel shader
extern const char* g_psMainFmt;   // 0x15d07d4 -> "PS_OUT main(...)\n{\n..."
extern const char* g_psRetFmt;    // 0x15d07d0 -> "\nreturn Out;\n}\n"

// byte-table used by the offset function
extern byte g_byteTable719c08[];  // 0x1719c08

// pixel-shader state tables (FUN_011f6940 / FUN_011f6920)
extern byte  g_170eca9[];         // 0x170eca9
extern int   g_170eccc[];         // 0x170eccc
extern byte  g_170ed71[];         // 0x170ed71
extern int   g_170ed94[];         // 0x170ed94
extern int   g_170ed4c;           // 0x170ed4c
extern int   g_170ee14;           // 0x170ee14
extern int   g_170ed5c;           // 0x170ed5c
extern int   g_170ec98;           // 0x170ec98
extern int   g_170ed60;           // 0x170ed60

// ---- callees -----------------------------------------------------------------
int   __cdecl FUN_011f5fa0(unsigned length, int format, void** ppResource, unsigned f4); // 0x011f5fa0
int   __cdecl FUN_011f6370(int base);                                                   // 0x011f6370
char* __cdecl D3D9TextCopy(char* dst, const char* src);                                 // 0x011fd6d0
int   __cdecl FUN_011fcd10(int* a, int* b);                                             // 0x011fcd10
int   __cdecl FUN_011e1fd4(const char* src, int len, void* defs, void* inc,
                           const char* fn, const char* profile, int flags,
                           void** ppShader, void** ppErr, void* ppConst);               // 0x011e1fd4

// ===========================================================================
// @ 0x011f5db0
// ===========================================================================
void FUN_011f5db0(int key0, int key1, int length, int itemKey, int offset)
{
    TreeNode* node = g_treeRoot;
    if (!node)
        return;
    while ((u16)key0 != node->k0 || (u16)key1 != node->k1) {
        node = node->next;
        if (!node)
            return;
    }
    RangeItem* item;
    for (item = (RangeItem*)node->list; item; item = item->next) {
        if (itemKey == item->key &&
            (item->start + item->len == offset || length + offset == item->start))
            goto merge;
    }
    {
        RangeItem* n = (RangeItem*)g_poolTree.Alloc();
        n->key   = itemKey;
        n->start = offset;
        n->len   = length;
        n->prev  = 0;
        n->next  = (RangeItem*)node->list;
        if (node->list)
            ((RangeItem*)node->list)->prev = n;
        node->list = n;
    }
    return;

merge:
    if (item->start + item->len == offset) {
        item->len += length;
    } else if (length + offset == item->start) {
        item->start = offset;
        item->len  += length;
    }
    {
        int s = item->start;
        int l = item->len;
        RangeItem* other = (RangeItem*)node->list;
        if (!other)
            return;
        while (!(itemKey == other->key &&
                 (other->start + other->len == s || l + s == other->start))) {
            other = other->next;
            if (!other)
                return;
        }
        if (item->prev)
            item->prev->next = item->next;
        if (item->next)
            item->next->prev = item->prev;
        if (item == node->list)
            node->list = item->next;
        g_poolTree.Free(item);
        item = other;
        goto merge;
    }
}

// ===========================================================================
// @ 0x011f5ee0
// ===========================================================================
void FUN_011f5ee0(void)
{
    IBNode* n;
    for (int i = 0; i < 4; ++i) {
        g_rec[i].pResource = 0;
        g_rec[i].mSize     = 0;
        g_rec[i].mValid    = 0;
    }
    for (n = g_head[1]; n; n = n->pNext) {
        if (n->pResource) {
            (*(PFN_Release)VSlot(n->pResource, 8))(n->pResource);
            n->pResource = 0;
        }
        n->mValid  = 0;
        n->mFieldC = 0;
    }
    for (n = g_head[0]; n; n = n->pNext) {
        if (n->pResource) {
            (*(PFN_Release)VSlot(n->pResource, 8))(n->pResource);
            n->pResource = 0;
        }
        n->mValid  = 0;
        n->mFieldC = 0;
    }
    g_pool[1].Shutdown();
    g_pool[0].Shutdown();
}

// ===========================================================================
// @ 0x011f5fa0
// ===========================================================================
int FUN_011f5fa0(unsigned length, int format, void** ppResource, unsigned f4)
{
    int idx = (format != 0x65) ? 1 : 0;
    IBNode* best = 0;
    IBNode* n;
    for (n = g_head[idx]; n; n = n->pNext) {
        if (n->mValid == 0) {
            if (n->mSize == length)
                break;
            if (best == 0 || best->mSize < length)
                best = n;
        }
    }
    if (n != 0) {
        n->mValid = 1;
        *ppResource = n->pResource;
        return 0;
    }
    if (best == 0) {
        best = (IBNode*)g_pool[idx].Alloc();
        if (best == 0)
            return (int)0x8007000e;
        best->pNext = g_head[idx];
        g_head[idx] = best;
    } else {
        (*(PFN_Release)VSlot(best->pResource, 8))(best->pResource);
    }
    long hr = (*(PFN_CreateIndexBuffer)VSlot(g_d3d9Device, 0x6c))(
        g_d3d9Device, length, 0x208, (unsigned)format, 0, (void**)best, 0);
    if (hr >= 0) {
        best->mFieldC = f4;
        best->mValid  = 1;
        best->mSize   = length;
        *ppResource = best->pResource;
    }
    return (int)hr;
}

// ===========================================================================
// @ 0x011f6080
// ===========================================================================
void FUN_011f6080(void* pResource)
{
    IBNode* n;
    for (n = g_head[0]; n; n = n->pNext)
        if (n->pResource == pResource)
            goto found;
    for (n = g_head[1]; n; n = n->pNext)
        if (n->pResource == pResource)
            goto found;
    return;
found:
    n->mValid  = 0;
    n->mFieldC = 0;
}

// ===========================================================================
// @ 0x011f60c0  rw::graphics::DynamicIndexBufferManager::ForceDiscard
// ===========================================================================
void FUN_011f60c0(void)
{
    g_rec[0].mValid = 0;
    g_rec[1].mValid = 0;
    g_rec[2].mValid = 0;
    g_rec[3].mValid = 0;
    if (++g_cur65 >= 2)
        g_cur65 = 0;
    if (++g_cur66 >= 2)
        g_cur66 = 0;
}

// ===========================================================================
// @ 0x011f6110
// ===========================================================================
void FUN_011f6110(void)
{
    IBNode* n;
    for (n = g_head[0]; n; n = n->pNext) {
        if (n->pResource) {
            (*(PFN_Release)VSlot(n->pResource, 8))(n->pResource);
            n->pResource = 0;
        }
        if (n->mFieldC)
            *(unsigned*)n->mFieldC = 0;
        else
            n->mValid = 0;
    }
    for (n = g_head[1]; n; n = n->pNext) {
        if (n->pResource) {
            (*(PFN_Release)VSlot(n->pResource, 8))(n->pResource);
            n->pResource = 0;
        }
        if (n->mFieldC)
            *(unsigned*)n->mFieldC = 0;
        else
            n->mValid = 0;
    }
}

// ===========================================================================
// @ 0x011f6180
// ===========================================================================
int FUN_011f6180(void)
{
    if (g_pool[0].mBase != 0 || g_pool[1].mBase != 0)
        return 0;
    g_pool[0].Init(0x14, 4);
    g_pool[1].Init(0x14, 4);
    g_head[0] = 0;
    g_head[1] = 0;
    if (g_015d07cc == 0)
        return 1;
    g_cur65 = 0;
    int sz = g_015d07cc * 2;
    IBRec* rec = &g_rec[0];
    for (int i = 0; i < 0x18; i += 0xc) {
        if (FUN_011f5fa0((unsigned)sz, 0x65, &rec->pResource, 0) < 0)
            return 0;
        rec->mSize  = (unsigned)sz;
        rec->mValid = 0;
        ++rec;
    }
    g_cur66 = 0;
    sz = g_015d07cc << 2;
    rec = &g_rec[2];
    for (int i = 0; i < 0x18; i += 0xc) {
        if (FUN_011f5fa0((unsigned)sz, 0x66, &rec->pResource, 0) < 0)
            return 0;
        rec->mSize  = (unsigned)sz;
        rec->mValid = 0;
        ++rec;
    }
    return 1;
}

// ===========================================================================
// @ 0x011f6270
// ===========================================================================
void FUN_011f6270(void)
{
    IBNode* n;
    for (n = g_head[0]; n; n = n->pNext) {
        (*(PFN_CreateIndexBuffer)VSlot(g_d3d9Device, 0x6c))(
            g_d3d9Device, n->mSize, 0x208, 0x65, 0, (void**)n, 0);
        if (n->mFieldC)
            *(unsigned*)n->mFieldC = (unsigned)(size_t)n->pResource;
    }
    for (n = g_head[1]; n; n = n->pNext) {
        (*(PFN_CreateIndexBuffer)VSlot(g_d3d9Device, 0x6c))(
            g_d3d9Device, n->mSize, 0x208, 0x66, 0, (void**)n, 0);
        if (n->mFieldC)
            *(unsigned*)n->mFieldC = (unsigned)(size_t)n->pResource;
    }
    g_cur65 = 0;
    IBRec* rec = &g_rec[0];
    for (int i = 0; i < 0x18; i += 0xc) {
        if (FUN_011f5fa0(rec->mSize, 0x65, &rec->pResource, 0) < 0)
            break;
        rec->mValid = 0;
        ++rec;
    }
    g_cur66 = 0;
    rec = &g_rec[2];
    for (int i = 0; i < 0x18; i += 0xc) {
        if (FUN_011f5fa0(rec->mSize, 0x66, &rec->pResource, 0) < 0)
            return;
        rec->mValid = 0;
        ++rec;
    }
}

// ===========================================================================
// @ 0x011f6370
// ===========================================================================
int FUN_011f6370(int base)
{
    byte* p = (byte*)(base + 0x11);
    int* out = (int*)(base + 0x34);
    byte b = *p;
    int prev = 0;
    do {
        p++;
        int cur;
        int next;
        if (g_byteTable719c08[b] == 0) {
            cur  = 0;
            next = prev;
        } else {
            next = prev + g_byteTable719c08[b];
            cur  = prev;
        }
        *out = cur;
        b = *p;
        out++;
        prev = next;
    } while (b != 0);
    return 0;
}

// ===========================================================================
// @ 0x011f63b0  rw::graphics::(anonymous)::rwg_D3D9GenerateInputStruct
// ===========================================================================
char* FUN_011f63b0(char* dest, unsigned mask, unsigned numTex, unsigned texMask)
{
    dest = D3D9TextCopy(dest, "\nstruct PS_IN\n{\n");
    if (mask & 2)
        dest = D3D9TextCopy(dest, "float4 position :POSITION0;\n");
    if (mask & 4)
        dest = D3D9TextCopy(dest, "float3 normal :NORMAL0;\n");
    if (mask & 8)
        dest = D3D9TextCopy(dest, "float3 tangent :TANGENT0;\n");
    if (mask & 0x10)
        dest = D3D9TextCopy(dest, "float3 binormal :BINORMAL0;\n");
    if (mask & 0x20)
        dest = D3D9TextCopy(dest, "float4 color :COLOR0;\n");
    if (mask & 0x140)
        dest = D3D9TextCopy(dest, "float4 specularAndFog :COLOR1;\n");
    byte i = 0;
    if (numTex != 0) {
        unsigned n = 0;
        do {
            if (texMask & (1u << ((n + 6) & 0x1f))) {
                int wrote = sprintf(dest, "float4 texcoord%d :TEXCOORD%d;\n", n, n);
                dest += wrote;
            }
            i = (byte)(i + 1);
            n = i;
        } while (n < numTex);
    }
    if ((char)mask < 0)
        dest = D3D9TextCopy(dest, "int4 indices :BLENDINDICES0;\n");
    dest = D3D9TextCopy(dest, "};\n\n");
    return dest;
}

// ===========================================================================
// @ 0x011f64c0  rw::graphics::(anonymous)::rwg_D3D9GenerateCurrentStruct
// ===========================================================================
char* FUN_011f64c0(char* dest, unsigned mask)
{
    dest = D3D9TextCopy(dest, "struct PS_CURRENT\n{\n");
    if (mask & 2)
        dest = D3D9TextCopy(dest, "float4 color;\n");
    if (mask & 4)
        dest = D3D9TextCopy(dest, "float4 color1;\n");
    if (mask & 8)
        dest = D3D9TextCopy(dest, "float4 color2;\n");
    if (mask & 0x10)
        dest = D3D9TextCopy(dest, "float4 color3;\n");
    if (mask & 0x20)
        dest = D3D9TextCopy(dest, "float depth;\n");
    dest = D3D9TextCopy(dest, "};\n\n");
    return dest;
}

// ===========================================================================
// @ 0x011f6550  rw::graphics::(anonymous)::rwg_D3D9GenerateOutputStruct
// ===========================================================================
char* FUN_011f6550(char* dest, unsigned mask)
{
    dest = D3D9TextCopy(dest, "struct PS_OUT\n{\n");
    if (mask & 2)
        dest = D3D9TextCopy(dest, "float4 color :COLOR0;\n");
    if (mask & 4)
        dest = D3D9TextCopy(dest, "float4 color1 :COLOR1;\n");
    if (mask & 8)
        dest = D3D9TextCopy(dest, "float4 color2 :COLOR2;\n");
    if (mask & 0x10)
        dest = D3D9TextCopy(dest, "float4 color3 :COLOR3;\n");
    if (mask & 0x20)
        dest = D3D9TextCopy(dest, "float depth :DEPTH;\n");
    dest = D3D9TextCopy(dest, "};\n\n");
    return dest;
}

// ===========================================================================
// @ 0x011f65e0  rw::graphics::(anonymous)::rwg_D3D9GenerateDumpOutput
// ===========================================================================
char* FUN_011f65e0(char* dest, unsigned mask)
{
    dest = D3D9TextCopy(dest, "\n");
    if (mask & 2)
        dest = D3D9TextCopy(dest, "Out.color = Current.color;\n");
    if (mask & 4)
        dest = D3D9TextCopy(dest, "Out.color1 = Current.color1;\n");
    if (mask & 8)
        dest = D3D9TextCopy(dest, "Out.color2 = Current.color2;\n");
    if (mask & 0x10)
        dest = D3D9TextCopy(dest, "Out.color3 = Current.color3;\n");
    if (mask & 0x20)
        dest = D3D9TextCopy(dest, "Out.depth = Current.depth;\n");
    return dest;
}

// ===========================================================================
// @ 0x011f6660  rw::graphics::(anonymous)::rwg_D3D9BinaryFindPixelShader
// ===========================================================================
int FUN_011f6660(const byte* pName, const byte* pKey, int table, unsigned count)
{
    int lo = 0;
    unsigned n = count;
    if (n == 0)
        return -1 - lo;
    int hi = (int)n - 1;
    while (n > 1) {
        int mid = lo + (int)(n >> 1) + (int)(n & 1) - 1;
        const byte* def   = (const byte*)(table + mid * 0x44);
        const byte* dname = def + 0x11;
        int c = StrCmp(pKey, dname);
        if (c == 0 && ByteCmp(pName, def, 0x11) == 0)
            return mid;
        c = StrCmp(pKey, dname);
        if (c < 0) {
            hi = mid - 1;
        } else if (c == 0) {
            if (ByteCmp(pName, def, 0x11) < 0)
                hi = mid - 1;
            else
                lo = mid + 1;
        } else {
            lo = mid + 1;
        }
        n = (unsigned)(hi - lo + 1);
        if (n == 0)
            return -1 - lo;
    }
    {
        const byte* def   = (const byte*)(table + lo * 0x44);
        const byte* dname = def + 0x11;
        int c = StrCmp(pKey, dname);
        if (c == 0 && ByteCmp(pName, def, 0x11) == 0)
            return lo;
        c = StrCmp(pKey, dname);
        if (c >= 0) {
            if (c == 0) {
                if (ByteCmp(pName, def, 0x11) < 0)
                    return -1 - lo;
            }
            return -2 - lo;
        }
        return -1 - lo;
    }
}

// ===========================================================================
// @ 0x011f68c0
// ===========================================================================
void FUN_011f68c0(void)
{
    g_savedPixelShader = g_pixelShader;
    if (g_pixelShader) {
        (*(PFN_SetPixelShader)VSlot(g_d3d9Device, 0x1ac))(g_d3d9Device, 0);
        g_pixelShader = 0;
    }
}

// ===========================================================================
// @ 0x011f68f0
// ===========================================================================
void FUN_011f68f0(void)
{
    if (g_savedPixelShader != 0 && g_pixelShader != g_savedPixelShader) {
        void* dev = g_d3d9Device;
        (*(PFN_SetPixelShader)VSlot(dev, 0x1ac))(dev, g_savedPixelShader);
        g_pixelShader = g_savedPixelShader;
    }
}

// ===========================================================================
// @ 0x011f6920
// ===========================================================================
void FUN_011f6920(void)
{
    g_170ed71[0] = 0;
    g_170ee14 = 0;
    g_170eca9[0] = 0;
    g_170ed4c = 0;
}

// ===========================================================================
// @ 0x011f6940
// ===========================================================================
void FUN_011f6940(void)
{
    g_170ed5c = 0;
    byte b = 0;
    char c;
    do {
        c = (char)g_170eca9[b];
        int v = g_170eccc[b];
        g_170ed71[b] = (byte)c;
        g_170ed94[b] = v;
        b++;
    } while (c != 0);
    g_170ee14 = g_170ed4c;
}

// ===========================================================================
// @ 0x011f6980
// ===========================================================================
void FUN_011f6980(void)
{
    FUN_011f6370((int)&g_170ec98);
    FUN_011fcd10(&g_170ec98, &g_170ed60);
}

// ===========================================================================
// @ 0x011f69a0  rw::graphics::(anonymous)::rwg_D3D9GeneratePixelShader
// ===========================================================================
char* FUN_011f69a0(int desc)
{
    byte effects[20];
    byte maxIds[32];
    unsigned inputMask = 0;
    byte maxId = 0;
    unsigned i;

    for (i = 0; i < 0x11; ++i) {
        byte b = ((byte*)desc)[i];
        effects[i] = b;
        if (b != 0) {
            inputMask |= 1u << ((b + 5) & 0x1f);
            if (maxId < b)
                maxId = b;
        }
    }

    int* field34 = (int*)(desc + 0x34);
    unsigned inputMask2 = 0;
    unsigned currentMask = 0;
    unsigned texCount = 0;
    unsigned idx = 0;
    char* dest = g_psHlslBuffer;

    do {
        unsigned id = ((byte*)(desc + 0x11))[idx];
        maxIds[idx] = maxId;
        if (id == 0)
            break;
        unsigned off = id * 0x10;
        unsigned defInput = *(unsigned*)(g_psDefs + off);
        inputMask2 |= defInput;
        currentMask |= *(unsigned*)(g_psDefs + off + 4);
        if ((defInput & 0xffff0000) == 0) {
            unsigned ns = g_psSamplers[id];
            if (ns != 0) {
                unsigned k = 0;
                do {
                    if (effects[texCount + k] == 0) {
                        effects[texCount + k] = (byte)(maxId + 1);
                        inputMask |= 1u << ((maxId + 6) & 0x1f);
                        maxId++;
                    }
                    k++;
                } while (k < ns);
            }
        } else {
            unsigned n = g_psDefs[off + 2];
            unsigned k = maxId + 6;
            while (n != 0) {
                inputMask |= 1u << (k & 0x1f);
                k++;
                n--;
            }
            maxId = (byte)(maxId + g_psDefs[off + 2]);
        }
        void* fn = *(void**)(g_psDefs + off + 8);
        if (fn != 0) {
            typedef char* (__cdecl* Fn)(char*, unsigned, int, unsigned);
            dest = ((Fn)fn)(dest, id, *field34, texCount);
        }
        texCount += g_psSamplers[id];
        idx++;
        field34++;
    } while (idx < 0x20);

    dest = FUN_011f63b0(dest, inputMask2, maxId, inputMask);
    dest = FUN_011f64c0(dest, currentMask);
    dest = FUN_011f6550(dest, currentMask);
    dest = D3D9TextCopy(dest, g_psMainFmt);

    {
        byte* pEffect = (byte*)(desc + 0x11);
        byte* pMax = maxIds;
        texCount = 0;
        for (unsigned k = 0; k < 0x20; ++k) {
            if (*pEffect == 0)
                break;
            unsigned id = *pEffect;
            (void)*pMax;
            void* fn = *(void**)(g_psDefs + id * 0x10 + 0xc);
            if (fn != 0) {
                typedef char* (__cdecl* Fn)(char*, unsigned*);
                dest = ((Fn)fn)(dest, &id);
            }
            texCount += g_psSamplers[id];
            pEffect++;
            pMax++;
        }
    }

    dest = FUN_011f65e0(dest, currentMask);
    dest = D3D9TextCopy(dest, g_psRetFmt);
    *dest = 0;

    unsigned ver = 0;
    unsigned short sv = *(unsigned short*)((byte*)g_16f6568 + 0x12);
    if (sv != 0)
        ver = sv | 0xffff0000u;
    const char* profile = 0;
    switch (ver) {
    case 0xffff0101: profile = "ps_1_1"; break;
    case 0xffff0102: profile = "ps_1_2"; break;
    case 0xffff0103: profile = "ps_1_3"; break;
    case 0xffff0104: profile = "ps_1_4"; break;
    case 0xffff0200: profile = "ps_2_0"; break;
    case 0xffff0261: profile = "ps_2_a"; break;
    case 0xffff0300: profile = "ps_3_0"; break;
    default: break;
    }

    void* ppShader = 0;
    void* ppErr = 0;
    void* pConst = 0;
    int hr = FUN_011e1fd4(g_psHlslBuffer, (int)(dest - g_psHlslBuffer), 0, 0,
                          "main", profile, 2, &ppShader, &ppErr, 0);
    if (hr < 0)
        return 0;
    if (ppErr) {
        (*(PFN_Release)VSlot(ppErr, 8))(ppErr);
        ppErr = 0;
    }
    void* dev = g_d3d9Device;
    typedef void* (__stdcall* FnGetBuffer)(void*, void*);
    void* buf = ((FnGetBuffer)VSlot(ppShader, 0xc))(ppShader, &pConst);
    (*(PFN_SetPixelShader)VSlot(dev, 0x1a8))(dev, buf);
    (*(PFN_Release)VSlot(ppShader, 8))(ppShader);
    return (char*)ppShader;
}
