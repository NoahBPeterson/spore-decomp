// src/game/SPCreatureAnim/creature_mesh_spore.cpp -- migrated from slice(s) s009c7ff0, s009c6fc0, s009c66a0, s009c56c0 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/creature_mesh_spore.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/creature_instance_data.h"
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s009c56c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefCounted {
    void* vptr;         // +0x00
    int   f04;          // +0x04
    char  pad08[0x38];  // +0x08
    int   refCount;     // +0x40
};
struct mesh_instance {
    float        x;      // +0x00
    float        y;      // +0x04
    float        z;      // +0x08
    RefCounted*  object; // +0x0c
    int          index;  // +0x10
};
struct cMWModel;
struct body_shape {
    int   flags;   // +0x00
    float a;       // +0x04
    float b;       // +0x08
    float c;       // +0x0c
};
struct creature_mesh_instance_data {
    char       pad00[0x04];  // +0x00
    void*      poseModel;    // +0x04
    cMWModel*  mesh_lo;      // +0x08
    char       pad0c[0x1c];  // +0x0c
    mesh_instance* bodyBegin; // +0x28
    mesh_instance* bodyEnd;   // +0x2c

    void SetStateInWorld(int, int, void* world);
    void UpdateBodyShapes(int body, int arg2, int arg3);
};
struct shape_model {
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
    virtual void setValue(int body, int id, float v, int arg3);      // +0x74
    virtual void setWeight(int body, int id, float v, int arg3);     // +0x78
    virtual void slot31();                                           // +0x7c
    virtual void setRange(int body, int id, float* lo, float* hi,
                          int arg3);                                 // +0x80
};
// ---- items of slice s009c56c0 end

// ---- items of slice s009c66a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint32;
struct body_mesh_data {
    float        x;         // +0x00
    float        y;         // +0x04
    float        z;         // +0x08
    RefCounted*  model;     // +0x0c
    uint32       modcount;  // +0x10
};
struct bone {
    float m[12];
};
bone* RawCopy30(const void* first, const void* last, void* dst);      // 0x009c5c80
void* RawFill30(void* dst, uint32 n, const void* src);                // 0x009c6830
void  RawMoveOut30(void* out, const void* a2, void* a3, void* a4,
                   const void* a5);                                   // 0x009c64c0
void  RawMoveOut14(void* out, const void* a2, void* a3, void* a4,
                   const void* a5);                                   // 0x009c6500
void  RawFill14(void* dst, uint32 n, const void* src);                // 0x009c6560
void  RawCopy14(const void* first, const void* last, void* dst);      // 0x009c65b0
void* RawDestroy14(const void* first, const void* last, void* dst);   // 0x009c6600
void  MoveDown30(void* dst, const void* src, const void* end);        // 0x00714f70
void  SetRange30(void* first, const void* last, const void* src);     // 0x00714850
void* EAAllocate(uint32 n, const char* tag, int a, int b, const char* file,
                 int line);                                          // 0x00f473a0
void  EADeallocate(void* p);                                         // 0x00f47380
void  BoneDefaultCtor(void* self);                                   // operator_new[] thunk 0x011e073e
static void ReleaseModel(RefCounted* obj)
{
    if (obj == 0)
        return;
    if (obj->refCount > 1) {
        --obj->refCount;
        return;
    }
    bool flag = (unsigned)obj->f04 >> 31;
    void (__stdcall *release)(RefCounted*, unsigned) =
        *(void (__stdcall **)(RefCounted*, unsigned))((char*)obj->vptr + 0x170);
    release(obj, (unsigned)flag);
}
struct BoneVector {
    bone* mpBegin;     // +0x00
    bone* mpEnd;       // +0x04
    bone* mpCapacity;  // +0x08

    bone* erase(bone* first, bone* last);
    void  insert_fill(bone* pos, uint32 n, const bone* src);
    void  resize(uint32 n);
};
struct MeshHandle {
    RefCounted* mObj;      // +0x00
    uint32      mCount;    // +0x04
    BoneVector  mVec;      // +0x08

    void Clear();
};
struct BodyMeshVector {
    body_mesh_data* mpBegin;     // +0x00
    body_mesh_data* mpEnd;       // +0x04
    body_mesh_data* mpCapacity;  // +0x08

    void insert_fill(body_mesh_data* pos, uint32 n, const body_mesh_data* src);
};
struct MeshObj {
    void*           field0;     // +0x00
    unsigned        flags;      // +0x04  (low 14 bits preserved)
    char            xform[0x44];// +0x08  (cSPTransform)
    unsigned        f4c;        // +0x4c
    unsigned        f50;        // +0x50
    unsigned        f54;        // +0x54
    float           f58;        // +0x58
    unsigned char   f5c;        // +0x5c
    char            pad5d[0x64 - 0x5d];
    RefCounted*     f64;        // +0x64
    unsigned short  f68;        // +0x68
    char            pad6a[2];
    float           f6c;        // +0x6c
    unsigned        f70;        // +0x70
    unsigned        f74;        // +0x74
    unsigned        f78;        // +0x78
    unsigned        f7c;        // +0x7c
    unsigned        f80;        // +0x80
    unsigned        f84;        // +0x84
};
void* TransformAssign(void* dst, const void* src);              // 0x00537dc0
// ---- items of slice s009c66a0 end

// ---- items of slice s009c6fc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct Xf {
    Xf();  // 0x409930
    uint32_t pad0[2];
    uint16_t flags;
    uint16_t mod;
    float t[3];
    float scale;
    float rot[9];
};
struct cMWModel_s009c_6fc0 {
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
    virtual int GetNumSubmeshes(cMWModel_s009c_6fc0* m);
    virtual void vpad26();
    virtual void vpad27();
    virtual void SetDeformA(cMWModel_s009c_6fc0* m, uint32_t id, int mode, float v, int sub);
    virtual void SetDeformB(cMWModel_s009c_6fc0* m, uint32_t id, float v, int sub);
    virtual void SetDeformC(cMWModel_s009c_6fc0* m, uint32_t id, float v, int sub);
    virtual void vpad31();
    virtual bool GetDeformRange(cMWModel_s009c_6fc0* m, uint32_t id, float* lo, float* hi, int sub);
    virtual void vpad33();
    virtual void vpad34();
    virtual void vpad35();
    virtual void vpad36();
    virtual void vpad37();
    virtual void SetNumXforms(cMWModel_s009c_6fc0* m, uint32_t n, Bone* xforms);
    virtual void SetCallback(cMWModel_s009c_6fc0* m, void (*cb)(void*), void* user, int a, uint32_t b);
    virtual void SetSubmeshXform(cMWModel_s009c_6fc0* m, int sub, const Xf* xf);
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
    virtual uint32_t GetDeformIds(cMWModel_s009c_6fc0* m, uint32_t* ids, int sub);
};
struct IModelManager {
virtual void mp0();
virtual void mp1();
virtual void mp2();
virtual void mp3();
virtual void mp4();
virtual void mp5();
virtual void mp6();
virtual void mp7();
virtual void mp8();
virtual void mp9();
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
    cMWModel_s009c_6fc0* model;             // +0x0c
    uint32_t modcount;           // +0x10
};
struct BoneVec {
    Bone* mpBegin;
    Bone* mpEnd;
    Bone* mpCapacity;
    uint32_t alloc;
    void resize(uint32_t n);     // 0x9c6c90
};
Mat9* QuatMulMat(Mat9* out, const float* quat, const Mat9* m);          // 0x99c0b0
Mat9* ConvMat(Mat9* out, const Mat9* in);                                // 0x9a46a0
Vec3* QuaternionVectorTrans(Vec3* out, const void* q, const Vec3* v);   // 0x99c1a0
Mat9* MatCopyOut(Mat9* out, const Mat9* in);                             // 0x9c6660
Mat9* Matrix3FromQuaternion(Mat9* out, const float* quat);              // 0x59c190
void EyeLookAtCallback(void*);                                           // 0x9c5e90
namespace nSPCreatureAnim {
struct creature_mesh_instance_data_s009c_6fc0 {
    Creature* creature;          // +0x00
    IModelWorld* world;          // +0x04
    cMWModel_s009c_6fc0* model;             // +0x08
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
    void AttachBodyModel(InstBody* bi, cMWModel_s009c_6fc0* m, int s);  // 0x9c5cb0
    void Update(Bone* out, float r, float g, float b, float a, bool p7, bool p8, bool p9);
};
}
namespace nSPCreatureAnim {
static inline void ApplyDeform(IModelWorld* w, cMWModel_s009c_6fc0* m, uint32_t id, const Deform* d, int sub)
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
}
// ---- items of slice s009c6fc0 end

// ---- items of slice s009c7ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(fabs)
typedef unsigned int  uint;
typedef unsigned long ulong;
#define VPAD(n) virtual void vpad##n()
struct IRefObj {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
VPAD(23);
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
VPAD(28);
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
VPAD(33);
VPAD(34);
VPAD(35);
VPAD(36);
VPAD(37);
VPAD(38);
VPAD(39);
VPAD(40);
VPAD(41);
VPAD(42);
VPAD(43);
VPAD(44);
VPAD(45);
VPAD(46);
VPAD(47);
VPAD(48);
VPAD(49);
VPAD(50);
VPAD(51);
VPAD(52);
VPAD(53);
VPAD(54);
VPAD(55);
VPAD(56);
VPAD(57);
VPAD(58);
VPAD(59);
VPAD(60);
VPAD(61);
VPAD(62);
VPAD(63);
VPAD(64);
VPAD(65);
VPAD(66);
VPAD(67);
VPAD(68);
VPAD(69);
VPAD(70);
VPAD(71);
VPAD(72);
VPAD(73);
VPAD(74);
VPAD(75);
VPAD(76);
VPAD(77);
VPAD(78);
VPAD(79);
VPAD(80);
VPAD(81);
VPAD(82);
VPAD(83);
VPAD(84);
VPAD(85);
VPAD(86);
VPAD(87);
VPAD(88);
VPAD(89);
VPAD(90);
    virtual void Release(int complete);          // +0x170
};
struct RefObject : IRefObj {
    unsigned char pad_004[0x3c];
    int RefCount;                                // +0x40
};
struct cMWModel_s009c_7ff0 : RefObject {
    unsigned char pad_044[0x68 - 0x44];
    unsigned short mModificationCount;           // +0x68
    unsigned char pad_06a[0x90 - 0x6a];
};
struct cIModelWorld {
virtual void v000();
virtual void v004();
virtual void v008();
    virtual void* CreateModelGroup(void* a, void* b, int idx);          // +0x0c (ret 0xc)
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
    virtual bool AssignKeyModel(void* key, void* desc);                 // +0x4c (ret 8)
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
    virtual void AssignModel(void* model, void* group, int idx);        // +0xa4 (ret 0xc)
};
template <class T>
struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned char mAllocatorSlot[8];

    ulong size()  const { return (ulong)(mpEnd - mpBegin); }
    bool  empty() const { return mpBegin == mpEnd; }
    T*    begin()       { return mpBegin; }
    T*    end()         { return mpEnd; }
    T&    operator[](ulong i) { return mpBegin[i]; }

    void SetBodyCount(ulong n);                  // 0x009c8170 (ret 4)
    void erase(T* first, T* last);               // 0x009c6d20
    void resize(T* end, ulong n, const T* v);    // 0x009c6d70
};
struct body_static_data {
    unsigned char pad_000[0x10c];
    float rx;                                    // +0x10c
    float ry;                                    // +0x110
    float rz;                                    // +0x114
    unsigned char pad_118[0x130 - 0x118];
    float c130;                                  // +0x130
    float c134;                                  // +0x134
    float c138;                                  // +0x138
    float c13c;                                  // +0x13c
    float c140;                                  // +0x140
    float rest_center[3];                        // +0x144
    ulong flags_150;                             // +0x150
    unsigned char pad_154[0x1f8 - 0x154];
    ulong f1f8;                                  // +0x1f8
    ulong f1fc;                                  // +0x1fc
    ulong f200;                                  // +0x200
    unsigned char pad_204[0x208 - 0x204];
    ulong f208;                                  // +0x208
    unsigned char pad_20c[0x21c - 0x20c];
    ulong bone_idx;                              // +0x21c
    unsigned char pad_220[0x324 - 0x220];
    float loc[3];                                // +0x324
};
struct creature_static_data {
    unsigned char pad_000[0x37c];
    ulong num_bones_with_mesh_parts;             // +0x37c
    bool  block_default_deforms_hack;            // +0x380
    unsigned char pad_381[3];
    body_static_data* BodiesBegin;               // +0x384
    body_static_data* BodiesEnd;                 // +0x388
};
struct creature_instance_data {
    creature_static_data* sd;                    // +0x00
    unsigned char pad_004[0x18 - 0x04];
    float pos[3];                                // +0x18
    unsigned char pad_024[0x34 - 0x24];
    unsigned char flags_34;                      // +0x34
    unsigned char pad_035[0x3c - 0x35];
    float quat[4];                               // +0x3c
    unsigned char pad_04c[0x70 - 0x4c];
    float scale;                                 // +0x70
    unsigned char pad_074[0x2e4 - 0x74];
    unsigned char* mpAnimsBegin;                 // +0x2e4 (0x2bc-byte records)
    unsigned char* mpAnimsEnd;                   // +0x2e8
};
struct body_mesh_data_s009c_7ff0 {                          // 0x14
    float     local_origin[3];                   // +0x00
    cMWModel_s009c_7ff0* model;                             // +0x0c
    ulong     modcount;                          // +0x10
};
struct ResKey { ulong a, b, c; };
struct creature_mesh_instance_data_s009c_7ff0 {
    struct mesh_data {
        cMWModel_s009c_7ff0*       model;                   // +0x00
        ulong           modcount;                // +0x04
        sp_vector<bone> posed_xforms;            // +0x08 (0x14 -> +0x1c)
        void Clear();                            // 0x009c6c30
        void Assign(cMWModel_s009c_7ff0* m);                // 0x00478db0 (thiscall ret 4)
    };

    creature_instance_data* creature;            // +0x00
    cIModelWorld*           world;               // +0x04
    mesh_data               mesh_lo;             // +0x08
    bool  force_not_in_world;                    // +0x24
    bool  enable_auto_eye_lookat;                // +0x25
    unsigned short pad_26;                       // +0x26
    sp_vector<body_mesh_data_s009c_7ff0> BodyMeshes;        // +0x28

    creature_mesh_instance_data_s009c_7ff0* ctor();         // 0x009c8200
    __declspec(noinline) void Clear();            // 0x009c7ff0
    bool Bind(creature_instance_data* c, cIModelWorld* w, void* unused,
              ResKey* key, bool eye_lookat);     // 0x009c8050 (ret 0x14)
    void SetWorldState();                        // 0x009c8890
    bool Init(creature_instance_data* c, cIModelWorld* w, void* data); // 0x009c8230 (ret 0x10)
    void Dispose();                              // 0x009c8460
    void RefreshWorldState();                    // 0x009c8900

    static void MinClearance(float* minOut, creature_static_data* sd);        // 0x009c8630
    static void MinClearanceIdx(float* minOut, uint* idxOut, creature_static_data* sd); // 0x009c86e0
    static void BodyToWorld(float* out, uint* outIdx, body_static_data* b);     // 0x009c87e0
};
uint  ModelIdToGroup(void* key, cIModelWorld* world, void* out);    // 0x009c66a0
void* ElemInitCopyB(void* first, void* last, void* dst);            // 0x009c6860
void  ElemDestroy(uint* first, uint* last);                         // 0x009c67e0
struct body_mesh_data_s009c_7ff0;
void* InvalidEditorModelKey(ResKey* key, uint flags);               // 0x0068c700
void* EngineGetManager();                                           // 0x00401010
// ---- items of slice s009c7ff0 end

// @ 0x009c5cb0
void creature_mesh_instance_data::UpdateBodyShapes(int body, int arg2, int arg3)
{
    float total = 0.0f;
    int count = *(int*)((char*)body + 0xa0);

    for (int i = 0; i < count; ++i) {
        body_shape* s = (body_shape*)((char*)body + 0xa8 + i * 0x14);
        if ((s->flags & 1) == 0)
            total += s->c;
    }

    for (int i = 0; i < count; ++i) {
        body_shape* s = (body_shape*)((char*)body + 0xa8 + i * 0x14);
        if (s->flags & 1)
            continue;

        int id = *(int*)((char*)s - 4);

        float angle;
        if (s->flags & 2) {
            // atan2 in turns, wrapped into [0,1)
            angle = atan2f(s->b, s->a) * 0.159154937f;
            if (angle < 0.0f)
                angle += 1.0f;
        } else {
            angle = s->a / (s->c + 9.99999994e-09f);
        }

        float weight;
        if (total > 0.0f)
            weight = s->c / total;
        else
            weight = 0.0f;

        shape_model* model = (shape_model*)poseModel;
        float lo, hi;
        model->setRange(arg2, id, &lo, &hi, arg3);
        model = (shape_model*)poseModel;
        model->setValue(arg2, id, lo + (hi - lo) * angle, arg3);
        model = (shape_model*)poseModel;
        model->setWeight(arg2, id, weight, arg3);
    }
}

// @ 0x009c6440
void creature_mesh_instance_data::SetStateInWorld(int, int, void* world)
{
    int n = (int)((char*)bodyEnd - (char*)bodyBegin) / 0x14;
    if (n != 0) {
        int count = n;
        int off = 0;
        do {
            mesh_instance* base = bodyBegin;
            if (*(cMWModel**)((char*)base + off + 0x0c) != 0) {
                cMWModel* model = *(cMWModel**)((char*)base + off + 0x0c);
                void* v = *(void**)model;
                void* t = *(void**)v;
                void (__stdcall *fn)(cMWModel*, void*) =
                    *(void (__stdcall **)(cMWModel*, void*))((char*)t + 0x16c);
                fn(model, world);
            }
            off += 0x14;
            --count;
        } while (count != 0);
    }

    if (mesh_lo != 0) {
        void* v = *(void**)mesh_lo;
        void* t = *(void**)v;
        void (__stdcall *fn)(cMWModel*, void*) =
            *(void (__stdcall **)(cMWModel*, void*))((char*)t + 0x16c);
        fn(mesh_lo, world);
    }
}

// @ 0x009c6500
void UcopyOut(mesh_instance** out, mesh_instance* first, mesh_instance* last, mesh_instance* dest)
{
    *out = dest;
    if (first != last) {
        do {
            if (dest != 0) {
                dest->x = first->x;
                dest->y = first->y;
                dest->z = first->z;
                RefCounted* o = first->object;
                dest->object = o;
                if (o != 0)
                    ++o->refCount;
                dest->index = first->index;
            }
            first = (mesh_instance*)((char*)first + 0x14);
            dest = (mesh_instance*)((char*)dest + 0x14);
        } while (first != last);
        *out = dest;
    }
}

// @ 0x009c6560
void Ufill(mesh_instance* dstBase, unsigned count, const mesh_instance* src)
{
    if (count <= 0u)
        return;

    char* p = (char*)dstBase + 8;
    do {
        mesh_instance* dest = (mesh_instance*)(p - 8);
        if (dest != 0) {
            dest->x = src->x;
            dest->y = src->y;
            dest->z = src->z;
            RefCounted* o = src->object;
            dest->object = o;
            if (o != 0)
                ++o->refCount;
            dest->index = src->index;
        }
        --count;
        p += 0x14;
    } while (count > 0);
}

// @ 0x009c65b0
void UcopyRange(mesh_instance* first, mesh_instance* last, mesh_instance* dest)
{
    if (first == last)
        return;

    do {
        if (dest != 0) {
            dest->x = first->x;
            dest->y = first->y;
            dest->z = first->z;
            RefCounted* o = first->object;
            dest->object = o;
            if (o != 0)
                ++o->refCount;
            dest->index = first->index;
        }
        first = (mesh_instance*)((char*)first + 0x14);
        dest = (mesh_instance*)((char*)dest + 0x14);
    } while (first != last);
}

// @ 0x009c6600
mesh_instance* DestroyRange(mesh_instance* first, mesh_instance* last, mesh_instance* dest)
{
    while (first != last) {
        RefCounted* obj = first->object;
        if (obj != 0) {
            if (obj->refCount > 1) {
                --obj->refCount;
            } else {
                unsigned flag = (unsigned)obj->f04 >> 31;
                void (__stdcall *release)(RefCounted*, unsigned) =
                    *(void (__stdcall **)(RefCounted*, unsigned))
                        ((char*)obj->vptr + 0x170);
                release(obj, flag);
            }
        }
        first = (mesh_instance*)((char*)first + 0x14);
        dest = (mesh_instance*)((char*)dest + 0x14);
    }

    return dest;
}

// @ 0x009c6660
float* Transpose3x3(float* dst, const float* src)
{
    const float* source = *(const float* volatile*)&src;
    float* destination = *(float* volatile*)&dst;
    float (*d)[3] = (float(*)[3])destination;
    const float (*s)[3] = (const float(*)[3])source;
    d[0][0] = s[0][0];
    d[1][0] = s[0][1];
    d[2][0] = s[0][2];
    d[0][1] = s[1][0];
    d[1][1] = s[1][1];
    d[2][1] = s[1][2];
    d[0][2] = s[2][0];
    d[1][2] = s[2][1];
    d[2][2] = s[2][2];
    return destination;
}

// @ 0x009c66a0
MeshObj* CloneMeshInstance(MeshObj* src, void* mgr, unsigned* out)
{
    if (src == 0 || mgr == 0)
        return 0;

    void*  owner = src->field0;
    void** v = *(void***)owner;
    int local_14;
    int local_1c;
    ((void (__thiscall*)(void*, int*, int*))v[0x50 / 4])(owner, &local_14, &local_1c);

    MeshObj* dst = (MeshObj*)((void* (__thiscall*)(void*, int, int, int))
        (*(void***)mgr)[0x0c / 4])(mgr, local_14, local_1c, 2);

    TransformAssign(dst->xform, src->xform);
    dst->flags = (dst->flags & 0xffffc000u) | (src->flags & 0x3fffu);

    dst->f4c = src->f4c;
    dst->f50 = src->f50;
    dst->f54 = src->f54;
    dst->f58 = src->f58;
    dst->f5c = src->f5c;

    RefCounted* n = src->f64;
    RefCounted* o = dst->f64;
    if (n != o) {
        if (n != 0)
            ((void (__thiscall*)(RefCounted*))(*(void***)n)[0])(n);
        dst->f64 = n;
        if (o != 0)
            ((void (__thiscall*)(RefCounted*))(*(void***)o)[1])(o);
    }

    dst->f7c = src->f7c;
    dst->f80 = src->f80;
    dst->f84 = src->f84;
    dst->f70 = src->f70;
    dst->f74 = src->f74;
    dst->f78 = src->f78;
    dst->f6c = src->f6c;

    ((void (__thiscall*)(MeshObj*, int))(*(void***)dst)[0x16c / 4])(dst, 0);

    int got = ((int (__thiscall*)(MeshObj*, int))(*(void***)src->field0)[0xa8 / 4])(src, -1);
    if (got != 0)
        ((void (__thiscall*)(void*, MeshObj*, int, int))
            (*(void***)mgr)[0xa4 / 4])(mgr, dst, got, -1);

    *out = (unsigned)dst->f68 - 1;
    return dst;
}

// @ 0x009c67e0
void ReleaseRange(body_mesh_data* first, body_mesh_data* last)
{
    while (first < last) {
        if (first->model != 0)
            ReleaseModel(first->model);
        first = (body_mesh_data*)((char*)first + 0x14);
    }
}

// @ 0x009c6860
body_mesh_data* CopyRangeOut(body_mesh_data* first, body_mesh_data* last, body_mesh_data* dest)
{
    if (first == last)
        return dest;

    do {
        dest->x = first->x;
        dest->y = first->y;
        dest->z = first->z;

        RefCounted* src = first->model;
        RefCounted* old = dest->model;
        if (old != src) {
            if (src != 0)
                ++src->refCount;
            dest->model = src;
            if (old != 0)
                ReleaseModel(old);
        }
        dest->modcount = first->modcount;

        first = (body_mesh_data*)((char*)first + 0x14);
        dest  = (body_mesh_data*)((char*)dest + 0x14);
    } while (first != last);

    return dest;
}

// @ 0x009c68f0
body_mesh_data* CopyRangeBackward(body_mesh_data* dst, body_mesh_data* first, body_mesh_data* last)
{
    if (last == first)
        return dst;

    do {
        dst  = (body_mesh_data*)((char*)dst - 0x14);
        last = (body_mesh_data*)((char*)last - 0x14);

        dst->x = last->x;
        dst->y = last->y;
        dst->z = last->z;

        RefCounted* src = last->model;
        RefCounted* old = dst->model;
        if (old != src) {
            if (src != 0)
                ++src->refCount;
            dst->model = src;
            if (old != 0)
                ReleaseModel(old);
        }
        dst->modcount = last->modcount;
    } while (last != first);

    return dst;
}

// @ 0x009c6970
void FillRange(body_mesh_data* first, body_mesh_data* last, const body_mesh_data* src)
{
    if (first == last)
        return;

    do {
        first->x = src->x;
        first->y = src->y;
        first->z = src->z;

        RefCounted* o = src->model;
        RefCounted* old = first->model;
        if (old != o) {
            if (o != 0)
                ++o->refCount;
            first->model = o;
            if (old != 0)
                ReleaseModel(old);
        }
        first->modcount = src->modcount;

        first = (body_mesh_data*)((char*)first + 0x14);
    } while (first != last);
}

// @ 0x009c69f0
bone* BoneVector::erase(bone* first, bone* last)
{
    bone* end = mpEnd;
    bone* dst = first;
    bone* src = last;

    if (last != end) {
        do {
            *dst = *src;
            dst = (bone*)((char*)dst + 0x30);
            src = (bone*)((char*)src + 0x30);
        } while (src != end);
    }

    int n = (int)((char*)first - (char*)last) / 0x30;
    mpEnd = (bone*)((char*)mpEnd + n * 0x30);
    return first;
}

// @ 0x009c6a60
void BoneVector::insert_fill(bone* pos, uint32 n, const bone* src)
{
    uint32 cap = (uint32)(((char*)mpCapacity - (char*)mpBegin) / 0x30);
    if (cap < n) {
        uint32 used = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x30);
        uint32 want = used * 2;
        if (used == 0)
            want = 1;
        uint32 newCap = used + n;
        if (newCap < want)
            newCap = want;
        bone* buf = 0;
        if (newCap != 0)
            buf = (bone*)EAAllocate(newCap * 0x30, "EASTL", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                     0xd1);
        bone* mid = RawCopy30(mpBegin, pos, buf);
        RawFill30(mid, n, src);
        bone* newEnd = RawCopy30(pos, mpEnd, (bone*)((char*)mid + n * 0x30));
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            EADeallocate(mpBegin);
        mpBegin = buf;
        mpEnd = newEnd;
        mpCapacity = (bone*)((char*)buf + newCap * 0x30);
        return;
    }

    if (n == 0)
        return;

    bone local[1];
    local[0] = *src;                     // snapshot *src (12 dwords)

    uint32 tail = (uint32)(((char*)mpEnd - (char*)pos) / 0x30);
    if (n < tail) {
        bone* dst = (bone*)((char*)mpEnd - n * 0x30);
        RawMoveOut30(0, dst, mpEnd, mpEnd, 0);
        mpEnd = (bone*)((char*)mpEnd + n * 0x30);
        MoveDown30(pos, dst, mpEnd);
        SetRange30(pos, (bone*)((char*)pos + n * 0x30), local);
        return;
    }

    uint32 extra = n - tail;
    RawFill30(mpEnd, extra, local);
    mpEnd = (bone*)((char*)mpEnd + extra * 0x30);
    RawMoveOut30(0, pos, mpEnd, mpEnd, 0);
    mpEnd = (bone*)((char*)mpEnd + tail * 0x30);
    SetRange30(pos, mpEnd, local);
}

// @ 0x009c6c30
void MeshHandle::Clear()
{
    RefCounted* obj = mObj;
    if (obj != 0) {
        mObj = 0;
        ReleaseModel(obj);
    }
    mCount = 0;
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
}

// @ 0x009c6c90
void BoneVector::resize(uint32 n)
{
    uint32 used = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x30);
    if (used < n) {
        char buf[0x30];
        BoneDefaultCtor(buf);
        insert_fill(mpEnd, n - used, (bone*)buf);
        return;
    }
    erase((bone*)((char*)mpBegin + n * 0x30), mpEnd);
}

// @ 0x009c6d70
void BodyMeshVector::insert_fill(body_mesh_data* pos, uint32 n, const body_mesh_data* src)
{
    uint32 cap = (uint32)(((char*)mpCapacity - (char*)mpBegin) / 0x14);
    if (cap < n) {
        uint32 used = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x14);
        uint32 want = used * 2;
        if (used == 0)
            want = 1;
        uint32 newCap = used + n;
        if (newCap < want)
            newCap = want;
        body_mesh_data* buf = 0;
        if (newCap != 0)
            buf = (body_mesh_data*)EAAllocate(newCap * 0x14, "EASTL", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                     0xd1);
        RawCopy14(mpBegin, pos, buf);
        RawFill14((body_mesh_data*)((char*)buf + n * 0x14), 0, 0);
        RawCopy14(pos, mpEnd, (body_mesh_data*)((char*)buf + n * 0x14));
        RawDestroy14(mpBegin, pos, 0);
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            EADeallocate(mpBegin);
        mpEnd = (body_mesh_data*)((char*)buf + n * 0x14 +
                                  ((char*)mpEnd - (char*)pos));
        mpBegin = buf;
        mpCapacity = (body_mesh_data*)((char*)buf + newCap * 0x14);
        return;
    }

    if (n == 0)
        return;

    body_mesh_data local = *src;
    if (local.model != 0)
        ++local.model->refCount;

    uint32 tail = (uint32)(((char*)mpEnd - (char*)pos) / 0x14);
    if (n < tail) {
        body_mesh_data* dst = (body_mesh_data*)((char*)mpEnd - n * 0x14);
        RawMoveOut14(0, dst, mpEnd, mpEnd, 0);
        mpEnd = (body_mesh_data*)((char*)mpEnd + n * 0x14);
        CopyRangeBackward(mpEnd, dst, mpEnd);
        FillRange(pos, (body_mesh_data*)((char*)pos + n * 0x14), &local);
    } else {
        uint32 extra = n - tail;
        FillRange(mpEnd, (body_mesh_data*)((char*)mpEnd + extra * 0x14), &local);
        mpEnd = (body_mesh_data*)((char*)mpEnd + extra * 0x14);
        RawMoveOut14(0, pos, mpEnd, mpEnd, 0);
        mpEnd = (body_mesh_data*)((char*)mpEnd + tail * 0x14);
        FillRange(pos, mpEnd, &local);
    }

    ReleaseModel(local.model);
}

// @ 0x009c6fc0
namespace nSPCreatureAnim {
void creature_mesh_instance_data_s009c_6fc0::Update(Bone* out, float r, float g, float b, float a, bool p7, bool p8, bool p9)
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
                    cMWModel_s009c_6fc0* bmodel = bm->model;
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
        cMWModel_s009c_6fc0* m = model;
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

// @ 0x009c7ff0
void creature_mesh_instance_data_s009c_7ff0::Clear()
{
    force_not_in_world = false;
    creature = 0;
    mesh_lo.Clear();
    body_mesh_data_s009c_7ff0* b = BodyMeshes.mpBegin;
    body_mesh_data_s009c_7ff0* e = BodyMeshes.mpEnd;
    void* first = ElemInitCopyB(e, e, b);
    ElemDestroy((uint*)first, (uint*)e);
    BodyMeshes.mpEnd += BodyMeshes.mpBegin - BodyMeshes.mpEnd;
}

// @ 0x009c8050
bool creature_mesh_instance_data_s009c_7ff0::Bind(creature_instance_data* c, cIModelWorld* w, void* unused, ResKey* key, bool eye_lookat)
{
    Clear();
    creature = c;
    if (world != w) {
        if (w)
            w->v000();
        cIModelWorld* old = world;
        world = w;
        if (old)
            old->v004();
    }
    ResKey local = *key;
    if ((local.c & 0xff0000) == 0x620000)
        InvalidEditorModelKey(&local, 0);
    cIModelWorld* mgr = (cIModelWorld*)EngineGetManager();
    struct ResDesc { ulong a; unsigned short b, c; } desc;
    desc.b = 0;
    desc.c = 4;
    desc.a = 0x609b763;
    if (!mgr->AssignKeyModel(&local, &desc))
        return false;
    cMWModel_s009c_7ff0* m = (cMWModel_s009c_7ff0*)world->CreateModelGroup((void*)key->a, (void*)key->c, 0);
    mesh_lo.Assign(m);
    if (mesh_lo.model) {
        mesh_lo.modcount = mesh_lo.model->mModificationCount - 1;
        mesh_lo.model->Release(0);
        if ((key->c & 0xff0000) == 0x610000)
            *(uint*)((char*)mesh_lo.model + 4) |= 0x1000;
    }
    enable_auto_eye_lookat = eye_lookat;
    return mesh_lo.model != 0;
}

// @ 0x009c8170
void sp_vector<body_mesh_data_s009c_7ff0>::SetBodyCount(ulong n)
{
    ulong have = size();
    if (n > have) {
        body_mesh_data_s009c_7ff0 tmp;
        tmp.local_origin[0] = 0.0f;
        tmp.local_origin[1] = 0.0f;
        tmp.local_origin[2] = 0.0f;
        tmp.model = 0;
        resize(mpEnd, n - have, &tmp);
        return;
    }
    erase(mpBegin + n, mpEnd);
}

// @ 0x009c8200
creature_mesh_instance_data_s009c_7ff0* creature_mesh_instance_data_s009c_7ff0::ctor()
{
    world = 0;
    mesh_lo.model = 0;
    mesh_lo.posed_xforms.mpBegin = 0;
    mesh_lo.posed_xforms.mpEnd = 0;
    mesh_lo.posed_xforms.mpCapacity = 0;
    BodyMeshes.mpBegin = 0;
    BodyMeshes.mpEnd = 0;
    BodyMeshes.mpCapacity = 0;
    Clear();
    return this;
}

// @ 0x009c8230
bool creature_mesh_instance_data_s009c_7ff0::Init(creature_instance_data* c, cIModelWorld* w, void* data)
{
    Clear();
    creature = c;
    if (world != w) {
        if (w)
            w->v000();
        cIModelWorld* old = world;
        world = w;
        if (old)
            old->v004();
    }
    uint mdl = ModelIdToGroup((void*)data, world, mesh_lo.posed_xforms.mpBegin);
    mesh_lo.Assign((cMWModel_s009c_7ff0*)mdl);
    if (*(char*)((char*)data + 0x34))
        mesh_lo.model->pad_044[0] |= 0x1000;
    else
        mesh_lo.model->pad_044[0] &= 0xffffefff;
    world->AssignModel(mesh_lo.model, *(void**)((char*)data + 8), -1);

    int nparts = (int)(*(unsigned char**)(*(char**)data + 0x9c) -
                       *(unsigned char**)(*(char**)data + 0x98)) / 0x8c;
    int nbodies = (int)(creature->mpAnimsEnd - creature->mpAnimsBegin) / 0x2bc;
    BodyMeshes.SetBodyCount(nparts);
    if (nbodies != 0) {
        int off = 0;
        ulong left = nbodies;
        do {
            body_static_data* sb = (body_static_data*)((char*)creature->sd->BodiesBegin + off);
            uint bi = (uint)sb->bone_idx;
            if (bi < nparts && *(cMWModel_s009c_7ff0**)(*(char**)((char*)data + 0xc) + bi * 4) != 0) {
                body_mesh_data_s009c_7ff0* bmd = (body_mesh_data_s009c_7ff0*)((char*)BodyMeshes.mpBegin + bi * 0x14);
                bmd->local_origin[0] = sb->loc[0] + sb->rest_center[0];
                bmd->local_origin[1] = sb->loc[1] + sb->rest_center[1];
                bmd->local_origin[2] = sb->loc[2] + sb->rest_center[2];
                void* mi = (void*)ModelIdToGroup(
                    *(void**)(*(char**)((char*)data + 0xc) + bi * 4), world,
                    &bmd->model);
                cMWModel_s009c_7ff0* old = (cMWModel_s009c_7ff0*)bmd->model;
                if ((void*)old != mi) {
                    if (mi)
                        ++*(int*)((char*)mi + 0x40);
                    bmd->model = (cMWModel_s009c_7ff0*)mi;
                    if (old) {
                        if (old->RefCount > 1)
                            --old->RefCount;
                        else
                            old->Release((old->pad_004[0] & 0x80) != 0);
                    }
                }
                if (*(char*)((char*)data + 0x34))
                    bmd->model->pad_044[0] |= 0x1000;
                else
                    bmd->model->pad_044[0] &= 0xffffefff;
                if (*(void**)((char*)data + 0x20) != *(void**)((char*)data + 0x24))
                    world->AssignModel(bmd->model,
                                       *(void**)(*(char**)((char*)data + 8) + bi * 4), -1);
            }
            off += 0x468;
            --left;
        } while (left);
    }
    enable_auto_eye_lookat = (bool)*(char*)((char*)data + 0x34);
    return true;
}
