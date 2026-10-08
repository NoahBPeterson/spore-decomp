// Slice s0099f0b0: nSPCreatureAnim packed-animation clone (0x0099f110).
// Builds a fresh, relocatable "ANIM" (version 0x19) blob from an existing one. When `filterOn` is set, only
// groups flagged as usable (word +0xac bit0, with bit3 or at least one channel with flag 0x10) are kept and, inside
// them, only channels with flag 0x10 or an element-type nibble of 0. Layout of the result:
//   header (0x200) | group pointer table | groups (0xe4 + channel array + frame data) | fixup offsets | event records | strings
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <string.h>

typedef unsigned int uint;

static inline int Strlen(const char* s)
{
    const char* p = s;
    while (*p++) {}
    return (int)(p - s - 1);
}

extern const uint32_t kAnimElemSize[16];        // 0x015504cc : bytes per channel element, by type nibble
extern int g_animSerial;                        // 0x0166b260
extern const float g_one;                       // 0x01485720
extern const float kQuatEpsilon;                // 0x013f11c8 (1e-6)
void* __cdecl operator_new(uint size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

struct AnimEvent {                              // 0x60 bytes
    uint32_t flags;                             // +0x00 (bits 6..7: kind; 1 and 2 carry a string)
    char pad04[0x3c];
    const char* str;                            // +0x40
    uint32_t pad44;
    float weight;                               // +0x48
    char pad4c[0x14];
};

struct AnimChannel {                            // 0x20 bytes
    uint32_t flags;                             // +0x00 (low nibble: element type, 0x10: kept when filtering)
    uint32_t pad04;                             // +0x04 (non-zero marks an event channel)
    uint32_t offset;                            // +0x08 element offset inside a frame
    uint32_t stride;                            // +0x0c frame stride
    char pad10[0x10];
};

struct AnimGroup {                              // 0xe4 bytes
    uint32_t pad00;
    void* owner;                                // +0x04
    char name[0xa4];                            // +0x08
    uint16_t flags;                             // +0xac (bit0 usable, bit3 always kept)
    char padae[0x26];
    uint32_t frameCount;                        // +0xd4
    char* frameData;                            // +0xd8
    uint32_t channelCount;                      // +0xdc
    AnimChannel* channels;                      // +0xe0
};

struct AnimEventRef {                           // 12 bytes inside an event channel's frame data
    uint32_t pad0;
    uint32_t pad4;
    uint16_t first;                             // +8 : first event record
    uint8_t count;                              // +10
};

struct AnimHeader {                             // 0x200 bytes
    uint32_t magic;                             // +0x000 'ANIM'
    uint32_t size;                              // +0x004
    uint32_t version;                           // +0x008 (0x19)
    char name[0x108];                           // +0x00c
    uint32_t pad114;                            // +0x114
    uint32_t flags;                             // +0x118 (bit0: has weighted events)
    char pad11c[0x10];
    uint32_t serial;                            // +0x12c
    char pad130[0xc];
    uint32_t eventCount;                        // +0x13c
    AnimEvent* events;                          // +0x140
    uint32_t groupCount;                        // +0x144
    AnimGroup** groups;                         // +0x148
    uint32_t fixupCount;                        // +0x14c
    uint32_t fixupOffset;                       // +0x150
    char pad154[0xac];
};

// @ 0x0099f110
AnimHeader* CloneAnim(AnimHeader* src, bool filterOn)
{
    int groupBytes = 0x200;                     // header + group pointer table, grows per kept group
    uint fixups = 2;
    uint groupCount = 0;
    int eventCount = 0;
    int stringBytes = 0;
    uint8_t hasWeight = 0;
    uint groupIdx[64];
    uint nGroups = src->groupCount;
    {
        AnimGroup** gp = src->groups;
        for (uint gi = 0; gi < nGroups; gi++, gp++) {
            AnimGroup* grp = *gp;
            bool keep = true;
            if (filterOn) {
                if (!(grp->flags & 1)) {
                    keep = false;
                } else if (!(grp->flags & 8)) {
                    keep = false;
                    for (uint c = 0; c < grp->channelCount; c++) {
                        if (grp->channels[c].flags & 0x10) {
                            keep = true;
                            break;
                        }
                    }
                }
            }
            if (keep) {
                uint nch = grp->channelCount;
                groupBytes += 0xe8;
                fixups += 4;
                groupIdx[groupCount++] = gi;
                AnimChannel* ch = grp->channels;
                for (uint rem = nch; rem; rem--, ch++) {
                    uint f = ch->flags;
                    if ((f & 0x10) || !filterOn || !(f & 0xf))
                        groupBytes += 0x20 + kAnimElemSize[f & 0xf] * grp->frameCount;
                }
                if (grp->flags != 0) {
                    AnimChannel* evch = 0;
                    AnimChannel* p = grp->channels;
                    for (uint c = 0; c < nch; c++, p++) {
                        if (!(p->flags & 0xf) && p->pad04) {
                            evch = grp->channels + c;
                            break;
                        }
                    }
                    char* frame = grp->frameData + evch->offset;
                    uint frames = grp->frameCount;
                    {
                        for (; frames; frames--, frame += evch->stride) {
                            AnimEventRef* ref = (AnimEventRef*)frame;
                            if (ref->count) {
                                uint first = ref->first;
                                eventCount += ref->count;
                                uint last = first + ref->count;
                                if (first < last) {
                                    AnimEvent* ev = src->events + first;
                                    int n = last - first;
                                    do {
                                        if (ev->weight > 0.0f)
                                            hasWeight |= 1;
                                        switch (ev->flags & 0xc0) {
                                        case 0x40:
                                        case 0x80:
                                            if (ev->str) {
                                                stringBytes += Strlen(ev->str) + 1;
                                                fixups++;
                                            }
                                        }
                                        ev++;
                                        n--;
                                    } while (n);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int fixupAt = groupBytes + fixups * 4;      // offset of the event records
    uint total = fixupAt + eventCount * 0x60 + stringBytes;
    uint pad = ((total + 3) & ~3u) - total;
    total += pad;
    char* mem = (char*)operator_new(total, "Anim/Anim", 0, 0, 0, 0);
    memset(mem + total - pad, 0, pad);
    char* strCursor = mem + fixupAt + eventCount * 0x60;
    AnimHeader* dst = (AnimHeader*)mem;
    uint32_t keepField = dst->pad114;
    *dst = *src;
    dst->pad114 = keepField;
    uint32_t* fixCursor = (uint32_t*)(mem + groupBytes);
    dst->serial = g_animSerial++;
    dst->size = total;
    dst->magic = 0x4d494e41;
    dst->version = 0x19;
    uint recIdx = 0;
    {
        int len = Strlen(dst->name);
        memset(dst->name + len + 1, 0, 0x103 - len);
    }
    dst->eventCount = eventCount;
    dst->events = (AnimEvent*)(mem + fixupAt);
    dst->fixupCount = fixups;
    dst->groupCount = groupCount;
    dst->pad114 = 0;
    dst->fixupOffset = groupBytes;
    fixCursor[0] = 0x140;
    fixCursor[1] = 0x148;
    fixCursor += 2;
    AnimGroup** table = (AnimGroup**)(mem + 0x200);
    if (hasWeight != 0)
        dst->flags |= 1;
    else
        dst->flags &= ~1u;
    int off = (int)((char*)table - mem);
    dst->groups = table;
    for (uint k = groupCount; k; k--) {
        *fixCursor++ = off;
        off += 4;
    }
    char* cursor = (char*)(table + groupCount);
    for (uint j = 0; j < groupCount; j++) {
        AnimGroup* sg = src->groups[groupIdx[j]];
        dst->groups[j] = (AnimGroup*)cursor;
        AnimGroup* ng = (AnimGroup*)cursor;
        memcpy(ng, sg, 0xe4);
        {
            int len = Strlen(ng->name);
            memset(ng->name + len + 1, 0, 0x7f - len);
        }
        ng->owner = dst;
        *fixCursor++ = (cursor - mem) + 4;
        *fixCursor++ = (cursor - mem) + 0xd8;
        *fixCursor++ = (cursor - mem) + 0xe0;
        ng->channels = (AnimChannel*)(cursor + 0xe4);
        uint nsc = sg->channelCount;
        uint kept = 0;
        uint stride = 0;
        uint chIdx[9];
        if (nsc) {
            int o = 0;
            uint c = 0;
            do {
                AnimChannel* sc = (AnimChannel*)((char*)sg->channels + o);
                if ((sc->flags & 0x10) || !filterOn || !(sc->flags & 0xf)) {
                    chIdx[kept] = c;
                    memcpy(ng->channels + kept, sc, 0x20);
                    kept++;
                    stride += kAnimElemSize[sc->flags & 0xf];
                }
                o += 0x20;
                c++;
            } while (c < nsc);
        }
        char* data = cursor + 0xe4 + kept * 0x20;
        ng->channelCount = kept;
        {
            uint acc = 0;
            for (uint c = 0; c < kept; c++) {
                AnimChannel* nc = &ng->channels[c];
                nc->offset = acc;
                nc->stride = stride;
                acc += kAnimElemSize[nc->flags & 0xf];
            }
        }
        ng->frameData = data;
        for (uint f = 0; f < sg->frameCount; f++) {
            for (uint c = 0; c < kept; c++) {
                AnimChannel* sc = &sg->channels[chIdx[c]];
                uint sz = kAnimElemSize[sc->flags & 0xf];
                memcpy(data, sg->frameData + sc->stride * f + sc->offset, sz);
                if ((sc->flags & 0xf) == 2) {
                    float* q = (float*)data;
                    if (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3] < kQuatEpsilon) {
                        q[0] = 0.0f;
                        q[1] = 0.0f;
                        q[2] = 0.0f;
                        q[3] = g_one;
                    }
                }
                char* elem = data;
                data += sz;
                if (!(sc->flags & 0xf)) {
                    AnimEventRef* ref = (AnimEventRef*)elem;
                    uint cnt = ref->count;
                    if (cnt) {
                        AnimEvent* de = (AnimEvent*)(mem + fixupAt) + recIdx;
                        AnimEvent* se = src->events + ref->first;
                        memcpy(de, se, cnt * 0x60);
                        ref->first = (uint16_t)recIdx;
                        for (uint r = cnt; r; r--, de++) {
                            switch (de->flags & 0xc0) {
                            case 0x40:
                            case 0x80:
                                if (de->str) {
                                    const char* s = de->str;
                                    int len = Strlen(s) + 1;
                                    de->str = strCursor;
                                    *fixCursor++ = ((char*)de - mem) + 0x40;
                                    de->flags = (de->flags & 0xffffff7f) | 0x40;
                                    for (const char* p = s; p != s + len; p++)
                                        strCursor[p - s] = *p;
                                    strCursor += len;
                                }
                            }
                        }
                        recIdx += cnt;
                    }
                }
            }
        }
        cursor = data;
    }
    return dst;
}
