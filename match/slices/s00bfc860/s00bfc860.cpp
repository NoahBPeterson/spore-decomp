// Ref setter (0x00bfc860): assign the ref-counted member at +0x48 (AutoRefCount<T>::operator=(T*): AddRef the new
// object, store it, Release the old one).
#include "game/types.h"

struct RefObject_bfc860 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void AddRef();
    virtual void Release();
};
struct Owner_bfc860 {
    char mPad[0x48];
    RefObject_bfc860* mpObject;                  // +0x48
    void SetObject(RefObject_bfc860* pObject);
};

// @ 0x00bfc860
void Owner_bfc860::SetObject(RefObject_bfc860* pObject)
{
    RefObject_bfc860* const pOld = mpObject;
    if (pObject != pOld) {
        if (pObject)
            pObject->AddRef();
        mpObject = pObject;
        if (pOld)
            pOld->Release();
    }
}
