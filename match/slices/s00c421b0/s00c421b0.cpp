// Ref setter (0x00c421b0): assign the ref-counted member at +0x4cc (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_c421b0 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_c421b0 {
    char mPad[0x4cc];
    RefObject_c421b0* mpObject;                  // +0x4cc
    void SetObject(RefObject_c421b0* pObject);
};

// @ 0x00c421b0
void Owner_c421b0::SetObject(RefObject_c421b0* pObject)
{
    RefObject_c421b0* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
