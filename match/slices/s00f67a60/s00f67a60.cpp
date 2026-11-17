// Ref setter (0x00f67a60): assign the ref-counted member at +0x74 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_f67a60 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_f67a60 {
    char mPad[0x74];
    RefObject_f67a60* mpObject;                  // +0x74
    void SetObject(RefObject_f67a60* pObject);
};

// @ 0x00f67a60
void Owner_f67a60::SetObject(RefObject_f67a60* pObject)
{
    RefObject_f67a60* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
