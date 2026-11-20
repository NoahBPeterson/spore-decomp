// @ 0x00e24d10
// Decompiled slice s00e24d10 -- builds a property list and submits it to the
// property-list factory (a UI notification: one pointer value, an integer and
// a zero vector are published under indices 0, 1 and 3).
#include <intrin.h>
#include "types.h"

struct Variant;

// Reference-counted object; Release is vtable slot +0x04.
struct cRefCounted {
    virtual void slot00();
    virtual void Release();                                    // +0x04
};

struct cPropertyList : cRefCounted {
    virtual void slot08(); virtual void slot0c(); virtual void slot10();
    virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void SetValue(int nIndex, const Variant& value);   // +0x20
};

struct cPropListFactory {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void Create(cPropertyList** ppOut);                // +0x18
    virtual void slot1c(); virtual void slot20(); virtual void slot24();
    virtual void slot28(); virtual void slot2c(); virtual void slot30();
    virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48();
    virtual void slot4c(); virtual void slot50();
    virtual void Submit(uint32_t nID, cPropertyList* pFirst,
                        cPropertyList* pSecond);               // +0x54
};

// EA property variant: payload at +0x00, tag words at +0x10/+0x12.
struct Variant {
    uint32_t mData[4];                                         // +0x00 .. +0x0f
    uint16_t mFlags;                                           // +0x10
    uint16_t mType;                                            // +0x12

    void     SetPointer(const void* p);                        // 0x00e21b30
    Variant& SetU32(const uint32_t* pValue);                   // 0x00422eb0
    Variant& SetVec3(const float* pValue);                     // 0x006a3570
    void     Destruct(int bReset);                             // 0x0093db80
};

cPropListFactory* PropListFactory();                           // 0x006895b0

// Intrusive pointer as the shipped code uses it: reset() clears the slot
// before releasing, and release() frees what is still held (its destructor
// body; the two slots are released in reverse declaration order at the end).
template <class T>
struct RefPtr {
    T* mpObject;                                               // +0x00

    RefPtr() : mpObject(0) {}
    void release() {
        if (mpObject) mpObject->Release();
    }
    void reset() {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};

// @ 0x00e24d10
void FUN_00e24d10(uint32_t nID, void* pValue)
{
    RefPtr<cPropertyList> pList;
    RefPtr<cPropertyList> pOwner;
    uint32_t nZero;
    float    vecZero[3];
    Variant  value;

    cPropListFactory* pFactory = PropListFactory();

    // Lists are re-created from scratch: the slot is cleared first.
    pList.reset();
    pFactory->Create(&pList.mpObject);
    pOwner.reset();
    pFactory->Create(&pOwner.mpObject);

    {
        cPropertyList* pTarget = pList.mpObject;
        value.mFlags = 0;
        value.mType = 0;
        value.SetPointer(pValue);
        pTarget->SetValue(0, value);
        if (value.mFlags & 4) value.Destruct(0);
    }
    {
        cPropertyList* pTarget = pList.mpObject;
        nZero = 0;
        value.mFlags = 0;
        value.mType = 0;
        value.SetU32(&nZero);
        pTarget->SetValue(1, value);
        if (value.mFlags & 4) value.Destruct(0);
    }
    {
        cPropertyList* pTarget = pList.mpObject;
        vecZero[0] = 0.0f;
        vecZero[1] = 0.0f;
        vecZero[2] = 0.0f;
        value.mFlags = 0;
        value.mType = 0;
        value.SetVec3(vecZero);
        pTarget->SetValue(3, value);
        if (value.mFlags & 4) value.Destruct(0);
    }

    pFactory->Submit(nID, pList.mpObject, pOwner.mpObject);

    // Slots are released in reverse declaration order, as destructors would.
    pOwner.release();
    pList.release();
}
