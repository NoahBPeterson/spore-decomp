// slice s00a92450: EA::Swarm::cDistributeEffect parameter dispatch
//   0x00a92450 SetFloatParams(int param, const float* data, int count)
//   0x00a92920 SetIntParams  (int param, const int*   data, int count)
//   0x00a92b80 SetUnknownParam(int param, void* data)
// Retail member offsets follow the 2017 ModAPI cDistributeEffect layout, confirmed
// against the disassembly.  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>

struct V3 { float x, y, z; V3() {} V3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {} };

// eastl::vector<T, sp_vector_allocator> (20 bytes: begin/end/capacity + allocator).
template <class T> struct SpVec { T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAlloc[2]; };

struct cEffectParams;
struct cDistributeDescription;
struct cDistributeEffect;

// Element type stored in cDistributeEffect::mEffects (+0xd8).
struct IChildEffect {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool SetFloatParams(int param, const float* data, int count);   // +0x1c
    virtual bool SetIntParams(int param, const int* data, int count);       // +0x20
    virtual bool SetUnknownParam(int param, void* data);                    // +0x24
};

// cDistributeDescription: only the fields these three functions touch.
struct cDistributeDescription {
    uint32_t pad00[2];
    uint32_t mFlags;            // +0x08
    int      mDensity;          // +0x0c
    int      mEffectIndex;      // +0x10
    uint8_t  mSourceType;       // +0x14
    uint8_t  pad15[3];
    int      mSourceSize;       // +0x18
    uint32_t pad1c;
    float    mScale;            // +0x20
    uint8_t  pad24[0x130 - 0x24];
    float    mAltitudeRange[2]; // +0x130
    uint8_t  pad138[0x158 - 0x138];
    uint8_t  mOverrideSet;      // +0x158
};

// cIEffectsWorld: virtual slots 0x20 and 0x30 return helper objects.
struct cIEffectsWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void* v20();        // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void* v30();        // +0x30
};

// A cSurfaceRec-ish record: AddRef/Release at vtable +0/+4, count at +0xc, array at +0x10.
struct cSurfaceData {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04;
    uint32_t pad08;             // +0x08
    int      mCount;            // +0x0c
    struct Rec { int v0; int v1; int key; int pad; } mRecs[1];  // +0x10
};

struct cEffectParams {
    uint32_t mFloatParams[25];          // +0x00
    SpVec<float> mFloatParamStorage;    // +0x64
    uint32_t mIntParams[10];            // +0x78
    SpVec<int> mIntParamStorage;        // +0xa0
    void* mUnknownParams[9];            // +0xb4
    cEffectParams();                    // 0x007d55e0
    bool FloatStore(int index, const void* src, int count);  // 0x00a83fd0
    bool IntStore(int index, const void* src, int count);    // 0x00a84040
};

extern "C" void* __cdecl EAAllocate(unsigned int size, const char* name, int, int, int, int);  // 0x00f473a0
void mul_705290(V3* out, const V3* in);                                                        // 0x00705290

struct cDistributeEffect {
    uint32_t pad00[0x14 / 4];
    cDistributeDescription* mDesc;      // +0x14
    int      mCollectionIndex;          // +0x18
    cIEffectsWorld* mWorld;             // +0x1c
    void*    mGlobalParams;             // +0x20
    cEffectParams* mChildParams;        // +0x24
    uint32_t mFlags;                    // +0x28
    uint8_t  pad2c[0xa0 - 0x2c];
    float    mAltitudeRange[2];         // +0xa0
    uint8_t  pada8[0xd8 - 0xa8];
    SpVec<IChildEffect*> mEffects;      // +0xd8
    int      mOverrideID_hi;            // +0xec
    uint32_t mFormat0;                  // +0xf0
    uint32_t mFormat1;                  // +0xf4
    uint8_t  padf8[0x100 - 0xf8];
    V3       mSubdivOffset;             // +0x100
    V3       mSubdivScale;              // +0x10c
    void*    mField118;                 // +0x118
    uint8_t  pad11c[0x170 - 0x11c];
    V3       mVec170;                   // +0x170
    float    mField17C;                 // +0x17c
    float    mField180;                 // +0x180
    float    mField184;                 // +0x184
    float    mField188;                 // +0x188
    float    mField18C;                 // +0x18c
    int      mField190;                 // +0x190
    int      mField194;                 // +0x194

    void ClearSamples(int);             // 0x00a8d350
    void ReleaseRenderSet();            // 0x00a89490
    void CreateRenderSet();             // 0x00a91bc0

    bool SetFloatParams(int param, const float* data, int count);
    bool SetIntParams(int param, const int* data, int count);
    bool SetUnknownParam(int param, void* data);
};

// The world helper returned by cIEffectsWorld::v20() / v30().
typedef bool(__thiscall* FnSetShader)(void*, int, int, int, int, const float*);
typedef cDistributeDescription* (__thiscall* FnGetDesc)(void*, int, int, int);

// @ 0x00a92450
bool cDistributeEffect::SetFloatParams(int param, const float* data, int count) {
    if (param <= 0xe) {
        if (param != 0xe) {
            switch (param) {
            case 1: {
                if ((mFlags >> 0xd) & 1)
                    mField18C = data[0];
                break;
            }
            case 4: {
                mField180 = data[0];
                break;
            }
            case 5: {
                mVec170 = V3(data[0], data[1], data[2]);
                break;
            }
            }
        } else {
            if (mOverrideID_hi >= 0) {
                uint32_t flags = mDesc->mFlags;
                void* o = mWorld->v20();
                FnSetShader fn = (FnSetShader)(*(void***)o)[0x74 / 4];
                return fn(o, (~(int)(flags >> 8)) & 1, mOverrideID_hi, 0, count, data);
            }
        }
    } else {
        switch (param) {
        case 0x10: {
            cDistributeDescription* d = mDesc;
            if (!((d->mFlags >> 2) & 1))
                break;
            float v0 = d->mAltitudeRange[0];
            float v1 = d->mAltitudeRange[1];
            const float* p = data;
            int i = 0;
            if (count > 0) {
                do {
                    if (count == 2 || (int)p[2] == (int)d->mOverrideSet) {
                        v0 = p[0];
                        v1 = p[1];
                        break;
                    }
                    i += 3;
                    p += 3;
                } while (i < count);
            }
            if (mAltitudeRange[0] != v0 || !(mAltitudeRange[1] == v1)) {
                mAltitudeRange[0] = v0;
                mAltitudeRange[1] = v1;
                ClearSamples(0);
            }
            return true;
        }
        case 0x11: {
            mSubdivOffset = *(const V3*)data;
            float s = mDesc->mScale;
            mSubdivScale = V3(s, s, s);
            mul_705290(&mSubdivScale, (const V3*)(data + 3));
            return true;
        }
        case 0x14: {
            if ((mFlags >> 0xd) & 1) {
                if (count == 1) {
                    mField18C = data[0];
                    return true;
                }
                mField18C = 1.0f;
                float want = (float)mDesc->mOverrideSet;
                for (int i = 0; i < count; i += 2) {
                    if (data[i + 1] == want) {
                        mField18C = data[i];
                        break;
                    }
                }
                return true;
            }
            break;
        }
        case 0x101: {
            mField184 = data[2];
            mField188 = data[5];
            if (mDesc->mSourceType >= 1) {
                int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
                for (int i = 0; i < n; ++i)
                    mEffects.mpBegin[i]->SetFloatParams(param, data, count);
            }
            return true;
        }
        }
    }

    // default: propagate to children, then store in the child parameter block.
    int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        bool r = mEffects.mpBegin[i]->SetFloatParams(param, data, count);
        changed = r || changed;
    }
    if (mChildParams == 0) {
        cEffectParams* p = (cEffectParams*)EAAllocate(0xd8, "Swarm", 0, 0, 0, 0);
        if (p)
            new (p) cEffectParams();
        mChildParams = p;
    }
    mChildParams->FloatStore(param, data, count);
    return changed;
}

// @ 0x00a92920
bool cDistributeEffect::SetIntParams(int param, const int* data, int count) {
    switch (param) {
    case 0: {
        if (!((mDesc->mFlags >> 8) & 1))
            break;
        int v0 = -1, v1 = -1;
        int i = 0;
        if (count > 0) {
            do {
                if (count < 2 || data[i + 1] == (int)(uint8_t)mDesc->mOverrideSet) {
                    v0 = data[i];
                    v1 = 0;
                    break;
                }
                i += 2;
            } while (i < count);
        }
        if ((int)mFormat0 != v0 || (int)mFormat1 != v1) {
            uint32_t flags = mFlags;
            mFormat0 = v0;
            mFormat1 = v1;
            if ((flags & 1) && (((flags >> 0xd) & 1) || ((flags >> 0xc) & 1))) {
                ReleaseRenderSet();
                CreateRenderSet();
            }
        }
        return true;
    }
    case 1: {
        if (!((mDesc->mFlags >> 7) & 1))
            break;
        int v0 = -1, v1 = -1;
        int i = 0;
        if (count > 0) {
            do {
                if (count < 2 || data[i + 1] == (int)(uint8_t)mDesc->mOverrideSet) {
                    v0 = data[i];
                    v1 = 0;
                    break;
                }
                i += 2;
            } while (i < count);
        }
        if ((int)mFormat0 != v0 || (int)mFormat1 != v1) {
            uint32_t flags = mFlags;
            mFormat0 = v0;
            mFormat1 = v1;
            if ((flags & 1) && (((flags >> 0xd) & 1) || ((flags >> 0xc) & 1))) {
                ReleaseRenderSet();
                CreateRenderSet();
            }
        }
        return true;
    }
    case 4:
        mField190 = data[0];
        mField194 = data[1];
        return true;
    case 5:
        if (*(const uint8_t*)data & 7)
            ClearSamples(0);
        if (*(const uint8_t*)data & 8)
            mFlags |= 0x400;
        return true;
    }

    int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        bool r = mEffects.mpBegin[i]->SetIntParams(param, data, count);
        changed = r || changed;
    }
    if (mChildParams == 0) {
        cEffectParams* p = (cEffectParams*)EAAllocate(0xd8, "Swarm", 0, 0, 0, 0);
        if (p)
            new (p) cEffectParams();
        mChildParams = p;
    }
    mChildParams->IntStore(param, data, count);
    return changed;
}

// @ 0x00a92b80
bool cDistributeEffect::SetUnknownParam(int param, void* data) {
    switch (param) {
    case 3: {
        if (((mFlags >> 0xd) & 1) || ((mDesc->mFlags >> 0xe) & 1)) {
            cDistributeDescription* d = mDesc;
            if ((d->mFlags >> 0xe) & 1) {
                void* o = mWorld->v30();
                FnGetDesc fn = (FnGetDesc)(*(void***)o)[0x70 / 4];
                d = fn(o, d->mSourceType, d->mEffectIndex, mCollectionIndex);
            }
            int v0 = -1, v1 = -1;
            cSurfaceData* sd = (cSurfaceData*)data;
            int cnt = sd->mCount;
            volatile int want = d->mOverrideSet;
            int i = 0;
            if (cnt > 0) {
                do {
                    if (sd->mRecs[i].key == want) {
                        v0 = sd->mRecs[i].v0;
                        v1 = sd->mRecs[i].v1;
                        break;
                    }
                    ++i;
                } while (i < cnt);
            }
            if ((int)mFormat0 != v0 || (int)mFormat1 != v1) {
                uint32_t flags = mFlags;
                mFormat1 = v1;
                mFormat0 = v0;
                if ((flags & 1) && (((flags >> 0xd) & 1) || ((flags >> 0xc) & 1))) {
                    ReleaseRenderSet();
                    CreateRenderSet();
                }
            }
            if (!((mDesc->mFlags >> 0xe) & 1))
                return true;
        }
        break;
    }
    case 4: {
        mField118 = data;
        if (((cSurfaceData*)data)->mCount == 3)
            mFlags |= 0x10;
        else
            mFlags &= ~0x10;
        if (((cSurfaceData*)mField118)->mCount == 6) {
            mFlags |= 0x20;
            return true;
        }
        mFlags &= ~0x20;
        return true;
    }
    }

    int n = (int)(mEffects.mpEnd - mEffects.mpBegin);
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        bool r = mEffects.mpBegin[i]->SetUnknownParam(param, data);
        changed = r || changed;
    }
    if (mChildParams == 0) {
        cEffectParams* p = (cEffectParams*)EAAllocate(0xd8, "Swarm", 0, 0, 0, 0);
        if (p)
            new (p) cEffectParams();
        mChildParams = p;
    }
    cSurfaceData* sd = (cSurfaceData*)data;
    void* old = mChildParams->mUnknownParams[param];
    if (data != old) {
        if (data)
            sd->AddRef();
        mChildParams->mUnknownParams[param] = data;
        if (old)
            ((cSurfaceData*)old)->Release();
    }
    return changed;
}
