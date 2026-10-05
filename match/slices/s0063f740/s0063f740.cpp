// slice s0063f740: cSPPlayModeSubModePhoto send/write photo path.
#include "../s00636320/s00636320.h"

struct cString { char pad[0x14]; cString(); ~cString(); };   // 0x006B5060 / 0x006B5240
void FUN_00809db0(void* a, void* b);                         // 0x00809DB0 (cdecl)
struct CAchievementController { void AutoTest(uint32_t a, int b); };   // 0x00676E90
CAchievementController* FUN_00675250();                      // 0x00675250
extern void* gAppProperties2;                                // 0x015FD918

struct cSPPlayModeSubModePhoto {
    char pad0[0xf98];
    int  mDialogInProgress;        // +0xF98

    void WritePhotoWithComment();
    bool FUN_0063fa40();
    void SendPhoto();
    void FUN_0063fda0();
    void CloseSendPhotoWindow();   // 0x0063EC10 (external)
};

// @ 0x0063FD20
void cSPPlayModeSubModePhoto::SendPhoto()
{
    cString s;
    if (!FUN_0063fa40()) {
        CloseSendPhotoWindow();
        BeginProfScope(0, 1)->End();
        FUN_00809db0((void*)0x1524c60, (void*)0x1524c18);
        mDialogInProgress = 8;
        if (*(int*)(*(int*)((char*)gAppProperties2 + 0x3c) + 0x118) == 0)
            FUN_00675250()->AutoTest(0xb4c2a66b, 1);
    }
}

// @ 0x0063F740  PARTIAL
void cSPPlayModeSubModePhoto::WritePhotoWithComment() {}
// @ 0x0063FA40  PARTIAL
extern void gPartialCall();
__declspec(noinline) bool cSPPlayModeSubModePhoto::FUN_0063fa40() { gPartialCall(); return false; }
// @ 0x0063FDA0  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063fda0() {}
