// Ref setter (0x00615c10): assign the ref-counted member at +0xd90 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_615c10 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_615c10 {
    char mPad[0xd90];
    RefObject_615c10* mpObject;                  // +0xd90
    void SetObject(RefObject_615c10* pObject);
};

// @ 0x00615c10
void Owner_615c10::SetObject(RefObject_615c10* pObject)
{
    RefObject_615c10* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
