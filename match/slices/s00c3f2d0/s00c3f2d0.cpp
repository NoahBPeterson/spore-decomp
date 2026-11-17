// Ref setter (0x00c3f2d0): assign the ref-counted member at +0x24c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_c3f2d0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_c3f2d0 {
    char mPad[0x24c];
    RefObject_c3f2d0* mpObject;                  // +0x24c
    void SetObject(RefObject_c3f2d0* pObject);
};

// @ 0x00c3f2d0
void Owner_c3f2d0::SetObject(RefObject_c3f2d0* pObject)
{
    RefObject_c3f2d0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
