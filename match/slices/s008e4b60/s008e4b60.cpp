// Ref setter (0x008e4b60): assign the ref-counted member at +0x44 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_8e4b60 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_8e4b60 {
    char mPad[0x44];
    RefObject_8e4b60* mpObject;                  // +0x44
    void SetObject(RefObject_8e4b60* pObject);
};

// @ 0x008e4b60
void Owner_8e4b60::SetObject(RefObject_8e4b60* pObject)
{
    RefObject_8e4b60* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
