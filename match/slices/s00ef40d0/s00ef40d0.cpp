// Slice s00ef40d0: 00ef4f80, a UI spinner's per-frame update (thiscall, one int arg, ret 4).
// Class and field names are descriptive guesses; offsets, vtable slots and call conventions come from the binary.

float __cdecl GetElapsedSeconds();                                  // SPUIHelpers::GetElapsedSeconds (0x805080): no args, float in st0
void __cdecl SetRotationQuat(void* transform, const float* rot);    // 0x808230: cdecl (caller does add esp,8)

namespace SP {
class cCombatant {
public:
    void NotifyAttack(int arg);                                     // thiscall, ret 4 (0x10829f0)
};
}

// Virtual interface stub: only the slots this function calls are named (vtable offset = slot * 4).
struct IVirtualSlots {
    virtual void Slot0();  virtual void Slot1();  virtual void Slot2();  virtual void Slot3();
    virtual void Slot4();  virtual void Slot5();  virtual void Slot6();
    virtual void Slot7(int arg);                                    // +0x1c
    virtual void Slot8();  virtual void Slot9();
    virtual unsigned char Slot10();                                 // +0x28
    virtual void Slot11(); virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void Slot15(); virtual void Slot16(); virtual void Slot17(); virtual void Slot18();
    virtual void Slot19(); virtual void Slot20(); virtual void Slot21(); virtual void Slot22();
    virtual void Slot23(); virtual void Slot24(); virtual void Slot25(); virtual void Slot26();
    virtual void Slot27(); virtual void Slot28(); virtual void Slot29(); virtual void Slot30();
    virtual void Slot31(int a, int b);                              // +0x7c
};

class cSpinner {
public:
    char mUnk00[0x2c];
    IVirtualSlots* mpB;          // +0x2c: slot 10 tested with & 1; also the SetRotation target of the second block
    char mUnk30[0x68 - 0x30];
    void* mpTransform;           // +0x68
    IVirtualSlots* mpC;          // +0x6c: slot 31
    char mUnk70[0x74 - 0x70];
    SP::cCombatant* mpCombatant; // +0x74
    char mUnk78[0x84 - 0x78];
    IVirtualSlots* mpD;          // +0x84: slot 7, then slot 10 as bool
    char mUnk88[0x9e - 0x88];
    unsigned char mFlag9e;       // +0x9e
    unsigned char mFlag9f;       // +0x9f

    void Update(int arg);
};

// Quaternion-like rotation {0, 0, 1, -2 * elapsed}, stored as four floats and passed by pointer.
// The target is taken by reference so the member is read after GetElapsedSeconds() returns.
template <typename T>
__forceinline void SetSpinRotation(T* const& target) {
    float rot[4];
    rot[3] = GetElapsedSeconds() * -2.0f;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 1.0f;
    SetRotationQuat(target, rot);
}

void cSpinner::Update(int arg)
{
    if (mpCombatant)
        mpCombatant->NotifyAttack(arg);
    IVirtualSlots* d = mpD;
    if (d != 0)
        d->Slot7(arg);
    if (mpTransform != 0 && mpC != 0) {
        bool spin;
        if (mFlag9f == 0 && mFlag9e == 0) {
            IVirtualSlots* e = mpD;
            spin = e != 0 && e->Slot10() != 0;
        } else {
            spin = true;
        }
        if (spin) {
            mpC->Slot31(1, 1);
            SetSpinRotation(mpTransform);
        } else {
            mpC->Slot31(1, 0);
        }
    }
    IVirtualSlots* b = mpB;
    if (b != 0 && (b->Slot10() & 1) != 0)
        SetSpinRotation(mpB);
}
