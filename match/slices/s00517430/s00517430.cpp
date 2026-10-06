// w1g1 slice s00517430 -- nSPSkinner::cPaintRenderJob::RenderInternal (3772 bytes).
// Complete source (every path of the original); not byte-exact (/Od frame layout unresolved).
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

struct Raster;

// ---- SP::cTextureInstance: +0 raster, +4 flags (bit0 = resident), +8 atomic refcount --------
struct cTextureInstance {
    Raster* mRaster;
    unsigned char mFlags;
    unsigned char pad5[3];
    volatile long mRefCount;
};

// ---- resource manager (FUN_0067dd60): vtable +0x20 Get(key,a,b), +0x34 Load(tex) ------------
struct ResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual cTextureInstance* Get(unsigned key, int a, int b);      // +0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Load(cTextureInstance* t);                          // +0x34
};
ResMgr* GetResMgr();                                // 0067dd60
void __fastcall AtomicRefCounted_Release(cTextureInstance* t);      // 00402420 (thiscall)

// ---- rw graphics pieces ---------------------------------------------------------------------
struct VertexDescriptor {};
struct VBDesc { char pad[0xf]; unsigned char stride; };    // [vb->+0]->+0xf = vertex stride
struct VertexBuffer {
    VBDesc* desc;                                   // +0
    void* d3dvb;                                    // +4
    unsigned count;                                 // +8 (vertices already consumed / offset)
    unsigned capacity;                              // +0xc
    void* Lock(int flags, int offsetBytes, int sizeBytes);     // 011f3620
    void Unlock();                                  // 011f36a0
};

struct IDevice;
struct IDeviceVtbl {
    void* pad0[81];
    long (__stdcall* DrawPrimitive)(IDevice*, int type, unsigned start, unsigned primCount);   // +0x144
    void* pad1[18];
    long (__stdcall* SetStreamSource)(IDevice*, unsigned stream, void* vb, unsigned off, unsigned stride); // +0x190
};
struct IDevice { const IDeviceVtbl* vtbl; };

struct StreamSlot { void* vb; unsigned off; unsigned stride; };

struct ShaderObj { char pad[0x14]; void (__cdecl* fn14)(int); };

extern const VertexDescriptor* g_vertexDescriptor;      // 016f65a0
extern unsigned g_softStateUpdated;                     // 016f9110
extern IDevice* g_d3d9Device;                           // 016f89d0
extern StreamSlot g_streams[];                          // 016f9138
extern ShaderObj* g_shader;                             // 016f6568

int  __cdecl VertexDescriptor_AreEqual(const VertexDescriptor* a, const VertexDescriptor* b);   // 011f2e70
void __fastcall ApplyVertexDescriptor(const VertexDescriptor* vd);                              // 011f2bc0 (thiscall)
void __cdecl D3D9Sync();                                // 011f21a0

struct CompiledState { void Dispatch(); };              // 011ee580

struct Vec4 {
    float x, y, z, w;
    Vec4(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
};

struct cRTTBuffer {
    void* mCamera;                                  // +0
    unsigned material;                              // +4
    unsigned writemask;                             // +8
    Vec4 params[3];                                 // +0xc
    Raster* textures[2];                            // +0x3c
    int maxparam;                                   // +0x44
    int maxtexture;                                 // +0x48
    unsigned vtxcount;                              // +0x4c
    char pad50[0x14];
    void Begin();                                   // 00528e90
    void SetWriteMask(int a, int b, int c, int d);  // 00529280 (StateBits::Set)
    CompiledState* PrepareState();                  // 005293a0
    void BeginDraw();                               // 00529bf0
    void SetParam(int i, const Vec4& v)
    {
        if (maxparam <= i)
            maxparam = i + 1;
        params[i] = v;
    }
    void SetTexture(int i, Raster* r)
    {
        if (r != 0 && maxtexture <= i)
            maxtexture = i + 1;
        textures[i] = r;
    }
};

struct RenderState {
    char pad0[0x10];
    cRTTBuffer* rttA;                               // +0x10
    cRTTBuffer* rttB;                               // +0x14
    char pad18[0x1c];
    const VertexDescriptor* vdesc;                  // +0x34
    VertexBuffer* vb;                               // +0x38
};

struct RenderMgr {                                  // FUN_00401080 result
    char pad0[0xc];
    RenderState* state;                             // +0xc
};
RenderMgr* GetRenderMgr();                          // 00401080

namespace {
void __cdecl FastMemCopy(void* dst, const void* src, unsigned bytes);   // 00516ac0
}

namespace nSPSkinner {

struct cPaintBatch {                                // cPaintList::Batch, size 0x18
    int mFirstVertex;                               // +0
    int mVertices;                                  // +4
    unsigned char mBlendModes[3];                   // +8
    unsigned char mIdentityPass;                    // +0xb
    cTextureInstance* mBrush[3];                    // +0xc
};

struct BatchVec {                                   // eastl::vector<Batch> payload at list+0x14
    cPaintBatch* mpBegin;
    cPaintBatch* mpEnd;
    cPaintBatch* begin() { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cPaintList {
    char* mVerticesBegin;                           // +0 (28-byte vertices)
    char pad4[0x10];
    BatchVec mBatches;                              // +0x14
};

static inline Raster* ResolveRaster(cTextureInstance* t)
{
    if (!(t->mFlags & 1))
        GetResMgr()->Load(t);
    return t->mRaster;
}

class cPaintRenderJob {
public:
    char padBase[0x10];
    cPaintList* mPaintList;                         // +0x10
    int mStage;                                     // +0x14
    int mVBStart;                                   // +0x18
    int mVBCount;                                   // +0x1c
    int mVBBatches;                                 // +0x20
    int mBatchIdx;                                  // +0x24
    int mLockFailCount;                             // +0x28
    bool mSkipIdentity;                             // +0x2c
    bool RenderInternal();                          // 0x00517430
};

// @ 0x00517430
bool cPaintRenderJob::RenderInternal()
{
    cPaintList* list;
    RenderState* rs;
    rs = GetRenderMgr()->state;
    list = mPaintList;
    if (!((unsigned)mBatchIdx < (unsigned)list->mBatches.size()))
        return true;

    if (mStage == 0) {
        int total = 0;
        cPaintBatch* p = list->mBatches.begin() + mBatchIdx;
        int n = list->mBatches.size() - mBatchIdx;
        while (n > 0) {
            int nv = p->mVertices;
            if (total + nv > 0x8ca0)
                break;
            total += nv;
            n--;
            p++;
        }
        mVBBatches = (int)(p - (list->mBatches.begin() + mBatchIdx));
        int first = list->mBatches.begin()[mBatchIdx].mFirstVertex;
        mVBStart = first & ~1;
        mVBCount = (first & 1) + total;

        VertexBuffer* vb = rs->vb;
        int count = mVBCount;
        if (count == 0)
            count = vb->capacity;
        unsigned char stride = vb->desc->stride;
        void* dst = vb->Lock(6, vb->count * stride, stride * count);
        VertexBuffer* locked = 0;
        if (dst)
            locked = vb;
        if (locked) {
            mLockFailCount = 0;
            FastMemCopy(dst, list->mVerticesBegin + mVBStart * 0x1c, mVBCount * 0x1c);
            rs->vb->Unlock();
        } else {
            mLockFailCount = mLockFailCount + 1;
            if (mLockFailCount > 5)
                return true;
            return false;
        }
    } else {
        const VertexDescriptor* vd = rs->vdesc;
        if (!g_vertexDescriptor || !VertexDescriptor_AreEqual(g_vertexDescriptor, vd))
            g_softStateUpdated |= 0x100000;
        g_vertexDescriptor = vd;
        ApplyVertexDescriptor(g_vertexDescriptor);

        IDevice* dev = g_d3d9Device;
        StreamSlot* slots = g_streams;
        void* vbp = rs->vb->d3dvb;
        unsigned vcount = rs->vb->count;
        dev->vtbl->SetStreamSource(dev, 0, vbp, vcount * 0x1c, 0x1c);
        slots[0].vb = vbp;
        slots[0].off = rs->vb->count * 0x1c;
        slots[0].stride = 0x1c;
        for (int s = 1; s < 4; s++) {
            if (slots[s].vb != 0) {
                dev->vtbl->SetStreamSource(dev, s, 0, 0, 0);
                slots[s].vb = 0;
                slots[s].off = 0;
                slots[s].stride = 0;
            }
        }

        int st = mStage - 1;
        cRTTBuffer* buf;
        if (st == 0)
            buf = rs->rttA;
        else
            buf = rs->rttB;
        buf->Begin();
        if (st == 0)
            buf->SetWriteMask(1, 1, 1, 0);
        else if (st == 1)
            buf->SetWriteMask(1, 0, 0, 0);
        else if (st == 2)
            buf->SetWriteMask(0, 0, 1, 0);
        else
            buf->SetWriteMask(0, 1, 0, 0);

        cTextureInstance* defTex = GetResMgr()->Get(0xbd77bb98, 0, 0);
        if (defTex)
            _InterlockedExchangeAdd(&defTex->mRefCount, 1);

        cPaintBatch* cur = list->mBatches.begin() + mBatchIdx;
        cPaintBatch* end = cur + mVBBatches;
        for (; cur < end; cur++) {
            cTextureInstance* dt = defTex;
            if (!(dt->mFlags & 1))
                GetResMgr()->Load(dt);
            Raster* tex0 = dt->mRaster;
            Raster* tex1 = 0;

            if (st == 0 && cur->mIdentityPass != 1) {
                if (cur->mBrush[0])
                    tex0 = ResolveRaster(cur->mBrush[0]);
                if (tex0) {
                    switch (cur->mBlendModes[0]) {
                    case 2: buf->material = 0x262bf86f; break;
                    case 3: buf->material = 0x28fedd44; break;
                    case 4: buf->material = 0x7d02141c; break;
                    case 5: buf->material = 0xd1663766; break;
                    default: buf->material = 0xae08f862;
                    }
                }
            } else if (st == 1) {
                if (cur->mBrush[1])
                    tex0 = ResolveRaster(cur->mBrush[1]);
                if (cur->mBrush[2])
                    tex1 = ResolveRaster(cur->mBrush[2]);
                if (tex1 == 0) {
                    if (tex0) {
                        switch (cur->mBlendModes[1]) {
                        case 2: buf->material = 0xb9ac2ae2; break;
                        case 3: buf->material = 0xc6ced15d; break;
                        case 4: buf->material = 0x4db46b47; break;
                        case 5: buf->material = 0x1b675065; break;
                        default: buf->material = 0x5ce94d87;
                        }
                    }
                } else {
                    switch (cur->mBlendModes[1]) {
                    case 2: buf->material = 0x9a88e7b3; break;
                    case 3: buf->material = 0x9d5bcc90; break;
                    case 4: buf->material = 0xf605e298; break;
                    case 5: buf->material = 0x059c333a; break;
                    default: buf->material = 0x408e6ca6;
                    }
                    buf->SetParam(0, Vec4(1.0f, 0.0f, 0.0f, 0.0f));
                }
            } else if (st == 2) {
                if (cur->mBrush[1])
                    tex0 = ResolveRaster(cur->mBrush[1]);
                if (cur->mBrush[2])
                    tex1 = ResolveRaster(cur->mBrush[2]);
                if (tex1 == 0) {
                    if (tex0) {
                        switch (cur->mBlendModes[2]) {
                        case 2: buf->material = 0x9ecf875f; break;
                        case 3: buf->material = 0x81f1ebb4; break;
                        case 4: buf->material = 0x162c01ec; break;
                        case 5: buf->material = 0xb6fb2576; break;
                        default: buf->material = 0x1b481432;
                        }
                    }
                } else {
                    switch (cur->mBlendModes[2]) {
                    case 2: buf->material = 0x9a88e7b3; break;
                    case 3: buf->material = 0x9d5bcc90; break;
                    case 4: buf->material = 0xf605e298; break;
                    case 5: buf->material = 0x059c333a; break;
                    default: buf->material = 0x408e6ca6;
                    }
                    buf->SetParam(0, Vec4(0.0f, 0.0f, 1.0f, 0.0f));
                }
            } else if (st == 3 && cur->mIdentityPass != 0) {
                if (cur->mBrush[0])
                    tex0 = ResolveRaster(cur->mBrush[0]);
                if (tex0) {
                    if (cur->mIdentityPass == 1) {
                        switch (cur->mBlendModes[0]) {
                        case 2: buf->material = 0x262bf86f; break;
                        case 3: buf->material = 0x28fedd44; break;
                        case 4: buf->material = 0x7d02141c; break;
                        case 5: buf->material = 0xd1663766; break;
                        default: buf->material = 0xae08f862;
                        }
                    } else {
                        buf->material = 0x82d83269;
                    }
                }
            } else {
                tex0 = 0;
            }

            if (tex0) {
                int firstVert = cur->mFirstVertex - mVBStart;
                unsigned verts = cur->mVertices;
                cPaintBatch* nx = cur;
                for (;;) {
                    cPaintBatch* nn = nx + 1;
                    if (!(nn < end))
                        break;
                    if (nx->mBrush[0] != nn->mBrush[0] || nx->mBrush[1] != nn->mBrush[1] ||
                        nx->mBrush[2] != nn->mBrush[2])
                        break;
                    if (nx->mBlendModes[st] != nn->mBlendModes[st])
                        break;
                    if (st == 0 && nn->mIdentityPass == 1)
                        break;
                    if (st == 3 && nn->mIdentityPass == 0)
                        break;
                    verts += nn->mVertices;
                    nx = nn;
                }
                cur = nx;
                buf->SetTexture(0, tex0);
                buf->SetTexture(1, tex1);
                CompiledState* cs = buf->PrepareState();
                cs->Dispatch();
                D3D9Sync();
                if (g_vertexDescriptor != rs->vdesc) {
                    const VertexDescriptor* vd2 = rs->vdesc;
                    if (!g_vertexDescriptor || !VertexDescriptor_AreEqual(g_vertexDescriptor, vd2))
                        g_softStateUpdated |= 0x100000;
                    g_vertexDescriptor = vd2;
                    ApplyVertexDescriptor(g_vertexDescriptor);
                }
                void (__cdecl* fn)(int) = g_shader->fn14;
                fn(0);
                g_softStateUpdated = 0;
                if (verts != 0 && verts <= rs->vb->capacity)
                    dev->vtbl->DrawPrimitive(dev, 4, firstVert, verts / 3);
            }
        }
        buf->SetWriteMask(1, 1, 1, 1);
        buf->BeginDraw();
        if (defTex)
            AtomicRefCounted_Release(defTex);
    }

    mStage = mStage + 1;
    if (mStage == 4 && mSkipIdentity)
        mStage = mStage + 1;
    if (mStage > 4) {
        mStage = 0;
        mBatchIdx = mBatchIdx + mVBBatches;
        if (mBatchIdx == list->mBatches.size())
            return true;
    }
    return false;
}

} // namespace nSPSkinner
