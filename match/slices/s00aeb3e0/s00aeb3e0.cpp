// Slice s00aeb3e0 -- Spore "space tool" (SpaceTool / CommManager) comm-event helpers,
// the comm-dialog host ctor/dtor, the SpaceTool hashtable find-or-insert, the
// cSPUICommScreen message handler and two small vector/serialization helpers.
//
// This file follows the idioms of the neighbouring slices s00aea5d0 (bfs2 #45) and
// s00ae9490 (cl1 #47): raw-offset accessors for the 0xa0-byte Entry (E/EI), refcounted
// addref/relref through masked vtable helpers, and every external callee declared by its
// hexadecimal name so the differential tester resolves the relocation.
//
// Flags: default VS2008 (/O2 /MD /Gy /EHsc /TP).  The originals are part of a /MD /O2
// Simulator build; the LTCG inlining of the original is not reproduced, so most bodies
// below are behaviourally-equivalent reconstructions rather than byte-exact copies.
#include "types.h"

typedef unsigned int   u32;
typedef unsigned char  u8;

extern "C" void* op_new(u32 size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
extern "C" void  op_del(void* p);                                                               // 0x00f47380

// ---- generic virtual dispatch helpers (masked targets) --------------------
typedef void* (__thiscall *tc0_t)(void*);
typedef void* (__thiscall *tc1_t)(void*, int);
typedef void* (__thiscall *tc2_t)(void*, int, int);
typedef void* (__thiscall *tc3_t)(void*, int, int, int);
typedef void* (__thiscall *tc4_t)(void*, int, int, int, int);
static inline void* vt0(void* p, int slot) { return ((tc0_t*)(*(void***)p))[slot](p); }
static inline void* vt1(void* p, int slot, int a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }
static inline void* vt2(void* p, int slot, int a, int b) { return ((tc2_t*)(*(void***)p))[slot](p, a, b); }
static inline void* vt3(void* p, int slot, int a, int b, int c) { return ((tc3_t*)(*(void***)p))[slot](p, a, b, c); }
static inline void* vt4(void* p, int slot, int a, int b, int c, int d) { return ((tc4_t*)(*(void***)p))[slot](p, a, b, c, d); }
static inline void  addref(void* p) { if (p) vt0(p, 0); }
static inline void  relref(void* p) { if (p) vt0(p, 1); }

#define E(e, off)  (*(void**)((char*)(e) + (off)))
#define EI(e, off) (*(int*)((char*)(e) + (off)))

static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---- external helpers (masked callees) ------------------------------------
struct E12 { u32 a; u32 b; void* p; };
struct E12Vec { E12* b; E12* e; E12* c; };
extern "C" bool EA_ReadInt32(void* s, int* p, int n, int flags);        // 0x0093a780

// ---- game singletons ------------------------------------------------------
void* SP_MessageServer();                    // 0x0067dcc0
void* SP_EventLog(int id, int a);            // 0x00b3d3e0
void* SP_NounManager();                      // 0x00b3d300
void* SP_CommManager();                      // 0x00b3d4a0
void* SP_StarManager();                      // 0x00b3d2a0
void* SP_EventLogMgr();                      // 0x00b3d2a0 alias
void* ctor_UILayout();                       // 0x00dd1ca0
void* FUN_01021300();                        // 0x01021300 GetPlayerEmpire
void* FUN_01021260();                        // 0x01021260 GetActivePlanet
void* FUN_010212a0();                        // 0x010212a0 GetActivePlanetRecord
int   FUN_01021090();                        // 0x01021090 GetPlayerEmpireID
int   FUN_01021080();                        // 0x01021080 GetUniverseContext
void* FUN_01046fc0(int id, int a, int b);    // 0x01046fc0 cStarMap::GetFromId
void* FUN_00ba6dc0(int id);                  // 0x00ba6dc0
void* FUN_00ba9370(int id);                  // 0x00ba9370
void* FUN_00c31730();                        // 0x00c31730 cEmpire::GetHomePlanet
void* FUN_00ce6950(void* starRecord);      // 0x00ce6950 cStarRecordRef::GetCommContext
void  FUN_00c77bf0(void* sphere);            // 0x00c77bf0
void  FUN_00b20750(int id);                  // 0x00b20750 GetFeedback
void* FUN_00bd9bf0(void* city);              // 0x00bd9bf0 cCity::GetCivilization
void* FUN_00aed4d0();                        // 0x00aed4d0

// neighbouring / intra-slice callees
void* FUN_00aeae10(void* first, void* last);          // 0x00aeae10 Vec12::erase
void  FUN_00aeae90(E12* pos, E12* value);             // 0x00aeae90 Vec12::DoInsertValue
void  FUN_0102df20(int* msg, int arg, int a4, int a5);// 0x0102df20 SP::DoSpaceCommAction
void  FUN_00cfeeb0(int* msg, int a2, int a3, int a4); // 0x00cfeeb0 SP::DoCivCommAction
struct Tgt {
    void* FUN_00ae9330(void* p);   // 0x00ae9330 thiscall
    void* FUN_00ae9000(void* p);   // 0x00ae9000 thiscall
};
void  FUN_00921440(void* out, int a, int b, int c);   // 0x00921440
void  FUN_009fd7f0(void* key);                        // 0x009fd7f0 Vec4::Vec4
void  FUN_00b5b960();                                 // 0x00b5b960 SP::cGonzagoSubsystem::ctor
void  FUN_00b5b9a0();                                 // 0x00b5b9a0 SP::cGonzagoSubsystem::dtor
void* FUN_010458f0(void* starMap, int a2, int a3, int a4); // 0x010458f0 CreateStarRecordVisual

// ===========================================================================
// The space tool (matches s00aea5d0 / s00ae9490 layouts).
// ===========================================================================
struct PtrVec { void** b; void** e; void** c; };
struct HashTable {
    u32    mBucketCount;   // +0x00
    void** mpBuckets;      // +0x04
    u32    mEndIndex;      // +0x08
};

struct SpaceTool {
    char   pad00[0x20];
    void*  mp20;           // +0x20 selected entry
    E12Vec mVec;           // +0x24 vector of Entry* (stride 4)
    char   pad30[0x08];    // +0x30
    int    m38;            // +0x38 current comm-event id
    char   pad3c[0x04];    // +0x3c
    HashTable mHash;       // +0x40
    char   pad50[0x10];    // +0x50
    u8     mb60;           // +0x60
    char   pad61[0x03];
    char   m64[0x14];      // +0x64

    void  FUN_00aeb5b0(void* value);                             // 0x00aeb5b0
    void  FUN_00aeb680(int newId);                               // 0x00aeb680
    void  FUN_00aeb700();                                        // 0x00aeb700
    void  FUN_00aeb720(int a1, int a2, int a3, int a4, int a5, int a6);  // 0x00aeb720
    void  FUN_00aeb760(int a1, int a2, int a3, int a4, int a5, int a6);  // 0x00aeb760
    void  FUN_00aeb7b0(int* msg, int a3, int a4, int a5);        // 0x00aeb7b0
    void  FUN_00aeb890(int* msg, int a2, int a3, int a4);        // 0x00aeb890
    void  FUN_00aeb960(void* out, void* key);                    // 0x00aeb960
    void  FUN_00aeba50(void* stream);                            // 0x00aeba50
    void  FUN_00aebb30();                                        // 0x00aebb30 dtor
    u32   FUN_00aebc10(int msgId, int arg);                      // 0x00aebc10
    void  FUN_00aebcd0(int index);                               // 0x00aebcd0

    // neighbouring / intra-slice callees, thiscall on the same object
    void* FUN_00aeb160(int a1, int a2, int a3, int a4, int a5, int a6, int a7); // 0x00aeb160 AddEntry
    void* FUN_00aeb240(int a1, int a2, int a3, int a4, int a5, int a6);    // 0x00aeb240 CreateEntry
    void  FUN_00aebe90(void* dlg);                               // 0x00aebe90 ShowDialog
    void  FUN_00aeb090();                                        // 0x00aeb090 Cleanup
    void  FUN_00aea850(void* p);                                 // 0x00aea850 ReleaseSelected
    void  FUN_00aea210();                                        // 0x00aea210 CloseCommEvent
    void  FUN_00ae9f50();                                        // 0x00ae9f50 OnShutdown0
    void  FUN_00ae9700(E12* out);                                // 0x00ae9700 E12::Read
    void  FUN_00aea510(int n);                                   // 0x00aea510
    void  FUN_00aeb030(void* table, u32 count);                  // 0x00aeb030 destroy_hash_buckets
    void  FUN_00ae6970();                                        // 0x00ae6970 vector dtor
    void  FUN_00de1270(int a);                                   // 0x00de1270 hash-resize
};

void* FUN_00aeae10(void* first, void* last);          // 0x00aeae10 Vec12::erase
void  FUN_00aeae90(E12* pos, E12* value);             // 0x00aeae90 Vec12::DoInsertValue

// ===========================================================================
// 0x00aeb3e0 -- event-log comm entry builder.  ret 0x20 / cdecl, 8 args.
// ===========================================================================
// @ 0x00aeb3e0
int FUN_00aeb3e0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, char a8)
{
    void* e = ((SpaceTool*)0)->FUN_00aeb160(a1, a3, a4, a5, a7, a6, 0);
    *(u8*)((char*)e + 0x30) = 1;

    int flag = (-(int)(a8 != 0) & 0x5272ef81) + (int)0xd0689d9a;
    void* starMap = FUN_01046fc0(a2, (int)0xc3f6ca28, flag);
    void* visual = FUN_010458f0(starMap, a2, (int)0xc3f6ca28, flag);
    *(void**)((char*)e + 0x10) = visual;

    bool skipEvent = false;
    {
        int ctx = FUN_01021080();
        if (ctx == 0) {
            skipEvent = true;
        } else if (FUN_01021080() != 1) {
            skipEvent = false;
        } else {
            skipEvent = true;
        }
        if (skipEvent) {
            FUN_00ba6dc0(a3);
            if ((int)(size_t)FUN_010212a0() == a3)
                goto lab_buildUserData;
        }
    }

    if (a1 == FUN_01021090()) {
        void* home = FUN_00c31730();
        int commCtx = (int)(size_t)FUN_00ce6950(home);
        int id;
        if (a3 == commCtx) id = (int)0x450a97a4;
        else               id = (int)0xf51fbdf;
        void* log = SP_EventLog(id, 0x131a9f54);
        int ev = (*(int(__thiscall**)(void*, int, int, int, int, int, int))((char*)*(void**)log + 0x00))
                     (log, id, 0x131a9f54, 0, 0, 1, 0);
        *(int*)((char*)e + 0x14) = ev;
    } else {
        void* emp = FUN_00ba9370(a1);
        if (emp == 0)
            goto lab_buildUserData;
        *(int*)(0x16e0d08 + 0x1c) = (int)(size_t)emp;
        void* log = SP_EventLog(0x5aa0b119, 0x131a9f54);
        int ev = (*(int(__thiscall**)(void*, int, int, int, int, int, int))((char*)*(void**)log + 0x00))
                     (log, (int)0x5aa0b119, 0x131a9f54, 0, 0, 1, 0);
        *(int*)((char*)e + 0x14) = ev;
    }

lab_buildUserData:
    {
        int* d = (int*)op_new(0x2c, "Simulator", 0, 0, 0, 0);
        if (d != 0) {
            d[2] = 0;
            d[1] = 0x13ef094;
            d[3] = -1;
            d[4] = 0;
            d[5] = -1;
            d[6] = -1;
            d[7] = -1;
            d[8] = 0;
            d[9] = 0;
            d[10] = 0;
            d[0] = 0x145bec4;
            d[1] = 0x145bec0;
            (*(void(__thiscall**)(int*))((char*)*(void**)d + 0x00))(d);
        }
        d[4] = a2;
        d[3] = a1;
        d[5] = a3;
        d[6] = a4;
        d[7] = a5;
        d[8] = a6;
        d[9] = *(int*)((char*)e + 0x10);
        d[10] = *(int*)((char*)e + 0x14);
        int ev = *(int*)((char*)e + 0x14);
        void* log = SP_EventLog(ev, (int)(size_t)d);
        (*(void(__thiscall**)(void*, int, int*))((char*)*(void**)log + 0x00))(log, ev, d);
        ev = *(int*)((char*)e + 0x14);
        log = SP_EventLog(ev, 0xae9c90);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)log + 0x00))(log, ev, 0xae9c90);
    }

    FUN_00c77bf0(SP_NounManager());
    (*(void(__thiscall**)(void*))((char*)*(void**)e + 4))(e);
    return (int)(size_t)e;
}

// ===========================================================================
// 0x00aeb5b0 -- vector<Entry12>::push_back of a 0xc-byte element.
// ===========================================================================
// @ 0x00aeb5b0
void SpaceTool::FUN_00aeb5b0(void* value)
{
    E12* end = (E12*)mVec.e;
    if (end < (E12*)mVec.c) {
        mVec.e = end + 1;
        if (end) {
            const E12* v = (const E12*)value;
            end->a = v->a;
            end->b = v->b;
            void* p = v->p;
            end->p = p;
            if (p)
                addref(p);
        }
        return;
    }
    FUN_00aeae90(end, (E12*)value);
}

// ===========================================================================
// 0x00aeb600 -- post the three comm-screen "close" messages then clean up.
// __fastcall (ecx = this), tail-calls Cleanup.
// ===========================================================================
// @ 0x00aeb600
void __fastcall FUN_00aeb600(void* self)
{
    vt3(SP_MessageServer(), 0x2c / 4, (int)(self ? (char*)self + 0x1c : 0), 0x580d038, (int)0xffffd8f1);
    vt3(SP_MessageServer(), 0x2c / 4, (int)(self ? (char*)self + 0x1c : 0), 0x153c326, (int)0xffffd8f1);
    vt3(SP_MessageServer(), 0x2c / 4, (int)(self ? (char*)self + 0x1c : 0), 0x609f3d9, (int)0xffffd8f1);
    ((SpaceTool*)self)->FUN_00aeb090();
}

// ===========================================================================
// 0x00aeb680 -- switch the current comm-event id, tearing down the previous
// event when crossing in/out of the "dbdba1" placeholder range.
// ===========================================================================
// @ 0x00aeb680
void SpaceTool::FUN_00aeb680(int newId)
{
    int cur = m38;
    if (newId == cur)
        return;

    if (cur != 0xdbdba1 && newId != 0xdbdba1) {
      if (newId >= (int)0x1654c04) {
        if (newId <= (int)0x1654c05) {
        int d = cur + (int)0xfe9ab3fc;
        if ((u32)d <= 1)
            ((Tgt*)this)->FUN_00ae9000((void*)(size_t)newId);
        else
            ((Tgt*)this)->FUN_00ae9330((void*)(size_t)newId);
        }
      }
    }

    if (m38 != 0xdbdba1 && newId != 0xdbdba1 &&
        (u32)(m38 + (int)0xfe9ab3fc) <= 1 &&
        (newId < (int)0x1654c04 || newId > (int)0x1654c05)) {
        FUN_00aeb090();
    }

    m38 = newId;
}

// ===========================================================================
// 0x00aeb700 -- clear the current comm-event (Cleanup if it was in range).
// ===========================================================================
// @ 0x00aeb700
void SpaceTool::FUN_00aeb700()
{
    u32 d = (u32)m38 + 0xfe9ab3fcU;
    if (d <= 1)
        FUN_00aeb090();
    m38 = -1;
}

// ===========================================================================
// 0x00aeb720 -- AddEntry + ShowDialog for a 6-argument comm event (ret 0x18).
// ===========================================================================
// @ 0x00aeb720
void SpaceTool::FUN_00aeb720(int a1, int a2, int a3, int a4, int a5, int a6)
{
    void* dlg = FUN_00aeb160(0, a6, a5, a4, a3, a2, a1);
    FUN_00aebe90(dlg);
}

// ===========================================================================
// 0x00aeb760 -- CreateEntry + ShowDialog for a 6-argument comm event (ret 0x18).
// ===========================================================================
// @ 0x00aeb760
void SpaceTool::FUN_00aeb760(int a1, int a2, int a3, int a4, int a5, int a6)
{
    void* dlg = FUN_00aeb240(a1, a2, a3, a4, a5, a6);
    FUN_00aebe90(dlg);
}

// ===========================================================================
// 0x00aeb7b0 -- comm-action dispatcher on a raw 4-dword message (ret 0x10).
// ===========================================================================
// @ 0x00aeb7b0
void SpaceTool::FUN_00aeb7b0(int* msg, int a3, int a4, int a5)
{
    int id = msg[0];
    if (id == (int)0xcaff0f72) {
        void* dlg = FUN_00aeb160(a3, a4, (int)0xc8fbf7d7, (int)0x2ea8fb98, 0, 0, 0);
        FUN_00aebe90(dlg);
    } else if (id == 0x1994745) {
        FUN_00ae9f50();
        vt4(SP_MessageServer(), 0x18 / 4, 0x490d429, 0, 0, 0);
    } else if (id == 0x2d5dcec) {
        int b = msg[1];
        int c = msg[3];
        void* dlg = FUN_00aeb160(a3, a4, c, b, a5, 0, 0);
        FUN_00aebe90(dlg);
    } else {
        FUN_0102df20(msg, a3, a4, a5);
    }

    void* sel = mp20;
    if (sel != 0 &&
        *(int*)((char*)sel + 0x64) == *(int*)((char*)sel + 0x68) &&
        *(int*)((char*)sel + 0x78) == *(int*)((char*)sel + 0x7c) &&
        msg[1] != (int)0x2ea8fb98 && msg[1] != 0) {
        FUN_00aea210();
        FUN_00aea850(mp20);
    }
}

// ===========================================================================
// 0x00aeb890 -- civ-comm action dispatcher (CreateEntry variant, ret 0x10).
// ===========================================================================
// @ 0x00aeb890
void SpaceTool::FUN_00aeb890(int* msg, int a2, int a3, int a4)
{
    int commCtx = (int)(size_t)FUN_00ce6950(FUN_01021260());
    int v;
    if (a4 != 0)
        v = (*(int(__thiscall**)(int, int))((char*)*(void**)a4 + 0x0c))(a4, 0x17f243b);
    else if (a2 != 0)
        v = (*(int(__thiscall**)(int, int))((char*)*(void**)a2 + 0x0c))(a2, 0x17f243b);
    else
        v = 0;

    int id = msg[0];
    if (id == (int)0xcaff0f72) {
        void* dlg = FUN_00aeb240(v, 0, 1, (int)0x2ea8fb98, (int)0xc8fbf7d7, 0);
        FUN_00aebe90(dlg);
    } else if (id == 0x1994745) {
        FUN_00ae9f50();
        vt4(SP_MessageServer(), 0x18 / 4, 0x490d429, 0, 0, 0);
    } else if (id == 0x2d5dcec) {
        void* dlg = FUN_00aeb240(a3, a4, 1, msg[1], msg[3], 0);
        FUN_00aebe90(dlg);
    }

    FUN_00cfeeb0(msg, a2, a3, a4);
    (void)commCtx;
}

// ===========================================================================
// 0x00aeb960 -- hashtable find-or-insert, out = {node, bucketPtr, inserted}.
// Nodes are 0x1c bytes: key at +0x00, payload at +0x0c, next at +0x18.
// ===========================================================================
// @ 0x00aeb960
void SpaceTool::FUN_00aeb960(void* outv, void* key)
{
    u32 k = *(u32*)key;
    u32 bucket = k % mHash.mBucketCount;
    char* bucketPtr = (char*)mHash.mpBuckets + bucket * 4;
    char* node = *(char**)bucketPtr;

    while (node != 0) {
        if (k == *(u32*)node) {
            u32* out = (u32*)outv;
            out[0] = (u32)(size_t)node;
            *((u8*)outv + 8) = 0;
            out[1] = (u32)(size_t)bucketPtr;
            return;
        }
        node = *(char**)(node + 0x18);
    }

    char local[4];
    FUN_00921440(local, mHash.mBucketCount, mHash.mEndIndex, 1);

    char* n = (char*)op_new(0x1c, "Simulator", 0, 0, kAllocFile, 0xd1);
    if (n != 0)
        FUN_009fd7f0(key);
    *(u32*)(n + 0x18) = 0;

    if (local[0] != 0) {
        bucket = k % *(u32*)(local + 0);
        FUN_00de1270(*(int*)(local + 0));
    }

    u32 off = bucket * 4;
    *(u32*)(n + 0x18) = *(u32*)((char*)mHash.mpBuckets + off);
    *(u32*)((char*)mHash.mpBuckets + off) = (u32)(size_t)n;
    mHash.mEndIndex++;

    u32* out = (u32*)outv;
    out[0] = (u32)(size_t)n;
    *((u8*)outv + 8) = 1;
    out[1] = (u32)(size_t)mHash.mpBuckets + off;
}

// ===========================================================================
// 0x00aeba50 -- deserialize a vector of 0xc-byte elements from a stream.
// ===========================================================================
// @ 0x00aeba50
void SpaceTool::FUN_00aeba50(void* stream)
{
    FUN_00aeae10(mVec.b, mVec.e);

    int count = 0;
    void* inner = vt0(stream, 0x20 / 4);
    void* io = vt0(inner, 0x18 / 4);
    EA_ReadInt32(io, &count, 1, 0);
    FUN_00aea510(count);

    for (int i = 0; i < (u32)count; ++i) {
        E12 tmp;
        tmp.a = 0; tmp.b = 0; tmp.p = 0;
        FUN_00ae9700(&tmp);
        E12* end = (E12*)mVec.e;
        if (end < (E12*)mVec.c) {
            mVec.e = end + 1;
            if (end) {
                end->a = tmp.a;
                end->b = tmp.b;
                end->p = tmp.p;
                if (end->p)
                    addref(end->p);
            }
        } else {
            FUN_00aeae90(end, &tmp);
        }
        if (tmp.p)
            relref(tmp.p);
    }

    vt0(this, 0x1c / 4);
}

// ===========================================================================
// 0x00aebb30 -- destructor: release the hash buckets, vectors and selected
// entry, restore the derived vtables and tail-jump to the base dtor.
// ===========================================================================
// @ 0x00aebb30
void SpaceTool::FUN_00aebb30()
{
    char* s = (char*)this;
    *(u32*)(s + 0x00) = 0x145bf20;
    *(u32*)(s + 0x04) = 0x145bf1c;
    *(u32*)(s + 0x1c) = 0x145bf14;

    int e = *(int*)(s + 0x64);
    if (*(int*)(s + 0x6c) - e > 1 && e != 0)
        op_del((void*)(size_t)e);

    FUN_00aeb030(*(void**)(s + 0x44), *(u32*)(s + 0x48));
    char* ht = s + 0x40;
    *(u32*)(ht + 0x0c) = 0;
    if (*(u32*)(ht + 0x08) > 1)
        op_del(*(void**)(ht + 0x04));

    if (*(void**)(s + 0x3c)) {
        void* p = *(void**)(s + 0x3c);
        relref(p);
    }

    FUN_00ae6970();
    if (*(void**)(s + 0x20))
        relref(*(void**)(s + 0x20));

    *(u32*)(s + 0x1c) = 0x13eb394;
    FUN_00b5b9a0();
}

// ===========================================================================
// 0x00aebc10 -- cSPUICommScreen message handler (ret 8).
// ===========================================================================
// @ 0x00aebc10
u32 SpaceTool::FUN_00aebc10(int msgId, int arg)
{
    if (msgId == 0x153c326) {
        void* lay = ctor_UILayout();
        if (lay != 0) {
            lay = ctor_UILayout();
            vt0(lay, 0xdd30d0 / 4);   // SP::cSPUICommScreen::Hide
        }
        return 0;
    }
    if (msgId == 0x580d038) {
        void* dlg = mp20;
        if (dlg != 0) {
            int a1 = *(int*)((char*)dlg + 0x14);
            int a2 = *(int*)((char*)dlg + 0x0c);
            int a3 = *(int*)((char*)dlg + 0x1c);
            int a4 = *(int*)((char*)dlg + 0x18);
            int a5 = *(int*)((char*)dlg + 0x20);
            (void)arg;
            SpaceTool* cm = (SpaceTool*)SP_CommManager();
            void* d = cm->FUN_00aeb160(a2, a1, a4, a3, a5, 0, 0);
            cm->FUN_00aebe90(d);
            void* sel = mp20;
            if (sel != 0) {
                mp20 = 0;
                relref(sel);
            }
        }
        return 0;
    }
    if (msgId == 0x609f3d9) {
        *((u8*)this + 0x44) = 1;
        return 0;
    }
    return 0;
}

// ===========================================================================
// 0x00aebcd0 -- select and act on the entry at an index (ret 4).
// ===========================================================================
// @ 0x00aebcd0
void SpaceTool::FUN_00aebcd0(int index)
{
    void* sel = mp20;
    if (sel == 0)
        return;

    int count = (*(int*)((char*)sel + 0x68) - *(int*)((char*)sel + 0x64)) >> 4;
    int l10, l0c, l8, l4;
    void* ref;
    if (index < count) {
        char* p = (char*)(*(int*)((char*)sel + 0x64) + index * 0x10);
        l10 = *(int*)(p + 0x00);
        l0c = *(int*)(p + 0x04);
        l8  = *(int*)(p + 0x08);
        l4  = *(int*)(p + 0x0c);
        ref = *(void**)((char*)sel + 0x40);
    } else {
        int d = index - count;
        char* p = (char*)(d * 0x10 + *(int*)((char*)sel + 0x78));
        l10 = *(int*)(p + 0x00);
        l0c = *(int*)(p + 0x04);
        l8  = *(int*)(p + 0x08);
        l4  = *(int*)(p + 0x0c);
        ref = *(void**)(*(int*)((char*)sel + 0x50) + d * 0xc + 8);
    }

    void* e = mp20;
    int local[4];
    local[0] = l10; local[1] = l0c; local[2] = l8; local[3] = l4;
    if (*(int*)((char*)e + 0x0c) == 1) {
        int a1 = *(int*)((char*)e + 0x18);
        int a2 = *(int*)((char*)e + 0x24);
        int a3 = *(int*)((char*)e + 0x20);
        FUN_00b20750(a1);
        int civ = *(int*)((char*)e + 0x28);
        if (civ == 0)
            civ = (int)(*(int*)((char*)e + 0x20));
        FUN_00aeb890(local, civ, a3, a2);
        FUN_00aea850(e);
        return;
    }
    FUN_00aeb7b0(local, *(int*)((char*)e + 0x18), *(int*)((char*)e + 0x34), (int)(size_t)ref);
    FUN_00aea850(e);
}

// ===========================================================================
// 0x00aebde0 -- constructor of the comm-dialog host (ret).
// ===========================================================================
// @ 0x00aebde0
void* FUN_00aebde0(void* self)
{
    char* p = (char*)self;
    FUN_00b5b960();                            // SP::cGonzagoSubsystem::ctor

    *(u32*)(p + 0x1c) = 0x13eb394;
    *(u32*)(p + 0x00) = 0x145bf20;
    *(u32*)(p + 0x04) = 0x145bf1c;
    *(u32*)(p + 0x1c) = 0x145bf14;
    *(u32*)(p + 0x20) = 0;
    *(u32*)(p + 0x24) = 0;
    *(u32*)(p + 0x28) = 0;
    *(u32*)(p + 0x2c) = 0;
    *(int*)(p + 0x38) = -1;
    *(u32*)(p + 0x3c) = 0;
    *(float*)(p + 0x50) = 1.0f;                // _DAT_01485720
    *(float*)(p + 0x54) = 2.0f;                // 0x01470f1c
    *(u32*)(p + 0x4c) = 0;
    *(u32*)(p + 0x58) = 0;
    *(u32*)(p + 0x48) = 1;
    *(u32*)(p + 0x44) = 0x154df28;
    *(u8*)(p + 0x60) = 0;
    *(u32*)(p + 0x64) = 0x1667bac;             // gEmptyString16
    *(u32*)(p + 0x68) = 0x1667bac;
    *(u32*)(p + 0x6c) = 0x1667bad;
    *(int*)(p + 0x74) = -1;
    return p;
}
