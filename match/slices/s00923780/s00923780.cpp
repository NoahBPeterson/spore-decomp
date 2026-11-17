// Ref setter (0x00923780): assign the ref-counted member at +0x4 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_923780 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_923780 {
    char mPad[0x4];
    RefObject_923780* mpObject;                  // +0x4
    void SetObject(RefObject_923780* pObject);
};

// @ 0x00923780
void Owner_923780::SetObject(RefObject_923780* pObject)
{
    RefObject_923780* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
