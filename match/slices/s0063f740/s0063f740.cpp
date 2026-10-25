// slice s0063f740: cSPPlayModeSubModePhoto send/write photo path.
#include "../s00636320/s00636320.h"

struct cString { char pad[0x14]; cString(); ~cString(); };   // 0x006B5060 / 0x006B5240
void FUN_00809db0(void* a, void* b);                         // 0x00809DB0 (cdecl)
struct CAchievementController { void AutoTest(uint32_t a, int b); };   // 0x00676E90
CAchievementController* FUN_00675250();                      // 0x00675250
extern void* gAppProperties2;                                // 0x015FD918

// ---------------------------------------------------------------- send-photo dialog helpers
// The signed-in account record (Pollen::AuthManager 0x00607A60).
struct IAuthField { void* mpValue; };
struct IAuth {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual IAuthField* GetField();                                    // +0x30
};
IAuth* AuthManager();                                                 // 0x00607A60
void ConvertNameToUTF16(void* pFieldValue, eastl::string16* pOut);    // 0x006B8F00 (cdecl)

// 0x006375E0: e-mail / directory name validator; the by-value string is destroyed by the callee.
char FindParentDir2(eastl::string name);

// The cSPPlayModeUI members reached from the photo sub-mode (it owns the send dialog).
struct IPhotoSendUI {
    IWindow* FindEditorUIWindow(uint32_t id);            // 0x00634E40
    void SetSendEmailDialogVisibility(bool b);           // 0x00635400
    void GetEditorText(uint32_t id, eastl::string* out); // 0x006377D0
};

// The photo browser sub-object of the sub-mode (+0x50).
struct cSPPlayModePhotoBrowserWriter {
    bool SaveThumbnail(void* pJob);                      // 0x00632D60
};

struct IVideoSource {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04();
    virtual const wchar_t** GetURL();                    // +0x14
};
IVideoSource* VideoSource();                             // 0x0067DE40

namespace EA {
void ConvertToString8Impl(eastl::string* pOut, const wchar_t* pSrc, unsigned int length);  // 0x0093C440
}

struct IMessageServer {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04();
    virtual void Send(uint32_t msgId, void* pData, int flags);   // +0x14
};
IMessageServer* MessageServer();                         // 0x0067DCC0

struct cSPPlayModeSubModePhoto {
    char pad0[0x4c];
    IPhotoSendUI* mpSendUI;              // +0x4C: the play-mode UI that owns the send dialog
    cSPPlayModePhotoBrowserWriter mPhotoBrowser;   // +0x50
    char pad54[0xf98 - 0x54];
    int  mDialogInProgress;              // +0xF98

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

// @ 0x0063FA40  validates the sender / recipient / message fields of the send-photo dialog,
// writes the thumbnail to the save area and hands the four strings to the message server.
bool cSPPlayModeSubModePhoto::FUN_0063fa40()
{
    cFourStrings strings;        // sender, recipient, message, thumbnail name
    eastl::string field;         // text read back from the dialog controls
    eastl::string16 name16;      // sender name from the account record

    // Pre-fill the sender control with the account name.
    ConvertNameToUTF16(AuthManager()->GetField()->mpValue, &name16);
    mpSendUI->FindEditorUIWindow(0x4581d50)->SetCaption(name16.mpBegin);
    mpSendUI->GetEditorText(0x4581d50, &field);

    bool failed = false;
    if (field.mpBegin == field.mpEnd || !FindParentDir2(eastl::string(field))) {
        mpSendUI->SetSendEmailDialogVisibility(false);
        BeginProfScope(0, 1)->End();
        FUN_00809db0((void*)0x1524c60, (void*)0x1524c24);
        mDialogInProgress = 8;
        failed = true;
    }
    strings.a.sprintf("%s", field.mpBegin);

    // Recipient.
    mpSendUI->GetEditorText(0x4581d78, &field);
    if (!failed) {
        if (field.mpBegin == field.mpEnd || !FindParentDir2(eastl::string(field))) {
            mpSendUI->SetSendEmailDialogVisibility(false);
            BeginProfScope(0, 1)->End();
            FUN_00809db0((void*)0x1524c60, (void*)0x1524c30);
            mDialogInProgress = 8;
            failed = true;
        }
    }
    strings.b.sprintf("%s", field.mpBegin);

    // Message body, then the thumbnail that travels with it.
    mpSendUI->GetEditorText(0x4581d90, &field);
    strings.c.sprintf("%s", field.mpBegin);
    if (!failed && !mPhotoBrowser.SaveThumbnail(&strings))
        failed = true;

    // URL of the just-uploaded photo.
    const wchar_t* url = *VideoSource()->GetURL();
    eastl::string url8;
    EA::ConvertToString8Impl(&url8, url, 0xffffffffu);
    strings.d.sprintf("%s", url8);

    if (!failed)
        MessageServer()->Send(0x457076f, &strings.a, 0);

    return failed;
}

// @ 0x0063FDA0  PARTIAL
void cSPPlayModeSubModePhoto::FUN_0063fda0() {}
