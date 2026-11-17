// Ref setter (0x00a11dd0): assign the ref-counted member at +0x374 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_a11dd0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_a11dd0 {
    char mPad[0x374];
    RefObject_a11dd0* mpObject;                  // +0x374
    void SetObject(RefObject_a11dd0* pObject);
};

// @ 0x00a11dd0
void Owner_a11dd0::SetObject(RefObject_a11dd0* pObject)
{
    RefObject_a11dd0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
