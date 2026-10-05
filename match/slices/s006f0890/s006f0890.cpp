// Slice s006f0890 — SP::cEffectsRenderer rendering helpers (all large).
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"

// ---- 0x006f0890 (skeleton) --------------------------------------------------
// @ 0x006f0890
void RenderHelper890(int, int, int)
{
}

// ---- 0x006f0b90 (skeleton: called with this = outer-0x18) -------------------
// @ 0x006f0b90
void RenderHelperB90(int, int, int)
{
}

// ---- 0x006f0fb0 (skeleton: cEffectsRenderer::CreateTextureParticleSet) -----
// @ 0x006f0fb0
void* CreateTextureParticleSet(void* pResource)
{
    (void)pResource;
    return 0;
}

// ---- 0x006f13a0 (approximate: RenderMainEffectsLayer) ----------------------
// @ 0x006f13a0
struct cEffectsRendererLayer {
    char pad0[0x2c];
    void* mpAt2c;
    char pad1[0x344 - 0x30];
    void* mpAt344;
    char pad2[0x34c - 0x348];
    void* mpAt34c;
    char pad3[0x354 - 0x350];
    void* mpAt354;

    void RenderMainEffectsLayer(unsigned int flags, unsigned int type,
                                unsigned int a, unsigned int b);
};

// @ 0x006f13a0
void cEffectsRendererLayer::RenderMainEffectsLayer(unsigned int flags, unsigned int type,
                                                   unsigned int, unsigned int b)
{
    if (flags == 0 || (flags & 0x6000000) != 0)
        flags |= 0xff;
    mpAt354 = (void*)b;
    switch (type) {
    case 3:
        break;
    default:
        break;
    }
    mpAt354 = 0;
}

// ---- 0x006f1510 (skeleton: eastl vector insert, stride 0xc0) ----------------
// @ 0x006f1510
void VectorInsertC0(void* self, int a, int b)
{
    (void)self; (void)a; (void)b;
}

// ---- 0x006f16c0 (skeleton: eastl vector push_back, stride 0xc0) -------------
// @ 0x006f16c0
void VectorPushBackC0(void* self)
{
    (void)self;
}
