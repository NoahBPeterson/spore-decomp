// Slice s00ff4d50 - player-inventory tool loading / serialization, colony growth
// simulation, tool lookup helpers and two insertion-sort overloads.
//
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- vtable calls
struct VObj { void** vt; };

typedef void* (__thiscall *FnVp0)(void*);
typedef void* (__thiscall *FnVp1i)(void*, int);
typedef void* (__thiscall *FnVp2i)(void*, int, int);
typedef int   (__thiscall *FnVp0i)(void*);
typedef char  (__thiscall *FnVp0c)(void*);

// ---------------------------------------------------------------- externals
struct IStream;

bool __cdecl EA_IO_WriteUint32(void* s, const void* p, uint32_t n, int endian); // 0x0093aa70
bool __cdecl EA_IO_ReadInt32(void* s, void* p, uint32_t n, int endian);         // 0x0093a780

void* __cdecl operator_new(uint32_t size, const char* tag, int a, int b, int c, int d); // 0x00f473a0
void  __cdecl operator_delete_array(void* p);                                            // 0x00f47380

extern char g_15b5ed8;      // [0x015b5ed8] variable-list table used when reading
extern char g_15b6160;      // [0x015b6160] variable-list table used when writing
extern char g_1654c05[];    // [0x01654c05] active-vignette identifier
extern char g_18c43e8[];    // [0x018c43e8] game-data selection key
extern char g_13f09b4[];    // [0x013f09b4] "Simulator"
extern int  g_16db738;      // [0x016db738] planet-embassy presence marker

extern char g_00cd7d10[];   // [0x00cd7d10] game-data selector
extern char g_00d3d420[];   // [0x00d3d420] game-data selector
extern char g_00acdff0[];   // [0x00acdff0] game-data selector
extern char g_00b1e500[];   // [0x00b1e500] game-data selector

extern char g_67b69c4[];    // [0x067b69c4] UFO-count message fragments
extern char g_67b69d0[];    // [0x067b69d0]
extern char g_67b69d8[];    // [0x067b69d8]
extern char g_67b69e3[];    // [0x067b69e3]
extern char g_67b69eb[];    // [0x067b69eb]
extern char g_67b69f1[];    // [0x067b69f1]

extern void* g_vtbl_cPlayerInventory;    // [0x01494d68]
extern void* g_vtbl_cPlayerInventoryI;   // [0x01494d54]
extern void* g_vtbl_cColonySimulator;    // [0x01494ee4]
extern void* g_vtbl_cContentValidation;  // [0x013ec458]

// ---------------------------------------------------------------- serializer
struct cDataSerializationInfo { char d[0x14]; };

class cVarListSerializer {
public:
    cDataSerializationInfo mInfos[128];  // +0x0000
    int      mSerializableVarCount;      // +0x0a00
    int      mSerializedVarCount;        // +0x0a04
    uint32_t mSignature;                 // +0x0a08
    void*    mpObject;                   // +0x0a0c
    void*    mpSerializerList;           // +0x0a10

    cVarListSerializer(void* obj, void* list, uint32_t sig); // 0x00692f90
    bool __thiscall Serialize(IStream* s);                   // 0x00692900
    bool __thiscall SerializeRead(IStream* s);               // 0x00693e10
};

// Common prologue shared by every Write()/Read() body: resolve the stream.
static inline void* StreamWriter(IStream* s) {
    return ((FnVp0)((VObj*)s)->vt[0x20 / 4])(s);
}
static inline void* WriterValue(void* w) {
    return ((FnVp0)((VObj*)w)->vt[0x18 / 4])(w);
}

// ---------------------------------------------------------------- inventory
struct cRefCounted;

struct ToolVector {
    cRefCounted* mpBegin;                                    // +0x00
    cRefCounted* mpEnd;                                      // +0x04
    cRefCounted* mpCapacity;                                 // +0x08
    cRefCounted* __thiscall erase(cRefCounted* first, cRefCounted* last); // 0x005c2170
    void __thiscall Append(cRefCounted* tool);               // 0x00f14270
};

struct cRefCounted {
    virtual void Dtor();                 // vt[0]
    virtual void AddRef();               // vt[4]
    virtual void Release();              // vt[8]
};

struct cPropertyList {
    void** mpVtbl;                                       // +0x00
    char   pad04[0x38 - 0x04];
    cRefCounted* mItems;                                 // +0x38
    cRefCounted* mItemsEnd;                              // +0x3c
    cRefCounted* mItemsCap;                              // +0x40

    bool __thiscall HasProperty(int key);                // vt[0x1c]
    cPropertyList* __thiscall GetSubList(int key);       // vt[0x28]
    void __thiscall QueryKeys(cPropertyList** out, int a, int b); // vt[0x2c]
    void __thiscall Release();                           // vt[0]
};

struct cSPToolManager {
    void** mpVtbl;                                              // +0x00
    bool __thiscall CreateToolFromToolID(cRefCounted** out, cRefCounted* spec); // 0x0104e340
    cPropertyList* __thiscall TakePropertyList(cPropertyList* p);               // 0x00b3d390
    void __thiscall QueryKeys(cPropertyList** out, int a, int b);               // vt[0x2c]
};

void* __cdecl SP_PropertyManager();   // 0x0067de30

struct cPlayerInventory {
    void*  mpVtbl0;                       // +0x00
    void*  mpVtbl1;                       // +0x04
    char   pad08[0x4c - 0x08];
    ToolVector mUnlockableTools;          // +0x4c
    char   pad58[0x60 - 0x58];
    ToolVector mTransitionRewardTools;    // +0x60
    char   pad6c[0x74 - 0x6c];
    ToolVector mDecorationTools;          // +0x74
    char   pad80[0x88 - 0x80];
    ToolVector mProjectileTools;          // +0x88
    char   mb94;                          // +0x94

    cPlayerInventory* __thiscall ctor();          // 0x00ff5190
    void __thiscall LoadToolData();               // 0x00ff4d50
    bool __thiscall Read(IStream* s);             // 0x00ff50f0
    void __thiscall BaseCtor();                   // 0x00c87b20
    char __thiscall ReadBase(IStream* s);         // 0x00c883d0
};

// ---------------------------------------------------------------- 0x00ff4d50
// Walks the player inventory's property list and registers the projectile and
// decoration tools it references with the inventory's tool vectors.
// @ 0x00ff4d50
void __thiscall cPlayerInventory::LoadToolData() {
    cPropertyList* pToolList = 0;
    cSPToolManager* toolMgr = (cSPToolManager*)SP_PropertyManager();
    toolMgr->QueryKeys(&pToolList, 0x59252ee9, 0x30608f0b);
    pToolList = toolMgr->TakePropertyList(pToolList);
    if (pToolList == 0)
        return;

    if (pToolList->HasProperty(0xf0609ec3)) {
        cPropertyList* ids = pToolList->GetSubList(0x63aa10b);
        cRefCounted* created = 0;
        toolMgr->CreateToolFromToolID(&created, (cRefCounted*)ids);
        mUnlockableTools.Append(created);
    }
    if (pToolList->HasProperty((int)0x2c08e1e)) {
        cPropertyList* ids = pToolList->GetSubList(0x4ed333f);
        cRefCounted* created = 0;
        toolMgr->CreateToolFromToolID(&created, (cRefCounted*)ids);
        mTransitionRewardTools.Append(created);
    }
    if (pToolList->HasProperty(0x30608f0b)) {
        cPropertyList* ids = pToolList->GetSubList(0x59252ee9);
        cRefCounted* created = 0;
        toolMgr->CreateToolFromToolID(&created, (cRefCounted*)ids);
        mDecorationTools.Append(created);
    }
    pToolList->Release();
}

// ---------------------------------------------------------------- 0x00ff50f0
// @ 0x00ff50f0
bool __thiscall cPlayerInventory::Read(IStream* s) {
    int id;
    mUnlockableTools.erase(mUnlockableTools.mpBegin, mUnlockableTools.mpEnd);

    void* stream = StreamWriter(s);
    void* value = WriterValue(stream);
    EA_IO_ReadInt32(value, &id, 1, 0);

    char ok = ReadBase(s);
    cVarListSerializer ser(this, &g_15b5ed8, 0x1a80d26);
    if (ok && ser.SerializeRead(s))
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x00ff5190
// @ 0x00ff5190
cPlayerInventory* __thiscall cPlayerInventory::ctor() {
    BaseCtor();
    void* zero = 0;
    mpVtbl0 = &g_vtbl_cPlayerInventory;
    mpVtbl1 = &g_vtbl_cPlayerInventoryI;
    mUnlockableTools.mpBegin = (cRefCounted*)zero;
    mUnlockableTools.mpEnd = (cRefCounted*)zero;
    mUnlockableTools.mpCapacity = (cRefCounted*)zero;
    mTransitionRewardTools.mpBegin = (cRefCounted*)zero;
    mTransitionRewardTools.mpEnd = (cRefCounted*)zero;
    mTransitionRewardTools.mpCapacity = (cRefCounted*)zero;
    mDecorationTools.mpBegin = (cRefCounted*)zero;
    mDecorationTools.mpEnd = (cRefCounted*)zero;
    mDecorationTools.mpCapacity = (cRefCounted*)zero;
    mProjectileTools.mpBegin = (cRefCounted*)zero;
    mProjectileTools.mpEnd = (cRefCounted*)zero;
    mProjectileTools.mpCapacity = (cRefCounted*)zero;
    mb94 = 0;
    LoadToolData();
    return this;
}

// ---------------------------------------------------------------- 0x00ff51f0
void __stdcall FUN_01062e70(int type, float value, float fallback); // 0x01062e70

// @ 0x00ff51f0
void __cdecl FUN_00ff51f0(void* param_1, float param_2, float param_3) {
    if (param_1 == 0)
        return;
    if (param_2 > 1.0f) {
        FUN_01062e70(0, param_3, -1.0f);
        return;
    }
    if (param_2 > 0.0f) {
        FUN_01062e70(1, param_3, -1.0f);
        return;
    }
    if (param_2 == 0.0f) {
        FUN_01062e70(2, param_3, -1.0f);
        return;
    }
    if (param_2 > -1.0f) {
        FUN_01062e70(3, param_3, -1.0f);
        return;
    }
    FUN_01062e70(4, param_3, -1.0f);
}

// ---------------------------------------------------------------- 0x00ff5270
struct CNounManagerA {
    int __thiscall GetPlayerEmpireOrMinus1();   // 0x00b1f9d0
};
void* __cdecl FUN_00b3d300();                   // 0x00b3d300  SP::NounManager

struct CObjBef8e0 { void* __thiscall AsReference(); };   // 0x00bef8e0
struct CObjC8e7e0 { void* __thiscall AsReference(); };   // 0x00c8e7e0
struct CObjBD9BF0 { void* __thiscall GetCivilization(); }; // 0x00bd9bf0

// @ 0x00ff5270
void __cdecl SP_DoCommunityReaction(int* param_1, float param_2, float param_3) {
    CNounManagerA* mgr = (CNounManagerA*)FUN_00b3d300();
    int empire = mgr->GetPlayerEmpireOrMinus1();
    if (((FnVp0i)((VObj*)param_1)->vt[0x4c / 4])(param_1) == empire)
        return;

    CObjBef8e0* a = (CObjBef8e0*)((FnVp1i)((VObj*)param_1)->vt[0x0c / 4])(param_1, 0x901f1362);
    CObjC8e7e0* b = (CObjC8e7e0*)((FnVp1i)((VObj*)param_1)->vt[0x0c / 4])(param_1, 0x4f396a66);
    CObjBD9BF0* c = (CObjBD9BF0*)((FnVp1i)((VObj*)param_1)->vt[0x0c / 4])(param_1, 0xee9b2232);

    void* r = 0;   // kept in ecx
    if (a != 0)
        r = a->AsReference();
    if (b != 0)
        r = b->AsReference();
    if (c != 0)
        r = ((CObjBef8e0*)c->GetCivilization())->AsReference();

    if (param_2 != 0.0f)
        FUN_00ff51f0(r, param_2, param_3);
}

// ---------------------------------------------------------------- 0x00ff5330
// @ 0x00ff5330
void __cdecl FUN_00ff5330(int param_1, int* param_2, int* param_3,
                          int* param_4, int* param_5, int* param_6) {
    *param_6 = 0;
    *param_5 = 0;
    *param_4 = 0;
    *param_3 = 0;
    *param_2 = 0;
    while (param_1 > 0) {
        param_1--;
        switch (param_1) {
        case 0:  (*param_2)++; break;
        case 3:  (*param_5)++; break;
        case 12: (*param_5)++; break;
        case 18: (*param_5)++; break;
        case 1:  (*param_6)++; break;
        case 4:  (*param_6)++; break;
        case 6:  (*param_6)++; break;
        case 8:  (*param_6)++; break;
        case 10: (*param_6)++; break;
        case 13: (*param_6)++; break;
        case 15: (*param_6)++; break;
        case 17: (*param_6)++; break;
        case 9:  (*param_4)++; break;
        case 14: (*param_4)++; break;
        case 2:  (*param_3)++; break;
        case 5:  (*param_3)++; break;
        case 7:  (*param_3)++; break;
        case 11: (*param_3)++; break;
        case 16: (*param_3)++; break;
        case 19: (*param_3)++; break;
        case 20: (*param_3)++; break;
        }
    }
}

// ---------------------------------------------------------------- 0x00ff53f0
// @ 0x00ff53f0
int __cdecl FUN_00ff53f0(int param_1) {
    param_1 = param_1 * 5;
    if (param_1 > 100)
        param_1 = 100;
    return param_1;
}

// ---------------------------------------------------------------- 0x00ff5410
struct CFileCountHolder {
    int __thiscall GetFileCount();   // 0x008e7f80
};

struct CNoun120 {
    void** mpVtbl;                          // +0x000
    char   pad04[0x120 - 0x04];
    CFileCountHolder mFileCount120;         // +0x120
    char   pad124[0x588 - 0x124];
    CFileCountHolder mFileCount588;         // +0x588
};

struct CTribe {
    void** mpVtbl;                          // +0x000
    char   pad04[0x354 - 0x04];
    CNoun120** mAgents;                     // +0x354
    CNoun120** mAgentsEnd;                  // +0x358

    int** __thiscall GetMembers();          // 0x00c8e810
};

// @ 0x00ff5410
void __cdecl FUN_00ff5410(CTribe* param_1, int* param_2, int* param_3,
                          int* param_4, int* param_5, int* param_6) {
    int** members = (int**)param_1->GetMembers();
    int n = (int)(members[1] - members[0]) >> 2;
    for (int i = 0; i < n; ++i) {
        CNoun120* m = (CNoun120*)((int*)members[0])[i];
        if (m->mFileCount120.GetFileCount() == 2)
            continue;
        switch (((FnVp0i)((VObj*)m)->vt[0x38 / 4])(m)) {
        case 0xff10521:
            (*param_2)++;
            break;
        case 0x1a55e4d:
            (*param_3)++;
            break;
        case 0xecade42:
            (*param_4)++;
            break;
        case 0x1007ae63:
            (*param_6)++;
            break;
        }
    }

    int n2 = (int)(param_1->mAgentsEnd - param_1->mAgents) >> 2;
    for (int i = 0; i < n2; ++i) {
        CNoun120* m = param_1->mAgents[i];
        if (m->mFileCount588.GetFileCount() != 2)
            (*param_5)++;
    }
}

// ---------------------------------------------------------------- 0x00ff54e0
struct cGonzagoTimer {
    void __thiscall ctor();                    // 0x00b63890
    void __thiscall dtor();                    // 0x00b638b0
    void __thiscall Start();                   // 0x00bc30f0
    void __thiscall Restart();                 // 0x00bc3130
    long long __thiscall GetElapsedTime();     // 0x00bc3190
    char pad[0x40];
};

struct cColonySimulator {
    void* mpVtbl;                            // +0x00
    int   m04;                               // +0x04
    cGonzagoTimer mTimer;                    // +0x08

    cColonySimulator* __thiscall ctor();                       // 0x00ff54e0
    void* __thiscall scalarDeletingDtor(char flags);           // 0x00ff5810
    void __thiscall DoGrowthSim(void* city);                   // 0x00ff5720
    void __thiscall OnTick(int a, int b, int c);               // 0x00ff5840
};

// @ 0x00ff54e0
cColonySimulator* __thiscall cColonySimulator::ctor() {
    m04 = 0;
    mpVtbl = &g_vtbl_cColonySimulator;
    mTimer.ctor();
    mTimer.Start();
    return this;
}

// ---------------------------------------------------------------- 0x00ff5510
struct CCityGrow {
    void** mpVtbl;                       // +0x000
    char   pad04[0x120 - 0x04];
    void** mpCombatVtbl;                 // +0x120
    char   pad124[0x340 - 0x124];
    int    mCount340;                    // +0x340
    int    mCount344;                    // +0x344
    char   pad348[0x354 - 0x348];
    int    mCount354;                    // +0x354
    int    mCount358;                    // +0x358

    int  __thiscall FUN_00bd8110();      // 0x00bd8110
    int  __thiscall FUN_00bd9b60();      // 0x00bd9b60
    int  __thiscall GetCreatureCount();  // 0x00bd8120
    void __thiscall FUN_00c74860(int v);// 0x00c74860
    void __thiscall FUN_00bd9e50();      // 0x00bd9e50
    void __thiscall FUN_00be2070(int a, int b); // 0x00be2070
    void __thiscall FUN_00be5130(int v); // 0x00be5130
    void __thiscall FUN_00be7370(int v); // 0x00be7370
    void __thiscall FUN_00be3850();      // 0x00be3850
    void* __thiscall FUN_00bd7ef0(int v);// 0x00bd7ef0
    int  __thiscall FUN_00bdb590(void* a, int b); // 0x00bdb590
    int** __thiscall GetMembers();       // 0x00c8e810
};

int __cdecl FUN_00bdb470(int v);   // 0x00bdb470
void* __cdecl FUN_00b3d480(void* city, int flag);   // 0x00b3d480

struct CAc8cd0 { void* __thiscall FUN_00ac8cd0(); }; // 0x00ac8cd0

// @ 0x00ff5510
int __cdecl SP_DetermineCityGrowth(CCityGrow* param_1, int* param_2) {
    int local_28 = 0;
    int iStack_24, iStack_20, iStack_1c, iStack_18;
    int iStack_14, iStack_10, iStack_c, iStack_8, iStack_4;
    int i = 0;

    if (param_1 == 0)
        return local_28;

    char cVar2 = ((FnVp0c)((VObj*)&param_1->mpCombatVtbl)->vt[0x58 / 4])(&param_1->mpCombatVtbl);
    int uVar3 = param_1->FUN_00bd8110();

    iStack_18 = 0;
    iStack_10 = 0;
    iStack_8 = 0;
    iStack_20 = 0;
    iStack_24 = 0;
    FUN_00ff5410((CTribe*)param_1, &iStack_18, &iStack_10, &iStack_8, &iStack_20, &iStack_24);
    int sum = iStack_24 + iStack_20 + iStack_8 + iStack_10 + iStack_18;

    iStack_1c = 0;
    iStack_14 = 0;
    iStack_c = 0;
    iStack_4 = 0;
    FUN_00ff5330(uVar3, &iStack_24, &iStack_1c, &iStack_14, &iStack_c, &iStack_4);

    if (cVar2 == 0) {
        if (iStack_20 != iStack_1c) {
            local_28 = iStack_1c - iStack_20;
            *param_2 = 0xff10521;
        } else if (iStack_10 != iStack_14) {
            *param_2 = 0x1a55e4d;
            return iStack_14 - iStack_10;
        } else if (iStack_8 != iStack_c) {
            *param_2 = 0xecade42;
            return iStack_c - iStack_8;
        } else if (iStack_24 != iStack_4) {
            *param_2 = 0x436f315;
            return iStack_4 - iStack_24;
        }
    } else if (iStack_4 + iStack_c + iStack_14 + iStack_1c + iStack_24 < sum) {
        if (sum - iStack_20 < iStack_20) {
            *param_2 = 0x436f315;
            return -1;
        }
        int** members = param_1->GetMembers();
        int count = (int)(members[1] - members[0]) >> 2;
        if (count > 0) {
            do {
                CNoun120* m = (CNoun120*)((int*)members[0])[i];
                int t = ((FnVp0i)((VObj*)m)->vt[0x38 / 4])(m);
                if (t != 0x1007ae63) {
                    *param_2 = ((FnVp0i)((VObj*)m)->vt[0x38 / 4])(m);
                    return -1;
                }
                i++;
            } while (i < count);
            return 0;
        }
    }
    return local_28;
}

// ---------------------------------------------------------------- 0x00ff5720
// @ 0x00ff5720
void __thiscall cColonySimulator::DoGrowthSim(void* city) {
    if (city == 0)
        return;

    int code;
    int r = SP_DetermineCityGrowth((CCityGrow*)city, &code);
    CCityGrow* c = (CCityGrow*)city;

    if (r >= 1) {
        if (code == 0x436f315) {
            if (FUN_00bdb470(0x436f315) == 0)
                c->FUN_00be3850();
        } else if (FUN_00bdb470(code) == 0) {
            void* a = c->FUN_00bd7ef0(code);
            if (c->FUN_00bdb590(a, 0) != 0)
                c->FUN_00be7370(code);
        }
    } else if (r < 0) {
        if (code == 0x436f315)
            c->FUN_00be2070(0, 0);
        else
            c->FUN_00be5130(code);
        c->FUN_00bd9e50();
    }

    int v = ((c->mCount358 - c->mCount354) >> 2) + ((c->mCount344 - c->mCount340) >> 2);
    v -= c->FUN_00bd9b60();
    v = v * 5;
    if (v > 100)
        v = 100;
    if (v != c->GetCreatureCount()) {
        c->FUN_00c74860(v);
        void* o = FUN_00b3d480(city, 0);
        ((CAc8cd0*)o)->FUN_00ac8cd0();
    }
}

// ---------------------------------------------------------------- 0x00ff5810
// @ 0x00ff5810
void* __thiscall cColonySimulator::scalarDeletingDtor(char flags) {
    mpVtbl = &g_vtbl_cColonySimulator;
    mTimer.dtor();
    mpVtbl = &g_vtbl_cContentValidation;
    if ((flags & 1) != 0)
        operator_delete_array(this);
    return this;
}

// ---------------------------------------------------------------- 0x00ff5840
struct CNounManagerB {
    int* __thiscall GetGameDataVector(void* a, void* b, void* c, void* d, void* e); // 0x00b21340
};
void* __cdecl FUN_00b3d300_1();    // 0x00b3d300  SP::NounManager (no argument form)
void* __cdecl FUN_01029940();      // 0x01029940  SP::GetSpaceCombatTuning

struct CCombatTuning {
    int __thiscall GetSecondsBetweenColonySimulatorTicks();   // 0x01029b50
};

struct CProfLeaveZone {
    void** mpVtbl;                       // +0x00
    char   pad04[0x34 - 0x04];
    void** mpSubVtbl;                    // +0x34
};

struct CColonyEntry {
    void* __thiscall GetCity();          // 0x00bd9e30
};

// @ 0x00ff5840
void __thiscall cColonySimulator::OnTick(int a, int b, int c) {
    CNounManagerB* nm = (CNounManagerB*)FUN_00b3d300_1();
    int* vecBase = (int*)nm->GetGameDataVector(g_00cd7d10, g_00d3d420, g_00acdff0,
                                               g_00b1e500, g_18c43e8);
    int* vec = vecBase + 1;

    CCombatTuning* tuning = (CCombatTuning*)FUN_01029940();
    long long interval = tuning->GetSecondsBetweenColonySimulatorTicks() * 1000;

    long long elapsed = mTimer.GetElapsedTime();
    if ((unsigned long long)elapsed > (unsigned long long)interval) {
        mTimer.Restart();
        int n = (vec[1] - vec[0]) >> 2;
        for (int i = 0; i < n; ++i) {
            int* city = (int*)((int*)vec[0])[i];
            if (city[0x74c / 4] == -1)
                DoGrowthSim(city);
        }
    }

    int n2 = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < n2; ++i) {
        CColonyEntry* e = (CColonyEntry*)((int*)vec[0])[i];
        void* p = e->GetCity();
        if (p != 0) {
            char ok = ((FnVp0c)((VObj*)((char*)p + 0x34))->vt[0x50 / 4])((char*)p + 0x34);
            if (ok != 0)
                ((FnVp0)((VObj*)p)->vt[0x68 / 4])(p);
        }
    }
}

// ---------------------------------------------------------------- 0x00ff5930
struct CB8de30 { void* __thiscall GetNounManager(); };   // 0x00b8de30
struct CC8b560 { char  __thiscall IsSomething(); };       // 0x00c8b560
struct CB8dab0 { int   __thiscall GetType(); };           // 0x00b8dab0
struct CAvatar { void* __thiscall GetAvatar(); };         // 0x00b1fdb0
struct CStarManager {
    void* __thiscall GetEmpireByID();                     // 0x00ba9370
    void* __thiscall FUN_00baf700();                      // 0x00baf700
};
struct CTerraforming {
    char __thiscall IsEnabled();                          // 0x00bbe5c0
};

void* __cdecl FUN_01021230();                     // 0x01021230
int   __cdecl FUN_01021090();                     // 0x01021090
void* __stdcall FUN_00b3d2a0(void* which);        // 0x00b3d2a0  SP::StarManager
void* __stdcall FUN_00b3d430(void* which);        // 0x00b3d430  SP::TerraformingManager
char  __cdecl FUN_00c6fe50(void* p);              // 0x00c6fe50
int   __cdecl FUN_0102b010(void* a, char* b, char* c); // 0x0102b010  SP::sGetNumUFOs

// @ 0x00ff5930
int __cdecl FUN_00ff5930(void* param_1) {
    CB8de30* nounMgr = (CB8de30*)((CB8de30*)param_1)->GetNounManager();
    if (((CC8b560*)FUN_01021230())->IsSomething() == 0) {
        if (((CB8dab0*)param_1)->GetType() == 5) {
            CAvatar* avatarMgr = (CAvatar*)nounMgr;
            if (avatarMgr->GetAvatar() != (void*)FUN_01021090()) {
                void* starMgr = FUN_00b3d2a0(avatarMgr->GetAvatar());
                void* empire = ((CStarManager*)starMgr)->GetEmpireByID();
                void* starMgr2 = FUN_00b3d2a0(empire);
                void* ufo = ((CStarManager*)starMgr2)->FUN_00baf700();

                if (FUN_00c6fe50(param_1) != 0)
                    return FUN_0102b010(ufo, g_67b69e3, g_67b69f1);

                CTerraforming* terra = (CTerraforming*)FUN_00b3d430(param_1);
                if (terra->IsEnabled() != 0)
                    return FUN_0102b010(ufo, g_67b69d8, g_67b69eb);

                return FUN_0102b010(ufo, g_67b69c4, g_67b69d0);
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ff5a10
void* __cdecl NounManager();                      // 0x00b3d300  SP::NounManager

struct CNounManagerC {
    void __thiscall RemoveNoun(void* noun);                       // 0x00b225d0
    void* __thiscall GetCurrentTerrainSphere();                   // 0x00f67d90
};

struct CObjB8E7D0 {
    void __thiscall FUN_00b8e7d0(int v);                          // 0x00b8e7d0
};

struct CTerrainSphere {
    void __thiscall RemoveEmbassyFromPlanet(void* planet);        // 0x00c77450
};

struct CGetter10666a0 {
    int __thiscall FUN_01067e60();                                // 0x01067e60
};

struct CToolNoun {
    char pad00[0x64c];
    int  mPlaceRef;                        // +0x64c
};

void* __cdecl FUN_010666a0();                     // 0x010666a0
void  __cdecl FUN_01041c30(void* a, int b);       // 0x01041c30

// @ 0x00ff5a10
void __cdecl FUN_00ff5a10(void* param_1, void* param_2) {
    ((CNounManagerC*)NounManager())->RemoveNoun(param_1);
    ((CObjB8E7D0*)param_2)->FUN_00b8e7d0(((CToolNoun*)param_1)->mPlaceRef);
    if (((CToolNoun*)param_1)->mPlaceRef == g_16db738) {
        ((CTerrainSphere*)((CNounManagerC*)NounManager())->GetCurrentTerrainSphere())
            ->RemoveEmbassyFromPlanet(param_2);
    }
    CGetter10666a0* g = (CGetter10666a0*)FUN_010666a0();
    FUN_01041c30(param_1, g->FUN_01067e60());
}

// ---------------------------------------------------------------- 0x00ff5a90
struct cSPSimPlanetHighLOD {
    void** mpVtbl;                        // +0x00
    char   pad04[0x20 - 0x04];
    void*  mp20;                          // +0x20

    bool __thiscall WriteBase(IStream* s);       // 0x00b5b610
    char __thiscall ReadBase(IStream* s);        // 0x00b5b650
    bool __thiscall Write(IStream* s);           // 0x00ff5a90
    char __thiscall Read(IStream* s);            // 0x00ff5c50
};

// @ 0x00ff5a90
bool __thiscall cSPSimPlanetHighLOD::Write(IStream* s) {
    void* stream = StreamWriter(s);
    uint32_t id = 0xf04d0722;
    void* value = WriterValue(stream);
    EA_IO_WriteUint32(value, &id, 1, 0);

    char ok = WriteBase(s);
    cVarListSerializer ser((char*)this - 8, &g_15b6160, 0x1a80d26);
    if (ok && ser.Serialize(s))
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x00ff5b30
struct CGetter10666a0B {
    int __thiscall FUN_01067e60();        // 0x01067e60
};
void __cdecl FUN_00ce8f70(void* a, int b);            // 0x00ce8f70

// @ 0x00ff5b30
void __stdcall FUN_00ff5b30(void* param_1) {
    CGetter10666a0B* g = (CGetter10666a0B*)FUN_010666a0();
    FUN_00ce8f70(param_1, g->FUN_01067e60());
}

// ---------------------------------------------------------------- 0x00ff5b50
void* __cdecl FUN_00b3d480_0();   // 0x00b3d480  (no-argument form)

struct CCityVisualizer {
    void __thiscall setActiveVignette(char* name);   // 0x00ad2560
};

// @ 0x00ff5b50
void __cdecl FUN_00ff5b50() {
    CCityVisualizer* v = (CCityVisualizer*)FUN_00b3d480_0();
    v->setActiveVignette(g_1654c05);
}

// ---------------------------------------------------------------- 0x00ff5ba0
// @ 0x00ff5ba0
void __cdecl FUN_00ff5ba0(int* param_1, int* param_2) {
    int* it = param_1;
    if (param_1 != param_2) {
        while (it = it + 1, it != param_2) {
            int v = *it;
            int* p;
            for (p = it; p != param_1 && v < p[-1]; p = p - 1)
                *p = p[-1];
            *p = v;
        }
    }
}

// ---------------------------------------------------------------- 0x00ff5be0
// @ 0x00ff5be0
void __cdecl FUN_00ff5be0(int* param_1, int* param_2) {
    for (int* it = param_1; it != param_2; it = it + 1) {
        int v = *it;
        int* p = it;
        int prev = p[-1];
        while (v < prev) {
            *p = prev;
            p = p - 1;
            prev = p[-1];
        }
        *p = v;
    }
}

// ---------------------------------------------------------------- 0x00ff5c50
// @ 0x00ff5c50
char __thiscall cSPSimPlanetHighLOD::Read(IStream* s) {
    int id;
    void* stream = StreamWriter(s);
    void* value = WriterValue(stream);
    EA_IO_ReadInt32(value, &id, 1, 0);

    char ok = ReadBase(s);
    cVarListSerializer ser((char*)this - 8, &g_15b6160, 0x1a80d26);
    char res;
    if (ok != 0 && ser.SerializeRead(s) != 0)
        res = 1;
    else
        res = 0;

    cColonySimulator* sim = (cColonySimulator*)operator_new(0x28, g_13f09b4, 0, 0, 0, 0);
    if (sim != 0)
        sim = sim->ctor();

    void* old = mp20;
    if (sim != old) {
        if (sim != 0)
            ((cRefCounted*)sim)->AddRef();
        mp20 = sim;
        if (old != 0)
            ((cRefCounted*)old)->Release();
    }
    return res;
}
