// rw::audio::core MP3 stream player (RenderWare 4 audio core, VC .NET 2003, /GL+/LTCG).
// The original was LTCG-linked, so only the call-free functions are byte-exact (manifest.txt);
// the rest are complete, behaviour-equivalent source (nonmatching.txt).  32-bit only.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

namespace rw { namespace audio { namespace core {

struct Mp3Player;

static inline int RwFloat2Int(float f)
{
    int r;
    __asm { cvtss2si eax, f }
    __asm { mov r, eax }
    return r;
}

// ---------------------------------------------------------------- filesys Stream
struct Stream {
    void* GetChunk();                 // 0x011e6b50
    int   FUN_011e6bf0();             // 0x011e6bf0  (has data?)
    bool  FUN_011e6c50();             // 0x011e6c50
    void  ReleaseChunk(void* chunk);  // 0x011e7c70
};

struct System {
    void* Alloc(unsigned size, const char* name, int align, int flags);  // 0x0112c820
    void  Free(void* p, int flags);                                       // 0x0112c850
};
extern System* g_pSystem;    // 0x016e61a8

int AiffPlayer_checkChunkID(uint32_t id);   // 0x01130be0 (slice s0112fc10)

// ---------------------------------------------------------------- decoder interface
struct Decoder {
    virtual int Decode(int offset, int count, int bytes);
    virtual int Fill(void** channels, int bytes);
    virtual int Init(void* header);
    virtual int Stop(int immediate);
};

// ---------------------------------------------------------------- free callees
typedef void (*EventFn)(void*, Mp3Player*);
void*  FUN_011402c0(unsigned size);                          // 0x011402c0
void   FUN_01132fe0(void* p);                                // 0x01132fe0
void   FUN_0113fca0(void* p);                                // 0x0113fca0
int    FUN_0113f1c0(int index);                              // 0x0113f1c0
int    FUN_0113f1d0(EventFn fn, int a2, void* a3, void* slot, int size); // 0x0113f1d0
int    FUN_0113f250(int handle, void* a, void* b, void* c);  // 0x0113f250
int    FUN_0113fba0(int handle, int value);                  // 0x0113fba0
int    FUN_0113fdd0(int handle, int index, int value);       // 0x0113fdd0
int    FUN_0113ff00(int handle, int value);                  // 0x0113ff00
int    FUN_0113f9b0(int handle);                             // 0x0113f9b0
int    FUN_0113f750(int handle);                             // 0x0113f750
void   FUN_01133450();                                       // 0x01133450
void   FUN_01133460();                                       // 0x01133460
void   FUN_0113ec90(void* p, int size);                      // 0x0113ec90 SNDMEMI_alloc
int    SNDPKTPLAY_submit(int handle, void* packet);          // 0x0113f5c0

extern const uint16_t g_015ba5b8[];   // 0x015ba5b8
extern const uint16_t g_015ba59a[];   // 0x015ba59a
extern const uint16_t g_015ba57c[];   // 0x015ba57c
extern const uint8_t  g_014cafd2[];   // 0x014cafd2  channel gain table
extern int            g_016e6268;     // 0x016e6268  doubly linked list head

// ---------------------------------------------------------------- sub-objects
struct AiffStreamState {
    uint8_t  f0, f1, f2, f3, f4, f5;
    uint16_t w6, w8, wa, wc, we;
};
struct AiffPuller {
    uint16_t w0;
    uint8_t  b2, b3, b4, b5, b6;
    uint16_t gain[6];
    uint32_t f14[6];
    uint32_t pad2c[6];
    uint32_t f44, f48, f4c, f50;
    uint32_t f54, f58, f5c, f60;
};

struct Chunk { int field0; int size; void* data; };   // filesys Stream chunk: +4 length, +8 data

struct Mp3Format {            // sound format block pointed to by the player's +0x20
    float  f0, f1, f2;
    float* p3;               // +0x0c  points to a float table
    float  f4, f5;
};

struct Mp3Player {
    int          mPosition;      // 0x00
    int          mBytes;         // 0x04
    int          mState;         // 0x08
    int          mField0c;       // 0x0c
    int          mField10;       // 0x10
    int          mField14;       // 0x14
    int          mField18;       // 0x18
    int          mField1c;       // 0x1c
    Mp3Format*   mpFormat;       // 0x20
    AiffStreamState m24;         // 0x24
    AiffPuller   m34;            // 0x34
    uint16_t     mSampleRate;    // 0x98
    uint8_t      mChannels;      // 0x9a
    uint8_t      mField9b;       // 0x9b
    int          mField9c;       // 0x9c
    int          mFielda0;       // 0xa0
    int          mFielda4;       // 0xa4
    int          mTotal;         // 0xa8
    int          mpBase;         // 0xac
    int          mHandle;        // 0xb0
    int          mStartHandle;   // 0xb4
    void*        mChunks[10];    // 0xb8
    Stream*      mpStream;       // 0xe0
    int          mFielde4;       // 0xe4
    int          mPending;       // 0xe8
    int          mFieldec;       // 0xec
    void*        mpExtra;        // 0xf0
    int          mListNode0;     // 0xf4
    int          mListNode1;     // 0xf8
    void       (*mpOnFree)(Mp3Player*);  // 0xfc
    Mp3Player*   mpSelf;         // 0x100
    char         mEvent[0x1f8];  // 0x104
};

struct SndPacket {
    int      field0;             // +0x00
    uint32_t size;               // +0x04
    int      field8;             // +0x08
    void*    channel[8];         // +0x0c
};

void Mp3Player_releaseChunk(void* chunkData, Mp3Player* self);
void Mp3Player_tick(Mp3Player* self);
void Mp3Player_fill(Mp3Player* self);
void Mp3Player_playChunk(Chunk* chunk, Mp3Player* self);

// @ 0x01130c50
int Mp3Player_parseHeader(unsigned char* data, Mp3Player* self)
{
    int id = AiffPlayer_checkChunkID(((unsigned)data[0] << 24) | ((unsigned)data[1] << 16) |
                                     ((unsigned)data[2] << 8) | (unsigned)data[3]);
    if (id >= -3 && id <= 0)
        return id;

    int uVar3 = (id >> 9) & 1;
    int uVar4 = (id >> 0x13) & 3;
    int uVar5 = (id >> 0xc) & 0xf;
    int uVar6 = (id >> 0xa) & 3;

    self->mField14 = uVar4;
    if (((id >> 0x11) & 3) == 0 || uVar5 == 0xf || uVar4 == 1 || uVar6 == 3 || uVar5 == 0)
        return 0;

    self->mChannels = (uint8_t)(((id & 0xc0) != 0xc0) ? 2 : 1);
    uint16_t rate = g_015ba5b8[uVar6];
    self->mSampleRate = rate;

    if (uVar4 == 0) {
        rate >>= 2;
        self->mSampleRate = rate;
        int t = g_015ba57c[uVar5];
        self->mField10 = t;
        self->mField1c = 0x240;
        self->mField18 = ((t * 0x23280) / (int)(unsigned)self->mSampleRate) >> 1;
        self->mField18 += uVar3;
        return self->mField18;
    }
    if (uVar4 == 2) {
        rate >>= 1;
        self->mSampleRate = rate;
        int t = g_015ba57c[uVar5];
        self->mField10 = t;
        self->mField1c = 0x240;
        self->mField18 = ((t * 0x23280) / (int)(unsigned)self->mSampleRate) >> 1;
        self->mField18 += uVar3;
        return self->mField18;
    }
    if (uVar4 == 3) {
        int t = g_015ba59a[uVar5];
        self->mField10 = t;
        self->mField1c = 0x480;
        self->mField18 = (t * 0x23280) / (int)(unsigned)self->mSampleRate;
        self->mField18 += uVar3;
        return self->mField18;
    }
    self->mField18 += uVar3;
    return self->mField18;
}

// @ 0x01130d90
// Locate the next MPEG/RIFF/ID3 sync word in [data, data+len-4); returns 0 if none.
unsigned Mp3Player_findSync(unsigned char* data, int len)
{
    unsigned char* end = data + len - 4;
    unsigned char found = 0;
    if (data < end) {
        unsigned h = ((unsigned)data[0] << 24) | ((unsigned)data[1] << 16) |
                     ((unsigned)data[2] << 8) | (unsigned)data[3];
        for (data = data + 4; data < end; ++data) {
            if (((h & 0xffffff00) == 0x54414700) ||
                ((h & 0xffffff00) == 0x49443300) ||
                (h == 0x52494646) ||
                (((h & 0xffe00000) == 0xffe00000) && ((h & 0xf000) != 0xf000) &&
                 ((h & 0xc00) != 0xc00) && (h != 0))) {
                data -= 4;
                found = 1;
                break;
            }
            h = (h << 8) | *data;
        }
    }
    return (unsigned)(-(int)found) & (unsigned)data;
}

// @ 0x01130e50
// Timer callback: parse the current frame and submit it to the packet player once.
void Mp3Player_processFrame(void* data, Mp3Player* self)
{
    SndPacket pkt;
    pkt.field0 = 0;
    pkt.size = 0;
    pkt.field8 = 0;

    Mp3Player_parseHeader((unsigned char*)data, self);
    self->mBytes += self->mField1c;

    if (self->mPosition < self->mTotal) {
        unsigned char* p = (unsigned char*)(self->mpBase + self->mPosition);
        int r = Mp3Player_parseHeader(p, self);
        unsigned size = (unsigned)self->mField1c & 0x7fffffffu;
        if (r > 0) {
            pkt.size = size | 0x80000000u;
            pkt.channel[0] = p;
            SNDPKTPLAY_submit(self->mHandle, &pkt);
            self->mPosition += r;
            return;
        }
        if (r == 0) {
            p = (unsigned char*)Mp3Player_findSync(p, (self->mpBase - (int)p) + self->mTotal);
            if (p != 0) {
                r = Mp3Player_parseHeader(p, self);
                if (r > 0) {
                    pkt.size = size | 0x80000000u;
                    pkt.channel[0] = p;
                    SNDPKTPLAY_submit(self->mHandle, &pkt);
                    self->mPosition += r;
                    return;
                }
            }
        }
    }
    self->mState = 3;
}

// @ 0x01130f40
// Submit one stream chunk: lazily create the packet player, then hand the chunk to it.
void Mp3Player_submitChunk(Chunk* chunk, Mp3Player* self)
{
    int len = chunk->size;
    SndPacket pkt;
    pkt.field0 = 0;
    pkt.field8 = 0;
    pkt.channel[0] = chunk->data;
    unsigned size = ((unsigned)self->mField1c & 0x7fffffffu) | 0x80000000u;
    pkt.size = size;

    if (self->mStartHandle == -1) {
        unsigned char channels = self->mChannels;
        int i = 0;
        if (channels != 0) {
            do {
                self->m34.gain[i] = (uint16_t)((uint16_t)g_014cafd2[i + (unsigned)channels * 6] << 8);
                ++i;
            } while (i < (int)(unsigned)self->mChannels);
        }
        self->mStartHandle = FUN_0113f250(self->mHandle, &self->mSampleRate, &self->m34, &self->m24);
        pkt.size &= 0x7fffffffu;
        if (self->mState == 1)
            FUN_0113fba0(self->mStartHandle, 0);
    }
    SNDPKTPLAY_submit(self->mHandle, &pkt);
    self->mPending++;
    self->mBytes += pkt.size & 0x7fffffffu;
    self->mPosition += len;
}

// @ 0x01131040
void Mp3Player_fill(Mp3Player* self)
{
    int i = 0;
    void** slot = self->mChunks;
    for (;;) {
        if (!self->mpStream->FUN_011e6bf0())
            return;
        if (self->mPending >= 10)
            break;
        if (*slot == 0) {
            Chunk* c = (Chunk*)self->mpStream->GetChunk();
            unsigned char* d = (unsigned char*)c->data;
            int id = AiffPlayer_checkChunkID(((unsigned)d[0] << 24) | ((unsigned)d[1] << 16) |
                                             ((unsigned)d[2] << 8) | (unsigned)d[3]);
            if ((unsigned)(id + 3) < 4) {
                self->mpStream->ReleaseChunk(c);
            } else {
                int r = Mp3Player_parseHeader(d, self);
                if (r != c->size)
                    self->mpStream->FUN_011e6c50();
                *slot = c;
                FUN_01133450();
                Mp3Player_submitChunk((Chunk*)*slot, self);
                FUN_01133460();
            }
        }
        ++i;
        ++slot;
        if (i >= 10)
            return;
    }
}

// @ 0x01131110
void Mp3Player_releaseChunk(void* chunkData, Mp3Player* self)
{
    int i = 0;
    void** p = self->mChunks;
    while (*p == 0 || *(int*)((char*)*p + 8) != (int)chunkData) {
        ++i;
        ++p;
        if (i > 9)
            goto common;
    }
    self->mpStream->ReleaseChunk(*p);
    self->mChunks[i] = 0;

common:
    self->mPending--;
    if (self->mPending == 0 && self->mpStream->FUN_011e6c50())
        self->mState = 3;
    if (self->mPending == 0 && self->mFielda0 <= 0 && self->mpStream->FUN_011e6c50())
        self->mState = 3;
}

// @ 0x011311b0
void Mp3Player_tick(Mp3Player* self)
{
    if (self == 0)
        return;
    if (self->mField0c < 0) {
        int size = FUN_0113f1c0(0xb);
        self->mHandle = FUN_0113f1d0(&Mp3Player_releaseChunk, 0, self, &self->mEvent, size);
        self->mField0c = 1;
        FUN_01132fe0(&self->m24);
        FUN_0113fca0(&self->m34);
        self->mField9b = 0x10;
        self->m34.b5 = 0x7f;
        Mp3Format* f = self->mpFormat;
        self->m24.f0 = (uint8_t)RwFloat2Int(f->f0 * 127.0f);
        self->m24.w8 = (int16_t)RwFloat2Int(f->f1 * 4096.0f);
        self->m24.f3 = (uint8_t)RwFloat2Int(f->f2 * 127.0f);
        self->m24.wc = (int16_t)RwFloat2Int(f->f4);
        self->m24.we = (int16_t)RwFloat2Int(f->f5);
        self->m24.f4 = (uint8_t)RwFloat2Int(f->p3[0] * 127.0f);
        self->mStartHandle = -1;
        return;
    }
    if (self->mpStream->FUN_011e6bf0() && self->mPending < 10)
        Mp3Player_fill(self);
}

// @ 0x011312f0
// Link the player into the global shutdown list and install its on-free callback.
void Mp3Player_link(Mp3Player* self)
{
    self->mpOnFree = &Mp3Player_tick;
    self->mpSelf = self;
    int* node = &self->mListNode0;
    *node = g_016e6268;
    self->mListNode1 = 0;
    if (g_016e6268 != 0)
        *(int*)(g_016e6268 + 4) = (int)node;
    g_016e6268 = (int)node;
}

// @ 0x011313b0
int Mp3Player_setTableGain(void* fmt, int index, Mp3Player* self)
{
    float* tbl = *(float**)((unsigned char*)fmt + 0xc);
    FUN_0113fdd0(self->mStartHandle, index, RwFloat2Int(tbl[index] * 127.0f));
    return 0;
}

// @ 0x011313f0
int Mp3Player_start(Mp3Player* self)
{
    FUN_0113fba0(self->mStartHandle, 0);
    self->mState = 1;
    return 0;
}

// @ 0x01131420
int Mp3Player_setStart(void* fmt, Mp3Player* self)
{
    FUN_0113fba0(self->mStartHandle, RwFloat2Int(*(float*)((unsigned char*)fmt + 4) * 4096.0f));
    self->mState = 0;
    return 0;
}

// @ 0x01131460
int Mp3Player_destroy(Mp3Player* self)
{
    if (self == 0)
        return 0;
    if (self->mState != 2) {
        FUN_0113f9b0(self->mHandle);
        FUN_0113f750(self->mHandle);
        if (self->mpExtra != 0) {
            self->mpStream->ReleaseChunk(self->mpExtra);
            self->mpExtra = 0;
        }
        int i = 10;
        void** p = self->mChunks;
        do {
            if (*p != 0) {
                self->mpStream->ReleaseChunk(*p);
                *p = 0;
            }
            ++p;
            --i;
        } while (i != 0);
        self->mState = 2;
    }
    if (self->mpOnFree != 0) {
        int* node = &self->mListNode0;
        if ((int)node == g_016e6268)
            g_016e6268 = *node;
        if (self->mListNode1 != 0)
            *(int*)(self->mListNode1) = *node;
        if (*node != 0)
            *(int*)(*node + 4) = self->mListNode1;
        FUN_0113ec90(node, 0x10);
    }
    g_pSystem->Free(self, 0);
    return 0;
}

// @ 0x01131540
int Mp3Player_setChannel(void* fmt, Mp3Player* self)
{
    FUN_0113ff00(self->mStartHandle, RwFloat2Int(*(float*)fmt * 127.0f));
    return 0;
}

// @ 0x011315e0
int Mp3Player_getState(Mp3Player* self, int* out)
{
    *out = self->mState;
    return 0;
}

// @ 0x011315f0
int Mp3Player_getProgress(Mp3Player* self, float* out)
{
    unsigned short rate = self->mSampleRate;
    if (rate == 0) {
        *out = 0.0f;
        return 0;
    }
    *out = (float)self->mBytes / (float)rate;
    return 0;
}

// @ 0x01131630
int Mp3Player_getPosition(Mp3Player* self, float* out)
{
    unsigned short rate = self->mSampleRate;
    if (rate == 0) {
        *out = -1.0f;
        return -4;
    }
    if (self->mField0c == 1 && self->mState != 0 && self->mState != 1) {
        *out = -1.0f;
        return 0;
    }
    float f = (float)self->mField18 * 0.5f;
    float r;
    if (self->mField0c == 1)
        r = (float)self->mField9c / f;
    else
        r = (float)self->mTotal / f;
    if (self->mField14 == 3)
        *out = ((r * 1152.0f) / (float)rate) * 0.5f;
    else if (self->mField14 == 2)
        *out = ((r * 576.0f) / (float)rate) * 0.5f;
    else
        *out = ((r * 384.0f) / (float)rate) * 0.5f;
    return 0;
}

// @ 0x01131730
// Create a complete MP3 player from an in-memory file image.
Mp3Player* Mp3Player_create(Mp3Format* fmt, void* base, int total)
{
    SndPacket pkt;
    pkt.field0 = 0;
    pkt.size = 0;
    pkt.field8 = 0;

    int size = FUN_0113f1c0(0xb);
    Mp3Player* self = (Mp3Player*)g_pSystem->Alloc((unsigned)(size + 0x104),
                                                   "MP3 Player Instance", 0x10, 0);
    self->mHandle = FUN_0113f1d0(&Mp3Player_processFrame, 0, self, &self->mEvent, size);
    FUN_01132fe0(&self->m24);
    FUN_0113fca0(&self->m34);
    self->mpFormat = fmt;
    self->mPosition = 0;
    self->mBytes = 0;
    self->mpBase = (int)base;
    self->mTotal = total;
    self->mState = 0;
    self->mField0c = 0;
    self->mpExtra = 0;
    self->mFieldec = 0;
    for (int k = 0; k < 10; ++k)
        self->mChunks[k] = 0;
    self->mpOnFree = 0;

    unsigned char* p = (unsigned char*)base;
    int sel = Mp3Player_parseHeader(p, self);
    int done = 0;
    for (;;) {
        int idx = sel + 3;
        if (idx == 0) {
            // RIFF
            if ((((unsigned)p[8] << 24) | ((unsigned)p[9] << 16) | ((unsigned)p[10] << 8) |
                 (unsigned)p[11]) != 0x57415645) {
                self->mPosition = self->mTotal;
                self->mState = 3;
                return self;
            }
            p += 0xc;
            unsigned char* limit = (unsigned char*)base + total;
            while (p < limit) {
                unsigned tag = ((unsigned)p[0] << 24) | ((unsigned)p[1] << 16) |
                               ((unsigned)p[2] << 8) | (unsigned)p[3];
                unsigned sz = ((unsigned)p[4] << 24) | ((unsigned)p[5] << 16) |
                              ((unsigned)p[6] << 8) | (unsigned)p[7];
                if (tag == 0x666d7420) {
                    if (sz < 0x10)
                        break;
                    if ((((unsigned)p[8] << 8) | (unsigned)p[9]) != 0x55) {
                        self->mPosition = self->mTotal;
                        self->mState = 3;
                        return self;
                    }
                } else if (tag == 0x64617461) {
                    p += 8;
                    break;
                }
                p = p + sz + 8;
            }
            self->mPosition += (int)(p - (unsigned char*)base);
            Mp3Player_parseHeader(p, self);
        } else if (idx == 1) {
            // ID3
            int v = ((((p[6] & 0x7f) << 7 | (p[7] & 0x7f)) << 7 | (p[8] & 0x7f)) << 7 |
                     (p[9] & 0x7f)) + 10;
            self->mPosition += v;
            p += v;
            Mp3Player_parseHeader(p, self);
        } else if (idx == 2) {
            self->mPosition = self->mTotal;
            self->mState = 3;
            return self;
        } else if (idx == 3) {
            unsigned char* q = (unsigned char*)Mp3Player_findSync(
                p, (self->mpBase - (int)p) + self->mTotal);
            if (q == 0) {
                self->mPosition = self->mTotal;
                self->mState = 3;
                return self;
            }
            self->mPosition = (int)(q - (unsigned char*)self->mpBase);
            p = q;
            done = 1;
        } else {
            done = 1;
        }

        int next = Mp3Player_parseHeader(p, self);
        if (done) {
            Mp3Format* f = self->mpFormat;
            self->mField9b = 0x10;
            self->m34.b5 = 0x7f;
            self->m24.f0 = (uint8_t)RwFloat2Int(f->f0 * 127.0f);
            self->m24.w8 = (int16_t)RwFloat2Int(f->f1 * 4096.0f);
            self->m24.f3 = (uint8_t)RwFloat2Int(f->f2 * 127.0f);
            self->m24.wc = (int16_t)RwFloat2Int(f->f4);
            self->m24.we = (int16_t)RwFloat2Int(f->f5);
            self->m24.f4 = (uint8_t)RwFloat2Int(f->p3[0] * 127.0f);

            unsigned char channels = self->mChannels;
            int j = 0;
            if (channels != 0) {
                do {
                    self->m34.gain[j] =
                        (uint16_t)((uint16_t)g_014cafd2[j + (unsigned)channels * 6] << 8);
                    ++j;
                } while (j < (int)(unsigned)self->mChannels);
            }
            self->mStartHandle = FUN_0113f250(self->mHandle, &self->mSampleRate,
                                              &self->m34, &self->m24);

            for (int n = 0; n < 10; ++n) {
                int pos = self->mPosition;
                int r = Mp3Player_parseHeader((unsigned char*)base + pos, self);
                pkt.size = (unsigned)((n > 0) ? (int)0x80000000 : 0) |
                           ((unsigned)self->mField1c & 0x7fffffffu);
                pkt.channel[0] = (unsigned char*)base + pos;
                SNDPKTPLAY_submit(self->mHandle, &pkt);
                self->mPosition += r;
            }
            return self;
        }
        sel = next;
    }
}

} } } // namespace rw::audio::core
