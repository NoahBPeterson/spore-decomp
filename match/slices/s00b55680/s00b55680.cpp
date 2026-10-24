// Slice s00b55680 -- FUN_00b55680 (2436 bytes), module flags /O2 /MD /Gy /EHsc /TP /arch=SSE /fp:fast.
//
// Cell update, dispatched on the byte at self+0xa7:
//   * self+0xa7 == 0 : the physics-proxy branch.  The cell's Havok locomotion controller is looked
//     up in the eastl hashtable at 0x0167ed58; when present it is given the placed speed and handed
//     to FUN_00b4dd70.  Otherwise the cell is placed on the planet surface (FUN_00b523e0 ->
//     cPlanetModel::BuildSurfaceOrientation -> ProjectToSurface), a hkSimpleShapePhantom is built
//     from the box half-extents and added to the Havok world, and the corrected contact position is
//     written back with hkRigidBody::setPosition.
//   * self+0xa7 != 0 : the locomotion branch.  The state bits at self+0xa8/self+0xac/self+0xae drive
//     FUN_00b3e620 / FUN_00b54230 / FUN_00b52690 and the surface-orientation rebuild.
//
// NONMATCHING reconstruction: the control flow, the callee set and the field semantics are complete,
// but the original's stack-block layout (one 4x4 hkTransform reused as the phantom's out-parameter
// block, with the blend weight and the hit flag overlaid on it) and its x87 arithmetic are
// approximated, so a large instruction diff remains.
#include "types.h"
#include <math.h>
#include <new>

// ---------------------------------------------------------------- shared types
struct Vec3 { float x, y, z; };                     // 12-byte direction vector

struct hkVector4 {                                  // Havok 4-vector (also used for positions)
    float x;                                        // +0x00
    float y;                                        // +0x04
    float z;                                        // +0x08
    float w;                                        // +0x0c
};

struct hkQuaternion {                               // Havok quaternion
    float x;                                        // +0x00
    float y;                                        // +0x04
    float z;                                        // +0x08
    float w;                                        // +0x0c
};

struct hkTransform {                                // Havok transform; only its address is used here
    float mValue[12];                               // +0x00
};

struct hkShape {                                    // 0x016e42d0 is one of these shape tags
    virtual void v0();                              // slot 0
    virtual void v1();                              // slot 1
    virtual void v2();                              // slot 2
    virtual void slot3(void* xform, int flag, void* out);    // slot 3 (+0x0c)  orientation query
};

struct hkRotation {                                 // a Havok rotation matrix (three 4-float rows)
    float mRow0[4];                                 // +0x00
    float mRow1[4];                                 // +0x10
    float mRow2[4];                                 // +0x20
    void set(const hkQuaternion& q);                // 0x010824a0  ?set@hkRotation@@QAEXABVhkQuaternion@@@Z
};

struct hkPhantom {                                  // Havok phantom (forward-declared, used by hkWorld)
    char mDummy;
};

struct hkWorld {
    hkPhantom* addPhantom(hkPhantom* p);            // 0x01083320  ?addPhantom@hkWorld@@QAEPAVhkPhantom@@PAV2@@Z
    void removePhantom(hkPhantom* p);               // 0x01083400  ?removePhantom@hkWorld@@QAEXPAVhkPhantom@@@Z
};

struct hkMemory {                                   // the Havok allocator singleton (0x016e4178)
    virtual void* v0();                             // slot 0
    virtual void* v1();                             // slot 1
    virtual void* v2();                             // slot 2
    virtual void* v3();                             // slot 3
    virtual void* allocate(int size, int alignment); // slot 4 (+0x10)
};

struct hkWorldObject {                              // the phantom's Havok base
    void removeReference();                         // 0x0109ae60  ?removeReference@hkWorldObject@@QAEXXZ
};

struct hkSimpleShapePhantom : hkWorldObject {       // 0x130-byte Havok shape phantom
    hkSimpleShapePhantom(const hkShape* shape, const hkTransform& xform, unsigned int flags);
                                                    // 0x0108c750  ??0hkSimpleShapePhantom@@QAE@PBVhkShape@@ABVhkTransform@@I@Z
    virtual void v0();                              // slot 0
    virtual void v1();                              // slot 1
    virtual void v2();                              // slot 2
    virtual void v3();                              // slot 3
    virtual void v4();                              // slot 4
    virtual void v5();                              // slot 5
    virtual void v6();                              // slot 6
    virtual void v7();                              // slot 7
    virtual void v8();                              // slot 8
    virtual void v9();                              // slot 9
    virtual void v10();                             // slot 10
    virtual void v11();                             // slot 11
    virtual void slot12(void* a, void* b, void* c, int d);   // slot 12 (+0x30)  contact query
    unsigned short mSize;                           // +0x004  set to 0x130
    unsigned short mPad006;                         // +0x006
    hkWorld*       mpWorld;                         // +0x008  the owning world the ctor caches
};

struct hkEntity {
    void activate();                                // 0x01088ae0  ?activate@hkEntity@@QAEXXZ
};

struct Body;                                        // the entity's orientation/shape object

struct hkRigidBody : hkEntity {                     // the physics proxy on the other side
    char        mPad004[0x18];                      // +0x004
    hkShape*    mpShape;                            // +0x01c  the shape handed to the phantom ctor
    char        mPad020[0x38];                      // +0x020
    Body*       mpBody;                             // +0x058
    void setPosition(const hkVector4& v);           // 0x01087820  ?setPosition@hkRigidBody@@QAEXABVhkVector4@@@Z
};

struct Body {                                       // *(other + 0x58)
    char        mPad004[0x0c];                      // +0x004
    hkTransform mXform10;                           // +0x010  transform handed to the phantom ctor
    hkVector4   mPos40;                             // +0x040  handed to BuildSurfaceOrientation
    char        mPad050[0x30];                      // +0x050
    float       mHalfX;                             // +0x080  box half extents
    float       mHalfY;                             // +0x084
    float       mHalfZ;                             // +0x088
    float       mHalfW;                             // +0x08c
    virtual void v0();                              // slot 0
    virtual void v1();                              // slot 1
    virtual void v2();                              // slot 2
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21();                             // slot 21
    virtual void slot22(void* tag);                 // slot 22 (+0x58)
    virtual void slot23(void* tag);                 // slot 23 (+0x5c)
};

namespace SP {

struct cHavokLocomotiveController {                 // the physics object stored in the hashtable
    void FUN_00aef6b0(int mode, float speed);       // 0x00aef6b0  ?FUN_00aef6b0@cHavokLocomotiveController@SP@@QAEXHM@Z
};

struct cPlanetModel {                               // the planet the cell sits on
    float* FUN_00b7f190(void* outQuat, const void* position);
                                                    // 0x00b7f190  SP::cPlanetModel::BuildSurfaceOrientation
    float* FUN_00b7f1f0(void* out16, void* direction);
                                                    // 0x00b7f1f0  SP::cPlanetModel::BuildSurfaceOrientation_2
    float* FUN_00b82df0(void* out, const void* position, int a, int b, int c, int d);
                                                    // 0x00b82df0  SP::cPlanetModel::ProjectToSurface
};

cPlanetModel* FUN_00b3d350();                       // 0x00b3d350  SP::PlanetModel

} // namespace SP

// ---------------------------------------------------------------- the cell actor behind self
struct Actor {
    char          mPad004[0x4c];                    // +0x004
    unsigned      mFlags50;                         // +0x050  self[0x14]
    char          mPad054[0x1d];                    // +0x054
    unsigned char mField71;                         // +0x071
    char          mPad072[0x35];                    // +0x072
    unsigned char mFieldA7;                         // +0x0a7  dispatch gate
    unsigned      mFieldA8;                         // +0x0a8  self[0x2a] state bits
    unsigned      mFieldAC;                         // +0x0ac  self[0x2b] placement state
    void*         mOrganism;                        // +0x0b0  self[0x2c]
    float         mFieldB4;                         // +0x0b4  self[0x2d] orientation distance
    unsigned      mFieldB8;                         // +0x0b8  self[0x2e] mode bits
    // virtual table slots (only the used ones are named)
    virtual void  v00(); virtual void  v01(); virtual void  v02(); virtual void  v03();
    virtual void  v04(); virtual void  v05(); virtual void  v06(); virtual void  v07();
    virtual void  v08(); virtual void  v09(); virtual void  v10();
    virtual void* FUN_2c(int arg = 0);              // slot 11 (+0x2c)  the encounter direction
    virtual void* FUN_30();                         // slot 12 (+0x30)
    virtual void  v13();                            // slot 13
    virtual void  FUN_38(hkVector4* v);             // slot 14 (+0x38)  set the orientation target
    virtual void  FUN_3c(hkVector4* v);             // slot 15 (+0x3c)
    virtual void  v16(); virtual void  v17(); virtual void  v18(); virtual void  v19();
    virtual void  v20(); virtual void  v21(); virtual void  v22(); virtual void  v23();
    virtual void  v24(); virtual void  v25();
    virtual float* FUN_68();                        // slot 26 (+0x68)  the bounds
    virtual void  v27();                            // slot 27
    virtual void  FUN_70();                         // slot 28 (+0x70)
    virtual void  v29(); virtual void  v30(); virtual void  v31(); virtual void  v32();
    virtual void  v33(); virtual void  v34(); virtual void  v35(); virtual void  v36();
    virtual void  v37(); virtual void  v38(); virtual void  v39(); virtual void  v40();
    virtual void  v41(); virtual void  v42(); virtual void  v43(); virtual void  v44();
    virtual void  v45();
    virtual int   FUN_b8(int id);                   // slot 46 (+0xb8)
};

// ---------------------------------------------------------------- the eastl cell -> physics map
struct HashIterator {                               // eastl::hashtable_iterator (value = the proxy)
    void* mpNode;                                   // +0x00
    SP::cHavokLocomotiveController* mpObject;       // +0x04
};

struct CellPhysicsTable {                           // 0x0167ed58
    void FUN_00645ed0(HashIterator* out, const unsigned int* key);
                                                    // 0x00645ed0  eastl::hashtable<unsigned int, ...>::find
};

// ---------------------------------------------------------------- globals
extern CellPhysicsTable g_167ed58;                  // 0x0167ed58  the cell -> physics hashtable
extern void**           g_167ed5c;                  // 0x0167ed5c  its bucket array
extern int              g_167ed60;                  // 0x0167ed60  its end bucket index
extern float            g_13eecd8;                  // 0x013eecd8  the placed locomotion speed
extern float            g_1569b04;                  // 0x01569b04  the surface offset
extern float            g_1461294;                  // 0x01461294  the phantom reference value
extern char             g_1569ab8;                  // 0x01569ab8  proxy-enabled gate
extern char             g_16e42d0;                  // 0x016e42d0  the shape tag handed to the body's slots
extern char             g_13ef52c;                  // 0x013ef52c  the static the phantom records by address
extern hkMemory*        g_16e4178;                  // 0x016e4178  hkMemory::s_instance
extern hkWorld*         g_167ecd0;                  // 0x0167ecd0  hkWorld::s_instance

// ---------------------------------------------------------------- internal callees
void __cdecl FUN_00b4dd70(void* self, void* proxy);                         // 0x00b4dd70
void* __cdecl FUN_00b53940(void* self);                                     // 0x00b53940
void __cdecl FUN_00b3e620(void* self, int mode, int a3, int a4, int a5, int a6);
                                                                            // 0x00b3e620
int __cdecl FUN_00b54230(void* self, void* other);                          // 0x00b54230
void __cdecl FUN_00b54000(void* self, void* phantom);                       // 0x00b54000
void __cdecl FUN_00b523e0(void* self, void* other);                         // 0x00b523e0
int __cdecl FUN_00b532b0(void* self);                                       // 0x00b532b0
void __cdecl FUN_00b52690(void* self, void* other, int flag, void* organism,
                          int a4, int a5, int a6);                          // 0x00b52690  PlaceObjectOnSurface
void __cdecl FUN_00b537f0(void* a, int b, int c, int d);                   // 0x00b537f0
unsigned __cdecl FUN_00b52230(void* self, void* other);                     // 0x00b52230
int __cdecl FUN_00b33e40(void* self);                                       // 0x00b33e40

// the phantom's reference argument (its first two fields are the original's; the two trailing
// fields are where this reconstruction keeps the outputs the phantom writes back)
struct PhantomRef {
    void*    mpName;                                // +0x00
    float    mValue;                                // +0x04
    unsigned mHit;                                  // +0x08  out: nonzero => a contact was found
    float    mWeight;                               // +0x0c  out: the blend weight in [0,1]
};

union FloatBits {                                   // the sentinel the contact block is seeded with
    unsigned u;
    float    f;
};

// @ 0x00b55680
void __cdecl FUN_00b55680(Actor* self, hkRigidBody* otherArg, char param_3)
{
    if (self->mFieldA7 == 0) {
        /* -------------------------------------------------- the physics-proxy branch */
        const unsigned int key = (unsigned int)self;
        HashIterator it;
        g_167ed58.FUN_00645ed0(&it, &key);
        if (it.mpNode != g_167ed5c[g_167ed60] && it.mpObject != 0) {
            it.mpObject->FUN_00aef6b0(0, g_13eecd8);
            FUN_00b4dd70(self, it.mpObject);
            return;
        }

        hkRigidBody* other = otherArg;
        if (other == 0 && (other = (hkRigidBody*)FUN_00b53940(self)) == 0) {
            FUN_00b3e620(self, 1, 0, 0, 0, 0);
            return;
        }
        if ((self->mFlags50 & 0x2000) != 0) {
            FUN_00b3e620(self, 1, 0, 0, 0, 0);
            FUN_00b54230(self, other);
            FUN_00b54000(self, 0);
            return;
        }
        if (self->mField71 != 0 && (self->mFlags50 & 0x4000) == 0) {
            FUN_00b3e620(self, 1, 0, 0, 0, 0);
            FUN_00b54230(self, other);
            return;
        }

        SP::cPlanetModel* planet = SP::FUN_00b3d350();
        void* encountered = self->FUN_30();
        void* direction   = self->FUN_2c((int)encountered);
        char  scratch16[16];
        const float* encounterPos = (const float*)planet->FUN_00b7f1f0(scratch16, direction);

        hkVector4 encounter;
        encounter.x = encounterPos[0];
        encounter.y = encounterPos[1];
        encounter.z = encounterPos[2];
        encounter.w = encounterPos[3];
        self->FUN_3c(&encounter);
        FUN_00b523e0(self, other);

        hkVector4 surfaceQuat;
        const float* pfVar4 = planet->FUN_00b7f190(&surfaceQuat, &other->mpBody->mPos40);

        // rotate the box half-extents by the surface quaternion (the original's quaternion product)
        const float qw = pfVar4[3];
        const float qz = pfVar4[2];
        const float qy = pfVar4[1];
        const float qx = pfVar4[0];
        const Body* body = other->mpBody;
        const float bw = body->mHalfW;
        hkQuaternion boxRot;
        boxRot.x = (body->mHalfX * qw + (body->mHalfY * qz - body->mHalfZ * qy)) - bw * qx;
        boxRot.y = (body->mHalfY * qw + (body->mHalfZ * qx - body->mHalfX * qz)) - bw * qy;
        boxRot.z = (body->mHalfZ * qw + (body->mHalfX * qy - body->mHalfY * qx)) - bw * qz;
        boxRot.w = ((bw * qw + body->mHalfY * qy) + body->mHalfZ * qz) + body->mHalfX * qx;

        // the transform the phantom is handed: identity rotation, then set from the quaternion
        hkRotation xform;
        xform.mRow0[0] = 1.0f; xform.mRow0[1] = 0.0f; xform.mRow0[2] = 0.0f; xform.mRow0[3] = 0.0f;
        xform.mRow1[0] = 0.0f; xform.mRow1[1] = 1.0f; xform.mRow1[2] = 0.0f; xform.mRow1[3] = 0.0f;
        xform.mRow2[0] = 0.0f; xform.mRow2[1] = 0.0f; xform.mRow2[2] = 1.0f; xform.mRow2[3] = 0.0f;
        xform.set(boxRot);

        char scratch12[48];                         // the scratch matrix the query writes back
        other->mpShape->slot3(&xform, 0, scratch12);

        const float* bounds = self->FUN_68();
        const float cx = (bounds[3] + bounds[0]) * 0.5f;
        const float cy = (bounds[4] + bounds[1]) * 0.5f;
        const float cz = (bounds[5] + bounds[2]) * 0.5f;
        const float e0 = ((cx * boxRot.x + cy * boxRot.y) + cz * boxRot.z) * boxRot.z;
        const float e1 = boxRot.x * boxRot.x;
        const float e2 = (cy * boxRot.x - cx * boxRot.y) * boxRot.x;

        hkVector4 contact;                          // the scratch the phantom fills in
        planet->FUN_00b82df0(&contact, &other->mpBody->mPos40, 1, 0, 0, 0);
        const float len = (float)sqrt((double)((contact.x * contact.x) +
                                                ((contact.z * contact.z) + (contact.y * contact.y))));
        self->FUN_70();
        const float invLen = 1.0f / len;
        const float nx = invLen * contact.x;
        const float dist = len - (g_1569b04 + ((e0 + (e1 + -0.5f) * e2) + e2) * 2.0f);
        contact.x = dist * nx;
        const float ny = contact.y * invLen;
        contact.y = ny * dist;
        const float pushed = len - g_1569b04;
        const float nz = contact.z * invLen;
        contact.z = nz * dist;
        contact.w = (invLen * 0.0f) * dist;

        // build the phantom and add it to the world
        hkSimpleShapePhantom* ph = (hkSimpleShapePhantom*)g_16e4178->allocate(0x130, 0x2e);
        ph->mSize = 0x130;
        new (ph) hkSimpleShapePhantom(other->mpShape, other->mpBody->mXform10, 0xc);
        g_167ecd0->addPhantom((hkPhantom*)ph);
        ph->removeReference();

        // the correction target: the box-rotation product, with the ground offset in its z/w slots
        hkVector4 target;
        target.x = boxRot.x;
        target.y = boxRot.y;
        target.z = boxRot.z;
        target.w = boxRot.w;
        target.z = g_1569b04;
        target.w = g_1569b04;

        PhantomRef ref;
        FloatBits sentinel;
        sentinel.u = 0x7f7fffee;
        ref.mpName    = &g_13ef52c;
        ref.mValue    = g_1461294;
        ref.mHit      = 0;
        ref.mWeight   = g_1461294;
        contact.z     = 0.0f;                       // the seeded "no contact yet" sentinel slots
        contact.w     = sentinel.f;

        ph->slot12(&contact, &target, &ref, 0);
        if (ref.mHit != 0) {
            const float w = 1.0f - ref.mWeight;
            hkVector4 corrected;
            corrected.x = ref.mWeight * target.x + w * contact.x;
            corrected.y = ref.mWeight * target.y + w * contact.y;
            corrected.z = ref.mWeight * target.z + w * contact.z;
            corrected.w = ref.mWeight * target.w + w * contact.w;
            other->setPosition(corrected);
            FUN_00b52230(self, other);
            other->activate();
            other->mpBody->slot23(&g_16e42d0);
            other->activate();
            other->mpBody->slot22(&g_16e42d0);
        }
        g_167ecd0->removePhantom((hkPhantom*)ph);
        (void)pushed;
        return;
    }

    /* ------------------------------------------------------ the locomotion branch */
    if (((self->mFieldA8 >> 1) & 1) == 0) {
        return;
    }

    void* organism = self->mOrganism;
    int flag = 0;
    if (((self->mFieldA8 >> 4) & 1) != 0 || param_3 != 0) {
        flag = 1;
    }
    const int bit4 = (int)((self->mFieldB8 >> 4) & 1);
    const int bit1 = (int)((self->mFieldB8 >> 1) & 1);
    const int bit2 = (int)((~(self->mFieldB8 >> 2)) & 1);

    hkRigidBody* other = otherArg;
    const int iVar2 = FUN_00b532b0(self);

    if (iVar2 == 0) {
        if (other == 0 && (other = (hkRigidBody*)FUN_00b53940(self)) == 0) {
            FUN_00b3e620(self, (int)organism, bit4, bit1, bit2, flag);
        } else if (self->mFieldAC == 0) {
            FUN_00b3e620(self, (int)organism, bit4, bit1, bit2, flag);
            FUN_00b54230(self, other);
        } else if (self->mFieldAC == 1) {
            const bool bVar9 = flag != 0;
            FUN_00b52690(self, other, flag, organism, bit4, bit1, bit2);
            if (bVar9) {
                goto LAB_00b558c8;
            }
        }
    } else {
        FUN_00b3e620(self, (int)organism, bit4, bit1, bit2, flag);
        const int id = self->FUN_b8(0x116dd1b);
        FUN_00b537f0((void*)id, iVar2, 1, 1);
    }

    if (self->mFieldB4 != 0.0f) {
        const float* pfDir = (const float*)self->FUN_2c();
        const float dx = pfDir[0];
        const float dy = pfDir[1];
        const float dz = pfDir[2];
        const int steps = (int)(self->mFieldB4 /
                                (float)sqrt((double)(dx * dx + (dz * dz + dy * dy))) + 1.0f);
        hkVector4 target;
        target.x = dx * (float)steps;
        target.y = dy * (float)steps;
        target.z = dz * (float)steps;
        target.w = 0.0f;
        self->FUN_38(&target);
        if (iVar2 == 0) {
            FUN_00b54230(self, other);
        } else {
            const int id2 = FUN_00b33e40(self);
            FUN_00b537f0((void*)id2, iVar2, 1, 1);
        }
    }

LAB_00b558c8:
    if (g_1569ab8 != 0 && (self->mFlags50 & 0x2000) != 0) {
        FUN_00b54000(self, 0);
        return;
    }
}