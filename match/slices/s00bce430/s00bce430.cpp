// Ref setter (0x00bce430): assign the ref-counted member at +0x6a0 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_bce430 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_bce430 {
    char mPad[0x6a0];
    RefObject_bce430* mpObject;                  // +0x6a0
    void SetObject(RefObject_bce430* pObject);
};

// @ 0x00bce430
void Owner_bce430::SetObject(RefObject_bce430* pObject)
{
    RefObject_bce430* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
