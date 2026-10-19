// src/game/SPEditors/SPUIAssetBrowser.cpp -- migrated from slice(s) s0064bc50, s0064acd0, s00649f60, s00647f40, s00646370, s00645620, s00644b90 by tools/migrate/rewrite.py
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

// ---- items of slice s00644b90 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EASTL_allocator_allocate(size_t, const char*, int, int, const char*, int); // 0x00f473a0
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define AT(T, off) (*(T*)((char*)this + (off)))
struct IRC { virtual void AddRef(); virtual void Release(); };
struct Key3;
struct RCObj {
    virtual void v0(); virtual void v1(const void*); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual uint32_t v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual Key3* v16(); virtual void v17(const void*); virtual bool v18(); virtual void v19(); virtual void v20();
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
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
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
extern Key3 g1525894, g15258a0;
// ---- items of slice s00644b90 end




// unnamed retail callees and globals that name local stubs (address in the comment)
extern Key3 g1525894, g15258a0;

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
    uint32_t f00, f04, f08, f0c, f10, f14, f18, f1c;
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
// ---- items of slice s0064bc50 end

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
        bool less = k[0] < p->f00;
        if ((k[0] == p->f00) && (less = k[2] < p->f08, k[2] == p->f08))
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







// @ 0x00648ce0
void __cdecl sub_648ce0()
{}






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
