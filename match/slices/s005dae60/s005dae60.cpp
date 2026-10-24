#include "types.h"
#include <math.h>

extern "C" void* memcpy(void* dst, const void* src, unsigned int n);
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);
void FreeRawBlock(void* p);                       // 0x00F47380
extern const char kEditorAllocName[];             // 0x013EB430

// Slice s005dae60: SP editor subsystem widgets / Eastl map-operator[] instantiations.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (this module has no /EHsc; confirmed by chk).
//
//   005dae60  eastl::map<AutoRefCount<cMWModel>, vector<cSPEditorTactileComponent*>>::operator[]
//   005daf10  ... (second instantiation)
//   005daff0  ... (third)
//   005db0a0  ... (fourth)
//   005db150  editor feedback-event registration (rbtree + vector push)
//   005db270  ...
//   005db390  ...
//   005db580  ...
//   005db650  ...
//   005dbb50  small UI helper
//   005dbb60  small UI widget create (2 values)
//   005dbbb0  small UI widget create (3 values, mode 4)
//   005dbc10  small UI widget create (3 values, mode 0)
//   005dbc70  UTFInternet::HTTPRequest ctor

// ---------------------------------------------------------------------------------------------
// external callees (signatures chosen so the call sites reproduce the original stack traffic)
void* __cdecl FUN_0067de90();                 // global getter
struct Handler7ebce0 { void f(int); };        // 0x7ebce0
struct Handler7ec160 { void* f(int, int); };  // 0x7ec160
struct Handler7eb820 { void f(int); };        // 0x7eb820

struct Editor {
    void* FUN_005dbb60(int p2);
    void FUN_005dbbb0(int p2);
    void FUN_005dbc10(int p2);
};

// @ 0x005dbb50
void FUN_005dbb50()
{
    ((Handler7ebce0*)FUN_0067de90())->f(-1);
}

// @ 0x005dbb60
void* Editor::FUN_005dbb60(int p2)
{
    void* o = ((Handler7ec160*)FUN_0067de90())->f(5, p2);
    if (o) {
        ((Handler7eb820*)o)->f(2);
        *(uint32_t*)*(uint32_t*)((char*)o + 0xc) = *(uint32_t*)((char*)this + 0x448);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 4) =
            *(uint32_t*)(*(uint32_t*)((char*)this + 0x98) + 0x58);
    }
    return o;
}

// @ 0x005dbbb0
void Editor::FUN_005dbbb0(int p2)
{
    void* o = ((Handler7ec160*)FUN_0067de90())->f(5, 4);
    if (o) {
        ((Handler7eb820*)o)->f(2);
        *(uint32_t*)*(uint32_t*)((char*)o + 0xc) = *(uint32_t*)((char*)this + 0x448);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 4) =
            *(uint32_t*)(*(uint32_t*)((char*)this + 0x98) + 0x58);
        ((Handler7eb820*)o)->f(3);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 8) = (uint32_t)p2;
    }
}

// @ 0x005dbc10
void Editor::FUN_005dbc10(int p2)
{
    void* o = ((Handler7ec160*)FUN_0067de90())->f(5, 0);
    if (o) {
        ((Handler7eb820*)o)->f(2);
        *(uint32_t*)*(uint32_t*)((char*)o + 0xc) = *(uint32_t*)((char*)this + 0x448);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 4) =
            *(uint32_t*)(*(uint32_t*)((char*)this + 0x98) + 0x58);
        ((Handler7eb820*)o)->f(3);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 8) = (uint32_t)p2;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x005dbc70  UTFInternet::HTTPRequest::HTTPRequest
// Complete, but 24 bytes off: cl schedules the 0.2f constant load late (in the zero-fill
// loop) where the original hoisted it right after the +0x1c store.
namespace UTFInternet {
struct HTTPRequest {
    virtual ~HTTPRequest();
    uint32_t pad04[3];       // +0x04
    float m10;               // +0x10
    float m14;               // +0x14
    float m18;               // +0x18
    float m1c;               // +0x1c
    uint32_t pad20[0x10];    // +0x20 .. +0x5f
    uint32_t m60[21];        // +0x60 .. +0xb3
    float mB4;               // +0xb4
    HTTPRequest();
};
HTTPRequest::HTTPRequest()
{
    m10 = 1.0f;
    m14 = 1.0f;
    m18 = 0.25f;
    m1c = 1.0f;
    for (int i = 0; i < 21; ++i)
        m60[i] = 0;
    mB4 = 0.2f;
}
}

// ---------------------------------------------------------------------------------------------
// The Eastl rbtree/vector instantiations below are template expansions of the editor's
// object-model maps.  They are reconstructed behaviourally (find-or-insert in a red-black
// tree keyed by pointer, mapped value = vector<cSPEditorTactileComponent*>); the register
// allocation of cl's inlined rbtree internals is not reproduced, so they are not byte-exact.
// (Kept as compilable placeholders; see partial.txt.)

// @ 0x005dae60
void* FUN_005dae60(void* self, void* key) { (void)self; (void)key; return 0; }

// @ 0x005daf10
void* FUN_005daf10(void* self, void* key) { (void)self; (void)key; return 0; }

// @ 0x005daff0
void* FUN_005daff0(void* self, void* key) { (void)self; (void)key; return 0; }

// @ 0x005db0a0
void* FUN_005db0a0(void* self, void* key) { (void)self; (void)key; return 0; }

// @ 0x005db150
void FUN_005db150(void* self) { (void)self; }

// @ 0x005db270
void FUN_005db270(void* self) { (void)self; }

// @ 0x005db390
void FUN_005db390(void* self) { (void)self; }

// @ 0x005db580
void FUN_005db580(void* self) { (void)self; }

#define PV(n) virtual void pv##n();

// Source object (arg0): a ref-counted handle.  Its first field points at the
// actual component, whose vtable slot +0x170 is the release function.
struct TactileSource {
    void* mComponent;                              // +0x00
    int mField4;                                   // +0x04
    int mField8;                                   // +0x08
    float mField0c;                                // +0x0c
    float mField10;                                // +0x10
    float mField14;                                // +0x14
    char mPad18[0x28];                             // +0x18 .. +0x3f
    int mRefCount;                                 // +0x40
    char mPad44[8];                                // +0x44 .. +0x4b
    float mField4c;                                // +0x4c
    float mField50;                                // +0x50
    float mField54;                                // +0x54
    float mField58;                                // +0x58
};

// The actual component behind the handle; 0x005db650 releases it through
// vtable slot +0x170, passing the handle and the destructor flag.
class TactileComponentObject {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33)
    PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
    PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
    PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66)
    PV(67) PV(68) PV(69) PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77)
    PV(78) PV(79) PV(80) PV(81) PV(82) PV(83) PV(84) PV(85) PV(86) PV(87) PV(88)
    PV(89) PV(90) PV(91)
    virtual void Destroy(TactileSource* source, int flag);  // +0x170
};

// Element stored in the per-source vector (allocated with size 0x28).
struct TactileComponent {
    uint32_t mType;                                // +0x00
    int mID;                                       // +0x04
    float mValue;                                  // +0x08
    float mArgA;                                   // +0x0c
    float mArgB;                                   // +0x10
    float mArgC;                                   // +0x14
    float mZero;                                   // +0x18
    float mPhase;                                  // +0x1c
    float mZero2;                                  // +0x20
    int mZero3;                                    // +0x24
};

struct TactileVector {
    TactileComponent** mpBegin;                    // +0x00
    TactileComponent** mpEnd;                      // +0x04
    TactileComponent** mpCapacity;                 // +0x08
    unsigned int mAllocator;                       // +0x0c
    void Construct(int count, void* allocator);    // 0x0066aec0
    void Grow(TactileComponent** end, TactileComponent** value);  // 0x00630b30
};

struct TactileMap {
    TactileVector* Find(TactileSource** key);      // 0x005daf10
};

struct TactileOwner {
    char mPad00[0x20];
    TactileMap mMap;                               // +0x20
    void Add(TactileSource* source, int type, float arg2, float arg3, int arg4);
};

// @ 0x005db650
void TactileOwner::Add(TactileSource* source, int type, float arg2, float arg3, int arg4)
{
    float value;
    switch (type) {
    case 1: value = source->mField58; break;
    case 2: value = source->mField4c; break;
    case 3: value = source->mField50; break;
    case 4: value = source->mField54; break;
    case 5: value = source->mField0c; break;
    case 6: value = source->mField10; break;
    case 7: value = source->mField14; break;
    }

    TactileVector* vec = mMap.Find(&source);
    int count = (int)(vec->mpEnd - vec->mpBegin);
    TactileVector temp;
    temp.Construct(count, &vec->mAllocator);
    memcpy(temp.mpBegin, vec->mpBegin,
           (unsigned int)((char*)vec->mpEnd - (char*)vec->mpBegin));

    TactileComponent* found = 0;
    for (int i = 0; i < count; ++i) {
        TactileComponent* c = temp.mpBegin[i];
        if (c != 0 && c->mType == (uint32_t)type) {
            found = c;
            break;
        }
    }

    if (found != 0) {
        found->mType = (uint32_t)type;
        found->mID = arg4;
        found->mValue = value;
        found->mArgA = arg2;
        found->mArgB = arg3;
        found->mArgC = arg3;
        found->mZero = 0.0f;
        found->mZero2 = 0.0f;
        found->mZero3 = 0;
        found->mPhase = (float)(1.0f - asin(0.9090908893868948));
    } else {
        TactileComponent* c =
            (TactileComponent*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
        c->mType = (uint32_t)type;
        c->mID = arg4;
        c->mValue = value;
        c->mArgA = arg2;
        c->mArgB = arg3;
        c->mArgC = arg3;
        c->mZero = 0.0f;
        c->mZero2 = 0.0f;
        c->mZero3 = 0;
        c->mPhase = (float)(1.0f - asin(0.9090908893868948));

        vec = mMap.Find(&source);
        if (vec->mpEnd < vec->mpCapacity) {
            *vec->mpEnd = c;
            vec->mpEnd = vec->mpEnd + 1;
        } else {
            vec->Grow(vec->mpEnd, &c);
        }
    }

    if (temp.mpBegin != 0 && *((int*)temp.mpBegin - 1) != 0)
        FreeRawBlock(temp.mpBegin);

    if (source != 0) {
        if (source->mRefCount > 1) {
            source->mRefCount = source->mRefCount - 1;
        } else {
            TactileComponentObject* component =
                (TactileComponentObject*)source->mComponent;
            component->Destroy(source,
                               (int)(((unsigned int)source->mField4 >> 31) & 1));
        }
    }
}
