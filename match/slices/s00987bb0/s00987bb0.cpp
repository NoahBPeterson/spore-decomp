// Ref setter (0x00987bb0): assign the ref-counted member at +0x40 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_987bb0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_987bb0 {
    char mPad[0x40];
    RefObject_987bb0* mpObject;                  // +0x40
    void SetObject(RefObject_987bb0* pObject);
};

// @ 0x00987bb0
void Owner_987bb0::SetObject(RefObject_987bb0* pObject)
{
    RefObject_987bb0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
