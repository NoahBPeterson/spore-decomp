// Ref setter (0x00f99ee0): assign the ref-counted member at +0x214 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_f99ee0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_f99ee0 {
    char mPad[0x214];
    RefObject_f99ee0* mpObject;                  // +0x214
    void SetObject(RefObject_f99ee0* pObject);
};

// @ 0x00f99ee0
void Owner_f99ee0::SetObject(RefObject_f99ee0* pObject)
{
    RefObject_f99ee0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
