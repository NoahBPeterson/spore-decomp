// Ref setter (0x00662b00): assign the ref-counted member at +0x4c (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_662b00 {
    virtual void v0();
    virtual void v1();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_662b00 {
    char mPad[0x4c];
    RefObject_662b00* mpObject;                  // +0x4c
    void SetObject(RefObject_662b00* pObject);
};

// @ 0x00662b00
void Owner_662b00::SetObject(RefObject_662b00* pObject)
{
    RefObject_662b00* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
