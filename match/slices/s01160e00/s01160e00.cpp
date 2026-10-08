// Slice s01160e00 (0x01160e00): fourth-order IIR filter block (direct form I, one pass over
// 256 samples per channel, unrolled eight outputs per iteration).
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

struct cIIRBufferDesc {
    uint8_t pad0[4];
    float* mData;               // 0x04
    uint8_t pad8[0x0e - 0x08];
    unsigned short mStride;     // 0x0e (floats per channel)
};

struct cIIRBuffers {
    uint8_t pad[0x3000c];
    cIIRBufferDesc* mIn;        // 0x3000c
    cIIRBufferDesc* mOut;       // 0x30010
};

class cIIRFilter {
public:
    float mCoef[10];            // 0x00: b0..b4, (unused), a1..a4
    uint32_t mChannels;         // 0x28
    unsigned short mXOffset;    // 0x2c: input history, 5 floats per channel
    unsigned short mYOffset;    // 0x2e: output history, 5 floats per channel

    void Process(cIIRBuffers* io);   // 0x01160e00
};

extern const float kDenormGuard;   // 0x014ce60c

// One filter output: feed-forward on x0..x4, feedback on y1..y4, plus a denormal guard.
inline float IIRStep(const float* c, float x0, float x1, float x2, float x3, float x4,
                     float y1, float y2, float y3, float y4)
{
    return (((((c[0] * x0 + c[1] * x1) + x2 * c[2]) + c[3] * x3) + x4 * c[4]) -
            (((c[6] * y1 + c[7] * y2) + c[8] * y3) + c[9] * y4)) + kDenormGuard;
}

// @ 0x01160e00
void cIIRFilter::Process(cIIRBuffers* io)
{
    unsigned short xOff = mXOffset;
    unsigned short yOff = mYOffset;
    cIIRBufferDesc* in = io->mIn;
    cIIRBufferDesc* out = io->mOut;
    for (uint32_t ch = 0; ch < mChannels; ++ch) {
        float* xs = (float*)((char*)this + xOff) + ch * 5;
        float* ys = (float*)((char*)this + yOff) + ch * 5;
        const float* src = in->mData + in->mStride * ch;
        float* dst = out->mData + out->mStride * ch;

        float x1 = xs[0], x2 = xs[1], x3 = xs[2], x4 = xs[3];
        float y1 = ys[1], y2 = ys[2], y3 = ys[3], y4 = ys[4];
        float s0, s1, s2, s3 = 0, s4, s5, s6, s7 = 0;
        float o0, o1, o2, o3, o4, o5, o6, o7;
        for (int blk = 32; blk != 0; --blk) {
            s0 = src[0];
            o0 = IIRStep(mCoef, s0, x1, x2, x3, x4, y1, y2, y3, y4);
            dst[0] = o0;
            s1 = src[1];
            o1 = IIRStep(mCoef, s1, s0, x1, x2, x3, o0, y1, y2, y3);
            dst[1] = o1;
            s2 = src[2];
            o2 = IIRStep(mCoef, s2, s1, s0, x1, x2, o1, o0, y1, y2);
            dst[2] = o2;
            s3 = src[3];
            o3 = IIRStep(mCoef, s3, s2, s1, s0, x1, o2, o1, o0, y1);
            dst[3] = o3;
            s4 = src[4];
            o4 = IIRStep(mCoef, s4, s3, s2, s1, s0, o3, o2, o1, o0);
            dst[4] = o4;
            s5 = src[5];
            o5 = IIRStep(mCoef, s5, s4, s3, s2, s1, o4, o3, o2, o1);
            dst[5] = o5;
            s6 = src[6];
            o6 = IIRStep(mCoef, s6, s5, s4, s3, s2, o5, o4, o3, o2);
            dst[6] = o6;
            s7 = src[7];
            o7 = IIRStep(mCoef, s7, s6, s5, s4, s3, o6, o5, o4, o3);
            dst[7] = o7;
            src += 8;
            dst += 8;
            x1 = s7; x2 = s6; x3 = s5; x4 = s4;
            y1 = o7; y2 = o6; y3 = o5; y4 = o4;
        }
        xs[0] = s7;
        xs[4] = s3;
        xs[1] = s6;
        xs[2] = s5;
        xs[3] = s4;
        ys[1] = y1;
        ys[2] = y2;
        ys[3] = y3;
        ys[4] = y4;
    }
    io->mIn = out;
    io->mOut = in;
}
