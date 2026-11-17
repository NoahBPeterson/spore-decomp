// Ref setter (0x00cb5520): assign the ref-counted member at +0x5e0 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_cb5520 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_cb5520 {
    char mPad[0x5e0];
    RefObject_cb5520* mpObject;                  // +0x5e0
    void SetObject(RefObject_cb5520* pObject);
};

// @ 0x00cb5520
void Owner_cb5520::SetObject(RefObject_cb5520* pObject)
{
    RefObject_cb5520* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
