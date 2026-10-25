// Slice s007c8940 -- SP::cConfigManager option application / ArgScript commands.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

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
typedef bool  (__thiscall *VFnB2)(void*, void*, void*);
typedef bool  (__thiscall *VFnIP)(void*, const char*, void*);
typedef void  (__thiscall *VFn2P)(void*, void*, void*);
typedef float (__thiscall *VFnF1)(void*, void*);
typedef void  (__thiscall *VFn4)(void*, void*, void*, void*, void*);
typedef char  (__thiscall *VFnC3)(void*, void*, void*, void*);
typedef void* (__thiscall *VFnP1)(void*, void*);
typedef void* (__thiscall *VFnP0)(void*);
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
    char     pad14[0x34 - 0x14];
    void*    mBehaviors;      // +0x34 (array of 0x18-byte behavior headers)
    char     pad38[0xac - 0x38];
};

// 0x34 array element: pointer pair to 0x10-byte behavior entries.
struct OptionBehavior { int* elems; int* elemsEnd; int pad8[4]; };
struct BehaviorElem { int key; int value; int arg; int pad; };

// 0x40 behavior message allocated and posted by ApplyOption.
struct BehaviorMsg {
    void* vt;        // +0x00
    long  refs;      // +0x04
    void* field8;    // +0x08
    void* fieldC;    // +0x0c
    void* field10;   // +0x10
    void* field14;   // +0x14
    void* field18;   // +0x18
    char  pad1c[0x30 - 0x1c];
    void* field30;   // +0x30
    char  pad34[0x38 - 0x34];
    void* field38;   // +0x38
};

// EA::Variant: 16-byte payload, flags at +0x10, type id at +0x12.
struct Variant {
    uint32_t data[4];
    uint16_t flags;
    uint16_t type;
    void __thiscall Clear(int full);                 // 0x0093db80
    Variant* __thiscall SetUInt(const unsigned* v);  // 0x00427fd0
    Variant* __thiscall AssignKey(const void* key);  // 0x00422f40
};
struct ResourceKey { uint32_t a, b, c; };

// eastl::string (empty-string sentinel is a global).
struct EString {
    char* begin;
    char* end;
    char* cap;
    void __thiscall assign(const char* first, const char* last);  // 0x00454cb0
    void __thiscall append(const char* first, const char* last);  // 0x00455d60
};
extern char g_emptyString16[];      // 0x01667bac

extern char g_vt_13eb90c[];         // 0x013eb90c
extern char g_vt_13eb844[];         // 0x013eb844

struct cConfigManager {
    char pad00[0x64];
    cOption* mOptionsBegin;   // +0x64
    cOption* mOptionsEnd;     // +0x68
    char pad6c[0x80 - 0x6c];
    Str16* mStrings;          // +0x80
    Str16* mStringsEnd;       // +0x84
    char pad88[0xb0 - 0x88];
    void*  mNotifier;         // +0xb0 (object whose vt[0x30] is applied)

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
void __cdecl SPKeyFromName(void* outKey, const char* name, int a, int b);       // 0x0068d5a0
void* __cdecl CopyConstructAutoRef(void* out, void* first, void* last, void* dest, void* tag); // 0x007c7d70

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
            if (g_sAppPreferences != 0) {
                Variant v;
                v.flags = 0; v.type = 0;
                v.SetUInt(&setting);
                ((VFn2P)VSLOT(g_sAppPreferences, 0x14))(g_sAppPreferences, (void*)id, &v);
                if (v.flags & 4)
                    v.Clear(0);
            }
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
            if (g_sAppPreferences != 0) {
                Variant v;
                v.flags = 0; v.type = 10; v.data[0] = p->def;
                ((VFn2P)VSLOT(g_sAppPreferences, 0x14))(g_sAppPreferences, (void*)p->id, &v);
                if (v.flags & 4)
                    v.Clear(0);
            }
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
            if (g_sAppPreferences != 0) {
                Variant* got = 0;
                if (((VFnB2)VSLOT(g_sAppPreferences, 0x24))(g_sAppPreferences, (void*)p->id, &got)
                    && got->type == 10) {
                    if (got->flags & 0x30)
                        p->cur = *(int*)got->data[0];
                    else
                        p->cur = (int)got->data[0];
                } else {
                    p->cur = p->def;
                    Variant v;
                    v.flags = 0; v.type = 10; v.data[0] = p->def;
                    ((VFn2P)VSLOT(g_sAppPreferences, 0x14))(g_sAppPreferences, (void*)p->id, &v);
                    if (v.flags & 4)
                        v.Clear(0);
                }
            }
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
    if (opt->cur < (unsigned)((opt->resEnd - opt->resBegin) >> 2)) {
        int value = ((int*)opt->resBegin)[opt->cur];
        if (value != 0) {
            void* notifier = mNotifier;
            ((VFn1)VSLOT(notifier, 0x30))(notifier, (void*)value);
        }
        OptionBehavior* ob = (OptionBehavior*)((char*)opt->mBehaviors + opt->cur * 0x18);
        int count = (int)((ob->elemsEnd - ob->elems) >> 4);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                BehaviorElem* e = (BehaviorElem*)ob->elems + i;
                Variant* out = 0;
                void* pm = PropertyManager();
                char ok = ((VFnC3)VSLOT(pm, 0x2c))(pm, (void*)e->key,
                                                   (void*)e->value, &out);
                if (ok) {
                    ((VFn1)VSLOT(out, 0x30))(out, (void*)e->arg);
                    BehaviorMsg* msg = (BehaviorMsg*)operator new(0x40, "App", 0, 0, 0, 0);
                    if (msg) {
                        msg->field30 = (void*)0xf62def;
                        msg->vt = g_vt_13eb90c;
                        _InterlockedExchange(&msg->refs, 0);
                        msg->vt = g_vt_13eb844;
                        msg->field38 = 0;
                        ((VFn0)VSLOT(msg, 4))(msg);
                    }
                    msg->field8 = (void*)0xb1b104;
                    msg->field10 = (void*)e->value;
                    msg->field18 = (void*)e->key;
                    void* ms = MessageServer();
                    ((VFn4)VSLOT(ms, 0x18))(ms, (void*)0xf62ade, msg, 0, 0);
                    ((VFn0)VSLOT(msg, 8))(msg);
                }
                if (out)
                    ((VFn0)VSLOT(out, 4))(out);
            }
        }
    }
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
struct cOptionCheat  : CCmd { cConfigManager* mManager; void Execute(cArguments*); };
struct cCardCommand  : CCmd { void Execute(cArguments*); };
struct cUnknownCmd   : CCmd { void Execute(cArguments*); };
struct cInitCommand  : CCmd { void* mParser2; char pad14[0xc]; const char* mName; void Execute(cArguments*); void Init(const char* prefix); };

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
            Output(mParser, "%s: default: %d, current: %d\n", list.a[0],
                   ((VFnI1)VSLOT(mManager, 0x34))(mManager, (void*)id),
                   ((VFnI1)VSLOT(mManager, 0x30))(mManager, (void*)id));
        } else {
            int v = ((VFnI1)VSLOT(mParser, 0x9c))(mParser, list.a[1]);
            ((void (__thiscall*)(void*, int, int))VSLOT(mManager, 0x2c))(mManager, id, v);
        }
    }
    if (args->NumArguments() < 2) {
        int* vb = 0; int* ve = 0; int* vc = 0;
        ((void (__thiscall*)(void*, void*))VSLOT(mManager, 0x38))(mManager, &vb);
        int n = (int)((char*)ve - (char*)vb) >> 2;
        for (int i = 0; i < n; i++) {
            void* pm = PropertyManager();
            void* name = ((VFnP1)VSLOT(pm, 0x1c))(pm, (void*)vb[i]);
            int id = vb[i];
            if (name == 0) {
                Output(mParser, "0x%08x   default: %2d, current: %2d\n", (void*)id,
                       ((VFnI1)VSLOT(mManager, 0x34))(mManager, (void*)id),
                       ((VFnI1)VSLOT(mManager, 0x30))(mManager, (void*)id));
            } else {
                Output(mParser, "%-40.40s: default: %2d, current: %2d\n", name,
                       ((VFnI1)VSLOT(mManager, 0x34))(mManager, (void*)id),
                       ((VFnI1)VSLOT(mManager, 0x30))(mManager, (void*)id));
            }
        }
        if (vb && vb[-1] != 0)
            EA_Free(vb);
    }
}

// @ 0x007c8d20
void VariantPropertyCommand_Execute(cArguments* args)
{
    void** a = (void**)args->MainArguments(2);
    ResourceKey key;
    key.a = 0; key.b = 0; key.c = 0;
    SPKeyFromName(&key, (const char*)a[1], 0, 0);
    Variant var;
    var.flags = 0; var.type = 0;
    var.AssignKey(&key);
    int id = GetPropID((const char*)a[0]);
    ((VFn2P)VSLOT(g_sAppProperties, 0x14))(g_sAppProperties, (void*)id, &var);
    if (var.flags & 4)
        var.Clear(0);
}

void* __cdecl InsertAutoRef(void* out, void* src);  // external original; stub body omitted in this slice

struct AutoRefVec {
    char* begin; char* end; char* cap;
    void __thiscall Resize(int n, void* alloc);   // 0x007c7a40
    void* InsertAutoRef(void* src);
};
// @ 0x007c8af0
void* AutoRefVec::InsertAutoRef(void* src)
{
    int* s = (int*)src;
    Resize((int)((char*)s[1] - (char*)s[0]) >> 4, s + 3);
    void* tmp = 0;
    CopyConstructAutoRef(&tmp, (void*)s[0], (void*)s[1], begin, src);
    end = (char*)tmp;
    return this;
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

typedef void* (__thiscall *InsertThiscall)(void*, void*);
static InsertThiscall volatile g_insertAutoRef = (InsertThiscall)InsertAutoRef;

// @ 0x007c9830
void __cdecl FillAutoRef(char* first, unsigned n, char* src)
{
    char* volatile cur = first;
    while (n--) {
        if (cur) {
            g_insertAutoRef((char*)cur, src);
            ((char*)cur)[0x14] = src[0x14];
        }
        cur = (char*)cur + 0x18;
    }
}

// @ 0x007c9320
void cInitCommand::Init(const char* prefix)
{
    if (mState == 0) {
        void* oldFile = mState;
        void* fp = CreateFileParser();
        if (fp != oldFile) {
            if (fp)
                ((VFn0)VSLOT(fp, 0))(fp);
            mState = fp;
            if (oldFile)
                ((VFn0)VSLOT(oldFile, 4))(oldFile);
        }
        ((VFn0)VSLOT(mState, 8))(mState);
        void* oldParser = mParser2;
        void* p = CreateParser();
        if (p != oldParser) {
            if (p)
                ((VFn0)VSLOT(p, 0))(p);
            mParser2 = p;
            if (oldParser)
                ((VFn0)VSLOT(oldParser, 4))(oldParser);
        }
        ((VFn1)VSLOT(mState, 0x10))(mState, mParser2);
        ((void (__thiscall*)(void*, int, int))VSLOT(mParser2, 0x24))(mParser2, 0, 0);
        ((VFn1)VSLOT(mParser2, 0x10))(mParser2, (char*)this + 0x20);
        void* cm = CheatManager();
        void* obj = ((VFnP0)VSLOT(cm, 0x38))(cm);
        void* res = ((VFnP0)VSLOT(obj, 0xc4))(obj);
        ((VFn1)((void***)mParser2)[0xbc / 4])(mParser2, res);
        RegisterConfigScriptCommands(mParser2);
    }
    ((VFn0)VSLOT(mState, 0x18))(mState);

    EString s;
    s.begin = g_emptyString16;
    s.end = g_emptyString16;
    s.cap = g_emptyString16 + 1;
    const char* e = prefix;
    while (*e) ++e;
    s.assign(prefix, e);
    s.append("Options.txt", "Options.txt" + 11);
    ((VFn2P)VSLOT(mState, 0x1c))(mState, s.begin, (void*)4);

    e = prefix;
    while (*e) ++e;
    s.assign(prefix, e);
    s.append("ConfigManager.txt", "ConfigManager.txt" + 17);
    ((VFn2P)VSLOT(mState, 0x1c))(mState, s.begin, (void*)5);

    if (s.cap - s.begin > 1 && s.begin)
        EA_Free(s.begin);
}

void cInitCommand::Execute(cArguments*)
{
    Init(0);
}
