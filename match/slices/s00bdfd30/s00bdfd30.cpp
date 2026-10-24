// Slice s00bdfd30 -- builds the list of candidate links (pairs of live combat objects) for a combat group.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <string.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct PointVec { Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCap; };

// SP::cCombatant (sub-object at +0x120 of the queried host)
struct Combatant {
    int GetDamageState();                                   // 0x008e7f80
};

struct PosIface {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual const Vec3* GetPos();                           // +0x2c
};

struct Host {                                               // result of QueryInterface(0xe9cb8ba)
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual uint32_t GetType();                             // +0x20
    char pad04[0x34 - 4];
    PosIface pos;                                           // +0x34
    char pad38[0x120 - 0x38];
    Combatant cmb;                                          // +0x120
    char pad121[0x2c8 - 0x121];
    PointVec* GetPoints();                                  // 0x00bcc6c0 (this+0x2c8)
    PointVec* GetNormals();                                 // 0x00bcc6d0 (this+0x2dc)
};

struct Object {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual Host* QueryInterface(uint32_t type);            // +0x0c
};

struct Entry {                                              // 0x18 bytes
    uint8_t flag;
    char pad[0x17];
    Object* Get();                                          // 0x00fcc210 ([this+4])
};

struct Link {                                               // 0x50 bytes
    int a, b;
    float f0, f1, f2, f3, f4, f5;
    Vec3 pa;                                                // +0x20
    Vec3 pb;                                                // +0x2c
    Vec3 da;                                                // +0x38
    Vec3 db;                                                // +0x44
};

struct LinkVec {
    Link* mpBegin; Link* mpEnd; Link* mpCap;
    void erase(Link* first, Link* last);                    // 0x00bdeb10
    void DoInsertValue(Link* pos, Link& v);                 // 0x00bdeb80
    __forceinline void push_back()
    {
        if (mpEnd < mpCap) {
            mpEnd = mpEnd + 1;
        } else {
            Link tmp;
            DoInsertValue(mpEnd, tmp);
        }
    }
};

int __cdecl NearestIndex(PointVec* v, const Vec3* p);       // 0x00ac08f0

struct MatrixOwner { char pad[0x274]; uint8_t mat[1]; };

extern const unsigned kMaxEntries;                          // 0x01459c68 (= 14)

struct cCombatLinks {
    char pad000[0x324];
    MatrixOwner* mMatrix;                                   // +0x324
    char pad328[0x43c - 0x328];
    Entry* mEntriesBegin;                                   // +0x43c
    Entry* mEntriesEnd;                                     // +0x440
    char pad444[0x684 - 0x444];
    LinkVec mLinks;                                         // +0x684
    void BuildLinks();                                      // 0x00be0020
};

static __forceinline Vec3 Normalized(const Vec3& d)
{
    float inv = (float)(1.0 / sqrt(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f));
    return Vec3(inv * d.x, d.y * inv, d.z * inv);
}

// @ 0x00be0020
void cCombatLinks::BuildLinks()
{
    mLinks.erase(mLinks.mpBegin, mLinks.mpEnd);
    unsigned total = (unsigned)(mEntriesEnd - mEntriesBegin);
    const unsigned& cnt = (total > 14) ? kMaxEntries : total;
    int n = (int)cnt;
    if (n == 0)
        return;
    for (int i = 0; i < n - 1; i++) {
        Object* oa = mEntriesBegin[i].Get();
        if (!oa)
            continue;
        Host* ha = oa->QueryInterface(0xe9cb8ba);
        if (!ha)
            continue;
        if (ha->cmb.GetDamageState() == 2)
            continue;
        for (int j = i + 1; j < n; j++) {
            if (!mMatrix->mat[i * 14 + j])
                continue;
            if (!mEntriesBegin[j].flag)
                continue;
            Object* ob = mEntriesBegin[j].Get();
            if (!ob)
                continue;
            Host* hb = ob->QueryInterface(0xe9cb8ba);
            if (!hb)
                continue;
            if (hb->cmb.GetDamageState() == 2)
                continue;

            float f0 = 0.0f, f1 = 0.0f, f2 = 0.0f, f3 = 0.0f, f4 = 0.0f, f5 = 0.0f;
            uint32_t ta = ha->GetType();
            uint32_t tb = hb->GetType();
            bool ba = (ta == 0x18ea1eb || ta == 0x18eb106);
            bool bb = (tb == 0x18ea1eb || tb == 0x18eb106);
            if (ta == 0x18ea2cc) {
                if (bb) {
                    f0 = 1.0f;
                    goto L224;
                }
                if (tb != 0x1a56aba)
                    goto L224;
                f2 = 1.0f;
            L24e:
                if (ba)
                    f4 = 1.0f;
            } else {
                if (ta == 0x1a56aba && bb)
                    f1 = 1.0f;
            L224:
                if (tb == 0x18ea2cc) {
                    if (ba)
                        f3 = 1.0f;
                    else if (ta == 0x1a56aba)
                        f5 = 1.0f;
                } else if (tb == 0x1a56aba) {
                    goto L24e;
                }
            }

            mLinks.push_back();
            Link* l = mLinks.mpEnd - 1;
            l->a = i;
            l->b = j;
            l->f0 = f0; l->f1 = f1; l->f2 = f2; l->f3 = f3; l->f4 = f4; l->f5 = f5;

            Vec3 pa = *ha->pos.GetPos();
            Vec3 pb = *hb->pos.GetPos();
            Vec3 d1 = Vec3(pb.x - pa.x, pb.y - pa.y, pb.z - pa.z);
            l->da = Normalized(d1);
            l->pa.x = pa.x + l->da.x;
            l->pa.y = l->da.y + pa.y;
            l->pa.z = l->da.z + pa.z;
            Vec3 d2 = Vec3(pa.x - pb.x, pa.y - pb.y, pa.z - pb.z);
            l->db = Normalized(d2);
            l->pb.x = pb.x + l->db.x;
            l->pb.y = l->db.y + pb.y;
            l->pb.z = l->db.z + pb.z;

            PointVec* pts = ha->GetPoints();
            PointVec* nrm = ha->GetNormals();
            if (pts->mpBegin != pts->mpEnd) {
                int k = NearestIndex(pts, &pb);
                Vec3 p = pts->mpBegin[k];
                Vec3 q = nrm->mpBegin[k];
                l->pa = p;
                l->da = q;
            }
            PointVec* pts2 = hb->GetPoints();
            PointVec* nrm2 = hb->GetNormals();
            if (pts2->mpBegin != pts2->mpEnd) {
                int k = NearestIndex(pts2, &pa);
                Vec3 p = pts2->mpBegin[k];
                Vec3 q = nrm2->mpBegin[k];
                l->pb = p;
                l->db = q;
            }
        }
    }
}

// ===========================================================================
// gold7 functions (0x00BDFD30..0x00BE0FC0).  See the per-function notes below.
// Flags: /O2 /MD /Gy /GS- /TP /arch:SSE /fp:fast
// ===========================================================================

struct GameTime { bool IsPlayer(void* p); };                  // 0x00ac8d60
GameTime* GameTimeQuery();                                    // 0x00b3d480
int GetPlayerEmpireID();                                      // 0x01021090
void EndThisPlayer(void* self);                               // 0x00bdbf10

namespace EA { namespace IO {
struct IStream;
void ReadInt32(IStream* s, void* out, int count, int flag);   // 0x0093a780
}}

struct IStreamObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void* V18();                                      // +0x18
};
struct IStreamProvider {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void Close();                                     // +0x1c
    virtual IStreamObj* GetStream();                          // +0x20
};

extern int g_156e880;                                         // 0x0156e880
void* operator_new_simulator(unsigned size);                  // 0x00f473a0
void MoveOverlap(int** first, int** last, int** dst);         // 0x00ae6880
void VectorEraseAutoRef(void* first, void* last);             // 0x00e25bd0
void FUN_00c3f2d0(void* p, int v);                            // 0x00c3f2d0
void FUN_00bfc720(void* p);                                   // 0x00bfc720
struct cGameNounManager { void RemoveNoun(void* n); };        // 0x00b225d0
cGameNounManager* NounManager();                              // 0x00b3d300
void SPVectorDoInsertPtr(void** pos, void* v);                // 0x00aea5d0
int InsertNode(void* header, void* lb, int key);              // 0x00de6a60

// --- EA::Text::AnalysisInfo_ (POD 0x20, bulk-copied) -----------------------
struct AnalysisInfo { int w[8]; };                   // 0x20 bytes

struct AnalysisVec {                                 // eastl::vector<AnalysisInfo, sp_vector_allocator>
    AnalysisInfo* mpBegin; AnalysisInfo* mpEnd; AnalysisInfo* mpCap;
    void insert(AnalysisInfo* pos, const AnalysisInfo& v);   // 0x00c06c30
    void erase(AnalysisInfo* first, AnalysisInfo* last);     // 0x00899420
    void resize(unsigned n);                                 // 0x00f281f0
    __forceinline void push_back(const AnalysisInfo& v) {
        if (mpEnd < mpCap) { *mpEnd = v; ++mpEnd; }
        else insert(mpEnd, v);
    }
};

struct GTClock {
    long long Now();                                 // 0x00b316c0
};
GTClock* GameTimeManager();                          // 0x00b3d380

struct cAnalysisOwner {
    char pad0[0x7f8];
    AnalysisVec m7f8;                                // +0x7f8
    void AddAnalysis(const AnalysisInfo& a, long long delta);   // 0x00be06c0
};

// A 0x14-byte bubble record pushed into cCommunity's bubble vectors.
struct EmptyBubble {
    float x, y, z, w; int id;
    EmptyBubble() {}
    EmptyBubble(float a, float b, float c, float d, int e) : x(a), y(b), z(c), w(d), id(e) {}
};

struct BubbleVec {                                  // eastl::vector<EmptyBubble, sp_vector_allocator>
    EmptyBubble* mpBegin; EmptyBubble* mpEnd; EmptyBubble* mpCap;
    void DoInsertValue(EmptyBubble* pos, const EmptyBubble& v);   // 0x00bde910
    __forceinline void push_back(const EmptyBubble& v) {
        if (mpEnd < mpCap) { *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};

// The interface whose vt[0x8c] returns the object's position.
struct BobbleHost {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();  virtual void v4();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();  virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual const Vec3* GetPos();                    // +0x8c
};

struct cCommunity {
    char pad0[0x70];
    BubbleVec mBubbles;                              // +0x70  (begin,end,cap)
    char pad7c[0x2a4 - 0x7c];
    BubbleVec mBubbles2;                             // +0x2a4
    char pad2b0[0x320 - 0x2b0];
    BobbleHost* mHost;                               // +0x320
    char pad324[0x51c - 0x324];
    float m51c, m520, m524;                          // +0x51c,+0x520,+0x524
    void AddSpecialBubbles();                        // 0x00c01310
    void EmitBubbles();                              // 0x00bdfd30
    void EmitBubbleAt(const Vec3* p, float w, int id);  // 0x00bdff50
    void EndThisPlayer();                            // 0x00bdbf10
};

// @ 0x00bdfd30
void cCommunity::EmitBubbles()
{
    AddSpecialBubbles();
    if (!mHost)
        return;
    Vec3 p = *mHost->GetPos();
    mBubbles.push_back(EmptyBubble(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble(p.x, p.y, p.z, 8.0f, 0));
    mBubbles.push_back(EmptyBubble(m51c, m520, m524, 8.0f, 0));
}

// @ 0x00bdff50
void cCommunity::EmitBubbleAt(const Vec3* p, float w, int id)
{
    GameTime* t = GameTimeQuery();                   // 0x00b3d480
    if (t->IsPlayer(this))                           // 0x00ac8d60
    {
        EmptyBubble b;
        b.w = 0.0f;
        b.id = 0;
        mBubbles2.push_back(b);
        EmptyBubble* d = mBubbles2.mpEnd - 1;
        d->x = p->x;
        d->y = p->y;
        d->z = p->z;
        d->w = w;
        d->id = id;
        return;
    }
    if (id == GetPlayerEmpireID())                   // 0x01021090
        EndThisPlayer();                             // 0x00bdbf10
}

// @ 0x00be06c0
void cAnalysisOwner::AddAnalysis(const AnalysisInfo& a, long long delta)
{
    GTClock* g = GameTimeManager();
    long long now = g->Now();
    m7f8.push_back(a);
    *(long long*)((char*)m7f8.mpEnd - 0x18) = now + delta;
}

// --- RefVec2 (vector of 0xc-byte ref-counted elements) ---------------------
struct RefVecElem { void* mpVtbl; int pad; int pad2; };   // 0xc
struct RefVec2 {
    RefVecElem* mpBegin; RefVecElem* mpEnd; RefVecElem* mpCap;
    void insert(RefVecElem* pos, const RefVecElem& v);   // 0x00bdf480
    void AddDefault();                                   // 0x00be0730
};

// @ 0x00be0730
void RefVec2::AddDefault()
{
    RefVecElem v;
    v.mpVtbl = 0;
    v.pad = 0;
    v.pad2 = 0;
    insert(mpEnd, v);
}

// --- std::map<int,...>::GetOrInsert ----------------------------------------
struct MapNode {
    MapNode* mpLeft;      // +0
    MapNode* mpRight;     // +4
    char pad8[8];         // +8
    int mKey;             // +0x10
    char mVal[0x14];      // +0x14
};

struct IntMap {
    char pad0[4];
    MapNode mHead;                                    // +4  (sentinel: left=root)
    int* GetOrInsert(const int* key);                 // 0x00be0790
};

// @ 0x00be0790
int* IntMap::GetOrInsert(const int* key)
{
    MapNode* header = &mHead;                         // +4
    MapNode* node = mHead.mpLeft;                     // +0xc
    MapNode* lb = header;
    while (node) {
        if (node->mKey < *key) {
            node = node->mpLeft;
        } else {
            lb = node;
            node = node->mpRight;
        }
    }
    if (lb != header && *key <= lb->mKey)
        return (int*)((char*)lb + 0x14);
    int inserted = InsertNode(header, lb, *key);      // 0x00de6a60
    return (int*)((char*)inserted + 0x14);
}

// --- cVarListSerializer -----------------------------------------------------
struct cVarListSerializer {
    cVarListSerializer(void* a, const void* b, int c);               // 0x00692f90
    void Read(void* owner);                                          // 0x00693e10
};

// @ 0x00be0b90
void RebuildAnalysisFromStream(IStreamProvider* owner, AnalysisVec* vec)
{
    vec->erase(vec->mpBegin, vec->mpEnd);
    unsigned count = 0;
    EA::IO::IStream* s = (EA::IO::IStream*)owner->GetStream()->V18();
    EA::IO::ReadInt32(s, &count, 1, 0);
    vec->resize(count);
    for (unsigned i = 0; i < count; i++) {
        AnalysisInfo a;
        cVarListSerializer ser(a.w, &g_156e880, 0x1a80d26);
        ser.Read(owner);
        vec->push_back(a);
    }
    owner->Close();
}

// --- find-and-erase over a vector of pointers -------------------------------
struct PtrVec2 {
    int** mpBegin; int** mpEnd; int** mpCap;
};

// @ 0x00be0c80
bool RemoveItem(PtrVec2* vec, int** key)
{
    for (int** it = vec->mpBegin; it != vec->mpEnd; ++it) {
        if (*it == *key) {
            if (it + 1 < vec->mpEnd)
                MoveOverlap(it + 1, vec->mpEnd, it);        // 0x00ae6880
            vec->mpEnd = vec->mpEnd - 1;
            int* e = *vec->mpEnd;
            if (e)
                (*(void (**)(void))(*e + 0x64))();
            return true;
        }
    }
    return false;
}

// --- 0x20-byte record with a vector member ---------------------------------
struct FloatVec {                                    // 0x14 bytes: 3 pointers + allocator state
    float* mpBegin; float* mpEnd; float* mpCap;
    int mAllocState[2];
    void reserve(unsigned n);                         // 0x004aa350
    FloatVec& operator=(const FloatVec& o);           // 0x0050d4e0
};
struct InfoRec {                                     // 0x20 bytes
    Vec3 pos;
    FloatVec v;
    InfoRec(const InfoRec& o);
};

// @ 0x00be0d70
InfoRec::InfoRec(const InfoRec& o) : pos(o.pos)
{
    v.reserve((unsigned)(o.v.mpEnd - o.v.mpBegin));
    memcpy(v.mpBegin, o.v.mpBegin, (char*)o.v.mpEnd - (char*)o.v.mpBegin);
    v.mpEnd = v.mpBegin + (o.v.mpEnd - o.v.mpBegin);
}

// @ 0x00be0dd0
void CopyInfoRecs(InfoRec* first, InfoRec* last, InfoRec* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst) {
            dst->pos = first->pos;
            unsigned n = (unsigned)(first->v.mpEnd - first->v.mpBegin);
            float* p = n ? (float*)operator_new_simulator(n * 4) : 0;   // 0x00f473a0
            dst->v.mpBegin = p;
            dst->v.mpEnd = p;
            dst->v.mpCap = p + n;
            memcpy(p, first->v.mpBegin, (char*)first->v.mpEnd - (char*)first->v.mpBegin);
            dst->v.mpEnd = p + n;
        }
    }
}

// @ 0x00be0e80
InfoRec* CopyInfoRecsFwd(InfoRec* first, InfoRec* last, InfoRec* dst)
{
    for (; first != last; ++first, ++dst)
        *dst = *first;
    return dst;
}

// @ 0x00be0ed0
InfoRec* CopyInfoRecsBwd(InfoRec* first, InfoRec* last, InfoRec* dst)
{
    while (last != first) {
        --last;
        --dst;
        *dst = *last;
    }
    return dst;
}

// --- Simulator::cGameData ---------------------------------------------------
struct Spatial {
    void Clear();                                    // 0x00c8b2e0
};

struct SimData {
    char pad0[0x38];
    char m38[1];                                     // +0x38
    char pad39[0x100 - 0x39];
    Spatial m100;                                    // +0x100
    char pad104[0x1d8 - 0x104];
    int m1d8;                                        // +0x1d8
    int m1dc;                                        // +0x1dc
    int* m1e0;                                       // +0x1e0 vector begin
    int* m1e4;                                       // +0x1e4 vector end
    char pad1e8[0x1f4 - 0x1e8];
    int* m1f4;                                       // +0x1f4 vector begin
    int* m1f8;                                       // +0x1f8 vector end
    int* m1fc;                                       // +0x1fc vector cap
    char pad200[0x208 - 0x200];
    void* m208;                                      // +0x208
    void RemoveOwner();                              // 0x00be0f20
    bool AddOwner(int* p);                            // 0x00be0fc0
};

// @ 0x00be0f20
void SimData::RemoveOwner()
{
    memcpy(m1e0, m1e4, 0);
    m1e4 += (m1e0 - m1e4);
    VectorEraseAutoRef(m1f4, m1f8);                  // 0x00e25bd0
    FUN_00c3f2d0(m208, 0);
    cGameNounManager* nm = NounManager();            // 0x00b3d300
    nm->RemoveNoun(m208);                            // 0x00b225d0
    if (m208) {
        void* old = m208;
        m208 = 0;
        (*(void (**)(void))((*(int*)old) + 4))();
    }
    m100.Clear();
    FUN_00bfc720(m38);                               // tail call
}

// @ 0x00be0fc0
bool SimData::AddOwner(int* p)
{
    bool result = false;
    if (p) {
        int* q = (int*)(*(void** (__thiscall*)(void*, int))(*(int*)p + 0xc))(p, 0x137e8e0);
        if (q) {
            bool found = false;
            int** it = (int**)m1f4;
            int** end = (int**)m1f8;
            while (it != end) {
                if (found)
                    return result;
                found = (*it == q);
                ++it;
            }
            if (!found) {
                (*(void (**)(void))(*q))();
                if ((int*)m1f8 < (int*)m1fc) {
                    int* slot = (int*)m1f8;
                    m1f8 = (int*)((char*)m1f8 + 4);
                    if (slot) {
                        *slot = (int)q;
                        (*(void (**)(void))(*q))();
                    }
                } else {
                    SPVectorDoInsertPtr((void**)&m1f8, q);   // 0x00aea5d0
                }
                if (q)
                    (*(void (**)(void))((*q) + 4))();
                result = true;
            }
        }
    }
    if (m1d8 != 0) {
        if (m1f4 == m1f8) {
            m1d8 = 1;
            m1dc = -1;
            return result;
        }
        m1d8 = 2;
        int e = *m1f4;
        m1dc = (*(int (**)(void))((*(int*)(e + 0x508)) + 0x10))();
    }
    return result;
}
