// Ref setter (0x00615bd0): assign the ref-counted member at +0xd8c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_615bd0 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_615bd0 {
    char mPad[0xd8c];
    RefObject_615bd0* mpObject;                  // +0xd8c
    void SetObject(RefObject_615bd0* pObject);
};

// @ 0x00615bd0
void Owner_615bd0::SetObject(RefObject_615bd0* pObject)
{
    RefObject_615bd0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
