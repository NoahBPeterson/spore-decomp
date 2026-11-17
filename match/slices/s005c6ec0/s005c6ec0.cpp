// Ref setter (0x005c6ec0): assign the ref-counted member at +0x4 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_5c6ec0 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_5c6ec0 {
    char mPad[0x4];
    RefObject_5c6ec0* mpObject;                  // +0x4
    void SetObject(RefObject_5c6ec0* pObject);
};

// @ 0x005c6ec0
void Owner_5c6ec0::SetObject(RefObject_5c6ec0* pObject)
{
    RefObject_5c6ec0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
