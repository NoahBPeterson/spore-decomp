// src/game/SPAudio/AudioResourceConfiguration.cpp -- migrated from slice(s) s00a196f0, s00a187f0, s00a168c0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioResourceConfiguration.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResourceConfiguration.h"
#include "EA/Audio/ResponseCurve.h"
#include <intrin.h>
#include <string.h>

// ---- items of slice s00a168c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef unsigned int   u32;
struct Variant {
    union {
        u32   u;
        void* p;
        float f;
        char  bytes[0x10];
    };
    u16 mFlags;    // +0x10
    u16 mTypeId;   // +0x12
};
struct Key { u32 a, b, c; };
typedef bool (__thiscall* GetPropertyFn)(void*, u32, Variant const*&);
struct RC {
    void* vtbl;   // +0x00 (IConfiguration)

    bool GetPropertyAsKey(u32 key, Key* out);                        // 00a174d0
    bool GetPropertyAsKeyInstance(u32 key, u32* out);                // 00a17520
    bool GetPropertyAsFloatArray(u32 key, u32* count, const void** arr);  // 00a17560
    bool GetPropertyAsUint32Array(u32 key, u32* count, const void** arr); // 00a175c0
    bool GetPropertyAsKeyArray(u32 key, u32* count, const void** arr);    // 00a17620

    bool GetProperty(u32 key, Variant const*& v)
    {
        GetPropertyFn f = *(GetPropertyFn*)((char*)(*(void**)this) + 0x20);
        return f(this, key, v);
    }
};
// ---- items of slice s00a168c0 end

// ---- items of slice s00a187f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, int lowercase);   // 0x00932E80
}
}
struct PropertyTypeMap {
    uint32_t& operator[](const uint32_t& key);   // 0x00643A40 eastl::map<uint,uint>::operator[]
};
namespace EA {
namespace Audio {
class FactoryConfiguration { public:
    char pad[0x40];
    PropertyTypeMap mLegacyTypes;   // +0x40
    void AddLegacyPropertyTypes();
};
}
}
namespace EA {
namespace Audio {
#define H(s) EA::Hash::FNV1_String8(s, 0x811c9dc5, 1)
}
}
// ---- items of slice s00a187f0 end

// ---- items of slice s00a196f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool  f_0093a700(void* reader, void* dst, int count, int flag);   // read raw
extern bool  f_0093a780(void* reader, void* dst, int count, int flag);   // read raw
extern bool  f_0093ac80(void* reader, void* dst);                        // ReadBool
extern bool  f_00593840(void* reader, void* dst);                        // read object
extern bool  f_00692720(void* reader, void* dst, int z);
extern bool  f_00692740(void* reader, void* dst, int z);
extern bool  f_00692760(void* reader, void* dst, int z);
extern void* f_00f473a0(int size, const char* name, int a, int b, const char* file, int line);
extern void  f_00f47380(void* p);                                        // operator delete
extern void  f_00542b80(void* dst, void* src);                           // Variant::operator=
extern void* f_008de1a0(void);                                           // Eapd::Debug::ObjectError
extern void  __stdcall f_006a2b80(void* self, unsigned n);               // vector resize (ret 4)
typedef unsigned char      u8;
struct Variant_s00a1_96f0 {
    void*          mData;      // 0x00
    int            mDim0;      // 0x04
    int            mDim1;      // 0x08
    int            mExtra;     // 0x0c
    unsigned short mFlags;     // 0x10
    unsigned short mType;      // 0x12
};
struct IOReader {
    void*               mVtbl;  // 0x00
    void* readObj(void* obj, int size);
};
struct Mutex {
    char mData[0x30];      // retail EA::Thread::Mutex is 0x30 bytes
    void ctor(int a, int b);
    void dtor();
};
#define TAG_A ((void*)0x01667bac)
#define TAG_B ((void*)0x01667bad)
#define TAG_C ((void*)0x01667bae)
struct ResConfig {
    char  mPad0[0x24];
    void* mPropBegin;          // 0x24
    void* mPropEnd;            // 0x28
    void* mPropCap;            // 0x2c
    char  mPad1[0x3c - 0x30];
    void* mChildren;           // 0x3c
    char  mPad2[0x360 - 0x40];
    int   mNumPoints;          // 0x360

    char  ReadVariant(IOReader* reader, Variant_s00a1_96f0* v);
    char  Read(IOReader* reader);
};
struct RBTree_s00a1_96f0 {   // eastl rbtree storage at FactoryConfiguration+0x40
    void* mNodeParent;                    // +0x00 (unused by this slice)
    void  DoNukeSubtree(void* node);      // 0x009a9600
};
struct FactoryConfiguration_s00a1_96f0 {
    void* mVtbl;        // 0x00
    void* mField04;     // 0x04
    void* mField08;     // 0x08
    char  mPad[0x04];
    Mutex mMutex;       // 0x10
    RBTree_s00a1_96f0 mTree;  // 0x40
    void* mAnchor;      // 0x44
    void* mField48;     // 0x48
    void* mField4c;     // 0x4c
    u8    mField50;     // 0x50
    char  mPad3[0x54 - 0x51];
    void* mField54;     // 0x54
    char  mPad4[0x5c - 0x58];
    void* mField5c;     // 0x5c
    void* mField60;     // 0x60
    void* mField64;     // 0x64

    FactoryConfiguration_s00a1_96f0();
    ~FactoryConfiguration_s00a1_96f0();
    void AddLegacyPropertyTypes();  // 0x00a18d90 (FactoryConfiguration::AddLegacyPropertyTypes)
};
// ---- items of slice s00a196f0 end

// @ 0x00a174d0
bool RC::GetPropertyAsKey(u32 key, Key* out)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20) {
        const void* src = (v->mFlags & 0x30) ? v->p : (const void*)v;
        *out = *(const Key*)src;
        return true;
    }
    return false;
}

// @ 0x00a17520
bool RC::GetPropertyAsKeyInstance(u32 key, u32* out)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20) {
        const void* src = (v->mFlags & 0x30) ? v->p : (const void*)v;
        u32 value = *(const u32*)src;
        *out = value;
        return true;
    }
    return false;
}

// @ 0x00a17560
bool RC::GetPropertyAsFloatArray(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x0d && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// @ 0x00a175c0
bool RC::GetPropertyAsUint32Array(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x0a && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// @ 0x00a17620
bool RC::GetPropertyAsKeyArray(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20 && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// @ 0x00a18d90
namespace EA { namespace Audio {
void FactoryConfiguration::AddLegacyPropertyTypes()
{
    mLegacyTypes[H("parent")] = 0x20;
    mLegacyTypes[H("gain")] = 0xd;
    mLegacyTypes[H("pan")] = 0xd;
    mLegacyTypes[H("pitch")] = 0xd;
    mLegacyTypes[H("mindistance")] = 0xd;
    mLegacyTypes[H("maxdistance")] = 0xd;
    mLegacyTypes[H("rolloff")] = 0xd;
    mLegacyTypes[H("streambuffersize")] = 0xa;
    mLegacyTypes[H("streambufferreadsize")] = 0xa;
    mLegacyTypes[H("is3d")] = 1;
    mLegacyTypes[H("islooped")] = 1;
    mLegacyTypes[H("samples")] = 0x80000020;
    mLegacyTypes[H("fadein")] = 0xd;
    mLegacyTypes[H("fadeout")] = 0xd;
    mLegacyTypes[H("priority")] = 0xd;
    mLegacyTypes[H("autoduck")] = 1;
    mLegacyTypes[H("duckcurve")] = 0x8000000d;
    mLegacyTypes[H("ducks")] = 1;
    mLegacyTypes[H("attenuation")] = 0x8000000d;
    mLegacyTypes[H("primitives")] = 0x80000013;
    mLegacyTypes[H("soundtype")] = 0x20;
    mLegacyTypes[H("enable")] = 0xd;
    mLegacyTypes[H("startdelay")] = 0xd;
    mLegacyTypes[H("showmindistance")] = 1;
    mLegacyTypes[H("footcurvenumlegstogain")] = 0x8000000d;
    mLegacyTypes[H("footcurveveltogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvelentohipass")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstopitch")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetopitch")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstohipass")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetohipass")] = 0x8000000d;
    mLegacyTypes[H("atmospheric")] = 0x8000000d;
    mLegacyTypes[H("polyphony")] = 0xa;
    mLegacyTypes[H("streampoolguid")] = 0x20;
    mLegacyTypes[H("probability")] = 0xd;
    mLegacyTypes[H("dspchain")] = 0x80000013;
    mLegacyTypes[H("syms")] = 0x80000013;
    mLegacyTypes[H("dacoutputmode")] = 0x13;
    mLegacyTypes[H("ignorecontext")] = 1;
    mLegacyTypes[H("voicetemplate")] = 0x20;
    mLegacyTypes[H("foottype")] = 0x13;
    mLegacyTypes[H("mouthtype")] = 0x13;
    mLegacyTypes[H("weapontype")] = 0x13;
    mLegacyTypes[H("time")] = 0xd;
    mLegacyTypes[H("wetlevel")] = 0x8000000d;
    mLegacyTypes[H("reverbtime")] = 0xd;
    mLegacyTypes[H("reverbspacesize")] = 0xd;
    mLegacyTypes[H("timeinvariantpitch")] = 0xd;
    mLegacyTypes[H("listeneroffset")] = 0x8000000d;
}
}}  // namespace EA::Audio

// @ 0x00a196f0
char ResConfig::ReadVariant(IOReader* reader, Variant_s00a1_96f0* v)
{
    bool ok;
    if (v->mType != 0) {
        f_00542b80(v, (void*)0x0166d9a0);
    }
    if (!f_0093a700(reader, &v->mType, 1, 0) ||
        !f_0093a700(reader, &v->mFlags, 1, 0)) {
        ok = false;
    } else {
        ok = true;
    }

    if ((v->mFlags & 0x30) == 0) {
        switch (v->mType) {
        case 1:
            if (ok && f_0093ac80(reader, v)) return 1;
            break;
        case 2:
        case 6:
            if (ok && f_00593840(reader, v)) return 1;
            break;
        case 3:
        case 8:
            if (ok && f_00692720(reader, v, 0)) return 1;
            break;
        case 5:
            if (ok && f_00593840(reader, v)) return 1;
            break;
        case 7:
            if (ok && f_00692720(reader, v, 0)) return 1;
            break;
        case 9:
        case 10:
        case 13:
            if (ok && f_00692740(reader, v, 0)) return 1;
            break;
        case 11:
        case 12:
        case 14:
            if (ok && f_00692760(reader, v, 0)) return 1;
            break;
        case 0x11:
            v->mType = 0;
            v->mFlags = 0;
            return 0;
        case 0x12:
            v->mData = TAG_A;
            v->mDim0 = (int)0x01667bac;
            v->mDim1 = (int)0x01667bad;
            {
                extern bool f_00a17a00(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                if (ok && f_00a17a00(this, reader, v)) return 1;
            }
            break;
        case 0x13:
            v->mData = TAG_A;
            v->mDim0 = (int)0x01667bac;
            v->mDim1 = (int)0x01667bae;
            {
                extern bool f_00a18d20(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                if (ok && f_00a18d20(this, reader, v)) return 1;
            }
            break;
        default:
            if (ok && reader->readObj(v, 0x10)) {
                v->mFlags &= 0xfff2;
                return 1;
            }
            v->mFlags &= 0xfff2;
            return 0;
        }
    } else if ((v->mFlags & 0x40) == 0) {
        bool ok2;
        if (ok && f_0093a780(reader, &v->mDim1, 1, 0) &&
            f_0093a780(reader, &v->mDim0, 1, 0)) {
            ok2 = true;
        } else {
            ok2 = false;
        }
        void* arr = f_00f473a0(v->mDim1 * v->mDim0, "Audio/EAVariant/kfCArray", 0, 0, 0, 0);
        int stride = v->mDim1;
        char* p = (char*)arr;
        char* end = (char*)arr + v->mDim1 * v->mDim0;
        v->mData = arr;
        if (p >= end) return (char)(ok2 ? 1 : 0);

        do {
            bool ok3 = ok2;
            switch (v->mType - 1) {
            case 0:
                if (!ok3 || !f_0093ac80(reader, p)) ok3 = false;
                break;
            case 1:
            case 5:
                if (!ok3 || !f_00593840(reader, p)) ok3 = false;
                break;
            case 2:
            case 7:
                if (!ok3 || !f_00692720(reader, p, 0)) ok3 = false;
                break;
            case 4:
                if (!ok3 || !f_00593840(reader, p)) ok3 = false;
                break;
            case 6:
                if (!ok3 || !f_00692720(reader, p, 0)) ok3 = false;
                break;
            case 8:
            case 9:
            case 0xc:
                if (!ok3 || !f_00692740(reader, p, 0)) ok3 = false;
                break;
            case 10:
            case 0xb:
            case 0xd:
                if (!ok3 || !f_00692760(reader, p, 0)) ok3 = false;
                break;
            case 0xf:
                if (!ok3 || !reader->readObj(p, 0)) ok3 = false;
                break;
            case 0x10:
                v->mFlags = 0;
                v->mType = 0;
                f_00f47380(arr);
                ok3 = false;
                break;
            case 0x11:
                if (p != 0) {
                    *(void**)p = TAG_A;
                    *(void**)(p + 4) = TAG_A;
                    *(void**)(p + 8) = TAG_B;
                }
                {
                    extern bool f_00a17a00(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                    if (!ok3 || !f_00a17a00(this, reader, (Variant_s00a1_96f0*)p)) ok3 = false;
                }
                break;
            case 0x12:
                if (p != 0) {
                    *(void**)p = TAG_A;
                    *(void**)(p + 4) = TAG_A;
                    *(void**)(p + 8) = TAG_C;
                }
                {
                    extern bool f_00a18d20(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                    if (!ok3 || !f_00a18d20(this, reader, (Variant_s00a1_96f0*)p)) ok3 = false;
                }
                break;
            default:
                if (!ok3 || !reader->readObj(p, 0x10)) ok3 = false;
                v->mFlags &= 0xfffe;
                break;
            }
            ok2 = ok3;
            p += stride;
        } while (p < end);
        return (char)(ok2 ? 1 : 0);
    } else {
        v->mFlags = 0;
        v->mType = 0;
    }
    return 0;
}

// @ 0x00a19d60
FactoryConfiguration_s00a1_96f0::FactoryConfiguration_s00a1_96f0()
{
    mVtbl = (void*)0x013effa8;                     // vtbl_Resource::PFRecordRead
    mField04 = 0;
    mField08 = (void*)0x00ad77c2;
    mVtbl = (void*)0x014527b8;                     // ??_7FactoryConfiguration...
    mMutex.ctor(0, 1);

    void* anchor = (char*)this + 0x44;
    void** a = (void**)anchor;
    a[0] = anchor;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    *(void**)((char*)this + 0x48) = anchor;
    *(void**)((char*)this + 0x4c) = 0;
    *(u8*)((char*)this + 0x50) = 0;
    *(void**)((char*)this + 0x54) = 0;

    void* tag = (void*)0x01667bac;
    *(void**)((char*)this + 0x5c) = tag;
    *(void**)((char*)this + 0x60) = tag;
    *(void**)((char*)this + 0x64) = (void*)0x01667bad;

    AddLegacyPropertyTypes();
}

// @ 0x00a19e00
FactoryConfiguration_s00a1_96f0::~FactoryConfiguration_s00a1_96f0()
{
    if (((char*)mField64 - (char*)mField5c) > 1 && mField5c != 0) {
        f_00f47380(mField5c);
    }
    // eastl::rbtree<...>::DoNukeSubtree(mField4c) on the tree at +0x40
    mTree.DoNukeSubtree(mField4c);
    mMutex.dtor();
    mVtbl = (void*)0x013effb8;
}

// @ 0x00a19e90
char ResConfig::Read(IOReader* reader)
{
    u32 header = 0;
    if (!f_0093a780(reader, &header, 1, 0)) return 0;

    int count = 0;
    if ((int)header < 0) {
        int info[3] = {0, 0, 0};
        if (!f_0093a780(reader, info, 3, 0)) return 0;

        void* dbg = f_008de1a0();
        void** children = (void**)((char*)this + 0x3c);
        void* node = *children;
        if (node != 0) {
            *children = 0;
            ((void (__thiscall*)(void*))((void**)*(void**)node)[1])(node);
        }
        if (!((bool (__thiscall*)(void*, int*, void**, int, int, int, int))
                  ((void**)*(void**)dbg)[3])(dbg, info, children, 0, 0, 0, 0))
            return 0;
        header = (u32)info[0];
    }

    unsigned n = header & 0x7fffffff;
    f_006a2b80((char*)this + 0x24, n);
    int elems = (int)((char*)mPropEnd - (char*)mPropBegin) / 0x18;
    char result = 1;
    char prev = 1;
    if (elems > 0) {
        int off = 0;
        do {
            char ok;
            if (result == 0 ||
                !f_0093a780(reader, (char*)mPropBegin + off, 1, 0) ||
                !ReadVariant(reader, (Variant_s00a1_96f0*)((char*)mPropBegin + off + 4))) {
                ok = 0;
            } else {
                ok = 1;
            }
            result = ok;
            off += 0x18;
            --elems;
            prev = result;
        } while (elems != 0);
    }
    (void)count;
    return prev;
}
