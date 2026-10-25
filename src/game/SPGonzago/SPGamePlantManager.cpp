// src/game/SPGonzago/SPGamePlantManager.cpp -- migrated from slice(s) s00b2a8d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGamePlantManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>

// ---- items of slice s00b2a8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted {
    virtual void     AddRef();                              // +0x00
    virtual uint32_t Release();                             // +0x04
};
struct AutoRef {
    IRefCounted* mpObject;                                  // +0x00

    AutoRef() : mpObject(0) {}

    AutoRef(const AutoRef& src) : mpObject(src.mpObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }

    ~AutoRef()
    {
        if (mpObject)
            mpObject->Release();
    }

    void Clear()
    {
        if (mpObject) {
            IRefCounted* pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
    }

    void AssignObject(IRefCounted* pNew)
    {
        IRefCounted* pOld = mpObject;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            mpObject = pNew;
            if (pOld)
                pOld->Release();
        }
    }

    void Assign(const AutoRef& src)
    {
        AssignObject(src.mpObject);
    }
};
struct cTypeInfo {
    AutoRef  mProps;                                        // +0x00
    float    mMinEmitMap;                                   // +0x04
    float    mMaxEmitMap;                                   // +0x08
    float    mSpriteScale;                                  // +0x0c
    int32_t  mResourceIDs[11];                              // +0x10 .. +0x38

    cTypeInfo& operator=(const cTypeInfo& src);             // 0x00b2b150
};
// ---- items of slice s00b2a8d0 end

// @ 0x00b2b150
cTypeInfo& cTypeInfo::operator=(const cTypeInfo& src)
{
    mProps.Assign(src.mProps);
    mMinEmitMap = src.mMinEmitMap;
    mMaxEmitMap = src.mMaxEmitMap;
    mSpriteScale = src.mSpriteScale;
    mResourceIDs[0] = src.mResourceIDs[0];
    mResourceIDs[1] = src.mResourceIDs[1];
    mResourceIDs[2] = src.mResourceIDs[2];
    mResourceIDs[3] = src.mResourceIDs[3];
    mResourceIDs[4] = src.mResourceIDs[4];
    mResourceIDs[5] = src.mResourceIDs[5];
    mResourceIDs[6] = src.mResourceIDs[6];
    mResourceIDs[7] = src.mResourceIDs[7];
    mResourceIDs[8] = src.mResourceIDs[8];
    mResourceIDs[9] = src.mResourceIDs[9];
    mResourceIDs[10] = src.mResourceIDs[10];
    return *this;
}
