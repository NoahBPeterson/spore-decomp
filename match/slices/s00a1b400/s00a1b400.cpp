// Ref setter (0x00a1b400): assign the ref-counted member at +0xc90 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_a1b400 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_a1b400 {
    char mPad[0xc90];
    RefObject_a1b400* mpObject;                  // +0xc90
    void SetObject(RefObject_a1b400* pObject);
};

// @ 0x00a1b400
void Owner_a1b400::SetObject(RefObject_a1b400* pObject)
{
    RefObject_a1b400* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
