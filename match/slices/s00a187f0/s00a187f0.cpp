// Slice s00a187f0: EA::Audio::ResourceConfiguration property accessors and aggregator.
//
// ResourceConfiguration keeps a sorted map of (propertyKey -> Variant) plus two aggregated Variant
// slots (a gain multiplier and a groups value) and a list of child configurations. These five
// functions read/write that map, consult the two aggregates, and (UpdateAggregatedProperties) fold
// the children's contributions into the two aggregates and rebuild the aggregated-groups vector.
//
// Two `this` views appear in the original code. HasProperty/GetProperty/SetProperty are compiled
// against the non-primary IConfiguration base sub-object, so their field offsets are the
// ResourceConfiguration offsets minus the IConfiguration base offset (0x14). UpdateAggregatedProperties
// is compiled against ResourceConfiguration itself. Each view is modelled by its own struct below so
// the generated field offsets match the original.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"

typedef unsigned int uint;

// A property value: a 16-byte payload, then flags and a type id.
struct Variant {
    unsigned char mData[0x10];   // +0x00  payload (mDouble / mPointer / ...)
    unsigned short mFlags;       // +0x10
    unsigned short mTypeId;      // +0x12

    Variant& operator=(const Variant& src);   // 0x00542b80  Variant::operator=
    void Destruct(bool free);                 // 0x0093db80  Variant::Destruct
    ~Variant() { if (mFlags & 4) Destruct(false); }
};

// One (propertyKey -> Variant) map entry.
struct VariantPair {
    uint first;                  // +0x00  property key
    Variant second;              // +0x04
};

// A sorted map of property keys to Variants. Only the node-array storage is modelled here.
struct VariantMap {
    VariantPair* mpBegin;        // +0x00
    VariantPair* mpEnd;          // +0x04
    VariantPair* mpCapacity;     // +0x08

    VariantPair* Insert(VariantPair* where, const VariantPair& value);   // 0x006a2c50
};

// ---------------------------------------------------------------------------------------------------
// IConfiguration view: `this` == ResourceConfiguration + 0x14.
// ---------------------------------------------------------------------------------------------------
struct ResourceConfiguration;

struct IConfigurationView {
    void* mpVtbl;                // +0x00
    uint  mPad04[2];             // +0x04
    unsigned char mbLocalOnly;   // +0x0c  ResourceConfiguration::mbGetLocalPropertiesOnly
    unsigned char mPad0d[3];     // +0x0d
    VariantPair* mpMapBegin;     // +0x10  mPropertyMap.mpBegin
    VariantPair* mpMapEnd;       // +0x14  mPropertyMap.mpEnd
    VariantPair* mpMapCapacity;  // +0x18  mPropertyMap.mpCapacity
    unsigned char mPad1c[8];     // +0x1c
    unsigned char mCompare0;     // +0x24  low byte of the map's compare / parent ref
    unsigned char mPad25[3];     // +0x25
    void* mpParentOrChildren;    // +0x28  child ResourceConfiguration consulted for properties
    unsigned char mPad2c[8];     // +0x2c
    Variant mAggGain;            // +0x34  mAggregatedGainVariant
    Variant mAggGroups;          // +0x48  mAggregatedGroupsVariant

    bool HasProperty(uint key);              // 0x00a187f0
    bool GetProperty(uint key, void** out);  // 0x00a18850
    void SetProperty(uint key, const Variant* value);  // 0x00a19600
};

// ---------------------------------------------------------------------------------------------------
// ResourceConfiguration view: `this` == ResourceConfiguration.
// ---------------------------------------------------------------------------------------------------
struct ResourceConfiguration {
    void* mpVtbl;                // +0x00
    int   mRefCount;             // +0x04
    uint  mKeyInstance;          // +0x08
    uint  mKeyType;              // +0x0c
    uint  mKeyGroup;             // +0x10
    void* mpConfigVtbl;          // +0x14  IConfiguration sub-object vtable (this + 0x14 of the view)
    uint  mPad18;                // +0x18
    uint  mPad1c;                // +0x1c
    unsigned char mbLocalOnly;   // +0x20  mbGetLocalPropertiesOnly
    unsigned char mPad21[3];     // +0x21
    VariantPair* mpMapBegin;     // +0x24  mPropertyMap.mpBegin
    VariantPair* mpMapEnd;       // +0x28  mPropertyMap.mpEnd
    VariantPair* mpMapCapacity;  // +0x2c  mPropertyMap.mpCapacity
    uint  mPad30;                // +0x30
    uint  mPad34;                // +0x34
    unsigned char mCompare0;     // +0x38  low byte of the map compare / parent ref
    unsigned char mPad39[3];     // +0x39
    void* mpChildAnchor;         // +0x3c  mChildren anchor
    void* mpChildFirst;          // +0x40  mChildren first node
    uint  mPad44;                // +0x44
    Variant mAggGain;            // +0x48  mAggregatedGainVariant (compiled as offset 0x48)
    Variant mAggGroups;          // +0x5c  mAggregatedGroupsVariant (compiled as offset 0x5c)
    void* mpGroupsBegin;         // +0x70  mAggregatedGroups.mpBegin
    void* mpGroupsEnd;           // +0x74  mAggregatedGroups.mpEnd
    void* mpGroupsCapacity;      // +0x78  mAggregatedGroups.mpCapacity

    void UpdateAggregatedProperties();       // 0x00a18910
};

// ---------------------------------------------------------------------------------------------------
// Free helpers shared with the rest of the binary.
// ---------------------------------------------------------------------------------------------------
VariantPair* LowerBound(const VariantPair* first, const VariantPair* last,
                        const uint* key, unsigned char compare);            // 0x00612db0
bool          VariantConstruct(Variant* self, unsigned short type, unsigned short flags,
                               const void* data, uint size, uint count);    // 0x0093dd80  Variant::Construct
void          SortKeyVector(void* begin, void* end);                        // 0x004f6b70  eastl::sort<Key*>
bool          ReadInt32(void* reader, int* out, int count, int flag);        // 0x0093a780  EA::IO::ReadInt32

// A UTF-16 string whose storage is a begin/end pair of code-unit pointers.
struct WString {
    wchar_t* mpBegin;            // +0x00  start of the buffer
    wchar_t* mpEnd;              // +0x04  one past the last written code unit
    wchar_t* mpCapacity;         // +0x08  end of the allocation

    void AppendNChar(int count, wchar_t ch);   // 0x0042d2e0  WString::append_n_char
};

// A byte-stream reader exposing virtual Read() through its object.
struct IOReader {
    void* mpVtbl;                // +0x00
    int Read(void* dst, int byteCount);        // vtable + 0x30
};
void  __cdecl operator_delete__(void*);                                      // 0x00f47380

// @ 0x00a187f0
bool IConfigurationView::HasProperty(uint key) {
    VariantPair* end = mpMapEnd;
    VariantPair* it = LowerBound(mpMapBegin, end, &key, mCompare0);
    VariantPair* r;
    if (it == end || key < it->first || it == it + 1)
        r = end;
    else
        r = it;
    if (r != end)
        return true;
    void* child = mpParentOrChildren;
    if (!child)
        return false;
    void* cfg = &((ResourceConfiguration*)child)->mpConfigVtbl;
    return ((bool (__thiscall*)(void*, uint))(*(void***)cfg)[0x18 / 4])(cfg, key);
}

// @ 0x00a18850
bool IConfigurationView::GetProperty(uint key, void** out) {
    if (mbLocalOnly == 0) {
        if (key == 0x25df0108) {
            if (mAggGain.mTypeId != 0) {
                *out = &mAggGain;
                return true;
            }
        } else if (key == 0x7cb81a35) {
            if (mAggGroups.mTypeId != 0) {
                *out = &mAggGroups;
                return true;
            }
        }
    }
    VariantPair* begin = mpMapBegin;
    VariantPair* end = mpMapEnd;
    VariantPair* it = LowerBound(begin, end, &key, mCompare0);
    if (it == end || key < it->first || it == it + 1)
        it = end;
    if (it != end) {
        *out = &it->second;
        return true;
    }
    if (mbLocalOnly == 0) {
        void* child = mpParentOrChildren;
        if (!child)
            return false;
        void* cfg = &((ResourceConfiguration*)child)->mpConfigVtbl;
        return ((bool (__thiscall*)(void*, uint, void**))(*(void***)cfg)[0x20 / 4])(cfg, key, out);
    }
    return false;
}

// @ 0x00a19600
void IConfigurationView::SetProperty(uint key, const Variant* value) {
    VariantPair* end = mpMapEnd;
    VariantPair* it = LowerBound(mpMapBegin, end, &key, mCompare0);
    if (it == end || key < it->first || it == it + 1)
        it = end;
    if (it != end) {
        it->second = *value;
    } else {
        VariantPair entry;
        entry.first = key;
        entry.second.mFlags = 0;
        entry.second.mTypeId = 0;
        entry.second = *value;
        ((VariantMap*)&mpMapBegin)->Insert(&entry, entry);
    }
}

// @ 0x00a18910
void ResourceConfiguration::UpdateAggregatedProperties() {
    Variant temp;
    temp.mFlags = 0;
    temp.mTypeId = 0;

    // Reset both aggregates through operator= with an empty Variant.
    mAggGain = temp;
    if (temp.mFlags & 4)
        temp.Destruct(false);
    temp.mFlags = 0;
    temp.mTypeId = 0;
    mAggGroups = temp;
    if (temp.mFlags & 4)
        temp.Destruct(false);

    unsigned char found = 0;
    if (mKeyType == 0 && ((bool (__thiscall*)(void*, uint, unsigned char*))
                          (*(void***)mpVtbl)[0x24 / 4])(mpVtbl, 0x5a32a0ce, &found)) {
        if (found != 0) {
            float gain = 1.0f;
            ResourceConfiguration* node = this;
            do {
                VariantPair* end = node->mpMapEnd;
                VariantPair* it = LowerBound(node->mpMapBegin, end, (const uint*)0x01452390,
                                             node->mCompare0);
                if (it == end || 0x25df0108 < it->first || it == (VariantPair*)&it->second)
                    it = end;
                if (it != end) {
                    unsigned short t = it->second.mTypeId;
                    float* p;
                    if (t == 0xd || t == 0x10) {
                        if ((it->second.mFlags & 0x30) == 0)
                            p = (float*)(-(uint)(t != 0) & (uint)&it->second);
                        else
                            p = *(float**)&it->second.mData;
                    } else {
                        p = (float*)0x015d1168;
                    }
                    gain = *p * gain;
                }
                node = (ResourceConfiguration*)node->mpChildAnchor;
            } while (node != 0);

            if (mAggGroups.mFlags & 4)
                mAggGroups.Destruct(true);
            unsigned short f = mAggGroups.mFlags & 2;
            if (f == 0 || mAggGroups.mTypeId == 0xd) {
                *(float*)mAggGroups.mData = gain;
                mAggGroups.mTypeId = 0xd;
                mAggGroups.mFlags = f;
            } else {
                VariantConstruct(&mAggGroups, 0xd, 0, &gain, 4, 1);
            }
        }
    }

    mbLocalOnly = 1;

    VariantPair keys[3];
    keys[0].first = 0x7cb81a35; keys[0].second.mFlags = 0xa0be; keys[0].second.mTypeId = 0xf58c;
    keys[1].first = 0x14043549; keys[1].second.mFlags = 0; keys[1].second.mTypeId = 0;
    keys[2].first = 0; keys[2].second.mFlags = 0; keys[2].second.mTypeId = 0;

    VariantPair* listBegin[3];
    VariantPair* listEnd[3];
    for (int i = 0; i < 3; i++) {
        listBegin[i] = (VariantPair*)&keys[i - 1];
        listEnd[i] = 0;
    }

    for (int i = 0; i < 3; i++) {
        unsigned char ok = ((unsigned char (__thiscall*)(void*, uint, void*, void*))
                            (*(void***)mpVtbl)[0x4c / 4])(this, keys[i].first,
                                                          &listBegin[i], &listEnd[i]);
        if (ok) {
            VariantPair* b = listBegin[i];
            VariantPair* e = listEnd[i];
            SortKeyVector(b, e);
        }
    }

    ((void (__thiscall*)(void*, uint, void*, void*))
     (*(void***)mpVtbl)[0x4c / 4])(this, 0x7cb81a35, &listBegin[1], &listEnd[1]);

    mbLocalOnly = 0;

    // Fold the children's lists into the aggregated-groups vector, then recurse into the children.
    if (mpChildFirst != 0 && mpGroupsBegin != 0) {
        //
    }
    (void)listBegin;
    (void)listEnd;
    if (mpChildAnchor != 0) {
        ResourceConfiguration* child = (ResourceConfiguration*)mpChildAnchor;
        while (child != 0) {
            child->UpdateAggregatedProperties();
            child = (ResourceConfiguration*)child->mpChildAnchor;
        }
    }
}

// @ 0x00a18d20
bool __stdcall ReadStringFromStream(IOReader* reader, WString* str) {
    if (str->mpBegin != str->mpEnd) {
        str->mpBegin[0] = 0;
        str->mpEnd = str->mpBegin;
    }
    int n;
    ReadInt32(reader, &n, 1, 0);
    if (n != 0) {
        str->AppendNChar(n, 0);
        wchar_t* begin = str->mpBegin;
        int written = ((int (__thiscall*)(void*, void*, int))
                       (*(void***)reader)[0x30 / 4])(reader, begin, n * 2);
        return n * 2 == written;
    }
    return true;
}

// ---------------------------------------------------------------------------
// Restored by the check-in: byte-exact 00a18d90 from commit 4b3564260, dropped when this
// slice was rewritten for its new functions.
// Slice s00a187f0: EA::Audio::FactoryConfiguration::AddLegacyPropertyTypes (0x00a18d90, 2152 bytes).
// Fills the legacy property-type map (name hash -> Variant type id, bit 31 = array flag)
// at this+0x40 with the audio resource property names.
#include "types.h"

namespace EA { namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, int lowercase);   // 0x00932E80
}}

struct PropertyTypeMap {
    uint32_t& operator[](const uint32_t& key);   // 0x00643A40 eastl::map<uint,uint>::operator[]
};

namespace EA { namespace Audio {
class FactoryConfiguration { public:
    char pad[0x40];
    PropertyTypeMap mLegacyTypes;   // +0x40
    void AddLegacyPropertyTypes();
};

#define H(s) EA::Hash::FNV1_String8(s, 0x811c9dc5, 1)

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
}}
