// Ref setter (0x00a10920): assign the ref-counted member at +0x10 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_a10920 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_a10920 {
    char mPad[0x10];
    RefObject_a10920* mpObject;                  // +0x10
    void SetObject(RefObject_a10920* pObject);
};

// @ 0x00a10920
void Owner_a10920::SetObject(RefObject_a10920* pObject)
{
    RefObject_a10920* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
