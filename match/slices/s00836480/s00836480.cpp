// Ref setter (0x00836480): assign the ref-counted member at +0x3c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_836480 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_836480 {
    char mPad[0x3c];
    RefObject_836480* mpObject;                  // +0x3c
    void SetObject(RefObject_836480* pObject);
};

// @ 0x00836480
void Owner_836480::SetObject(RefObject_836480* pObject)
{
    RefObject_836480* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
