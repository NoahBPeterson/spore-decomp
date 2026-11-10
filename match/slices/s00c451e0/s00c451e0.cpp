// Slice s00c451e0: lazily resolved empire pointer held in an AutoRefCount.
#include "types.h"

struct Empire {
    virtual void AddRef();      // slot 0
    virtual void Release();     // slot 1
};

struct StarManager {
    Empire* GetEmpireByID();    // 0x00ba9370
};

Empire* __stdcall GetStarManager(int avatar);   // 0x00b3d2a0

template <typename T>
class AutoRef {
 public:
    T* mpObject;
    AutoRef& operator=(T* q) {
        T* old = mpObject;
        if (q != old) {
            if (q) q->AddRef();
            mpObject = q;
            if (old) old->Release();
        }
        return *this;
    }
};

struct Holder {
    uint32_t pad0000[0x8c / 4];   // +0x000
    int32_t  mAvatar;             // +0x08c
    AutoRef<Empire> mEmpire;      // +0x090

    Empire* GetEmpire();
};

// @ 0x00c451e0
Empire* Holder::GetEmpire()
{
    if (mEmpire.mpObject == 0 && mAvatar != -1)
        mEmpire = ((StarManager*)GetStarManager(mAvatar))->GetEmpireByID();
    return mEmpire.mpObject;
}
