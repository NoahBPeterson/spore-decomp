// src/game/SPBake/SPSkinPaintClearDescription.cpp -- migrated from slice(s) s0052c230 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinPaintClearDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cICommand.h"

// unnamed retail callees and globals (address in the comment)
extern float kDefaultHairAngle;     // 0x015e0574

// ---- items of slice s0052c230 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {    // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3(float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};
extern float kDefaultHairAngle;     // 0x015e0574
namespace EA {
struct RefCountTemplateInt {        // EA::RefCountTemplate<int>
    virtual ~RefCountTemplateInt();
    int mRefCount;                  // +0x04
    RefCountTemplateInt() : mRefCount(0) {}
};
}
namespace EA {
namespace Swarm {
struct cDescription_s0052_c230 : RefCountTemplateInt {
    cDescription_s0052_c230() {}
    virtual ~cDescription_s0052_c230();
};  // namespace Swarm
}
}
struct cSPSkinPaintClearDescription : EA::Swarm::cDescription_s0052_c230 {   // 0x70
    int mDiffuseUserColor;          // +0x08
    Vector3 mDiffuse;               // +0x0c
    Vector3 mSpecBump;              // +0x18
    float mGlossFactor;             // +0x24
    float mPhongFactor;             // +0x28
    float mPartBumpScale;           // +0x2c
    float mPartSpecScale;           // +0x30
    float mHairAngle;               // +0x34
    float mHairLength;              // +0x38
    float mHairWidth;               // +0x3c
    float mHairTaper;               // +0x40
    float mHairCurl;                // +0x44
    float mHairWave;                // +0x48
    float mHairMessiness;           // +0x4c
    float mHairDensity;             // +0x50
    bool mHairFaceCamera;           // +0x54
    uint64_t mHairTextureInstance;  // +0x58
    uint64_t mHairPrintGeomInstance;// +0x60
    uint32_t mBitFlags;             // +0x68
    uint32_t pad6c;
    cSPSkinPaintClearDescription();
    virtual ~cSPSkinPaintClearDescription();
};
// ---- items of slice s0052c230 end

// @ 0x0052d160
inline cSPSkinPaintClearDescription::cSPSkinPaintClearDescription()
: mDiffuseUserColor(-1), mDiffuse(1.0f, 1.0f, 1.0f), mSpecBump(0.0f, 1.0f, 0.5f), mGlossFactor(0.5f),
      mPhongFactor(1.0f), mPartBumpScale(1.0f), mPartSpecScale(1.0f), mHairAngle(kDefaultHairAngle),
      mHairLength(0.0f), mHairWidth(0.03f), mHairTaper(1.0f), mHairCurl(0.0f), mHairWave(0.0f),
      mHairMessiness(0.0f), mHairDensity(1.0f), mHairFaceCamera(true), mHairTextureInstance(0),
      mHairPrintGeomInstance(0), mBitFlags(0)
{
}
