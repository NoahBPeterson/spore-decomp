// Slice s0045bc20: skinning-influence bookkeeping helpers from the /Od editor module.
// Flags: /Od /Ob1 /MD /Gy /TP.
#include "types.h"

extern "C" void FUN_0045d790(void*);              // 0x45d790 (vector assign, masked)
extern "C" void* FUN_0045da80(void* dst, void* src); // 0x45da80
extern "C" void* _Unchecked_idl0(void* dst, void* a, void* b);

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
struct Skin {
    char      pad0[0x100];
    char      vec100[0x28];   // +0x100
    char      vec128[0x28];   // +0x128
    char      pad2[0x0c];
    char*     geomA;          // +0x114
    char*     geomAEnd;       // +0x118
    char      pad3[0x20];
    char*     geomB;          // +0x13c
    char*     geomBEnd;       // +0x140
    char      pad4[0x0c];
    char*     geomC;          // +0x128? (see code)
    void      Rebuild();
};

void Skin::Rebuild()
{
    char pad_d4[64];
    char pad_94[64];
    char pad_54[64];

    FUN_0045d790(vec100);
    FUN_0045d790(vec128);

    unsigned int i = 0;
    unsigned int n = (unsigned int)((geomAEnd - geomA) >> 6);
    for (; i < n; i = i + 1) {
        char* src = (char*)FUN_0045da80(pad_54, geomA + i * 0x40);
        char* dst = geomA + i * 0x40;
        for (int k = 0; k < 0x10; k = k + 1) {
            ((uint32_t*)dst)[k] = ((uint32_t*)src)[k];
        }
        char* src2 = (char*)FUN_0045da80(pad_94, geomB + i * 0x40);
        char* dst2 = geomB + i * 0x40;
        for (int k = 0; k < 0x10; k = k + 1) {
            ((uint32_t*)dst2)[k] = ((uint32_t*)src2)[k];
        }
    }

    unsigned int j = 0;
    unsigned int m = (unsigned int)((geomAEnd - geomA) >> 6);
    for (; j < m; j = j + 1) {
        if (*(int*)((char*)this + 0xec + j * 4) >= 0) {
            int idx = *(int*)((char*)this + 0xec + j * 4);
            char* src = (char*)_Unchecked_idl0(pad_d4, geomA + j * 0x40, geomB + idx * 0x40);
            char* dst = geomA + j * 0x40;
            for (int k = 0; k < 0x10; k = k + 1) {
                ((uint32_t*)dst)[k] = ((uint32_t*)src)[k];
            }
        }
    }
    return;
}
