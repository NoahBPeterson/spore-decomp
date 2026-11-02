// src/game/SPEditors/SPUIAssetBrowser.cpp -- migrated from slice(s) s0064c8e0, s00648d90, s00643b50, s006470b0, s0064bc50, s0064acd0, s00649f60, s00647f40, s00646370, s00645620, s00644b90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIAssetBrowser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIAssetBrowser.h"
#include "SP/cString.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorUI.h"
#include "SP/cSPPlayModeUI.h"
#include "cSPUILayout.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/cSPUIAssetGrid.h"
#include "SP/cSPUIFeedListCategory.h"
#include "SP/cSPUIFeedListItem.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "EA/UTFWin/IWindow.h"
#include "cSPUIAnimator.h"
#include "SP/cPollinator.h"
#include "SP/cSPUIAssetVerbs.h"
#include "SP/cISPLargeAssetView.h"
#include "SP/cSPUIAssetWebBrowser.h"
#include "SP/cSPUIFeedEdit.h"
#include "SP/cSPUIFeedList.h"
#include "SP/cSPUISporeGuidePage.h"

// ---- items of slice s00644b90 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EASTL_allocator_allocate(size_t, const char*, int, int, const char*, int); // 0x00f473a0
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define AT(T, off) (*(T*)((char*)this + (off)))
struct IRC { virtual void AddRef(); virtual void Release(); };
struct Key3;
struct RCObj {
virtual void v0();
virtual void v1(const void*);
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual uint32_t v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual Key3* v16();
virtual void v17(const void*);
virtual bool v18();
virtual void v19();
virtual void v20();
    uint32_t pad[3];
    void AddRef() { ((IRC*)((char*)this + 0x10))->AddRef(); }
    void Release() { ((IRC*)((char*)this + 0x10))->Release(); }
};
struct Key3 {
    uint32_t a, b, c;
    bool operator<(const Key3& o) const {
        if (a != o.a) return a < o.a;
        if (c != o.c) return c < o.c;
        return b < o.b;
    }
};
struct MsgServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void Send(uint32_t id, void* data, int);
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void Register(void* listener, uint32_t id);
};
MsgServer* MessageServer_s0064_4b90();
#define VSLOT(o, byteoff) ((*(void***)(o))[(byteoff) / 4])
typedef int   (__thiscall *Fn_i0)(void*);
typedef void* (__thiscall *Fn_p2)(void*, uint32_t, uint32_t);
typedef void  (__thiscall *Fn_v2)(void*, uint32_t, uint32_t);
typedef void  (__thiscall *Fn_v1)(void*, void*);
typedef uint8_t (__thiscall *Fn_b0)(void*);
struct WinV {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void SetFlag(uint32_t f, bool v);
};
struct ListDataV {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual WinV* GetWin(uint32_t id, uint32_t f);
};
void* AuthManager();                                      // SP::Pollen::AuthManager (0x607a60)
struct WebBrowser { void SetActive(bool a); void Navigate(uint32_t a, uint32_t b); };
struct SubA { void Set(uint32_t a); void Fn_e720(); void Fn_ef30(uint32_t a, uint32_t b); };
struct Browser {
    void SetWebBrowserVisibility(char vis, uint32_t x);
    void Fn_c50(char vis, uint32_t a, uint32_t b);
    void Fn_d10(char vis, int x);
    int IsA();
    int IsB();
    int CanSporepediaShowSporeGuide();
    void Fn_e20(char flag);
    void Fn_eb0();
    void PreloadTextures();
    void Fn_160();
    void Fn_260();
    uint32_t Get_c();
    uint32_t Get_10();
    void SetCallToActionMessage(const short* msg);
    uint8_t Query(const Key3* in, Key3* out);
};
struct StyleMgr { void* GetStyle(uint32_t id, uint32_t z); };
StyleMgr* GetStyleManager(uint32_t a);                    // EA::Text::GetStyleManager (0x885bd0)
void GetBounds(float* out, void* win);                    // FUN_00805ef0
typedef void (__thiscall *Fn_rect)(void*, float*, uint32_t, uint32_t);
struct PlainRC { virtual void AddRef(); virtual void Release(); };
struct Ent20 { uint32_t a, b, c; PlainRC* d; RCObj* e; };
struct VecEnt20 { Ent20 *mpBegin, *mpEnd, *mpCap; bool empty() const { return mpBegin == mpEnd; } uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); } };
struct RelPair { PlainRC* b; RCObj* a; void Release2(); };
struct LocaleMsg2 { uint32_t vt0, vt1, f8, fc; PlainRC* owner; void Dtor(); };
struct ResourceKey {
    uint32_t inst, type, group;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : inst(i), type(t), group(g) {}
};
struct TexturePreload { TexturePreload* ctor(int n); void PreloadTextureList(const ResourceKey* k); };
struct BrowserB { void Fn990(); };
struct Obj3 { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual Key3* GetKey(); };
struct WinMgr { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void SetWin(uint32_t, void*); };
WinMgr* GetWindowManager();                               // SP::WindowManager (0x67caa0)
void ErrDlg(void* a, const Key3* k);                      // FUN_00809db0
struct SvcA { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void Do13(uint32_t a, uint32_t b); };
struct SvcB { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual SvcA* Get(); };
SvcB* GetSvcB();                                          // FUN_0067de40
extern Key3 g1525894, g15258a0;
struct Obj6p { char pad[0x28]; uint32_t f28; };
struct Obj6c { bool Check(); };
struct Node12 { uint32_t a; PlainRC* b; uint32_t c; };
struct Ent20x : Ent20 { Ent20x* Copy(const Ent20* o); };
struct cString { char buf[20]; cString(); const short* c_str(); const short* ValueOrDefault(); };
struct MsgHandlerObj {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
    virtual void SetText(const short* t);
};
void GetPropertyAsText(void* list, uint32_t id, cString* out);   // SP::GetPropertyAsText (0x6a1360)
namespace __equiv_ann1 {
struct SubA {
    void Fn_e720();   // 0x0065e720 (equiv t1)
    void Fn_ef30();   // 0x0065ef30 (equiv t1)
    void Set();   // 0x0065d9f0 (equiv t3)
};
}
namespace __equiv_ann1 {
struct WebBrowser {
    void Navigate();   // 0x0065c3c0 (equiv t3)
    void SetActive();   // 0x0065b2a0 (equiv t2)
};
}
// ---- items of slice s00644b90 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00645620 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void gPartialCall3();
struct cBase0 { virtual void b0(); char pad[0xc]; };              // size 0x10
struct cRefCountA { virtual void AddRef(); virtual void Release(); };        // slots 0,1 at +0
struct cRefCountB { virtual void AddRef(); virtual void Release(); };        // slots 0,1 at +0x10
struct cRefB : cBase0, cRefCountB {};                             // refcount base at +0x10
struct Elem {
    uint32_t a, b, c;   // +0x00
    cRefCountA* p;      // +0x0C
    cRefB*      q;      // +0x10
};
struct cAssetBrowser2 { int FUN_00645cc0(); };   // 0x00645CC0
cAssetBrowser2* GetAssetBrowser2();              // 0x00401030
struct IAuthMgr {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8();
    virtual bool a9();                               // +0x24
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
    virtual void a15(); virtual void a16();
    virtual void a17();                              // +0x44
    virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21();
    virtual bool a22();                              // +0x58
};
IAuthMgr* GetAuthMgr();                              // 0x00607A60
struct cSPUIAssetBrowser {
    char pad04[0x4];
    char pad1c0[0x1c0 - 0x4];
    int  mField1c0;            // +0x1C0
    char pad230[0x230 - 0x1c4];
    int  mField230;            // +0x230
    char pad24d[0x24d - 0x234];
    bool mb24d;                // +0x24D
    bool mb24e;                // +0x24E

    int  FUN_00645d90();                                  // 0x00645D90
    void FUN_00645db0(Elem* other);                       // 0x00645DB0
    void FUN_00645e20();                                  // 0x00645E20
    static Elem* FUN_00646030(Elem* first, Elem* last, uint32_t* key);   // 0x00646030
    static void FUN_006460b0(Elem* first, Elem* last, Elem* src);        // 0x006460B0
    static Elem* FUN_00646140(Elem* first, Elem* last, Elem* dst);       // 0x00646140
    static Elem* FUN_006461d0(Elem* first, Elem* last, Elem* dst);       // 0x006461D0
    void FUN_00646260();                                  // 0x00646260
    void FUN_006462b0(void* p);                           // 0x006462B0
    void FUN_00645620();
    void FUN_00645bf0();
    void FUN_00645cc0_();
};
// ---- items of slice s00645620 end

// ---- items of slice s00646370 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl eastl_dealloc(void* p);                    // 0x00f47380
extern "C" void* __cdecl eastl_alloc(uint32_t n, const char* name, int a, int b,
                                     const char* file, int line);    // 0x00f473a0
extern "C" void* __cdecl uninit_copy14(void* first, void* last, void* dest);    // 0x00645450
extern "C" void* __cdecl uninit_destroy14(void* first, void* last, void* dest); // 0x006454c0
extern wchar_t gEmptyString16[];                       // 0x01667bac
inline void FreeChecked(void* p) {
    if (p && ((uint32_t*)p)[-1])
        eastl_dealloc(p);
}
struct Key8 { uint32_t first; uint32_t second; };
struct InsertResult { void* node; void* bucket; bool inserted; };
class Vec14 {
public:
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    void reserve(uint32_t n);
};
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
struct RefPair {
    uint32_t first;
    IRef* second;
    RefPair() {}
};
struct EmptyTag {};
struct Container0F8 {
    uint8_t mData[0x20];
    InsertResult find_insert(const Key8& key, EmptyTag tag);
};
struct Container118 {
    uint8_t mData[0x20];
    InsertResult find_insert(const Key8& key, EmptyTag tag);
};
struct Container138 {
    uint8_t mData[0x24];
    InsertResult insert(const RefPair& key, EmptyTag tag);
};
struct Container15C {
    uint8_t mData[0x24];
    InsertResult insert(const RefPair& key, EmptyTag tag);
};
struct Owner {
    uint8_t pad0[0xf8];
    Container0F8 m0F8;      // +0xf8
    Container118 m118;      // +0x118
    Container138 m138;      // +0x138
    Container15C m15C;      // +0x15c

    bool Insert0F8(uint32_t a, uint32_t b);
    bool Insert118(uint32_t a, uint32_t b);
    bool Insert138(uint32_t a, IRef* b);
    bool Insert15C(uint32_t a, IRef* b);
};
struct Elem20 {
    uint32_t f00, f04, f08, f0c, f10;          // sizeof == 0x14
};
struct OutPair { void* first; void* second; };
struct MapFindSelf {
    Elem20* mBegin;     // +0
    Elem20* mEnd;       // +4
    uint32_t mField8;   // +8
    uint32_t mFieldC;   // +0xc
    uint32_t mField10;  // +0x10
    uint8_t  mFlag14;   // +0x14

    void Find(OutPair* out, const OutPair* key);
};
extern "C" Elem20* __cdecl lower_bound20(Elem20* first, Elem20* last, const OutPair* key, uint8_t flag); // 0x00646030
struct MapFindInsert {
    uint32_t mField0;       // +0
    void* mpBuckets;        // +4
    uint32_t mBucketCount;  // +8
    uint32_t mCountC;       // +0xc
    uint32_t mField10;      // +0x10

    void find(InsertResult* out, const uint32_t* key);
    void insert(InsertResult* out, const uint32_t* key, EmptyTag tag);
    uint32_t* FindOrInsert(uint32_t* key);
};
void* __cdecl operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                           const char* file, int line);                         // 0x00f473a0
struct Key { uint32_t instance, type, group; };
struct ResObj {                       // Resource::ResourceObject
    virtual int AddRef();             // +0x00
    virtual int Release();            // +0x04
    virtual int v2();                 // +0x08
    virtual void* Cast(uint32_t t);   // +0x0c
    uint32_t mRefCount;               // +0x04 (data)
    Key mKey;                         // +0x08
};
struct CastTarget3c609f8 { uint32_t pad[6]; int mField18; };   // type 0x03c609f8 (model base)
template <class T> struct Ref {
    T* p;
    Ref() : p(0) {}
    Ref(T* x) : p(x) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
    void Reset() { T* t = p; if (t) { p = 0; t->Release(); } }
};
struct RecordInfo { uint32_t chunkOffset, compressedSize, memorySize; int16_t flags; bool isSaved; };
struct Database {                     // Resource::Database
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0A(); virtual void s0B();
    virtual void s0C();
    virtual bool OpenRecord(const Key& name, void* ppDst, uint32_t access, uint32_t cd,
                            bool arg10, RecordInfo* pInfo);     // +0x34
};
struct IResourceManager {
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual bool GetResource(const Key& name, Ref<ResObj>* ppDst, void* factoryData,
                             Database* pDatabase, void* pFactory, const Key* pCacheName);   // +0x0c
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual bool GetPrivateResource(const Key& name, Ref<ResObj>* ppDst, void* factoryData,
                                    Database* pDatabase, void* pFactory, const Key* pCacheName);  // +0x1c
    virtual bool WriteResource(ResObj* pResource, void* factoryData, Database* pDatabase,
                               void* pFactory, const Key* pNameKey);   // +0x20
    virtual void s09(); virtual void s0A(); virtual void s0B(); virtual void s0C();
    virtual void s0D(); virtual void s0E(); virtual void s0F(); virtual void s10();
    virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15();
    virtual Database* FindDatabase(const Key& name);   // +0x58
};
IResourceManager* __cdecl GetManager();                // 0x0067dcd0 (EA::ResourceMan::GetManager)
struct cIDGenerator {                                  // App::cIDGenerator
    virtual void s00();
    virtual void Generate(Key& dst, uint32_t typeID, uint32_t poolID, uint32_t highBits,
                          uint32_t lowBits8, uint32_t lowBits0);   // +0x04
};
cIDGenerator* __cdecl GetIDGenerator();                // 0x0067de60 (SP::IDGenerator)
struct cAssetMetadata : ResObj {                       // Pollinator::cAssetMetadata, 0xd8 bytes
    uint32_t pad[(0xd8 - 0x14) / 4];
    cAssetMetadata();                                  // 0x00550450
    void GetTagsString(void* pDstString16);            // 0x00550cf0
    const wchar_t* GetDescription();                   // 0x005508c0 (mDescription.c_str(), no args)
    const wchar_t* GetName();                          // 0x00414e10 (mName.c_str(), no args)
    bool Set(const Key& assetKey, const wchar_t* name, const wchar_t* description,
             const wchar_t* tags, const Key& parentKey, bool isPollinated);  // 0x00551240 (ret 0x18)
};
struct String16 {                                      // eastl::basic_string<wchar_t>, 16 bytes
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    void DeallocateSelf();                             // 0x00933960
};
struct ImgObj { void* mPixels; uint32_t flags; uint32_t mRefCount;
                void* GetPixels();                     // 0x0046f260
};
struct ImgPtr {                                        // atomic refcounted pointer, count at +8
    ImgObj* p;
    ImgPtr(ImgObj* x);                                 // 0x005725b0
    ImgPtr& operator=(ImgObj* x);                      // 0x00576650
    ~ImgPtr();                                         // 0x00576620
};
struct ThumbService {                                  // object returned by 0x0067dd60
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual ImgObj* LoadImage(Key k, int mode);        // +0x1c
};
ThumbService* __cdecl GetThumbService();               // 0x0067dd60
struct cImportExport {                                 // SP::Thumbnail::cImportExport singleton
    bool CreateExportThumb(ResObj* model, void* pixels, Database* saveDb, int zero, bool flag);   // 0x005fa8d0 (ret 0x14)
};
cImportExport* __cdecl GetImportExport();              // 0x005f7930
struct cSPMemPool {
    void* LockedAlloc(uint32_t size, int a, int b, int c, int d, int e);   // 0x009289f0 (ret 0x18)
    void  Free(void* p);                                                  // 0x009276c0 (ret 4)
};
extern cSPMemPool* g_pSPMemPool;                       // 0x016c8b44
struct ChangeNotifier {                                // object returned by 0x00401010
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0A(); virtual void s0B();
    virtual void s0C(); virtual void s0D(); virtual void s0E(); virtual void s0F();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void OnAssetCloned(const Key* oldKey, const Key* newKey);   // +0x50
};
ChangeNotifier* __cdecl GetChangeNotifier();           // 0x00401010
struct MessageServer {                                 // object returned by SP::MessageServer
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04();
    virtual void PostMessage(uint32_t id, const Key* data, int arg);    // +0x14
};
MessageServer* __cdecl GetMessageServer();             // 0x0067dcc0
Database* __cdecl GetSaveArea(uint32_t id);            // 0x006b1f90 (SP::GetSaveArea)
void __cdecl MarkResourceDirty(ResObj* r);             // 0x006ad010
bool __cdecl SetAssetData(uint32_t typeID, bool flag); // 0x004bbe20 (SP::cSPAssetDataList::SetAssetData)
int  __cdecl GetModelCategory(const Key* key);         // 0x00552300
int  __cdecl FindModelPart(const Key* key, uint32_t hash);   // 0x00556140
void __cdecl SummarizeVehiclePart(Key* newKey, int part);    // 0x00555f70 (SP::cVehicleModelSummarizer)
uint32_t __cdecl ReadRecordData(Database* db, const Key* key, void* buf, uint32_t size, int a, int b);  // 0x008ddb00
bool     __cdecl WriteRecordData(Database* db, const Key* key, void* buf, uint32_t size, int a);        // 0x008ddb90
static __forceinline void SummarizePart(const Key* key, Key* newKey, uint32_t hash) {
    if (FindModelPart(key, hash))
        SummarizeVehiclePart(newKey, FindModelPart(key, hash));
}
// ---- items of slice s00646370 end

// ---- items of slice s00649f60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl UpdateMouseFocus(int); // 0x00804f50
struct State {
    uint8_t pad[0x1c];
    uint8_t mField1C;   // +0x1c
};
extern "C" State* __cdecl SporeGuide();     // 0x00401040
extern "C" State* __cdecl AssetBrowser();   // 0x00401030
struct cSPUIAssetBrowser_s0064_9f60 {
    uint8_t pad0[0x1c];
    uint8_t mIsVisible;       // +0x1c
    uint8_t pad1D[0x08];      // +0x1d..0x24
    uint8_t mField25;         // +0x25
    uint8_t pad26[0x03];      // +0x26..0x28
    uint8_t mField29;         // +0x29
    uint8_t pad2A[0x92];      // +0x2a..0xbb
    void*   mpFieldBC;        // +0xbc
    uint8_t padC0[0x108];     // +0xc0..0x1c7
    uint8_t mField1C8;        // +0x1c8
    uint8_t padC9[0x6b];      // +0x1c9..0x233
    uint8_t mField234;        // +0x234

    void SetVisibility(int a, int b, int c);   // 0x0064a400 (declared)
    void Update();                              // 0x0064ab20
};
// ---- items of slice s00649f60 end

// ---- items of slice s0064acd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[2];                                          // 0x1667bac
extern uint32_t g15da784, g15da788, g15da78c, g15da790;
struct Key_s0064_acd0 { uint32_t a, b, c; };
struct Key4 { uint32_t a, b, c, d; };
struct IRef_s0064_acd0  {
    virtual int AddRef();
    virtual int Release();
};
struct IRef2 { virtual void s0(); virtual int AddRef(); virtual int Release(); };
void* operator new(unsigned int n, const char* name, int a, int b, int c, int d);
void __cdecl operator delete(void* p);
#define S(n) virtual void s##n();
struct IMessageServer {
    S(0) S(1) S(2) S(3) S(4)
    virtual void Post(uint32_t id, void* data, int flag);                 // slot 5 (+0x14)
    virtual void Post4(uint32_t id, void* data, int a, int b);            // slot 6 (+0x18)
};
IMessageServer* __cdecl GetMessageServer_s0064_acd0();                               // 0x67dcc0
struct IObjectTemplateDB {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
    S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
    S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
    virtual void SetBanned(Key_s0064_acd0* k, bool banned);                          // slot 30 (+0x78)
};
IObjectTemplateDB* __cdecl GetObjectTemplateDB();                         // 0x67cb40
struct IApp {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13)
    virtual int GetMode();                                                // slot 14 (+0x38)
};
IApp* __cdecl GetApp();                                                   // 0x67dd10
int __cdecl FUN_00552300(void* key);
struct IBanObj {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15)
    virtual Key_s0064_acd0* GetKey();                                                // slot 16 (+0x40)
    S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27)
    virtual bool IsOfficial();                                            // slot 28 (+0x70)
};
struct BanEntry {            // 0x14 bytes
    Key_s0064_acd0 key;
    uint32_t pad;
    IBanObj* obj;            // +0x10
};
struct BanMsg {
    uint32_t d[3];
    IRef_s0064_acd0* p;
    BanMsg(void* owner, Key_s0064_acd0* k, int flag);                                // 0x644a80
};
struct FeedMsg {
    uint32_t d[4];
    IRef_s0064_acd0* p;                 // +0x10
    uint8_t flagA;           // +0x14
    uint8_t flagB;           // +0x15
    void Init(uint32_t id);                                               // 0x666af0
    void InitFromAsset(void* asset);                                      // 0x666a60
};
struct CardBase {
    S(0)
    virtual void SetKey(Key_s0064_acd0* k);                                          // slot 1
    S(2) S(3) S(4) S(5) S(6) S(7) S(8)
    virtual uint32_t GetTypeID();                                         // slot 9 (+0x24)
    S(10)
    virtual bool IsAssetCard();                                           // slot 11 (+0x2c)
    uint32_t pad[3];
};
struct Card : CardBase, IRef_s0064_acd0 {};          // IRef subobject at +0x10
struct CardRef {
    Card* p;
    void Assign(Card* c);                                                 // 0x6428c0
};
typedef Card* (__cdecl *CardFactory)();
typedef Card* (__cdecl *CardWrapFn)(Card*);
struct ConfigTable {                                                      // `this` is the config id itself
    CardFactory GetFactory(uint32_t typeId);                              // 0x642c10
    CardWrapFn  GetWrapper(uint32_t kind);                                // 0x642c40
};
struct TimelineSporepediaCardData : Card {                                // 0x78 bytes (operator new size)
    TimelineSporepediaCardData();                                         // 0x642100
    uint32_t data[(0x78 - 0x14) / 4];
};
struct AssetHolder {                                                      // 8 bytes at stack
    uint32_t a, b;
    AssetHolder() { a = 0; b = 0; }
    void Set(CardRef* c);                                                 // 0x642930
    ~AssetHolder();                                                       // 0x644fc0
};
struct VecIter { void Finish(); };                                        // 0x645db0
struct IProp { uint8_t pad[0x12]; uint16_t type; bool* GetBool(); };      // 0x41e920
struct IPropList {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8)
    virtual bool GetProperty(uint32_t id, IProp** out);                   // slot 9 (+0x24)
};
struct FeedCategory {
    void Expand(int b);                                                    // 0x664480
};
struct FeedList {
    void SetHidden(bool b);                                               // 0x662a90
    FeedCategory* FindCategory(uint32_t id);                              // 0x662a40
    void FUN_00662ad0();
};
bool __cdecl GetPropertyAsKeyInstance(IPropList* props, uint32_t id, uint32_t* out);   // 0x6a12a0
void __cdecl GetPropertyKeyArray(IPropList* props, uint32_t id, int* count, Key_s0064_acd0** arr); // 0x6a0ae0
struct GridInner {
    void FUN_00661380(void* outVec);                                      // 0x661380
    void FUN_00662750(uint32_t a, uint32_t b, bool c);                    // 0x662750
};
struct AssetGrid {
    uint8_t pad0[0xe0];
    GridInner* inner;                                                     // +0xe0
    uint8_t pad1[0x178 - 0xe4];
    uint32_t id178;                                                       // +0x178
    uint8_t pad2[0x1bb - 0x17c];
    uint8_t b1bb;                                                         // +0x1bb
    void FUN_0064f310();
    void FilterEntries();                                                 // 0x64e5b0
    bool Layout(Key_s0064_acd0* key, uint8_t b30, int one, uint32_t f38);            // 0x655840
};
bool __cdecl SetAssetData(uint32_t id, int one);                          // 0x4bbe20
struct AssetList { Key_s0064_acd0* begin; Key_s0064_acd0* end; Key_s0064_acd0* cap; };
struct FeedItem {
    uint8_t pad[0x178];
    uint32_t id178;
    void GetAssetList(AssetList* out);                                    // 0x668d90
};
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void assign(const wchar_t* b, const wchar_t* e);                      // 0x423650
    WString& operator=(const WString& o);                                 // 0x57cb60
    void DeallocateSelf();                                                // 0x933960
};
struct LaunchData;
struct LaunchDataRef {
    LaunchData* p;
    void Assign(LaunchData* d);                                           // 0x61df40 / 0x5766e0
    void CopyFrom(const void* other);                                     // 0x5766e0
};
struct SubRef { IRef_s0064_acd0* p; void CopyFrom(const void* other); };             // 0xac9480
struct LaunchData : IRef2 {
    uint32_t f04, f08;
    uint32_t f0c;                                                         // +0x0c
    Key_s0064_acd0 k10;                                                              // +0x10
    uint32_t f1c;
    uint32_t pad20;
    Key4 k24;                                                             // +0x24
    uint8_t b34, b35, b36, b37, b38, b39, b3a, b3b, b3c, b3d, b3e, b3f;
    uint32_t pad40[4];
    WString str50;                                                        // +0x50
    uint32_t pad5c[2];
    uint8_t b64, b65, b66, b67;
    uint32_t pad68;
    uint8_t b6c, b6d, b6e, b6f;
    uint32_t pad70[5];
    uint32_t f84, f88, f8c, f90;
    SubRef f94;
    LaunchDataRef f98;
    LaunchData();                                                         // 0x5a9080
};
void __cdecl EditorLaunch(LaunchData* d);                                 // 0x5a9200
void __cdecl EditorLaunchEx(uint32_t id, Key_s0064_acd0* k, uint32_t a, uint32_t b, Key4 v, bool flag); // 0x5a94d0
struct IHandlerObj {
    S(0) S(1)
    virtual bool TryHandle(Key_s0064_acd0* k, int one);                              // slot 2 (+8)
};
struct HIter { void* node; HIter() {} HIter(const HIter& o) { node = o.node; } };
struct HMap {
    uint32_t pad;
    void** buckets;                                                       // +0x160 (this+4)
    uint32_t nBuckets;                                                    // +0x164
    HIter find(const uint32_t& key) const;                                // 0x645ed0
    IHandlerObj*& operator[](const uint32_t& key);                        // 0x646f40
};
struct IWin80 {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15)
    S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30)
    virtual void Fade(int a, int b);                                      // slot 31 (+0x7c)
};
struct IWin5c {
    S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15)
    S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30)
    S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) S(44) S(45)
    S(46) S(47) S(48) S(49) S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57)
    virtual void SetFocusChild(void* w);                                  // slot 58 (+0xe8)
};
struct Msg {                       // message passed to HandleMessage
    uint32_t pad0[4];
    uint32_t f10;                  // +0x10
    uint32_t f14;
    uint8_t  b18;
    uint8_t  pad19[3];
    uint32_t f1c, f20;
    Key_s0064_acd0      key;                  // +0x24
    uint8_t  b30, b31, b32, pad33;
    uint32_t f34, f38;
};
struct cSPUIAssetBrowser_s0064_acd0 {
    uint32_t vptr;                 // +0x00
    uint32_t pad04[6];             // +0x04
    uint8_t  b1c, b1d, b1e, b1f;   // +0x1c
    uint32_t f20;                  // +0x20
    uint16_t pad24;                // +0x24
    uint8_t  b26, b27;             // +0x26
    uint16_t pad28;                // +0x28
    uint8_t  b2a, b2b;             // +0x2a
    uint32_t pad2c[12];            // +0x2c
    IWin5c*  p5c;                  // +0x5c
    uint32_t pad60;
    IRef_s0064_acd0*    p64;                  // +0x64
    uint32_t pad68[6];
    IWin80*  p80;                  // +0x80
    uint32_t pad84[13];
    uint32_t cfgId;                // +0xb8
    AssetGrid* grid;               // +0xbc
    FeedList* feedList;            // +0xc0
    uint32_t padc4[2];
    BanEntry* banBegin;            // +0xcc
    BanEntry* banEnd;              // +0xd0
    uint32_t padd4[34];            // +0xd4
    HMap     handlers;             // +0x15c
    uint32_t pad168[11];
    IPropList* props;              // +0x194
    uint32_t pad198;
    uint32_t mField19C;            // +0x19c
    uint32_t f1a0, f1a4, f1a8;     // +0x1a0
    uint8_t  b1ac, b1ad, b1ae, b1af;
    LaunchDataRef f1b0;            // +0x1b0
    LaunchData* src1b4;            // +0x1b4
    uint32_t f1b8;                 // +0x1b8
    uint32_t f1bc;                 // +0x1bc
    uint32_t f1c0;                 // +0x1c0
    uint8_t  b1c4, b1c5, b1c6, b1c7;
    uint32_t pad1c8[7];
    uint32_t f1e4, f1e8;           // +0x1e4
    uint8_t  b1ec, b1ed, b1ee, b1ef;
    uint32_t pad1f0[14];
    IRef_s0064_acd0*    p228;                 // +0x228
    uint32_t f22c;                 // +0x22c
    uint32_t pad230;
    uint8_t  b234, b235, b236, b237;
    uint32_t f238;                 // +0x238
    uint8_t  b23c, b23d, b23e, b23f;
    uint32_t f240, f244, f248;     // +0x240
    uint8_t  b24c;                 // +0x24c

    void ShowSporeGuide();  // 0x0064b6a0 (cSPUIAssetBrowser::ShowSporeGuide)
    void BanItem();  // 0x0064b4b0 (cSPUIAssetBrowser::BanItem)
    void HandleMessage(Msg* m);  // 0x0064b6b0 (cSPUIAssetBrowser::HandleMessage)
    void LaunchEditorEnd();  // 0x0064acd0 (cSPUIAssetBrowser::LaunchEditorEnd)
    void Update();                                                        // 0x64ab20
    void SetLargeCardVisibililty(int a, int b, int c);                    // 0x6478c0
    void FilterGridEntries(int a);                                        // 0x648d90
    void SetVisibility(int a, int b, int c);                              // 0x64a400
    void FUN_00644e20(int a);                                             // 0x644e20
    void FUN_0064c280();                                                  // 0x64c280
    IBanObj* FUN_00645300();                                              // 0x645300
};
struct ABSingleton {
    uint32_t FUN_00645cc0();
    uint32_t FUN_00645bf0();
};
ABSingleton* __cdecl GetAssetBrowser();                                   // 0x401030
struct BanVector {
    void ClearAssetViews();                                               // 0x648aa0
    VecIter* Insert(Key_s0064_acd0* key, AssetHolder* h);                            // 0x648ce0
};
void __cdecl LaunchSporeGuide(uint32_t id);                               // 0x0064aba0
void __cdecl GetEditorSettings(bool flag, LaunchData** out);              // 0x6447c0
struct GameRoot { uint8_t pad[0x3c]; struct { uint8_t pad[0x118]; uint32_t f118; }* sub; };
extern GameRoot* g15fd918;
static inline void FreeStr(WString& s) {
    if (((uint32_t)((char*)s.mpCapacity - (char*)s.mpBegin) & ~1u) > 2 && s.mpBegin)
        operator delete(s.mpBegin);
}
// ---- items of slice s0064acd0 end

// ---- items of slice s0064bc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct LaunchParams {
    uint32_t f00;
    uint32_t f04, f08, f0c;
    uint8_t  f10, f11, f12, f13, f14;
    uint8_t  pad15[3];
    uint32_t f18, f1c, f20;
    uint8_t  f24;
    uint8_t  pad25[3];
    uint32_t f28;
    uint8_t  f2c;
    uint8_t  pad2d[3];
    uint32_t f30;
    uint32_t f34;
    uint32_t f38;
    uint32_t f3c, f40, f44;
};
extern "C" void __cdecl AdvancedLaunch(LaunchParams* p);   // 0x0064a990
struct AssetEntry {
    char pad[0x10];
    void* mpObject;
};
struct StopwatchData {
    uint32_t f00, f04, f08, f0c;
};
struct AssetKey {
    uint32_t mInstance;   // +0x00
    uint32_t mType;       // +0x04
    uint32_t mGroup;      // +0x08
};
struct EaHashIter {
    void* mpNode;         // +0x00 (buckets[count] means "not found")
    void* mpBucket;       // +0x04
};
struct EaMap {
    void* mpAllocator;    // +0x00
    void** mpBuckets;     // +0x04
    uint32_t mBucketCount;// +0x08
    uint32_t mSize;       // +0x0c
    EaHashIter find(const uint32_t& key) const;  // 0x00645ed0
    void** FindOrInsert(const uint32_t& key);    // 0x00646f40
};
struct cSPUIAssetBrowserLayout {
    char pad00[0x14];
    void* mpAnimator;             // +0x14
    void* mpSomething18;          // +0x18
    unsigned char mActive;        // +0x1c
    char pad1d[2];
    unsigned char mField1f;       // +0x1f
    char pad20[0x1c];
    float mTimer;                 // +0x3c
    StopwatchData mStopwatch;     // +0x40
    char pad50[0xc];
    void* mpSomething5c;          // +0x5c
    char pad60[4];
    void* mpSomething64;          // +0x64
    char pad68[0x18];
    void* mpSomething80;          // +0x80
    void* mpSomething84;          // +0x84
    char pad88[0x30];
    void* mpSomethingB8;          // +0xb8
    void* mpSomethingBC;          // +0xbc
    void* mpSomethingC0;          // +0xc0
    char padC4[4];
    void* mpSomethingC8;          // +0xc8
    AssetEntry* mpEntriesBegin;   // +0xcc
    AssetEntry* mpEntriesEnd;     // +0xd0
    AssetEntry* mpEntriesCap;     // +0xd4
    char padD8[0xc];
    AssetKey* mpVec2Begin;        // +0xe4 (key vector)
    AssetKey* mpVec2End;          // +0xe8
    AssetKey* mpVec2Cap;          // +0xec
    char padF0[0x68];
    void* mpSomething158;         // +0x158
    EaMap mMap;                   // +0x15c
    char pad16C[0x10];
    void* mpSomething17c;         // +0x17c
    char pad180[0x20];
    void* mpServer;               // +0x1a0
    void* mpHandler;              // +0x1a4
    uint32_t mMsgId;              // +0x1a8
    unsigned char mField1ac;      // +0x1ac
    char pad1AD[0x1a];
    unsigned char mField1c7;      // +0x1c7
    unsigned char mExpanded;      // +0x1c8
    char pad1C9[0x5f];
    void* mpSomething228;         // +0x228 (= handler's +0x224)
    char pad22C[4];
    int mState230;                // +0x230 (= handler's +0x22c)
    unsigned char mField234;      // +0x234
    char pad235[0x17];
    unsigned char mField24c;      // +0x24c
    char pad24D[1];
    unsigned char mField24e;      // +0x24e

    void* Get_10();                           // 0x00645300
    void Fn_e20(char one);                    // 0x00644e20
    void BanItem();                           // 0x0064b4b0
    void SetVisibility(int a, int b, int c);  // 0x0064a400
    void LaunchEditorEnd();                   // 0x0064acd0
};
typedef void (__fastcall *VCall_Int)(void*, int, int);
typedef void (__fastcall *VCall_IntInt)(void*, int, int, int);
typedef unsigned int (__fastcall *VCall_UInt)(void*);
typedef void (__fastcall *VCall_Ptr)(void*, int, void*);
static void** VTableOf(void* p) { return *(void***)p; }
void* __cdecl FUN_0067cab0(void);                                         // 0x0067cab0
struct SpVector {
    AssetKey* mpBegin;    // +0x00
    AssetKey* mpEnd;      // +0x04
    AssetKey* mpCap;      // +0x08
    void DoInsertKey(AssetKey* pos, const AssetKey* value);  // 0x004e3e10
    AssetKey* Erase(AssetKey* first, AssetKey* last);        // 0x0050f740
};
struct LocaleString {
    void* mpBegin;        // +0x00
    void* mpEnd;          // +0x04
    void* mpCap;          // +0x08
    void Init(const void* name, const uint32_t* id);          // 0x0057ed80
    void Dtor();                                             // 0x00530670
};
struct LocaleMsg2_s0064_bc50 {
    char pad[0x18];
    void Ctor(int arg);                                      // 0x00666a60
    void Dtor();                                             // 0x00644ff0
};
struct Feed {                                                // object at base+0x228
    char pad[0x50];
    void* mpName;         // +0x50
};
struct cSPUIAssetBrowserModalHandler {
    char pad00[0x3c];
    StopwatchData mStopwatch;     // +0x3c (= base +0x40)
    char pad4c[0x10c];
    EaMap mMap;                   // +0x158 (= base +0x15c)
    char pad168[0xbc];
    void* mpFeed;                 // +0x224 (= base +0x228)
    char pad228[4];
    int mModalState;              // +0x22c (= base +0x230)
    void OnModalWindowEnd(int unused, uint32_t messageId);   // 0x0064bcd0
};
inline cSPUIAssetBrowserLayout* BrowserOf(cSPUIAssetBrowserModalHandler* handler) {
    return (cSPUIAssetBrowserLayout*)((char*)handler - 4);
}
struct BrowserGlobals {
    char pad00[0x1f];
    unsigned char mField1f;   // +0x1f
    char pad20[0x3c];
    void* mpPanel;            // +0x5c
    char pad60[0x20];
    void* mpTarget;           // +0x80
};
struct MsgMgr { void* Find(uint32_t id, int one); };                    // 0x0045ae10
struct AchievementsSystem {
    void AutoTest(uint32_t id, int one);                               // 0x00676e90
};
struct cSPUIAssetVerbs {
    bool IsVerb(int verb);                     // 0x00656740
    void SetSelection(int a, int b, int c);    // 0x006571e0
};
struct Pollinator {
    void UnsubscribeToFeed(void* arg);         // 0x00610810
    void DeleteMyFeed(void* arg);              // 0x006106f0
};
struct AppRuntimeState { char pad[0x118]; int mField118; };
struct AppPropertyList { char pad[0x3c]; AppRuntimeState* mpState; };
extern AppPropertyList* g_AppProperties;       // 0x015fd918
void  __fastcall FUN_00801360(void* self);                        // 0x00801360
void* __cdecl AssetBrowser_s0064_bc50();                                     // 0x00401030
void* __cdecl MessageManager();                                   // 0x00401050
void* __cdecl MessageServer_s0064_bc50();                                    // 0x0067dcc0
void* __cdecl AudioSystem();                                      // 0x00a206f0
AchievementsSystem* __cdecl AchievementsController();             // 0x00675250
void  __cdecl RecordEvent2(uint32_t id, uint32_t value);          // 0x00435ed0
Pollinator* __cdecl GetPollinator();                              // 0x0067cb30
void  __cdecl OperatorDelete(void* p);                            // 0x00f47380
void  __fastcall StopwatchRestart(StopwatchData* self);           // 0x00571e80
typedef AssetKey* (__fastcall *VCall_Key)(void*);
typedef bool (__fastcall *VCall_Bool_Key)(void*, int, AssetKey*);
typedef bool (__fastcall *VCall_Bool_KeyInt)(void*, int, AssetKey*, int);
typedef void (__fastcall *VCall_Msg)(void*, int, uint32_t, void*, int);
__forceinline void AutoTestMessage(uint32_t id) {
    if (g_AppProperties->mpState->mField118 == 0)
        AchievementsController()->AutoTest(id, 1);
}
__declspec(noinline) void __fastcall sub_64c280(cSPUIAssetBrowserLayout* self);
// ---- items of slice s0064bc50 end

// ---- items of slice s006470b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_allocTag[];                       // 0x13f6b3c
extern char g_animTargetVtbl[];                 // 0x13f6400
extern char g_animTargetVtbl2[];                // 0x13f63fc
void* __cdecl operator new(unsigned size, const void* tag, int, int, int, int);   // 0xf473a0
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};
struct IRefCounted2 {
    virtual int AddRef();
    virtual int Release();
};
struct cISPLargeAssetView : IRefCounted2 {      // secondary interface living at +0xc of the concrete view
    virtual void Show(int a, int b, int c, int d, int e);   // slot 2
    virtual void Hide();                                    // slot 3
};
struct LargeViewBase0 { virtual void Reserved(); int pad; };
struct LargeAssetView : IRefCounted, LargeViewBase0, cISPLargeAssetView {
    char pad[0xd0 - 0x14];
    LargeAssetView* __thiscall Construct(int n);   // 0x66cbd0 (returns this)
};
struct LargeViewMap {
    cISPLargeAssetView*& __thiscall operator[](const unsigned int& key);   // 0x646f40
};
struct LargeViewRef {                           // AutoRefCount<cISPLargeAssetView>
    cISPLargeAssetView* p;
    void __thiscall Assign(cISPLargeAssetView** src);                        // 0xac9480
};
struct IWindowS {
    virtual int AddRef();
    virtual int Release();
    virtual void vpad2();
    virtual void vpad3();
    virtual IWindowS* GetParent();
    virtual void vpad5();
    virtual void vpad6();
    virtual void vpad7();
    virtual void vpad8();
    virtual void vpad9();
    virtual void vpad10();
    virtual void vpad11();
    virtual void vpad12();
    virtual void vpad13();
    virtual const float* GetArea();
    virtual void vpad15();
    virtual void vpad16();
    virtual void vpad17();
    virtual void vpad18();
    virtual void vpad19();
    virtual void vpad20();
    virtual void vpad21();
    virtual void vpad22();
    virtual void vpad23();
    virtual void vpad24();
    virtual void SetLocation(float x, float y);
    virtual void vpad26();
    virtual void vpad27();
    virtual void vpad28();
    virtual void vpad29();
    virtual void vpad30();
    virtual void SetFlag(int flag, int on);
    virtual void vpad32();
    virtual void vpad33();
    virtual void vpad34();
    virtual void vpad35();
    virtual void vpad36();
    virtual void vpad37();
    virtual void vpad38();
    virtual void vpad39();
    virtual void vpad40();
    virtual void vpad41();
    virtual void vpad42();
    virtual void vpad43();
    virtual void vpad44();
    virtual void vpad45();
    virtual void vpad46();
    virtual void vpad47();
    virtual void vpad48();
    virtual float* ToLocal(float* out, float x, float y);
};
struct IAssetViewS {   // selected-asset object returned by FUN_00645300
    virtual void vpad0();
    virtual void vpad1();
    virtual void vpad2();
    virtual void vpad3();
    virtual void vpad4();
    virtual void vpad5();
    virtual void vpad6();
    virtual void vpad7();
    virtual void vpad8();
    virtual unsigned GetID();
    virtual void vpad10();
    virtual void vpad11();
    virtual void vpad12();
    virtual void vpad13();
    virtual void vpad14();
    virtual void vpad15();
    virtual void vpad16();
    virtual void vpad17();
    virtual void vpad18();
    virtual void vpad19();
    virtual void vpad20();
    virtual void vpad21();
    virtual void vpad22();
    virtual void vpad23();
    virtual bool IsReady();
};
struct AnimTarget {    // temporary animation target; its inlined dtor resets two vptrs and releases a window ref
    void* vtbl;
    int pad;
    void* vtbl2;
    IWindowS* pWin;
    ~AnimTarget() { vtbl = g_animTargetVtbl; vtbl2 = g_animTargetVtbl2; if (pWin) pWin->Release(); }
};
struct cSPUIAnimator_s0064_70b0 {
    void __thiscall RemoveAnimation(IWindowS* win, int channel);                 // 0x7f6210
    void __thiscall AddAnimation(AnimTarget* t, IWindowS* win, int channel);     // 0x7f8d10
};
struct IMessageServer_s0064_70b0 {
virtual void vpad0();
virtual void vpad1();
virtual void vpad2();
virtual void vpad3();
virtual void vpad4();
    virtual void PostMessage(unsigned id, int a, int b);                         // slot 5
};
struct IAudioSystem {
virtual void vpad0();
virtual void vpad1();
virtual void vpad2();
virtual void vpad3();
virtual void vpad4();
virtual void vpad5();
virtual void vpad6();
virtual void vpad7();
virtual int GetSetiHandle();
};
struct cSPUIAssetBrowser_s0064_70b0 {
    char pad0[0x14];
    cSPUIAnimator_s0064_70b0* mAnimator;                      // +0x14
    char pad1[0x24 - 0x18];
    bool mFlag24;                                  // +0x24
    char pad2[0x3c - 0x25];
    float mLargeCardHideTime;                      // +0x3c
    char pad3[0x84 - 0x40];
    IWindowS* mWinLargeCardInputBlocker;           // +0x84
    char pad4[0x9c - 0x88];
    IWindowS* mWinLargeCard;                       // +0x9c
    void* mpMsgServerHandle;                       // +0xa0
    char pad5[0x138 - 0xa4];
    LargeViewMap mLargeAssetViews;                 // +0x138 (retail layout)
    char pad6[0x158 - 0x13c];
    LargeViewRef mCurrentLargeAssetView;           // +0x158
    char pad7[0x1a8 - 0x15c];
    int mCallerID;                                 // +0x1a8
    char pad8[0x23d - 0x1ac];
    bool mFlag23d;                                 // +0x23d
    void __thiscall CreateLargeAssetViews();
    void __thiscall SetLargeCardVisibililty(bool visible, const float* rect, bool immediate);  // 0x006478c0 (cSPUIAssetBrowser::SetLargeCardVisibililty)
    IAssetViewS* __thiscall GetSelectedAsset();    // 0x645300
};
cSPUIAssetBrowser_s0064_70b0* __cdecl AssetBrowser_s0064_70b0();         // SP::AssetBrowser (0x401030)
IMessageServer_s0064_70b0* __cdecl MessageServer();           // SP::MessageServer (0x67dcc0)
IAudioSystem* __cdecl GetSystemAT();               // EA::Audio::GetSystemAT (0xa206f0)
void __cdecl KillSetiEffects(unsigned id, int handle);   // SP::cSPUISpace::KillSetiEffects (0x435ed0)
float __cdecl GetElapsedSeconds(float duration, int zero);                        // SPUIHelpers::GetElapsedSeconds (0x805080)
AnimTarget* __cdecl CreatePositionTarget(AnimTarget* out, IWindowS* win, float x, float y, float dur);   // 0x7f80d0
AnimTarget* __cdecl CreateShadeAlphaTarget(AnimTarget* out, IWindowS* win, int alpha, float dur);        // 0x7f8290
AnimTarget* __cdecl CreateScaleTarget(AnimTarget* out, IWindowS* win, float scale, float dur);           // 0x7f81d0
void __cdecl SetWindowAlpha(IWindowS* win, float a);                                                     // 0x804fc0
void __cdecl SetScale(IWindowS* win, float sx, float sy);                                                // UI::cWindowTransform::SetScale (0x808190)
#define ASSIGN(k) { \
        key = (k); \
        cISPLargeAssetView*& slot = mLargeAssetViews[key]; \
        cISPLargeAssetView* old = slot; \
        if (p != old) { if (p) p->AddRef(); slot = p; if (old) old->Release(); } }
#define NEXT_P() { LargeAssetView* t = view; p = t ? static_cast<cISPLargeAssetView*>(t) : 0; }
    void* operator new(unsigned int, void*, int, int, int, int); // 0x00f473a0
// ---- items of slice s006470b0 end

// ---- items of slice s00643b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
MsgServer* MessageServer_s0064_3b50();
struct Q4 { uint32_t a, b, c, d; };
extern Q4 g15da784_s0064_3b50, g15da7c4;
struct PropOwner { char pad[0x3c]; struct { char pad[0x118]; int flag; }* inner; };
extern PropOwner* g_15fd918;
struct EditorLaunchData { EditorLaunchData* ctor(); };
struct SlotCall { virtual void s0(); virtual void s1(); };
#define OF(T, off) (*(T*)((char*)o + (off)))
struct Msg910 { Key3 k; uint8_t flag; uint8_t pad[3]; Key3 out; };
extern Key3 g1525858, g1525864, g1525870, g152587c, g15258ac;
void Dlg809db0(void* a, const Key3* k);
struct HubD {
    void Fn990();
    void Fn_a40();
};
struct RCBase { virtual void v0(); virtual void v1(); virtual void v2(); };
struct LocaleMsg {
    uint32_t vt0, vt1, f8; RCBase* owner; Key3 key; uint8_t b;
    LocaleMsg(RCBase* o, const Key3* k, uint8_t bb);
    void Dtor();
};
// ---- items of slice s00643b50 end

// ---- items of slice s00647f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete(void* p);                                                                // 0xf47380
extern "C" void EA_RemoveHandler(void* h, void* a, void* b, void* c, void* d);   // 0x571db0
extern "C" void DoFreeNodes34(void* buckets, unsigned int n);                    // 0x961d60
extern "C" void DoFreeBucketsVoidP(void* buckets, unsigned int n);               // 0x693230
struct Primary {
    virtual void p0();
    uint8_t pad[0xc];
};
struct IRef2_s0064_7f40 {
    virtual void AddRef();
    virtual void Release();
};
struct RefObj : Primary, IRef2_s0064_7f40 {};
struct AutoRefObj {
    RefObj* p;
    AutoRefObj() : p(0) {}
    ~AutoRefObj() { if (p) p->Release(); }
};
struct AutoRef {
    IRef2_s0064_7f40* p;
    ~AutoRef() { if (p) p->Release(); }
};
struct Entry14 {
    uint32_t f00, f04, f08;
    AutoRef  h0c;   // +0xc  (primary base)
    AutoRefObj h10; // +0x10 (secondary base)
    void Construct(const Entry14& v);      // 0x645390: copy whole element
    void AssignHandles(const Entry14& v);  // 0x645db0: assign the two handles (this=&h0c)
};
inline bool EntryLess(const Entry14& a, const Entry14& b)
{
    if (a.f00 == b.f00) {
        if (a.f08 == b.f08)
            return a.f04 < b.f04;
        return a.f08 < b.f08;
    }
    return a.f00 < b.f00;
}
struct Key12 { uint32_t a, b, c; };
struct GridVec {
    Entry14* mpBegin;
    Entry14* mpEnd;
    Entry14* mpCapacity;
    uint32_t mFieldC;    // +0xc
    uint32_t mField10;   // +0x10
    uint8_t  mField14;   // +0x14

    Entry14* EraseAt(Entry14* pos);   // 0x648af0
    Entry14* Insert(Entry14* pos, const Entry14& v); // 0x648b40
    void InsertAt(Entry14* pos, const Entry14& v);   // 0x6485e0 (declared)
    Entry14* InsertSorted(Entry14* pos, const Entry14& v); // 0x648c60 (declared)
    Entry14* FindOrInsert(const Key12& k);           // 0x648ce0
    void GrowTo(unsigned int n);                     // 0x648bb0
    void ClearAssetViews();                          // 0x648aa0
    void DoInsertValuesEnd(Entry14* pos, unsigned int n, const Entry14& v); // 0x6483d0
};
extern "C" Entry14* __cdecl f646030(Entry14* first, Entry14* last, const Key12* key, uint8_t flag);
struct GridOps {
    void DestroyRange(Entry14* first, Entry14* last);  // 0x645ff0 (this = GridVec)
    void Sift(Entry14* first, Entry14* last);          // 0x648380 (this = GridVec)
};
typedef void (__thiscall *Fn_v0)(void*);
struct cSPUIAssetGrid {
    void Dtor();       // @ 0x00647f40
    void* Ctor();      // @ 0x00648730
};
// ---- items of slice s00647f40 end

// ---- items of slice s00648d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define SV(n) virtual void v##n();
struct IObj;
struct IBanObj_s0064_8d90;
struct ViewSub;
struct IViewRef;
struct Elem_s0064_8d90 {
  uint32_t  key0;     // +0x00
  uint32_t  key1;     // +0x04
  uint32_t  key2;     // +0x08
  IViewRef* mpView;   // +0x0c
  IBanObj_s0064_8d90*  mpObj;    // +0x10
};
struct Key3_s0064_8d90 { uint32_t a, b, c; };
struct IObj {
  virtual int AddRef();
  virtual int Release();
};
struct IViewRef {
  virtual int AddRef();                 // slot 0
  virtual int Release();                // slot 1
  SV(2) SV(3) SV(4) SV(5) SV(6) SV(7) SV(8) SV(9) SV(10)
  SV(11) SV(12) SV(13) SV(14) SV(15) SV(16) SV(17) SV(18) SV(19) SV(20)
  SV(21) SV(22) SV(23) SV(24) SV(25) SV(26) SV(27) SV(28) SV(29) SV(30)
  SV(31) SV(32) SV(33) SV(34) SV(35) SV(36) SV(37) SV(38) SV(39) SV(40)
  SV(41) SV(42) SV(43) SV(44) SV(45) SV(46) SV(47) SV(48) SV(49)
  virtual void SetFirstUpdate(int v);   // slot 50 -> 0x00657930
};
struct ViewSub {
  SV(0) SV(1) SV(2) SV(3) SV(4) SV(5) SV(6) SV(7) SV(8)
  virtual uint32_t GetTypeID();         // slot 9  (vtable+0x24)
  SV(10) SV(11) SV(12) SV(13) SV(14)
  virtual Key3_s0064_8d90*    GetKey();            // slot 16 (vtable+0x40)
  virtual int      AddRef();            // slot 17
  virtual int      Release();           // slot 18
};
struct IBanObj_s0064_8d90 {
  SV(0) SV(1) SV(2) SV(3) SV(4) SV(5) SV(6) SV(7) SV(8) SV(9) SV(10)
  SV(11) SV(12) SV(13) SV(14) SV(15)
  virtual Key3_s0064_8d90* GetKey();               // slot 16
};
struct Vec14_s0064_8d90 {
  Elem_s0064_8d90* mpBegin;     // +0x00
  Elem_s0064_8d90* mpEnd;       // +0x04
  Elem_s0064_8d90* mpCapacity;  // +0x08
  int size() const { return (int)(mpEnd - mpBegin); }
};
void __stdcall Vec14Reserve(Vec14_s0064_8d90* v, uint32_t n);     // 0x00646fc0
void __stdcall Vec14SwapInto(Vec14_s0064_8d90* v, Vec14_s0064_8d90* tmp);    // 0x00646c90
void __stdcall Vec14Make(Vec14_s0064_8d90* tmp, uint32_t n);      // 0x00646c00
void __stdcall GridVecErase(Vec14_s0064_8d90* v, Elem_s0064_8d90* pos);      // 0x00648af0
Elem_s0064_8d90* __stdcall GridVecInsert(Elem_s0064_8d90* first, Elem_s0064_8d90* last, uint32_t* key);  // 0x00648ce0
Elem_s0064_8d90* __stdcall ListInsertPos(Elem_s0064_8d90* first, Elem_s0064_8d90* last, uint32_t* key, uint8_t flag); // 0x00646030
Elem_s0064_8d90* __stdcall ListCopy(Elem_s0064_8d90* first, Elem_s0064_8d90* last, Elem_s0064_8d90* dst);           // 0x00646140
void  __stdcall ListDestroy(Elem_s0064_8d90* first, Elem_s0064_8d90* last);                   // 0x00645ff0
void  __stdcall ElemInit(Elem_s0064_8d90* e);                                      // 0x00645db0
void  __stdcall SpVecGrow(const uint32_t* val, uint32_t** end);         // 0x00630b30
void  __stdcall BlobInit(uint32_t* blob);                               // 0x006563c0
void  __stdcall BlobOneArg(int a, uint32_t* blob, int c);               // 0x006571e0
void  __stdcall BlobTwoArg(int a, uint32_t* blob, uint32_t* out);       // 0x00656c70
uint32_t* __stdcall MakeKey4(uint32_t* out, uint32_t* src, int c);      // 0x00805fe0
void  __cdecl  FreeBlock(void* p);                                      // 0x00f47380
struct FilterMsg {
  uint32_t  pad0[3];
  IViewRef* mpView;  // +0x0c
  uint8_t   b10;     // +0x10
  uint8_t   pad11[3];
  int       n14;     // +0x14
  uint8_t   b18;     // +0x18
  uint8_t   b19;     // +0x19
  uint8_t   pad1a[2];
};
struct AssetGrid_s0064_8d90 {
  int  IndexOfView(IViewRef* v);      // 0x0064f280
  Elem_s0064_8d90* GetEntry(int index);          // 0x0064f2c0
  int  FindFirstVisibleEntry();       // 0x00653b80
  int  FindLastVisibleEntry();        // 0x00653c40
  void UpdateStatsText();             // 0x006528f0
};
struct HandlerMap {
  uint32_t* FindOrInsert(uint32_t* key);   // 0x00646f40
};
struct cSPUIAssetBrowserR {
  uint8_t  pad00[0x20];
  uint32_t f20;             // +0x20
  uint8_t  b24;             // +0x24
  uint8_t  pad25[0x2a - 0x25];
  uint8_t  b2a;             // +0x2a
  uint8_t  pad2b[0xbc - 0x2b];
  AssetGrid_s0064_8d90* mpGrid;        // +0xbc
  uint8_t  padc0[0xc8 - 0xc0];
  uint32_t mpCallerData;    // +0xc8
  Vec14_s0064_8d90    mBan;            // +0xcc
  uint8_t  padf8[0xe0 - 0xd8];
  uint32_t mpPreloadRef;    // +0xe0
  uint8_t  padf8b[0x138 - 0xe4];
  HandlerMap mHandlers;     // +0x138
  uint8_t  pad13c[0x1a8 - 0x13c];
  uint32_t f1a8;            // +0x1a8
  uint8_t  pad1ac[0x236 - 0x1ac];
  uint8_t  b236;            // +0x236
  uint8_t  pad237[0x23d - 0x237];
  uint8_t  b23d;            // +0x23d

  void SetLargeCardVisibility(int b, uint32_t* data, int c);   // 0x006478c0
  void FilterGridEntries(FilterMsg* msg);                      // 0x00648d90
};
struct ViewBody {
  uint8_t  pad00[0x24];
  IObj*    mp24;   // +0x24
  IObj*    mp28;   // +0x28
  uint8_t  pad2c[0x90 - 0x2c];
  ViewSub* mp90;   // +0x90
};
// ---- items of slice s00648d90 end

// ---- items of slice s0064c8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VPAD4(p)  virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define VPAD8(p)  VPAD4(p##a) VPAD4(p##b)
#define VPAD16(p) VPAD8(p##c) VPAD8(p##d)
#define VPAD32(p) VPAD16(p##e) VPAD16(p##f)
struct ResourceKey_s0064_c8e0 {
    uint32_t instance, type, group;
};
struct IVisibleObject {                 // windows / views / large asset views
VPAD16(a) VPAD8(b) VPAD4(c) virtual void v1c();
virtual void v1d();
virtual void v1e();
    virtual void SetVisible(bool visible, bool animate);       // +0x7c
};
struct IAssetDataList {
    VPAD32(a) VPAD16(b) VPAD8(c) VPAD4(d)
    virtual IVisibleObject* FindView(uint32_t id, bool create);  // +0xf0
};
struct IAuthManager {
VPAD8(a) virtual void v20();
virtual bool IsLoggedIn();
};
struct IMessageServer_s0064_c8e0 {
    VPAD4(a) virtual void v10();
    virtual void MessageSend(uint32_t messageID, void* pMessage, void* pHandler);  // +0x14
};
struct IGameModeManager {
VPAD8(a) VPAD4(b) virtual void v30();
virtual void v34();
    virtual uint32_t GetActiveModeID();                          // +0x38
};
struct Viewport { int x, y; };
struct IRenderView {
VPAD32(a) VPAD16(b) virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
    virtual void GetViewport(Viewport* pRect);                        // +0xd8
};
struct ICameraManager {
VPAD16(a) VPAD4(b) virtual void v14();
virtual void v15();
virtual void v16();
    virtual void SetMode(int a, int b);                          // +0x5c
};
struct IKeySource {
    VPAD16(a) virtual const ResourceKey_s0064_c8e0* GetKey();               // +0x40
};
struct IUpdatable {
VPAD8(a) virtual void v20();
virtual void Update();
};
struct ITypedObject {
    VPAD4(a) virtual uint32_t GetType();                         // +0x10
};
struct IBoolQuery {
    VPAD4(a) virtual bool IsActive();                            // +0x10
};
struct cCaptureJob {
    void Capture(Viewport* pViewport);                                // 0x0076dee0
};
struct cSPUILayoutCollection {
    void Hide();                                                 // 0x00801380
};
struct SporeGuideState {
    uint32_t pad0[7];
    bool mbVisible;                                              // +0x1c
};
struct AppProperties {
    uint32_t pad0[15];
    struct Inner { uint32_t pad[0x118 / 4]; uint32_t mValue; }* mpInner;   // +0x3c
};
struct cSPUIFeedListItem {
    uint32_t pad0[0x128 / 4];
    const wchar_t* mWebURL;          // +0x128
    const wchar_t* mSporeGuidePage;  // +0x12c
    uint32_t pad130;
    uint32_t mFeedArg;               // +0x134
    uint32_t pad138[6];
    uint32_t mFeedID;                // +0x150
    uint32_t mConfigID;              // +0x154
    uint32_t pad158[8];
    uint32_t mItemType;              // +0x178
    uint32_t mItemID;                // +0x17c

    void SetSelected(bool b);                                    // 0x00666490
    void GetAssetList(void* pList);                              // 0x00668d90
};
struct cSPUIFeedList {
    cSPUIFeedListItem* FindItem(uint32_t id);                    // 0x00662960
    cSPUIFeedListItem* FindItemByIndex(uint32_t id);             // 0x006629a0
};
struct cSPUIFeedEdit {
    void SetEditActive(bool active);                             // 0x0065d9f0
    void Refresh();                                              // 0x0065e720
    void OnEvent(void* pMsg);                                    // 0x0065dd30
};
struct cSPUIAssetWebBrowser {
    void SetActive(bool active);                                 // 0x0065b2a0
    void ClearPage();                                            // 0x0065b510
};
struct cSPUISporeGuidePage {
    void LoadSporeGuidePage(const wchar_t* name);                // 0x00675080
};
void operator delete[](void* p);                                 // 0x00f47380
struct InsertResult_s0064_c8e0 { uint32_t* it; bool inserted; };
struct IDSet {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    IDSet() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~IDSet() { if (mpBegin) delete[] (char*)mpBegin; }
    void reserve(uint32_t n);                                    // 0x00565f50
    InsertResult_s0064_c8e0 insert(const uint32_t& value);                  // 0x00554020
};
struct FeedEntry {                  // 0x34 bytes
    uint32_t mID;
    uint32_t pad[12];
};
struct FeedEntryVector {
    FeedEntry* mpBegin;
    FeedEntry* mpEnd;
    FeedEntry* mpCapacity;
    FeedEntryVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~FeedEntryVector();                                          // 0x00647080
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct AssetList_s0064_c8e0 {                   // 12 bytes, dtor 0x007a41a0
    uint32_t mpBegin, mpEnd, mpCapacity;
    AssetList_s0064_c8e0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~AssetList_s0064_c8e0();                                                // 0x007a41a0
};
struct cAssetFilterPreview {
    void SetFeedFilter(IDSet* pIDs);                             // 0x00661380
    void Apply(uint32_t feedID, uint32_t configID, bool reset);  // 0x00662750
};
struct cSPUIAssetGrid_s0064_c8e0 {
    uint32_t pad0[0xe0 / 4];
    cAssetFilterPreview* mpFilterPreview;                        // +0xe0
    uint32_t pade4[(0x1e4 - 0xe4) / 4];
    bool mbIsEditorGrid;                                         // +0x1e4

    const ResourceKey_s0064_c8e0* GetEntryByID(uint32_t id);                // 0x006505d0
    bool SelectAsset(const ResourceKey_s0064_c8e0* key, bool a, bool b, bool c);   // 0x00655840
    void ResetScroll();                                          // 0x0064e5b0
    void Repopulate();                                           // 0x0064f310
    void SetAssetList(AssetList_s0064_c8e0* list);                          // 0x00656310
    void SetFeed(struct cBrowserConfig* config, cSPUIFeedListItem* item);       // 0x00654730
    void ShowItem(struct cBrowserConfig* config, cSPUIFeedListItem* item);      // 0x00654f50
};
struct ConfigMapIterator { void* mpNode; };
struct ConfigMap {                   // eastl::map<ResourceKey, ...>
    uint32_t mCompare;
    uint32_t mAnchor[5];
    ConfigMapIterator find(const ResourceKey_s0064_c8e0& key);              // 0x00a21dc0
};
struct QueryKey {                    // ResourceKey + extra flag, 16 bytes
    ResourceKey_s0064_c8e0 key;
    uint32_t flags;
};
struct cBrowserConfig {
    uint32_t pad0[0x48 / 4];
    ConfigMap mConfigs;                                          // +0x48
    void SetQuery(const QueryKey* q, int flags);                 // 0x00643f70
    void SetQueryKey(const ResourceKey_s0064_c8e0* key);                    // 0x006435e0
    void SetAssets(AssetList_s0064_c8e0* list, int flags);                  // 0x00644550
};
struct BrowserMessage {              // id 0xb3d53f95
    uint32_t pad0[3];
    uint32_t mFeedItemID;            // +0x0c
    cSPUIFeedListItem* mpItem;       // +0x10
    bool mbByIndex;                  // +0x14
    bool mbForceReset;               // +0x15
    uint16_t pad16;
    explicit BrowserMessage(uint32_t feedItemID);               // 0x00666af0
    explicit BrowserMessage(cSPUIFeedListItem* item);           // 0x00666a60
    ~BrowserMessage();                                          // 0x00644ff0
};
template<typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p);                              // 0x00b5f950
    T* get() const { return mpObject; }
};
struct cRefFeedListItem : cSPUIFeedListItem {};
struct RefItem { virtual void AddRef(); virtual void Release(); };
struct SelectItemMessage {           // id 0x3b60b3ad, 0x20 bytes
    uint32_t pad0[3];
    AutoRefCount<RefItem> mpItem;    // +0x0c
    ResourceKey_s0064_c8e0 mKey;                // +0x10
    bool mbHasQueryFlags;            // +0x1c
    uint8_t pad1d;
    uint16_t pad1e;
    SelectItemMessage(cSPUIFeedListItem* item, const ResourceKey_s0064_c8e0* key, int flags);   // 0x00644a80
    ~SelectItemMessage();                                       // 0x00644af0
};
struct AssetPollinatedMessage {      // id 0x068cd252
    bool mbSuccess;                  // +0x00
    uint8_t pad1[3];
    ResourceKey_s0064_c8e0 mKey;                // +0x04
};
struct DialogResultMessage {         // id 0x1dd7bda9
    int mResult;
    ITypedObject* mpDialog;
};
struct EventMessage {                // id 0x54495773
    uint8_t pad0[0x33];
    uint8_t mBrowserIndex;           // +0x33
};
struct IHandlerBase { virtual void h0(); };
struct IModalWindowCallback { virtual void m0(); };
class cSPUIAssetBrowser_s0064_c8e0 : public IHandlerBase, public IModalWindowCallback {
public:
    uint32_t pad08[5];
    bool mIsVisible;                         // +0x1c
    uint8_t pad1d[0xc];
    uint8_t mBrowserIndex;                   // +0x29
    bool mbIsForEditor;                      // +0x2a
    uint8_t pad2b[0x15];
    uint32_t mCardWindows[4];                // +0x40
    uint32_t pad50[5];
    IAssetDataList* mpAssetListData;         // +0x64
    uint32_t pad68[10];
    IVisibleObject* mpLargeViewA;            // +0x90
    IVisibleObject* mpLargeViewB;            // +0x94
    IVisibleObject* mpSporeGuideView;        // +0x98
    uint32_t pad9c[7];
    cBrowserConfig* mpConfig;                // +0xb8
    cSPUIAssetGrid_s0064_c8e0* mpAssetGrid;             // +0xbc
    cSPUIFeedList* mpFeedList;               // +0xc0
    cSPUIFeedEdit* mpFeedEditor;             // +0xc4
    uint32_t padc8;
    uint8_t* mSelectionBegin;                // +0xcc  (vector of 20-byte entries)
    uint8_t* mSelectionEnd;                  // +0xd0
    uint32_t padd4[0x21];
    IBoolQuery* mpFilterPanel;               // +0x158
    uint32_t pad15c[8];
    uint32_t mCallToAction;                  // +0x17c
    uint32_t pad180[0x12];
    bool mbLockSelection;                    // +0x1c8
    uint8_t pad1c9[0x17];
    uint32_t mPendingButton;                 // +0x1e0
    uint32_t mFeedOverride;                  // +0x1e4
    uint32_t mConfigOverride;                // +0x1e8
    uint8_t pad1ec;
    bool mbForceReset;                       // +0x1ed
    uint8_t pad1ee[0x22];
    uint32_t mCurrentWebURL;                 // +0x210
    uint32_t pad214[2];
    cSPUIAssetWebBrowser* mpWebBrowserA;     // +0x21c
    cSPUIAssetWebBrowser* mpWebBrowserB;     // +0x220
    cSPUISporeGuidePage* mpSporeGuide;       // +0x224
    AutoRefCount<cRefFeedListItem> mpCurrentItem;   // +0x228
    uint32_t pad22c[2];
    bool mbLaunchingEditor;                  // +0x234
    bool mbEnteringEditor;                   // +0x235
    uint8_t pad236[0x17];
    bool mbPublishAllowed;                   // +0x24d
    bool mbAwaitingPollination;              // +0x24e
    bool mbPublishBlocked;                   // +0x24f

    bool HandleMessage(uint32_t messageID, void* pMessage);  // 0x0064b6b0 (cSPUIAssetBrowser::HandleMessage)

    // out-of-line members called from here
    void ShowPublishDialog();                                    // 0x00645e20
    void OnRefresh();                                            // 0x0064c6b0
    void LaunchEditorEnd();                                      // 0x0064acd0
    void OnLayoutChanged();                                      // 0x00645260
    void SetLargeCardState(bool show, uint32_t id);              // 0x00644d10
    void ShowLargeCard(bool show, uint32_t a, uint32_t b);       // 0x00644c50
    void SetLargeCardVisibility(bool a, bool b, bool c);         // 0x006478c0
    void Update();                                               // 0x0064ab20
    void OnTabChanged();                                         // 0x00644a40
    uint32_t GetSelectedID();                                    // 0x006452c0
    IKeySource* GetSelectedAsset();                              // 0x00645300
    void FilterGridEntries(void* filter);                        // 0x00648d90
    void ClosePollinationUI(int a);                              // 0x00644e20
    bool IsWebPageShown();                                       // 0x00644dd0
    void SetWebBrowserVisibility(bool visible, const wchar_t* url);   // 0x00644b90
    void OnEditorChosen();                                       // 0x0064c0d0
    int CanLaunchEditor();                                       // 0x00645cc0
    void SetVisibility(int a, int b, int c);                     // 0x0064a400
    void HandleEvent(void* pMsg);                                // 0x0064b6b0

    __forceinline void HideLargeViewA();
    __forceinline void HideLargeViewB();
};
IAuthManager* AuthManager_s0064_c8e0();                                     // 0x00607a60
IMessageServer_s0064_c8e0* MessageServer_s0064_c8e0();                                 // 0x0067dcc0
IRenderView* RenderView();                                       // 0x0067dd40
cCaptureJob* CaptureJob();                                       // 0x0067dda0
ICameraManager* CameraManager();                                 // 0x0067dd50
IGameModeManager* GameModeManager();                             // 0x0067dd10
cSPUILayoutCollection* LayoutCollection();                       // 0x0067cab0
SporeGuideState* SporeGuide_s0064_c8e0();                                   // 0x00401040
cSPUIAssetBrowser_s0064_c8e0* AssetBrowser_s0064_c8e0();                               // 0x00401030
uint32_t GetRecorderState();                                     // 0x00435e90
void KillSetiEffects(uint32_t id, uint32_t state);               // 0x00435ed0
uint32_t SPIDFromName(const char* name);                         // 0x00571cf0
void CalloutMessageBox(IModalWindowCallback* cb, const ResourceKey_s0064_c8e0* key);   // 0x00809db0
bool KeysEqual(const ResourceKey_s0064_c8e0* a, const ResourceKey_s0064_c8e0* b);      // 0x004eb930
bool GetCreatorType(const ResourceKey_s0064_c8e0* key);                     // 0x00641900
IUpdatable* UpdateSaveAreas(const ResourceKey_s0064_c8e0* key);             // 0x006b22a0
void GetFeedEntries(uint32_t feedID, FeedEntryVector* out);      // 0x00661900
extern AppProperties* sAppProperties;                            // 0x015fd918
extern const ResourceKey_s0064_c8e0 kPollinateFailedDialog;                 // 0x01525840
extern const ResourceKey_s0064_c8e0 kConfirmDialogA;                        // 0x015258b8
extern const ResourceKey_s0064_c8e0 kConfirmDialogB;                        // 0x015258c4
__forceinline void cSPUIAssetBrowser_s0064_c8e0::HideLargeViewA() {
    AuthManager_s0064_c8e0()->IsLoggedIn();
    if (mpAssetListData) {
        IVisibleObject* view = mpAssetListData->FindView(0x561e0a8, true);
        if (view)
            view->SetVisible(true, false);
    }
    if (mpLargeViewA)
        mpLargeViewA->SetVisible(true, false);
    if (mpWebBrowserA)
        mpWebBrowserA->SetActive(false);
}
__forceinline void cSPUIAssetBrowser_s0064_c8e0::HideLargeViewB() {
    AuthManager_s0064_c8e0()->IsLoggedIn();
    if (mpAssetListData) {
        IVisibleObject* view = mpAssetListData->FindView(0x561e0a8, true);
        if (view)
            view->SetVisible(true, false);
    }
    if (mpLargeViewB)
        mpLargeViewB->SetVisible(true, false);
    if (mpWebBrowserB)
        mpWebBrowserB->SetActive(false);
}
// ---- items of slice s0064c8e0 end

// @ 0x006447c0
void MakeLaunchData(char flag, RCObj** out)
{
    if (!out) return;
    bool b = flag != 0;
    Q4 q = g15da784_s0064_3b50;
    uint8_t bl = 1;
    uint8_t nb = 1;
    uint8_t bb = 0;
    uint8_t nb2 = bl;
    if (b) {
        q = g15da7c4;
        bl = 0; nb = 0; bb = 1; nb2 = bl;
    }
    if (g_15fd918->inner->flag != 0) bl = 0;
    void* mem = EASTL_allocator_allocate(0x9c, "Editor", 0, 0, 0, 0);
    char* o = (char*)(mem ? ((EditorLaunchData*)mem)->ctor() : 0);
    OF(uint32_t, 0x24) = q.a;
    OF(uint32_t, 0x28) = q.b;
    OF(uint32_t, 0x2c) = q.c;
    OF(uint8_t, 0x34) = nb;
    OF(uint32_t, 0x30) = q.d;
    OF(uint8_t, 0x3d) = bb;
    OF(uint8_t, 0x6d) = flag;
    OF(uint8_t, 0x6f) = nb2;
    OF(uint8_t, 0x36) = 1; OF(uint8_t, 0x37) = 1; OF(uint8_t, 0x38) = 1;
    OF(uint8_t, 0x3a) = bl;
    OF(uint8_t, 0x64) = 1;
    ((SlotCall*)o)->s1();
    *out = (RCObj*)o;
}

// @ 0x00644910
uint8_t __stdcall Query910(const Key3* in, Key3* out)
{
    Msg910 m;
    m.k = *in;
    m.flag = 1;
    m.out.a = 0; m.out.b = 0; m.out.c = 0;
    MessageServer_s0064_3b50()->Send(0xf1ff568b, &m, 0);
    *out = m.out;
    return m.flag;
}

// @ 0x00644990
void HubD::Fn990()
{
    Key3 k; k.a = 0; k.b = 0; k.c = 0;
    uint8_t flag = 0;
    const Key3* p;
    if (AT(uint32_t, 0x22c) == 0) {
        MessageServer_s0064_3b50()->Send(0x12a93f05, &flag, 0);
        p = &g1525858;
        if (!flag) p = &g1525864;
    } else {
        MessageServer_s0064_3b50()->Send(0x12a93f05, &flag, 0);
        p = &g1525870;
        if (!flag) p = &g152587c;
    }
    k.a = p->a;
    k.b = p->b;
    k.c = p->c;
    Dlg809db0(&AT(char, 4), &k);
    AT(uint32_t, 0x230) = 1;
}

// @ 0x00644a80
LocaleMsg::LocaleMsg(RCBase* o, const Key3* k, uint8_t bb)
{
    *(volatile uint32_t*)&vt1 = 0x13ef094;
    f8 = 0;
    vt0 = 0x13ff800;
    vt1 = 0x13ff7fc;
    owner = o;
    if (o) o->v0();
    key = *k;
    b = bb;
}

// @ 0x00644b90
void SP::cSPUIAssetBrowser::SetWebBrowserVisibility(bool vis, unsigned int x)
{
    void* am = AuthManager();
    uint8_t bl = ((Fn_b0)VSLOT(am, 0x24))(am);
    ListDataV* ld = AT(ListDataV*, 0x64);
    if (ld) {
        WinV* w = ld->GetWin(0x561e0a8, 1);
        if (w) {
            uint8_t f;
            if (bl && vis) f = 1; else f = 0;
            w->SetFlag(1, f != 0);
        }
    }
    WinV* lv = AT(WinV*, 0x90);
    if (lv) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        lv->SetFlag(1, f != 0);
    }
    WebBrowser* wb = AT(WebBrowser*, 0x21c);
    if (wb) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        wb->SetActive(f);
        if (!bl && vis) MessageServer_s0064_4b90()->Send(0xd4231540, &x, 0);
    }
}

// @ 0x00644c50
void Browser::Fn_c50(char vis, uint32_t a, uint32_t b)
{
    void* am = AuthManager();
    uint8_t bl = ((Fn_b0)VSLOT(am, 0x24))(am);
    ListDataV* ld = AT(ListDataV*, 0x64);
    if (ld) {
        WinV* w = ld->GetWin(0x561e0a8, 1);
        if (w) {
            uint8_t f;
            if (bl && vis) f = 1; else f = 0;
            w->SetFlag(1, f != 0);
        }
    }
    WinV* lv = AT(WinV*, 0x94);
    if (lv) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        lv->SetFlag(1, f != 0);
    }
    WebBrowser* wb = AT(WebBrowser*, 0x220);
    if (wb) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        wb->SetActive(f);
        if (!bl && vis) AT(WebBrowser*, 0x220)->Navigate(a, b);
    }
}

// @ 0x00644d10
void Browser::Fn_d10(char vis, int x)
{
    void* am = AuthManager();
    uint8_t bl = ((Fn_b0)VSLOT(am, 0x24))(am);
    ListDataV* ld = AT(ListDataV*, 0x64);
    if (ld) {
        WinV* w = ld->GetWin(0x561e0a8, 1);
        if (w) {
            uint8_t f;
            if (bl && vis) f = 1; else f = 0;
            w->SetFlag(1, f != 0);
        }
    }
    if (AT(SubA*, 0xc4)) {
        if (vis && !bl) {
            AT(SubA*, 0xc4)->Set(1);
            if (x) { AT(SubA*, 0xc4)->Fn_ef30(x, 0); return; }
            AT(SubA*, 0xc4)->Fn_e720();
            return;
        }
        AT(SubA*, 0xc4)->Set(0);
    }
}

// @ 0x00644db0
int Browser::IsA()
{
    void* p = AT(void*, 0x98);
    if (p) {
        uint32_t r = (uint32_t)((Fn_i0)VSLOT(p, 0x28))(p);
        if (r & 1) return 1;
    }
    return 0;
}

// @ 0x00644dd0
int Browser::IsB()
{
    void* p = AT(void*, 0x90);
    if (p) {
        uint32_t r = (uint32_t)((Fn_i0)VSLOT(p, 0x28))(p);
        if (r & 1) return 1;
    }
    return 0;
}

// @ 0x00644df0
int Browser::CanSporepediaShowSporeGuide()
{
    if (AT(uint8_t, 0x1c) != 0 && AT(uint32_t, 0x158) == 0 && AT(uint32_t, 0x230) == 0) return 1;
    return 0;
}

// @ 0x00644e20
void Browser::Fn_e20(char flag)
{
    void* w = AT(void*, 0x80);
    if (w && AT(void*, 0x5c)) {
        if (flag) {
            ((Fn_v2)VSLOT(w, 0x7c))(w, 1, 1);
            w = AT(void*, 0x80);
            ((Fn_v2)VSLOT(w, 0x7c))(w, 0x40, 1);
            void* p = AT(void*, 0x5c);
            ((Fn_v1)VSLOT(p, 0xe8))(p, AT(void*, 0x80));
            AT(uint8_t, 0x1f) = 1;
            return;
        }
        ((Fn_v2)VSLOT(w, 0x7c))(w, 1, AT(uint8_t, 0x1c));
        w = AT(void*, 0x80);
        ((Fn_v2)VSLOT(w, 0x7c))(w, 0x40, 0);
        if (AT(void*, 0x64)) {
            void* p = AT(void*, 0x5c);
            ((Fn_v1)VSLOT(p, 0xe8))(p, AT(void*, 0x64));
        }
        AT(uint8_t, 0x1f) = 0;
    }
}

// @ 0x00644eb0
void Browser::Fn_eb0()
{
    void* cfg = AT(void*, 0xb0);
    if (!cfg) return;
    uint32_t id = (uint32_t)((Fn_i0)VSLOT(cfg, 0x40))(cfg);
    char* st = (char*)GetStyleManager(1)->GetStyle(id, 0);
    cfg = AT(void*, 0xb0);
    if (!cfg) return;
    void* prop = ((Fn_p2)VSLOT(cfg, 0xc))(cfg, 0xf15f4bd, 0);
    if (!prop || !st) return;
    *(float*)(st + 0x200) = AT(float, 0x214);
    if (*(int*)(st + 0x254) != 2) return;
    *(int*)(st + 0x254) = 0;
    float r0[4];
    GetBounds(r0, AT(void*, 0xb0));
    while (*(float*)(st + 0x200) > 8.0f) {
        float r1[4];
        ((Fn_rect)VSLOT(prop, 0x20))(prop, r1, 0, 1);
        if (!((r1[2] - r1[0]) > (r0[2] - r0[0]))) break;
        *(float*)(st + 0x200) = *(float*)(st + 0x200) - 1.0f;
    }
    *(int*)(st + 0x254) = 2;
}

// @ 0x00644fc0
void RelPair::Release2()
{
    if (a) a->Release();
    if (b) b->Release();
}

// @ 0x00644ff0
void LocaleMsg2::Dtor()
{
    if (owner) owner->Release();
    vt1 = 0x13ef094;
    vt0 = 0x13eb918;
}

// @ 0x00645010
void SP::cSPUIAssetBrowser::PreloadTextures()
{
    static ResourceKey keys[8] = {
        ResourceKey(0x7c6511a1, 0x510a95b, 0x851d4139), ResourceKey(0x0ab75403, 0x510a95b, 0x851d4139),
        ResourceKey(0x84f7a71d, 0x510a95b, 0x851d4139), ResourceKey(0xdecdb609, 0x510a95b, 0x851d4139),
        ResourceKey(0xc1966e00, 0x510a95b, 0x851d4139), ResourceKey(0x5a71fb79, 0x510a95b, 0x851d4139),
        ResourceKey(0xd525562b, 0x510a95b, 0x851d4139), ResourceKey(0x993618cc, 0x510a95b, 0x851d4139) };
    void* mem = EASTL_allocator_allocate(0x34, "", 0, 0, 0, 0);
    TexturePreload* tp = mem ? ((TexturePreload*)mem)->ctor(-1) : 0;
    PlainRC* old = AT(PlainRC*, 0x218);
    if (tp != (TexturePreload*)old) {
        if (tp) ((PlainRC*)tp)->AddRef();
        AT(TexturePreload*, 0x218) = tp;
        if (old) old->Release();
    }
    for (ResourceKey* k = keys; k < keys + 8; ++k)
        AT(TexturePreload*, 0x218)->PreloadTextureList(k);
}

// @ 0x00645160
void Browser::Fn_160()
{
    Ent20* begin = AT(Ent20*, 0xcc);
    Ent20* end = AT(Ent20*, 0xd0);
    uint32_t i = 0;
    Key3 out; out.a = 0; out.b = 0; out.c = 0;
    uint32_t n = (uint32_t)(end - begin);
    if (n != 0) {
        int off = 0;
        do {
            Obj3* o = (Obj3*)((Ent20*)((char*)AT(Ent20*, 0xcc) + off))->e;
            Key3 k; k.a = 0; k.b = 0; k.c = 0;
            if (o) {
                Key3* kp = o->GetKey();
                k.a = kp->a; k.b = kp->b; k.c = kp->c;
            }
            if (!Query(&k, &out)) {
                AT(uint32_t, 0x230) = 7;
                ErrDlg(&AT(char, 4), &out);
                return;
            }
            ++i;
            off += 0x14;
        } while (i < (uint32_t)(AT(Ent20*, 0xd0) - AT(Ent20*, 0xcc)));
    }
    GetWindowManager()->SetWin(0, AT(void*, 0x64));
    ((BrowserB*)this)->Fn990();
}

// @ 0x00645260
void Browser::Fn_260()
{
    const Key3* p;
    Obj6p* o = AT(Obj6p*, 0x228);
    if (o && ((Obj6c*)o)->Check()) {
        GetSvcB()->Get()->Do13(AT(Obj6p*, 0x228)->f28, 0);
        p = &g1525894;
    } else {
        p = &g15258a0;
    }
    ErrDlg(&AT(char, 4), p);
    AT(uint32_t, 0x230) = 5;
}

// @ 0x006452c0
uint32_t Browser::Get_c()
{
    VecEnt20& v = AT(VecEnt20, 0xcc);
    if (!v.empty() && v.size() == 1) return (uint32_t)v.mpBegin->d;
    return 0;
}

// @ 0x00645300
uint32_t Browser::Get_10()
{
    VecEnt20& v = AT(VecEnt20, 0xcc);
    if (!v.empty() && v.size() == 1) return (uint32_t)v.mpBegin->e;
    return 0;
}

// @ 0x00645340
Node12* __stdcall AllocNode12(const Node12* src)
{
    Node12* n = (Node12*)EASTL_allocator_allocate(0xc, "Editor", 0, 0, EASTL_ALLOC_FILE, 0xd1);
    if (n) {
        n->a = src->a;
        n->b = src->b;
        if (n->b) n->b->AddRef();
    }
    n->c = 0;
    return n;
}

// @ 0x00645390
Ent20x* Ent20x::Copy(const Ent20* o)
{
    a = o->a; b = o->b; c = o->c;
    d = o->d; if (d) d->AddRef();
    e = o->e; if (e) e->AddRef();
    return this;
}

// @ 0x006453e0
Ent20** UninitCopyOut(Ent20** out, Ent20* first, Ent20* last, Ent20* dest)
{
    *out = dest;
    for (; first != last; ++first) {
        Ent20* p = *out;
        if (p) {
            p->a = first->a; p->b = first->b; p->c = first->c;
            p->d = first->d; if (p->d) p->d->AddRef();
            p->e = first->e; if (p->e) p->e->AddRef();
        }
        *out = *out + 1;
    }
    return out;
}

// @ 0x00645450
Ent20* UninitCopy(Ent20* first, Ent20* last, Ent20* dest)
{
    if (first != last) {
        do {
            if (dest) {
                dest->a = first->a; dest->b = first->b; dest->c = first->c;
                dest->d = first->d; if (dest->d) dest->d->AddRef();
                dest->e = first->e; if (dest->e) dest->e->AddRef();
            }
            ++first;
            ++dest;
        } while (first != last);
        return dest;
    }
    return dest;
}

// @ 0x006454c0
Ent20* DestroyRange(Ent20* first, Ent20* last, Ent20* dest)
{
    if (first != last) {
        do {
            if (first->e) first->e->Release();
            PlainRC* x = first->d;
            if (x) x->Release();
            ++first;
            ++dest;
        } while (first != last);
        return dest;
    }
    return dest;
}

// @ 0x00645510
void UninitFillN(Ent20* dest, uint32_t n, const Ent20* v)
{
    while (n > 0) {
        if (dest) {
            dest->a = v->a; dest->b = v->b; dest->c = v->c;
            dest->d = v->d; if (dest->d) dest->d->AddRef();
            dest->e = v->e; if (dest->e) dest->e->AddRef();
        }
        n--;
        ++dest;
    }
}

// @ 0x006455b0
void Browser::SetCallToActionMessage(const short* msg)
{
    if (AT(MsgHandlerObj*, 0xb0)) {
        cString s;
        if (!msg || *msg == 0) {
            GetPropertyAsText(AT(void*, 0x194), 0x344ec74e, &s);
            msg = s.ValueOrDefault();
        }
        AT(MsgHandlerObj*, 0xb0)->SetText(msg);
        ((BrowserB*)this)->Fn990();
        s.c_str();
    }
}

// @ 0x00645620
void SP::cSPUIAssetBrowser::LoadConfigFile(SP::cSPUIAssetBrowserLaunch const & a1, bool & a2)
{}

// @ 0x00645bf0
void cSPUIAssetBrowser::FUN_00645bf0()
{}

// @ 0x00645cc0
void cSPUIAssetBrowser::FUN_00645cc0_()
{}

// @ 0x00645d90
int cSPUIAssetBrowser::FUN_00645d90()
{
    int r = mField1c0;
    if (r == 0) {
        r = GetAssetBrowser2()->FUN_00645cc0();
        if (r == 0)
            r = -1;
    }
    return r;
}

// @ 0x00645db0
void cSPUIAssetBrowser::FUN_00645db0(Elem* other)
{ other->a = 0; }

// @ 0x00645e20
__declspec(noinline) void cSPUIAssetBrowser::FUN_00645e20()
{ gPartialCall3(); }

// @ 0x00645ff0
void __stdcall FUN_00645ff0(Elem* first, Elem* last)
{
    for (; first < last; first = (Elem*)((char*)first + 0x14)) {
        cRefB* q = first->q;
        if (q)
            q->Release();
        cRefCountA* p = first->p;
        if (p)
            p->Release();
    }
}

// @ 0x00646030
Elem* cSPUIAssetBrowser::FUN_00646030(Elem* first, Elem* last, uint32_t* key)
{ (void)last; (void)key; return first; }

// @ 0x006460b0
void cSPUIAssetBrowser::FUN_006460b0(Elem* first, Elem* last, Elem* src)
{
    for (; first != last; first = (Elem*)((char*)first + 0x14)) {
        first->a = src->a;
        first->b = src->b;
        first->c = src->c;
        cRefCountA* newp = src->p;
        cRefCountA* oldp = first->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            first->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = src->q;
        cRefB* oldq = first->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            first->q = newq;
            if (oldq) oldq->Release();
        }
    }
}

// @ 0x00646140
Elem* cSPUIAssetBrowser::FUN_00646140(Elem* first, Elem* last, Elem* dst)
{
    while (first != last) {
        dst->a = first->a;
        dst->b = first->b;
        dst->c = first->c;
        cRefCountA* newp = first->p;
        cRefCountA* oldp = dst->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            dst->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = first->q;
        cRefB* oldq = dst->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            dst->q = newq;
            if (oldq) oldq->Release();
        }
        first = (Elem*)((char*)first + 0x14);
        dst = (Elem*)((char*)dst + 0x14);
    }
    return dst;
}

// @ 0x006461d0
Elem* cSPUIAssetBrowser::FUN_006461d0(Elem* first, Elem* last, Elem* dst)
{
    while (last != first) {
        last = (Elem*)((char*)last - 0x14);
        dst = (Elem*)((char*)dst - 0x14);
        dst->a = last->a;
        dst->b = last->b;
        dst->c = last->c;
        cRefCountA* newp = last->p;
        cRefCountA* oldp = dst->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            dst->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = last->q;
        cRefB* oldq = dst->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            dst->q = newq;
            if (oldq) oldq->Release();
        }
    }
    return dst;
}

// @ 0x00646260
void cSPUIAssetBrowser::FUN_00646260()
{
    mb24d = true;
    IAuthMgr* auth = GetAuthMgr();
    if (auth->a22() && !auth->a9()) {
        FUN_00645e20();
        return;
    }
    GetAuthMgr()->a17();
    mField230 = 0;
}

// @ 0x006462b0
void cSPUIAssetBrowser::FUN_006462b0(void* p)
{ (void)p; }

// @ 0x00646370
bool __stdcall CloneModelAsset(Key key, Key* pOutKey, int size, bool bKeepParent)
{
    uint32_t dbId;
    switch (key.type) {
    case 0x366a930d: dbId = 0x86ca01c9; break;
    case 0x2399be55: dbId = 0x11ac19a;  break;
    case 0x24682294: dbId = 0x11ac19b;  break;
    case 0x2b978c46: dbId = 0x11ac199;  break;
    case 0x3d97a8e4: dbId = 0x90368ea3; break;
    case 0x476a98c7: dbId = 0x90368ea2; break;
    default: return false;
    }
    Database* pSave = GetSaveArea(dbId);
    uint32_t group = key.group;
    Key newKey; newKey.instance = 0; newKey.type = 0; newKey.group = 0;
    if ((group & 0xc0000000) != 0x40000000 || dbId == 0)
        return false;

    cIDGenerator* gen = GetIDGenerator();
    gen->Generate(newKey, key.type, (group >> 16) & 0xff, (group >> 24) & 0x1f,
                  (group >> 8) & 0xff, 0);
    Ref<ResObj> spModel;
    IResourceManager* mgr = GetManager();
    spModel.Reset();
    if (!mgr->GetPrivateResource(key, &spModel, 0, 0, 0, 0))
        return false;

    // Re-key the privately loaded model and write it into the save area.
    spModel.p->mKey = newKey;
    Key nameKey = newKey;
    CastTarget3c609f8* pBase = (CastTarget3c609f8*)spModel.p->Cast(0x3c609f8);
    if (pBase) {
        if (size != -1)
            pBase->mField18 = size;
        nameKey.type = 0x1a99b06b;
    }
    MarkResourceDirty(spModel.p);
    GetManager()->WriteResource(spModel.p, 0, pSave, 0, &nameKey);

    // Clone the .pollen_metadata record next to the model.
    Key metaKey = key;
    metaKey.type = 0x30bdee3;
    bool bMetaOK = false;
    Ref<ResObj> spMeta;
    mgr = GetManager();
    spMeta.Reset();
    if (mgr->GetResource(metaKey, &spMeta, 0, 0, 0, 0)) {
        cAssetMetadata* pOld = spMeta.p ? (cAssetMetadata*)spMeta.p->Cast(0x30bdee3) : 0;
        Ref<cAssetMetadata> spNew(new ("Pollinator", 0, 0, 0, 0) cAssetMetadata());
        String16 tags;
        tags.mpBegin = gEmptyString16; tags.mpEnd = gEmptyString16; tags.mpCapacity = gEmptyString16 + 1;
        pOld->GetTagsString(&tags);
        Key parentKey;
        if (bKeepParent) { parentKey = key; } else { parentKey.instance = 0; parentKey.type = 0; parentKey.group = 0; }
        spNew.p->Set(newKey, pOld->GetName(), pOld->GetDescription(), tags.mpBegin, parentKey, false);
        MarkResourceDirty(spNew.p);
        bMetaOK = GetManager()->WriteResource(spNew.p, 0, pSave, 0, 0);
        tags.DeallocateSelf();
    }

    // Copy the .png thumbnails (png type 0x2f7d0004) to the new key.
    Key pngKey = key; pngKey.type = 0x2f7d0004;
    Database* pPngDb = GetManager()->FindDatabase(pngKey);
    Key pngNew = newKey; pngNew.type = 0x2f7d0004;
    bool bThumb = false;
    if (!pPngDb || !pSave)
        return false;

    {
    ImgPtr img(GetThumbService()->LoadImage(pngKey, 2));
    void* pixels = img.p->GetPixels();
    if (img.p && pixels) {
        bool bFlag = !SetAssetData(key.type, false);
        bThumb = GetImportExport()->CreateExportThumb(spModel.p, pixels, pSave, 0, bFlag);
    }
    img = 0;
    if (bThumb) {
        int count = 1;
        if (key.type == 0x366a930d) count = 4;
        for (int i = 0; i < count; ++i) {
            RecordInfo info;
            pngKey.group = (pngKey.group & 0xffffff00) | ((i + 1) & 0xff);
            pngNew.group = (pngNew.group & 0xffffff00) | ((i + 1) & 0xff);
            bool opened = pPngDb->OpenRecord(pngKey, 0, 1, 6, false, &info);
            if (!opened) {
                if (i != 0) continue;
                pngKey.group &= 0xffffff00;
                if (!pPngDb->OpenRecord(pngKey, 0, 1, 6, false, &info)) continue;
            }
            if (info.compressedSize == (uint32_t)-1) continue;
            void* buf = g_pSPMemPool->LockedAlloc(info.compressedSize, 0, 0, 0, 0, 0);
            uint32_t n = ReadRecordData(pPngDb, &pngKey, buf, info.compressedSize, 1, 0);
            if (n == info.compressedSize)
                bThumb = WriteRecordData(pSave, &pngNew, buf, n, 1);
            if (buf)
                g_pSPMemPool->Free(buf);
        }
    }
    }
    if (!bThumb || !bMetaOK)
        return false;

    if (newKey.type == 0x2b978c46 && GetModelCategory(&key) == 1) {
        SummarizePart(&key, &newKey, 0xa426730b);
        SummarizePart(&key, &newKey, 0xad56080c);
        SummarizePart(&key, &newKey, 0xf71fa311);
        SummarizePart(&key, &newKey, 0xbeb528cb);
        SummarizePart(&key, &newKey, 0x2db6dad3);
    }
    if (SetAssetData(newKey.type, false))
        GetChangeNotifier()->OnAssetCloned(&key, &newKey);
    GetMessageServer()->PostMessage(0xca665fa7, &newKey, 0);
    *pOutKey = newKey;
    return true;
}

// @ 0x00646ae0
void __fastcall sub_646ae0(void*)
{
}

// @ 0x00646d10
void MapFindSelf::Find(OutPair* out, const OutPair* key)
{
    Elem20* const last = mEnd;
    Elem20* p = lower_bound20(mBegin, last, key, mFlag14);
    if (p != last) {
        const uint32_t* k = (const uint32_t*)key;
        bool less;
        if (k[0] != p->f00)
            less = k[0] < p->f00;
        else if (k[2] != p->f08)
            less = k[2] < p->f08;
        else
            less = k[1] < p->f04;
        if (!less) {
            out->first = p;
            out->second = p + 1;
            return;
        }
    }
    out->first = p;
    out->second = p;
}

// @ 0x00646d70
void __stdcall sub_646d70(uint8_t* first, uint8_t* last)
{
    for (; first < last; first += 0x34) {
        FreeChecked(*(void**)(first + 0x20));
        FreeChecked(*(void**)(first + 8));
    }
}

// @ 0x00646dc0
bool Owner::Insert118(uint32_t a, uint32_t b)
{
    Key8 key; key.first = a; key.second = b;
    InsertResult r = m118.find_insert(key, EmptyTag());
    return r.inserted;
}

// @ 0x00646e00
bool Owner::Insert0F8(uint32_t a, uint32_t b)
{
    Key8 key; key.first = a; key.second = b;
    InsertResult r = m0F8.find_insert(key, EmptyTag());
    return r.inserted;
}

// @ 0x00646e40
bool Owner::Insert138(uint32_t a, IRef* b)
{
    if (b) b->AddRef();
    RefPair key; key.first = a; key.second = b;
    if (b) b->AddRef();
    InsertResult r = m138.insert(key, EmptyTag());
    if (key.second) key.second->Release();
    if (b) b->Release();
    return r.inserted;
}

// @ 0x00646ec0
bool Owner::Insert15C(uint32_t a, IRef* b)
{
    if (b) b->AddRef();
    RefPair key; key.first = a; key.second = b;
    if (b) b->AddRef();
    InsertResult r = m15C.insert(key, EmptyTag());
    if (key.second) key.second->Release();
    if (b) b->Release();
    return r.inserted;
}

// @ 0x00646f40
uint32_t* MapFindInsert::FindOrInsert(uint32_t* key)
{
    InsertResult r;
    find(&r, key);
    if ((uint32_t*)r.node != ((uint32_t**)mpBuckets)[mBucketCount])
        return (uint32_t*)r.node + 1;
    uint32_t keyCopy = *key;
    insert(&r, &keyCopy, EmptyTag());
    return (uint32_t*)r.node + 1;
}

// @ 0x00646fc0
void Vec14::reserve(uint32_t n)
{
    if (n > (uint32_t)((mpCapacity - mpBegin) / 0x14)) {
        uint8_t* pNewData;
        if (n)
            pNewData = (uint8_t*)eastl_alloc(n * 0x14, "Editor", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        else
            pNewData = 0;
        uint8_t* const pOldEnd = mpEnd;
        uint8_t* const pOldBegin = mpBegin;
        uninit_copy14(pOldBegin, pOldEnd, pNewData);
        uninit_destroy14(pOldBegin, pOldEnd, pNewData);
        if (mpBegin)
            eastl_dealloc(mpBegin);
        const uint32_t nPrevSize = (uint32_t)((mpEnd - mpBegin) / 0x14);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize * 0x14;
        mpCapacity = pNewData + n * 0x14;
    }
}

// @ 0x006470b0
void __thiscall cSPUIAssetBrowser_s0064_70b0::CreateLargeAssetViews()
{
    unsigned int key;
    LargeAssetView* volatile view;
    LargeAssetView* v;
    cISPLargeAssetView* p;
    void* mem = operator new(0xd0, g_allocTag, 0, 0, 0, 0);
    if (mem == 0) {
        view = 0;
    } else {
        v = ((LargeAssetView*)mem)->Construct(1);
        view = v;
        if (v) {
            ((IRefCounted*)v)->AddRef();
            p = static_cast<cISPLargeAssetView*>(v);
            goto have_p;
        }
    }
    p = 0;
have_p:
    ASSIGN(0xdfad9f51);
    NEXT_P();
    ASSIGN(0x9ea3031a);
    NEXT_P();
    ASSIGN(0x372e2c04);
    NEXT_P();
    ASSIGN(0xccc35c46);
    NEXT_P();
    ASSIGN(0x65672ade);
    NEXT_P();
    ASSIGN(0x99e92f05);
    NEXT_P();
    ASSIGN(0x4e3f7777);
    NEXT_P();
    ASSIGN(0xbdd15f3d);
    NEXT_P();
    ASSIGN(0x47c10953);
    NEXT_P();
    ASSIGN(0x72c49181);
    NEXT_P();
    ASSIGN(0x7d433fad);
    NEXT_P();
    ASSIGN(0xf670aa43);
    NEXT_P();
    ASSIGN(0x9ad7d4aa);
    NEXT_P();
    ASSIGN(0xbc1041e6);
    NEXT_P();
    ASSIGN(0xc0b74287);
    NEXT_P();
    ASSIGN(0x8f963dcb);
    NEXT_P();
    ASSIGN(0x2a5147a9);
    NEXT_P();
    ASSIGN(0x1f2a25b6);
    NEXT_P();
    ASSIGN(0xc15695da);
    NEXT_P();
    ASSIGN(0x441cd3e6);
    NEXT_P();
    ASSIGN(0x1a4e0708);
    NEXT_P();
    ASSIGN(0x449c040f);
    NEXT_P();
    ASSIGN(0x2090a11b);
    NEXT_P();
    ASSIGN(0x98e03c0d);
    NEXT_P();
    ASSIGN(0xbcd73e89);
    NEXT_P();
    ASSIGN(0xb8669ec9);
    NEXT_P();
    ASSIGN(0x37148141);
    NEXT_P();
    ASSIGN(0xffffffff);
    { LargeAssetView* t = view; if (t) ((IRefCounted*)t)->Release(); }
}

// @ 0x006478c0
void __thiscall cSPUIAssetBrowser_s0064_70b0::SetLargeCardVisibililty(bool visible, const float* rect, bool immediate)
{
    cSPUIAnimator_s0064_70b0* anim = AssetBrowser_s0064_70b0() ? AssetBrowser_s0064_70b0()->mAnimator : 0;
    if (mWinLargeCard == 0) return;
    if (anim) {
        anim->RemoveAnimation(mWinLargeCard, -1);
        anim->RemoveAnimation(mWinLargeCardInputBlocker, -1);
    }
    if (visible) {
        if (mWinLargeCardInputBlocker) mWinLargeCardInputBlocker->SetFlag(1, visible);
        if (anim) {
            if (rect) {
                const float* area = mWinLargeCard->GetArea();
                float ch = area[3] - area[1];
                float sy = (rect[3] - rect[1]) / ch;
                float cw = area[2] - area[0];
                float sx = (rect[2] - rect[0]) / cw;
                SetScale(mWinLargeCard, sx, sy);
                const float* pt;
                float tmp[2];
                float centre[2];
                IWindowS* parent = mWinLargeCard->GetParent();
                if (parent) {
                    pt = mWinLargeCard->GetParent()->ToLocal(tmp, (rect[2] + rect[0]) * 0.5f, (rect[3] + rect[1]) * 0.5f);
                } else {
                    centre[0] = (rect[2] + rect[0]) * 0.5f;
                    centre[1] = (rect[3] + rect[1]) * 0.5f;
                    pt = centre;
                }
                float px = pt[0] - cw * 0.5f;
                float py = pt[1] - ch * 0.5f;
                mWinLargeCard->SetLocation(px, py);
                AnimTarget t;
                float d = GetElapsedSeconds(0.3f, 0);
                anim->AddAnimation(CreatePositionTarget(&t, mWinLargeCard, 0.0f, 0.0f, d), mWinLargeCard, 1);
            }
        }
        if (anim) {
            mWinLargeCard->SetLocation(0.0f, 0.0f);
            { AnimTarget t; float d = GetElapsedSeconds(0.3f, 0);
              anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCard, 0xff, d), mWinLargeCard, 2); }
            { AnimTarget t; float d = GetElapsedSeconds(0.3f, 0);
              anim->AddAnimation(CreateScaleTarget(&t, mWinLargeCard, 1.0f, d), mWinLargeCard, 0); }
            SetWindowAlpha(mWinLargeCardInputBlocker, 0.0f);
            { AnimTarget t; float d = GetElapsedSeconds(0.15f, 0) + 0.3f;
              anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCardInputBlocker, 0xff, d), mWinLargeCardInputBlocker, 2); }
        }
        IAssetViewS* cur = GetSelectedAsset();
        unsigned id = cur->GetID();
        cISPLargeAssetView*& slot = mLargeAssetViews[id];
        cISPLargeAssetView* old = mCurrentLargeAssetView.p;
        cISPLargeAssetView* nu = slot;
        if (nu != old) {
            if (nu) nu->AddRef();
            mCurrentLargeAssetView.p = nu;
            if (old) old->Release();
        }
        if (mCurrentLargeAssetView.p == 0) {
            unsigned defKey = 0xffffffff;
            mCurrentLargeAssetView.Assign(&mLargeAssetViews[defKey]);
        }
        bool flag = false;
        if (mFlag24) flag = cur->IsReady() ? true : false;
        mCurrentLargeAssetView.p->Show((int)mpMsgServerHandle, (int)cur, mCallerID, flag, mFlag23d);
        IAudioSystem* audio = GetSystemAT();
        KillSetiEffects(0x6c329b06, audio ? audio->GetSetiHandle() : 0);
        MessageServer()->PostMessage(0x5c81b19, 0, 0);
        return;
    }
    if (anim && !immediate) {
        { AnimTarget t; float d = GetElapsedSeconds(0.1f, 0);
          anim->AddAnimation(CreateScaleTarget(&t, mWinLargeCard, 0.001f, d), mWinLargeCard, 0); }
        { AnimTarget t; float d = GetElapsedSeconds(0.1f, 0);
          anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCard, 0, d), mWinLargeCard, 2); }
        { AnimTarget t; float d = GetElapsedSeconds(0.1f, 0);
          anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCardInputBlocker, 0, d), mWinLargeCardInputBlocker, 2); }
        mLargeCardHideTime = 0.1f;
    } else {
        if (mWinLargeCardInputBlocker) mWinLargeCardInputBlocker->SetFlag(1, 0);
    }
    if (mCurrentLargeAssetView.p == 0) return;
    mCurrentLargeAssetView.p->Hide();
    cISPLargeAssetView* v = mCurrentLargeAssetView.p;
    if (v) {
        mCurrentLargeAssetView.p = 0;
        v->Release();
    }
    MessageServer()->PostMessage(0x5c81b25, 0, 0);
}

// @ 0x00647f40
void cSPUIAssetGrid::Dtor()
{
    AT(void*, 0) = (void*)0x13ff844;
    AT(void*, 4) = (void*)0x13ff838;
    AT(void*, 8) = (void*)0x13ff81c;
    AT(void*, 0xc) = (void*)0x13ff80c;
    for (;;) {
        void* p;
        p = AT(void*, 0x228); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x224); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x220); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x21c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x218); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x1bc); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x1b4); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x1b0); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x194); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        if (AT(void*, 0x180)) {
            EA_RemoveHandler(AT(void*, 0x180), AT(void*, 0x184), AT(void*, 0x188),
                             AT(void*, 0x18c), AT(void*, 0x190));
            AT(void*, 0x180) = 0;
        }
        p = AT(void*, 0x17c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        break;
    }
    DoFreeNodes34(AT(void*, 0x160), AT(unsigned int, 0x164));
    AT(unsigned int, 0x168) = 0;
    if (AT(unsigned int, 0x164) > 1)
        operator_delete(AT(void*, 0x160));
    if (AT(void*, 0x158)) ((Fn_v0)VSLOT(AT(void*, 0x158), 4))(AT(void*, 0x158));
    DoFreeNodes34(AT(void*, 0x13c), AT(unsigned int, 0x140));
    AT(unsigned int, 0x144) = 0;
    if (AT(unsigned int, 0x140) > 1)
        operator_delete(AT(void*, 0x13c));
    DoFreeBucketsVoidP(AT(void*, 0x11c), AT(unsigned int, 0x120));
    AT(unsigned int, 0x124) = 0;
    if (AT(unsigned int, 0x120) > 1)
        operator_delete(AT(void*, 0x11c));
    DoFreeBucketsVoidP(AT(void*, 0xfc), AT(unsigned int, 0x100));
    AT(unsigned int, 0x104) = 0;
    if (AT(unsigned int, 0x100) > 1)
        operator_delete(AT(void*, 0xfc));
    if (AT(void*, 0xe4) && *(uint32_t*)((char*)AT(void*, 0xe4) - 4))
        operator_delete(AT(void*, 0xe4));
    reinterpret_cast<GridOps*>(this)->DestroyRange(AT(Entry14*, 0xcc), AT(Entry14*, 0xd0));
    if (AT(void*, 0xcc))
        operator_delete(AT(void*, 0xcc));
    for (;;) {
        void* p;
        p = AT(void*, 0xc8); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xc4); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0xc0); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xbc); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xb8); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xb4); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xb0); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xac); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xa8); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xa4); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0xa0); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x9c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x98); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x94); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x90); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x8c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x88); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x84); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x80); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x7c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x78); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x74); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x70); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x6c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x68); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x64); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x60); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x5c); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        p = AT(void*, 0x58); if (p) { ((Fn_v0)VSLOT(p, 8))(p); }
        p = AT(void*, 0x18); if (p) { ((Fn_v0)VSLOT(p, 4))(p); }
        break;
    }
    AT(void*, 0xc) = (void*)0x13ec458;
    AT(void*, 8) = (void*)0x13eb938;
    AT(void*, 0) = (void*)0x13eb394;
}

// @ 0x00648c60
Entry14* GridVec::InsertSorted(Entry14* pos, const Entry14& v)
{
    Entry14* const end = mpEnd;
    bool less = false;
    if (pos != end)
        less = EntryLess(v, *pos);
    Entry14* where = less
        ? f646030(mpBegin, pos, (const Key12*)&v, mField14)
        : f646030(pos, end, (const Key12*)&v, mField14);
    if (where != end) {
        if (!EntryLess(v, *where))
            return where;
    }
    return Insert(where, v);
}

// @ 0x00648ce0
Entry14* GridVec::FindOrInsert(const Key12& k)
{
    Entry14* const end = mpEnd;
    Entry14* p = f646030(mpBegin, end, &k, mField14);
    if (p != end) {
        bool less;
        if (k.a == p->f00) {
            if (k.c == p->f08)
                less = k.b < p->f04;
            else
                less = k.c < p->f08;
        } else {
            less = k.a < p->f00;
        }
        if (!less)
            return (Entry14*)((char*)p + 0xc);
    }
    Entry14 value;
    value.f00 = k.a;
    value.f04 = k.b;
    value.f08 = k.c;
    value.h0c.p = 0;
    value.h10.p = 0;
    Entry14* r = InsertSorted(p, value);
    return (Entry14*)((char*)r + 0xc);
}

// @ 0x00648d90
void cSPUIAssetBrowserR::FilterGridEntries(FilterMsg* msg)
{
  cSPUIAssetBrowserR* self = this;
  uint8_t  b41 = 0;   // msg->b10
  uint8_t  b42 = 0;   // msg->b18
  uint8_t  b43 = 0;   // msg->b19
  IViewRef* p34 = 0;  // msg->mpView
  uint32_t n30 = 0;   // msg->n14

  if (msg != 0) {
    b41 = msg->b10;
    p34 = msg->mpView;
    n30 = (uint32_t)msg->n14;
    b42 = msg->b18;
    b43 = msg->b19;
  }

  if (msg == 0 || b42 == 0) {
    // clear the ban list
    for (int i = 0; i < self->mBan.size(); i++) {
      if (self->mBan.mpBegin[i].mpView != 0)
        self->mBan.mpBegin[i].mpView->SetFirstUpdate(0);
    }
    Elem_s0064_8d90* b = self->mBan.mpBegin;
    Elem_s0064_8d90* e = self->mBan.mpEnd;
    Elem_s0064_8d90* d = ListCopy(e, e, b);
    ListDestroy(d, self->mBan.mpEnd);
    self->mBan.mpEnd = self->mBan.mpEnd - (int)((e - b) / 0x14);
  }

  if (p34 != 0 && ((ViewBody*)p34)->mp90 != 0) {
    ViewBody* v = (ViewBody*)p34;
    Key3_s0064_8d90 key;
    int  idx = -1;
    int  lim = -1;

    Key3_s0064_8d90* kp = v->mp90->GetKey();
    key.a = kp->a; key.b = kp->b; key.c = kp->c;

    if (self->mpGrid != 0)
      idx = self->mpGrid->IndexOfView(p34);

    if (b43 != 0 && self->mpGrid != 0 && idx >= 0) {
      int lo = self->mpGrid->FindFirstVisibleEntry();
      int hi = self->mpGrid->FindLastVisibleEntry();
      if (lo >= 0 && hi >= 0) {
        lim = (hi <= idx) ? hi : lo;
        if (lim >= 0) {
          int d = lim - idx;
          int sgn = d >> 31;
          Vec14Reserve(&self->mBan, (uint32_t)((d ^ sgn) - sgn) + (uint32_t)self->mBan.size());
        }
      }
    }

    do {
      if (self->mpGrid != 0 && idx >= 0) {
        Elem_s0064_8d90* hit = self->mpGrid->GetEntry(idx);
        if (hit != 0) {
          key.a = hit->key0;
          key.b = hit->key1;
          key.c = hit->key2;
          p34 = hit->mpView;
        }
      }
      if (key.a != 0 || key.b != 0 || key.c != 0) {
        Elem_s0064_8d90* b = self->mBan.mpBegin;
        Elem_s0064_8d90* e = self->mBan.mpEnd;
        Elem_s0064_8d90* inserted = ListInsertPos(b, e, (uint32_t*)&key, (uint8_t)self->mpPreloadRef);
        Elem_s0064_8d90* where = e;
        if (inserted != e) {
          bool before = key.a < inserted->key0;
          if (key.a == inserted->key0) {
            before = key.c < inserted->key2;
            if (key.c == inserted->key2)
              before = key.b < inserted->key1;
          }
          if (!before && (Elem_s0064_8d90*)((char*)inserted + 0x14) != inserted)
            where = inserted;
        }
        if (where == self->mBan.mpEnd) {
          p34->SetFirstUpdate(1);
          {
            IViewRef* held = p34;
            if (held != 0)
              held->AddRef();
            {
              ViewSub* sub = v->mp90;
              if (sub != 0)
                sub->AddRef();
              Elem_s0064_8d90 tmpKey;
              tmpKey.key0 = key.a;
              tmpKey.key1 = key.b;
              tmpKey.key2 = key.c;
              tmpKey.mpView = held;
              tmpKey.mpObj = 0;
              Elem_s0064_8d90* node = GridVecInsert(self->mBan.mpBegin, self->mBan.mpEnd, (uint32_t*)&tmpKey);
              ElemInit(node);
              if (sub != 0)
                sub->Release();
            }
            if (held != 0)
              held->Release();
          }
        } else if (b42 != 0 && b43 == 0) {
          p34->SetFirstUpdate(0);
          GridVecErase(&self->mBan, where);
          p34 = 0;
        }
      }
      if (idx >= 0 && lim >= 0) {
        if (idx < lim) idx++;
        else if (lim < idx) idx--;
      }
    } while (b42 != 0 && b43 != 0 && lim >= 0 && idx != lim);
  }

  {
    // move the built vector into a temp, refill from keys.
    Vec14_s0064_8d90 tmp;
    tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0;
    Vec14SwapInto(&tmp, &self->mBan);
    Elem_s0064_8d90* oldB = self->mBan.mpBegin;
    Elem_s0064_8d90* oldE = self->mBan.mpEnd;
    self->mBan.mpBegin = tmp.mpBegin;
    self->mBan.mpEnd = tmp.mpEnd;
    self->mBan.mpCapacity = tmp.mpCapacity;
    ListDestroy(oldB, oldE);
    if (oldB != 0)
      FreeBlock(oldB);

    if (self->mpCallerData != 0) {
      Vec14_s0064_8d90 keys;
      keys.mpBegin = 0; keys.mpEnd = 0; keys.mpCapacity = 0;
      Vec14Make(&keys, (uint32_t)self->mBan.size());
      for (int i = 0; i < self->mBan.size(); i++) {
        uint32_t val = 0;
        if (keys.mpEnd < keys.mpCapacity) {
          *(uint32_t*)keys.mpEnd = val;
          keys.mpEnd = (Elem_s0064_8d90*)((char*)keys.mpEnd + 4);
        } else {
          SpVecGrow(&val, (uint32_t**)&keys.mpEnd);
        }
      }
      if (keys.mpBegin == keys.mpEnd) {
        BlobInit((uint32_t*)&tmp);
        BlobOneArg(0, (uint32_t*)&tmp, 0);
      } else {
        BlobInit((uint32_t*)&tmp);
        BlobTwoArg(1, (uint32_t*)&tmp, (uint32_t*)&keys);
      }
      if (keys.mpBegin != 0 && ((uint32_t*)keys.mpBegin)[-1] != 0)
        FreeBlock(keys.mpBegin);
    }
  }

  {
    uint32_t u1 = 0;
    uint32_t u12 = 0;
    ViewBody* v = (ViewBody*)p34;
    bool vis = false;
    if (b41 != 0 && p34 != 0 && v->mp90 != 0) {
      uint32_t typeId = v->mp90->GetTypeID();
      uint32_t* slot = self->mHandlers.FindOrInsert(&typeId);
      if (*slot != 0) {
        if (n30 != 0) {
          u12 = 1;
        } else if (self->b2a != 0 && v->mp28 != 0) {
          n30 = (uint32_t)(size_t)MakeKey4(&typeId, (uint32_t*)v->mp28, 0);
          u12 = 1;
        } else {
          n30 = 0;
          u12 = 1;
        }
        vis = true;
      }
    }
    if (!vis) {
      u1 = 0;
      n30 = 0;
      u12 = 0;
    }
    self->SetLargeCardVisibility((int)u12, &n30, (int)u1);
  }

  if (self->mpGrid != 0)
    self->mpGrid->UpdateStatsText();
}

// @ 0x00649f60
void __fastcall sub_649f60(void*)
{}

// @ 0x0064a220
void __fastcall sub_64a220(void*)
{}

// @ 0x0064a400
void __fastcall sub_64a400(void*)
{}

// @ 0x0064a990
void __fastcall sub_64a990(void*)
{}

// @ 0x0064ab20
void cSPUIAssetBrowser_s0064_9f60::Update()
{
    if (!mIsVisible)
        return;
    if (!mField25)
        return;
    if (!mField29 && SporeGuide()->mField1C)
        return;
    void* const p = mpFieldBC;
    if (p && (mField234 || mField1C8) && p)
        return;

    bool v = false;
    if (mField29) {
        if (AssetBrowser()->mField1C)
            v = true;
    }
    SetVisibility(0, 1, v);
    UpdateMouseFocus(1);
}

// @ 0x0064aba0
void __fastcall sub_64aba0(void*)
{}

// @ 0x0064acd0
void cSPUIAssetBrowser_s0064_acd0::LaunchEditorEnd()
{
    if (b24c) {
        b24c = 0;
        b234 = 0;
        if (p80 && p5c) {
            p80->Fade(1, b1c);
            p80->Fade(0x40, 0);
            if (p64)
                p5c->SetFocusChild(p64);
            b1f = 0;
        }
        FUN_0064c280();
        return;
    }
    Key_s0064_acd0 k = { 0, 0, 0 };
    if (banBegin != banEnd && (banEnd - banBegin) == 1 && banBegin->obj != 0) {
        IBanObj* o = FUN_00645300();
        Key_s0064_acd0* kp = o->GetKey();
        k = *kp;
    }
    void* endNode = handlers.buckets[handlers.nBuckets];
    if (handlers.find(k.b).node != endNode) {
        IHandlerObj* h = handlers[k.b];
        if (h->TryHandle(&k, 1)) {
            SetVisibility(0, 0, 0);
            b234 = 0;
            FUN_00644e20(0);
            return;
        }
    }
    bool f15 = false;
    if (b1c4 && f1b8 != 0x2ccd1d2)
        f15 = true;
    WString tmpStr;
    tmpStr.mpBegin = gEmptyWString;
    tmpStr.mpEnd = gEmptyWString;
    tmpStr.mpCapacity = gEmptyWString + 1;
    Key4 key4;
    uint8_t t18, t10, t12, t11, t14, t13, t16;
    LaunchData* src = src1b4;
    if (src) {
        key4 = src->k24;
        t18 = src->b34; t10 = src->b36; t12 = src->b38; t11 = src->b37;
        t14 = src->b3a; t13 = src->b3d; t16 = src->b6f;
        if (&src->str50 != &tmpStr)
            tmpStr.assign(src->str50.mpBegin, src->str50.mpEnd);
    } else {
        LaunchData* out = 0;
        GetEditorSettings(b1c4, &out);
        key4 = out->k24;
        t18 = out->b34; t10 = out->b36; t12 = out->b38; t11 = out->b37;
        t14 = out->b3a; t13 = out->b3d; t16 = out->b6f;
        out->Release();
    }
    LaunchDataRef cell;
    cell.p = 0;
    LaunchData* esi = 0;
    bool b17 = false;
    uint32_t ebx;
    if (b235) {
        ebx = GetAssetBrowser()->FUN_00645cc0();
        b17 = true;
        if (f1b0.p) {
            cell.CopyFrom(&f1b0);
            esi = cell.p;
        }
        b235 = 0;
        k.a = 0; k.b = 0; k.c = 0;
        if (esi)
            goto finish;
        goto std_launch;
    }
    if (b23c) {
        ebx = f238;
        b23c = 0;
        goto std_launch;
    }
    ebx = f1c0;
    if (ebx == 0) {
        ebx = GetAssetBrowser()->FUN_00645cc0();
        if (ebx == 0)
            ebx = (uint32_t)-1;
    }
    if (g15fd918->sub->f118 == 0 || f1b8 != 0x51b22b0)
        goto std_launch;
    {
        // "Casual" editor launch
        uint32_t c0 = g15da784, c1 = g15da788, c2 = g15da78c, c3 = g15da790;
        LaunchData* p = new("Casual", 0, 0, 0, 0) LaunchData();
        cell.Assign(p);
        LaunchData* e = cell.p;
        e->f1c = 0x418a508;
        e->k10 = k;
        e->f0c = 0x5bf8f774;
        e->f90 = 0x517560a;
        if (e->f94.p) {
            IRef_s0064_acd0* t = e->f94.p;
            e->f94.p = 0;
            t->Release();
        }
        e->k24.a = c0; e->k24.b = c1; e->k24.c = c2; e->k24.d = c3;
        e->b34 = t18; e->b36 = t10; e->b37 = t11; e->b38 = t12; e->b3d = t13;
        e->b3c = 0;
        e->b64 = 1;
        e->b6d = 0;
        e->b6e = 0;
        Key4 kv;
        kv.a = c0; kv.b = c1; kv.c = c2; kv.d = c3;
        EditorLaunchEx(0x5bf8f774, &k, 0x517560a, f1bc, kv, t18 != 0);
        GetMessageServer_s0064_acd0()->Post4(0xb03bc30c, e, 0, 0);
        if (GetApp()->GetMode() == 0xdbdba1)
            GetMessageServer_s0064_acd0()->Post4(0x51cc0b8, 0, 0, 0);
        SetVisibility(0, 0, 0);
        b234 = 0;
        FUN_00644e20(0);
        e->Release();
        tmpStr.DeallocateSelf();
        return;
    }
std_launch:
    {
        LaunchData* p = new("Editor", 0, 0, 0, 0) LaunchData();
        if (p) {
            p->AddRef();
            esi = p;
        }
        esi->k10 = k;
        esi->f0c = ebx;
        esi->f90 = 0x13c5a95e;
        esi->f94.CopyFrom(&f1bc);
        esi->k24 = key4;
        esi->b34 = t18; esi->b36 = t10; esi->b37 = t11; esi->b38 = t12;
        esi->b3a = t14; esi->b3d = t13;
        esi->b6d = b1c4; esi->b6e = f15; esi->b6f = t16;
        esi->b64 = 1;
        if (&tmpStr != &esi->str50)
            esi->str50.assign(tmpStr.mpBegin, tmpStr.mpEnd);
        if (b17 && GetAssetBrowser()->FUN_00645bf0()) {
            LaunchData* e2 = new("Editor", 0, 0, 0, 0) LaunchData();
            LaunchDataRef cell2;
            cell2.p = e2;
            if (e2)
                e2->AddRef();
            e2->f0c = GetAssetBrowser()->FUN_00645bf0();
            e2->f90 = 0x13c5a95e;
            e2->f94.CopyFrom(&f1bc);
            e2->k24 = key4;
            e2->b34 = t18; e2->b36 = t10; e2->b37 = t11; e2->b38 = t12;
            e2->b3a = t14; e2->b3d = t13;
            e2->b6d = b1c4; e2->b6e = f15; e2->b6f = t16;
            e2->b64 = 1;
            e2->b3c = 1;
            e2->b6c = 1;
            e2->str50 = tmpStr;
            esi->f98.CopyFrom(&cell2);
            esi->b34 = 0;
            e2->Release();
        }
    }
finish:
    if (f240) {
        LaunchData* c = esi->f98.p;
        if (c) {
            c->f84 = f240; c->f88 = f244; c->f8c = f248;
        } else {
            esi->f84 = f240; esi->f88 = f244; esi->f8c = f248;
        }
    }
    if (esi->f1c == 0x1654c10)
        esi->b39 = 0;
    EditorLaunch(esi);
    SetVisibility(0, 0, 0);
    b234 = 0;
    if (p80 && p5c) {
        p80->Fade(1, b1c);
        p80->Fade(0x40, 0);
        if (p64)
            p5c->SetFocusChild(p64);
        b1f = 0;
    }
    esi->Release();
    FreeStr(tmpStr);
}

// @ 0x0064b4b0
void cSPUIAssetBrowser_s0064_acd0::BanItem()
{
    if (banBegin == banEnd)
        return;
    IMessageServer* ms = GetMessageServer_s0064_acd0();
    uint32_t off = 0;
    for (unsigned i = 0; i < (unsigned)(banEnd - banBegin); i++, off += 0x14) {
        BanEntry* e = (BanEntry*)((char*)banBegin + off);
        IBanObj* obj = e->obj;
        if (obj) {
            Key_s0064_acd0 itemKey = e->key;
            Key_s0064_acd0* kp = obj->GetKey();
            Key_s0064_acd0 k2 = *kp;
            bool flag = false;
            if ((FUN_00552300(&k2) == 1 && obj->IsOfficial()) || f22c == 0)
                flag = true;
            GetObjectTemplateDB()->SetBanned(&k2, flag);
            if (b2a && grid) {
                BanMsg msg(p228, &itemKey, 0);
                ms->Post(0x3b60b3ad, &msg, 0);
                if (msg.p)
                    msg.p->Release();
            }
        }
    }
    FilterGridEntries(0);
    if (b2a) {
        ms->Post(0x53dd093, 0, 0);
        if (grid)
            grid->FilterEntries();
    } else {
        SetLargeCardVisibililty(0, 0, 0);
        Update();
    }
    bool changed = false;
    GetMessageServer_s0064_acd0()->Post(0x12a93f05, &changed, 0);
    if (changed) {
        Update();
        ms->Post(0x4715068, 0, 0);
    }
}

// @ 0x0064b6a0
void cSPUIAssetBrowser_s0064_acd0::ShowSporeGuide()
{
    LaunchSporeGuide(mField19C);
}

// @ 0x0064b6b0
void cSPUIAssetBrowser_s0064_acd0::HandleMessage(Msg* m)
{
    Key_s0064_acd0* key = &m->key;
    bool hasKey = key->a != 0;
    if (!b2a) {
        bool handled = false;
        if (hasKey && m->b30) {
            Key4 k4;
            k4.a = key->a; k4.b = key->b; k4.c = key->c;
            k4.d = 0;
            CardRef card;
            card.p = 0;
            CardFactory fn = 0;
            if (cfgId != 0)
                fn = ((ConfigTable*)cfgId)->GetFactory(m->key.b);
            Card* made;
            if (fn)
                made = fn();
            else
                made = new("Sporepedia", 0, 0, 0, 0) TimelineSporepediaCardData();
            card.Assign(made);
            Card* c = card.p;
            c->SetKey((Key_s0064_acd0*)&k4);
            CardWrapFn w = ((ConfigTable*)cfgId)->GetWrapper(c->GetTypeID());
            if (w) {
                card.Assign(w(c));
                c = card.p;
            }
            if (c->IsAssetCard()) {
                AssetHolder h;
                h.Set(&card);
                BanVector* v = (BanVector*)&banBegin;
                v->ClearAssetViews();
                v->Insert(key, &h)->Finish();
                SetLargeCardVisibililty(1, 0, 0);
                handled = true;
            }
            ((IRef_s0064_acd0*)c)->Release();
        }
        if (!handled)
            Update();
        IRef_s0064_acd0* t = p228;
        if (t) {
            p228 = 0;
            t->Release();
        }
        return;
    }

    if (f1a0 == 0 && f1a4 == 0) {
        f1a0 = m->f1c;
        uint32_t t20 = m->f20;
        f1a4 = t20;
        if (f1a0 == 0 && t20 == 0)
            f1a8 = 0;
        else
            f1a8 = m->f14;
    }
    b1ac = m->b18;
    f20 = m->f34;
    bool bl = false;
    {
        IProp* out;
        if (props && props->GetProperty(0xb4d1731e, &out) && out->type == 1)
            bl = *out->GetBool();
    }
    if (grid)
        grid->b1bb = bl;
    bool show;
    if (m->b32 && !b26 && !b27 && p228)
        show = false;
    else
        show = true;
    bool r12;
    if (!hasKey) {
        r12 = false;
        if (show)
            r12 = true;
    } else {
        r12 = true;
    }
    b1ed = 0;
    if (grid) {
        if (f1e4 != 0 && f1e8 != 0) {
            GridInner* e0 = grid->inner;
            if (e0) {
                AssetList t = { 0, 0, 0 };
                e0->FUN_00661380(&t);
                if (t.begin)
                    operator delete(t.begin);
                e0->FUN_00662750(f1e4, f1e8, !show);
            }
            if (show)
                grid->FUN_0064f310();
        } else if (show) {
            b1ed = 1;
            grid->FUN_0064f310();
        }
    }
    if (r12) {
        bool hide = true;
        IProp* o2;
        if (props && props->GetProperty(0x5aeeaa2, &o2) && o2->type == 1)
            hide = *o2->GetBool();
        feedList->SetHidden(hide);
        int count = 0;
        Key_s0064_acd0* arr = 0;
        GetPropertyKeyArray(props, 0x59c3490, &count, &arr);
        for (int i = 0; i < count; i++) {
            FeedCategory* c = feedList->FindCategory(arr[i].a);
            if (c)
                c->Expand(1);
        }
    }
    FeedMsg fm;
    bool post = true;
    if (show) {
        uint32_t v = m->f10;
        if (v) {
            fm.Init(v);
            fm.flagA = 1;
            fm.flagB = 1;
        } else if (GetPropertyAsKeyInstance(props, 0x3449565e, &v)) {
            fm.Init(v);
            fm.flagB = 1;
        } else {
            post = false;
        }
    } else if (p228) {
        fm.InitFromAsset(p228);
    } else {
        post = false;
    }
    if (post) {
        GetMessageServer_s0064_acd0()->Post(0xb3d53f95, &fm, 0);
        if (fm.p)
            fm.p->Release();
    }
    if (hasKey && grid) {
        if (!grid->Layout(key, m->b30, 1, m->f38)) {
            if (SetAssetData(m->key.b, 1)) {
                FeedMsg fm2;
                fm2.Init(0xe2415c7d);
                GetMessageServer_s0064_acd0()->Post(0xb3d53f95, &fm2, 0);
                grid->Layout(key, m->b30, 1, m->f38);
                if (fm2.p)
                    fm2.p->Release();
            }
        }
    }
    FeedItem* it = (FeedItem*)p228;
    if (it && it->id178 == 0x11f44f6b) {
        AssetList l = { 0, 0, 0 };
        it->GetAssetList(&l);
        if (l.begin == l.end) {
            FeedMsg fm3;
            fm3.Init(0xe2415c7d);
            GetMessageServer_s0064_acd0()->Post(0xb3d53f95, &fm3, 0);
            if (fm3.p)
                fm3.p->Release();
        }
        if (l.begin && ((uint32_t*)l.begin)[-1])
            operator delete(l.begin);
    }
    if (m->b31)
        feedList->FUN_00662ad0();
}

// @ 0x0064bc50
void __cdecl Launch(uint32_t a, uint32_t b, uint32_t c)
{
    LaunchParams p;
    p.f04 = 0;
    p.f08 = 0;
    p.f0c = 0;
    p.f10 = 0;
    p.f11 = 0;
    p.f12 = 0;
    p.f14 = 0;
    p.f18 = 0;
    p.f1c = 0;
    p.f20 = 0;
    p.f28 = 0;
    p.f2c = 0;
    p.f3c = 0;
    p.f40 = 0;
    p.f44 = 0;
    p.f00 = a;
    const uint32_t one = 1;
    p.f13 = (uint8_t)one;
    p.f24 = (uint8_t)one;
    p.f34 = one;
    p.f38 = b;
    p.f30 = c;
    AdvancedLaunch(&p);
}

// @ 0x0064bcd0
void cSPUIAssetBrowserModalHandler::OnModalWindowEnd(int unused, uint32_t messageId)
{
    (void)unused;
    switch (mModalState) {
    case 1: {
        mModalState = 0;
        void* audio = AudioSystem();
        uint32_t value = audio ? ((VCall_UInt)VTableOf(audio)[0x20 / 4])(audio) : 0;
        RecordEvent2(0xe76c9b4f, value);
        if (messageId == 0x5107b1a)
            BrowserOf(this)->BanItem();
        return;
    }
    case 2: {
        mModalState = 0;
        if (messageId != 0x5107b1a)
            return;
        cSPUIAssetBrowserLayout* base = BrowserOf(this);
        if (!base->Get_10())
            return;
        void* view = base->Get_10();
        AssetKey* src = ((VCall_Key)VTableOf(view)[0x40 / 4])(view);
        AssetKey key;
        key.mInstance = src->mInstance;
        key.mType = src->mType;
        key.mGroup = src->mGroup;
        base->Fn_e20(1);
        void* endNode = mMap.mpBuckets[mMap.mBucketCount];
        EaHashIter it = mMap.find(key.mType);
        if (it.mpNode == endNode) {
            void* value = *mMap.FindOrInsert(key.mType);
            if (((VCall_Bool_Key)VTableOf(value)[0xc / 4])(value, 0, &key))
                return;
        }
        FUN_00801360(FUN_0067cab0());
        StopwatchRestart(&mStopwatch);
        void* server = MessageServer_s0064_bc50();
        ((VCall_Msg)VTableOf(server)[0x14 / 4])(server, 0, 0x2ba2010, &key, 0);
        switch (key.mInstance) {
        case 0x4178b8e8: case 0x372e2c04: case 0x65672ade:
        case 0x9ea3031a: case 0xccc35c46: case 0xdfad9f51:
            AutoTestMessage(0x2e3fc8f2);
            break;
        case 0x72c49181: case 0x4e3f7777: case 0x47c10953:
        case 0xbdd15f3d: case 0x99e92f05:
            AutoTestMessage(0x71c5a637);
            break;
        case 0x2090a11b: case 0x1a4e0708: case 0x1f2a25b6:
        case 0x2a5147a9: case 0x441cd3e6: case 0x449c040f:
        case 0xbc1041e6: case 0x9ad7d4aa: case 0x98e03c0d:
        case 0x7d433fad: case 0x8f963dcb: case 0xc0b74287:
        case 0xc15695da: case 0xf670aa43:
            AutoTestMessage(0xadda228a);
            break;
        default:
            break;
        }
        return;
    }
    case 5: {
        mModalState = 0;
        if (messageId != 0x5107b1a || !mpFeed)
            return;
        LocaleString str;
        LocaleMsg2_s0064_bc50 msg;
        str.Init(((Feed*)mpFeed)->mpName, &messageId);
        msg.Ctor(0);
        void* server = MessageServer_s0064_bc50();
        ((VCall_Msg)VTableOf(server)[0x14 / 4])(server, 0, 0xb3d53f95, &msg, 0);
        GetPollinator()->UnsubscribeToFeed(str.mpBegin);
        msg.Dtor();
        str.Dtor();
        return;
    }
    case 6: {
        mModalState = 0;
        if (messageId != 0x5107b1a || !mpFeed)
            return;
        LocaleString str;
        LocaleMsg2_s0064_bc50 msg;
        str.Init(((Feed*)mpFeed)->mpName, &messageId);
        msg.Ctor(0);
        void* server = MessageServer_s0064_bc50();
        ((VCall_Msg)VTableOf(server)[0x14 / 4])(server, 0, 0xb3d53f95, &msg, 0);
        GetPollinator()->DeleteMyFeed(str.mpBegin);
        msg.Dtor();
        str.Dtor();
        return;
    }
    case 7:
        mModalState = 0;
        return;
    default:
        return;
    }
}

// @ 0x0064c0d0
void __fastcall sub_64c0d0(cSPUIAssetBrowserLayout* self)
{
    AssetKey key;
    key.mInstance = 0;
    key.mType = 0;
    key.mGroup = 0;
    if (self->mpEntriesBegin != self->mpEntriesEnd) {
        if (self->mpEntriesEnd - self->mpEntriesBegin == 1) {
            void* obj = self->mpEntriesBegin[0].mpObject;
            if (obj) {
                AssetKey* src = ((VCall_Key)VTableOf(obj)[0x40 / 4])(obj);
                key.mInstance = src->mInstance;
                key.mType = src->mType;
                key.mGroup = src->mGroup;
            }
        }
    }
    void* endNode = self->mMap.mpBuckets[self->mMap.mBucketCount];
    EaHashIter it = self->mMap.find(key.mType);
    if (it.mpNode != endNode) {
        void* value = *self->mMap.FindOrInsert(key.mType);
        if (((VCall_Bool_KeyInt)VTableOf(value)[8 / 4])(value, 0, &key, 0)) {
            self->SetVisibility(0, 0, 0);
            return;
        }
    }
    self->mField234 = 1;
    BrowserGlobals* browser = (BrowserGlobals*)AssetBrowser_s0064_bc50();
    if (browser->mpTarget && browser->mpPanel) {
        ((VCall_IntInt)VTableOf(browser->mpTarget)[0x7c / 4])(browser->mpTarget, 0, 1, 1);
        ((VCall_IntInt)VTableOf(browser->mpTarget)[0x7c / 4])(browser->mpTarget, 0, 0x40, 1);
        ((VCall_Ptr)VTableOf(browser->mpPanel)[0xe8 / 4])(browser->mpPanel, 0, browser->mpTarget);
        browser->mField1f = 1;
    }
    void* handle = self->mpSomething17c;
    if (handle) {
        ((VCall_Int)VTableOf(handle)[0xc / 4])(handle, 0, 0);
        handle = self->mpSomething17c;
        if (handle) {
            self->mpSomething17c = 0;
            ((VCall_UInt)VTableOf(handle)[4 / 4])(handle);
        }
    }
    void* item = ((MsgMgr*)MessageManager())->Find(0x4cf52822, 1);
    if (item) {
        ((VCall_UInt)VTableOf(item)[0])(item);
        ((VCall_UInt)VTableOf(item)[4 / 4])(item);
    } else {
        self->LaunchEditorEnd();
    }
}

// @ 0x0064c280
void __fastcall sub_64c280(cSPUIAssetBrowserLayout* self)
{
    if (self->mField1ac && self->mpSomethingC8 &&
        ((cSPUIAssetVerbs*)self->mpSomethingC8)->IsVerb(2))
        return sub_64c0d0(self);

    void* server = self->mpServer;
    if (!server && !self->mpHandler)
        return;
    if (self->mpEntriesBegin == self->mpEntriesEnd)
        return;

    void* handler = self->mpHandler;
    SpVector keyVec;
    keyVec.mpBegin = 0;
    keyVec.mpEnd = 0;
    keyVec.mpCap = 0;
    for (int i = 0; i < (int)(self->mpEntriesEnd - self->mpEntriesBegin); ++i) {
        void* obj = self->mpEntriesBegin[i].mpObject;
        if (!obj)
            continue;
        AssetKey* src = ((VCall_Key)VTableOf(obj)[0x40 / 4])(obj);
        if (src->mInstance == 0)
            continue;
        if (keyVec.mpEnd < keyVec.mpCap) {
            AssetKey* dst = keyVec.mpEnd;
            keyVec.mpEnd = dst + 1;
            if (dst) {
                dst->mInstance = src->mInstance;
                dst->mType = src->mType;
                dst->mGroup = src->mGroup;
            }
        } else {
            keyVec.DoInsertKey(keyVec.mpEnd, src);
        }
    }
    self->SetVisibility(0, 0, 0);
    if (server) {
        if (keyVec.mpBegin == keyVec.mpEnd) {
            AssetKey empty;
            empty.mInstance = 0;
            empty.mType = 0;
            empty.mGroup = 0;
            ((VCall_Ptr)VTableOf(server)[0])(server, 0, &empty);
        } else {
            ((VCall_Ptr)VTableOf(server)[0])(server, 0, keyVec.mpBegin);
        }
    }
    if (handler)
        ((VCall_Ptr)VTableOf(handler)[0])(handler, 0, &keyVec);
    if (keyVec.mpBegin) {
        uint32_t* header = (uint32_t*)keyVec.mpBegin;
        if (header[-1] != 0)
            OperatorDelete(keyVec.mpBegin);
    }
}

// @ 0x0064c8e0
bool cSPUIAssetBrowser_s0064_c8e0::HandleMessage(uint32_t messageID, void* pMessage)
{
    switch (messageID) {
    case 0x044edd9c:
        if (mIsVisible) {
            IRenderView* view = RenderView();
            if (view) {
                Viewport viewport;
                viewport.x = -1;
                viewport.y = -1;
                view->GetViewport(&viewport);
                cCaptureJob* job = CaptureJob();
                if (job)
                    job->Capture(&viewport);
            }
        }
        break;

    case 0x044db12e:
        if (pMessage && mbPublishAllowed && !mbPublishBlocked)
            ShowPublishDialog();
        break;

    case 0x0141a7b3:
        OnRefresh();
        break;

    case 0x0462c656:
        if (mbLaunchingEditor)
            LaunchEditorEnd();
        break;

    case 0x05132389:
        if (*(uint32_t*)pMessage && mpCurrentItem.get() && mIsVisible) {
            BrowserMessage msg(mpCurrentItem.get()->mItemID);
            MessageServer_s0064_c8e0()->MessageSend(0xb3d53f95, &msg, 0);
        }
        break;

    case 0x05a86fa1:
        if (mpCurrentItem.get())
            OnLayoutChanged();
        break;

    case 0x05b96086:
    case 0x05b98f52:
    case 0x05c5594a:
        mbPublishAllowed = false;
        break;

    case 0x05bd6378:
        mbPublishBlocked = true;
        break;

    case 0x05dd52c7:
        mbPublishBlocked = false;
        if (mbPublishAllowed)
            ShowPublishDialog();
        break;

    case 0x05de7b4a:
        if (!mIsVisible && mpFeedList)
            mPendingButton = 0;
        break;

    case 0x05e7cb29:
        if (mCallToAction)
            CameraManager()->SetMode(0x16, 2);
        break;

    case 0x06134914: {
        cSPUIFeedListItem* item = (cSPUIFeedListItem*)pMessage;
        if (item->mItemType == 0x11f44f6b) {
            HideLargeViewA();
            HideLargeViewB();
            if (mpSporeGuideView)
                mpSporeGuideView->SetVisible(true, false);
            SetLargeCardState(true, item->mFeedArg);
        }
        break;
    }

    case 0x06255f5e: {
        uint32_t id = *(uint32_t*)pMessage;
        if (id) {
            cSPUIFeedListItem* item = mpFeedList->FindItemByIndex(id);
            if (item && item->mItemType == 0x11f44f6b) {
                BrowserMessage msg(item);
                MessageServer_s0064_c8e0()->MessageSend(0xb3d53f95, &msg, 0);
                HideLargeViewA();
                if (mpSporeGuideView)
                    mpSporeGuideView->SetVisible(true, false);
                HideLargeViewB();
                SetLargeCardState(true, id);
            }
        }
        break;
    }

    case 0x0639cceb:
        if (pMessage && mpFeedEditor)
            mpFeedEditor->OnEvent(pMessage);
        break;

    case 0x062d7860:
        KillSetiEffects(0x2ddb6155, GetRecorderState());
        HideLargeViewB();
        break;

    case 0x06299932:
        if (pMessage) {
            uint32_t a = ((uint32_t*)pMessage)[0];
            uint32_t b = ((uint32_t*)pMessage)[1];
            if (mpSporeGuideView)
                mpSporeGuideView->SetVisible(true, false);
            ShowLargeCard(true, a, b);
        }
        break;

    case 0x066fcce4: {
        cSPUIFeedList* feedList = mpFeedList;
        cSPUIFeedListItem* item = feedList->FindItem(SPIDFromName("Feed_RecentDownloads"));
        if (item)
            item->SetSelected(true);
        break;
    }

    case 0x068cd252: {
        if (!mIsVisible)
            break;
        AssetPollinatedMessage* msg = (AssetPollinatedMessage*)pMessage;
        if (!msg)
            break;
        ResourceKey_s0064_c8e0 key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (GetSelectedAsset())
            key = *GetSelectedAsset()->GetKey();
        if (KeysEqual(&key, &msg->mKey) && mbAwaitingPollination) {
            ClosePollinationUI(0);
            if (mCardWindows[0] | mCardWindows[1]) {
                LayoutCollection()->Hide();
                mCardWindows[0] = 0;
                mCardWindows[1] = 0;
                mCardWindows[2] = 0;
                mCardWindows[3] = 0;
            }
            if (msg->mbSuccess) {
                if (GetCreatorType(&key)) {
                    if (mbIsForEditor) {
                        if (mpFeedList) {
                            BrowserMessage m(mpCurrentItem.get());
                            MessageServer_s0064_c8e0()->MessageSend(0xb3d53f95, &m, 0);
                        }
                    } else {
                        SetLargeCardVisibility(false, false, false);
                        SetLargeCardVisibility(true, false, false);
                    }
                }
            } else {
                CalloutMessageBox(this, &kPollinateFailedDialog);
            }
            if (key.instance && key.group) {
                IUpdatable* p = UpdateSaveAreas(&key);
                if (p)
                    p->Update();
            }
            mbAwaitingPollination = false;
            break;
        }
        if (!mbIsForEditor || !mpFeedList)
            break;
        cSPUIFeedListItem* item = mpCurrentItem.get();
        if (!item)
            break;
        cBrowserConfig* config = mpConfig;
        if (!config || !mpAssetGrid)
            break;
        if (item->mItemType == 0x11f44f6b) {
            if (config->mConfigs.find(key).mpNode == (void*)&config->mConfigs.mAnchor)
                break;
            SelectItemMessage m(item, &msg->mKey, 0);
            MessageServer_s0064_c8e0()->MessageSend(0x3b60b3ad, &m, 0);
            mpAssetGrid->ResetScroll();
            m.mbHasQueryFlags = true;
            MessageServer_s0064_c8e0()->MessageSend(0x3b60b3ad, &m, 0);
        } else if (item->mItemType == 0xe8104769) {
            BrowserMessage m(item);
            MessageServer_s0064_c8e0()->MessageSend(0xb3d53f95, &m, 0);
        }
        break;
    }

    case 0x148f5c9d:
        if (mpCurrentItem.get())
            OnTabChanged();
        break;

    case 0x14ac4938:
        KillSetiEffects(0x2ddb6155, GetRecorderState());
        SetLargeCardVisibility(false, false, false);
        if (mbIsForEditor) {
            if (mpAssetGrid && mpAssetGrid->mbIsEditorGrid && GetSelectedID() && GetSelectedAsset()) {
            ResourceKey_s0064_c8e0 key;
            key.instance = 0;
            key.type = 0;
            key.group = 0;
            ResourceKey_s0064_c8e0 entryKey;
            entryKey.instance = 0;
            entryKey.type = 0;
            entryKey.group = 0;
            key = *GetSelectedAsset()->GetKey();
            mpAssetGrid->GetEntryByID(GetSelectedID());
            FilterGridEntries(0);
            if (!mpAssetGrid->SelectAsset(&entryKey, false, true, false))
                mpAssetGrid->SelectAsset(&key, false, true, false);
            }
        } else {
            Update();
        }
        break;

    case 0x1dd7bda9: {
        DialogResultMessage* msg = (DialogResultMessage*)pMessage;
        if (!msg || !msg->mpDialog)
            break;
        bool accepted = msg->mResult == 1;
        if (msg->mpDialog->GetType() == 0x3ffd6b1) {
            if (accepted) {
            send_refresh:
                BrowserMessage m(0xe2415c7d);
                MessageServer_s0064_c8e0()->MessageSend(0xb3d53f95, &m, 0);
                MessageServer_s0064_c8e0()->MessageSend(0x53dd093, 0, 0);
                break;
            }
            CalloutMessageBox(this, &kConfirmDialogA);
        } else if (msg->mpDialog->GetType() == 0x3cf01e6) {
            if (accepted)
                goto send_refresh;
            CalloutMessageBox(this, &kConfirmDialogB);
        }
        break;
    }

    case 0x3b60b3ad: {
        SelectItemMessage* msg = (SelectItemMessage*)pMessage;
        cSPUIFeedListItem* item =
            (cSPUIFeedListItem*)(msg ? msg->mpItem : AutoRefCount<RefItem>()).get();
        if (msg && item && item == mpCurrentItem.get() && !mbLockSelection &&
            item->mItemType != 0x49daa92a && !item->mWebURL && !item->mSporeGuidePage &&
            mpConfig && mpAssetGrid) {
            if (msg->mbHasQueryFlags) {
                QueryKey q;
                q.key = msg->mKey;
                q.flags = 0;
                mpConfig->SetQuery(&q, 0);
            } else {
                mpConfig->SetQueryKey(&msg->mKey);
            }
            mpAssetGrid->ShowItem(mpConfig, item);
        }
        return false;
    }

    case 0x54495773: {
        EventMessage* msg = (EventMessage*)pMessage;
        if (mIsVisible && mpFeedList && msg && msg->mBrowserIndex == mBrowserIndex)
            HandleEvent(msg);
        break;
    }

    case 0x94174b89:
        if (pMessage)
            FilterGridEntries(pMessage);
        break;

    case 0xb3d53f95: {
        if (!mIsVisible || !mpFeedList)
            break;
        BrowserMessage* msg = (BrowserMessage*)pMessage;
        if (!msg)
            break;
        if (!mBrowserIndex && SporeGuide_s0064_c8e0()->mbVisible)
            break;
        bool webPageShown = IsWebPageShown();
        HideLargeViewA();
        HideLargeViewB();
        if (mpSporeGuideView)
            mpSporeGuideView->SetVisible(true, false);
        SetLargeCardState(false, 0);

        cSPUIFeedListItem* item = msg->mpItem;
        if (!item) {
            if (msg->mbByIndex)
                item = mpFeedList->FindItemByIndex(msg->mFeedItemID);
            else
                item = mpFeedList->FindItem(msg->mFeedItemID);
        }
        AssetList_s0064_c8e0 assets;
        if (item) {
            mCurrentWebURL = (uint32_t)item->mWebURL;
            if (item->mItemType == 0x49daa92a) {
                bool loggedIn = AuthManager_s0064_c8e0()->IsLoggedIn();
                if (mpAssetListData) {
                    IVisibleObject* view = mpAssetListData->FindView(0x561e0a8, true);
                    if (view)
                        view->SetVisible(true, loggedIn);
                }
                if (mpFeedEditor) {
                    if (!loggedIn) {
                        mpFeedEditor->SetEditActive(true);
                        mpFeedEditor->Refresh();
                    } else {
                        mpFeedEditor->SetEditActive(false);
                    }
                }
            } else if (item->mWebURL) {
                SetWebBrowserVisibility(true, item->mWebURL);
                goto update_grid;
            } else if (item->mSporeGuidePage) {
                if (mpSporeGuideView) {
                    mpSporeGuideView->SetVisible(true, true);
                    mpSporeGuide->LoadSporeGuidePage(item->mSporeGuidePage);
                }
            } else {
                if (mpAssetGrid) {
                    uint32_t feedID = mFeedOverride;
                    if (!feedID)
                        feedID = item->mFeedID;
                    uint32_t configID = mConfigOverride;
                    if (!configID)
                        configID = item->mConfigID;
                    bool reset = msg->mbForceReset || mbForceReset;
                    mbForceReset = false;
                    IDSet ids;
                    if (feedID != item->mFeedID) {
                        FeedEntryVector entries;
                        GetFeedEntries(item->mFeedID, &entries);
                        ids.reserve(entries.size());
                        for (uint32_t i = 0; i < entries.size(); ++i) {
                            if (entries.mpBegin[i].mID)
                                ids.insert(entries.mpBegin[i].mID);
                        }
                    }
                    cAssetFilterPreview* preview = mpAssetGrid->mpFilterPreview;
                    if (preview) {
                        preview->SetFeedFilter(&ids);
                        preview->Apply(feedID, configID, !reset);
                    }
                    if (reset)
                        mpAssetGrid->Repopulate();
                }
                item->GetAssetList(&assets);
            }
        }
        if (webPageShown && mpWebBrowserA)
            mpWebBrowserA->ClearPage();
    update_grid:
        if (mpConfig && mpAssetGrid) {
            bool haveKeys = false;
            bool filterActive = false;
            ResourceKey_s0064_c8e0 key;
            key.instance = 0;
            key.type = 0;
            key.group = 0;
            ResourceKey_s0064_c8e0 entryKey;
            entryKey.instance = 0;
            entryKey.type = 0;
            entryKey.group = 0;
            if ((mSelectionEnd - mSelectionBegin) / 20 == 1 && GetSelectedID() && GetSelectedAsset()) {
                key = *GetSelectedAsset()->GetKey();
                const ResourceKey_s0064_c8e0* entry = mpAssetGrid->GetEntryByID(GetSelectedID());
                if (entry)
                    entryKey = *entry;
                haveKeys = true;
            }
            if (mpFilterPanel && mpFilterPanel->IsActive())
                filterActive = true;
            FilterGridEntries(0);
            mpAssetGrid->SetAssetList(&assets);
            mpConfig->SetAssets(&assets, 0);
            mpAssetGrid->SetFeed(mpConfig, item);
            if (haveKeys && !mpAssetGrid->SelectAsset(&entryKey, filterActive, true, false))
                mpAssetGrid->SelectAsset(&key, filterActive, true, false);
        }
        mpCurrentItem = (cRefFeedListItem*)item;
        break;
    }

    case 0xbf7280e2:
        if (AssetBrowser_s0064_c8e0() && AssetBrowser_s0064_c8e0()->CanLaunchEditor()) {
            mbEnteringEditor = true;
            if (sAppProperties->mpInner->mValue && GameModeManager()->GetActiveModeID() == 0xdbdba1) {
                MessageServer_s0064_c8e0()->MessageSend(0x56d39e9, 0, 0);
                mbEnteringEditor = false;
                AssetBrowser_s0064_c8e0()->SetVisibility(0, 0, 0);
            } else {
                OnEditorChosen();
            }
        }
        break;

    case 0xcadf3aca: {
        ResourceKey_s0064_c8e0 key = *(ResourceKey_s0064_c8e0*)pMessage;
        if (!mpAssetGrid->SelectAsset(&key, true, true, false) && SetAssetData(key.type, true)) {
            BrowserMessage m(0xe2415c7d);
            MessageServer_s0064_c8e0()->MessageSend(0xb3d53f95, &m, 0);
            mpAssetGrid->SelectAsset(&key, true, true, false);
        }
        break;
    }
    }
    return true;
}
