// Slice s01023fc0: SP::nSpaceCheats::cCommandMission::Execute(cArguments*) @ 0x01023FC0.
// The "mission" cheat console command:
//   mission create <type> | complete <id> | fulfill <id> | abort <id> | fail <id> | list
//         | debugdraw (dd) | next <type> | ui
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc, same cheat-console region as 0x01025840).
#include "s01023fc0.h"

using namespace EA::ArgScript;

namespace SP {
namespace nSpaceCheats {

// @ 0x01023FC0
void cCommandMission::Execute(cArguments* args)
{
    int numArgs = args->NumArguments();
    if (numArgs <= 1)
        return;

    eastl::sim_string sub(args->operator[](1));

    if (sub == "create") {
        if (numArgs > 2) {
            if (SpaceGameGet()) {
                cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
                if (!planet) {
                    Output(mpFormatParser, "You need to be planet-side to create a mission\n");
                    return;
                }
                eastl::string typeName(args->operator[](2));
                void* target = planet->GetOrbitTarget();
                cSPMission* mission = GetMissionManager()->CreateMissionFromID(
                    SPIDFromName(typeName.c_str()), planet->mpPlanetRecord, target, 0);
                if (mission) {
                    mission->Accept();
                    Output(mpFormatParser, "Mission 0x%X is created.\n", mission);
                } else {
                    Output(mpFormatParser, "Mission creation failed, perhaps it was unable to find a suitable planet.\n");
                }
            } else {
                Output(mpFormatParser, "Can only create a mission while on the planet\n");
            }
        } else {
            Output(mpFormatParser, "Usage: mission create <typename>\n");
        }
    } else if (sub == "complete") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission) {
                        mission->Complete();
                        Output(mpFormatParser, "Mission 0x%X is completed. \n", mission);
                    } else {
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                    }
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        } else {
            Output(mpFormatParser, "Usage: mission complete <id>\n");
        }
    } else if (sub == "fulfill") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission) {
                        mission->Fulfill();
                        Output(mpFormatParser, "Mission 0x%X is fulfilled. \n", mission);
                    } else {
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                    }
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        }
    } else if (sub == "abort") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission) {
                        mission->Abort();
                        Output(mpFormatParser, "Mission 0x%X is aborted.\n", mission);
                    } else {
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                    }
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        } else {
            Output(mpFormatParser, "Usage: mission abort <id>\n");
        }
    } else if (sub == "fail") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission)
                        mission->Fail();
                    else
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        } else {
            Output(mpFormatParser, "Usage: mission fail <id>\n");
        }
    } else if (sub == "list") {
        MissionList list(*GetMissionManager()->GetMissionList());
        for (cSPMission** it = list.mpBegin; it != list.mpEnd; ++it) {
            cSPMission* mission = *it;
            eastl::string16 name;
            const char* suffix = mission->mpParentMission ? "(sub-mission)" : "";
            const wchar_t* text = mission->GetName(&name)->c_str();
            Output(mpFormatParser, "\t- ID:0x%X, %ls %s\n", mission, text, suffix);
        }
        Output(mpFormatParser, "Total %d missions. ", list.size());
        Output(mpFormatParser, "(Regular: %d, Event: %d)\n",
            GetMissionManager()->GetNumNonEventMissions(false), GetMissionManager()->GetNumEventMissions());
    } else if (sub == "debugdraw" || sub == "dd") {
        if (GetMissionManager()->ToggleDebugDraw())
            Output(mpFormatParser, "Enabled debug draw mission lines.\n");
        else
            Output(mpFormatParser, "Disabled debug draw mission lines.\n");
    } else if (sub == "next") {
        eastl::string typeName(args->operator[](2));
        GetMissionManager()->SetNextMissionID(SPIDFromName(typeName.c_str()));
    } else if (sub == "ui") {
        GetUIManager()->ShowMissionUI(0);
    } else {
        Output(mpFormatParser, "Command 'mission' did not understand argument");
    }
}

} // namespace nSpaceCheats
} // namespace SP
