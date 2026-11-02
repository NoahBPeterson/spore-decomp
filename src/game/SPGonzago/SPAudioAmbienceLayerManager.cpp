// src/game/SPGonzago/SPAudioAmbienceLayerManager.cpp -- migrated from slice(s) s00e9ed80, s00543590, s00e9fca0, s00e9e290 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioAmbienceLayerManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include <math.h>
#include <wchar.h>
#include "SP/cCameraManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cViewer.h"
#include <new.h>

// unnamed retail callees and globals (address in the comment)
extern uint32_t gAmbCheatArg;    // 0x01487138  (arg to CheatManager::s1c)
extern void* g_vtbl_01487150;
extern void* g_vtbl_01487140;
extern void* g_vtbl_0148713c;
extern void* g_vtbl_013eb394;
extern void* g_vtbl_013ef094;

// ---- items of slice s00e9e290 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct cAmbienceTag {
    void*    mpVtbl;   // +0x00  (vtable slot 0, overwritten with a free-list link)
    void*    mpUnk4;   // +0x04
    uint32_t mKey8;    // +0x08  (rbtree key passed to FUN_00e9db10)
};
struct InnerVec {
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCap;      // +0x08
    void DoInsertValue(void** position, cAmbienceTag* const& value);  // 0x00ea9440, thiscall ret 8
};
struct CheatManager {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c(void* arg);
};
struct TagMapNode {
    uint8_t       pad00[0x14];
    cAmbienceTag* mpValue;   // +0x14
};
struct TagMap {
    uint32_t mUnk00;     // +0x00
    void*    mAnchor;    // +0x04  (end() sentinel; self-referential)
    void*    mRoot;      // +0x08
    void*    mRootNode;  // +0x0c  (passed to DoNukeSubtree)
    uint8_t  mUnk10;     // +0x10
    uint8_t  pad11[3];
    uint32_t mUnk14;     // +0x14
    void find(void* result, void* key);              // 0x00e5c780
    void DoNukeSubtree(void* node);                  // 0x009a9600
};
struct Config {
    virtual void s0();
    virtual void Release();                          // vtable slot 1 -> [eax+4]
    virtual void s2();
};
struct SubObj {
    void* a; void* b; void* c; void* d; void* e;
    void dtor();                                     // 0x00e9ddc0
};
struct RespCurve {
    void*   mBegin;      // +0x00
    void*   pad04[3];
    void*   mCap;        // +0x10
    uint8_t pad14[0x364 - 0x14];
};
struct FixedStr {
    char* mBegin;        // +0x00
    char* mEnd;          // +0x04
    char* mCap;          // +0x08
};
class cAmbLayer {
public:
    void*     mpVtbl;             // +0x00
    void*     mpVtbl4;            // +0x04
    void*     mpVtbl8;            // +0x08
    uint8_t   pad0c[4];           // +0x0c
    Config*   mpConfiguration;     // +0x10
    void*     mpAutoMsgHandler;    // +0x14
    uint32_t  mAutoMsg18;          // +0x18
    uint32_t  mAutoMsg1c;          // +0x1c
    uint32_t  mAutoMsg20;          // +0x20
    uint32_t  mAutoMsg24;          // +0x24
    int32_t   mNumCells;           // +0x28
    InnerVec** mMapBegin;          // +0x2c
    InnerVec** mMapEnd;            // +0x30
    InnerVec** mMapCap;            // +0x34
    uint8_t   pad38[8];            // +0x38..+0x3f
    void*     mViewIdxBegin;       // +0x40
    int32_t   mViewIdxEnd;         // +0x44
    int32_t   mViewIdxCap;         // +0x48
    uint8_t   pad4c[8];            // +0x4c..+0x53
    void*     mViewTagsBegin;      // +0x54
    int32_t   mViewTagsEnd;        // +0x58
    int32_t   mViewTagsCap;        // +0x5c
    uint8_t   pad60[8];            // +0x60..+0x67
    void*     mDynTagsBegin;       // +0x68
    int32_t   mDynTagsEnd;         // +0x6c
    int32_t   mDynTagsCap;         // +0x70
    uint8_t   pad74[0xc];          // +0x74..+0x7f
    TagMap    mIdToTagMap;         // +0x80..+0x97
    uint8_t   pad98[4];            // +0x98..+0x9b
    float     mOriginX;            // +0x9c
    float     mOriginY;            // +0xa0
    float     mOriginZ;            // +0xa4
    float     mRadius;             // +0xa8
    uint8_t   mbSphereChanged;     // +0xac
    uint8_t   padad[3];
    SubObj    mSubB0;              // +0xb0..+0xc3  (has a destructor)
    void*     mpC4;                // +0xc4
    uint8_t   padc8[0x24];         // +0xc8..+0xeb
    RespCurve mCurveA;             // +0xec
    RespCurve mCurveB;             // +0x450
    uint8_t   pad7b4[8];           // +0x7b4..+0x7bb
    FixedStr  mStr;                // +0x7bc
    uint8_t   pad7c8[4];           // +0x7c8..+0x7cb
    uint32_t  mFlags;              // +0x7cc

    // methods of this class (declaration-only; call sites are masked relocs)
    void FUN_00e9e220();                    // 0x00e9e220
    void FUN_00e9dcc0(cAmbienceTag* t);     // 0x00e9dcc0

    // functions reconstructed in this slice
    bool Shutdown();
    bool RemoveTag(uint tag);
    void DestroyCubeMap();
    bool FUN_00e9ed00(cAmbienceTag* p);
    void Destroy();                         // 0x00e9e3a0
};
CheatManager* __cdecl SP_CheatManager();                     // 0x0067de20
void          __cdecl operator_delete_array(void*);           // 0x00f47380
void          __cdecl EA_Messaging_RemoveHandler(void*, uint, uint, uint, uint); // 0x00571db0
int           __stdcall FUN_00e9db10(void* key);              // 0x00e9db10
extern uint32_t gAmbCheatArg;    // 0x01487138  (arg to CheatManager::s1c)
extern cAmbienceTag* gTagFreeListHead;   // 0x016c6a04
extern void* g_vtbl_01487150;
extern void* g_vtbl_01487140;
extern void* g_vtbl_0148713c;
extern void* g_vtbl_013eb394;
extern void* g_vtbl_013ef094;
// ---- items of slice s00e9e290 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cAmbienceTag* gTagFreeListHead;   // 0x016c6a04

// ---- items of slice s00e9fca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t     gPropId015a8b78;  // 0x015a8b78
typedef unsigned int uintptr_t;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct IWnd {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV                                            // 0x08
    virtual void* GetChild(uint id);              // 0x0c
    virtual IWnd* Slot10();                       // 0x10
    PV4 PV                                        // 0x14..0x24
    virtual void  Slot28(int a, int b);           // 0x28
    PV16 PV4                                      // 0x2c..0x78
    virtual void  Slot7c(int a, int b);           // 0x7c
    PV4 PV2                                       // 0x80..0x94
    virtual void  Slot98();                       // 0x98
    PV8 PV4                                       // 0x9c..0xc8
    virtual void  SlotCC(void** out);             // 0xcc
    virtual void  SlotD0(void** out);             // 0xd0
    PV4 PV                                        // 0xd4..0xe4
    virtual void  SlotE8(void* p);                // 0xe8
    PV                                            // 0xec
    virtual void* SlotF0(uint id, int a);         // 0xf0
    PV4                                           // 0xf4..0x100
    virtual void  Slot104(void* p);               // 0x104
    virtual void  Slot108(void* p);               // 0x108
};
struct IConfiguration {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV4 PV                                        // 0x08..0x18
    virtual void Slot1c(uint id, void** out);     // 0x1c
    PV2                                           // 0x20, 0x24
    virtual void Slot28(uint id, int* out);       // 0x28
    PV                                            // 0x2c
    virtual void Slot30(uint id, void** out);     // 0x30
};
struct AudioSystem {
    PV4 PV                                        // 0x00..0x10
    virtual bool Slot14(uint a, void** cfg, uint b);        // 0x14
    PV4 PV2                                       // 0x18..0x2c
    virtual void Slot30(void* id, uint hash, void** out);   // 0x30
    PV                                            // 0x34
    virtual void Slot38(uint a);                  // 0x38
    PV                                            // 0x3c
    virtual void Slot40(uint a, uint b);          // 0x40
    PV4 PV                                        // 0x44..0x54
    virtual void Slot58();                        // 0x58
};
struct AmbConfig {
    void*    mpBegin;                             // +0x00
    uint8_t  pad04[4];                            // +0x04
    void*    mpEnd;                               // +0x08
    uint8_t  pad0c[4];                            // +0x0c
    uint16_t mFlags;                              // +0x10
    uint16_t mCount;                              // +0x12
};
struct cAmbienceLayerManager {
    uint8_t         pad00[0x10];
    IConfiguration* mpConfiguration;              // +0x10
    uint8_t         pad14[0x14];                  // +0x14..+0x27
    int32_t         mNumCells;                    // +0x28
    uint8_t         pad2c[0xc0];                  // +0x2c..+0xeb
    uint8_t         mCurveA[0x364];               // +0xec (ResponseCurve)
    uint8_t         mCurveB[0x364];               // +0x450 (ResponseCurve)
    uint8_t         mItSamplePts[0x40];           // +0x7b4
};
void*       EA_GetSystemAT(void);                       // 0x00a206f0
void*       __cdecl EA_ConvertToString8(void*, const int*);   // 0x0093c570
bool __fastcall FUN_00e9fca0(cAmbienceLayerManager* self, void* edx);  // 0x00e9fca0 (defined below; used by a stub's inline body)
struct Thiscall {
    void  FUN_00e9e220();                        // 0x00e9e220
    void  FUN_00e9faa0(void* s);                 // 0x00e9faa0
    void  FUN_00e9fbc0();                        // 0x00e9fbc0
    void  FUN_00e9fca0();                        // 0x00e9fca0 (SetupLayers)
    void  SetWindow(IWnd* w);                    // 0x00e9fe90 (cWindowPulse::SetWindow)
    void  SetMusicNote(void* m);                 // 0x00ea2d50 (cCityMusicNoteEditor::SetMusic)
    void  SetMusicLoad(void* m);                 // 0x00ea23a0 (cCityMusicLoadSave::SetMusic)
    void  ResetUndoBuffer();                     // 0x00eb10d0
    unsigned char FUN_00ead820();                // 0x00ead820 (returns char)
    unsigned char FUN_00ead840();                // 0x00ead840 (returns char)
    void  FUN_00ea3b50();                        // 0x00ea3b50 (cCityMusicNoteEditor::Update)
    void  FUN_00ea3420(int b);                   // 0x00ea3420 (RedrawMelody)
    void  FUN_00ea3120();                        // 0x00ea3120 (LoopMelody)
    void  SetSoundProperty(int v);               // 0x00ea3040
    void  InitFromConfiguration(void* cfg, uint id);   // 0x00a1a9d0
    void  FUN_0095ea30(void* vec);               // 0x0095ea30
};
// ---- items of slice s00e9fca0 end

// ---- items of slice s00543590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern const wchar_t* gAttrTerm2;      // 0x013f3978  L"term"  (category handler copy)
extern const wchar_t* gAttrScheme;     // 0x013f397c  L"scheme"
extern "C" __declspec(dllimport) unsigned long wcstoul(const wchar_t*, wchar_t**, int);
#pragma intrinsic(wcscmp)
unsigned int FNV1_String16(const wchar_t* s, unsigned int hash, int lower);  // 0x00932f30
struct Alloc {                       // empty allocator: passed by reference (1-byte temp)
    char mDummy;
    Alloc() {}
};
struct String8 {                     // eastl::basic_string<char>: 0x10 bytes
    char* mpBegin;                   // +0x00
    char* mpEnd;                     // +0x04
    char* mpCapacity;                // +0x08
    char* mpAllocator;               // +0x0c
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
};
struct String16 {                    // eastl::basic_string<wchar_t>: 0x0c bytes
    wchar_t* mpBegin;                // +0x00
    wchar_t* mpEnd;                  // +0x04
    wchar_t* mpCapacity;             // +0x08
    String16(const wchar_t* p, const Alloc& a = Alloc());  // 0x0041df50 (by value: sret)
    void FreeBuffer();                                     // 0x004237d0
    ~String16() { FreeBuffer(); }
};
struct LinkStringMap {               // vector_map<unsigned int, String8, less<unsigned int>>
    String8* mpBegin;                // +0x00
    String8* mpEnd;                  // +0x04
    String8* mpCapacity;             // +0x08
    String8* op_index(const void* key);                    // 0x00546930
};
struct TagList {                     // vector<String16>
    String16* mpBegin;               // +0x00
    String16* mpEnd;                 // +0x04
    String16* mpCapacity;            // +0x08
    void push_back(const String16& v);                     // 0x00546a60
};
struct UintList {                    // vector<unsigned long>
    unsigned long* mpBegin;          // +0x00
    unsigned long* mpEnd;            // +0x04
    unsigned long* mpCapacity;       // +0x08
    void push_back(const unsigned long& v);                // 0x00546b00
};
struct AtomEntry40 {
    char mPad00[0x8c];
    LinkStringMap mLinkMap;          // +0x8c
    char mPad98[0x10];
    String8 mThumbLink;              // +0xa8
    String8 mAssetLink;              // +0xb8
    unsigned int mnAssetType;        // +0xc8
    char mPadCC[0x14];
    TagList mTags;                   // +0xe0
    char mPadEC[0x0c];
    UintList mUintList;              // +0xf8
};
struct AtomDocument40 {
    char mPad00[0x50];
    String8 mSelfLink;               // +0x50
};
namespace EA {
template <typename T>
class AutoRefCount_s0054_3590 {
 public:
    T* mpObject;                     // +0x00
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
struct Ctx40 {
    char mPad00[0x20];
    EA::AutoRefCount_s0054_3590<AtomDocument40> mpDocument;  // +0x20
    bool mbInDoc;                                 // +0x24
    char mPad25[3];
    AtomEntry40* mpCurEntry;                      // +0x28

    void FUN_00543b90(int* attrs);
    void FUN_00543bb0(int* attrs);
    void FUN_00543bd0(int* attrs);
    void FUN_00543bf0(int* attrs);
    void FUN_00543590(int* attrs);
    void FUN_005439d0(int* attrs);
    void FUN_00543c10(int* attrs, int mode);
};
// ---- items of slice s00543590 end

// ---- items of slice s00e9ed80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);              // 0x011e0744
extern char g_eastlAllocator;                            // 0x013ebb38
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vector3Vec {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    Vector3* erase(Vector3* first, Vector3* last);               // 0x009e0480, thiscall ret 8
    void DoInsertValue(Vector3* pos, const Vector3& v);          // 0x00e9e620, thiscall ret 8
    void push_back(const Vector3& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) Vector3(v);
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
extern const Vector3 kZeroVector;                                // 0x016c6964
template <class T> struct SPVec4
{
    T* mpBegin;                                          // +0x00
    T* mpEnd;                                            // +0x04
    T* mpCapacity;                                       // +0x08
    void DoInsertValue(T* pos, const T* pValue);         // 0x00ea9440 (ret 8)
    void resize(int n);                                  // 0x00eb0230 (ret 4)
    void push_back(const T v)
    {
        if (mpEnd < mpCapacity)
        {
            T* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot != 0)
                *slot = v;
        }
        else
        {
            DoInsertValue(mpEnd, &v);
        }
    }
};
void* operator new(unsigned size, const char* tag, int a, int b, void* c, int d);   // 0x00f473a0
void operator delete[](void* p);                                                  // 0x00f47380
struct cSPVector3_s00e9_ed80
{
    float x, y, z;
};
struct cAmbienceTag_s00e9_ed80
{
    uint32_t    mFlags;                                  // +0x00 (free-list link while free)
    uint32_t    mType;                                   // +0x04
    cSPVector3_s00e9_ed80  mPosition;                               // +0x08
    uint32_t    mInstanceId;                             // +0x14
};
extern cAmbienceTag_s00e9_ed80* g_freeTags;                         // [0x016c6a04]
struct FixedAllocator
{
    bool AddCore(void* pCore, unsigned size);            // 0x00926650 (ret 8)
};
extern FixedAllocator g_tagAllocator;                    // [0x016c69f4]
struct TagNode
{
    uint32_t pad00[5];                                   // +0x00 (parent/child/colour)
    cAmbienceTag_s00e9_ed80* mpValue;                               // +0x14
};
struct TagTree
{
    TagNode* mpAnchor;                                   // +0x00
    TagNode* mpEnd;                                      // +0x04
    void find(TagNode** pOut, const uint32_t* pKey);     // 0x00e5c780 (ret 8)
};
struct ResponseCurve
{
    uint8_t pad[0x364];                                  // +0x000 (fixed data array)
    float GetOutputValue(float x) const;                 // 0x00a1a110 (ret 4)
};
struct cAmbienceLayerManager_s00e9_ed80;
struct IHandler
{
    virtual void v00();                                  // +0x00 (activate)
    virtual void v04();                                  // +0x04 (release)
    virtual void v08();                                  // +0x08 (addref)
    virtual void v0c();                                  // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual float Test(void* p);                         // +0x20 (ret 4)
    virtual void v24();
    virtual void v28();
    virtual void Release();                              // +0x2c
};
typedef IHandler** IHandlerSlot;
class cAmbienceLayer : public IHandler
{
public:
    float x, y, z;                                       // +0x04 sampled position
    void FUN_00a355e0(const char* name);                 // 0x00a355e0 (ret 4)
    float FUN_00a34ed0();                                // 0x00a34ed0 (ret 0) -> distance
    void FUN_00ed4890(uint32_t hash);                    // 0x00ed4890 (ret 4)
    void UpdatePrimitives(float dt, uint32_t n);         // 0x00a34ee0 (ret 8)
    void FUN_00a35c00();                                 // 0x00a35c00 (ret 0)
    void FUN_00a35c40(IHandlerSlot pList, float t);      // 0x00a35c40 (ret 8)
    void Update();                                       // 0x00a35d20 (ret 0)
    bool Init();                                         // 0x00a36570 (ret 0)
};
cAmbienceLayer* __fastcall cAmbienceLayer_operatorNew(void* p);   // 0x00a35aa0
class cAmbienceLayerManager_s00e9_ed80
{
public:
    uint8_t  pad00[0x28];                                // +0x00
    int32_t  mnCubeMapSize;                              // +0x28
    SPVec4<uint8_t*> mCubeMapFaces;                      // +0x2c
    uint8_t  pad38[0x54 - 0x38];                         // +0x38
    SPVec4<cAmbienceTag_s00e9_ed80*> mAmbientViewTags;              // +0x54
    uint8_t  pad60[0x68 - 0x60];                         // +0x60
    SPVec4<cAmbienceTag_s00e9_ed80*> mDynamicViewTags;              // +0x68 (end at 0x6c is the generation cursor)
    uint8_t  pad74[0x7c - 0x74];                         // +0x74
    cAmbienceTag_s00e9_ed80**  mDynamicViewTagsIterator;            // +0x7c  (dynamic tag slot cursor)
    TagTree  mIdToTagMap;                                // +0x80
    uint8_t  pad88[0x9c - 0x88];                         // +0x88
    Vector3  mCentre;                                    // +0x9c  (ambient sphere centre)
    float    mfMaxLayerDistance;                         // +0xa8
    uint8_t  mbDirty;                                    // +0xac
    uint8_t  padad[0xb0 - 0xad];                         // +0xad
    SPVec4<cAmbienceLayer*> mLayers;                     // +0xb0
    uint8_t  padbc[0xc4 - 0xbc];                         // +0xbc
    Vector3Vec mSamplePoints;                            // +0xc4  (SamplePoints::mPoints)
    uint8_t  padd4[0xd8 - 0xd4];                         // +0xd4
    float    mfSampleRadius;                             // +0xd8
    int32_t  mnSamplePoints;                             // +0xdc
    float    mfRingRadius;                               // +0xe0
    float    mfRingStep;                                 // +0xe4
    uint32_t mModificationCount;                         // +0xe8
    ResponseCurve mCurveSampleRadius;                    // +0xec
    ResponseCurve mCurveDistanceBetween;                 // +0x450
    uint8_t  pad474[0x7cc - 0x7b4];                      // +0x7b4
    uint32_t mStateFlags;                                // +0x7cc  (bit0 busy, bit1 no planet, bit2 game mode)
    uint32_t mPhase;                                     // +0x7d0
    cSPVector3_s00e9_ed80* mItSamplePts;                            // +0x7d4
    cSPVector3_s00e9_ed80* mItSamplePtsEnd;                         // +0x7d8

    void  InsertDynamicTag(cAmbienceTag_s00e9_ed80*** pSlot, const cSPVector3_s00e9_ed80* pPos, uint32_t id);  // @ 0x00e9f3d0
    void  GenerateDynamicAmbienceTags();                                                // @ 0x00e9f480
    void  Update(float dt);                                                             // @ 0x00e9f770
    bool  InsertTag(uint32_t key, float x, float y, float z, uint32_t id);              // @ 0x00e9f9c0
    bool  FUN_00e9faa0(const char* name);                                               // @ 0x00e9faa0
    void  ResetCubeMap();                                                               // @ 0x00e9fbc0
    void  DestroyCubeMap();                                                             // 0x00e9e350
    void  GenerateDynamicAmbienceTagsBegin();                                           // 0x00e9dd80
    void  RemoveDynamicTags();                                                          // 0x00e9ea40
    bool  FUN_00e9dd20(uint32_t hash);                                                  // 0x00e9dd20
    bool  FUN_00e9ed00(cAmbienceTag_s00e9_ed80* tag);                                              // 0x00e9ed00
    void  SamplePointsRebuild();                                                        // 0x00e9ed80
    void  FUN_00e9e8f0(cAmbienceLayer** pos, cAmbienceLayer** pValue);                  // 0x00e9e8f0
};
struct IEff
{
    virtual void* Get(uint32_t name, int zero);          // +0x8c (ret 8)
};
IEff* EffectsManagerPtr();                               // 0x0067ddd0
struct IObject
{
    virtual void Slot0();
    virtual void v04();
    virtual void Slot8();
    virtual void SlotC();
virtual void Slot10();
virtual void Slot14();
virtual void Slot18();
virtual void Slot1c();
    virtual float Test(void* p);                         // +0x20 (ret 4)
};
class cTerrainMapSet
{
public:
    uint8_t  pad00[0x34];                                // +0x00
    float    mfRadius;                                   // +0x34
    float    mfMaxHeight;                                // +0x38
    float    mfWaterHeight;                              // +0x3c
    float    mfWaterDelta;                               // +0x40
    float    mfBeachHeight;                              // +0x44
    float GetHeightAt(const cSPVector3_s00e9_ed80* pSample);        // 0x00f927c0 (ret 4)
};
struct cTerrainSample
{
    uint8_t  pad00[0x38];                                // +0x00
    float    mfX;                                        // +0x38
    float    mfY;                                        // +0x3c
    float    mfZ;                                        // +0x40
    uint8_t  pad44[4];                                   // +0x44
    float    mfRadius;                                   // +0x48
};
class cPlanetSurface
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cTerrainMapSet* GetMap();                    // +0x0c (ret 0)
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual float Test(const cSPVector3_s00e9_ed80* p);             // +0x20 (ret 4)
    bool FUN_00b7e3e0(const cSPVector3_s00e9_ed80* pSample);        // 0x00b7e3e0 (ret 4)
};
struct PlanetModelT
{
    uint8_t  pad00[0x24];                                // +0x00
    cPlanetSurface* mpSurface;                           // +0x24
};
PlanetModelT* PlanetModelObj();                           // 0x00b3d350
uint32_t SP_GetCurrentGameMode();                        // 0x00b5b800
struct SampleVec
{
    cTerrainSample** mpBegin;                            // +0x00
    cTerrainSample** mpEnd;                              // +0x04
    cTerrainSample** mpCapacity;                         // +0x08
    uint8_t          pad0c[8];                           // +0x0c
    uint32_t         mnGuard;                            // +0x14 (0 => inline buffer)
    cTerrainSample*  mBuffer[256];                       // +0x18
    SampleVec()
        : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 256), mnGuard(0) {}
    ~SampleVec()
    {
        if (mpBegin != 0 && ((uint32_t*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
};
SampleVec* __stdcall FUN_00b3d3c0(Vector3* pCentre, SampleVec* pOut, int mode, float radius, int a, int b);  // 0x00b3d3c0
void __fastcall FUN_00b79c30(SampleVec* p);                // 0x00b79c30 (ecx arg)
struct LARGE_INTEGER_T { __int64 QuadPart; };
extern "C" int __stdcall QueryPerformanceCounter_(LARGE_INTEGER_T* p);   // kernel32
struct EAStopwatch
{
    uint8_t pad00[0x18];                                 // +0x00
    LARGE_INTEGER_T mDeadline;                           // +0x18 (QPC deadline)
    void ctor(int units, bool b);
    void SetTimeLimit(uint32_t limit, bool b);           // 0x0093a480 (ret 8)
    void Restart();                                      // 0x00571e80 (ret 0)
    void Destroy();                                      // 0x0093a2e0 (ret 0)
};
uint32_t FNVHash(const char* s, uint32_t seed, int mode);  // 0x00932e80 (cdecl)
static __forceinline cAmbienceTag_s00e9_ed80* AcquireTag()
{
    cAmbienceTag_s00e9_ed80* tag = g_freeTags;
    while (tag == 0)
    {
        if (!g_tagAllocator.AddCore(0, 0))
        {
            tag = 0;
            break;
        }
        tag = g_freeTags;
    }
    if (tag != 0)
    {
        g_freeTags = (cAmbienceTag_s00e9_ed80*)tag->mFlags;
        tag->mFlags = 0;
        tag->mType = 0;
        tag->mInstanceId = 0;
    }
    return tag;
}
struct PtrVec100
{
    void** mpBegin;                                      // +0x00
    void** mpEnd;                                        // +0x04
    void** mpCapacity;                                   // +0x08
};
// ---- items of slice s00e9ed80 end

// @ 0x005439d0
void Ctx40::FUN_005439d0(int* attrs)
{
    if (mpCurEntry != 0) {
        const wchar_t** p = (const wchar_t**)attrs;
        const wchar_t* pTerm;
        unsigned int schemeHash;
        while (*p != 0) {
            const wchar_t* key = *p++;
            const wchar_t* val = *p++;
            if (wcscmp(key, gAttrTerm2) == 0) {
                pTerm = val;
                continue;
            }
            if (wcscmp(key, gAttrScheme) == 0)
                schemeHash = FNV1_String16(val, 0x811c9dc5, 1);
        }
        switch (schemeHash) {
        case 0x326cb657:
            mpCurEntry->mTags.push_back(String16(pTerm));
            break;
        case 0x9a5acf10: {
            unsigned long v = wcstoul(pTerm, 0, 0x10);
            mpCurEntry->mUintList.push_back(v);
            break;
        }
        default:
            break;
        }
    }
}

// @ 0x00e9e290
bool cAmbLayer::Shutdown()
{
    mFlags |= 1;
    CheatManager* cm = SP_CheatManager();
    if (cm != 0) {
        cm->s1c(&gAmbCheatArg);
    }
    void* h = mpAutoMsgHandler;
    if (h != 0) {
        mpAutoMsgHandler = 0;
        EA_Messaging_RemoveHandler(h, mAutoMsg18, mAutoMsg1c, mAutoMsg20, mAutoMsg24);
    }
    FUN_00e9e220();
    return false;
}

// @ 0x00e9e2f0
bool cAmbLayer::RemoveTag(uint tag)
{
    void* it;
    mIdToTagMap.find(&it, &tag);
    if (it == &mIdToTagMap.mAnchor) {
        return false;
    }
    cAmbienceTag* t = ((TagMapNode*)it)->mpValue;
    if (t == 0) {
        return false;
    }
    FUN_00e9dcc0(t);
    t->mpVtbl = gTagFreeListHead;
    gTagFreeListHead = t;
    return true;
}

// @ 0x00e9e350
void cAmbLayer::DestroyCubeMap()
{
    int n = (int)(mMapEnd - mMapBegin);
    for (int i = 0; i < n; i++) {
        InnerVec* e = mMapBegin[i];
        if (e != 0) {
            if (e->mpBegin != 0) {
                operator_delete_array(e->mpBegin);
            }
            operator_delete_array(e);
        }
        mMapBegin[i] = 0;
    }
}

// @ 0x00e9e3a0
void cAmbLayer::Destroy()
{
    mpVtbl  = &g_vtbl_01487150;
    mpVtbl4 = &g_vtbl_01487140;
    mpVtbl8 = &g_vtbl_0148713c;
    if ((mStr.mCap - mStr.mBegin) > 1 && mStr.mBegin != 0)
        operator_delete_array(mStr.mBegin);
    if (mCurveB.mBegin != 0 && mCurveB.mBegin != mCurveB.mCap)
        operator_delete_array(mCurveB.mBegin);
    if (mCurveA.mBegin != 0 && mCurveA.mBegin != mCurveA.mCap)
        operator_delete_array(mCurveA.mBegin);
    if (mpC4 != 0)
        operator_delete_array(mpC4);
    mSubB0.dtor();
    mIdToTagMap.DoNukeSubtree(mIdToTagMap.mRootNode);
    if (mDynTagsBegin != 0)
        operator_delete_array(mDynTagsBegin);
    if (mViewTagsBegin != 0)
        operator_delete_array(mViewTagsBegin);
    if (mViewIdxBegin != 0)
        operator_delete_array(mViewIdxBegin);
    if (mMapBegin != 0)
        operator_delete_array(mMapBegin);
    if (mpAutoMsgHandler != 0) {
        void* h = mpAutoMsgHandler;
        mpAutoMsgHandler = 0;
        EA_Messaging_RemoveHandler(h, mAutoMsg18, mAutoMsg1c, mAutoMsg20, mAutoMsg24);
    }
    if (mpConfiguration != 0)
        mpConfiguration->Release();
    mpVtbl4 = &g_vtbl_013eb394;
    mpVtbl8 = &g_vtbl_013ef094;
}

// @ 0x00e9ed00
bool cAmbLayer::FUN_00e9ed00(cAmbienceTag* p)
{
    if (p == 0) {
        return false;
    }
    int idx = FUN_00e9db10(&p->mKey8);
    InnerVec* v = mMapBegin[idx];
    void** end = v->mpEnd;
    void** it = v->mpBegin;
    int n = (int)(end - it);
    void** w = it;
    for (int k = 0; k < n; k++, w++) {
        if (*w == 0) {
            it[k] = p;
            return true;
        }
    }
    void** cur = v->mpEnd;
    if (cur < v->mpCap) {
        v->mpEnd = cur + 1;
        if (cur != 0) {
            *cur = p;
        }
    } else {
        v->DoInsertValue(cur, p);
    }
    return true;
}

// @ 0x00e9f3d0
void cAmbienceLayerManager_s00e9_ed80::InsertDynamicTag(cAmbienceTag_s00e9_ed80*** pSlot, const cSPVector3_s00e9_ed80* pPos, uint32_t id)
{
    if (*pSlot == mDynamicViewTags.mpEnd)
    {
        mDynamicViewTags.push_back(AcquireTag());
        *pSlot = mDynamicViewTags.mpEnd - 1;
    }
    cAmbienceTag_s00e9_ed80* tag = *(cAmbienceTag_s00e9_ed80**)*pSlot;
    tag->mFlags |= 1;
    *pSlot += 1;
    tag->mPosition = *pPos;
    tag->mType = id;
}

// @ 0x00e9f480
void cAmbienceLayerManager_s00e9_ed80::GenerateDynamicAmbienceTags()
{
    EAStopwatch stopwatch;
    stopwatch.ctor(3, 0);
    stopwatch.SetTimeLimit(500, 1);

    PlanetModelT* pModel = PlanetModelObj();
    if (!pModel)
        return;
    cPlanetSurface* pSurface = PlanetModelObj()->mpSurface;
    if (!pSurface)
    {
        if (mItSamplePts == mItSamplePtsEnd)
            mPhase = 2;
        return;
    }

    IObject* pObj = (IObject*)EffectsManagerPtr()->Get(0x2c9c762, 0);
    if (pObj)
        pObj->Slot0();
    cAmbienceLayer* pLayerProxy = (cAmbienceLayer*)EffectsManagerPtr()->Get(0x1c8a626, 0);
    if (pLayerProxy)
        pLayerProxy->v00();

    SampleVec samples;
    FUN_00b79c30(FUN_00b3d3c0(&mCentre, &samples, 7, mfRingRadius, 0, 0));
    unsigned nSamples = (unsigned)(samples.mpEnd - samples.mpBegin);

    for (; mItSamplePts != mItSamplePtsEnd; ++mItSamplePts)
    {
        LARGE_INTEGER_T now;
        QueryPerformanceCounter_(&now);
        __int64 remaining = stopwatch.mDeadline.QuadPart - now.QuadPart;
        if (remaining < 0)
            break;

        if (pSurface->FUN_00b7e3e0(mItSamplePts))
        {
            InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0x9e3c3dfa);
        }
        else
        {
            cTerrainMapSet* pMap = pSurface->GetMap();
            float height = (pMap->mfBeachHeight + pMap->mfWaterHeight) * pMap->mfMaxHeight
                         + pMap->mfRadius;
            float terrainH = pSurface->GetMap()->GetHeightAt(mItSamplePts);
            if (terrainH < height)
                InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0x9a1731dc);
        }
        for (unsigned i = 0; i < nSamples; ++i)
        {
            cTerrainSample* p = samples.mpBegin[i];
            float dz = p->mfZ - mItSamplePts->z;
            float dy = p->mfY - mItSamplePts->y;
            float dx = p->mfX - mItSamplePts->x;
            if (p->mfRadius * p->mfRadius > dz * dz + dy * dy + dx * dx)
                InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0x6d5c48c);
        }
        if (pObj != 0 && pSurface->Test(mItSamplePts) == 1.0f
            && pObj->Test(mItSamplePts) == 1.0f)
            InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0xfd3d2ed9);
    }

    InsertDynamicTag(&mDynamicViewTagsIterator, (const cSPVector3_s00e9_ed80*)&mCentre, 0x76822486);
    if (pLayerProxy)
        pLayerProxy->v04();
    if (pObj)
        pObj->v04();
    if (mItSamplePts == mItSamplePtsEnd)
        mPhase = 2;
}

// @ 0x00e9f770
void cAmbienceLayerManager_s00e9_ed80::Update(float dt)
{
    if (mStateFlags & 8)
        return;
    if (mCentre.x != kZeroVector.x || mCentre.y != kZeroVector.y || mCentre.z != kZeroVector.z)
    {
        if (PlanetModelObj() == 0 || PlanetModelObj()->mpSurface == 0)
            mStateFlags |= 2;
        else
            mStateFlags &= ~2u;
        if (SP_GetCurrentGameMode() == 0xffffffffu || SP_GetCurrentGameMode() == 0x2ccd1d2
            || SP_GetCurrentGameMode() == 0xdbdba1)
            mStateFlags |= 4;
        else
            mStateFlags &= ~4u;

        EAStopwatch stopwatch;
        stopwatch.ctor(3, 0);
        stopwatch.Restart();

        if (mStateFlags == 0)
        {
            switch (mPhase)
            {
            case 0:
            {
                float a = mCurveSampleRadius.GetOutputValue(mfSampleRadius);
                float b = mCurveDistanceBetween.GetOutputValue(mfSampleRadius);
                if (mbDirty != 0 || a != mfRingRadius || b != mfRingStep)
                {
                    mfRingRadius = a;
                    mfRingStep = b;
                    SamplePointsRebuild();
                    GenerateDynamicAmbienceTagsBegin();
                    mPhase = 1;
                }
                break;
            }
            case 1:
                GenerateDynamicAmbienceTags();
                break;
            case 2:
                if (mbDirty != 0)
                    RemoveDynamicTags();
                mPhase = 0;
                break;
            }
        }
        else
        {
            mPhase = 0;
        }
        ++mModificationCount;
        for (int i = 0; i < (int)(mLayers.mpEnd - mLayers.mpBegin); ++i)
        {
            cAmbienceLayer* pLayer = mLayers.mpBegin[i];
            pLayer->UpdatePrimitives(dt, mModificationCount);
            if (mPhase != 1)
            {
                pLayer->FUN_00a35c00();
                if (mAmbientViewTags.mpBegin != mAmbientViewTags.mpEnd)
                    pLayer->FUN_00a35c40((IHandlerSlot)&mAmbientViewTags, dt);
                if (mDynamicViewTags.mpBegin != mDynamicViewTags.mpEnd)
                    pLayer->FUN_00a35c40((IHandlerSlot)&mDynamicViewTags, dt);
                pLayer->Update();
            }
        }
        stopwatch.Destroy();
        mbDirty = 0;
    }
}

// @ 0x00e9f9c0
bool cAmbienceLayerManager_s00e9_ed80::InsertTag(uint32_t key, float x, float y, float z, uint32_t id)
{
    TagNode* pNode;
    mIdToTagMap.find(&pNode, &key);
    if (pNode != mIdToTagMap.mpEnd && pNode->mpValue != 0)
        return false;

    cAmbienceTag_s00e9_ed80* tag = AcquireTag();
    if (!tag)
        return false;

    cSPVector3_s00e9_ed80 pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    tag->mPosition = pos;
    tag->mType = id;
    tag->mInstanceId = key;
    return FUN_00e9ed00(tag);
}

// @ 0x00e9faa0
bool cAmbienceLayerManager_s00e9_ed80::FUN_00e9faa0(const char* name)
{
    uint32_t hash = FNVHash(name, 0x811c9dc5, 1);
    if (FUN_00e9dd20(hash))
        return false;

    cAmbienceLayer* pLayer = 0;
    void* pMem = operator new(0x298, "Audio", 0, 0, 0, 0);
    if (pMem != 0)
        pLayer = cAmbienceLayer_operatorNew(pMem);
    if (pLayer != 0)
        pLayer->v08();
    pLayer->FUN_00a355e0(name);
    pLayer->FUN_00ed4890(hash);
    if (!pLayer->Init())
    {
        if (pLayer != 0)
            pLayer->v0c();
        return false;
    }
    if (mLayers.mpEnd < mLayers.mpCapacity)
    {
        cAmbienceLayer** slot = mLayers.mpEnd;
        mLayers.mpEnd = slot + 1;
        if (slot != 0)
        {
            *slot = pLayer;
            if (pLayer != 0)
                pLayer->v08();
        }
    }
    else
    {
        FUN_00e9e8f0(mLayers.mpEnd, &pLayer);
    }
    float distance = pLayer->FUN_00a34ed0();
    if (mfMaxLayerDistance < distance)
        mfMaxLayerDistance = distance;
    if (pLayer != 0)
        pLayer->v0c();
    return true;
}

// @ 0x00e9fbc0
void cAmbienceLayerManager_s00e9_ed80::ResetCubeMap()
{
    DestroyCubeMap();
    int nFaces = mnCubeMapSize * mnCubeMapSize * 6;
    mCubeMapFaces.resize(nFaces);
    for (int i = 0; i < nFaces; ++i)
    {
        PtrVec100* pList = (PtrVec100*)operator new(0x14, "Audio", 0, 0, 0, 0);
        if (pList != 0)
        {
            pList->mpBegin = 0;
            pList->mpEnd = 0;
            pList->mpCapacity = 0;
        }
        else
        {
            pList = 0;
        }
        if ((uint32_t)(pList->mpCapacity - pList->mpBegin) < 100)
        {
            void** pNew = (void**)operator new(400, "Simulator", 0, 0, &g_eastlAllocator, 0xd1);
            memcpy(pNew, pList->mpBegin, (char*)pList->mpEnd - (char*)pList->mpBegin);
            if (pList->mpBegin != 0)
                operator delete[](pList->mpBegin);
            void** pOldBegin = pList->mpBegin;
            pList->mpBegin = pNew;
            pList->mpEnd = pNew + (pList->mpEnd - pOldBegin);
            pList->mpCapacity = pNew + 100;
        }
        mCubeMapFaces.mpBegin[i] = (uint8_t*)pList;
    }
}

// @ 0x00e9fca0
bool __fastcall FUN_00e9fca0(cAmbienceLayerManager* self, void* edx)
{
    (void)edx;
    ((Thiscall*)self)->FUN_00e9e220();
    AmbConfig c;
    self->mpConfiguration->Slot1c(0xc49b97a3, (void**)&c);
    bool dynamic = (c.mFlags & 0x30) != 0;
    if (!dynamic) {
        if (c.mCount == 0)
            return true;
    } else if (c.mpEnd == 0) {
        return true;
    }
    void* iter = dynamic ? c.mpBegin : (void*)&c;
    int count = dynamic ? (int)(uintptr_t)c.mpEnd : (c.mCount != 0 ? 1 : 0);
    for (int i = 0; i < count; ++i) {
        void* tmp = 0;
        void* s = EA_ConvertToString8(&tmp, (const int*)iter);
        ((Thiscall*)self)->FUN_00e9faa0(*(void**)s);
        if (tmp)
            operator_delete_array(tmp);
        iter = (char*)iter + 0x10;
    }
    return true;
}

// @ 0x00e9fd70
char __fastcall FUN_00e9fd70(cAmbienceLayerManager* self, void* edx)
{
    (void)edx;
    AudioSystem* sys = (AudioSystem*)EA_GetSystemAT();
    IConfiguration* cfg = self->mpConfiguration;
    if (cfg) {
        self->mpConfiguration = 0;
        cfg->Release();
    }
    if (!sys->Slot14(0x6ff1e689, (void**)&self->mpConfiguration, 0x21407ee))
        return 0;
    cfg = self->mpConfiguration;
    self->mNumCells = 10;
    cfg->Slot28(gPropId015a8b78, &self->mNumCells);
    self->mpConfiguration->Slot30(0xf5a18499, (void**)&self->mItSamplePts);
    ((Thiscall*)(void*)self->mCurveA)->InitFromConfiguration(self->mpConfiguration, 0xdc079eb6);
    ((Thiscall*)(void*)self->mCurveB)->InitFromConfiguration(self->mpConfiguration, 0x2f826725);
    ((Thiscall*)self)->FUN_00e9fbc0();
    ((Thiscall*)self)->FUN_00e9fca0();
    return 1;
}
