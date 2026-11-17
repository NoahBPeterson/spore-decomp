// Ref setter (0x00c00660): assign the ref-counted member at +0x11c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_c00660 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_c00660 {
    char mPad[0x11c];
    RefObject_c00660* mpObject;                  // +0x11c
    void SetObject(RefObject_c00660* pObject);
};

// @ 0x00c00660
void Owner_c00660::SetObject(RefObject_c00660* pObject)
{
    RefObject_c00660* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
