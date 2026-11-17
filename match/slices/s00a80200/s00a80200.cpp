// Ref setter (0x00a80200): assign the ref-counted member at +0x14 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_a80200 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_a80200 {
    char mPad[0x14];
    RefObject_a80200* mpObject;                  // +0x14
    void SetObject(RefObject_a80200* pObject);
};

// @ 0x00a80200
void Owner_a80200::SetObject(RefObject_a80200* pObject)
{
    RefObject_a80200* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
