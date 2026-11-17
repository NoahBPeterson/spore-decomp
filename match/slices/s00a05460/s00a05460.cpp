// Ref setter (0x00a05460): assign the ref-counted member at +0x4c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_a05460 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_a05460 {
    char mPad[0x4c];
    RefObject_a05460* mpObject;                  // +0x4c
    void SetObject(RefObject_a05460* pObject);
};

// @ 0x00a05460
void Owner_a05460::SetObject(RefObject_a05460* pObject)
{
    RefObject_a05460* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
