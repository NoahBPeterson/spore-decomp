// Slice s007c0780 — SP::cThumbnailManager::HandleMessage dispatcher, the
// cContentValidationSummarizer constructor it uses, and a destructor.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

struct RectID { int mPageID; int mAllocID; };
struct DoneMsg;

// multiple-inheritance base arrangement: the IHandlerRC subobject sits at +4,
// so an override receives `this` = manager + 4 and adjusts by -4.
struct cThumbnailManagerBase { virtual void v0(); };
struct IHandlerRC {
    virtual bool HandleMessage(unsigned int msgId, void* arg);
};

struct cThumbnailManager : cThumbnailManagerBase, IHandlerRC {
    void ThumbnailDone(DoneMsg* msg);
    void FUN_007bf720(void* arg);
    void FUN_007bbde0(void* arg);
    void DilateStart(void* arg);
    void DilateWithoutAODone(void* arg);
    void FUN_007bced0(void* arg);
    void PaletteJobInfo_Shutdown(void* arg);
    void FUN_007b29a0();
    void FUN_007b2970(void* arg);
    void FUN_007b77a0(void* arg);
};

// @ 0x007c1170  SP::cThumbnailManager::HandleMessage
bool IHandlerRC::HandleMessage(unsigned int msgId, void* arg)
{
    switch (msgId) {
    case 0x1c913db: ((cThumbnailManager*)((char*)this - 4))->ThumbnailDone((DoneMsg*)arg); return true;
    case 0x1c91270: ((cThumbnailManager*)((char*)this - 4))->FUN_007bf720(arg); return true;
    case 0x212c1ee: ((cThumbnailManager*)((char*)this - 4))->FUN_007bbde0(arg); return true;
    case 0x21d7528: ((cThumbnailManager*)((char*)this - 4))->DilateStart(arg); return true;
    case 0x21d752f: ((cThumbnailManager*)((char*)this - 4))->DilateWithoutAODone(arg); return true;
    case 0x31e09b4: ((cThumbnailManager*)((char*)this - 4))->FUN_007bced0(arg); return true;
    case 0x5221305: ((cThumbnailManager*)((char*)this - 4))->PaletteJobInfo_Shutdown(arg); return true;
    case 0x50b834d: ((cThumbnailManager*)((char*)this - 4))->FUN_007b29a0(); return true;
    case 0x5fadac4: ((cThumbnailManager*)((char*)this - 4))->FUN_007b2970(arg); return true;
    case 0x5fc2c38: ((cThumbnailManager*)((char*)this - 4))->FUN_007b77a0(arg); return true;
    case 0x7b240a0: ((cThumbnailManager*)((char*)this - 4))->FUN_007b77a0(arg); return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007c12a0  cContentValidationSummarizer-like constructor (vtable + zero)
// ---------------------------------------------------------------------------
struct ContentValidationSummarizer {
    virtual void v0();
    virtual void v1();
    char pad[0x94 - 0x08];
};

// @ 0x007c1330  matching destructor
void FUN_007c1330(void* p) { (void)p; }

// @ 0x007c0780  large capture routine (skeleton)
void FUN_007c0780(void* a) { (void)a; }
