// slice s01173c10 -- audio codec: reflection-coefficient (Huffman VLC) decode + reflection->LPC
//
// 01173c10, 01173eb0, 01173fa0 are hand-written assembly (pushal/popal register-save
// frames, fixed-point / SSE kernels); no compilable C++ source exists for them and they
// are recorded in partial.txt.

typedef unsigned int  u32;
typedef unsigned char u8;

// ---- globals referenced by the codec ----
extern const u32 g_bitMasks[];      // g_bitMasks[1] == 1, g_bitMasks[6] == 0x3f

struct HufEntry { int m_value; int m_bits; float m_fvalue; };
extern const u8       g_htab0[];    // 2 x 256 first-level byte table
extern const HufEntry g_htab1[];    // second-level table (12-byte entries)

struct BitReader {
    u8* m_buf;     // +0
    u32 m_bits;    // +4
    int m_count;   // +8
};

// @ 0x011741c0
void FUN_011741c0(BitReader* br, int flag, float* out, int stride)
{
    if (flag == 0) {
        int idx = 0;
        do {
            if ((br->m_bits & 3) == 1) {
                out[idx] = -2.0f;
                br->m_bits >>= 2;
                br->m_count -= 2;
            }
            else if ((br->m_bits & 3) == 3) {
                out[idx] = 2.0f;
                br->m_bits >>= 2;
                br->m_count -= 2;
            }
            else {
                out[idx] = 0.0f;
                br->m_bits >>= 1;
                br->m_count -= 1;
            }
            int c = br->m_count;
            if (c < 8) {
                u8 b = *br->m_buf++;
                br->m_bits |= (u32)b << c;
                br->m_count = c + 8;
            }
            idx += stride;
        } while (idx < 0x6c);
        return;
    }

    int row = 0;
    int idx = 0;
    for (;;) {
        u32 sym = g_htab0[row * 0x100 + (br->m_bits & 0xff)];
        row = g_htab1[sym].m_value;
        int nb = g_htab1[sym].m_bits;
        br->m_bits >>= nb;
        br->m_count -= nb;
        int c = br->m_count;
        if (c < 8) {
            u8 b = *br->m_buf++;
            br->m_bits |= (u32)b << c;
            br->m_count = c + 8;
        }
        if (sym < 4) {
            if (sym < 2) {
                int mag = 7;
                for (;;) {
                    u32 bit = br->m_bits & g_bitMasks[1];
                    br->m_count--;
                    c = br->m_count;
                    br->m_bits >>= 1;
                    if (c < 8) {
                        u8 b = *br->m_buf++;
                        br->m_bits |= (u32)b << c;
                        br->m_count = c + 8;
                    }
                    if (bit != 1) break;
                    mag++;
                }
                u32 sign = br->m_bits & g_bitMasks[1];
                br->m_count--;
                c = br->m_count;
                br->m_bits >>= 1;
                if (c < 8) {
                    u8 b = *br->m_buf++;
                    br->m_bits |= (u32)b << c;
                    br->m_count = c + 8;
                }
                out[idx] = (sign == 1) ? (float)mag : (float)-mag;
                idx += stride;
            }
            else {
                u32 run = br->m_bits & g_bitMasks[6];
                br->m_count -= 6;
                c = br->m_count;
                br->m_bits >>= 6;
                if (c < 8) {
                    u8 b = *br->m_buf++;
                    br->m_bits |= (u32)b << c;
                    br->m_count = c + 8;
                }
                int n = run + 7;
                if (0x6c < n * stride + idx) n = (0x6c - idx) / stride;
                if (0 < n) {
                    do {
                        out[idx] = 0.0f;
                        idx += stride;
                        n--;
                    } while (n != 0);
                }
            }
        }
        else {
            out[idx] = g_htab1[sym].m_fvalue;
            idx += stride;
        }
        if (0x6b < idx) return;
    }
}

// @ 0x01174420
// Reflection coefficients (matrix at this+0xc .. this+0x2c) -> LPC.
// The original passes the output array in EDI (register-ABI); reproduced here as a
// trailing parameter.
void ReflectionToLpc(int param_1, float* out)
{
    float local_60[24];
    float local_50;
    float local_4c[19];

    local_4c[6] = *(float*)(param_1 + 0x28);
    local_4c[5] = *(float*)(param_1 + 0x24);
    local_4c[4] = *(float*)(param_1 + 0x20);
    local_4c[3] = *(float*)(param_1 + 0x1c);
    local_4c[2] = *(float*)(param_1 + 0x18);
    local_4c[1] = *(float*)(param_1 + 0x14);
    local_4c[0] = *(float*)(param_1 + 0x10);
    local_50 = *(float*)(param_1 + 0xc);

    for (int i = 2; i >= 0; --i)
        local_60[i + 1] = *(float*)(param_1 + i * 4);

    int k = 0;
    local_60[0] = 1.0f;
    do {
        local_60[0] = -(*(float*)(param_1 + 0x2c) * local_4c[6]) - *(float*)(param_1 + 0x28) * local_4c[5];
        local_4c[6] = *(float*)(param_1 + 0x28) * local_60[0] + local_4c[5];
        local_60[0] = local_60[0] - *(float*)(param_1 + 0x24) * local_4c[4];
        local_4c[5] = *(float*)(param_1 + 0x24) * local_60[0] + local_4c[4];
        local_60[0] = local_60[0] - *(float*)(param_1 + 0x20) * local_4c[3];
        local_4c[4] = *(float*)(param_1 + 0x20) * local_60[0] + local_4c[3];
        local_60[0] = local_60[0] - *(float*)(param_1 + 0x1c) * local_4c[2];
        local_4c[3] = *(float*)(param_1 + 0x1c) * local_60[0] + local_4c[2];
        local_60[0] = local_60[0] - *(float*)(param_1 + 0x18) * local_4c[1];
        local_4c[2] = *(float*)(param_1 + 0x18) * local_60[0] + local_4c[1];
        local_60[0] = local_60[0] - *(float*)(param_1 + 0x14) * local_4c[0];
        local_4c[1] = *(float*)(param_1 + 0x14) * local_60[0] + local_4c[0];
        local_60[0] = local_60[0] - *(float*)(param_1 + 0x10) * local_50;
        local_4c[0] = *(float*)(param_1 + 0x10) * local_60[0] + local_50;
        local_60[0] = local_60[0] - *(float*)(param_1 + 0xc) * local_60[3];
        local_50 = *(float*)(param_1 + 0xc) * local_60[0] + local_60[3];

        for (int i = 2; i >= 0; --i) {
            float f = *(float*)(param_1 + i * 4);
            local_60[0] = local_60[0] - f * local_60[i];
            local_60[i + 1] = f * local_60[0] + local_60[i];
        }

        int i2 = 0;
        float f7 = 0.0f;
        float f6 = 0.0f;
        local_60[k + 0xc] = local_60[0];
        if (1 < k) {
            float* p = local_60 + k + 10;
            do {
                f7 = f7 - out[i2] * p[1];
                float f1 = *p;
                i2 = i2 + 2;
                p = p - 2;
                f6 = f6 - out[i2 - 1] * f1;
            } while (i2 < k - 1);
        }
        if (i2 < k)
            local_60[0] = local_60[0] - local_60[(k - i2) + 0xb] * out[i2];

        out[k] = (f6 + f7) + local_60[0];
        k++;
    } while (k < 0xc);
}
