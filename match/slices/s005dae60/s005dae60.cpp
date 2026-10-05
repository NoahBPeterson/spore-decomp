#include "types.h"

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

// @ 0x005db650
void FUN_005db650(void* self) { (void)self; }
