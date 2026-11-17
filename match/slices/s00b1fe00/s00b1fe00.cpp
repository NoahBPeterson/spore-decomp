// Ref setter (0x00b1fe00): assign the ref-counted member at +0x70 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_b1fe00 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_b1fe00 {
    char mPad[0x70];
    RefObject_b1fe00* mpObject;                  // +0x70
    void SetObject(RefObject_b1fe00* pObject);
};

// @ 0x00b1fe00
void Owner_b1fe00::SetObject(RefObject_b1fe00* pObject)
{
    RefObject_b1fe00* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
