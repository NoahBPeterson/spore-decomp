// src/game/Swarm/SurfaceDecalManager.cpp -- migrated from slice(s) s00a7f2e0 by tools/migrate/rewrite.py
// Object file: Swarm/SurfaceDecalManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_00539440(void* a, void* b);   // EA::Swarm::normalized

// ---- items of slice s00a7f2e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00539440(void* a, void* b);   // EA::Swarm::normalized
struct ObjFE20 {
    virtual char v10(void*, void*, float*, int, int, int);   // slot 0x10
};
struct Owner {
    char  pad0[0x10];
    ObjFE20* p10;     // +0x10
    char  pad1[0x5c];
    float f70;        // +0x70
    void  FUN_00a7fe20(void* arg);
};
// ---- items of slice s00a7f2e0 end

// @ 0x00a7fe20
void Owner::FUN_00a7fe20(void* arg)
{
    char* p = (arg != 0) ? ((char*)arg - 8) : 0;

    unsigned short w = *(unsigned short*)(p + 0xa);
    if (*(unsigned short*)(p + 0xa0) == w)
        return;

    *(unsigned short*)(p + 0xa0) = w;
    *(unsigned int*)(p + 0x80) = *(unsigned int*)(p + 0x1c);
    *(unsigned int*)(p + 0x84) = *(unsigned int*)(p + 0x20);
    *(unsigned int*)(p + 0x88) = *(unsigned int*)(p + 0x24);
    *(unsigned int*)(p + 0x8c) = *(unsigned int*)(p + 0x28);
    *(unsigned int*)(p + 0x90) = *(unsigned int*)(p + 0x2c);
    *(unsigned int*)(p + 0x94) = *(unsigned int*)(p + 0x30);

    float* pf = (float*)(p + 0x74);
    if (p10 == 0) {
        *pf = *(float*)(p + 0xc);
        *(unsigned int*)(p + 0x78) = *(unsigned int*)(p + 0x10);
        *(unsigned int*)(p + 0x7c) = *(unsigned int*)(p + 0x14);
        *(unsigned int*)(p + 0x7c) = 0;
    } else {
        float fVar3 = this->f70;
        float buf[3];
        buf[0] = 0.0f; buf[1] = 0.0f; buf[2] = 0.0f;
        int f70bits = *(int*)&fVar3;
        char cVar5 = p10->v10(p + 0xc, pf, buf, 0, f70bits, 0);
        if (cVar5 != 0) {
            float out[3];
            float a0 = buf[0];
            float a1 = fVar3;
            float a2 = 0.0f;
            float left  = a0 * *(float*)(p + 0x8c) + (*(float*)(p + 0x94) * a1 + *(float*)(p + 0x90) * a2);
            float right = (*(float*)(p + 0x88) * a1 + *(float*)(p + 0x84) * a2) + *(float*)(p + 0x80) * a0;
            float fabsL = left < 0.0f ? -left : left;
            float fabsR = right < 0.0f ? -right : right;
            float* puVar6;
            if (fabsL <= fabsR) {
                out[0] = *(float*)(p + 0x90) * a1 - *(float*)(p + 0x94) * a2;
                puVar6 = (float*)FUN_00539440(buf, out);
                *(float*)(p + 0x80) = puVar6[0];
                *(float*)(p + 0x84) = puVar6[1];
                *(float*)(p + 0x88) = puVar6[2];
                *(float*)(p + 0x8c) = *(float*)(p + 0x88) * a2 - *(float*)(p + 0x84) * a1;
                *(float*)(p + 0x90) = *(float*)(p + 0x80) * a1 - *(float*)(p + 0x88) * a0;
                *(float*)(p + 0x94) = *(float*)(p + 0x84) * a0 - *(float*)(p + 0x80) * a2;
            } else {
                out[0] = *(float*)(p + 0x88) * a2 - *(float*)(p + 0x84) * a1;
                puVar6 = (float*)FUN_00539440(buf, out);
                *(float*)(p + 0x8c) = puVar6[0];
                *(float*)(p + 0x90) = puVar6[1];
                *(float*)(p + 0x94) = puVar6[2];
                *(float*)(p + 0x80) = *(float*)(p + 0x90) * a1 - *(float*)(p + 0x94) * a2;
                *(float*)(p + 0x84) = *(float*)(p + 0x94) * a0 - *(float*)(p + 0x8c) * a1;
                *(float*)(p + 0x88) = *(float*)(p + 0x8c) * a2 - *(float*)(p + 0x90) * a0;
            }
            float fVar2 = *(float*)(p + 0x70);
            *pf = fVar2 * a0 + *pf;
            *(float*)(p + 0x78) = fVar2 * a2 + *(float*)(p + 0x78);
            *(float*)(p + 0x7c) = fVar2 * a1 + *(float*)(p + 0x7c);
        }
    }

    int iv = *(int*)(p + 0x98);
    if (iv != 0) {
        if (*pf < *(float*)(iv + 0x28))
            *(float*)(iv + 0x28) = *pf;
        if (*(float*)(iv + 0x34) < *pf)
            *(float*)(iv + 0x34) = *pf;
        if (*(float*)(p + 0x78) < *(float*)(iv + 0x2c))
            *(float*)(iv + 0x2c) = *(float*)(p + 0x78);
        if (*(float*)(iv + 0x38) < *(float*)(p + 0x78))
            *(float*)(iv + 0x38) = *(float*)(p + 0x78);
        if (*(float*)(p + 0x7c) < *(float*)(iv + 0x30))
            *(float*)(iv + 0x30) = *(float*)(p + 0x7c);
        if (*(float*)(iv + 0x3c) < *(float*)(p + 0x7c))
            *(float*)(iv + 0x3c) = *(float*)(p + 0x7c);
    }
}
