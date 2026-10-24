// slice s005802f0 — editor name helpers, editor info save/load, GIF capture.
// SP::cAppModeEditorBase (editor mode) member methods + editor-info serializers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
typedef unsigned int uint32_t;

// ---------------------------------------------------------------------------
// eastl string (3 pointers + empty allocator) and the 20-byte SP::cString.
// ---------------------------------------------------------------------------
extern const wchar_t gEmptyString16[];          // 0x01667bac (mpBegin/mpEnd)
#define S16_EMPTY()     ((wchar_t*)gEmptyString16)
#define S16_EMPTY_CAP() ((wchar_t*)((char*)gEmptyString16 + 2))

namespace eastl {
class allocator_s0058_02f0 { public: };
template <typename T, typename A = allocator_s0058_02f0>
struct basic_string_s0058_02f0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAlloc;
    basic_string_s0058_02f0() {     // 0x0.. default ctor -> the empty string
        mpBegin = (T*)S16_EMPTY();
        mpEnd = (T*)S16_EMPTY();
        mpCapacity = (T*)S16_EMPTY_CAP();
    }
    void trim();                    // 0x0057eda0
};
} // namespace eastl

typedef eastl::basic_string_s0058_02f0<wchar_t> string16;

struct SPcString {                 // 20 bytes (retail SP::cString)
    uint32_t mTableResource;       // +0x0
    uint32_t mLocalString;         // +0x4
    uint32_t mSourceCStr;          // +0x8
    uint32_t mPlaceholderId;       // +0xc
    uint32_t mFlags;               // +0x10
    void Init();                   // 0x006b5060 ctor
    void Load(int, int, int);      // 0x006b54b0
    const wchar_t* GetText();      // 0x006b55c0
    void Dtor();                   // 0x006b5240
};

// ---------------------------------------------------------------------------
// format / name globals referenced by absolute address
// ---------------------------------------------------------------------------
extern const wchar_t DAT_013f5b90[];   // L"%s"
extern const wchar_t DAT_013f5b98[];   // L"%s"
extern const wchar_t DAT_013f5b9c[];   // L"GIF Name (PLACEHOLDER)"
extern const wchar_t DAT_013f5bcc[];   // L"%02u-%02u-%02u"
extern const wchar_t DAT_013f5bec[];   // L"%02u"
extern const wchar_t DAT_013f5bf8[];   // L"%04u"
extern const wchar_t DAT_013f5c04[];   // L"%s"
extern const wchar_t DAT_013f5c0c[];   // L"Spore_GIF_"
extern const wchar_t DAT_013f5c24[];   // L"EditorUser_%hs"
extern const wchar_t DAT_013f5c44[];   // L"EditorOfflineUser"
extern const wchar_t DAT_013f5c68[];   // L"%s.db"
extern const wchar_t DAT_013f5c74[];   // L"%s.db.tmp"
extern const char    kEditorAllocName[];   // 0x013eb430 "Editor"
extern const char    kSimulatorAllocName[];// 0x013f09b4 "Simulator"
extern const char    kEditorPropListName[];// 0x013f5b78 "Editor/cPropertyList"
extern void*         g_1897c18[];           // 0x01897c18 (EA::Allocator ref arg)

// ---------------------------------------------------------------------------
// stub for the thiscall callees (member -> ecx = this)
// ---------------------------------------------------------------------------
struct Ext {
    // 005802f0
    void  SaveMetadata();                    // 0x0057ea30
    char  IsVisible();                       // 0x005dc450
    void  SetInputBlocked(int);              // 0x005dd090
    void  EnableBasicEditorButtons(int, char);// 0x005de690
    int   SetFlag(char, int);                // 0x0067c420
    void  SaveModel(const void*, int);       // 0x0057f6c0
    void  SetOldModelName(void*);            // 0x005d6090
    void  AutoTest(int, int);                // 0x00676e90
    void  RemoveExportThumb(const void*);    // 0x005faec0
    // 00580700
    void  SetupThumbnailModelWorld(void*, int); // 0x00574da0
    void  Bounds(void*, int);                // 0x004ad550
    void  BoxInit(void*);                    // 0x004ad6f0
    float* PropGetFloat();                   // 0x0041ea70
    int*   PropGetInt();                     // 0x0041e990
    void   GetImageResource(int);            // 0x00576650
    char   AssignAutoRef(void*);             // 0x0057ee20
    // 005809a0
    void* DtSet(int);                        // 0x0092e3d0
    int   DtLo(int);                         // 0x0092df80
    // 00580cb0 / 00580df0 serializer helpers
    void* ctorA(void*, void*, void*, void*); // 0x00693cd0
    void* ctorB(void*, void*, void*, void*); // 0x00693d60
    void  SerInit();                         // 0x00692ea0
    void  SerStart(int);                     // 0x00692ec0
    void  SerEnd();                          // 0x00693900
    void  VarListCtor(void*, int, int);      // 0x00692f90
    void  VarListSerialize(void*);           // 0x00692900
    void  VarListRead(void*);                // 0x00693e10
    // 00580df0
    void  RangeInitialize(void*);            // 0x00579a90
    void  AllocateSelf(int);                 // 0x00429760
    void* DatabaseCtor(const wchar_t*, void*);// 0x008d9f80
    void* ObjectDbCtor(void*);               // 0x0069fa60
};

// ---------------------------------------------------------------------------
// cdecl callees
// ---------------------------------------------------------------------------
int  __cdecl WStr_Format(wchar_t* out, unsigned fmt, ...);              // 0x0041e050
void __cdecl GetPropertyAsText(void* list, unsigned id, void* out);     // 0x006a1360
extern "C" __declspec(dllimport) wchar_t* __cdecl wcsncpy(wchar_t*, const wchar_t*, size_t);
void* __cdecl opnew_f473a0(unsigned, const char*, int, int, int, int);  // 0x00f473a0
void  __cdecl opdel_f47380(void*);                                      // 0x00f47380
void  __cdecl DoInsertValue(void*, const void*, int);                   // 0x011e0744
unsigned __cdecl LookupByHash_572110(unsigned);                         // 0x00572110
void* __cdecl IDGenerator_67de60();                                     // 0x0067de60
void* __cdecl FUN_67cac0();                                             // 0x0067cac0
char  __cdecl GetEditorPropertyList_5bf0e0(const void*, void**);        // 0x005bf0e0
char  __cdecl GetPropertyAsKey_6a1250(void*, unsigned, void*);          // 0x006a1250
void* __cdecl SP_GetSaveArea_6b1f90(int);                               // 0x006b1f90
char  __cdecl SaveEditorPropertyList_5bf120(const void*, void*, int, void*); // 0x005bf120
void  __cdecl FUN_5bf3a0(const void*, void*, int, void*);               // 0x005bf3a0
char  __cdecl FUN_5bf610(void*, void*);                                 // 0x005bf610
void  __cdecl FUN_5942e0();                                             // 0x005942e0
void* __cdecl Achievements_Controller_675250(int);                      // 0x00675250
void* __cdecl FUN_5f7930(void*);                                        // 0x005f7930
void* __cdecl ObjectTemplateDB_67cb40();                                // 0x0067cb40
char  __cdecl GetPropertyAsVector2_6a10c0(void*, unsigned, void*);      // 0x006a10c0
void* __cdecl FUN_67ddb0();                                             // 0x0067ddb0
int   __cdecl Sprintf16_9399c0(wchar_t*, const wchar_t*, ...);          // 0x009399c0
void  __cdecl StrncpyUTF8ToUTF16_93cf10(wchar_t*, unsigned, const wchar_t*, int); // 0x0093cf10
int   __cdecl sprintf_char_472fe0(void*, const wchar_t*, wchar_t*);     // 0x00472fe0
void* __cdecl FUN_607a60();                                             // 0x00607a60 AuthManager
char  __cdecl MakeFileNameValid_931250(const wchar_t*, wchar_t*, int);  // 0x00931250
int   __cdecl Snprintf16_939a30(wchar_t*, unsigned, const wchar_t*, ...); // 0x00939a30
void* __cdecl FUN_688fa0(const wchar_t*);                               // 0x00688fa0
void  __cdecl WriteUint32_93aa70(void*, void*, int, int);               // 0x0093aa70
void  __cdecl ReadInt32_93a780(void*, void*, int, int);                 // 0x0093a780
void  __cdecl CommitFile_6891f0(void*, void*);                          // 0x006891f0
void* __cdecl memcpy_11e0744(void*, const void*, unsigned);             // 0x011e0744
void* __cdecl PathJoin_57cba0(void*, void*, void*);                     // 0x0057cba0
void  __cdecl assign_423650(void*, void*);                              // 0x00423650
char  __cdecl FileExists_931fa0(const wchar_t*);                        // 0x00931fa0
void* __cdecl ZoneObject_new_926020(int, const char*, int, int, int, int); // 0x00926020

// ---------------------------------------------------------------------------
// stub vtables for the objects called virtually (real virtual-call codegen)
// ---------------------------------------------------------------------------
struct PropList {                                   // mPropList object
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();                                  // 0x10
    virtual char v5(unsigned, void*);                   // 0x14
    virtual void v6(unsigned);                          // 0x18
    virtual char HasProperty(unsigned);                 // 0x1c
    virtual void s8();                                  // 0x20
    virtual char HasProp2(unsigned, void**);            // 0x24
    virtual void s10(); virtual void s11(); virtual void s12();
    virtual void v13(void*);                            // 0x34
};

struct IAuth {                                      // Pollen::AuthManager
    virtual void a0();  virtual void a1();  virtual void a2();  virtual void a3();
    virtual void a4();  virtual void a5();  virtual void a6();  virtual void a7();
    virtual void a8();                                  // 0x20
    virtual char IsOffline();                           // 0x24
    virtual void a10(); virtual void a11();
    virtual void* GetName();                            // 0x30
};

// ---------------------------------------------------------------------------
// the recovered cAppModeEditorBase (only the members used here are named)
// ---------------------------------------------------------------------------
struct cAppModeEditorBase_s0058_02f0 {
    char mPad0[0x24];
    void* mPropList;                                // +0x24
    char mPad1[0x1000 - 0x28];
    bool GetEditorName(string16* out);              // 0x005805e0
    bool GetDefaultModelName(string16* out);        // 0x00580670
    void Save(int param_2, int param_3);            // 0x005802f0
    void BuildThumb(int, int, int, int, int, int);  // 0x00580700
    void WriteEditorInfo();                         // 0x00580cb0
    void ReadEditorInfo();                          // 0x00580df0
};

// ---------------------------------------------------------------------------
// 0x005805e0  cAppModeEditorBase::GetEditorName(string16*)
// ---------------------------------------------------------------------------
// @ 0x005805e0
bool cAppModeEditorBase_s0058_02f0::GetEditorName(string16* out)
{
    PropList* list = (PropList*)this->mPropList;
    if (list != 0 && list->HasProperty(0x703e542f)) {
        SPcString s;
        s.Init();
        GetPropertyAsText(this->mPropList, 0x703e542f, &s);
        WStr_Format((wchar_t*)out, (unsigned)DAT_013f5b90, s.GetText());
        s.Dtor();
        return true;
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00580670  cAppModeEditorBase::GetDefaultModelName(string16*)
// ---------------------------------------------------------------------------
// @ 0x00580670
bool cAppModeEditorBase_s0058_02f0::GetDefaultModelName(string16* out)
{
    PropList* list = (PropList*)this->mPropList;
    if (list != 0 && list->HasProperty(0x4d92f82)) {
        SPcString s;
        s.Init();
        GetPropertyAsText(this->mPropList, 0x4d92f82, &s);
        WStr_Format((wchar_t*)out, (unsigned)DAT_013f5b90, s.GetText());
        out->trim();
        s.Dtor();
        return true;
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00580c10  editor user name -> wchar_t[256]
// ---------------------------------------------------------------------------
// @ 0x00580c10
void __cdecl FUN_00580c10(wchar_t* out)
{
    IAuth* auth = (IAuth*)FUN_607a60();
    if (auth->IsOffline()) {
        wcsncpy(out, DAT_013f5c44, 0x100);
        return;
    }
    string16 name;
    WStr_Format((wchar_t*)&name, (unsigned)DAT_013f5c24, *(int*)auth->GetName());
    MakeFileNameValid_931250(name.mpBegin, out, 4);
    if ((((int)name.mpCapacity - (int)name.mpBegin) & ~1) > 2 && name.mpBegin != 0)
        opdel_f47380(name.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x005802f0  cAppModeEditorBase::Save(bool, int)
// ---------------------------------------------------------------------------
struct ResKey { uint32_t mInstance; uint32_t mType; uint32_t mGroup; };

// @ 0x005802f0
void cAppModeEditorBase_s0058_02f0::Save(int param_2, int param_3)
{
    char* t = (char*)this;
    if (param_2 != 0 && *(char*)(t + 0x4b3) == 0) {
        int obj = *(int*)(t + 0x98);
        if (obj != 0 && *(int*)(obj + 0x10) != 0x2b978c46) {
            *(int*)(t + 0x1a4) = 0;
            ((Ext*)this)->SaveMetadata();
            return;
        }
    }

    int obj = *(int*)(t + 0x98);
    *(int*)(t + 0x388) = param_3;

    ResKey key;
    key.mInstance = *(uint32_t*)(obj + 0xc);
    key.mType     = *(uint32_t*)(obj + 0x10);
    key.mGroup    = *(uint32_t*)(obj + 0x14);

    unsigned hash = *(unsigned*)(t + 0x2a8);
    unsigned id = LookupByHash_572110(hash);
    void* idgen = IDGenerator_67de60();
    ResKey buf;
    buf.mInstance = 0; buf.mType = 0; buf.mGroup = 0;
    {
        typedef void (__thiscall *Fn)(void*, void*, unsigned, unsigned);
        (*(Fn)(*(char**)idgen + 8))(idgen, &buf, hash, id);
    }

    void* ui = *(void**)(t + 0x78);
    if (((Ext*)ui)->IsVisible()) {
        ((Ext*)ui)->SetInputBlocked(0);
        ((Ext*)ui)->EnableBasicEditorButtons(0, 1);
    }
    void* hints = FUN_67cac0();
    ((Ext*)hints)->SetFlag(0, 1);

    ((Ext*)this)->SaveModel(&key, 0);

    {
        int o2 = *(int*)(t + 0x98);
        typedef void* (__thiscall *Fn)(void*);
        void* mname = (*(Fn)(*(char**)o2 + 4))((void*)o2);
        ((Ext*)*(void**)0x15eebec)->SetOldModelName(mname);
    }

    buf.mInstance = 0; buf.mType = 0; buf.mGroup = 0;

    if (param_2 != 0) {
        void* plist = 0;
        if (GetEditorPropertyList_5bf0e0(&key, &plist)) {
            int* props = (int*)opnew_f473a0(0x38, kEditorPropListName, 0, 0, 0, 0);
            if (props != 0) {
                typedef void (__thiscall *CtorFn)(void*);
                ((CtorFn)(void*)0x006a1c40)(props);
                if (props != 0) {
                    typedef void (__thiscall *Fn)(void*);
                    (*(Fn)(*(char**)props))(props);              // vtbl[0]
                }
            }
            typedef void (__thiscall *Fn34)(void*, void*);
            (*(Fn34)(*(char**)props + 0x34))(props, plist);

            if (*(char*)(t + 0x4b9) != 0) {
                ResKey v;
                v.mInstance = 0; v.mType = 0; v.mGroup = 0;
                void* list = *(void**)(t + 0x24);
                typedef void (__thiscall *Fn14)(void*, unsigned, void*);
                (*(Fn14)(*(char**)list + 0x14))(list, 0xd8a4bc9, &v);
                {
                    void* sak = SP_GetSaveArea_6b1f90(*(int*)(t + 0x2ac));
                    SaveEditorPropertyList_5bf120(&key, sak, 0, 0);
                }
                typedef void (__thiscall *Fn18)(void*, unsigned);
                (*(Fn18)(*(char**)props + 0x18))(props, 0xd8a4bc9);
            }

            int* sub = *(int**)(t + 0x3bc);
            void* e = sub ? *(void**)((char*)sub + 0x30) : 0;
            if (e != 0 && *(int*)((char*)e + 0x10) != 0) {
                FUN_5942e0();
                FUN_5bf610(props, *(void**)((char*)e + 0x10));
            }
            {
                void* sak = SP_GetSaveArea_6b1f90(*(int*)(t + 0x2ac));
                SaveEditorPropertyList_5bf120(&key, props, 0, sak);
            }
            typedef void (__thiscall *Fn4)(void*);
            (*(Fn4)(*(char**)props + 4))(props);
        } else {
            goto lab_580510;
        }
    } else {
lab_580510:
        int* launch = *(int**)(t + 0x1cc);
        if (*(int*)((char*)launch + 0x84) != 0) {
            void* sak = SP_GetSaveArea_6b1f90(*(int*)(t + 0x2ac));
            FUN_5bf3a0(&key, (char*)launch + 0x84, 0, sak);
        } else {
            ResKey k2;
            k2.mInstance = 0; k2.mType = 0; k2.mGroup = 0;
            if (!GetPropertyAsKey_6a1250(*(void**)(t + 0x24), 0x1b814928, &k2))
                goto lab_580574;
            void* sak = SP_GetSaveArea_6b1f90(*(int*)(t + 0x2ac));
            FUN_5bf3a0(&key, &k2, 0, sak);
        }
    }

lab_580574:
    if (param_2 == 0) {
        if (*(int*)(t + 0x18c) == 0xa56567f7) {
            void* c = Achievements_Controller_675250(0x42df8d08);
            ((Ext*)c)->AutoTest(1, 0x42df8d08);
        }
    } else {
        ResKey kk;
        kk.mInstance = 0; kk.mType = 0; kk.mGroup = 0;
        void* r = FUN_5f7930(&kk);
        ((Ext*)r)->RemoveExportThumb(&kk);
        int* tdb = (int*)ObjectTemplateDB_67cb40();
        typedef void (__thiscall *Fn74)(void*, void*, int);
        (*(Fn74)(*(char**)tdb + 0x74))(tdb, &kk, 1);
    }
    if (param_3 != 0) {
        typedef void (__thiscall *Fn)(void*);
        (*(Fn)(*(char**)(void*)param_3 + 4))((void*)param_3);
    }
}

// ---------------------------------------------------------------------------
// 0x00580700  build a thumbnail/icon descriptor and hand it to the UI
// ---------------------------------------------------------------------------
// @ 0x00580700
void cAppModeEditorBase_s0058_02f0::BuildThumb(int a1, int a2, int a3, int a4, int a5, int a6)
{
    char* t = (char*)this;
    if (a1 == 0)
        return;

    ((Ext*)this)->SetupThumbnailModelWorld((void*)a2, 1);

    float box[6];
    ((Ext*)(void*)a1)->Bounds(box, 0);

    float uv[2];
    uv[0] = 0.0f; uv[1] = 0.0f;
    GetPropertyAsVector2_6a10c0(*(void**)(t + 0x24), 0x5e2eaac, uv);

    int f48 = 0, f44 = 0, f5c = 0;
    void* prop;

    void* list = *(void**)(t + 0x24);
    if (list != 0) {
        prop = 0;
        typedef char (__thiscall *Fn)(void*, unsigned, void*);
        if ((*(Fn)(*(char**)list + 0x24))(list, 0x5e301ef, &prop) &&
            prop != 0 && *(uint16_t*)((char*)prop + 0x12) == 0xd)
            f48 = *(int*)((Ext*)prop)->PropGetFloat();
    }
    list = *(void**)(t + 0x24);
    if (list != 0) {
        prop = 0;
        typedef char (__thiscall *Fn)(void*, unsigned, void*);
        if ((*(Fn)(*(char**)list + 0x24))(list, 0x5e303c5, &prop) &&
            prop != 0 && *(uint16_t*)((char*)prop + 0x12) == 0xd)
            f44 = *(int*)((Ext*)prop)->PropGetFloat();
    }
    list = *(void**)(t + 0x24);
    if (list != 0) {
        prop = 0;
        typedef char (__thiscall *Fn)(void*, unsigned, void*);
        if ((*(Fn)(*(char**)list + 0x24))(list, 0x5e30434, &prop) &&
            prop != 0 && *(uint16_t*)((char*)prop + 0x12) == 0xd)
            f5c = *(int*)((Ext*)prop)->PropGetFloat();
    }

    int* pi = (int*)opnew_f473a0(0x54, kEditorAllocName, 0, 0, 0, 0);
    if (pi != 0) {
        pi[1] = 0;
        pi[0] = 0x013f5874;
        pi[5] = 0;
        pi[10] = 0;
        pi[11] = 0;
        pi[12] = 0;
        typedef void (__thiscall *Fn4)(void*);
        (*(Fn4)(*(char**)pi + 4))(pi);
    } else {
        pi = 0;
    }

    int box2[3];
    box2[0] = 0; box2[1] = 0; box2[2] = 0;
    ((Ext*)(void*)a1)->BoxInit(box2);

    pi[2] = a3;
    pi[4] = a5;
    pi[3] = a4;

    ((Ext*)((char*)pi + 0x14))->GetImageResource(a6);
    ((Ext*)((char*)pi + 0x28))->AssignAutoRef(box2);

    float mx = (box[2] + box[0]) * 0.5f;
    float my = (box[4] + box[1]) * 0.5f;
    float mz = (box[5] + box[3]) * 0.5f;
    pi[6] = *(int*)&mx;
    pi[7] = *(int*)&my;
    pi[8] = *(int*)&mz;
    pi[9] = *(int*)(t + 0x2b8);
    pi[0x10] = *(int*)&uv[0];
    pi[0x11] = *(int*)&uv[1];
    pi[0x12] = f48;
    pi[0x13] = f5c;
    pi[0x14] = f44;

    int typ = a2;
    list = *(void**)(t + 0x24);
    if (list != 0) {
        prop = 0;
        typedef char (__thiscall *Fn)(void*, unsigned, void*);
        if ((*(Fn)(*(char**)list + 0x24))(list, 0x5d5fc14, &prop) &&
            prop != 0 && *(uint16_t*)((char*)prop + 0x12) == 9)
            typ = *(int*)((Ext*)prop)->PropGetInt();
    }
    if (typ == 0)
        pi[0xf] = 6;
    else if (typ == 1)
        pi[0xf] = 7;
    else if (typ == 2)
        pi[0xf] = 8;

    int* mgr = (int*)FUN_67ddb0();
    typedef void (__thiscall *Fn20)(void*, int, void*);
    (*(Fn20)(*(char**)mgr + 0x20))(mgr, a2, pi);

    if (box2[2] != 0 && *(int*)(box2[2] - 4) != 0)
        opdel_f47380((void*)box2[2]);

    typedef void (__thiscall *Fn8)(void*);
    (*(Fn8)(*(char**)pi + 8))(pi);
}

// ---------------------------------------------------------------------------
// 0x005809a0  capture a GIF name/serial for the editor save
// ---------------------------------------------------------------------------
// @ 0x005809a0
void __stdcall FUN_005809a0(void* arg)
{
    string16 a, b, c, d, e;

    WStr_Format((wchar_t*)&a, (unsigned)DAT_013f5c04, DAT_013f5c0c);
    *(void**)(*(int*)0x15eebec + 0x3c) = a.mpBegin;

    struct DT { __int64 v; } dt;
    dt.v = 0;
    ((Ext*)&dt)->DtSet(2);

    WStr_Format((wchar_t*)&b, (unsigned)DAT_013f5bf8, ((Ext*)&dt)->DtLo(1));
    *(void**)(*(int*)0x15eebec + 0x2c) = b.mpBegin;

    WStr_Format((wchar_t*)&c, (unsigned)DAT_013f5bec, ((Ext*)&dt)->DtLo(2));
    *(void**)(*(int*)0x15eebec + 0x30) = c.mpBegin;

    WStr_Format((wchar_t*)&d, (unsigned)DAT_013f5bec, ((Ext*)&dt)->DtLo(6));
    *(void**)(*(int*)0x15eebec + 0x34) = d.mpBegin;

    {
        int p10 = ((Ext*)&dt)->DtLo(10);
        int p9  = ((Ext*)&dt)->DtLo(9);
        int p8  = ((Ext*)&dt)->DtLo(8);
        WStr_Format((wchar_t*)&e, (unsigned)DAT_013f5bcc, p8, p9, p10);
    }
    *(void**)(*(int*)0x15eebec + 0x38) = e.mpBegin;

    SPcString s;
    s.Init();
    s.Load(0x7518573e, 0x5dc1fd4, (int)DAT_013f5b9c);

    wchar_t buf[0x104];
    Sprintf16_9399c0(buf, DAT_013f5c04, s.GetText());

    wchar_t out[0x104];
    StrncpyUTF8ToUTF16_93cf10(out, 0x104, buf, -1);

    sprintf_char_472fe0(arg, DAT_013f5b98, out);
    s.Dtor();

    if ((((int)e.mpCapacity - (int)e.mpBegin) & ~1) > 2 && e.mpBegin != 0) opdel_f47380(e.mpBegin);
    if ((((int)d.mpCapacity - (int)d.mpBegin) & ~1) > 2 && d.mpBegin != 0) opdel_f47380(d.mpBegin);
    if ((((int)c.mpCapacity - (int)c.mpBegin) & ~1) > 2 && c.mpBegin != 0) opdel_f47380(c.mpBegin);
    if ((((int)b.mpCapacity - (int)b.mpBegin) & ~1) > 2 && b.mpBegin != 0) opdel_f47380(b.mpBegin);
    if ((((int)a.mpCapacity - (int)a.mpBegin) & ~1) > 2 && a.mpBegin != 0) opdel_f47380(a.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x00580cb0  write the editor info database to the FTP job
// ---------------------------------------------------------------------------
// @ 0x00580cb0
void cAppModeEditorBase_s0058_02f0::WriteEditorInfo()
{
    wchar_t namebuf[0x100];
    wchar_t tmpname[0x100];
    wchar_t dbname[0x100];
    FUN_00580c10(namebuf);
    Snprintf16_939a30(tmpname, 0x100, DAT_013f5c74, namebuf);
    Snprintf16_939a30(dbname, 0x100, DAT_013f5c68, namebuf);

    void* job = FUN_688fa0(tmpname);
    if (job != 0) {
        typedef void (__thiscall *Fn0)(void*);
        (*(Fn0)(*(char**)job))(job);
        char c3[0x40];
        ((Ext*)c3)->ctorB(job, g_1897c18, g_1897c18, g_1897c18);
        ((Ext*)c3)->SerInit();
        void* gen = *(void**)(c3 + 8);
        void* s = (*(void* (__thiscall*)(void*))(*(char**)gen + 0x20))(gen);
        void* h = (*(void* (__thiscall*)(void*))(*(char**)s + 0x18))(s);
        int one = 1;
        WriteUint32_93aa70(h, &one, 1, 0);
        char ser[0x40];
        ((Ext*)ser)->VarListCtor(this, 0x150d100, 0x1a80d26);
        ((Ext*)ser)->VarListSerialize(gen);
        ((Ext*)c3)->SerEnd();
        (*(void (__thiscall*)(void*))(*(char**)((char*)job + 4) + 0x1c))((char*)job + 4);
        (*(void (__thiscall*)(void*))(*(char**)((char*)job + 4) + 8))((char*)job + 4);
    }
    CommitFile_6891f0(tmpname, dbname);
    (*(void (__thiscall*)(void*))(*(char**)job + 4))(job);
}

// ---------------------------------------------------------------------------
// 0x00580df0  read the editor info database back
// ---------------------------------------------------------------------------
// @ 0x00580df0
void cAppModeEditorBase_s0058_02f0::ReadEditorInfo()
{
    wchar_t namebuf[0x100];
    wchar_t dbname[0x80];
    FUN_00580c10(namebuf);
    Snprintf16_939a30(dbname, 0x80, DAT_013f5c68, namebuf);

    int* area = (int*)SP_GetSaveArea_6b1f90(0x4729a47);
    void* s28 = (*(void* (__thiscall*)(void*))(*(char**)area + 0x28))(area);

    string16 full;
    full.mpBegin = 0; full.mpEnd = 0; full.mpCapacity = 0;
    ((Ext*)&full)->RangeInitialize(s28);

    int n = (int)(full.mpEnd - full.mpBegin);
    string16 base;
    base.mpBegin = 0; base.mpEnd = 0; base.mpCapacity = 0;
    ((Ext*)&base)->AllocateSelf(n + 1);
    memcpy_11e0744(base.mpBegin, full.mpBegin, n * 2);
    base.mpEnd = (wchar_t*)((char*)base.mpBegin + n * 2);
    *base.mpEnd = 0;

    string16 joined;
    joined.mpBegin = 0; joined.mpEnd = 0; joined.mpCapacity = 0;
    void* r = PathJoin_57cba0(&joined, &base, dbname);
    if (r != &base)
        assign_423650(*(void**)r, ((void**)r)[1]);

    if ((((int)joined.mpCapacity - (int)joined.mpBegin) & ~1) > 2 && joined.mpBegin != 0)
        opdel_f47380(joined.mpBegin);

    if (FileExists_931fa0(base.mpBegin)) {
        void* dpf = (void*)ZoneObject_new_926020(0x388, kSimulatorAllocName, 0, 0, 0, 0);
        if (dpf != 0) {
            dpf = (void*)((Ext*)dpf)->DatabaseCtor(0, 0);
            if (dpf != 0)
                (*(void (__thiscall*)(void*))(*(char**)((char*)dpf + 4)))((char*)dpf + 4);
        }
        void* odb = (void*)ZoneObject_new_926020(0x24, kSimulatorAllocName, 0, 0, 0, 0);
        if (odb != 0) {
            odb = (void*)((Ext*)odb)->ObjectDbCtor(dpf);
            if (odb != 0)
                (*(void (__thiscall*)(void*))(*(char**)odb))(odb);
        }
        void* esi = (char*)odb + 4;
        (*(void (__thiscall*)(void*))(*(char**)esi + 4))(esi);
        (*(void (__thiscall*)(void*, void*))(*(char**)esi + 0x2c))(esi, base.mpBegin);
        (*(void (__thiscall*)(void*, int, int, int))(*(char**)esi + 0x18))(esi, 1, 0, 0);
        char c3[0x40];
        ((Ext*)c3)->ctorA(odb, g_1897c18, g_1897c18, g_1897c18);
        ((Ext*)c3)->SerInit();
        void* gen = *(void**)(c3 + 8);
        void* s = (*(void* (__thiscall*)(void*))(*(char**)gen + 0x20))(gen);
        void* h = (*(void* (__thiscall*)(void*))(*(char**)s + 0x18))(s);
        int val = 0;
        ReadInt32_93a780(h, &val, 1, 0);
        ((Ext*)c3)->SerStart(val);
        char ser[0x40];
        ((Ext*)ser)->VarListCtor(this, 0x150d100, 0x1a80d26);
        ((Ext*)ser)->VarListRead(gen);
        ((Ext*)c3)->SerEnd();
        (*(void (__thiscall*)(void*))(*(char**)esi + 0x1c))(esi);
        (*(void (__thiscall*)(void*))(*(char**)esi + 8))(esi);
        (*(void (__thiscall*)(void*))(*(char**)odb + 4))(odb);
        if (dpf != 0)
            (*(void (__thiscall*)(void*))(*(char**)((char*)dpf + 4) + 4))((char*)dpf + 4);
    }

    if ((((int)base.mpCapacity - (int)base.mpBegin) & ~1) > 2 && base.mpBegin != 0)
        opdel_f47380(base.mpBegin);
    if ((((int)full.mpCapacity - (int)full.mpBegin) & ~1) > 2 && full.mpBegin != 0)
        opdel_f47380(full.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x005810a0  cBoolVec::EraseAll
// ---------------------------------------------------------------------------
struct cBoolVec {
    void* mpBegin;
    void* mpEnd;
    void EraseAll();
};

// @ 0x005810a0
void cBoolVec::EraseAll()
{
    void* begin = mpBegin;
    void* end = mpEnd;
    DoInsertValue(begin, end, 0);
    mpEnd = (char*)mpEnd + (((int)end - (int)begin) >> 2) * -4;
}