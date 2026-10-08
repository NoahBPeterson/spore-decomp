// Slice s007e6210.
#include "../s007e5220/s007e5220.h"
#include <intrin.h>

extern "C" void operator_delete__(void* p);

// ---- generic property-list wrapper (watcher target) ----
struct PropListBase {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20();
  virtual char vf24(void* a, void* b);   // +0x24
};
int GetModCount(void* propertyList);
struct CPropList { int GetModificationCount(); };
struct PropWatcher {
  uint32_t f0;   // +0
  void*    f4;   // +4  (wraps the PropListBase)
  void*    f8;   // +8  (owner passed to vf24)
  int      fc;   // +0xc cached modification count
  void* f10;     // +0x10 (property list at wrapper+0x30)
  bool Check();
  void Read(void* p2);
};
extern int32_t gDefaultWatcherValue;

uint32_t* FUN_004e41c0();
struct R4E41c0 { uint32_t* getval(); };

struct JobManagerVtbl_ {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18();
  virtual void vf7(void* thread, void* sw, int b);   // +0x1c
  virtual void vf8(); virtual void vf9();
  virtual void vf10(void* a);                          // +0x28
  virtual void vf11();                                 // +0x2c
};
void* FUN_00921d70();

// @ 0x007E6690
struct PtrDel { void* p; void del(); };
void PtrDel::del() {
    operator_delete__(p);
}

// @ 0x007E6630
bool cAppSystem::FUN_007e6630() {
    long old = _InterlockedExchangeAdd((volatile long*)&mJobRefCount, 0);
    return old > 0;
}

// @ 0x007E65D0
void cAppSystem::FUN_007e65d0(bool add) {
    if (add) {
        if (_InterlockedIncrement((volatile long*)&mJobRefCount) == 1)
            ((JobManagerVtbl_*)mJobManager)->vf10(FUN_00921d70());
    } else {
        if (_InterlockedDecrement((volatile long*)&mJobRefCount) == 0)
            ((JobManagerVtbl_*)mJobManager)->vf11();
    }
}

// @ 0x007E6650
struct Stopwatch {
  char pad[0x20];
  void ctor(int a, int b);
  void SetTimeLimit(int limit, int b);
};
void cAppSystem::RunJobs(int timeLimit) {
    Stopwatch sw;
    sw.ctor(4, 0);
    sw.SetTimeLimit(timeLimit, 1);
    JobManagerVtbl_* jm = (JobManagerVtbl_*)mJobManager;
    jm->vf7(mBaseThread, &sw, 1);
}

// @ 0x007E66A0
bool PropWatcher::Check() {
    int* w = (int*)f4;
    if (w) {
        int mc = (int)w[0xc] ? ((CPropList*)w[0xc])->GetModificationCount() : 0;
        if ((int)fc != (int)w[0xd] + mc) {
            int mc2 = (int)w[0xc] ? ((CPropList*)w[0xc])->GetModificationCount() : 0;
            fc = (int)w[0xd] + mc2;
            PropListBase* pb = (PropListBase*)w;
            PropWatcher* local = this;
            if (pb->vf24(f8, &local)) {
                uint32_t v = *FUN_004e41c0();
                if (f0 != v) {
                    f0 = v;
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x007E6720
void PropWatcher::Read(void* p2) {
    PropListBase* pb = (PropListBase*)p2;
    if (pb->vf24(f8, &p2)) {
        int* q = (int*)p2;
        short t = *(short*)((char*)q + 0x12);
        int* src;
        if (t == 9 || t == 0x10) {
            if ((*(uint8_t*)((char*)q + 0x10) & 0x30) == 0)
                src = (int*)(-(uint32_t)(t != 0) & (uint32_t)q);
            else
                src = (int*)*q;
        } else {
            src = &gDefaultWatcherValue;
        }
        f0 = (uint32_t)*src;
    }
    int* w = (int*)f4;
    if (w[0xc]) {
        fc = (int)w[0xd] + ((CPropList*)w[0xc])->GetModificationCount();
        return;
    }
    fc = (int)w[0xd];
}

// @ 0x007E6210
void LoadGameInfoProperties(void* data) {
    // Reads "game info" AppProperties; incomplete (see partial.txt).
    (void)data;
}

// ---- PreShutdown helpers ----
extern void* gPTR_DAT_0153f85c;
extern void* gPTR_DAT_0153f860;
void FUN_008d5d10(int); void FUN_0067e090(int); void FUN_006ae940();
void FUN_00762f00(int); void FUN_0068c460();
void FUN_0067df00(int); void FUN_0067df30(int);
void FUN_007c79e0(); void FUN_00c2e4e0();
void* SP_CheatManager2();

typedef void (__thiscall *VF0)(void*);
typedef void (__thiscall *VF1)(void*, int);
typedef void (__thiscall *VF3)(void*, void*, int, int);
__forceinline void VC0(void* o, int off) { ((VF0)*(void**)((char*)*(void**)o + off))(o); }
__forceinline void VC1(void* o, int off, int a) { ((VF1)*(void**)((char*)*(void**)o + off))(o, a); }
__forceinline void VC3(void* o, int off, void* a, int b, int c) { ((VF3)*(void**)((char*)*(void**)o + off))(o, a, b, c); }

// @ 0x007E6470  (cAppSystem::PreShutdown)
int cAppSystem::PreShutdown() {
    VC0(*(void**)((char*)this + 0xc8), 0x1c);
    if (mJobManager) { VC0(mJobManager, 8); mBaseThread = 0; }
    if (mAsyncResourceManager) {
        FUN_008d5d10(0); FUN_0067e090(0); FUN_006ae940();
        VC0(mAsyncResourceManager, 4); mAsyncResourceManager = 0;
    }
    if (mGarbageMan) { FUN_00762f00(0); FUN_0068c460(); }
    VC1(SP_CheatManager2(), 0x1c, (int)gPTR_DAT_0153f85c);
    VC1(SP_CheatManager2(), 0x1c, (int)gPTR_DAT_0153f860);
    FUN_007c79e0();
    FUN_00c2e4e0();
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0xf62add, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, (int)0xae1cfe73, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0x255abf5, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0x212d3e7, 0xffffd8f1);
    void* pc = *(void**)((char*)this + 0xc8);
    if (pc) {
        VC0(pc, 0x10);
        FUN_0067df00(0);
        void* q = *(void**)((char*)this + 0xc8);
        if (q) { *(void**)((char*)this + 0xc8) = 0; VC0(q, 4); }
    }
    void* am = mAppStateManager;
    if (am) {
        VC0(am, 0x14);
        FUN_0067df30(0);
        void* q = *(void**)((char*)this + 0x34);
        if (q) { mAppStateManager = 0; VC0(q, 4); }
    }
    void* gs = mGraphicsSystem;
    if (gs) VC0(gs, 0x10);
    return 1;
}

// ================================================================================================
// @ 0x007E67A0  (cAppSystem::Init): the startup sequence.
// Creates and registers the app subsystems (id generator, locale, command server, telemetry, property
// manager, sockets/SSL, save areas + preferences, pack manager, input, canvas, graphics, app states,
// config manager).  The header's Init() has no parameter; the real one takes the command line, so the
// definition lives in a derived stub that adds the right signature (same layout, no virtuals).
// ================================================================================================
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PADV CAT_(vpad, __COUNTER__)
#define P1 virtual void PADV();
#define P2 P1 P1
#define P4 P2 P2
#define P8 P4 P4
#define P16 P8 P8
#define P32 P16 P16

inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void operator delete(void* p, const char* name, int a, int b, int c, int d);       // matching placement delete (EH cleanup)

namespace AppInit {

struct CommandLine {
    int FindSwitch(const wchar_t* name, int a, int b, int c);                   // 0x0092b300 (ret 0x10)
};

// locale manager (refcount at vtable slots 1/2)
struct cLocaleManager {
    P1 virtual void AddRef(); virtual void Release();
    char pad4[0x6c];
    cLocaleManager();                                                           // 0x00696420
    void Init(CommandLine* cmd, const wchar_t* dir);                            // 0x006964c0
};
struct NameMap {                                                                // id generator, 0x40 bytes
    char pad[0x40];
    NameMap();                                                                  // 0x0068db70
};
struct cCommandServer {
    P4 virtual void Start();                                                    // +0x10
};
struct cTelemetry {
    P1 virtual void Method1();                                                  // +4
    uint32_t pad4;
    struct RefSub { virtual void AddRef(); virtual void Release(); } mRef;      // +8
    char padc[0x40 - 0xc];
    cTelemetry();                                                               // 0x007ec0a0
    void Configure(bool dump);                                                  // 0x007eaf20 (ret 4)
    void AddRef() { mRef.AddRef(); }
    void Release() { mRef.Release(); }
};
struct cPropertyManager {
    virtual void AddRef(); virtual void Release();
    virtual void SetFlag(bool b);                                               // +8
    virtual void Start();                                                       // +0xc
    P4 P2 P1
    virtual bool GetPropertyList(uint32_t id, uint32_t group, void* out);       // +0x2c
};
struct Property {
    char pad[0x12];
    short mType;                                                                // +0x12
    uint32_t* GetUInt();                                                        // 0x0041ea00
    bool* GetBool();                                                            // 0x0041e920
};
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;                                                            // +0x10
    uint16_t mType;                                                             // +0x12
    uint16_t mSize;                                                             // +0x14
    uint16_t mExtra;                                                            // +0x16
    Variant() { mFlags = 0; mExtra = 0; }
    ~Variant() { if (mFlags & 4) Destruct(0); }
    void SetInt(const unsigned int* v);                                         // 0x00427fd0
    void Destruct(int a);                                                       // 0x0093db80
};
struct ResourceKey { uint32_t a, b, c; };
struct cPropertyList {                                                          // 0x38 bytes
    virtual void AddRef(); virtual void Release();
    P2 P1
    virtual void SetProperty(uint32_t id, Variant* v);                          // +0x14
    virtual void RemoveProperty(uint32_t id);                                   // +0x18
    P2
    virtual bool GetProperty(uint32_t id, Property** out);                      // +0x24
    P1
    virtual void CopyFrom(cPropertyList* other);                                // +0x2c
    uint32_t pad4;
    ResourceKey mKey;                                                           // +8
    char pad14[0x38 - 0x14];
    cPropertyList();                                                            // 0x006a1c40
};
struct PropListRef {                                                            // EA::AutoRefCount<cPropertyList>
    cPropertyList* mpObject;
    PropListRef() : mpObject(0) {}
    ~PropListRef() { if (mpObject) mpObject->Release(); }
};
struct cResourceHolder {                                                        // release at +8
    P1 virtual void AddRef(); virtual void Release();
    P4 P2
    virtual void Close();                                                       // +0x24
};
struct ResHolderRef {
    cResourceHolder* mpObject;
    ResHolderRef() : mpObject(0) {}
    ~ResHolderRef() { if (mpObject) mpObject->Release(); }
};
struct cResourceReader {                                                        // returned by resmgr+0x48
    P4 P2 P1
    virtual void Read(cResourceHolder* src, void* outRef, int a, uint32_t typeID);   // +0x1c
};
struct cResourceManager {
    P16 P2
    virtual cResourceReader* GetReader(uint32_t typeID, int a);                 // +0x48
};
struct cSaveArea {
    P8 P4 P1
    virtual bool Open(const ResourceKey* key, ResHolderRef* out, int a, int b, int c, int d);   // +0x34
};
struct PrefsRef {                                                               // AutoRefCount<cPropertyList> at +0xcc
    cPropertyList* mpObject;
};
struct cPackManager {
    char pad[0x14];
    cPackManager();                                                             // 0x00b7d170
    void Init();                                                                // 0x007db650
};
struct InputMan {
    P1 virtual void AddRef();
    char pad[0x37c - 8];
    InputMan();                                                                 // 0x008d32f0
};
struct AppCanvas {
    P1 virtual void AddRef();
    P4 P2
    virtual void SetX(int v);                                                   // +0x20
    P1
    virtual void SetFlags(uint32_t flags);                                      // +0x28
    P8 P4 P2 P1
    virtual void SetMessageServer(void* server);                                // +0x68
    P8 P2
    virtual void* GetDropTarget();                                              // +0x94
    char pad[0x98 - 4];
    AppCanvas();                                                                // 0x00849a40
};
struct cGraphicsSystem {
    virtual void AddRef(); virtual void Release();
    virtual bool Start();                                                       // +8
};
struct cAppStateManager {
    virtual void AddRef(); virtual void Release();
    P2
    virtual void Init(int a);                                                   // +0x10
};
struct cConfigManager {
    virtual void AddRef(); virtual void Release();
    P1
    virtual void Setup(CommandLine* cmd, bool needDefaults);                    // +0xc
    P2 P1
    virtual void SetCurrent(uint32_t id, int a);                                // +0x1c
};
struct SocketsManager { char pad[0x1cc]; SocketsManager(); };                   // 0x0094c260
struct SocketsGlobal { P1 virtual void Start(); };                              // +4
struct SSLManager {
    char pad[0x190];
    SSLManager(void* allocator);                                                // 0x0094fc40
    void Init();                                                                // 0x0094fed0
    void SetLoading(const void* a, int b);                                      // 0x0094f080 (ret 8)
    void SetCAFile(const wchar_t* path);                                        // 0x0094f0b0 (ret 4)
};
struct AppProps {
    virtual void Start();                                                       // +0
    void SetBoolProperty(uint32_t id, bool v);                                  // 0x006a17e0
};
struct SSLFileSystemGlobal { const wchar_t* GetCAFileName(); };                 // 0x007c78a0

}  // namespace AppInit

using namespace AppInit;

// global singletons / helpers (cdecl unless noted)
void __cdecl FUN_0067e080(void*);   // register id generator
void __cdecl FUN_0067e060(void*);   // register locale manager
void* __cdecl FUN_0068c0d0();       // creates the command server
void __cdecl FUN_006895c0(void*);
void __cdecl FUN_0067e0b0(void*);   // register telemetry
void __cdecl FUN_006bae50();
void* __cdecl FUN_006ab650();       // creates the property manager
void __cdecl FUN_0067e040(void*);
void __cdecl InitAppEffects();      // 0x007cec80
void __cdecl FUN_0094cd50(void*);
SocketsGlobal* __cdecl FUN_0094cd40();
void __cdecl FUN_0094f0e0(void*);
SSLManager* __cdecl GetSSLManager();                       // 0x0094f0d0
void* __cdecl GetDefaultAllocator();                       // 0x00925cb0
void __cdecl FUN_006b1d40(bool);
void __cdecl CreateDefaultSaveAreas();                     // 0x006b37d0
cSaveArea* __cdecl GetSaveArea(uint32_t id);               // 0x006b1f90
void __cdecl FUN_006b2400(uint32_t id);
void __cdecl SaveNamedResource(cPropertyList* prefs, const wchar_t* name, cResourceHolder* area);   // 0x006b4010
void __cdecl FUN_0067df10(void*);
void __cdecl FUN_0067e0d0(void*);
void __cdecl FUN_008d3120(void*);
void __cdecl FUN_0067ded0(void*);
void __cdecl FUN_0067dee0(void*);
void __cdecl FUN_006bbb60(void* dropTarget, void* slot);
cGraphicsSystem* __cdecl FUN_007a67e0();
void __cdecl FUN_006bb1c0(const char* msg, int code, int a, int b);
void __cdecl FUN_006894d0();
void __cdecl FUN_00689510(int);
cAppStateManager* __cdecl FUN_007e57c0();
void __cdecl FUN_0067df30(void*);
cConfigManager* __cdecl FUN_007cc390();
void __cdecl FUN_0067df40(void*);
void __cdecl FUN_006b4730();
void __cdecl FUN_0067def0(void*);

extern bool gCanvasHighFlag;                               // 0x0153fb34
extern unsigned int gPrefsVersion;                         // 0x0141390c
extern char gSSLGlobal[];                                  // 0x0153fb2c
extern SSLFileSystemGlobal gSSLFileSystem;                 // 0x0153fb2c

#define MF(T, off) (*(T*)((char*)this + (off)))

template <class T> __forceinline void SetRef(T*& slot, T* p)
{
    T* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

struct cAppSystemEx : cAppSystem {
    bool Init(CommandLine* cmd);
};

// @ 0x007E67A0
bool cAppSystemEx::Init(CommandLine* cmd)
{
    NameMap* idgen = new("App", 0, 0, 0, 0) NameMap();
    MF(NameMap*, 0x28) = idgen;
    FUN_0067e080(idgen);

    cLocaleManager* locale = new("App", 0, 0, 0, 0) cLocaleManager();
    SetRef(MF(cLocaleManager*, 0x24), locale);
    MF(cLocaleManager*, 0x24)->Init(cmd, (MF(wchar_t*, 0x128) == MF(wchar_t*, 0x12c)) ? 0 : MF(wchar_t*, 0x128));
    FUN_0067e060(MF(cLocaleManager*, 0x24));

    MF(cCommandServer*, 0x38) = (cCommandServer*)FUN_0068c0d0();
    FUN_006895c0(MF(cCommandServer*, 0x38));
    MF(cCommandServer*, 0x38)->Start();

    bool dumpTelemetry = cmd->FindSwitch(L"dumptelemetry", 0, 0, 0) != -1;
    cTelemetry* tele = new("App", 0, 0, 0, 0) cTelemetry();
    SetRef(MF(cTelemetry*, 0x48), tele);
    MF(cTelemetry*, 0x48)->Method1();
    FUN_0067e0b0(MF(cTelemetry*, 0x48));
    MF(cTelemetry*, 0x48)->Configure(dumpTelemetry);

    ((AppProps*)gAppProperties)->Start();
    FUN_006bae50();
    SetRef(MF(cPropertyManager*, 0x2c), (cPropertyManager*)FUN_006ab650());
    FUN_0067e040(MF(cPropertyManager*, 0x2c));
    MF(cPropertyManager*, 0x2c)->SetFlag(MF(bool, 0x159));
    MF(cPropertyManager*, 0x2c)->Start();
    InitAppEffects();

    FUN_0094cd50(new("App", 0, 0, 0, 0) SocketsManager());
    FUN_0094cd40()->Start();

    SSLManager* ssl = new("App", 0, 0, 0, 0) SSLManager(GetDefaultAllocator());
    FUN_0094f0e0(ssl);
    GetSSLManager()->SetLoading(gSSLGlobal, 1);
    GetSSLManager()->Init();
    GetSSLManager()->SetCAFile(gSSLFileSystem.GetCAFileName());

    FUN_006b1d40(MF(bool, 0x159) == false);
    CreateDefaultSaveAreas();
    cSaveArea* area = GetSaveArea(0x11ac192);
    ResourceKey key;
    key.a = 0xd9bd3ca1;
    key.b = 0xb1b104;
    key.c = 0x11ac192;
    cResourceReader* reader = MF(cResourceManager*, 0x1c)->GetReader(0xb1b104, -1);

    bool safe = cmd->FindSwitch(L"safe", 0, 0, 0) != -1;
    if (!safe && area && reader) {
        ResHolderRef holder;
        if (area->Open(&key, &holder, 1, 3, 1, 0)) {
            cPropertyList*& prefsSlot = MF(cPropertyList*, 0xcc);
            if (prefsSlot) {
                prefsSlot = 0;
            }
            reader->Read(holder.mpObject, &MF(cPropertyList*, 0xcc), 0, key.b);
            holder.mpObject->Close();
        }
    }

    cPropertyList* prefs = MF(cPropertyList*, 0xcc);
    if (prefs) {
        Property* prop;
        if (!prefs->GetProperty(0x4754439, &prop) || prop->mType != 10 || *prop->GetUInt() != 9) {
            cPropertyList* old = MF(cPropertyList*, 0xcc);
            if (old) {
                MF(cPropertyList*, 0xcc) = 0;
                old->Release();
            }
        }
    }
    bool needDefaults = MF(cPropertyList*, 0xcc) == 0;

    if (MF(cPropertyList*, 0xcc)) {
        Property* prop;
        if (!MF(cPropertyList*, 0xcc)->GetProperty(0x43f2ae3, &prop) || prop->mType != 1 || !*prop->GetBool())
            goto afterPrefs;
        FUN_006b2400(0x11ac1ac);
        MF(cPropertyList*, 0xcc)->RemoveProperty(0x43f2ae3);
    } else {
        cPropertyList* fresh = new("App", 0, 0, 0, 0) cPropertyList();
        SetRef(MF(cPropertyList*, 0xcc), fresh);
        cPropertyList* cur = MF(cPropertyList*, 0xcc);
        cur->mKey.a = key.a;
        cur->mKey.b = key.b;
        cur->mKey.c = key.c;
        PropListRef defaults;
        if (MF(cPropertyManager*, 0x2c)->GetPropertyList(0x4483e856, 0, &defaults.mpObject))
            MF(cPropertyList*, 0xcc)->CopyFrom(defaults.mpObject);
        else
            FUN_006bb1c0("Could not find the default preferences.\n\nThe data directory is missing or corrupt.", 0x3ec, 0, 0);
        Variant v;
        v.SetInt(&gPrefsVersion);
        MF(cPropertyList*, 0xcc)->SetProperty(0x4754439, &v);
    }
    if (area)
        SaveNamedResource(MF(cPropertyList*, 0xcc), L"Preferences", (cResourceHolder*)area);
afterPrefs:
    FUN_0067df10(MF(cPropertyList*, 0xcc));

    cPackManager* packs = new("App", 0, 0, 0, 0) cPackManager();
    MF(cPackManager*, 0x4c) = packs;
    packs->Init();
    FUN_0067e0d0(MF(cPackManager*, 0x4c));

    InputMan* input = new("App", 0, 0, 0, 0) InputMan();
    MF(InputMan*, 0x18) = input;
    input->AddRef();
    FUN_008d3120(MF(InputMan*, 0x18));
    FUN_0067ded0(MF(InputMan*, 0x18));

    AppCanvas* canvas = new("App", 0, 0, 0, 0) AppCanvas();
    MF(AppCanvas*, 0x10) = canvas;
    canvas->SetMessageServer(MF(void*, 0x14));
    MF(AppCanvas*, 0x10)->AddRef();
    uint32_t flags = 0x2a;
    if (gCanvasHighFlag)
        flags = 0x6a;
    if (cmd->FindSwitch(L"flock", 0, 0, 0) != -1)
        flags |= 0x80;
    MF(AppCanvas*, 0x10)->SetFlags(flags);
    MF(AppCanvas*, 0x10)->SetX(0xe);
    FUN_0067dee0(MF(AppCanvas*, 0x10));
    FUN_006bbb60(MF(AppCanvas*, 0x10)->GetDropTarget(), &MF(void*, 0x54));

    SetRef(MF(cGraphicsSystem*, 0x5c), FUN_007a67e0());
    if (!MF(cGraphicsSystem*, 0x5c)->Start()) {
        FUN_006bb1c0("Could not start the renderer.\nPlease ensure your display is set to 32 bits.", 0x3e9, 2, 0);
        return false;
    }

    MF(float, 0xb8) = 0.0f;
    MF(float, 0xbc) = 0.0f;
    FUN_006894d0();
    FUN_00689510(0);

    SetRef(MF(cAppStateManager*, 0x34), FUN_007e57c0());
    if (MF(cAppStateManager*, 0x34)) {
        MF(cAppStateManager*, 0x34)->Init(0);
        FUN_0067df30(MF(cAppStateManager*, 0x34));
    }

    SetRef(MF(cConfigManager*, 0x3c), FUN_007cc390());
    MF(cConfigManager*, 0x3c)->Setup(cmd, needDefaults);
    FUN_0067df40(MF(cConfigManager*, 0x3c));
    MF(cConfigManager*, 0x3c)->SetCurrent(0x9a06678c, 0);

    if (cmd->FindSwitch(L"vSync", 0, 0, 0) != -1)
        ((AppProps*)gAppProperties)->SetBoolProperty(0xd77e97, true);
    if (cmd->FindSwitch(L"noVSync", 0, 0, 0) != -1)
        ((AppProps*)gAppProperties)->SetBoolProperty(0xd77e97, false);
    FUN_006b4730();
    FUN_0067def0(this);
    return true;
}
