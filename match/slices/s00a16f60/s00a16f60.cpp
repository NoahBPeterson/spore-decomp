// @ 0x00a16f60
#include "game/types.h"
#include "EA/Audio/PrimitiveBase.h"
#include "EA/Audio/IConfiguration.h"

struct Server;
struct SystemAT;
Server* GetServer();                 // 0x00883860
SystemAT* GetSystemAT();             // 0x00a206f0

bool EA::Audio::PrimitiveBase::Init()
{
    Server* server = GetServer();
    if (server) {
        EA::Messaging::IHandlerRC* handler = this;
        // AddHandler(IHandlerRC*, message id), retail slot 8.
        ((void (__thiscall*)(Server*, EA::Messaging::IHandlerRC*, unsigned int))
            (*(void***)server)[8])(server, handler, 0x02b0c259);
    }

    SystemAT* system = GetSystemAT();
    IConfiguration** config = &mpConfig.mpObject;
    if (*config) {
        IConfiguration* previous = *config;
        *config = 0;
        previous->slot_1(); // IConfiguration::Release, retail slot 1.
    }
    // GetConfiguration evaluates Id after forming the configuration output.
    ((bool (__thiscall*)(SystemAT*, unsigned int, IConfiguration**, unsigned int))
        (*(void***)system)[5])(system, Id(), config, 0x021407ee);
    ConfigurePrimitive();
    return true;
}
