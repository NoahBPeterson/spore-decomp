// Ref setter (0x00febb50): assign the ref-counted member at +0x17c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_febb50 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_febb50 {
    char mPad[0x17c];
    RefObject_febb50* mpObject;                  // +0x17c
    void SetObject(RefObject_febb50* pObject);
};

// @ 0x00febb50
void Owner_febb50::SetObject(RefObject_febb50* pObject)
{
    RefObject_febb50* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
