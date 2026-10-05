#include <math.h>
#include <string.h>

extern int (*DAT_01634378)(...);
extern int DAT_0163437c;
extern int DAT_01634380;
extern int FUN_011fda50(...);


int
FUN_00797a20(int *param_1,int *param_2,int param_3,int *param_4,float *param_5,float *param_6,
            int param_7)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  unsigned int uVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float local_1830;
  float local_182c;
  float local_1828;
  int local_1824;
  float *local_17f0;
  int local_17e0;
  float local_17c0;
  float local_17bc;
  float local_17b8;
  float local_17b4;
  float local_17b0;
  float local_17ac;
  float local_17a8;
  float local_17a4;
  float local_1798;
  float local_1794;
  float local_1790;
  int uStack_178c;
  int uStack_1788;
  int uStack_1784;
  float fStack_1780;
  float fStack_177c;
  float fStack_1778;
  int local_1774;
  float local_1770;
  float fStack_176c;
  float fStack_1768;
  float fStack_1764;
  float local_1760;
  float fStack_175c;
  float fStack_1758;
  float fStack_1754;
  float local_1750;
  float fStack_174c;
  float fStack_1748;
  float fStack_1744;
  float local_1740;
  float fStack_173c;
  float fStack_1738;
  float fStack_1734;
  float local_1730;
  float fStack_172c;
  float fStack_1728;
  float fStack_1724;
  float local_1720;
  float fStack_171c;
  float fStack_1718;
  float fStack_1714;
  float local_1710;
  float fStack_170c;
  float fStack_1708;
  float fStack_1704;
  float local_1700;
  float fStack_16fc;
  float fStack_16f8;
  float fStack_16f4;
  float local_16f0;
  float fStack_16ec;
  float fStack_16e8;
  float fStack_16e4;
  float local_16e0;
  float fStack_16dc;
  float fStack_16d8;
  float fStack_16d4;
  float local_16d0;
  float fStack_16cc;
  float fStack_16c8;
  float fStack_16c4;
  float local_16b0;
  float fStack_16ac;
  float fStack_16a8;
  float fStack_16a4;
  float local_16a0;
  float fStack_169c;
  float fStack_1698;
  float fStack_1694;
  float fStack_1680;
  float fStack_167c;
  float fStack_1678;
  float fStack_1674;
  float fStack_1670;
  float fStack_166c;
  float fStack_1668;
  float fStack_1664;
  float local_1660;
  float fStack_165c;
  float fStack_1658;
  float fStack_1654;
  float local_1650;
  float fStack_164c;
  float fStack_1648;
  float fStack_1644;
  float fStack_1640;
  float fStack_163c;
  float fStack_1638;
  float fStack_1634;
  float local_1630;
  float fStack_162c;
  float fStack_1628;
  float fStack_1624;
  float fStack_1620;
  float fStack_161c;
  float fStack_1618;
  float fStack_1614;
  float local_1610;
  float fStack_160c;
  float fStack_1608;
  int uStack_1604;
  float fStack_1600;
  float fStack_15fc;
  float fStack_15f8;
  float fStack_15f4;
  float fStack_15f0;
  float fStack_15ec;
  float fStack_15e8;
  float fStack_15e4;
  float fStack_15e0;
  float fStack_15dc;
  float fStack_15d8;
  float fStack_15d4;
  float fStack_15d0;
  float fStack_15cc;
  float fStack_15c8;
  float fStack_15c4;
  float fStack_15c0;
  float fStack_15bc;
  float fStack_15b8;
  float fStack_15b4;
  float fStack_15b0;
  float fStack_15ac;
  float fStack_15a8;
  float fStack_15a4;
  float fStack_15a0;
  float fStack_159c;
  float fStack_1598;
  float fStack_1594;
  float fStack_1590;
  float fStack_158c;
  float fStack_1588;
  float fStack_1584;
  float fStack_1580;
  float fStack_157c;
  float fStack_1578;
  float fStack_1574;
  float fStack_1570;
  float fStack_156c;
  float fStack_1568;
  float fStack_1564;
  float fStack_1560;
  float fStack_155c;
  float fStack_1558;
  float fStack_1554;
  float local_1540;
  float fStack_153c;
  float fStack_1538;
  float fStack_1534;
  float local_1530;
  float fStack_152c;
  float fStack_1528;
  float fStack_1524;
  float local_1500;
  float fStack_14fc;
  float fStack_14f8;
  float fStack_14f4;
  float local_14f0;
  float fStack_14ec;
  float fStack_14e8;
  float fStack_14e4;
  float local_14c0;
  float fStack_14bc;
  float fStack_14b8;
  float fStack_14b4;
  float local_14b0;
  float fStack_14ac;
  float fStack_14a8;
  float fStack_14a4;
  float local_1480;
  float fStack_147c;
  float fStack_1478;
  float fStack_1474;
  float local_1470;
  float fStack_146c;
  float fStack_1468;
  float fStack_1464;
  float local_1440;
  float fStack_143c;
  float fStack_1438;
  float fStack_1434;
  float local_1430;
  float fStack_142c;
  float fStack_1428;
  float fStack_1424;
  float local_1400;
  float fStack_13fc;
  float fStack_13f8;
  float fStack_13f4;
  float local_13f0;
  float fStack_13ec;
  float fStack_13e8;
  float fStack_13e4;
  float fStack_13c0;
  float fStack_13bc;
  float fStack_13b8;
  float fStack_13b4;
  float fStack_13b0;
  float fStack_13ac;
  float fStack_13a8;
  float fStack_13a4;
  float local_1370;
  float fStack_136c;
  float fStack_1368;
  float fStack_1364;
  float local_1330;
  float fStack_132c;
  float fStack_1328;
  float fStack_1324;
  float local_1304 [205];
  float local_fd0 [1007];
  int uStack_14;
  
  uStack_14 = 0x797a30;
  local_1770 = *param_5;
  fStack_176c = param_5[1];
  fStack_1768 = param_5[2];
  fStack_1764 = param_5[3];
  local_1774 = *(int *)(param_3 + 0x14);
  local_1760 = param_5[4];
  fStack_175c = param_5[5];
  fStack_1758 = param_5[6];
  fStack_1754 = param_5[7];
  local_1750 = param_5[8];
  fStack_174c = param_5[9];
  fStack_1748 = param_5[10];
  fStack_1744 = param_5[0xb];
  local_1740 = param_5[0xc];
  fStack_173c = param_5[0xd];
  fStack_1738 = param_5[0xe];
  fStack_1734 = param_5[0xf];
  local_1830 = 1.0;
  local_182c = 1.0;
  local_1828 = 1.0;
  local_1824 = 0;
  if (0 < local_1774) {
    local_1630 = 1.4142135;
    fStack_162c = 1.4142135;
    fStack_1628 = 1.4142135;
    fStack_1624 = 1.4142135;
    pfVar7 = (float *)(*param_4 + 8);
    local_1610 = 0.5;
    fStack_160c = 0.5;
    fStack_1608 = 0.5;
    uStack_1604 = 0x3f000000;
    local_17f0 = (float *)(param_7 + 0x24);
    local_1650 = 0.0;
    fStack_164c = 0.0;
    fStack_1648 = 0.0;
    fStack_1644 = 0.0;
    local_16d0 = 1.0;
    fStack_16cc = 1.0;
    fStack_16c8 = 1.0;
    fStack_16c4 = 1.0;
    local_17e0 = 0;
    pfVar6 = local_1304;
    pfVar8 = local_fd0;
    do {
      if (*(int *)(param_3 + 0x10) == 0x30) {
        pfVar4 = (float *)FUN_011fda50(local_1824);
        fVar11 = *pfVar4;
        fVar13 = pfVar4[1];
        fVar15 = pfVar4[2];
        fVar16 = pfVar4[3];
        local_17c0 = pfVar4[4];
        local_17bc = pfVar4[5];
        local_17b8 = pfVar4[6];
        local_17b4 = pfVar4[7];
        local_17b0 = pfVar4[8];
        local_17ac = pfVar4[9];
        local_17a8 = pfVar4[10];
        local_17a4 = pfVar4[0xb];
      }
      else {
        pfVar4 = (float *)FUN_011fda50(local_1824);
        fVar11 = *pfVar4;
        fVar13 = pfVar4[1];
        fVar15 = pfVar4[2];
        fVar16 = pfVar4[3];
        local_17c0 = pfVar4[4];
        local_17bc = pfVar4[5];
        local_17b8 = pfVar4[6];
        fStack_1664 = pfVar4[7];
        uStack_178c = 0x3f800000;
        uStack_1788 = 0x3f800000;
        uStack_1784 = 0x3f800000;
        local_17b4 = 1.0;
        local_17b0 = 1.0;
        local_17ac = 1.0;
        fStack_1780 = local_17c0;
        fStack_177c = local_17bc;
        fStack_1778 = local_17b8;
        fStack_1670 = local_17c0;
        fStack_166c = local_17bc;
        fStack_1668 = local_17b8;
        fStack_15c0 = local_17c0;
        fStack_15bc = local_17bc;
        fStack_15b8 = local_17b8;
        fStack_15b4 = fStack_1664;
        fStack_15a0 = local_17c0;
        fStack_159c = local_17bc;
        fStack_1598 = local_17b8;
        fStack_1594 = fStack_1664;
      }
      fVar17 = local_17f0[-5];
      fVar18 = local_17f0[-4];
      fVar19 = local_17f0[-3];
      fVar10 = local_17f0[-2];
      local_16e0 = (fVar19 * fVar13 - fVar18 * fVar15) + (fVar10 * fVar11 + fVar16 * fVar17);
      fStack_16dc = (fVar17 * fVar15 - fVar19 * fVar11) + (fVar10 * fVar13 + fVar16 * fVar18);
      fStack_16d8 = (fVar18 * fVar11 - fVar17 * fVar13) + (fVar10 * fVar15 + fVar16 * fVar19);
      fStack_16d4 = (fVar17 * fVar11 - fVar17 * fVar11) + (fVar10 * fVar11 + fVar16 * fVar17);
      local_17ac = local_17f0[1] * local_17ac;
      local_17b4 = local_17f0[-1] * local_17b4;
      local_17b0 = local_17b0 * *local_17f0;
      fVar10 = local_1630 * local_16e0;
      fVar12 = fStack_162c * fStack_16dc;
      fVar14 = fStack_1628 * fStack_16d8;
      fVar15 = fStack_1624 *
               (fVar16 * local_17f0[-2] - ((fVar19 * fVar15 + fVar18 * fVar13) + fVar17 * fVar11));
      fVar16 = (local_1650 - fVar10) * fVar10 + local_1610;
      fVar17 = (fStack_164c - fVar12) * fVar12 + fStack_160c;
      fVar18 = (fStack_1648 - fVar14) * fVar14 + fStack_1608;
      fVar11 = fVar15 * fVar14 + fVar12 * fVar10;
      fVar13 = fVar15 * fVar10 + fVar14 * fVar12;
      local_1370 = fVar15 * fVar12 + fVar10 * fVar14;
      fVar20 = fVar12 * fVar10 - fVar15 * fVar14;
      fStack_136c = fVar14 * fVar12 - fVar15 * fVar10;
      fVar12 = fVar10 * fVar14 - fVar15 * fVar12;
      fStack_1368 = fVar17 + fVar16;
      fVar17 = fVar18 + fVar17;
      fVar16 = fVar16 + fVar18;
      fVar10 = (local_17b4 * fVar17 + fStack_164c * fVar20) + fStack_1648 * local_1370;
      fVar18 = (local_17b4 * fVar11 + fStack_164c * fVar16) + fStack_1648 * fStack_136c;
      fVar19 = (local_17b4 * fVar12 + fStack_164c * fVar13) + fStack_1648 * fStack_1368;
      local_16b0 = (local_1650 * fVar17 + local_17b0 * fVar20) + fStack_1648 * local_1370;
      fStack_16ac = (local_1650 * fVar11 + local_17b0 * fVar16) + fStack_1648 * fStack_136c;
      fStack_16a8 = (local_1650 * fVar12 + local_17b0 * fVar13) + fStack_1648 * fStack_1368;
      fStack_16a4 = (local_1650 * fVar20 + local_17b0 * fVar11) + fStack_1648 * fStack_1368;
      local_16a0 = (local_1650 * fVar17 + fStack_164c * fVar20) + local_17ac * local_1370;
      fStack_169c = (local_1650 * fVar11 + fStack_164c * fVar16) + local_17ac * fStack_136c;
      fStack_1698 = (local_1650 * fVar12 + fStack_164c * fVar13) + local_17ac * fStack_1368;
      fStack_1694 = (local_1650 * fVar20 + fStack_164c * fVar11) + local_17ac * fStack_1368;
      fVar15 = ((fStack_164c * fVar20 + local_1650 * fVar17) + fStack_1648 * local_1370) +
               local_1650 * local_16d0;
      fVar11 = ((fStack_164c * fVar16 + local_1650 * fVar11) + fStack_1648 * fStack_136c) +
               fStack_164c * fStack_16cc;
      fVar13 = ((fStack_164c * fVar13 + local_1650 * fVar12) + fStack_1648 * fStack_1368) +
               fStack_1648 * fStack_16c8;
      if (*(char *)(local_17f0 + 5) == '\0') {
        fVar16 = (fVar18 * local_1650 + fVar10 * local_1830) + fVar19 * local_1650;
        fVar17 = (fVar18 * local_182c + fVar10 * fStack_164c) + fVar19 * fStack_164c;
        fVar10 = (fVar18 * fStack_1648 + fVar10 * fStack_1648) + fVar19 * local_1828;
        local_1480 = (fStack_16ac * local_1650 + local_16b0 * local_1830) + fStack_16a8 * local_1650
        ;
        fStack_147c = (fStack_16ac * local_182c + local_16b0 * fStack_164c) +
                      fStack_16a8 * fStack_164c;
        fStack_1478 = (fStack_16ac * fStack_1648 + local_16b0 * fStack_1648) +
                      fStack_16a8 * local_1828;
        fStack_1474 = (fStack_16ac * fStack_1644 + local_16b0 * fStack_1644) +
                      fStack_16a8 * fStack_1644;
        local_1470 = (fStack_169c * local_1650 + local_16a0 * local_1830) + fStack_1698 * local_1650
        ;
        fStack_146c = (fStack_169c * local_182c + local_16a0 * fStack_164c) +
                      fStack_1698 * fStack_164c;
        fStack_1468 = (fStack_169c * fStack_1648 + local_16a0 * fStack_1648) +
                      fStack_1698 * local_1828;
        fStack_1464 = (fStack_169c * fStack_1644 + local_16a0 * fStack_1644) +
                      fStack_1698 * fStack_1644;
        fVar12 = ((fVar11 * local_1650 + fVar15 * local_1830) + fVar13 * local_1650) +
                 local_1650 * local_16d0;
        fVar14 = ((fVar11 * local_182c + fVar15 * fStack_164c) + fVar13 * fStack_164c) +
                 fStack_164c * fStack_16cc;
        fVar20 = ((fVar11 * fStack_1648 + fVar15 * fStack_1648) + fVar13 * local_1828) +
                 fStack_1648 * fStack_16c8;
        fVar22 = (fVar17 * local_1650 + fVar16 * local_16d0) + fVar10 * local_1650;
        fVar23 = (fVar17 * fStack_16cc + fVar16 * fStack_164c) + fVar10 * fStack_164c;
        fVar24 = (fVar17 * fStack_1648 + fVar16 * fStack_1648) + fVar10 * fStack_16c8;
        fVar11 = (fStack_147c * local_1650 + local_1480 * local_16d0) + fStack_1478 * local_1650;
        fVar13 = (fStack_147c * fStack_16cc + local_1480 * fStack_164c) + fStack_1478 * fStack_164c;
        fVar15 = (fStack_147c * fStack_1648 + local_1480 * fStack_1648) + fStack_1478 * fStack_16c8;
        fStack_1434 = (fStack_147c * fStack_1644 + local_1480 * fStack_1644) +
                      fStack_1478 * fStack_1644;
        fVar16 = (fStack_146c * local_1650 + local_1470 * local_16d0) + fStack_1468 * local_1650;
        fVar17 = (fStack_146c * fStack_16cc + local_1470 * fStack_164c) + fStack_1468 * fStack_164c;
        fVar19 = (fStack_146c * fStack_1648 + local_1470 * fStack_1648) + fStack_1468 * fStack_16c8;
        fStack_1424 = (fStack_146c * fStack_1644 + local_1470 * fStack_1644) +
                      fStack_1468 * fStack_1644;
        fVar10 = ((fVar14 * local_1650 + fVar12 * local_16d0) + fVar20 * local_1650) +
                 (local_17f0[2] * (local_17f0[-9] + local_17c0)) * local_16d0;
        fVar18 = ((fVar14 * fStack_16cc + fVar12 * fStack_164c) + fVar20 * fStack_164c) +
                 (local_17f0[3] * (local_17f0[-8] + local_17bc)) * fStack_16cc;
        fVar12 = ((fVar14 * fStack_1648 + fVar12 * fStack_1648) + fVar20 * fStack_16c8) +
                 (local_17f0[4] * (local_17f0[-7] + local_17b8)) * fStack_16c8;
        local_1440 = fVar11;
        fStack_143c = fVar13;
        fStack_1438 = fVar15;
        local_1430 = fVar16;
        fStack_142c = fVar17;
        fStack_1428 = fVar19;
      }
      else {
        fVar16 = local_17f0[0x1b];
        fVar17 = local_17f0[0x1d];
        fVar12 = local_17f0[0x1c];
        fVar14 = (fVar18 * local_1650 + fVar10 * fVar16) + fVar19 * local_1650;
        fVar20 = (fVar18 * fVar12 + fVar10 * fStack_164c) + fVar19 * fStack_164c;
        fVar10 = (fVar18 * fStack_1648 + fVar10 * fStack_1648) + fVar19 * fVar17;
        local_1540 = (fStack_16ac * local_1650 + local_16b0 * fVar16) + fStack_16a8 * local_1650;
        fStack_153c = (fStack_16ac * fVar12 + local_16b0 * fStack_164c) + fStack_16a8 * fStack_164c;
        fStack_1538 = (fStack_16ac * fStack_1648 + local_16b0 * fStack_1648) + fStack_16a8 * fVar17;
        fStack_1534 = (fStack_16ac * fStack_1644 + local_16b0 * fStack_1644) +
                      fStack_16a8 * fStack_1644;
        local_1530 = (fStack_169c * local_1650 + local_16a0 * fVar16) + fStack_1698 * local_1650;
        fStack_152c = (fStack_169c * fVar12 + local_16a0 * fStack_164c) + fStack_1698 * fStack_164c;
        fStack_1528 = (fStack_169c * fStack_1648 + local_16a0 * fStack_1648) + fStack_1698 * fVar17;
        fStack_1524 = (fStack_169c * fStack_1644 + local_16a0 * fStack_1644) +
                      fStack_1698 * fStack_1644;
        fVar18 = ((fVar11 * local_1650 + fVar15 * fVar16) + fVar13 * local_1650) +
                 local_1650 * local_16d0;
        fVar19 = ((fVar11 * fVar12 + fVar15 * fStack_164c) + fVar13 * fStack_164c) +
                 fStack_164c * fStack_16cc;
        fVar17 = ((fVar11 * fStack_1648 + fVar15 * fStack_1648) + fVar13 * fVar17) +
                 fStack_1648 * fStack_16c8;
        fVar22 = (fVar20 * local_1650 + fVar14 * local_16d0) + fVar10 * local_1650;
        fVar23 = (fVar20 * fStack_16cc + fVar14 * fStack_164c) + fVar10 * fStack_164c;
        local_16f0 = (fVar20 * fStack_1648 + fVar14 * fStack_1648) + fVar10 * fStack_16c8;
        fVar12 = (fStack_153c * local_1650 + local_1540 * local_16d0) + fStack_1538 * local_1650;
        fVar14 = (fStack_153c * fStack_16cc + local_1540 * fStack_164c) + fStack_1538 * fStack_164c;
        fVar20 = (fStack_153c * fStack_1648 + local_1540 * fStack_1648) + fStack_1538 * fStack_16c8;
        local_1660 = local_1650;
        fStack_165c = fStack_164c;
        fStack_1658 = fStack_16c8;
        fStack_1654 = fStack_1644;
        local_1330 = (fStack_152c * local_1650 + local_1530 * local_16d0) + fStack_1528 * local_1650
        ;
        fStack_132c = (fStack_152c * fStack_16cc + local_1530 * fStack_164c) +
                      fStack_1528 * fStack_164c;
        fStack_1328 = (fStack_152c * fStack_1648 + local_1530 * fStack_1648) +
                      fStack_1528 * fStack_16c8;
        fStack_1324 = (fStack_152c * fStack_1644 + local_1530 * fStack_1644) +
                      fStack_1528 * fStack_1644;
        fVar11 = local_17f0[0xf];
        fVar13 = local_17f0[0x10];
        fVar15 = local_17f0[0x11];
        fVar16 = ((fVar19 * local_1650 + fVar18 * local_16d0) + fVar17 * local_1650) +
                 (local_17f0[-9] + local_17c0) * local_16d0;
        fVar10 = ((fVar19 * fStack_16cc + fVar18 * fStack_164c) + fVar17 * fStack_164c) +
                 (local_17f0[-8] + local_17bc) * fStack_16cc;
        fVar17 = ((fVar19 * fStack_1648 + fVar18 * fStack_1648) + fVar17 * fStack_16c8) +
                 (local_17f0[-7] + local_17b8) * fStack_16c8;
        fVar18 = (fVar22 * local_17f0[0xb] + fVar23 * fVar11) + local_16f0 * local_17f0[0x13];
        fVar19 = (fVar22 * local_17f0[0xc] + fVar23 * fVar13) + local_16f0 * local_17f0[0x14];
        fVar22 = (fVar22 * local_17f0[0xd] + fVar23 * fVar15) + local_16f0 * local_17f0[0x15];
        local_14c0 = (fVar12 * local_17f0[0xb] + fVar14 * fVar11) + fVar20 * local_17f0[0x13];
        fStack_14bc = (fVar12 * local_17f0[0xc] + fVar14 * fVar13) + fVar20 * local_17f0[0x14];
        fStack_14b8 = (fVar12 * local_17f0[0xd] + fVar14 * fVar15) + fVar20 * local_17f0[0x15];
        fStack_14b4 = (fVar12 * local_17f0[0xe] + fVar14 * local_17f0[0x12]) +
                      fVar20 * local_17f0[0x16];
        local_14b0 = (local_1330 * local_17f0[0xb] + fStack_132c * fVar11) +
                     fStack_1328 * local_17f0[0x13];
        fStack_14ac = (local_1330 * local_17f0[0xc] + fStack_132c * fVar13) +
                      fStack_1328 * local_17f0[0x14];
        fStack_14a8 = (local_1330 * local_17f0[0xd] + fStack_132c * fVar15) +
                      fStack_1328 * local_17f0[0x15];
        fStack_14a4 = (local_1330 * local_17f0[0xe] + fStack_132c * local_17f0[0x12]) +
                      fStack_1328 * local_17f0[0x16];
        fVar11 = ((fVar16 * local_17f0[0xb] + fVar10 * fVar11) + fVar17 * local_17f0[0x13]) +
                 local_17f0[0x17] * local_16d0;
        fVar13 = ((fVar16 * local_17f0[0xc] + fVar10 * fVar13) + fVar17 * local_17f0[0x14]) +
                 local_17f0[0x18] * fStack_16cc;
        fVar15 = ((fVar16 * local_17f0[0xd] + fVar10 * fVar15) + fVar17 * local_17f0[0x15]) +
                 local_17f0[0x19] * fStack_16c8;
        fVar16 = (fVar19 * local_1650 + fVar18 * local_1830) + fVar22 * local_1650;
        fVar10 = (fVar19 * local_182c + fVar18 * fStack_164c) + fVar22 * fStack_164c;
        fVar17 = (fVar19 * fStack_1648 + fVar18 * fStack_1648) + fVar22 * local_1828;
        local_1500 = (fStack_14bc * local_1650 + local_14c0 * local_1830) + fStack_14b8 * local_1650
        ;
        fStack_14fc = (fStack_14bc * local_182c + local_14c0 * fStack_164c) +
                      fStack_14b8 * fStack_164c;
        fStack_14f8 = (fStack_14bc * fStack_1648 + local_14c0 * fStack_1648) +
                      fStack_14b8 * local_1828;
        fStack_14f4 = (fStack_14bc * fStack_1644 + local_14c0 * fStack_1644) +
                      fStack_14b8 * fStack_1644;
        local_14f0 = (fStack_14ac * local_1650 + local_14b0 * local_1830) + fStack_14a8 * local_1650
        ;
        fStack_14ec = (fStack_14ac * local_182c + local_14b0 * fStack_164c) +
                      fStack_14a8 * fStack_164c;
        fStack_14e8 = (fStack_14ac * fStack_1648 + local_14b0 * fStack_1648) +
                      fStack_14a8 * local_1828;
        fStack_14e4 = (fStack_14ac * fStack_1644 + local_14b0 * fStack_1644) +
                      fStack_14a8 * fStack_1644;
        fVar12 = ((fVar13 * local_1650 + fVar11 * local_1830) + fVar15 * local_1650) +
                 local_1650 * local_16d0;
        fVar14 = ((fVar13 * local_182c + fVar11 * fStack_164c) + fVar15 * fStack_164c) +
                 fStack_164c * fStack_16cc;
        fVar20 = ((fVar13 * fStack_1648 + fVar11 * fStack_1648) + fVar15 * local_1828) +
                 fStack_1648 * fStack_16c8;
        fVar22 = (fVar10 * local_1650 + fVar16 * local_16d0) + fVar17 * local_1650;
        fVar23 = (fVar10 * fStack_16cc + fVar16 * fStack_164c) + fVar17 * fStack_164c;
        fVar24 = (fVar10 * fStack_1648 + fVar16 * fStack_1648) + fVar17 * fStack_16c8;
        fVar11 = (fStack_14fc * local_1650 + local_1500 * local_16d0) + fStack_14f8 * local_1650;
        fVar13 = (fStack_14fc * fStack_16cc + local_1500 * fStack_164c) + fStack_14f8 * fStack_164c;
        fVar15 = (fStack_14fc * fStack_1648 + local_1500 * fStack_1648) + fStack_14f8 * fStack_16c8;
        fStack_13f4 = (fStack_14fc * fStack_1644 + local_1500 * fStack_1644) +
                      fStack_14f8 * fStack_1644;
        fVar16 = (fStack_14ec * local_1650 + local_14f0 * local_16d0) + fStack_14e8 * local_1650;
        fVar17 = (fStack_14ec * fStack_16cc + local_14f0 * fStack_164c) + fStack_14e8 * fStack_164c;
        fVar19 = (fStack_14ec * fStack_1648 + local_14f0 * fStack_1648) + fStack_14e8 * fStack_16c8;
        fStack_13e4 = (fStack_14ec * fStack_1644 + local_14f0 * fStack_1644) +
                      fStack_14e8 * fStack_1644;
        fVar10 = ((fVar14 * local_1650 + fVar12 * local_16d0) + fVar20 * local_1650) +
                 local_17f0[6] * local_16d0;
        fVar18 = ((fVar14 * fStack_16cc + fVar12 * fStack_164c) + fVar20 * fStack_164c) +
                 local_17f0[7] * fStack_16cc;
        fVar12 = ((fVar14 * fStack_1648 + fVar12 * fStack_1648) + fVar20 * fStack_16c8) +
                 local_17f0[8] * fStack_16c8;
        fStack_16ec = local_16f0;
        fStack_16e8 = local_16f0;
        fStack_16e4 = local_16f0;
        local_1400 = fVar11;
        fStack_13fc = fVar13;
        fStack_13f8 = fVar15;
        local_13f0 = fVar16;
        fStack_13ec = fVar17;
        fStack_13e8 = fVar19;
      }
      local_1730 = (fVar23 * local_1760 + fVar22 * local_1770) + fVar24 * local_1750;
      fStack_172c = (fVar23 * fStack_175c + fVar22 * fStack_176c) + fVar24 * fStack_174c;
      fStack_1728 = (fVar23 * fStack_1758 + fVar22 * fStack_1768) + fVar24 * fStack_1748;
      fStack_1724 = (fVar23 * fStack_1754 + fVar22 * fStack_1764) + fVar24 * fStack_1744;
      local_1720 = (fVar13 * local_1760 + fVar11 * local_1770) + fVar15 * local_1750;
      fStack_171c = (fVar13 * fStack_175c + fVar11 * fStack_176c) + fVar15 * fStack_174c;
      fStack_1718 = (fVar13 * fStack_1758 + fVar11 * fStack_1768) + fVar15 * fStack_1748;
      fStack_1714 = (fVar13 * fStack_1754 + fVar11 * fStack_1764) + fVar15 * fStack_1744;
      local_1710 = (fVar17 * local_1760 + fVar16 * local_1770) + fVar19 * local_1750;
      fStack_170c = (fVar17 * fStack_175c + fVar16 * fStack_176c) + fVar19 * fStack_174c;
      fStack_1708 = (fVar17 * fStack_1758 + fVar16 * fStack_1768) + fVar19 * fStack_1748;
      fStack_1704 = (fVar17 * fStack_1754 + fVar16 * fStack_1764) + fVar19 * fStack_1744;
      local_1700 = ((fVar18 * local_1760 + fVar10 * local_1770) + fVar12 * local_1750) +
                   local_1740 * local_16d0;
      fStack_16fc = ((fVar18 * fStack_175c + fVar10 * fStack_176c) + fVar12 * fStack_174c) +
                    fStack_173c * fStack_16cc;
      fStack_16f8 = ((fVar18 * fStack_1758 + fVar10 * fStack_1768) + fVar12 * fStack_1748) +
                    fStack_1738 * fStack_16c8;
      fStack_16f4 = ((fVar18 * fStack_1754 + fVar10 * fStack_1764) + fVar12 * fStack_1744) +
                    fStack_1734 * fStack_16c4;
      iVar1 = *(int *)(param_2[2] + local_1824 * 4);
      local_1798 = local_17b4;
      local_1794 = local_17b0;
      local_1790 = local_17ac;
      fStack_1364 = fStack_1368;
      if ((DAT_01634380 == -1) || (DAT_01634380 == iVar1)) {
        (*DAT_01634378)(iVar1,&local_1730,&local_17b4,DAT_0163437c);
      }
      pfVar4 = (float *)(*param_1 + local_17e0);
      fVar11 = pfVar4[6];
      fVar13 = *pfVar4;
      fVar15 = pfVar4[1];
      fVar16 = pfVar4[2];
      fVar10 = pfVar4[4];
      fVar17 = (fVar15 * local_1720 + fVar13 * local_1730) + fVar16 * local_1710;
      fVar18 = (fVar15 * fStack_171c + fVar13 * fStack_172c) + fVar16 * fStack_170c;
      fVar19 = (fVar15 * fStack_1718 + fVar13 * fStack_1728) + fVar16 * fStack_1708;
      fVar12 = (fVar15 * fStack_1714 + fVar13 * fStack_1724) + fVar16 * fStack_1704;
      fVar13 = pfVar4[5];
      fVar15 = pfVar4[9];
      fVar14 = (fVar13 * local_1720 + fVar10 * local_1730) + fVar11 * local_1710;
      fVar20 = (fVar13 * fStack_171c + fVar10 * fStack_172c) + fVar11 * fStack_170c;
      fVar22 = (fVar13 * fStack_1718 + fVar10 * fStack_1728) + fVar11 * fStack_1708;
      fVar10 = (fVar13 * fStack_1714 + fVar10 * fStack_1724) + fVar11 * fStack_1704;
      fVar11 = pfVar4[8];
      fVar13 = pfVar4[10];
      fVar16 = pfVar4[0xd];
      fVar23 = (fVar15 * local_1720 + fVar11 * local_1730) + fVar13 * local_1710;
      fVar24 = (fVar15 * fStack_171c + fVar11 * fStack_172c) + fVar13 * fStack_170c;
      fVar21 = (fVar15 * fStack_1718 + fVar11 * fStack_1728) + fVar13 * fStack_1708;
      fVar15 = (fVar15 * fStack_1714 + fVar11 * fStack_1724) + fVar13 * fStack_1704;
      fVar11 = pfVar4[0xc];
      fVar13 = pfVar4[0xe];
      fStack_15e0 = ((fVar16 * local_1720 + fVar11 * local_1730) + fVar13 * local_1710) +
                    local_1700 * local_16d0;
      fStack_15dc = ((fVar16 * fStack_171c + fVar11 * fStack_172c) + fVar13 * fStack_170c) +
                    fStack_16fc * fStack_16cc;
      fStack_15d8 = ((fVar16 * fStack_1718 + fVar11 * fStack_1728) + fVar13 * fStack_1708) +
                    fStack_16f8 * fStack_16c8;
      fStack_15d4 = ((fVar16 * fStack_1714 + fVar11 * fStack_1724) + fVar13 * fStack_1704) +
                    fStack_16f4 * fStack_16c4;
      fStack_1640 = fVar17;
      fStack_163c = fVar18;
      fStack_1638 = fVar19;
      fStack_1634 = fVar12;
      fStack_1680 = fVar14;
      fStack_167c = fVar20;
      fStack_1678 = fVar22;
      fStack_1674 = fVar10;
      fStack_1620 = fVar23;
      fStack_161c = fVar24;
      fStack_1618 = fVar21;
      fStack_1614 = fVar15;
      if (param_6 != (float *)0x0) {
        fVar11 = *param_6;
        fVar13 = param_6[1];
        fVar16 = param_6[2];
        fVar2 = param_6[4];
        fVar3 = param_6[5];
        fStack_1640 = (fVar11 * fVar17 + fVar13 * fVar14) + fVar16 * fVar23;
        fStack_163c = (fVar11 * fVar18 + fVar13 * fVar20) + fVar16 * fVar24;
        fStack_1638 = (fVar11 * fVar19 + fVar13 * fVar22) + fVar16 * fVar21;
        fStack_1634 = (fVar11 * fVar12 + fVar13 * fVar10) + fVar16 * fVar15;
        fVar11 = param_6[6];
        fStack_1680 = (fVar2 * fVar17 + fVar3 * fVar14) + fVar11 * fVar23;
        fStack_167c = (fVar2 * fVar18 + fVar3 * fVar20) + fVar11 * fVar24;
        fStack_1678 = (fVar2 * fVar19 + fVar3 * fVar22) + fVar11 * fVar21;
        fStack_1674 = (fVar2 * fVar12 + fVar3 * fVar10) + fVar11 * fVar15;
        fVar11 = param_6[8];
        fVar13 = param_6[9];
        fVar16 = param_6[10];
        fStack_1620 = (fVar11 * fVar17 + fVar13 * fVar14) + fVar16 * fVar23;
        fStack_161c = (fVar11 * fVar18 + fVar13 * fVar20) + fVar16 * fVar24;
        fStack_1618 = (fVar11 * fVar19 + fVar13 * fVar22) + fVar16 * fVar21;
        fStack_1614 = (fVar11 * fVar12 + fVar13 * fVar10) + fVar16 * fVar15;
        fVar11 = param_6[0xc];
        fVar13 = param_6[0xd];
        fVar16 = param_6[0xe];
        fStack_15e0 = ((fVar11 * fVar17 + fVar13 * fVar14) + fVar16 * fVar23) +
                      fStack_15e0 * local_16d0;
        fStack_15dc = ((fVar11 * fVar18 + fVar13 * fVar20) + fVar16 * fVar24) +
                      fStack_15dc * fStack_16cc;
        fStack_15d8 = ((fVar11 * fVar19 + fVar13 * fVar22) + fVar16 * fVar21) +
                      fStack_15d8 * fStack_16c8;
        fStack_15d4 = ((fVar11 * fVar12 + fVar13 * fVar10) + fVar16 * fVar15) +
                      fStack_15d4 * fStack_16c4;
        fStack_13c0 = fStack_1680;
        fStack_13bc = fStack_167c;
        fStack_13b8 = fStack_1678;
        fStack_13b4 = fStack_1674;
        fStack_13b0 = fStack_1620;
        fStack_13ac = fStack_161c;
        fStack_13a8 = fStack_1618;
        fStack_13a4 = fStack_1614;
      }
      iVar1 = *param_2;
      pfVar7[-2] = fStack_1640;
      pfVar7[-1] = fStack_1680;
      *pfVar7 = fStack_1620;
      pfVar7[1] = fStack_15e0;
      pfVar7[2] = fStack_163c;
      pfVar7[3] = fStack_167c;
      pfVar7[4] = fStack_161c;
      pfVar7[5] = fStack_15dc;
      pfVar7[6] = fStack_1638;
      pfVar7[7] = fStack_1678;
      pfVar7[8] = fStack_1618;
      pfVar7[9] = fStack_15d8;
      uVar5 = *(unsigned int *)(iVar1 + local_1824 * 4) & 3;
      if (uVar5 == 0) {
LAB_00798c60:
        local_1770 = local_1730;
        fStack_176c = fStack_172c;
        fStack_1768 = fStack_1728;
        fStack_1764 = fStack_1724;
        local_1760 = local_1720;
        fStack_175c = fStack_171c;
        fStack_1758 = fStack_1718;
        fStack_1754 = fStack_1714;
        local_1750 = local_1710;
        fStack_174c = fStack_170c;
        fStack_1748 = fStack_1708;
        fStack_1744 = fStack_1704;
        pfVar4 = pfVar6;
        pfVar9 = pfVar8;
        local_1830 = 1.0 / local_17b4;
        local_182c = 1.0 / local_17b0;
        local_1828 = 1.0 / local_17ac;
        local_1740 = local_1700;
        fStack_173c = fStack_16fc;
        fStack_1738 = fStack_16f8;
        fStack_1734 = fStack_16f4;
      }
      else if (uVar5 == 1) {
        local_1770 = pfVar8[-0x10];
        fStack_176c = pfVar8[-0xf];
        fStack_1768 = pfVar8[-0xe];
        fStack_1764 = pfVar8[-0xd];
        local_1830 = pfVar6[-3];
        pfVar9 = pfVar8 + -0x10;
        pfVar4 = pfVar6 + -3;
        local_1760 = pfVar8[-0xc];
        fStack_175c = pfVar8[-0xb];
        fStack_1758 = pfVar8[-10];
        fStack_1754 = pfVar8[-9];
        local_182c = pfVar6[-2];
        local_1750 = pfVar8[-8];
        fStack_174c = pfVar8[-7];
        fStack_1748 = pfVar8[-6];
        fStack_1744 = pfVar8[-5];
        local_1740 = pfVar8[-4];
        fStack_173c = pfVar8[-3];
        fStack_1738 = pfVar8[-2];
        fStack_1734 = pfVar8[-1];
        local_1828 = pfVar6[-1];
      }
      else {
        pfVar4 = pfVar6;
        pfVar9 = pfVar8;
        if (uVar5 == 2) {
          *pfVar8 = local_1770;
          pfVar8[1] = fStack_176c;
          pfVar8[2] = fStack_1768;
          pfVar8[3] = fStack_1764;
          *pfVar6 = local_1830;
          pfVar8[4] = local_1760;
          pfVar8[5] = fStack_175c;
          pfVar8[6] = fStack_1758;
          pfVar8[7] = fStack_1754;
          pfVar6[1] = local_182c;
          pfVar8[8] = local_1750;
          pfVar8[9] = fStack_174c;
          pfVar8[10] = fStack_1748;
          pfVar8[0xb] = fStack_1744;
          pfVar8[0xc] = local_1740;
          pfVar8[0xd] = fStack_173c;
          pfVar8[0xe] = fStack_1738;
          pfVar8[0xf] = fStack_1734;
          pfVar6[2] = local_1828;
          pfVar8 = pfVar8 + 0x10;
          pfVar6 = pfVar6 + 3;
          goto LAB_00798c60;
        }
      }
      local_17e0 = local_17e0 + 0x40;
      local_1824 = local_1824 + 1;
      local_17f0 = local_17f0 + 0x28;
      pfVar7 = pfVar7 + 0xc;
      pfVar6 = pfVar4;
      pfVar8 = pfVar9;
      fStack_1600 = fStack_1640;
      fStack_15fc = fStack_163c;
      fStack_15f8 = fStack_1638;
      fStack_15f4 = fStack_1634;
      fStack_15f0 = fStack_1620;
      fStack_15ec = fStack_161c;
      fStack_15e8 = fStack_1618;
      fStack_15e4 = fStack_1614;
      fStack_15d0 = fStack_15e0;
      fStack_15cc = fStack_15dc;
      fStack_15c8 = fStack_15d8;
      fStack_15c4 = fStack_15d4;
      fStack_15b0 = fStack_1680;
      fStack_15ac = fStack_167c;
      fStack_15a8 = fStack_1678;
      fStack_15a4 = fStack_1674;
      fStack_1590 = fStack_1640;
      fStack_158c = fStack_163c;
      fStack_1588 = fStack_1638;
      fStack_1584 = fStack_1634;
      fStack_1580 = fStack_15e0;
      fStack_157c = fStack_15dc;
      fStack_1578 = fStack_15d8;
      fStack_1574 = fStack_15d4;
      fStack_1570 = fStack_1620;
      fStack_156c = fStack_161c;
      fStack_1568 = fStack_1618;
      fStack_1564 = fStack_1614;
      fStack_1560 = fStack_1680;
      fStack_155c = fStack_167c;
      fStack_1558 = fStack_1678;
      fStack_1554 = fStack_1674;
    } while (local_1824 < local_1774);
  }
  return 1;
}
