// Ref setter (0x00c376d0): assign the ref-counted member at +0x800 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_c376d0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_c376d0 {
    char mPad[0x800];
    RefObject_c376d0* mpObject;                  // +0x800
    void SetObject(RefObject_c376d0* pObject);
};

// @ 0x00c376d0
void Owner_c376d0::SetObject(RefObject_c376d0* pObject)
{
    RefObject_c376d0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
