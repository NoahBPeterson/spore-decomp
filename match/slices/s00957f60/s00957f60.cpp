// Ref setter (0x00957f60): assign the ref-counted member at +0xc8 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_957f60 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_957f60 {
    char mPad[0xc8];
    RefObject_957f60* mpObject;                  // +0xc8
    void SetObject(RefObject_957f60* pObject);
};

// @ 0x00957f60
void Owner_957f60::SetObject(RefObject_957f60* pObject)
{
    RefObject_957f60* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
