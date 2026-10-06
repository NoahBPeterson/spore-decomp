// @ 0x010adab0
void __cdecl hkPoweredChain_CalculateVelocities(int *param_1,int param_2)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  int *piVar5;
  float fVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float *local_574;
  float *local_570;
  float *local_56c;
  int local_55c;
  int local_554;
  
  local_570 = (float *)param_1[4];
  local_56c = (float *)param_1[5];
  local_554 = 0;
  if (0 < param_1[1]) {
    local_55c = 0;
    pfVar10 = local_570 + 0x12;
    pfVar11 = local_56c + 0xe;
    local_574 = (float *)(param_2 + 8);
    do {
      iVar14 = param_1[7];
      piVar5 = (int *)(param_1[6] + local_554 * 4);
      iVar7 = *piVar5;
      iVar12 = iVar7 + iVar14;
      iVar13 = piVar5[1] + iVar14;
      pfVar1 = (float *)(iVar12 + 0x40);
      pfVar2 = (float *)(iVar12 + 0x50);
      pfVar3 = (float *)(iVar13 + 0x40);
      pfVar4 = (float *)(iVar13 + 0x50);
      fVar6 = *(float*)&param_1[2] * *(float *)(*param_1 + 0x40);
      fVar8 = *(float*)&param_1[3];
      local_574[-2] =
           *(float*)&param_1[2] * pfVar10[-0xf] -
           (((((*(float *)(iVar13 + 0x58) * pfVar10[-8] + *(float *)(iVar12 + 0x58) * pfVar10[-0xc])
              + (*(float *)(iVar12 + 0x48) - *(float *)(iVar13 + 0x48)) * pfVar10[-0x10]) * fVar6 +
             (((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar10[-8] +
              (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar10[-0xc]) +
             ((*(float *)(iVar12 + 0x18) - *(float *)(iVar12 + 0x48)) -
             (*(float *)(iVar13 + 0x18) - *(float *)(iVar13 + 0x48))) * pfVar10[-0x10]) * fVar8) +
            (((*(float *)(iVar13 + 0x54) * pfVar10[-9] + *(float *)(iVar12 + 0x54) * pfVar10[-0xd])
             + (*(float *)(iVar12 + 0x44) - *(float *)(iVar13 + 0x44)) * pfVar10[-0x11]) * fVar6 +
            (((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar10[-9] +
             (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) * pfVar10[-0xd]) +
            ((*(float *)(iVar12 + 0x14) - *(float *)(iVar12 + 0x44)) -
            (*(float *)(iVar13 + 0x14) - *(float *)(iVar13 + 0x44))) * pfVar10[-0x11]) * fVar8)) +
           (((*pfVar4 * pfVar10[-10] + *pfVar2 * pfVar10[-0xe]) + (*pfVar1 - *pfVar3) * *local_570)
            * fVar6 +
           fVar8 * (((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar10[-10] +
                    (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar10[-0xe]) +
                   ((*(float *)(iVar7 + 0x10 + iVar14) - *(float *)(iVar12 + 0x40)) -
                   (*(float *)(iVar13 + 0x10) - *pfVar3)) * *local_570)));
      fVar6 = *(float*)&param_1[2] * *(float *)(*param_1 + 0x40);
      fVar8 = *(float*)&param_1[3];
      local_574[-1] =
           *(float*)&param_1[2] * pfVar10[-3] -
           (((((*pfVar4 * pfVar10[2] + *pfVar2 * pfVar10[-2]) + (*pfVar1 - *pfVar3) * pfVar10[-6]) *
              fVar6 + fVar8 * (((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar10[2] +
                               (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar10[-2]) +
                              ((*(float *)(iVar12 + 0x10) - *pfVar1) -
                              (*(float *)(iVar13 + 0x10) - *pfVar3)) * pfVar10[-6])) +
            ((((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar10[4] +
              (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * *pfVar10) +
             ((*(float *)(iVar12 + 0x18) - *(float *)(iVar12 + 0x48)) -
             (*(float *)(iVar13 + 0x18) - *(float *)(iVar13 + 0x48))) * pfVar10[-4]) * fVar8 +
            fVar6 * ((*(float *)(iVar12 + 0x48) - *(float *)(iVar13 + 0x48)) * pfVar10[-4] +
                    (*(float *)(iVar13 + 0x58) * pfVar10[4] + *(float *)(iVar12 + 0x58) * *pfVar10))
            )) + ((((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar10[3] +
                   (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) * pfVar10[-1]) +
                  ((*(float *)(iVar12 + 0x14) - *(float *)(iVar12 + 0x44)) -
                  (*(float *)(iVar13 + 0x14) - *(float *)(iVar13 + 0x44))) * pfVar10[-5]) * fVar8 +
                 ((*(float *)(iVar12 + 0x44) - *(float *)(iVar13 + 0x44)) * pfVar10[-5] +
                 (*(float *)(iVar13 + 0x54) * pfVar10[3] + *(float *)(iVar12 + 0x54) * pfVar10[-1]))
                 * fVar6));
      fVar6 = *(float*)&param_1[2] * *(float *)(*param_1 + 0x40);
      fVar8 = *(float*)&param_1[3];
      *local_574 = *(float*)&param_1[2] * pfVar10[9] -
                   (((((*pfVar4 * pfVar10[0xe] + *pfVar2 * pfVar10[10]) +
                      (*pfVar1 - *pfVar3) * pfVar10[6]) * fVar6 +
                     fVar8 * (((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar10[0xe] +
                              (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar10[10]) +
                             ((*(float *)(iVar12 + 0x10) - *pfVar1) -
                             (*(float *)(iVar13 + 0x10) - *pfVar3)) * pfVar10[6])) +
                    (fVar6 * ((*(float *)(iVar13 + 0x58) * pfVar10[0x10] +
                              *(float *)(iVar12 + 0x58) * pfVar10[0xc]) +
                             (*(float *)(iVar12 + 0x48) - *(float *)(iVar13 + 0x48)) * pfVar10[8]) +
                    fVar8 * (((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) *
                              pfVar10[0x10] +
                             (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar10[0xc])
                            + ((*(float *)(iVar12 + 0x18) - *(float *)(iVar12 + 0x48)) -
                              (*(float *)(iVar13 + 0x18) - *(float *)(iVar13 + 0x48))) * pfVar10[8])
                    )) + (((*(float *)(iVar13 + 0x54) * pfVar10[0xf] +
                           *(float *)(iVar12 + 0x54) * pfVar10[0xb]) +
                          (*(float *)(iVar12 + 0x44) - *(float *)(iVar13 + 0x44)) * pfVar10[7]) *
                          fVar6 + fVar8 * (((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54))
                                            * pfVar10[0xf] +
                                           (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) *
                                           pfVar10[0xb]) +
                                          ((*(float *)(iVar12 + 0x14) - *(float *)(iVar12 + 0x44)) -
                                          (*(float *)(iVar13 + 0x14) - *(float *)(iVar13 + 0x44))) *
                                          pfVar10[7])));
      local_574[1] = 0.0;
      fVar8 = *(float *)(param_1[9] + 0x10 + local_55c);
      iVar14 = param_1[9] + local_55c;
      fVar9 = fVar8 * *(float *)(*param_1 + 0x40);
      fVar6 = *(float *)(iVar14 + 0x14);
      local_574[2] = fVar8 * pfVar11[-7] -
                     ((((*pfVar4 * pfVar11[-10] + *pfVar2 * *local_56c) * fVar9 +
                       ((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar11[-10] +
                       (*(float *)(iVar12 + 0x20) - *pfVar2) * *local_56c) * fVar6) +
                      (fVar9 * (*(float *)(iVar13 + 0x58) * pfVar11[-8] +
                               *(float *)(iVar12 + 0x58) * pfVar11[-0xc]) +
                      fVar6 * ((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar11[-8]
                              + (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) *
                                pfVar11[-0xc]))) +
                     (fVar9 * (*(float *)(iVar13 + 0x54) * pfVar11[-9] +
                              *(float *)(iVar12 + 0x54) * pfVar11[-0xd]) +
                     fVar6 * ((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar11[-9]
                             + (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) *
                               pfVar11[-0xd])));
      fVar6 = *(float *)(iVar14 + 0x28) * *(float *)(*param_1 + 0x40);
      fVar8 = *(float *)(iVar14 + 0x2c);
      local_574[3] = *(float *)(iVar14 + 0x28) * pfVar11[1] -
                     ((((*pfVar4 * pfVar11[-2] + *pfVar2 * pfVar11[-6]) * fVar6 +
                       ((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar11[-2] +
                       (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar11[-6]) * fVar8) +
                      (fVar6 * (*(float *)(iVar13 + 0x58) * *pfVar11 +
                               *(float *)(iVar12 + 0x58) * pfVar11[-4]) +
                      fVar8 * ((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * *pfVar11 +
                              (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar11[-4])
                      )) + (fVar6 * (*(float *)(iVar13 + 0x54) * pfVar11[-1] +
                                    *(float *)(iVar12 + 0x54) * pfVar11[-5]) +
                           fVar8 * ((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) *
                                    pfVar11[-1] +
                                   (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) *
                                   pfVar11[-5])));
      fVar6 = *(float *)(iVar14 + 0x40) * *(float *)(*param_1 + 0x40);
      local_570 = local_570 + 0x24;
      local_56c = local_56c + 0x18;
      pfVar10 = pfVar10 + 0x24;
      local_55c = local_55c + 0x4c;
      fVar8 = *(float *)(iVar14 + 0x44);
      local_554 = local_554 + 1;
      local_574[4] = *(float *)(iVar14 + 0x40) * pfVar11[9] -
                     ((((*pfVar4 * pfVar11[6] + *pfVar2 * pfVar11[2]) * fVar6 +
                       ((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar11[6] +
                       (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar11[2]) * fVar8) +
                      (fVar6 * (*(float *)(iVar13 + 0x58) * pfVar11[8] +
                               *(float *)(iVar12 + 0x58) * pfVar11[4]) +
                      fVar8 * ((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar11[8]
                              + (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar11[4]
                              ))) +
                     (fVar6 * (*(float *)(iVar13 + 0x54) * pfVar11[7] +
                              *(float *)(iVar12 + 0x54) * pfVar11[3]) +
                     fVar8 * ((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar11[7] +
                             (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) * pfVar11[3])))
      ;
      local_574[5] = 0.0;
      pfVar11 = pfVar11 + 0x18;
      local_574 = local_574 + 8;
    } while (local_554 < param_1[1]);
  }
  return;
}
