// s009c6fc0: nSPCreatureAnim::creature_mesh_instance_data::Update
// Layouts use the RETAIL offsets read from the disassembly (the 2008 PDB differs).
#include "types.h"

struct Mat9 {
    float m[9];
    Mat9() {}
    // element-wise copy loop (the original copies 3x3 matrices through a 3-iteration loop)
    Mat9(const Mat9& o) {
        for (int i = 0; i < 3; ++i) {
            m[i] = o.m[i];
            m[i + 3] = o.m[i + 3];
            m[i + 6] = o.m[i + 6];
        }
    }
};
struct Vec3 { float x, y, z; };
struct Bone { float m[12]; };  // in: 3x3 at m[0..8] + translation m[9..11]; out: 3x4 (translation column)

// Local transform: same prefix as cMWModel up to and including the rotation.
struct Xf {
    Xf();  // 0x409930
    uint32_t pad0[2];
    uint16_t flags;
    uint16_t mod;
    float t[3];
    float scale;
    float rot[9];
};

struct cMWModel {
    uint32_t vtbl;       // +0x00
    uint32_t flags;      // +0x04
    uint16_t xflags;     // +0x08
    uint16_t xmod;       // +0x0a
    float t[3];          // +0x0c
    float scale;         // +0x18
    float rot[9];        // +0x1c
    uint32_t pad40;      // +0x40
    uint32_t groups[2];  // +0x44
    float color[4];      // +0x4c
    uint32_t pad5c[3];   // +0x5c
    uint16_t stamp;      // +0x68
};

struct IModelWorld {
    virtual void vpad0();
    virtual void vpad1();
    virtual void vpad2();
    virtual void vpad3();
    virtual void vpad4();
    virtual void vpad5();
    virtual void vpad6();
    virtual void vpad7();
    virtual void vpad8();
    virtual void vpad9();
    virtual void vpad10();
    virtual void vpad11();
    virtual void vpad12();
    virtual void vpad13();
    virtual void vpad14();
    virtual void vpad15();
    virtual void vpad16();
    virtual void vpad17();
    virtual void vpad18();
    virtual void vpad19();
    virtual void vpad20();
    virtual void vpad21();
    virtual void vpad22();
    virtual void vpad23();
    virtual void vpad24();
    virtual int GetNumSubmeshes(cMWModel* m);
    virtual void vpad26();
    virtual void vpad27();
    virtual void SetDeformA(cMWModel* m, uint32_t id, int mode, float v, int sub);
    virtual void SetDeformB(cMWModel* m, uint32_t id, float v, int sub);
    virtual void SetDeformC(cMWModel* m, uint32_t id, float v, int sub);
    virtual void vpad31();
    virtual bool GetDeformRange(cMWModel* m, uint32_t id, float* lo, float* hi, int sub);
    virtual void vpad33();
    virtual void vpad34();
    virtual void vpad35();
    virtual void vpad36();
    virtual void vpad37();
    virtual void SetNumXforms(cMWModel* m, uint32_t n, Bone* xforms);
    virtual void SetCallback(cMWModel* m, void (*cb)(void*), void* user, int a, uint32_t b);
    virtual void SetSubmeshXform(cMWModel* m, int sub, const Xf* xf);
    virtual void vpad41();
    virtual void vpad42();
    virtual void vpad43();
    virtual void vpad44();
    virtual void vpad45();
    virtual void vpad46();
    virtual void vpad47();
    virtual void vpad48();
    virtual void vpad49();
    virtual void vpad50();
    virtual void vpad51();
    virtual void vpad52();
    virtual void vpad53();
    virtual void vpad54();
    virtual void vpad55();
    virtual void vpad56();
    virtual void vpad57();
    virtual void vpad58();
    virtual uint32_t GetDeformIds(cMWModel* m, uint32_t* ids, int sub);
};

struct IModelManager {
    virtual void mp0(); virtual void mp1(); virtual void mp2(); virtual void mp3(); virtual void mp4();
    virtual void mp5(); virtual void mp6(); virtual void mp7(); virtual void mp8(); virtual void mp9();
    virtual uint32_t GetGroupBit(uint32_t key, int arg);  // +0x28
};
IModelManager* SP_ModelManager();  // 0x67dd80

struct Deform {  // 0x14
    uint32_t id;
    uint32_t pad4;
    float weight;
    uint32_t padc;
    float extra;
};

struct BodyStatic {  // 0x468
    uint32_t pad0[0x51];
    float org0, org1, org2;      // +0x144
    uint32_t pad1[0x33];
    uint32_t boneIdx;            // +0x21c
    uint32_t pad2[0x41];
    float loc0, loc1, loc2;      // +0x324
    uint32_t pad3[3];
    int sub;                     // +0x33c
    uint32_t pad4[0xe];
    float scale;                 // +0x378
    uint32_t pad5;
    uint32_t ndef;               // +0x380
    Deform defs[11];             // +0x384
    uint32_t pad6[2];
};

struct StaticData {
    uint32_t pad0[0xdf];
    uint32_t numBones;           // +0x37c
    bool hack;                   // +0x380 (block_default_deforms_hack)
    uint8_t pad1[3];
    BodyStatic* bodiesBegin;     // +0x384
    BodyStatic* bodiesEnd;       // +0x388
    uint32_t pad2[0x1b];
    Bone* invXforms;             // +0x3f8
};

struct InstBody {  // 0x2bc
    uint32_t pad0[4];
    float pos[3];                // +0x10
    Mat9 rot;                    // +0x1c
};

struct Creature {
    StaticData* sd;              // +0x00
    uint32_t pad0[5];
    float pos[3];                // +0x18
    uint32_t pad1[6];
    float quat[4];               // +0x3c
    uint32_t pad2[9];
    float scale;                 // +0x70
    uint32_t pad3[0x9c];
    InstBody* bodies;            // +0x2e4
};

struct BodyMesh {  // 0x14
    float org[3];
    cMWModel* model;             // +0x0c
    uint32_t modcount;           // +0x10
};

struct BoneVec {
    Bone* mpBegin;
    Bone* mpEnd;
    Bone* mpCapacity;
    uint32_t alloc;
    void resize(uint32_t n);     // 0x9c6c90
};

// checkerlib / SP helpers (all cdecl)
Mat9* QuatMulMat(Mat9* out, const float* quat, const Mat9* m);          // 0x99c0b0
Mat9* ConvMat(Mat9* out, const Mat9* in);                                // 0x9a46a0
Vec3* QuaternionVectorTrans(Vec3* out, const void* q, const Vec3* v);   // 0x99c1a0
Mat9* MatCopyOut(Mat9* out, const Mat9* in);                             // 0x9c6660
Mat9* Matrix3FromQuaternion(Mat9* out, const float* quat);              // 0x59c190
void EyeLookAtCallback(void*);                                           // 0x9c5e90

namespace nSPCreatureAnim {

struct creature_mesh_instance_data {
    Creature* creature;          // +0x00
    IModelWorld* world;          // +0x04
    cMWModel* model;             // +0x08
    uint32_t modcount;           // +0x0c
    BoneVec posed;               // +0x10
    uint32_t pad20;              // +0x20
    bool force_not_in_world;     // +0x24
    bool enable_auto_eye_lookat; // +0x25
    uint16_t pad26;
    BodyMesh* bmBegin;           // +0x28
    BodyMesh* bmEnd;             // +0x2c
    BodyMesh* bmCap;             // +0x30

    void SetStateInWorld(int a, int b, bool c);              // 0x9c6440
    void AttachBodyModel(InstBody* bi, cMWModel* m, int s);  // 0x9c5cb0
    void Update(Bone* out, float r, float g, float b, float a, bool p7, bool p8, bool p9);
};

static inline void ApplyDeform(IModelWorld* w, cMWModel* m, uint32_t id, const Deform* d, int sub)
{
    float lo = 0.0f;
    float hi = 1.0f;
    if (w->GetDeformRange(m, id, &lo, &hi, sub)) {
        float v = (hi - lo) * d->weight + lo;
        w->SetDeformA(m, id, 3, 0.0f, sub);
        w->SetDeformB(m, id, v, sub);
        w->SetDeformC(m, id, d->extra, sub);
    }
}

// @ 0x9c6fc0
void creature_mesh_instance_data::Update(Bone* out, float r, float g, float b, float a, bool p7, bool p8, bool p9)
{
    bool bNew = true;      // need to (re)create per-body models
    bool bRebuild = true;  // need to rebuild transforms
    if (!p7 && model) {
        bNew = false;
        bRebuild = p8;
    }

    StaticData* sd = creature->sd;
    uint32_t nBodies = (uint32_t)(sd->bodiesEnd - sd->bodiesBegin);
    uint32_t nBones = sd->numBones;

    if (creature && model && ((model->flags >> 14) & 1)) {
        if (modcount != model->stamp) {
            int nSub = world->GetNumSubmeshes(model);
            if (!creature->sd->hack) {
                for (uint32_t i = 0, off = 0; i < nBodies; ++i, off += 0x468) {
                    BodyStatic* bs = creature->sd->bodiesBegin + i;
                    int sub = bs->sub;
                    if (sub > 0 && sub < nSub) {
                        for (uint32_t k = 0; k < bs->ndef; ++k)
                            ApplyDeform(world, model, bs->defs[k].id, &bs->defs[k], sub);
                    }
                }
            } else {
                for (uint32_t i = 0; i < nBodies; ++i) {
                    BodyStatic* bs = creature->sd->bodiesBegin + i;
                    int sub = bs->sub;
                    if (sub > 0 && sub < nSub) {
                        uint32_t ids[31];
                        uint32_t n = world->GetDeformIds(model, ids, sub);
                        uint32_t cnt = bs->ndef;
                        if (cnt >= n)
                            cnt = n;
                        for (uint32_t k = 0; k < cnt; ++k)
                            ApplyDeform(world, model, ids[k], &bs->defs[k], sub);
                    }
                }
            }
            if (bNew && enable_auto_eye_lookat && model && creature)
                world->SetCallback(model, EyeLookAtCallback, creature, -1, 0x36932030);
            modcount = model->stamp;
        }

        if (bRebuild) {
            float invScale = 1.0f / creature->scale;
            int nSub = world->GetNumSubmeshes(model);
            uint32_t boneOff = 0;
            for (uint32_t i = 0; i < nBodies; ++i, boneOff += 0x2bc) {
                InstBody* bi = (InstBody*)((char*)creature->bodies + boneOff);
                BodyStatic* bs = creature->sd->bodiesBegin + i;
                uint32_t idx = bs->boneIdx;
                if (idx >= nBones)
                    continue;

                Vec3 lp;
                lp.x = invScale * bi->pos[0];
                lp.y = bi->pos[1] * invScale;
                lp.z = bi->pos[2] * invScale;
                Mat9 cv;
                ConvMat(&cv, &bi->rot);
                Mat9 cv2 = cv;
                Mat9 cv3 = cv2;
                Bone* dst = &out[idx];
                *(Mat9*)dst->m = cv3;
                dst->m[9] = lp.x;
                dst->m[10] = lp.y;
                dst->m[11] = lp.z;

                BodyMesh* bm = 0;
                if (bNew && bmBegin != bmEnd && idx < (uint32_t)(bmEnd - bmBegin)) {
                    bm = bmBegin + idx;
                    if (!bm->model || !((bm->model->flags >> 14) & 1))
                        bm = 0;
                }
                if (bm) {
                    cMWModel* bmodel = bm->model;
                    if (bm->modcount != bmodel->stamp) {
                        BodyStatic* bs2 = creature->sd->bodiesBegin + i;
                        (void)bs2;
                        for (uint32_t k = 0; k < bs->ndef; ++k)
                            ApplyDeform(world, bm->model, bs->defs[k].id, &bs->defs[k], 0);
                        bm->modcount = bm->model->stamp;
                    }
                    Creature* c = creature;
                    Mat9 qm;
                    Mat9* q = QuatMulMat(&qm, c->quat, &bi->rot);
                    Mat9 r1;
                    ConvMat(&r1, q);
                    float s = c->scale;
                    Vec3 lv;
                    lv.x = bm->org[0] * s;
                    lv.y = bm->org[1] * s;
                    lv.z = bm->org[2] * s;
                    Vec3 t1;
                    Vec3* p1 = QuaternionVectorTrans(&t1, &bi->rot, &lv);
                    Vec3 w;
                    w.x = bi->pos[0] + p1->x;
                    w.y = bi->pos[1] + p1->y;
                    w.z = bi->pos[2] + p1->z;
                    Vec3 t2;
                    Vec3* p2 = QuaternionVectorTrans(&t2, c->quat, &w);
                    Vec3 pos;
                    pos.x = c->pos[0] + p2->x;
                    pos.y = p2->y + c->pos[1];
                    pos.z = p2->z + c->pos[2];
                    Mat9 tmpR;
                    Mat9* rr = MatCopyOut(&tmpR, &r1);
                    *(Mat9*)bmodel->rot = *rr;
                    bmodel->xflags |= 2;
                    bmodel->xmod += 1;
                    bmodel->xflags |= 4;
                    bmodel->t[0] = pos.x;
                    bmodel->t[1] = pos.y;
                    bmodel->t[2] = pos.z;
                    bmodel->xmod += 1;
                    bmodel->xmod += 1;
                    bmodel->scale = bs->scale * creature->scale;
                    bmodel->color[0] = r;
                    bmodel->color[1] = g;
                    bmodel->color[2] = b;
                    bmodel->color[3] = a;
                    if (!p9) bmodel->flags |= 2; else bmodel->flags &= ~2u;
                    if (p9) bmodel->flags |= 4; else bmodel->flags &= ~4u;
                    bool low = 1.0f > a;
                    uint32_t bit = SP_ModelManager()->GetGroupBit(0x420b420, 0);
                    if (bit < 0x40) {
                        uint32_t mask = 1u << (bit & 31);
                        if (low) bmodel->groups[bit >> 5] |= mask;
                        else bmodel->groups[bit >> 5] &= ~mask;
                    }
                    AttachBodyModel(bi, bmodel, 0);
                } else {
                    int sub = bs->sub;
                    if (sub > 0 && sub < nSub) {
                        float v0 = bs->org0 + bs->loc0;
                        float v2 = bs->org2 + bs->loc2;
                        float v1 = bs->org1 + bs->loc1;
                        float zz = ((cv3.m[8] * v2 + cv3.m[7] * v1) + cv3.m[6] * v0) + lp.z;
                        float xx = ((cv3.m[0] * v0 + cv3.m[2] * v2) + cv3.m[1] * v1) + lp.x;
                        float yy = ((cv3.m[5] * v2 + cv3.m[4] * v1) + cv3.m[3] * v0) + lp.y;
                        Xf xf;
                        Mat9 tmpR;
                        Mat9* rr = MatCopyOut(&tmpR, &cv3);
                        xf.scale = bs->scale;
                        *(Mat9*)xf.rot = *rr;
                        xf.t[0] = xx;
                        xf.t[1] = yy;
                        xf.t[2] = zz;
                        xf.flags |= 6;
                        xf.mod += 3;
                        world->SetSubmeshXform(model, sub, &xf);
                        if (bNew)
                            AttachBodyModel(bi, model, sub);
                    }
                }
            }
        }

    SetStateInWorld(0, 0, !force_not_in_world);

    {
        cMWModel* m = model;
        Mat9 qr;
        Mat9* rot = Matrix3FromQuaternion(&qr, creature->quat);
        *(Mat9*)m->rot = *rot;
        m->xflags |= 2;
        m->xmod += 1;
        m->t[0] = creature->pos[0];
        m->t[1] = creature->pos[1];
        m->xflags |= 4;
        m->xmod += 1;
        m->t[2] = creature->pos[2];
        m->xmod += 1;
        m->scale = creature->scale;
        m->color[0] = r;
        m->color[1] = g;
        m->color[2] = b;
        m->color[3] = a;
        if (!p9) m->flags |= 2; else m->flags &= ~2u;
        if (!p9) m->flags &= ~4u; else m->flags |= 4;
        bool low = 1.0f > a;
        uint32_t bit = SP_ModelManager()->GetGroupBit(0x420b420, 0);
        if (bit < 0x40) {
            uint32_t mask = 1u << (bit & 31);
            if (low) m->groups[bit >> 5] |= mask;
            else m->groups[bit >> 5] &= ~mask;
        }
    }

    if (bRebuild) {
        posed.resize(nBones);
        Bone* posedBegin = posed.mpBegin;
        Bone* inv = creature->sd->invXforms;
        for (uint32_t k = 0; k < nBones; ++k) {
            const float* A = out[k].m;
            const float* B = inv[k].m;
            float r00 = A[2] * B[6] + A[0] * B[0] + A[1] * B[3];
            float r01 = A[2] * B[7] + A[0] * B[1] + A[1] * B[4];
            float r02 = A[2] * B[8] + A[0] * B[2] + A[1] * B[5];
            float r10 = A[3] * B[0] + A[4] * B[3] + A[5] * B[6];
            float r11 = A[3] * B[1] + A[4] * B[4] + A[5] * B[7];
            float r12 = A[3] * B[2] + A[4] * B[5] + A[5] * B[8];
            float r20 = A[6] * B[0] + A[7] * B[3] + A[8] * B[6];
            float r21 = A[6] * B[1] + A[7] * B[4] + A[8] * B[7];
            float r22 = A[6] * B[2] + A[7] * B[5] + A[8] * B[8];
            float tx = ((A[2] * B[11] + A[0] * B[9]) + A[1] * B[10]) + A[9];
            float ty = A[10] + ((A[3] * B[9] + A[5] * B[11]) + A[4] * B[10]);
            float tz = ((A[6] * B[9] + A[8] * B[11]) + A[7] * B[10]) + A[11];
            Bone* o = &posed.mpBegin[k];
            o->m[0] = r00;
            o->m[1] = r01;
            o->m[2] = r02;
            o->m[3] = tx;
            o->m[4] = r10;
            o->m[5] = r11;
            o->m[6] = r12;
            o->m[7] = ty;
            o->m[8] = r20;
            o->m[9] = r21;
            o->m[10] = r22;
            o->m[11] = tz;
        }
        world->SetNumXforms(model, (uint32_t)(posed.mpEnd - posed.mpBegin), posedBegin);
    } else {
        world->SetNumXforms(model, nBones, 0);
    }
    }
}

}  // namespace nSPCreatureAnim
