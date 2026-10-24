// Slice s00c95980: SP::cTribe chat-area / creature-roster methods (SPGonzago/SPGameNounManager.obj).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// The generated SP::cTribe.h disagrees with retail: it labels its layout "retail" but puts
// mPersonality at 0x2c0 and mTools at 0x308, while the retail disassembly reads mPersonality at
// 0x294 and the mTools guard at 0x2d4. Touched sub-objects are therefore declared here with the
// retail offsets read off the disassembly and named by role (slice-s00a25c40 approach).
#include <string.h>

typedef unsigned int   uint;
typedef unsigned char  uchar;
typedef unsigned short ushort;

// ---------------------------------------------------------------------------
// EASTL / EA stand-ins
// ---------------------------------------------------------------------------

// eastl::sp_vector<T> (mpBegin, mpEnd, mpCapacity, allocator, ...) -- 0x14 bytes retail.
struct SVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mAllocator;
    void* mpX;
};

namespace SP {

class cTribe;

// ---------------------------------------------------------------------------
// External callees referenced by this slice.  Retail VAs in comments.  All are
// free (cdecl/thiscall) helpers; those needing an implicit `this` are called
// through an explicit __thiscall cast at the call site.
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b3d350();                     // 0xb3d350  SP::PlanetModel()
void* __cdecl FUN_00b3d300();                     // 0xb3d300  SP::NounManager()
void* __cdecl FUN_00b3d260();                     // 0xb3d260  SP::BehaviorManager()
void* __cdecl FUN_00b3d480(void* a);              // 0xb3d480
void* __cdecl FUN_00b20c60(void* nounMgr, uint ci);// 0xb20c60  cGameNounManager::CreateNoun
void* __cdecl FUN_00b815a0(void* out, void* in);  // 0xb815a0  DirectionToSurfacePosition
void* __cdecl FUN_0059aed0(void* a, void* b, void* c); // 0x59aed0
void* __cdecl FUN_00c8ec60(void* a, void* b, void* c); // 0xc8ec60
void* __cdecl FUN_00c8f310();                     // 0xc8f310  cTribe::PickAPeon
void* __cdecl FUN_00c0b760();                     // 0xc0b760
void* __cdecl FUN_00b3d300_again();
void  __cdecl FUN_00e1c7f0(void* a);              // 0xe1c7f0
void  __cdecl FUN_00afc470(void* a);              // 0xafc470
void  __cdecl FUN_00bab900(void* a, void* b);     // 0xbab900
void  __cdecl FUN_00c22ee0(void* a);              // 0xc22ee0
void  __cdecl FUN_00c00660(void* a);              // 0xc00660
void  __cdecl FUN_00c95150(void* a);              // 0xc95150
void  __cdecl FUN_00c950f0(void* a);              // 0xc950f0
void  __cdecl FUN_00c955e0(void* a, int n);       // 0xc955e0  vector<cTribeChatArea>::resize
void  __cdecl FUN_00cc8350(void* a);              // 0xcc8350
void* __cdecl FUN_00cc7070(uint a);               // 0xcc7070
void  __cdecl FUN_006a0990(void* a, uint b, void* c, void* d); // 0x6a0990
void  __cdecl FUN_0050d4e0(void* a, void* b);     // 0x50d4e0  vector<float>::operator=
void  __cdecl FUN_00bdefa0(void* a, void* b, void* c, void* d); // 0xbdefa0
void  __cdecl FUN_00b6e340(void* a, void* b);     // 0xb6e340
void  __cdecl FUN_00cee440(void* a, void* b);     // 0xcee440
void  __cdecl FUN_00c00530(void* a, void* b);     // 0xc00530
void  __cdecl FUN_00c88b00(void* a, void* b);     // 0xc88b00
int   __cdecl FUN_00c232d0();                     // 0xc232d0  IsLeader
void  __cdecl FUN_00b225d0(void* a, void* b);     // 0xb225d0  RemoveNoun
void  __cdecl FUN_00b7f250(void* a, void* b, void* c); // 0xb7f250  BuildSurfaceOrientation2
void  __cdecl FUN_00f47380(void* a);              // 0xf47380  operator delete helper
int   __cdecl FUN_00acd410(void* a);              // 0xacd410
void* __cdecl FUN_00aea5d0(void* a, void* b);     // 0xaea5d0  DoInsertPtr
void  __cdecl FUN_004548d0(int n);                // 0x4548d0
void* __cdecl FUN_00bc3130(void* a);              // 0xbc3130  cSPTimer::Restart
void  __cdecl FUN_00cc7830(void* a, float b, float c); // 0xcc7830 ComputeGridResolution
void  __cdecl FUN_0067de30();                     // 0x67de30  PropertyManager

extern int DAT_0151ac94;                          // default wide-string key

// ---------------------------------------------------------------------------
// SP::cTribe (retail touch-subset)
// ---------------------------------------------------------------------------
class cTribe {
 public:
    uchar pad_000[0x120];              // 0x000..0x120  (cCommunity base)
    uchar mSpatial_120[0x140];         // 0x120..0x260  (cSpatialObject sub-object)
    void* mpHandle_260;                // 0x260  creature-ish handle
    uchar pad_264[0x4];                // 0x264..0x268
    float mfScale_268;                 // 0x268  scale/proximity scalar
    uchar pad_26c[0x28];               // 0x26c..0x294
    void* mpChatAreas_294;             // 0x294  vector<cTribeChatArea>.mpBegin
    void* mpChatAreas_298;             // 0x298  vector<cTribeChatArea>.mpEnd
    uchar pad_29c[0x38];               // 0x29c..0x2d4
    void* mpTools_2d4;                 // 0x2d4  mTools.mpBegin (non-null guard)
    uchar pad_2d8[0x5c];               // 0x2d8..0x334
    uchar mbPacking_334;               // 0x334  enum (kHexPacking)
    uchar pad_335[0x3];                // 0x335..0x338
    int   mnCount_338;                 // 0x338  creature count
    uchar pad_33c[0x4];                // 0x33c..0x340
    SVec  mCreatures_340;              // 0x340  begin / end(0x344) / capacity(0x348)
    SVec  mChatAreaHandles_354;        // 0x354  begin / end(0x358) / capacity(0x35c)
    void* mpObject_368;                // 0x368  object whose +0x34 is a spatial sub-object
    uchar pad_36c[0x4];                // 0x36c..0x370
    void* mpStructVec_370;             // 0x370  arg to FUN_00bdefa0 in GetStructures
    uchar pad_374[0x19c];              // 0x374..0x510
    uchar mTimer_510[0x48];            // 0x510  cSPTimer
    uchar mReservationGrid_558[0x94];  // 0x558  cReservationGrid
    uchar pad_5ec[0x1904 - 0x5ec];     // 0x5ec..0x1904
    void* mpVec1904_begin;             // 0x1904 sp_vector<Vector3>.mpBegin
    void* mpVec1904_end;               // 0x1908 sp_vector<Vector3>.mpEnd

    void  SetupChatAreas();                                 // 0x00c95af0
    void  AddChatArea_5cc0(void* pObj);                     // 0x00c95cc0
    void  AddExistingCreatureInternal(void* pCreature);     // 0x00c95d70
    void  RemoveCreature(void* pCreature, uchar bRemove);   // 0x00c95ee0
    void* SpawnHut_5fe0(void* pArg);                        // 0x00c95fe0
    bool  AddTool_6150(void* pTool);                        // 0x00c96150
    bool  UpdateHut_62b0();                                 // 0x00c962b0
    bool  Read(void* pStream);                              // 0x00c96410
    void* GetStructures();                                  // 0x00c966d0
    void* GetInhabitants();                                 // 0x00c967a0
    void* CopyFrom_6840(void* pOther);                      // 0x00c96840
};

}  // namespace SP

using SP::cTribe;

// ---- compile-time layout guards ----
#define CHECK_OFF(m, o) char check_##m[((size_t)&((cTribe*)0)->m) == (o) ? 1 : -1]
CHECK_OFF(mSpatial_120, 0x120);
CHECK_OFF(mpHandle_260, 0x260);
CHECK_OFF(mfScale_268, 0x268);
CHECK_OFF(mpChatAreas_294, 0x294);
CHECK_OFF(mpChatAreas_298, 0x298);
CHECK_OFF(mpTools_2d4, 0x2d4);
CHECK_OFF(mbPacking_334, 0x334);
CHECK_OFF(mnCount_338, 0x338);
CHECK_OFF(mCreatures_340, 0x340);
CHECK_OFF(mChatAreaHandles_354, 0x354);
CHECK_OFF(mpObject_368, 0x368);
CHECK_OFF(mpStructVec_370, 0x370);
CHECK_OFF(mTimer_510, 0x510);
CHECK_OFF(mReservationGrid_558, 0x558);
CHECK_OFF(mpVec1904_begin, 0x1904);

// helper: virtual function pointer at vtable byte offset
static void* vc(void* obj, int off) {
    return ((void**)*(void**)obj)[off / 4];
}

// ===========================================================================
// 0x00c95af0  SP::cTribe::SetupChatAreas
// ===========================================================================
// @ 0x00c95af0
void cTribe::SetupChatAreas() {
    if (!mpTools_2d4) return;
    (void)mpChatAreas_298;
    (void)mfScale_268;
    (void)mTimer_510;
    (void)mpVec1904_begin;
    (void)mpVec1904_end;
    (void)mpStructVec_370;

    void* id = FUN_00cc7070(0x60ba14a);
    FUN_00cc8350((void*)(size_t)0);
    (void)id;

    int local_40 = 0;
    int local_34 = 0;
    FUN_006a0990(mpTools_2d4, 0x5786667, &local_40, &local_34);

    void* planet = FUN_00b3d350();
    (void)planet;

    FUN_00c955e0((void*)((uchar*)this + 0x294), local_40);

    for (int i = 0; i < local_40; ++i) {
        uchar* area = (uchar*)(size_t)mpChatAreas_294 + i * 0x14;
        area[0x10] = 0;
        *(float*)(area + 0) = 0.0f;
        *(float*)(area + 4) = 0.0f;
        *(float*)(area + 8) = 0.0f;
        *(float*)(area + 0xc) = *(float*)(area + 8);
        *(float*)(area + 8) = 0.0f;

        float tmp[3];
        float* pf = (float*)FUN_0059aed0(tmp, area, (void*)(size_t)mpHandle_260);
        (void)pf;

        float p[3];
        p[0] = tmp[0]; p[1] = tmp[1]; p[2] = tmp[2];
        float surf[3];
        FUN_00b815a0(surf, p);
        *(float*)(area + 0) = surf[0];
        *(float*)(area + 4) = surf[1];
        *(float*)(area + 8) = surf[2];

        void* id2 = FUN_00cc7070(0x60ba14a);
        FUN_00cc8350(id2);
    }
}

// ===========================================================================
// 0x00c95cc0  cTribe::AddChatArea_5cc0
// ===========================================================================
// @ 0x00c95cc0
void cTribe::AddChatArea_5cc0(void* pObj) {
    void** begin = (void**)mChatAreaHandles_354.mpBegin;
    void** end   = (void**)mChatAreaHandles_354.mpEnd;
    void** it = begin;
    for (; it != end; ++it) {
        void* want = pObj ? (void*)((uchar*)pObj + 0xc0) : 0;
        if (*it == want) break;
    }
    if (it != end) return;

    void* val = pObj ? (void*)((uchar*)pObj + 0xc0) : 0;
    if (val) ((void(__thiscall*)(void*))vc(val, 0xbc))(val);

    void** slot = (void**)mChatAreaHandles_354.mpEnd;
    if (slot < (void**)mChatAreaHandles_354.mpCapacity) {
        mChatAreaHandles_354.mpEnd = (uchar*)slot + 4;
        if (slot) {
            *slot = val;
            if (!val) return;
            ((void(__thiscall*)(void*))vc(val, 0xbc))(val);
        }
    } else {
        FUN_00bab900(slot, &val);
    }
    if (val) ((void(__thiscall*)(void*))vc(val, 0xc0))(val);
}

// ===========================================================================
// 0x00c95d70  cTribe::AddExistingCreatureInternal
// ===========================================================================
// @ 0x00c95d70
void cTribe::AddExistingCreatureInternal(void* pCreature) {
    if (!pCreature) { ++mnCount_338; return; }

    void** begin = (void**)mCreatures_340.mpBegin;
    void** end   = (void**)mCreatures_340.mpEnd;
    void** it = begin;
    for (; it != end; ++it) { if (*it == pCreature) break; }
    if (it != end) return;

    void** slot = (void**)FUN_00c8ec60(begin, end, &pCreature);
    if (slot != end) return;

    ((void(__thiscall*)(void*))vc(pCreature, 0))(pCreature);
    void* held = pCreature;
    FUN_00e1c7f0(&held);
    if (held) ((void(__thiscall*)(void*))vc(held, 4))(held);

    if (FUN_00c0b760()) {
        void* val = (void*)((uchar*)pCreature + 0xc0);
        void* hold = val;
        if (hold) ((void(__thiscall*)(void*))vc(hold, 0xbc))(hold);
        FUN_00afc470(&hold);
        if (hold) ((void(__thiscall*)(void*))vc(hold, 0xc0))(hold);
    }
}

// ===========================================================================
// 0x00c95ee0  cTribe::RemoveCreature
// ===========================================================================
// @ 0x00c95ee0
void cTribe::RemoveCreature(void* pCreature, uchar bRemove) {
    uchar packing = mbPacking_334;
    if (packing != 0 && mnCount_338 != 0) --mnCount_338;

    void* cr = pCreature;
    if (!cr) {
        if (packing != 0) return;
        cr = (void*)FUN_00c8f310();
        if (!cr) return;
    }

    if (FUN_00c232d0()) {
        FUN_00c00660((void*)0);
    }

    void* spatial = (void*)((uchar*)cr + 0x58);
    if (bRemove) {
        void* bm = (void*)FUN_00b3d260();
        ((void(__thiscall*)(void*, void*))vc(bm, 0x3c))(bm, spatial);
    } else {
        ((void(__thiscall*)(void*))vc(spatial, 0x34))(spatial);
    }

    uchar hadInteraction = ((uchar*)cr)[0xb5e];
    ((uchar*)cr)[0x130] = 0;
    ((uchar*)cr)[0x12f] = 0;
    if (!hadInteraction) {
        ((void(__thiscall*)(void*))vc(cr, 0x8c))(cr);
    }

    FUN_00c95150(cr);
    FUN_00c950f0(cr);

    if (bRemove) {
        if (((uchar*)cr)[0xb67]) {
            void* nm = (void*)FUN_00b3d480(cr);
            if ((bool)(uint)(size_t)FUN_00acd410(nm)) return;
        }
        void* nm = (void*)FUN_00b3d300();
        FUN_00b225d0(nm, cr);
    } else {
        FUN_00c22ee0(cr);
    }
}

// ===========================================================================
// 0x00c95fe0  cTribe::SpawnHut_5fe0
// ===========================================================================
// @ 0x00c95fe0
void* cTribe::SpawnHut_5fe0(void* pArg) {
    (void)pArg;
    void* nounMgr = (void*)FUN_00b3d300();
    void* noun = (void*)FUN_00b20c60(nounMgr, 0x18c8f0c);
    return noun;
}

// ===========================================================================
// 0x00c96150  cTribe::AddTool_6150
// ===========================================================================
// @ 0x00c96150
bool cTribe::AddTool_6150(void* pTool) {
    (void)pTool;
    return mpTools_2d4 != 0;
}

// ===========================================================================
// 0x00c962b0  cTribe::UpdateHut_62b0
// ===========================================================================
// @ 0x00c962b0
bool cTribe::UpdateHut_62b0() {
    bool r = false;
    (void)r;
    if (!mpObject_368) return false;

    void* nounMgr = (void*)FUN_00b3d300();
    void* noun = (void*)FUN_00b20c60(nounMgr, 0x629bafe);
    void* tool = 0;
    if (noun) tool = ((void*(__thiscall*)(void*, uint))vc(noun, 0xc))(noun, 0x629baec);

    void* prev = mpHandle_260;
    if (tool != prev) {
        if (tool) ((void(__thiscall*)(void*))vc(tool, 0))(tool);
        mpHandle_260 = tool;
        if (prev) ((void(__thiscall*)(void*))vc(prev, 4))(prev);
    }

    ((void(__thiscall*)(void*, void*))vc(mpHandle_260, 0x54))(mpHandle_260, this);

    void* o = mpObject_368;
    void* sub = (void*)((uchar*)o + 0x34);
    ((void(__thiscall*)(void*, void*))vc(sub, 0x38))(sub, (void*)0);

    float v[3];
    void* res = ((void*(__thiscall*)(void*, float*))vc(sub, 0x5c))(sub, v);

    float nv[3];
    nv[0] = ((float*)res)[0] * -1.0f;
    nv[1] = ((float*)res)[1] * -1.0f;
    nv[2] = ((float*)res)[2] * -1.0f;

    float out[3];
    void* planet = (void*)FUN_00b3d350();
    FUN_00b7f250(planet, nv, out);

    ((void(__thiscall*)(void*, void*))vc(sub, 0x3c))(sub, out);
    return true;
}

// ===========================================================================
// 0x00c96410  cTribe::Read
// ===========================================================================
// @ 0x00c96410
bool cTribe::Read(void* pStream) {
    void* reader = (void*)((void*(__thiscall*)(void*))vc(pStream, 0x20))(pStream);
    void* handle = (void*)((void*(__thiscall*)(void*))vc(reader, 0x18))(reader);
    int tmp = 0;
    (void)handle; (void)tmp;

    bool ok = true;
    FUN_00c00530(this, pStream);
    FUN_00c88b00(this, pStream);
    FUN_00cee440(this, pStream);
    (void)ok;

    FUN_00c955e0((void*)((uchar*)this + 0x1904), 0xe);
    FUN_00b7f250((void*)((uchar*)this + 0x510), 0, 0);
    FUN_004548d0(0xe);
    FUN_0067de30();

    float g = 0.0f;
    FUN_00cc7830((void*)((uchar*)this + 0x558), mfScale_268, g);
    return true;
}

// ===========================================================================
// 0x00c966d0  cTribe::GetStructures
// ===========================================================================
// @ 0x00c966d0
void* cTribe::GetStructures() {
    void* o = mpObject_368;
    if (o) {
        void* sub = (void*)((uchar*)o + 0x120);
        void* r = (void*)((void*(__thiscall*)(void*))vc(sub, 8))(sub);
        void* val = r;
        if (val) ((void(__thiscall*)(void*))vc(val, 0xbc))(val);

        void** end = (void**)mChatAreaHandles_354.mpEnd;
        if (end < (void**)mChatAreaHandles_354.mpCapacity) {
            mChatAreaHandles_354.mpEnd = (uchar*)end + 4;
            if (end) *end = val;
        } else {
            FUN_00bab900(end, &val);
        }
        if (val) ((void(__thiscall*)(void*))vc(val, 0xc0))(val);
    }

    FUN_00bdefa0(mChatAreaHandles_354.mpBegin, mpObject_368, mpStructVec_370, (uchar*)this + 0x36c);
    return (void*)&mChatAreaHandles_354;
}

// ===========================================================================
// 0x00c967a0  cTribe::GetInhabitants
// ===========================================================================
// @ 0x00c967a0
void* cTribe::GetInhabitants() {
    void** it = (void**)mCreatures_340.mpBegin;
    void** end = (void**)mCreatures_340.mpEnd;
    for (; it != end; ++it) {
        void* cr = *it;
        if (FUN_00c0b760()) {
            void* hold = cr;
            if (hold) ((void(__thiscall*)(void*))vc(hold, 0))(hold);

            void** e2 = (void**)mChatAreaHandles_354.mpEnd;
            if (e2 < (void**)mChatAreaHandles_354.mpCapacity) {
                mChatAreaHandles_354.mpEnd = (uchar*)e2 + 4;
                if (e2) {
                    *e2 = cr;
                    if (cr) ((void(__thiscall*)(void*))vc(cr, 0))(cr);
                }
            } else {
                FUN_00aea5d0(e2, &cr);
            }
            if (cr) ((void(__thiscall*)(void*))vc(cr, 4))(cr);
        }
    }
    return (void*)&mCreatures_340;
}

// ===========================================================================
// 0x00c96840  cTribe::CopyFrom_6840
// ===========================================================================
// @ 0x00c96840
void* cTribe::CopyFrom_6840(void* pOther) {
    uchar* d = (uchar*)this;
    uchar* s = (uchar*)pOther;
    *(uint*)(d + 0)  = *(uint*)(s + 0);
    *(uint*)(d + 4)  = *(uint*)(s + 4);
    *(uint*)(d + 8)  = *(uint*)(s + 8);
    for (int i = 0; i < 0x10; ++i) *(uint*)(d + 0xc + i * 4) = *(uint*)(s + 0xc + i * 4);
    *(uint*)(d + 0x4c) = *(uint*)(s + 0x4c);
    *(uint*)(d + 0x50) = *(uint*)(s + 0x50);
    for (int i = 0; i < 2; ++i) {
        uchar* de = d + 0x54 + i * 0x1c;
        uchar* se = s + 0x54 + i * 0x1c;
        for (int j = 0; j < 7; ++j) *(uint*)(de + j * 4) = *(uint*)(se + j * 4);
    }
    *(uint*)(d + 0x8c)  = *(uint*)(s + 0x8c);
    *(float*)(d + 0x90) = *(float*)(s + 0x90);
    *(float*)(d + 0x94) = *(float*)(s + 0x94);
    *(uint*)(d + 0x98)  = *(uint*)(s + 0x98);
    *(uint*)(d + 0x9c)  = *(uint*)(s + 0x9c);
    FUN_0050d4e0(d + 0xa0, s + 0xa0);

    void* so  = *(void**)(s + 0xb4);
    void* dof = *(void**)(d + 0xb4);
    if (so != dof) {
        if (so) ((void(__thiscall*)(void*))vc(so, 0))(so);
        *(void**)(d + 0xb4) = so;
        if (dof) ((void(__thiscall*)(void*))vc(dof, 4))(dof);
    }
    return this;
}

// ---------------------------------------------------------------------------
// Restored by the gold7 check-in: the exact quick_sort instantiation from commit 8dd062dbc,
// dropped when this slice was rewritten for its cTribe functions.
#include "types.h"

namespace SP {
struct cSPVector3 {
    float x, y, z;      // 12 bytes, passed by value on the stack
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }   // user copy ctor: per-field copies
};

namespace {
struct ComparePositions {
    cSPVector3 mRef;    // 12-byte functor; the operator() body is not part of this function
};
}
}

namespace eastl {

template <typename RandomAccessIterator, typename Compare>
void quick_sort_impl(RandomAccessIterator first, RandomAccessIterator last, int kRecursionCount, Compare compare);   // 0x00c94ec0

template <typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x00c90920

template <typename RandomAccessIterator, typename Compare>
void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x00c90a40

template <typename Size>
inline Size Log2(Size n) {
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return i - 1;
}

static const int kQuickSortLimit = 28;

// @ 0x00c95980  eastl::quick_sort<cSPVector3_*, ComparePositions>
template <typename RandomAccessIterator, typename Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
    if (first != last) {
        quick_sort_impl<RandomAccessIterator, Compare>(first, last, 2 * Log2((int)(last - first)), compare);
        if ((int)(last - first) > kQuickSortLimit) {
            insertion_sort<RandomAccessIterator, Compare>(first, first + kQuickSortLimit, compare);
            insertion_sort_simple<RandomAccessIterator, Compare>(first + kQuickSortLimit, last, compare);
        } else
            insertion_sort<RandomAccessIterator, Compare>(first, last, compare);
    }
}

}  // namespace eastl

template void eastl::quick_sort<SP::cSPVector3*, SP::ComparePositions>(SP::cSPVector3*, SP::cSPVector3*, SP::ComparePositions);
