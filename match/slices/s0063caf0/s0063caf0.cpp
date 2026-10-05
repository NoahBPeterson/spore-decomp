// slice s0063caf0: cSPPlayModeSubModeMovie YouTube registration + upload helpers.
#include "../s00636320/s00636320.h"

struct cEditorYouTubeAuthenticationMessage {   // 0x34
    eastl::string mUsername;
    eastl::string mPassword;
    eastl::string mSource;
    bool mCheckRegistration;
    ~cEditorYouTubeAuthenticationMessage();
};

struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
};
IMessageServer* GetMessageServer();   // 0x0067DCC0

struct cProp { char pad12[0x12]; short mType; char* GetBool(); };   // 0x0041E920
struct IPropList {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8();
    virtual bool GetProp(uint32_t id, void** out);   // +0x24
};
extern IPropList* gAppProperties;   // 0x015FD918

struct cSPPlayModeSubModeMovie {
    char pad34[0x34];
    cSPPlayModeUI* mUI;             // +0x34
    char pad38[0x22c0 - 0x38];
    bool mb22c0;                    // +0x22C0
    bool mb22c1;                    // +0x22C1
    char pad22c2[0x22fc - 0x22c2];
    uint32_t mField22fc;            // +0x22FC
    char pad2300[0x231c - 0x2300];
    bool mb231c;                    // +0x231C
    bool mb231d;                    // +0x231D
    bool mb231e;                    // +0x231E
    bool mb231f;                    // +0x231F
    bool mb2320;                    // +0x2320
    bool mb2321;                    // +0x2321
    char pad2322[0x234c - 0x2322];
    uint32_t mField234c;            // +0x234C

    void CheckYouTubeRegistration();   // 0x0063CED0
    void FUN_0063cf90();               // 0x0063CF90
    void FUN_0063caf0();
    __declspec(noinline) void FUN_0063cd30();
    void ConstructYouTubeVideoUploadXMLRequest(eastl::string* out);   // 0x0063D050
    void ConstructVideoURL();                       // 0x0063D170
    void FUN_0063d2f0();
    void FUN_0063b760();
    void ToggleRecordingIndicator(char b);          // 0x0063D910
};

void KillSetiEffects(uint32_t id, uint32_t state);   // 0x00435ED0 (cdecl)
extern char* gRecordingStopped;                       // 0x0152443C

struct IAudioSystem {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7();
    virtual uint32_t v8();                            // +0x20
};
IAudioSystem* GetSystemAT();                          // 0x00A206F0

// @ 0x0063CED0
void cSPPlayModeSubModeMovie::CheckYouTubeRegistration()
{
    cEditorYouTubeAuthenticationMessage msg;
    mb231e = true;
    mb231d = false;
    mb231c = false;
    msg.mUsername.sprintf("%s", (const char*)mField22fc);
    msg.mPassword.sprintf("%s", (const char*)mField234c);
    msg.mSource.sprintf("%s", "scc");
    msg.mCheckRegistration = true;
    GetMessageServer()->PostMessage(0x55be439, &msg, 0);
}

// @ 0x0063CF90
void cSPPlayModeSubModeMovie::FUN_0063cf90()
{
    cEditorYouTubeAuthenticationMessage msg;
    mb2321 = true;
    mb2320 = false;
    mb231f = false;
    msg.mUsername.sprintf("%s", (const char*)mField22fc);
    msg.mPassword.sprintf("%s", (const char*)mField234c);
    msg.mSource.sprintf("%s", "scc");
    msg.mCheckRegistration = false;
    GetMessageServer()->PostMessage(0x55be439, &msg, 0);
}

// @ 0x0063CAF0  PARTIAL
void cSPPlayModeSubModeMovie::FUN_0063caf0() {}
// @ 0x0063CD30  PARTIAL
extern volatile int gPartialSink;
__declspec(noinline) void cSPPlayModeSubModeMovie::FUN_0063cd30() { gPartialSink = 1; }
// @ 0x0063D050
void cSPPlayModeSubModeMovie::ConstructYouTubeVideoUploadXMLRequest(eastl::string* out)
{
    char bPrivate = 0;
    if (gAppProperties) {
        void* p;
        if (gAppProperties->GetProp(0x8608be4, &p) && ((cProp*)p)->mType == 1)
            bPrivate = *((cProp*)p)->GetBool();
    }

    out->clear();
    out->append_sprintf("%s", "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    out->append_sprintf("%s", "<entry xmlns=\"http://www.w3.org/2005/Atom\"\n");
    out->append_sprintf("%s", "\txmlns:media=\"http://search.yahoo.com/mrss/\"\n");
    out->append_sprintf("%s", "\txmlns:yt=\"http://gdata.youtube.com/schemas/2007\">\n");
    out->append_sprintf("%s", "\t<media:group>\n");
    out->append_sprintf("%s", "\t\t<media:title>Spore Creature Creator Video</media:title>\n");
    out->append_sprintf("%s", "\t\t<media:description>This video was created using the Spore Creature Creator.</media:description>\n");
    out->append_sprintf("%s", "\t\t<media:category scheme=\"http://gdata.youtube.com/schemas/2007/categories.cat\">Entertainment</media:category>\n");
    out->append_sprintf("%s", "\t\t<media:keywords>spore, creature</media:keywords>\n");
    if (bPrivate == 0)
        out->append_sprintf("%s", "\t<yt:private/>\n");
    out->append_sprintf("%s", "\t</media:group>\n");
    out->append_sprintf("%s", "</entry>\n");
}
// @ 0x0063D170  PARTIAL
void cSPPlayModeSubModeMovie::ConstructVideoURL() {}
// @ 0x0063D2F0  PARTIAL
void cSPPlayModeSubModeMovie::FUN_0063d2f0() {}
// @ 0x0063D910
void cSPPlayModeSubModeMovie::ToggleRecordingIndicator(char b)
{
    if (b == 0) {
        IAudioSystem* s = GetSystemAT();
        KillSetiEffects(0xcb4ad069, s ? s->v8() : 0);
        FUN_0063cd30();
    }
    IWindow* w = mUI->FindPlayModeUIWindow(0x42cadb8);
    if (w)
        w->SetCaption(EA::ConvertToString16(gRecordingStopped, -1).c_str());
    mb22c0 = false;
    mUI->SetUIGroupVisible(0x3f434ac, false);
    mUI->SetUIGroupVisible(0x3fc1740, true);
    if (mb22c1)
        FUN_0063b760();
}
