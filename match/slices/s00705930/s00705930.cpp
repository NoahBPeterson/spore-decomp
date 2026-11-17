// Ref setter (0x00705930): assign the ref-counted member at +0x448 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_705930 {
    virtual void v0();
    virtual void v1();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_705930 {
    char mPad[0x448];
    RefObject_705930* mpObject;                  // +0x448
    void SetObject(RefObject_705930* pObject);
};

// @ 0x00705930
void Owner_705930::SetObject(RefObject_705930* pObject)
{
    RefObject_705930* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
