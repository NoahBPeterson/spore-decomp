// Ref setter (0x006e7410): assign the ref-counted member at +0x6c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_6e7410 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_6e7410 {
    char mPad[0x6c];
    RefObject_6e7410* mpObject;                  // +0x6c
    void SetObject(RefObject_6e7410* pObject);
};

// @ 0x006e7410
void Owner_6e7410::SetObject(RefObject_6e7410* pObject)
{
    RefObject_6e7410* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
