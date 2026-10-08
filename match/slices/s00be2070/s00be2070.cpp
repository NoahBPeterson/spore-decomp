// Slice s00be2070: F_be2440, a 14-slot connectivity scorer (14x14 adjacency grid, ids[14]).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <string.h>
#include <xmmintrin.h>

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();

struct PFIdx { uint32_t pad; int GetFileCount(); bool F_bfc600(); };
struct Part {
    uint32_t pad0[0x120 / 4 - 1];
    PFIdx idx;                      // +0x120
    uint32_t pad1[(0x28c - 0x124) / 4];
    uint32_t mF;                    // +0x28c
    int mCount;                     // +0x290
    uint32_t mE, mC, mD;            // +0x294.. +0x29c
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual uint32_t GetId();       // slot 8 (+0x20)
    void F_bcc6e0(bool b);
};
struct Wrap {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual Part* Query(uint32_t id);   // slot 3 (+0xc)
};
struct Item { Wrap* F_fcc210(); };
struct Table { uint32_t pad; Item* F_af9ff0(int i); };
struct Slot {
    uint32_t pad0[0x20 / 4];
    int mKind;                      // +0x20
    uint8_t mFlag;                  // +0x24
    uint8_t pad1[3];
    uint32_t mVal;                  // +0x28
    int mCount;                     // +0x2c
    int mIndex;                     // +0x30
    uint32_t mId;                   // +0x34
};
struct Obj3;
struct Obj2 {
    uint32_t pad0[0x2c / 4];
    int mScore;                     // +0x2c
    Slot* F_ff07a0(int i);
    bool F_ff0330(int a, int b);
    void F_ff08b0(float f, Obj3* o);
};
struct Obj1 {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f)
    virtual void g0(); virtual void g1(); virtual void g2();
    virtual char* GetGrid();        // slot 27 (+0x6c)
    uint32_t pad0[(0x304 - 4) / 4];
    float mResult;                  // +0x304
    uint32_t pad1[(0x3ec - 0x308) / 4];
    Table tbl;                      // +0x3ec
    uint32_t pad2[(0x664 - 0x3f0) / 4];
    int mScore;                     // +0x664
    int mN1;                        // +0x668
    int mN2;                        // +0x66c
    uint32_t pad3[2];
    int mScore2;                    // +0x678
    void F_be0020();
};

enum { kA = 0x18ea1eb, kB = 0x18eb106, kC = 0x18ea2cc, kD = 0x1a56aba };

// @ 0x00be2440
void F_be2440(Obj1* a1, Obj2* a2, Obj3* a3)
{
    uint32_t D[14], C[14], E[14], F[14], ids[14];
    bool ok[14];
    int i0;
    for (i0 = 0; i0 < 14; ++i0) D[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) C[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) E[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) F[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) ok[i0] = false;
    for (i0 = 0; i0 < 14; ++i0) ids[i0] = 0;
    bool grid[14][14];
    memset(grid, 0, sizeof(grid));

    if (a1) {
        if (!a1->GetGrid()) return;
        for (uint32_t row = 0, off = 0; off < 0xc4; off += 14, ++row) {
            Item* it = a1->tbl.F_af9ff0(row);
            if (!it) continue;
            Wrap* w = it->F_fcc210();
            if (!w) continue;
            Part* p = w->Query(0xe9cb8ba);
            if (!p) continue;
            if (p->idx.GetFileCount() == 2) continue;
            if (p->mCount > 0) continue;
            if (p->idx.F_bfc600()) continue;
            ids[row] = p->GetId();
            for (uint32_t j = 0; j < 14; ++j) {
                const char* p = a1->GetGrid() + off;
                if (p[j + 0x274])
                    ((bool*)grid)[off + j] = true;
            }
        }
    } else {
        if (!a2) return;
        for (uint32_t i = 0; i < 14; ++i) {
            Slot* s = a2->F_ff07a0(i);
            if (!s) continue;
            int k = s->mIndex;
            if (s->mKind == 2) continue;
            if (s->mCount <= 0) continue;
            ids[k] = s->mId;
            for (uint32_t j = 0; j < 14; ++j) {
                if (a2->F_ff0330(k, j))
                    grid[k][j] = true;
            }
        }
    }

    for (int i = 0; i < 14; ++i)
        if (ids[i] == kA) ok[i] = true;

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < 14; ++i) {
            if (ids[i] != 0 && !ok[i]) {
                for (int j = 0; j < 14; ++j) {
                    if (ids[j] != 0 && ok[j] && grid[i][j]) {
                        ok[i] = true;
                        changed = true;
                    }
                }
            }
        }
    } while (changed);

    int n1 = 0, score = 0, n2 = 0;
    int i, j;
    for (i = 0; i < 14; ++i) {
        uint32_t id = ids[i];
        if (id != 0 && ok[i]) {
            if (id == kD) { C[i] += 1; n1 += 1; }
            if (id == kC) { D[i] += 1; n2 += 1; }
            for (j = 0; j < 14; ++j) {
                uint32_t o = ids[j];
                if (i != j && o != 0) {
                    if (id == kC && (o == kA || o == kB) && grid[i][j]) { E[i] += 400; score += 400; }
                    if (id == kD && (o == kA || o == kB) && grid[i][j]) { C[i]++; n1++; }
                    if (id == kC && o == kD && grid[i][j]) { D[i]++; n2++; }
                }
            }
        }
    }

    float res = (float)(n1 - n2 + 5) * 10.0f;
    float lo = 0.0f, hi = 100.0f;
    __asm {
        movss xmm0, res
        maxss xmm0, lo
        minss xmm0, hi
        movss res, xmm0
    }

    if (a1) {
        for (int i = 0; i < 14; ++i) {
            Item* it = a1->tbl.F_af9ff0(i);
            if (!it) continue;
            Wrap* w = it->F_fcc210();
            if (!w) continue;
            Part* p = w->Query(0xe9cb8ba);
            if (!p) continue;
            p->F_bcc6e0(ok[i]);
            p->mF = F[i]; p->mE = E[i]; p->mC = C[i]; p->mD = D[i];
        }
    }
    if (a2) {
        for (int i = 0; i < 14; ++i) {
            Slot* s = a2->F_ff07a0(i);
            if (s) { s->mFlag = ok[s->mIndex]; s->mVal = F[s->mIndex]; }
        }
    }
    if (a1) {
        a1->mResult = res;
        a1->mScore = score; a1->mN1 = n1; a1->mN2 = n2; a1->mScore2 = score;
        a1->F_be0020();
    }
    if (a2) {
        a2->F_ff08b0(res, a3);
        a2->mScore = score;
    }
}
