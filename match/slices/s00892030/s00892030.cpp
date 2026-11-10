// Slice s00892030 -- attach a document/resource to a UI panel.
//
//  0x00892030  Panel::Attach(src, mode):
//              * lock the panel's critical section (+0x28),
//              * if no document is attached yet and src is non-null and accepts the
//                panel (virtual +0x10), load the resource named at +0x160 (0x8d11f0)
//                and resolve src through it (0x8cc4b0 with callback 0x890f60 and
//                src->f1c(name)), then bind it (0x891b10); store it and AddRef
//                (virtual +0x04),
//              * on failure invoke this->f1c(); when the bound flag +0x164 is set,
//                hand the document to the +0x168 view (0x8a1600),
//              * unlock the critical section and return whether the bind succeeded.
#include "types.h"

// compile with /O2 /MD /Gy /TP /arch:SSE /fp:fast

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);   // IAT 0x013cc2d8
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);   // IAT 0x013cc2dc

extern "C" int   __cdecl FUN_008d11f0(char* name);                              // 0x008d11f0
extern "C" void* __cdecl FUN_008cc4b0(int res, void* obj, int cb, void* a, void* b); // 0x008cc4b0
extern "C" int   __cdecl FUN_00891b10(void* self, int mode);                    // 0x00891b10
extern "C" void  __cdecl FUN_008a1600(void* view, void* doc);                   // 0x008a1600

struct Doc {
    virtual void* f0();       // +0x00
    virtual int   f4();       // +0x04 (AddRef)
    virtual void* f8();       // +0x08
    virtual void* fc();       // +0x0c
    virtual int   f10();      // +0x10 (accepts panel?)
    virtual void* f14();      // +0x14
    virtual void* f18();      // +0x18
    virtual void* f1c(char* name);   // +0x1c
};

struct Panel {
    char  pad0[0x10];
    Doc*  mDoc;        // +0x10
    char  pad14[0x28 - 0x14];
    char  mCs[0x24];   // +0x28
    char  pad4c[0x150 - 0x4c];
    int   mRes150;     // +0x150
    int   mBand154;    // +0x154
    char  pad158[0x160 - 0x158];
    char  mName160[0x4];
    char  mFlag164;    // +0x164
    char  pad165[0x168 - 0x165];
    char  mView168[0x4];

    bool Attach(Doc* src, int mode);
};

// @ 0x00892030
bool Panel::Attach(Doc* src, int mode)
{
    bool ok = false;
    EnterCriticalSection(mCs);

    if (mDoc == 0 && src != 0 && src->f10() != 0) {
        mRes150 = FUN_008d11f0(mName160);
        if (mRes150 != 0) {
            mBand154 = (int)FUN_008cc4b0(mRes150, src, 0x890f60, mName160, src->f1c(mName160));
            if (mBand154 != 0 && FUN_00891b10(this, mode)) {
                mDoc = src;
                src->f4();
                ok = true;
                if (mFlag164 != 0) {
                    FUN_008a1600(mView168, mDoc);
                    LeaveCriticalSection(mCs);
                    return ok;
                }
            }
        }
    }

    if (!ok) {
        ((void(__thiscall*)(Panel*))((void**)this)[0x1c / 4])(this);
    }

    LeaveCriticalSection(mCs);
    return ok;
}
