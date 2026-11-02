// src/game/cmn/spat2hdr.cpp.cpp -- migrated from slice(s) s01140b70 by tools/migrate/rewrite.py
// Object file: cmn/spat2hdr.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int16_t g_16e7c74[];     // 0x16e7c74

// ---- items of slice s01140b70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int16_t g_16e7c74[];     // 0x16e7c74
struct SndParser {           // SNDI tag stream parser context
    const uint8_t* data;     // +0x00
    int32_t        tag;      // +0x04
    uint32_t       f08;      // +0x08  (byte value of the tag)
    const uint8_t* value;    // +0x0c
    uint32_t       size;     // +0x10
};
void SNDMEMI_alloc(void*, int);                       // 0x113ec90
void FUN_0113fca0(void*);                             // 0x113fca0
int  FUN_01156bb0(SndParser*);                        // 0x1156bb0
void FUN_01156c40(int, void*, void*, void*, void*);   // 0x1156c40
void* FUN_0112e980(const char*, int);                 // 0x112e980
void* FUN_011e0744(void*, const void*, uint32_t);     // 0x11e0744  (memcpy thunk)
// ---- items of slice s01140b70 end

// @ 0x011412b0
extern "C" void SNDI_patchtohdr(int arg0, const char* hdr, void* p4, void* p100, void* p28, uint8_t* flag)
{
    SNDMEMI_alloc(p4, 4);
    SNDMEMI_alloc(p100, 0x64);
    SNDMEMI_alloc(p28, 0x1c);

    if ((hdr[0] == 'P' && hdr[1] == 'T') ||
        (hdr[0] == 'G' && hdr[1] == 'S' && hdr[2] == 'T' && hdr[3] == 'R')) {
        FUN_01156c40(0, (void*)hdr, p4, p100, p28);
        if (flag != 0)
            *flag = 1;
        return;
    }

    if (flag != 0)
        *flag = 0;

    FUN_0113fca0(p100);

    uint8_t* p4b = (uint8_t*)p4;
    SndParser parser;
    parser.data = (const uint8_t*)hdr + 4;
    *(uint16_t*)p4b = 0x5622;
    p4b[2] = 1;
    p4b[3] = 10;
    *(uint32_t*)p28 = 0;

    uint32_t* pT = (uint32_t*)((char*)p100 + 0x54);

    while (FUN_01156bb0(&parser)) {
        int tag = parser.tag;
        uint32_t val = parser.f08;
        if (tag == 0xa0) {
            p4b[3] = (uint8_t)val;
        } else if (tag == 0x9c) {
            *(uint16_t*)((char*)p100 + 8) = (uint16_t)val;
        } else if (tag == 0x9d) {
            *(uint16_t*)((char*)p100 + 0xa) = (uint16_t)val;
        } else if (tag == 0x9e) {
            *(uint16_t*)((char*)p100 + 0xc) = (uint16_t)val;
        } else if (tag == 0x9f) {
            *(uint16_t*)((char*)p100 + 0xe) = (uint16_t)val;
        } else if (tag == 0xa6) {
            *(uint16_t*)((char*)p100 + 0x10) = (uint16_t)val;
        } else if (tag == 0xa7) {
            *(uint16_t*)((char*)p100 + 0x12) = (uint16_t)val;
        } else if (tag == 0x98) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 0", parser.size);
            *(void**)((char*)p100 + 0x14) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x2c) = parser.size;
        } else if (tag == 0x99) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 1", parser.size);
            *(void**)((char*)p100 + 0x18) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x30) = parser.size;
        } else if (tag == 0x9a) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 2", parser.size);
            *(void**)((char*)p100 + 0x1c) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x34) = parser.size;
        } else if (tag == 0x9b) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 3", parser.size);
            *(void**)((char*)p100 + 0x20) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x38) = parser.size;
        } else if (tag == 0xa4) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 4", parser.size);
            *(void**)((char*)p100 + 0x24) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x3c) = parser.size;
        } else if (tag == 0xa5) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 5", parser.size);
            *(void**)((char*)p100 + 0x28) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x40) = parser.size;
        } else if (tag == 0x80) {
            ((uint8_t*)p100)[6] = (uint8_t)val;
        } else if (tag == 0x82) {
            p4b[2] = (uint8_t)val;
        } else if (tag == 0x84) {
            *(uint16_t*)p4b = (uint16_t)val;
        } else if (tag == 0x85) {
            *(uint32_t*)p28 = val;
        } else if (tag == 0x13) {
            ((uint8_t*)p100)[5] = (uint8_t)val;
        } else if (tag == 0x06) {
            ((uint8_t*)p100)[2] = (uint8_t)val;
        } else if (tag == 0x88) {
            ((uint32_t*)p28)[1] = val;
        } else if (tag == 0x89) {
            ((uint32_t*)p28)[2] = val;
        } else if (tag == 0x94) {
            ((uint32_t*)p28)[3] = val;
        } else if (tag == 0x95) {
            ((uint32_t*)p28)[4] = val;
        } else if (tag == 0xa2) {
            ((uint32_t*)p28)[5] = val;
        } else if (tag == 0xa3) {
            ((uint32_t*)p28)[6] = val;
        } else if (tag == 0x14) {
            pT[-4] = (uint32_t)(size_t)parser.value;
            *pT = parser.size;
            pT++;
        }
    }

    int i = (int)(uint8_t)p4b[2] - 1;
    if (i >= 0) {
        int* pi = (int*)((char*)p28 + 4 + i * 4);
        int16_t* ps = (int16_t*)((char*)p100 + 8 + i * 2);
        uint8_t numchan = p4b[2];
        do {
            uint8_t t = (uint8_t)p4b[2];
            int idx = i + (int)numchan * 6;
            *ps = (int16_t)(*ps + g_16e7c74[idx]);
            *pi = *pi + arg0;
            i--;
            ps--;
            pi--;
        } while (i >= 0);
    }
}
