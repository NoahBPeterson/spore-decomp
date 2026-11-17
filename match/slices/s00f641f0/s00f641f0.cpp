// Ref setter (0x00f641f0): assign the ref-counted member at +0xa0 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_f641f0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_f641f0 {
    char mPad[0xa0];
    RefObject_f641f0* mpObject;                  // +0xa0
    void SetObject(RefObject_f641f0* pObject);
};

// @ 0x00f641f0
void Owner_f641f0::SetObject(RefObject_f641f0* pObject)
{
    RefObject_f641f0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
