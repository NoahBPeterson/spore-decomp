// Ref setter (0x00c36230): assign the ref-counted member at +0x128 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_c36230 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_c36230 {
    char mPad[0x128];
    RefObject_c36230* mpObject;                  // +0x128
    void SetObject(RefObject_c36230* pObject);
};

// @ 0x00c36230
void Owner_c36230::SetObject(RefObject_c36230* pObject)
{
    RefObject_c36230* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
