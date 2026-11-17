// Ref setter (0x00a42c50): assign the ref-counted member at +0xd4 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_a42c50 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_a42c50 {
    char mPad[0xd4];
    RefObject_a42c50* mpObject;                  // +0xd4
    void SetObject(RefObject_a42c50* pObject);
};

// @ 0x00a42c50
void Owner_a42c50::SetObject(RefObject_a42c50* pObject)
{
    RefObject_a42c50* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
