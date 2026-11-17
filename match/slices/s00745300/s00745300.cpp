// Ref setter (0x00745300): assign the ref-counted member at +0x48 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_745300 {
    virtual void AddRef();
    virtual void Release();
};
struct Owner_745300 {
    char mPad[0x48];
    RefObject_745300* mpObject;                  // +0x48
    void SetObject(RefObject_745300* pObject);
};

// @ 0x00745300
void Owner_745300::SetObject(RefObject_745300* pObject)
{
    RefObject_745300* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
