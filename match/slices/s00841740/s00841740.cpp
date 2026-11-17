// Ref setter (0x00841740): assign the ref-counted member at +0x14 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_841740 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_841740 {
    char mPad[0x14];
    RefObject_841740* mpObject;                  // +0x14
    void SetObject(RefObject_841740* pObject);
};

// @ 0x00841740
void Owner_841740::SetObject(RefObject_841740* pObject)
{
    RefObject_841740* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
