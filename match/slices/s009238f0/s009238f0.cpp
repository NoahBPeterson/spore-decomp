// Ref setter (0x009238f0): assign the ref-counted member at +0x30 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_9238f0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_9238f0 {
    char mPad[0x30];
    RefObject_9238f0* mpObject;                  // +0x30
    void SetObject(RefObject_9238f0* pObject);
};

// @ 0x009238f0
void Owner_9238f0::SetObject(RefObject_9238f0* pObject)
{
    RefObject_9238f0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
