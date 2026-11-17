// Ref setter (0x008eb830): assign the ref-counted member at +0x28 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_8eb830 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_8eb830 {
    char mPad[0x28];
    RefObject_8eb830* mpObject;                  // +0x28
    void SetObject(RefObject_8eb830* pObject);
};

// @ 0x008eb830
void Owner_8eb830::SetObject(RefObject_8eb830* pObject)
{
    RefObject_8eb830* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
