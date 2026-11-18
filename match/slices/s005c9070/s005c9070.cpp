// @ 0x005c9070
#include "game/types.h"

// These are the four actual vtables installed during the deleting destructor.
extern const void* const cSPPalettePageUI_IWinProc_vtable[];
extern const void* const cSPPalettePageUI_RefCount_vtable[];
extern const void* const cRC_vtable[];
extern const void* const ITracerBase_vtable[];
extern "C" void EASTL_allocator_deallocate(void*);

class cSPUILayout {
public:
    virtual void QueryInterface();
    virtual int AddRef();
    virtual int Release();
};

class cRefVector {
public:
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    int mAllocator[2];
    ~cRefVector(); // 0x005c8fd0
};

namespace eastl {
template<class T> class sp_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int mAllocator[2];
    ~sp_vector(); // 0x005c7f10
};
}

namespace SP {
// Local retail layout, retaining the member names of SP/cSPPalettePageUI.h.
// Explicit vptr fields let this represent the scalar deleting entry's flags
// and returned object pointer using ordinary C++.
class cSPPalettePageUI {
public:
    const void* const* mWinProcVtable;
    const void* const* mRefCountVtable;
    int mRefCount;
    cSPUILayout* mLayout;
    void* mWinPage;
    cSPUILayout* mData;
    float mScaleX;
    float mScaleY;
    eastl::sp_vector<void*> mOldItemUIs;
    cRefVector mItemUIs;

    cSPPalettePageUI* ScalarDeletingDestructor(unsigned int flags);
};

cSPPalettePageUI* cSPPalettePageUI::ScalarDeletingDestructor(unsigned int flags)
{
    mWinProcVtable = cSPPalettePageUI_IWinProc_vtable;
    mRefCountVtable = cSPPalettePageUI_RefCount_vtable;
    mItemUIs.~cRefVector();
    mOldItemUIs.~sp_vector();
    if (mData)
        mData->Release();
    if (mLayout)
        mLayout->Release();
    mRefCountVtable = cRC_vtable;
    mWinProcVtable = ITracerBase_vtable;
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}
}
