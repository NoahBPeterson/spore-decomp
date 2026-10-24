// Slice s00bcc010 - SP::cTribeTool / cVehicle serialization + gameplay helpers
// (SPGonzago/SPGameNounManager.obj style).  All 30 functions are __thiscall
// (this in ecx) with a stack argument and `ret N`.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)
#include "types.h"

// VF(obj, slot): the function pointer stored in slot `slot` of *obj's vtable.
#define VF(obj, slot) (*(void**)((char*)*(void**)(obj) + (slot) * 4))

// ----------------------------------------------------------------------
// external callees (documented with the real retail address)
// ----------------------------------------------------------------------
int   __cdecl FUN_004e1c30(void* tool, unsigned id, int def);  // 0x004e1c30 cdecl
void  __cdecl FUN_0093aa70(void* w, void* p, int n, int b);    // 0x0093aa70 EA::IO::WriteUint32
void  __cdecl FUN_0093a780(void* r, void* p, int n, int b);    // 0x0093a780 EA::IO::ReadInt32
void  __cdecl FUN_00be2440(void* a, int b, int c);             // 0x00be2440
void* __cdecl FUN_00d1e660();                                  // 0x00d1e660
void* __cdecl FUN_00b3d240();                                  // 0x00b3d240
void* __cdecl FUN_00b5b800();                                  // 0x00b5b800 SP::GetCurrentGameMode
void* __cdecl FUN_00cf74c0();                                  // 0x00cf74c0 SP::cCivModeStrategy::Get
struct CCivStrat { void __thiscall M7480(); };                 // 0x00cf7480 thiscall
void  __cdecl FUN_00b1e500();                                 // 0x00b1e500 callback
void* __cdecl FUN_00b3d300();                                 // 0x00b3d300 SP_NounManager
void  __cdecl FUN_00cd7d10();                                 // 0x00cd7d10 callback
void  __cdecl FUN_00d3d420();                                 // 0x00d3d420 callback
void  __cdecl FUN_00ace0f0();                                 // 0x00ace0f0 callback

// cVarListSerializer: retail size 0xa14.
struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    void __thiscall Construct(void* obj, int idA, int idB);    // 0x00692f90 ret 0xc
    char __thiscall Serialize(void* s);                        // 0x00692900 ret 4
    char __thiscall Deserialize(void* s);                      // 0x00693e10 ret 4
    int  __thiscall GetFields(void* s);                        // 0x00695960 ret 4
};

class cGameData {
 public:
    void __thiscall Write(void* s);                            // 0x00b18590 ret 4
    void __thiscall Read(void* s);                             // 0x00b18600 ret 4
    void __thiscall WriteAsText(void* s);                      // 0x00b18420 ret 4
    void __thiscall IsDestroyed(int a);                        // 0x00bfd0d0 ret 4
    void* __thiscall GetProperty(int iid);                     // 0x00b18460 ret 4
};

class cSpatialObject {
 public:
    char __thiscall Write(void* s);                            // 0x00c88a90 ret 4
    char __thiscall Read(void* s);                             // 0x00c88b00 ret 4
    void __thiscall SetLocalExtents(int a, float f);           // 0x00c89160 ret 8
    char __thiscall bcc570();                                  // 0x00bcc570
    void __thiscall bcc5e0(int a, float f);                    // 0x00bcc5e0
    char __thiscall bccdc0();                                  // 0x00bccdc0
    void __thiscall bcc6e0(char v);                            // 0x00bcc6e0
    float __thiscall bcc640();                                 // 0x00bcc640
};

class cLocomotiveObject {
 public:
    char __thiscall Write(void* s);                            // 0x00c448a0 ret 4
};

class cCombatant {
 public:
    char __thiscall Write(void* s);                            // 0x00bfc4a0 ret 4
    char __thiscall Read(void* s);                             // 0x00bfc540 ret 4
    char __thiscall IsSomething();                             // 0x00bfc600 ret
    void __thiscall Do(void* p);                               // 0x00bd7f20 ret 4
};

class cCity {
 public:
    void* __thiscall GetCivilization();                        // 0x00bd9bf0 ret
};

class cSPTimer {
 public:
    char __thiscall IsRunning();                               // 0x00feba90 ret
    int  __thiscall GetElapsedTime();                          // 0x00bc3190 ret
};

class cGameNounManager {
 public:
    int*  __thiscall GetGameDataVector(void* a, void* b, void* c, void* d, int e); // 0x00b21340 ret 0x14
    void  __thiscall RemoveNoun(void* noun);                   // 0x00b225d0 ret 4
    void* __thiscall GetPlayerCivilization();                  // 0x00b25fb0 ret
    void* __thiscall Unk25f40(void* p);                        // 0x00b25f40 ret 4
};

// GetProperty-style chain helpers (each returns `this` when iid matches).
class PropHost {
 public:
    void* __thiscall Get108(int iid);                          // 0x00ac0320 ret 4
    void* __thiscall Get51C(int iid);                          // 0x00abf740 ret 4
    void* __thiscall GetBase(int iid);                         // 0x00b18460 ret 4
    void* __thiscall Get120(int iid);                          // 0x00bfc380 ret 4
    void* __thiscall Get34a(int iid);                          // 0x00c884f0 ret 4
    void* __thiscall Get1E8(int iid);                          // 0x00c751c0 ret 4
    void* __thiscall Get34b(int iid);                          // 0x00c41d00 ret 4
};

// Shared serialization body: layout cGameData @0, cSpatialObject @0x34,
// cCombatant @0x120, flag byte @0x230.
class cSerializableNoun {
 public:
    char __thiscall WriteBase(void* s);                        // 0x00bcc350
    char __thiscall ReadBase(void* s);                         // 0x00bcc400
};

class cTribeTool : public cSerializableNoun {
 public:
    void __thiscall bcc010();
    void __thiscall bcc230(int elapsed);
    void __thiscall bcc760(int v);
    void __thiscall bcc7e0(int delta);
    int  __thiscall bcc800();
    int  __thiscall bcc820();
    void __thiscall bcc860(int unused);
    void* __thiscall bcc500(int iid);
    void __thiscall ResetTool();                               // 0x00bcbc80 ret
};

class cVehicle : public cSerializableNoun {
 public:
    void __thiscall Write1(void* s);                           // 0x00bcc8b0
    void __thiscall Read1(void* s);                            // 0x00bcc920
    void __thiscall Write2(void* s);                           // 0x00bcc9f0
    void __thiscall Read2(void* s);                            // 0x00bcca60
    void __thiscall Write3(void* s);                           // 0x00bccb30
    void __thiscall Read3(void* s);                            // 0x00bccba0
    bool __thiscall Write4(void* s);                           // 0x00bccc70
    bool __thiscall Read4(void* s);                            // 0x00bccd10
    void* __thiscall GetProp(int iid);                         // 0x00bcce20
    void __thiscall bccf20();
    bool __thiscall Write5(void* s);                           // 0x00bccf80
    void __thiscall WriteAsText(void* s);                      // 0x00bcd030
    void __thiscall bcd130(int delta);                         // 0x00bcd130
    int  __thiscall bcd250();
};

// Another object whose `this` sits 0xec above the serializable noun base.
class cToolExtra {
 public:
    void __thiscall bcc650(int param);
};

// ======================================================================
// 00bcc010 - pick the two tool ids via the noun's service, then count
// nearby nouns inside the squared radius and flash them.
// ======================================================================
// @ 0x00bcc010
void __thiscall cTribeTool::bcc010() {
    cTribeTool* self = this;
    void* mgr = FUN_00d1e660();
    char* noun = *(char**)((char*)mgr + 0x1c);
    void* svc = *(void**)(noun + 0x130);
    int selA;
    if (svc == 0 || !((char(__thiscall*)(void*, int, int*))VF(svc, 9))(svc, 0x1070c664, &selA)) {
        selA = 5;
    } else {
        short t = *(short*)(selA + 0x12);
        if (t == 9 || t == 0x10) {
            if ((*(unsigned char*)(selA + 0x10) & 0x30) == 0)
                selA = selA & -(int)(t != 0);
            else
                selA = *(int*)(*(int*)selA);
        } else {
            selA = *(int*)0x15d9c68;
        }
    }

    int   selB;
    float f;
    if (svc == 0 || !((char(__thiscall*)(void*, int, int*))VF(svc, 9))(svc, 0xe17636cf, &selB)) {
        f = *(float*)0x13f1cac;
    } else {
        short t = *(short*)(selB + 0x12);
        if (t == 0xd || t == 0x10) {
            if ((*(unsigned char*)(selB + 0x10) & 0x30) == 0)
                f = *(float*)(selB & -(int)(t != 0));
            else
                f = *(float*)*(int*)selB;
        } else {
            f = *(float*)0x15d9c6c;
        }
    }
    float dist2 = f * f;

    int    count = 0;
    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    int*   vec = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                       (void*)FUN_00ace0f0, (void*)FUN_00b1e500, 0x18eb45e);
    int*   p   = (int*)vec[1];
    while (p != (int*)vec[2]) {
        if ((unsigned)count >= (unsigned)selA) break;
        char* obj = (char*)*p;
        if (*(char*)(obj + 0xb5e) == 0 && *(char*)(obj + 0x135) != 0) {
            float* a = (float*)((int(__thiscall*)(void*))VF((char*)self + 0x34, 11))((char*)self + 0x34);
            float* b = (float*)((int(__thiscall*)(void*))VF(obj + 0xc0, 11))(obj + 0xc0);
            float dx = b[0] - a[0];
            float dy = b[1] - a[1];
            float dz = b[2] - a[2];
            float d2 = dx * dx + dy * dy + dz * dz;
            if (d2 < dist2) {
                count++;
                char* r = (char*)((void*(__thiscall*)(void*, int, int, float, void*))
                                  VF(*(char**)(obj + 0xb4c) + 8, 0))(*(char**)(obj + 0xb4c) + 8,
                                                                    0, 0x100, *(float*)0x1466a3c, self);
                if (r != 0) {
                    *(float*)(r + 0xc)  = *(float*)0x1485720;
                    *(float*)(r + 0x10) = *(float*)0x1485720;
                }
            }
        }
        p++;
    }
    *(int*)((char*)self + 0x10c) = 0;
}

// @ 0x00bcc230
void __thiscall cTribeTool::bcc230(int elapsed) {
    cTribeTool* self = this;
    void* mgr = FUN_00d1e660();
    char* noun = *(char**)((char*)mgr + 0x1c);
    int state = *(int*)((char*)self + 0x108);
    if (state >= 2) {
      if (state <= 4) {
        *(uint32_t*)((char*)self + 0x110) += elapsed;
        *(uint32_t*)((char*)self + 0x10c) += elapsed;
        void* tool = *(void**)(noun + 0x130);
        uint32_t p1 = FUN_004e1c30(tool, 0xbbcb85bc, 0x78) * 1000;
        uint32_t p2 = FUN_004e1c30(*(void**)(noun + 0x130), 0xbe3ce72d, 0x1e) * 1000;
        if (*(uint32_t*)((char*)self + 0x110) > p1) {
            *(int*)((char*)self + 0x108) = 4;
            self->ResetTool();
        } else if (*(uint32_t*)((char*)self + 0x10c) > p2) {
            self->bcc010();
        }
      }
    }
    if (*(int*)((char*)self + 0x108) == 5) {
        *(uint32_t*)((char*)self + 0x110) += elapsed;
        void* tool = *(void**)(noun + 0x130);
        if (*(uint32_t*)((char*)self + 0x110) > (uint32_t)(FUN_004e1c30(tool, 0x42729a8, 5) * 1000))
            ((cGameNounManager*)FUN_00b3d300())->RemoveNoun(self);
    }
}

// ======================================================================
// shared Write / Read for the noun classes
// ======================================================================
// @ 0x00bcc350
char __thiscall cSerializableNoun::WriteBase(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0xe9cb8ba;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cGameData*)this)->Write(s);
    bool ok = ((cSpatialObject*)((char*)this + 0x34))->Write(s) != 0 &&
              ((cCombatant*)((char*)this + 0x120))->Write(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156d770, 0x1a80d26);
    if (ok && vl.Serialize(s) != 0)
        return 1;
    return 0;
}

// @ 0x00bcc400
char __thiscall cSerializableNoun::ReadBase(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    char* sub = (char*)this + 0x34;
    ((cGameData*)this)->Read(s);
    bool ok = false;
    if (((cSpatialObject*)sub)->Read(s) != 0 &&
        ((cCombatant*)((char*)this + 0x120))->Read(s) != 0)
        ok = true;
    cVarListSerializer vl;
    vl.Construct(this, 0x156d770, 0x1a80d26);
    char res = 0;
    if (ok && vl.Deserialize(s) != 0) {
        res = 1;
        if (*(char*)((char*)this + 0x230) != 0) {
            int vv[3];
            vv[0] = 0xd1bf030c;
            vv[1] = 0;
            vv[2] = 0;
            ((void(__thiscall*)(void*, int*))VF(sub, 0x94 / 4))(sub, vv);
        } else {
            ((void(__thiscall*)(void*, void*))VF(sub, 0x94 / 4))(sub, (char*)this + 0xc4);
        }
    }
    return res;
}

// @ 0x00bcc500
void* __thiscall cTribeTool::bcc500(int iid) {
    if (iid == 0xe9cb8ba) return this;
    void* r = ((PropHost*)((char*)this + 0x108))->Get108(iid);
    if (r == 0) r = ((PropHost*)this)->GetBase(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x120))->Get120(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x34))->Get34a(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x1e8))->Get1E8(iid);
    return r;
}

// @ 0x00bcc570
char __thiscall cSpatialObject::bcc570() {
    if (FUN_00b5b800() == (void*)0x1654c10) return 1;
    char* obj = (char*)this - 0x34;
    void* a = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (a != 0) {
        void* b = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (b != 0) {
            if (((int(__thiscall*)(void*))VF(b, 8))(b) == 0x18c43e8)
                if (!((char(__thiscall*)(void*))VF(b, 11))(b))
                    return ((char(__thiscall*)(void*))VF((char*)b + 0x120, 0x16))((char*)b + 0x120);
        }
    }
    return 0;
}

// @ 0x00bcc5e0
void __thiscall cSpatialObject::bcc5e0(int a, float f) {
    ((cSpatialObject*)this)->SetLocalExtents(a, f);
    char* obj = (char*)this - 0x34;
    void* x = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (x != 0) {
        void* y = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (y != 0 && ((int(__thiscall*)(void*))VF(y, 8))(y) == 0x18c43e8)
            ((cCombatant*)y)->Do(obj);
    }
}

// @ 0x00bcc640
float __thiscall cSpatialObject::bcc640() {
    float c = ((float(__thiscall*)(void*))VF(this, 0x5c / 4))(this);
    return c * *(float*)0x1485544;
}

// @ 0x00bcc650
void __thiscall cToolExtra::bcc650(int param) {
    ((cGameData*)this)->IsDestroyed(param);
    char* obj = (char*)this - 0xec;
    ((void(__thiscall*)(void*, void*))VF(obj, 37))(obj, (char*)this + 0x104);
    void* h = FUN_00b3d240();
    uint32_t buf[3];
    ((void(__thiscall*)(void*, int, void*, void*))VF(h, 0x60 / 4))(
        h, 0x3704925,
        ((void*(__thiscall*)(void*))VF(obj, 11))(obj),
        ((void*(__thiscall*)(void*, void*))VF(obj, 23))(obj, buf));
}

// @ 0x00bcc6e0
void __thiscall cSpatialObject::bcc6e0(char v) {
    if (*(char*)((char*)this + 0x289) == v) return;
    char* o = (char*)this + 0x34;
    *(char*)((char*)this + 0x289) = v;
    void* tgt = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
    if (tgt == 0) return;
    if (*(char*)((char*)this + 0x289) != 0)
        ((void(__thiscall*)(void*, void*))VF(tgt, 0xc4 / 4))(tgt,
            ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 1, 1, 0));
    else
        ((void(__thiscall*)(void*, void*))VF(tgt, 0xc4 / 4))(tgt,
            ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 0, 1, 0));
}

// @ 0x00bcc760
void __thiscall cTribeTool::bcc760(int v) {
    int old = *(int*)((char*)this + 0x290);
    if (old == v) return;
    bool before = old > 0 || ((cCombatant*)((char*)this + 0x120))->IsSomething() != 0;
    *(int*)((char*)this + 0x290) = v;
    if (before != (v > 0 || ((cCombatant*)((char*)this + 0x120))->IsSomething() != 0))
        FUN_00be2440(((void*(__thiscall*)(void*))VF(this, 0x84 / 4))(this), 0, 0);
}

// @ 0x00bcc7e0
void __thiscall cTribeTool::bcc7e0(int delta) {
    bcc760(*(int*)((char*)this + 0x290) + delta);
}

// @ 0x00bcc800
int __thiscall cTribeTool::bcc800() {
    cSPTimer* t = (cSPTimer*)((char*)this + 0x258);
    if (t->IsRunning())
        return t->GetElapsedTime();
    return 0;
}

// @ 0x00bcc820
int __thiscall cTribeTool::bcc820() {
    return *(char*)((char*)this + 0x48) == 0;
}

// @ 0x00bcc860
void __thiscall cTribeTool::bcc860(int unused) {
    (void)unused;
    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    nm->GetPlayerCivilization();
    char* obj = (char*)this - 0x34;
    void* c = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (c != 0)
        ((void(__thiscall*)(void*))VF(c, 8))(c);
    ((CCivStrat*)FUN_00cf74c0())->M7480();
}

// ======================================================================
// cVehicle-side serialization
// ======================================================================
// @ 0x00bcc8b0
void __thiscall cVehicle::Write1(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0x1007ae63;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->WriteBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dab8, 0x1a80d26);
    vl.Serialize(s);
}

// @ 0x00bcc920
void __thiscall cVehicle::Read1(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->ReadBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dab8, 0x1a80d26);
    vl.Deserialize(s);
}

// @ 0x00bcc9f0
void __thiscall cVehicle::Write2(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0xecade42;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->WriteBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156db6c, 0x1a80d26);
    vl.Serialize(s);
}

// @ 0x00bcca60
void __thiscall cVehicle::Read2(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->ReadBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156db6c, 0x1a80d26);
    vl.Deserialize(s);
}

// @ 0x00bccb30
void __thiscall cVehicle::Write3(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0xff10521;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->WriteBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dba8, 0x1a80d26);
    vl.Serialize(s);
}

// @ 0x00bccba0
void __thiscall cVehicle::Read3(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    ((cSerializableNoun*)this)->ReadBase(s);
    cVarListSerializer vl;
    vl.Construct(this, 0x156dba8, 0x1a80d26);
    vl.Deserialize(s);
}

// @ 0x00bccc70
bool __thiscall cVehicle::Write4(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0x1a55e4d;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    bool ok = ((cSerializableNoun*)this)->WriteBase(s) != 0 &&
              ((cSerializableNoun*)this)->WriteBase(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156dbe4, 0x1a80d26);
    if (ok && vl.Serialize(s) != 0)
        return true;
    return false;
}

// @ 0x00bccd10
bool __thiscall cVehicle::Read4(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    int   ver;
    FUN_0093a780(w, &ver, 1, 0);
    bool ok = ((cSerializableNoun*)this)->ReadBase(s) != 0 &&
              ((cSerializableNoun*)this)->ReadBase(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156dbe4, 0x1a80d26);
    if (ok && vl.Deserialize(s) != 0)
        return true;
    return false;
}

// @ 0x00bccdc0
char __thiscall cSpatialObject::bccdc0() {
    char* obj = (char*)this - 0x34;
    void* a = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (a != 0) {
        void* b = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (b != 0) {
            if (((int(__thiscall*)(void*))VF(b, 8))(b) == 0x18c43e8)
                if (!((char(__thiscall*)(void*))VF(b, 11))(b))
                    return ((char(__thiscall*)(void*))VF((char*)b + 0x120, 0x16))((char*)b + 0x120);
        }
    }
    return 0;
}

// @ 0x00bcce20
void* __thiscall cVehicle::GetProp(int iid) {
    if (iid == 0x436f315) return this;
    void* r = ((PropHost*)((char*)this + 0x504))->Get108(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x51c))->Get51C(iid);
    if (r == 0) r = ((PropHost*)this)->GetBase(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x588))->Get120(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x34))->Get34b(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x650))->Get1E8(iid);
    return r;
}

// @ 0x00bccf20
void __thiscall cVehicle::bccf20() {
    void* c = ((void*(__thiscall*)(void*))VF(this, 12))(this);
    void* city = c;
    if (c == 0 || ((int(__thiscall*)(void*))VF(c, 8))(c) != 0x18c43e8)
        city = 0;
    if (((int(__thiscall*)(void*))VF(this, 0x4c / 4))(this) == -1)
        ((cCity*)city)->GetCivilization();
    else
        ((cGameNounManager*)FUN_00b3d300())->Unk25f40(
            (void*)((int(__thiscall*)(void*))VF(this, 0x4c / 4))(this));
}

// @ 0x00bccf80
bool __thiscall cVehicle::Write5(void* s) {
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0x436f315;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cGameData*)this)->Write(s);
    bool ok = ((cLocomotiveObject*)((char*)this + 0x34))->Write(s) != 0 &&
              ((cCombatant*)((char*)this + 0x588))->Write(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156dc20, 0x1a80d26);
    if (ok && vl.Serialize(s) != 0)
        return true;
    return false;
}

// @ 0x00bcd030
void __thiscall cVehicle::WriteAsText(void* s) {
    ((cGameData*)this)->WriteAsText(s);
    cVarListSerializer v1;
    cVarListSerializer v2;
    v1.Construct((char*)this + 0x34, 0x157a1f8, 0x1a80d26);
    v1.GetFields(s);
    v1.Construct((char*)this + 0x120, 0x1570858, 0x1a80d26);
    v1.GetFields(s);
    v2.Construct(this, 0x156d770, 0x1a80d26);
    v2.GetFields(s);
}

// @ 0x00bcd130
void __thiscall cVehicle::bcd130(int delta) {
    bool before = *(int*)((char*)this + 0x684) > 0 ||
                  ((cCombatant*)((char*)this + 0x588))->IsSomething() != 0;
    *(int*)((char*)this + 0x684) += delta;
    int  after  = *(int*)((char*)this + 0x684) > 0 ||
                  ((cCombatant*)((char*)this + 0x588))->IsSomething() != 0;
    if (before != (after != 0)) {        char* o = (char*)this + 0x34;
        if (*(int*)((char*)this + 0x684) > 0 ||
            ((cCombatant*)((char*)this + 0x588))->IsSomething() != 0) {
            ((void(__thiscall*)(void*, int))VF((char*)this + 0x588, 0x50 / 4))((char*)this + 0x588, 0);
            void* tgt = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
            if (tgt != 0) {
                void* t2 = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
                ((void(__thiscall*)(void*, void*))VF(t2, 0xc4 / 4))(t2,
                    ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 0, 1, 0));
            }
        } else {
            void* tgt = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
            if (tgt != 0) {
                void* t2 = ((void*(__thiscall*)(void*))VF(o, 0xb0 / 4))(o);
                ((void(__thiscall*)(void*, void*))VF(t2, 0xc4 / 4))(t2,
                    ((void*(__thiscall*)(void*, int, int, int))VF(o, 0xac / 4))(o, 1, 1, 0));
            }
        }
    }
}

// @ 0x00bcd250
int __thiscall cVehicle::bcd250() {
    cSPTimer* t = (cSPTimer*)((char*)this + 0x660);
    if (t->IsRunning())
        return t->GetElapsedTime();
    return 0;
}
