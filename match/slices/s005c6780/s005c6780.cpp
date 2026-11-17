// Ref setter (0x005c6780): assign the ref-counted member at +0x50 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_5c6780 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_5c6780 {
    char mPad[0x50];
    RefObject_5c6780* mpObject;                  // +0x50
    void SetObject(RefObject_5c6780* pObject);
};

// @ 0x005c6780
void Owner_5c6780::SetObject(RefObject_5c6780* pObject)
{
    RefObject_5c6780* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
