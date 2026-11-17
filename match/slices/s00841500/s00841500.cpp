// Ref setter (0x00841500): assign the ref-counted member at +0xcc (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_841500 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_841500 {
    char mPad[0xcc];
    RefObject_841500* mpObject;                  // +0xcc
    void SetObject(RefObject_841500* pObject);
};

// @ 0x00841500
void Owner_841500::SetObject(RefObject_841500* pObject)
{
    RefObject_841500* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
