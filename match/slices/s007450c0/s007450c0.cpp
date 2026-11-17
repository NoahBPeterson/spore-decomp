// Ref setter (0x007450c0): assign the ref-counted member at +0x5c8 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_7450c0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_7450c0 {
    char mPad[0x5c8];
    RefObject_7450c0* mpObject;                  // +0x5c8
    void SetObject(RefObject_7450c0* pObject);
};

// @ 0x007450c0
void Owner_7450c0::SetObject(RefObject_7450c0* pObject)
{
    RefObject_7450c0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
