// Ref setter (0x00a108e0): assign the ref-counted member at +0xc (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_a108e0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_a108e0 {
    char mPad[0xc];
    RefObject_a108e0* mpObject;                  // +0xc
    void SetObject(RefObject_a108e0* pObject);
};

// @ 0x00a108e0
void Owner_a108e0::SetObject(RefObject_a108e0* pObject)
{
    RefObject_a108e0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
