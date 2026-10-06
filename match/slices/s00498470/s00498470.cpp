// Slice s00498470 (batch w1g0, slice 96), 0x00498470..0x00498f??.
// /Od editor-region code: block placement / pinning helpers (SP::EditorUtils neighbourhood).
// Built unoptimized: /Od /Ob1 /arch:SSE /fp:fast. Callees are declared with the convention seen at the call site.

#include "types.h"

typedef unsigned int u32;

// cSPVector3-like: user copy ctor (inline, element-wise).
struct P3 { float x, y, z; };                   // plain POD triple (dword copies)
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
// Same layout but with the out-of-line copy constructor (0x004098a0).
struct Vec3C : Vec3 {
    Vec3C(const Vec3C& o);                      // 0x004098a0
};
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);                  // 0x0041cb40 (Matrix3::Assign)
};

template <unsigned N> struct Bitset {
    u32 mWord[(N + 31) / 32];
    bool test(unsigned pos) const {
        bool r;
        if (pos < N) {
            u32 w = mWord[pos >> 5];
            r = (w & (1u << (pos % 32))) != 0;
        } else {
            r = false;
        }
        return r;
    }
};

struct RefCountV {
    virtual void rc0();
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();                              // 0x00453540
};
struct Model {                                  // SP::cSPEditorModel (retail layout: vptr, then refcount base at +4)
    virtual void m0();
    RefCountV rc;
    bool FUN_004adc40();                        // 0x004adc40
};
template <class T> struct AutoRefModel {
    T* mp;
    AutoRefModel(T* p) : mp(p) { if (mp) mp->rc.AddRef(); }
    ~AutoRefModel() { if (mp) mp->rc.Release(); }
};

struct IPicker {                                // ray-cast / pick service (intrusive refcounted, Release = vtable slot 1)
    virtual void s0();
    virtual void Release();
    bool RayCast(int type, Vec3C origin, Vec3 dir, P3* hit, P3* normal, float* dist, bool flag);  // 0x004c4a30
    bool RayCast(int type, Vec3 origin, Vec3 dir, P3* hit, P3* normal, float* dist, bool flag);   // 0x004c4a30
    struct Block* PickResult(int type, Vec3 hit);                                                       // 0x004c4d30
};
template <class T> struct AutoRef {
    T* mp;
    ~AutoRef() { if (mp) mp->Release(); }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};
// raw member smart pointer (no ref ops needed by these functions): inline accessors only
template <class T> struct Ref {
    T* mp;
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};

struct Block {
    char pad0[0x28];
    Ref<Model> mEditorModel;                    // +0x28
    char pad1[0x33c - 0x2c];
    Ref<Block> mSocketBlock;                    // +0x33c
    Block** mSocketBegin;                       // +0x340 (vector of Block*)
    Block** mSocketEnd;                         // +0x344
    char pad2[0xdc8 - 0x348];
    Bitset<60> mFlags;                          // +0xdc8
    int GetSkinIdentifierForPicking();          // 0x0043a870
    void SetBooleanAttribute(int id, bool v);   // 0x00435a10
    float FUN_0043f3a0();                       // 0x0043f3a0
};

// ---- external callees ----
bool  __cdecl FUN_004974e0(Block* b, Vec3 pos, P3* out, bool* ok, float f, uint8_t g);
Matrix3* __cdecl MoveBlockAndTranslateSnappedBlocks(Matrix3* ret, Block* b, Matrix3 m);   // 0x00493ce0
bool  __cdecl FUN_004973f0(Block* b, Matrix3* m, float f, uint8_t g);
void  __cdecl FUN_0049ec40(Block* b, P3* pos, Matrix3* m1, Matrix3* m2, bool e);
void  __cdecl FUN_004983d0(Block* b, bool v);
void  __cdecl FUN_00498230(Block* b, int v);
Block* __cdecl PickBlockForPinning(Block* b, int a30, Vec3 origin, Vec3 dir, P3* out1, P3* out2, int a38, int a34); // 0x004a4d60
P3* __cdecl FUN_0041db10(P3* out, const P3* a, const P3* b);        // vector difference a - b
P3* __cdecl Vector3_Normalize(P3* out, const P3* in);                   // 0x00436ce0
float __cdecl VectorLength(const P3* v);                                    // 0x0040ae50

struct Viewer {
    void GetCameraLocationInfo(P3* pos, void* info, int a, int b);          // 0x007c3d30
};
struct App {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual Viewer* GetViewer();                // slot 22 (+0x58)
};
App* __cdecl App_Get();                         // 0x0067dd10 (SP::App)

struct HandleData {
    char pad[8];
    struct { int a; P3 pos; } sub;            // Vec3 at +0xc
};
struct Handle {                                 // gizmo / handle object with a vtable
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual int GetTypeId();                    // slot 4 (+0x10)
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual P3* GetPosition(P3* out);       // slot 9 (+0x24)
    HandleData* FUN_0047e680();                 // 0x0047e680
    Block* FUN_0047e6c0();                      // 0x0047e6c0 (owning block)
};

// @ 0x00498470
bool FUN_00498470(Block* blk, P3* pos, Matrix3* m1, Matrix3* m2, uint8_t e, float f, uint8_t g, char h)
{
    if (blk != 0 && (blk->mSocketBlock || g != 0) && blk->mEditorModel && blk->mEditorModel->FUN_004adc40()) {
        bool is15 = blk->mFlags.test(0xf);
        bool b1 = true;
        P3 outPos;
        if (FUN_004974e0(blk, *(Vec3*)pos, &outPos, &b1, f, g)) {
            Matrix3 tmpRet;
            *m1 = *MoveBlockAndTranslateSnappedBlocks(&tmpRet, blk, *m1);
            Matrix3 saved(*m2);
            if (FUN_004973f0(blk, m2, f, g)) {
                e = 1;
            } else if (is15) {
                e = 0;
                *m2 = saved;
            }
            if (!b1) {
                e = 0;
                *m2 = saved;
            }
            *pos = outPos;
            FUN_0049ec40(blk, pos, m1, m2, e != 0);
            if (!is15) {
                blk->SetBooleanAttribute(0xf, true);
                if (h)
                    FUN_004983d0(blk, is15);
            }
            return true;
        } else if (is15) {
            FUN_00498230(blk, 0);
            if (h)
                FUN_004983d0(blk, is15);
        }
    }
    return false;
}

// @ 0x004986d0
bool FUN_004986d0(Block* blk)
{
    if (blk != 0) {
        bool ok = blk->mEditorModel ? blk->mEditorModel->FUN_004adc40() : false;
        if (!ok)
            return false;
        if (blk->mFlags.test(0xf) && !blk->mSocketBlock) {
            if (blk->mFlags.test(0) || blk->mFlags.test(0x1f))
                return false;
            else
                return true;
        } else {
            return FUN_004986d0(blk->mSocketBlock);
        }
    }
    return false;
}

// @ 0x00498850
bool FUN_00498850(Handle* h, AutoRef<IPicker> picker)
{
    App* app = App_Get();
    P3 camPos;
    char camInfo[14];
    app->GetViewer()->GetCameraLocationInfo(&camPos, camInfo, 0, 0);
    P3 origin;
    origin = camPos;

    P3 tmpA, tmpB, tmpN;
    P3* hpos = h->GetPosition(&tmpA);
    P3* diff = FUN_0041db10(&tmpB, hpos, &camPos);
    Vec3 diffCopy = *(Vec3*)diff;
    P3* nrm = Vector3_Normalize(&tmpN, (P3*)&diffCopy);
    P3 dir;
    dir = *nrm;

    Block* pick = 0;
    if (picker.mp != 0) {
        int type = 1;
        bool swapped = false;
        P3 hit1, n1;
        float d1;
        bool found = picker->RayCast(type, *(Vec3C*)&origin, *(Vec3*)&dir, &hit1, &n1, &d1, true);
        P3 hit2, n2;
        float d2;
        if (picker->RayCast(2, *(Vec3*)&origin, *(Vec3*)&dir, &hit2, &n2, &d2, true)) {
            if (!found || d1 > d2) {
                hit1 = hit2;
                n1 = n2;
                swapped = true;
            }
            found = true;
        }
        if (found) {
            if (swapped)
                pick = picker->PickResult(2, *(Vec3*)&hit1);
            else
                pick = picker->PickResult(type, *(Vec3*)&hit1);
            if (h->GetTypeId() == 0x50e8e23) {
                HandleData* hd = h->FUN_0047e680();
                P3* p = &hd->sub.pos;
                Vec3 d3 = *(Vec3*)FUN_0041db10(&tmpA, &camPos, p);
                float len1 = VectorLength((P3*)&d3);
                float radius = h->FUN_0047e6c0()->FUN_0043f3a0();
                float a = len1 - radius;
                Vec3 d4 = *(Vec3*)FUN_0041db10(&tmpB, &hit1, &camPos);
                float len2 = VectorLength((P3*)&d4);
                if (a < len2)
                    pick = 0;
            }
        }
    }

    bool b1 = false;
    bool b2 = false;
    bool same = (pick == h->FUN_0047e6c0());
    if (!same) {
        Block* sock = h->FUN_0047e6c0()->mSocketBlock;
        if (sock != 0) {
            Block* sock2 = h->FUN_0047e6c0()->mSocketBlock;
            if (!sock2->mFlags.test(7)) {
                Block* sock3 = h->FUN_0047e6c0()->mSocketBlock;
                if (sock3 == pick) {
                    b1 = true;
                } else {
                    Block* sock4 = h->FUN_0047e6c0()->mSocketBlock;
                    Block*** vec = (Block***)&sock4->mSocketBegin;
                    int i = 0;
                    int n = (int)((Block**)vec[1] - (Block**)vec[0]);
                    for (; i < n; i++) {
                        Block** pe = &vec[0][i];
                        Block* q = *pe;
                        if (q == pick) {
                            b2 = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (pick == 0) {
        return false;
    } else if (!same && !b1 && !b2) {
        return true;
    }
    return false;
}

// @ 0x00498f10
Block* FUN_00498f10(Block* blk, Vec3 origin, Vec3 dir, AutoRef<IPicker> picker, P3* outHit, P3* outNormal,
                    int a30, int a34, int a38)
{
    AutoRefModel<Model> model(blk->mEditorModel.mp);
    Block* result = 0;
    int skinId = blk->GetSkinIdentifierForPicking();
    Block* pinned = 0;
    P3 hit, normal;
    if (!blk->mFlags.test(0xb))
        pinned = PickBlockForPinning(blk, a30, origin, dir, &hit, &normal, a38, a34);
    result = pinned;
    *outHit = hit;
    *outNormal = normal;
    if (picker.mp != 0 && skinId != 3) {
        bool swapped = false;
        P3 hit1, n1;
        float d1;
        bool found = picker->RayCast(skinId, origin, dir, &hit1, &n1, &d1, true);
        if (skinId == 1) {
            P3 hit2, n2;
            float d2;
            if (picker->RayCast(2, origin, dir, &hit2, &n2, &d2, true)) {
                if (!found || d1 > d2) {
                    hit1 = hit2;
                    n1 = n2;
                    swapped = true;
                }
                found = true;
            }
        }
        if (found) {
            bool take = true;
            if (pinned != 0) {
                P3 tmp;
                Vec3 d = *(Vec3*)FUN_0041db10(&tmp, (P3*)&origin, &hit);
                float len = VectorLength((P3*)&d);
                take = len > d1;
            }
            if (take) {
                *outHit = hit1;
                *outNormal = n1;
                if (swapped)
                    result = picker->PickResult(2, *(Vec3*)&hit1);
                else
                    result = picker->PickResult(skinId, *(Vec3*)&hit1);
            }
        }
    }
    return result;
}
