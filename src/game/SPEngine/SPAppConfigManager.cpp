// src/game/SPEngine/SPAppConfigManager.cpp -- migrated from slice(s) s007cd6d0, s007ce500, s007cc5f0, s007cb590, s007ca950, s007c9910, s007c8940, s007c77e0, s005409d0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppConfigManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned short gCfgDateTable[];  // @ 0x13f3a00
extern unsigned short gCfgTime12[];     // @ 0x13f39e4
extern unsigned short gCfgTime24[];     // @ 0x13f39dc
#include <ctype.h>
#include <stdio.h>
#include <wchar.h>
#include "EA/ArgScript/cIFileParser.h"
#include "SP/cConfigManager.h"
#include "SP/cConfigScriptState.h"
#include "SP/cOption.h"
#include "SP/cDirectPropertyList.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cError.h"
#include "EA/Variant.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPropertyList.h"
#include <string.h>
#include "rw/graphics/Device.h"
#include "EA/ArgScript/cIParser.h"

// ---- items of slice s005409d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
int   FUN_00454d50(const void* table, int start, int end);     // @ 0x454d50
void  FUN_0092e200(int a, int b, int c, unsigned d, unsigned e, int f); // @ 0x92e200
void  FUN_0092e470(int a, int b);                    // @ 0x92e470
void  EADateTime_Set(int a);                         // EA::DateTime::Set
extern unsigned short gCfgDateTable[];  // @ 0x13f3a00
extern unsigned short gCfgTime12[];     // @ 0x13f39e4
extern unsigned short gCfgTime24[];     // @ 0x13f39dc
// ---- items of slice s005409d0 end

// ---- items of slice s007c77e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char  g_saveAreaName[];  // 0x011ac192
extern void* g_sAppPreferences;             // 0x015fd91c
extern void* g_CmdKey_setting;              // 0x0153d204
extern void* g_CmdKey_boolProp;             // 0x0153d208
extern void* g_CmdKey_intProp;              // 0x0153d20c
extern void* g_CmdKey_floatProp;            // 0x0153d210
extern void* g_CmdKey_keyProp;              // 0x0153d214
extern void* g_CmdKey_props;                // 0x0153d218
extern void* g_CmdKey_option;               // 0x0153d200
extern void* g_CmdKey_vendor;               // 0x0153d22c
extern void* g_CmdKey_setVariables;         // 0x0153d1ec
extern void* g_CmdKey_setOption;            // 0x0153d21c
extern void* g_CmdKey_alert;                // 0x0153d220
extern void* g_CmdKey_setResolution;        // 0x0153d224
extern void* g_CmdKey_boolProp2;            // 0x0153d1f0
extern void* g_CmdKey_intProp2;             // 0x0153d1f4
extern void* g_CmdKey_floatProp2;           // 0x0153d1f8
extern void* g_CmdKey_keyProp2;             // 0x0153d1fc
extern void* g_CmdKey_card;                 // 0x0153d228
void*    __cdecl EA_New(unsigned size, const char* name, int, int, const char*, int); // 0x00f473a0
void     __cdecl EA_Free(void* p);                                               // 0x00f47380
void*    __cdecl CreateParser();                                                 // 0x008408d0
void*    __cdecl CheatManager();                                                 // 0x0067de20
void*    __cdecl GetSaveArea(const char* name);                                  // 0x006b1f90
bool     __cdecl SaveResource(void* res, void* area, int flags);                 // 0x006b1d50
void*    __cdecl FormatString(int idx, const char* fmt, const char* arg);        // 0x00840810
void     __cdecl FormatDouble(double v, char* out, int len, int prec, int flags);// 0x0092d730
void*    __cdecl DesktopDisplayMode(void* out);                                  // 0x011f8270
int      __cdecl TryGetUIntProperty(void* prop, unsigned key, uint32_t* out);    // 0x00410370
void     __cdecl RegisterConfigScriptCommands(void* parser);                     // 0x007c8530
typedef void (__thiscall *VFn0)(void*);
typedef void (__thiscall *VFn1)(void*, void*);
typedef void (__thiscall *VFn2P)(void*, void*, void*);
typedef void (__thiscall *VFn2)(void*, int, int);
typedef void* (__thiscall *VFnR)(void*);
#define VSLOT(obj, byteoff) (*(void***)(obj))[(byteoff) / 4]
inline void* operator new(size_t size, const char* pName, int flags, unsigned dbg, const char* file, int line)
{ return EA_New((unsigned)size, pName, flags, (int)dbg, file, line); }
struct RC { virtual void AddRef(); virtual void Release(); };  // refcount interface
struct AutoRefCount {
    uint32_t m0;
    uint32_t m4;
    RC*      mRC;
    uint32_t mPad;
};
struct String16 { char* mpBegin; char* mpEnd; char* mpCap; int mAlloc; };
struct cOption {
    uint32_t mID;            // +0x00
    uint32_t mDefault;       // +0x04
    uint32_t mCurrent;       // +0x08
    uint8_t* mResBegin;      // +0x0c
    uint8_t* mResEnd;        // +0x10
    char pad14[0xac - 0x14];
};
struct cConfigScriptState {
    char pad00[0x44];
    cOption* mOptionsBegin;     // +0x44
    cOption* mOptionsEnd;       // +0x48
    char pad4c[0x60 - 0x4c];
    String16* mConfigStrings;   // +0x60
    char pad64[0x74 - 0x64];
    float*   mConfigNumbers;    // +0x74

    bool SetOptionDefault(uint32_t id, uint32_t value);  // 0x007c7ac0
    void DumpAll(void* args);                            // 0x007c7b30
};
struct cConfigManager {
    char pad0[0xc];
    RC*  mFileParser;           // +0x0c
    void* mScriptParser;        // +0x10
    char pad14[0x20 - 0x14];
    cConfigScriptState mState;  // +0x20

    int  GetOption(uint32_t id);                                  // 0x007c7c40
    int  GetOptionDefault(uint32_t id);                           // 0x007c7c70
    int  GetNumScreenResolutions();                               // 0x007c7ca0
    bool GetScreenResolutionInfo(int i, uint32_t*, uint32_t*, uint32_t*); // 0x007c7cd0
    bool SavePreferences();                                       // 0x007c7a10
    bool Shutdown();                                              // 0x007c7be0
    void SetScriptPath(const void* a, const void* b);             // 0x007c8880
};
struct cOptionCheat {
    const char* Description(int which);     // 0x007c7aa0
};
struct cOptionBlockCommand {
    char pad0[0x30];
    cConfigScriptState* mState;     // +0x30
    void OnEndBlock(int);           // 0x007c7e70
    void OnRegister(void*, void*);  // 0x007c8270
};
struct cVendorCommand {
    char pad0[0x30];
    cConfigScriptState* mState;     // +0x30
    void OnRegister(void*, void*);  // 0x007c84a0
};
struct AutoRefVec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCap;        // +0x08
    char   pad0C[4];
    void*  mInline[4];   // +0x10
    void Destroy();
};
struct cCmdArgs {
    char pad0[4];
    void* mArg;                     // +0x04
    char pad8[4];
    cConfigScriptState* mState;     // +0x0c
    void Do(int);                   // 0x007c7eb0
};
struct CmdBase  { CmdBase();  virtual void Execute(); char pad[0x0c]; };   // 0x10 with vptr
struct BlockBase { BlockBase(); virtual void Execute(); char pad[0x30]; }; // 0x34 with vptr
struct CmdOptionSetting       : CmdBase { virtual void Execute(); };
struct CmdOptionBoolProperty  : CmdBase { virtual void Execute(); };
struct CmdOptionIntProperty   : CmdBase { virtual void Execute(); };
struct CmdOptionFloatProperty : CmdBase { virtual void Execute(); };
struct CmdOptionKeyProperty   : CmdBase { virtual void Execute(); };
struct CmdOptionProperties    : CmdBase { virtual void Execute(); };
struct CmdCard                : CmdBase { virtual void Execute(); };
struct CmdSetVariables        : CmdBase { virtual void Execute(); };
struct CmdSetOption           : CmdBase { virtual void Execute(); };
struct CmdAlert               : CmdBase { virtual void Execute(); };
struct CmdSetResolution       : CmdBase { virtual void Execute(); };
struct CmdBoolProperty        : CmdBase { virtual void Execute(); };
struct CmdIntProperty         : CmdBase { virtual void Execute(); };
struct CmdFloatProperty       : CmdBase { virtual void Execute(); };
struct CmdKeyProperty         : CmdBase { virtual void Execute(); };
struct CmdOptionBlock         : BlockBase { virtual void Execute(); };
struct CmdVendor              : BlockBase { virtual void Execute(); };
typedef void (__thiscall* Fn_0083c780)(void* self, void* a, void* b);   // 0x0083c780 cCommandBase::OnRegister
void __cdecl FUN_0083c780();
// ---- items of slice s007c77e0 end

// ---- items of slice s007c8940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_Cheat_isCardFound;              // 0x0153d1e4
extern void* g_Cheat_cardName;                 // 0x0153d1e0
extern void* g_Cheat_cardVendor;               // 0x0153d1dc
void*    __cdecl PropertyManager();     // 0x0067de30
void*    __cdecl CreateFileParser_s007c_8940();    // 0x00840940
int      __cdecl Output(void* stream, const char* fmt, ...);  // 0x00841000
void     __cdecl DoAlert(void* a, void* b, void* c, void* d); // 0x006bb1c0
__declspec(dllimport) int __cdecl isdigit(int c);                       // IAT 0x13cc4cc
__declspec(dllimport) unsigned long __cdecl strtoul(const char*, char**, int); // IAT 0x13cc4f8
typedef int   (__thiscall *VFnI1)(void*, void*);
typedef int   (__thiscall *VFnI2)(void*, void*, void*);
typedef bool  (__thiscall *VFnB1)(void*, void*);
typedef bool  (__thiscall *VFnIP)(void*, const char*, void*);
typedef float (__thiscall *VFnF1)(void*, void*);
#define VSLOT_s007c_8940(obj, off) (*(void***)(obj))[(off) / 4]
struct DirectPropertyList;
extern DirectPropertyList* g_sAppProperties;   // 0x015fd918
struct Str16 { char* a; char* b; char* c; char* d; void assign(const char*, const char*); };
struct cError { Str16 mMessage; cError(const char* fmt, ...); cError(const cError&); };
struct DirectPropertyList {
    void SetBoolProperty(int id, bool v);          // 0x006a17e0
    void SetIntProperty(int id, int v);            // 0x006a1880
    void SetFloatProperty(int id, float v);        // 0x006a1910
};
struct cArguments {
    void* MainArguments(int n);                    // 0x00838320
    void  MainArguments(void* out, int a, int b);  // 0x00838020
    bool  HasFlag(const char* f);                  // 0x008380b0
    int   NumArguments();                          // 0x00837f30
    void* OptionArguments(const char* o, int n);   // 0x00838330
};
struct cOption_s007c_8940 {
    uint32_t id;
    uint32_t def;
    uint32_t cur;
    uint8_t* resBegin;
    uint8_t* resEnd;
    char     pad[0xac - 0x14];
};
struct cConfigManager_s007c_8940 {
    char pad00[0x64];
    cOption_s007c_8940* mOptionsBegin;   // +0x64
    cOption_s007c_8940* mOptionsEnd;     // +0x68
    char pad6c[0x80 - 0x6c];
    Str16* mStrings;          // +0x80
    Str16* mStringsEnd;       // +0x84

    void ApplyOption(cOption_s007c_8940* opt);                  // 0x007c8940
    void SetOption(int id, unsigned setting);        // 0x007c94f0
    void ResetToDefaults();                          // 0x007c95d0
    void ApplyAllOptions();                          // 0x007c9680
    bool GetConfigString(unsigned i, Str16* out);    // 0x007c9760
};
struct cConfigScriptState_s007c_8940 {
    char pad0[4];
    bool SetOptionDefault(int id, unsigned v);       // 0x007c7ac0
};
struct CCmd {
    char pad0[4];
    void* mParser;      // +0x04
    char pad8[4];
    void* mState;       // +0x0c
};
struct cBoolPropertyCommand : CCmd { void Execute(cArguments*); };
struct cIntPropertyCommand  : CCmd { void Execute(cArguments*); };
struct cFloatPropertyCommand: CCmd { void Execute(cArguments*); };
struct cSetOptionCommand    : CCmd { void Execute(cArguments*); };
int __cdecl GetPropID(const char* name);              // 0x007c8bb0
void* __cdecl CopyStrings(void* first, void* last, void* dest); // 0x007c8b70
struct StateView {
    char   pad0[8];
    uint32_t id;         // +0x08
    char   padC;
    bool   flagD;        // +0x0d
    char   padE[2];
    void*  vecBegin;     // +0x10
    void*  vecEnd;       // +0x14
    char   pad18[0x20 - 0x18];
    Str16  str20;        // +0x20
    Str16  str30;        // +0x30
    bool   f40;          // +0x40
    bool   f41;          // +0x41
    bool   f42;          // +0x42
    bool   f43;          // +0x43
};
struct ArgList { int count; void* a[4]; };
struct cAlertCommand : CCmd { void Execute(cArguments*); };
struct cOptionCheat_s007c_8940  : CCmd {
    char pad10[4];
    cConfigManager_s007c_8940* mManager;
    void Execute(cArguments*);  // 0x007c9120 (cOptionCheat::Execute)
};
struct cCardCommand  : CCmd { void Execute(cArguments*); };
struct cUnknownCmd   : CCmd { void Execute(cArguments*); };
struct cInitCommand  : CCmd { char pad10[4]; cConfigManager_s007c_8940* mManager; void Execute(cArguments*); void Init(); };
void cInitCommand::Execute(cArguments*)
{
    Init();
}
// ---- items of slice s007c8940 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* __cdecl InsertAutoRef(void* out, void* src);  // 0x007c8af0 (stays in the slice: not this object's)

// ---- items of slice s007c9910 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyString[2];                        // 0x01667bac
#pragma intrinsic(strlen)
void* __cdecl VecDoInsertValue(void);                // 0x011e0744
void* __cdecl VecAllocGrow(int n, void*, void*);     // 0x007c98b0
void  __cdecl VecDestroyRange16(void*, void*);       // 0x00b007f0
void* __cdecl VecCopyImpl(void*, void*, void*);      // 0x006782c0
void  __cdecl VecUninitCopy(void*, void*, void*, void*, void*); // 0x007c7d70
void* __cdecl VecCopyRange(void*, void*, void*);      // 0x007c7e10
void  __cdecl UIntVecPushSlow(void*, unsigned*);     // 0x004558a0
struct AutoRef { uint32_t m0; uint32_t m4; RC* mRC; uint32_t mPad; };
struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void reserve(unsigned n);
    void push_back(uint32_t v) {
        if (mpEnd < mpCap) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            UIntVecPushSlow(this, &v);
        }
    }
};
struct AutoRefVec_s007c_9910 {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCap;
    AutoRef  mInline[4];
    void DoAssignFromIterator(AutoRef* first, AutoRef* last);  // 0x007c9fa0
    void InsertOne(AutoRef* pos, AutoRef* value);              // 0x007c9dc0
};
struct Pair16 { uint64_t key; uint32_t mRC; uint32_t mPad; };  // 16-byte vector element (retail strides by 0x10)
struct PairVec {
    Pair16* mpBegin;
    Pair16* mpEnd;
    Pair16* mpCap;
    PairVec& operator=(const PairVec&);                        // 0x007ca060
    void  DestroyRange(Pair16* first, Pair16* last);           // 0x007c8130
    void* Reserve(int n, Pair16* first, Pair16* last);         // 0x007c8210
};
struct Vec4 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void InsertOne(uint32_t* pos, uint32_t* value);            // 0x007c99e0
    void InsertN(uint32_t* pos, int n, uint32_t* value);       // 0x007c9bc0
};
struct MapVec {                                                // 0x007ca8e0
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void Destroy();
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct Property {                                   // 0x14 bytes (ModAPI App::Property)
    uint32_t d0, d1, d2, d3;
    int16_t  flags;                                 // +0x10 (bit 2: owns data)
    uint16_t type;                                  // +0x12
    Property() : flags(0), type(0) {}
    ~Property() { if (flags & 4) Clear(false); }
    void Set(int type, int flags, const void* data, int itemSize, int count);   // 0x0093dd80
    void Clear(bool b);                                                         // 0x0093db80
    void SetKey(const ResourceKey& k) { d0 = k.instanceID; d1 = k.typeID; d2 = k.groupID; type = 0x20; }
};
struct PropList : RC {                              // App::PropertyList (Editor::cPropertyList)
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void SetProperty(uint32_t id, const Property* p);                   // +0x14
    char pad04[0x08 - 0x04];
    ResourceKey mKey;                               // +0x08
};
struct cPropertyList : PropList {
    char pad14[0x38 - 0x14];
    cPropertyList();                                // 0x006a1c40
};
struct IParser : RC {
virtual void v2();
virtual void v3();
    virtual void AddState(void* p);                 // +0x10
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void Reset(int a, int b);               // +0x24
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
    virtual void SetFlags(int v);                   // +0xbc
};
struct IFileParser : RC {
virtual void v2();
virtual void v3();
    virtual void SetParser(IParser* p);             // +0x10
    virtual void v5();
    virtual void Begin();                           // +0x18
    virtual void SetPath(const char* path, int mode);   // +0x1c
    virtual bool Run();                             // +0x20
};
IFileParser* __cdecl CreateFileParser();            // 0x00840940
IParser*     __cdecl CreateParser_s007c_9910();                // 0x008408d0
struct IResAreaMgr {                                // vtable +0x20 used to register a property list
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void Register(PropList* pl, int a, void* area, int b, int c);       // +0x20
};
struct ICheatSub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
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
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
                   virtual void v48();
                   virtual int GetValue(); };                                     // +0xc4
struct ICheat { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
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
                virtual ICheatSub* GetSub(); };                                   // +0x38
ICheat*       __cdecl GetCheatManager();            // 0x0067de20
IResAreaMgr*  __cdecl GetResMgr();                  // 0x0067dcd0
void*         __cdecl GetSaveArea(uint32_t id);       // 0x006b1f90
struct EaString {
    char* mpBegin; char* mpEnd; char* mpCap;
    EaString() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCap(gEmptyString + 1) {}
    ~EaString() { if (mpCap - mpBegin > 1 && mpBegin) EA_Free(mpBegin); }
    void assign(const char* b, const char* e);       // 0x00454cb0
    void append(const char* b, const char* e);       // 0x00455d60
};
struct SpUIntVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    SpUIntVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~SpUIntVec() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EA_Free(mpBegin); }
    void DoInsertValue(uint32_t* pos, const uint32_t& v);                  // 0x004558a0
    void push_back(const uint32_t& v) {
        if (mpEnd < mpCap) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
struct MapElem {                                    // vector_map<u64, PropertyListPtr> element, 0x18 bytes
    struct Entry { uint32_t a, b; PropList* pl; uint32_t pad; };
    Entry* mpBegin; Entry* mpEnd;
    char pad[0x10];
};
struct cOption_s007c_9910 {
    uint32_t id; uint32_t def; uint32_t cur;
    PropList** resBegin;                            // +0x0c fixed_vector<PropertyListPtr,4>
    PropList** resEnd;                              // +0x10
    char pad14[0x34 - 0x14];
    MapElem* mapBegin;                              // +0x34 fixed_vector<vector_map<..>,4>
    MapElem* mapEnd;                                // +0x38
    char pad3c[0xac - 0x3c];
};
struct cConfigManager_s007c_9910 {
    char pad00[0x0c];
    IFileParser* mFileParser; // +0x0c
    IParser* mParser;         // +0x10
    char pad14[0x20 - 0x14];
    char mState[0x44];        // +0x20
    cOption_s007c_9910* mOptionsBegin;   // +0x64
    cOption_s007c_9910* mOptionsEnd;     // +0x68
    char pad6c[0x80 - 0x6c];
    void* mStrings;           // +0x80
    void* mStringsEnd;        // +0x84

    void GetOptionIDs(UIntVec* out);          // 0x007ca150
    void Initialize(const char* path);        // 0x007ca1c0
};
// ---- items of slice s007c9910 end

// ---- items of slice s007ca950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" bool __cdecl SPKeyFromName(void* pOutKey, const wchar_t* pName, int a, int b);  // 0x0068d5a0
#ifndef SPORE_S007CA950_H
#endif  // SPORE_S007CA950_H
typedef unsigned int uint32;
typedef unsigned __int64 uint64;
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void* __cdecl EASTL_allocator_allocate(unsigned int size, const char* name, int flags,
                                       int debugFlags, const char* file, int line);  // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p);                                      // 0x00f47380
#define EASTL_ALLOCATOR_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace std {
struct random_access_iterator_tag {};
}
namespace std {
template <typename T> struct iterator_traits;
}
namespace std {
template <typename T> struct iterator_traits<T*> { typedef T value_type; };
}
namespace eastl {
struct allocator_s007c_a950 {              // retail: 8 bytes, trivially copyable
    int mPad0;                  // +0
    void* mpPoolBegin;          // +4
    void deallocate(void* p, unsigned int) { if (p && p != mpPoolBegin) EASTL_allocator_deallocate(p); }
};
}
namespace eastl {
template <int NodeSize, int NodeCount, int Alignment, int AlignmentOffset, bool bEnableOverflow>
class fixed_vector_allocator { public: // retail: 12 bytes, mpPoolBegin at +4
    int   mOverflowAllocator;   // +0
    void* mpPoolBegin;          // +4
    void* mpPadEnd;             // +8 (uninitialized in retail)
    unsigned int capacity() const { return NodeCount; }
    void deallocate(void* p, unsigned int) {
        if (p && p != mpPoolBegin) EASTL_allocator_deallocate(p);
    }
};
}
namespace eastl {
template <typename T> struct less_s007c_a950 {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <typename T1, typename T2> struct pair_s007c_a950 {
    T1 first;
    T2 second;
    pair_s007c_a950() {}
    pair_s007c_a950(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
template <int B, typename Tag> struct copy_impl {
    template <typename In, typename Out>
    static Out do_copy(In first, In last, Out result) {
        for (; first != last; ++first, ++result)
            *result = *first;
        return result;
    }
};
}
namespace eastl {
template <int B, typename Tag> struct uninitialized_move_impl {
    template <typename F, typename D>
    static D do_move_start(F first, F last, D dest) {
        typedef typename std::iterator_traits<F>::value_type value_type;
        for (; first != last; ++first, ++dest)
            ::new ((void*)&*dest) value_type(*first);
        return dest;
    }
    template <typename F, typename D>
    static D do_move_commit(F first, F last, D dest) {
        typedef typename std::iterator_traits<F>::value_type value_type;
        for (; first != last; ++first, ++dest)
            first->~value_type();
        return dest;
    }
};
}
namespace eastl {
template <typename T> T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
    T* d = result;
    for (; first != last; ++first, ++d)
        ::new ((void*)d) T(*first);
    return d;
}
}
namespace eastl {
template <typename It, typename T>
void fill(It first, It last, const T& value) {
    for (; first != last; ++first)
        *first = value;
}
}
namespace eastl {
template <typename T, typename A>
struct VectorBase_s007c_a950 {
    T* mpBegin;      // +0
    T* mpEnd;        // +4
    T* mpCapacity;   // +8
    A  mAllocator;   // +12
};
}
namespace eastl {
template <typename T, typename A>
struct vector_s007c_a950 : VectorBase_s007c_a950<T, A> {
    typedef VectorBase_s007c_a950<T, A> base_type;
    typedef unsigned int size_type;
    typedef T value_type;
    typedef T* iterator;

    vector_s007c_a950() { this->mpBegin = 0; this->mpEnd = 0; this->mpCapacity = 0; }
    ~vector_s007c_a950();

    size_type size() const { return (size_type)(this->mpEnd - this->mpBegin); }
    size_type capacity() const { return (size_type)(this->mpCapacity - this->mpBegin); }

    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first) first->~T();
    }
    T* DoAllocate(size_type n) {
        if (n == 0) return 0;
        return (T*)EASTL_allocator_allocate((unsigned int)(n * sizeof(T)), "App", 0, 0,
                                            EASTL_ALLOCATOR_FILE, 0xd1);
    }
    void DoFree(T* p, size_type) { if (p) EASTL_allocator_deallocate(p); }
    T* DoRealloc(size_type n, const T* first, const T* last) {
        T* p = DoAllocate(n);
        uninitialized_copy_ptr(first, last, p);
        return p;
    }

    void DoInsertValue(T* position, const T& value);            // out of line 0x00621fc0
    void push_back();                                           // out of line
    T* insert(T* position, const T& value);                     // out of line
    void insert(T* position, size_type n, const T& value);      // out of line
    T* erase(T* first, T* last);                                // out of line 0x00621f50
    void resize(size_type n);                                   // out of line

    template <typename It> void DoAssignFromIterator(It first, It last, std::random_access_iterator_tag);
    vector_s007c_a950& operator=(const vector_s007c_a950& x);
};
}
namespace eastl {
template <typename Key_s007c_a950, typename Value, typename Compare>
class map_value_compare { public:
    Compare c;
    bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
    bool operator()(const Key_s007c_a950& a, const Value& b) const { return c(a, b.first); }
};
}
namespace eastl {
template <typename Key_s007c_a950, typename T, typename Compare, typename Allocator, typename RA>
struct vector_map_s007c_a950 : RA {
    typedef RA base_type;
    typedef typename RA::value_type value_type;
    typedef typename RA::iterator iterator;
    typedef Key_s007c_a950 key_type;
    typedef map_value_compare<Key_s007c_a950, value_type, Compare> value_compare;

    value_compare mValueCompare;

    pair_s007c_a950<iterator, bool> insert(const value_type& value);
    iterator insert(iterator position, const value_type& value);
    T& operator[](const key_type& key);
};
}
namespace eastl {
template <typename It, typename Key_s007c_a950, typename Cmp>
It lower_bound(It first, It last, const Key_s007c_a950& key, Cmp compare);
}
namespace eastl {
template <typename Key_s007c_a950, typename T, typename C, typename A, typename RA>
pair_s007c_a950<typename vector_map_s007c_a950<Key_s007c_a950, T, C, A, RA>::iterator, bool>
vector_map_s007c_a950<Key_s007c_a950, T, C, A, RA>::insert(const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB = eastl::lower_bound(this->mpBegin, itEnd, value.first, mValueCompare);
    if ((itLB != itEnd) && !mValueCompare(value, *itLB))
        return pair_s007c_a950<iterator, bool>(itLB, false);
    return pair_s007c_a950<iterator, bool>(base_type::insert(itLB, value), true);
}
}
namespace eastl {
template <typename Key_s007c_a950, typename T, typename C, typename A, typename RA>
typename vector_map_s007c_a950<Key_s007c_a950, T, C, A, RA>::iterator
vector_map_s007c_a950<Key_s007c_a950, T, C, A, RA>::insert(iterator position, const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB;
    if ((position != itEnd) && mValueCompare(value, *position))
        itLB = eastl::lower_bound(this->mpBegin, position, value.first, mValueCompare);
    else
        itLB = eastl::lower_bound(position, itEnd, value.first, mValueCompare);
    if ((itLB == itEnd) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    return itLB;
}
}
namespace eastl {
template <typename Key_s007c_a950, typename T, typename C, typename A, typename RA>
T& vector_map_s007c_a950<Key_s007c_a950, T, C, A, RA>::operator[](const key_type& key) {
    iterator itBegin = this->mpBegin;
    iterator itEnd = this->mpEnd;
    iterator it = eastl::lower_bound(itBegin, itEnd, key, mValueCompare);
    if ((it == itEnd) || mValueCompare(key, *it))
        it = base_type::insert(it, value_type(key, T()));
    return it->second;
}
}
namespace eastl {
template <int N, int Align> struct aligned_buffer { char mBuffer[N]; };
}
namespace eastl {
template <typename T, int N, bool B>
struct fixed_vector_s007c_a950 : vector_s007c_a950<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > {
    typedef vector_s007c_a950<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > base_type;
    typedef typename base_type::size_type size_type;
    aligned_buffer<sizeof(T) * N, 4> mBuffer;

    T* buffer() { return (T*)mBuffer.mBuffer; }
    fixed_vector_s007c_a950() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
    }
    fixed_vector_s007c_a950(const fixed_vector_s007c_a950& x) : base_type() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
        this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
    }
    fixed_vector_s007c_a950& operator=(const fixed_vector_s007c_a950& x) {
        if (&x != this) {
            this->erase(this->mpBegin, this->mpEnd);
            this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
        }
        return *this;
    }
};
}
namespace EA {
template <typename T> struct AutoRefCount_s007c_a950 {
    T* mpObject;   // +0
    AutoRefCount_s007c_a950(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s007c_a950(const AutoRefCount_s007c_a950& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s007c_a950() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s007c_a950& operator=(const AutoRefCount_s007c_a950& x) {
        if (x.mpObject != mpObject) {
            T* pOld = mpObject;
            if (x.mpObject) x.mpObject->AddRef();
            mpObject = x.mpObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    AutoRefCount_s007c_a950& operator=(T* p) {
        if (p != mpObject) {
            T* pOld = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
}
namespace EA {
struct Variant_s007c_a950 {
    unsigned int mData[4];   // +0
    unsigned short mFlags;   // +0x10
    unsigned short mTypeId;  // +0x12
    Variant_s007c_a950() : mFlags(0), mTypeId(0) {}
    ~Variant_s007c_a950() { if (mFlags & 4) Destruct(false); }
    Variant_s007c_a950& operator=(const Variant_s007c_a950& x);
    template <typename T> Variant_s007c_a950& operator=(const T& x);
    void Destruct(bool bReconstruct);  // 0x0093db80 (EA::Variant::Destruct)
};
}
namespace EA {
namespace ResourceMan {
struct Key_s007c_a950 { unsigned int mInstance; unsigned int mType; unsigned int mGroup; unsigned int mPad; };
}
}
namespace SP {
class cPropertyList_s007c_a950 {
public:
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                      // +0x04
virtual void v02();
virtual void v03();
virtual void v04();
    virtual void SetProperty(int id, const EA::Variant_s007c_a950& value);  // +0x14 0x006a2e20
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
    virtual void v30(cPropertyList_s007c_a950* p);                          // +0x30
    char pad[0x54 - 0x34];
};
}
namespace SP {
class IPropertyManager {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0A();
virtual void v0B();
virtual void v0C();
virtual void v0D();
virtual void v0E();
virtual void v0F();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual bool HasPropertyList(uint32 a, uint32 b);                              // +0x28
    virtual bool GetPropertyList(uint32 a, uint32 b, EA::AutoRefCount_s007c_a950<cPropertyList_s007c_a950>& out);  // +0x2c
    virtual void v2C(cPropertyList_s007c_a950* p);                                            // +0x30
};
}
namespace SP {
IPropertyManager* PropertyManager_s007c_a950();   // 0x0067de30
}
namespace Editor {
class cPropertyList_s007c_a950 : public SP::cPropertyList_s007c_a950 {
public:
    cPropertyList_s007c_a950();
};  // namespace Editor
}
namespace EA {
namespace ArgScript {
struct cArguments_s007c_a950 {
    void** MainArguments(int n);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
    void** OptionArguments(const char* pName, int n);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
};
}
}
typedef eastl::pair_s007c_a950<uint64, EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950> > PropPair;
typedef eastl::vector_s007c_a950<PropPair, eastl::allocator_s007c_a950>                PropVec;
typedef eastl::vector_map_s007c_a950<uint64, EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950>,
                          eastl::less_s007c_a950<uint64>, eastl::allocator_s007c_a950, PropVec> PropMap;
typedef eastl::vector_s007c_a950<EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950>,
                      eastl::fixed_vector_allocator<4, 4, 4, 0, 1> > PropFixVec;
namespace eastl {
template <typename T, typename A>
vector_s007c_a950<T, A>& vector_s007c_a950<T, A>::operator=(const vector_s007c_a950& x) {
    if (&x != this) {
        const size_type n = x.size();
        if (n > capacity()) {
            T* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            DoDestroyValues(this->mpBegin, this->mpEnd);
            DoFree(this->mpBegin, capacity());
            this->mpBegin = pNewData;
            this->mpEnd = pNewData + n;
            this->mpCapacity = pNewData + n;
        } else if (n <= size()) {
            T* const pNewEnd =
                copy_impl<0, std::random_access_iterator_tag>::do_copy(x.mpBegin, x.mpEnd, this->mpBegin);
            DoDestroyValues(pNewEnd, this->mpEnd);
            this->mpEnd = pNewEnd;
        } else {
            T* const position = x.mpBegin + size();
            copy_impl<0, std::random_access_iterator_tag>::do_copy(x.mpBegin, position, this->mpBegin);
            this->mpEnd = uninitialized_copy_ptr(position, x.mpEnd, this->mpEnd);
        }
    }
    return *this;
}
}
namespace eastl {
template <typename T, typename A>
T* vector_s007c_a950<T, A>::insert(T* position, const T& value) {
    const int n = (int)(position - this->mpBegin);
    if ((position == this->mpEnd) && (this->mpEnd != this->mpCapacity)) {
        ::new (this->mpEnd++) T(value);
    } else {
        DoInsertValue(position, value);
    }
    return this->mpBegin + n;
}
}
namespace eastl {
template <typename T, typename A>
void vector_s007c_a950<T, A>::resize(size_type n) {
    if (n > size()) {
        insert(this->mpEnd, n - size(), T());
    } else {
        erase(this->mpBegin + n, this->mpEnd);
    }
}
}
namespace eastl {
template <typename T, typename A>
template <typename It>
void vector_s007c_a950<T, A>::DoAssignFromIterator(It first, It last, std::random_access_iterator_tag) {
    const size_type n = (size_type)(last - first);
    if (n > capacity()) {
        T* const pNewData = DoRealloc(n, first, last);
        DoDestroyValues(this->mpBegin, this->mpEnd);
        DoFree(this->mpBegin, capacity());
        this->mpBegin = pNewData;
        this->mpEnd = this->mpBegin + n;
        this->mpCapacity = this->mpEnd;
    } else if (n <= size()) {
        T* const pNewEnd = copy_impl<0, std::random_access_iterator_tag>::do_copy(first, last, this->mpBegin);
        DoDestroyValues(pNewEnd, this->mpEnd);
        this->mpEnd = pNewEnd;
    } else {
        It position = first + size();
        copy_impl<0, std::random_access_iterator_tag>::do_copy(first, position, this->mpBegin);
        this->mpEnd = uninitialized_copy_ptr(position, last, this->mpEnd);
    }
}
}
template PropVec& PropVec::operator=(const PropVec&);
namespace SP {
struct cOption_s007c_a950 {
    unsigned int mID;              // +0x00
    unsigned int mDefaultSetting;  // +0x04
    unsigned int mCurrentSetting;  // +0x08
    eastl::fixed_vector_s007c_a950<EA::AutoRefCount_s007c_a950<cPropertyList_s007c_a950>, 4, 1> mPropertySettings;  // +0x0c
    eastl::fixed_vector_s007c_a950<PropMap, 4, 1>                         mExternalSettings;  // +0x34
    ~cOption_s007c_a950();
};
}
template SP::cOption_s007c_a950* eastl::uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_commit<SP::cOption_s007c_a950*, SP::cOption_s007c_a950*>(SP::cOption_s007c_a950*, SP::cOption_s007c_a950*, SP::cOption_s007c_a950*);
namespace {

struct cPropertySource {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0A();
virtual void v0B();
virtual void v0C();
virtual void v0D();
virtual void v0E();
virtual void v0F();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1A();
virtual void v1B();
virtual void v1C();
virtual void v1D();
virtual void v1E();
virtual void v1F();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual void v24();
    virtual bool  GetBool(void* p);    // +0x94
    virtual float GetFloat(void* p);   // +0x98
    virtual int   GetInt(void* p);     // +0x9c
};

struct OptionTable {
    char pad00[0x44];
    char* mBase;    // +0x44
    char pad48[0x10];
    int   mCount;   // +0x58
    int   mIndex;   // +0x5c
};

struct CommandBase {
    void* mp0;                // +0x0
    cPropertySource* mpSource; // +0x4
    void* mp8;                // +0x8
    OptionTable* mpTable;     // +0xc
};

void __cdecl ThrowBadPropListName();

SP::cPropertyList_s007c_a950* GetPropListSettings(const void* pName, PropMap* pMap);

// Duplicated (inlined) prologue shared by the five commands.
static inline SP::cPropertyList_s007c_a950* GetTargetList(CommandBase* pThis, void** pOption) {
    if (pOption) {
        OptionTable* t = pThis->mpTable;
        char* p = t->mBase + t->mCount * 0xac;
        return GetPropListSettings(pOption[0], (PropMap*)(*(char**)(p + 0x34) + t->mIndex * 0x18));
    }
    OptionTable* t = pThis->mpTable;
    char* p = t->mBase + t->mCount * 0xac;
    return (*(SP::cPropertyList_s007c_a950***)(p + 0xc))[t->mIndex];
}

class cOptionBoolPropertyCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments_s007c_a950* pArgs);
};
class cOptionIntPropertyCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments_s007c_a950* pArgs);
};
class cOptionFloatPropertyCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments_s007c_a950* pArgs);
};
class cOptionPropertiesCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments_s007c_a950* pArgs);
};
class SomeOptionPropertiesCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments_s007c_a950* pArgs);
};

}  // anonymous namespace
// ---- items of slice s007ca950 end

// ---- items of slice s007cb590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyChar;   // 0x01667bac
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent(void);
namespace eastl {
struct allocator_s007c_b590 {              // retail: 8 bytes, trivially copyable
    int mPad0;                  // +0
    void* mpPoolBegin;          // +4
    void deallocate(void* p, unsigned int) { if (p && p != mpPoolBegin) EASTL_allocator_deallocate(p); }
};
}
namespace eastl {
template <typename T> struct less_s007c_b590 {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <typename T1, typename T2> struct pair_s007c_b590 {
    T1 first;
    T2 second;
    pair_s007c_b590() {}
    pair_s007c_b590(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
template <int B, typename Tag> struct copy_backward_impl {
    template <typename In, typename Out>
    static Out do_copy(In first, In last, Out result) {
        while (last != first) {
            --last;
            --result;
            *result = *last;
        }
        return result;
    }
};
}
namespace eastl {
template <typename T, typename A>
struct VectorBase_s007c_b590 {
    T* mpBegin;      // +0
    T* mpEnd;        // +4
    T* mpCapacity;   // +8
    A  mAllocator;   // +12
};
}
namespace eastl {
template <typename T, typename A>
struct vector_s007c_b590 : VectorBase_s007c_b590<T, A> {
    typedef VectorBase_s007c_b590<T, A> base_type;
    typedef unsigned int size_type;
    typedef T value_type;
    typedef T* iterator;

    vector_s007c_b590() { this->mpBegin = 0; this->mpEnd = 0; this->mpCapacity = 0; }
    ~vector_s007c_b590();

    size_type size() const { return (size_type)(this->mpEnd - this->mpBegin); }
    size_type capacity() const { return (size_type)(this->mpCapacity - this->mpBegin); }

    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first) first->~T();
    }
    T* DoAllocate(size_type n) {
        if (n == 0) return 0;
        return (T*)EASTL_allocator_allocate((unsigned int)(n * sizeof(T)), "App", 0, 0,
                                            EASTL_ALLOCATOR_FILE, 0xd1);
    }
    void DoFree(T* p, size_type) { if (p) EASTL_allocator_deallocate(p); }
    T* DoRealloc(size_type n, const T* first, const T* last) {
        T* p = DoAllocate(n);
        uninitialized_copy_ptr(first, last, p);
        return p;
    }

    void DoInsertValue(T* position, const T& value);            // out of line 0x00621fc0
    void push_back();                                           // out of line
    T* insert(T* position, const T& value);                     // out of line
    void insert(T* position, size_type n, const T& value);      // out of line
    T* erase(T* first, T* last);                                // out of line 0x00621f50
    void resize(size_type n);                                   // out of line

    template <typename It> void DoAssignFromIterator(It first, It last, std::random_access_iterator_tag);
    vector_s007c_b590& operator=(const vector_s007c_b590& x);
};
}
namespace eastl {
template <typename Key_s007c_b590, typename Value, typename Compare>
struct map_value_compare_s007c_b590 {
    Compare c;
    bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
    bool operator()(const Key_s007c_b590& a, const Value& b) const { return c(a, b.first); }
};
}
namespace eastl {
template <typename Key_s007c_b590, typename T, typename Compare, typename Allocator, typename RA>
struct vector_map_s007c_b590 : RA {
    typedef RA base_type;
    typedef typename RA::value_type value_type;
    typedef typename RA::iterator iterator;
    typedef Key_s007c_b590 key_type;
    typedef map_value_compare_s007c_b590<Key_s007c_b590, value_type, Compare> value_compare;

    value_compare mValueCompare;

    pair_s007c_b590<iterator, bool> insert(const value_type& value);
    iterator insert(iterator position, const value_type& value);
    T& operator[](const key_type& key);
};
}
namespace eastl {
template <typename It, typename Key_s007c_b590, typename Cmp>
It lower_bound(It first, It last, const Key_s007c_b590& key, Cmp compare);
}
namespace eastl {
template <typename Key_s007c_b590, typename T, typename C, typename A, typename RA>
pair_s007c_b590<typename vector_map_s007c_b590<Key_s007c_b590, T, C, A, RA>::iterator, bool>
vector_map_s007c_b590<Key_s007c_b590, T, C, A, RA>::insert(const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB = eastl::lower_bound(this->mpBegin, itEnd, value.first, mValueCompare);
    if ((itLB != itEnd) && !mValueCompare(value, *itLB))
        return pair_s007c_b590<iterator, bool>(itLB, false);
    return pair_s007c_b590<iterator, bool>(base_type::insert(itLB, value), true);
}
}
namespace eastl {
template <typename Key_s007c_b590, typename T, typename C, typename A, typename RA>
typename vector_map_s007c_b590<Key_s007c_b590, T, C, A, RA>::iterator
vector_map_s007c_b590<Key_s007c_b590, T, C, A, RA>::insert(iterator position, const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB;
    if ((position != itEnd) && mValueCompare(value, *position))
        itLB = eastl::lower_bound(this->mpBegin, position, value.first, mValueCompare);
    else
        itLB = eastl::lower_bound(position, itEnd, value.first, mValueCompare);
    if ((itLB == itEnd) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    return itLB;
}
}
namespace eastl {
template <typename Key_s007c_b590, typename T, typename C, typename A, typename RA>
T& vector_map_s007c_b590<Key_s007c_b590, T, C, A, RA>::operator[](const key_type& key) {
    iterator itBegin = this->mpBegin;
    iterator itEnd = this->mpEnd;
    iterator it = eastl::lower_bound(itBegin, itEnd, key, mValueCompare);
    if ((it == itEnd) || mValueCompare(key, *it))
        it = base_type::insert(it, value_type(key, T()));
    return it->second;
}
}
namespace eastl {
template <typename T, int N, bool B>
struct fixed_vector_s007c_b590 : vector_s007c_b590<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > {
    typedef vector_s007c_b590<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > base_type;
    typedef typename base_type::size_type size_type;
    aligned_buffer<sizeof(T) * N, 4> mBuffer;

    T* buffer() { return (T*)mBuffer.mBuffer; }
    fixed_vector_s007c_b590() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
    }
    fixed_vector_s007c_b590(const fixed_vector_s007c_b590& x) : base_type() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
        this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
    }
    fixed_vector_s007c_b590& operator=(const fixed_vector_s007c_b590& x) {
        if (&x != this) {
            this->erase(this->mpBegin, this->mpEnd);
            this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
        }
        return *this;
    }
};
}
namespace EA {
template <typename T> struct AutoRefCount_s007c_b590 {
    T* mpObject;   // +0
    AutoRefCount_s007c_b590(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s007c_b590(const AutoRefCount_s007c_b590& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s007c_b590() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s007c_b590& operator=(const AutoRefCount_s007c_b590& x) {
        if (x.mpObject != mpObject) {
            T* pOld = mpObject;
            if (x.mpObject) x.mpObject->AddRef();
            mpObject = x.mpObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    AutoRefCount_s007c_b590& operator=(T* p) {
        if (p != mpObject) {
            T* pOld = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
}
namespace EA {
struct Variant_s007c_b590 {
    unsigned int mData[4];   // +0
    unsigned short mFlags;   // +0x10
    unsigned short mTypeId;  // +0x12
    Variant_s007c_b590() : mFlags(0), mTypeId(0) {}
    ~Variant_s007c_b590() { if (mFlags & 4) Destruct(false); }
    Variant_s007c_b590& operator=(const Variant_s007c_b590& x);
    template <typename T> Variant_s007c_b590& operator=(const T& x);
    void Destruct(bool bReconstruct);  // 0x0093db80 (EA::Variant::Destruct)
};
}
namespace EA {
namespace ResourceMan {
struct Key_s007c_b590 { unsigned int mInstance; unsigned int mType; unsigned int mGroup; unsigned int mPad; };
}
}
namespace SP {
class cPropertyList_s007c_b590 {
public:
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                      // +0x04
virtual void v02();
virtual void v03();
virtual void v04();
    virtual void SetProperty(int id, const EA::Variant_s007c_b590& value);  // +0x14 0x006a2e20
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
    virtual void v30(cPropertyList_s007c_b590* p);                          // +0x30
    char pad[0x54 - 0x34];
};
}
namespace Editor {
class cPropertyList_s007c_b590 : public SP::cPropertyList_s007c_b590 {
public:
    cPropertyList_s007c_b590();
};  // namespace Editor
}
namespace EA {
namespace ArgScript {
struct cArguments_s007c_b590 {
    void** MainArguments(int n);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
    void** OptionArguments(const char* pName, int n);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
};
}
}
struct sp_vector_allocator {
    unsigned int mData[2];
    void deallocate(void* p, unsigned int) {
        if (p && ((unsigned int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
};
struct string8 {
    char* mpBegin;        // +0
    char* mpEnd;          // +4
    char* mpCapacity;     // +8
    unsigned int mAllocator;  // +0xc
    string8() : mpBegin(&gEmptyChar), mpEnd(&gEmptyChar), mpCapacity(&gEmptyChar + 1), mAllocator(0) {}
    ~string8() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
    string8& assign(const char* first, const char* last);
    string8& operator=(const string8& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};
typedef eastl::pair_s007c_b590<uint64, EA::AutoRefCount_s007c_b590<SP::cPropertyList_s007c_b590> > PropPair_s007c_b590;
typedef eastl::vector_s007c_b590<PropPair_s007c_b590, eastl::allocator_s007c_b590>                PropVec_s007c_b590;
typedef eastl::vector_map_s007c_b590<uint64, EA::AutoRefCount_s007c_b590<SP::cPropertyList_s007c_b590>,
                          eastl::less_s007c_b590<uint64>, eastl::allocator_s007c_b590, PropVec_s007c_b590> PropMap_s007c_b590;
typedef eastl::vector_s007c_b590<PropMap_s007c_b590, eastl::fixed_vector_allocator<sizeof(PropMap_s007c_b590), 4, 4, 0, 1> > MapFixVec;

// Retail's element construction (0x7c9830: vector copy ctor 0x7c8af0 + a 1-byte compare copy)
// leaves the destination allocator field untouched; the implicit copy constructor would copy it.
namespace eastl {
template <typename T>
T* uninitialized_fill_n_ptr(T* first, unsigned int n, const T& value) {
    T* d = first;
    for (unsigned int i = 0; i < n; ++i, ++d) {
        ::new ((void*)d) T;
        *d = value;
    }
    return d;
}
}

// The retail resize (0x7cc3c0) calls the out-of-line insert/erase instantiations. Route through
// masked declarations so the calls land on the image functions instead of this TU's copies (the
// call trace and all helper effects then match retail exactly).
struct MapFixVecView_s007c_b590 {
    void insert(PropMap_s007c_b590* position, unsigned int n, const PropMap_s007c_b590& value);  // 0x007cbdc0
    PropMap_s007c_b590* erase(PropMap_s007c_b590* first, PropMap_s007c_b590* last);              // 0x007cbd60
};

// The header only declares the vector special members; bind our references to the retail helpers.
namespace __equiv_ann1 {
struct vector_s007c_b590 {
    ~vector_s007c_b590();                                    // 0x007cef60
    vector_s007c_b590& operator=(const vector_s007c_b590&);  // 0x007ca060
};
}

// Dispatch resize's out-of-line calls: the MapFixVec instantiation must land on the image
// functions (call trace + helper effects), other instantiations keep their local copies.
namespace eastl {
inline void resize_insert(MapFixVec* v, PropMap_s007c_b590* position, unsigned int n,
                          const PropMap_s007c_b590& value) {
    ((MapFixVecView_s007c_b590*)v)->insert(position, n, value);
}
inline PropMap_s007c_b590* resize_erase(MapFixVec* v, PropMap_s007c_b590* first,
                                        PropMap_s007c_b590* last) {
    return ((MapFixVecView_s007c_b590*)v)->erase(first, last);
}
template <typename T, typename A>
inline void resize_insert(vector_s007c_b590<T, A>* v, T* position, unsigned int n, const T& value) {
    v->insert(position, n, value);
}
template <typename T, typename A>
inline T* resize_erase(vector_s007c_b590<T, A>* v, T* first, T* last) {
    return v->erase(first, last);
}
}
namespace eastl {
template <typename T, typename A>
T* vector_s007c_b590<T, A>::erase(T* first, T* last) {
    T* const pFirst = first;
    T* const pLast = last;
    T* const position = copy_impl<0, std::random_access_iterator_tag>::do_copy(pLast, this->mpEnd, pFirst);
    DoDestroyValues(position, this->mpEnd);
    this->mpEnd -= (pLast - pFirst);
    return pFirst;
}
}
namespace eastl {
template <typename T, typename A>
void vector_s007c_b590<T, A>::resize(size_type n) {
    if (n > (size_type)(this->mpEnd - this->mpBegin)) {
        T value;
        resize_insert(this, this->mpEnd, n - (size_type)(this->mpEnd - this->mpBegin), value);
    } else {
        resize_erase(this, this->mpBegin + n, this->mpEnd);
    }
}
}
namespace eastl {
template <typename T, typename A>
void vector_s007c_b590<T, A>::insert(T* position, size_type n, const T& value) {
    if (n <= (size_type)(this->mpCapacity - this->mpEnd)) {
        if (n > 0) {
            const T temp = value;
            const size_type nExtra = (size_type)(this->mpEnd - position);
            if (n < nExtra) {
                uninitialized_copy_ptr(this->mpEnd - n, this->mpEnd, this->mpEnd);
                copy_backward_impl<0, std::random_access_iterator_tag>::do_copy(position, this->mpEnd - n, this->mpEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(this->mpEnd, n - nExtra, temp);
                uninitialized_copy_ptr(position, this->mpEnd, this->mpEnd + n - nExtra);
                fill(position, this->mpEnd, temp);
            }
            this->mpEnd += n;
        }
    } else {
        const size_type nPrevSize = size();
        const size_type nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const size_type nNewSize = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        T* const pNewData = DoAllocate(nNewSize);
        T* pNewEnd = uninitialized_copy_ptr(this->mpBegin, position, pNewData);
        pNewEnd = uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_copy_ptr(position, this->mpEnd, pNewEnd);
        DoDestroyValues(this->mpBegin, this->mpEnd);
        DoFree(this->mpBegin, capacity());
        this->mpBegin = pNewData;
        this->mpEnd = pNewEnd;
        this->mpCapacity = pNewData + nNewSize;
    }
}
}
namespace eastl {
template <typename T, typename A>
template <typename It>
void vector_s007c_b590<T, A>::DoAssignFromIterator(It first, It last, std::random_access_iterator_tag) {
    const size_type n = (size_type)(last - first);
    if (n > capacity()) {
        T* const pNewData = DoRealloc(n, first, last);
        DoDestroyValues(this->mpBegin, this->mpEnd);
        DoFree(this->mpBegin, capacity());
        this->mpBegin = pNewData;
        this->mpEnd = this->mpBegin + n;
        this->mpCapacity = this->mpEnd;
    } else if (n <= size()) {
        T* const pNewEnd = copy_impl<0, std::random_access_iterator_tag>::do_copy(first, last, this->mpBegin);
        DoDestroyValues(pNewEnd, this->mpEnd);
        this->mpEnd = pNewEnd;
    } else {
        It position = first + size();
        copy_impl<0, std::random_access_iterator_tag>::do_copy(first, position, this->mpBegin);
        this->mpEnd = uninitialized_copy_ptr(position, last, this->mpEnd);
    }
}
}
template eastl::fixed_vector_s007c_b590<PropMap_s007c_b590, 4, 1>::fixed_vector_s007c_b590(const eastl::fixed_vector_s007c_b590<PropMap_s007c_b590, 4, 1>&);
struct string16 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; unsigned int mAllocator;
    ~string16() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
};
namespace EA {
string16 ConvertToString16(const string8& s);                 // 0x0093c6d0
}
namespace EA {
string8  ConvertToString8(const wchar_t* p, int n = -1);      // 0x0093c440
}
void string8_sprintf(string8* s, const char* fmt, ...);        // 0x00472fe0 (cdecl, string is arg 0)
struct SpStringVecView
{
    string8* mpBegin; string8* mpEnd; string8* mpCapacity; unsigned int pad[2];
    void resize(int n);   // 0x00553be0
};
struct SpFloatVecView
{
    float* mpBegin; float* mpEnd; float* mpCapacity; unsigned int pad[2];
    void resize(int n);   // 0x004afc80
};
struct StrRaw { char* b; char* e; char* cap; unsigned int al; };
struct CBig
{
    StrRaw s[9];            // +0x00
    float  f90;             // +0x90
    int    i94;             // +0x94
    unsigned char b98, b99, b9a, b9b, b9c, pad9d[3];  // +0x98
    float  fa0, fa4, fa8, fac;                        // +0xa0
    CBig();      // 0x006b8460
    ~CBig();     // 0x005f8910
};
void GetSystemInfo(CBig* out);                         // 0x006b8680 (cdecl)
struct PathObj
{
    unsigned int d[0x100];
    PathObj(const wchar_t* s);   // 0x00930f60 (ret 4)
    const wchar_t* GetFirst();   // 0x00930bf0
    const wchar_t* GetSecond();  // 0x00572590
};
struct DevCaps {
    unsigned int d00[0x98 / 4];
    unsigned int maxSimultaneousTextures;              // +0x98
    unsigned int d9c[(0xc4 - 0x9c) / 4];
    unsigned char vsMinor, vsMajor; unsigned short padc6;      // +0xc4 VertexShaderVersion
    unsigned int maxVertexShaderConst;                 // +0xc8
    unsigned char psMinor, psMajor; unsigned short padce;      // +0xcc PixelShaderVersion
    unsigned int dd0[(0xf0 - 0xd0) / 4];
    unsigned int numSimultaneousRTs;                   // +0xf0
    unsigned int df4[(0x110 - 0xf4) / 4];
    unsigned int ps20NumTemps;                         // +0x110
    unsigned int d114;
    unsigned int ps20NumInstructionSlots;              // +0x118
    unsigned int d11c[(0x128 - 0x11c) / 4];
    unsigned int maxVS30Slots;                         // +0x128
    unsigned int maxPS30Slots;                         // +0x12c
    unsigned int d130;
    unsigned int deviceId;                             // +0x134
    unsigned int vendorId;                             // +0x138
    unsigned int d13c;
    unsigned int driverLow, driverHigh;                // +0x140
    unsigned int d148[(0x1fc - 0x148) / 4];
    char         description[0x200];                   // +0x1fc
    unsigned int dispW, dispH;                         // +0x3fc
};
bool FUN_006b8250();                                   // 0x006b8250
unsigned int FUN_006b8410();                           // 0x006b8410
bool IsVistaKB940105Required();                        // 0x007c5f50
struct AppProps
{
    unsigned char GetDescription(unsigned int id);   // 0x006a25a0 (thiscall, ret 4)
};
extern AppProps* g_sAppProperties_s007c_b590;                                    // 0x015fd918
struct IDev9 {
    struct VT { void* f0; void* f1; void* f2; void* f3;
                unsigned int (__stdcall *GetAvailableTextureMem)(IDev9*); } *vt;   // slot 4 (+0x10)
};
extern IDev9* g_pD3D9Device;                                          // 0x016f89d0
struct DispMode { unsigned int width, height, refresh, format; };
DispMode D3D9GetDesktopDisplayMode();                                 // 0x011f8270 (sret)
DevCaps* GetD3DCAPS9();                                               // 0x011f8af0
namespace SP {
struct cOption_s007c_b590 {
    unsigned int mID;              // +0x00
    unsigned int mDefaultSetting;  // +0x04
    unsigned int mCurrentSetting;  // +0x08
    eastl::fixed_vector_s007c_b590<EA::AutoRefCount_s007c_b590<cPropertyList_s007c_b590>, 4, 1> mPropertySettings;  // +0x0c
    eastl::fixed_vector_s007c_b590<PropMap_s007c_b590, 4, 1>                         mExternalSettings;  // +0x34
    ~cOption_s007c_b590();
};
}
namespace SP {
struct cConfigScriptState_s007c_b590 {
    void* mpVtable;                       // +0x00
    unsigned int mVendorID;               // +0x04
    unsigned int mCardID;                 // +0x08
    bool mOverrideCardIDs;                // +0x0c
    bool mFoundCard;                      // +0x0d
    char pad0e[2];
    string8 mCurrentCardVendor;           // +0x10
    string8 mCardVendor;                  // +0x20
    string8 mCardName;                    // +0x30
    bool mFirstRun;                       // +0x40
    bool mAbortApp;                       // +0x41
    bool mPad42;                          // +0x42
    bool mPad43;                          // +0x43
    eastl::vector_s007c_b590<cOption_s007c_b590, sp_vector_allocator> mOptions;     // +0x44
    int mCurrentOptionID;                 // +0x58
    unsigned int mCurrentOptionSetting;   // +0x5c
    eastl::vector_s007c_b590<string8, sp_vector_allocator> mConfigStrings;  // +0x60
    eastl::vector_s007c_b590<float, sp_vector_allocator>   mConfigNumbers;  // +0x74

    cConfigScriptState_s007c_b590();
    ~cConfigScriptState_s007c_b590();
    void GatherInformation();  // 0x007cb590 (SP::cConfigScriptState::GatherInformation)
};
}
namespace SP {
struct IConfigUnknown {
    virtual void AddRef();
    virtual void Release();
};
}
namespace SP {
struct cConfigManager_s007c_b590 {
    void* mpVtable0;                      // +0x00
    void* mpVtable1;                      // +0x04
    unsigned int mRefCount;               // +0x08
    EA::AutoRefCount_s007c_b590<IConfigUnknown> mpPad0c;  // +0x0c
    EA::AutoRefCount_s007c_b590<IConfigUnknown> mpPad10;  // +0x10
    unsigned int mPad14;                  // +0x14
    unsigned int mPad18;                  // +0x18
    int mPad1c;                           // +0x1c
    cConfigScriptState_s007c_b590 mState;            // +0x20
    char padA0[8];
    int mPadA8;                           // +0xa8
    bool mPadAC;                          // +0xac
    bool mPadAD;                          // +0xad
    char padAE[2];
    EA::AutoRefCount_s007c_b590<IConfigUnknown> mpPadB0;  // +0xb0

    cConfigManager_s007c_b590();
    ~cConfigManager_s007c_b590();
};
}
namespace SP {
namespace {
struct SettingSource {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0A();
virtual void v0B();
virtual void v0C();
virtual void v0D();
virtual void v0E();
virtual void v0F();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1A();
virtual void v1B();
virtual void v1C();
virtual void v1D();
virtual void v1E();
virtual void v1F();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
    virtual unsigned int GetSetting(void* p);   // +0xa0
};

struct OptionTable2 {
    char pad00[0x44];
    char* mBase;    // +0x44
    char pad48[0x10];
    int   mCount;   // +0x58
    int   mIndex;   // +0x5c
};

struct SettingCommand {
    void* mp0;               // +0x0
    SettingSource* mpSource; // +0x4
    void* mp8;               // +0x8
    OptionTable2* mpTable;   // +0xc
    void Execute(EA::ArgScript::cArguments_s007c_b590* pArgs);
};
}  // anonymous namespace
}
// ---- items of slice s007cb590 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
inline void AssignRaw(string8& dst, const StrRaw& src);  // 0x007cc580 (stays in the slice: not this object's)

// ---- items of slice s007cc5f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace std {
template <typename T> struct iterator_traits_s007c_c5f0;
}
namespace std {
template <typename T> struct iterator_traits_s007c_c5f0<T*> { typedef T value_type; };
}
namespace eastl {
struct allocator_s007c_c5f0 {              // retail: 8 bytes, trivially copyable
    int mPad0;                  // +0
    void* mpPoolBegin;          // +4
    void deallocate(void* p, unsigned int) { if (p && p != mpPoolBegin) EASTL_allocator_deallocate(p); }
};
}
namespace eastl {
template <typename T> struct less_s007c_c5f0 {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <typename T1, typename T2> struct pair_s007c_c5f0 {
    T1 first;
    T2 second;
    pair_s007c_c5f0() {}
    pair_s007c_c5f0(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
template <int B, typename Tag> struct uninitialized_move_impl_s007c_c5f0 {
    template <typename F, typename D>
    static D do_move_start(F first, F last, D dest) {
        typedef typename std::iterator_traits_s007c_c5f0<F>::value_type value_type;
        for (; first != last; ++first, ++dest)
            ::new ((void*)&*dest) value_type(*first);
        return dest;
    }
    template <typename F, typename D>
    static D do_move_commit(F first, F last, D dest) {
        typedef typename std::iterator_traits_s007c_c5f0<F>::value_type value_type;
        for (; first != last; ++first, ++dest)
            first->~value_type();
        return dest;
    }
};
}
namespace eastl {
template <typename T, typename A>
struct VectorBase_s007c_c5f0 {
    T* mpBegin;      // +0
    T* mpEnd;        // +4
    T* mpCapacity;   // +8
    A  mAllocator;   // +12
};
}
namespace eastl {
template <typename T, typename A>
struct vector_s007c_c5f0 : VectorBase_s007c_c5f0<T, A> {
    typedef VectorBase_s007c_c5f0<T, A> base_type;
    typedef unsigned int size_type;
    typedef T value_type;
    typedef T* iterator;

    vector_s007c_c5f0() { this->mpBegin = 0; this->mpEnd = 0; this->mpCapacity = 0; }
    ~vector_s007c_c5f0();

    size_type size() const { return (size_type)(this->mpEnd - this->mpBegin); }
    size_type capacity() const { return (size_type)(this->mpCapacity - this->mpBegin); }

    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first) first->~T();
    }
    T* DoAllocate(size_type n) {
        if (n == 0) return 0;
        return (T*)EASTL_allocator_allocate((unsigned int)(n * sizeof(T)), "App", 0, 0,
                                            EASTL_ALLOCATOR_FILE, 0xd1);
    }
    void DoFree(T* p, size_type) { if (p) EASTL_allocator_deallocate(p); }
    T* DoRealloc(size_type n, const T* first, const T* last) {
        T* p = DoAllocate(n);
        uninitialized_copy_ptr(first, last, p);
        return p;
    }

    void DoInsertValue(T* position, const T& value);            // out of line 0x00621fc0
    void push_back();                                           // out of line
    T* insert(T* position, const T& value);                     // out of line
    void insert(T* position, size_type n, const T& value);      // out of line
    T* erase(T* first, T* last);                                // out of line 0x00621f50
    void resize(size_type n);                                   // out of line

    template <typename It> void DoAssignFromIterator(It first, It last, std::random_access_iterator_tag);
    vector_s007c_c5f0& operator=(const vector_s007c_c5f0& x);
};
}
namespace eastl {
template <typename Key_s007c_c5f0, typename Value, typename Compare>
struct map_value_compare_s007c_c5f0 {
    Compare c;
    bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
    bool operator()(const Key_s007c_c5f0& a, const Value& b) const { return c(a, b.first); }
};
}
namespace eastl {
template <typename Key_s007c_c5f0, typename T, typename Compare, typename Allocator, typename RA>
struct vector_map_s007c_c5f0 : RA {
    typedef RA base_type;
    typedef typename RA::value_type value_type;
    typedef typename RA::iterator iterator;
    typedef Key_s007c_c5f0 key_type;
    typedef map_value_compare_s007c_c5f0<Key_s007c_c5f0, value_type, Compare> value_compare;

    value_compare mValueCompare;

    pair_s007c_c5f0<iterator, bool> insert(const value_type& value);
    iterator insert(iterator position, const value_type& value);
    T& operator[](const key_type& key);
};
}
namespace eastl {
template <typename It, typename Key_s007c_c5f0, typename Cmp>
It lower_bound(It first, It last, const Key_s007c_c5f0& key, Cmp compare);
}
namespace eastl {
template <typename Key_s007c_c5f0, typename T, typename C, typename A, typename RA>
pair_s007c_c5f0<typename vector_map_s007c_c5f0<Key_s007c_c5f0, T, C, A, RA>::iterator, bool>
vector_map_s007c_c5f0<Key_s007c_c5f0, T, C, A, RA>::insert(const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB = eastl::lower_bound(this->mpBegin, itEnd, value.first, mValueCompare);
    if ((itLB != itEnd) && !mValueCompare(value, *itLB))
        return pair_s007c_c5f0<iterator, bool>(itLB, false);
    return pair_s007c_c5f0<iterator, bool>(base_type::insert(itLB, value), true);
}
}
namespace eastl {
template <typename Key_s007c_c5f0, typename T, typename C, typename A, typename RA>
typename vector_map_s007c_c5f0<Key_s007c_c5f0, T, C, A, RA>::iterator
vector_map_s007c_c5f0<Key_s007c_c5f0, T, C, A, RA>::insert(iterator position, const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB;
    if ((position != itEnd) && mValueCompare(value, *position))
        itLB = eastl::lower_bound(this->mpBegin, position, value.first, mValueCompare);
    else
        itLB = eastl::lower_bound(position, itEnd, value.first, mValueCompare);
    if ((itLB == itEnd) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    return itLB;
}
}
namespace eastl {
template <typename Key_s007c_c5f0, typename T, typename C, typename A, typename RA>
T& vector_map_s007c_c5f0<Key_s007c_c5f0, T, C, A, RA>::operator[](const key_type& key) {
    iterator itBegin = this->mpBegin;
    iterator itEnd = this->mpEnd;
    iterator it = eastl::lower_bound(itBegin, itEnd, key, mValueCompare);
    if ((it == itEnd) || mValueCompare(key, *it))
        it = base_type::insert(it, value_type(key, T()));
    return it->second;
}
}
namespace eastl {
template <typename T, int N, bool B>
struct fixed_vector_s007c_c5f0 : vector_s007c_c5f0<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > {
    typedef vector_s007c_c5f0<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > base_type;
    typedef typename base_type::size_type size_type;
    aligned_buffer<sizeof(T) * N, 4> mBuffer;

    T* buffer() { return (T*)mBuffer.mBuffer; }
    fixed_vector_s007c_c5f0() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
    }
    fixed_vector_s007c_c5f0(const fixed_vector_s007c_c5f0& x) : base_type() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
        this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
    }
    fixed_vector_s007c_c5f0& operator=(const fixed_vector_s007c_c5f0& x) {
        if (&x != this) {
            this->erase(this->mpBegin, this->mpEnd);
            this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
        }
        return *this;
    }
};
}
namespace EA {
template <typename T> struct AutoRefCount_s007c_c5f0 {
    T* mpObject;   // +0
    AutoRefCount_s007c_c5f0(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s007c_c5f0(const AutoRefCount_s007c_c5f0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s007c_c5f0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s007c_c5f0& operator=(const AutoRefCount_s007c_c5f0& x) {
        if (x.mpObject != mpObject) {
            T* pOld = mpObject;
            if (x.mpObject) x.mpObject->AddRef();
            mpObject = x.mpObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    AutoRefCount_s007c_c5f0& operator=(T* p) {
        if (p != mpObject) {
            T* pOld = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
}
namespace EA {
struct Variant_s007c_c5f0 {
    unsigned int mData[4];   // +0
    unsigned short mFlags;   // +0x10
    unsigned short mTypeId;  // +0x12
    Variant_s007c_c5f0() : mFlags(0), mTypeId(0) {}
    ~Variant_s007c_c5f0() { if (mFlags & 4) Destruct(false); }
    Variant_s007c_c5f0& operator=(const Variant_s007c_c5f0& x);
    template <typename T> Variant_s007c_c5f0& operator=(const T& x);
    void Destruct(bool bReconstruct);  // 0x0093db80 (EA::Variant::Destruct)
};
}
namespace EA {
namespace ResourceMan {
struct Key_s007c_c5f0 { unsigned int mInstance; unsigned int mType; unsigned int mGroup; unsigned int mPad; };
}
}
namespace SP {
class cPropertyList_s007c_c5f0 {
public:
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                      // +0x04
virtual void v02();
virtual void v03();
virtual void v04();
    virtual void SetProperty(int id, const EA::Variant_s007c_c5f0& value);  // +0x14 0x006a2e20
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
    virtual void v30(cPropertyList_s007c_c5f0* p);                          // +0x30
    char pad[0x54 - 0x34];
};
}
namespace EA {
namespace ArgScript {
struct cArguments_s007c_c5f0 {
    void** MainArguments(int n);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
    void** OptionArguments(const char* pName, int n);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
};
}
}
struct string8_s007c_c5f0 {
    char* mpBegin; char* mpEnd; char* mpCapacity; unsigned int mAllocator;
    string8_s007c_c5f0() : mpBegin(&gEmptyChar), mpEnd(&gEmptyChar), mpCapacity(&gEmptyChar + 1), mAllocator(0) {}
    ~string8_s007c_c5f0() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin); }
    void clear() {
        if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; }
    }
};
typedef eastl::pair_s007c_c5f0<uint64, EA::AutoRefCount_s007c_c5f0<SP::cPropertyList_s007c_c5f0> > PropPair_s007c_c5f0;
typedef eastl::vector_s007c_c5f0<PropPair_s007c_c5f0, eastl::allocator_s007c_c5f0>                PropVec_s007c_c5f0;
typedef eastl::vector_map_s007c_c5f0<uint64, EA::AutoRefCount_s007c_c5f0<SP::cPropertyList_s007c_c5f0>,
                          eastl::less_s007c_c5f0<uint64>, eastl::allocator_s007c_c5f0, PropVec_s007c_c5f0> PropMap_s007c_c5f0;
namespace SP {
struct cOption_s007c_c5f0 {
    unsigned int mID;              // +0x00
    unsigned int mDefaultSetting;  // +0x04
    unsigned int mCurrentSetting;  // +0x08
    eastl::fixed_vector_s007c_c5f0<EA::AutoRefCount_s007c_c5f0<cPropertyList_s007c_c5f0>, 4, 1> mPropertySettings;  // +0x0c
    eastl::fixed_vector_s007c_c5f0<PropMap_s007c_c5f0, 4, 1>                         mExternalSettings;  // +0x34
    cOption_s007c_c5f0();  // 0x007cc6f0 (SP::cOption::cOption_s007c_c5f0)
    cOption_s007c_c5f0(const cOption_s007c_c5f0& x);  // 0x007cc6f0 (SP::cOption::cOption_s007c_c5f0)
    cOption_s007c_c5f0& operator=(const cOption_s007c_c5f0& x);
    ~cOption_s007c_c5f0();  // 0x007cc6f0 (SP::cOption::cOption_s007c_c5f0)
};
}
namespace SP {
typedef eastl::vector_s007c_c5f0<cOption_s007c_c5f0, sp_vector_allocator> cOptionVec;
}
namespace eastl {
template <typename T, typename A>
void vector_s007c_c5f0<T, A>::DoInsertValue(T* position, const T& value) {
    if (this->mpEnd != this->mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < this->mpEnd))
            ++pValue;
        ::new (this->mpEnd) T(*(this->mpEnd - 1));
        copy_backward_impl<0, std::random_access_iterator_tag>::do_copy(position, this->mpEnd - 1, this->mpEnd);
        *position = *pValue;
        ++this->mpEnd;
    } else {
        const size_type nPrevSize = size();
        const size_type nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        T* const pNewData = DoAllocate(nNewSize);
        T* pNewEnd = uninitialized_move_impl_s007c_c5f0<0, std::random_access_iterator_tag>::do_move_start(this->mpBegin, position, pNewData);
        uninitialized_move_impl_s007c_c5f0<0, std::random_access_iterator_tag>::do_move_commit(this->mpBegin, position, pNewData);
        ::new (pNewEnd) T(value);
        ++pNewEnd;
        T* const pNewEnd2 = uninitialized_move_impl_s007c_c5f0<0, std::random_access_iterator_tag>::do_move_start(position, this->mpEnd, pNewEnd);
        uninitialized_move_impl_s007c_c5f0<0, std::random_access_iterator_tag>::do_move_commit(position, this->mpEnd, pNewEnd);
        DoFree(this->mpBegin, capacity());
        this->mpBegin = pNewData;
        this->mpEnd = pNewEnd2;
        this->mpCapacity = pNewData + nNewSize;
    }
}
}
namespace eastl {
template <typename T, typename A>
void vector_s007c_c5f0<T, A>::push_back() {
    if (this->mpEnd != this->mpCapacity)
        ::new (this->mpEnd++) T();
    else
        DoInsertValue(this->mpEnd, T());
}
}
namespace eastl {
template <typename T, typename A>
T* vector_s007c_c5f0<T, A>::erase(T* first, T* last) {
    T* const position = copy_impl<0, std::random_access_iterator_tag>::do_copy(last, this->mpEnd, first);
    DoDestroyValues(position, this->mpEnd);
    this->mpEnd -= (last - first);
    return first;
}
}
namespace eastl {
template <typename T, typename A>
void vector_s007c_c5f0<T, A>::resize(size_type n) {
    if (n > (size_type)(this->mpEnd - this->mpBegin)) {
        T value;
        insert(this->mpEnd, n - (size_type)(this->mpEnd - this->mpBegin), value);
    } else {
        erase(this->mpBegin + n, this->mpEnd);
    }
}
}
struct cConfigScriptState_s007c_c5f0 { void Reset(); };
// ---- items of slice s007cc5f0 end

// ---- items of slice s007ce500 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" void  __cdecl EFree(void* p);                       // 0x00f47380
#pragma intrinsic(_InterlockedExchangeAdd)
struct VirtualObj {
    virtual void v0();
    virtual int Release();   // slot 1 (0x4)
    virtual void v2();
};
template <typename T> struct AutoRef_s007c_e500 {
    T* mpObject;
    ~AutoRef_s007c_e500() { if (mpObject) mpObject->Release(); }
};
struct VPair {
    uint64_t first;
    AutoRef_s007c_e500<VirtualObj> pObj;
};
struct VVec {
    VPair* mpBegin;   // +0
    VPair* mpEnd;     // +4
    VPair* mpEndCap;  // +8
    ~VVec();
};
// ---- items of slice s007ce500 end

// @ 0x00541680
char SP_ConfigManager_Init(void* param_1, int* param_2)
{
    char local_11 = 0;
    EADateTime_Set(1);
    wchar_t* s = (wchar_t*)*(int*)param_1;
    int y = 0, mo = 0, d = 0;
    int iVar1 = swscanf(s, L"%d-%d-%d", &y, &mo, &d);
    if (iVar1 == 3) {
        unsigned short* p = gCfgDateTable;
        while (*p != 0) p = p + 1;
        iVar1 = FUN_00454d50(gCfgDateTable, 0, (int)(p - gCfgDateTable));
        if (iVar1 != -1) {
            unsigned int h = 0, mi = 0;
            int se = 0;
            int iVar2 = swscanf(s + iVar1 + 1, L"%d:%d:%d", &h, &mi, &se);
            if (iVar2 == 3) {
                FUN_0092e200(y, mo, d, h, mi, se);
                unsigned short* q = gCfgTime12;
                while (*q != 0) q = q + 1;
                iVar2 = FUN_00454d50(gCfgTime12, iVar1, (int)(q - gCfgTime12));
                if (iVar2 == -1) {
                    unsigned short* r = gCfgTime24;
                    while (*r != 0) r = r + 1;
                    iVar1 = FUN_00454d50(gCfgTime24, iVar1, (int)(r - gCfgTime24));
                    iVar2 = swscanf(s + iVar1 + 1, L"%d:%d", &h, &mi);
                    if (iVar2 == 2) {
                        local_11 = 1;
                    } else {
                        iVar2 = swscanf(s + iVar1 + 1, L"%d", &h);
                        if (iVar2 == 1) {
                            mi = h % 100;
                            h = h / 100;
                            local_11 = 1;
                        }
                    }
                    if (local_11 != 0) {
                        if (s[iVar1] == L'-') {
                            FUN_0092e470(8, h);
                            FUN_0092e470(9, mi);
                        } else {
                            FUN_0092e470(8, -(int)h);
                            FUN_0092e470(9, -(int)mi);
                        }
                    }
                } else {
                    local_11 = 1;
                }
            }
        }
    }
    param_2[0] = 0;
    param_2[1] = 0;
    return local_11;
}

// @ 0x007c7a10
bool cConfigManager::SavePreferences()
{
    void* prefs = g_sAppPreferences;
    if (prefs != 0)
        return SaveResource(prefs, GetSaveArea(g_saveAreaName), 0);
    return false;
}

// @ 0x007c7aa0
const char* cOptionCheat::Description(int which)
{
    const char* s = "no arguments       lists all options\n[option]           list value of given option\n[option value]     sets option\n-reset             reset all options to default\n-save              save current options\n";
    if (which == 0)
        s = "lists options or sets an option";
    return s;
}

// @ 0x007c7ac0
bool cConfigScriptState::SetOptionDefault(uint32_t id, uint32_t value)
{
    cOption* begin = mOptionsBegin;
    for (unsigned i = 0; i < (unsigned)((int)((char*)mOptionsEnd - (char*)begin) / 0xac); i++) {
        if (begin[i].mID == id) {
            begin[i].mDefault = value;
            return true;
        }
    }
    return false;
}

// @ 0x007c7b30
void cConfigScriptState::DumpAll(void* args)
{
    __declspec(align(64)) char buf[92];
    for (int i = 0; i < 0x21; i++) {
        FormatDouble((double)mConfigNumbers[i], buf, 0x1f, 6, 0);
        void* s = FormatString(i, "cpuSpeed", buf);
        ((VFn1)VSLOT(args, 0x6c))(args, s);
    }
    String16* p = mConfigStrings;
    for (int off = 0, j = 0; off < 0xe0; off += 0x10, p++, j++) {
        void* s = FormatString(j, "userName", p->mpBegin);
        ((VFn1)VSLOT(args, 0x6c))(args, s);
    }
}

// @ 0x007c7be0
bool cConfigManager::Shutdown()
{
    void* cm = CheatManager();
    ((VFn1)VSLOT(cm, 0x1c))(cm, (void*)"option");
    if (mFileParser != 0) {
        ((VFn0)VSLOT(mFileParser, 0xc))(mFileParser);
        RC* old = mFileParser;
        if (old != 0) {
            mFileParser = 0;
            ((VFn0)VSLOT(old, 4))(old);
        }
    } else {
        ((VFn0)VSLOT(mScriptParser, 0xc))(mScriptParser);
    }
    RC* p = (RC*)mScriptParser;
    if (p != 0) {
        mScriptParser = 0;
        ((VFn0)VSLOT(p, 4))(p);
    }
    return true;
}

// @ 0x007c7c40
int cConfigManager::GetOption(uint32_t id)
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == id)
            return (int)p->mCurrent;
        p++;
    }
    return 0;
}

// @ 0x007c7c70
int cConfigManager::GetOptionDefault(uint32_t id)
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == id)
            return (int)p->mDefault;
        p++;
    }
    return 0;
}

// @ 0x007c7ca0
int cConfigManager::GetNumScreenResolutions()
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == 0x46170a1u)
            return (int)(p->mResEnd - p->mResBegin) >> 2;
        p++;
    }
    return 0;
}

// @ 0x007c7cd0
bool cConfigManager::GetScreenResolutionInfo(int i, uint32_t* p1, uint32_t* p2, uint32_t* p3)
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == 0x46170a1u)
            goto found;
        p++;
    }
    return false;
found:
    if (i < 0)
        return false;
    if (i >= (int)((p->mResEnd - p->mResBegin) >> 2))
        return false;
    uint32_t prop = ((uint32_t*)p->mResBegin)[i];
    *p1 = 0;
    *p2 = 0;
    *p3 = 0;
    TryGetUIntProperty((void*)prop, 0x38d0a06u, p1);
    TryGetUIntProperty((void*)prop, 0x38d0a07u, p2);
    TryGetUIntProperty((void*)prop, 0xd77e98u, p3);
    return true;
}

// @ 0x007c7d70
AutoRefCount** CopyConstructAutoRef(AutoRefCount** out, AutoRefCount* first, AutoRefCount* last, AutoRefCount* dest)
{
    *out = dest;
    for (; first != last; first++) {
        AutoRefCount* d = *out;
        if (d != 0) {
            d->m0  = first->m0;
            d->m4  = first->m4;
            d->mRC = first->mRC;
            if (d->mRC != 0)
                ((VFn0)VSLOT(d->mRC, 0))(d->mRC);
        }
        *out = *out + 1;
    }
    return out;
}

// @ 0x007c7e10
AutoRefCount* CopyAutoRef(AutoRefCount* first, AutoRefCount* last, AutoRefCount* dest)
{
    while (first != last) {
        dest->m0 = first->m0;
        dest->m4 = first->m4;
        RC* s = first->mRC;
        RC* d = dest->mRC;
        if (s != d) {
            if (s != 0)
                ((VFn0)VSLOT(s, 0))(s);
            dest->mRC = s;
            if (d != 0)
                ((VFn0)VSLOT(d, 4))(d);
        }
        first++;
        dest++;
    }
    return dest;
}

// @ 0x007c7e70
void cOptionBlockCommand::OnEndBlock(int)
{
    *(uint32_t*)((char*)mState + 0x58) = 0xffffffffu;
}

// @ 0x007c7eb0
void cCmdArgs::Do(int)
{
    mState->DumpAll(mArg);
}

// @ 0x007c7ec0
void SetResolutionCommand_Execute(void* self, void* args)
{
    int id = ((VFnI1)VSLOT((void*)*(uint32_t*)((char*)self + 4), 0x9c))(
        (void*)*(uint32_t*)((char*)self + 4), *(void**)args);
    cConfigScriptState* st = *(cConfigScriptState**)((char*)self + 0xc);
    cOption* op = st->mOptionsBegin;
    cOption* end = st->mOptionsEnd;
    while (op != end) {
        if (op->mID == 0x46170a1u)
            goto found;
        op++;
    }
    return;
found:
    {
        float ratio;
        uint32_t desktopW;
        uint32_t desktopH;
        uint8_t dmod[8];
        uint32_t best = 0;
        void* disp = DesktopDisplayMode(dmod);
        uint32_t* dm = (uint32_t*)disp;
        desktopW = dm[0];
        desktopH = dm[1];
        ratio = (float)desktopW / (float)desktopH;
        int count = (int)((op->mResEnd - op->mResBegin) >> 2);
        float bestScore = 3.4028234663852886e38f;
        int bestIdx = -1;
        for (int i = 0; i < count; i++) {
            uint32_t prop = ((uint32_t*)op->mResBegin)[i];
            uint32_t w = 0, h = 0, monitor = 0;
            if (prop != 0) {
                ((VFn1)VSLOT((void*)prop, 0x24))((void*)prop, &w);
                ((VFn1)VSLOT((void*)prop, 0x24))((void*)prop, &h);
                ((VFn1)VSLOT((void*)prop, 0x24))((void*)prop, &monitor);
            }
            float score = (float)((int)(desktopH - w) < 0 ? w - desktopH : desktopH - w) * 300000.0f
                        + (float)(int)monitor;
            if (score < bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        op->mDefault = bestIdx;
    }
}

// @ 0x007c80c0
void AutoRefVec::Destroy()
{
    void** it = mpBegin;
    void** e = mpEnd;
    for (; it < e; it++) {
        if (*it != 0)
            ((VFn0)VSLOT(*it, 4))(*it);
    }
    void* b = mpBegin;
    if (b != 0 && b != mInline[0])
        EA_Free(b);
}

// @ 0x007c8160
uint32_t* LowerBoundPair(uint32_t* first, uint32_t* last, uint32_t* key)
{
    int n = (int)((char*)last - (char*)first) >> 4;
    while (n > 0) {
        int half = n >> 1;
        uint32_t* mid = (uint32_t*)((char*)first + (half << 4));
        if (mid[1] < key[1] || (mid[1] == key[1] && mid[0] < key[0])) {
            first = (uint32_t*)((char*)mid + 0x10);
            n = n - 1 - half;
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x007c8270
void cOptionBlockCommand::OnRegister(void* a, void* b)
{
    mState = (cConfigScriptState*)b;
    ((Fn_0083c780)FUN_0083c780)(this, a, b);
    void* c;
    c = new ("ArgScript/OptionSetting", 0, 0, 0, 0) CmdOptionSetting();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_setting, c);
    c = new ("ArgScript/OptionBoolProperty", 0, 0, 0, 0) CmdOptionBoolProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_boolProp, c);
    c = new ("ArgScript/OptionIntProperty", 0, 0, 0, 0) CmdOptionIntProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_intProp, c);
    c = new ("ArgScript/OptionFloatProperty", 0, 0, 0, 0) CmdOptionFloatProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_floatProp, c);
    c = new ("ArgScript/OptionKeyProperty", 0, 0, 0, 0) CmdOptionKeyProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_keyProp, c);
    c = new ("ArgScript/OptionProperties", 0, 0, 0, 0) CmdOptionProperties();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_props, c);
}

// @ 0x007c84a0
void cVendorCommand::OnRegister(void* a, void* b)
{
    mState = (cConfigScriptState*)b;
    ((Fn_0083c780)FUN_0083c780)(this, a, b);
    void* c = new ("ArgScript/Card", 0, 0, 0, 0) CmdCard();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_card, c);
}

// @ 0x007c8530
void __cdecl RegisterConfigScriptCommands(void* parser)
{
    void* c;
    c = new ("ArgScript/OptionBlock", 0, 0, 0, 0) CmdOptionBlock();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_option, c);
    c = new ("ArgScript/Vendor", 0, 0, 0, 0) CmdVendor();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_vendor, c);
    c = new ("ArgScript/SetVariables", 0, 0, 0, 0) CmdSetVariables();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_setVariables, c);
    c = new ("ArgScript/SetOption", 0, 0, 0, 0) CmdSetOption();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_setOption, c);
    c = new ("ArgScript/Alert", 0, 0, 0, 0) CmdAlert();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_alert, c);
    c = new ("ArgScript/SetResolution", 0, 0, 0, 0) CmdSetResolution();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_setResolution, c);
    c = new ("ArgScript/BoolProperty", 0, 0, 0, 0) CmdBoolProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_boolProp2, c);
    c = new ("ArgScript/IntProperty", 0, 0, 0, 0) CmdIntProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_intProp2, c);
    c = new ("ArgScript/FloatProperty", 0, 0, 0, 0) CmdFloatProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_floatProp2, c);
    c = new ("ArgScript/KeyProperty", 0, 0, 0, 0) CmdKeyProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_keyProp2, c);
}

// @ 0x007c8880
void cConfigManager::SetScriptPath(const void* a, const void* b)
{
    if (mScriptParser == 0) {
        void* p = CreateParser();
        if (p != mScriptParser) {
            if (p != 0)
                ((VFn0)VSLOT(p, 0))(p);
            void* old = mScriptParser;
            mScriptParser = p;
            if (old != 0)
                ((VFn0)VSLOT(old, 4))(old);
        }
        ((VFn0)VSLOT(mScriptParser, 8))(mScriptParser);
        ((VFn2)VSLOT(mScriptParser, 0x24))(mScriptParser, 0, 1);
        ((VFn1)VSLOT(mScriptParser, 0x10))(mScriptParser, &mState);
        void* cm = CheatManager();
        void* c = ((VFnR)VSLOT(cm, 0x38))(cm);
        void* r = ((VFnR)VSLOT(c, 0xc4))(c);
        ((VFn1)VSLOT(mScriptParser, 0xbc))(mScriptParser, r);
        RegisterConfigScriptCommands(mScriptParser);
    }
    *(void**)((char*)this + 0x14) = (void*)a;
    *(void**)((char*)this + 0x1c) = (void*)b;
}

// @ 0x007c8940
void SP::cConfigManager::ApplyOption(SP::cOption const & opt)
{
    (void)opt;
}

// @ 0x007c8af0
// InsertAutoRef is supplied by its slice object; this object only calls it.
void* __cdecl InsertAutoRef(void* out, void* src);

// @ 0x007c8b70
void* __cdecl CopyStrings(void* first, void* last, void* dest)
{
    while (first != last) {
        if (first != dest)
            ((Str16*)dest)->assign(((Str16*)first)->a, ((Str16*)first)->b);
        first = (char*)first + 0x10;
        dest = (char*)dest + 0x10;
    }
    return dest;
}

// @ 0x007c8bb0
int __cdecl GetPropID(const char* name)
{
    int id = -1;
    if (isdigit((unsigned char)*name))
        return (int)strtoul(name, 0, 0);
    void* pm = PropertyManager();
    if (!((VFnIP)VSLOT_s007c_8940(pm, 0x18))(pm, name, &id))
        throw cError("no such property: %s", name);
    return id;
}

// @ 0x007c8c30
void cBoolPropertyCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    DirectPropertyList* pl = g_sAppProperties;
    pl->SetBoolProperty(GetPropID((const char*)a[0]),
        ((VFnB1)VSLOT_s007c_8940(mParser, 0x94))(mParser, (void*)a[1]));
}

// @ 0x007c8c80
void cIntPropertyCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    DirectPropertyList* pl = g_sAppProperties;
    pl->SetIntProperty(GetPropID((const char*)a[0]),
        ((VFnI1)VSLOT_s007c_8940(mParser, 0x9c))(mParser, (void*)a[1]));
}

// @ 0x007c8cd0
void cFloatPropertyCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    DirectPropertyList* pl = g_sAppProperties;
    pl->SetFloatProperty(GetPropID((const char*)a[0]),
        ((VFnF1)VSLOT_s007c_8940(mParser, 0x98))(mParser, (void*)a[1]));
}

// @ 0x007c8d20
void VariantPropertyCommand_Execute(cArguments* args)
{
    ArgList list;
    args->MainArguments(&list, 2, 0);
    (void)list;
}

// @ 0x007c8de0
void cSetOptionCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    int id = GetPropID((const char*)a[0]);
    int v = ((VFnI1)VSLOT_s007c_8940(mParser, 0xa0))(mParser, (void*)a[1]);
    if (!((cConfigScriptState_s007c_8940*)mState)->SetOptionDefault(id, (unsigned)v))
        throw cError("Unknown option: '%x'", id);
}

// @ 0x007c8e50
void cAlertCommand::Execute(cArguments* args)
{
    ArgList list;
    args->MainArguments(&list, 1, 2);
    uint32_t id = (uint32_t)list.a[0];
    int delay = 0x7d0;
    if (list.count > 1)
        delay = ((VFnI1)VSLOT_s007c_8940(mParser, 0x9c))(mParser, list.a[1]);
    int type = 2;
    if (args->HasFlag("info"))
        type = 0;
    if (args->HasFlag("warning"))
        type = 1;
    StateView* st = (StateView*)mState;
    bool show = args->HasFlag("always") || st->f40 || type != 2;
    if (type == 2) {
        if (st->f43)
            goto doalert;
        type = 1;
    }
    if (!st->f42)
        return;
doalert:
    if (show) {
        int v = 0;
        int* opt = (int*)args->OptionArguments((const char*)0x13fc890, 1);
        if (opt)
            v = *opt;
        DoAlert((void*)id, (void*)delay, (void*)(size_t)type, (void*)(size_t)v);
    }
    if (type == 2) {
        st->f41 = 1;
        throw cError("Terminal alert");
    }
}

// @ 0x007c8f70
void cCardCommand::Execute(cArguments* args)
{
    void** a = (void**)args->MainArguments(2);
    StateView* st = (StateView*)mState;
    if (st->vecBegin == st->vecEnd || st->flagD)
        return;
    int id = ((VFnI1)VSLOT_s007c_8940(mParser, 0xa0))(mParser, a[0]);
    if (id == (int)st->id) {
        st->flagD = true;
        st->str30.assign((char*)a[1], 0);
        void* flag = st->flagD ? (void*)0x13fc77c : (void*)0x13fc778;
        ((VFn2P)VSLOT_s007c_8940(mParser, 0x6c))(mParser, g_Cheat_isCardFound, flag);
        ((VFn2P)VSLOT_s007c_8940(mParser, 0x6c))(mParser, g_Cheat_cardName, a[1]);
    }
    void* flag = st->flagD ? (void*)0x13fc77c : (void*)0x13fc778;
    ((VFn2P)VSLOT_s007c_8940(mParser, 0x6c))(mParser, g_Cheat_isCardFound, flag);
}

// @ 0x007c9040
void cUnknownCmd::Execute(cArguments* args)
{
    ((VFn0)VSLOT_s007c_8940(mParser, 0x8c))(mParser);
    ArgList list;
    args->MainArguments(&list, 2, 0x7fffffff);
    StateView* st = (StateView*)mState;
    if (st->str30.a != st->str30.b) {
        st->str30.a[0] = 0;
        st->str30.b = st->str30.a;
    }
    if (st->flagD)
        return;
    char* name = (char*)list.a[0];
    for (int i = 1; i < list.count; i++) {
        int id = ((VFnI1)VSLOT_s007c_8940(mParser, 0xa0))(mParser, list.a[i]);
        if (id == (int)st->id) {
            st->str20.assign(name, 0);
            st->str30.assign(name, 0);
            ((VFn2P)VSLOT_s007c_8940(mParser, 0x6c))(mParser, g_Cheat_cardVendor, name);
        }
    }
}

// @ 0x007c9120
void cOptionCheat_s007c_8940::Execute(cArguments* args)
{
    ArgList list;
    args->MainArguments(&list, 0, 2);
    if (args->HasFlag("reset"))
        ((VFn0)VSLOT_s007c_8940(mManager, 0x40))(mManager);
    if (args->HasFlag("save"))
        ((VFn0)VSLOT_s007c_8940(mManager, 0x3c))(mManager);
    if (list.count >= 1) {
        int id = GetPropID((const char*)list.a[0]);
        if (list.count == 1) {
            int def = ((VFnI1)VSLOT_s007c_8940(mManager, 0x30))(mManager, (void*)id);
            int cur = ((VFnI2)VSLOT_s007c_8940(mManager, 0x34))(mManager, (void*)id, (void*)def);
            Output(mParser, "%s: default: %d, current: %d\n", list.a[0], def, cur);
        } else {
            int v = ((VFnI1)VSLOT_s007c_8940(mParser, 0x9c))(mParser, list.a[1]);
            ((void (__thiscall*)(void*, int, int))VSLOT_s007c_8940(mManager, 0x2c))(mManager, id, v);
        }
    }
    if (args->NumArguments() < 2) {
        // list all options
    }
}

// @ 0x007c9320
void cInitCommand::Init()
{
    if (mManager == 0) {
        void* fp = CreateFileParser_s007c_8940();
        ((void (__thiscall*)(void*, void*))VSLOT_s007c_8940(mManager, 0x8c))(mManager, fp);
    }
}

// @ 0x007c94f0
void cConfigManager_s007c_8940::SetOption(int id, unsigned setting)
{
    cOption_s007c_8940* p = mOptionsBegin;
    cOption_s007c_8940* e = mOptionsEnd;
    if (p != e) {
        while (p->id != (uint32_t)id) {
            p++;
            if (p == e)
                return;
        }
        if ((unsigned)((p->resEnd - p->resBegin) >> 2) > setting) {
            p->cur = setting;
            if (g_sAppPreferences != 0)
                ((void (__thiscall*)(void*, int, unsigned))0)(g_sAppPreferences, id, setting);
            ApplyOption(p);
        }
    }
}

// @ 0x007c95d0
void cConfigManager_s007c_8940::ResetToDefaults()
{
    cOption_s007c_8940* p = mOptionsBegin;
    if (p != mOptionsEnd) {
        do {
            p->cur = p->def;
            if (g_sAppPreferences != 0)
                ((void (__thiscall*)(void*, int, unsigned))0)(g_sAppPreferences, p->id, p->def);
            ApplyOption(p);
            p++;
        } while (p != mOptionsEnd);
    }
}

// @ 0x007c9680
void cConfigManager_s007c_8940::ApplyAllOptions()
{
    cOption_s007c_8940* p = mOptionsBegin;
    if (p != mOptionsEnd) {
        do {
            if (g_sAppPreferences != 0)
                ((void (__thiscall*)(void*, int, unsigned))0)(g_sAppPreferences, p->id, p->def);
            ApplyOption(p);
            p++;
        } while (p != mOptionsEnd);
    }
}

// @ 0x007c9760
bool cConfigManager_s007c_8940::GetConfigString(unsigned i, Str16* out)
{
    if (i < (unsigned)(mStringsEnd - mStrings)) {
        Str16* p = mStrings + i;
        if (p != out)
            out->assign(p->a, p->b);
        return true;
    }
    return false;
}

// @ 0x007c97a0
void* __cdecl UninitCopyAutoRef2(void* out, char* first, char* last, char* dest)
{
    *(char**)out = dest;
    for (; first != last; first += 0x18) {
        char* d = *(char**)out;
        if (d) {
            InsertAutoRef(d, first);
            d[0x14] = first[0x14];
        }
        *(char**)out += 0x18;
    }
    return out;
}

typedef void* (__thiscall *InsertThiscall_s007c_8940)(void*, void*);
static InsertThiscall_s007c_8940 volatile g_insertAutoRef_s007c_8940 = (InsertThiscall_s007c_8940)InsertAutoRef;

// @ 0x007c9830
void __cdecl FillAutoRef(char* first, unsigned n, char* src)
{
    char* volatile cur = first;
    while (n--) {
        if (cur) {
            g_insertAutoRef_s007c_8940((char*)cur, src);
            ((char*)cur)[0x14] = src[0x14];
        }
        cur = (char*)cur + 0x18;
    }
}

// @ 0x007c9910
void* __cdecl CopyAutoRefRange(void* first, void* last, void* dest)
{
    while (first != last) {
        if (dest) {
            InsertAutoRef(dest, first);
            ((char*)dest)[0x14] = ((char*)first)[0x14];
        }
        first = (char*)first + 0x18;
        dest = (char*)dest + 0x18;
    }
    return dest;
}

// @ 0x007c99e0
void Vec4::InsertOne(uint32_t* pos, uint32_t* value)
{
    uint32_t* end = mpEnd;
    if (end != mpCap) {
        if (pos <= value && value < end)
            value++;
        uint32_t last = 0;
        if (end)
            last = *(end - 1);
        if (end) {
            *end = last;
            if (last)
                ((RC*)last)->AddRef();
        }
        VecCopyRange(pos, end - 1, end);
        uint32_t old = *value;
        uint32_t cur = *pos;
        if (old != cur) {
            if (old)
                ((RC*)old)->AddRef();
            *pos = old;
            if (cur)
                ((RC*)cur)->Release();
        }
        mpEnd = end + 1;
        return;
    }
    int count = (int)(end - mpBegin) >> 2;
    unsigned cap = count ? (unsigned)count * 2 : 1;
    uint32_t* buf = cap ? (uint32_t*)EA_New(cap * 4, "App", 0, 0, 0, 0xd1) : 0;
    (void)VecDoInsertValue();
    (void)value;
    mpBegin = buf;
}

// @ 0x007c9bc0
void Vec4::InsertN(uint32_t* pos, int n, uint32_t* value)
{
    int size = (int)(mpCap - mpEnd) >> 2;
    if ((unsigned)size < (unsigned)n) {
        int count = (int)(mpEnd - mpBegin) >> 2;
        unsigned cap = count * 2;
        if (count == 0) cap = 1;
        unsigned need = (unsigned)count + n;
        if (need < cap) need = cap;
        uint32_t* buf = need ? (uint32_t*)EA_New(need * 4, "App", 0, 0, 0, 0xd1) : 0;
        (void)VecDoInsertValue();
        mpBegin = buf;
    }
    (void)pos; (void)value;
}

// @ 0x007c9dc0
void AutoRefVec_s007c_9910::InsertOne(AutoRef* pos, AutoRef* value)
{
    AutoRef* end = mpEnd;
    if (end != mpCap) {
        if (pos <= value && value < end)
            value++;
        if (end) {
            end->m0 = end[-1].m0;
            end->m4 = end[-1].m4;
            end->mRC = end[-1].mRC;
            if (end->mRC)
                end->mRC->AddRef();
        }
        VecCopyRange(pos, end - 1, end);
        pos->m0 = value->m0;
        pos->m4 = value->m4;
        RC* s = value->mRC;
        RC* d = pos->mRC;
        if (s != d) {
            if (s) s->AddRef();
            pos->mRC = s;
            if (d) d->Release();
        }
        mpEnd = end + 1;
        return;
    }
    int count = (int)(end - mpBegin);
    unsigned cap = count ? (unsigned)count * 2 : 1;
    AutoRef* buf = cap ? (AutoRef*)EA_New(cap * 0x10, "App", 0, 0, 0, 0xd1) : 0;
    (void)VecDoInsertValue();
    (void)value;
    mpBegin = buf;
}

// @ 0x007c9fa0
void AutoRefVec_s007c_9910::DoAssignFromIterator(AutoRef* first, AutoRef* last)
{
    AutoRef* b = mpBegin;
    int n = (int)(last - first);
    if (n > (int)(mpCap - b)) {
        AutoRef* nb = (AutoRef*)VecAllocGrow(n, first, last);
        VecDestroyRange16(b, mpEnd);
        if (b != 0 && b != mInline)
            EA_Free(b);
        mpBegin = nb;
        mpEnd = nb + n;
        mpCap = nb + n;
        return;
    }
    if (n <= (int)(mpEnd - b)) {
        AutoRef* e = (AutoRef*)VecCopyImpl(first, last, b);
        VecDestroyRange16(e, mpEnd);
        mpEnd = e;
        return;
    }
    AutoRef* mid = first + (mpEnd - b);
    VecCopyImpl(first, mid, b);
    VecUninitCopy(0, mid, last, mpEnd, 0);
    mpEnd = mpBegin + n;
}

// @ 0x007ca060
PairVec& PairVec::operator=(const PairVec& x)
{
    if (&x != this) {
        unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCap - mpBegin)) {
            Pair16* nb = (Pair16*)Reserve(n, x.mpBegin, x.mpEnd);
            DestroyRange(mpBegin, mpEnd);
            if (mpBegin) EA_Free(mpBegin);
            mpBegin = nb;
            mpEnd = nb + n;
            mpCap = nb + n;
            return *this;
        }
        if (n <= (unsigned)(mpEnd - mpBegin)) {
            Pair16* e = (Pair16*)VecCopyRange(x.mpBegin, x.mpEnd, mpBegin);
            DestroyRange(e, mpEnd);
            mpEnd = mpBegin + n;
            return *this;
        }
        Pair16* it = mpEnd;
        VecCopyRange(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
        VecUninitCopy(&it, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, (void*)&x);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x007ca150
void cConfigManager_s007c_9910::GetOptionIDs(UIntVec* out)
{
    out->reserve((unsigned)((int)((char*)mOptionsEnd - (char*)mOptionsBegin) / 0xac));
    cOption_s007c_9910* p = mOptionsBegin;
    while (p != mOptionsEnd) {
        out->push_back(p->id);
        p++;
    }
}

// @ 0x007ca1c0
void cConfigManager_s007c_9910::Initialize(const char* path)
{
    if (!mFileParser) {
        IFileParser* fp = CreateFileParser();
        IFileParser* oldFp = mFileParser;
        if (fp != oldFp) {
            if (fp)
                fp->AddRef();
            mFileParser = fp;
            if (oldFp)
                oldFp->Release();
        }
        mFileParser->v2();
        IParser* pa = CreateParser_s007c_9910();
        IParser* oldPa = mParser;
        if (pa != oldPa) {
            if (pa)
                pa->AddRef();
            mParser = pa;
            if (oldPa)
                oldPa->Release();
        }
        mFileParser->SetParser(mParser);
        mParser->Reset(0, 0);
        mParser->AddState(mState);
        mParser->SetFlags(GetCheatManager()->GetSub()->GetValue());
        RegisterConfigScriptCommands(mParser);
    }
    mFileParser->Begin();

    EaString str;
    str.assign(path, path + strlen(path));
    str.append("Options.txt", "Options.txt" + 11);
    mFileParser->SetPath(str.mpBegin, 5);
    if (!mFileParser->Run())
        return;

    IResAreaMgr* mgr = GetResMgr();
    void* area = GetSaveArea(0x11ac19e);
    SpUIntVec ids;
    SpUIntVec firsts;
    SpUIntVec counts;
    int numOptions = (int)(mOptionsEnd - mOptionsBegin);
    for (int oi = 0; oi != numOptions; oi++) {
        cOption_s007c_9910* o = &mOptionsBegin[oi];
        if (o->id == 0x46170a2 || o->id == 0x46170a1)
            continue;
        int n = (int)(o->resEnd - o->resBegin);
        int first = 0;
        if (n > 0) {
            PropList** pp = o->resBegin;
            while (*pp == 0) {
                first++;
                pp++;
                if (first >= n)
                    break;
            }
        }
        ids.push_back(o->id);
        firsts.push_back((uint32_t)first);
        counts.push_back((uint32_t)n);
        uint32_t id = o->id;
        for (int k = first; k < n; k++) {
            PropList* pl = o->resBegin[k];
            if (pl) {
                pl->mKey.instanceID = id;
                pl->mKey.typeID = 0xb1b104;
                pl->mKey.groupID = (k & 0xff) | 0x40470100;
                mgr->Register(o->resBegin[k], 0, area, 0, 0);
            }
            MapElem* me = &o->mapBegin[k];
            if (me->mpBegin != me->mpEnd) {
                int m = 1;
                for (MapElem::Entry* e = me->mpBegin; e != me->mpEnd; e++) {
                    ResourceKey key;
                    key.instanceID = e->a;
                    key.typeID = 0xb1b104;
                    key.groupID = e->b;
                    PropList* epl = e->pl;
                    {
                        Property p;
                        p.SetKey(key);
                        epl->SetProperty(0x5daaffe, &p);
                    }
                    epl->mKey.instanceID = id;
                    epl->mKey.typeID = 0xb1b104;
                    epl->mKey.groupID = ((((m & 0x1f) << 24) | 0x40470100) & 0xffffff00) | (k & 0xff);
                    m++;
                    mgr->Register(epl, 0, area, 0, 0);
                }
            }
        }
    }

    cPropertyList* list = new ("App/ConfigManager", 0, 0, 0, 0) cPropertyList();
    {
        Property p;
        p.Set(10, 0x98, ids.mpBegin, 4, (int)(ids.mpEnd - ids.mpBegin));
        list->SetProperty(0x5daafff, &p);
    }
    {
        Property p;
        p.Set(10, 0x98, firsts.mpBegin, 4, (int)(firsts.mpEnd - firsts.mpBegin));
        list->SetProperty(0x5dab000, &p);
    }
    {
        Property p;
        p.Set(10, 0x98, counts.mpBegin, 4, (int)(counts.mpEnd - counts.mpBegin));
        list->SetProperty(0x5dab001, &p);
    }
    list->mKey.instanceID = 0;
    list->mKey.typeID = 0xb1b104;
    list->mKey.groupID = 0x40470000;
    mgr->Register(list, 0, area, 0, 0);
}

// @ 0x007ca8e0
void MapVec::Destroy()
{
    // element-wise teardown of vector_map<u64,AutoRef> then free (see partial.txt)
}

// @ 0x007ca950
template PropPair* PropVec::insert(PropPair*, const PropPair&)
;

// @ 0x007ca9f0
template PropMap::iterator PropMap::insert(PropMap::iterator, const PropMap::value_type&)
;

// @ 0x007cab40
template void PropFixVec::resize(PropFixVec::size_type)
;

// @ 0x007cabc0
template eastl::pair_s007c_a950<PropMap::iterator, bool> PropMap::insert(const PropMap::value_type&)
;

// @ 0x007cac20
template EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950>& PropMap::operator[](const PropMap::key_type&)
;

// @ 0x007cace0
SP::cPropertyList_s007c_a950* GetPropListSettings(const void* pName, PropMap* pMap)
{
    EA::ResourceMan::Key_s007c_a950 key;
    key.mInstance = 0; key.mType = 0; key.mGroup = 0; key.mPad = 0;
    if (!SPKeyFromName(&key, (const wchar_t*)pName, 0, 0))
        ThrowBadPropListName();
    uint64 id = ((uint64)key.mInstance) | ((uint64)key.mGroup << 32);
    eastl::pair_s007c_a950<PropMap::iterator, bool> result =
        pMap->insert(PropMap::value_type(id, EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950>(0)));
    if (result.second) {
        SP::IPropertyManager* pm = SP::PropertyManager_s007c_a950();
        pm->HasPropertyList(key.mInstance, key.mGroup);
        Editor::cPropertyList_s007c_a950* pList = new ("App", 0, 0, 0, 0) Editor::cPropertyList_s007c_a950();
        result.first->second = pList;
    }
    return result.first->second.mpObject;
}

// @ 0x007cae30
void cOptionBoolPropertyCommand::Execute(EA::ArgScript::cArguments_s007c_a950* pArgs)
{
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList_s007c_a950* pList = GetTargetList(this, opt);
    if (pList) {
        bool b = mpSource->GetBool(main[1]);
        EA::Variant_s007c_a950 v;
        v = b;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007caf40
void cOptionIntPropertyCommand::Execute(EA::ArgScript::cArguments_s007c_a950* pArgs)
{
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList_s007c_a950* pList = GetTargetList(this, opt);
    if (pList) {
        int i = mpSource->GetInt(main[1]);
        EA::Variant_s007c_a950 v;
        v = i;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007cb050
void cOptionFloatPropertyCommand::Execute(EA::ArgScript::cArguments_s007c_a950* pArgs)
{
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList_s007c_a950* pList = GetTargetList(this, opt);
    if (pList) {
        float f = mpSource->GetFloat(main[1]);
        EA::Variant_s007c_a950 v;
        v = f;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007cb160
void cOptionPropertiesCommand::Execute(EA::ArgScript::cArguments_s007c_a950* pArgs)
{
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList_s007c_a950* pList = GetTargetList(this, opt);
    if (pList) {
        EA::ResourceMan::Key_s007c_a950 key;
        key.mInstance = 0; key.mType = 0; key.mGroup = 0; key.mPad = 0;
        SPKeyFromName(&key, (const wchar_t*)main[1], 0, 0);
        EA::Variant_s007c_a950 v;
        v = key;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007cb270
void SomeOptionPropertiesCommand::Execute(EA::ArgScript::cArguments_s007c_a950* pArgs)
{
    void** main = pArgs->MainArguments(1);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList_s007c_a950* pList = GetTargetList(this, opt);
    EA::ResourceMan::Key_s007c_a950 key;
    key.mInstance = 0; key.mType = 0; key.mGroup = 0; key.mPad = 0;
    SPKeyFromName(&key, (const wchar_t*)main[0], 0, 0);
    SP::IPropertyManager* pm = SP::PropertyManager_s007c_a950();
    EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950> result;
    if (pm->GetPropertyList(key.mInstance, key.mGroup, result) && pList)
        pList->v30(result.mpObject);
}

// @ 0x007cb390
namespace SP {
cOption_s007c_a950::~cOption_s007c_a950()
{}
}  // namespace SP

// @ 0x007cb3e0
template eastl::fixed_vector_s007c_a950<EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950>, 4, 1>::fixed_vector_s007c_a950(const eastl::fixed_vector_s007c_a950<EA::AutoRefCount_s007c_a950<SP::cPropertyList_s007c_a950>, 4, 1>&)
;

// @ 0x007cb450
template void eastl::fill<PropMap*, PropMap>(PropMap*, PropMap*, const PropMap&)
;

// @ 0x007cb590
namespace SP {
void cConfigScriptState_s007c_b590::GatherInformation()
{
    SpStringVecView* sv = reinterpret_cast<SpStringVecView*>(&mConfigStrings);
    SpFloatVecView*  nv = reinterpret_cast<SpFloatVecView*>(&mConfigNumbers);
    sv->resize(0xe);
    nv->resize(0x21);
    DevCaps* caps = GetD3DCAPS9();
    CBig big;
    GetSystemInfo(&big);

#define str sv->mpBegin
#define num nv->mpBegin

    str[2].assign("Spore", "Spore" + 5);
    str[4].assign("1.0.0", "1.0.0" + 5);
    str[13].assign("Unknown", "Unknown" + 7);
    str[13].assign("Release", "Release" + 7);
    AssignRaw(str[1], big.s[0]);
    AssignRaw(str[0], big.s[1]);
    AssignRaw(str[7], big.s[2]);
    AssignRaw(str[5], big.s[3]);
    AssignRaw(str[6], big.s[4]);
    AssignRaw(str[8], big.s[5]);
    AssignRaw(str[9], big.s[6]);
    AssignRaw(str[4], big.s[7]);

    PathObj path(EA::ConvertToString16(*(string8*)&big.s[8]).mpBegin);
    str[2] = EA::ConvertToString8(path.GetFirst(), -1);
    str[3] = EA::ConvertToString8(path.GetSecond(), -1);

    num[0] = big.f90;
    num[1] = (float)big.i94;
    num[2] = (big.b9b && big.b9a) ? 1.0f : 0.0f;
    num[3] = big.b9b ? 1.0f : 0.0f;
    num[6] = big.fa8;
    num[7] = big.fac;
    num[8] = big.fa0;
    num[9] = big.fa4;
    num[0x1f] = !FUN_006b8250() ? 1.0f : 0.0f;
    { float* p = &num[0x20]; *p = (float)FUN_006b8410(); }
    ((unsigned short*)&caps->deviceId)[1] = 0;
    if (!mOverrideCardIDs) {
        mVendorID = caps->vendorId;
        mCardID = caps->deviceId;
    }
    DispMode dm = D3D9GetDesktopDisplayMode();
    num[10] = (float)dm.width;
    num[11] = (float)dm.height;
    num[13] = (float)dm.refresh;
    { float* p = &num[14]; *p = (float)g_sAppProperties_s007c_b590->GetDescription(0x38d0a09); }
    num[15] = 0.0f;
    num[16] = (float)caps->dispW / (float)caps->dispH;
    { float* p = &num[17]; *p = (float)(g_pD3D9Device->vt->GetAvailableTextureMem(g_pD3D9Device) >> 20); }
    num[18] = (float)caps->maxSimultaneousTextures;
    string8_sprintf(&str[10], "0x%08x%08x", caps->driverHigh, caps->driverLow);
    {
        const char* d = caps->description;
        const char* e = d;
        while (*e++) {}
        str[11].assign(d, d + (e - (d + 1)));
    }
    string8_sprintf(&str[12], "vendor:0x%04x, card:0x%04x", caps->vendorId, caps->deviceId);
    unsigned int vsVer = (caps->vsMajor << 8) | caps->vsMinor;
    unsigned int psVer = (caps->psMajor << 8) | caps->psMinor;
    num[0x13] = (float)vsVer;
    num[0x14] = (float)psVer;
    num[0x15] = (float)caps->numSimultaneousRTs;
    num[0x16] = (float)caps->maxVertexShaderConst;
    num[0x17] = 8.0f;
    num[0x18] = 256.0f;
    num[0x19] = 96.0f;
    num[0x1b] = 12.0f;
    if (psVer >= 0x300) {
        num[0x17] = 224.0f;
        num[0x18] = (float)caps->maxVS30Slots;
        num[0x19] = (float)caps->maxPS30Slots;
        num[0x1b] = 32.0f;
    } else if (psVer >= 0x200) {
        num[0x17] = 32.0f;
        num[0x19] = (float)(int)caps->ps20NumInstructionSlots;
        num[0x1b] = (float)(int)caps->ps20NumTemps;
    }
    num[0x1c] = g_sAppProperties_s007c_b590->GetDescription(0x668d4fa1) ? 1.0f : 0.0f;
    num[0x1d] = big.b9c ? 1.0f : 0.0f;
    num[0x1e] = IsVistaKB940105Required() ? 1.0f : 0.0f;
    unsigned int drv = caps->driverLow;
    num[4] = (float)((drv >> 16) * 10000 + (drv & 0xffff));
    num[5] = IsDebuggerPresent() ? 1.0f : 0.0f;
#undef str
#undef num
}
}  // namespace SP

// @ 0x007cbd60
template PropMap_s007c_b590* MapFixVec::erase(PropMap_s007c_b590*, PropMap_s007c_b590*)
;

// @ 0x007cbdc0
template void MapFixVec::insert(PropMap_s007c_b590*, MapFixVec::size_type, const PropMap_s007c_b590&)
;

// @ 0x007cc000
template void MapFixVec::DoAssignFromIterator<const PropMap_s007c_b590*>(const PropMap_s007c_b590*, const PropMap_s007c_b590*, std::random_access_iterator_tag)
;

// @ 0x007cc110
namespace SP {
cConfigScriptState_s007c_b590::cConfigScriptState_s007c_b590()
: mpVtable(0), mVendorID(0), mCardID(0), mOverrideCardIDs(false), mFoundCard(false),
      mFirstRun(false), mAbortApp(false), mPad42(false), mPad43(true),
      mCurrentOptionID(0), mCurrentOptionSetting(0) {}
}  // namespace SP

// @ 0x007cc190
SP::cConfigScriptState::~cConfigScriptState()
{}

// @ 0x007cc260
namespace SP {
cConfigManager_s007c_b590::~cConfigManager_s007c_b590()
{}
}  // namespace SP

// @ 0x007cc310
namespace SP {
cConfigManager_s007c_b590::cConfigManager_s007c_b590()
: mpVtable0(0), mpVtable1(0), mRefCount(0), mpPad0c(0), mpPad10(0),
      mPad14(0x9a06678c), mPad18(0x24a0e52), mPad1c(0),
      mPadA8(-1), mPadAC(false), mPadAD(false), mpPadB0(0) {}
}  // namespace SP

// @ 0x007cc3c0
template void MapFixVec::resize(MapFixVec::size_type)
;

// @ 0x007cc480
namespace SP {
void SettingCommand::Execute(EA::ArgScript::cArguments_s007c_b590* pArgs)
{
    void** main = pArgs->MainArguments(1);
    unsigned int setting = mpSource->GetSetting(main[0]);
    OptionTable2* t = mpTable;
    t->mIndex = setting;
    char* p = t->mBase + t->mCount * 0xac;
    SP::cOption_s007c_b590* pOption = (SP::cOption_s007c_b590*)p;
    unsigned int size = (unsigned int)(pOption->mPropertySettings.mpEnd - pOption->mPropertySettings.mpBegin);
    if (size <= (unsigned int)t->mIndex) {
        pOption->mPropertySettings.resize((size_t)t->mIndex + 1);
        pOption->mExternalSettings.resize((size_t)t->mIndex + 1);
    }
    EA::AutoRefCount_s007c_b590<SP::cPropertyList_s007c_b590>* pSlot = pOption->mPropertySettings.mpBegin + t->mIndex;
    if (pSlot->mpObject == 0) {
        SP::cPropertyList_s007c_b590* pList = new ("App", 0, 0, 0, 0) Editor::cPropertyList_s007c_b590();
        *pSlot = pList;
    }
}
}  // namespace SP

// @ 0x007cc580
inline void AssignRaw(string8& dst, const StrRaw& src)
{
    if ((const void*)&src != (const void*)&dst)
        dst.assign(src.b, src.e);
}

// @ 0x007cc5f0
SP::cOption & SP::cOption::operator=(SP::cOption const & x)
{
    mID = x.mID;
    mDefaultSetting = x.mDefaultSetting;
    mCurrentSetting = x.mCurrentSetting;
    mPropertySettings = x.mPropertySettings;
    mExternalSettings = x.mExternalSettings;
    return *this;
}

// @ 0x007cc6f0
SP::cOption_s007c_c5f0::cOption_s007c_c5f0(const cOption_s007c_c5f0& x)
: mID(x.mID), mDefaultSetting(x.mDefaultSetting), mCurrentSetting(x.mCurrentSetting),
      mPropertySettings(x.mPropertySettings), mExternalSettings(x.mExternalSettings) {}

// @ 0x007cc7f0
template void SP::cOptionVec::DoInsertValue(SP::cOption_s007c_c5f0*, const SP::cOption_s007c_c5f0&)
;

// @ 0x007cc9a0
template void SP::cOptionVec::push_back()
;

// @ 0x007ccb10
void cOptionBlockCommandExecute(void*, EA::ArgScript::cArguments_s007c_c5f0*)
{}

// @ 0x007ccc30
void cConfigScriptState_s007c_c5f0::Reset()
{
    char* p = (char*)this;
    *(int*)(p + 0x58) = -1;
    *(int*)(p + 0x5c) = -1;
    SP::cOptionVec* pOptions = (SP::cOptionVec*)(p + 0x44);
    pOptions->erase(pOptions->mpBegin, pOptions->mpEnd);
    *(char*)(p + 0xd) = 0;
    string8_s007c_c5f0* pS0 = (string8_s007c_c5f0*)(p + 0x10); pS0->clear();
    string8_s007c_c5f0* pS1 = (string8_s007c_c5f0*)(p + 0x20); pS1->clear();
    string8_s007c_c5f0* pS2 = (string8_s007c_c5f0*)(p + 0x30); pS2->clear();
}
template SP::cOption_s007c_c5f0* SP::cOptionVec::erase(SP::cOption_s007c_c5f0*, SP::cOption_s007c_c5f0*);

// @ 0x007cccc0
void cConfigManagerAddResolutionOption(void*)
{}

// @ 0x007cce50
void cConfigManagerLoadResolutionOptions(void*)
{}

// @ 0x007cd340
void cConfigManagerLoadOptionSetup(void*)
{}

// @ 0x007cd6d0
void cConfigManagerInitialize(void*)
{}

// @ 0x007cd7a0
void cConfigManagerSetupParser(void*, void*, bool)
{}

// @ 0x007cd8b0
void cConfigManagerTryConfigure(void*)
{}

// @ 0x007cd8d0
void cConfigManagerConfigure(void*)
{}

// @ 0x007cef60
VVec::~VVec()
{
    for (VPair* p = mpBegin; p < mpEnd; p = (VPair*)((char*)p + 0x10))
        p->~VPair();
    if (mpBegin)
        EFree(mpBegin);
}
