// Slice s006ee1f0 — SP::cEffectsRenderer ctor/dtor and dispatch helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE (SSE float code, EH frames, no cookie).
#include "types.h"

struct IRC { virtual void v0(); virtual void v1(); virtual void v2(); };

template<class T>
struct evec {
    T* mpBegin; T* mpEnd; T* mpCapacity; char mAllocator[4];
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void push_back(const T& v);
    void erase(T* first, T* last);
};

// Minimal view of the retail cEffectsRenderer object (size >= 0x388).
class cEffectsRenderer {
public:
    char pad0[0x224];
    evec<unsigned int> mVec224;   // +0x224
    char pad1[0x238 - 0x234];
    evec<unsigned int> mVec238;   // +0x238
    char pad2[0x260 - 0x248];
    void* mFrustumCull;           // +0x260
    char pad3[0x388 - 0x264];

    cEffectsRenderer();                                                     // 6ee1f0
    ~cEffectsRenderer();                                                    // 6ee4f0
    void AddActive(unsigned int id);                                        // 6ee940
    void DispatchWithAdditionalMaterial(int, int, int);                     // 6ee6f0
};

// A 2-byte-element bool-like vector used by 6eea80.
struct vbvec {
    unsigned short* mpBegin;
    unsigned short* mpEnd;
    void resize(unsigned int n);
};

// ---- 0x006ee1f0 (skeleton: full ctor) --------------------------------------
// @ 0x006ee1f0
cEffectsRenderer::cEffectsRenderer()
{
}

// ---- 0x006ee4f0 (skeleton: compiler-generated dtor) ------------------------
// @ 0x006ee4f0
cEffectsRenderer::~cEffectsRenderer()
{
}

// ---- 0x006ee940 (approximate) ----------------------------------------------
// @ 0x006ee940
void cEffectsRenderer::AddActive(unsigned int id)
{
    mVec238.push_back(id);
}

// ---- 0x006ee6f0 (skeleton: model dispatch loop) ----------------------------
// @ 0x006ee6f0
void cEffectsRenderer::DispatchWithAdditionalMaterial(int, int, int)
{
}

// ---- 0x006eea80 (approximate: vector-bool resize) --------------------------
// @ 0x006eea80
void vbvec::resize(unsigned int n)
{
    unsigned int sz = (unsigned int)((mpEnd - mpBegin) / 2);
    if (n > sz) {
        // Insert (n - sz) zero elements at the end (out-of-line helper).
        while (sz < n) { *mpEnd++ = 0; ++sz; }
    } else {
        mpEnd = mpBegin + n;
    }
}

// ---- 0x006eeb60 (skeleton: eastl vector<cTextureParticleSet> insert) --------
// @ 0x006eeb60
void vector_insert_stub(void* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
}
