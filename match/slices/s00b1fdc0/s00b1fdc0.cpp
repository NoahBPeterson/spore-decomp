// Ref setter (0x00b1fdc0): assign the ref-counted member at +0x58 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_b1fdc0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_b1fdc0 {
    char mPad[0x58];
    RefObject_b1fdc0* mpObject;                  // +0x58
    void SetObject(RefObject_b1fdc0* pObject);
};

// @ 0x00b1fdc0
void Owner_b1fdc0::SetObject(RefObject_b1fdc0* pObject)
{
    RefObject_b1fdc0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
