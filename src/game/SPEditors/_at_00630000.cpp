// src/game/SPEditors/_at_00630000.cpp -- migrated from slice(s) s0063aa90, s00634490, s0062f6e0 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00630000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cJob.h"
#include "SP/cPlayModePhoto.h"
#include "SP/cSPPlayModeBGInfo.h"
#include "SP/cSPPlayModeBGMgr.h"
#include "SP/cSPPlayModePhotoBrowser.h"
#include "SP/cSPPlayModeUI.h"
#include <intrin.h>
#include "SP/cPropertyList.h"
#include "EA/Stopwatch.h"
#include "SP/cPlayModeTokenTranslator.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorUI.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "SP/cSPPlayModeSubModeBase.h"
#include "SP/cSPPlayModeSubModeDance.h"
#include "SP/cSPPlayModeSubModeMovie.h"
#include "cSPUILayout.h"
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _rotl)

// ---- items of slice s0062f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRef(const AutoRef& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
template <class T> struct SPVec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    SPVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SPVec();
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* erase(T* first, T* last);
    T* insert(T* pos, const T& v);
    void DoInsertValueEnd(T* pos, const T& v);
};
struct cSPPlayModeUI {
    void* FindPlayModeUIWindow(uint32_t id);
    void* FindEditorUIWindow(uint32_t id);
    void SetUIGroupVisible(uint32_t id, bool v);
    void SetEditorUIGroupVisible(uint32_t id, bool v);
    void SetEditorUIEnabled(uint32_t id, bool v);
    void SetEnabled(uint32_t id, bool v);
    void ToggleUIGroup(uint32_t id, bool v);
};
struct cJob {
    int ContinueJob();         // 0x0068f970
    void Cancel(int);          // 0x00692400
    void AddRef();             // 0x0068f950
    void Release();            // 0x00690120
};
struct cPlayModePhoto {
    virtual void d0();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[0x30 / 4 - 1];
    AutoRef<cJob> writeJob;    // +0x30 (retail layout; PDB has it at the same place)
    AutoRef<cJob> loadJob;     // +0x34
    uint8_t bIsSelected;       // +0x38
    uint8_t bIsLoaded;         // +0x39
};
struct UIImage : IRefCount {
    uint32_t pad[4];
    UIImage(void* raster);                   // 0x008333b0
    int GetWidth();                          // 0x008332a0
    int GetHeight();                         // 0x008332d0
};
struct UIImageView {
    UIImageView(UIImage* img, int w, int h, float u0, float v0, float u1, float v1, int flag); // 0x009579f0
};
struct cSPPlayModePhotoBrowser {
    virtual void v0();
    SPVec<AutoRef<cPlayModePhoto> > mPhotos;   // +0x04
    uint32_t pad0[2];
    uint32_t mCurrentFirstPhotoIndex;          // +0x18
    uint32_t mCurrentSelectedPhotoIndex;       // +0x1c
    uint32_t pad1;
    cSPPlayModeUI* mUI;                        // +0x24
    uint32_t pad2[(0x54 - 0x28) / 4];
    uint32_t mMode;                            // +0x54
    uint32_t pad3[(0xe8c - 0x58) / 4];
    void* mAsyncHandle;                        // +0xe8c

    void EnterMoveMode();
    void EnterDeleteMode();
    void ExitDeleteMode();
    void ExitMoveMode();
    uint8_t IsSendPhotoWinVisible();
    cPlayModePhoto* GetPhotoAt(uint32_t idx, bool relative);
    void SelectAll(bool v);
    static UIImageView* __stdcall GetImageFromRaster(void* raster);
    cPlayModePhoto* FindPhotoByGuid(uint32_t guid);
    void ReleaseAsyncHandle();
    cJob* CancelAllPendingLoadJobs();
    int IsPhotosWriting();
    bool AnyWriteJobActive();
    void UpdatePageButtons(int unused);
};
// ---- items of slice s0062f6e0 end

// ---- items of slice s00634490 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct wstring16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    wstring16& operator=(const wchar_t* p);   // 0x005c3d90
};
struct cStringTokenTranslator {
    virtual void v0();
    uint32_t pad;
    cStringTokenTranslator();     // 0x006b5870
};
struct cPlayModeTokenTranslator : cStringTokenTranslator {
    uint32_t pageCurrent;         // +0x08
    uint32_t pageCount;           // +0x0c
    uint32_t photoCurrent;        // +0x10
    uint32_t photoCount;          // +0x14
    const wchar_t* movieName;     // +0x18
    const wchar_t* moviePathname; // +0x1c
    uint32_t bgPageCurrent;       // +0x20
    uint32_t bgPageCount;         // +0x24
    uint32_t animPageCurrent;     // +0x28
    uint32_t animPageCount;       // +0x2c
    const wchar_t* videoURL;      // +0x30
    const wchar_t* statusMessage; // +0x34
    const wchar_t* gifName;       // +0x38
    const wchar_t* mayaExportName;// +0x3c
    const wchar_t* mayaExportPath;// +0x40
    const wchar_t* mYear;         // +0x44
    const wchar_t* mMonth;        // +0x48
    const wchar_t* mDayOfMonth;   // +0x4c
    const wchar_t* mTime;         // +0x50
    const wchar_t* mUnused54;     // +0x54
    const wchar_t* movieNamePrefix; // +0x58
    const wchar_t* mUnused5c;     // +0x5c

    cPlayModeTokenTranslator();
    bool TranslateToken(const wchar_t* token, wstring16* out);
};
// ---- items of slice s00634490 end

// ---- items of slice s0063aa90 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cEditorMode2 {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual char* GetSaveInfo();
    void SaveModel(char* p, bool b);                                    // 0x0057F6C0
    void FUN_00574110(uint32_t id, int a, float b, float c);            // 0x00574110
    void OnLayout(int a, int b);                                        // 0x00B267F0
};
class cPlayModeUI2 { public: void SetEnabled(uint32_t id, bool b); };   // 0x00634EF0
class cSPPlayMode {
public:
    void WakeupCreature();                                              // 0x0062A760
    void FUN_00628810();                                                // 0x00628810
    void SetAllBabySitUp();                                             // 0x00629220
    char pad0[0xc]; cPlayModeUI2* mpUI;                                 // +0xc
    char pad1[0x1d - 0x10]; uint8_t mB1d, mB1e;                         // +0x1d, +0x1e
    char pad2[0x28 - 0x1f]; float mF28, mF2c, mF30;                     // +0x28..
};
class cSPPlayModeAnimation2 {
public:
virtual void v0();
virtual void v1();
virtual void v2();
    virtual float PlayAnimation(uint32_t creatureID, uint32_t animID, int a, int b, void* c);  // +0xc
};
class cSPPlayModeSubModeBase {
public:
    virtual void v0();
    void Init(void* params);                                            // 0x0063B270 (called out of line from other TUs; body below as InitCopy)
    void InitCopy(void* params);
    cEditorMode2* mEditorBaseMode;                                      // +0x4
    cSPPlayModeAnimation2* mAnim;                                       // +0x8
    void* mSubModeParams;                                               // +0xc
    cSPPlayMode* mPlayMode;                                             // +0x10
};
class cSPPlayModeSubModeDance : public cSPPlayModeSubModeBase {
public:
    cSPPlayModeSubModeDance();
    void Init(void* params);
    bool IsDancingAnim(uint32_t animID, bool baby);
    bool HandleButton(uint32_t id);

    char pad14[0x28 - 0x14];
    uint32_t mField28;                                                  // +0x28
    uint32_t mDanceMovesGUID[6];                                        // +0x2c
    uint32_t mBabyDanceMovesGUID[6];                                    // +0x44
    uint8_t mField5c;                                                   // +0x5c (inside event array slot)
    char pad5d[3];
    uint32_t mDanceEventIDs[6];                                         // +0x60
};
// ---- items of slice s0063aa90 end

// @ 0x00630060
cPlayModePhoto* cSPPlayModePhotoBrowser::GetPhotoAt(uint32_t idx, bool relative)
{
    uint32_t i = relative ? mCurrentFirstPhotoIndex + idx : idx;
    if (i < mPhotos.size())
        return mPhotos.mpBegin[i].mpObject;
    return 0;
}

// @ 0x006345b0
cPlayModeTokenTranslator::cPlayModeTokenTranslator()
: cStringTokenTranslator()
{
    movieName = 0;
    moviePathname = 0;
    videoURL = 0;
    statusMessage = 0;
    gifName = 0;
    mayaExportName = 0;
    mayaExportPath = 0;
    mYear = 0;
    mMonth = 0;
    mDayOfMonth = 0;
    mTime = 0;
    mUnused54 = 0;
    movieNamePrefix = 0;
    mUnused5c = 0;
    pageCurrent = 0;
    pageCount = 0;
    photoCurrent = 0;
    photoCount = 0;
    bgPageCurrent = 0;
    bgPageCount = 0;
    animPageCurrent = 0;
    animPageCount = 0;
}

// @ 0x0063b5a0
cSPPlayModeSubModeDance::cSPPlayModeSubModeDance()
{
    char* p = (char*)this;
    *(uint32_t*)(p + 0x14) = 0;
    *(uint32_t*)(p + 0x18) = 0;
    *(uint32_t*)(p + 0x1c) = 0;
    *(uint32_t*)(p + 0x20) = 0;
}
