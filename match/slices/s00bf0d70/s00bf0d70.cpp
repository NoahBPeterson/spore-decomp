// Ref setter (0x00bf0d70): assign the ref-counted member at +0x460 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_bf0d70 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_bf0d70 {
    char mPad[0x460];
    RefObject_bf0d70* mpObject;                  // +0x460
    void SetObject(RefObject_bf0d70* pObject);
};

// @ 0x00bf0d70
void Owner_bf0d70::SetObject(RefObject_bf0d70* pObject)
{
    RefObject_bf0d70* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
