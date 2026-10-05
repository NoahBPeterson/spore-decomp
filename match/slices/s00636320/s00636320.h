// Shared declarations for the SP cSPPlayModeUI module (retail layout, 2017 build).
// Slices s00636320 .. s00645620.
#pragma once
#include "types.h"

struct IWindow;
struct IOther;
struct IControl;
struct cSPEditorUI;

// ---------------------------------------------------------------- EASTL string
void operator delete(void* p);   // 0x00F47380

namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
extern char    gEmptyString8[1];
template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
template <> struct EmptyStr<char>    { static char*    Get() { return gEmptyString8; } };
template <typename T>
struct allocator {
    void deallocate(void* p) { operator delete(p); }
};
template <typename T, typename Allocator = allocator<T> >
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    int sprintf(const char* fmt, ...);   // 0x00472FE0
    int append_sprintf(const char* fmt, ...);   // 0x005F9450
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;
}

namespace EA {
eastl::string16 ConvertToString16(const char* p, int length = -1);   // 0x0093C5A0
eastl::string16 ConvertToString16(const eastl::string& s);           // 0x0093C6D0
}

// ---------------------------------------------------------------- editor / UI
struct cAppModeEditorBase {
    char pad78[0x78];
    cSPEditorUI* mpEditorUI;        // +0x78
    char pad7c[0x358 - 0x7c];
    void* mPaintPaletteObject;      // +0x358
};

struct cSPEditorUI {
    char pad[0x14];
    void EnableUIButton(uint32_t id, bool b);     // 0x005DC610
    IWindow* FindWindowByID(uint32_t id);         // 0x005DC310
};

struct cSPUILayout {
    char pad[0x18];
    bool IsVisible();                                         // 0x00810070
    IWindow* FindWindowByID(uint32_t id, bool recurse);       // 0x008105B0
    void Shutdown(bool b);                                    // 0x00811AD0
};

struct cSPEditorNaming { void ResetParentWin(); };            // 0x005BFB70

// ---------------------------------------------------------------- interfaces
struct IOther {
    virtual void o00(); virtual void o01(); virtual void o02(); virtual void o03(); virtual void o04();
    virtual void o05(); virtual void o06(); virtual void o07(); virtual void o08(); virtual void o09();
    virtual void o10(); virtual void o11(); virtual void o12(); virtual void o13(); virtual void o14();
    virtual void o15(); virtual void o16(); virtual void o17(); virtual void o18(); virtual void o19();
    virtual void o20(); virtual void o21(); virtual void o22(); virtual void o23(); virtual void o24();
    virtual void o25(); virtual void o26(); virtual void o27(); virtual void o28(); virtual void o29();
    virtual void o30(); virtual void o31(); virtual void o32(); virtual void o33(); virtual void o34();
    virtual void o35(); virtual void o36(); virtual void o37(); virtual void o38(); virtual void o39();
    virtual void o40(); virtual void o41(); virtual void o42(); virtual void o43(); virtual void o44();
    virtual void o45(); virtual void o46(); virtual void o47(); virtual void o48(); virtual void o49();
    virtual void o50(); virtual void o51(); virtual void o52(); virtual void o53(); virtual void o54();
    virtual void Attach(IWindow* p);              // +0xDC
};

struct IWindow {
    virtual void v00();
    virtual int Release();                                    // +0x04
    virtual void v02();
    virtual IControl* v03(uint32_t id);                       // +0x0C
    virtual IOther* GetOther();                               // +0x10
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual uint8_t v10();                                    // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual const wchar_t* GetText();                         // +0x3C
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void SetFlag(int flag, int on);                   // +0x7C
    virtual void SetCaption(const wchar_t* text);             // +0x80
    virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
    virtual void v53(); virtual void v54(IWindow* p);         // +0xD8
    virtual void v55(IWindow* p);                             // +0xDC
};

struct IControl {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03(); virtual void c04();
    virtual void c05(); virtual void c06(); virtual void c07(); virtual void c08(); virtual void c09();
    virtual void SetMode(int a, int b);                       // +0x28
};

// ---------------------------------------------------------------- helpers
struct cProfScope { void End(); };                            // 0x0067C420
cProfScope* __stdcall BeginProfScope(int a, int b);           // 0x0067CAC0
void EndModal(IWindow* w, int a, int b);                      // 0x00809C50 (cdecl)

// A struct of four eastl::string (member offsets 0,0x10,0x20,0x30).
struct cFourStrings {
    eastl::string a, b, c, d;
    ~cFourStrings();
};

// ---------------------------------------------------------------- cSPPlayModeUI
struct cSPPlayModeUI {
    char pad0[0xC];
    cAppModeEditorBase* mpEditor;       // +0x0C
    void* mpPlayMode;                   // +0x10
    cSPUILayout mLayout;                // +0x14
    cSPUILayout mCameraControlsLayout;  // +0x2C
    bool mbLayoutInit;                  // +0x44
    char pad45[0x64 - 0x45];
    IWindow* mpMovieSavedDialog;        // +0x64

    IWindow* FindPlayModeUIWindow(uint32_t id);               // 0x00634DC0
    void SetUIGroupVisible(uint32_t id, bool on);             // 0x00635760
    void EnablePhotoViewerButton(bool b);                     // 0x00636320
    void HideMovieSavedDialogCustom();                        // 0x006364A0
    bool DoMessageInternal(uint32_t a, void* msg);            // 0x00636560
    bool Shutdown();                                          // 0x006373E0
    void SetYTUsername(const eastl::string& s);               // 0x006374B0
    void SetYTPassword(const eastl::string& s);               // 0x00637510
    void GetEditorText(uint32_t id, eastl::string* out);      // 0x006377D0
    void GetYTUsername(eastl::string* out);                   // 0x00637800
    void GetYTPassword(eastl::string* out);                   // 0x00637830
    void ShowSendEmailDialog();                               // 0x00637860
    void SendVideoURLInfoToServer();                          // 0x00637C90
    void ResetSendEmailWindow();                              // 0x00635520
    void HideYouTubeLoginDialog();                            // 0x00636260
};
