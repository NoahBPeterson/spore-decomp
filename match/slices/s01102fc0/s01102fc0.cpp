// Slice s01102fc0: hkMoppLongRayVirtualMachine::queryLongRay, MOPP compiler settings, hkAgent1nMachine walkers.
// x87-era Havok 3.1.  Operation order is kept as in the binary.
#include "s01102fc0.h"

// 2^-16 (0x00142ea58 holds 1.5258789e-05f)
static const float HK_MOPP_RANGE_SCALE = 1.52587890625e-05f;

// ---------------------------------------------------------------------------------------------------
// hkMoppLongRayVirtualMachine
// ---------------------------------------------------------------------------------------------------
// @ 0x01102fc0  hkMoppLongRayVirtualMachine::queryLongRay (raycast with output)
hkBool hkMoppLongRayVirtualMachine::queryLongRay(const hkShapeCollection* collection, const hkMoppCode* code, const hkShapeRayCastInput& input, hkShapeRayCastOutput& output)
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
    m_hit = 0;
    queryRay((const hkVector4*)zeroBits, code->m_data, fromTo);
    return m_hit;
}

// @ 0x01103140  hkMoppLongRayVirtualMachine::queryLongRay (raycast into a collector)
void hkMoppLongRayVirtualMachine::queryLongRay(const hkShapeCollection* collection, const hkMoppCode* code, const hkShapeRayCastInput& input, const hkCdBody& body, hkRayHitCollector& collector)
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
    m_hit = 0;
    queryRay((const hkVector4*)zeroBits, code->m_data, fromTo);
}

// ---------------------------------------------------------------------------------------------------
// Shape container key list + projection helpers (hkpMoppUtility / MOPP compiler side)
// ---------------------------------------------------------------------------------------------------
struct hkShapeContainer {
    // vtable slots used here (hkShapeContainer in the 3.1 shape collection): 7 getNumChildShapes, 8 getFirstKey,
    // 9 getNextKey, 10 getChildShape
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6();
    virtual int  getNumChildShapes() const;                                      // +0x1c
    virtual uint32_t getFirstKey() const;                                        // +0x20
    virtual uint32_t getNextKey(uint32_t oldKey) const;                          // +0x24
    virtual const struct hkProjShape* getChildShape(uint32_t key, void* buffer512) const;   // +0x28
};
struct hkProjShape {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual float getMaximumProjection(const hkVector4& direction) const;        // +0x10
};

struct hkShapeKeyList : hkReferencedObject {                                     // vtable 0x014a5dec
    hkShapeContainer* m_container;                                               // +8
    int m_numKeys;                                                               // +0xc
    hkShapeKeyList(hkShapeContainer* container);
    void fillKeys(uint8_t* out /* stride 0x10 {key, 0, ...} */) const;
};

// @ 0x01103330  hkShapeKeyList::hkShapeKeyList
hkShapeKeyList::hkShapeKeyList(hkShapeContainer* container)
{
    m_referenceCount = 1;
    m_container = container;
    m_numKeys = container->getNumChildShapes();
}

// @ 0x011032c0  hkShapeKeyList::fillKeys
void hkShapeKeyList::fillKeys(uint8_t* out) const
{
    int n = m_numKeys;
    uint32_t key = m_container->getFirstKey();
    for (int i = n; i > 0; i--) {
        ((uint32_t*)out)[0] = key;
        ((uint32_t*)out)[1] = 0;
        out += 0x10;
        key = m_container->getNextKey(key);
    }
}

struct hkProjectionHelper {
    uint32_t m_pad[2];                 // +0
    hkShapeContainer* m_container;     // +8
    void calcMinMaxProjectionsAndStore(const hkVector4& dir, uint32_t* entries /*stride 0x10: key@0, min@8, max@0xc*/, int n, float* minOut, float* maxOut) const;
    void calcMinMaxProjections(const hkVector4& dir, uint32_t* entries /*stride 0x10: key@0*/, int n, float* minOut, float* maxOut) const;
};

// min = -getMaximumProjection(-dir), max = getMaximumProjection(dir) per child (a missing child counts as 0/0);
// returns the overall min / max.  The two binary copies differ only in the write back of min/max into the entries.
static inline void hkCalcMinMaxProjections(const hkShapeContainer* container, const hkVector4& dir, uint32_t* entries, int n, float* minOut, float* maxOut, bool writeBack)
{
    *minOut = 3.40282e+38f;      // 0x7f7fffee
    *maxOut = -3.40282e+38f;     // 0xff7fffee
    for (int i = 0; i < n; i++) {
        uint8_t buffer[512];
        const hkProjShape* child = container->getChildShape(entries[0], buffer);
        float maxProj;
        float minProj;           // X87-PRECISION: the callee's return value stays on the FPU stack (unrounded) until stored/compared
        if (child) {
            maxProj = child->getMaximumProjection(dir);
            hkVector4 neg;
            neg.x = -dir.x; neg.y = -dir.y; neg.z = -dir.z; neg.w = -dir.w;
            minProj = -child->getMaximumProjection(neg);
        } else {
            minProj = 0.0f;      // 0x01485378
            maxProj = 0.0f;
        }
        if (writeBack) {
            ((float*)entries)[2] = minProj;
            ((float*)entries)[3] = maxProj;
        }
        if (minProj < *minOut) *minOut = minProj;     // fcomp + test ah,5 / jp: store when strictly less (NaN: no)
        if (*maxOut < maxProj) *maxOut = maxProj;     // fcomp + test ah,0x41 / jne: store when strictly greater
        entries += 4;
    }
}
// @ 0x01103370  (variant that stores min/max back into each entry)
void hkProjectionHelper::calcMinMaxProjectionsAndStore(const hkVector4& dir, uint32_t* entries, int n, float* minOut, float* maxOut) const
{
    hkCalcMinMaxProjections(m_container, dir, entries, n, minOut, maxOut, true);
}
// @ 0x01103470  (variant that only returns the overall min/max)
void hkProjectionHelper::calcMinMaxProjections(const hkVector4& dir, uint32_t* entries, int n, float* minOut, float* maxOut) const
{
    hkCalcMinMaxProjections(m_container, dir, entries, n, minOut, maxOut, false);
}

// ---------------------------------------------------------------------------------------------------
// Small stdcall helpers whose owning classes are not identified
// ---------------------------------------------------------------------------------------------------
// @ 0x011032a0  stdcall(const uint32_t* a, uint32_t* out): *out = a[1]; return true
int __stdcall hkFun_011032a0(const uint32_t* a, uint32_t* out)
{
    *out = a[1];
    return 1;
}

// @ 0x01103300  stdcall(const hkVector4* src, ?, ?, ?, hkVector4* dst): *dst = *src (the three middle arguments are unused)
void __stdcall hkFun_01103300(const hkVector4* src, uint32_t, uint32_t, uint32_t, hkVector4* dst)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->w = src->w;
}

// ---------------------------------------------------------------------------------------------------
// Reference counted object with one pointer member (vtable 0x013ef094)
// ---------------------------------------------------------------------------------------------------
struct hkReferencedObjectWithPtr : hkReferencedObject {
    void* m_ptr;                                       // +8
    hkReferencedObjectWithPtr();
    hkReferencedObjectWithPtr* destroy(unsigned flags);   // 0x01103560 (flags & 1 -> release the memory chunk)
};
// @ 0x01103360  constructor
hkReferencedObjectWithPtr::hkReferencedObjectWithPtr()
{
    m_ptr = 0;
}
// @ 0x01103560  destructor (flags & 1: hkMemory::deallocateChunk(this, memSize, 0x25))
hkReferencedObjectWithPtr* hkReferencedObjectWithPtr::destroy(unsigned flags)
{
    m_ptr = 0;
    if (flags & 1) {
        hkMemory::s_instance->deallocateChunk(this, (int)m_memSizeAndFlags, 0x25);
    }
    return this;
}

// ---------------------------------------------------------------------------------------------------
// MOPP compiler settings
// ---------------------------------------------------------------------------------------------------
struct hkMoppSettingsPartA {                          // 20 bytes, at settings+4
    float m_f0; int32_t m_i1; int32_t m_i2; int32_t m_i3; int32_t m_i4;
    void init(int preset);                              // 0x011037e0
};
struct hkMoppSettingsPartB {                          // 24 bytes, at settings+0x18
    float m_f[5]; float m_f5;
    void init();                                        // 0x01103830
};
struct hkMoppSettings {
    void* m_result;                                     // +0  (hkMoppCode*)
    hkMoppSettingsPartA m_a;                            // +4
    hkMoppSettingsPartB m_b;                            // +0x18
    float m_c0, m_c1, m_c2;                             // +0x30,+0x34,+0x38
    uint32_t m_c3;                                      // +0x3c (never touched by the setters)
    float m_d0, m_d1, m_d2; uint32_t m_d3; int32_t m_d4;   // +0x40..+0x50
    hkMoppSettings* construct(int preset);              // 0x01103610
    void setA(const uint32_t* a);                       // 0x01103590 (5 dwords -> +4)
    void setB(const uint32_t* b);                       // 0x011035c0 (6 dwords -> +0x18)
    void setC(const uint32_t* c);                       // 0x011037a0
    int  getScratchSize(struct hkMoppSource* src) const;     // 0x011035f0
    void* build(struct hkMoppSource* src, void* buffer, int bufferSize);   // 0x01103670
};

// @ 0x01103590
void hkMoppSettings::setA(const uint32_t* a)
{
    uint32_t* d = (uint32_t*)&m_a;
    d[0] = a[0]; d[1] = a[1]; d[2] = a[2]; d[3] = a[3]; d[4] = a[4];
}
// @ 0x011035c0
void hkMoppSettings::setB(const uint32_t* b)
{
    uint32_t* d = (uint32_t*)&m_b;
    d[0] = b[0]; d[1] = b[1]; d[2] = b[2]; d[3] = b[3]; d[4] = b[4]; d[5] = b[5];
}
// @ 0x011037a0
void hkMoppSettings::setC(const uint32_t* c)
{
    // raw dword copies (the binary uses integer moves)
    ((uint32_t&)m_c0) = c[0];
    ((uint32_t&)m_c1) = c[1];
    ((uint32_t&)m_c2) = c[2];
    ((uint32_t&)m_d0) = c[4];
    ((uint32_t&)m_d1) = c[5];
    ((uint32_t&)m_d2) = c[6];
    m_d3 = c[7];
    m_d4 = (int32_t)c[8];
}

// @ 0x011037e0
void hkMoppSettingsPartA::init(int preset)
{
    m_i4 = 5;
    m_i3 = 5;
    ((uint32_t&)m_f0) = 0x3dcccccd;      // 0.1f
    m_i1 = 1000;
    m_i2 = 10;
    if (preset == 0) {
        ((uint32_t&)m_f0) = 0x3e4ccccd;  // 0.2f
    } else if (preset == 1) {
        ((uint32_t&)m_f0) = 0x3d4ccccd;  // 0.05f
        m_i2 = 0x1e;
    }
}
// @ 0x01103830
void hkMoppSettingsPartB::init()
{
    m_f[0] = 1.0f; m_f[1] = 1.0f; m_f[2] = 1.0f; m_f[3] = 1.0f; m_f[4] = 1.0f;
    m_f5 = 0.5f;                         // 0x3f000000
}
// @ 0x01103610
hkMoppSettings* hkMoppSettings::construct(int preset)
{
    m_a.init(preset);
    m_b.init();
    m_c1 = 0.2f;                         // 0x3e4ccccd
    m_c0 = 0.5f;                         // 0x3f000000
    m_c2 = 1.0f;                         // 0x3f800000
    m_d4 = 4;
    m_d0 = 0.2f;
    m_d1 = 0.2f;
    m_d2 = 0.05f;                        // 0x3d4ccccd
    m_d3 = 0;
    return this;
}

// ---------------------------------------------------------------------------------------------------
// MOPP build driver
// ---------------------------------------------------------------------------------------------------
struct hkMoppSource {                                  // polymorphic input: vtable slots used: 2, 3, 5? (see below)
    virtual void m0(); virtual void m1();
    virtual int  getNumPrimitives();                   // +8
    virtual void setScratchBuffer(void* buffer);       // +0xc
    virtual void m4();
};
// helper objects (opaque; sizes and member offsets from the stack frame of 0x01103670).  All callees are thiscall.
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
    virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3(); virtual void o4();
    virtual void attach(void* code, void* record);       // slot 5 (+0x14)
    uint8_t m_data[0x7c];
    void init(const void* settingsC, hkMoppArena* arena, hkMoppSource* src);   // FUN_0111df20
    void destroy();                                      // FUN_005725f0
};

// @ 0x011035f0  size in bytes of the scratch memory for 'src'
int hkMoppSettings::getScratchSize(hkMoppSource* src) const
{
    int n = src->getNumPrimitives();
    return (n + 0x1b400 + *(const int32_t*)&m_a.m_i1) * 16;      // [this+8] == m_a.m_i1 (the "1000" slack count)
}

// @ 0x01103670  compile a MOPP; uses 'buffer' when it is large enough, otherwise allocates (class 0x25)
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

// ---------------------------------------------------------------------------------------------------
// 0x30 byte value-type copy (8 dwords + word + 14 bytes)
// ---------------------------------------------------------------------------------------------------
struct hkBytes48 {
    uint32_t m_w[8]; uint16_t m_h; uint8_t m_b[14];
    hkBytes48* copyFrom(const hkBytes48* other);
};
// @ 0x01103af0
hkBytes48* hkBytes48::copyFrom(const hkBytes48* other)
{
    for (int i = 0; i < 8; i++) m_w[i] = other->m_w[i];
    m_h = other->m_h;
    for (int i = 0; i < 14; i++) m_b[i] = other->m_b[i];
    return this;
}

// ---------------------------------------------------------------------------------------------------
// hkAgent3Input helpers
// ---------------------------------------------------------------------------------------------------
struct hkAgent3Input {
    const hkCdBody* m_bodyA;                  // +0
    const hkCdBody* m_bodyB;                  // +4 (pointers are 4 bytes in the binary)
    const hkCollisionInput* m_input;          // +8
    hkContactMgr* m_contactMgr;               // +0xc
    hkTransform m_aTb;                        // +0x10
};
struct hkAgent3ProcessInput : hkAgent3Input { // 0x70 bytes
    uint32_t m_pad[4];                        // +0x50
    hkVector4 m_linearTimInfo;                // +0x60
};
// source triple that the (compiler outlined) block at 0x01103a10 reads through ESI
struct hkAgent3Source { const hkCdBody* m_bodyA; const hkCdBody* m_bodyB; const hkCollisionInput* m_input; hkContactMgr* m_contactMgr; };
// scratch the block writes through EDI
struct hkAgent3Scratch { hkCdBody m_bodyA; hkCdBody m_bodyB; hkTransform m_transformA; hkTransform m_transformB; };

// @ 0x01103a10  (outlined block, register ABI: ESI = src, EDI = scratch, stack = out).  Moves both bodies to the
// input's time with hkSweptTransformUtil::lerp2 and fills an hkAgent3Input.  scratch->m_bodyB.m_shape/m_shapeKey
// are expected to be set by the caller.
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

// @ 0x01103aa0  (ECX = src, EAX = dst): swapped (flipped) copy of an hkAgent3ProcessInput
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

// ---------------------------------------------------------------------------------------------------
// hkAgent1nMachine
// ---------------------------------------------------------------------------------------------------
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
// agent entry header: [0] stream command, [1] agent type, [3] size in bytes
struct hkAgent1nMachineEntry { uint8_t m_streamCommand; uint8_t m_agentType; uint8_t m_pad2; uint8_t m_size; };

typedef void (__cdecl *hkAgent3InvalidateTimFunc)(hkAgent1nMachineEntry* entry, void* agentData, const hkCollisionInput* input);
typedef void (__cdecl *hkAgent3WarpTimeFunc)(hkAgent1nMachineEntry* entry, void* agentData, hkTime oldTime, hkTime newTime, const hkCollisionInput* input);
struct hkAgent1nMachine_VisitorInput;
typedef void (__cdecl *hkAgent3DestroyFunc)(hkAgent1nMachineEntry* entry, void* agentData, void* constraintOwner);
struct hkAgent3Funcs {                        // 0x34 bytes in the 32-bit binary
    hkAgent3DestroyFunc m_destroyFunc;        // +0
    void* m_other0[5];
    hkAgent3InvalidateTimFunc m_invalidateTimFunc;   // +0x18
    hkAgent3WarpTimeFunc m_warpTimeFunc;             // +0x1c
    void* m_other1[5];
};
struct hkCollisionDispatcher {
    uint8_t m_pad[0x1698];                    // (32-bit layout)
    hkAgent3Funcs m_agent3Func[1];            // +0x1698, indexed by agent type
};
struct hkArrayUtil { static void __cdecl _reserveMore(void* array, int elemSize); };

// @ 0x01103850  hkAgent1nMachine_InvalidateTim
void __cdecl hkAgent1nMachine_InvalidateTim(hkAgent1nTrack& track, const hkCollisionInput& input)
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
                const hkCollisionDispatcher* dispatcher = input.m_dispatcher;
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

// @ 0x01103930  hkAgent1nMachine_WarpTime
void __cdecl hkAgent1nMachine_WarpTime(hkAgent1nTrack& track, hkTime oldTime, hkTime newTime, const hkCollisionInput& input)
{
    int sectorIndex = 1;
    hkAgent1nSector* sector = track.m_sectorsData[0];
    for (;;) {
        uint8_t* end = (uint8_t*)sector + sector->m_bytesAllocated + 0x10;
        uint8_t* p = sector->m_data;
        do {
            uint8_t* entryBase = p;
            uint8_t type = *p;
            if (type <= 6) {
                void* agentData = 0;
                bool call = false;
                switch (type) {
                case 0:
                    p += p[3];
                    break;
                case 1:
                    return;
                case 2: case 3: case 6:
                    agentData = p + 0x10;
                    call = true;
                    break;
                case 4: case 5:
                    agentData = p + 0x20;
                    // fucompp + test ah,0x44 / jp: equal -> keep chain with newTime, anything else (incl. NaN) -> invalid
                    if (*(float*)(p + 0xc) == oldTime) {
                        *(float*)(p + 0xc) = newTime;          // copied as raw bits in the binary
                    } else {
                        *(float*)(p + 0xc) = -1.0f;
                    }
                    call = true;
                    break;
                }
                if (call) {
                    p += p[3];
                    hkAgent3WarpTimeFunc f = input.m_dispatcher->m_agent3Func[entryBase[1]].m_warpTimeFunc;
                    if (f) f((hkAgent1nMachineEntry*)entryBase, agentData, oldTime, newTime, &input);
                }
            }
        } while (p < end);
        sector = track.m_sectorsData[sectorIndex++];
    }
}

// ---------------------------------------------------------------------------------------------------
// hkAgent1nMachine_UpdateShapeCollectionFilterVisitor / hkAgent1nMachine_Create
// ---------------------------------------------------------------------------------------------------
struct hkAgent1nMachine_VisitorInput {
    const hkCdBody* m_bodyA;                  // +0
    const hkCdBody* m_collectionBodyB;        // +4
    const void* m_containerShapeB;            // +8
    const hkCollisionInput* m_input;          // +0xc
    void* m_constraintOwner;                  // +0x10
};
struct hkAgent1nMachineKeyedEntry : hkAgent1nMachineEntry { uint32_t m_shapeKeyA; uint32_t m_shapeKeyB; };   // key B at +8

// @ 0x01103b50  hkAgent1nMachine_UpdateShapeCollectionFilterVisitor
void* __cdecl hkAgent1nMachine_UpdateShapeCollectionFilterVisitor(hkAgent1nMachine_VisitorInput& vin, hkAgent1nMachineKeyedEntry* entry, void* agentData)
{
    const hkCollisionInput* input = vin.m_input;
    hkBool enabled = input->m_filter->isCollisionEnabled(*input, *vin.m_bodyA, *vin.m_collectionBodyB, vin.m_containerShapeB, entry->m_shapeKeyB);
    if (enabled == 0 && entry->m_streamCommand != 0) {
        // the filter now rejects this pair: destroy the agent in place; the next entry slides into this slot
        input->m_dispatcher->m_agent3Func[entry->m_agentType].m_destroyFunc(entry, agentData, vin.m_constraintOwner);
        return entry;
    }
    return (uint8_t*)entry + entry->m_size;
}

struct hkThreadMemory {
    uint8_t m_pad0[0x68];
    void** m_freeListHead;                    // +0x68 (singly linked, first word = next)
    uint8_t m_pad1[0xac - 0x68 - sizeof(void*)];
    int m_numFreeChunks;                      // +0xac
};
extern unsigned long g_hkThreadMemoryTls;     // 0x016e4174
#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
#endif

// @ 0x01103bc0  hkAgent1nMachine_Create  (a track starts with one sector that only holds the end marker)
void __cdecl hkAgent1nMachine_Create(hkAgent1nTrack& track)
{
    track.m_sectorsSize = 0;
    if ((track.m_sectorsCapacityAndFlags & 0x3fffffff) == 0) {
        hkArrayUtil::_reserveMore(&track, 4);
    }
    track.m_sectorsSize++;
    hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    uint32_t* chunk = (uint32_t*)tm->m_freeListHead;
    if (chunk) {
        tm->m_numFreeChunks--;
        tm->m_freeListHead = *(void***)chunk;
    } else {
        chunk = (uint32_t*)hkMemory::s_instance->allocateChunkFromSizeClass(0xc, 0x1c);
    }
    hkAgent1nSector* sector;
    if (chunk) {
        chunk[0] = 0;
        sector = (hkAgent1nSector*)chunk;
    } else {
        sector = 0;
    }
    track.m_sectorsData[0] = sector;
    uint8_t* base = (uint8_t*)sector;
    base[0x13] = 0x10;                        // end marker entry: size
    base[0x10] = 1;                           // end marker entry: command 1
    *(uint32_t*)(base + 0x18) = 0xffffffff;
    sector->m_bytesAllocated = 0x10;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
