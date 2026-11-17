// Ref setter (0x00ae38f0): assign the ref-counted member at +0x38 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_ae38f0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_ae38f0 {
    char mPad[0x38];
    RefObject_ae38f0* mpObject;                  // +0x38
    void SetObject(RefObject_ae38f0* pObject);
};

// @ 0x00ae38f0
void Owner_ae38f0::SetObject(RefObject_ae38f0* pObject)
{
    RefObject_ae38f0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
