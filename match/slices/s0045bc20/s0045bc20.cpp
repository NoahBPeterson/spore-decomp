// Slice s0045bc20: skinning-influence bookkeeping helpers from the /Od editor module.
// Flags: /Od /Ob1 /MD /Gy /TP.
#include "types.h"

extern "C" void FUN_0045d790(void*);              // 0x45d790 (vector assign, masked)
extern "C" void* FUN_0045da80(void* dst, void* src); // 0x45da80
extern "C" void* _Unchecked_idl0(void* dst, void* a, void* b); // 0x0045daa0

// =====================================================================
// @ 0x45bc20  free-list unlink (reverse the free chain from `index`)
// =====================================================================
struct FreeList {
    char  pad[0xec];
    int*  next;
    void  Unlink(int index);
};

void FreeList::Unlink(int index)
{
    int prev = -1;
    int cur = index;
    while (cur != -1) {
        int nxt = next[cur];
        next[cur] = prev;
        prev = cur;
        cur = nxt;
    }
    return;
}

// =====================================================================
// @ 0x45bc80  compact bone influences: fold duplicate joint slots into their weight
// =====================================================================
struct Infl {
    int16_t j0;
    int16_t j1;
    int16_t j2;
    int16_t j3;
};

struct Weights {
    float w0;
    float w1;
    float w2;
    float w3;
};

struct Skel {
    char   pad0[0x74];
    Infl*  influences;    // +0x74
    Infl*  inflEnd;       // +0x78
    char   pad1[0x0c];
    Weights* weights;     // +0x88
    void   Compact();
};

void Skel::Compact()
{
    Infl* in = influences;
    Weights* wt = weights;
    for (unsigned int i = 0; i < (unsigned int)(inflEnd - in); i = i + 1) {
        Infl* r = &in[i];
        Weights* w = &wt[i];
        if (r->j3 == r->j0) {
            w->w0 = w->w0 + w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        } else if (r->j3 == r->j1) {
            w->w1 = w->w1 + w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        } else if (r->j3 == r->j2) {
            w->w2 = w->w2 + w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        }

        if (r->j2 == r->j0) {
            w->w0 = w->w0 + w->w2;
            r->j2 = r->j3;
            w->w2 = w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        } else if (r->j2 == r->j1) {
            w->w1 = w->w1 + w->w2;
            r->j2 = r->j3;
            w->w2 = w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        }

        if (r->j1 == r->j0) {
            w->w0 = w->w0 + w->w1;
            r->j1 = r->j2;
            w->w1 = w->w2;
            r->j2 = r->j3;
            w->w2 = w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        }
    }
    return;
}

// =====================================================================
// @ 0x45c0f0  rebuild skinning arrays into local copies + remap indices
// =====================================================================
// 0x14-byte vector slot holding 0x40-byte elements (three pointers + allocator).
struct SkinVec {
    char*  mpBegin;                        // +0x00
    char*  mpEnd;                          // +0x04
    char*  mpCapacity;                     // +0x08
    void*  mpAlloc;                        // +0x0c

    void Assign(const SkinVec& src);       // 0x0045d790
};

struct Skin {
    char     pad00[0xec];   // +0x000
    int*     pIdx;          // +0x0ec  element -> source element index (-1 = keep)
    char     padF0[0x10];   // +0x0f0
    SkinVec  v100;          // +0x100
    SkinVec  v114;          // +0x114  live position array
    SkinVec  v128;          // +0x128
    SkinVec  v13c;          // +0x13c  live normal array

    void Rebuild();
};

// @ 0x45c0f0
void Skin::Rebuild()
{
    char pad_d4[64];
    char pad_94[64];
    char pad_54[64];

    v114.Assign(v100);
    v13c.Assign(v128);

    int i = 0;
    int n = (int)((v114.mpEnd - v114.mpBegin) >> 6);
    for (; i < n; i = i + 1) {
        char* src = (char*)FUN_0045da80(pad_54, v114.mpBegin + i * 0x40);
        char* dst = v114.mpBegin + i * 0x40;
        for (int k = 0; k < 0x10; k = k + 1) {
            ((uint32_t*)dst)[k] = ((uint32_t*)src)[k];
        }
        char* src2 = (char*)FUN_0045da80(pad_94, v13c.mpBegin + i * 0x40);
        char* dst2 = v13c.mpBegin + i * 0x40;
        for (int k = 0; k < 0x10; k = k + 1) {
            ((uint32_t*)dst2)[k] = ((uint32_t*)src2)[k];
        }
    }

    int j = 0;
    int m = (int)((v128.mpEnd - v128.mpBegin) >> 6);
    for (; j < m; j = j + 1) {
        if (pIdx[j] >= 0) {
            int idx = pIdx[j];
            char* src = (char*)_Unchecked_idl0(pad_d4, v128.mpBegin + j * 0x40,
                                               v13c.mpBegin + idx * 0x40);
            char* dst = v128.mpBegin + j * 0x40;
            for (int k = 0; k < 0x10; k = k + 1) {
                ((uint32_t*)dst)[k] = ((uint32_t*)src)[k];
            }
        }
    }
    return;
}
