// Slice s00bdfd30 -- builds the list of candidate links (pairs of live combat objects) for a combat group.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

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
