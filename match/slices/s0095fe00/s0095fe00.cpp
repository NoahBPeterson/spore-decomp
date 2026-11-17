// Ref setter (0x0095fe00): assign the ref-counted member at +0x1e0 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_95fe00 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_95fe00 {
    char mPad[0x1e0];
    RefObject_95fe00* mpObject;                  // +0x1e0
    void SetObject(RefObject_95fe00* pObject);
};

// @ 0x0095fe00
void Owner_95fe00::SetObject(RefObject_95fe00* pObject)
{
    RefObject_95fe00* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
