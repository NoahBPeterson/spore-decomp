// Ref setter (0x009238b0): assign the ref-counted member at +0x2c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_9238b0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_9238b0 {
    char mPad[0x2c];
    RefObject_9238b0* mpObject;                  // +0x2c
    void SetObject(RefObject_9238b0* pObject);
};

// @ 0x009238b0
void Owner_9238b0::SetObject(RefObject_9238b0* pObject)
{
    RefObject_9238b0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
