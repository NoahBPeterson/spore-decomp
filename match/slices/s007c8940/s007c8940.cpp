// Slice s007c8940 -- SP::cConfigManager option application / ArgScript commands.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------- masked externs
void*    __cdecl PropertyManager();     // 0x0067de30
void*    __cdecl CheatManager();        // 0x0067de20
void*    __cdecl MessageServer();       // 0x0067dcc0
void*    __cdecl CreateParser();        // 0x008408d0
void*    __cdecl CreateFileParser();    // 0x00840940
void     __cdecl RegisterConfigScriptCommands(void*);   // 0x007c8530
void*    __cdecl EA_New(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
void     __cdecl EA_Free(void*);        // 0x00f47380
int      __cdecl Output(void* stream, const char* fmt, ...);  // 0x00841000
void     __cdecl DoAlert(void* a, void* b, void* c, void* d); // 0x006bb1c0

__declspec(dllimport) int __cdecl isdigit(int c);                       // IAT 0x13cc4cc
__declspec(dllimport) unsigned long __cdecl strtoul(const char*, char**, int); // IAT 0x13cc4f8

typedef void  (__thiscall *VFn0)(void*);
typedef void  (__thiscall *VFn1)(void*, void*);
typedef int   (__thiscall *VFnI1)(void*, void*);
typedef int   (__thiscall *VFnI2)(void*, void*, void*);
typedef bool  (__thiscall *VFnB1)(void*, void*);
typedef bool  (__thiscall *VFnIP)(void*, const char*, void*);
typedef void  (__thiscall *VFn2P)(void*, void*, void*);
typedef float (__thiscall *VFnF1)(void*, void*);
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

inline void* operator new(size_t size, const char* n, int f, unsigned d, const char* fi, int l)
{ return EA_New((unsigned)size, n, f, (int)d, fi, l); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

// ---------------------------------------------------------------- globals
struct DirectPropertyList;
extern DirectPropertyList* g_sAppProperties;   // 0x015fd918
extern void* g_sAppPreferences;                // 0x015fd91c
extern void* g_Cheat_isCardFound;              // 0x0153d1e4
extern void* g_Cheat_cardName;                 // 0x0153d1e0
extern void* g_Cheat_cardVendor;               // 0x0153d1dc

// ---------------------------------------------------------------- types
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

struct cOption {
    uint32_t id;
    uint32_t def;
    uint32_t cur;
    uint8_t* resBegin;
    uint8_t* resEnd;
    char     pad[0xac - 0x14];
};

struct cConfigManager {
    char pad00[0x64];
    cOption* mOptionsBegin;   // +0x64
    cOption* mOptionsEnd;     // +0x68
    char pad6c[0x80 - 0x6c];
    Str16* mStrings;          // +0x80
    Str16* mStringsEnd;       // +0x84

    void ApplyOption(cOption* opt);                  // 0x007c8940
    void SetOption(int id, unsigned setting);        // 0x007c94f0
    void ResetToDefaults();                          // 0x007c95d0
    void ApplyAllOptions();                          // 0x007c9680
    bool GetConfigString(unsigned i, Str16* out);    // 0x007c9760
};

struct cConfigScriptState {
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

// ---------------------------------------------------------------- helpers
int __cdecl GetPropID(const char* name);              // 0x007c8bb0
void* __cdecl CopyStrings(void* first, void* last, void* dest); // 0x007c8b70

// @ 0x007c8bb0
int __cdecl GetPropID(const char* name)
{
    int id = -1;
    if (isdigit((unsigned char)*name))
        return (int)strtoul(name, 0, 0);
    void* pm = PropertyManager();
    if (!((VFnIP)VSLOT(pm, 0x18))(pm, name, &id))
        throw cError("no such property: %s", name);
    return id;
}

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

// @ 0x007c8c30
void cBoolPropertyCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    DirectPropertyList* pl = g_sAppProperties;
    pl->SetBoolProperty(GetPropID((const char*)a[0]),
        ((VFnB1)VSLOT(mParser, 0x94))(mParser, (void*)a[1]));
}

// @ 0x007c8c80
void cIntPropertyCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    DirectPropertyList* pl = g_sAppProperties;
    pl->SetIntProperty(GetPropID((const char*)a[0]),
        ((VFnI1)VSLOT(mParser, 0x9c))(mParser, (void*)a[1]));
}

// @ 0x007c8cd0
void cFloatPropertyCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    DirectPropertyList* pl = g_sAppProperties;
    pl->SetFloatProperty(GetPropID((const char*)a[0]),
        ((VFnF1)VSLOT(mParser, 0x98))(mParser, (void*)a[1]));
}

// @ 0x007c8de0
void cSetOptionCommand::Execute(cArguments* args)
{
    int* a = (int*)args->MainArguments(2);
    int id = GetPropID((const char*)a[0]);
    int v = ((VFnI1)VSLOT(mParser, 0xa0))(mParser, (void*)a[1]);
    if (!((cConfigScriptState*)mState)->SetOptionDefault(id, (unsigned)v))
        throw cError("Unknown option: '%x'", id);
}

// ---------------------------------------------------------------- manager option application
// @ 0x007c94f0
void cConfigManager::SetOption(int id, unsigned setting)
{
    cOption* p = mOptionsBegin;
    cOption* e = mOptionsEnd;
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
void cConfigManager::ResetToDefaults()
{
    cOption* p = mOptionsBegin;
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
void cConfigManager::ApplyAllOptions()
{
    cOption* p = mOptionsBegin;
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
bool cConfigManager::GetConfigString(unsigned i, Str16* out)
{
    if (i < (unsigned)(mStringsEnd - mStrings)) {
        Str16* p = mStrings + i;
        if (p != out)
            out->assign(p->a, p->b);
        return true;
    }
    return false;
}

// @ 0x007c8940
void cConfigManager::ApplyOption(cOption* opt)
{
    (void)opt;
}

// ---------------------------------------------------------------- remaining commands
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
struct cOptionCheat  : CCmd { char pad10[4]; cConfigManager* mManager; void Execute(cArguments*); };
struct cCardCommand  : CCmd { void Execute(cArguments*); };
struct cUnknownCmd   : CCmd { void Execute(cArguments*); };
struct cInitCommand  : CCmd { char pad10[4]; cConfigManager* mManager; void Execute(cArguments*); void Init(); };

// @ 0x007c8f70
void cCardCommand::Execute(cArguments* args)
{
    void** a = (void**)args->MainArguments(2);
    StateView* st = (StateView*)mState;
    if (st->vecBegin == st->vecEnd || st->flagD)
        return;
    int id = ((VFnI1)VSLOT(mParser, 0xa0))(mParser, a[0]);
    if (id == (int)st->id) {
        st->flagD = true;
        st->str30.assign((char*)a[1], 0);
        void* flag = st->flagD ? (void*)0x13fc77c : (void*)0x13fc778;
        ((VFn2P)VSLOT(mParser, 0x6c))(mParser, g_Cheat_isCardFound, flag);
        ((VFn2P)VSLOT(mParser, 0x6c))(mParser, g_Cheat_cardName, a[1]);
    }
    void* flag = st->flagD ? (void*)0x13fc77c : (void*)0x13fc778;
    ((VFn2P)VSLOT(mParser, 0x6c))(mParser, g_Cheat_isCardFound, flag);
}

// @ 0x007c9040
void cUnknownCmd::Execute(cArguments* args)
{
    ((VFn0)VSLOT(mParser, 0x8c))(mParser);
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
        int id = ((VFnI1)VSLOT(mParser, 0xa0))(mParser, list.a[i]);
        if (id == (int)st->id) {
            st->str20.assign(name, 0);
            st->str30.assign(name, 0);
            ((VFn2P)VSLOT(mParser, 0x6c))(mParser, g_Cheat_cardVendor, name);
        }
    }
}

// @ 0x007c8e50
void cAlertCommand::Execute(cArguments* args)
{
    ArgList list;
    args->MainArguments(&list, 1, 2);
    uint32_t id = (uint32_t)list.a[0];
    int delay = 0x7d0;
    if (list.count > 1)
        delay = ((VFnI1)VSLOT(mParser, 0x9c))(mParser, list.a[1]);
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

// @ 0x007c9120
void cOptionCheat::Execute(cArguments* args)
{
    ArgList list;
    args->MainArguments(&list, 0, 2);
    if (args->HasFlag("reset"))
        ((VFn0)VSLOT(mManager, 0x40))(mManager);
    if (args->HasFlag("save"))
        ((VFn0)VSLOT(mManager, 0x3c))(mManager);
    if (list.count >= 1) {
        int id = GetPropID((const char*)list.a[0]);
        if (list.count == 1) {
            int def = ((VFnI1)VSLOT(mManager, 0x30))(mManager, (void*)id);
            int cur = ((VFnI2)VSLOT(mManager, 0x34))(mManager, (void*)id, (void*)def);
            Output(mParser, "%s: default: %d, current: %d\n", list.a[0], def, cur);
        } else {
            int v = ((VFnI1)VSLOT(mParser, 0x9c))(mParser, list.a[1]);
            ((void (__thiscall*)(void*, int, int))VSLOT(mManager, 0x2c))(mManager, id, v);
        }
    }
    if (args->NumArguments() < 2) {
        // list all options
    }
}

// @ 0x007c8d20
void VariantPropertyCommand_Execute(cArguments* args)
{
    ArgList list;
    args->MainArguments(&list, 2, 0);
    (void)list;
}

// @ 0x007c8af0
void* __cdecl InsertAutoRef(void* out, void* src)
{
    (void)out; (void)src;
    return out;
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

// @ 0x007c9830
void __cdecl FillAutoRef(char* first, unsigned n, char* src)
{
    while (n--) {
        if (first) {
            InsertAutoRef(first, src);
            first[0x14] = src[0x14];
        }
        first += 0x18;
    }
}

// @ 0x007c9320
void cInitCommand::Init()
{
    if (mManager == 0) {
        void* fp = CreateFileParser();
        ((void (__thiscall*)(void*, void*))VSLOT(mManager, 0x8c))(mManager, fp);
    }
}

void cInitCommand::Execute(cArguments*)
{
    Init();
}
