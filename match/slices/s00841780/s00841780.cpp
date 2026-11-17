// Ref setter (0x00841780): assign the ref-counted member at +0x18 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_841780 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_841780 {
    char mPad[0x18];
    RefObject_841780* mpObject;                  // +0x18
    void SetObject(RefObject_841780* pObject);
};

// @ 0x00841780
void Owner_841780::SetObject(RefObject_841780* pObject)
{
    RefObject_841780* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
