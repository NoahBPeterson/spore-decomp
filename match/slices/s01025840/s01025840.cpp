// Slice s01025840 — one function, @ 0x01025840 (16,198 bytes).
//
// SP::nSpaceCheats::cCommandSpace::Execute(cArguments*)  (real PDB name).
// The space-mode cheat console command ("space -<option>").
//
// Shape: a first group of independent options (energy, capture, warValue,
// starValue, year, siderealDay, day) that only set `handled`; then, if none of
// them ran, one option of a long else-if chain runs and returns ("Unknown
// argument" when nothing matches).  "oursystem"/"sol" share the go-to-home
// tail with the final block.
//
// Callee names come from the 2008 dev build (same function at dev 0x008d5fb0,
// disassembled against its PDB) where the code lines up; see s01025840.h.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no EH frame although
// several locals have destructors; cvttss2si float->int needs /fp:fast).
//
// Status: complete (every option, call, store and output of the original);
// not byte-exact.  Known layout differences: the original merges the shared
// tails ("This command is usable only...", GoToStar, the two warValue
// messages) and keeps a few pooled-literal/temporary orderings that are not
// reproduced here.
#include "s01025840.h"

using namespace EA::ArgScript;

namespace SP {
namespace nSpaceCheats {

// @ 0x01025840
void cCommandSpace::Execute(cArguments* args)
{
    bool handled = false;
    int numArgs = args->NumArguments();
    (void)numArgs;

    // ---- options that can be combined ------------------------------------
    if (args->HasFlag("energy")) {
        handled = true;
        cSpaceshipUFO* ufo = GetUFOSimulator()->GetUFO();
        if (ufo)
            ufo->IncrementEnergy(ufo->mMaxEnergy);
    }

    if (args->HasFlag("capture")) {
        handled = true;
        CaptureStar(cSPLivingUniverse::GetActiveStarRecord(), cSPLivingUniverse::GetPlayerEmpireID());
    }

    if (args->HasFlag("warValue")) {
        handled = true;
        if (cSPLivingUniverse::GetActiveStar() && cSPLivingUniverse::GetActiveStarRecord()) {
            cEmpire* empire = StarManager()->GetEmpireByID(cSPLivingUniverse::GetActiveStarRecord()->GetEmpireID());
            cEmpire* playerEmpire = cSPLivingUniverse::GetPlayerEmpire();
            if (empire && empire != playerEmpire) {
                cPlayer* player = GameNounManager()->GetPlayer();
                int value = player->GetPeacePriceForPlayer(empire);
                if (value != -1) {
                    float elapsed = player->GetPlayerWarElapsedSeconds(empire);
                    int captureDelta = player->GetPlayerWarCaptureDelta(empire);
                    int playerStars = (int)playerEmpire->GetStars().size();
                    int enemyStars = (int)empire->GetStars().size();
                    Output(mpFormatParser, "Value: %d\n", value);
                    Output(mpFormatParser, "Player Stars: %d\n", playerStars);
                    Output(mpFormatParser, "Enemy Stars: %d\n", enemyStars);
                    Output(mpFormatParser, "Capture Delta: %d\n", captureDelta);
                    Output(mpFormatParser, "Elapsed Seconds: %.0f\n", (double)elapsed);
                } else {
                    Output(mpFormatParser, "No war is ongoing with this empire");
                }
            } else {
                Output(mpFormatParser, "No valid empire detected at this star.");
            }
        }
    }

    if (args->HasFlag("starValue")) {
        handled = true;
        if (cSPLivingUniverse::GetActiveStar() && cSPLivingUniverse::GetActiveStarRecord()) {
            cStarRecord* star = cSPLivingUniverse::GetActiveStarRecord();
            eastl::vector<cPlanetRecord*>& planets = star->GetPlanetRecords();
            cTerraformingManager* terraforming = TerraformingManager();
            int planetCount = (int)planets.size();
            int inhabitable = 0;
            int buildings = 0;
            int turrets = 0;
            float tscore = 0.0f;
            for (int i = 0; i < planetCount; i++) {
                cPlanetRecord* planet = planets[i];
                if (planet->mType != 1 && planet->mType != 0 && !planet->IsDestroyed()) {
                    GetTurretAndBuildingCounts(planet, &buildings, &turrets);
                    inhabitable++;
                    tscore += (float)terraforming->GetTScore(planet);
                }
            }
            Output(mpFormatParser, "Value: %d\n", star->GetValue());
            Output(mpFormatParser, "Planet Count: %d\n", planetCount);
            Output(mpFormatParser, "Inhabitable: %d\n", inhabitable);
            Output(mpFormatParser, "Buildings: %d\n", buildings);
            Output(mpFormatParser, "Turrets: %d\n", turrets);
            Output(mpFormatParser, "Average T-Score: %f\n", (double)(tscore / (float)inhabitable));
        }
    }

    const char** opt;
    if ((opt = args->OptionArguments("year", 1)) != 0) {
        handled = true;
        float year = mpFormatParser->ParseFloat(opt[0]);
        cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet) {
            cEllipticalOrbit orbit(planet->GetOrbit());
            orbit.mfPeriod = year;
            planet->SetOrbit(orbit);
        }
    }

    if ((opt = args->OptionArguments("siderealDay", 1)) != 0) {
        handled = true;
        float day = mpFormatParser->ParseFloat(opt[0]);
        int ms = FloatToIntRound(day * 1000.0f);
        cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet && ms >= 0) {
            planet->SetRotationPeriod(day);
            planet->SetRotationNull(day == 0.0f);
        }
    }

    if ((opt = args->OptionArguments("day", 1)) != 0) {
        handled = true;
        float length = mpFormatParser->ParseFloat(opt[0]);
        if (cSPLivingUniverse::GetActivePlanet() && length >= 0.0f)
            TimeOfDay()->SetDayLength(length);
    }

    const Vector3& ufoPosition = GetUFOSimulator()->GetUFO()->mSpatial.GetPosition();

    if (handled)
        return;

    // ---- exclusive options ------------------------------------------------
    if (args->HasFlag("listPlants")) {
        Output(mpFormatParser, "Disabled");
        return;
    }

    if ((opt = args->OptionArguments("startEvent", 1)) != 0) {
        eastl::sim_string eventName(opt[0]);
        uint32_t eventID = EA::Hash::FNV1_String16(EA::ConvertToString16(eventName).c_str(), 0x811c9dc5, true);
        if (!gpEventManager->StartEvent(eventID))
            Output(mpFormatParser, "failed to create event\n");
        return;
    }

    if ((opt = args->OptionArguments("setRelationship", 1)) != 0) {
        float amount = mpFormatParser->ParseFloat(opt[0]);
        const float kMinRelationship = -10.0f;
        const float kMaxRelationship = 10.0f;
        amount = Min(Max(amount, kMinRelationship), kMaxRelationship);
        cStarRecord* star = cSPLivingUniverse::GetActiveStar()->mpStarRecord;
        if (star->GetTechLevel() != 5)
            return;
        cEmpire* empire = StarManager()->GetEmpireByID(star->GetEmpireID());
        if (!empire || empire == cSPLivingUniverse::GetPlayerEmpire())
            return;
        uint32_t politicalID = empire->mPoliticalID;
        uint32_t eventID;
        if (amount > 0.0f) {
            eventID = 0x526e5dc;   // positive relationship event
        } else {
            eventID = 0x526e5f3;   // negative relationship event
            amount = (float)fabs(amount);
        }
        RelationshipManager()->ApplyRelationship(politicalID, cSPLivingUniverse::GetPlayerEmpireID(), eventID, amount);
        return;
    }

    if (args->HasFlag("listAnimals")) {
        Output(mpFormatParser, "obsolete\n");
        return;
    }

    if ((opt = args->OptionArguments("addCargo", 2)) != 0) {
        if (strcmp(opt[0], "slot") == 0) {
            unsigned int slots = mpFormatParser->ParseUInt(opt[1]);
            SpaceGameGet()->GetPlayerInventory()->AddCargoSlots(slots);
        }
        EA::InlineRef<cSpaceInventoryItem> item;
        if (strcmp(opt[0], "animal") == 0) {
            eastl::string name(opt[1]);
            uint32_t id = HashString16(EA::ConvertToString16(name).c_str());
            ResourceKey key = GetValidatedSpeciesKey(id, 0);
            AnimalSpeciesManager()->MakeInventoryItemFromSpecies(item.AsPPTypeParam(), key, true, 0);
        } else if (strcmp(opt[0], "plant") == 0) {
            ResourceKey key;
            key.instanceID = mpFormatParser->ParseUInt(opt[1]);
            key.typeID = 0;
            key.groupID = 0;
            cPlantSpecies* species = PlantSpeciesManager()->GetSpeciesFromID(key);
            if (species)
                species->MakeInventoryItem(item.AsPPTypeParam());
        } else if (strcmp(opt[0], "rare") == 0) {
            eastl::string name(opt[1]);
            ResourceKey key;
            key.instanceID = HashString16(EA::ConvertToString16(name).c_str());
            key.typeID = 0;
            key.groupID = 0;
            SpaceTrading()->CreateCommodityFromID(item.AsPPTypeParam(), key, true, 1.0f);
        } else {
            return;
        }
        if (item.get()) {
            cSpaceInventory* inventory = SpaceGameGet()->GetPlayerInventory();
            item->mInventoryFlags = 10;
            inventory->AddItem(item.get(), false, true);
        }
        return;
    }

    if (args->HasFlag("findAllRares")) {
        unsigned int categories = SpaceTrading()->GetRareCategoryCount();
        for (unsigned int category = 0; category < categories; category++) {
            unsigned int count = SpaceTrading()->GetRareCount(category);
            for (unsigned int index = 0; index < count; index++)
                SpaceTrading()->FindRare(SpaceTrading()->GetRareKey(category, index), 1);
        }
        return;
    }

    if (args->HasFlag("enableGetOut")) {
        gbEnableGetOut = !gbEnableGetOut;
        return;
    }
    if (args->HasFlag("solarrollover")) {
        gbSolarRollover = !gbSolarRollover;
        return;
    }
    if (args->HasFlag("picking")) {
        gbDebugPicking = !gbDebugPicking;
        return;
    }

    int count;
    if ((opt = args->OptionArguments("testTravel", &count, 0, 3)) != 0) {
        float distance;
        if (count <= 0 || !(0.0f < (distance = mpFormatParser->ParseFloat(opt[0]))))
            distance = GetUFOSimulator()->GetMaxTravelDistance();
        if (!(distance > 0.0f))
            return;
        bool toCore = count > 1 ? strcmp(opt[1], "core") == 0 : false;
        bool repeat = count > 2 ? strcmp(opt[2], "repeat") == 0 : false;
        const Vector3* from = toCore ? &gGalacticCorePosition : &cSPLivingUniverse::GetActiveStar()->GetPosition();
        Vector3 position = *from;
        StarManager()->TestIfAllStarsAreReachable(position, distance, repeat);
        return;
    }

    if (args->HasFlag("zones")) {
        gbDebugZones = !gbDebugZones;
        return;
    }

    if (args->HasFlag("trade")) {
        SpaceGameGet()->mTradeUI.ToggleTradeScreen();
        return;
    }

    if (args->HasFlag("demotrade")) {
        gbSolarRollover = !gbSolarRollover;
        eastl::vector<cTradeObject*> objects(SpaceGameGet()->GetPlayerInventory()->GetTradeObjects());
        for (cTradeObject** it = objects.begin(); it != objects.end(); ++it)
            SpaceGameGet()->GetPlayerInventory()->AddTradeObject((*it)->GetID());
        gbDemoTrade = true;
        return;
    }

    if (args->HasFlag("allEmpires")) {
        AllEmpiresFlag()->mbShowAll = !AllEmpiresFlag()->mbShowAll;
        return;
    }

    if (args->HasFlag("vtune")) {
        gbVTune = true;
        return;
    }

    if ((opt = args->OptionArguments("reach", &count, 2, 2)) != 0) {
        gReachMin = mpFormatParser->ParseFloat(opt[0]);
        gReachMax = mpFormatParser->ParseFloat(opt[1]);
        return;
    }

    if (args->HasFlag("dumpEventTimes")) {
        float elapsed = 0.0f;
        GetFloatProperty(gpEventManager->mpProps, 0x31e761f, elapsed);
        Output(mpFormatParser, "PirateRaid : %d secs\n", (int)((float)(gpEventManager->mPirateRaidTimeMS / 1000) - elapsed));
        GetFloatProperty(gpEventManager->mpProps, 0x397a073, elapsed);
        Output(mpFormatParser, "RaidPlunder : %d secs\n", (int)((float)(gpEventManager->mRaidPlunderTimeMS / 1000) - elapsed));
        GetFloatProperty(gpEventManager->mpProps, 0x4488192, elapsed);
        Output(mpFormatParser, "BioDisaster : %d secs\n", (int)(gpEventManager->mBioDisasterTime - elapsed));
        return;
    }

    if (args->HasFlag("demo")) {
        IMessageServer* server = MessageServer();
        eastl::string16 command;
        command = L"tool enable all";
        cCheatMessage msg1(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg1, 0);
        command = L"space -allEmpires";
        cCheatMessage msg2(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg2, 0);
        cSpaceInventory* inventory = SpaceGameGet()->GetPlayerInventory();
        int slots = inventory->GetCargoSlotCount();
        if (slots < 50)
            inventory->AddCargoSlots(50 - slots);
        return;
    }

    if (args->HasFlag("alex")) {
        IMessageServer* server = MessageServer();
        eastl::string16 command;
        gbAlexCheat = !gbAlexCheat;
        for (int i = 0; i < 10; i++)
            SpaceTrading()->AddCommodityToInventory(SpaceTrading()->GetRareKey(0, i), 1);
        for (int i = 0; i < 10; i += 2)
            SpaceTrading()->AddCommodityToInventory(SpaceTrading()->GetRareKey(1, i), 1);
        SpaceTrading()->AddCommodityToInventory(cSPLivingUniverse::GetActivePlanetRecord()->GetSpiceKey(), 0x62);
        command = L"tool enable interplanetarydrive";
        cCheatMessage msg1(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg1, 0);
        command = L"tool enable interstellardrive";
        cCheatMessage msg2(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg2, 0);
        command = L"space -solarrollover";
        cCheatMessage msg3(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg3, 0);
        command = L"space -allEmpires";
        cCheatMessage msg4(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg4, 0);
        return;
    }

    if (args->HasFlag("baris")) {
        IMessageServer* server = MessageServer();
        eastl::string16 command;
        command = L"tool enable all";
        cCheatMessage msg1(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg1, 0);
        command = L"space -solarrollover";
        cCheatMessage msg2(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg2, 0);
        command = L"space -allEmpires";
        cCheatMessage msg3(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg3, 0);
        command = L"mission dd";
        cCheatMessage msg4(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg4, 0);
        command = L"space -debug r";
        cCheatMessage msg5(command.c_str(), command.size());
        server->PostMSG(kMsgCheat, &msg5, 0);
        return;
    }

    if (args->HasFlag("cricket")) {
        // Monte-Carlo: how many random rares until all 8 collections of 10 are complete.
        opt = args->OptionArguments("cricket", 1);
        if (!opt)
            return;
        if (opt[0] != "rares")   // pointer compare (pooled literal), as in the original
            return;
        eastl::vector<eastl::set<int> > collections;
        collections.reserve(8);
        eastl::vector<int> completedAfter;
        completedAfter.reserve(8);
        int zero = 0;
        eastl::vector<int> totals(8, zero);
        int totalRares = 0;
        int totalRepeats = 0;
        int runs = 100;
        do {
            collections.erase(collections.begin(), collections.end());
            collections.resize(8);
            completedAfter.clear();
            int rares = 0;
            int repeats = 0;
            for (;;) {
                int roll = (int)gRandom.RandomUint32Uniform(80);
                int item = roll % 10;
                eastl::set<int>& collection = collections[roll / 10];
                size_t before = collection.size();
                collection.insert(item);
                size_t after = collection.size();
                rares++;
                if (before == after) {
                    repeats++;
                    continue;
                }
                if (after != 10)
                    continue;
                completedAfter.push_back(rares);
                if (completedAfter.size() == 8)
                    break;
            }
            totalRares += rares;
            totalRepeats += repeats;
            for (int i = 0; i < 8; i++)
                totals[i] += completedAfter[i];
        } while (--runs);
        Output(mpFormatParser, "Found %.1f rares with %.1f repeats\n", totalRares * 0.01, totalRepeats * 0.01);
        Output(mpFormatParser, "Collections completed: ");
        for (int i = 0; i < 8; i++)
            Output(mpFormatParser, "%.1f ", totals[i] * 0.01);
        Output(mpFormatParser, "\n");
        return;
    }

    if ((opt = args->OptionArguments("money", 1)) != 0) {
        cSPLivingUniverse::GetPlayerEmpire()->AddMoney(mpFormatParser->ParseUInt(opt[0]));
        cSPUIWindow* window = SpaceGameGet()->GetWindow(0xb);
        window->SetMode(8);
        window->mpState->mValue = 0;
        return;
    }

    if (args->OptionArguments("lategame", 1)) {
        Output(mpFormatParser, "LateGame cheat has been supersceded by the testscript system.\n");
        Output(mpFormatParser, "example:  tester -run TestScript lategame\\stage1 \n");
        return;
    }

    if ((opt = args->OptionArguments("initPlanetRecords", 1)) != 0) {
        float radius = mpFormatParser->ParseFloat(opt[0]);
        eastl::vector<cStarRecord*> stars;
        tStarSearchCriteria criteria;
        if (radius > 0.0f)
            criteria.mMaxDistance = radius;
        StarManager()->GetStarRecords(ufoPosition, criteria, stars);
        int starCount = (int)stars.size();
        for (int i = 0; i < starCount; i++) {
            cStarRecord* star = stars[i];
            StarManager()->ActivatePlanetRecordsForQuery(star, 0);
            eastl::vector<cPlanetRecord*>& planets = star->GetPlanetRecords();
            int planetCount = (int)planets.size();
            for (int j = 0; j < planetCount; j++) {
                cPlanetRecord* planetRecord = planets[j];
                EA::InlineRef<cPlanet> planet;
                StarManager()->GetOrActivatePlanet(planetRecord, planet.AsPPTypeParam());
            }
        }
        return;
    }

    if ((opt = args->OptionArguments("initStarRecords", 1)) != 0) {
        float radius = mpFormatParser->ParseFloat(opt[0]);
        eastl::vector<cStarRecord*> stars;
        tStarSearchCriteria criteria;
        if (radius > 0.0f)
            criteria.mMaxDistance = radius;
        StarManager()->GetStarRecords(ufoPosition, criteria, stars);
        int starCount = (int)stars.size();
        for (int i = 0; i < starCount; i++) {
            stars[i]->SetPlanetsDirty(true);
            if (i % 1000 == 0)
                Output(mpFormatParser, "%d,%d\n", i, starCount);
        }
        eastl::map<uint32_t, cEmpire*>& empires = StarManager()->GetEmpireMap();
        eastl::rbtree_iterator<uint32_t, cEmpire*> it;
        for (it.mpNode = empires.begin_node(); it.mpNode != empires.end_node(); ++it) {
            it.mpNode->second->SetStarGraphUpdate(true);
            it.mpNode->second->UpdateStarGraph();
        }
        return;
    }

    if (args->HasFlag("listempires")) {
        eastl::map<uint32_t, cEmpire*>& empires = StarManager()->GetEmpireMap();
        eastl::rbtree_iterator<uint32_t, cEmpire*> it;
        for (it.mpNode = empires.begin_node(); it.mpNode != empires.end_node(); ++it) {
            cEmpire* empire = it.mpNode->second;
            Output(mpFormatParser, "Empire: %ls\n", empire->GetName());
            eastl::vector<cStarRecord*>& stars = empire->GetStars();
            int starCount = (int)stars.size();
            for (int i = 0; i < starCount; i++) {
                cStarRecord* star = stars[i];
                if (!star)
                    continue;
                Output(mpFormatParser, "\tStar: %ls\n", star->GetName().mpBegin);
                eastl::vector<cPlanetRecord*>& planets = star->GetPlanetRecords();
                int planetCount = (int)planets.size();
                for (int j = 0; j < planetCount; j++) {
                    cPlanetRecord* planet = planets[j];
                    if (empire->OwnsPlanet(planet))
                        Output(mpFormatParser, "\t\tPlanet: %ls\n", planet->mpName);
                }
            }
        }

        // "listempires record": star-record ownership report.
        if (!args->HasFlag("record"))
            return;
        eastl::map<uint32_t, cEmpire*>& empireMap = StarManager()->mEmpires;
        eastl::map<uint32_t, uint32_t> starsPerEmpire;
        eastl::vector<tEmpireStarBucket>& buckets = StarManager()->mStarBuckets;
        for (tEmpireStarBucket* bucket = buckets.begin(); bucket != StarManager()->mStarBuckets.end(); bucket++) {
            unsigned int n = bucket->mStars.size();
            for (unsigned int i = 0; i < n; i++) {
                cStarRecord* star = bucket->mStars[i];
                if (star->GetEmpireID() != (uint32_t)-1 && star->GetEmpireID() != 0) {
                    uint32_t empireID = star->GetEmpireID();
                    starsPerEmpire[empireID]++;
                }
            }
        }
        Output(mpFormatParser, "Star Record Report\n==================\n");
        Output(mpFormatParser, "Number of empires: %d\n", empireMap.size());
        Output(mpFormatParser, "Number of uniques empire ids found: %d\n", starsPerEmpire.size());
        int minSize = 999999;
        int maxSize = 0;
        unsigned int total = 0;
        eastl::rbtree_iterator<uint32_t, uint32_t> rit;
        for (rit.mpNode = starsPerEmpire.begin_node(); rit.mpNode != starsPerEmpire.end_node(); ++rit) {
            uint32_t empireID = rit.mpNode->first;
            int size = (int)rit.mpNode->second;
            if (empireID == (uint32_t)-1 || empireID == 0)
                continue;
            if (size != 0 && size != 1) {
                if (minSize > size)
                    minSize = size;
                if (maxSize < size)
                    maxSize = size;
            }
            total += size;
        }
        Output(mpFormatParser, "Average Empire Size: %d\n", starsPerEmpire.size() ? total / starsPerEmpire.size() : 0);
        Output(mpFormatParser, "Min Empire Size: %d\n", empireMap.size());   // (sic) prints the empire count
        eastl::map<int, int> histogram;
        for (rit.mpNode = starsPerEmpire.begin_node(); rit.mpNode != starsPerEmpire.end_node(); ++rit) {
            int size = (int)rit.mpNode->second;
            histogram[size]++;
        }
        eastl::rbtree_iterator<int, int> hit;
        for (hit.mpNode = histogram.begin_node(); hit.mpNode != histogram.end_node(); ++hit)
            Output(mpFormatParser, "%d empires with %d stars\n", hit.mpNode->second, hit.mpNode->first);
        for (hit.mpNode = histogram.begin_node(); hit.mpNode != histogram.end_node(); ++hit)
            Output(mpFormatParser, "%d,%d\n", hit.mpNode->first, hit.mpNode->second);
        (void)maxSize;
        (void)minSize;
        return;
    }

    if (args->HasFlag("dumprel"))
        return;

    if (args->HasFlag("asteroids")) {
        gbDebugAsteroids = !gbDebugAsteroids;
        return;
    }

    if ((opt = args->OptionArguments("debug", 1)) != 0) {
        eastl::string what(opt[0]);
        if (what == "count" || what == "counts" || what == "c")
            gbDebugCounts = !gbDebugCounts;
        else if (what == "relationship" || what == "relationships" || what == "r")
            gbDebugRelationships = !gbDebugRelationships;
        else if (what == "planet" || what == "planets" || what == "p")
            gbDebugPlanets = !gbDebugPlanets;
        else if (what == "powerLevel" || what == "power")
            gbDebugPowerLevel = !gbDebugPowerLevel;
        else if (what == "awareness" || what == "a")
            gbDebugAwareness = !gbDebugAwareness;
        else if (what == "explosions" || what == "e")
            gbDebugExplosions = !gbDebugExplosions;
        else if (what == "hazards" || what == "hazard" || what == "h")
            gbDebugHazards = !gbDebugHazards;
        return;
    }

    if ((opt = args->OptionArguments("wildlife", 1)) != 0) {
        float radius = mpFormatParser->ParseFloat(opt[0]);
        eastl::sim_string typeNames[7] = { "Astrd", "Gas G", "Barren", "t1", "t2", "t3", "ArtDir" };
        eastl::vector<eastl::vector<int> > plants;
        eastl::vector<eastl::vector<int> > animals;
        for (int k = 7; k; k--) {
            plants.push_back(eastl::vector<int>(10, 0));
            animals.push_back(eastl::vector<int>(10, 0));
        }
        eastl::vector<cStarRecord*> stars;
        tStarSearchCriteria criteria;
        criteria.mMaxDistance = radius;
        StarManager()->GetStarRecords(cSPLivingUniverse::GetActiveStar()->GetPosition(), criteria, stars);
        int starCount = (int)stars.size();
        for (int i = 0; i < starCount; i++) {
            cStarRecord* star = stars[i];
            StarManager()->ActivatePlanetRecordsForQuery(star, 0);
            eastl::vector<cPlanetRecord*>& planets = star->GetPlanetRecords();
            int planetCount = (int)planets.size();
            for (int j = 0; j < planetCount; j++) {
                StarManager()->ActivatePlanet(planets[j], 0);
                cPlanetRecord* planet = planets[j];
                plants[planet->mType][planet->mPlantSpecies.size()]++;
                planet = planets[j];
                animals[planet->mType][planet->mAnimalSpecies.size()]++;
            }
        }
        Output(mpFormatParser, "\n");
        Output(mpFormatParser, "                             plants                               creatures  \n");
        Output(mpFormatParser, "type  |#    |  0   1   2   3   4   5   6   7   8   9|  0   1   2   3   4   5   6   7   8   9\n");
        Output(mpFormatParser, "------+-----+---------------------------------------+----------------------------------------\n");
        for (int type = 0; type < 7; type++) {
            int* p = plants[type].mpBegin;
            int* a = animals[type].mpBegin;
            int planetCount = p[2] + p[3] + p[4] + p[5] + p[6] + p[7] + p[8] + p[9] + p[0] + p[1];
            Output(mpFormatParser,
                   "%6s|%5d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",
                   typeNames[type].c_str(), planetCount,
                   p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9],
                   a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
        }
        Output(mpFormatParser, "------+-----+---------------------------------------+----------------------------------------\n");
        return;
    }

    if ((opt = args->OptionArguments("dump", 1)) != 0) {
        eastl::string what(opt[0]);
        if (what == "planets") {
            int zero = 0;
            eastl::vector<int> starsPerTech(6, zero);
            eastl::vector<cStar*>& allStars = StarManager()->mStars;
            int starCount = (int)allStars.size();
            for (int i = 0; i < starCount; i++)
                starsPerTech[allStars[i]->mpStarRecord->GetTechLevel()]++;

            zero = 0;
            eastl::vector<int> planetsPerType(7, zero);
            zero = 0;
            eastl::vector<int> planetsPerTech(6, zero);
            eastl::vector<eastl::vector<int> > typePerTech;
            for (int k = 7; k; k--) {
                eastl::vector<int> row(6, 0);
                typePerTech.push_back(row);
            }
            eastl::vector<cPlanet*>& allPlanets = StarManager()->mPlanets;
            int planetCount = (int)allPlanets.size();
            for (int i = 0; i < planetCount; i++) {
                cPlanet* planet = allPlanets[i];
                int type = planet->GetType();
                int tech = planet->GetTechLevel();
                planetsPerType[type]++;
                planetsPerTech[tech]++;
                typePerTech[type][tech]++;
            }
            Output(mpFormatParser, "\n");
            Output(mpFormatParser, "Tech level   |  Stars Planets | Asteroids Gas Giants     T0     T1     T2     T3\n");
            Output(mpFormatParser, "-------------+----------------+-------------------------------------------------\n");
            for (int tech = 0; tech < 6; tech++) {
                eastl::string name = GameNounManager()->GetTechLevelName(tech);
                Output(mpFormatParser, "%12s | %6d %7d | %9d %10d %6d %6d %6d %6d\n",
                       name.c_str(), starsPerTech[tech], planetsPerTech[tech],
                       typePerTech[0][tech], typePerTech[1][tech], typePerTech[2][tech],
                       typePerTech[3][tech], typePerTech[4][tech], typePerTech[5][tech]);
            }
            Output(mpFormatParser, "-------------+----------------+-------------------------------------------------\n");
            Output(mpFormatParser, "Totals       | %6d %7d | %9d %10d %6d %6d %6d %6d\n",
                   starCount, planetCount,
                   planetsPerType[0], planetsPerType[1], planetsPerType[2],
                   planetsPerType[3], planetsPerType[4], planetsPerType[5]);
            Output(mpFormatParser, "-------------+----------------+-------------------------------------------------\n");
            Output(mpFormatParser, "                                Asteroids Gas Giants     T0     T1     T2     T3\n");
            Output(mpFormatParser, "\n");
        }
        return;
    }

    if ((opt = args->OptionArguments("gotoSave", 1)) != 0) {
        if (cSPLivingUniverse::GetUniverseContext() != 2)
            return;
        int index = mpFormatParser->ParseInt(opt[0]);
        if (index >= (int)StarManager()->mSaveStars.size())
            return;
        cStarRecord* star = StarManager()->mSaveStars[index];
        if (star)
            GoToStar(star);
        return;
    }

    if (args->HasFlag("oursystem") || args->HasFlag("sol")) {
        if (cSPLivingUniverse::GetUniverseContext() == 2)
            GoToStar(StarManager()->GetHomeStar());
        return;
    }

    if ((opt = args->OptionArguments("flyto", &count, 1, 0x7fffffff)) != 0) {
        if (cSPLivingUniverse::GetUniverseContext() != 2)
            return;
        int starType = 0;
        int techLevel = 0;
        eastl::string where(opt[0]);
        where.make_lower();

        if (where == "pos") {
            float x = mpFormatParser->ParseFloat(opt[1]);
            float y = mpFormatParser->ParseFloat(opt[2]);
            Vector3 position;
            GalaxyCoordsToPosition(x, y, position);
            tStarSearchCriteria criteria;
            criteria.mStarTypes &= ~0xeu;
            cStarRecord* star = StarManager()->FindClosestStar(position, criteria);
            if (star)
                GoToStar(star);
        }

        if (where == "archetype") {
            eastl::string archetype(opt[1]);
            archetype.make_lower();
            unsigned int index;
            for (index = 0; index < 8; index++) {
                if (strcmp(archetype.c_str(), gArchetypeNames[index]) == 0)
                    break;
            }
            if (index < 8) {
                eastl::vector<EA::InlineRef<cStarRecord> > homes;
                eastl::map<uint32_t, cEmpire*>& empires = StarManager()->GetEmpireMap();
                eastl::rbtree_iterator<uint32_t, cEmpire*> it;
                for (it.mpNode = empires.begin_node(); it.mpNode != empires.end_node(); ++it) {
                    cEmpire* empire = it.mpNode->second;
                    if (empire->mArchetype == (int)index) {
                        EA::InlineRef<cStarRecord> home(empire->GetHomeStarRecord());
                        homes.push_back(home);
                    }
                }
                if (!homes.empty()) {
                    gpCompareStarPosition = &cSPLivingUniverse::GetActiveStarRecord()->GetPosition();
                    eastl::sort(homes.begin(), homes.end(), CompareStarRecordDistance);
                    GoToStar(homes[0].get());
                }
            }
        }

        if (where == "starter") {
            eastl::string16 name = EA::ConvertToString16(opt[1], -1);
            eastl::vector<cStarRecord*>& stars = StarManager()->GetStarRecordList();
            int starCount = (int)stars.size();
            for (int i = 0; i < starCount; i++) {
                cStarRecord* star = stars[i];
                if (EA::Locale::StringEqualsNoCase(&star->GetName(), &name)) {
                    GoToStar(star);
                    break;
                }
            }
        }

        if (where == "sol" || where == "oursystem") {
            GoToStar(StarManager()->GetHomeStar());
            return;
        }
        if (where == "home") {
            GoToStar(cSPLivingUniverse::GetPlayerEmpire()->GetHomeStarRecord());
            return;
        }
        if (where == "star") {
            if (count > 1) {
                eastl::string16 name = EA::ConvertToString16(opt[1], -1);
                cStarRecord* star = StarManager()->FindStarByName(name.c_str());
                if (star)
                    GoToStar(star);
            }
            return;
        }

        if (where == "blackhole" || where == "bh")
            starType = 2;
        else if (where == "protoplanetary" || where == "pp")
            starType = 3;
        else if (where == "galacticcore" || where == "gc" || where == "core")
            starType = 1;
        else if (where == "oo")
            starType = 7;
        else if (where == "og" || where == "go")
            starType = 8;
        else if (where == "om" || where == "mo")
            starType = 9;
        else if (where == "gg")
            starType = 10;
        else if (where == "gm" || where == "mg")
            starType = 11;
        else if (where == "mm")
            starType = 12;
        else if (where == "civilization" || where == "civ")
            techLevel = 4;
        else if (where == "tribe")
            techLevel = 2;
        else if (where == "empire" || where == "space")
            techLevel = 5;
        else if (where == "grob" || where == "grox") {
            const Vector3& here = cSPLivingUniverse::GetActiveStarRecord()->GetPosition();
            eastl::vector<cStarRecord*>& groxStars = StarManager()->GetGrox()->GetStars();
            cStarRecord* closest = 0;
            float closestDistance = 3.402823466e+38F;
            for (cStarRecord** it = groxStars.mpBegin; it != groxStars.mpEnd; it++) {
                cStarRecord* star = *it;
                const Vector3& p = star->GetPosition();
                float dx = p.x - here.x;
                float dy = p.y - here.y;
                float dz = p.z - here.z;
                float distance = dz * dz + dy * dy + dx * dx;
                if (closestDistance > distance) {
                    closestDistance = distance;
                    closest = star;
                }
            }
            if (closest)
                GoToStar(closest);
        }

        if (starType || techLevel) {
            cSpaceshipUFO* ufo = GetUFOSimulator()->GetUFO();
            tStarSearchCriteria criteria;
            criteria.mMinDistance = 0.0f;
            if (starType)
                criteria.SetStarType(starType);
            if (techLevel)
                criteria.SetTechLevel(techLevel);
            cStarRecord* star = StarManager()->FindClosestStar(ufo->mSpatial.GetPosition(), criteria);
            if (star)
                GoToStar(star);
        }

        if (where == "rare") {
            cSpaceshipUFO* ufo = GetUFOSimulator()->GetUFO();
            tStarSearchCriteria criteria;
            criteria.mMinDistance = 0.0f;
            criteria.mFlags = 2;
            cStarRecord* star = StarManager()->FindClosestStar(ufo->mSpatial.GetPosition(), criteria);
            if (star)
                GoToStar(star);
        }
        return;
    }

    if (args->HasFlag("wormhole")) {
        if (cSPLivingUniverse::GetUniverseContext() != 1)
            return;
        if (cSPLivingUniverse::GetActiveStar()->GetType() != 2)
            return;
        AppModeSpace()->TransitionThroughWormhole();
        return;
    }

    if ((opt = args->OptionArguments("setarchetype", 1)) != 0) {
        cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet->GetTechLevel() != 5) {
            Output(mpFormatParser, "This command is usable only when you are at empire planets\n");
            return;
        }
        cEmpire* empire = planet->GetEmpire();
        int archetype;
        if (_stricmp(opt[0], "warrior") == 0)
            archetype = 0;
        else if (_stricmp(opt[0], "trader") == 0)
            archetype = 1;
        else if (_stricmp(opt[0], "scientist") == 0)
            archetype = 2;
        else if (_stricmp(opt[0], "shaman") == 0)
            archetype = 3;
        else if (_stricmp(opt[0], "bard") == 0)
            archetype = 4;
        else if (_stricmp(opt[0], "zealot") == 0)
            archetype = 5;
        else if (_stricmp(opt[0], "diplomat") == 0)
            archetype = 6;
        else if (_stricmp(opt[0], "ecologist") == 0)
            archetype = 7;
        else if (_stricmp(opt[0], "grob") == 0 || _stricmp(opt[0], "grox") == 0)
            archetype = 8;
        else {
            Output(mpFormatParser, "Valid archetypes: warrior, trader, scientist, shaman, bard, zealot, diplomat, ecologist, grob,\n");
            return;
        }
        empire->mArchetype = archetype;
        Output(mpFormatParser, "Succesfully changed archetype of %ls to %s\n", empire->GetName(), opt[0]);
        return;
    }

    if ((opt = args->OptionArguments("setempiretrait", 1)) != 0) {
        cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet->GetTechLevel() != 5) {
            Output(mpFormatParser, "This command is usable only when you are at empire planets\n");
            return;
        }
        cEmpire* empire = planet->GetEmpire();
        int trait;
        if (_stricmp(opt[0], "Stingy") == 0)
            trait = 1;
        else if (_stricmp(opt[0], "Generous") == 0)
            trait = 2;
        else if (_stricmp(opt[0], "AccidentProne") == 0)
            trait = 3;
        else {
            Output(mpFormatParser, "Valid traits: Stingy, Generous, AccidentProne\n");
            return;
        }
        empire->mTrait = trait;
        Output(mpFormatParser, "Succesfully changed trait of %ls to %s\n", empire->GetName(), opt[0]);
        return;
    }

    if (args->OptionArguments("drone", 0)) {
        if (cSPLivingUniverse::GetUniverseContext() != 0)
            return;
        cCivilization* civ = GameNounManager()->GetPlayerCivilization();
        if (!civ)
            return;
        ResourceKey modelKey = civ->GetModelTypeKey(GetVehicleType(0, 2));
        Math::Vector3 position(GetUFOSimulator()->GetUFO()->mSpatial.GetPosition());
        Math::Quaternion orientation;
        orientation = GetUFOSimulator()->GetUFO()->mSpatial.GetOrientation();
        for (int i = 4; i; i--) {
            EA::AutoRefCount<cVehicle> vehicle(GameNounManager()->CreateVehicle());
            cVehicle* v = vehicle.get();
            if (v) {
                v->Init(2, 0, modelKey);
                v->SetDrone(true);
                v->mSpatial.SetPosition(position);
                v->mSpatial.SetOrientation(orientation);
                civ->AddVehicle(v);
            }
        }
        return;
    }

    if (args->OptionArguments("forceautosave", 0)) {
        gbForceAutosave = !gbForceAutosave;
        return;
    }

    if (args->HasFlag("clearplanet")) {
        cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
        if (planet && cSPLivingUniverse::GetUniverseContext() != 0) {
            cPlanetGenerator* generator = PlanetGenerator();
            generator->RemoveTerrain(planet->mpPlanetData->GetTerrainID());
            planet->ClearCities();
            planet->ClearVehicles();
            planet->mpPlanetData->mBuildings.Clear();
            eastl::vector<void*>& cities = planet->mpPlanetData->mpCityList;
            while (cities.mpBegin != cities.mpEnd) {
                operator delete[](cities.mpEnd[-1]);
                cities.mpEnd--;
            }
            RebuildPlanetData(planet->mpPlanetData, planet->GetTechLevel());
            planet->SetDirty(true);
            return;
        }
        cSPLivingUniverse::GetUniverseContext();   // result unused (stripped debug output)
        return;
    }

    if (args->HasFlag("taketurn")) {
        AppModeSpace()->mpTurnUpdater->mbTurnPending = false;
        AppModeSpace()->mpTurnUpdater->mbTurnStarted = false;
        AppModeSpace()->mpTurnUpdater->Update(100000000);
        return;
    }

    if ((opt = args->OptionArguments("runcinematic", &count, 1, 2)) != 0) {
        eastl::string name(opt[0]);
        CinematicManager()->PlayCinematic(name.c_str(), 1, 1, 0, 0, 0);
        return;
    }

    if ((opt = args->OptionArguments("rename", &count, 2, 2)) != 0) {
        eastl::string what(opt[0]);
        eastl::string newName(opt[1]);
        if (what == "planet") {
            cPlanetRecord* planet = cSPLivingUniverse::GetActivePlanetRecord();
            if (planet)
                planet->SetName(EA::ConvertToString16(newName));
        } else if (what == "star") {
            cStarRecord* star = cSPLivingUniverse::GetActiveStarRecord();
            if (star)
                star->SetName(EA::ConvertToString16(newName));
        }
        return;
    }

    if ((opt = args->OptionArguments("planet", &count, 1, 1)) != 0) {
        eastl::string name(opt[0]);
        cTypeGroupFilter filter(0xb1b104, SPIDFromName(name.c_str()));
        eastl::vector<ResourceKey> keys;
        ResourceManager()->GetResourceKeyList(keys, &filter, 0);
        if (keys.mpBegin == keys.mpEnd) {
            Output(mpFormatParser, "Planet script %s not found\n", eastl::vararg(name));
        } else {
            gForcedPlanetScript = keys.mpBegin[0];
            gForcedPlanetScriptFlags = 0;
            gbDebugPlanets = true;
            Output(mpFormatParser, "Planet script %s is on deck\n", eastl::vararg(name));
        }
        return;
    }

    if (args->HasFlag("regen_planet")) {
        if (!cSPLivingUniverse::GetActivePlanet())
            return;
        if (cSPLivingUniverse::GetUniverseContext() != 1)
            return;
        uint32_t seed = cSPLivingUniverse::GetActivePlanet()->GetSeed();
        int script = RandomInt(PlanetGenerator()->GetTerrainScript(seed));
        eastl::string command;
        command.sprintf("forceplanet %d %d %u", seed, script, RandomInt(0xfffffff));
        CheatManager()->ExecuteCommand(command.c_str());
        command.sprintf("space -clearplanet");
        CheatManager()->ExecuteCommand(command.c_str());
        return;
    }

    if (args->HasFlag("listcomm")) {
        cCommManager* comm = CommManager();
        int eventCount = (int)comm->mEvents.size();
        for (int i = 0; i < eventCount; i++) {
            EA::AutoRefCount<cCommEvent> event(*(EA::AutoRefCount<cCommEvent>*)&comm->mEvents.mpBegin[i]);
            cCommEvent* e = event.get();
            if (!e)
                continue;

            eastl::string16 planetName((eastl::allocator()));
            cPlanetRecord* planet = StarManager()->GetPlanetRecord(e->mPlanetID);
            planetName = planet ? planet->GetName() : eastl::string16(L"None");

            eastl::string16 starName((eastl::allocator()));
            cStarRecord* star;
            starName = (planet && (star = planet->GetStarRecord()) != 0) ? star->GetName() : eastl::string16(L"None");

            eastl::string16 empireName((eastl::allocator()));
            cEmpire* empire = StarManager()->GetEmpireByID(e->GetSourceEmpireID());
            empireName = empire ? *(const eastl::string16*)&empire->GetName() : eastl::string16(L"None");

            eastl::string16 missionName((eastl::allocator()));
            if (e->mpMission)
                e->mpMission->GetName(missionName);

            eastl::string16 fileName((eastl::allocator()));
            ResourceKey fileKey;
            fileKey.instanceID = 0;
            fileKey.typeID = 0x55ada24;
            fileKey.groupID = 0x55ada23;
            fileKey.instanceID = e->mFileID;
            ResourceManager()->GetFileName(fileKey, fileName);

            eastl::string16 galaxy((eastl::allocator()));
            galaxy = e->mbGalaxy ? L"Y" : L"-";

            Output(mpFormatParser, "%d.\t Planet: %ls \t Star: %ls \t Empire: %ls \n",
                   i, planetName.c_str(), starName.c_str(), empireName.c_str());
            Output(mpFormatParser, "\t Pri: %d \t Galaxy: %ls\n", e->mPriority, galaxy.c_str());
            Output(mpFormatParser, "\t FileID: %ls\t DialogID: 0x%X\n\t Mission: %ls\n",
                   fileName.c_str(), e->mDialogID, missionName.c_str());
            Output(mpFormatParser, "\t Duration (sec): %d \t Elapsed (sec): %d\n",
                   e->mDurationMS / 1000, e->mElapsedMS / 1000);
        }
        return;
    }

    Output(mpFormatParser, "Unknown argument");
}

} // namespace nSpaceCheats
} // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
