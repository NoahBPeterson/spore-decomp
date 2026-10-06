// Slice s00a2c6c0 - EA::Audio::System::DoCommand (0xa2c6c0): the audio system's main-thread command
// dispatcher. Reads typed parameters out of an EA::Audio::Command and forwards them to the
// ISystem virtual methods (called here by vtable byte offset) or to the system's own tables.
#include "types.h"
#include <new>

typedef unsigned char  u8;
typedef unsigned int   u32;

// Virtual call by vtable byte offset (the ISystem / IMixable slot names are not recovered yet).
template<class R> __forceinline R vcall(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template<class R, class A1> __forceinline R vcall(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }
template<class R, class A1, class A2> __forceinline R vcall(void* o, int off, A1 a1, A2 a2)
{ return ((R (__thiscall*)(void*, A1, A2))(*(void***)o)[off / 4])(o, a1, a2); }
template<class R, class A1, class A2, class A3> __forceinline R vcall(void* o, int off, A1 a1, A2 a2, A3 a3)
{ return ((R (__thiscall*)(void*, A1, A2, A3))(*(void***)o)[off / 4])(o, a1, a2, a3); }
template<class R, class A1, class A2, class A3, class A4>
__forceinline R vcall(void* o, int off, A1 a1, A2 a2, A3 a3, A4 a4)
{ return ((R (__thiscall*)(void*, A1, A2, A3, A4))(*(void***)o)[off / 4])(o, a1, a2, a3, a4); }
template<class R, class A1, class A2, class A3, class A4, class A5>
__forceinline R vcall(void* o, int off, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{ return ((R (__thiscall*)(void*, A1, A2, A3, A4, A5))(*(void***)o)[off / 4])(o, a1, a2, a3, a4, a5); }

namespace EA {
namespace Audio {

struct Vec3  { float x, y, z; };
struct Mat33 { float m[9]; };

// ResourceMan-style key: instance, type, group.
struct Key { u32 instance, type, group; };

struct Command {
    u8* mCommandStart; u8* mCommandEnd; u8* mCommandPtr;
    u32 mCommandId; u32 mCommandSize; u32 mNumParameters;
    u32  Type();                                   // 0xfc7e50 (returns mCommandId)
    bool SetT1(int id, int* type, int* size);      // 0xa0fa50
    bool GetFloat(int id, float* out);             // 0xa0fa70
    bool GetUint32(int id, u32* out);              // 0xa0fab0
    const char* GetString8(int id);                // 0xa0fb60
    bool GetVoidPtr(int id, void** out);           // 0xa0fb90
    void* GetData(int id, u32* outSize);           // 0xa0fbd0
    bool GetVector3(int id, float* out);           // 0xa0fc10
    bool GetMatrix33(int id, float* out);          // 0xa0fc60
};

// Reference-counted object pointer (slot 1 of the vtable is Release).
struct IVisualEffect { void** vftable; };
struct VisualEffectRef {
    IVisualEffect* mp;
    VisualEffectRef() : mp(0) {}
    ~VisualEffectRef() { if (mp) vcall<void>(mp, 4); }
    void** AsPPTypeParam();                        // 0xa16f40
};

// Intrusive list of Sounds: the list node sits at +0x10 in the object.
struct ListNode { ListNode* next; ListNode* prev; };
struct Sound { void** vftable; u32 pad[3]; ListNode node; };
struct SoundIter { Sound* p; SoundIter() : p(0) {} };
struct SoundList {
    ListNode anchor;
    SoundIter begin();                             // 0xa21c70
    SoundIter end();                               // 0xa21c90
};
static inline Sound* FromNode(ListNode* n) { return n ? (Sound*)((char*)n - 0x10) : 0; }
static inline Sound* NextSound(Sound* s)   { return FromNode(s->node.next); }

// eastl::hashtable<u32, pair<const u32, Style*>> (fixed allocator), only what DoCommand touches.
struct HashNode { u32 key; void* value; HashNode* next; };
struct HashIter {
    HashNode* node; HashNode** bucket;
    HashIter() : node(0), bucket(0) {}
};
struct StyleTable {
    u32 pad0;
    HashNode** mpBucketArray;
    u32 mnBucketCount;
    HashIter find(const u32& key) const;           // 0x645ed0
};

// eastl::vector<u32>
struct UIntVector {
    u32* mpBegin; u32* mpEnd; u32* mpCapacity;
    void DoInsertValue(u32* pos, const u32& v);    // 0x899480
};

struct Lookup12 { u32 a, b, c; Lookup12() {} };
struct LookupTable {
    Lookup12 Find(const u32& key);                 // 0xa27600
};

struct System {
    void** vftable;                                // ISystem
    u32 pad0[(0x3fc - 4) / 4];
    u8  mbFlag3fc;                                 // +0x3fc
    u8  pad3fd[7];
    StyleTable mStyleTable;                        // +0x404
    u32 pad1[(0x13769c - 0x404 - sizeof(StyleTable)) / 4];
    UIntVector mUIntVector;                        // +0x13769c
    u32 pad2[(0x13795c - 0x13769c - sizeof(UIntVector)) / 4];
    LookupTable mLookup;                           // +0x13795c
    u32 pad3[(0x157438 - 0x13795c - sizeof(LookupTable)) / 4];
    SoundList mSounds;                             // +0x157438
    u32 pad4[(0x15b6d8 - 0x157438 - sizeof(SoundList)) / 4];
    Vec3  mListenerPos[2];                         // +0x15b6d8 (indexed by listener id)
    Mat33 mListenerMat[1];                         // +0x15b6f0 (indexed by listener id)
    u32 pad5[(0x15bbe4 - 0x15b6f0 - sizeof(Mat33)) / 4];
    Vec3 mVec15bbe4;                               // +0x15bbe4
    u8   mbHasVec15bbe4;                           // +0x15bbf0

    bool DoCommand(Command* cmd);
};

// @ 0xa2c6c0
bool System::DoCommand(Command* cmd)
{
    vcall<void>(this, 0x1ec, cmd);
    switch (cmd->Type()) {

    case 0x3475331: {
        u32 id, handle;
        cmd->GetUint32(0x3475381, &id);
        cmd->GetUint32(0x3475385, &handle);
        Vec3 pos;
        Vec3* ppos = 0;
        if (cmd->GetVector3(0x39e41ea, &pos.x))
            ppos = &pos;
        if (vcall<bool>(this, 0x94, id, handle, 0, ppos, 0))
            break;
        mLookup.Find(id);
        vcall<void>(this, 0x98, handle, true);
        return false;
    }

    case 0x3475365: {
        u32 handle;
        if (!cmd->GetUint32(0x3475385, &handle))
            return false;
        if (!vcall<bool>(this, 0x200, cmd, handle))
            vcall<void>(this, 0x128, 0x3a129ee, handle, 0, 0, 0);
        break;
    }

    case 0x347536b:
    case 0x3a12a81: {
        u32 handle, flag;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetUint32(0x34753a0, &flag);
        vcall<void>(this, 0x98, handle, flag != 0);
        break;
    }

    case 0x347536f: {
        u32 handle; float v;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetFloat(0x34753a4, &v);
        vcall<void>(this, 0xa0, handle, v);
        break;
    }

    case 0x3475373: {
        u32 handle; float a, b, c;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetFloat(0x3475391, &a);
        cmd->GetFloat(0x3475395, &b);
        cmd->GetFloat(0x3475398, &c);
        vcall<void>(this, 0xa4, handle, a, b, c);
        break;
    }

    case 0x3475376: {
        u32 a, b, e = 0;
        float f;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        if (cmd->SetT1(0x34753ad, 0, 0))
            cmd->GetUint32(0x34753ad, &e);
        cmd->GetFloat(0x34753aa, &f);
        vcall<void>(this, 0xac, a, b, f, e != 0);
        break;
    }

    case 0x347537a: {
        u32 a, b, size;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        void* data = cmd->GetData(0x34753b0, &size);
        vcall<void>(this, 0xa8, a, b, data, size);
        break;
    }

    case 0x399197f: {
        u32 handle;
        cmd->GetUint32(0x3475385, &handle);
        vcall<void>(this, 0xd8, handle, cmd->GetString8(0x347537e));
        break;
    }

    case 0x3991984: {
        u32 handle; float v;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetFloat(0x34753aa, &v);
        vcall<void>(this, 0xe0, handle, v);
        break;
    }

    case 0x3cdd1a9: {
        u32 a; float v;
        cmd->GetUint32(0x34753a7, &a);
        cmd->GetFloat(0x34753aa, &v);
        vcall<void>(this, 0xfc, a, v);
        break;
    }

    case 0x3992099: {
        u32 listener = 0;
        Vec3 pos;
        Mat33 mat;
        cmd->GetUint32(0x490d2eb, &listener);
        cmd->GetVector3(0x3abafae, &pos.x);
        mListenerPos[listener] = pos;
        cmd->GetMatrix33(0x39e41fc, mat.m);
        mListenerMat[listener] = mat;
        break;
    }

    case 0x407ab38: {
        u32 a, b;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        vcall<void>(this, 0x1d8, a, b);
        break;
    }

    case 0x407ab40: {
        u32 a, b;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        vcall<void>(this, 0x1dc, a, b);
        break;
    }

    case 0x42c8c77: {
        u32 a, b, c = 0, d = 1;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x42c8c8b, &b);
        cmd->GetUint32(0x47fc2f4, &c);
        cmd->GetUint32(0x47fc2fa, &d);
        void* obj = vcall<void*>(this, 0x1d4, a);
        if (obj)
            vcall<void>(obj, 0x1c, b != 0, c, -1.0f, d != 0);
        break;
    }

    case 0x435b26d:
        mbFlag3fc = 1;
        break;

    case 0x436201e: {
        u32 handle;
        u32 info[3] = { 0, 0, 0 };
        cmd->GetUint32(0x4362059, &info[1]);
        cmd->GetUint32(0x3475385, &info[0]);
        cmd->GetUint32(0x4362049, &info[2]);
        vcall<void>(this, 0x1bc, info);
        cmd->GetUint32(0x3475385, &handle);
        Sound* s   = FromNode(mSounds.anchor.next);
        Sound* end = FromNode(&mSounds.anchor);
        while (s != end) {
            if (vcall<bool>(s, 0x38, handle))
                vcall<void>(s, 0x34);
            s = NextSound(s);
        }
        break;
    }

    case 0x437419c: {
        u32 a = 0, b = 0, c = 0;
        VisualEffectRef ref;
        cmd->GetUint32(0x43741f1, &a);
        cmd->GetUint32(0x43741ff, &b);
        cmd->GetUint32(0x43743cb, &c);
        if (a == 0 || b == 0 || c == 0)
            break;
        HashIter it = mStyleTable.find(b);
        if (it.node == mStyleTable.mpBucketArray[mStyleTable.mnBucketCount])
            break;
        void* style = it.node->value;
        if (vcall<bool>(this, 0xe4, a, ref.AsPPTypeParam()))
            vcall<void>(style, 0x18, c, ref.mp);
        break;
    }

    case 0x43741d8: {
        u32 a = 0, b = 0, c = 0;
        VisualEffectRef ref;
        cmd->GetUint32(0x43741f1, &a);
        cmd->GetUint32(0x43741ff, &b);
        cmd->GetUint32(0x43743cb, &c);
        if (a == 0 || b == 0 || c == 0)
            break;
        HashIter it = mStyleTable.find(b);
        if (it.node == mStyleTable.mpBucketArray[mStyleTable.mnBucketCount])
            break;
        void* style = it.node->value;
        if (vcall<bool>(this, 0xe4, a, ref.AsPPTypeParam()))
            vcall<void>(style, 0x1c, c, ref.mp);
        break;
    }

    case 0x44888b0: {
        u32 flag = 0;
        cmd->GetUint32(0x34753a0, &flag);
        vcall<void>(this, 0x80, flag != 0);
        break;
    }

    case 0x44888b5: {
        SoundIter s = mSounds.begin();
        SoundIter e = mSounds.end();
        while (s.p != e.p) {
            if (vcall<bool>(s.p, 0x20, -1, 0))
                vcall<void>(s.p, 0x80, 3, 0);
            s.p = NextSound(s.p);
        }
        break;
    }

    case 0x44f2b21: {
        u32 id, b;
        u32 c = 0, d = 1;
        cmd->GetUint32(0x3475385, &id);
        cmd->GetUint32(0x42c8c8b, &b);
        cmd->GetUint32(0x47fc2f4, &c);
        cmd->GetUint32(0x47fc2fa, &d);
        bool bB = b != 0;
        bool bD = d != 0;
        SoundIter s = mSounds.begin();
        SoundIter e = mSounds.end();
        while (s.p != e.p) {
            if (vcall<bool>(s.p, 0x3c, id))
                vcall<void>(s.p, 0x1c, bB, c, 2.0f, bD);
            s.p = NextSound(s.p);
        }
        UIntVector& v = mUIntVector;
        u32* p = v.mpBegin;
        u32* last = v.mpEnd;
        for (; p != last; ++p) {
            if (*p == id) {
                if (b == 0) {
                    *p = last[-1];
                    --v.mpEnd;
                }
                goto done;
            }
        }
        if (v.mpEnd < v.mpCapacity)
            ::new((void*)v.mpEnd++) u32(id);
        else
            v.DoInsertValue(v.mpEnd, id);
        break;
    }

    case 0x45010e7: {
        u32 a, b, c;
        void* p = 0;
        void* q = 0;
        cmd->GetUint32(0x4501144, &a);
        cmd->GetUint32(0x4502374, &b);
        cmd->GetUint32(0x4597e49, &c);
        cmd->GetVoidPtr(0x45705b8, &p);
        cmd->GetVoidPtr(0x45706c7, &q);
        vcall<void>(this, 0x1f8, a, c, b, p, q);
        break;
    }

    case 0x4503efa: {
        u32 a;
        cmd->GetUint32(0x4501144, &a);
        vcall<void>(this, 0x1fc, a);
        break;
    }

    case 0x4640907: {
        u32 a, size;
        u32 n = 0;
        void* p = 0;
        void* q = 0;
        cmd->GetUint32(0x4501144, &a);
        cmd->GetVoidPtr(0x45705b8, &p);
        cmd->GetVoidPtr(0x45706c7, &q);
        void* data = cmd->GetData(0x4501150, &size);
        if (data)
            n = size >> 2;
        vcall<void>(this, 0x1f4, a, data, n, p, q);
        break;
    }

    case 0x4fe2220: {
        u32 a;
        cmd->GetUint32(0x4362049, &a);
        vcall<void>(this, 0x120, a);
        break;
    }

    case 0x566783b: {
        u32 a, e = 0;
        float f;
        cmd->GetUint32(0x34753a7, &a);
        if (cmd->SetT1(0x34753ad, 0, 0))
            cmd->GetUint32(0x34753ad, &e);
        cmd->GetFloat(0x34753aa, &f);
        vcall<void>(this, 0xb0, a, f, e != 0);
        break;
    }

    case 0x60c62f5: {
        u32 size;
        u32* ids = (u32*)cmd->GetData(0x60c631d, &size);
        if (ids) {
            for (u32 remaining = size >> 2; remaining != 0; --remaining) {
                u32 id = *ids++;
                VisualEffectRef ref;
                if (vcall<bool>(this, 0x138, id, ref.AsPPTypeParam(), 0x21407ee)) {
                    u32 count;
                    Key* keys;
                    if (vcall<bool>(ref.mp, 0x4c, 0x701ed91e, &count, &keys) && count != 0) {
                        for (u32 i = 0; i < count; ++i) {
                            Key k = *keys++;
                            k.type = 0x1a527db;
                            k.group = 0x21407ee;
                            vcall<void>(this, 0x194, &k, 0, 0);
                        }
                    }
                } else {
                    Key k;
                    k.instance = id;
                    k.type = 0x1a527db;
                    k.group = 0x21407ee;
                    vcall<void>(this, 0x194, &k, 0, 0);
                }
            }
        }
        break;
    }

    case 0x673a543: {
        u32 a, b;
        cmd->GetUint32(0x4362049, &a);
        cmd->GetUint32(0x3475385, &b);
        vcall<void>(this, 0x104, a, b);
        break;
    }

    case 0x673a567: {
        u32 a, b;
        cmd->GetUint32(0x4362049, &a);
        cmd->GetUint32(0x3475385, &b);
        vcall<void>(this, 0x10c, a, b);
        break;
    }

    case 0x7ead55c: {
        u32 a;
        if (cmd->GetUint32(0x4362049, &a)) {
            SoundIter s = mSounds.begin();
            SoundIter e = mSounds.end();
            while (s.p != e.p) {
                if (vcall<bool>(s.p, 0x3c, a))
                    vcall<void>(s.p, 0x80, 3, 0);
                s.p = NextSound(s.p);
            }
        }
        break;
    }

    case 0x7f43dc0:
        cmd->GetVector3(0x39e41ea, &mVec15bbe4.x);
        mbHasVec15bbe4 = 1;
        break;

    case 0x7f43dd0:
        mbHasVec15bbe4 = 0;
        break;
    }
done:
    return true;
}

} // namespace Audio
} // namespace EA
