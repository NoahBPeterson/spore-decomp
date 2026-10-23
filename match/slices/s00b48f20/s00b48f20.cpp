// s00b48f20.cpp — SporeApp steering-function region (cLocomotiveObject steering
// callbacks + the steer-vector emitter they share).
// Reconstructed from Ghidra decompiles + disassembly.

#include <stddef.h>
#include <math.h>

inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }

// ---- globals ---------------------------------------------------------------
extern "C" float DAT_0167eb8c;   // 0x167eb8c  invalid-vector sentinel x
extern "C" float DAT_0167eb90;   // 0x167eb90  invalid-vector sentinel y
extern "C" float DAT_0167eb94;   // 0x167eb94  invalid-vector sentinel z

// ---- callees ---------------------------------------------------------------
extern "C" int   FUN_00c41ec0();   // 0xc41ec0  __fastcall(this) -> this+0x1f4
extern "C" void  FUN_00b48e00();   // 0xb48e00  __fastcall(this) SteerVec::push_back
extern "C" void* FUN_00d20610();   // 0xd20610  cLocomotiveObject::GetVelocity (fastcall)
extern "C" void* FUN_00436ce0(void*, void*);                  // 0x436ce0  Vector3_Normalize
extern "C" void  FUN_00699800(void*, void*, float, void*, void*); // 0x699800 SegmentPhysics
extern "C" void* FUN_00449c20(void*, void*);                  // 0x449c20  SP::normalized_safe
extern "C" int   FUN_00b3d310();   // 0xb3d310
extern "C" int   FUN_00c0c2f0();   // 0xc0c2f0  fastcall(this) -> this+0xeac
extern "C" int*  FUN_00b41a40();   // 0xb41a40  (thiscall, 2 args)
extern "C" int   FUN_00c03520();   // 0xc03520  (thiscall, 1 arg, ret 4)
extern "C" int   FUN_00c02600();   // 0xc02600  SP::IsValidNeighbourEntry (thiscall, 1 arg, ret 4)
extern "C" void  FUN_00b3d870();   // 0xb3d870  __fastcall(this) -> *this += 4
extern "C" int*  FUN_00c420d0();   // 0xc420d0  __fastcall(this) -> this+0x278
extern "C" void* FUN_00b5b800();   // 0xb5b800  SP::GetCurrentGameMode
extern "C" int   FUN_00bc96a0();   // 0xbc96a0  PlayIdleAnimation (thiscall, 2 args)
extern "C" int   FUN_00d99980(int); // 0xd99980 SP::GetAnimalFromStimulus
extern "C" void* FUN_00b3d350();   // 0xb3d350  SP::PlanetModel
extern "C" float FUN_00b7e430();   // 0xb7e430  (thiscall, 2 args) -> float
extern "C" void  FUN_00b7ee70();   // 0xb7ee70  (thiscall, 2 args)
extern "C" void  FUN_00b47600();   // 0xb47600  SteerVec::DoInsertValue (thiscall, 2 args)

// ===========================================================================
// @ 0x00b48f20
void FUN_00b48f20(float* param_1, float param_2, float* param_3, float param_4)
{
  float* pfVar1 = param_3;
  float local_30 = param_3[0] - param_1[0];
  float fVar5 = param_2 + param_4;
  float local_2c = param_3[1] - param_1[1];
  float local_28 = param_3[2] - param_1[2];
  float fVar6 = sqrtf(local_28 * local_28 + (local_2c * local_2c + local_30 * local_30));

  float t2 = fVar5 + 2.0f;
  float t1 = fVar5 * 1.5f;
  float maxd = (t1 <= t2) ? t1 : t2;

  float param_4b = ((float (__thiscall*)(void*))VFn(*(void**)((char*)param_1 + 0x80), 0xc8))(*(void**)((char*)param_1 + 0x80));

  if (fVar6 < maxd) {
    float inv = 1.0f / fVar6;
    float fStack_24 = inv * local_30;
    float fStack_20 = local_2c * inv;
    float fStack_1c = local_28 * inv;

    int iVar2 = ((int (__fastcall*)(void*))FUN_00c41ec0)(*(void**)((char*)param_1 + 0x80));
    if (*(int*)((char*)iVar2 + 0x5c) != 0) {
      float dx = pfVar1[0] - *(float*)((char*)iVar2 + 0x14);
      float dz = pfVar1[2] - *(float*)((char*)iVar2 + 0x1c);
      float dy = pfVar1[1] - *(float*)((char*)iVar2 + 0x18);
      if ((dx * dx + dz * dz + dy * dy) < fVar5 * fVar5) {
        float ax = param_1[0] - *(float*)((char*)iVar2 + 0x14);
        float az = param_1[2] - *(float*)((char*)iVar2 + 0x1c);
        float ay = param_1[1] - *(float*)((char*)iVar2 + 0x18);
        if ((ax * ax + az * az + ay * ay) < fVar6 * fVar6) return;
      }
      ((void (__fastcall*)(void*))FUN_00b48e00)((char*)param_1 + 0x84);
      float* e = (float*)(*(int*)((char*)param_1 + 0x88) - 0x2c);
      e[5] = 0.3f;
      *(int*)e = 1;
      e[2] = pfVar1[0];
      e[3] = pfVar1[1];
      e[4] = pfVar1[2];
      e[6] = fVar5;
      e[7] = maxd;
    }

    float* vel = (float*)((void* (__fastcall*)(void*))FUN_00d20610)(*(void**)((char*)param_1 + 0x80));
    float fStack_3c = vel[0];
    float fStack_38 = vel[1];
    float fStack_34 = vel[2];

    if (sqrtf(fStack_38 * fStack_38 + (fStack_34 * fStack_34 + fStack_3c * fStack_3c)) < param_4b
        && *(int*)((char*)iVar2 + 0x5c) != 0) {
      fStack_3c = *(float*)((char*)iVar2 + 0x14) - param_1[0];
      fStack_38 = *(float*)((char*)iVar2 + 0x18) - param_1[1];
      fStack_34 = *(float*)((char*)iVar2 + 0x1c) - param_1[2];
      if (fStack_3c == DAT_0167eb8c && fStack_38 == DAT_0167eb90 && fStack_34 == DAT_0167eb94)
        return;
      float fStack_18[3];
      float* n = (float*)FUN_00436ce0(fStack_18, &fStack_3c);
      fStack_3c = n[0];
      fStack_38 = n[1];
      fStack_34 = n[2];
      if (1.0f < param_4b) {
        fStack_3c = fStack_3c * param_4b;
        fStack_38 = fStack_38 * param_4b;
        fStack_34 = fStack_34 * param_4b;
      }
    }

    float dot = (fStack_38 * local_2c + fStack_3c * local_30) + fStack_34 * local_28;
    if (0.0f < dot) {
      local_30 = param_1[0];
      local_2c = param_1[1];
      local_28 = param_1[2];
      if (fVar6 < fVar5 && 1.5258789e-05f < fVar6) {
        float k = (fVar5 - fVar6) + 0.1f;
        local_30 = local_30 - fStack_24 * k;
        local_2c = local_2c - fStack_20 * k;
        local_28 = local_28 - fStack_1c * k;
      }
      float fStack_18[3];
      FUN_00699800(fStack_18, pfVar1, fVar5, &local_30, &fStack_3c);
      if (fStack_18[0] != DAT_0167eb8c || fStack_18[1] != DAT_0167eb90 || fStack_18[2] != DAT_0167eb94) {
        fStack_24 = fStack_18[0] - local_30;
        fStack_20 = fStack_18[1] - local_2c;
        fStack_1c = fStack_18[2] - local_28;
        float auStack_c[3];
        float* n2 = (float*)FUN_00449c20(auStack_c, &fStack_24);
        fStack_24 = dot * n2[0];
        fStack_20 = n2[1] * dot;
        fStack_1c = n2[2] * dot;
        ((void (__fastcall*)(void*))FUN_00b48e00)((char*)param_1 + 0x84);
        float* e = (float*)(*(int*)((char*)param_1 + 0x88) - 0x2c);
        *(int*)e = 2;
        e[2] = fStack_24;
        e[3] = fStack_20;
        e[4] = fStack_1c;
      }
    }
  }
}

// ===========================================================================
// @ 0x00b493e0
void FUN_00b493e0(void* param_1)
{
  int* edi;
  if (*(void**)((char*)param_1 + 0x80) == 0) {
    edi = 0;
  } else {
    void* o = *(void**)((char*)param_1 + 0x80);
    edi = (int*)((int (__thiscall*)(void*, int))VFn(o, 0xb8))(o, 0xce9f6639);
    if (edi != 0) {
      if (*(char*)((char*)edi + 0xf90) == 0) return;
      int i = ((int (__fastcall*)(void*))FUN_00c0c2f0)(edi);
      if (i < 2) return;
    }
  }

  void* o2 = *(void**)((char*)param_1 + 0x80);
  float* vel = (float*)((void* (__fastcall*)(void*))FUN_00d20610)(o2);
  if (vel[0] == DAT_0167eb8c && vel[1] == DAT_0167eb90 && vel[2] == DAT_0167eb94)
    return;

  {
    void* o3 = *(void**)((char*)param_1 + 0x80);
    float fStack_2c = ((float (__thiscall*)(void*))VFn(o3, 0x74))(o3);
    float auStack_c[3];
    ((void (__thiscall*)(void*, void*))VFn(o3, 0x5c))(o3, auStack_c);

    int* p3 = edi;
    if (p3 == 0 || ((void* (__thiscall*)(void*))VFn(p3, 0x20))(p3) != (void*)0x18eb45e) {
      // 0xb496b9 : walk the c420d0 list
      void* o4 = *(void**)((char*)param_1 + 0x80);
      int* pit = ((int* (__fastcall*)(void*))FUN_00c420d0)(o4);
      int* it = (int*)pit[0];
      int* end = (int*)pit[1];
      while (it != end) {
        int* e = (int*)*it;
        if (*(char*)((char*)e + 0x70) != 0
            && *(char*)((char*)e + 0x75) != 0
            && (*(unsigned char*)((char*)e + 0x50) & 0x10) == 0) {
          float v74 = ((float (__thiscall*)(void*))VFn(e, 0x74))(e);
          void* u = ((void* (__thiscall*)(void*))VFn(e, 0x2c))(e);
          FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74);
        }
        ++it;
      }
      return;
    }

    int x = FUN_00b3d310();
    if (*(int*)((char*)x + 0x20) == 0) {
      // 0xb49569 : idle-animation driven target
      if (((*(unsigned int*)((char*)p3 + 0xb58) >> 8) & 1) == 0
          && FUN_00b5b800() == (void*)0x1654c01) {
        int r = ((int (__thiscall*)(void*, int, int))FUN_00bc96a0)(
            (void*)(*(int*)((char*)p3 + 0xb4c) + 8), 0x4000000, 0);
        if (r != 0) {
          int a = FUN_00d99980(r);
          if (a != 0) {
            void* esi2 = (void*)(a + 0xc0);
            float v74 = ((float (__thiscall*)(void*))VFn(esi2, 0x74))(esi2);
            void* u = ((void* (__thiscall*)(void*))VFn(esi2, 0x2c))(esi2);
            FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74 * 5.0f);
          }
        }
      }
    } else {
      // 0xb494bd : walk the neighbour vector at p3+0x1124
      int* vec[2];
      void* tmp;
      ((int* (__thiscall*)(void*, void*, void*))FUN_00b41a40)((void*)vec, (void*)((char*)p3 + 0x1124), &tmp);
      int* it = vec[0];
      int* end = vec[1];
      while (it != end) {
        int* e8 = *(int**)((char*)*it + 8);
        void* obj2 = e8 ? (void*)((char*)e8 + 0xc0) : 0;
        if (*(char*)((char*)obj2 + 0x70) != 0) {
          float v74 = ((float (__thiscall*)(void*))VFn(obj2, 0x74))(obj2);
          void* u = ((void* (__thiscall*)(void*))VFn(obj2, 0x2c))(obj2);
          FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74);
        }
        do {
          ++it;
          if (it == end) goto done;
        } while (((int (__thiscall*)(void*, void*))FUN_00c02600)(&it, (void*)*it) == 0);
      }
    }

  done:
    // 0xb495e4 : walk the second vector at p3+0x140c
    int* it2 = *(int**)((char*)p3 + 0x140c);
    int* end2 = *(int**)((char*)p3 + 0x1410);
    if (it2 == end2) return;
    if (((int (__thiscall*)(void*, void*))FUN_00c03520)(&it2, (void*)*it2) == 0) {
      ((void (__fastcall*)(void*))FUN_00b3d870)(&it2);
    }
    if (it2 == end2) return;
    do {
      int* e8 = *(int**)((char*)*it2 + 8);
      void* obj3 = e8 ? ((void* (__thiscall*)(void*, int))VFn(e8, 0xc))(e8, 0x1186577) : 0;
      if (*(char*)((char*)obj3 + 0x70) != 0) {
        float v74 = ((float (__thiscall*)(void*))VFn(obj3, 0x74))(obj3);
        void* u = ((void* (__thiscall*)(void*))VFn(obj3, 0x2c))(obj3);
        FUN_00b48f20((float*)param_1, fStack_2c, (float*)u, v74);
      }
      do {
        ++it2;
        if (it2 == end2) return;
      } while (((int (__thiscall*)(void*, void*))FUN_00c03520)(&it2, (void*)*it2) == 0);
    } while (it2 != end2);
    return;
  }
}

// ===========================================================================
// @ 0x00b49730
void FUN_00b49730(void* param_1)
{
  int* esi;
  if (*(void**)((char*)param_1 + 0x80) == 0) {
    esi = 0;
  } else {
    void* o = *(void**)((char*)param_1 + 0x80);
    esi = (int*)((int (__thiscall*)(void*, int))VFn(o, 0xb8))(o, 0xd0036e08);
    if (esi != 0) {
      if (*(int*)((char*)esi + 0x2b0) == 3) return;
      if (*(char*)((char*)esi + 0xf90) == 0) return;
    }
  }

  int* edi = (int*)FUN_00b3d350();
  float r = ((float (__thiscall*)(void*, void*, int))FUN_00b7e430)(edi, param_1, 0);
  if (r > -1.0f) {
    float fStack_38[3];
    ((void (__thiscall*)(void*, float*, void*))FUN_00b7ee70)(edi, fStack_38, param_1);

    float scale = 0.5f;
    if (((*(unsigned int*)((char*)esi + 0xb58) >> 9) & 1) != 0) {
      if (FUN_00b5b800() == (void*)0x1654c05) scale = 5.0f;
      else scale = 0.5f;
    }

    float a = (-1.0f - r) * -1.0f;
    float m = (1.0f <= a) ? 1.0f : a;
    float k = m * scale;

    float c0 = fStack_38[0] * k;
    float c1 = fStack_38[1] * k;
    float c2 = fStack_38[2] * k;

    unsigned end = *(unsigned*)((char*)param_1 + 0x88);
    if (end < *(unsigned*)((char*)param_1 + 0x8c)) {
      *(unsigned*)((char*)param_1 + 0x88) = end + 0x2c;
      if (end != 0) *(int*)(end + 4) = 1;
    } else {
      int val[0x2c / 4];
      val[1] = 1;
      ((void (__thiscall*)(void*, void*, void*))FUN_00b47600)((char*)param_1 + 0x84, (void*)end, val);
    }
    int* e = (int*)(*(int*)((char*)param_1 + 0x88) - 0x2c);
    *(int*)e = 2;
    *(float*)((char*)e + 8) = c0;
    *(float*)((char*)e + 0xc) = c1;
    *(float*)((char*)e + 0x10) = c2;
  }
}
