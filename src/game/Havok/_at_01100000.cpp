// src/game/Havok/_at_01100000.cpp -- migrated from slice(s) s0110fe20, s0110fa20, s0110dd70, s0110b3a0, s0110ad70, s0110a0d0, s011090b0, s01108460, s01107270, s01106490, s01102fc0, s01102010, s01101c00, s01100cf0 by tools/migrate/rewrite.py
// Object file: Havok/_at_01100000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <emmintrin.h>
#include <stddef.h>
#include <float.h>

// unnamed retail callees and globals (address in the comment)
extern void* g_hkPredGskAgent3_createFunc;            // 0x010FF820
extern void* g_hkPredGskAgent3_destroyFunc;           // 0x010FF800
extern void* g_hkPredGskAgent3_cleanupFunc;           // 0x010FF880
extern void* g_hkPredGskAgent3_removePointFunc;       // 0x010FF760
extern void* g_hkPredGskAgent3_commitPotentialFunc;   // 0x010FF7A0
extern void* g_hkPredGskAgent3_createZombieFunc;      // 0x010FF7D0
extern void* g_hkPredGskAgent3_sepNormalFunc;         // 0x010FF8C0
extern void* g_hkPredGskAgent3_processFunc;           // 0x010FF9E0

// ---- items of slice s01100cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_hkPredGskAgent3_createFunc;            // 0x010FF820
extern void* g_hkPredGskAgent3_destroyFunc;           // 0x010FF800
extern void* g_hkPredGskAgent3_cleanupFunc;           // 0x010FF880
extern void* g_hkPredGskAgent3_removePointFunc;       // 0x010FF760
extern void* g_hkPredGskAgent3_commitPotentialFunc;   // 0x010FF7A0
extern void* g_hkPredGskAgent3_createZombieFunc;      // 0x010FF7D0
extern void* g_hkPredGskAgent3_sepNormalFunc;         // 0x010FF8C0
extern void* g_hkPredGskAgent3_processFunc;           // 0x010FF9E0
struct Agent3Funcs {
    void* m_createFunc;                               // +0x00  0x010FF820
    void* m_destroyFunc;                              // +0x04  0x010FF800
    void* m_cleanupFunc;                              // +0x08  0x010FF880
    void* m_removePointFunc;                          // +0x0c  0x010FF760
    void* m_commitPotentialFunc;                      // +0x10  0x010FF7A0
    void* m_createZombieFunc;                         // +0x14  0x010FF7D0
    void* m_updateFilterFunc;                         // +0x18  null
    void* m_invalidateTimFunc;                        // +0x1c  null
    void* m_warpTimeFunc;                             // +0x20  null
    void* m_sepNormalFunc;                            // +0x24  0x010FF8C0
    void* m_processFunc;                              // +0x28  0x010FF9E0
    char  m_isPredictive;                             // +0x2c  1
    char  m_ignoreSymmetricVersion;                   // +0x2d  0
};
class hkCollisionDispatcher_s0110_0cf0 {
public:
    // 0x010CD4C0: thiscall, &funcs / typeA / typeB on the stack, ret 0xc
    int registerAgent3(Agent3Funcs& funcs, int typeA, int typeB);
};
struct hkMoppCode {
    char  pad00[0x10];
    float m_offsetX;                    // +0x10
    float m_offsetY;                    // +0x14
    float m_offsetZ;                    // +0x18
    float m_scale;                      // +0x1c
    const unsigned char* m_data;        // +0x20
};
struct hkSphere {
    float x;                            // +0x00
    float y;                            // +0x04
    float z;                            // +0x08
    float radius;                       // +0x0c
};
struct hkMoppSphereState {
    int m_minHi0;                       // +0x00  high half of m_lo[0]
    int m_minHi1;                       // +0x04  high half of m_lo[1]
    int m_minHi2;                       // +0x08  high half of m_lo[2]
    int m_spanHi;                       // +0x0c  high half of the cell span, +1
    int m_scratch0;                     // +0x10
    int m_scratch1;                     // +0x14
    int m_scratch2;                     // +0x18
    int m_scratch3;                     // +0x1c
    int m_shift;                        // +0x20
    int m_zero;                         // +0x24
};
struct hkMoppSphereVirtualMachine {
    void* m_primitives;                 // +0x00  destination hkArray<hkMoppPrimitiveInfo>
    char  pad04[0x0c];
    int   m_lo[3];                      // +0x10  query minima in cell coordinates
    int   m_hi0;                        // +0x1c  query span
    void querySphereRec(hkMoppSphereState* st, const unsigned char* p);   // 0x01100d70
    void querySphere(const hkMoppCode* code, const hkSphere& sphere, void* primitives);
};
// ---- items of slice s01100cf0 end

// ---- items of slice s01101c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int hkUint32;
struct hkVector4_s0110_1c00 { float x, y, z, w; };
struct hkMoppPrimitiveInfo {
    hkUint32 m_id;
    hkUint32 m_data[3];
};
template <class T>
struct hkArray {
    T*   m_data;
    int  m_size;
    int  m_capacityAndFlags;
};
struct hkMoppCode_s0110_1c00 {
    char                 m_pad000[0x10];
    float                m_offsetX;    // 0x10  quantization origin
    float                m_offsetY;    // 0x14
    float                m_offsetZ;    // 0x18
    float                m_scale;      // 0x1c  world -> cell scale
    const unsigned char* m_data;       // 0x20  MOPP byte stream
};
struct hkAabb_s0110_1c00 { hkVector4_s0110_1c00 m_min; hkVector4_s0110_1c00 m_max; };
struct hkTransform_s0110_1c00 {
    float     m_col0[4];      // 0x00
    float     m_col1[4];      // 0x10
    float     m_col2[4];      // 0x20
    hkVector4_s0110_1c00 m_translation;  // 0x30
};
struct hkMoppObbState {
    int m_hi[3];       // 0x00  (m_hi >> 16) + 1 per axis
    int m_pad0c;       // 0x0c  unused
    int m_lo[3];       // 0x10  m_lo >> 16 per axis
    int m_pad1c;       // 0x1c  unused
    int m_org[3];      // 0x20  quantized origin, starts at 0
    int m_primOffset;  // 0x2c  starts at 0
    int m_shift;       // 0x30  starts at 0
    int m_reg[4];      // 0x34  scratch (only m_reg[0] is initialized)
};
static __forceinline int ToInt(float f)
{
    return _mm_cvtsd_si32(_mm_set_sd(f));
}
struct hkMoppObbVirtualMachine {
    hkArray<hkMoppPrimitiveInfo>* m_primitives;  // 0x00  output array
    int                           m_pad04[3];
    int                           m_hi[3];       // 0x10  rounding-up cell bounds
    int                           m_pad1c;
    int                           m_lo[3];       // 0x20  rounding-down cell bounds
    char                          m_pad2c[4];
    const hkMoppCode_s0110_1c00*             m_code;        // 0x30  code being queried

    // The recursive MOPP bytecode walker (thiscall, callee pops its 2 arguments).
    void queryObbRecurse(const hkMoppObbState* state, const unsigned char* p);  // 0x011014d0

    // 0x01101c00
    void queryObb(const hkMoppCode_s0110_1c00* code, const hkTransform_s0110_1c00& transform, const hkVector4_s0110_1c00& extent,
                  float radius, hkArray<hkMoppPrimitiveInfo>* primitives);

    // 0x01101e90
    void queryAabb(const hkMoppCode_s0110_1c00* code, const hkAabb_s0110_1c00& aabb,
                   hkArray<hkMoppPrimitiveInfo>* primitives);
};
// ---- items of slice s01101c00 end

// ---- items of slice s01102010 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char hkSolverCheckKeycode(int);   // 0x010bfbe0
extern char g_hkKeycodeOk;                   // 0x016e5ac0
class hkBool_s0110_2010 { public:
    char m_b;
    hkBool_s0110_2010() {}
    hkBool_s0110_2010(bool b) : m_b(b) {}
    operator bool() const { return m_b != 0; }
};
struct hkShapeRayCastOutput { float m_pad[4]; int m_shapeKey; float m_hitFraction; };   // +0x10 key, +0x14 fraction
class hkRayShapeCollectionFilter_s0110_2010;
struct hkShapeRayCastInput {
    float m_from[4];                  // +0
    float m_to[4];                    // +0x10
    uint32_t m_filterInfo;            // +0x20
    hkRayShapeCollectionFilter_s0110_2010* m_rayShapeCollectionFilter;   // +0x24
};
class hkRayHitCollector { public: virtual void v0(); float m_earlyOutHitFraction; };
class hkCdBody_s0110_2010 { public: const void* m_shape; uint32_t m_shapeKey; const void* m_motion; const hkCdBody_s0110_2010* m_parent; };
struct hkCdBodyMotionHolder { uint8_t pad[8]; const void* m_motion; };
class hkShape_s0110_2010 { public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
    virtual hkBool_s0110_2010 castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;          // slot 5 (+0x14)
    virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody_s0110_2010& body, hkRayHitCollector& collector) const;   // slot 6 (+0x18)
};
class hkShapeCollection { public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual const hkShape_s0110_2010* getChildShape(uint32_t key, void* buffer) const;                                // slot 10 (+0x28)
};
class hkRayShapeCollectionFilter_s0110_2010 { public:
    virtual hkBool_s0110_2010 isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& collection, uint32_t key) const;   // slot 0
};
struct hkMoppCodeRef { uint8_t pad[0x10]; float m_offset[4]; };
class hkOstream_s0110_2010 { public:
    hkOstream_s0110_2010(char* buf, int size, bool flag);
    ~hkOstream_s0110_2010();
    hkOstream_s0110_2010& operator<<(const char* s);
};
class hkError { public:
virtual void v0();
virtual void v1();
    virtual int message(int level, int id, const char* desc, const char* file, int line);   // slot 2
    static hkError* s_instance;      // 0x016e4184
};
struct hkMoppState {
    float m_off[4];       // +0x00 offset xyz, +0x0c w
    int   m_shift;        // +0x10
    float m_scale;        // +0x14
    int   m_primOffset;   // +0x18
    int   m_prop[4];      // +0x1c..0x28  (word 7 is carried across the copy)
    void copyFrom(const hkMoppState& src);   // 0x01101fd0
};
struct hkMoppLongRayVirtualMachine {
    uint8_t m_pad0[0x10];
    const hkMoppCodeRef* m_code;                // +0x10
    float m_invScale;                           // +0x14
    uint8_t m_pad1[8];
    hkShapeRayCastInput m_rayInput;             // +0x20 (0x28 bytes)
    uint8_t m_pad2[8];
    hkBool_s0110_2010 m_hit;                               // +0x50
    uint8_t m_pad3[3];
    float m_hitFraction;                        // +0x54
    hkShapeRayCastOutput* m_output;             // +0x58
    hkRayHitCollector* m_collector;             // +0x5c
    const hkCdBody_s0110_2010* m_cdBody;                   // +0x60
    const hkShapeCollection* m_shapeCollection; // +0x64
    void queryRay(hkMoppState* st, const uint8_t* p, float* ray);
};
// ---- items of slice s01102010 end

// ---- items of slice s01102fc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifdef _WIN32
#endif
typedef float hkTime;
class hkBool_s0110_2fc0 {
public:
    hkBool_s0110_2fc0() {}
    hkBool_s0110_2fc0(int v) : m_bool((unsigned char)v) {}
    operator unsigned char() const { return m_bool; }
    unsigned char m_bool;
};
class hkVector4_s0110_2fc0 { public: float x, y, z, w; };
class hkTransform_s0110_2fc0 { public:
    hkVector4_s0110_2fc0 m_rot[3];
    hkVector4_s0110_2fc0 m_trans;
    void setMulInverseMul(const hkTransform_s0110_2fc0& a, const hkTransform_s0110_2fc0& b);   // this = inverse(a) * b
    void setInverse(const hkTransform_s0110_2fc0& t);
};
class hkSweptTransform { public: uint32_t m_data[20]; };                            // 0x50 bytes at hkMotionState+0x40
class hkMotionState { public:                                                       // hkCdBody::m_motion points at one
    hkTransform_s0110_2fc0 m_transform;                                                 // +0
    hkSweptTransform m_sweptTransform;                                       // +0x40
};
struct hkSweptTransformUtil { static void lerp2(const hkSweptTransform& swept, float t, hkTransform_s0110_2fc0& out); };
class hkReferencedObject_s0110_2fc0 { public:
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags);
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};
class hkMemory { public:
    virtual void* allocate(int nbytes, int memClass);                        // slot 0
    virtual void  deallocate(void* p);                                       // slot 1
virtual void  v2();
virtual void v3();
    virtual void* allocateChunk(int nbytes, int memClass);                   // slot 4
    virtual void  deallocateChunk(void* p, int nbytes, int memClass);        // slot 5
    virtual void* allocateChunkFromSizeClass(int sizeIndex, int memClass);   // slot 6
    static hkMemory* s_instance;                                             // 0x016e4178
};
class hkCdBody_s0110_2fc0 { public:
    const void* m_shape; uint32_t m_shapeKey; const hkMotionState* m_motion; const hkCdBody_s0110_2fc0* m_parent;
};
struct hkContactMgr;
struct hkCollisionDispatcher_s0110_2fc0;
struct hkCollisionInput_s0110_2fc0;
class hkCollisionFilter_s0110_2fc0 { public:
    // vtable slot 0 (returns hkBool through a hidden pointer in the binary)
    virtual hkBool_s0110_2fc0 isCollisionEnabled(const hkCollisionInput_s0110_2fc0& input, const hkCdBody_s0110_2fc0& a, const hkCdBody_s0110_2fc0& b, const void* bContainer, uint32_t bKey) const;
};
struct hkCollisionInput_s0110_2fc0 {
    hkCollisionDispatcher_s0110_2fc0* m_dispatcher;      // +0
    hkCollisionFilter_s0110_2fc0* m_filter;              // +4
    uint32_t m_pad[2];
    float m_stepTime;                         // +0x10  (time handed to hkSweptTransformUtil::lerp2)
};
class hkMoppCode_s0110_2fc0 : public hkReferencedObject_s0110_2fc0 { public:
    uint32_t m_pad0;                          // +8
    uint32_t m_pad1;                          // +0xc
    hkVector4_s0110_2fc0 m_offset;                       // +0x10: xyz = offset, w = scale (CodeInfo::getScale)
    uint8_t* m_data;                          // +0x20 (hkArray<hkUint8>::m_data)
    int m_dataSize;
    int m_dataCapacityAndFlags;
};
struct hkShapeRayCastInput_s0110_2fc0 {                  // 40 bytes
    hkVector4_s0110_2fc0 m_from;                         // +0
    hkVector4_s0110_2fc0 m_to;                           // +0x10
    uint32_t m_filterInfo;                    // +0x20
    uint32_t m_userData;                      // +0x24
};
struct hkShapeRayCastOutput;
struct hkShapeCollection;
struct hkMoppLongRayVirtualMachine_s0110_2fc0 {
    uint8_t m_pad0[0x10];                     // +0
    const hkMoppCode_s0110_2fc0* m_code;                 // +0x10
    float m_invScale;                         // +0x14
    uint8_t m_pad1[8];                        // +0x18
    hkShapeRayCastInput_s0110_2fc0 m_rayInput;           // +0x20 .. 0x48
    uint8_t m_pad2[8];                        // +0x48
    hkBool_s0110_2fc0 m_hit;                             // +0x50
    uint8_t m_pad3[3];
    float m_hitFraction;                      // +0x54  (early out hit fraction)
    hkShapeRayCastOutput* m_output;           // +0x58
    hkRayHitCollector* m_collector;           // +0x5c
    const hkCdBody_s0110_2fc0* m_cdBody;                 // +0x60
    const hkShapeCollection* m_shapeCollection; // +0x64
    hkBool_s0110_2fc0 queryLongRay(const hkShapeCollection* collection, const hkMoppCode_s0110_2fc0* code, const hkShapeRayCastInput_s0110_2fc0& input, hkShapeRayCastOutput& output);
    void   queryLongRay(const hkShapeCollection* collection, const hkMoppCode_s0110_2fc0* code, const hkShapeRayCastInput_s0110_2fc0& input, const hkCdBody_s0110_2fc0& body, hkRayHitCollector& collector);
    void   queryRay(const hkVector4_s0110_2fc0* zeroVec, const uint8_t* moppData, const float* fromTo);   // FUN_01102010 (thiscall) 0x01102010
};
static const float HK_MOPP_RANGE_SCALE = 1.52587890625e-05f;
struct hkShapeContainer {
    // vtable slots used here (hkShapeContainer in the 3.1 shape collection): 7 getNumChildShapes, 8 getFirstKey,
    // 9 getNextKey, 10 getChildShape
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
    virtual int  getNumChildShapes() const;                                      // +0x1c
    virtual uint32_t getFirstKey() const;                                        // +0x20
    virtual uint32_t getNextKey(uint32_t oldKey) const;                          // +0x24
    virtual const struct hkProjShape* getChildShape(uint32_t key, void* buffer512) const;   // +0x28
};
struct hkProjShape {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
    virtual float getMaximumProjection(const hkVector4_s0110_2fc0& direction) const;        // +0x10
};
struct hkShapeKeyList : hkReferencedObject_s0110_2fc0 {                                     // vtable 0x014a5dec
    hkShapeContainer* m_container;                                               // +8
    int m_numKeys;                                                               // +0xc
    hkShapeKeyList(hkShapeContainer* container);
    void fillKeys(uint8_t* out /* stride 0x10 {key, 0, ...} */) const;
};
#include "MoppSettings.h"
static void __cdecl MoppCallInitA(hkMoppSettings* self, int preset)
{
    self->m_a.init(preset);
}
static void __cdecl MoppCallInitB(hkMoppSettings* self, int preset)
{
    self->m_b.init(preset);
}
static void (__cdecl* volatile g_moppInitA)(hkMoppSettings*, int) = MoppCallInitA;
static void (__cdecl* volatile g_moppInitB)(hkMoppSettings*, int) = MoppCallInitB;
struct hkMoppArena {                                     // 16 bytes
    uint8_t* m_begin; uint8_t* m_mid; uint8_t* m_end; uint32_t m_counter;
    void init(int bytes);                                // FUN_0111eab0
};
struct hkMoppArenaCounter { void* getRecord(); };        // FUN_0111eef0 (called on &arena.m_counter)
struct hkMoppObj2Sub {                                   // at hkMoppObj2 + 0x20
    uint8_t m_data[0x3c];
    void finalize();                                     // FUN_0111fbd0
    void* compile(hkMoppSource* src, struct hkMoppObj2* obj2, struct hkMoppObj3* obj3, const hkMoppSettingsPartA* a, hkMoppArena* arena);   // FUN_011202d0
    void destroy();                                      // FUN_005725f0
};
struct hkMoppObj2 {                                      // 0x5c bytes
    uint8_t m_head[0x20];
    hkMoppObj2Sub m_sub;
    void init(const hkMoppSettingsPartB* b);             // FUN_01120610
};
struct hkMoppObj3 {                                      // 0x80 bytes, vtable first
virtual void o0();
virtual void o1();
virtual void o2();
virtual void o3();
virtual void o4();
    virtual void attach(void* code, void* record);       // slot 5 (+0x14)
    uint8_t m_data[0x7c];
    void init(const void* settingsC, hkMoppArena* arena, hkMoppSource* src);   // FUN_0111df20
    void destroy();                                      // FUN_005725f0
};
struct hkAgent3Input {
    const hkCdBody_s0110_2fc0* m_bodyA;                  // +0
    const hkCdBody_s0110_2fc0* m_bodyB;                  // +4 (pointers are 4 bytes in the binary)
    const hkCollisionInput_s0110_2fc0* m_input;          // +8
    hkContactMgr* m_contactMgr;               // +0xc
    hkTransform_s0110_2fc0 m_aTb;                        // +0x10
};
struct hkAgent3ProcessInput : hkAgent3Input { // 0x70 bytes
    uint32_t m_pad[4];                        // +0x50
    hkVector4_s0110_2fc0 m_linearTimInfo;                // +0x60
};
struct hkAgent3Source { const hkCdBody_s0110_2fc0* m_bodyA; const hkCdBody_s0110_2fc0* m_bodyB; const hkCollisionInput_s0110_2fc0* m_input; hkContactMgr* m_contactMgr; };
struct hkAgent3Scratch { hkCdBody_s0110_2fc0 m_bodyA; hkCdBody_s0110_2fc0 m_bodyB; hkTransform_s0110_2fc0 m_transformA; hkTransform_s0110_2fc0 m_transformB; };
struct hkAgent1nSector {
    uint32_t m_bytesAllocated;                // +0
    uint32_t m_pad[3];
    uint8_t  m_data[512 - 16];                // +0x10
};
struct hkAgent1nTrack {
    hkAgent1nSector** m_sectorsData;          // +0   hkArray<hkAgent1nSector*>
    int m_sectorsSize;                        // +4
    int m_sectorsCapacityAndFlags;            // +8
};
struct hkAgent1nMachineEntry { uint8_t m_streamCommand; uint8_t m_agentType; uint8_t m_pad2; uint8_t m_size; };
typedef void (__cdecl *hkAgent3InvalidateTimFunc)(hkAgent1nMachineEntry* entry, void* agentData, const hkCollisionInput_s0110_2fc0* input);
typedef void (__cdecl *hkAgent3WarpTimeFunc)(hkAgent1nMachineEntry* entry, void* agentData, hkTime oldTime, hkTime newTime, const hkCollisionInput_s0110_2fc0* input);
struct hkAgent1nMachine_VisitorInput;
typedef void (__cdecl *hkAgent3DestroyFunc)(hkAgent1nMachineEntry* entry, void* agentData, void* constraintOwner);
struct hkAgent3Funcs {                        // 0x34 bytes in the 32-bit binary
    hkAgent3DestroyFunc m_destroyFunc;        // +0
    void* m_other0[5];
    hkAgent3InvalidateTimFunc m_invalidateTimFunc;   // +0x18
    hkAgent3WarpTimeFunc m_warpTimeFunc;             // +0x1c
    void* m_other1[5];
};
class hkCollisionDispatcher_s0110_2fc0 { public:
    uint8_t m_pad[0x1698];                    // (32-bit layout)
    hkAgent3Funcs m_agent3Func[1];            // +0x1698, indexed by agent type
};
struct hkAgent1nMachine_VisitorInput {
    const hkCdBody_s0110_2fc0* m_bodyA;                  // +0
    const hkCdBody_s0110_2fc0* m_collectionBodyB;        // +4
    const void* m_containerShapeB;            // +8
    const hkCollisionInput_s0110_2fc0* m_input;          // +0xc
    void* m_constraintOwner;                  // +0x10
};
struct hkAgent1nMachineKeyedEntry : hkAgent1nMachineEntry { uint32_t m_shapeKeyA; uint32_t m_shapeKeyB; };   // key B at +8
// ---- items of slice s01102fc0 end

// ---- items of slice s01106490 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned FUN_01105940(const float* segA, const float* dA,
                                 const float* segB, const float* dB,
                                 float* out9);
struct __declspec(align(16)) hkVector4_s0110_6490 {
    float x, y, z, w;
};
class hkContactPoint_s0110_6490 { public:
    hkVector4_s0110_6490 m_position;
    hkVector4_s0110_6490 m_separatingNormal;   // w = distance
};
static const float HK_REAL_EPSILON = 1.1920929e-07f;   // 0x014a5e90
static __forceinline float Rounded(double x)
{
    volatile float m = (float)x;
    return m;
}
typedef double hkExtReal;
static __forceinline hkExtReal dot3(const hkVector4_s0110_6490& a, const hkVector4_s0110_6490& b)
{
    return (hkExtReal)a.x * b.x + (hkExtReal)a.z * b.z + (hkExtReal)a.y * b.y;
}
template <bool spillLength>
static __forceinline void normalize3(hkVector4_s0110_6490& v)
{
    hkExtReal len2 = (hkExtReal)v.x * v.x + (hkExtReal)v.y * v.y + (hkExtReal)v.z * v.z;
    if (spillLength)
        len2 = Rounded(len2);
    hkExtReal inv;
    if (len2 == 0.0f)
        inv = 0.0f;
    else
        inv = 1.0f / sqrt(len2);
    v.x = Rounded(inv * v.x);
    v.y = Rounded(inv * v.y);
    v.z = Rounded(inv * v.z);
    v.w = Rounded(inv * v.w);
}
// ---- items of slice s01106490 end

// ---- items of slice s01107270 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkVector4_s0110_7270 { public: float v[4]; };
struct hkContactPointF {
    float pos[4];
    float nrm[4];   // nrm[3] is the separating distance
    void assign(const hkContactPointF& o);   // 0x01101fd0: 32-byte copy
};
struct hkCollideTriangleUtil {
    struct ClosestLineSegLineSegResult {
        hkVector4_s0110_7270 closestPointA;
        hkVector4_s0110_7270 closestAminusClosestB;
        float distanceSquared;
    };
    static int closestLineSegLineSeg(const hkVector4_s0110_7270& A, const hkVector4_s0110_7270& dA, const hkVector4_s0110_7270& B,
                                     const hkVector4_s0110_7270& dB, ClosestLineSegLineSegResult& r);
};
extern "C" void hkCollideCapsuleUtilManifoldCapsVsCaps_s0110_7270(const float* a, float ra, const float* b, float rb,
                                                       hkContactPointF* out);
#define EDGE_END(i)   (*(const signed char*)(0x014a5e70 + (i)))
#define EDGE_START(i) (*(const signed char*)(0x014a5e72 + (i)))
// ---- items of slice s01107270 end

// ---- items of slice s01108460 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float hkReal;
struct __declspec(align(16)) hkVector4_s0110_8460 {
    hkReal x, y, z, w;
};
struct hkMatrix3_s0110_8460 {
    hkVector4_s0110_8460 c0, c1, c2;
};
struct hkTransform_s0110_8460 {
    hkVector4_s0110_8460 c0, c1, c2;   // basis columns
    hkVector4_s0110_8460 t;            // translation
};
static const hkVector4_s0110_8460 g_axisMask[8] = {
    { 1.0f, 1.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 1.0f, 1.0f },
    { 0.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
};
static void hkSetBitIfClear(unsigned int* bits, unsigned int bit)
{
    if ((*bits & (bit << 1)) == 0)
        *bits |= bit;
}
struct hkFeaturePointList {
    uint8_t  m_rec[1];    // variable: record[i].class@+4*i, .feature@+4*i+1
    uint8_t  pad20;
    uint8_t  m_count;     // +0x21  number of records
    uint8_t  m_valid;     // +0x22
};
struct hkSignBytes {
    uint8_t m_lo;
    uint8_t m_hi;
};
struct hkFeatureContactPoint {
    uint8_t  m_id;        // +0x00
    uint8_t  m_feature;   // +0x01
    uint16_t m_axis;      // +0x02
};
struct hkFeaturePointCache {
    hkVector4_s0110_8460 m_v0;       // +0x00
    hkVector4_s0110_8460 m_v1;       // +0x10
    hkVector4_s0110_8460 m_v2;       // +0x20
    hkReal   m_w30;       // +0x30  stored as +/-1.0f
    uint32_t m_d34;       // +0x34
    uint32_t m_d38;       // +0x38  feature id
    uint32_t m_d3c;
};
struct hkProcessCdPoint {
    hkVector4_s0110_8460 m_position;   // +0x00
    hkVector4_s0110_8460 m_normal;     // +0x10  (w @ +0x1c)
    uint16_t  m_d20;        // +0x20
    uint16_t  m_pad22;
};
struct hkBoxBoxManifold {
    uint8_t  m_rec[1];
    uint8_t  pad20;
    uint8_t  m_count;     // +0x21
    uint8_t  m_d22;
};
class hkBoxBoxCollisionDetection {
public:
    uint8_t            pad00[0x14];
    const hkTransform_s0110_8460* m_wTa;          // +0x14  A's world transform
    const hkTransform_s0110_8460* m_wTb;          // +0x18  B's world transform
    uint8_t            pad1c[4];
    hkMatrix3_s0110_8460      m_aRb;             // +0x20  B's rotation expressed in A
    hkVector4_s0110_8460      m_aTb;             // +0x50  B's origin expressed in A
    hkVector4_s0110_8460      m_radiusA;         // +0x60
    hkVector4_s0110_8460      m_radiusB;         // +0x70
    hkVector4_s0110_8460      pad80;
    hkVector4_s0110_8460      m_boundaryTol;     // +0x90

    void faceAVertexBValidationDataFromFeatureId(hkFeaturePointCache& out,
                                                 const hkFeatureContactPoint& cp);        // 0x01108940
    void faceBVertexAValidationDataFromFeatureId(hkFeaturePointCache& out,
                                                 const hkFeatureContactPoint& cp);        // 0x01108ac0
    void faceAVertexBContactPointFromFeaturePointCache(hkProcessCdPoint& out,
                                                       const hkFeatureContactPoint& cp,
                                                       const hkFeaturePointCache& cache);  // 0x01108a10
    void faceBVertexAContactPointFromFeaturePointCache(hkProcessCdPoint& out,
                                                       const hkFeatureContactPoint& cp,
                                                       const hkFeaturePointCache& cache);  // 0x01108b80
    void edgeEdgeContactPointFromFeaturePointCache(hkProcessCdPoint& out,
                                                   const hkFeatureContactPoint& cp,
                                                   const hkFeaturePointCache& cache);      // 0x01108c30
    void tryToAddPointFaceA(hkBoxBoxManifold& manifold, hkFeatureContactPoint cp,
                            unsigned short a, hkReal tol);                                    // 0x01108d00
};
// ---- items of slice s01108460 end

// ---- items of slice s011090b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint16_t g_14a5f70[7];   // 0x014a5f70
extern float          g_14a5f80;      // 0x014a5f80  epsilon
extern float          g_1485378;      // 0x01485378  neighbour dot threshold
struct Slot {
    uint8_t  m00;       // +0x00  slot kind (0..6 selects the matrix / commit helper)
    uint8_t  m01;       // +0x01  slot flags (hashed from the entry mask)
    uint16_t m02;       // +0x02  handle returned by the sink
};
struct Req {
    uint8_t  m00;       // +0x00  kind (low byte of the caller key)
    uint8_t  m01;       // +0x01  flags
    uint16_t m02;       // +0x02  id (high word of the caller key)
    int32_t  m04;       // +0x04  reserved handle
};
union Key {
    int32_t mKey;
    Req     mReq;
};
struct SlotSet {
    Slot    mSlots[8];                                     // +0x00
    uint8_t m20;                                           // +0x20  added counter
    uint8_t m21;                                           // +0x21  used slot count
    int32_t Reserve(uint32_t a, uint32_t b, Req* req);      // 0x010ec540
    void    Release(int32_t handle);                        // 0x010ec4a0
};
struct Node {
    float    m00;       // +0x00
    float    m04;       // +0x04
    float    m08;       // +0x08
    uint8_t  pad0C[4];  // +0x0c
    float    m10;       // +0x10
    float    m14;       // +0x14
    float    m18;       // +0x18
    uint8_t  pad1C[4];  // +0x1c
    uint16_t m20;       // +0x20
    uint8_t  pad22[0x0e];
};
struct Cursor {
    Node* mpNode;       // +0x00
};
struct Mat34 {
    float m[15];
};
struct __declspec(align(16)) Hit {
    float   m00[4];     // +0x00
    float   m10[4];     // +0x10
    float   m20[4];     // +0x20
    float   m30;        // +0x30
    float   m34;        // +0x34
    int32_t m38;        // +0x38  index into m00 / the m60 table
    uint8_t pad3C[4];   // +0x3c
};
struct SlotScatter {
    uint32_t m00;       // +0x00
    uint32_t m04;       // +0x04
    uint32_t m08;       // +0x08
    void*    m0C;       // +0x0c  sink object, vtable slot +0x08 adds a node
    Cursor*  m10;       // +0x10
    Mat34*   m14;       // +0x14  matrix for slot kinds 3..6
    Mat34*   m18;       // +0x18  matrix for slot kinds 0..2
    uint8_t  pad1C[0x60 - 0x1c];
    float    m60[4];    // +0x60  per-component offsets
    uint8_t  pad70[0xa0 - 0x70];
    float    mA0[4];    // +0xa0  per-component extents
    float    mB0;       // +0xb0  clearance radius

    void Place(SlotSet* set, int32_t key, uint32_t mask, float limit);   // 0x011090b0
    void QuerySlot(Hit* out, Req* req);                                  // 0x01108ac0
    void CommitA(Node* node, int32_t* handle, Hit* out);                 // 0x01108a10
    void CommitB(Node* node, int32_t* handle, Hit* out);                 // 0x01108b80
    void CommitC(Node* node, int32_t* handle, Hit* out);                 // 0x01108c30
};
// ---- items of slice s011090b0 end

// ---- items of slice s0110a0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static const float kSignTable[8][4] =
{
    {  1.0f,  1.0f,  1.0f, 0.0f },   // 0
    {  1.0f,  1.0f, -1.0f, 0.0f },   // 1
    {  1.0f, -1.0f,  1.0f, 0.0f },   // 2
    {  1.0f, -1.0f, -1.0f, 0.0f },   // 3
    { -1.0f,  1.0f,  1.0f, 0.0f },   // 4
    { -1.0f,  1.0f, -1.0f, 0.0f },   // 5
    { -1.0f, -1.0f,  1.0f, 0.0f },   // 6
    { -1.0f, -1.0f, -1.0f, 0.0f },   // 7
};
static inline float xorSign(float value, float fromSign)
{
    // retail: (uint)value ^ ((uint)expr & 0x80000000)
    union { float f; unsigned u; } a, b;
    a.f = value;
    b.f = fromSign;
    a.u ^= (b.u & 0x80000000u);
    return a.f;
}
struct hkFeatureContactPoint_s0110_a0d0          // 4-byte box-box feature pair
{
    unsigned char  mA;       // 0x00
    unsigned char  mB;       // 0x01
    unsigned short mIndex;   // 0x02
};
struct hkFeaturePointCache_s0110_a0d0           // 0x40 bytes, per-feature validation scratch
{
    float mPoint[4];     // 0x00
    float mDir[4];       // 0x10
    float mTan[4];       // 0x20
    float mScale;        // 0x30
    float mDist;         // 0x34
    float mIndexA;       // 0x38
    float mIndexB;       // 0x3c
};
struct hkProcessCdPoint_s0110_a0d0              // 0x30-byte manifold point slot
{
    float          mX;          // 0x00
    float          mY;          // 0x04
    float          mZ;          // 0x08
    uint32_t       pad0c[1];    // 0x0c
    float          mNX;         // 0x10
    float          mNY;         // 0x14
    float          mNZ;         // 0x18
    uint32_t       pad1c[1];    // 0x1c
    unsigned short mIndex;      // 0x20
    uint32_t       pad22[3];    // 0x22
    unsigned short pad2e;       // 0x2e
};
struct hkPointRing                   // per-detection point ring with cursor
{
    hkProcessCdPoint_s0110_a0d0* mCursor;      // 0x00
    uint32_t          pad04[11];    // 0x04 .. 0x2f
    hkProcessCdPoint_s0110_a0d0  mPoints[1];   // 0x30
};
struct hkBoxBoxManifoldEntry
{
    unsigned char  mA;       // 0x00
    unsigned char  mB;       // 0x01
    unsigned short mIndex;   // 0x02
};
struct hkBoxBoxManifold_s0110_a0d0
{
    hkBoxBoxManifoldEntry mEntries[8];   // 0x00
    unsigned char         mCount20;      // 0x20
    unsigned char         mCount21;      // 0x21

    void removePoint(int index);         // @ 0x010ec4a0
};
struct TC_contactPoint
{
    void FUN_01108a10(hkProcessCdPoint_s0110_a0d0&, const hkFeatureContactPoint_s0110_a0d0&, const hkFeaturePointCache_s0110_a0d0&);  // faceAVertexB
    void FUN_01108b80(hkProcessCdPoint_s0110_a0d0&, const hkFeatureContactPoint_s0110_a0d0&, const hkFeaturePointCache_s0110_a0d0&);  // faceBVertexA
    void FUN_01108c30(hkProcessCdPoint_s0110_a0d0&, const hkFeatureContactPoint_s0110_a0d0&, const hkFeaturePointCache_s0110_a0d0&);  // edgeEdge
};
struct TC_manifold
{
    int FUN_010ec540(void* a, void* b, void* c);   // hkBoxBoxManifold::addPoint
};
void FUN_01108750(void* out, void* a, void* b);    // hkBoxBoxUtils::hkPackSigns2
struct hkBoxBoxCollisionDetection_s0110_a0d0
{
    void*        m00;         // 0x00
    void*        m04;         // 0x04
    void*        m08;         // 0x08
    void*        mVtObj;      // 0x0c  object whose vtable slot 2 is queried
    hkPointRing* mRing;       // 0x10  manifold point ring
    float*       mMatA;       // 0x14
    float*       mMatB;       // 0x18
    uint32_t     pad1c[1];    // 0x1c
    float        mRow[6][4];  // 0x20 .. 0x7f
    uint32_t     pad80[12];   // 0x80 .. 0xaf
    float        mB0;         // 0xb0
    float        mB4;         // 0xb4
    uint32_t     padB8[2];    // 0xb8
    float        mC[4];       // 0xc0
    float        mD[4];       // 0xd0

    void  faceAVertexBValidationDataFromFeatureIndex(hkFeaturePointCache_s0110_a0d0& c, float featureIndex) const;  // 0x0110a0d0
    void  faceBVertexAValidationDataFromFeatureIndex(hkFeaturePointCache_s0110_a0d0& c, int featureIndex) const;    // 0x0110a2b0
    void  edgeEdgeValidationDataFromFeatureIndex(hkFeaturePointCache_s0110_a0d0& c) const;                           // 0x0110a4b0
    void  addAdditionalEdgeHelper(hkBoxBoxManifold_s0110_a0d0& m, hkFeatureContactPoint_s0110_a0d0& p, float f) const;          // 0x0110a9c0
    char* FUN_0110a600(char* outFlag, hkFeaturePointCache_s0110_a0d0& cache) const;                                  // 0x0110a600
    void  FUN_0110ac90(hkBoxBoxManifold_s0110_a0d0& m, void* a2, void* a3, int p4, int p5, void* a6, void* a7, float f); // 0x0110ac90
};
// ---- items of slice s0110a0d0 end

// ---- items of slice s0110ad70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#undef CONSIDER
struct FeaturePairList {
  unsigned char mPairs[8][4];   // +0x00  {feature, signs, pad, pad}
  unsigned char mField20;       // +0x20
  unsigned char mCount;         // +0x21
  char          mPad22[0x26];   // +0x22

  void FUN_010ec500();          // 0x010ec500
};
struct FeaturePair {
  unsigned char mFeature[2];    // +0x00
  unsigned short mPad;          // +0x02
};
union DepthSlot {
  float    mFloat;
  unsigned mBits;
};
struct __declspec(align(16)) FeaturePointCache {
  float mFeatures[12];   // +0x00  [0..3] = A side, [4..7] = B side
  float mScale;          // +0x30
  float mResult;         // +0x34
  int   mIndex;          // +0x38
  int   mSubIndex;       // +0x3c
};
struct ProcessCdPoint {
  float mPoint[3];    // +0x00  contact position
  float mDistance;    // +0x0c
  float mPlane[4];    // +0x10  contact normal
};
struct CdPoint {
  float mPoint[3];    // +0x00
  float mDistance;    // +0x0c
  float mPlane[4];    // +0x10
};
struct CollisionInput {
  char mData[0x10];   // +0x00
};
struct BoxBoxDetector {
  char           mPad00[0x60];   // +0x00
  float          mPlaneA[4];     // +0x60
  float          mPlaneB[4];     // +0x70
  CollisionInput mInput;         // +0x80
  float          mThreshA[4];    // +0x90
  float          mThreshB[4];    // +0xa0
  char           mPadB0[0x30];   // +0xb0
  DepthSlot      mDepth[5][4];   // +0xe0

  void FUN_010d93e0();                                   // 0x010d93e0
  int  FUN_01109460(CollisionInput* in);                 // 0x01109460
  void FUN_0110a0d0(FeaturePointCache* d, int id);       // 0x0110a0d0
  void FUN_0110a2b0(FeaturePointCache* d, int id);       // 0x0110a2b0
  void FUN_0110a4b0(FeaturePointCache* d);               // 0x0110a4b0
  void FUN_0110a600(void* res, FeaturePointCache* d);    // 0x0110a600
  void FUN_01108a10(ProcessCdPoint* cp, FeaturePair* fp,
                    FeaturePointCache* d);               // 0x01108a10
  void FUN_01108b80(ProcessCdPoint* cp, FeaturePair* fp,
                    FeaturePointCache* d);               // 0x01108b80
  void FUN_01108c30(ProcessCdPoint* cp, FeaturePair* fp,
                    FeaturePointCache* d);               // 0x01108c30

  int  FUN_0110ad70(FeaturePairList* list, unsigned char* out,
                    FeaturePointCache* d);
  void FUN_0110b260(unsigned char* out, CdPoint* result);
};
static unsigned char PackSigns1(const float* dir, float scale)
{
  DepthSlot bits;
  bits.mFloat = scale;

  unsigned char s0 = dir[0] < 0.0f;
  unsigned char s1 = dir[1] < 0.0f;
  unsigned char s2 = dir[2] < 0.0f;

  return (unsigned char)((s0 << 7) | (s1 << 6) | (s2 << 5) |
                         ((bits.mBits >> 28) & 8));
}
static unsigned short PackSigns2(const float* dirA, const float* dirB,
                                 int a, int b)
{
  unsigned char s0 = dirA[0] < 0.0f;
  unsigned char s1 = dirA[1] < 0.0f;
  unsigned char s2 = dirA[2] < 0.0f;
  unsigned char s3 = dirB[0] < 0.0f;
  unsigned char s4 = dirB[1] < 0.0f;
  unsigned char s5 = dirB[2] < 0.0f;

  unsigned char lo = (unsigned char)(((s2 << 1) | (s1 << 2) |
                                      (s0 * (unsigned char)0xf8)) | 1) << 4;
  unsigned char hi = (unsigned char)(~((s5 << 1) | (s4 << 2) |
                                      (s3 * (unsigned char)0xf8)) & 0xe) << 4;

  return (unsigned short)(((hi + (unsigned char)b) * 256) +
                          (unsigned char)(lo + (unsigned char)a));
}
#define CONSIDER(level, sub, value)                                  \
  if (best < mDepth[level][sub].mFloat) {                            \
    id = value;                                                      \
    best = mDepth[level][sub].mFloat;                                \
  }
// ---- items of slice s0110ad70 end

// ---- items of slice s0110b3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool g_hkBoxBoxAddAdditionalEdges;   // 0x016e58f8
extern const int g_hkBoxBoxNextAxis[4];     // 0x014a5ec4 {1, 2, 0, 1}
typedef uint16_t hkContactPointId;
class hkBool_s0110_b3a0 {
public:
    char m_bool;
    hkBool_s0110_b3a0() {}
    operator bool() const { return m_bool != 0; }
};
class __declspec(align(16)) hkVector4_s0110_b3a0 {
public:
    hkReal x, y, z, w;

    hkReal& operator()(int i) { return (&x)[i]; }
    const hkReal& operator()(int i) const { return (&x)[i]; }
    void setRotatedDir(const class hkRotation_s0110_b3a0& r, const hkVector4_s0110_b3a0& v);   // 0x010814a0
};
class hkRotation_s0110_b3a0 {
public:
    hkVector4_s0110_b3a0 c0, c1, c2;   // columns
    const hkVector4_s0110_b3a0& getColumn(int i) const { return (&c0)[i]; }
};
class hkTransform_s0110_b3a0 {
public:
    hkRotation_s0110_b3a0 m_rotation;
    hkVector4_s0110_b3a0  m_translation;
};
class hkCdBody_s0110_b3a0;
struct hkCollisionInput_s0110_b3a0;
class hkContactPoint_s0110_b3a0 {
public:
    hkVector4_s0110_b3a0 m_position;
    hkVector4_s0110_b3a0 m_separatingNormal;   // w = distance
};
struct hkProcessCdPoint_s0110_b3a0 {
    hkContactPoint_s0110_b3a0   m_contact;
    hkContactPointId m_contactPointId;   // +0x20
    uint16_t         m_pad22;
    uint32_t         m_pad24[3];

    hkProcessCdPoint_s0110_b3a0& operator=(const hkProcessCdPoint_s0110_b3a0& o);   // 0x01103af0
};
struct hkProcessCollisionOutput {
    hkProcessCdPoint_s0110_b3a0* m_firstFreeContactPoint;   // +0x00
    uint32_t          m_pad04[(0x30 - 0x04) / 4];
    hkProcessCdPoint_s0110_b3a0  m_contactPoints[8];        // +0x30

    int getNumContactPoints() const { return (int)(m_firstFreeContactPoint - &m_contactPoints[0]); }
};
class hkContactMgr_s0110_b3a0 {
public:
    virtual void v00();
    virtual void v04();
    virtual hkContactPointId addContactPoint(const hkCdBody_s0110_b3a0& a, const hkCdBody_s0110_b3a0& b,
                                             const hkCollisionInput_s0110_b3a0& input, hkProcessCdPoint_s0110_b3a0& cp);   // +0x08
    virtual void v0c();
    virtual void removeContactPoint(hkContactPointId id);   // +0x10
};
class hkFeatureContactPoint_s0110_b3a0 {
public:
    hkFeatureContactPoint_s0110_b3a0() { m_contactPointId = 0; }

    uint8_t          m_featureIdA;
    uint8_t          m_featureIdB;
    hkContactPointId m_contactPointId;
};
class hkBoxBoxManifold_s0110_b3a0 {
public:
    int  addPoint(const hkCdBody_s0110_b3a0& bodyA, const hkCdBody_s0110_b3a0& bodyB, hkFeatureContactPoint_s0110_b3a0& fcp);   // 0x010ec540
    void removePoint(int index);                                                                // 0x010ec4a0

    hkFeatureContactPoint_s0110_b3a0 m_contactPoints[8];
    uint8_t   m_faceVertexFeatureCount;      // +0x20
    uint8_t   m_numPoints;                   // +0x21
    hkBool_s0110_b3a0    m_isComplete;                  // +0x22
    hkBool_s0110_b3a0    m_manifoldNormalInitialized;   // +0x23
    uint32_t  m_pad24[3];
    hkVector4_s0110_b3a0 m_manifoldNormalA;             // +0x30
    hkVector4_s0110_b3a0 m_manifoldNormalB;             // +0x40
};
inline hkReal hkFabs(hkReal r) { return (hkReal)fabs(r); }
inline hkReal hkMin2(hkReal a, hkReal b) { return (a < b) ? a : b; }
__forceinline int compareLessThan4(const hkVector4_s0110_b3a0& v, const hkVector4_s0110_b3a0& a)
{
    return ((v.x < a.x) ? 8 : 0) | ((v.y < a.y) ? 4 : 0) | ((v.z < a.z) ? 2 : 0) | ((v.w < a.w) ? 1 : 0);
}
__forceinline int compareLessThanZero4(const hkVector4_s0110_b3a0& v)
{
    return ((v.x < 0.0f) ? 8 : 0) | ((v.y < 0.0f) ? 4 : 0) | ((v.z < 0.0f) ? 2 : 0) | ((v.w < 0.0f) ? 1 : 0);
}
__forceinline void setAbs4(hkVector4_s0110_b3a0& r, const hkVector4_s0110_b3a0& v)
{
    r.x = hkFabs(v.x);
    r.y = hkFabs(v.y);
    r.z = hkFabs(v.z);
    r.w = hkFabs(v.w);
}
__forceinline void setRotatedDirInl(hkVector4_s0110_b3a0& r, const hkRotation_s0110_b3a0& m, const hkVector4_s0110_b3a0& v)
{
    const hkReal v0 = v.x;
    const hkReal v1 = v.y;
    const hkReal v2 = v.z;
    r.x = m.c0.x * v0 + m.c1.x * v1 + m.c2.x * v2;
    r.y = m.c0.y * v0 + m.c1.y * v1 + m.c2.y * v2;
    r.z = m.c0.z * v0 + m.c1.z * v1 + m.c2.z * v2;
}
__forceinline void setRotatedInverseDir(hkVector4_s0110_b3a0& r, const hkRotation_s0110_b3a0& m, const hkVector4_s0110_b3a0& v)
{
    const hkReal v0 = v.x;
    const hkReal v1 = v.y;
    const hkReal v2 = v.z;
    r.x = m.c0.x * v0 + m.c0.y * v1 + m.c0.z * v2;
    r.y = m.c1.x * v0 + m.c1.y * v1 + m.c1.z * v2;
    r.z = m.c2.x * v0 + m.c2.y * v1 + m.c2.z * v2;
}
__forceinline void setTransformedPos(hkVector4_s0110_b3a0& r, const hkTransform_s0110_b3a0& t, const hkVector4_s0110_b3a0& v)
{
    const hkReal v0 = v.x;
    const hkReal v1 = v.y;
    const hkReal v2 = v.z;
    r.x = t.m_rotation.c0.x * v0 + t.m_rotation.c1.x * v1 + t.m_rotation.c2.x * v2 + t.m_translation.x;
    r.y = t.m_rotation.c0.y * v0 + t.m_rotation.c1.y * v1 + t.m_rotation.c2.y * v2 + t.m_translation.y;
    r.z = t.m_rotation.c0.z * v0 + t.m_rotation.c1.z * v1 + t.m_rotation.c2.z * v2 + t.m_translation.z;
}
__forceinline hkReal dot3_s0110_b3a0(const hkVector4_s0110_b3a0& a, const hkVector4_s0110_b3a0& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
static uint8_t vertexIdFromNormal(const hkVector4_s0110_b3a0& n, hkReal din)
{
    int mask = compareLessThanZero4(n);
    uint32_t bits = *reinterpret_cast<const uint32_t*>(&din);
    return (uint8_t)(((mask << 4) & 0xe0) | ((bits >> 28) & 8));
}
class hkBoxBoxCollisionDetection_s0110_b3a0 {
public:
    class hkFeaturePointCache {
    public:
        hkVector4_s0110_b3a0 m_vA;           // +0x00
        hkVector4_s0110_b3a0 m_vB;           // +0x10
        hkVector4_s0110_b3a0 m_normal;       // +0x20
        hkReal    m_nscale;       // +0x30
        hkReal    m_distance;     // +0x34
        int       m_featureIndexA;  // +0x38
        int       m_featureIndexB;  // +0x3c
    };

    void calcManifold(hkBoxBoxManifold_s0110_b3a0& manifold) const;

    void initVars() const;   // 0x010d93e0
    void faceAVertexBValidationDataFromFeatureId(hkFeaturePointCache& fpp, const hkFeatureContactPoint_s0110_b3a0& fcp) const;   // 0x01108940
    void faceBVertexAValidationDataFromFeatureId(hkFeaturePointCache& fpp, const hkFeatureContactPoint_s0110_b3a0& fcp) const;   // 0x01108ac0
    hkBool_s0110_b3a0 edgeEdgeValidationDataFromFeatureId(hkFeaturePointCache& fpp) const;                                     // 0x0110a600
    void faceAVertexBContactPointFromFeaturePointCache(hkProcessCdPoint_s0110_b3a0& cp, const hkFeatureContactPoint_s0110_b3a0& fcp, const hkFeaturePointCache& fpp) const;   // 0x01108a10
    void faceBVertexAContactPointFromFeaturePointCache(hkProcessCdPoint_s0110_b3a0& cp, const hkFeatureContactPoint_s0110_b3a0& fcp, const hkFeaturePointCache& fpp) const;   // 0x01108b80
    void edgeEdgeContactPointFromFeaturePointCache(hkProcessCdPoint_s0110_b3a0& cp, const hkFeatureContactPoint_s0110_b3a0& fcp, const hkFeaturePointCache& fpp) const;      // 0x01108c30
    int  checkIntersection(const hkVector4_s0110_b3a0& tolerance4) const;                                                     // 0x01109460
    int  findClosestPoint(hkBoxBoxManifold_s0110_b3a0& manifold, hkFeatureContactPoint_s0110_b3a0& fcp, hkFeaturePointCache& fpp) const;   // 0x0110ad70
    void tryToAddPointFaceA(hkBoxBoxManifold_s0110_b3a0& manifold, hkFeatureContactPoint_s0110_b3a0 fcp, uint16_t edgeMask, hkReal minDist) const;   // 0x01108d00
    void tryToAddPointFaceB(hkBoxBoxManifold_s0110_b3a0& manifold, hkFeatureContactPoint_s0110_b3a0 fcp, uint16_t edgeMask, hkReal minDist) const;   // 0x011090b0
    void addAdditionalEdges(hkBoxBoxManifold_s0110_b3a0& manifold, int edgeA, int edgeB, int otherA, int otherB,
                            const hkVector4_s0110_b3a0& normalInA, const hkVector4_s0110_b3a0& normalInB, hkReal minDist) const;      // 0x0110ac90
    void checkCompleteness(hkBoxBoxManifold_s0110_b3a0& manifold, int maskA, int maskB) const;                              // 0x01108550

    const hkCdBody_s0110_b3a0*           m_bodyA;        // +0x00
    const hkCdBody_s0110_b3a0*           m_bodyB;        // +0x04
    const hkCollisionInput_s0110_b3a0*   m_env;          // +0x08
    hkContactMgr_s0110_b3a0*             m_contactMgr;   // +0x0c
    hkProcessCollisionOutput* m_result;       // +0x10
    const hkTransform_s0110_b3a0*        m_wTa;          // +0x14
    const hkTransform_s0110_b3a0*        m_wTb;          // +0x18
    uint32_t                  m_pad1c;
    hkRotation_s0110_b3a0                m_aRb;          // +0x20
    hkVector4_s0110_b3a0                 m_aTb;          // +0x50
    hkVector4_s0110_b3a0                 m_radiusA;      // +0x60
    hkVector4_s0110_b3a0                 m_radiusB;      // +0x70
    hkVector4_s0110_b3a0                 m_tolerance4;   // +0x80
    hkVector4_s0110_b3a0                 m_boundaryToleranceA;   // +0x90
    hkVector4_s0110_b3a0                 m_boundaryToleranceB;   // +0xa0
    hkReal                    m_tolerance;    // +0xb0
    uint32_t                  m_padb4[3];
    hkVector4_s0110_b3a0                 m_dinA;         // +0xc0
    hkVector4_s0110_b3a0                 m_dinB;         // +0xd0
};
static __forceinline void calcManifoldNormalB(hkBoxBoxManifold_s0110_b3a0& manifold, const hkRotation_s0110_b3a0& aRb)
{
    setRotatedInverseDir(manifold.m_manifoldNormalB, aRb, manifold.m_manifoldNormalA);
    *reinterpret_cast<uint32_t*>(&manifold.m_manifoldNormalB.w) = 0;
    manifold.m_manifoldNormalInitialized.m_bool = true;
}
// ---- items of slice s0110b3a0 end

// ---- items of slice s0110dd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
class __declspec(align(16)) hkVector4_s0110_dd70 {
public:
    hkReal x, y, z, w;
};
static __forceinline void hkCopy(hkVector4_s0110_dd70& d, const hkVector4_s0110_dd70& s) { d.x = s.x; d.y = s.y; d.z = s.z; d.w = s.w; }
class hkTransform_s0110_dd70 {
public:
    hkVector4_s0110_dd70 m_col0, m_col1, m_col2;   // rotation columns
    hkVector4_s0110_dd70 m_translation;
};
class hkConvexShape;
struct hkGskOut {
    hkVector4_s0110_dd70 m_normal;   // +0
    hkVector4_s0110_dd70 m_point;    // +0x10
    hkReal m_dist;        // +0x20
    hkReal m_half;        // +0x24
};
enum hkGskStatus { HK_GSK_OK = 0 };
hkGskStatus hkCalculatePenetrationDepth(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                                        const hkTransform_s0110_dd70& aTb, hkReal tolerance,
                                        hkVector4_s0110_dd70* simplexA, hkVector4_s0110_dd70* simplexB,
                                        hkVector4_s0110_dd70* diffs, int* dim, hkGskOut& out);   // 0x01121e10
class hkCollideTriangleUtil_s0110_dd70 {
public:
    struct ClosestLineSegLineSegResult {
        hkVector4_s0110_dd70 m_closestPointA;
        hkVector4_s0110_dd70 m_closestPointB;
        hkVector4_s0110_dd70 m_closestAB;
        hkReal m_distanceSquared;
        hkReal m_t;
        hkReal m_u;
        hkReal m_pad;
    };
    static int closestLineSegLineSeg(const hkVector4_s0110_dd70& A, const hkVector4_s0110_dd70& dA, const hkVector4_s0110_dd70& B,
                                     const hkVector4_s0110_dd70& dB, ClosestLineSegLineSegResult& result);  // 0x01105940
};
static inline unsigned int hkVertexId(const hkVector4_s0110_dd70& v) { return *(const unsigned int*)&v.w & 0xc0ffffffu; }
static __forceinline void setTransformedPos_s0110_dd70(hkVector4_s0110_dd70& out, const hkTransform_s0110_dd70& t, const hkVector4_s0110_dd70& v) {
    const hkReal vx = v.x, vy = v.y, vz = v.z;
    hkReal rx = t.m_col0.x * vx; rx += t.m_col1.x * vy; rx += t.m_col2.x * vz; rx += t.m_translation.x;
    hkReal ry = t.m_col0.y * vx; ry += t.m_col1.y * vy; ry += t.m_col2.y * vz; ry += t.m_translation.y;
    hkReal rz = t.m_col0.z * vx; rz += t.m_col1.z * vy; rz += t.m_col2.z * vz; rz += t.m_translation.z;
    out.x = rx; out.y = ry; out.z = rz;
    out.w = 0.0f;
}
class hkGsk {
public:
    void handlePenetration(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                           const hkTransform_s0110_dd70& aTb);                                            // 0x0110dd70
protected:
    void reduceDimensionExtended();                                                            // 0x0110cec0

public:
    int m_dimA;                                     // +0x000
    int m_dimB;                                     // +0x004
    int m_maxDimA;                                  // +0x008
    int m_maxDimB;                                  // +0x00c
    bool m_doNotHandlePenetration;                  // +0x010
    int m_featureChange;                            // +0x014
    int m_pad18[2];
    hkVector4_s0110_dd70 m_verticesA[4];                       // +0x020
    hkVector4_s0110_dd70 m_verticesAinA[4];                    // +0x060 (unused here)
    hkVector4_s0110_dd70 m_verticesBinA[4];                    // +0x0a0
    hkVector4_s0110_dd70 m_verticesB[4];                       // +0x0e0
    hkVector4_s0110_dd70 m_closestPointDir;                    // +0x120
    hkCollideTriangleUtil_s0110_dd70::ClosestLineSegLineSegResult m_lineResult;   // +0x130
};
// ---- items of slice s0110dd70 end

// ---- items of slice s0110fa20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_0110e510();  // 0x110e510  hkGsk::getClosestFeature
extern "C" void FUN_0110cd00();  // 0x110cd00  hkTriangleUtil::sortFeatureIndices
struct GskFeatureQuery {
    signed char idx0;   // +0
    signed char idx1;   // +1
    signed char idx2;   // +2
    signed char idx3;   // +3
    int pad4;
    int pad8;
    int padC;
    int valid;          // +0x10 -> [esp+0x30]? used as the 0x110cd00 guard
};
static inline void* VSlot(void* obj, int byte_offset)
{
    return (*(void***)obj)[byte_offset / 4];
}
// ---- items of slice s0110fa20 end

// ---- items of slice s0110fe20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef hkUint16       hkContactPointId_s0110_fe20;
class __declspec(align(16)) hkVector4_s0110_fe20
{
public:
    float x, y, z, w;

    inline void setSub4(const hkVector4_s0110_fe20& a, const hkVector4_s0110_fe20& b)
    { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
    inline void setCross(const hkVector4_s0110_fe20& a, const hkVector4_s0110_fe20& b)
    {
        x = a.y * b.z - a.z * b.y;
        y = a.z * b.x - a.x * b.z;
        z = a.x * b.y - a.y * b.x;
        w = 0.0f;
    }
    inline hkReal dot3(const hkVector4_s0110_fe20& a) const { return x * a.x + y * a.y + z * a.z; }
    inline hkReal lengthSquared3() const { return x * x + y * y + z * z; }
    // (1-t)*a + t*b
    inline void setInterpolate4(const hkVector4_s0110_fe20& a, const hkVector4_s0110_fe20& b, hkReal t)
    {
        const hkReal s = 1.0f - t;
        x = s * a.x + t * b.x; y = s * a.y + t * b.y; z = s * a.z + t * b.z; w = s * a.w + t * b.w;
    }
    // this = a + b * r
    inline void setAddMul4(const hkVector4_s0110_fe20& a, const hkVector4_s0110_fe20& b, hkReal r)
    { x = b.x * r + a.x; y = b.y * r + a.y; z = b.z * r + a.z; w = b.w * r + a.w; }
    inline void setNeg4(const hkVector4_s0110_fe20& a) { x = -a.x; y = -a.y; z = -a.z; w = -a.w; }
    inline void mul4(hkReal r) { x *= r; y *= r; z *= r; w *= r; }
    // normalize the xyz part; a zero vector stays zero
    inline void normalize3IfNotZero()
    {
        const hkReal len2 = lengthSquared3();
        const hkReal inv = (len2 == 0.0f) ? 0.0f : 1.0f / (hkReal)sqrt(len2);
        mul4(inv);
    }
};
static inline int signMask4(hkReal x, hkReal y, hkReal z, hkReal w)
{
    return ((x < 0.0f) << 3) | ((y < 0.0f) << 2) | ((z < 0.0f) << 1) | (int)(w < 0.0f);
}
struct hkGskManifold
{
    struct ContactPoint
    {
        hkUchar          m_dimA;
        hkUchar          m_dimB;
        hkContactPointId_s0110_fe20 m_id;
        hkUchar          m_vert[4];   // byte offsets (index * sizeof(hkVector4)) into the work vertices
    };
    hkUchar      m_numVertsA;
    hkUchar      m_numVertsB;
    hkUchar      m_numContactPoints;
    ContactPoint m_contactPoints[4];
    hkUchar      m_padding[32];       // followed by the vertex id array
};
struct hkGskManifoldWork
{
    hkVector4_s0110_fe20 m_vertices[16];   // +0x000 vertices of A then B (world space)
    hkVector4_s0110_fe20 m_masterNormal;   // +0x100
    hkReal    m_radiusA;        // +0x110
    hkReal    m_radiusB;        // +0x114
    hkReal    m_keepContact;    // +0x118
    hkReal    m_radiusSumSqrd;  // +0x11c
};
struct hkProcessCdPoint_s0110_fe20
{
    hkVector4_s0110_fe20        m_position;           // +0x00
    hkVector4_s0110_fe20        m_separatingNormal;   // +0x10 (w = distance)
    hkContactPointId_s0110_fe20 m_contactPointId;     // +0x20
    hkUint16         m_pad[7];
};
struct hkProcessCollisionOutput_s0110_fe20
{
    hkProcessCdPoint_s0110_fe20* m_firstFreeContactPoint;   // +0x0
};
class hkContactMgr_s0110_fe20
{ public:
    virtual void v0();
    virtual void v1();
    virtual void addContactPoint();
    virtual void reserveContactPoints();
    virtual void removeContactPoint(hkContactPointId_s0110_fe20 id);   // +0x10
};
void __fastcall hkGskManifold_removeUnusedVertices(hkGskManifold* manifold);
static inline const hkVector4_s0110_fe20& vertexAt(const hkGskManifoldWork& work, int byteOffset)
{
    return *(const hkVector4_s0110_fe20*)((const char*)&work + byteOffset);
}
static inline void memCpy4(void* dst, const void* src, int numWords)
{
    hkUint32* d = (hkUint32*)dst;
    const hkUint32* s = (const hkUint32*)src;
    for (int i = numWords - 1; i >= 0; i--)
        *d++ = *s++;
}
// ---- items of slice s0110fe20 end

// @ 0x01100cf0
int __cdecl FUN_01100cf0(hkCollisionDispatcher_s0110_0cf0* dispatcher, int typeA, int typeB)
{
    Agent3Funcs funcs;
    funcs.m_updateFilterFunc       = 0;
    funcs.m_invalidateTimFunc      = 0;
    funcs.m_warpTimeFunc           = 0;
    funcs.m_ignoreSymmetricVersion = 0;
    funcs.m_createFunc             = &g_hkPredGskAgent3_createFunc;
    funcs.m_processFunc            = &g_hkPredGskAgent3_processFunc;
    funcs.m_sepNormalFunc          = &g_hkPredGskAgent3_sepNormalFunc;
    funcs.m_cleanupFunc            = &g_hkPredGskAgent3_cleanupFunc;
    funcs.m_removePointFunc        = &g_hkPredGskAgent3_removePointFunc;
    funcs.m_commitPotentialFunc    = &g_hkPredGskAgent3_commitPotentialFunc;
    funcs.m_createZombieFunc       = &g_hkPredGskAgent3_createZombieFunc;
    funcs.m_destroyFunc            = &g_hkPredGskAgent3_destroyFunc;
    funcs.m_isPredictive           = 1;
    return dispatcher->registerAgent3(funcs, typeA, typeB);
}

// @ 0x011013f0
void hkMoppSphereVirtualMachine::querySphere(const hkMoppCode* code, const hkSphere& sphere, void* primitives)
{
    const unsigned char* data = code->m_data;
    m_primitives = primitives;

    float f = (sphere.x - code->m_offsetX) * code->m_scale;
    m_lo[0] = (int)f - 1;
    f = (sphere.y - code->m_offsetY) * code->m_scale;
    m_lo[1] = (int)f - 1;
    f = (sphere.z - code->m_offsetZ) * code->m_scale;
    m_lo[2] = (int)f - 1;
    f = sphere.radius * code->m_scale;
    int span = (int)f + 2;
    m_hi0 = span;

    hkMoppSphereState st;
    st.m_minHi0    = (int16_t)(m_lo[0] >> 16);
    st.m_minHi1    = (int16_t)(m_lo[1] >> 16);
    st.m_minHi2    = (int16_t)(m_lo[2] >> 16);
    st.m_spanHi    = (span >> 16) + 1;
    st.m_scratch0  = 0;
    st.m_scratch1  = 0;
    st.m_scratch2  = 0;
    st.m_scratch3  = 0;
    st.m_shift     = 0x10;
    st.m_zero      = 0;

    querySphereRec(&st, data);
}

// @ 0x01101c00
void hkMoppObbVirtualMachine::queryObb(const hkMoppCode_s0110_1c00* code, const hkTransform_s0110_1c00& transform, const hkVector4_s0110_1c00& extent, float radius, hkArray<hkMoppPrimitiveInfo>* primitives)
{
    m_primitives = primitives;
    m_code = code;

    float hx = extent.x;
    float hy = extent.y;
    float hz = extent.z;
    float ex = ((fabsf(hy * transform.m_col1[0]) + fabsf(hx * transform.m_col0[0]))
                + fabsf(hz * transform.m_col2[0])) + radius;
    float ey = ((fabsf(hy * transform.m_col1[1]) + fabsf(hx * transform.m_col0[1]))
                + fabsf(hz * transform.m_col2[1])) + radius;
    float ez = ((fabsf(hy * transform.m_col1[2]) + fabsf(hx * transform.m_col0[2]))
                + fabsf(hz * transform.m_col2[2])) + radius;

    float tx = transform.m_translation.x;
    float ty = transform.m_translation.y;
    float tz = transform.m_translation.z;

    m_lo[0] = ToInt(((tx - ex) - code->m_offsetX) * code->m_scale) - 1;
    m_hi[0] = ToInt(((tx + ex) - code->m_offsetX) * code->m_scale) + 1;
    m_lo[1] = ToInt(((ty - ey) - code->m_offsetY) * code->m_scale) - 1;
    m_hi[1] = ToInt(((ty + ey) - code->m_offsetY) * code->m_scale) + 1;
    m_lo[2] = ToInt(((tz - ez) - code->m_offsetZ) * code->m_scale) - 1;
    m_hi[2] = ToInt(((tz + ez) - code->m_offsetZ) * code->m_scale) + 1;

    hkMoppObbState state;
    state.m_hi[0] = (m_hi[0] >> 16) + 1;
    state.m_hi[1] = (m_hi[1] >> 16) + 1;
    state.m_hi[2] = (m_hi[2] >> 16) + 1;
    state.m_lo[0] = m_lo[0] >> 16;
    state.m_lo[1] = m_lo[1] >> 16;
    state.m_lo[2] = m_lo[2] >> 16;
    state.m_org[0] = 0;
    state.m_org[1] = 0;
    state.m_org[2] = 0;
    state.m_primOffset = 0;
    state.m_shift = 0;
    state.m_reg[0] = 0;

    queryObbRecurse(&state, code->m_data);
}

// @ 0x01102010
void hkMoppLongRayVirtualMachine::queryRay(hkMoppState* st, const uint8_t* p, float* ray)
{
    hkMoppState local;
    float rayCopy[8];
    char textBuf[0x200];
    float a, b, lo, hi;
    int axis;
    uint32_t skipHi, skipLo;
    const uint8_t* next;
    float u, t;
    int ax, hiIdx;
    float fa, fb, d, c[8];

    if (!g_hkKeycodeOk) {
        g_hkKeycodeOk = hkSolverCheckKeycode(4);
        if (!g_hkKeycodeOk) return;
    }

    for (;;) {
        uint32_t op = p[0];
        axis = 999;

        switch (op) {
        case 0:
            return;
        case 1: case 2: case 3: case 4: {
            float x = (float)p[1], y = (float)p[2], z = (float)p[3];
            float f = (float)(1 << (op & 0x1f));
            ray[0] = ray[0] - x; ray[1] = ray[1] - y; ray[2] = ray[2] - z;
            ray[4] = ray[4] - x; ray[5] = ray[5] - y; ray[6] = ray[6] - z;
            ray[0] = f * ray[0]; ray[1] = f * ray[1]; ray[2] = f * ray[2]; ray[3] = f * ray[3];
            ray[4] = f * ray[4]; ray[5] = f * ray[5]; ray[6] = f * ray[6]; ray[7] = f * ray[7];
            local.m_off[0] = (x + st->m_off[0]) * f;
            local.m_off[1] = (y + st->m_off[1]) * f;
            local.m_off[2] = (z + st->m_off[2]) * f;
            local.m_off[3] = st->m_off[3] * f;
            local.m_shift = st->m_shift + (int)op;
            p += 4;
            local.m_scale = f * st->m_scale;
            local.m_prop[0] = st->m_prop[0];
            local.m_primOffset = st->m_primOffset;
            st = &local;
            continue;
        }
        case 5: p += p[1] + 2; continue;
        case 6: p += (uint32_t)p[1] * 0x100 + p[2] + 3; continue;
        case 7: p += (uint32_t)((p[1] << 8) | p[2]) * 0x100 + p[3] + 4; continue;
        case 9: {
            uint32_t v = p[1];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset += v;
            p += 2;
            continue;
        }
        case 10: {
            uint32_t v = (p[1] << 8) | p[2];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset += v;
            p += 3;
            continue;
        }
        case 0xb: {
            uint32_t v = (((p[1] << 8) | p[2]) << 8 | p[3]) << 8 | p[4];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset = v;
            p += 5;
            continue;
        }
        case 0x10: case 0x11: case 0x12:
            axis = op - 0x10;
            lo = (float)p[1]; hi = (float)p[2];
            a = ray[axis]; b = ray[op - 0xc];
            goto splitCommon;
        case 0x13:
            lo = (float)(p[1] << 1); hi = (float)(p[2] << 1);
            a = ray[2] + ray[1]; b = ray[6] + ray[5];
            goto splitCommon;
        case 0x14:
            lo = (float)(int)(p[1] * 2 - 0xff); hi = (float)(int)(p[2] * 2 - 0xff);
            a = ray[1] - ray[2]; b = ray[5] - ray[6];
            goto splitCommon;
        case 0x15:
            lo = (float)(p[1] << 1); hi = (float)(p[2] << 1);
            a = ray[2] + ray[0]; b = ray[6] + ray[4];
            goto splitCommon;
        case 0x16:
            lo = (float)(int)(p[1] * 2 - 0xff); hi = (float)(int)(p[2] * 2 - 0xff);
            a = ray[0] - ray[2]; b = ray[4] - ray[6];
            goto splitCommon;
        case 0x17:
            lo = (float)(p[1] << 1); hi = (float)(p[2] << 1);
            a = ray[1] + ray[0]; b = ray[5] + ray[4];
            goto splitCommon;
        case 0x18:
            lo = (float)(int)(p[1] * 2 - 0xff); hi = (float)(int)(p[2] * 2 - 0xff);
            a = ray[0] - ray[1]; b = ray[4] - ray[5];
            goto splitCommon;
        case 0x19:
            lo = (float)(p[1] * 3); hi = (float)(p[2] * 3);
            a = (ray[2] + ray[1]) + ray[0]; b = (ray[6] + ray[5]) + ray[4];
            goto splitCommon;
        case 0x1a:
            lo = (float)(int)((p[1] - 0x55) * 3); hi = (float)(int)((p[2] - 0x55) * 3);
            a = (ray[1] + ray[0]) - ray[2]; b = (ray[5] + ray[4]) - ray[6];
            goto splitCommon;
        case 0x1b:
            lo = (float)(int)((p[1] - 0x55) * 3); hi = (float)(int)((p[2] - 0x55) * 3);
            a = (ray[0] - ray[1]) + ray[2]; b = (ray[4] - ray[5]) + ray[6];
            goto splitCommon;
        case 0x1c:
            lo = (float)(int)((p[1] - 0xaa) * 3); hi = (float)(int)((p[2] - 0xaa) * 3);
            a = (ray[0] - ray[1]) - ray[2]; b = (ray[4] - ray[5]) - ray[6];
            goto splitCommon;
        case 0x20: case 0x21: case 0x22:
            skipHi = p[2];
            axis = op - 0x20;
            next = p + 3;
            hi = (float)p[1];
            lo = hi + 1.0f;
            a = ray[axis]; b = ray[op - 0x1c];
            skipLo = 0;
            goto splitBody;
        case 0x23: case 0x24: case 0x25:
            lo = (float)p[1]; hi = (float)p[2];
            axis = op - 0x23;
            a = ray[axis];
            next = p + 7;
            b = ray[op - 0x1f];
            skipLo = (p[3] << 8) | p[4];
            skipHi = (p[5] << 8) | p[6];
            goto splitBody;
        case 0x26: case 0x27: case 0x28:
            ax = op - 0x26;
            a = (float)p[1];
            b = (float)p[2];
            p += 3;
            goto planeClip;
        case 0x29: case 0x2a: case 0x2b:
            ax = op - 0x29;
            a = ((float)(int)(((p[1] << 8 | p[2]) << 8) | p[3]) * m_invScale) * st->m_scale - ((float*)st)[ax];
            b = ((float)(int)(((p[4] << 8 | p[5]) << 8) | p[6]) * m_invScale) * st->m_scale - ((float*)st)[ax];
            p += 7;
            goto planeClip;
        case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
        case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
            skipHi = op - 0x30;
            goto leaf;
        case 0x50: skipHi = p[1]; goto leaf;
        case 0x51: skipHi = (p[1] << 8) | p[2]; goto leaf;
        case 0x52: skipHi = ((p[1] << 8) | p[2]) << 8 | p[3]; goto leaf;
        case 0x53: skipHi = p[4] + (uint32_t)((p[1] << 8) | p[2]) * 0x10000 + (uint32_t)p[3] * 0x100; goto leaf;
        case 0x60: case 0x61: case 0x62: case 0x63:
            local.m_prop[op - 0x60] = p[1];
            p += 2;
            goto propDone;
        case 0x64: case 0x65: case 0x66: case 0x67:
            local.m_prop[op - 0x64] = (p[1] << 8) | p[2];
            p += 3;
            goto propDone;
        case 0x68: case 0x69: case 0x6a: case 0x6b:
            local.m_prop[op - 0x68] = (((p[1] << 8 | p[2]) << 8) | p[3]) << 8 | p[4];
            p += 5;
        propDone:
            {
                int keep = local.m_prop[0];
                if (st != &local) { local.copyFrom(*st); st = &local; }
                local.m_prop[0] = keep;
            }
            continue;
        default: {
            hkOstream_s0110_2010 os(textBuf, 0x200, true);
            os << "Unknown command - This mopp data has been corrupted (check for memory trashing), or an hkMoppBvTreeShape has been pointed at invalid mopp data.\n";
            hkError::s_instance->message(3, 0x1298fedd, textBuf, ".\\collide\\mopp\\machine\\hkMoppLongRayVirtualMachine.cpp", 0x1c9);
            continue;
        }
        }

        // ---- ops 0x26..0x2b: clip the ray against a plane slab ----
    planeClip:
        fa = ray[ax]; fb = ray[ax + 4];
        if (fb <= fa) {
            if (fa < a) return;
            if (b < fb) return;
            hiIdx = 1;
        } else {
            if (fb < a) return;
            if (b < fa) return;
            hiIdx = 0;
        }
        for (int i = 0; i < 8; i++) c[i] = ray[i];
        d = fa - b;
        if (d * (fb - b) < 0.0f) {
            t = d / (d - (fb - b));
            u = 1.0f - t;
            ray[hiIdx * -4 + 4] = c[4] * t + c[0] * u;
            ray[hiIdx * -4 + 5] = c[1] * u + c[5] * t;
            ray[hiIdx * -4 + 6] = c[6] * t + c[2] * u;
            ray[hiIdx * -4 + 7] = c[7] * t + c[3] * u;
        }
        fa = fa - a;
        if (fa * (fb - a) < 0.0f) {
            float* q = ray + hiIdx * 4;
            t = fa / (fa - (fb - a));
            u = 1.0f - t;
            q[0] = c[4] * t + c[0] * u;
            q[1] = c[5] * t + c[1] * u;
            q[2] = c[6] * t + c[2] * u;
            q[3] = c[7] * t + c[3] * u;
        }
        continue;

        // ---- leaf: report primitive ----
    leaf:
        {
            int key = (int)skipHi + st->m_primOffset;
            hkBool_s0110_2010 enabled;
            if (m_rayInput.m_rayShapeCollectionFilter) {
                if (!m_rayInput.m_rayShapeCollectionFilter->isCollisionEnabled(m_rayInput, *m_shapeCollection, key)) return;
            }
            char shapeBuf[0x100];
            const hkShape_s0110_2010* shape = m_shapeCollection->getChildShape(key, shapeBuf);
            if (m_output) {
                if (!shape->castRay(m_rayInput, *m_output)) return;
                m_hit = 1;
                m_hitFraction = m_output->m_hitFraction;
                m_output->m_shapeKey = key;
                return;
            }
            hkCdBody_s0110_2010 body;
            body.m_shape = shape;
            body.m_shapeKey = key;
            body.m_motion = ((const hkCdBodyMotionHolder*)m_cdBody)->m_motion;
            body.m_parent = m_cdBody;
            shape->castRayWithCollector(m_rayInput, body, *m_collector);
            m_hitFraction = m_collector->m_earlyOutHitFraction;
            return;
        }

        // ---- ops 0x10..0x1c: tail shared by the split ops ----
    splitCommon:
        skipHi = p[3];
        next = p + 4;
        skipLo = 0;
        // fallthrough
    splitBody:
        if (hi <= b || hi <= a) {
            p = next + skipHi;
            if (a <= lo || b <= lo) {
                float cal = a - lo;      // local_2c4
                float cah = a - hi;      // local_2bc
                float cbl = b - lo;      // local_2b4
                float cbh = b - hi;
                for (int i = 0; i < 8; i++) rayCopy[i] = ray[i];
                if (cbl <= cal) {
                    if (cbh * cah < 0.0f) {
                        t = cah / (cah - cbh);
                        u = 1.0f - t;
                        rayCopy[4] = t * ray[4] + u * ray[0];
                        rayCopy[5] = u * ray[1] + t * ray[5];
                        rayCopy[6] = u * ray[2] + t * ray[6];
                        rayCopy[7] = u * ray[3] + t * ray[7];
                    }
                    queryRay(st, p, rayCopy);
                    if (cbl * cal < 0.0f) {
                        t = cal / (cal - cbl);
                        u = 1.0f - t;
                        ray[0] = u * ray[0] + t * ray[4];
                        ray[1] = u * ray[1] + t * ray[5];
                        ray[2] = u * ray[2] + t * ray[6];
                        ray[3] = u * ray[3] + t * ray[7];
                    }
                    if (m_hitFraction < 1.0f) {
                        float f = m_hitFraction, g = 1.0f - f;
                        float x = f * m_rayInput.m_to[0] + g * m_rayInput.m_from[0];
                        float y = f * m_rayInput.m_to[1] + g * m_rayInput.m_from[1];
                        float z = f * m_rayInput.m_to[2] + g * m_rayInput.m_from[2];
                        float wv = f * m_rayInput.m_to[3] + g * m_rayInput.m_from[3];
                        const hkMoppCodeRef* c = m_code;
                        ray[4] = x - c->m_offset[0];
                        ray[5] = y - c->m_offset[1];
                        ray[6] = z - c->m_offset[2];
                        ray[7] = wv - c->m_offset[3];
                        float s = st->m_scale;
                        ray[4] = s * ray[4]; ray[5] = s * ray[5]; ray[6] = s * ray[6]; ray[7] = s * ray[7];
                        ray[4] = ray[4] - st->m_off[0]; ray[5] = ray[5] - st->m_off[1];
                        ray[6] = ray[6] - st->m_off[2]; ray[7] = ray[7] - st->m_off[3];
                        if (axis < 3 && lo < ray[axis + 4]) return;
                    }
                    p += skipLo - skipHi;
                } else {
                    if (cbl * cal < 0.0f) {
                        t = cal / (cal - cbl);
                        u = 1.0f - t;
                        rayCopy[4] = t * ray[4] + u * ray[0];
                        rayCopy[5] = u * ray[1] + t * ray[5];
                        rayCopy[6] = u * ray[2] + t * ray[6];
                        rayCopy[7] = u * ray[3] + t * ray[7];
                    }
                    queryRay(st, p + (skipLo - skipHi), rayCopy);
                    if (cbh * cah < 0.0f) {
                        t = cah / (cah - cbh);
                        u = 1.0f - t;
                        ray[0] = t * ray[4] + u * ray[0];
                        ray[1] = u * ray[1] + t * ray[5];
                        ray[2] = u * ray[2] + t * ray[6];
                        ray[3] = u * ray[3] + t * ray[7];
                    }
                    if (m_hitFraction < 1.0f) {
                        float f = m_hitFraction, g = 1.0f - f;
                        float x = f * m_rayInput.m_to[0] + g * m_rayInput.m_from[0];
                        float y = f * m_rayInput.m_to[1] + g * m_rayInput.m_from[1];
                        float z = f * m_rayInput.m_to[2] + g * m_rayInput.m_from[2];
                        float wv = f * m_rayInput.m_to[3] + g * m_rayInput.m_from[3];
                        const hkMoppCodeRef* c = m_code;
                        ray[4] = x - c->m_offset[0];
                        ray[5] = y - c->m_offset[1];
                        ray[6] = z - c->m_offset[2];
                        ray[7] = wv - c->m_offset[3];
                        float s = st->m_scale;
                        ray[4] = s * ray[4]; ray[5] = s * ray[5]; ray[6] = s * ray[6]; ray[7] = s * ray[7];
                        ray[4] = ray[4] - st->m_off[0]; ray[5] = ray[5] - st->m_off[1];
                        ray[6] = ray[6] - st->m_off[2]; ray[7] = ray[7] - st->m_off[3];
                        if (axis < 3 && ray[axis + 4] < hi) return;
                    }
                }
            }
        } else {
            p = next + skipLo;
        }
    }
}

// @ 0x01102fc0
hkBool_s0110_2fc0 hkMoppLongRayVirtualMachine_s0110_2fc0::queryLongRay(const hkShapeCollection* collection, const hkMoppCode_s0110_2fc0* code, const hkShapeRayCastInput_s0110_2fc0& input, hkShapeRayCastOutput& output)
{
    m_output = &output;
    m_shapeCollection = collection;
    m_hitFraction = 1.0f;                                   // 0x3f800000
    m_code = code;
    float zero[4] = { 0.0f, 0.0f, 0.0f, 0.0f };             // esp+0x30..0x3c (ints 0)
    uint32_t zeroBits[4] = { 0, 0, 0, 0 };
    (void)zero;
    m_invScale = 1.0f / code->m_offset.w;                   // fdiv, rounded to float on fstp
    float s = code->m_offset.w * HK_MOPP_RANGE_SCALE;       // esp+0x44
    // Ray in MOPP space: (v - offset) * (scale * 2^-16), 4 components each for from and to.
    // X87-PRECISION: for from.x and from.y the (v-offset) difference stays in an 80-bit register and is multiplied
    // by s before being stored; every other component is stored to float after the subtraction and re-loaded.
    float fromTo[8];
    fromTo[2] = input.m_from.z - code->m_offset.z;
    fromTo[3] = input.m_from.w - code->m_offset.w;
    fromTo[4] = input.m_to.x - code->m_offset.x;
    fromTo[5] = input.m_to.y - code->m_offset.y;
    fromTo[6] = input.m_to.z - code->m_offset.z;
    fromTo[7] = input.m_to.w - code->m_offset.w;
    fromTo[0] = (input.m_from.x - code->m_offset.x) * s;    // X87-PRECISION: unrounded difference
    fromTo[1] = (input.m_from.y - code->m_offset.y) * s;    // X87-PRECISION: unrounded difference
    fromTo[2] = fromTo[2] * s;
    fromTo[3] = fromTo[3] * s;
    fromTo[4] = fromTo[4] * s;
    fromTo[5] = fromTo[5] * s;
    fromTo[6] = fromTo[6] * s;
    fromTo[7] = fromTo[7] * s;
    m_rayInput = input;                                     // 10 dwords
    m_hit.m_bool = 0;
    queryRay((const hkVector4_s0110_2fc0*)zeroBits, code->m_data, fromTo);
    return m_hit;
}

// @ 0x01103140
void hkMoppLongRayVirtualMachine_s0110_2fc0::queryLongRay(const hkShapeCollection* collection, const hkMoppCode_s0110_2fc0* code, const hkShapeRayCastInput_s0110_2fc0& input, const hkCdBody_s0110_2fc0& body, hkRayHitCollector& collector)
{
    m_shapeCollection = collection;
    m_cdBody = &body;
    m_collector = &collector;
    m_output = 0;
    m_hitFraction = collector.m_earlyOutHitFraction;
    m_code = code;
    uint32_t zeroBits[4] = { 0, 0, 0, 0 };
    m_invScale = 1.0f / code->m_offset.w;
    float s = code->m_offset.w * HK_MOPP_RANGE_SCALE;
    float fromTo[8];
    fromTo[2] = input.m_from.z - code->m_offset.z;
    fromTo[3] = input.m_from.w - code->m_offset.w;
    fromTo[4] = input.m_to.x - code->m_offset.x;
    fromTo[5] = input.m_to.y - code->m_offset.y;
    fromTo[6] = input.m_to.z - code->m_offset.z;
    fromTo[7] = input.m_to.w - code->m_offset.w;
    fromTo[0] = (input.m_from.x - code->m_offset.x) * s;    // X87-PRECISION: unrounded difference
    fromTo[1] = (input.m_from.y - code->m_offset.y) * s;    // X87-PRECISION: unrounded difference
    fromTo[2] = fromTo[2] * s;
    fromTo[3] = fromTo[3] * s;
    fromTo[4] = fromTo[4] * s;
    fromTo[5] = fromTo[5] * s;
    fromTo[6] = fromTo[6] * s;
    fromTo[7] = fromTo[7] * s;
    m_rayInput = input;
    m_hit.m_bool = 0;
    queryRay((const hkVector4_s0110_2fc0*)zeroBits, code->m_data, fromTo);
}

// @ 0x01103330
hkShapeKeyList::hkShapeKeyList(hkShapeContainer* container)
{
    m_referenceCount = 1;
    m_container = container;
    m_numKeys = container->getNumChildShapes();
}

// @ 0x01103670
void* hkMoppSettings::build(hkMoppSource* src, void* buffer, int bufferSize)
{
    int n = src->getNumPrimitives() + m_a.m_i1;
    hkMoppArena arena;
    arena.init(n * 12);
    hkMoppObj2 obj2;
    obj2.init(&m_b);
    hkMoppObj3 obj3;
    obj3.init(&m_c0, &arena, src);
    int bytes = (src->getNumPrimitives() + 0x1b400 + m_a.m_i1) * 16;
    uint8_t* mem = (uint8_t*)buffer;
    if (buffer == 0 || bufferSize < bytes) {
        mem = (uint8_t*)hkMemory::s_instance->allocate(bytes, 0x25);
    }
    arena.m_mid = mem + n * 16;                 // iStack_f8
    arena.m_end = arena.m_mid + 0xf8000;        // iStack_f4
    arena.m_begin = mem;                        // iStack_fc
    src->setScratchBuffer(mem);
    obj2.m_sub.finalize();
    void* code = obj2.m_sub.compile(src, &obj2, &obj3, &m_a, &arena);
    obj2.m_sub.destroy();
    if (mem != buffer) {
        hkMemory::s_instance->deallocate(mem);
    }
    m_result = code;                            // this[0]
    void* record = ((hkMoppArenaCounter*)&arena.m_counter)->getRecord();
    obj3.attach(code, (char*)record + 0x10);
    obj3.destroy();
    return record;
}

// @ 0x01103850
void __cdecl hkAgent1nMachine_InvalidateTim(hkAgent1nTrack& track, const hkCollisionInput_s0110_2fc0& input)
{
    hkAgent1nSector* sector = track.m_sectorsData[0];
    uint8_t* p = sector->m_data;
    uint8_t* end = (uint8_t*)sector + sector->m_bytesAllocated + 0x10;
    int sectorIndex = 1;
    for (;;) {
        uint8_t* entryBase = p;
        uint8_t type = *p;
        if (type <= 6) {
            void* agentData = 0;
            bool call = false;
            switch (type) {
            case 0:                                            // padding entry
                p += p[3];
                break;
            case 1:                                            // end of track
                return;
            case 2: case 3: case 6:
                agentData = p + 0x10;
                call = true;
                break;
            case 4: case 5:                                    // entries with a TIM: reset it
                *(float*)(p + 0xc) = -1.0f;                    // 0xbf800000
                ((uint32_t*)(p + 0x10))[3] = 0;
                ((uint32_t*)(p + 0x10))[2] = 0;
                ((uint32_t*)(p + 0x10))[1] = 0;
                ((uint32_t*)(p + 0x10))[0] = 0;
                agentData = p + 0x20;
                call = true;
                break;
            }
            if (call) {
                const hkCollisionDispatcher_s0110_2fc0* dispatcher = input.m_dispatcher;
                p += p[3];
                hkAgent3InvalidateTimFunc f = dispatcher->m_agent3Func[entryBase[1]].m_invalidateTimFunc;
                if (f) f((hkAgent1nMachineEntry*)entryBase, agentData, &input);
            }
        }
        // types above 6 are not advanced (the binary loops on the same entry)
        if (p >= end) {
            sector = track.m_sectorsData[sectorIndex++];
            end = (uint8_t*)sector + sector->m_bytesAllocated + 0x10;
            p = sector->m_data;
        }
    }
}

// @ 0x01103a10
void hkAgent3Input_setAtTime(hkAgent3Input* out, const hkAgent3Source* src, hkAgent3Scratch* scratch)
{
    hkSweptTransformUtil::lerp2(src->m_bodyA->m_motion->m_sweptTransform, src->m_input->m_stepTime, scratch->m_transformA);
    hkSweptTransformUtil::lerp2(src->m_bodyB->m_motion->m_sweptTransform, src->m_input->m_stepTime, scratch->m_transformB);
    out->m_bodyA = &scratch->m_bodyA;
    out->m_bodyB = &scratch->m_bodyB;
    out->m_contactMgr = src->m_contactMgr;
    out->m_input = src->m_input;
    scratch->m_bodyA.m_shape = src->m_bodyA->m_shape;
    scratch->m_bodyA.m_shapeKey = src->m_bodyA->m_shapeKey;
    scratch->m_bodyA.m_parent = src->m_bodyA;
    scratch->m_bodyA.m_motion = (const hkMotionState*)&scratch->m_transformA;
    scratch->m_bodyB.m_parent = src->m_bodyB;
    scratch->m_bodyB.m_motion = (const hkMotionState*)&scratch->m_transformB;
    out->m_aTb.setMulInverseMul(scratch->m_transformA, scratch->m_transformB);
}

// @ 0x01103aa0
void hkAgent3ProcessInput_setFlipped(hkAgent3ProcessInput* dst, const hkAgent3ProcessInput* src)
{
    dst->m_bodyA = src->m_bodyB;
    dst->m_bodyB = src->m_bodyA;
    dst->m_input = src->m_input;
    dst->m_contactMgr = src->m_contactMgr;
    dst->m_linearTimInfo.x = -src->m_linearTimInfo.x;
    dst->m_linearTimInfo.y = -src->m_linearTimInfo.y;
    dst->m_linearTimInfo.z = -src->m_linearTimInfo.z;
    dst->m_linearTimInfo.w = src->m_linearTimInfo.w;
    dst->m_aTb.setInverse(src->m_aTb);
}

// @ 0x01103b50
void* __cdecl hkAgent1nMachine_UpdateShapeCollectionFilterVisitor(hkAgent1nMachine_VisitorInput& vin, hkAgent1nMachineKeyedEntry* entry, void* agentData)
{
    const hkCollisionInput_s0110_2fc0* input = vin.m_input;
    hkBool_s0110_2fc0 enabled = input->m_filter->isCollisionEnabled(*input, *vin.m_bodyA, *vin.m_collectionBodyB, vin.m_containerShapeB, entry->m_shapeKeyB);
    if (enabled == 0 && entry->m_streamCommand != 0) {
        // the filter now rejects this pair: destroy the agent in place; the next entry slides into this slot
        input->m_dispatcher->m_agent3Func[entry->m_agentType].m_destroyFunc(entry, agentData, vin.m_constraintOwner);
        return entry;
    }
    return (uint8_t*)entry + entry->m_size;
}

// @ 0x01106490
extern "C" void hkCollideCapsuleUtilManifoldCapsVsCaps(const hkVector4_s0110_6490* capsA, float capsARadius, const hkVector4_s0110_6490* capsB, float capsBRadius, hkContactPoint_s0110_6490* pointsOut)
{
    hkVector4_s0110_6490 dA;
    dA.x = Rounded((hkExtReal)capsA[1].x - capsA[0].x);
    dA.y = Rounded((hkExtReal)capsA[1].y - capsA[0].y);
    dA.z = Rounded((hkExtReal)capsA[1].z - capsA[0].z);
    dA.w = Rounded((hkExtReal)capsA[1].w - capsA[0].w);
    hkVector4_s0110_6490 dB;
    dB.x = Rounded((hkExtReal)capsB[1].x - capsB[0].x);
    dB.y = Rounded((hkExtReal)capsB[1].y - capsB[0].y);
    dB.z = Rounded((hkExtReal)capsB[1].z - capsB[0].z);
    dB.w = Rounded((hkExtReal)capsB[1].w - capsB[0].w);

    // orient segment A along B
    hkExtReal dAdBExact = dot3(dB, dA);
    float dAdB = Rounded(dAdBExact);
    hkVector4_s0110_6490 segA[2];
    if (dAdBExact < 0.0f) {
        dAdB = -dAdB;
        segA[0] = capsA[1];
        dA.x = -dA.x;
        dA.y = -dA.y;
        dA.z = -dA.z;
        dA.w = -dA.w;
        segA[1] = capsA[0];
    } else {
        segA[0] = capsA[0];
        segA[1] = capsA[1];
    }

    // --- closest points between the segments (hkLineSegmentUtil::closestLineSegLineSeg) ---------
    hkExtReal dx, dy, dz;   // unrounded
    dx = (hkExtReal)capsB[0].x - segA[0].x;
    dy = (hkExtReal)capsB[0].y - segA[0].y;
    dz = (hkExtReal)capsB[0].z - segA[0].z;
    float projA = Rounded(dx * dA.x + dz * dA.z + dy * dA.y);
    float projB = Rounded(dx * dB.x + dz * dB.z + dy * dB.y);
    float dA2 = Rounded(dot3(dA, dA));
    hkExtReal dB2Exact = dot3(dB, dB);
    float dB2 = Rounded(dB2Exact);
    float dA2dB2 = Rounded(dB2Exact * dA2);
    float dAdB2 = Rounded((hkExtReal)dAdB * dAdB);
    float det = Rounded(fabs((hkExtReal)dA2dB2 - dAdB2));
    hkExtReal numExact = (hkExtReal)dB2 * projA - (hkExtReal)projB * dAdB;
    float num = Rounded(numExact);

    int flags;
    hkExtReal t;   // unrounded
    if (det * det <= numExact * det) {
        t = 1.0f;
        flags = 1;
    } else if (num <= 0.0f) {
        t = 0.0f;
        flags = 2;
    } else if ((fabs((hkExtReal)dA2dB2) + dAdB2) * 9.5367432e-07f < det) {
        t = (hkExtReal)num / det;
        flags = 0;
    } else {
        t = 1.0f;
        flags = 1;
    }

    hkExtReal uExact = dAdB * t - projB;
    float u = Rounded(uExact);
    if (uExact >= dB2) {
        u = 1.0f;
        flags = 4;
    } else if (u <= 0.0f) {
        u = 0.0f;
        flags = 8;
    } else {
        u = Rounded((hkExtReal)u / dB2);
        goto done;
    }
    {
        hkExtReal tExact = (hkExtReal)u * dAdB + projA;
        float tr = Rounded(tExact);
        if (tExact <= 0.0f) {
            t = 0.0f;
            flags |= 2;
        } else if (tr >= dA2) {
            t = 1.0f;
            flags |= 1;
        } else {
            t = (hkExtReal)tr / dA2;
        }
    }
done:

    hkVector4_s0110_6490 closestA;
    closestA.x = Rounded(dA.x * t + segA[0].x);
    closestA.y = Rounded(dA.y * t + segA[0].y);
    closestA.z = Rounded(dA.z * t + segA[0].z);
    closestA.w = Rounded(dA.w * t + segA[0].w);
    hkVector4_s0110_6490 closestB;
    closestB.x = Rounded((hkExtReal)dB.x * u + capsB[0].x);
    closestB.y = Rounded((hkExtReal)dB.y * u + capsB[0].y);
    closestB.z = Rounded((hkExtReal)dB.z * u + capsB[0].z);
    closestB.w = Rounded((hkExtReal)dB.w * u + capsB[0].w);
    hkExtReal diffX = closestA.x - closestB.x;   // unrounded
    hkVector4_s0110_6490 diff;
    diff.y = Rounded((hkExtReal)closestA.y - closestB.y);
    diff.z = Rounded((hkExtReal)closestA.z - closestB.z);
    diff.w = Rounded((hkExtReal)closestA.w - closestB.w);

    // --- point 0 ---------------------------------------------------------------------------------
    float radiusSum = Rounded((hkExtReal)capsARadius + capsBRadius);
    hkExtReal maxDist = radiusSum + pointsOut[0].m_separatingNormal.w;
    if (maxDist < HK_REAL_EPSILON)
        maxDist = HK_REAL_EPSILON;
    hkVector4_s0110_6490& n0 = pointsOut[0].m_separatingNormal;
    n0.y = diff.y;
    n0.w = diff.w;
    hkExtReal dist2Exact = diffX * diffX + (hkExtReal)diff.z * diff.z + (hkExtReal)diff.y * diff.y;
    float dist2 = Rounded(dist2Exact);
    n0.z = diff.z;
    if (!(dist2Exact < maxDist * maxDist)) {
        // separated: only the plane
        float inv = Rounded(1.0f / sqrt((hkExtReal)dist2));
        n0.x = Rounded(diffX);
        n0.x = Rounded((hkExtReal)inv * n0.x);
        n0.y = Rounded((hkExtReal)inv * n0.y);
        n0.z = Rounded((hkExtReal)inv * n0.z);
        n0.w = Rounded((hkExtReal)inv * n0.w);
        n0.w = Rounded((hkExtReal)inv * dist2 - radiusSum);
        return;
    }
    n0.x = Rounded(diffX);
    hkExtReal dist;   // unrounded
    if (dist2 < HK_REAL_EPSILON) {
        // the segments intersect: any normal perpendicular to A
        dist = 0.0f;
        int i0 = 0, i1 = 1, i2 = 2;
        float ax = fabsf(dA.x);
        float ay = fabsf(dA.y);
        float az = fabsf(dA.z);
        float m = ax;
        if (ay < ax) {
            i1 = 0;
            m = ay;
            i0 = 1;
        }
        if (az < m) {
            i2 = i0;
            i0 = 2;
        }
        float* dAv = &dA.x;
        float* nv = &n0.x;
        float v = -dAv[i1];
        nv[i0] = 0.0f;
        n0.w = 0.0f;
        nv[i1] = dAv[i2];
        nv[i2] = v;
        normalize3<false>(n0);
    } else {
        hkExtReal invExact = 1.0f / sqrt((hkExtReal)dist2);
        float inv = Rounded(invExact);
        dist = invExact * dist2;
        n0.x = Rounded((hkExtReal)inv * n0.x);
        n0.y = Rounded((hkExtReal)inv * n0.y);
        n0.z = Rounded((hkExtReal)inv * n0.z);
        n0.w = Rounded((hkExtReal)inv * n0.w);
    }
    {
        hkVector4_s0110_6490& p0 = pointsOut[0].m_position;
        hkExtReal s = capsBRadius - dist;
        p0 = closestA;
        p0.x = Rounded(s * n0.x + closestA.x);
        p0.y = Rounded(s * n0.y + closestA.y);
        p0.z = Rounded(s * n0.z + closestA.z);
        p0.w = Rounded(s * n0.w + closestA.w);
        n0.w = Rounded(dist - radiusSum);
    }

    // --- end-point contacts (skipped when the segments are close to parallel) -------------------
    if (dA2dB2 * 0.2f < det)
        return;

    hkExtReal invDet = 1.0f / dA2dB2;   // unrounded
    hkVector4_s0110_6490 p = segA[0];
    hkVector4_s0110_6490 q = capsB[0];
    hkExtReal qx = q.x;                 // q.x lives on the FPU stack (unrounded once moved)
    float kA = Rounded(dB2 * invDet);
    float kB = Rounded(invDet * dA2);
    int mask = 10;
    hkContactPoint_s0110_6490* out = pointsOut + 1;
    for (int i = 0;; ++i, ++out) {
        if ((mask & flags) == 0) {
            // a, b: projections of the end-point pair (unrounded); the second pair's are
            // (dA2 - a) - dAdB and (dB2 - b) - dAdB
            hkExtReal a = i ? ((hkExtReal)dA2 - projA) - dAdB : projA;
            hkExtReal b = i ? ((hkExtReal)dB2 + projB) - dAdB : -(hkExtReal)projB;
            if (b > 0.0f) {
                if (b > dB2)
                    goto next;
                if (a > 0.0f) {
                    if (a > dA2)
                        goto next;
                    if (a * a * kA < b * b * kB)
                        goto moveP;
                }
                {
                    hkExtReal s = b * kB;
                    qx = dB.x * s + qx;
                    q.y = Rounded(dB.y * s + q.y);
                    q.z = Rounded(dB.z * s + q.z);
                    q.w = Rounded(dB.w * s + q.w);
                }
            } else if (a > 0.0f) {
                if (a > dA2)
                    goto next;
            moveP:
                hkExtReal s = a * kA;
                p.x = Rounded(dA.x * s + p.x);
                p.y = Rounded(dA.y * s + p.y);
                p.z = Rounded(dA.z * s + p.z);
                p.w = Rounded(dA.w * s + p.w);
            }
            {
                float rs = radiusSum;
                hkVector4_s0110_6490 pq;
                pq.x = Rounded(p.x - qx);
                pq.y = Rounded((hkExtReal)p.y - q.y);
                pq.z = Rounded((hkExtReal)p.z - q.z);
                pq.w = Rounded((hkExtReal)p.w - q.w);
                hkExtReal maxD = (hkExtReal)rs + out->m_separatingNormal.w;
                hkExtReal d2Exact = (hkExtReal)pq.z * pq.z + (hkExtReal)pq.y * pq.y + (hkExtReal)pq.x * pq.x;
                float d2 = Rounded(d2Exact);
                if (d2Exact < maxD * maxD) {
                    hkExtReal len = sqrt((hkExtReal)d2);   // unrounded
                    hkVector4_s0110_6490& n = out->m_separatingNormal;
                    n = pq;
                    if (d2 > HK_REAL_EPSILON)
                        normalize3<true>(n);
                    else
                        n = pointsOut[0].m_separatingNormal;
                    hkExtReal s = capsBRadius - len;
                    out->m_position = p;
                    out->m_position.x = Rounded(s * n.x + p.x);
                    out->m_position.y = Rounded(s * n.y + p.y);
                    out->m_position.z = Rounded(s * n.z + p.z);
                    out->m_position.w = Rounded(s * n.w + p.w);
                    n.w = Rounded(len - rs);
                }
            }
        }
    next:
        if (i == 1)
            return;
        p = segA[1];
        q = capsB[1];
        qx = q.x;
        dA.x = -dA.x;
        dA.y = -dA.y;
        dA.z = -dA.z;
        dA.w = -dA.w;
        mask = 5;
        dB.x = -dB.x;
        dB.y = -dB.y;
        dB.z = -dB.z;
        dB.w = -dB.w;
    }
}

// @ 0x01106f80
extern "C" int hkCollideCapsuleManifoldCapsVsCapsTol(const hkVector4_s0110_6490* capsA, float capsARadius, const hkVector4_s0110_6490* capsB, float capsBRadius, float tolerance, hkContactPoint_s0110_6490* pointsOut)
{
    // 16-byte aligned locals: the original's frame is `and esp,~15; sub esp,0x68`
    hkVector4_s0110_6490 dA;
    dA.x = capsA[1].x - capsA[0].x;
    dA.y = capsA[1].y - capsA[0].y;
    dA.z = capsA[1].z - capsA[0].z;
    dA.w = capsA[1].w - capsA[0].w;
    hkVector4_s0110_6490 dB;
    dB.x = capsB[1].x - capsB[0].x;
    dB.y = capsB[1].y - capsB[0].y;
    dB.z = capsB[1].z - capsB[0].z;
    dB.w = capsB[1].w - capsB[0].w;

    struct Closest {
        hkVector4_s0110_6490 closestA;   // closest point on A
        hkVector4_s0110_6490 diff;       // closestA - closestB
        float dist2;
    };
    Closest cl;
    unsigned flags = FUN_01105940(&capsA[0].x, &dA.x, &capsB[0].x, &dB.x, (float*)&cl);

    float radiusSum = tolerance + (capsARadius + capsBRadius);
    if (radiusSum * radiusSum < cl.dist2)
        return 1;

    float dist = sqrtf(cl.dist2);
    hkVector4_s0110_6490& n0 = pointsOut[0].m_separatingNormal;

    if (flags != 0) {
        if (cl.dist2 > 0.0f) {
            n0 = cl.diff;
            goto normalize;
        }
    } else {
        float cx = dB.z * dA.y - dB.y * dA.z;
        float cy = dA.z * dB.x - dB.z * dA.x;
        float cz = dB.y * dA.x - dA.y * dB.x;
        if (cx * cx + (cy * cy + cz * cz) > HK_REAL_EPSILON) {
            if (cx * cl.diff.x + (cy * cl.diff.y + cz * cl.diff.z) < 0.0f) {
                cx = -cx;
                cy = -cy;
                cz = -cz;
            }
            n0.x = cx;
            n0.y = cy;
            n0.z = cz;
            n0.w = 0.0f;
            goto normalize;
        }
    }
    {
        // segments intersect: any normal perpendicular to A, built from the two axes that do not
        // include A's smallest component
        const float* dv = &dA.x;
        float* nv = &n0.x;
        float ax = fabsf(dA.x);
        float ay = fabsf(dA.y);
        float az = fabsf(dA.z);
        bool b = ax <= ay;
        float m = b ? ax : ay;
        int i = !b;
        int j = 2;
        if (az < m) {
            i = 2;
            j = !b;
        }
        nv[i] = 0.0f;
        float v = dv[j];
        nv[3] = 0.0f;
        nv[b] = v;
        nv[j] = -dv[b];
    }

normalize:
    {
        // the squared length stays on the x87 stack: its exponent range covers the overflow a 32-bit
        // store would turn into +inf (a 3.4e38 component squares to 1.2e77)
        hkExtReal len2 = (hkExtReal)n0.z * n0.z + ((hkExtReal)n0.y * n0.y + (hkExtReal)n0.x * n0.x);
        hkExtReal scale;
        if (len2 == 0.0f)
            scale = 0.0f;
        else
            scale = 1.0f / sqrt(len2);
        n0.x = scale * n0.x;
        n0.y = scale * n0.y;
        n0.z = scale * n0.z;
        n0.w = scale * n0.w;
    }
    {
        hkVector4_s0110_6490& p0 = pointsOut[0].m_position;
        float s = capsBRadius - dist;
        p0 = cl.closestA;
        p0.x = s * n0.x + cl.closestA.x;
        p0.y = s * n0.y + cl.closestA.y;
        p0.z = s * n0.z + cl.closestA.z;
        p0.w = s * n0.w + cl.closestA.w;
        n0.w = dist - (capsARadius + capsBRadius);
    }
    return 0;
}

// @ 0x01107270
void hkCollideCapsuleUtilManifoldCapsVsTriangle(const float* cap, float capRadius, const float* tri, float triRadius, const float* sc, float extraRadius, int singleCheck, hkContactPointF* out)
{
    float* o = (float*)out;

    // triangle edges
    float e12x = tri[8] - tri[4], e12y = tri[9] - tri[5], e12z = tri[10] - tri[6];
    float w = sc[3];
    float e20x = tri[0] - tri[8], e20y = tri[1] - tri[9], e20z = tri[2] - tri[10];
    float nx = (e20z * e12y - e12z * e20y) * w;
    float ny = w * (e12z * e20x - e12x * e20z);
    float nz = w * (e12x * e20y - e12y * e20x);
    float nw = w * 0.0f;
    float p0 = sc[0];
    float q0 = p0 * e12x;
    float q1 = e12y * p0;
    float q2 = e12z * p0;
    float p1 = sc[1];
    float r1 = e20y * p1;
    float r0 = e20x * p1;
    float b8 = p1 * e20z;
    float p2 = sc[2];
    float s0 = (tri[4] - tri[0]) * p2;
    float s1 = (tri[5] - tri[1]) * p2;
    float s2 = p2 * (tri[6] - tri[2]);

    __declspec(align(16)) float m80[4];
    __declspec(align(16)) float m70[4];
    __declspec(align(16)) float m60[4];
    m80[0] = q1 * nz - q2 * ny;
    m70[0] = q2 * nx - q0 * nz;
    m60[0] = q0 * ny - q1 * nx;
    m80[1] = nz * r1 - ny * b8;
    m70[1] = nx * b8 - r0 * nz;
    m60[1] = r0 * ny - nx * r1;
    m80[2] = nz * s1 - ny * s2;
    m70[2] = nx * s2 - s0 * nz;
    m60[2] = s0 * ny - nx * s1;
    m80[3] = nx;
    m70[3] = ny;
    m60[3] = nz;
    float off = -(sc[4] * sc[0]);

    float d0x = cap[0] - tri[0], d0y = cap[1] - tri[1], d0z = cap[2] - tri[2];
    float d1x = cap[4] - tri[0], d1y = cap[5] - tri[1], d1z = cap[6] - tri[2];

    __declspec(align(16)) float f[8];
    f[0] = (m70[0] * d0y + (d0x * m80[0] + m60[0] * d0z)) + off;
    f[1] = m70[1] * d0y + (d0x * m80[1] + m60[1] * d0z);
    f[2] = d0x * m80[2] + (d0y * m70[2] + m60[2] * d0z);
    f[3] = d0x * nx + (d0y * ny + d0z * nz);
    o[7] = 3.40282e+38f;
    o[15] = 3.40282e+38f;
    o[23] = 3.40282e+38f;
    f[4] = (m70[0] * d1y + (d1x * m80[0] + m60[0] * d1z)) + off;
    f[5] = m70[1] * d1y + (d1x * m80[1] + m60[1] * d1z);
    f[6] = d1x * m80[2] + (d1y * m70[2] + m60[2] * d1z);
    f[7] = d1x * nx + (d1y * ny + d1z * nz);

    float c4 = capRadius + triRadius;
    float rr = c4 + extraRadius;
    if ((((rr < f[2]) << 1 | (rr < f[1]) << 2 | (rr < f[0]) << 3 | (rr < f[3])) &
         ((rr < f[6]) << 1 | (rr < f[5]) << 2 | (rr < f[4]) << 3 | (rr < f[7]))) != 0)
        return;
    if (f[3] < -rr && f[7] < -rr)
        return;

    unsigned c0[2];
    unsigned uA = (f[2] < 0.0f) << 1 | (f[1] < 0.0f) << 2 | (f[0] < 0.0f) << 3 | (f[3] < 0.0f);
    c0[0] = uA;
    unsigned uB = (f[6] < 0.0f) << 1 | (f[5] < 0.0f) << 2 | (f[4] < 0.0f) << 3 | (f[7] < 0.0f);
    c0[1] = uB;

    if (((uB ^ uA) & 1) != 0) {
        float t = f[3] / (f[3] - f[7]);
        float u = 1.0f - t;
        float l1 = u * f[1] + t * f[5];
        float l2 = u * f[2] + t * f[6];
        if ((((l2 < 0.0f) << 1 | (l1 < 0.0f) << 2 | (u * f[0] + t * f[4] < 0.0f) * -8) & 0xe) == 0xe) {
            o[15] = -3.40282e+38f;
            for (int i = 0; i < 2; ++i) {
                float sd = f[3 + 4 * i];
                if ((c0[i] & 0xe) == 0xe) {
                    float v = -fabsf(sd) - c4;
                    if (o[15] < v) {
                        float s;
                        if ((c0[i] & 1) == 0) {
                            o[12] = -nx; o[13] = -ny; o[14] = -nz; o[15] = -nw;
                            s = -triRadius;
                        } else {
                            o[12] = nx; o[13] = ny; o[14] = nz; o[15] = nw;
                            s = triRadius;
                        }
                        s = s - sd;
                        o[8] = cap[4 * i];
                        o[9] = cap[4 * i + 1];
                        o[10] = cap[4 * i + 2];
                        o[11] = cap[4 * i + 3];
                        o[8] = nx * s + o[8];
                        o[9] = ny * s + o[9];
                        o[10] = nz * s + o[10];
                        o[11] = s * nw + o[11];
                        o[15] = v;
                    }
                }
            }
            float dd[4];
            dd[0] = f[4] - f[0];
            dd[1] = f[5] - f[1];
            dd[2] = f[6] - f[2];
            f[7] = f[7] - f[3];
            for (int k = 0; k < 3; ++k) {
                float a = dd[k];
                float inv = 1.0f / (a * a + f[7] * f[7]);
                float cr = a * f[3] - f[7] * f[k];
                cr = (cr * cr) * inv;
                if (cr < (c4 + o[15]) * (c4 + o[15])) {
                    float tt = -((f[7] * f[3] + a * f[k]) * inv);
                    if (-0.0001f < tt && tt < 1.0001f) {
                        float c9 = m70[k];
                        float c10 = f[7];
                        if (f[7] < 0.0f) {
                            c10 = -f[7];
                            a = -a;
                        }
                        float c98 = c10 * m60[k];
                        a = -a;
                        o[12] = a * nx + m80[k] * c10;
                        o[13] = a * ny + c10 * c9;
                        o[14] = a * nz + c98;
                        o[15] = a * nw + c10 * 0.0f;
                        float len2 = o[14] * o[14] + (o[13] * o[13] + o[12] * o[12]);
                        float il;
                        if (len2 == 0.0f) il = 0.0f; else il = 1.0f / (float)sqrt(len2);
                        o[12] = il * o[12];
                        o[13] = il * o[13];
                        o[14] = il * o[14];
                        o[15] = il * o[15];
                        float uu = 1.0f - tt;
                        float px = tt * cap[4] + uu * cap[0];
                        float py = uu * cap[1] + tt * cap[5];
                        float pz = uu * cap[2] + tt * cap[6];
                        float pw = uu * cap[3] + tt * cap[7];
                        o[11] = pw;
                        float dist = -(float)sqrt(cr);
                        o[8] = px;
                        o[9] = py;
                        o[10] = pz;
                        float g = triRadius - dist;
                        o[8] = g * o[12] + px;
                        o[9] = g * o[13] + py;
                        o[10] = g * o[14] + pz;
                        o[11] = g * o[15] + pw;
                        o[15] = dist - c4;
                    }
                }
            }
            return;
        }
    }

    __declspec(align(16)) float seg[4];
    seg[0] = cap[4] - cap[0];
    seg[1] = cap[5] - cap[1];
    seg[2] = cap[6] - cap[2];
    seg[3] = cap[7] - cap[3];
    int idx = 0;
    bool oneShot = false;
    unsigned both = uB | uA;

    if ((both & 0xe) != 0xe) {
        if (singleCheck != 0) {
            o[7] = extraRadius;
            o[15] = extraRadius;
            o[23] = extraRadius;
            hkContactPointF best;
            ((float*)&best)[7] = 3.40282e+38f;
            unsigned m = 8;
            for (int e = 0; e < 3; ++e) {
                if ((m & both) == 0) {
                    float seg2[8];
                    const float* p = tri + EDGE_START(e) * 4;
                    seg2[0] = p[0]; seg2[1] = p[1]; seg2[2] = p[2]; seg2[3] = p[3];
                    const float* q = tri + EDGE_END(e) * 4;
                    seg2[4] = q[0]; seg2[5] = q[1]; seg2[6] = q[2]; seg2[7] = q[3];
                    hkCollideCapsuleUtilManifoldCapsVsCaps_s0110_7270(cap, capRadius, seg2, triRadius, out);
                    // NaN (unordered) must take the same arm as out<=best: the retail
                    // compare is `!(out.w > best.w)` (fcomp; test ah,0x41; jne).
                    if (!(o[7] > ((float*)&best)[7]))
                        best.assign(*out);
                    else
                        out->assign(best);
                }
                m = (int)m >> 1;
            }
            return;
        }
        oneShot = true;
    }

    for (;;) {
        if (!oneShot) {
            for (;;) {
                if (idx > 1)
                    return;
                if ((c0[idx] & 0xe) != 0xe)
                    break;
                float fd = f[idx * 4 + 3];
                float g;
                if ((c0[idx] & 1) == 0)
                    g = triRadius - fd;
                else
                    g = -triRadius - fd;
                o[0] = cap[idx * 4];
                o[1] = cap[idx * 4 + 1];
                o[2] = cap[idx * 4 + 2];
                o[3] = cap[idx * 4 + 3];
                o[0] = nx * g + o[0];
                o[1] = ny * g + o[1];
                o[2] = nz * g + o[2];
                o[3] = g * nw + o[3];
                if ((c0[idx] & 1) == 0) {
                    o[4] = nx; o[5] = ny; o[6] = nz; o[7] = nw;
                    o[7] = fd - c4;
                } else {
                    o[4] = -nx; o[5] = -ny; o[6] = -nz; o[7] = -nw;
                    o[7] = -fd - c4;
                }
                ++idx;
                o += 8;
            }
        }
        // edge phase
        unsigned m = 8;
        for (int e = 0; e < 3; ++e) {
            unsigned hi, lo;
            if (oneShot) {
                hi = m & c0[1];
                lo = c0[0];
            } else {
                hi = c0[idx];
                lo = m;
            }
            if ((lo & hi) == 0) {
                const float* pB = tri + EDGE_END(e) * 4;
                const float* pA = tri + EDGE_START(e) * 4;
                float ed[4];
                ed[0] = pB[0] - pA[0];
                ed[1] = pB[1] - pA[1];
                ed[2] = pB[2] - pA[2];
                ed[3] = pB[3] - pA[3];
                hkCollideTriangleUtil::ClosestLineSegLineSegResult r;
                int fl = hkCollideTriangleUtil::closestLineSegLineSeg(*(const hkVector4_s0110_7270*)cap, *(const hkVector4_s0110_7270*)seg,
                                                                      *(const hkVector4_s0110_7270*)pA, *(const hkVector4_s0110_7270*)ed, r);
                float rad = c4 + o[7];
                if (r.distanceSquared < rad * rad) {
                    bool skip = false;
                    if ((fl & (1 << idx)) != 0) {
                        if (!oneShot) skip = true;
                        else idx = 1;
                    }
                    if (!skip) {
                        float n0, n1, n2, n3;
                        float* diff = r.closestAminusClosestB.v;
                        bool useCross = true;
                        if (fl == 0) {
                            n1 = ed[0] * seg[2] - seg[0] * ed[2];
                            n2 = seg[0] * ed[1] - ed[0] * seg[1];
                            n3 = 0.0f;
                            n0 = ed[2] * seg[1] - ed[1] * seg[2];
                        } else {
                            useCross = false;
                            bool tiny = r.distanceSquared <= 1.4210855e-14f;
                            if (tiny) {
                                diff[0] = m80[e];
                                diff[1] = m70[e];
                                diff[2] = m60[e];
                                diff[3] = 0.0f;
                                n3 = 0.0f;
                                n0 = ed[2] * seg[1] - ed[1] * seg[2];
                                n1 = ed[0] * seg[2] - seg[0] * ed[2];
                                n2 = seg[0] * ed[1] - ed[0] * seg[1];
                                float l2 = n1 * n1 + (n2 * n2 + n0 * n0);
                                if (l2 > 1.4210855e-14f)
                                    useCross = true;
                            }
                            if (!useCross) {
                                n0 = diff[0];
                                n1 = diff[1];
                                n2 = diff[2];
                                n3 = diff[3];
                            }
                        }
                        float l2 = n1 * n1 + (n2 * n2 + n0 * n0);
                        float il;
                        if (l2 == 0.0f) il = 0.0f; else il = 1.0f / (float)sqrt(l2);
                        n0 = n0 * il;
                        n1 = il * n1;
                        n2 = il * n2;
                        n3 = il * n3;
                        float dist = diff[1] * n1 + (diff[2] * n2 + diff[0] * n0);
                        if (dist < 0.0f) {
                            dist = -dist;
                            n0 = -n0; n1 = -n1; n2 = -n2; n3 = -n3;
                        }
                        float g = triRadius - dist;
                        o[0] = n0 * g + r.closestPointA.v[0];
                        o[1] = n1 * g + r.closestPointA.v[1];
                        o[2] = n2 * g + r.closestPointA.v[2];
                        o[3] = n3 * g + r.closestPointA.v[3];
                        o[6] = n2;
                        o[7] = n3;
                        o[4] = n0;
                        o[5] = n1;
                        o[7] = dist - c4;
                    }
                }
            }
            m = (int)m >> 1;
        }
        if (oneShot)
            return;
        ++idx;
        o += 8;
    }
}

// @ 0x01108460
void buildSectionBits(unsigned int value, unsigned int* bits, int n)
{
    const unsigned int t = value >> 4;
    const unsigned int b1 = (~(t >> 1)) & 1u;
    const unsigned int b2 = (~(t >> 2)) & 1u;
    const unsigned int b3 = (~(t >> 3)) & 1u;
    if (n != 0)
        hkSetBitIfClear(bits, 1u << (2 * b2 + 4 * b1));
    if (n != 1)
        hkSetBitIfClear(bits, 1u << (2 * b3 + 4 * b1 + 8));
    if (n != 2)
        hkSetBitIfClear(bits, 1u << (2 * b3 + 4 * b2 + 16));
}

// @ 0x011084f0
void buildSelectedBit(unsigned int value, unsigned int* bits)
{
    const unsigned int t = value >> 4;
    const unsigned int b1 = (~(t >> 1)) & 1u;
    const unsigned int b2 = (~(t >> 2)) & 1u;
    const unsigned int b3 = (~(t >> 3)) & 1u;
    const unsigned int sel = value & 0xf;
    unsigned int k;
    if (sel == 0)
        k = 2 * b2 + 4 * b1;
    else if (sel == 1)
        k = 2 * b3 + 4 * b1 + 8;
    else
        k = 2 * b3 + 4 * b2 + 16;
    hkSetBitIfClear(bits, 1u << k);
}

// @ 0x01108550
void hkFeatureBits(unsigned int* bitsLo, unsigned int* bitsHi, unsigned int count, hkFeaturePointList* list)
{
    (void)count;
    unsigned int a = 0, b = 0;
    for (unsigned int i = 0; i < list->m_count; ++i) {
        const unsigned int cls = list->m_rec[i * 4];
        const unsigned int val = list->m_rec[i * 4 + 1];
        if (cls <= 2)
            buildSectionBits(val, bitsHi, (int)cls);
        else if (cls <= 6)
            buildSectionBits(val, bitsLo, (int)cls - 3);
        else {
            buildSelectedBit(cls, bitsLo);
            buildSelectedBit(val, bitsHi);
        }
    }
    a = *bitsLo;
    b = *bitsHi;
    list->m_valid = (uint8_t)(!((a & 0x555555u) || (b & 0x555555u)) ? 0 : 1);
    (void)a; (void)b;
}

// @ 0x01108750
void hkPackSigns2(hkSignBytes* out, const hkVector4_s0110_8460& a, const hkVector4_s0110_8460& b, int loSel, int hiSel)
{
    hkVector4_s0110_8460 av = a;
    hkVector4_s0110_8460 bv = b;
    (&av.x)[loSel] = 1.0f;
    (&bv.x)[hiSel] = 1.0f;
    const unsigned int sa = ((av.x >= 0.0f) ? 8u : 0u) | ((av.y >= 0.0f) ? 4u : 0u)
                          | ((av.z >= 0.0f) ? 2u : 0u) | ((av.w >= 0.0f) ? 1u : 0u);
    const unsigned int sb = ((bv.x >= 0.0f) ? 8u : 0u) | ((bv.y >= 0.0f) ? 4u : 0u)
                          | ((bv.z >= 0.0f) ? 2u : 0u) | ((bv.w >= 0.0f) ? 1u : 0u);
    out->m_lo = (uint8_t)(((sa & 0xe) << 4) | (uint8_t)loSel);
    out->m_hi = (uint8_t)((((~sb) & 0xe) << 4) + (uint8_t)hiSel);
}

// @ 0x011088b0
int hkPackSigns1(const hkVector4_s0110_8460& v, unsigned int hiBits)
{
    const unsigned int s = ((v.x >= 0.0f) ? 8u : 0u) | ((v.y >= 0.0f) ? 4u : 0u)
                         | ((v.z >= 0.0f) ? 2u : 0u) | ((v.w >= 0.0f) ? 1u : 0u);
    return (int)((s & 0xe0) | ((hiBits >> 28) & 8u));
}

// @ 0x01108940
void hkBoxBoxCollisionDetection::faceAVertexBValidationDataFromFeatureId( hkFeaturePointCache& out, const hkFeatureContactPoint& cp)
{
    out.m_d38 = cp.m_id;
    unsigned int wbits = 0x3f800000u | ((unsigned int)(cp.m_feature & 0xf8) << 28);
    out.m_w30 = *(hkReal*)&wbits;

    const hkVector4_s0110_8460& mask = g_axisMask[(cp.m_feature >> 1) & 7];
    hkVector4_s0110_8460 a;
    a.x = m_radiusB.x * mask.x;
    a.y = m_radiusB.y * mask.y;
    a.z = m_radiusB.z * mask.z;
    a.w = m_radiusB.w * mask.w;
    out.m_v1 = a;

    hkVector4_s0110_8460 p;
    p.x = m_aRb.c0.x * a.x + m_aRb.c1.x * a.y + m_aRb.c2.x * a.z + m_aTb.x;
    p.y = m_aRb.c0.y * a.x + m_aRb.c1.y * a.y + m_aRb.c2.y * a.z + m_aTb.y;
    p.z = m_aRb.c0.z * a.x + m_aRb.c1.z * a.y + m_aRb.c2.z * a.z + m_aTb.z;
    p.w = 0.0f;
    out.m_v0 = p;
}

// @ 0x01108a10
void hkBoxBoxCollisionDetection::faceAVertexBContactPointFromFeaturePointCache( hkProcessCdPoint& out, const hkFeatureContactPoint& cp, const hkFeaturePointCache& cache)
{
    out.m_d20 = cp.m_axis;
    const hkVector4_s0110_8460& a = cache.m_v1;
    const unsigned int rows = *(const unsigned int*)&cache.m_w30;
    const unsigned int off = (unsigned int)((float)rows * 0.0f);
    (void)off;

    const hkVector4_s0110_8460* t = (const hkVector4_s0110_8460*)&cache.m_w30;
    out.m_position.x = m_aRb.c0.x * t[0].x + m_aRb.c1.x * t[0].y + m_aRb.c2.x * t[0].z + m_aTb.x;
    out.m_position.y = m_aRb.c0.y * t[0].x + m_aRb.c1.y * t[0].y + m_aRb.c2.y * t[0].z + m_aTb.y;
    out.m_position.z = m_aRb.c0.z * t[0].x + m_aRb.c1.z * t[0].y + m_aRb.c2.z * t[0].z + m_aTb.z;
    out.m_position.w = 0.0f;

    out.m_normal.x = m_aRb.c0.x * a.x + m_aRb.c1.x * a.y + m_aRb.c2.x * a.z + m_aTb.x;
    out.m_normal.y = m_aRb.c0.y * a.x + m_aRb.c1.y * a.y + m_aRb.c2.y * a.z + m_aTb.y;
    out.m_normal.z = m_aRb.c0.z * a.x + m_aRb.c1.z * a.y + m_aRb.c2.z * a.z + m_aTb.z;
    out.m_normal.w = 0.0f;
}

// @ 0x01108ac0
void hkBoxBoxCollisionDetection::faceBVertexAValidationDataFromFeatureId( hkFeaturePointCache& out, const hkFeatureContactPoint& cp)
{
    out.m_d38 = cp.m_id;
    unsigned int wbits = 0x3f800000u | ((unsigned int)(cp.m_feature & 0xf8) << 28);
    out.m_w30 = *(hkReal*)&wbits;

    const hkVector4_s0110_8460& mask = g_axisMask[(cp.m_feature >> 1) & 7];
    hkVector4_s0110_8460 a;
    a.x = m_radiusA.x * mask.x;
    a.y = m_radiusA.y * mask.y;
    a.z = m_radiusA.z * mask.z;
    a.w = m_radiusA.w * mask.w;
    out.m_v0 = a;

    hkVector4_s0110_8460 d;
    d.x = a.x - m_aTb.x;
    d.y = a.y - m_aTb.y;
    d.z = a.z - m_aTb.z;

    hkVector4_s0110_8460 p;
    p.x = m_aRb.c0.x * d.x + m_aRb.c0.y * d.y + m_aRb.c0.z * d.z;
    p.y = m_aRb.c1.x * d.x + m_aRb.c1.y * d.y + m_aRb.c1.z * d.z;
    p.z = m_aRb.c2.x * d.x + m_aRb.c2.y * d.y + m_aRb.c2.z * d.z;
    p.w = 0.0f;
    out.m_v1 = p;
}

// @ 0x01108b80
void hkBoxBoxCollisionDetection::faceBVertexAContactPointFromFeaturePointCache( hkProcessCdPoint& out, const hkFeatureContactPoint& cp, const hkFeaturePointCache& cache)
{
    out.m_d20 = cp.m_axis;
    const hkVector4_s0110_8460& a = cache.m_v1;
    const int bucket = (int)cache.m_d38 - 4;

    out.m_position.x = m_aRb.c0.x * a.x + m_aRb.c1.x * a.y + m_aRb.c2.x * a.z + m_aTb.x;
    out.m_position.y = m_aRb.c0.y * a.x + m_aRb.c1.y * a.y + m_aRb.c2.y * a.z + m_aTb.y;
    out.m_position.z = m_aRb.c0.z * a.x + m_aRb.c1.z * a.y + m_aRb.c2.z * a.z + m_aTb.z;
    out.m_position.w = 0.0f;

    const hkVector4_s0110_8460* t = (const hkVector4_s0110_8460*)&cache.m_w30;
    out.m_normal.x = m_aRb.c0.x * t[bucket].x + m_aRb.c1.x * t[bucket].y + m_aRb.c2.x * t[bucket].z + m_aTb.x;
    out.m_normal.y = m_aRb.c0.y * t[bucket].x + m_aRb.c1.y * t[bucket].y + m_aRb.c2.y * t[bucket].z + m_aTb.y;
    out.m_normal.z = m_aRb.c0.z * t[bucket].x + m_aRb.c1.z * t[bucket].y + m_aRb.c2.z * t[bucket].z + m_aTb.z;
    out.m_normal.w = 0.0f;
}

// @ 0x01108d00
void hkBoxBoxCollisionDetection::tryToAddPointFaceA(hkBoxBoxManifold& manifold, hkFeatureContactPoint cp, unsigned short a, hkReal tol)
{
    hkFeaturePointCache cache;
    faceAVertexBValidationDataFromFeatureId(cache, cp);
    const hkReal ax = fabsf(cache.m_v0.x);
    const hkReal ay = fabsf(cache.m_v0.y);
    const hkReal az = fabsf(cache.m_v0.z);
    const hkReal aw = fabsf(cache.m_v0.w);
    if (ax > m_boundaryTol.x || ay > m_boundaryTol.y
        || az > m_boundaryTol.z || aw > m_boundaryTol.w)
        return;
    const unsigned int count = manifold.m_count;
    manifold.m_rec[count * 4 + 0] = cp.m_id;
    manifold.m_rec[count * 4 + 1] = cp.m_feature;
    manifold.m_rec[count * 4 + 2] = (uint8_t)(a & 0xff);
    manifold.m_rec[count * 4 + 3] = (uint8_t)(tol != 0.0f);
    manifold.m_count = (uint8_t)(count + 1);
}

// @ 0x011090b0
void SlotScatter::Place(SlotSet* set, int32_t key, uint32_t mask, float limit)
{
    for (int32_t g = 0; g < 7; ++g) {
        uint16_t group = g_14a5f70[g];
        if (((uint32_t)group & mask) != 0)
            continue;

        Key keyhdr;
        keyhdr.mKey = key;
        Req& req = keyhdr.mReq;
        {
            uint8_t hi = (uint8_t)(((uint32_t)key >> 8) & 0xff);
            req.m01 = (uint8_t)((uint8_t)(group & 0xff) ^ hi) | (hi & 0x0f);
        }

        // already recorded in the ring?
        bool present = false;
        for (int32_t i = (int32_t)set->m21 - 1; i >= 0; --i) {
            if (set->mSlots[i].m00 == req.m00 && set->mSlots[i].m01 == req.m01) {
                present = true;
                break;
            }
        }
        if (present)
            continue;

        Hit hit;
        QuerySlot(&hit, &req);

        // req.m10[3] is compared by the original as well, but its flag is
        // masked out of the branch, so only the first three components gate.
        if (!(fabsf(hit.m10[0]) < mA0[0] &&
              fabsf(hit.m10[1]) < mA0[1] &&
              fabsf(hit.m10[2]) < mA0[2]))
            continue;

        float depth = -(hit.m30 * hit.m00[hit.m38]) - m60[hit.m38];
        hit.m34 = depth;
        if (depth < limit - g_14a5f80)
            continue;

        bool transformed = false;
        float rx = 0.0f, ry = 0.0f, rz = 0.0f;
        if ((uint8_t)key <= 2) {
            const float* p = hit.m10;
            const Mat34* m = m18;
            rx = p[0] * m->m[0] + p[1] * m->m[4] + p[2] * m->m[8] + m->m[12];
            ry = p[0] * m->m[1] + p[1] * m->m[5] + p[2] * m->m[9] + m->m[13];
            rz = p[0] * m->m[2] + p[1] * m->m[6] + p[2] * m->m[10] + m->m[14];
            transformed = true;
        } else if ((uint8_t)key <= 6) {
            const float* p = hit.m00;
            const Mat34* m = m14;
            rx = p[0] * m->m[0] + p[1] * m->m[4] + p[2] * m->m[8] + m->m[12];
            ry = p[0] * m->m[1] + p[1] * m->m[5] + p[2] * m->m[9] + m->m[13];
            rz = p[0] * m->m[2] + p[1] * m->m[6] + p[2] * m->m[10] + m->m[14];
            transformed = true;
        }
        if (transformed) {
            // reject the placement when it lands inside the radius of an
            // already committed node
            Node* node = m10->mpNode;
            float clearance = mB0 * mB0;
            bool blocked = false;
            for (uint32_t i = 0; i < set->m21; ++i) {
                if (set->mSlots[i].m00 > 6)
                    continue;
                const Node* nb = node + 1 + i;
                float dx = rx - nb->m00;
                float dy = ry - nb->m04;
                float dz = rz - nb->m08;
                if (dx * dx + dy * dy + dz * dz <= clearance + g_14a5f80) {
                    blocked = true;
                    break;
                }
            }
            if (blocked)
                continue;
        }

        if (set->m21 >= 8)
            continue;

        req.m04 = set->Reserve(m00, m04, &req);
        if (req.m04 < 0)
            continue;

        Node* node = m10->mpNode;
        if (hit.m38 <= 2)
            CommitA(node, &req.m04, &hit);
        else if (hit.m38 <= 6)
            CommitB(node, &req.m04, &hit);
        else
            CommitC(node, &req.m04, &hit);

        if (set->m21 > 1) {
            const Node* prev = node - 1;
            float dot = prev->m10 * node->m10 +
                        prev->m14 * node->m14 +
                        prev->m18 * node->m18;
            if (!(dot > g_1485378)) {
                set->Release(req.m04);
                continue;
            }
        }

        uint16_t handle = ((uint16_t(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, Node*))
                           (*((char**)*(void**)m0C + 2)))(m0C, m00, m04, m08, node);
        set->mSlots[req.m04].m02 = handle;
        if (handle == 0xffff) {
            set->Release(req.m04);
            continue;
        }

        m10->mpNode = node + 1;
        node->m20 = set->mSlots[req.m04].m02;
        if (req.m00 <= 6)
            ++set->m20;
    }
}

// @ 0x0110a0d0
void hkBoxBoxCollisionDetection_s0110_a0d0::faceAVertexBValidationDataFromFeatureIndex(hkFeaturePointCache_s0110_a0d0& c, float featureIndex) const
{
    int fi = (int)featureIndex;

    c.mIndexA = featureIndex;
    float fVar1 = mRow[0][fi];
    float fVar2 = mRow[1][fi];
    float fVar3 = mRow[2][fi];

    if (0.0f <= mC[fi])
    {
        c.mScale = 1.0f;
        c.mDir[0] = -mRow[5][0];
        c.mDir[1] = -mRow[5][1];
        c.mDir[2] = -mRow[5][2];
        c.mDir[3] = -mRow[5][3];
    }
    else
    {
        c.mScale = -1.0f;
        c.mDir[0] = mRow[5][0];
        c.mDir[1] = mRow[5][1];
        c.mDir[2] = mRow[5][2];
        c.mDir[3] = mRow[5][3];
    }

    float local_20 = -1e-05f;
    float local_1c = -1e-05f;
    if (0.0f < mD[0])
        local_20 = 1e-05f;
    if (0.0f < mD[1])
        local_1c = 1e-05f;
    float fVar5 = -1e-05f;
    if (0.0f < mD[2])
        fVar5 = 1e-05f;

    float fVar4 = c.mScale;
    c.mDir[0] = xorSign(c.mDir[0], local_20 * fVar4 + fVar1);
    c.mDir[1] = xorSign(c.mDir[1], local_1c * fVar4 + fVar2);
    c.mDir[2] = xorSign(c.mDir[2], fVar5 * fVar4 + fVar3);
    c.mDir[3] = xorSign(c.mDir[3], fVar4 * -1e-05f);

    fVar1 = c.mDir[0];
    fVar2 = c.mDir[1];
    fVar3 = c.mDir[2];
    c.mPoint[0] = (fVar1 * mRow[0][0] + (fVar2 * mRow[1][0] + fVar3 * mRow[2][0])) + mRow[3][0];
    c.mPoint[1] = (fVar1 * mRow[0][1] + (fVar2 * mRow[1][1] + fVar3 * mRow[2][1])) + mRow[3][1];
    c.mPoint[2] = (fVar1 * mRow[0][2] + (fVar2 * mRow[1][2] + fVar3 * mRow[2][2])) + mRow[3][2];
    c.mPoint[3] = 0.0f;
}

// @ 0x0110a2b0
void hkBoxBoxCollisionDetection_s0110_a0d0::faceBVertexAValidationDataFromFeatureIndex(hkFeaturePointCache_s0110_a0d0& c, int featureIndex) const
{
    c.mIndexA = (float)(featureIndex + 4);

    const float* pf = &mRow[featureIndex + 2][0];
    float fVar1 = pf[0];
    float fVar2 = pf[1];
    float fVar3 = pf[2];
    float fVar4 = pf[3];

    if (0.0f <= mD[featureIndex])
    {
        c.mScale = 1.0f;
        c.mPoint[0] = mRow[4][0];
        c.mPoint[1] = mRow[4][1];
        c.mPoint[2] = mRow[4][2];
        c.mPoint[3] = mRow[4][3];
    }
    else
    {
        c.mScale = -1.0f;
        c.mPoint[0] = -mRow[4][0];
        c.mPoint[1] = -mRow[4][1];
        c.mPoint[2] = -mRow[4][2];
        c.mPoint[3] = -mRow[4][3];
    }

    float local_20 = 1e-05f;
    float local_1c = 1e-05f;
    if (0.0f < mC[0])
        local_20 = -1e-05f;
    if (0.0f < mC[1])
        local_1c = -1e-05f;
    float fVar5 = 1e-05f;
    if (0.0f < mC[2])
        fVar5 = -1e-05f;

    float fVar6 = -c.mScale;
    c.mPoint[0] = xorSign(c.mPoint[0], fVar1 + local_20 * fVar6);
    c.mPoint[1] = xorSign(c.mPoint[1], fVar2 + local_1c * fVar6);
    c.mPoint[2] = xorSign(c.mPoint[2], fVar3 + fVar5 * fVar6);
    c.mPoint[3] = xorSign(c.mPoint[3], fVar4 + fVar6 * 1e-05f);

    fVar1 = c.mPoint[0] - mRow[3][0];
    fVar3 = c.mPoint[1] - mRow[3][1];
    fVar2 = c.mPoint[2] - mRow[3][2];
    c.mDir[0] = fVar1 * mRow[0][0] + (fVar3 * mRow[0][1] + fVar2 * mRow[0][2]);
    c.mDir[1] = fVar1 * mRow[1][0] + (fVar3 * mRow[1][1] + fVar2 * mRow[1][2]);
    c.mDir[2] = fVar1 * mRow[2][0] + (fVar3 * mRow[2][1] + fVar2 * mRow[2][2]);
    c.mDir[3] = 0.0f;
}

// @ 0x0110a4b0
void hkBoxBoxCollisionDetection_s0110_a0d0::edgeEdgeValidationDataFromFeatureIndex(hkFeaturePointCache_s0110_a0d0& c) const
{
    const float* pf = &mRow[(int)c.mIndexB + 2][0];

    float local_20[3];
    local_20[2] = 0.0f;
    local_20[1] = 0.0f;
    local_20[0] = 0.0f;
    local_20[(int)c.mIndexA] = 1.0f;

    float fVar10 = pf[2] * local_20[1] - pf[1] * local_20[2];
    float fVar11 = pf[0] * local_20[2] - pf[2] * local_20[0];
    local_20[2] = pf[1] * local_20[0] - pf[0] * local_20[1];

    if (fVar10 * mC[0] + (fVar11 * mC[1] + local_20[2] * mC[2]) < 0.0f)
    {
        fVar10 = -fVar10;
        fVar11 = -fVar11;
        local_20[2] = -local_20[2];
    }

    c.mPoint[2] = local_20[2];
    c.mPoint[3] = 0.0f;
    c.mPoint[0] = fVar10;
    c.mPoint[1] = fVar11;
    c.mDir[0] = fVar10 * mRow[0][0] + (fVar11 * mRow[0][1] + local_20[2] * mRow[0][2]);
    c.mDir[1] = fVar10 * mRow[1][0] + (fVar11 * mRow[1][1] + local_20[2] * mRow[1][2]);
    c.mDir[2] = fVar10 * mRow[2][0] + (fVar11 * mRow[2][1] + local_20[2] * mRow[2][2]);
    c.mDir[3] = 0.0f;
}

// @ 0x0110a600
char* hkBoxBoxCollisionDetection_s0110_a0d0::FUN_0110a600(char* outFlag, hkFeaturePointCache_s0110_a0d0& cache) const
{
    unsigned uVar12 = ((unsigned)cache.mIndexB) & 0xf;
    unsigned uVar10 = ((unsigned)cache.mIndexA) & 0xf;
    unsigned uVar11 = (((unsigned char)cache.mIndexA) >> 1) & 0x70;
    unsigned uVar8  = (((unsigned char)cache.mIndexB) >> 1) & 0x70;

    const float* tA = kSignTable[uVar11 >> 4];
    const float* tB = kSignTable[uVar8 >> 4];

    float local_40[4];
    float local_50[4];
    float local_30[4];
    float local_20[7];

    local_40[0] = tA[0] * mRow[4][0];
    local_40[1] = mRow[4][1] * tA[1];
    local_40[2] = mRow[4][2] * tA[2];
    local_40[3] = mRow[4][3] * tA[3];

    float fVar2 = mRow[5][0] * tB[0];
    float fVar3 = mRow[5][1] * tB[1];
    local_20[2] = mRow[5][2] * tB[2];

    const float* pfVar9 = &mRow[uVar12 + 2][0];
    float fVar1 = mRow[5][uVar12];
    fVar1 = fVar1 + fVar1;
    local_50[0] = fVar1 * pfVar9[0];
    local_50[1] = fVar1 * pfVar9[1];
    local_50[2] = fVar1 * pfVar9[2];
    local_50[3] = fVar1 * pfVar9[3];

    local_20[0] = (fVar2 * mRow[0][0] + (fVar3 * mRow[1][0] + local_20[2] * mRow[2][0])) + mRow[3][0];
    local_30[0] = local_20[0] - local_40[0];
    local_30[1] = ((fVar2 * mRow[0][1] + (fVar3 * mRow[1][1] + local_20[2] * mRow[2][1])) + mRow[3][1]) - local_40[1];
    local_30[2] = ((fVar2 * mRow[0][2] + (fVar3 * mRow[1][2] + local_20[2] * mRow[2][2])) + mRow[3][2]) - local_40[2];
    local_30[3] = -local_40[3];

    fVar2 = mRow[4][uVar10] * -2.0f;
    fVar3 = fVar2 * local_50[uVar10];
    fVar1 = mRow[5][uVar12];
    fVar1 = (fVar1 * fVar1) * 4.0f;
    float fVar4 = local_30[0] * local_50[0] + (local_30[1] * local_50[1] + local_30[2] * local_50[2]);
    float fVar5 = (float)fabsf((fVar2 * fVar2) * fVar1 - fVar3 * fVar3);
    float fVar6 = (fVar2 * local_30[uVar10]) * fVar1 - fVar4 * fVar3;

    if (FLT_EPSILON * fVar5 < fVar6 &&
        !((1.0f - FLT_EPSILON) * fVar5 < fVar6))
    {
        float fVar7 = (1.0f - FLT_EPSILON) * fVar5;
        (void)fVar7;
        fVar4 = (fVar6 / fVar5) * fVar3 - fVar4;
        if (!(fVar4 < FLT_EPSILON * fVar1) && (fVar4 < (1.0f - FLT_EPSILON) * fVar1))
        {
            local_20[2] = 0.0f;
            local_20[1] = 0.0f;
            local_20[0] = 0.0f;
            local_40[uVar10] = (fVar6 / fVar5) * fVar2 + local_40[uVar10];
            local_20[uVar10] = fVar2 * 0.5f;

            fVar1 = local_20[1] * local_50[2] - local_20[2] * local_50[1];
            fVar3 = local_20[2] * local_50[0] - local_50[2] * local_20[0];
            local_50[2] = local_50[1] * local_20[0] - local_20[1] * local_50[0];
            fVar2 = (float)sqrtf(fVar1 * fVar1 + (fVar3 * fVar3 + local_50[2] * local_50[2]));
            local_50[3] = 1.0f / fVar2;
            local_50[0] = fVar1 * local_50[3];
            local_50[1] = fVar3 * local_50[3];
            local_50[2] = local_50[2] * local_50[3];
            local_50[3] = local_50[3] * 0.0f;

            if (mB4 <= fVar2)
            {
                if (local_50[0] * tA[0] + (local_50[2] * tA[2] + local_50[1] * tA[1]) < 0.0f)
                {
                    local_50[0] = -local_50[0];
                    local_50[1] = -local_50[1];
                    local_50[2] = -local_50[2];
                    local_50[3] = -local_50[3];
                }
                fVar1 = local_50[0] * local_30[0] + (local_50[1] * local_30[1] + local_50[2] * local_30[2]);
                if (fVar1 <= mB0)
                {
                    cache.mPoint[0] = local_40[0];
                    cache.mPoint[3] = local_40[3];
                    cache.mPoint[1] = local_40[1];
                    cache.mPoint[2] = local_40[2];
                    cache.mTan[0] = -local_50[0];
                    cache.mTan[1] = -local_50[1];
                    cache.mTan[2] = -local_50[2];
                    cache.mTan[3] = -local_50[3];
                    cache.mDist = fVar1;
                    *outFlag = 1;
                    return outFlag;
                }
            }
        }
    }

    *outFlag = 0;
    return outFlag;
}

// @ 0x0110a9c0
void hkBoxBoxCollisionDetection_s0110_a0d0::addAdditionalEdgeHelper(hkBoxBoxManifold_s0110_a0d0& manifold, hkFeatureContactPoint_s0110_a0d0& feat, float f) const
{
    int iVar8 = (int)manifold.mCount21 - 1;
    if (iVar8 >= 0)
    {
        do
        {
            if (manifold.mEntries[iVar8].mA == feat.mA &&
                manifold.mEntries[iVar8].mB == feat.mB)
                return;
            iVar8 = iVar8 - 1;
        } while (iVar8 >= 0);
    }

    unsigned local_18 = (unsigned)feat.mA;
    unsigned local_14 = (unsigned)feat.mB;
    (void)local_18;
    (void)local_14;

    char flag;
    hkFeaturePointCache_s0110_a0d0 cache;
    FUN_0110a600(&flag, cache);
    if (flag == 0)
        return;

    if (!(f * 0.999f < cache.mDist))
        return;

    float fVar2;
    float fVar6;
    float fVar3;
    float d0;
    float d1;
    float d2;

    if (feat.mA < 7)
    {
        if (feat.mA < 3)
        {
            const float* pfVar10 = mMatB;
            d0 = cache.mDir[0];
            d1 = cache.mDir[1];
            d2 = cache.mDir[2];
            fVar2 = (d0 * pfVar10[0] + (d1 * pfVar10[4] + d2 * pfVar10[8])) + pfVar10[0xc];
            fVar6 = (d0 * pfVar10[1] + (d1 * pfVar10[5] + d2 * pfVar10[9])) + pfVar10[0xd];
            fVar3 = d1 * pfVar10[6] + d2 * pfVar10[10];
        }
        else
        {
            const float* pfVar10 = mMatA;
            d0 = cache.mPoint[0];
            d1 = cache.mPoint[1];
            d2 = cache.mPoint[2];
            fVar2 = (d0 * pfVar10[0] + (d1 * pfVar10[4] + d2 * pfVar10[8])) + pfVar10[0xc];
            fVar6 = (d0 * pfVar10[1] + (d1 * pfVar10[5] + d2 * pfVar10[9])) + pfVar10[0xd];
            fVar3 = d1 * pfVar10[6] + d2 * pfVar10[10];
        }

        float local_58 = (d0 * mMatA[2] + fVar3) + mMatA[0xe];
        (void)local_58;

        if (manifold.mCount21 != 0)
        {
            int i = 0;
            do
            {
                if (manifold.mEntries[i].mA < 7)
                {
                    float dx = fVar2 - mRing->mPoints[i].mX;
                    float dy = fVar6 - mRing->mPoints[i].mY;
                    float dz = local_58 - mRing->mPoints[i].mZ;
                    if (dx * dx + (dy * dy + dz * dz) <= mB0 * mB0 + FLT_EPSILON)
                        return;
                }
                i = i + 1;
            } while (i < (int)manifold.mCount21);
        }
    }

    if (manifold.mCount21 >= 8)
        return;

    int idx = ((TC_manifold*)&manifold)->FUN_010ec540(m00, m04, &cache);
    if (idx < 0)
        return;

    hkProcessCdPoint_s0110_a0d0* cur = mRing->mCursor;

    if (feat.mA <= 2)
        ((TC_contactPoint*)this)->FUN_01108a10(*cur, feat, cache);
    else if (feat.mA <= 6)
        ((TC_contactPoint*)this)->FUN_01108b80(*cur, feat, cache);
    else
        ((TC_contactPoint*)this)->FUN_01108c30(*cur, feat, cache);

    if (manifold.mCount21 > 1)
    {
        hkProcessCdPoint_s0110_a0d0* prev = mRing->mCursor - 1;
        float dot = prev->mNX * cur->mNX + (prev->mNY * cur->mNY + prev->mNZ * cur->mNZ);
        if (dot <= 0.0f)
        {
            manifold.removePoint(idx);
            return;
        }
    }

    {
        typedef short (__thiscall *VtSlot2)(void*, void*, void*, void*, void*);
        void** vtbl = *(void***)mVtObj;
        short result = ((VtSlot2)vtbl[2])(mVtObj, m00, m04, m08, cur);
        manifold.mEntries[idx].mIndex = (unsigned short)result;
        if (result == -1)
        {
            manifold.removePoint(idx);
            return;
        }

        mRing->mCursor = mRing->mCursor + 1;
        feat.mIndex = manifold.mEntries[idx].mIndex;
        cur->mIndex = manifold.mEntries[idx].mIndex;

        if (feat.mA > 6)
            return;
        manifold.mCount20 = (unsigned char)(manifold.mCount20 + 1);
    }
}

// @ 0x0110ac90
void hkBoxBoxCollisionDetection_s0110_a0d0::FUN_0110ac90(hkBoxBoxManifold_s0110_a0d0& manifold, void* a2, void* a3, int p4, int p5, void* a6, void* a7, float f)
{
    hkFeatureContactPoint_s0110_a0d0 feat;
    feat.mA = 0;
    feat.mB = 0;
    feat.mIndex = 0;

    FUN_01108750(&feat, a2, a3);
    (void)a6;
    (void)a7;

    addAdditionalEdgeHelper(manifold, feat, f);

    int cVar1;
    if (p4 == 0)
        cVar1 = 3;
    else
        cVar1 = (p4 == 1) + 1;

    unsigned char bVar4 = (unsigned char)(1u << (cVar1 + 4));
    feat.mA = (unsigned char)(feat.mA ^ bVar4);
    addAdditionalEdgeHelper(manifold, feat, f);

    int cVar3;
    if (p5 == 0)
        cVar3 = 3;
    else
        cVar3 = (p5 == 1) + 1;

    unsigned char bVar2 = (unsigned char)(feat.mB ^ (unsigned char)(1u << (cVar3 + 4)));
    feat.mB = bVar2;
    addAdditionalEdgeHelper(manifold, feat, f);

    feat.mA = (unsigned char)(feat.mA ^ bVar4);
    addAdditionalEdgeHelper(manifold, feat, f);
}

// @ 0x0110ad70
int BoxBoxDetector::FUN_0110ad70(FeaturePairList* list, unsigned char* out, FeaturePointCache* d)
{
  int counter = 8;
  do {
    float best = mDepth[0][0].mFloat;
    int id = 0;
    CONSIDER(0, 0, 0)
    CONSIDER(0, 1, 1)
    CONSIDER(0, 2, 2)
    CONSIDER(1, 0, 4)
    CONSIDER(1, 1, 5)
    CONSIDER(1, 2, 6)
    CONSIDER(2, 0, 8)
    CONSIDER(2, 1, 9)
    CONSIDER(2, 2, 10)
    CONSIDER(3, 0, 12)
    CONSIDER(3, 1, 13)
    CONSIDER(3, 2, 14)
    CONSIDER(4, 0, 16)
    CONSIDER(4, 1, 17)

    if (best < mDepth[4][2].mFloat) {
      id = 18;
      d->mIndex = (id - 8) >> 2;
      d->mSubIndex = (id - 8) & 3;
      FUN_0110a4b0(d);
      unsigned short packed = PackSigns2(d->mFeatures, d->mFeatures + 4,
                                         d->mIndex, d->mSubIndex);
      *out = (unsigned char)packed;
      out[1] = (unsigned char)(packed >> 8);
      d->mIndex = *out;
      d->mSubIndex = out[1];
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == out[1])
          return 1;
      }
      char res[4];
      FUN_0110a600(res, d);
      if (res[0] != 0)
        return 2;
    } else if (id <= 2) {
      *out = (unsigned char)id;
      FUN_0110a0d0(d, id);
      unsigned char signs = PackSigns1(d->mFeatures + 4, d->mScale);
      out[1] = signs;
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == signs)
          return 1;
      }
      float a0 = fabsf(d->mFeatures[0]);
      float a1 = fabsf(d->mFeatures[1]);
      float a2 = fabsf(d->mFeatures[2]);
      float a3 = fabsf(d->mFeatures[3]);
      unsigned mask = (unsigned)(((a0 < mThreshA[0]) * -8) |
                                 ((a1 < mThreshA[1]) << 2) |
                                 ((a2 < mThreshA[2]) << 1) |
                                 (a3 < mThreshA[3]));
      if ((mask & 0xe) == 0xe) {
        d->mResult = d->mFeatures[d->mIndex] * d->mScale - mPlaneA[d->mIndex];
        return 2;
      }
    } else if (id <= 6) {
      *out = (unsigned char)id;
      FUN_0110a2b0(d, id - 4);
      unsigned char signs = PackSigns1(d->mFeatures, d->mScale);
      out[1] = signs;
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == signs)
          return 1;
      }
      float a0 = fabsf(d->mFeatures[4]);
      float a1 = fabsf(d->mFeatures[5]);
      float a2 = fabsf(d->mFeatures[6]);
      float a3 = fabsf(d->mFeatures[7]);
      unsigned mask = (unsigned)(((a0 < mThreshB[0]) * -8) |
                                 ((a1 < mThreshB[1]) << 2) |
                                 ((a2 < mThreshB[2]) << 1) |
                                 (a3 < mThreshB[3]));
      if ((mask & 0xe) == 0xe) {
        d->mResult = -(d->mFeatures[d->mIndex] * d->mScale) -
                     mPlaneA[d->mIndex];
        return 2;
      }    } else {
      d->mIndex = (id - 8) >> 2;
      d->mSubIndex = (id - 8) & 3;
      FUN_0110a4b0(d);
      unsigned short packed = PackSigns2(d->mFeatures, d->mFeatures + 4,
                                         d->mIndex, d->mSubIndex);
      *out = (unsigned char)packed;
      out[1] = (unsigned char)(packed >> 8);
      d->mIndex = *out;
      d->mSubIndex = out[1];
      for (int i = list->mCount - 1; i >= 0; --i) {
        if (list->mPairs[i][0] == *out && list->mPairs[i][1] == out[1])
          return 1;
      }
      char res[4];
      FUN_0110a600(res, d);
      if (res[0] != 0)
        return 2;
    }

    mDepth[id >> 2][id & 3].mBits = 0xff7fffee;
  } while (--counter > 0);
  return 0;
}

// @ 0x0110b260
void BoxBoxDetector::FUN_0110b260(unsigned char* out, CdPoint* result)
{
  FeaturePairList    list;
  FeaturePointCache  data;
  ProcessCdPoint     cp;
  FeaturePair        pair;
  unsigned char      ok = 0;

  list.FUN_010ec500();
  pair.mPad = 0;
  FUN_010d93e0();

  if (FUN_01109460(&mInput) == 0) {
    if (FUN_0110ad70(&list, pair.mFeature, &data) != 2) {
      *out = 0;
      return;
    }
    ok = 1;
    int id = data.mIndex;
    if (id <= 2)
      FUN_01108a10(&cp, &pair, &data);
    else if (id <= 6)
      FUN_01108b80(&cp, &pair, &data);
    else
      FUN_01108c30(&cp, &pair, &data);

    float dist;
    if (pair.mFeature[0] > 2) {
      float depth = -cp.mPlane[3];
      cp.mPoint[0] = cp.mPlane[0] * depth + cp.mPoint[0];
      cp.mPoint[1] = cp.mPlane[1] * depth + cp.mPoint[1];
      cp.mPoint[2] = cp.mPlane[2] * depth + cp.mPoint[2];
      dist = depth * cp.mPlane[3] + cp.mDistance;
    } else {
      dist = cp.mDistance;
    }

    result->mPlane[0] = cp.mPlane[0];
    result->mPlane[1] = cp.mPlane[1];
    result->mPlane[2] = cp.mPlane[2];
    result->mPlane[3] = cp.mPlane[3];
    result->mDistance = dist;
    result->mPoint[0] = cp.mPoint[0];
    result->mPoint[1] = cp.mPoint[1];
    result->mPoint[2] = cp.mPoint[2];
    result->mPlane[3] = cp.mPlane[3];
  }
  *out = ok;
}

// @ 0x0110b3a0
void hkBoxBoxCollisionDetection_s0110_b3a0::calcManifold(hkBoxBoxManifold_s0110_b3a0& manifold) const
{
    initVars();

    hkProcessCdPoint_s0110_b3a0* firstPoint = m_result->m_firstFreeContactPoint;

    // 1. Revalidate the existing points.
    {
        int i = 0;
        if (manifold.m_numPoints > 0) {
            hkFeatureContactPoint_s0110_b3a0* fcp = &manifold.m_contactPoints[0];
            do {
                int featureA = fcp->m_featureIdA;
                if (featureA <= 2) {
                    hkFeaturePointCache fpp;
                    faceAVertexBValidationDataFromFeatureId(fpp, *fcp);
                    hkVector4_s0110_b3a0 absV;
                    setAbs4(absV, fpp.m_vA);
                    if ((compareLessThan4(absV, m_boundaryToleranceA) & 0xe) != 0xe)
                        goto removePoint;
                    fpp.m_distance = fpp.m_nscale * fpp.m_vA(fpp.m_featureIndexA) - m_radiusA(fpp.m_featureIndexA);
                    hkProcessCdPoint_s0110_b3a0* cp = m_result->m_firstFreeContactPoint;
                    m_result->m_firstFreeContactPoint = cp + 1;
                    faceAVertexBContactPointFromFeaturePointCache(*cp, *fcp, fpp);
                    i++;
                    fcp++;
                } else if (featureA <= 6) {
                    hkFeaturePointCache fpp;
                    faceBVertexAValidationDataFromFeatureId(fpp, *fcp);
                    hkVector4_s0110_b3a0 absV;
                    setAbs4(absV, fpp.m_vB);
                    if ((compareLessThan4(absV, m_boundaryToleranceB) & 0xe) != 0xe)
                        goto removePoint;
                    fpp.m_distance = -(fpp.m_nscale * fpp.m_vB(fpp.m_featureIndexA - 4)) - m_radiusB(fpp.m_featureIndexA - 4);
                    hkProcessCdPoint_s0110_b3a0* cp = m_result->m_firstFreeContactPoint;
                    m_result->m_firstFreeContactPoint = cp + 1;
                    faceBVertexAContactPointFromFeaturePointCache(*cp, *fcp, fpp);
                    i++;
                    fcp++;
                } else {
                    hkFeaturePointCache fpp;
                    fpp.m_featureIndexA = featureA;
                    fpp.m_featureIndexB = fcp->m_featureIdB;
                    if (!edgeEdgeValidationDataFromFeatureId(fpp))
                        goto removePoint;
                    hkProcessCdPoint_s0110_b3a0* cp = m_result->m_firstFreeContactPoint;
                    m_result->m_firstFreeContactPoint = cp + 1;
                    edgeEdgeContactPointFromFeaturePointCache(*cp, *fcp, fpp);
                    i++;
                    fcp++;
                }
                continue;
            removePoint:
                if (fcp->m_featureIdA <= 6)
                    manifold.m_faceVertexFeatureCount--;
                m_contactMgr->removeContactPoint(fcp->m_contactPointId);
                manifold.removePoint(i);
            } while (i < manifold.m_numPoints);
        }
    }

    // 2. Does the manifold normal still match?
    hkBool_s0110_b3a0 normalChanged;
    if (manifold.m_numPoints < 2) {
        manifold.m_manifoldNormalInitialized.m_bool = false;
        normalChanged.m_bool = true;
    } else {
        if (!manifold.m_manifoldNormalInitialized)
            calcManifoldNormalB(manifold, m_aRb);
        hkVector4_s0110_b3a0 nA;
        setRotatedDirInl(nA, m_aRb, manifold.m_manifoldNormalB);
        normalChanged.m_bool = dot3_s0110_b3a0(nA, manifold.m_manifoldNormalA) < 0.95f;
        if (!normalChanged && manifold.m_isComplete)
            return;
    }

    // 3. Separating-axis test, with a tolerance just below the closest current point.
    int separated;
    if (manifold.m_numPoints == 0) {
        separated = checkIntersection(m_tolerance4);
    } else {
        hkReal minDist = firstPoint[0].m_contact.m_separatingNormal.w;
        for (int k = manifold.m_numPoints - 1; k > 0; k--)
            minDist = hkMin2(minDist, firstPoint[k].m_contact.m_separatingNormal.w);
        hkVector4_s0110_b3a0 tol4;
        minDist = minDist - m_tolerance4.x * 0.05f;
        tol4.x = minDist;
        tol4.y = minDist;
        tol4.z = minDist;
        tol4.w = minDist;
        separated = checkIntersection(tol4);
    }
    if (separated)
        return;

    // 4. Closest feature pair.
    hkFeatureContactPoint_s0110_b3a0 fcp;
    hkFeaturePointCache fpp;
    int closest = findClosestPoint(manifold, fcp, fpp);

    if (normalChanged && closest) {
        hkVector4_s0110_b3a0& normal = manifold.m_manifoldNormalA;
        if (fpp.m_featureIndexA <= 2) {
            hkReal s = -fpp.m_nscale;
            normal.x = 0.0f;
            normal.y = 0.0f;
            normal.z = 0.0f;
            normal.w = 0.0f;
            normal(fcp.m_featureIdA) = s;
        } else if (fpp.m_featureIndexA <= 6) {
            hkReal s = -fpp.m_nscale;
            const hkVector4_s0110_b3a0& col = m_aRb.getColumn(fcp.m_featureIdA - 4);
            normal.x = s * col.x;
            normal.y = s * col.y;
            normal.z = s * col.z;
            normal.w = s * col.w;
        } else {
            normal = fpp.m_normal;
        }

        if (manifold.m_manifoldNormalInitialized) {
            hkVector4_s0110_b3a0 worldNormal;
            worldNormal.setRotatedDir(m_wTa->m_rotation, manifold.m_manifoldNormalA);

            int base = m_result->getNumContactPoints() - manifold.m_numPoints;
            int k = 0;
            if (manifold.m_numPoints > 0) {
                do {
                    hkProcessCdPoint_s0110_b3a0& cp = m_result->m_contactPoints[base + k];
                    if (dot3_s0110_b3a0(worldNormal, cp.m_contact.m_separatingNormal) < 0.95f) {
                        cp = *(m_result->m_firstFreeContactPoint - 1);
                        if (manifold.m_contactPoints[k].m_featureIdA <= 6)
                            manifold.m_faceVertexFeatureCount--;
                        m_contactMgr->removeContactPoint(manifold.m_contactPoints[k].m_contactPointId);
                        manifold.removePoint(k);
                        m_result->m_firstFreeContactPoint--;
                    } else {
                        k++;
                    }
                } while (k < manifold.m_numPoints);
            }

            if (manifold.m_numPoints < 2)
                manifold.m_manifoldNormalInitialized.m_bool = false;
            else
                calcManifoldNormalB(manifold, m_aRb);
        }
    }

    if (closest != 2)
        return;

    // 4b. A new vertex point must not duplicate an existing vertex point.
    if (fcp.m_featureIdA <= 6) {
        hkVector4_s0110_b3a0 pos;
        if (fcp.m_featureIdA <= 2)
            setTransformedPos(pos, *m_wTb, fpp.m_vB);
        else
            setTransformedPos(pos, *m_wTa, fpp.m_vA);
        for (int k = 0; k < manifold.m_numPoints; k++) {
            if (manifold.m_contactPoints[k].m_featureIdA <= 6) {
                const hkVector4_s0110_b3a0& p = m_result->m_contactPoints[k].m_contact.m_position;
                hkReal dx = pos.x - p.x;
                hkReal dy = pos.y - p.y;
                hkReal dz = pos.z - p.z;
                hkReal t = m_tolerance;
                if (dx * dx + dz * dz + dy * dy <= t * t + 1.1920929e-07f)
                    return;
            }
        }
    }

    if (manifold.m_numPoints >= 8)
        return;

    int index = manifold.addPoint(*m_bodyA, *m_bodyB, fcp);
    if (index >= 0) {
        hkProcessCdPoint_s0110_b3a0* cp = m_result->m_firstFreeContactPoint;
        if (fpp.m_featureIndexA <= 2)
            faceAVertexBContactPointFromFeaturePointCache(*cp, fcp, fpp);
        else if (fpp.m_featureIndexA <= 6)
            faceBVertexAContactPointFromFeaturePointCache(*cp, fcp, fpp);
        else
            edgeEdgeContactPointFromFeaturePointCache(*cp, fcp, fpp);

        if (manifold.m_numPoints > 1) {
            const hkVector4_s0110_b3a0& prev = (m_result->m_firstFreeContactPoint - 1)->m_contact.m_separatingNormal;
            if (dot3_s0110_b3a0(prev, cp->m_contact.m_separatingNormal) <= 0.0f) {
                manifold.removePoint(index);
                return;
            }
        }

        hkContactPointId id = m_contactMgr->addContactPoint(*m_bodyA, *m_bodyB, *m_env, *cp);
        manifold.m_contactPoints[index].m_contactPointId = id;
        if (id == 0xffff) {
            manifold.removePoint(index);
        } else {
            m_result->m_firstFreeContactPoint++;
            fcp.m_contactPointId = manifold.m_contactPoints[index].m_contactPointId;
            cp->m_contactPointId = manifold.m_contactPoints[index].m_contactPointId;
            if (fcp.m_featureIdA <= 6)
                manifold.m_faceVertexFeatureCount++;
        }
    }

    // 5. Faces nearly aligned with the normal: add the face points.
    hkFeatureContactPoint_s0110_b3a0 fcpA = fcp;
    if (manifold.m_numPoints < 1)
        return;

    int numPoints = manifold.m_numPoints;
    int base = m_result->getNumContactPoints() - numPoints;
    const hkVector4_s0110_b3a0& normal = m_result->m_contactPoints[base].m_contact.m_separatingNormal;

    hkVector4_s0110_b3a0 normalInA;
    setRotatedInverseDir(normalInA, m_wTa->m_rotation, normal);
    hkVector4_s0110_b3a0 normalInB;
    setRotatedInverseDir(normalInB, m_wTb->m_rotation, normal);
    normalInB.w = 0.0f;
    normalInA.x = -normalInA.x;
    normalInA.y = -normalInA.y;
    normalInA.z = -normalInA.z;
    normalInA.w = 0.0f;

    hkVector4_s0110_b3a0 absA;
    setAbs4(absA, normalInA);
    hkVector4_s0110_b3a0 absB;
    setAbs4(absB, normalInB);

    int axisA;
    int maskA;
    if (absA.x > absA.y) {
        axisA = 0;
        maskA = 0x80;
    } else {
        axisA = 1;
        maskA = 0x40;
    }
    if (absA.z > absA(axisA)) {
        axisA = 2;
        maskA = 0x20;
    }
    int axisB;
    int maskB;
    if (absB.x > absB.y) {
        axisB = 0;
        maskB = 0x80;
    } else {
        axisB = 1;
        maskB = 0x40;
    }
    if (absB.z > absB(axisB)) {
        axisB = 2;
        maskB = 0x20;
    }

    if (absA(axisA) < 0.98f)
        return;
    if (absB(axisB) < 0.98f)
        return;

    hkFeatureContactPoint_s0110_b3a0 fcpB;
    fcpA.m_featureIdB = vertexIdFromNormal(normalInB, m_dinA(axisA));
    fcpB.m_featureIdB = vertexIdFromNormal(normalInA, m_dinB(axisB));
    fcpA.m_featureIdA = (uint8_t)axisA;
    fcpB.m_featureIdA = (uint8_t)(axisB + 4);

    hkReal minDist = 1.0f;
    if (numPoints > 0) {
        const hkProcessCdPoint_s0110_b3a0* p = &m_result->m_contactPoints[base];
        for (int k = manifold.m_numPoints; k != 0; k--, p++) {
            if (p->m_contact.m_separatingNormal.w < minDist)
                minDist = p->m_contact.m_separatingNormal.w;
        }
    }

    tryToAddPointFaceA(manifold, fcpA, (uint16_t)maskB, minDist);
    tryToAddPointFaceB(manifold, fcpB, (uint16_t)maskA, minDist);

    if (manifold.m_faceVertexFeatureCount >= 4) {
        manifold.m_isComplete.m_bool = true;
        return;
    }

    if (g_hkBoxBoxAddAdditionalEdges) {
        int b0 = g_hkBoxBoxNextAxis[axisB];
        int a0 = g_hkBoxBoxNextAxis[axisA];
        int a1 = g_hkBoxBoxNextAxis[axisA + 1];
        normalInB.x = -normalInB.x;
        normalInB.y = -normalInB.y;
        normalInB.z = -normalInB.z;
        int b1 = g_hkBoxBoxNextAxis[axisB + 1];
        normalInB.w = 0.0f;
        addAdditionalEdges(manifold, a0, b0, a1, b1, normalInA, normalInB, minDist);
        addAdditionalEdges(manifold, a0, b1, a1, b0, normalInA, normalInB, minDist);
        addAdditionalEdges(manifold, a1, b0, a0, b1, normalInA, normalInB, minDist);
        addAdditionalEdges(manifold, a1, b1, a0, b0, normalInA, normalInB, minDist);
    }

    checkCompleteness(manifold, maskA, maskB);
}

// @ 0x0110dd70
void hkGsk::handlePenetration(const hkConvexShape* shapeA, const hkConvexShape* shapeB, const hkTransform_s0110_dd70& aTb)
{
    int n = 4;
    if (m_dimB >= 3) {
        if (m_dimB > 3) {
            hkCopy(m_verticesA[3], m_verticesA[0]);
        } else if (m_dimA > 1) {
            hkCopy(m_verticesA[3], m_verticesA[1]);
            hkCopy(m_verticesB[3], m_verticesB[0]);
            hkCopy(m_verticesBinA[3], m_verticesBinA[0]);
        } else {
            n = 3;
        }
        hkCopy(m_verticesA[1], m_verticesA[0]);
        hkCopy(m_verticesA[2], m_verticesA[0]);
    } else {
        if (m_dimA >= 3) {
            if (m_dimA > 3) {
                hkCopy(m_verticesB[3], m_verticesB[0]);
                hkCopy(m_verticesBinA[3], m_verticesBinA[0]);
            } else if (m_dimB > 1) {
                hkCopy(m_verticesA[3], m_verticesA[0]);
                hkCopy(m_verticesB[3], m_verticesB[1]);
                hkCopy(m_verticesBinA[3], m_verticesBinA[1]);
            } else {
                n = 3;
            }
            hkCopy(m_verticesB[1], m_verticesB[0]);
            hkCopy(m_verticesBinA[1], m_verticesBinA[0]);
            hkCopy(m_verticesB[2], m_verticesB[0]);
            hkCopy(m_verticesBinA[2], m_verticesBinA[0]);
        } else {
            n = 1;
        }
    }

    hkVector4_s0110_dd70 diffs[4];
    for (int i = 0; i < n; i++) {
        const hkVector4_s0110_dd70& a = m_verticesA[i];
        const hkVector4_s0110_dd70& b = m_verticesBinA[i];
        diffs[i].x = a.x - b.x; diffs[i].y = a.y - b.y; diffs[i].z = a.z - b.z; diffs[i].w = a.w - b.w;
    }

    hkGskOut out;
    hkCalculatePenetrationDepth(shapeA, shapeB, aTb, 1e-4f, m_verticesA, m_verticesB, diffs, &n, out);

    if (n == 1) {
        m_dimB = 1;
        m_dimA = 1;
    } else {
        m_dimB = 3;
        m_dimA = 3;
        if (hkVertexId(m_verticesA[1]) == hkVertexId(m_verticesA[2]) ||
            hkVertexId(m_verticesA[0]) == hkVertexId(m_verticesA[2])) {
            m_dimA = 2;
        }
        if (hkVertexId(m_verticesA[0]) == hkVertexId(m_verticesA[1])) {
            m_dimA--;
            hkCopy(m_verticesA[0], m_verticesA[m_dimA]);
        }
        if (hkVertexId(m_verticesB[1]) == hkVertexId(m_verticesB[2]) ||
            hkVertexId(m_verticesB[0]) == hkVertexId(m_verticesB[2])) {
            m_dimB--;
        }
        if (m_dimB >= 2 && hkVertexId(m_verticesB[0]) == hkVertexId(m_verticesB[1])) {
            m_dimB--;
            hkCopy(m_verticesB[0], m_verticesB[m_dimB]);
        }

        hkTransform_s0110_dd70 t;
        t.m_col0.x = aTb.m_col0.x; t.m_col0.y = aTb.m_col0.y; t.m_col0.z = aTb.m_col0.z;
        t.m_col1.x = aTb.m_col1.x; t.m_col1.y = aTb.m_col1.y; t.m_col1.z = aTb.m_col1.z;
        t.m_col2.x = aTb.m_col2.x; t.m_col2.y = aTb.m_col2.y; t.m_col2.z = aTb.m_col2.z;
        t.m_translation.x = aTb.m_translation.x; t.m_translation.y = aTb.m_translation.y; t.m_translation.z = aTb.m_translation.z;
        const int nB = m_dimB;
        for (int i = 0; i < nB; i++) {
            setTransformedPos_s0110_dd70(m_verticesBinA[i], t, m_verticesB[i]);
        }

        if (m_dimA + m_dimB > 4) {
            reduceDimensionExtended();
        }
        if (m_dimA == 2 && m_dimB == 2) {
            hkVector4_s0110_dd70 dA, dB;
            dA.x = m_verticesA[1].x - m_verticesA[0].x;
            dA.y = m_verticesA[1].y - m_verticesA[0].y;
            dA.z = m_verticesA[1].z - m_verticesA[0].z;
            dA.w = m_verticesA[1].w - m_verticesA[0].w;
            dB.x = m_verticesBinA[1].x - m_verticesBinA[0].x;
            dB.y = m_verticesBinA[1].y - m_verticesBinA[0].y;
            dB.z = m_verticesBinA[1].z - m_verticesBinA[0].z;
            dB.w = m_verticesBinA[1].w - m_verticesBinA[0].w;
            hkCollideTriangleUtil_s0110_dd70::closestLineSegLineSeg(m_verticesA[0], dA, m_verticesBinA[0], dB, m_lineResult);
        }
    }
    hkCopy(m_closestPointDir, out.m_normal);
    m_featureChange = 1;
}

// @ 0x0110fa20
int FUN_0110fa20(int* q, unsigned char* shape, float* outA, float* outB)
{
    float* matrix = (float*)q[1];
    void* objA = (void*)q[2];
    void* objB = (void*)q[3];
    float threshold = ((float*)q)[4];

    signed char c8 = (signed char)shape[8];
    signed char c9 = (signed char)shape[9];
    signed char c10 = (signed char)shape[10];
    signed char c11 = (signed char)shape[11];

    float matA[16];
    float matB[16];
    ((void (__thiscall*)(void*, void*, int, void*))VSlot(objA, 0x28))(objA, shape, (int)c8, matA);
    ((void (__thiscall*)(void*, void*, int, void*))VSlot(objB, 0x28))(objB, shape + (unsigned int)c8 * 2, (int)c9, matB);

    GskFeatureQuery query;
    query.idx0 = c8;
    query.idx1 = c9;
    query.idx2 = c10;
    query.idx3 = c11;
    query.pad4 = 0;
    query.pad8 = 0;
    query.padC = 0;
    query.valid = 0;

    float closest[4];
    closest[0] = 0.0f;
    closest[1] = 0.0f;
    closest[2] = 0.0f;
    closest[3] = 0.0f;
    ((void (__thiscall*)(void*, void*, void*, void*, void*))&FUN_0110e510)
        (&query, objA, objB, (void*)q[0], closest);

    if (query.pad8 != 0)
        ((void (__thiscall*)(void*, void*))&FUN_0110cd00)(&query, shape);

    float dist = closest[3] - *(float*)((char*)objA + 0xc) - *(float*)((char*)objB + 0xc);

    outA[0] = closest[0] * matrix[0] + closest[1] * matrix[4] + closest[2] * matrix[8];
    outA[1] = closest[0] * matrix[1] + closest[1] * matrix[5] + closest[2] * matrix[9];
    outA[2] = closest[0] * matrix[2] + closest[1] * matrix[6] + closest[2] * matrix[10];
    outA[3] = 0.0f;
    outA[3] = dist;

    if (dist < threshold) {
        float v0, v1, v2;
        if (c8 == 1) {
            float delta = *(float*)((char*)objB + 0xc) - closest[3];
            v0 = closest[0] * delta + matA[0];
            v1 = closest[1] * delta + matA[4];
            v2 = closest[2] * delta + matA[8];
        } else if (c9 == 1) {
            float delta = *(float*)((char*)objB + 0xc);
            v0 = closest[0] * delta + matB[0];
            v1 = closest[1] * delta + matB[4];
            v2 = closest[2] * delta + matB[8];
        } else {
            float delta = *(float*)((char*)objB + 0xc) - closest[3];
            v0 = closest[0] * delta + 0.0f;
            v1 = closest[1] * delta + 0.0f;
            v2 = closest[2] * delta + 0.0f;
        }
        outB[0] = v0 * matrix[0] + v1 * matrix[4] + v2 * matrix[8] + matrix[0xc];
        outB[1] = v0 * matrix[1] + v1 * matrix[5] + v2 * matrix[9] + matrix[0xd];
        outB[2] = v0 * matrix[2] + v1 * matrix[6] + v2 * matrix[10] + matrix[0xe];
        outB[3] = 0.0f;
        return 0;
    }

    return 1;
}

// @ 0x0110fc50
void __fastcall hkGskManifold_removeUnusedVertices(unsigned char* p)
{
    unsigned char used[16];
    for (int i = 0; i < 16; i++)
        used[i] = 0;

    unsigned char* base_p = p;
    if ((int)base_p[2] > 0) {
        unsigned int n = base_p[2];
        unsigned char* rec = base_p + 8;
        do {
            unsigned int b = rec[-3];
            unsigned int a = rec[-4];
            unsigned int sum = a + b;
            used[rec[0] >> 4] = 1;
            used[rec[1] >> 4] = 1;
            if (sum > 2)
                used[rec[2] >> 4] = 1;
            if (sum == 4)
                used[rec[3] >> 4] = 1;
            rec += 8;
        } while (--n != 0);
    }

    unsigned int rec_count = base_p[2];
    unsigned int total = (unsigned int)base_p[0] + (unsigned int)base_p[1];
    unsigned short* verts = (unsigned short*)(base_p + rec_count * 8 + 4);
    unsigned int remap[16];
    int i = 0;
    unsigned int w = 0;
    unsigned int off = 0;
    if ((int)total > 0) {
        do {
            remap[i] = off;
            if (used[i] != 0) {
                verts[w] = verts[i];
                w++;
                off += 0x10;
            }
            i++;
        } while (i < (int)total);
    }

    unsigned char base = (unsigned char)(remap[base_p[0]] >> 4);
    base_p[0] = base;
    base_p[1] = (unsigned char)(w - base);

    if (base_p[2] != 0) {
        unsigned int count2 = base_p[2];
        unsigned char* idx = base_p + 9;
        unsigned int n = count2;
        do {
            idx[-1] = (unsigned char)remap[idx[-1] >> 4];
            idx[0] = (unsigned char)remap[idx[0] >> 4];
            idx[1] = (unsigned char)remap[idx[1] >> 4];
            idx[2] = (unsigned char)remap[idx[2] >> 4];
            idx += 8;
        } while (--n != 0);
    }
}

// @ 0x0110fd70
void FUN_0110fd70(unsigned char* p, int index)
{
    unsigned int n = (unsigned char)(p[2] - 1);
    p[2] = (unsigned char)n;
    unsigned char* src = p + n * 8;
    unsigned char* dst = p + (unsigned int)index * 8;
    *(uint32_t*)(dst + 4) = *(uint32_t*)(src + 4);
    *(uint32_t*)(dst + 8) = *(uint32_t*)(src + 8);

    src = p + (unsigned int)p[2] * 8 + 0xc;
    dst = p + (unsigned int)p[2] * 8 + 4;
    int nslots = ((int)p[1] - 1 + (int)p[0]) >> 1;
    if (nslots >= 0) {
        int n2 = nslots + 1;
        do {
            *(uint32_t*)dst = *(uint32_t*)src;
            dst += 4;
            src += 4;
        } while (--n2 != 0);
    }

    hkGskManifold_removeUnusedVertices(p);
}

// @ 0x0110fdd0
void FUN_0110fdd0(unsigned char* p, void* obj)
{
    for (int i = 0; i < p[2]; i++) {
        unsigned short v = *(unsigned short*)(p + 6 + i * 8);
        if (v != 0xffff) {
            (*(void (__thiscall**)(void*, int))(*(void***)obj + 4))(obj, (int)v);
        }
    }
    p[2] = 0;
    p[0] = 0;
    p[1] = 0;
}

// @ 0x0110fe20
void __cdecl hkGskManifold_verifyAndGetPoints(hkGskManifold& manifold, const hkGskManifoldWork& work, int firstPointIndex, hkProcessCollisionOutput_s0110_fe20& out, hkContactMgr_s0110_fe20* contactMgr)
{
    const int originalNumPoints = manifold.m_numContactPoints;

    hkGskManifold::ContactPoint* cpoint = &manifold.m_contactPoints[firstPointIndex];
    for (int i = firstPointIndex; i < manifold.m_numContactPoints; i++, cpoint++)
    {
        hkProcessCdPoint_s0110_fe20* cp = out.m_firstFreeContactPoint;

        hkVector4_s0110_fe20 pointA;   // contact point on A
        hkVector4_s0110_fe20 diff;     // pointA - pointB (xyz)
        hkVector4_s0110_fe20 normal;
        int failed;

        switch (cpoint->m_dimA * 4 + cpoint->m_dimB)
        {
        case 1 * 4 + 1:   // point - point
        {
            const hkVector4_s0110_fe20& a = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4_s0110_fe20& b = vertexAt(work, cpoint->m_vert[1]);
            hkVector4_s0110_fe20 d; d.setSub4(a, b);
            if (d.lengthSquared3() > work.m_radiusSumSqrd)
            {
                failed = 1;
                break;
            }
            diff = d;
            normal = work.m_masterNormal;
            pointA = a;
            failed = 0;
            break;
        }

        case 1 * 4 + 2:   // point A - edge B
        {
            const hkVector4_s0110_fe20& a  = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4_s0110_fe20& b0 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4_s0110_fe20& b1 = vertexAt(work, cpoint->m_vert[2]);
            hkVector4_s0110_fe20 edge; edge.setSub4(b1, b0);
            pointA = a;
            normal = work.m_masterNormal;
            hkVector4_s0110_fe20 d1; d1.setSub4(b1, a);
            hkVector4_s0110_fe20 d0; d0.setSub4(a, b0);
            hkVector4_s0110_fe20 cross; cross.setCross(edge, d1);
            const hkReal dot1 = d1.dot3(edge);
            const hkReal dot0 = d0.dot3(edge);
            const hkReal edgeLen2 = edge.lengthSquared3();
            const int mask = signMask4(dot1, dot0, cross.lengthSquared3(), edgeLen2 * work.m_radiusSumSqrd);
            if (mask & 0xd)
            {
                failed = 1;
                break;
            }
            const hkReal t = dot1 / (dot0 + dot1);
            hkVector4_s0110_fe20 pointB; pointB.setInterpolate4(b0, b1, t);
            diff.setSub4(pointA, pointB);
            failed = 0;
            break;
        }

        case 1 * 4 + 3:   // point A - triangle B
        {
            const hkVector4_s0110_fe20& a  = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4_s0110_fe20& b0 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4_s0110_fe20& b1 = vertexAt(work, cpoint->m_vert[2]);
            const hkVector4_s0110_fe20& b2 = vertexAt(work, cpoint->m_vert[3]);
            diff.setSub4(a, b0);
            pointA = a;
            hkVector4_s0110_fe20 e0; e0.setSub4(b2, b1);
            hkVector4_s0110_fe20 e1; e1.setSub4(b0, b2);
            hkVector4_s0110_fe20 e2; e2.setSub4(b1, b0);
            hkVector4_s0110_fe20 n; n.setCross(e0, e1);
            n.normalize3IfNotZero();
            hkVector4_s0110_fe20 p0; p0.setSub4(a, b1);
            hkVector4_s0110_fe20 p1; p1.setSub4(a, b2);
            hkVector4_s0110_fe20 p2; p2.setSub4(a, b0);
            hkVector4_s0110_fe20 c0; c0.setCross(p0, e0);
            hkVector4_s0110_fe20 c1; c1.setCross(p1, e1);
            hkVector4_s0110_fe20 c2; c2.setCross(p2, e2);
            normal = n;
            const int mask = signMask4(c0.dot3(n), c1.dot3(n), c2.dot3(n), n.dot3(work.m_masterNormal));
            if (mask & 1)
                normal.setNeg4(n);
            failed = ~mask & 0xe;
            break;
        }

        case 2 * 4 + 1:   // edge A - point B
        {
            const hkVector4_s0110_fe20& a0 = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4_s0110_fe20& a1 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4_s0110_fe20& b  = vertexAt(work, cpoint->m_vert[2]);
            hkVector4_s0110_fe20 edge; edge.setSub4(a1, a0);
            normal = work.m_masterNormal;
            hkVector4_s0110_fe20 d1; d1.setSub4(a1, b);
            hkVector4_s0110_fe20 d0; d0.setSub4(b, a0);
            hkVector4_s0110_fe20 cross; cross.setCross(edge, d1);
            const hkReal dot1 = d1.dot3(edge);
            const hkReal dot0 = d0.dot3(edge);
            const hkReal edgeLen2 = edge.lengthSquared3();
            const int mask = signMask4(dot1, dot0, cross.lengthSquared3(), edgeLen2 * work.m_radiusSumSqrd);
            if (mask & 0xd)
            {
                failed = 1;
                break;
            }
            const hkReal t = dot1 / (dot1 + dot0);
            pointA.setInterpolate4(a1, a0, t);
            diff.setSub4(pointA, b);
            failed = 0;
            break;
        }

        case 2 * 4 + 2:   // edge A - edge B
        {
            const hkVector4_s0110_fe20& a0 = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4_s0110_fe20& a1 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4_s0110_fe20& b0 = vertexAt(work, cpoint->m_vert[2]);
            const hkVector4_s0110_fe20& b1 = vertexAt(work, cpoint->m_vert[3]);
            hkVector4_s0110_fe20 edgeA; edgeA.setSub4(a1, a0);
            hkVector4_s0110_fe20 edgeB; edgeB.setSub4(b1, b0);
            hkVector4_s0110_fe20 d0; d0.setSub4(a0, b0);
            hkVector4_s0110_fe20 d1; d1.setSub4(a1, b1);
            hkVector4_s0110_fe20 n; n.setCross(edgeA, edgeB);
            hkVector4_s0110_fe20 planeA; planeA.setCross(edgeA, n);
            hkVector4_s0110_fe20 planeB; planeB.setCross(edgeB, n);
            normal = work.m_masterNormal;
            const hkReal distA0 = d0.dot3(planeB);
            const hkReal distB0 = d0.dot3(planeA);
            const hkReal distA1 = d1.dot3(planeB);
            const hkReal distB1 = d1.dot3(planeA);
            const int mask = signMask4(distA0, distB0, distA1, distB1);
            if (mask != 0xc && mask != 3)
            {
                failed = 1;
                break;
            }
            const hkReal tA = distA0 / (distA0 - distA1);
            pointA.setInterpolate4(a0, a1, tA);
            const hkReal tB = distB0 / (distB0 - distB1);
            hkVector4_s0110_fe20 pointB; pointB.setInterpolate4(b0, b1, tB);
            diff.setSub4(pointA, pointB);
            failed = 0;
            break;
        }

        case 3 * 4 + 1:   // triangle A - point B
        {
            const hkVector4_s0110_fe20& a0 = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4_s0110_fe20& a1 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4_s0110_fe20& a2 = vertexAt(work, cpoint->m_vert[2]);
            const hkVector4_s0110_fe20& b  = vertexAt(work, cpoint->m_vert[3]);
            diff.setSub4(a0, b);
            hkVector4_s0110_fe20 e0; e0.setSub4(a2, a1);
            hkVector4_s0110_fe20 e1; e1.setSub4(a0, a2);
            hkVector4_s0110_fe20 e2; e2.setSub4(a1, a0);
            hkVector4_s0110_fe20 n; n.setCross(e0, e1);
            n.normalize3IfNotZero();
            hkVector4_s0110_fe20 p0; p0.setSub4(b, a1);
            hkVector4_s0110_fe20 p1; p1.setSub4(b, a2);
            hkVector4_s0110_fe20 p2; p2.setSub4(b, a0);
            hkVector4_s0110_fe20 c0; c0.setCross(p0, e0);
            hkVector4_s0110_fe20 c1; c1.setCross(p1, e1);
            hkVector4_s0110_fe20 c2; c2.setCross(p2, e2);
            const hkReal d0 = c0.dot3(n);
            const hkReal d1 = c1.dot3(n);
            const hkReal d2 = c2.dot3(n);
            const hkReal dn = n.dot3(work.m_masterNormal);
            // project B onto the triangle plane
            pointA.setAddMul4(b, n, diff.dot3(n));
            normal = n;
            const int mask = signMask4(d0, d1, d2, dn);
            if (mask & 1)
                normal.setNeg4(n);
            failed = ~mask & 0xe;
            break;
        }

        case 0:
        default:
            failed = 1;
            break;
        }

        if (!failed)
        {
            const hkReal dist = normal.dot3(diff) - work.m_radiusB;
            const hkReal negDist = -dist;
            const hkReal finalDist = dist - work.m_radiusA;
            if (finalDist < work.m_keepContact)
            {
                cp->m_position.setAddMul4(pointA, normal, negDist);
                cp->m_separatingNormal = normal;
                cp->m_separatingNormal.w = finalDist;
                cp->m_contactPointId = cpoint->m_id;
                out.m_firstFreeContactPoint++;
                continue;
            }
        }

        // the point is no longer valid: release it and move the last point into its slot
        if (cpoint->m_id != 0xffff)
            contactMgr->removeContactPoint(cpoint->m_id);
        manifold.m_numContactPoints--;
        *cpoint = manifold.m_contactPoints[manifold.m_numContactPoints];
        i--;
        cpoint--;
    }

    if (manifold.m_numContactPoints < originalNumPoints)
    {
        // the vertex ids follow the contact points: move them down over the freed slots
        const int numVerts = manifold.m_numVertsA + manifold.m_numVertsB;
        memCpy4(&manifold.m_contactPoints[manifold.m_numContactPoints], &manifold.m_contactPoints[originalNumPoints],
                (numVerts + 1) >> 1);
        hkGskManifold_removeUnusedVertices(&manifold);
    }
}
