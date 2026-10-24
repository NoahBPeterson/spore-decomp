// Slice s00ccaff0 -- contiguous run 0x00ccaff0..0x00ccc120.
// Tools: VS2008 SP1 (cl 15.00).  Flags: /O2 /MD /Gy /EHsc /TP
//
//   00ccaff0  cTribeDisplayStrategy::SendSelectMessage
//   00ccb0f0  cTribeDisplayStrategy::MaintainSelectionState
//   00ccb2c0  cTribeDisplayStrategy::FUN_00ccb2c0  (citizen ghost-shell population)
//   00ccb420  cTribeDisplayStrategy::HandleMessage
//   00ccb810  eastl::vector<Vertex3D>::operator=  (Assign)
//   00ccba20  eastl::vector<Vertex3D>::insert(pos) (InsertAt)
//   00ccbb60  cTribeDisplayStrategy::FUN_00ccbb60  (erase citizen)
//   00ccbc00  hashtable<ImageCursorProvider>::operator[]
//   00ccbc90  eastl::vector<Vertex3D>::insert(pos,val)  [byte-exact]
//   00ccbd10  cTribeDisplayStrategy::FUN_00ccbd10  (targeted NPC effect)
//   00ccc070  map<AutoRefCount<Citizen>,cCitizenUIData>::operator[]
//   00ccc120  map<...,cCitizenUIData>::insert(hint,val)
#include <math.h>
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

// 0x18-byte vertex (position + normal/colour + uv)
struct Vertex3D { float f[6]; };

// refcounted object: vtable slot 0 = AddRef, slot 1 = Release
struct IObj { virtual void AddRef(); virtual void Release(); };
inline void AddRefOf(void* o) { if (o) ((IObj*)o)->AddRef(); }
inline void ReleaseOf(void* o) { if (o) ((IObj*)o)->Release(); }

// Interface (vtable) dispatch.  Only ever used to call a slot of an interface
// whose full vtable we do not model; never used to read a data field.
#define VF(o, n) (*(void**)((uint8_t*)(*(void**)(o)) + (n)))

// ---------------------------------------------------------------------------
// engine entry points (address-named so difftest can resolve them)
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b3d300();                                     // NounManager
void* __cdecl FUN_0067dcc0();                                     // MessageServer
void* __cdecl FUN_0067ddd0();                                     // EffectsManager
void* __cdecl FUN_00b30d70();                                     // GetGameTerrainCursor
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(int a, int b, const char* n, void* p);
void* __cdecl FUN_00f473a0(uint32_t size, uint32_t alloc, int a, int b, int c, int d); // operator_new
void  __cdecl FUN_00f47380(void* p);                              // operator_delete_array
void* __cdecl FUN_00ac8730(void* p);
void  __cdecl FUN_0075d4b0(const char* name, void* a, int b);
void* __cdecl FUN_00421c80(void* p, int a);                       // SlotMessage::Construct
void  __cdecl FUN_0061df40(void* p);
void  __cdecl FUN_00ccaf60();                                     // posse ghost callback
void  __cdecl FUN_00c99c30(void* tribe);                          // cTribe::ChooseNewHutModel
void* __cdecl FUN_00cd40b0();                                     // cTribeModeStrategy::Instance()

// __thiscall externs modelled as native member functions (the method name embeds
// the target address so difftest can resolve it).
struct S00e0ad00 { void __thiscall FUN_00e0ad00(int a); };
struct S00e25b50 { void* __thiscall FUN_00e25b50(); };                 // cSPUIPosseItemTribeGhostShell ctor
struct S00bfc5d0 { bool __thiscall FUN_00bfc5d0(); };
struct S00cc8be0 { void __thiscall FUN_00cc8be0(); };
struct S00e24c90 { void* __thiscall FUN_00e24c90(int a); };            // cSPUIPosse::FindItem
struct S00c8eae0 { uint32_t __thiscall FUN_00c8eae0(); };              // cTribe::GetMaxPopulation
struct S00bfc5f0 { void* __thiscall FUN_00bfc5f0(); };                 // cGameNounManager::GetPlayerTribe
struct S00cc9040 { void __thiscall FUN_00cc9040(void* key); };        // on this->[0x78]
struct S00e0f9c0 { void __thiscall FUN_00e0f9c0(void* key, int a, int b); }; // MinimapWin::RemoveIcon
struct S00cc9460 { void __thiscall FUN_00cc9460(void* obj); };        // MakeTribeIcon
struct S00cc91e0 { void __thiscall FUN_00cc91e0(void* obj); };
struct S00437f70 { void __thiscall FUN_00437f70(bool b); };           // Model::SetFlag
struct S00cd4460 { bool __thiscall FUN_00cd4460(uint32_t k); };       // TerrainHasKey
struct S00cd50b0 { void __thiscall FUN_00cd50b0(); };                 // TrackTribeMember
struct S00cd6980 { void __thiscall FUN_00cd6980(uint32_t e); };       // SignalTribeEvent
struct S00bfc5e0 { void __thiscall FUN_00bfc5e0(bool b); };           // on key+0x5a8
void* __cdecl FUN_006985b0(Vector3* out, const Vector3* in);     // OrthogonalVector
void* __cdecl FUN_0069b440(void* out, const Vector3* f, const Vector3* u); // Matrix3FromFacingAndUp
void* __cdecl FUN_0041cb40(void* dst, void* src);                 // Matrix3::Assign
void* __cdecl FUN_00b3d350();                                     // PlanetModel
void  __cdecl FUN_00b7e3b0(void* pm, Vector3* out, const Vector3* p); // GetNormalAt
float __cdecl FUN_00d99a60(void* a);                              // DistanceBetweenBodies

// rbtree / vector helpers
void __cdecl FUN_00e5c780();                                      // tree find
void __cdecl FUN_005f05e0();                                      // tree erase
Vertex3D* __cdecl FUN_00ccb260(uint32_t n, Vertex3D* f, Vertex3D* l); // Grow
void __cdecl FUN_00720250(Vertex3D* first, Vertex3D* last, Vertex3D* dst); // CopyVertex3D
void __cdecl FUN_00cc8b50(Vertex3D* d, Vertex3D* f, Vertex3D* l); // CopyBackwardVertex3D
Vertex3D* __cdecl FUN_00cca1d0(Vertex3D* f, Vertex3D* l, Vertex3D* d); // UninitCopyVertex3D
void __cdecl FUN_00cca110(void** out, Vertex3D* first, Vertex3D* lastEq, Vertex3D* dst, Vertex3D* last); // FillVertex3D

void* __cdecl FUN_00ccad80(void* a, void* b, void* c, void* d);   // tree insert (hint)
void* __cdecl FUN_00921580(void* n);                              // RBTreeIncrement

// ---------------------------------------------------------------------------
// nodes
// ---------------------------------------------------------------------------
struct RBNode {
    RBNode*  mpLeft;    // +0x00
    RBNode*  mpRight;   // +0x04
    RBNode*  mpParent;  // +0x08
    uint32_t mColor;    // +0x0c
};

// map<AutoRefCount<cSPCreatureCitizen>, cCitizenUIData>
struct CitizenUIData {
    void*    mpPosseObject;   // +0x14
    uint32_t mUiState;        // +0x18
};
struct CitizenNode : RBNode {
    void*         mpKey;      // +0x10  AutoRefCount<cSPCreatureCitizen>
    CitizenUIData mValue;     // +0x14
};

// map<cTribeModeStrategy*, cSPCreatureCitizen*> (the member tree)
struct MemberNode : RBNode {
    void* mpStrategy;   // +0x10
    void* mpCreature;   // +0x14
};

// ---------------------------------------------------------------------------
// eastl::vector<Vertex3D>
// ---------------------------------------------------------------------------
struct Vec3D {
    Vertex3D* mpBegin;      // +0x00
    Vertex3D* mpEnd;        // +0x04
    Vertex3D* mpCapacity;   // +0x08

    Vertex3D* Grow(uint32_t n, Vertex3D* first, Vertex3D* last);   // 0x00ccb260
    Vec3D*    Assign(Vec3D* other);                                // 0x00ccb810
    void      InsertAt(Vertex3D* pos, Vertex3D* val);              // 0x00ccba20
    Vertex3D* Insert(Vertex3D* pos, Vertex3D* val);                // 0x00ccbc90
};

// rbtree<...> object at 0x94 (its own `this` in FindOrInsert / InsertHint2).
struct TreeIter { CitizenNode* mpNode; };
struct EffectTree {
    void* mpNode00;      // +0x00
    void* mpEnd04;       // +0x04
    void* mpNode08;      // +0x08
    void* mpRoot0c;      // +0x0c
    void* mpNode10;      // +0x10
    uint8_t mFlag14;     // +0x14
    TreeIter Find(uint32_t* keyRef) const;                          // 0x00e5c780
    void     Erase(uint32_t* keyRef);                               // 0x005f05e0
    uint8_t* FindOrInsert(uint32_t* key);                           // 0x00ccc070
    uint8_t* InsertHint2(RBNode* hint, uint32_t* val);              // 0x00ccc120
    void*    FUN_00ccb930(void* out1, void* hint, void* out2, void* flag); // 0x00ccb930
};

// hashtable<uint, pair<const uint, ImageCursor>> at 0x2c0.
struct HashNode { void* mpValue; };
struct HashIter { void* mpNode; void* mpBucket; };
struct Hashtable {
    void*    mp_00;         // +0x00
    void**   mpBuckets;     // +0x04
    uint32_t mBucketCount;  // +0x08
    void     Find(HashIter* out, const uint32_t* keyRef) const;     // 0x00db4780
    void     InsertNode(HashIter* out, const uint32_t* key, uint32_t flag); // 0x00ccb1a0
    HashNode* FUN_00ccbc00(uint32_t* key);                          // 0x00ccbc00
};

// eastl::vector<8-byte item> and the cSPUIPosse slot that holds one.
struct PosseItem { uint32_t mWords[2]; };
struct ItemList {
    PosseItem* mpBegin;     // +0x00
    PosseItem* mpEnd;       // +0x04
    PosseItem* mpCapacity;  // +0x08
    int Count() const { return (int)(mpEnd - mpBegin); }
};
struct PosseObject {              // cSPUIPosse (only the item vector is used here)
    uint8_t pad_00[0xa4];
    ItemList mItems;              // +0xa4
};

// ---------------------------------------------------------------------------
// cTribeDisplayStrategy: `this` base differs per method (HandleMessage's this
// is 0x38 past the base used by SendSelect/Maintain/bb60), so members are named
// by the offset each method uses.
// ---------------------------------------------------------------------------
struct cTDS {
    uint8_t  pad_00[0x08];
    void*    mpPosseVec0;              // +0x08
    void*    mpPosseVec1;              // +0x0c
    void*    mpPosseVec2;              // +0x10
    void*    mpPosseVec3;              // +0x14
    void*    mpPosseVec4;              // +0x18
    void*    mpPosse;                  // +0x1c  cSPUIPosse*
    uint8_t  pad_20[0x38 - 0x20];
    void*    mpMiniMapWin_38;          // +0x38
    void*    mp_3c;                    // +0x3c
    void*    mpObj_40;                 // +0x40
    uint8_t  pad_44[0x60 - 0x44];
    MemberNode* mpMemberEnd;           // +0x60  (sentinel; == this+0x60)
    MemberNode* mpMemberRoot;          // +0x64
    uint8_t  pad_68[0x70 - 0x68];
    void*    mpMiniMapWin;             // +0x70
    uint8_t  pad_74[4];
    void*    mpObj_78;                 // +0x78
    uint8_t  pad_7c[0x94 - 0x7c];
    EffectTree mEffectTree;            // +0x94
    uint8_t  pad_ac[0xc0 - 0xac];
    uint8_t  mEffectSlot[0x200];       // +0xc0  inlined effect object (vtable at +0xc0)
    Hashtable mEffectCache;            // +0x2c0

    void  SendSelectMessage(void* key, uint32_t kind);                          // 0x00ccaff0
    void  MaintainSelectionState(void* key);                                    // 0x00ccb0f0
    void  FUN_00ccb2c0();                                                       // 0x00ccb2c0
    bool  HandleMessage(uint32_t id, void* msg);                                // 0x00ccb420
    void  FUN_00ccbb60(void* key);                                              // 0x00ccbb60
    void  FUN_00ccbd10(void* a, Vector3* p, float f, int kind, bool b);         // 0x00ccbd10
};

// ===========================================================================
// @ 0x00ccbb60
// ===========================================================================
void cTDS::FUN_00ccbb60(void* key)
{
    if (mpMiniMapWin)
        ((S00e0f9c0*)mpMiniMapWin)->FUN_00e0f9c0(key, 1, 0);
    uint32_t k = (uint32_t)(uintptr_t)key;
    AddRefOf(key);
    TreeIter it = mEffectTree.Find(&k);
    ReleaseOf(key);
    if (it.mpNode != (RBNode*)((uint8_t*)this + 0x98)) {
        if (mpObj_78)
            ((S00cc9040*)mpObj_78)->FUN_00cc9040(key);
        uint32_t k2 = (uint32_t)(uintptr_t)key;
        AddRefOf(key);
        mEffectTree.Erase(&k2);
        ReleaseOf(key);
    }
}

// ===========================================================================
// @ 0x00ccc070
// ===========================================================================
uint8_t* EffectTree::FindOrInsert(uint32_t* key)
{
    RBNode* end = (RBNode*)&mpEnd04;
    RBNode* root = (RBNode*)mpRoot0c;
    RBNode* pos = end;
    if (root) {
        uint32_t k = *key;
        do {
            if (*((uint32_t*)root + 4) < k)
                root = root->mpLeft;
            else {
                pos = root;
                root = root->mpRight;
            }
        } while (root);
    }
    if (pos != end && *((uint32_t*)pos + 4) <= *key)
        return (uint8_t*)pos + 0x14;
    uint32_t owned = *key;
    AddRefOf((void*)(uintptr_t)owned);
    uint32_t value[4];
    value[0] = owned; value[1] = 0; value[2] = 0; value[3] = 0;
    uint32_t flag = (uint32_t)(uintptr_t)key & 0xffffff00u;
    FUN_00ccb930((void*)&key, pos, value, (void*)(uintptr_t)flag);
    ReleaseOf((void*)(uintptr_t)owned);
    return (uint8_t*)(uintptr_t)key + 0x14;
}

// ===========================================================================
// @ 0x00ccc120
// ===========================================================================
uint8_t* EffectTree::InsertHint2(RBNode* hint, uint32_t* val)
{
    RBNode* end = (RBNode*)mpEnd04;
    uint8_t* r;
    if (hint == end || val[1] > ((uint32_t*)hint)[1] ||
        (val[1] == ((uint32_t*)hint)[1] && val[0] >= ((uint32_t*)hint)[0]))
        r = (uint8_t*)FUN_00ccad80(hint, end, val, (void*)(uint32_t)mFlag14);
    else
        r = (uint8_t*)FUN_00ccad80(mpNode00, hint, val, (void*)(uint32_t)mFlag14);
    if ((RBNode*)r == end ||
        ((uint32_t*)val)[1] < ((uint32_t*)r)[1] ||
        (((uint32_t*)val)[1] == ((uint32_t*)r)[1] && ((uint32_t*)val)[0] < ((uint32_t*)r)[0]))
        r = (uint8_t*)((Vec3D*)this)->Insert((Vertex3D*)r, (Vertex3D*)val);
    return r;
}

// ===========================================================================
// @ 0x00ccb810
// ===========================================================================
Vec3D* Vec3D::Assign(Vec3D* other)
{
    if (other == this)
        return this;
    Vertex3D* ob = other->mpBegin;
    uint32_t n = (uint32_t)((char*)other->mpEnd - (char*)ob) / 0x18u;
    Vertex3D* tb = mpBegin;
    if (n > (uint32_t)((char*)mpCapacity - (char*)tb) / 0x18u) {
        Vertex3D* nb = Grow(n, ob, other->mpEnd);
        if (mpBegin)
            FUN_00f47380(mpBegin);
        mpCapacity = (Vertex3D*)((char*)nb + (n + n * 2) * 8);
        mpBegin = nb;
        mpEnd = (Vertex3D*)((char*)nb + (n + n * 2) * 8);
        return this;
    }
    int have = (int)((char*)mpEnd - (char*)tb) / 0x18;
    if ((uint32_t)have < (uint32_t)n) {
        Vertex3D* mid = (Vertex3D*)((char*)ob + (have + have * 2) * 8);
        FUN_00720250(ob, mid, tb);
        Vertex3D* e = other->mpEnd;
        void* scratch;
        FUN_00cca110(&scratch, mid, e, mpEnd, e);
        mpEnd = (Vertex3D*)((char*)mpBegin + (n + n * 2) * 8);
        return this;
    }
    FUN_00720250(ob, other->mpEnd, tb);
    mpEnd = (Vertex3D*)((char*)mpBegin + (n + n * 2) * 8);
    return this;
}

// ===========================================================================
// @ 0x00ccba20
// ===========================================================================
void Vec3D::InsertAt(Vertex3D* pos, Vertex3D* val)
{
    Vertex3D* end = mpEnd;
    if (end != mpCapacity) {
        if (val >= pos && val < end)
            val = (Vertex3D*)((char*)val + 0x18);
        if (end) {
            ((uint32_t*)end)[0] = ((uint32_t*)end)[-6];
            ((uint32_t*)end)[1] = ((uint32_t*)end)[-5];
            end->f[2] = ((Vertex3D*)((char*)end - 0x18))->f[2];
            end->f[3] = ((Vertex3D*)((char*)end - 0x18))->f[3];
            end->f[4] = ((Vertex3D*)((char*)end - 0x18))->f[4];
        }
        FUN_00cc8b50(pos, (Vertex3D*)((char*)end - 0x18), end);
        ((uint32_t*)pos)[0] = ((uint32_t*)val)[0];
        ((uint32_t*)pos)[1] = ((uint32_t*)val)[1];
        ((uint32_t*)pos)[2] = ((uint32_t*)val)[2];
        ((uint32_t*)pos)[3] = ((uint32_t*)val)[3];
        ((uint32_t*)pos)[4] = ((uint32_t*)val)[4];
        ((uint32_t*)pos)[5] = ((uint32_t*)val)[5];
        mpEnd = (Vertex3D*)((char*)mpEnd + 0x18);
        return;
    }
    Vertex3D* b = mpBegin;
    int n = (int)((char*)end - (char*)b) / 0x18;
    int cap2;
    if (n == 0) {
        cap2 = 1;
    } else {
        cap2 = n + n;
        if (cap2 == 0) {
            b = 0;
            goto alloc_done;
        }
    }
    b = (Vertex3D*)FUN_00f473a0((cap2 + cap2 * 2) * 8, 0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
alloc_done:
    b = FUN_00cca1d0(mpBegin, pos, b);
    if (b) {
        ((uint32_t*)b)[0] = ((uint32_t*)val)[0];
        ((uint32_t*)b)[1] = ((uint32_t*)val)[1];
        ((uint32_t*)b)[2] = ((uint32_t*)val)[2];
        ((uint32_t*)b)[3] = ((uint32_t*)val)[3];
        ((uint32_t*)b)[4] = ((uint32_t*)val)[4];
    }
    Vertex3D* ne = FUN_00cca1d0(pos, mpEnd, b + 1);
    if (mpBegin)
        FUN_00f47380(mpBegin);
    mpBegin = b;
    mpEnd = ne;
    mpCapacity = (Vertex3D*)((char*)b + (cap2 + cap2 * 2) * 8);
}

// ===========================================================================
// @ 0x00ccbc00
// ===========================================================================
extern uint32_t g13ebc58;   // "App"

HashNode* Hashtable::FUN_00ccbc00(uint32_t* key)
{
    HashIter out;
    out.mpNode = 0; out.mpBucket = 0;
    Find(&out, key);
    if (out.mpNode == mpBuckets[mBucketCount]) {
        uint32_t keyval = *key;
        uint32_t flag = (uint32_t)(uintptr_t)key & 0xffffff00u;
        InsertNode(&out, &keyval, flag);
    }
    return (HashNode*)((uint8_t*)out.mpNode + 4);
}

// ===========================================================================
// @ 0x00ccbc90   (byte-exact)
// ===========================================================================
Vertex3D* Vec3D::Insert(Vertex3D* pos, Vertex3D* val)
{
    int idx = (int)((char*)pos - (char*)mpBegin) / 0x18;
    Vertex3D* end = mpEnd;
    if (pos == end && end != mpCapacity) {
        mpEnd = (Vertex3D*)((char*)end + 0x18);
        if (end) {
            ((uint32_t*)end)[0] = ((uint32_t*)val)[0];
            ((uint32_t*)end)[1] = ((uint32_t*)val)[1];
            end->f[2] = val->f[2];
            end->f[3] = val->f[3];
            end->f[4] = val->f[4];
        }
    } else {
        InsertAt(pos, val);
    }
    return (Vertex3D*)((char*)mpBegin + (idx + idx * 2) * 8);
}

// ===========================================================================
// @ 0x00ccaff0
// ===========================================================================
void cTDS::SendSelectMessage(void* key, uint32_t kind)
{
    AddRefOf(key);
    uint32_t k = (uint32_t)(uintptr_t)key;
    TreeIter it = mEffectTree.Find(&k);
    ReleaseOf(key);
    if (it.mpNode == (RBNode*)((uint8_t*)this + 0x98))
        return;
    void* m = FUN_00f473a0(0x40, 0x13f6b3c, 0, 0, 0, 0);
    if (m) {
        *(uint32_t*)((uint8_t*)m + 0x30) = 0x3e41916;
        *(void**)m = (void*)0x13eb90c;
        *(uint32_t*)((uint8_t*)m + 4) = 0;
        *(void**)m = (void*)0x13eb844;
        *(uint32_t*)((uint8_t*)m + 0x38) = 0;
        (*(void (__thiscall*)(void*))VF(m, 4))(m);
    } else {
        m = 0;
    }
    void* owner = it.mpNode->mValue.mpPosseObject;
    if ((*(uint8_t*)((uint8_t*)m + 0x38) & 1) && *(void**)((uint8_t*)m + 8))
        (*(void (__thiscall*)(void*))VF(*(void**)((uint8_t*)m + 8), 4))(*(void**)((uint8_t*)m + 8));
    *(void**)((uint8_t*)m + 8) = owner;
    AddRefOf(owner);
    *(uint32_t*)((uint8_t*)m + 0x38) |= 1;
    *(uint32_t*)((uint8_t*)m + 0x10) = kind;
    void* ms = FUN_0067dcc0();
    (*(void (__thiscall*)(void*, uint32_t, void*, int, int))VF(ms, 0x18))(
        ms, *(uint32_t*)((uint8_t*)m + 0x30), m, 0, 0);
    (*(void (__thiscall*)(void*))VF(m, 8))(m);
}

// ===========================================================================
// @ 0x00ccb0f0
// ===========================================================================
void cTDS::MaintainSelectionState(void* key)
{
    uint32_t k = (uint32_t)(uintptr_t)key;
    AddRefOf(key);
    TreeIter it = mEffectTree.Find(&k);
    ReleaseOf(key);
    if (it.mpNode == (RBNode*)((uint8_t*)this + 0x98))
        return;
    uint8_t* sub = (uint8_t*)key + 0xc0;
    uint32_t flags = 0;
    if ((*(uint8_t (__thiscall*)(void*))VF(sub, 0x50))(sub))
        flags = 1;
    if (((S00bfc5d0*)((uint8_t*)key + 0x5a8))->FUN_00bfc5d0() ||
        (*(uint8_t (__thiscall*)(void*))VF(sub, 0x24))(sub))
        flags |= 2;
    if (flags != it.mpNode->mValue.mUiState) {
        SendSelectMessage(key, flags);
        it.mpNode->mValue.mUiState = flags;
    }
}

// ===========================================================================
// @ 0x00ccb2c0
// ===========================================================================
void cTDS::FUN_00ccb2c0()
{
    void* posse = mpPosse;
    (*(void (__thiscall*)(void*, void*, void*))VF(posse, 0xa0))(posse, (void*)0x00ccaf60, this);
    void* mgr = FUN_00b3d300();
    void* tribe = ((S00bfc5f0*)mgr)->FUN_00bfc5f0();
    uint32_t maxPop = ((S00c8eae0*)tribe)->FUN_00c8eae0();
    uint32_t have = 0;
    void* v;
    if ((v = mpPosseVec0) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec1) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec2) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec3) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec4) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosse) != 0) have += ((PosseObject*)v)->mItems.Count();
    if (have < maxPop) {
        uint32_t n = maxPop - have;
        do {
            void* a = FUN_009512c0();
            void* p = FUN_009512d0(0x14c, 4, "UI/PosseItemTribeGhostShell", a);
            void* item = p ? ((S00e25b50*)p)->FUN_00e25b50() : 0;
            (*(void (__thiscall*)(void*, int))VF(item, 0x88))(item, 0xb);
            void* againPosse = mpPosse;
            (*(void (__thiscall*)(void*, void*))VF(againPosse, 0xa4))(againPosse, item);
            if (--n == 0) break;
        } while (true);
        ((S00cc8be0*)this)->FUN_00cc8be0();
        return;
    }
    if (maxPop < have) {
        uint32_t n = have - maxPop;
        do {
            void* item = ((S00e24c90*)mpPosse)->FUN_00e24c90(0);
            if (item) {
                void* p2 = mpPosse;
                (*(void (__thiscall*)(void*, void*, int))VF(p2, 0xa8))(p2, item, 1);
            }
            if (--n == 0) break;
        } while (true);
        ((S00cc8be0*)this)->FUN_00cc8be0();
    }
}

// ===========================================================================
// @ 0x00ccb420
// ===========================================================================
bool cTDS::HandleMessage(uint32_t id, void* msg)
{
    switch (id) {
    case 3: {
        void* p = *(void**)((uint8_t*)msg + 0x10);
        if (!p) break;
        void* o = FUN_00ac8730(p);
        if (!o) break;
        ((S00cc9460*)((uint8_t*)this - 0x38))->FUN_00cc9460(o);
        return true;
    }
    case 0x1ee100d: {
        void* v = mpMiniMapWin_38;
        if (!v) break;
        uint8_t* s = (uint8_t*)v + 4;
        (*(void (__thiscall*)(void*))VF(s, 0x90))(s);
        ((S00e0ad00*)v)->FUN_00e0ad00(4);
        return true;
    }
    case 0x1e8c9e0:
    case 0x58baddd: {
        ((S00cc9460*)((uint8_t*)this - 0x38))->FUN_00cc9460(*(void**)((uint8_t*)msg + 8));
        return true;
    }
    case 0x3deb129: {
        void* k = *(void**)((uint8_t*)msg + 8);
        if (!k) break;
        MemberNode* end = mpMemberEnd;
        MemberNode* it = mpMemberRoot;
        if (it == end) break;
        do {
            if (it->mpCreature == k) {
                uint8_t* s = (uint8_t*)it->mpStrategy;
                if (s[0xb5e] == 0) {
                    uint32_t flags = *(uint32_t*)((uint8_t*)msg + 0x10);
                    uint8_t* e = s + 0xc0;
                    if (flags & 1) {
                        (*(void (__thiscall*)(void*, int))VF(e, 0x54))(e, 1);
                        void* inst = FUN_00cd40b0();
                        if (!((S00cd4460*)inst)->FUN_00cd4460(0x56d1871)) {
                            if (((S00cd4460*)inst)->FUN_00cd4460(0x64be5ff))
                                ((S00cd6980*)inst)->FUN_00cd6980(0x64e70b3);
                        }
                    } else {
                        (*(void (__thiscall*)(void*, int))VF(e, 0x54))(e, 0);
                    }
                    ((S00bfc5e0*)(s + 0x5a8))->FUN_00bfc5e0((flags & 2) != 0);
                    ((cTDS*)((uint8_t*)this - 0x38))->MaintainSelectionState(it->mpStrategy);
                    void* cur = FUN_00b30d70();
                    (*(void (__thiscall*)(void*))VF(cur, 0x74))(cur);
                    cur = FUN_00b30d70();
                    (*(void (__thiscall*)(void*))VF(cur, 0xc8))(cur);
                }
            }
            it = (MemberNode*)FUN_00921580(it);
        } while (it != mpMemberEnd);
        return true;
    }
    case 0x3deb12a: {
        void* k = *(void**)((uint8_t*)msg + 8);
        if (!k) break;
        MemberNode* end = mpMemberEnd;
        MemberNode* it = mpMemberRoot;
        if (it == end) break;
        do {
            if (it->mpCreature == k) {
                void* inst = (void*)FUN_00cd40b0();
                (*(void (__thiscall*)(void*, int))VF((uint8_t*)inst, 0))((uint8_t*)inst, 0);
            }
            it = (MemberNode*)FUN_00921580(it);
        } while (it != mpMemberEnd);
        return true;
    }
    case 0x685ce6c: {
        uint8_t* base = *(uint8_t**)msg;
        bool f8 = (*(void**)((uint8_t*)msg + 8) == 0);
        void* v = *(void**)(base + 0x64);
        void* r = v ? (*(void* (__thiscall*)(void*, uint32_t))VF(v, 0xc))(v, 0x4f396a66) : 0;
        void* mgr = FUN_00b3d300();
        void* tribe = ((S00bfc5f0*)mgr)->FUN_00bfc5f0();
        if (!tribe || tribe != r) break;
        if (!f8) {
            void* m = FUN_00f473a0(0x40, 0x13ebc58, 0, 0, 0, 0);
            m = m ? FUN_00421c80(m, 0) : 0;
            FUN_0061df40(m);
            *(uint32_t*)((uint8_t*)m + 0x30) = 0x68b2082;
            *(void**)((uint8_t*)m + 8) = base;
            void* ms = FUN_0067dcc0();
            (*(void (__thiscall*)(void*, uint32_t, void*, int, int))VF(ms, 0x18))(ms, 0x68b2082, m, 0, 0);
            (*(void (__thiscall*)(void*))VF(m, 8))(m);
            return true;
        }
        void* e = (*(void* (__thiscall*)(void*))VF(tribe, 0xac))(tribe);
        if (!e) break;
        void* e2 = (*(void* (__thiscall*)(void*))VF((uint8_t*)e + 0x34, 0xac))((uint8_t*)e + 0x34);
        if (!e2) break;
        ((S00437f70*)e2)->FUN_00437f70(true);
        return true;
    }
    case 0x61ed580: {
        void* o = *(void**)((uint8_t*)msg + 8);
        if (!o) break;
        if (!mpObj_40) break;
        ((S00cc91e0*)mpObj_40)->FUN_00cc91e0(o);
        return true;
    }
    case 0x3e41917: {
        void* p = *(void**)((uint8_t*)this + 0x10);
        FUN_0075d4b0("c:\\dumpthumb.png", p, 1);
        return true;
    }
    case 0x68b2082: {
        uint8_t* base = *(uint8_t**)((uint8_t*)msg + 8);
        void* v = *(void**)(base + 0x64);
        void* r = v ? (*(void* (__thiscall*)(void*, uint32_t))VF(v, 0xc))(v, 0x4f396a66) : 0;
        void* mgr = FUN_00b3d300();
        void* tribe = ((S00bfc5f0*)mgr)->FUN_00bfc5f0();
        if (!tribe || tribe != r) break;
        FUN_00c99c30(tribe);
        void* e = (*(void* (__thiscall*)(void*))VF(tribe, 0xac))(tribe);
        if (!e) break;
        void* e2 = (*(void* (__thiscall*)(void*))VF((uint8_t*)e + 0x34, 0xac))((uint8_t*)e + 0x34);
        if (!e2) break;
        *(uint32_t*)((uint8_t*)e2 + 4) &= ~1u;
        break;
    }
    }
    return true;
}

// ===========================================================================
// @ 0x00ccbd10
// ===========================================================================
extern float g1582ff0;
extern float g1582ff4;
extern float g1471064;
extern float g13ef53c;
extern float g13ebc5c;
extern float g1485720;
extern float g169b184, g169b188, g169b18c;
extern uint8_t g169b160[0x24];   // a Matrix3

void cTDS::FUN_00ccbd10(void* a, Vector3* p, float f, int kind, bool b)
{
    (void)a;
    bool bVar4;
    uint8_t bVar5;
    if (g1582ff0 < f) {
        bVar4 = false;
        if (g1582ff4 < f) goto after_range;
        bVar5 = 1;
    } else {
        bVar4 = true;
after_range:
        bVar5 = 0;
    }
    uint32_t hash;
    switch (kind) {
    case 0:
        if (b) goto case3;
        hash = bVar4 ? 0x4ccc8e63u : ((uint32_t)(-(int)bVar5) & 0x60e181dc) + 0x8fbc1ed7;
        break;
    case 1:
        if (!b)
            hash = bVar4 ? 0xb69dc16au : ((uint32_t)(-(int)bVar5) & 0x879b0692) + 0xae79fece;
        else
            hash = bVar4 ? 0xa231da2fu : ((uint32_t)(-(int)bVar5) & 0xd8ed2874) + 0x7d2bf7a3;
        break;
    case 2:
        hash = bVar4 ? 0x3751cceau : ((uint32_t)(-(int)bVar5) & 0x22551592) + 0x2f2e0a4e;
        break;
    case 3:
case3:
        hash = bVar4 ? 0xb490e2ecu : ((uint32_t)(-(int)bVar5) & 0x2917cb66) + 0x59861ae4;
        break;
    default:
        return;
    }
    uint8_t* sub = mEffectSlot;
    Vector3 tmp;
    (*(Vector3* (__thiscall*)(void*, Vector3*, float, int))VF(sub, 0x74))(sub, &tmp, f, 1);
    void* body = (*(void* (__thiscall*)(void*))VF(sub, 0x2c))(sub);
    float dist = FUN_00d99a60(body);
    float weight = (g13ebc5c - dist) * g13ef53c;
    if (weight <= 0.5f) weight = 0.5f;
    if (weight >= g1485720) weight = g1485720;
    HashNode* e = mEffectCache.FUN_00ccbc00((uint32_t*)&tmp);
    void* h = e->mpValue;
    *(uint8_t*)((uint8_t*)e + 8) = 1;
    if (h == 0) {
newh:
        void* em = FUN_0067ddd0();
        if (e->mpValue) {
            void* old = e->mpValue;
            e->mpValue = 0;
            (*(void (__thiscall*)(void*))VF(old, 4))(old);
        }
        void* created = 0;
        uint8_t ok = (*(uint8_t (__thiscall*)(void*, uint32_t, int, void**))VF(em, 0x2c))(em, hash, 0, &created);
        if (ok) {
            h = created;
            *(uint32_t*)e = hash;
        } else {
            h = e->mpValue;
        }
        if (h == 0)
            return;
    } else if (h != (void*)*(uint32_t*)e) {
        (*(void (__thiscall*)(void*, int))VF(h, 0xc))(h, 1);
        h = 0;
        goto newh;
    }
    uint32_t n8 = 0, n4 = 0;
    Vector3 pos;
    pos = *p;
    n4 = n4 & ~4u;
    (void)n8;
    FUN_0041cb40(g169b160, g169b160);
    Vector3 src = *p;
    Vector3 normal;
    void* pm = FUN_00b3d350();
    FUN_00b7e3b0(pm, &normal, &src);
    Vector3 ortho;
    FUN_006985b0(&ortho, &normal);
    uint8_t m[0x24];
    FUN_0069b440(m, &normal, &ortho);
    n4 |= 2;
    g1471064 = f;
    (*(void (__thiscall*)(void*, void*))VF(h, 0x18))(h, &n4);
    uint8_t alive = (*(uint8_t (__thiscall*)(void*))VF(h, 0x10))(h);
    if (!alive)
        (*(void (__thiscall*)(void*, int))VF(h, 8))(h, 0);
    (void)normal; (void)m;
}