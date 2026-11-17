// Ref setter (0x00c23e50): assign the ref-counted member at +0x1010 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_c23e50 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_c23e50 {
    char mPad[0x1010];
    RefObject_c23e50* mpObject;                  // +0x1010
    void SetObject(RefObject_c23e50* pObject);
};

// @ 0x00c23e50
void Owner_c23e50::SetObject(RefObject_c23e50* pObject)
{
    RefObject_c23e50* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
