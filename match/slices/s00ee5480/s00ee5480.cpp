// Slice s00ee5480 -- SP UI message handler, 0x00ee5480 (~5117 bytes, /O2 /MD /Gy /TP).
//
// A large boolean message/notification handler for an SP UI editor object.  `this`
// is the editor (fields at +0x14 handle, +0x18/+0x1c/+0x20 state, +0x24 object ref,
// +0x28 text control ref, +0x2c..+0x40 EA::RectT<float>).  The message (`mp`) is a
// dword struct: +0x0 object id, +0x4 target, +0x8 message id, +0xc sub id,
// +0x10/+0x14 floats, +0x18 object.
//
// PARTIAL: this port reproduces the function's top-level message dispatch and every
// side-effecting engine call identifiable from the Ghidra decompilation, but a few
// deep sub-blocks (unaffiliated-register reconstructions and the tail switch on the
// virtual object's class id) are approximated rather than guaranteed complete.
// Byte-exact is not attempted: a 5000-byte /O2 handler cannot be reproduced from
// decompilation alone.
//
// Card: work/match/scratch_30_card.txt
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- callees (names unknown in the 2008 dev PDB) --------------------------------------
extern "C" {
int   FUN_00435e90(...);
int   FUN_005ff6a0(...);
int   FUN_006c0200(...);
int   FUN_00806ca0(...);
int   FUN_008085d0(...);
int   FUN_00881f00(...);
int   FUN_00dfbba0(...);
int   FUN_00dfd080(...);
int   FUN_00e12f80(...);
int   FUN_00ecb520(...);
int   FUN_00ecb730(...);
int   FUN_00ed39a0(...);
int   FUN_00ed4b50(...);
int   FUN_00ed8950(...);
int   FUN_00edc9e0(...);
int   FUN_00edcce0(...);
int   FUN_00edce00(...);
int   FUN_00edcf30(...);
float FUN_00edcfc0(...);
int   FUN_00edd2d0(...);
int   FUN_00eddf30(...);
int   FUN_00ede110(...);
int   FUN_00ede2b0(...);
int   FUN_00ede400(...);
int   FUN_00ede530(...);
int   FUN_00ede660(...);
int   FUN_00ede790(...);
int   FUN_00ede8c0(...);
int   FUN_00ede9f0(...);
int   FUN_00edf070(...);
int   FUN_00edf090(...);
int   FUN_00edf240(...);
int   FUN_00edf2c0(...);
int   FUN_00edf370(...);
int   FUN_00edf410(...);
int   FUN_00edf830(...);
int   FUN_00edfa30(...);
int   FUN_00edfcc0(...);
int   FUN_00edfd30(...);
int   FUN_00ee01e0(...);
int   FUN_00ee0310(...);
int   FUN_00ee0450(...);
int   FUN_00ee0590(...);
int   FUN_00ee06d0(...);
int   FUN_00ee0960(...);
int   FUN_00ee0eb0(...);
int   FUN_00ee1140(...);
int   FUN_00ee1200(...);
int   FUN_00ee16f0(...);
int   FUN_00ee30d0(...);
int   FUN_00ee31d0(...);
float FUN_00eeebd0(...);
int   FUN_00eef810(...);
int   FUN_00ef7a80(...);
int   FUN_00efbbe0(...);
int   FUN_00efc520(...);
int   FUN_00efc8c0(...);
int   FUN_00f0bdf0(...);
int   FUN_00f0bea0(...);
int   FUN_00f253e0(...);
int   FUN_00f25670(...);
int   FUN_00f27670(...);
int   FUN_00f28b80(...);
int   FUN_00f293b0(...);
int   FUN_00f3be30(...);
int   FUN_00f3e8a0(...);
int   FUN_00f40370(...);
int   FUN_00f41a10(...);
int   FUN_00f427c0(...);
int   FUN_00f45970(...);
int   FUN_00f45a80(...);
int   FUN_008050f0(...);
}

// named engine entry points (from the card's call annotations)
int   SP_WindowManager(...);                       // SP::WindowManager
int   SP_MessageServer(...);                       // SP::MessageServer
int   SP_QualifyNameWithGroup(...);                // SP::QualifyNameWithGroup
int   SP_KillSetiEffects(...);                     // SP::cSPUISpace::KillSetiEffects
int   FUN_00885d0(...);                            // SPUIHelpers::CreateCallbackWinProc
int   EA_operator_new(...);                        // EA::UTFWin::MultiHeapObject::operator_new
int   cSPUILayoutManager_GetWorldMainWindow(...);  // cSPUILayoutManager::GetWorldMainWindow
int   EA_AutoRefCount_assign(...);                 // EA::AutoRefCount<T>::operator=
int   EA_RectT_assign(...);                        // EA::RectT<float>::operator=
int   FUN_00881f00(...);                           // value formatting helper

// globals
extern void* DAT_016c7aa4;
extern char  DAT_01667bac;
extern char  DAT_01667bae;
extern int   DAT_0148a488[];
extern int   DAT_0148a4a0[];
extern int   DAT_0148a4b0[];
extern int   DAT_0148a4c0[];

#define I(p,o)  (*(int*)((char*)(p)+(o)))
#define U(p,o)  (*(unsigned*)((char*)(p)+(o)))
#define F(p,o)  (*(float*)((char*)(p)+(o)))
#define B(p,o)  (*(char*)((char*)(p)+(o)))

// virtual call: slot at byte offset o of the vtable at *(void**)p
#define VS(p,o) (*(void**)((*(char**)(p))+(o)))
#define VC0(RT,p,o)             ((RT(__thiscall*)(void*))VS(p,o))((void*)(p))
#define VC1(RT,p,o,a)           ((RT(__thiscall*)(void*,int))VS(p,o))((void*)(p),(int)(a))
#define VC2(RT,p,o,a,b)         ((RT(__thiscall*)(void*,int,int))VS(p,o))((void*)(p),(int)(a),(int)(b))
#define VC3(RT,p,o,a,b,c)       ((RT(__thiscall*)(void*,int,int,int))VS(p,o))((void*)(p),(int)(a),(int)(b),(int)(c))
#define VC5F(RT,p,o,a,b,c,d,e)  ((RT(__thiscall*)(void*,int,int,int,float,float))VS(p,o))((void*)(p),(int)(a),(int)(b),(int)(c),(float)(d),(float)(e))
#define VC2F(RT,p,o,a,b)        ((RT(__thiscall*)(void*,float,float))VS(p,o))((void*)(p),(float)(a),(float)(b))

// message ids (bit patterns of the float immediates in the decompilation)
enum {
  MSG_685A2B9 = 0x0685a2b9, SUB_6849100 = 0x06849100,
  MSG_287259F6 = 0x287259f6, MSG_4CAB02D = 0x04cab02d,
  ID_742BD88 = 0x0742bd88, ID_742BD98 = 0x0742bd98, ID_742BDB0 = 0x0742bdb0,
  ID_742BDC0 = 0x0742bdc0, ID_742BDD0 = 0x0742bdd0,
  ID_742BDE0 = 0x0742bde0, ID_742BE6 = 0x0742cbe6, ID_742CBE0 = 0x0742cbe0,
  ID_595E0A8 = 0x0595e0a8, ID_74656A0 = 0x074656a0,
  ID_6F00A884 = 0x6f00a884, ID_76A93C50 = 0x76a93c50, ID_76A93C51 = 0x76a93c51,
  ID_76A93C53 = 0x76a93c53,
  R_7957BA8 = 0x07957ba8, R_7918320 = 0x07918320, R_792BF78 = 0x0792bf78,
  R_7C8A7A8 = 0x07c8a7a8, R_7C8A7D0 = 0x07c8a7d0, R_8918320 = 0x08918320,
  R_892BF78 = 0x0892bf78, R_9918320 = 0x09918320, R_7EC82C0 = 0x07ec82c0,
  R_7A44749 = 0x07a44749, R_7A4489C = 0x07a4489c,
  R_742CD10 = 0x0742cd10, R_742C8F8 = 0x0742c8f8, R_742C8D0 = 0x0742c8d0,
  R_791A7C8 = 0x0791a7c8, R_7C8A7D1 = 0x07c8a7d1,
  R_742BDE0 = 0x0742bde0, R_74656A0 = 0x074656a0
};

// @ 0x00ee5480
int FUN_00ee5480(void* selfp, int param_2, void* mp)
{
  char* self = (char*)selfp;
  char* m = (char*)mp;
  int iVar2, iVar5, iVar6;
  char cVar3;
  float fVar7, fVar16, fVar21;
  int* piVar10;
  void* piVar11;
  float* pfVar13;
  void* puVar14;
  void* puVar23;
  int uVar8, uVar20, uVar22;
  unsigned uVar9;
  int bVar15;
  char cStack_561 = 0;
  void* puStack_560 = 0;
  void* puStack_55c = 0;
  void* puStack_558 = 0;
  u8 auStack_550[3];
  u8 uStack_54d;
  float afStack_54c[3];
  void* puStack_540 = 0;
  void* puStack_53c = 0;
  char auStack_520[1252];
  int iStack_3c = 0;

  int id = I(self, 0x14);
  if (id == -1 || id == -2) return 0;
  iVar5 = FUN_00f3e8a0(id);
  if (iVar5 == 0) return 0;
  iVar6 = FUN_00efc520();
  iVar6 = iVar6 * 0x4e0 + I(iVar5, 0x70);

  int mid = I(m, 8);
  unsigned umid = (unsigned)mid;

  if (umid < 0x0685a2ba) {
    if (mid == MSG_685A2B9) {
      if (I(m, 0xc) == SUB_6849100) {
        piVar11 = (void*)FUN_00edc9e0(I(m, 0), 0x76c61c8);
        if (piVar11) {
          piVar10 = (int*)VC0(void*, piVar11, 0x10);
          VC1(void, piVar10, 0xe8, (int)piVar11);
        }
        piVar11 = (void*)FUN_00edc9e0(I(m, 0), 0x2791ba0);
        if (piVar11) {
          piVar10 = (int*)VC0(void*, piVar11, 0x10);
          VC1(void, piVar10, 0xe8, (int)piVar11);
        }
      }
      goto L5a83;
    }
    if (umid < 9) {
      if (mid == 8) {
        if ((void*)I(self, 0x24) == (void*)I(m, 4)) {
          pfVar13 = (float*)VC0(void*, (void*)I(m, 4), 0x38);
          FUN_00806ca0((void*)I(m, 4), *pfVar13 + F(m, 0xc), pfVar13[1] + F(m, 0x10));
          iVar2 = -1;
          cVar3 = (char)FUN_00edd2d0(&puStack_560);
          if (cVar3 != 0) {
            uVar8 = FUN_00edcce0((void*)I(self, 0x28));
            cVar3 = (char)FUN_00eddf30(iVar6, I(self, 0x14), puStack_560, uVar8);
            iVar2 = (-(int)(cVar3 != 0) & 0xff01ff00) - 0x10000;
          }
          VC1(void, (void*)I(m, 4), 0x5c, iVar2);
          fVar7  = F(m, 0xc);
          fVar21 = F(m, 0x10);
          puVar23 = auStack_550;
          VC0(void, (void*)I(m, 4), 0xc0);
          pfVar13 = afStack_54c;
          for (iVar2 = 7; iVar2 != 0; --iVar2) {
            *pfVar13++ = *(float*)m;
            m += 4;
          }
          puStack_540 = puStack_55c;
          puStack_53c = puStack_558;
          piVar11 = (void*)SP_WindowManager();
          piVar10 = (int*)SP_WindowManager();
          iVar2 = *piVar10;
          uVar8 = VC5F(int, piVar11, 4, (int)afStack_54c, 0, (int)puVar23, fVar7, fVar21);
          uVar9 = VC2(unsigned, (void*)iVar2, 0x10, 0, uVar8);
          (void)uVar9;
          return 0;
        }
      } else if (mid == 6) {
        piVar11 = (void*)I(m, 4);
        iVar2 = VC0(int, piVar11, 0x1c);
        if (iVar2 == R_742C8F8 && I(self, 0x24) == 0) {
          uVar8 = FUN_00edcce0(piVar11);
          piVar10 = (int*)FUN_00edf070(uVar8);
          fVar7 = 0.0f;
          if (piVar10) {
            piVar11 = (void*)VC2(int, piVar10, 0xf0, R_742C8D0, 1);
            fVar7 = (float)FUN_00e12f80(piVar11, 1);
          }
        }
        if (piVar11 != 0 &&
            (iVar2 = VC0(int, piVar11, 0x1c)) == R_742C8D0 &&
            I(self, 0x24) == 0) {
          EA_AutoRefCount_assign(self + 0x24, (int)piVar11);
          uVar8 = VC0(int, piVar11, 0x38);
          EA_RectT_assign(self + 0x2c, uVar8);
          uVar8 = VC0(int, piVar11, 0x10);
          EA_AutoRefCount_assign(self + 0x28, uVar8);
          VC3(void, piVar11, 0xc0, (int)&puStack_560, I(self, 0x2c), I(self, 0x30));
          VC0(void, (void*)I(self, 0x28), 0xdc);
          piVar10 = (int*)EA_operator_new(0x5b598fa);
          piVar10 = (int*)cSPUILayoutManager_GetWorldMainWindow((int)piVar10);
          VC1(void, piVar10, 0xd8, (int)piVar11);
          VC2F(void, piVar11, 0x70, F(self, 0x2c), F(self, 0x30));
          piVar10 = (int*)SP_WindowManager();
          VC2(void, piVar10, 0x58, 1, (int)piVar11);
          VC1(void, (void*)I(self, 0x28), 0x78, 0x747d67c);
          FUN_00435e90();
          SP_KillSetiEffects();
          FUN_00ed4b50(0);
          FUN_00ef7a80();
          return 0;
        }
      } else { // mid == 7
        fVar7 = (float)(mid - 7);
        if (fVar7 == 0.0f && I(self, 0x24) == I(m, 4)) {
          puStack_560 = (void*)(self - 0xc);
          FUN_00edf410();
          cVar3 = (char)FUN_00edd2d0(&puStack_560);
          if (cVar3 != 0) {
            uVar8 = FUN_00edcce0((void*)I(m, 4));
            FUN_00ee0eb0(iVar5, iVar6, I(self, 0x14), puStack_560, uVar8);
            if (I(iVar6, 0x4b8) == 5 && puStack_560 == (void*)0xfffffffe)
              FUN_00efbbe0(0x4f, 0x50);
          }
          FUN_00ee16f0();
          return 0;
        }
      }
      return 0;
    }
    if (mid == 0x1c) {   // 3.92364e-44
      if (F(m, 0xc) == 0.0f) {
        piVar11 = (void*)I(m, 0x18);
        iVar2 = VC0(int, piVar11, 0x1c);
        if (iVar2 == R_7957BA8) {
          puStack_560 = (void*)&DAT_01667bac;
          puStack_55c = (void*)&DAT_01667bac;
          puStack_558 = (void*)&DAT_01667bae;
          FUN_00f28b80(&puStack_560);
          uVar8 = VC0(int, piVar11, 0x3c);
          cVar3 = (char)FUN_00f293b0(uVar8);   // hashtable DoFindNode
          if (cVar3 == 0) {
            FUN_00f45970();
            uVar8 = VC0(int, piVar11, 0x3c);
            FUN_00f293b0(uVar8);
            piVar11 = (void*)SP_MessageServer();
            VC2(void, piVar11, 0x14, 0x795b639, I(self, 0x14));
            FUN_00f45a80();
            FUN_00ee16f0();
          }
          fVar7 = (float)SP_QualifyNameWithGroup();
        }
        if (I(self, 0x18) != 0) {
          piVar11 = (void*)SP_WindowManager();
          uVar8 = VC1(int, piVar11, 0x48, 0);
          fVar7 = (float)FUN_00edc9e0(uVar8, 0x742be58);
          if (fVar7 == 0.0f) {
            FUN_00edf240();
            return 0;
          }
        }
      }
      return 0;
    }
    if (mid != MSG_4CAB02D) return 0;
    if (I(m, 0xc) == SUB_6849100) {
      iVar2 = (int)(float)FUN_00edce00(I(m, 0));
      fVar21 = F(m, 0x10);
      cVar3 = (char)iVar2;
      if (cVar3 == 0) fVar16 = F(iVar5, 0x24);
      else            fVar16 = F(iVar5, 0x48);
      if (fVar21 == fVar16) return 0;
      if (fVar21 == 2.8026e-45f) {
        if (cVar3 == 0) iVar6 = I(iVar5, 0x28);
        else            iVar6 = I(iVar5, 0x50);
        if (iVar6 == 0) { FUN_00edfcc0(); goto L5a83; }
      }
      FUN_00f45970();
      if (cVar3 == 0) {
        cVar3 = (char)FUN_00f27670();
        if (cVar3 != 0 || (cVar3 = (char)FUN_00f253e0()) != 0) {
          if ((fVar16 == 2.0f || fVar16 == 1.0f) && fVar21 == 0.0f && I(iVar5, 0x48) == 1)
            I(iVar5, 0x48) = 0;
          if (fVar16 == 0.0f && fVar21 == 1.0f && I(iVar5, 0x48) == 0)
            I(iVar5, 0x48) = 1;
        }
        F(iVar5, 0x24) = fVar21;
        FUN_00ed39a0(I(self, 0x14));
        VC1(void, (void*)I(self, 8), 0x1c, I(self, 0x14));
      } else {
        F(iVar5, 0x48) = fVar21;
        FUN_00ee16f0();
      }
      FUN_00f41a10(I(self, 0x14));
      FUN_00f45a80();
    }
L5a83:
    FUN_00435e90();
    goto L5a8e;
  }

  if (umid > MSG_287259F6) {
    if (mid != ID_6F00A884 || I(m, 0xc) != SUB_6849100) return 0;
    iVar2 = FUN_008050f0(I(m, 0));
    if ((unsigned)iVar2 < R_7C8A7D1) {
      if (iVar2 == R_7C8A7D0) {
        uVar8 = 0;
        piVar11 = (void*)FUN_005ff6a0(I(m, 0));
        if (piVar11) uVar8 = VC0(int, piVar11, 0x20);
        pfVar13 = (float*)(iVar6 + 0x494);
        FUN_00edfa30(uVar8, pfVar13, &cStack_561, &uStack_54d, 0x7cc8a44);
        uVar20 = (int)(*pfVar13 * 100.0f);
        FUN_00881f00((double)uVar20, auStack_520, 0x20, 0);
        fVar7 = *pfVar13;
        uVar8 = 0x7cc8a44; uVar22 = 0x7c8a7d0;
        goto L64f0;
      }
      if (iVar2 == R_7918320) {
        piVar11 = (void*)FUN_005ff6a0(I(m, 0));
        puVar14 = piVar11 ? (void*)VC0(int, piVar11, 0x20) : (void*)0;
        u8* pbVar1 = (u8*)(iVar6 + 1);
        puStack_560 = (void*)(iVar6 + 2);
        FUN_00edfa30(puVar14, (void*)(iVar6 + 0x48c), (void*)(iVar6 + 2), pbVar1, 0xf69d44ec);
        fVar7 = (float)FUN_00eeebd0();
        afStack_54c[0] = fVar7;
        SP_KillSetiEffects();          // EA::Locale::SetNumberString
        uVar9 = *pbVar1;
        puVar23 = auStack_520;
        uVar22 = 0xf69d44ec;
        uVar8 = FUN_00edf070(0x7918320);
        FUN_00edf830(uVar8, (unsigned)uVar9, (int)puStack_560);
        FUN_00ee1200(I(self, 0x14), *pbVar1);
        return 0;
      }
      if (iVar2 != R_792BF78) {
        if (iVar2 != R_7C8A7A8) return 0;
        piVar11 = (void*)FUN_005ff6a0(I(m, 0));
        puVar14 = piVar11 ? (void*)VC0(int, piVar11, 0x20) : (void*)0;
        iVar2 = I(iVar5, 4);
        uVar8 = 0;
        if (iVar2 == 0x24682294) uVar8 = 0x7cc8a4b;
        else if (iVar2 == 0x2b978c46) uVar8 = 0x7cc8a48;
        else if (iVar2 == 0x476a98c7) uVar8 = 0x7cc8a4b;
        pfVar13 = (float*)(iVar6 + 0x490);
        FUN_00edfa30(puVar14, pfVar13, &uStack_54d, &cStack_561, uVar8);
        iVar5 = I(iVar5, 4);
        if (iVar5 == 0x24682294 || iVar5 == 0x476a98c7) {
          uVar20 = (int)(*pfVar13 * 100.0f);
          FUN_00881f00((double)uVar20, auStack_520, 0x20, 0);
        } else if (iVar5 == 0x2b978c46) {
          FUN_00edfcc0();
        }
        fVar7 = *pfVar13;
        uVar22 = 0x7c8a7a8;
        goto L64f0;
      }
      fVar7 = FUN_00edcfc0(I(m, 0));
      afStack_54c[0] = fVar7;
      bVar15 = F(iVar6, 0x484) != fVar7 * 175.0f;
      F(iVar6, 0x484) = fVar7 * 175.0f;
      if (fVar7 == 1.0f) FUN_00efbbe0(0x52, 0x53);
    } else if (iVar2 == R_8918320) {
      fVar7 = FUN_00edcfc0(I(m, 0)) * 2000.0f;
      fVar16 = F(iVar6, 0x49c);
      bVar15 = fVar16 != fVar7;
      F(iVar6, 0x49c) = fVar7;
    } else if (iVar2 == R_892BF78) {
      fVar7 = FUN_00edcfc0(I(m, 0)) * 50.0f;
      fVar16 = F(iVar6, 0x498);
      bVar15 = fVar16 != fVar7;
      F(iVar6, 0x498) = fVar7;
    } else {
      if (iVar2 != R_9918320) return 0;
      fVar7 = FUN_00edcfc0(I(m, 0)) * 49.0f + 1.0f;
      fVar16 = F(iVar6, 0x4a0);
      bVar15 = fVar16 != fVar7;
      F(iVar6, 0x4a0) = fVar7;
    }
    if (!bVar15) return 0;
    goto L6802;
  }

  if (mid != 0x0742bde0) {                 // 1.3453206e-14
    if (mid == R_7A44749) {
      if (I(m, 0xc) == R_742CD10) {
        iVar2 = FUN_008050f0(I(m, 0));
        if ((unsigned)iVar2 < R_7C8A7D1) {
          if (iVar2 == R_7C8A7D0)      FUN_00ede9f0(iVar5, iVar6, I(self, 0x20));
          else if (iVar2 == R_7918320) { FUN_00ede2b0(iVar5, iVar6, I(self, 0x20)); goto L5c44; }
          else if (iVar2 == R_792BF78) { FUN_00ede400(iVar5, iVar6, I(self, 0x20)); goto L5c16; }
          else if (iVar2 == R_7C8A7A8) FUN_00ede8c0(iVar5, iVar6, I(self, 0x20));
          else return 0;
        } else {
          if (iVar2 == R_8918320)      FUN_00ede660(iVar5, iVar6, I(self, 0x20));
          else if (iVar2 == R_892BF78) { FUN_00ede790(iVar5, iVar6, I(self, 0x20)); goto L5c44; }
          else if (iVar2 == R_9918320) { FUN_00ede530(iVar5, iVar6, I(self, 0x20)); goto L5c16; }
          else return 0;
        }
        FUN_00f427c0();
        return 0;
      }
    } else if (mid == R_7A4489C && I(m, 0xc) == R_742CD10) {
      iVar2 = FUN_008050f0(I(m, 0));
      if ((unsigned)iVar2 < R_7C8A7D1) {
        if (iVar2 == R_7C8A7D0)      uVar8 = I(iVar6, 0x494);
        else if (iVar2 == R_7918320) { uVar8 = I(iVar6, 0x48c); goto L5b3c; }
        else if (iVar2 == R_792BF78) { uVar8 = I(iVar6, 0x484); goto L5b17; }
        else if (iVar2 == R_7C8A7A8) uVar8 = I(iVar6, 0x490);
        else return 0;
      } else {
        if (iVar2 == R_8918320)      { uVar8 = I(iVar6, 0x498); goto L5b3c; }
        else if (iVar2 == R_892BF78) { uVar8 = I(iVar6, 0x4a0); goto L5b17; }
        else if (iVar2 == R_9918320) uVar8 = I(iVar6, 0x49c);
        else return 0;
      }
      I(self, 0x20) = uVar8;
      FUN_00f45970();
      return 0;
    }
    return 0;
  }

  // ---- mid == 0x0742bde0 -------------------------------------------------------------
  {
  int sub = I(m, 0xc);
  if ((int)sub < 0x0742bde1) {
    if (sub == R_742BDE0) {
      cVar3 = (char)FUN_00edcf30(I(m, 0));
      puStack_560 = (void*)(int)cVar3;
      puVar14 = puStack_560;
      cVar3 = (char)FUN_00ee01e0();
      if (cVar3 != 0) {
        FUN_00ee16f0();
        FUN_00ee1140(I(self, 0x14), (int)puVar14);
        FUN_00f40370();
      }
      FUN_00f427c0();
      FUN_00435e90();
      goto L5a8e;
    }
    if ((int)sub < 0x0742bd99) {
      if (sub == 0x0742bd98) goto L5e72;
      if (sub == 0x03791004) { FUN_00edce00(I(m, 0), I(self, 0xc)); FUN_00edfcc0(); return 0; }
      if (sub == 0x03791005) {
        uVar8 = FUN_00435e90();
        uVar22 = 0x13bed0aa;
        SP_KillSetiEffects();
        fVar7 = (float)FUN_00eef810(afStack_54c, 0xb10e526f, I(self, 0x14), iVar5, uVar22, uVar8);
        if (afStack_54c[0] != 0.0f) {
          FUN_00f45970();
          puStack_560 = (void*)I(self, 0xc);
          uVar8 = I(self, 8);
          FUN_00edf2c0((int)puStack_560, 0);
          FUN_008085d0((int)puStack_560, (int)FUN_00edf370, 2, 0, uVar8);
          cVar3 = (char)FUN_00edce00(I(m, 0));
          if (cVar3 == 0) {
            F(iVar5, 0x28) = afStack_54c[0];
            F(iVar5, 0x2c) = afStack_54c[1];
            F(iVar5, 0x30) = afStack_54c[2];
            FUN_00ed39a0(I(self, 0x14));
            VC1(void, (void*)I(self, 8), 0x1c, I(self, 0x14));
          } else {
            F(iVar5, 0x50) = afStack_54c[0];
            F(iVar5, 0x54) = afStack_54c[1];
            F(iVar5, 0x58) = afStack_54c[2];
            FUN_00ee16f0();
          }
          FUN_00f41a10(I(self, 0x14));
          FUN_00f45a80();
          return 0;
        }
        return 0;
      }
      if (sub == 0x0595e0a8) { FUN_00ee30d0(); FUN_00435e90(); goto L5a8e; }
    } else if (sub == 0x0742bdb0 || sub == 0x0742bdc0 ||
               sub == 0x0742bdd0 /* || sub == 0x0742bde0 already handled */) {
      goto L5e72;
    }
  } else {
    if ((int)sub < 0x07ec82c1) {
      if (sub == R_7EC82C0) {
        iVar5 = FUN_00f3e8a0(I(self, 0x14));
        iVar6 = FUN_00efc520();
        FUN_00dfd080(iVar6 * 0x4e0 + I(iVar5, 0x70));
        if (iStack_3c == -1) { FUN_00435e90(); SP_KillSetiEffects(); uVar22 = FUN_00efc520(10); }
        else                 { FUN_00435e90(); SP_KillSetiEffects(); uVar22 = FUN_00efc520(0xffffffff); }
        FUN_00ee0960(I(self, 0x14), uVar22);
        FUN_00ee16f0();
        FUN_00dfbba0();
        return 0;
      }
      if (sub == R_74656A0) {
        FUN_00ecb730();
        uVar8 = FUN_00f3e8a0(I(self, 0x14));
        FUN_00f0bdf0(uVar8, 2);
      } else {
        if (sub != R_791A7C8 && sub != 0x0791a7c0) goto L6102;
        I(self, 0x1c) = I(self, 0x1c) + (int)(sub == R_791A7C8) * 2 - 1;
        FUN_00435e90();
        SP_KillSetiEffects();
      }
L6802:
      FUN_00ee16f0();
      return 0;
    }
    if (sub > ID_76A93C50 + 0xffffffff /* > 0x76a93c4f */) {
      if (sub < ID_76A93C51 + 1 /* < 0x76a93c52 */) {
        puStack_560 = (void*)(int)I(iVar5, 0x74);
        if (I(iVar5, 0x14) != 0 && puStack_560 != 0) {
          iVar2 = FUN_006c0200();
          if (iVar2 != 0) {
            iVar5 = FUN_00efc520();
            iVar6 = FUN_00f3be30();
            FUN_00efc8c0((int)((unsigned)(I(m, 0xc) == ID_76A93C51) * 2 - 1 + iVar5) % iVar6);
            FUN_00ee31d0();
            FUN_00ee16f0();
            FUN_00435e90();
            goto L5a8e;
          }
        }
        return 0;
      }
      if (sub == ID_76A93C53) {
        cStack_561 = B(iVar5, 0x20) == 0;
        FUN_00edfd30(iVar5 + 0x20, &cStack_561);
        FUN_00435e90();
        SP_KillSetiEffects();
        return 0;
      }
    }
  }
  }

L6102:
  if ((int)mid < 0x0742cbe0 || (int)mid > 0x0742cbe5) return 0;
  cStack_561 = 0;
  FUN_00edf240();
  piVar11 = (void*)VC0(int, (void*)I(m, 0), 0x10);
  piVar11 = (void*)VC0(int, piVar11, 0x10);
  uVar8 = VC0(int, piVar11, 0x1c);
  switch (uVar8) {
    case ID_742BD88: {
      int sel = I(m, 0xc) - 0x0742cbe0;
      if (I(m, 0x18) == 2) {
        if (sel != 5) {
          cVar3 = (char)FUN_00f25670();
          if (cVar3 != 0) {
            FUN_00f0bea0();
            uVar8 = FUN_00f3e8a0(I(self, 0x14));
            FUN_00ecb520(uVar8, 1);
            FUN_00ee16f0();
            break;
          }
          goto L61b2;
        }
L61b9:
        cVar3 = (char)FUN_00f25670();
        if (cVar3 == 0) goto L61e8;
        FUN_00f0bea0();
        uVar8 = FUN_00f3e8a0(I(self, 0x14));
        FUN_00ecb520(uVar8, 0);
      } else {
L61b2:
        if (sel == 5) goto L61b9;
L61e8:
        FUN_00ecb730();
      }
      cVar3 = (char)FUN_00ede110(iVar5, iVar6, sel);
      cStack_561 = cVar3;
      FUN_00ee16f0();
      if (cVar3 != 0)
        FUN_00ed8950(I(self, 0x14), DAT_0148a488[I(iVar6, 0x4ac)]);
      FUN_00f427c0();
      if (I(iVar6, 0x4ac) == 5) { uVar8 = 0x49; uVar22 = 0x4a; goto L639a; }
      break;
    }
    case ID_742BD98:
      cStack_561 = (char)FUN_00ee0310(iVar5, iVar6, I(m, 0xc) - 0x0742cbe0);
      if (cStack_561 != 0) FUN_00f427c0();
      break;
    case ID_742BDB0:
      cStack_561 = (char)FUN_00ee0450(iVar5, iVar6, I(m, 0xc) - 0x0742cbe0);
      if (cStack_561 != 0) {
        FUN_00f427c0();
        FUN_00ed8950(I(self, 0x14), DAT_0148a4a0[I(iVar6, 0x4b0)]);
      }
      break;
    case ID_742BDC0:
      cStack_561 = (char)FUN_00ee0590(iVar5, iVar6, I(m, 0xc) - 0x0742cbe0);
      if (cStack_561 != 0) {
        FUN_00f427c0();
        FUN_00ed8950(I(self, 0x14), DAT_0148a4b0[I(iVar6, 0x4b4)]);
      }
      break;
    case ID_742BDD0:
      cStack_561 = (char)FUN_00ee06d0();
      if (cStack_561 != 0) {
        FUN_00ed8950(I(self, 0x14), DAT_0148a4c0[I(iVar6, 0x4b8)]);
        FUN_00f427c0();
      }
      if (I(iVar6, 0x4b8) == 5)      { uVar8 = 0x4c; uVar22 = 0x4d; }
      else if (I(iVar6, 0x4b8) == 4) { uVar8 = 0x5f; uVar22 = 0x60; }
      else break;
L639a:
      FUN_00efbbe0(uVar8, uVar22);
      break;
  }
  FUN_00435e90();
  SP_KillSetiEffects();
  if (cStack_561 != 0) { FUN_00ee16f0(); return 0; }
  return 0;

L5a8e:
  SP_KillSetiEffects();
  (void)uVar9;
  return 0;

L5b17:
  I(self, 0x20) = uVar8;
  FUN_00f45970();
  return 0;

L5b3c:
  I(self, 0x20) = uVar8;
  FUN_00f45970();
  return 0;

L5c16:
  FUN_00f427c0();
  return 0;

L5c44:
  FUN_00f427c0();
  return 0;

L5e72:
  cVar3 = (char)FUN_00edcf30(I(m, 0));
  if (cVar3 == 0) { FUN_00edf240(); FUN_00435e90(); }
  else            { FUN_00edf090(I(m, 0xc)); FUN_00435e90(); }
  SP_KillSetiEffects();
  return 0;

L64f0:
  uVar20 = 0;
  uVar22 = FUN_00edf070(uVar22);
  FUN_00edf830(uVar22, (unsigned)(int)fVar7, uVar20, uVar8);
  return 0;
}
