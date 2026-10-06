// Slice s010af750 -- _hkPoweredChain_ScanAndEnableMotors (0x010af750, ~5115 bytes).
//
// Havok powered-chain scan: for every link it builds the link's world transform
// (a 4x4 expansion of the local matrices), walks the 3 motors, and when a motor's
// target is out of tolerance it records the largest-mismatch motor and finally
// sets the corresponding 2-bit state in the chain's motor-state byte array.
//
// Ported from the Ghidra decompilation.  The contiguous float scratch block
// (local_1f0 .. local_100, which the decompiler split into named locals) is kept
// as one array `mat` so addresses into it stay valid; all other locals keep the
// decompiler's names.
//
// PARTIAL: arithmetic/loop structure is reproduced, but the exact Havok transform
// layout written by FUN_0120b1b0 and a handful of stack-local aliasing details are
// reconstructed rather than guaranteed complete.
//
// Card: work/match/scratch_31_card.txt
#include "types.h"

typedef unsigned char  byte;
typedef unsigned int   uint;

extern "C" void FUN_0120b1b0(...);   // hkTransform storage helper

#define F(p, o) (*(float*)((char*)(p) + (o)))
#define I(p, o) (*(int*)((char*)(p) + (o)))

// local_1f0 .. local_100 are consecutive stack floats; index = (0x1f0 - offset)/4
static float mat[64];
#define m_1f0 mat[0]
#define m_1ec mat[1]
#define m_1e8 mat[2]
#define m_1e4 mat[3]
#define m_1e0 mat[4]
#define m_1dc mat[5]
#define m_1d8 mat[6]
#define m_1d4 mat[7]
#define m_1d0 mat[8]
#define m_1cc mat[9]
#define m_1c8 mat[10]
#define m_1c4 mat[11]
#define m_1c0 mat[12]
#define m_1bc mat[13]
#define m_1b8 mat[14]
#define m_1b4 mat[15]
#define m_1b0 mat[16]
#define m_1ac mat[17]
#define m_1a8 mat[18]
#define m_1a4 mat[19]
#define m_1a0 mat[20]
#define m_19c mat[21]
#define m_198 mat[22]
#define m_194 mat[23]
#define m_190 mat[24]
#define m_18c mat[25]
#define m_188 mat[26]
#define m_184 mat[27]
#define m_180 mat[28]
#define m_17c mat[29]
#define m_178 mat[30]
#define m_174 mat[31]
#define m_170 mat[32]
#define m_16c mat[33]
#define m_168 mat[34]
#define m_164 mat[35]
#define m_160 mat[36]
#define m_15c mat[37]
#define m_158 mat[38]
#define m_154 mat[39]
#define m_150 mat[40]
#define m_14c mat[41]
#define m_148 mat[42]
#define m_144 mat[43]
#define m_140 mat[44]
#define m_13c mat[45]
#define m_138 mat[46]
#define m_134 mat[47]
#define m_130 mat[48]
#define m_12c mat[49]
#define m_128 mat[50]
#define m_124 mat[51]
#define m_120 mat[52]
#define m_11c mat[53]
#define m_118 mat[54]
#define m_114 mat[55]
#define m_110 mat[56]
#define m_10c mat[57]
#define m_108 mat[58]
#define m_100 mat[59]
#define m_fc  mat[60]

static inline float hk_abs(float x) { return x < 0.0f ? -x : x; }

// @ 0x010af750
void FUN_010af750(int* param_1, int* param_2, int* param_3)
{
  int* piVar1;
  float fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8;
  int iVar9, iVar12, iVar13, iVar14;
  float* pfVar10;
  byte bVar11;

  float local_320, local_31c, local_318, local_310, local_30c, local_308;
  float local_300, local_2fc, local_2f8, local_2f0, local_2ec, local_2e8;
  float local_2d0[6];
  int local_2b8, local_2b4;
  float local_2b0, local_2ac, local_2a8, local_2a0, local_29c, local_298;
  int local_284;
  float local_280, local_27c, local_278, local_270, local_26c, local_268;
  int local_254, local_250;
  float local_24c, local_248;
  int local_244;
  float local_240, local_23c, local_238, local_230, local_22c, local_228;
  int local_220;
  float* local_21c;
  float local_218;
  byte* local_214;
  float local_210, local_20c, local_208;
  uint local_1f8, local_1f4;
  float local_e8, local_e0, local_dc, local_d8, local_c8, local_c0, local_bc, local_b8, local_b0, local_ac;
  float local_98, local_90, local_8c, local_88, local_7c, local_78;
  float local_68, local_60, local_5c, local_58, local_48, local_38, local_30, local_18;

  iVar12 = param_1[8];
  iVar13 = param_1[1];
  local_220 = -1;
  local_244 = -1;
  iVar9 = iVar13 * 0x3c0;
  iVar14 = iVar9 + -0x240 + iVar12;
  local_218 = 0.0f;
  local_2f8 = 0.0f;
  local_2fc = 0.0f;
  local_300 = 0.0f;
  local_2e8 = 0.0f;
  local_2ec = 0.0f;
  local_2f0 = 0.0f;
  local_238 = ((F(iVar14,0x28) + F(iVar14,0x18)) + F(iVar14,8)) * 0.0f;
  local_230 = ((F(iVar14,0x80) + F(iVar14,0x70)) + F(iVar14,0x60)) * 0.0f;
  local_22c = ((F(iVar14,0x84) + F(iVar14,0x74)) + F(iVar14,0x64)) * 0.0f;
  local_228 = ((F(iVar14,0x88) + F(iVar14,0x78)) + F(iVar14,0x68)) * 0.0f;
  pfVar10 = (float*)(iVar13 * 0x20 + -0x20 + param_1[10] + 0x20);
  iVar13 = iVar13 + -1;
  local_2d0[0] = ((F(iVar14,0xb0) + F(iVar14,0xa0)) + F(iVar14,0x90)) * 0.0f + local_230;
  local_2b4 = iVar13;
  local_2d0[1] = ((F(iVar14,0xb4) + F(iVar14,0xa4)) + F(iVar14,0x94)) * 0.0f + local_22c;
  local_2d0[2] = ((F(iVar14,0xb8) + F(iVar14,0xa8)) + F(iVar14,0x98)) * 0.0f + local_228;
  local_320 = *pfVar10 - (((F(iVar14,0x50) + F(iVar14,0x40)) + F(iVar14,0x30)) * 0.0f +
                ((F(iVar9 + iVar12,-0x220) + F(iVar9 + iVar12,-0x230)) + F(iVar9 + iVar12,-0x240)) * 0.0f);
  local_31c = pfVar10[1] - (((F(iVar14,0x24) + F(iVar14,0x14)) + F(iVar14,4)) * 0.0f +
                ((F(iVar14,0x54) + F(iVar14,0x44)) + F(iVar14,0x34)) * 0.0f);
  local_318 = pfVar10[2] - (local_238 + ((F(iVar14,0x58) + F(iVar14,0x48)) + F(iVar14,0x38)) * 0.0f);
  local_310 = pfVar10[4] - local_2d0[0];
  local_30c = pfVar10[5] - local_2d0[1];
  local_308 = pfVar10[6] - local_2d0[2];

  if (-1 < iVar13) {
    local_254 = iVar13 * 3;
    iVar14 = iVar13 * 0x3c0;
    local_250 = iVar13 * 0x4c;
    local_21c = (float*)(iVar13 * 0x20 + -8 + param_1[10] + 0x20);
    local_2d0[3] = 0.0f;
    do {
      fVar8 = local_308; fVar7 = local_30c; fVar6 = local_310;
      fVar5 = local_318; fVar4 = local_31c; fVar2 = local_320;
      iVar14 = iVar14 + -0x3c0;
      local_2b0 = local_300; local_2ac = local_2fc; local_2a8 = local_2f8;
      local_2a0 = local_2f0; local_29c = local_2ec; local_298 = local_2e8;
      local_300 = local_320; local_2fc = local_31c; local_2f8 = local_318;
      local_2f0 = local_310; local_2ec = local_30c; local_2e8 = local_308;
      local_2b4 = iVar13;
      if (iVar13 < 1) {
        local_318 = 0.0f; local_31c = 0.0f; local_320 = 0.0f;
        local_308 = 0.0f; local_30c = 0.0f; local_310 = 0.0f;
        m_1ec = 0; m_1e8 = 0.0f; m_1e4 = 0; m_1e0 = 0;
        m_1d8 = 0.0f; m_1d4 = 0; m_1d0 = 0; m_1cc = 0; m_1c4 = 0;
        m_1f0 = 1.0f;                         // 0x3f800000
        m_1dc = 1.0f;
        m_1c8 = 1.0f;
        m_1c0 = 0; m_1bc = 0; m_1b8 = 0; m_1b4 = 0; m_1b0 = 0;
        m_1ac = 0; m_1a8 = 0; m_1a4 = 0; m_1a0 = 0; m_19c = 0; m_198 = 0; m_194 = 0;
        m_190 = 0.0f; m_18c = 0.0f; m_188 = 0.0f; m_184 = 0;
        m_180 = 0.0f; m_17c = 0.0f; m_178 = 0.0f; m_174 = 0;
        m_170 = 0.0f; m_16c = 0.0f; m_168 = 0.0f; m_164 = 0;
        m_15c = 0.0f; m_158 = 0.0f; m_154 = 0;
        m_150 = 0.0f; m_148 = 0.0f; m_144 = 0;
        m_140 = 0.0f; m_13c = 0.0f; m_134 = 0;
        m_160 = 1.0f; m_14c = 1.0f; m_138 = 1.0f;
      } else {
        fVar3 = local_320 * F(iVar12, 0x184 + iVar14);
        local_c8 = local_318 * F(iVar12, 0x1a8 + iVar14) +
                   (local_31c * F(iVar12, 0x198 + iVar14) +
                    local_320 * F(iVar12, 0x188 + iVar14));
        local_23c = local_308 * F(iVar12, 0x1d4 + iVar14) +
                    (local_30c * F(iVar12, 0x1c4 + iVar14) +
                     local_310 * F(iVar12, 0x1b4 + iVar14));
        local_238 = local_308 * F(iVar12, 0x1d8 + iVar14) +
                    (local_30c * F(iVar12, 0x1c8 + iVar14) +
                     local_310 * F(iVar12, 0x1b8 + iVar14));
        local_c0 = local_320 * F(iVar12, 0x1e0 + iVar14) +
                   (local_318 * F(iVar12, 0x200 + iVar14) +
                    local_31c * F(iVar12, 0x1f0 + iVar14));
        local_bc = local_318 * F(iVar12, 0x204 + iVar14) +
                   (local_31c * F(iVar12, 500 + iVar14) +
                    local_320 * F(iVar12, 0x1e4 + iVar14));
        local_b8 = local_318 * F(iVar12, 0x208 + iVar14) +
                   (local_31c * F(iVar12, 0x1f8 + iVar14) +
                    local_320 * F(iVar12, 0x1e8 + iVar14));
        local_240 = (local_310 * F(iVar12, 0x1b0 + iVar14) +
                     (local_308 * F(iVar12, 0x1d0 + iVar14) +
                      local_30c * F(iVar12, 0x1c0 + iVar14))) +
                    (local_320 * F(iVar12, 0x180 + iVar14) +
                     (local_318 * F(iVar12, 0x1a0 + iVar14) +
                      local_31c * F(iVar12, 400 + iVar14)));
        local_230 = (local_310 * F(iVar12, 0x210 + iVar14) +
                     (local_308 * F(iVar12, 0x230 + iVar14) +
                      local_30c * F(iVar12, 0x220 + iVar14))) + local_c0;
        local_22c = (local_308 * F(iVar12, 0x234 + iVar14) +
                     (local_30c * F(iVar12, 0x224 + iVar14) +
                      local_310 * F(iVar12, 0x214 + iVar14))) + local_bc;
        local_228 = (local_308 * F(iVar12, 0x238 + iVar14) +
                     (local_30c * F(iVar12, 0x228 + iVar14) +
                      local_310 * F(iVar12, 0x218 + iVar14))) + local_b8;
        local_320 = local_21c[-6] - local_240;
        local_31c = local_21c[-5] -
                    ((local_318 * F(iVar12, 0x1a4 + iVar14) +
                      (local_31c * F(iVar12, 0x194 + iVar14) + fVar3)) + local_23c);
        local_318 = local_21c[-4] - (local_c8 + local_238);
        local_310 = local_21c[-2] - local_230;
        local_30c = local_21c[-1] - local_22c;
        local_308 = *local_21c - local_228;
        FUN_0120b1b0(mat, iVar12 + 0x300 + iVar14);
      }
      local_98 = m_1c8 * local_318 + (m_1d8 * local_31c + m_1e8 * local_320);
      local_90 = local_320 * m_190 + (local_31c * m_180 + local_318 * m_170);
      local_8c = local_320 * m_18c + (local_31c * m_17c + local_318 * m_16c);
      local_88 = local_320 * m_188 + (local_31c * m_178 + local_318 * m_168);
      iVar12 = param_1[8];
      local_68 = fVar5 * F(iVar12, 0x628 + iVar14) +
                 (fVar4 * F(iVar12, 0x618 + iVar14) + fVar2 * F(iVar12, 0x608 + iVar14));
      local_60 = fVar2 * F(iVar12, 0x660 + iVar14) +
                 (fVar5 * F(iVar12, 0x680 + iVar14) + fVar4 * F(iVar12, 0x670 + iVar14));
      local_5c = fVar5 * F(iVar12, 0x684 + iVar14) +
                 (fVar4 * F(iVar12, 0x674 + iVar14) + fVar2 * F(iVar12, 0x664 + iVar14));
      local_58 = fVar5 * F(iVar12, 0x688 + iVar14) +
                 (fVar4 * F(iVar12, 0x678 + iVar14) + fVar2 * F(iVar12, 0x668 + iVar14));
      local_e8 = local_2a8 * F(iVar12, 0x6e8 + iVar14) +
                 (local_2ac * F(iVar12, 0x6d8 + iVar14) + local_2b0 * F(iVar12, 0x6c8 + iVar14));
      local_27c = local_298 * F(iVar12, 0x714 + iVar14) +
                  (local_29c * F(iVar12, 0x704 + iVar14) + local_2a0 * F(iVar12, 0x6f4 + iVar14));
      local_278 = local_298 * F(iVar12, 0x718 + iVar14) +
                  (local_29c * F(iVar12, 0x708 + iVar14) + local_2a0 * F(iVar12, 0x6f8 + iVar14));
      local_e0 = local_2b0 * F(iVar12, 0x720 + iVar14) +
                 (local_2a8 * F(iVar12, 0x740 + iVar14) + local_2ac * F(iVar12, 0x730 + iVar14));
      local_214 = (byte*)(param_1[9] + local_250);
      local_dc = local_2a8 * F(iVar12, 0x744 + iVar14) +
                 (local_2ac * F(iVar12, 0x734 + iVar14) + local_2b0 * F(iVar12, 0x724 + iVar14));
      local_2b8 = 0;
      local_d8 = local_2a8 * F(iVar12, 0x748 + iVar14) +
                 (local_2ac * F(iVar12, 0x738 + iVar14) + local_2b0 * F(iVar12, 0x728 + iVar14));
      local_280 = (local_2b0 * F(iVar12, 0x6c0 + iVar14) +
                   (local_2a8 * F(iVar12, 0x6e0 + iVar14) + local_2ac * F(iVar12, 0x6d0 + iVar14))) +
                  (local_2a0 * F(iVar12, 0x6f0 + iVar14) +
                   (local_298 * F(iVar12, 0x710 + iVar14) + local_29c * F(iVar12, 0x700 + iVar14)));
      local_270 = local_e0 +
                  (local_2a0 * F(iVar12, 0x750 + iVar14) +
                   (local_298 * F(iVar12, 0x770 + iVar14) + local_29c * F(iVar12, 0x760 + iVar14)));
      local_26c = local_dc +
                  (local_298 * F(iVar12, 0x774 + iVar14) +
                   (local_29c * F(iVar12, 0x764 + iVar14) + local_2a0 * F(iVar12, 0x754 + iVar14)));
      local_268 = local_d8 +
                  (local_298 * F(iVar12, 0x778 + iVar14) +
                   (local_29c * F(iVar12, 0x768 + iVar14) + local_2a0 * F(iVar12, 0x758 + iVar14)));
      local_2d0[0] = local_270 +
                     (((fVar6 * F(iVar12, 0x690 + iVar14) +
                        (fVar8 * F(iVar12, 0x6b0 + iVar14) + fVar7 * F(iVar12, 0x6a0 + iVar14))) + local_60) +
                      ((local_310 * m_160 + (local_30c * m_150 + local_308 * m_140)) + local_90));
      local_2d0[1] = local_26c +
                     (((fVar8 * F(iVar12, 0x6b4 + iVar14) +
                        (fVar7 * F(iVar12, 0x6a4 + iVar14) + fVar6 * F(iVar12, 0x694 + iVar14))) + local_5c) +
                      ((local_310 * m_15c + (local_30c * m_14c + local_308 * m_13c)) + local_8c));
      local_2d0[2] = local_268 +
                     (((fVar8 * F(iVar12, 0x6b8 + iVar14) +
                        (fVar7 * F(iVar12, 0x6a8 + iVar14) + fVar6 * F(iVar12, 0x698 + iVar14))) + local_58) +
                      ((local_310 * m_158 + (local_30c * m_148 + local_308 * m_138)) + local_88));
      local_1f4 = (uint)*local_214;
      local_284 = 0;
      do {
        local_1f8 = (*local_214 >> (((byte)local_2b8 & 0xf) << 1)) & 3;
        if (local_1f8 == 3 || local_1f8 == 1) {
          piVar1 = (int*)(param_1[6] + iVar13 * 4);
          iVar13 = piVar1[1] + param_1[7];
          iVar9 = *piVar1 + param_1[7];
          pfVar10 = (float*)((local_254 + local_2b8) * 0x20 + param_1[5]);
          local_38 = F(iVar9,0x28) - F(iVar9,0x58);
          m_110 = F(iVar13,0x20) - F(iVar13,0x50);
          m_10c = F(iVar13,0x24) - F(iVar13,0x54);
          m_108 = F(iVar13,0x28) - F(iVar13,0x58);
          m_130 = F(iVar9,0x50);
          m_12c = F(iVar9,0x54);
          local_30 = (F(iVar9,0x20) - F(iVar9,0x50)) * *pfVar10;
          m_124 = F(iVar9,0x5c);
          m_120 = F(iVar13,0x50);
          m_128 = F(iVar9,0x58);
          m_11c = F(iVar13,0x54);
          m_118 = F(iVar13,0x58);
          m_114 = F(iVar13,0x5c);
          local_48 = m_108 * pfVar10[6];
          local_210 = m_110 * pfVar10[4] + local_30;
          local_18 = F(iVar9,0x58) * pfVar10[2];
          local_7c = F(iVar13,0x54) * pfVar10[5];
          local_78 = F(iVar13,0x58) * pfVar10[6];
          fVar4 = *(float*)(local_214 + local_284 + 0x10) * F(*param_1, 0x40);
          m_100 = (m_120 * pfVar10[4] + F(iVar9,0x50) * *pfVar10) * fVar4;
          m_fc  = (local_7c + F(iVar9,0x54) * pfVar10[1]) * fVar4;
          fVar2 = *(float*)(local_214 + local_284 + 0x14);
          local_20c = (m_10c * pfVar10[5] +
                       (F(iVar9,0x24) - F(iVar9,0x54)) * pfVar10[1]) * fVar2;
          local_208 = (local_48 + local_38 * pfVar10[2]) * fVar2;
          local_b0 = m_100 + local_210 * fVar2;
          local_ac = m_fc + local_20c;
          local_24c = *(float*)(local_214 + local_284 + 0x10) * pfVar10[7] -
                      ((((local_78 + local_18) * fVar4 + local_208) + local_ac) + local_b0);
          local_248 = local_2d0[local_2b8];
          iVar13 = local_2b4;
          if (local_1f8 == 3) {
            if ((local_248 < local_24c) != (local_248 == local_24c)) {
LAB_010b0b08:
              if (local_218 < hk_abs(local_248 - local_24c)) {
                local_218 = hk_abs(local_248 - local_24c);
                local_220 = local_2b4;
                local_244 = local_2b8;
              }
            }
          } else if (local_1f8 == 1 && local_24c <= local_248) {
            goto LAB_010b0b08;
          }
        }
        local_2b8 = local_2b8 + 1;
        local_284 = local_284 + 0x18;
      } while (local_284 < 0x48);
      iVar13 = iVar13 + -1;
      local_21c = local_21c + -8;
      local_2b4 = iVar13;
      local_250 = local_250 + -0x4c;
      local_254 = local_254 + -3;
    } while (-1 < iVar13);

    if (-1 < local_220) {
      bVar11 = (byte)((char)local_244 * 2);
      *(byte*)(local_220 * 0x4c + param_1[9]) =
          (byte)(~((byte)'\x03' << (bVar11 & 0x1f)) & *(byte*)(local_220 * 0x4c + param_1[9]) |
                 (byte)('\0' << (bVar11 & 0x1f)));
      *param_2 = local_220;
      *param_3 = local_244;
    }
  }
  return;
}
