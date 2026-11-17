// Ref setter (0x00ca0000): assign the ref-counted member at +0xbc0 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_ca0000 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_ca0000 {
    char mPad[0xbc0];
    RefObject_ca0000* mpObject;                  // +0xbc0
    void SetObject(RefObject_ca0000* pObject);
};

// @ 0x00ca0000
void Owner_ca0000::SetObject(RefObject_ca0000* pObject)
{
    RefObject_ca0000* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
