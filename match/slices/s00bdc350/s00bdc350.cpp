// Slice s00bdc350: effect, minimap and range-helper functions.
//
// Targets:
//   00bdc350  effect attach/refresh with XformMsg
//   00bdc4a0  effect enable/disable (bool)
//   00bdc6f0  range-for over 0xc-byte entries, virtual notify
//   00bdc7b0  fill an output iterator from a range of objects
//   00bdc8a0  combat/empire reaction update (8-byte delta)
//   00bdd120  minimap message handler
//   00bdd2f0  copy a transform block into object+0x70
//   00bdd350  two virtual calls (report + notify)
#include <stddef.h>
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// Shared vtable-call helpers.
// ---------------------------------------------------------------------------
typedef void (__thiscall *Void0)(void*);
typedef void (__thiscall *Void1)(void*, void*);
typedef int  (__thiscall *Int1)(void*, int);
typedef bool (__thiscall *Bool2)(void*, int, void*);

struct VObj { void** mpVtbl; };

// ---------------------------------------------------------------------------
// 00bdd350
// ---------------------------------------------------------------------------
// ecx is not used; both parameters are ordinary stack objects.  The first is
// an object whose vtable supplies the final notify method, the second is a
// pointer to an optional object whose vtable supplies the query method.
// @ 0x00bdd350
bool __cdecl FUN_00bdd350(void* self, void** other)
{
    int value = 0;
    void* obj = *other;
    if (obj != 0)
        value = ((Int1)(*(void***)obj)[0xb8 / 4])(obj, 0x179c807);

    ((Void1)(*(void***)self)[0x2c / 4])(self, (void*)value);
    return true;
}

// ---------------------------------------------------------------------------
// 00bdd2f0
// ---------------------------------------------------------------------------
// Copies the cached transform (three ints/float bits from +0x51c..+0x524) and
// the constant 8.0f into the object reached through +0x70, at +0x50.
struct Obj2f0 {
    char pad00[0x70];
    char* mp70;                 // +0x70
    char pad74[0x320 - 0x74];
    int m320;                   // +0x320
    char pad324[0x51c - 0x324];
    int m51c;                   // +0x51c (float bits)
    int m520;                   // +0x520 (float bits)
    int m524;                   // +0x524 (float bits)
    void __thiscall Notify();   // 0x00bdbaa0
};

// @ 0x00bdd2f0
void __fastcall FUN_00bdd2f0(Obj2f0* self)
{
    if (self->m320 == 0)
        return;

    self->Notify();

    struct Transform2f0 {
        int mX;                 // +0x50
        int mY;                 // +0x54
        int mZ;                 // +0x58
        float mW;               // +0x5c
        int mE;                 // +0x60
        Transform2f0(int x, int y, int z, float w, int e)
            : mX(x), mY(y), mZ(z), mW(w), mE(e) {}
    };
    int zero = 0;
    *(Transform2f0*)(self->mp70 + 0x50) =
        Transform2f0(self->m51c, self->m520, self->m524,
                     *(float*)0x013eeda0, zero);
}

// ---------------------------------------------------------------------------
// 00bdc6f0
// ---------------------------------------------------------------------------
// The range is an array of 0xc-byte entries; each entry owns two optional
// objects.  Every live object receives a virtual notify with the same context.
struct Entry6f0 {
    void* mpFirst;              // +0x00
    void* mpSecond;             // +0x04
    int mPad;                   // +0x08
};

struct Range6f0 {
    Entry6f0* mpBegin;          // +0x00
    Entry6f0* mpEnd;            // +0x04
};

// @ 0x00bdc6f0
bool __cdecl FUN_00bdc6f0(void* context, Range6f0* range)
{
    Entry6f0* it = range->mpBegin;
    Entry6f0* end = range->mpEnd;
    if (it != end) {
        do {
            if (it != 0) {
                void* first = it->mpFirst;
                if (first != 0)
                    ((Void1)(*(void***)first)[0x1c / 4])(first, context);

                void* second = it->mpSecond;
                if (second != 0)
                    ((Void1)(*(void***)second)[0x1c / 4])(second, context);
            }
            it = (Entry6f0*)((char*)it + 0xc);
        } while (it != end);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 00bdc7b0
// ---------------------------------------------------------------------------
// Writes `value` through the output iterator, then for each source object
// stores its +0x34 subobject through the iterator and calls that subobject's
// virtual method at +0xbc.  The iterator is advanced by one int per element.
struct Object7b0 {
    char pad00[0x34];
    int mSub;                   // +0x34
};

// @ 0x00bdc7b0
int** __cdecl FUN_00bdc7b0(int** out, Object7b0** first, Object7b0** last,
                          int value)
{
    *out = (int*)value;
    while (first != last) {
        if (*out != 0) {
            Object7b0* obj = *first;
            int* sub = obj ? (int*)((char*)obj + 0x34) : 0;
            *(*out) = (int)sub;
            if (sub != 0)
                ((Void0)(*(void***)sub)[0xbc / 4])(sub);
        }
        *out = *out + 1;
        ++first;
    }
    return out;
}

// ---------------------------------------------------------------------------
// Shared types for the effect/minimap cluster.
// ---------------------------------------------------------------------------
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef unsigned long long u64;
extern "C" long __stdcall _InterlockedExchange(volatile long*, long);

struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[9]; };

struct XformMsg {                       // ctor 0x00434040, 0x38 bytes
    u16 mFlags;                         // +0x00
    short mCount;                       // +0x02
    Vector3 mPosition;                  // +0x04
    float mScale;                       // +0x10
    Matrix3 mRotation;                  // +0x14
    XformMsg();
    void SetPos(const Vector3& v) { mPosition = v; mFlags |= 4; ++mCount; }
    void SetRot(const Matrix3& m) { mRotation = m; mFlags |= 2; ++mCount; }
};

struct IEffect {
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual void Start(int flags);      // +0x08
    virtual void Stop(int flags);       // +0x0c
    virtual void v10();                 // +0x10
    virtual void v14();                 // +0x14
    virtual void SetTransform(XformMsg* msg);  // +0x18
};

struct EffectsMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateEffect(u32 id, int flags, IEffect** out);  // +0x2c
};

struct Obj590 {
    char padC4[0xc4];
    Vector3 mC4;                        // +0xc4
    char* __thiscall F00bef950();       // 0x00bef950
};

struct Timer {
    char m[0x20];
    void __thiscall Restart();          // 0x00bc3130
};

struct SelfB {
    char pad00[0x120];
    void* m120Vtbl;                     // +0x120 (inline subobject)
    char pad124[0x220 - 0x124];
    float m220;                         // +0x220
    char pad224[0x2cc - 0x224];
    int m2cc;                           // +0x2cc
    int m2d0;                           // +0x2d0
    char pad2d4[0x320 - 0x2d4];
    void* m320;                         // +0x320
    char pad324[0x58c - 0x324];
    u8 m58c;                            // +0x58c
    char pad58d[0x590 - 0x58d];
    Obj590* m590;                       // +0x590
    char pad594[0x64c - 0x594];
    int m64c;                           // +0x64c
    char pad650[0x758 - 0x650];
    float m758;                         // +0x758
    int m75c;                           // +0x75c
    char pad760[0x764 - 0x760];
    int m764;                           // +0x764
    IEffect* m768;                      // +0x768
    char pad76c[4];
    Timer m770;                         // +0x770
    char pad790[0x7d4 - 0x790];
    IEffect* m7d4;                      // +0x7d4

    void __thiscall F00bdbc20(void* p); // 0x00bdbc20
    void __thiscall F00bdbf10();        // 0x00bdbf10
    int __thiscall F00bf01e0();         // helper on the noun result
    bool __thiscall FUN_00bdc4a0(char enable);
    void __thiscall FUN_00bdc8a0(u64 delta);
    void __thiscall FUN_00bdd120(float amount, int key);
};

EffectsMgr* __cdecl EffectsManager();                    // 0x0067ddd0
Vector3 __cdecl normalized_safe(const Vector3& v);       // 0x00449c20
Matrix3& __cdecl Matrix3FromQuaternion(Matrix3& out, const Quaternion& q); // 0x0059c190
Matrix3& __cdecl QuaternionToMatrix(Matrix3& out, const Quaternion& q);    // 0x004a9b40
int __cdecl GetPlayerEmpireID();                         // 0x01021090
u32 __cdecl GetCurrentGameMode();                        // 0x00b5b800
void __cdecl DoCommunityReaction(void* self, float f, const Vector3& pos); // 0x00ff5270
void* __cdecl RelationshipManager();                     // 0x00b3d2c0
void* __cdecl FUN_00b3d240();                            // 0x00b3d240
void* __cdecl MessageServer();                           // 0x00883860

struct RelationshipMgr {
    float __thiscall RecordEvent(int a, int b, u32 ev, float amount); // 0x00d06240
};

struct NounMgr {
    void* __thiscall FUN_00b25f40(int id);  // 0x00b25f40
    int __thiscall GetPlayerEmpireOrMinus1(); // 0x00b1f9d0
};

struct NounObj {
    int __thiscall FUN_00bf01e0();          // 0x00bf01e0
};

NounMgr* __cdecl NounManager();              // 0x00b3d300

struct MessageBasicRC5 {
    void* mpVtbl;                           // +0x00
    volatile int mRefCount;                 // +0x04
    void* mData0;                           // +0x08
    char pad0c[4];
    u32 mData1;                             // +0x10
    char pad14[0x30 - 0x14];
    u32 mId;                                // +0x30
    char pad34[4];
    int mRCFlags;                           // +0x38
    char pad3c[4];
    void __thiscall Destruct();             // 0x00421cf0
};

struct CivStrategy {
    void __thiscall PostFeedback(SelfB* self, u32 a, u32 b, void* pos,
                                 Vector4* p4, int x, int y); // 0x00cf9040
};
CivStrategy* __cdecl CivModeStrategyGet();   // 0x00cf74c0

struct RandomGlobal {
    double __thiscall RandomDouble();        // 0x009360d0
};

// ---------------------------------------------------------------------------
// 00bdc350
// ---------------------------------------------------------------------------
// @ 0x00bdc350
void __fastcall FUN_00bdc350(SelfB* self)
{
    if (self->m764 != 0) {
        if (self->m768 != 0) {
            self->m768->Stop(0);
            IEffect* old = self->m768;
            self->m768 = 0;
            if (old != 0)
                old->Release();
        }
        self->m770.Restart();
        return;
    }

    char* p = self->m590->F00bef950();
    self->F00bdbc20(p + 0x504);

    if (self->m768 == 0) {
        EffectsMgr* mgr = EffectsManager();
        IEffect* old = self->m768;
        if (old != 0) {
            self->m768 = 0;
            old->Release();
        }
        if (mgr->CreateEffect(0xb332de96, 0, &self->m768)) {
            XformMsg msg;
            Vector3* pos = ((Vector3* (__thiscall*)(void*))
                            (*(void***)&self->m120Vtbl)[0x2c / 4])
                           (&self->m120Vtbl);
            msg.SetPos(*pos);
            Quaternion* q = ((Quaternion* (__thiscall*)(void*))
                             (*(void***)((char*)self->m320 + 0x34))[0x30 / 4])
                            ((char*)self->m320 + 0x34);
            Matrix3 rot;
            Matrix3FromQuaternion(rot, *q);
            msg.SetRot(rot);
            self->m768->SetTransform(&msg);
            self->m768->Start(0);
        }
    }
    self->m770.Restart();
}

// ---------------------------------------------------------------------------
// 00bdc4a0
// ---------------------------------------------------------------------------
// @ 0x00bdc4a0
bool __thiscall SelfB::FUN_00bdc4a0(char enable)
{
    SelfB* self = this;
    IEffect* effect = self->m7d4;
    bool had = effect != 0;

    if (enable != 0) {
        if (effect == 0) {
            EffectsMgr* mgr = EffectsManager();
            IEffect* old = self->m7d4;
            if (old != 0) {
                self->m7d4 = 0;
                old->Release();
            }
            if (mgr->CreateEffect(0xc66a87f2, 0, &self->m7d4)) {
                void* sub = (char*)self->m320 + 0x34;
                Vector3* posPtr = ((Vector3* (__thiscall*)(void*))
                                   (*(void***)sub)[0x2c / 4])(sub);
                Vector3 pos;
                pos.x = posPtr->x;
                pos.y = posPtr->y;
                pos.z = posPtr->z;
                float scale = *(float*)((char*)((void* (__thiscall*)(void*))
                                  (*(void***)sub)[0x68 / 4])(sub) + 0x14);
                Vector3 n = normalized_safe(pos);
                pos.x = n.x * scale + pos.x;
                pos.y = n.y * scale + pos.y;
                pos.z = n.z * scale + pos.z;

                XformMsg msg;
                msg.SetPos(pos);
                Quaternion* q = ((Quaternion* (__thiscall*)(void*))
                                 (*(void***)sub)[0x30 / 4])(sub);
                Matrix3 rot;
                QuaternionToMatrix(rot, *q);
                msg.SetRot(rot);
                self->m7d4->SetTransform(&msg);
                self->m7d4->Start(0);
            }
        }
        return had;
    }

    if (effect != 0) {
        effect->Stop(1);
        IEffect* old = self->m7d4;
        if (old != 0) {
            self->m7d4 = 0;
            old->Release();
        }
    }
    return had;
}

// ---------------------------------------------------------------------------
// 00bdc8a0
// ---------------------------------------------------------------------------
// @ 0x00bdc8a0
void __thiscall SelfB::FUN_00bdc8a0(u64 delta)
{
    SelfB* self = this;
    if (self->m2cc == 2 || self->m2d0 < 1) {
        if (self->m2cc != 0 && self->m2d0 == 0)
            self->m2cc = 0;
    } else {
        if (self->m64c <= self->m2d0) {
            self->m2cc = 2;
            int empire = ((int (__thiscall*)(void*))
                          (*(void***)self)[0x4c / 4])(self);
            if (empire != GetPlayerEmpireID()) {
                float f = ((RelationshipMgr*)RelationshipManager())
                          ->RecordEvent(((int (__thiscall*)(void*))
                                         (*(void***)self)[0x4c / 4])(self),
                                        GetPlayerEmpireID(), 0x526e52d, 1.0f);
                Vector3* pos = ((Vector3* (__thiscall*)(void*))
                                (*(void***)&self->m120Vtbl)[0x2c / 4])
                               (&self->m120Vtbl);
                DoCommunityReaction(self, f, *pos);
                self->F00bdbf10();
            }
            void* obj = FUN_00b3d240();
            char buf[12];
            void* value = ((void* (__thiscall*)(void*, char*, void*))
                           (*(void***)self)[0x5c / 4])(self, buf,
                                                       (void*)0x0168bd70);
            ((void (__thiscall*)(void*, u32, void*))
             (*(void***)obj)[0x60 / 4])(obj, 0x2df3697, value);
        }
        if (self->m2cc == 1) {
            double r = ((RandomGlobal*)0x01601760)->RandomDouble();
            if (r < *(float*)0x01471064)
                ++self->m2d0;
        }
    }

    if (self->m220 > 0.0f)
        self->m220 -= (float)delta * 0.001f;
    if (self->m220 < 0.0f)
        self->m220 = 0.0f;
}

// ---------------------------------------------------------------------------
// 00bdd120
// ---------------------------------------------------------------------------
// @ 0x00bdd120
void __thiscall SelfB::FUN_00bdd120(float amount, int key)
{
    SelfB* self = this;
    int empire = ((int (__thiscall*)(void*))
                  (*(void***)self)[0x4c / 4])(self);
    if (key == empire)
        return;

    if (self->m75c == -1)
        self->m75c = key;

    float f = *(float*)0x013eeda0 * amount;
    NounObj* noun = (NounObj*)NounManager()->FUN_00b25f40(key);
    int count = noun->FUN_00bf01e0();
    f = f / ((float)count + *(float*)0x0147b9f0);

    if (self->m75c == key)
        self->m758 += f;
    else
        self->m758 -= f;

    if (self->m758 < 0.0f) {
        self->m75c = key;
        self->m758 = -self->m758;
        return;
    }

    if (self->m758 > *(float*)0x013ec4d0) {
        self->m758 = *(float*)0x013ec4d0;
        if (self->m75c == NounManager()->GetPlayerEmpireOrMinus1()) {
            MessageBasicRC5 msg;
            msg.mId = 0;
            msg.mpVtbl = (void*)0x013eb90c;
            _InterlockedExchange((volatile long*)&msg.mRefCount, 0);
            msg.mpVtbl = (void*)0x013eb844;
            msg.mRCFlags = 0;
            msg.mId = 0x53039b6;
            msg.mData0 = self;
            msg.mData1 = 0xffffff00;

            void* server = MessageServer();
            ((void (__thiscall*)(void*, u32, MessageBasicRC5*, int))
             (*(void***)server)[0x14 / 4])(server, msg.mId, &msg, 0);

            if (GetCurrentGameMode() == 0x01654c04 && self->m58c == 0) {
                Vector3* p = &self->m590->mC4;
                self->m58c = 1;
                Vector4 pos = { p->x, p->y, p->z, *(float*)0x01485720 };
                CivModeStrategyGet()->PostFeedback(
                    self, 0x927dca97, 0xaa9a8ed7,
                    ((void* (__thiscall*)(void*))
                     (*(void***)&self->m120Vtbl)[0x2c / 4])(&self->m120Vtbl),
                    &pos, 0, 0);
            }
            msg.Destruct();
        }
    }
}
