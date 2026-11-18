// @ 0x00d4a570
#include "game/types.h"

struct AbilitySlot {
    int mAbility;
    unsigned char mFlag;
    unsigned char padding[3];
};
extern AbilitySlot* g_169e3ec;
extern "C" char sGetButtonCategoryFromButtonID(int button, int* index, int* category);
float FUN_00d49560(int ability);
void FUN_00d49f80(void* context, float value, void* button);

bool VerbTray_HandleRebuild(void* button, void* context)
{
    int index;
    int category;
    unsigned int buttonID = ((unsigned int (__thiscall*)(void*))
        (*(void***)button)[7])(button);
    if (!sGetButtonCategoryFromButtonID(buttonID, &index, &category))
        return false;
    int ability = g_169e3ec[index + category * 5].mAbility;
    if (ability == -1)
        return false;
    float value = FUN_00d49560(ability);
    if (value >= 1.0f)
        return false;
    FUN_00d49f80(context, value, button);
    return true;
}
