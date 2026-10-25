// slice s0057f420 — SP::cUnkF420 ArgScript "export paint theme" cheat handler.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same family as the other SPAppModeEditorBase
// functions; the deferred cdecl stack clean-ups and the tail-merged epilogues are optimized codegen).
// The handler validates the locale, checks that the creature editor is in paint mode with a named,
// finished creature, then exports the current paint theme to "<name>.dae".
#include "types.h"
#include <intrin.h>

typedef unsigned int size_t;

// ---------------------------------------------------------------------------------------------
// EASTL string16 pieces
namespace eastl {
extern wchar_t gEmptyString[2];   // 0x01667BAC

template <typename T> struct basic_string {
    T* mpBegin;          // +0x0
    T* mpEnd;            // +0x4
    T* mpCapacity;       // +0x8
    uint32_t mAllocator; // +0xc

    basic_string() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~basic_string() { DeallocateSelf(); }

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    void DeallocateSelf();   // 0x00933960
};
typedef basic_string<wchar_t> string16;
}  // namespace eastl

// ---------------------------------------------------------------------------------------------
// Callees (external, relocated in the original)
namespace EA { namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(size_t* pCount, int minCount, int maxCount);   // 0x00838020 (ret 0xc)
};
void Output(int* pOutput, const char* pFormat, ...);   // 0x00841000
} }

namespace EA { namespace IO {
void SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
               wchar_t* pExtension, int flags);   // 0x00930180
} }

bool GetBoolProperty(void* pPropertyList, uint32_t propertyID, bool* pOut);   // 0x00407190
extern void* _sAppPreferences_SP;                                             // 0x015FD91C

// eastl::basic_string<wchar_t>::sprintf as an out-of-line cdecl helper taking the destination first.
int WStr_Format(eastl::string16* pDst, const wchar_t* pFormat, ...);   // 0x0041E050

// eastl::operator==(const string16&, const wchar_t*)
bool FUN_006ab760(const eastl::string16& lhs, const wchar_t* rhs);   // 0x006AB760

// Global localization singleton: vtable slot +0x14 returns the current language string.
class cLocalization {
public:
    virtual void l00(); virtual void l04(); virtual void l08(); virtual void l0c(); virtual void l10();
    virtual const eastl::string16& GetLanguage();   // +0x14
};
cLocalization* GetLocalization();   // 0x0067DE40

// Paint-theme source used by the exporter (see s0057bfb0).
class cPaintThemeSource {
public:
    void GetPath(uint32_t themeID, eastl::string16* pOut);   // 0x005F9230
};
cPaintThemeSource* GetPaintThemeSource();   // 0x005F7930

class cSPEditorModel {
public:
    const wchar_t* GetFileName();   // 0x004AE000
};

class cSPEditorSkinManager {
public:
    bool IsBusy();   // 0x004C58B0
};

// ---------------------------------------------------------------------------------------------
// The editor the cheat operates on (layout offsets taken from the disassembly; see s0057bfb0).
class cAppModeEditorBase {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual cSPEditorModel* GetSaveModel();   // +0x40

    char pad04[0x150 - 0x04];                 // +0x04 .. +0x150
    cSPEditorSkinManager* mpSkinManager;      // +0x150
    char pad154[0x2a8 - 0x154];               // +0x154 .. +0x2a8
    uint32_t m2a8;                            // +0x2a8
    char pad2ac[0x2b0 - 0x2ac];               // +0x2ac .. +0x2b0
    bool mb2b0;                               // +0x2b0
    char pad2b1[0x31c - 0x2b1];               // +0x2b1 .. +0x31c
    int m31c;                                 // +0x31c

    bool ExportPaintTheme(bool showDialog);   // 0x0057C590
};

// ---------------------------------------------------------------------------------------------
// ArgScript cheat-command object (the receiver).
class cUnkF420 {
public:
    virtual void v00();   // +0x00
    virtual void v04();   // +0x04
    virtual void v08();   // +0x08
    virtual void v0c();   // +0x0c  (run preamble)
    virtual void v10();   // +0x10  (run epilogue)

    int* mOutput;                       // +0x04
    uint32_t pad08;                     // +0x08
    uint32_t pad0c;                     // +0x0c
    cAppModeEditorBase* mpEditor;       // +0x10

    void FUN_0057f420(void* args);
};

// ---------------------------------------------------------------------------------------------
__forceinline size_t WcsLen(const wchar_t* p)
{
    const wchar_t* q = p;
    while (*q)
        ++q;
    return (size_t)(q - p);
}

// @ 0x0057f420  cUnkF420::FUN_0057f420
void cUnkF420::FUN_0057f420(void* argsPtr)
{
    if (this)
        v0c();

    EA::ArgScript::cArguments* args = (EA::ArgScript::cArguments*)argsPtr;
    size_t count;
    args->MainArguments(&count, 0, 0x7fffffff);

    if (!FUN_006ab760(GetLocalization()->GetLanguage(), L"en-us") &&
        !FUN_006ab760(GetLocalization()->GetLanguage(), L"en-us") &&
        !FUN_006ab760(GetLocalization()->GetLanguage(), L"en-gb")) {
        EA::ArgScript::Output(mOutput,
            "This cheat is not supported in the current language.\nLaunch the game with the "
            "command line parameter '-locale:en-us' to use this cheat.\n");
        v10();
        return;
    }

    if (!mpEditor->mb2b0 || mpEditor->m2a8 != 0x2b978c46) {
        EA::ArgScript::Output(mOutput,
            "switch to the creature editor or an outfitter before running this cheat\n");
        v10();
        return;
    }
    if (mpEditor->m31c != 1) {
        EA::ArgScript::Output(mOutput, "switch to paint mode before running this cheat\n");
        v10();
        return;
    }

    if (mpEditor->GetSaveModel() == 0) {
        EA::ArgScript::Output(mOutput,
            "creature must have a name before running this cheat\n");
        v10();
        return;
    }
    const wchar_t* creatureName = mpEditor->GetSaveModel()->GetFileName();
    if (creatureName == 0 || WcsLen(creatureName) == 0) {
        EA::ArgScript::Output(mOutput,
            "creature must have a name before running this cheat\n");
        v10();
        return;
    }

    cSPEditorSkinManager* skinManager = mpEditor->mpSkinManager;
    if (skinManager == 0) {
        v10();
        return;
    }
    if (skinManager->IsBusy()) {
        EA::ArgScript::Output(mOutput,
            "creature must be finished painting before running this cheat\n");
        v10();
        return;
    }

    eastl::string16 themePath;
    cPaintThemeSource* source = GetPaintThemeSource();
    if (source == 0) {
        EA::ArgScript::Output(mOutput, "export failed\n");
        v10();
        return;
    }
    source->GetPath(0x2b978c46, &themePath);
    if (themePath.empty()) {
        EA::ArgScript::Output(mOutput, "export failed\n");
        v10();
        return;
    }

    wchar_t fileName[260];
    EA::IO::SplitPath(creatureName, 0, 0, fileName, 0, 4);
    eastl::string16 exportPath;
    WStr_Format(&exportPath, L"%ls%ls.dae", themePath.c_str(), fileName);

    bool showDialog = false;
    GetBoolProperty(_sAppPreferences_SP, 0x87c4363, &showDialog);

    if (mpEditor->ExportPaintTheme(showDialog == 0))
        EA::ArgScript::Output(mOutput, "exported to %ls\n", exportPath.c_str());
    else
        EA::ArgScript::Output(mOutput, "export failed\n");

    v10();
}
