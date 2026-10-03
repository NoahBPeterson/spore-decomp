// Constructor of a large editor/simulator state object (vtbl at 0x013EC448, secondary vtbl at +8).
// Built without optimization: /Od /Ob1 /arch:SSE.
// Behaviorally equivalent reconstruction; NOT byte-exact (see nonmatching.txt).
#include "types.h"

struct Vector3 { float x, y, z; Vector3() {} Vector3(const Vector3&); };
struct Matrix3 { float m[9]; Matrix3() {} Matrix3(const Matrix3&); };
extern const Vector3 g_ZeroVector;   // 0x015D255C
extern const Matrix3 g_IdentityMatrix; // 0x015D2428
extern const float kOne, kHalfA, kTwo, kPlain, kF410, kF414, kF418, kF41c, kF434, kF378, kF720, kF064;

struct RefCounted { char pad[0x40]; int refCount; };
struct IReleasable { virtual void Slot0(); virtual void Slot1(); };

template <class T> struct RefPtr {
    T* p;
    RefPtr() { p = 0; if (p) p->refCount++; }
};
struct VCall0Ptr { IReleasable* p; VCall0Ptr() { p = 0; if (p) p->Slot0(); } };
struct VCall1Ptr { IReleasable* p; VCall1Ptr() { p = 0; if (p) p->Slot1(); } };

struct Allocator { char c; };
struct Transform { uint32_t d[14]; Transform(); };
struct VecA { uint32_t d[14]; VecA(); void Init(); };      // 0x1c8-style EASTL vectors
struct VecB { uint32_t d[30]; VecB(Allocator&); void Init(); };
struct VecC { uint32_t d[8]; VecC(); };
struct Blk460 { uint32_t d[13]; Blk460(); };
struct Blk4c8 { uint32_t d[70]; Blk4c8(); };
struct Blk630 { uint32_t d[39]; Blk630(); };
struct Blk614 { uint32_t d[7]; Blk614(Allocator&); };
struct Blk170 { uint32_t d[6]; Blk170(int, int); };
struct Blk24 { uint32_t d[3]; Blk24(Allocator&); };
struct IPtrVec { uint32_t d[14]; void resize(int); };
struct EditorState;
void InitSubsystem(EditorState*, uint32_t*, void*);
void InitTail(void*);
void SetRef(void*, int);

struct EditorState {
    void* vtbl0;           // 0x00
    uint32_t f04;
    void* vtbl8;           // 0x08
    uint32_t f0c;
    RefPtr<RefCounted> r10;
    RefPtr<RefCounted> r14;
    VCall0Ptr r18;
    uint32_t f1c, f20, f24, f28;
    bool b2c;
    float f30;
    bool b34;
    char b38, b39; uint32_t f3c;
    char b40, b41; uint32_t f44;
    Vector3 v48, v54;
    Matrix3 m60, m84, ma8, mcc, mf0, m114;
    float f138[3];
    float f144[3];
    uint32_t f150;
    uint32_t f154[3];
    uint32_t f160, f164, f168; float f16c;
    uint32_t pad170[0x6];
    uint32_t f188, f18c, f190;
    uint32_t pad194[3];
    char b1a0; uint32_t f1a4; char b1a8, b1a9;
    uint32_t pad1ac[2];
    int f1b4, f1b8, f1bc, f1c0, f1c4, f1c8, f1cc;
    float f1d0, f1d4, f1d8, f1dc, f1e0, f1e4;
    Vector3 v1e8; Matrix3 m1f4;
    float f218, f21c, f220, f224, f228, f22c;
    char b230;
    uint32_t pad234[3];
    uint32_t pad240[2];
    int f248;
    Transform t24c, t284, t2c0, t2f8;
    uint32_t pad330[3];
    VCall1Ptr p33c;
    VecA v340;
    uint32_t f378;
    uint32_t pad37c[10];
    Vector3 v3a0, v3ac;
    char pad3b8[0x11];
    char b3c9; char pad3ca[0xe];
    int f3d8; uint32_t f3dc;
    VCall1Ptr p3e0, p3e4;
    char b3e8;
    VCall0Ptr p3ec;
    RefPtr<RefCounted> r3f0;
    Vector3 v3f4, v400, v40c, v418, v424;
    int f430; uint32_t f434; char b438; uint32_t f43c;
    float f440, f444;
    uint32_t pad448[2];
    float f450;
    uint32_t pad454[1];
    uint32_t f458, f45c;

    EditorState();
};

// @ 0x004346B0
EditorState::EditorState()
{
    vtbl0 = (void*)0x013EC448;
    f04 = 0;
    vtbl8 = (void*)0x013EC438;
    f0c = 0;
    f1c = 0; f20 = 0; f24 = 0; f28 = 0;
    b2c = false;
    f30 = kF378;
    b34 = true;
    b38 = 0; b39 = 0; f3c = 0;
    b40 = 0; b41 = 0; f44 = 0;
    f150 = 0xfffffffe;
    for (int i = 3; --i >= 0; ) f154[i] = 0;
    f160 = 0; f164 = 0; f168 = 0; f16c = kF378;
    f188 = 0; f18c = 0; f190 = 0;
    b1a0 = 0; f1a4 = 0; b1a8 = 0; b1a9 = 0;
    f1b4 = -1; f1b8 = -1; f1bc = -1; f1c0 = -2;
    f1c4 = 1; f1c8 = 1; f1cc = 3;
    f1d0 = kF064; f1d4 = kF720; f1d8 = kF720; f1dc = kF720;
    f1e0 = kF414; f1e4 = kF410;
    f218 = kF41c; f21c = kF418; f220 = kF378; f224 = kF378;
    f228 = kF434; f22c = kF064;
    b230 = 1;
    f248 = -1;
    f378 = 0;
    b3c9 = 0;
    f3d8 = -1; f3dc = 0;
    b3e8 = 0;
    f430 = -1; f434 = 0; b438 = 0; f43c = 0;
    f440 = kF378; f444 = kF378; f450 = kF378;
    f458 = 0; f45c = 0;
    for (int i = 0; i < 3; i++) { f138[i] = kF378; f144[i] = kF378; }
}
