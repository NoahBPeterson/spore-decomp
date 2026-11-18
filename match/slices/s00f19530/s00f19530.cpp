// @ 0x00f19530
#include "game/types.h"

// Effect operations on the spatial interface returned by AsInterface. The
// virtual float accessor is kept by slot because its retail name is unknown.
struct ScenarioEffectTarget {
    bool IsEffectActive(unsigned int id);                  // 0x00c88940
    void* CreateEffect(unsigned int resource, int flags,
                       unsigned int id);                   // 0x00c8b130
    void SetEffectScaled(unsigned int id, char enabled);    // 0x00c8a110
};

namespace UI {
void __cdecl cScenarioPlayProgressBar_SetAttr(void* object)
{
    if (object) {
        ScenarioEffectTarget* target =
            ((ScenarioEffectTarget* (__thiscall*)(void*, unsigned int))
             (*(void***)object)[3])(object, 0x01186577);
        if (target && !target->IsEffectActive(0x07b0f76d)) {
            float radius = ((float (__thiscall*)(void*))
                            (*(void***)target)[0x70 / 4])(target);
            unsigned int resource = radius < 10.0f ? 0x389be214 : 0x6a18548c;
            target->CreateEffect(resource, 0, 0x07b0f76d);
            target->SetEffectScaled(0x07b0f76d, 1);
        }
    }
}
}
