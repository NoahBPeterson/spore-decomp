
#include "types.h"

struct IGameObject {
    virtual void AddRef();             // vtable +0x00
    virtual void Release();            // vtable +0x04
    virtual void Unused08();           // vtable +0x08
    virtual void* Cast(unsigned int);  // vtable +0x0C
};

struct ISpatialObject {
    void** mpVtable;

    __forceinline void AddRef()
    {
        ((void (__thiscall*)(ISpatialObject*))
            mpVtable[0xBC / 4])(this);
    }

    __forceinline void Release()
    {
        ((void (__thiscall*)(ISpatialObject*))
            mpVtable[0xC0 / 4])(this);
    }
};

struct Meter {
    unsigned char mPad00[0x14];
    ISpatialObject* mpSpatial;          // +0x14
    unsigned char mPad18[0x10];
    IGameObject* mpObject;              // +0x28

    void SetObject(IGameObject* object);
};

// @ 0x00e077d0
void Meter::SetObject(IGameObject* object)
{
    IGameObject* previousObject = mpObject;

    if (object != previousObject) {
        if (object)
            object->AddRef();

        mpObject = object;

        if (previousObject)
            previousObject->Release();
    }

    ISpatialObject* spatial = object
        ? (ISpatialObject*)object->Cast(0x01186577)
        : 0;

    ISpatialObject* previousSpatial = mpSpatial;

    if (spatial != previousSpatial) {
        if (spatial)
            spatial->AddRef();

        mpSpatial = spatial;

        if (previousSpatial)
            previousSpatial->Release();
    }
}
