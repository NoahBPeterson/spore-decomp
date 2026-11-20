// @ 0x0084acf0
#include "game/types.h"

// Explicit vtable views are used here because the deleting destructor changes
// both interface tables before invoking the base destructor.
struct IMEServerVTable {
    void* methods[5];
    void (__stdcall *SetEnabled)(bool);
};
struct IHandlerVTable { void* methods[2]; };

extern IMEServerVTable IMEServerWin32_vftable;
extern IHandlerVTable IMEServerWin32_IHandler_vftable;
extern IHandlerVTable IHandler_vftable;
void EASTL_allocator_deallocate(void*);

class IMEServer {
public:
    IMEServerVTable* mpVTable;
    bool mbInitialized;
    bool mbEnabled;
    char mPad06[2];
    void* mpMessageServer;
    char mCompositionAndContainers[0xb0];
    ~IMEServer();
};

class IMEServerWin32 : public IMEServer {
public:
    IHandlerVTable* mpHandlerVTable;
    void* mhWnd;
    unsigned mC4;
    unsigned mC8;
    void* mpCanvas;
    void* mD0;

    void* Destroy(unsigned flags);
};

void* IMEServerWin32::Destroy(unsigned flags)
{
    mpVTable = &IMEServerWin32_vftable;
    mpHandlerVTable = &IMEServerWin32_IHandler_vftable;
    if (mbInitialized) {
        mbInitialized = false;
        mpMessageServer = 0;
        IMEServerWin32_vftable.SetEnabled(false);
    }
    mpHandlerVTable = &IHandler_vftable;
    IMEServer::~IMEServer();
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}
