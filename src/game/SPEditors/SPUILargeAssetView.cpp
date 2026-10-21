// src/game/SPEditors/SPUILargeAssetView.cpp -- migrated from slice(s) s0066ee50, s0066daf0, s0066ce00, s0066bf70, s0066afd0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUILargeAssetView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include "SP/eModelType.h"
#include "EA/ResourceMan/Key.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern float gF13eb960;   // 0x013eb960
extern float gF13ef580;   // 0x013ef580
extern int   gVt140075c;  // 0x0140075c

// ---- items of slice s0066afd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef char  (__thiscall *FnChrIP)(void*, int, void*);
#define VT(p) (*(void***)(p))
struct RefObj {
    virtual void v0();       // +0x00 AddRef
    virtual int  Release();  // +0x04
    virtual void Release2(); // +0x08
    virtual void v3();       // +0x0c
};
struct IWindow {
    virtual void AddRef();                     // 0x00
    virtual int  Release();                    // 0x04
    virtual void v02();                        // 0x08
    virtual IWindow* FindWindow(unsigned id);  // 0x0c
};
struct cSPUILayout_s0066_afd0 {
    virtual void s0();
    virtual void s1();
    virtual int  Release();
    IWindow* FindWindowByID(unsigned id, int flag);   // 0x008105b0
};
void* __cdecl SP_AssetBrowser();                   // 0x00401030
struct Prop { float* GetFloat(); };                // 0x0041ea70
extern float gF13eb960;   // 0x013eb960
extern float gF13ef580;   // 0x013ef580
extern int   gVt140075c;  // 0x0140075c
struct ColourCfg {
    void FUN_0066bd80(cSPUILayout_s0066_afd0* layout);
};
// ---- items of slice s0066afd0 end

// ---- items of slice s0066bf70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int gVt13ef094;   // 0x013ef094
typedef void  (__thiscall *FnVoidI)(void*, int);
void  __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380
void  __cdecl FUN_00f47040(void* p);                 // 0x00f47040
void* __cdecl SP_AppSystem();                        // 0x0067dd00
void  __cdecl FUN_00571db0(void* h, void* a, void* b, void* c, void* d);
struct RefObj_s0066_bf70 {
    virtual void v0();
    virtual int  Release();
    virtual void Release2();
};
struct cSPUILayout_s0066_bf70 {
    virtual void s0();
    virtual void s1();
    virtual int  Release();
    void Shutdown(bool);  // 0x00811ad0 (cSPUILayout::Shutdown)
};
struct Sub64 { void FUN_006571e0(int, int, int); };
struct Cb70 {
    Cb70* FUN_0066cb70(unsigned flags);
};
// ---- items of slice s0066bf70 end

// ---- items of slice s0066ce00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kCalloutText[];                               // 0x01527F2C
struct ResKey { uint32_t instance, type, group; };
struct MsgWindow
{
	virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
	virtual void w4(); virtual void w5(); virtual void w6();
	virtual uint32_t GetControlID() const;   // +0x1c
};
struct Message
{
	MsgWindow* source;   // +0x00
	int field04;         // +0x04
	uint32_t eventType;  // +0x08
	int field0C;         // +0x0c (kMsgComponentActivated: command/event id)
	int field10;         // +0x10 (key code for key messages)
};
struct cPropertyList
{
	bool GetDescription(uint32_t id) const;   // 0x006A25A0 (returns "has property id")
};
extern cPropertyList* sAppProperties;         // 0x015FD918
int      __cdecl KeyGetAxis(ResKey* key, uint32_t axis);                  // 0x00556140
void     __cdecl KeyResetAxis(ResKey* key, uint32_t axis);                // 0x005562A0
void     __cdecl KeySetValue(ResKey* key, uint32_t value);                // 0x00555F70
uint32_t __cdecl KeyCombine(int a, int b, int c, int d);                  // 0x00556440
bool     __cdecl IsLinkedActive(void* obj);                               // 0x008050B0
struct MsgServer
{
	virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
	virtual void Send(uint32_t id, void* data, int z);   // +0x14
};
MsgServer* __cdecl GetMessageServer();                    // 0x0067DCC0
struct WinMgrObj
{
	virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5();
	virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void pA(); virtual void pB();
	virtual void pC();
	virtual void Apply34(void* v);                        // +0x34
};
struct WinMgr
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void Apply10(void* v);                        // +0x10
};
WinMgr* __cdecl GetWindowManager();                       // 0x0067CAA0 (SP::WindowManager)
struct Singleton67de40
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual WinMgrObj* GetTarget();                       // +0x20
};
Singleton67de40* __cdecl GetSingleton67de40();            // 0x0067DE40
struct PtrVec
{
	void** mBegin; void** mEnd; void** mCap;
	uint32_t mAllocator[2];   // eastl allocator state (untouched by the ctor)
	PtrVec() : mBegin(0), mEnd(0), mCap(0) {}
	~PtrVec();                                            // 0x007A41A0
};
struct SpaceInv
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8();                                    // +0x20
	void SetItem(void* item);                             // 0x00599BE0 (TraitSuperPowerRollover wrapper)
	void SetActive();                                     // 0x00599530
	void SetInactive();                                   // 0x00599560
	void* GetRootWindow();                                // 0x00828100
};
void __cdecl SetWindowParent(void* w, void* root, int flag);   // 0x00808B20
void __cdecl CalloutMessageBox(void* where, const void* what); // 0x00809DB0
struct TextZoomName
{
	void Activate(int a);     // 0x00834A00
	void Deactivate(int a);   // 0x00834C60
};
struct FlagsObj   // flags at +4
{
	uint32_t pad;
	uint32_t flags;
	bool Test(int bit) const { return ((flags >> bit) & 1) != 0; }
	void Set(int bit) { flags |= (1u << bit); }
	void Clear(int bit) { flags &= ~(1u << bit); }
};
struct DoorObj   // object at this+0x70
{
	void Poke(int a, int b, int c);   // 0x006571E0 (thiscall, ret 0xc)
};
struct KeyPanel;   // the 0x66d430 owner
struct ObjHolder3c   // objects at this+0x3c / +0x40 (vtable +0x10 is used with 0 or 3 stack args)
{
	virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
	virtual int Slot4();   // +0x10
};
struct MetaObj
{
	__int64 GetAssetKey() const;   // 0x005508A0
};
struct ChildPanel    // object at this+0x7c: window-ish with HandleMessage at +0x18, +0x34 getter, +0x118 flags object
{
	virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
	virtual void c4(); virtual void c5();
	virtual bool HandleMessage(void* window, Message* msg);   // +0x18
	virtual void c7(); virtual void c8(); virtual void c9(); virtual void cA(); virtual void cB();
	virtual void cC();
	virtual void* GetLinkable();                              // +0x34
	char pad[0x118 - 4];
	FlagsObj* mpFlags;   // +0x118
};
struct KeyPanel
{
	char       pad04[0x3c - 0];
	ObjHolder3c* mp3c;    // +0x3c
	ObjHolder3c* mp40;    // +0x40
	char       pad44[0x70 - 0x44];
	DoorObj*   mp70;      // +0x70
	void*      mp74;      // +0x74  (ItemSource-like, accessed through raw vtable slots)
	MetaObj*   mp78;      // +0x78
	ChildPanel* mp7c;     // +0x7c
	void*      mp80;
	SpaceInv*  mp84;      // +0x84
	char       pad88[0x90 - 0x88];
	TextZoomName* mp90;   // +0x90

	bool HandleMessage(void* window, Message* msg);
};
typedef ResKey*   (__thiscall *FnGetKey)(void*);
typedef bool      (__thiscall *FnFill)(void*, PtrVec*);
typedef int       (__thiscall *FnSlot4b)(void*, void*, Message*, int);
typedef void*     (__thiscall *FnSlot4c)(void*, int);
// ---- items of slice s0066ce00 end

// ---- items of slice s0066daf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
void operator delete[](void* p);
namespace SP {
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i = 0, uint32_t t = 0, uint32_t g = 0) : instanceID(i), typeID(t), groupID(g) {}
};
}
namespace SP {
struct Rect {
    float x1, y1, x2, y2;
    Rect(const Rect& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
    Rect& operator=(const Rect& r) { x1 = r.x1; y1 = r.y1; x2 = r.x2; y2 = r.y2; return *this; }
};
}
namespace SP {
struct Point {
    float x, y;
    Point(float ax, float ay) : x(ax), y(ay) {}
};
}
namespace SP {
struct IWindow_s0066_daf0 {
    virtual int AddRef();                                   // 0x00
    virtual int Release();                                  // 0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                    // 0x0C
    virtual IWindow_s0066_daf0* GetParent();                           // 0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual const Rect& GetArea();                          // 0x34
    virtual const Rect& GetRealArea();                      // 0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60();
    virtual void SetLocation(float x, float y);             // 0x64
    virtual void v68();
    virtual void SetLayoutArea(const Rect& area);           // 0x6C
    virtual void v70(); virtual void v74();
    virtual void SetCursorID(uint32_t id);                  // 0x78
    virtual void SetFlag(int flag, bool value);             // 0x7C
    virtual void SetCaption(const wchar_t* caption);        // 0x80
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4(); virtual void vd8(); virtual void vdc(); virtual void ve0();
    virtual void ve4(); virtual void ve8(); virtual void vec(); virtual void vf0();
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(void* winProc);                 // 0x104
};
}
namespace SP {
struct cSPUILayout {
    IWindow_s0066_daf0* FindWindowByID(uint32_t id, bool recursive);   // 008105B0
};
}
namespace SP {
struct ICastable {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Cast(uint32_t typeID);                    // 0x0C
};
}
namespace SP {
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    string16();
    ~string16();
    const wchar_t* c_str() const { return mpBegin; }
};
}
namespace SP {
extern wchar_t gEmptyString16[1];                           // 01667BAC
}
namespace SP {
inline string16::string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
}
namespace SP {
inline string16::~string16() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
        operator delete[](mpBegin);
}
}
namespace SP {
struct IAssetData {
    virtual int AddRef();                                   // 0x00
    virtual int Release();                                  // 0x04
    virtual void v08();
    virtual const wchar_t* GetName();                       // 0x0C
    virtual const wchar_t* GetAuthor();                     // 0x10
    virtual const wchar_t* GetDescription();                // 0x14
    virtual void v18(); virtual void v1c();
    virtual void GetTags(string16& out);                    // 0x20
    virtual uint32_t GetModelType();                        // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int GetParentID();                              // 0x38
    virtual float GetSize();                                // 0x3C
    virtual const ResourceKey* GetKey();                    // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual bool HasVerbs();                                // 0x64
    virtual void v68(); virtual void v6c();
    virtual bool IsPublished();                             // 0x70

    uint32_t pad04[3];
    ICastable mObject;                                      // +0x10
};
}
namespace SP {
struct cPlayableAsset {
    bool IsPlayable();                                      // 006418E0
};
}
namespace SP {
struct cAssetMetadata {
    uint64_t GetAssetKey();                                 // 005508A0
};
}
namespace SP {
struct IAuthManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool IsOffline();                               // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c();
    virtual uint64_t GetUserID();                           // 0x40
};
}
namespace SP {
struct cDownloadEntry {                                     // 0x70 bytes
    uint32_t pad00[4];
    uint64_t mAssetKey;                                     // +0x10
    uint32_t pad18[(0x68 - 0x18) / 4];
    int      mState;                                        // +0x68
    uint32_t pad6c;
};
}
namespace SP {
struct cDownloadList {
    cDownloadEntry* mpBegin;
    unsigned size();                                        // 0065B160
};
}
namespace SP {
struct cDownloadManager {
    uint32_t pad00[0xc8 / 4];
    cDownloadList mList;                                    // +0xC8
};
}
namespace SP {
struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey& key, ResourceObject** ppOut,
                             int a, int b, int c, int d);   // 0x0C
};
}
namespace SP {
struct cPropertyList_s0066_daf0 {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
struct IPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s0066_daf0** ppOut); // 0x2C
};
}
namespace SP {
struct IModelManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void SetPreviewModel(int model);                // 0x24
};
}
namespace SP {
struct cDirectValues {
    uint32_t pad[0x118 / 4];
    int mOfflineMode;                                       // +0x118
};
}
namespace SP {
struct cDirectPropertyList_s0066_daf0 {
    uint32_t pad[0x3c / 4];
    cDirectValues* mpValues;                                // +0x3C
    bool GetDescription(uint32_t propertyID);               // 006A25A0 0x006a25a0
    float GetFloatProperty(uint32_t propertyID);            // 006A2710 0x006a2710
};
}
namespace SP {
extern cDirectPropertyList_s0066_daf0* gAppProperties;                 // 015FD918
}
namespace SP {
struct cSPUIAssetComments_s0066_daf0 {
    virtual int AddRef();
    virtual int Release();
    cSPUIAssetComments_s0066_daf0();                                   // 0064E170
    void Init(IWindow_s0066_daf0* window);                             // 0064E230 0x0064e230
    uint32_t pad04[(0x78 - 4) / 4];
};
}
namespace SP {
struct cSPUIMissingExpansionPackPage_s0066_daf0 {
    virtual int AddRef();
    virtual int Release();
    cSPUIMissingExpansionPackPage_s0066_daf0();                        // 006715D0
    void Init(IWindow_s0066_daf0* window);                             // 00671690 0x00671690
    uint32_t pad04[(0x78 - 4) / 4];
};
}
namespace SP {
struct cSPCardInventory {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual void Show();                                    // 0x1C
    cSPCardInventory();                                     // 005994D0
    void SetMessageID(uint32_t id, int value);              // 00827FA0
    uint32_t pad04[(0xb0 - 4) / 4];
};
}
namespace SP {
struct cSPCardStats {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c();
    virtual void Load(cSPUILayout* layout, cAssetMetadata* metadata);   // 0x20
    cSPCardStats();                                         // 006700D0
    uint32_t pad04[(0xd0 - 4) / 4];
};
}
namespace SP {
struct cSPUIAssetVerbs_s0066_daf0 {
    virtual int AddRef();
    virtual int Release();
    cSPUIAssetVerbs_s0066_daf0();                                      // 00656B00
    void Init(IWindow_s0066_daf0* window);                             // 00656B80 0x00656b80
    uint32_t pad04[(0x5c - 4) / 4];
};
}
namespace SP {
struct TextZoomName_s0066_daf0 {
    TextZoomName_s0066_daf0();                                         // 008345C0
    void SetTargetWindow(void* window, int a, int b, int c, ResourceKey key);  // 00834FA0
    uint32_t pad00[0x78 / 4];
};
}
namespace SP {
struct cVerbIconSlot {
    uint32_t GetSoundID();                                  // 01137690
    float GetSize();                                        // 00885D10
};
}
namespace SP {
struct cVerbTrayBase {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c();
    virtual void Load(IWindow_s0066_daf0* window, ResourceKey key, int keys, int count, int flags); // 0x10
    virtual void v14();
    virtual void Clear();                                   // 0x18
    int GetIconCount();                                     // 00605930
    float GetHeight();                                      // 006058B0
    cVerbIconSlot* GetSlot(int index);                      // 005C1CE0
};
}
namespace SP {
struct cSPVerbTray : cVerbTrayBase {
    cSPVerbTray();                                          // 005E0CF0
    uint32_t pad04[(0xbc - 4) / 4];
};
}
namespace SP {
struct cSPSporepediaVerbTray : cVerbTrayBase {
    cSPSporepediaVerbTray();                                // 005E8920
    uint32_t pad04[(0x54 - 4) / 4];
};
}
namespace SP {
struct cSwatchModel {
    int GetModel();                                         // 005F2770
};
}
namespace SP {
struct cSPSwatch_s0066_daf0 {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual void SetActive(bool active);                    // 0x2C
    uint32_t pad04[3];
    cSwatchModel mModel;                                    // +0x10
    char pad14[0x163 - 0x14];
    bool mIsAnimated;                                       // +0x163

    void Init(const ResourceKey& key, IWindow_s0066_daf0* window, int a, int b, int c, int d, uint32_t modelType); // 005F4F80 0x005f5000
    void SetUpdating(int value);                            // 005F2260
    void SetEditorCameraController(int value);              // 005F6500 0x005f6500
};
}
namespace SP {
class cSPSwatchManager { public:
    cSPSwatch_s0066_daf0* CreateSwatch(int flags);                     // 005F0CA0
};
}
namespace SP {
struct cCardRollover {
    virtual ~cCardRollover();
    int   mnRefCount;   // +0x04
    int   field_08;
    int   field_0c;
    int   field_10;
    int   field_14;
    float mSpeedIn;     // +0x18
    float mSpeedOut;    // +0x1C

    cCardRollover() : mnRefCount(0), field_08(0), field_0c(0), field_10(0), field_14(0),
                      mSpeedIn(0.01f), mSpeedOut(0.02f) {}
    int AddRef() { return ++mnRefCount; }
    int Release() {
        if (--mnRefCount == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
    void Attach(cSPUILayout* layout);                       // 0066BD80
};
}
namespace SP {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    void Reset() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T** AsPPTypeParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace SP {
template <class T> struct AutoRefCountOOL {
    T* mpObject;
    AutoRefCountOOL() : mpObject(0) {}
    ~AutoRefCountOOL() { if (mpObject) mpObject->Release(); }
    AutoRefCountOOL& operator=(T* pObject);                 // 00B5F950
    T** AsPPTypeParam();                                    // 00A16F40
    __forceinline void Reset() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace SP {
struct TextZoomPtr {
    TextZoomName_s0066_daf0* mpObject;
    TextZoomPtr& operator=(TextZoomName_s0066_daf0* p);                // 00572620
    TextZoomName_s0066_daf0* operator->() const { return mpObject; }
};
}
namespace SP {
namespace SPUIHelpers {
void __cdecl SetWindowAreaToParent(IWindow_s0066_daf0* window);                      // 00806BF0
}
}
namespace SP {
namespace SPUIHelpers {
void __cdecl AutoSizeWindowForText(IWindow_s0066_daf0* window, int a, int b);        // 00806E40
}
}
namespace SP {
namespace SPUIHelpers {
void __cdecl CenterWindow(IWindow_s0066_daf0* window, Point center);                 // 00806CA0
}
}
namespace SP {
IAuthManager* __cdecl AuthManager();                                      // 00607A60
}
namespace SP {
cDownloadManager* __cdecl DownloadManager();                              // 0067CB30
}
namespace SP {
IResourceManager* __cdecl GetManager();  // EA::ResourceMan::GetManager 0067DCD0 (not the SP::ResourceManager wrapper 004DA3A0)
}
namespace SP {
IPropertyManager* __cdecl PropertyManager();                              // 0067DE30
}
namespace SP {
IModelManager* __cdecl ModelManager();                                    // 0067DD80
}
namespace SP {
cSPSwatchManager* __cdecl SwatchManager();                                // 00401020
}
namespace SP {
struct cAssetBrowser { uint32_t pad[0x1cc / 4]; uint32_t mFilterModelType; };
}
namespace SP {
cAssetBrowser* __cdecl AssetBrowser();                                    // 00401030
}
namespace SP {
int __cdecl GetEditorForModelType(uint32_t modelType);                    // 004BB860
}
namespace SP {
void __cdecl GetVerbIconKeysForLargeCard(uint32_t modelType, float size,
                                          ResourceKey* verbKey, ResourceKey* layoutKey); // 0066CD20
}
namespace SP {
void __cdecl GetPropertyArrayKeys(cPropertyList_s0066_daf0* props, uint32_t id, int* count, int* keys); // 006A0AE0
}
namespace SP {
bool __cdecl GetBoolProperty(cPropertyList_s0066_daf0* props, uint32_t id, bool& out);   // 00407190
}
namespace SP {
bool __cdecl GetPropertyAsKeyInstance(cPropertyList_s0066_daf0* props, uint32_t id, uint32_t* out); // 006A12A0
}
namespace SP {
bool __cdecl ComputeVerbIcons(const ResourceKey* key, ResourceObject** ppOut);           // 004BAFC0
}
namespace SP {
int __cdecl GetCreatureCaps(uint32_t modelType);                          // 004D1370
}
namespace SP {
void __cdecl FillCreatureVerbTray(ResourceObject* res, cVerbTrayBase* tray, int caps, float size); // 004E87F0
}
namespace SP {
struct cEditorResource_s0066_daf0;
}
namespace SP {
cEditorResource_s0066_daf0* __cdecl interface_cast_EditorResource(const AutoRefCount<ResourceObject>& res); // 00421EB0
}
namespace SP {
void __cdecl FillBuildingVerbTray(cEditorResource_s0066_daf0* res, cVerbTrayBase* tray);   // 004E6C10
}
namespace SP {
void __cdecl FillVehicleVerbTray(cEditorResource_s0066_daf0* res, cVerbTrayBase* tray);    // 004E7E50
}
namespace SP {
void __cdecl FillUFOVerbTray(cEditorResource_s0066_daf0* res, cVerbTrayBase* tray);        // 004E7DA0
}
namespace SP {
int __cdecl GetAssetKeyType(const ResourceKey* key);                      // 00552300
}
namespace SP {
uint32_t __cdecl RemapTypeId(uint32_t modelType);                         // 00432F10
}
namespace SP {
void __cdecl KillSetiEffects(uint32_t instanceID, uint32_t groupID);      // 00435ED0
}
namespace SP {
void __cdecl PlayEditorSound(uint32_t id, uint32_t param, float value, int flags); // 00435F40
}
namespace SP {
void __cdecl SetShaderParam(int index, float* value, int count);          // 00777AE0
}
namespace SP {
extern uint32_t gCardInventoryParam;                                      // 01527E74
}
namespace SP {
extern uint32_t gEditorConfigGroupID;                                     // 01527DA4
}
namespace SP {
struct cSPUILargeAssetView_s0066_daf0 {
    uint32_t pad00[6];
    cSPUILayout* mLayout;                                   // +0x18
    AutoRefCount<IWindow_s0066_daf0> mWinParent;                       // +0x1C
    AutoRefCount<IWindow_s0066_daf0> mWinRoot;                         // +0x20
    AutoRefCount<IWindow_s0066_daf0> mWinBakingArea;                   // +0x24
    AutoRefCount<IWindow_s0066_daf0> mWin28;                           // +0x28
    AutoRefCount<IWindow_s0066_daf0> mWinRenderWindow;                 // +0x2C
    AutoRefCount<IWindow_s0066_daf0> mWin30;                           // +0x30
    AutoRefCount<IWindow_s0066_daf0> mWinName;                         // +0x34
    AutoRefCount<IWindow_s0066_daf0> mWinAuthor;                       // +0x38
    AutoRefCount<IWindow_s0066_daf0> mWinDescription;                  // +0x3C
    AutoRefCount<IWindow_s0066_daf0> mWinTags;                         // +0x40
    AutoRefCount<IWindow_s0066_daf0> mWinVerbContainer;                // +0x44
    AutoRefCount<IWindow_s0066_daf0> mWinBakingForeground;             // +0x48
    AutoRefCount<IWindow_s0066_daf0> mWinPublished;                    // +0x4C
    AutoRefCount<IWindow_s0066_daf0> mWinShare;                        // +0x50
    AutoRefCount<IWindow_s0066_daf0> mWinShareIcon;                    // +0x54
    AutoRefCount<IWindow_s0066_daf0> mWinDownloaded;                   // +0x58
    AutoRefCount<IWindow_s0066_daf0> mWin5c;                           // +0x5C
    AutoRefCountOOL<cSPUIAssetComments_s0066_daf0> mCommentsBrowser;   // +0x60
    AutoRefCount<cSPUIMissingExpansionPackPage_s0066_daf0> mExpansionPackBrowser; // +0x64
    AutoRefCountOOL<cVerbTrayBase> mVerbIcons;                // +0x68
    AutoRefCount<IWindow_s0066_daf0> mWinAssetVerbs;                   // +0x6C
    AutoRefCount<cSPUIAssetVerbs_s0066_daf0> mAssetVerbs;              // +0x70
    AutoRefCount<IAssetData> mAssetData;                    // +0x74
    cAssetMetadata* mpMetadata;                             // +0x78
    AutoRefCount<cSPSwatch_s0066_daf0> mSwatch;                        // +0x7C
    AutoRefCount<cCardRollover> mRollover;                  // +0x80
    AutoRefCount<cSPCardInventory> mInventory;              // +0x84
    uint32_t field_88;
    AutoRefCount<cSPCardStats> mStats;                      // +0x8C
    TextZoomPtr mTextZoom;                                  // +0x90
    bool mIsOnline;                                         // +0x94
    Rect mBakingArea;                                       // +0x98
    bool mIsLoaded;                                         // +0xA8
    bool mIsPlayable;                                       // +0xA9
    bool field_aa;
    bool mHasResource;                                      // +0xAB
    bool mIsEditable;                                       // +0xAC
    float mSwatchZoom;                                      // +0xB0

    void UpdateDescription();                               // 0066D280
    void SetupAdventure();                                  // 0066C9E0
    void LoadAssetViewLarge();
};
}
// ---- items of slice s0066daf0 end

// @ 0x0066bd40
void* __fastcall FUN_0066bd40(void* self)
{
    float v0 = gF13eb960;
    ((uint32_t*)self)[1] = 0;
    *(void**)self = &gVt140075c;
    ((uint32_t*)self)[2] = 0;
    ((uint32_t*)self)[3] = 0;
    ((uint32_t*)self)[4] = 0;
    ((uint32_t*)self)[5] = 0;
    *(float*)((char*)self + 0x18) = v0;
    *(float*)((char*)self + 0x1c) = gF13ef580;
    return self;
}

// @ 0x0066bd80
void ColourCfg::FUN_0066bd80(cSPUILayout_s0066_afd0* layout)
{
    void* b = SP_AssetBrowser();
    if (b) {
        void* pi = *(void**)((char*)b + 0x18);
        if (pi) {
            void* prop;
            char c = ((FnChrIP)VT(pi)[9])(pi, 0xc97f8ee9, &prop);
            if (c && *(int16_t*)((char*)prop + 0x12) == 0xd) {
                float* f = ((Prop*)prop)->GetFloat();
                *(float*)((char*)this + 0x18) = *f;
            }
            c = ((FnChrIP)VT(pi)[9])(pi, 0x2034014d, &prop);
            if (c && *(int16_t*)((char*)prop + 0x12) == 0xd) {
                float* f = ((Prop*)prop)->GetFloat();
                *(float*)((char*)this + 0x1c) = *f;
            }
        }
    }
    if (!layout) return;
    {
        IWindow* w = layout->FindWindowByID(0x4cab570, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 8);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 8) = child;
                if (old) old->Release();
            }
        }
    }
    {
        IWindow* w = layout->FindWindowByID(0x4cab571, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 0xc);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 0xc) = child;
                if (old) old->Release();
            }
        }
    }
    {
        IWindow* w = layout->FindWindowByID(0x4cab56f, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 0x10);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 0x10) = child;
                if (old) old->Release();
            }
        }
    }
    {
        IWindow* w = layout->FindWindowByID(0x4cab56e, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 0x14);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 0x14) = child;
                if (old) old->Release();
            }
        }
    }
}

// @ 0x0066bf20
void __fastcall FUN_0066bf20(void* self)
{
    void* p;
    p = *(void**)((char*)self + 8);
    if (p) { *(void**)((char*)self + 8) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0xc);
    if (p) { *(void**)((char*)self + 0xc) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0x10);
    if (p) { *(void**)((char*)self + 0x10) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0x14);
    if (p) { *(void**)((char*)self + 0x14) = 0; ((RefObj*)p)->Release(); }
}

// @ 0x0066bf70
void __fastcall FUN_0066bf70(void* self)
{ (void)self; }

// @ 0x0066c0c0
void __fastcall FUN_0066c0c0(void* self)
{ (void)self; }

// @ 0x0066c370
void __fastcall FUN_0066c370(void* self)
{
    if (*(uint8_t*)((char*)self + 0xac)) {
        *(uint8_t*)((char*)self + 0xac) = 0;
        void* app = SP_AppSystem();
        ((FnVoidI)VT(app)[16])(app, 0);
    }
    *(uint8_t*)((char*)self + 0x9e) = 0;
    void* p;
    p = *(void**)((char*)self + 0xc);
    if (p) {
        ((cSPUILayout_s0066_bf70*)p)->Shutdown(true);
        if (p) { *(void**)((char*)self + 0xc) = 0; ((RefObj_s0066_bf70*)p)->Release2(); }
    }
    p = *(void**)((char*)self + 0x54);
    if (p) {
        FUN_00f47040(p);
        if (p) { *(void**)((char*)self + 0x54) = 0; ((RefObj_s0066_bf70*)p)->Release(); }
    }
    p = *(void**)((char*)self + 0x58);
    if (p) {
        FUN_00f47040(p);
        if (p) { *(void**)((char*)self + 0x58) = 0; ((RefObj_s0066_bf70*)p)->Release(); }
    }
    p = *(void**)((char*)self + 0x64);
    if (p) ((Sub64*)p)->FUN_006571e0(0, 0, 0);
    p = *(void**)((char*)self + 0x68);
    if (p) { *(void**)((char*)self + 0x68) = 0; ((RefObj_s0066_bf70*)((char*)p + 0x10))->Release(); }
    p = *(void**)((char*)self + 0x6c);
    if (p) { *(void**)((char*)self + 0x6c) = 0; ((RefObj_s0066_bf70*)p)->Release(); }
    p = *(void**)((char*)self + 0x7c);
    if (p) { *(void**)((char*)self + 0x7c) = 0; ((RefObj_s0066_bf70*)p)->Release(); }
    p = *(void**)((char*)self + 0xb0);
    if (p) {
        void* a = *(void**)((char*)self + 0xb4);
        void* b = *(void**)((char*)self + 0xb8);
        void* c = *(void**)((char*)self + 0xbc);
        void* d = *(void**)((char*)self + 0xc0);
        *(void**)((char*)self + 0xb0) = 0;
        FUN_00571db0(p, a, b, c, d);
    }
    p = *(void**)((char*)self + 0x14);
    if (p) ((FnVoidI)VT(p)[0x1e])(p, 0x1002);
}

// @ 0x0066c490
void __fastcall FUN_0066c490(void* self)
{ (void)self; }

// @ 0x0066c720
void __fastcall FUN_0066c720(void* self)
{ (void)self; }

// @ 0x0066c9e0
void __fastcall FUN_0066c9e0(void* self)
{ (void)self; }

// @ 0x0066cb70
Cb70* Cb70::FUN_0066cb70(unsigned flags)
{
    *(void**)this = &gVt140075c;
    _ReadWriteBarrier();
    void* p;
    p = *(void**)((char*)this + 0x14); if (p) ((RefObj_s0066_bf70*)p)->Release();
    p = *(void**)((char*)this + 0x10); if (p) ((RefObj_s0066_bf70*)p)->Release();
    p = *(void**)((char*)this + 0xc);  if (p) ((RefObj_s0066_bf70*)p)->Release();
    p = *(void**)((char*)this + 8);    if (p) ((RefObj_s0066_bf70*)p)->Release();
    *(void**)this = &gVt13ef094;
    if (flags & 1) EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x0066cbd0
void __fastcall FUN_0066cbd0(void* self)
{ (void)self; }

// @ 0x0066cd20
namespace SP {
void GetVerbIconKeysForLargeCard(eModelType self, EA::ResourceMan::Key & a2, EA::ResourceMan::Key & a3)
{ (void)self; }
}  // namespace SP

// @ 0x0066ce00
void __fastcall FUN_0066ce00(void* self)
{ (void)self; }

// @ 0x0066d280
void __fastcall FUN_0066d280(void* self)
{ (void)self; }

// @ 0x0066d430
bool KeyPanel::HandleMessage(void* window, Message* msg)
{
	switch (msg->eventType)
	{
	case 9:
	{
		int src = msg->field04;
		ObjHolder3c* w = mp3c;
		if (w && src == w->Slot4())
		{
			ObjHolder3c* t = mp3c;
			GetWindowManager()->Apply10((void*)((FnSlot4b)VT(t)[4])(t, mp3c, msg, 0));
		}
		w = mp40;
		if (!w)
			return false;
		if (src != w->Slot4())
			return false;
		ObjHolder3c* t = mp40;
		GetWindowManager()->Apply10((void*)((FnSlot4b)VT(t)[4])(t, mp40, msg, 0));
		return false;
	}
	case 2:
	{
		ChildPanel* c = mp7c;
		if (!c)
			return false;
		if (!IsLinkedActive(c->GetLinkable()))
			return false;
		if (!mp7c->HandleMessage(window, msg))
			return false;
		return true;
	}
	case 1:
	{
		if (sAppProperties->GetDescription(0xb4daca6a) && mp74)
		{
			ResKey key = *((FnGetKey)VT(mp74)[0x40 / 4])(mp74);
			if (key.type == 0x2b978c46)
			{
				uint32_t axis;
				uint32_t nv;
				switch (msg->field10)
				{
				case 0x31:
					axis = 0xa426730b;
					switch (KeyGetAxis(&key, axis))
					{
					case 0xcfb01b93: nv = 0xa8ec6f99; goto doSet;
					case 0xa8ec6f99: nv = 0x5ece4770; goto doSet;
					case 0: nv = 0xcfb01b93; goto doSet;
					case 0x5ece4770:
					default:
						goto doReset;
					}
				case 0x32:
					axis = 0xad56080c;
					switch (KeyGetAxis(&key, axis))
					{
					case 0xfd159d91: nv = 0xb9de15f2; goto doSet;
					case 0: nv = 0x17e5ef84; goto doSet;
					case 0x17e5ef84: nv = 0xfd159d91; goto doSet;
					case 0xb9de15f2:
					default:
						goto doReset;
					}
				case 0x33:
					axis = 0xf71fa311;
					switch (KeyGetAxis(&key, axis))
					{
					case 0: nv = 0x0cac124d; goto doSet;
					case 0x0cac124d: nv = 0x60a78928; goto doSet;
					case 0x60a78928: nv = 0xc2ca9495; goto doSet;
					case 0xc2ca9495:
					default:
						goto doReset;
					}
				case 0x34:
					axis = 0xbeb528cb;
					switch (KeyGetAxis(&key, axis))
					{
					case 0x0a35d0f5: nv = 0x3360727f; goto doSet;
					case 0: nv = 0x0a35d0f5; goto doSet;
					case 0x3360727f: nv = 0x6aeb96a1; goto doSet;
					case 0x6aeb96a1:
					default:
						goto doReset;
					}
				case 0x35:
					KeyResetAxis(&key, 0xa426730b);
					KeyResetAxis(&key, 0xad56080c);
					KeyResetAxis(&key, 0xf71fa311);
					KeyResetAxis(&key, 0xbeb528cb);
					KeyResetAxis(&key, 0x2db6dad3);
					return false;
				default:
					goto tail;
				}
			doReset:
				KeyResetAxis(&key, axis);
				goto recompute;
			doSet:
				KeySetValue(&key, nv);
			recompute:
				{
					int a = KeyGetAxis(&key, 0xa426730b);
					int b = KeyGetAxis(&key, 0xad56080c);
					int c = KeyGetAxis(&key, 0xf71fa311);
					int d = KeyGetAxis(&key, 0xbeb528cb);
					KeySetValue(&key, KeyCombine(a, b, c, d));
				}
			}
		}
	tail:
		{
			ChildPanel* c = mp7c;
			if (c)
			{
				if (IsLinkedActive(c->GetLinkable()))
				{
					if (!mp7c->HandleMessage(window, msg))
						return false;
					return true;
				}
			}
		}
		return false;
	}
	case 0x1b:
	{
		MsgWindow* w = msg->source;
		if (!w)
			return false;
		uint32_t id = w->GetControlID();
		if (id == 0x53d6fe29)
		{
			if (!mp90)
				return false;
			mp90->Activate(0);
			return false;
		}
		if (id + 0x4b2511b0u > 4)
			return false;
		void* src74 = mp74;
		PtrVec items;
		if (src74 && ((FnFill)VT(src74)[0x8c / 4])(src74, &items))
		{
			void* item = items.mBegin[w->GetControlID() + 0x4b2511b0u];
			if (mp84 && item)
			{
				mp84->SetItem(item);
				mp84->v8();
				mp84->SetActive();
				SetWindowParent(w, mp84->GetRootWindow(), 1);
			}
		}
		return false;
	}
	case 0x287259f6:
	{
		switch (msg->field0C)
		{
		case 0x53d6fe2a:
		{
			if (!mp78)
				return false;
			__int64 k = mp78->GetAssetKey();
			GetMessageServer()->Send(0x6299932, &k, 0);
			return true;
		}
		case 0x06135298:
		{
			void* src74 = mp74;
			if (src74)
			{
				WinMgrObj* target = GetSingleton67de40()->GetTarget();
				void* v = ((FnSlot4c)VT(src74)[4])(src74, 0);
				target->Apply34(v);
			}
			CalloutMessageBox((char*)this + 8, kCalloutText);
			return true;
		}
		case 0x54acb9f1:
			mp70->Poke(0, 0, 0);
			return false;
		case 0x74d01473:
		{
			if (!mp7c)
				return false;
			FlagsObj* f = mp7c->mpFlags;
			if (!f)
				return false;
			if (!f->Test(2))
				f->Set(2);
			else
				f->Clear(2);
			f = mp7c->mpFlags;
			if (!f->Test(10))
			{
				f->Set(10);
				return false;
			}
			f->Clear(10);
			return false;
		}
		case 0x74174c59:
			GetMessageServer()->Send(0x14ac4938, 0, 0);
			return true;
		}
		return false;
	}
	case 0x1c:
	{
		MsgWindow* w = msg->source;
		if (!w)
			return false;
		uint32_t id = w->GetControlID();
		if (id == 0x53d6fe29)
		{
			if (mp90)
				mp90->Deactivate(0);
			return false;
		}
		if (id + 0x4b2511b0u > 4)
			return false;
		if (mp84)
			mp84->SetInactive();
		return false;
	}
	}
	return false;
}

// @ 0x0066daf0
namespace SP {
void cSPUILargeAssetView_s0066_daf0::LoadAssetViewLarge()
{
    if (mIsLoaded)
        return;

    mWinRoot = mLayout->FindWindowByID(0xf3c6dc19, true);
    if (mWinRoot) {
        mWinRoot->AddWinProc(this);
        SPUIHelpers::SetWindowAreaToParent(mWinRoot);
        if (mIsOnline) {
            mCommentsBrowser = new("UI", 0, 0, 0, 0) cSPUIAssetComments_s0066_daf0();
            mCommentsBrowser->Init(mWinRoot);
        }
        mExpansionPackBrowser = new("UI", 0, 0, 0, 0) cSPUIMissingExpansionPackPage_s0066_daf0();
        mExpansionPackBrowser->Init(mWinRoot);
        mInventory = new("UI", 0, 0, 0, 0) cSPCardInventory();
        mInventory->SetMessageID(0x14e46c34, gCardInventoryParam);
        mInventory->Show();
    }

    mWinBakingArea = mLayout->FindWindowByID(0x65f79e0, true);
    mWin28 = mLayout->FindWindowByID(0x65f79d8, true);
    if (mWinBakingArea)
        mBakingArea = mWinBakingArea->GetArea();

    mStats = new("UI", 0, 0, 0, 0) cSPCardStats();
    mStats->Load(mLayout, mpMetadata);

    IWindow_s0066_daf0* shareIconWin;
    if (gAppProperties->mpValues->mOfflineMode == 0) {
        mWinShare = mLayout->FindWindowByID(0x6135298, true);
        if (mWinShare && !AuthManager()->IsOffline()) {
            bool downloaded = false;
            if (mpMetadata) {
                cDownloadList* list = &DownloadManager()->mList;
                unsigned count = list->size();
                for (unsigned i = 0; i < count; ++i) {
                    cDownloadEntry* entry = &list->mpBegin[i];
                    if (entry->mState == 2 && entry->mAssetKey == mpMetadata->GetAssetKey()) {
                        downloaded = true;
                        break;
                    }
                }
            }
            mWinDownloaded = mLayout->FindWindowByID(0x615c7a8, true);
            if (mWinDownloaded)
                mWinDownloaded->SetFlag(1, downloaded);
            mWinShare->SetFlag(1, mpMetadata != 0 && !downloaded &&
                                  mpMetadata->GetAssetKey() != AuthManager()->GetUserID() &&
                                  mpMetadata->GetAssetKey() != 0xfffffffffffffffeULL);
        } else if (mWinShare) {
            mWinShare->SetFlag(1, false);
        }
        mWinShareIcon = mLayout->FindWindowByID(0x6136d30, true);
        shareIconWin = mWinShareIcon;
    } else {
        mWinShare = mLayout->FindWindowByID(0x6135298, true);
        shareIconWin = mWinShare;
    }
    if (shareIconWin)
        shareIconWin->SetFlag(1, false);

    mWinAssetVerbs = mLayout->FindWindowByID(0x34af0c8f, true);
    if (mWinAssetVerbs) {
        mAssetVerbs = new("UI", 0, 0, 0, 0) cSPUIAssetVerbs_s0066_daf0();
        mAssetVerbs->Init(mWinAssetVerbs);
    }

    mWinRenderWindow = mLayout->FindWindowByID(0xf3c6d819, true);
    if (mWinRenderWindow)
        mWinRenderWindow->SetFlag(1, false);

    mWinName = mLayout->FindWindowByID(0x53d6fe29, true);
    if (mWinName && mAssetData) {
        mWinName->SetCaption(mAssetData->GetName() ? mAssetData->GetName() : L"<Missing>");
        mTextZoom = new("UI/cSPUITextZoom", 0, 0, 0, 0) TextZoomName_s0066_daf0();
        mTextZoom->SetTargetWindow(mWinName ? mWinName->Cast(0xf15f4bd) : 0, 0, 0, 0, ResourceKey(0, 0, 0));
    }

    mWinAuthor = mLayout->FindWindowByID(0x53d6fe2a, true);
    if (mWinAuthor && mAssetData) {
        mWinAuthor->SetCaption(mAssetData->GetAuthor() ? mAssetData->GetAuthor() : L"<Missing>");
        SPUIHelpers::AutoSizeWindowForText(mWinAuthor, 0, 0);
        if (mWinAuthor->GetParent()) {
            const Rect& parentArea = mWinAuthor->GetParent()->GetRealArea();
            float left = parentArea.x1;
            float right = parentArea.x2;
            const Rect& area = mWinAuthor->GetRealArea();
            mWinAuthor->SetLocation((right + left) * 0.5f - (area.x2 - area.x1) * 0.5f, area.y1);
        }
        if (mWinShare) {
            float authorRight = mWinAuthor->GetRealArea().x2;
            mWinShare->SetLocation(authorRight, mWinShare->GetRealArea().y1);
            Rect shareArea = mWinShare->GetRealArea();
            if (mWinShareIcon)
                SPUIHelpers::CenterWindow(mWinShareIcon, Point((shareArea.x2 + shareArea.x1) * 0.5f,
                                                               (shareArea.y2 + shareArea.y1) * 0.5f));
            if (mWinDownloaded)
                SPUIHelpers::CenterWindow(mWinDownloaded, Point((shareArea.x2 + shareArea.x1) * 0.5f,
                                                                (shareArea.y2 + shareArea.y1) * 0.5f));
        }
        cPlayableAsset* playable;
        if (mAssetData && (playable = (cPlayableAsset*)mAssetData->mObject.Cast(0x13d55dc8)) != 0 &&
            playable->IsPlayable())
            mWinAuthor->SetFlag(0x10, true);
        else
            mWinAuthor->SetFlag(0x10, false);
    }

    mWinPublished = mLayout->FindWindowByID(0x56e3f98, true);
    if (mWinPublished && mAssetData)
        mWinPublished->SetFlag(1, mAssetData->IsPublished());

    mWinDescription = mLayout->FindWindowByID(0xb456a483, true);
    const wchar_t* description = mAssetData->GetDescription();
    if (mWinDescription && mAssetData && description)
        mWinDescription->SetCaption(description);
    if (mWinDescription && mWinDescription->GetParent())
        mWinDescription->GetParent()->AddWinProc(this);

    mWinTags = mLayout->FindWindowByID(0xb456a47a, true);
    if (mWinTags && mAssetData) {
        string16 tags;
        mAssetData->GetTags(tags);
        mWinTags->SetCaption(tags.c_str());
    }
    if (mWinTags && mWinTags->GetParent())
        mWinTags->GetParent()->AddWinProc(this);

    mWin5c = mLayout->FindWindowByID(0x6664868, true);
    mWin30 = mLayout->FindWindowByID(0x3431bd1e, true);
    mWinBakingForeground = mLayout->FindWindowByID(0x34a0979a, true);
    if (mWinBakingForeground)
        mWinBakingForeground->SetFlag(1, false);

    mRollover = new("UI", 0, 0, 0, 0) cCardRollover();
    mRollover->Attach(mLayout);

    AutoRefCount<ResourceObject> resource;
    if (mHasResource) {
        IAssetData* assetData = mAssetData;
        IResourceManager* resourceManager = GetManager();
        if (!resourceManager->GetResource(*assetData->GetKey(), resource.AsPPTypeParam(), 0, 0, 0, 0)) {
            resource.Reset();
            mHasResource = false;
            mIsPlayable = false;
            mIsEditable = false;
        }
    }

    if (!mHasResource) {
        if (mWinBakingForeground)
            mWinBakingForeground->SetFlag(1, false);
        if (mWinRenderWindow)
            mWinRenderWindow->SetFlag(1, 0);
    } else {
        mWinVerbContainer = mLayout->FindWindowByID(0x3fbba82, true);
        if (mWinVerbContainer && resource) {
            ResourceKey verbKey;
            ResourceKey layoutKey;
            uint32_t modelType = mAssetData->GetModelType();
            if (AssetBrowser() && AssetBrowser()->mFilterModelType) {
                uint32_t filterType = AssetBrowser()->mFilterModelType;
                if (GetEditorForModelType(filterType) == GetEditorForModelType(modelType))
                    modelType = filterType;
            }
            GetVerbIconKeysForLargeCard(modelType, mAssetData->GetSize(), &verbKey, &layoutKey);
            if (verbKey.instanceID != 0 && mAssetData->HasVerbs()) {
                AutoRefCountOOL<cPropertyList_s0066_daf0> verbProps;
                PropertyManager()->GetPropertyList(verbKey.instanceID, verbKey.groupID, verbProps.AsPPTypeParam());
                int keyCount = 0;
                int keys = 0;
                GetPropertyArrayKeys(verbProps, 0x4aa3838, &keyCount, &keys);
                if (verbKey.instanceID != 0 && layoutKey.instanceID != 0) {
                    if (mVerbIcons)
                        mVerbIcons->Clear();
                    bool editorTray = false;
                    IWindow_s0066_daf0* trayWindow = mLayout->FindWindowByID(0x630c829, true);
                    GetBoolProperty(verbProps, 0x630a7a2, editorTray);
                    if (editorTray) {
                        mVerbIcons = new("Editor", 0, 0, 0, 0) cSPVerbTray();
                        if (trayWindow)
                            trayWindow->SetFlag(1, false);
                    } else {
                        mVerbIcons = new("Sporepedia", 0, 0, 0, 0) cSPSporepediaVerbTray();
                        if (trayWindow)
                            trayWindow->SetFlag(1, true);
                    }
                    mVerbIcons->Load(mWinVerbContainer, layoutKey, keys, keyCount, 0);
                }
            } else {
                if (mVerbIcons)
                    mVerbIcons->Clear();
                mVerbIcons.Reset();
            }

            if (mVerbIcons) {
                if (mAssetData->GetKey()->typeID == 0x2b978c46) {
                    AutoRefCountOOL<ResourceObject> creatureRes;
                    if (!ComputeVerbIcons(mAssetData->GetKey(), creatureRes.AsPPTypeParam())) {
                        creatureRes.Reset();
                    } else {
                        int caps = GetCreatureCaps(mAssetData->GetModelType());
                        FillCreatureVerbTray(creatureRes, mVerbIcons, caps, mAssetData->GetSize());
                    }
                } else if (mAssetData->GetModelType() == 0xdfad9f51) {
                    FillBuildingVerbTray(interface_cast_EditorResource(resource), mVerbIcons);
                } else if (mAssetData->GetKey()->typeID != 0x24682294 &&
                           mAssetData->GetKey()->typeID != 0x476a98c7) {
                    FillVehicleVerbTray(interface_cast_EditorResource(resource), mVerbIcons);
                } else {
                    FillUFOVerbTray(interface_cast_EditorResource(resource), mVerbIcons);
                }
                IWindow_s0066_daf0* trayWindow = mLayout->FindWindowByID(0x630c829, true);
                if (trayWindow) {
                    if (mVerbIcons && mVerbIcons->GetIconCount() > 0) {
                        Rect trayArea = trayWindow->GetRealArea();
                        trayArea.y2 = trayArea.y1 + mVerbIcons->GetHeight() + 15.0f;
                        trayWindow->SetLayoutArea(trayArea);
                    } else {
                        trayWindow->SetFlag(1, false);
                    }
                }
            } else {
                IWindow_s0066_daf0* trayWindow = mLayout->FindWindowByID(0x630c829, true);
                if (trayWindow)
                    trayWindow->SetFlag(1, false);
            }
        }

        if ((mAssetData && (GetAssetKeyType(mAssetData->GetKey()) == 1 ||
                            mAssetData->GetParentID() == 0x7fffffff)) ||
            gAppProperties->GetDescription(0xb4daca6a))
            UpdateDescription();

        IAssetData* asset = mAssetData;
        AutoRefCount<cPropertyList_s0066_daf0> editorProps;
        IPropertyManager* propertyManager = PropertyManager();
        if (propertyManager->GetPropertyList(RemapTypeId(asset->GetModelType()), gEditorConfigGroupID,
                                             editorProps.AsPPTypeParam())) {
            uint32_t soundGroup = 0;
            if (GetPropertyAsKeyInstance(editorProps, 0x5d29fdd, &soundGroup)) {
                KillSetiEffects(soundGroup, 0x5d2b737);
                PlayEditorSound(0x5d2b737, 0xbd5385c8, 0.0f, 0);
                if (mVerbIcons) {
                    int iconCount = mVerbIcons->GetIconCount();
                    for (int i = 0; i < iconCount; ++i) {
                        if (mVerbIcons->GetSlot(i)->GetSoundID() > 0)
                            PlayEditorSound(0x1d6253c0, mVerbIcons->GetSlot(i)->GetSoundID(),
                                            mVerbIcons->GetSlot(i)->GetSize(), 0);
                    }
                }
            }
        }

        if (!mSwatch)
            mSwatch = SwatchManager()->CreateSwatch(0);
        if (mSwatch) {
            ResourceKey key = *mAssetData->GetKey();
            bool isAdventure = false;
            if (key.typeID == 0x3d97a8e4 || key.typeID == 0x2b978c46 || key.typeID == 0x438f6347) {
                isAdventure = true;
                mSwatch->Init(key, mWinRenderWindow, 1, 0, 2, 1, mAssetData->GetModelType());
            } else {
                mSwatch->Init(key, mWinRenderWindow, 0, 0, 1, 1, mAssetData->GetModelType());
            }
            mSwatch->SetActive(true);
            mSwatch->SetUpdating(0);
            mSwatch->SetEditorCameraController(1);
            mSwatchZoom = gAppProperties->GetFloatProperty(0x678aff6);
            SetShaderParam(0x236, &mSwatchZoom, 1);
            if (!mSwatch->mIsAnimated) {
                mWinBakingForeground->SetFlag(1, true);
                mWinRenderWindow->SetFlag(1, false);
                if (mWinRoot)
                    mWinRoot->SetCursorID(0x1024);
            } else {
                mWinBakingForeground->SetFlag(1, false);
                mWinRenderWindow->SetFlag(1, true);
                if (mWinRoot)
                    mWinRoot->SetCursorID(0x1002);
            }
            if (isAdventure)
                SetupAdventure();
            ModelManager()->SetPreviewModel(mSwatch->mModel.GetModel());
        }
    }

    mIsLoaded = true;
}
}  // namespace SP

// @ 0x0066ee50
void __fastcall FUN_0066ee50(void* self)
{ (void)self; }

// @ 0x0066efe0
void __fastcall FUN_0066efe0(void* self, void* a)
{ (void)self; (void)a; }

// @ 0x0066f090
void __fastcall FUN_0066f090(void* self)
{ (void)self; }
