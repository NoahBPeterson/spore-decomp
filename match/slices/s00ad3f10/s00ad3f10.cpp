// Slice s00ad3f10 -- SPAppStateManager.obj (Simulator app-state "vignette context" family).
//   0x00AD3F10  the scalar-deleting destructor of the vignette-context resource object
//   0x00AD4550  the vignette/actor behaviour callback: rescans the placed-object list and
//               either tears the list down (param_2 == 0) or rebuilds it (param_2 != 0)
//   0x00AD4A10  GetActionInventory(): the nearest space-inventory object of the active sim
// Everything is named from usage (the ModAPI ids kGameCreature 0x1654C01, kGameTribe 0x1654C02,
// kScenarioMode 0x1654C10). Every callee/data name embeds its image address so the equivalence
// harness can resolve the relocations back to the original addresses.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned char byte;
typedef unsigned int  uint;

// ---------------------------------------------------------------------------------------------
// data symbols (only their addresses matter for byte-exactness; the relocations are masked)
extern char vtbl_0145a6e0[];      // 0x0145A6E0  cVignetteContext vtable (derived)
extern char vtbl_0145a6d0[];      // 0x0145A6D0  cVignetteContext secondary vtable
extern char vtbl_013ec458[];      // 0x013EC458  EA::RefCountBase vtable (base)
extern char vtbl_013eb938[];      // 0x013EB938  Editor::cEditorResource vtable (base)
extern char d_013f09b4[];         // 0x013F09B4  "Simulator"
extern char d_013ebb38[];         // 0x013EBB38  ".../EASTL/allocator.h"
extern char d_01654c10[];         // 0x01654C10  the "scenario mode" game-mode object
extern char d_018ebadc[];         // 0x018EBADC  action-inventory type descriptor
extern float f_0145a5c8;          // 0x0145A5C8  FLT_MAX

// ---------------------------------------------------------------------------------------------
// free functions (cdecl)
extern "C" void* FUN_00f473a0(int size, const char* tag, int a, int b, const char* file, int line); // 0x00F473A0 EAAllocate
extern "C" void  FUN_00f47380(void* p);                          // 0x00F47380 EAFree
extern "C" void  FUN_00ad2650(int id, void* dst);                // 0x00AD2650 GetNamedTarget
extern "C" int   FUN_00ad2710(void* p);                          // 0x00AD2710

struct Vector3;
extern "C" Vector3& FUN_00ad2ae0(Vector3& out, void* xf, int a, int b, int c, const Vector3& v); // 0x00AD2AE0 ComputePoint
extern "C" void  FUN_00cd7d10();                                 // 0x00CD7D10 callback
extern "C" void  FUN_00d3d420();                                 // 0x00D3D420 callback
extern "C" void  FUN_00ad48b0();                                 // 0x00AD48B0 callback
extern "C" void  FUN_00b1e500();                                 // 0x00B1E500 callback
extern "C" void* FUN_00b5b800();                                 // 0x00B5B800 GetCurrentGameMode()

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Quaternion { float x, y, z, w; };
extern Vector3 kInvalidPosition;                                 // 0x0167A4BC  (0,0,0)

// ---------------------------------------------------------------------------------------------
// 0x00AD3F10: the secondary "pool" sub-object at +0x10 that the destructor tears down.
struct Sub005687d0
{
    int m00;                                                     // +0x00
    int m04;                                                     // +0x04  payload pointer
    int m08;                                                     // +0x08  count
    int m0c;                                                     // +0x0C
    void m_005687d0(int a, int b);                               // 0x005687D0
};
struct cResObj
{
    void* mpVtbl0;                                               // +0x00
    int   m04;                                                   // +0x04
    void* mpVtbl1;                                               // +0x08
    int   m0c;                                                   // +0x0C
    Sub005687d0 mSub;                                            // +0x10
    void* ScalarDtor(uint flags);
};

// ---------------------------------------------------------------------------------------------
// the argument object of the behaviour callback (0x00AD4550): a vtable object whose slot +0xC
// casts to the sim object below.
struct cOuter
{
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* Cast(uint id);                                 // +0x0C
};

// a game object (only its +0xB8 cast slot is used)
#define V(n) virtual void v##n()
struct cGameObject
{
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28); V(2c);
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c); V(70); V(74); V(78); V(7c); V(80); V(84); V(88); V(8c);
    V(90); V(94); V(98); V(9c); V(a0); V(a4); V(a8); V(ac); V(b0); V(b4);
    virtual void* Cast(uint id);                                 // +0xB8
};
#undef V

// the 0x30-byte action target (ctor 0x00AD7940 / dtor 0x00AD7AD0)
struct cActionTarget
{
    Vector3 mPosition;                                           // +0x00
    uint pad_0c[(0x2C - 0x0C) / 4];
    cGameObject* mpObject;                                       // +0x2C
    void m_00ad7940();                                           // 0x00AD7940
    void m_00ad7ad0();                                           // 0x00AD7AD0
};

// the sim object the callback casts to (iVar4)
struct cSim
{
    char pad_00[0x0c];
    int  m0c;                                                    // +0x0C
    int* mpBegin;                                                // +0x10
    int* mpEnd;                                                  // +0x14
    char pad_18[0x30 - 0x18];
    int  mListHead;                                              // +0x30  (list sentinel next)
    int  mListTail;                                              // +0x34  (list sentinel prev)
    int* mpFree;                                                 // +0x38  (free node list)
    char pad_3c[0x40 - 0x3C];
    int* mpPoolLo;                                               // +0x40
    int* mpPoolHi;                                               // +0x44
    int  mAlloc;                                                 // +0x48  (allocator arena)
    char pad_4c[0x70 - 0x4C];
    char mFlag70;                                                // +0x70
    char pad_71[0x74 - 0x71];
    int  mA74;                                                   // +0x74
    int  mA78;                                                   // +0x78
    int  mA7c;                                                   // +0x7C
    int  mpObj80;                                                // +0x80
    char mFlag84;                                                // +0x84
};

// the sim object's node pool (the +0x30 sentinel sub-object)
struct cNodePool
{
    virtual void v00();
    void m_00a222c0();                                           // 0x00A222C0
};

// the object the callback casts to (ebp): a big thing with a +0xB48 sub-object
struct cB48
{
    char m_00bca810(int a, int b, void* c, float d, void* e, int f);   // 0x00BCA810
};
struct cTgt
{
    char pad_00[0xb48];
    int  mB48;                                                   // +0xB48
    char pad_b4c[0xb5e - 0xb4c];
    char mB5e;                                                   // +0xB5E
    char m_00c0e640(int a);                                      // 0x00C0E640
    char m_00c12400(int a);                                      // 0x00C12400
    int  m_00c14990(int a, void* b, int c);                      // 0x00C14990
    int  m_00c14910(int a, void* b, int c);                      // 0x00C14910
    int  m_00c12310(int a, int b, int c);                        // 0x00C12310
    int  m_00c12190(int a, int b, int c);                        // 0x00C12190
};

// the cinematic manager (0x00B3D4D0)
struct cCinMgr
{
    char pad_00[0x1a8];
    int  mField1a8;                                              // +0x1A8
    char m_00adb2a0(int id, cActionTarget* target);              // 0x00ADB2A0
    char m_00adb1b0(int id, void* p);                            // 0x00ADB1B0
};
extern "C" cCinMgr* FUN_00b3d4d0();                              // 0x00B3D4D0

// the noun manager (0x00B3D300)
struct cNounMgr
{
    void* m_00b21340(void* a, void* b, void* c, void* d, int e);    // 0x00B21340
};
extern "C" cNounMgr* FUN_00b3d300();                             // 0x00B3D300

// ---------------------------------------------------------------------------------------------
// 0x00AD4A10 helpers
struct Sub2c
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* m_2c();                               // +0x2C
};
struct SubList
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* m_2c();                               // +0x2C
};
struct cListObj
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int  m_4c();                                         // +0x4C
    char pad_04[0x30];
    SubList mSub;                                                // +0x34
};
struct ObjVec
{
    int m00;
    cListObj** mpBegin;                                          // +0x04
    cListObj** mpEnd;                                            // +0x08
};
struct cInv
{
    char pad_00[0x34];
    Sub2c mSub;                                                  // +0x34
};
struct cUFOSim
{
    cInv* m_00a1ad60();                                          // 0x00A1AD60 GetPlayerInventory
};
extern "C" cUFOSim* FUN_00ffbe50();                              // 0x00FFBE50 GetUFOSimulator

struct cRes9 { char pad_00[0x84]; int m84; };                    // +0x84
struct cMgr9
{
    cRes9* m_00c71e30();                                         // 0x00C71E30
};
extern "C" cMgr9* FUN_01021260();                                // 0x01021260

// ---------------------------------------------------------------------------------------------
// @ 0x00ad3f10
void* cResObj::ScalarDtor(uint flags)
{
    Sub005687d0* sub = &mSub;
    mpVtbl0 = (void*)vtbl_0145a6e0;
    mpVtbl1 = (void*)vtbl_0145a6d0;
    sub->m_005687d0(sub->m04, sub->m08);
    sub->m0c = 0;
    if (1 < (uint)sub->m08)
        FUN_00f47380((void*)sub->m04);
    mpVtbl1 = (void*)vtbl_013ec458;
    mpVtbl0 = (void*)vtbl_013eb938;
    if (flags & 1)
        FUN_00f47380(this);
    return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ad4550
bool FUN_00ad4550(int* param_1, char param_2)
{
    bool bVar12 = true;
    if (param_1 != 0) {
        cSim* s = (cSim*)((cOuter*)param_1)->Cast(0x448444b);
        if (s != 0) {
            cActionTarget target;
            target.m_00ad7940();
            if (FUN_00b3d4d0()->m_00adb2a0(s->m0c, &target) == 0) {
                target.m_00ad7ad0();
                return true;
            }

            cGameObject* pObject = target.mpObject;
            cTgt* tgt;
            if (pObject == 0 || (tgt = (cTgt*)pObject->Cast(0xce9f6639)) == 0) {
                target.m_00ad7ad0();
                return true;
            }

            Vector3 vecPos = kInvalidPosition;
            if (s->mA78 != 0) {
                Vector3 tmp;
                vecPos = FUN_00ad2ae0(tmp, &target, s->mA74, s->mA78, s->mA7c, kInvalidPosition);
            }

            if (param_2 == 0) {
                int* head = (int*)((char*)s + 0x30);
                while (head[0] != (int)head) {
                    int* node = (int*)head[0];
                    if (tgt->m_00c12400(node[2]) == 0) {
                        bVar12 = (s->mFlag70 != 0);
                        break;
                    }
                    node = (int*)head[0];
                    *(int*)node[1] = node[0];
                    *(int*)(node[0] + 4) = node[1];
                    if ((uint)node < (uint)s->mpPoolLo || (uint)s->mpPoolHi <= (uint)node) {
                        FUN_00f47380(node);
                    } else {
                        node[0] = (int)s->mpFree;
                        s->mpFree = node;
                    }
                }
            } else {
                int iVar11 = s->mpObj80;
                cCinMgr* mgr = FUN_00b3d4d0();
                if (mgr->mField1a8 != 0)
                    iVar11 = mgr->mField1a8;
                if (iVar11 != 0)
                    tgt->m_00c0e640(iVar11);

                int* head = (int*)((char*)s + 0x30);
                ((cNodePool*)head)->m_00a222c0();
                head[0] = (int)head;
                head[1] = (int)head;

                void* mode = FUN_00b5b800();
                if (mode != (void*)d_01654c10 || tgt->mB5e == 0) {
                    int count = (int)(s->mpEnd - s->mpBegin) >> 2;
                    uint i = 0;
                    if (count != 0) {
                        do {
                            int obj = s->mpBegin[i];
                            int r;
                            if (s->mA78 == 0) {
                                if (i == 0)
                                    r = tgt->m_00c12310(obj, -1, 0);
                                else
                                    r = tgt->m_00c12190(obj, 0, -1);
                            } else if (i == 0) {
                                r = tgt->m_00c14990(obj, &vecPos, -1);
                            } else {
                                r = tgt->m_00c14910(obj, &vecPos, -1);
                            }

                            if (s->mFlag84 != 0 && i == 0 && s->mA78 != 0) {
                                int iStack_a4 = 0;
                                cActionTarget target2;
                                target2.m_00ad7940();
                                if (FUN_00b3d4d0()->m_00adb1b0(s->mA78, &iStack_a4) == 0)
                                    FUN_00ad2650(s->mA78, &target2);
                                int localB0 = 0;
                                int iVar9 = FUN_00ad2710(&localB0);
                                if (iStack_a4 != 0 || iVar9 != 0) {
                                    int tri[3];
                                    tri[0] = r;
                                    tri[1] = iStack_a4;
                                    tri[2] = 0;
                                    ((cB48*)tgt->mB48)->m_00bca810(4, 0, tgt, f_0145a5c8, tri, iVar9);
                                }
                                target2.m_00ad7ad0();
                            }

                            int* node = s->mpFree;
                            if (node == 0) {
                                node = (int*)FUN_00f473a0(s->mAlloc, d_013f09b4, 0, 0, d_013ebb38, 0xd1);
                            } else {
                                s->mpFree = (int*)node[0];
                            }
                            node[2] = r;
                            node[0] = (int)head;
                            node[1] = head[1];
                            *(int*)head[1] = (int)node;
                            head[1] = (int)node;

                            i++;
                        } while ((int)i < count);
                    }
                }
                bVar12 = (s->mFlag70 != 0);
            }
            target.m_00ad7ad0();
        }
    }
    return bVar12;
}

// @ 0x00ad4a10
int* FUN_00ad4a10(void)
{
    int local_18 = -1;
    if (FUN_01021260() != 0) {
        cRes9* r = FUN_01021260()->m_00c71e30();
        if (r != 0)
            local_18 = FUN_01021260()->m_00c71e30()->m84;
    }

    float fStack_14;
    int* local_10 = 0;
    Vector3 vec = *FUN_00ffbe50()->m_00a1ad60()->mSub.m_2c();
    fStack_14 = f_0145a5c8;

    ObjVec* v = (ObjVec*)FUN_00b3d300()->m_00b21340(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00ad48b0,
        (void*)FUN_00b1e500, 0x18ebadc);
    int n = (int)(v->mpEnd - v->mpBegin);
    int i = 0;
    if (0 < n) {
        do {
            cListObj* obj = v->mpBegin[i];
            if (obj->m_4c() == local_18) {
                const Vector3* q = obj->mSub.m_2c();
                float d = (vec.z - q->z) * (vec.z - q->z)
                        + (vec.y - q->y) * (vec.y - q->y)
                        + (vec.x - q->x) * (vec.x - q->x);
                if (d < fStack_14) {
                    fStack_14 = d;
                    local_10 = (int*)obj;
                }
            }
            i++;
        } while (i < n);
        return local_10;
    }
    return 0;
}
