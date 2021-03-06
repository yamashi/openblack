/*****************************************************************************
 * Copyright (c) 2018-2020 openblack developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/openblack/openblack
 *
 * openblack is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "FeatureScriptCommands.h"

#include <tuple>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>
#include <spdlog/spdlog.h>

#include "3D/Camera.h"
#include "3D/LandIsland.h"
#include "AllMeshes.h"
#include "Entities/Components/Abode.h"
#include "Entities/Components/AnimatedStatic.h"
#include "Entities/Components/Footpath.h"
#include "Entities/Components/Stream.h"
#include "Entities/Components/Transform.h"
#include "Entities/Components/Tree.h"
#include "Entities/Components/Villager.h"
#include "Entities/Registry.h"
#include "Enums.h"
#include "Game.h"
#include "ScriptingBindingUtils.h"

using namespace openblack::lhscriptx;

// alias parameter types for signature list readability
const constexpr ParameterType TString = ParameterType::String;
const constexpr ParameterType TNumber = ParameterType::Number;
const constexpr ParameterType TFloat = ParameterType::Float;
const constexpr ParameterType TVector = ParameterType::Vector;

namespace openblack
{
std::unordered_map<std::string, AbodeInfo> abodeIdLookup {
    // Norse
    {"NORSE_ABODE_TOWN_CENTRE", AbodeInfo::NorseTownCentre},
    {"NORSE_ABODE_STORAGE_PIT", AbodeInfo::NorseStoragePit},
    {"NORSE_ABODE_GRAVEYARD", AbodeInfo::NorseGraveyard},
    {"NORSE_ABODE_WORKSHOP", AbodeInfo::NorseWorkshop},
    {"NORSE_ABODE_CRECHE", AbodeInfo::NorseCreche},
    {"NORSE_ABODE_A", AbodeInfo::NorseHut},
    {"NORSE_ABODE_B", AbodeInfo::NorseShackX},
    {"NORSE_ABODE_C", AbodeInfo::NorseShackY},
    {"NORSE_ABODE_D", AbodeInfo::NorseTent},
    {"NORSE_ABODE_E", AbodeInfo::NorseTempleX},
    {"NORSE_ABODE_F", AbodeInfo::NorseTempleY},
    {"NORSE_WONDER", AbodeInfo::NorseWonder},
    // Celtic
    {"CELTIC_ABODE_TOWN_CENTRE", AbodeInfo::CelticTownCentre},
    {"CELTIC_ABODE_STORAGE_PIT", AbodeInfo::CelticStoragePit},
    {"CELTIC_ABODE_GRAVEYARD", AbodeInfo::CelticGraveyard},
    {"CELTIC_ABODE_WORKSHOP", AbodeInfo::CelticGraveyard},
    {"CELTIC_ABODE_CRECHE", AbodeInfo::CelticCreche},
    {"CELTIC_ABODE_A", AbodeInfo::CelticHut},
    {"CELTIC_ABODE_B", AbodeInfo::CelticShackX},
    {"CELTIC_ABODE_C", AbodeInfo::CelticShackY},
    {"CELTIC_ABODE_D", AbodeInfo::CelticTent},
    {"CELTIC_ABODE_E", AbodeInfo::CelticTempleX},
    {"CELTIC_ABODE_F", AbodeInfo::CelticTempleY},
    {"CELTIC_WONDER", AbodeInfo::CelticWonder},
    // Japanese
    {"JAPANESE_ABODE_TOWN_CENTRE", AbodeInfo::JapaneseTownCentre},
    {"JAPANESE_ABODE_STORAGE_PIT", AbodeInfo::JapaneseStoragePit},
    {"JAPANESE_ABODE_GRAVEYARD", AbodeInfo::JapaneseGraveyard},
    {"JAPANESE_ABODE_WORKSHOP", AbodeInfo::JapaneseWorkshop},
    {"JAPANESE_ABODE_CRECHE", AbodeInfo::JapaneseCreche},
    {"JAPANESE_ABODE_A", AbodeInfo::JapaneseHut},
    {"JAPANESE_ABODE_B", AbodeInfo::JapaneseShackX},
    {"JAPANESE_ABODE_C", AbodeInfo::JapaneseShackY},
    {"JAPANESE_ABODE_D", AbodeInfo::JapaneseTent},
    {"JAPANESE_ABODE_E", AbodeInfo::JapaneseTempleX},
    {"JAPANESE_ABODE_F", AbodeInfo::JapaneseTempleY},
    {"JAPANESE_WONDER", AbodeInfo::JapaneseWonder},
    // Aztec
    {"AZTEC_ABODE_TOWN_CENTRE", AbodeInfo::AztecTownCentre},
    {"AZTEC_ABODE_STORAGE_PIT", AbodeInfo::AztecStoragePit},
    {"AZTEC_ABODE_GRAVEYARD", AbodeInfo::AztecGraveyard},
    {"AZTEC_ABODE_WORKSHOP", AbodeInfo::AztecGraveyard},
    {"AZTEC_ABODE_CRECHE", AbodeInfo::AztecCreche},
    {"AZTEC_ABODE_A", AbodeInfo::AztecHut},
    {"AZTEC_ABODE_B", AbodeInfo::AztecShackX},
    {"AZTEC_ABODE_C", AbodeInfo::AztecShackY},
    {"AZTEC_ABODE_D", AbodeInfo::AztecTent},
    {"AZTEC_ABODE_E", AbodeInfo::AztecTempleX},
    {"AZTEC_ABODE_F", AbodeInfo::AztecTempleY},
    {"AZTEC_WONDER", AbodeInfo::AztecWonder},
    // Tibetan
    {"TIBETAN_ABODE_TOWN_CENTRE", AbodeInfo::TibetanTownCentre},
    {"TIBETAN_ABODE_STORAGE_PIT", AbodeInfo::TibetanStoragePit},
    {"TIBETAN_ABODE_GRAVEYARD", AbodeInfo::TibetanGraveyard},
    {"TIBETAN_ABODE_WORKSHOP", AbodeInfo::TibetanWorkshop},
    {"TIBETAN_ABODE_CRECHE", AbodeInfo::TibetanCreche},
    {"TIBETAN_ABODE_A", AbodeInfo::TibetanHut},
    {"TIBETAN_ABODE_B", AbodeInfo::TibetanShackX},
    {"TIBETAN_ABODE_C", AbodeInfo::TibetanShackY},
    {"TIBETAN_ABODE_D", AbodeInfo::TibetanTent},
    {"TIBETAN_ABODE_E", AbodeInfo::TibetanTempleX},
    {"TIBETAN_ABODE_F", AbodeInfo::TibetanTempleY},
    {"TIBETAN_WONDER", AbodeInfo::TibetanWonder},
    // American Indian
    {"INDIAN_ABODE_TOWN_CENTRE", AbodeInfo::IndianTownCentre},
    {"INDIAN_ABODE_STORAGE_PIT", AbodeInfo::IndianStoragePit},
    {"INDIAN_ABODE_GRAVEYARD", AbodeInfo::IndianGraveyard},
    {"INDIAN_ABODE_WORKSHOP", AbodeInfo::IndianWorkshop},
    {"INDIAN_ABODE_CRECHE", AbodeInfo::IndianCreche},
    {"INDIAN_ABODE_A", AbodeInfo::IndianHut},
    {"INDIAN_ABODE_B", AbodeInfo::IndianShackX},
    {"INDIAN_ABODE_C", AbodeInfo::IndianShackY},
    {"INDIAN_ABODE_D", AbodeInfo::IndianTent},
    {"INDIAN_ABODE_E", AbodeInfo::IndianTempleX},
    {"INDIAN_ABODE_F", AbodeInfo::IndianTempleY},
    {"INDIAN_WONDER", AbodeInfo::IndianWonder},
    // Greek
    {"GREEK_ABODE_TOWN_CENTRE", AbodeInfo::GreekTownCentre},
    {"GREEK_ABODE_STORAGE_PIT", AbodeInfo::GreekStoragePit},
    {"GREEK_ABODE_GRAVEYARD", AbodeInfo::GreekGraveyard},
    {"GREEK_ABODE_WORKSHOP", AbodeInfo::GreekWorkshop},
    {"GREEK_ABODE_CRECHE", AbodeInfo::GreekCreche},
    {"GREEK_ABODE_A", AbodeInfo::GreekHut},
    {"GREEK_ABODE_B", AbodeInfo::GreekShackX},
    {"GREEK_ABODE_C", AbodeInfo::GreekShackY},
    {"GREEK_ABODE_D", AbodeInfo::GreekTent},
    {"GREEK_ABODE_E", AbodeInfo::GreekTempleX},
    {"GREEK_ABODE_F", AbodeInfo::GreekTempleY},
    {"GREEK_WONDER", AbodeInfo::GreekWonder},
};

std::unordered_map<std::string, FeatureInfo> featureInfoLookup {
    {"Fat Pilar Lime", FeatureInfo::FatPilarLime},
    {"Pilar3 Lime", FeatureInfo::Pilar3Lime},
    {"Aztec Statue Feature", FeatureInfo::AztcStatue},
    {"Spikey Pilar Lime", FeatureInfo::SpikeyPilarLime},
    {"Pilar2 Lime", FeatureInfo::Pilar2Lime},
    {"Crater", FeatureInfo::Crater},
    {"Pier", FeatureInfo::Pier},
};
} // namespace openblack

const std::array<const ScriptCommandSignature, 105> FeatureScriptCommands::Signatures = {{
    CREATE_COMMAND_BINDING("CREATE_MIST", CreateMist),
    CREATE_COMMAND_BINDING("CREATE_PATH", CreatePath),
    CREATE_COMMAND_BINDING("CREATE_TOWN", CreateTown),
    CREATE_COMMAND_BINDING("SET_TOWN_BELIEF", SetTownBelief),
    CREATE_COMMAND_BINDING("SET_TOWN_BELIEF_CAP", SetTownBeliefCap),
    CREATE_COMMAND_BINDING("SET_TOWN_UNINHABITABLE", SetTownUninhabitable),
    CREATE_COMMAND_BINDING("SET_TOWN_CONGREGATION_POS", SetTownCongregationPos),
    CREATE_COMMAND_BINDING("CREATE_ABODE", CreateAbode),
    CREATE_COMMAND_BINDING("CREATE_PLANNED_ABODE", CreatePlannedAbode),
    CREATE_COMMAND_BINDING("CREATE_TOWN_CENTRE", CreateTownCentre),
    CREATE_COMMAND_BINDING("CREATE_TOWN_SPELL", CreateTownSpell),
    CREATE_COMMAND_BINDING("CREATE_NEW_TOWN_SPELL", CreateNewTownSpell),
    CREATE_COMMAND_BINDING("CREATE_TOWN_CENTRE_SPELL_ICON", CreateTownCentreSpellIcon),
    CREATE_COMMAND_BINDING("CREATE_SPELL_ICON", CreateSpellIcon),
    CREATE_COMMAND_BINDING("CREATE_PLANNED_SPELL_ICON", CreatePlannedSpellIcon),
    CREATE_COMMAND_BINDING("CREATE_VILLAGER", CreateVillager),
    CREATE_COMMAND_BINDING("CREATE_TOWN_VILLAGER", CreateTownVillager),
    CREATE_COMMAND_BINDING("CREATE_SPECIAL_TOWN_VILLAGER", CreateSpecialTownVillager),
    CREATE_COMMAND_BINDING("CREATE_VILLAGER_POS", CreateVillagerPos),
    CREATE_COMMAND_BINDING("CREATE_CITADEL", CreateCitadel),
    CREATE_COMMAND_BINDING("CREATE_PLANNED_CITADEL", CreatePlannedCitadel),
    CREATE_COMMAND_BINDING("CREATE_CREATURE_PEN", CreateCreaturePen),
    CREATE_COMMAND_BINDING("CREATE_WORSHIP_SITE", CreateWorshipSite),
    CREATE_COMMAND_BINDING("CREATE_PLANNED_WORSHIP_SITE", CreatePlannedWorshipSite),
    CREATE_COMMAND_BINDING("CREATE_ANIMAL", CreateAnimal),
    CREATE_COMMAND_BINDING("CREATE_NEW_ANIMAL", CreateNewAnimal),
    CREATE_COMMAND_BINDING("CREATE_FOREST", CreateForest),
    CREATE_COMMAND_BINDING("CREATE_TREE", CreateTree),
    CREATE_COMMAND_BINDING("CREATE_NEW_TREE", CreateNewTree),
    CREATE_COMMAND_BINDING("CREATE_FIELD", CreateField),
    CREATE_COMMAND_BINDING("CREATE_TOWN_FIELD", CreateTownField),
    CREATE_COMMAND_BINDING("CREATE_FISH_FARM", CreateFishFarm),
    CREATE_COMMAND_BINDING("CREATE_TOWN_FISH_FARM", CreateTownFishFarm),
    CREATE_COMMAND_BINDING("CREATE_FEATURE", CreateFeature),
    CREATE_COMMAND_BINDING("CREATE_FLOWERS", CreateFlowers),
    CREATE_COMMAND_BINDING("CREATE_WALL_SECTION", CreateWallSection),
    CREATE_COMMAND_BINDING("CREATE_PLANNED_WALL_SECTION", CreatePlannedWallSection),
    CREATE_COMMAND_BINDING("CREATE_PITCH", CreatePitch),
    CREATE_COMMAND_BINDING("CREATE_POT", CreatePot),
    CREATE_COMMAND_BINDING("CREATE_TOWN_TEMPORARY_POTS", CreateTownTemporaryPots),
    CREATE_COMMAND_BINDING("CREATE_MOBILEOBJECT", CreateMobileObject),
    CREATE_COMMAND_BINDING("CREATE_MOBILESTATIC", CreateMobileStatic),
    CREATE_COMMAND_BINDING("CREATE_MOBILE_STATIC", CreateMobileUStatic),
    CREATE_COMMAND_BINDING("CREATE_DEAD_TREE", CreateDeadTree),
    CREATE_COMMAND_BINDING("CREATE_SCAFFOLD", CreateScaffold),
    CREATE_COMMAND_BINDING("COUNTRY_CHANGE", CountryChange),
    CREATE_COMMAND_BINDING("HEIGHT_CHANGE", HeightChange),
    CREATE_COMMAND_BINDING("CREATE_CREATURE", CreateCreature),
    CREATE_COMMAND_BINDING("CREATE_CREATURE_FROM_FILE", CreateCreatureFromFile),
    CREATE_COMMAND_BINDING("CREATE_FLOCK", CreateFlock),
    CREATE_COMMAND_BINDING("LOAD_LANDSCAPE", LoadLandscape),
    CREATE_COMMAND_BINDING("VERSION", Version),
    CREATE_COMMAND_BINDING("CREATE_AREA", CreateArea),
    CREATE_COMMAND_BINDING("START_CAMERA_POS", StartCameraPos),
    CREATE_COMMAND_BINDING("FLY_BY_FILE", FlyByFile),
    CREATE_COMMAND_BINDING("TOWN_NEEDS_POS", TownNeedsPos),
    CREATE_COMMAND_BINDING("CREATE_FURNITURE", CreateFurniture),
    CREATE_COMMAND_BINDING("CREATE_BIG_FOREST", CreateBigForest),
    CREATE_COMMAND_BINDING("CREATE_NEW_BIG_FOREST", CreateNewBigForest),
    CREATE_COMMAND_BINDING("CREATE_INFLUENCE_RING", CreateInfluenceRing),
    CREATE_COMMAND_BINDING("CREATE_WEATHER_CLIMATE", CreateWeatherClimate),
    CREATE_COMMAND_BINDING("CREATE_WEATHER_CLIMATE_RAIN", CreateWeatherClimateRain),
    CREATE_COMMAND_BINDING("CREATE_WEATHER_CLIMATE_TEMP", CreateWeatherClimateTemp),
    CREATE_COMMAND_BINDING("CREATE_WEATHER_CLIMATE_WIND", CreateWeatherClimateWind),
    CREATE_COMMAND_BINDING("CREATE_WEATHER_STORM", CreateWeatherStorm),
    CREATE_COMMAND_BINDING("BRUSH_SIZE", BrushSize),
    CREATE_COMMAND_BINDING("CREATE_STREAM", CreateStream),
    CREATE_COMMAND_BINDING("CREATE_STREAM_POINT", CreateStreamPoint),
    CREATE_COMMAND_BINDING("CREATE_WATERFALL", CreateWaterfall),
    CREATE_COMMAND_BINDING("CREATE_ARENA", CreateArena),
    CREATE_COMMAND_BINDING("CREATE_FOOTPATH", CreateFootpath),
    CREATE_COMMAND_BINDING("CREATE_FOOTPATH_NODE", CreateFootpathNode),
    CREATE_COMMAND_BINDING("LINK_FOOTPATH", LinkFootpath),
    CREATE_COMMAND_BINDING("CREATE_BONFIRE", CreateBonfire),
    CREATE_COMMAND_BINDING("CREATE_BASE", CreateBase),
    CREATE_COMMAND_BINDING("CREATE_NEW_FEATURE", CreateNewFeature),
    CREATE_COMMAND_BINDING("SET_INTERACT_DESIRE", SetInteractDesire),
    CREATE_COMMAND_BINDING("TOGGLE_COMPUTER_PLAYER", ToggleComputerPlayer),
    CREATE_COMMAND_BINDING("SET_COMPUTER_PLAYER_CREATURE_LIKE", SetComputerPlayerCreatureLike),
    CREATE_COMMAND_BINDING("MULTIPLAYER_DEBUG", MultiplayerDebug),
    CREATE_COMMAND_BINDING("CREATE_STREET_LANTERN", CreateStreetLantern),
    CREATE_COMMAND_BINDING("CREATE_STREET_LIGHT", CreateStreetLight),
    CREATE_COMMAND_BINDING("SET_LAND_NUMBER", SetLandNumber),
    CREATE_COMMAND_BINDING("CREATE_ONE_SHOT_SPELL", CreateOneShotSpell),
    CREATE_COMMAND_BINDING("CREATE_ONE_SHOT_SPELL_PU", CreateOneShotSpellPu),
    CREATE_COMMAND_BINDING("CREATE_FIRE_FLY", CreateFireFly),
    CREATE_COMMAND_BINDING("TOWN_DESIRE_BOOST", TownDesireBoost),
    CREATE_COMMAND_BINDING("CREATE_ANIMATED_STATIC", CreateAnimatedStatic),
    CREATE_COMMAND_BINDING("FIRE_FLY_SPELL_REWARD_PROB", FireFlySpellRewardProb),
    CREATE_COMMAND_BINDING("CREATE_NEW_TOWN_FIELD", CreateNewTownField),
    CREATE_COMMAND_BINDING("CREATE_SPELL_DISPENSER", CreateSpellDispenser),
    CREATE_COMMAND_BINDING("LOAD_COMPUTER_PLAYER_PERSONALLTY", LoadComputerPlayerPersonality),
    CREATE_COMMAND_BINDING("SET_COMPUTER_PLAYER_PERSONALLTY", SetComputerPlayerPersonality),
    CREATE_COMMAND_BINDING("SET_GLOBAL_LAND_BALANCE", SetGlobalLandBalance),
    CREATE_COMMAND_BINDING("SET_LAND_BALANCE", SetLandBalance),
    CREATE_COMMAND_BINDING("CREATE_DRINK_WAYPOINT", CreateDrinkWaypoint),
    CREATE_COMMAND_BINDING("SET_TOWN_INFLUENCE_MULTIPLIER", SetTownInfluenceMultiplier),
    CREATE_COMMAND_BINDING("SET_PLAYER_INFLUENCE_MULTIPLIER", SetPlayerInfluenceMultiplier),
    CREATE_COMMAND_BINDING("SET_TOWN_BALANCE_BELIEF_SCALE", SetTownBalanceBeliefScale),
    CREATE_COMMAND_BINDING("START_GAME_MESSAGE", StartGameMessage),
    CREATE_COMMAND_BINDING("ADD_GAME_MESSAGE_LINE", AddGameMessageLine),
    CREATE_COMMAND_BINDING("EDIT_LEVEL", EditLevel),
    CREATE_COMMAND_BINDING("SET_NIGHTTIME", SetNighttime),
    CREATE_COMMAND_BINDING("MAKE_LAST_OBJECT_ARTIFACT", MakeLastObjectArtifact),
    CREATE_COMMAND_BINDING("SET_LOST_TOWN_SCALE", SetLostTownScale),
}};

openblack::AbodeInfo GetAbodeInfo(const std::string& abodeType)
{
	auto item = openblack::abodeIdLookup.find(abodeType);

	if (item == openblack::abodeIdLookup.end())
	{
		spdlog::error("Missing abode mesh lookup for \"{}\".", abodeType);
		return openblack::AbodeInfo::TibetanWonder;
	}

	return item->second;
}

openblack::FeatureInfo GetFeatureInfo(const std::string& featureType)
{
	auto item = openblack::featureInfoLookup.find(featureType);

	if (item == openblack::featureInfoLookup.end())
	{
		spdlog::error("Missing abode mesh lookup for \"{}\".", featureType);
		return openblack::FeatureInfo::Ark;
	}

	return item->second;
}

inline float GetRadians(const float rotation)
{
	return -(rotation * 0.001f);
}

inline float GetSize(const float size)
{
	return size * 0.001;
}

void FeatureScriptCommands::CreateMist(glm::vec3 position, float param_2, int32_t param_3, float param_4, float param_5)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreatePath(int32_t param_1, int32_t param_2, int32_t param_3, int32_t param_4)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTown(int32_t townId, glm::vec3 position, const std::string& playerOwner,
                                       [[maybe_unused]] int32_t, const std::string& civilisation)
{
	spdlog::debug(R"(LHScriptX: Creating town {} for "{}" with civilisation "{}".)", townId, playerOwner, civilisation);

	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<Town>(entity, townId);
	auto& registryContext = registry.Context();
	registryContext.towns.insert({townId, entity});
}

void FeatureScriptCommands::SetTownBelief(int32_t townId, const std::string& playerOwner, float belief)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	auto& registryContext = registry.Context();

	Town& town = registry.Get<Town>(registryContext.towns.at(townId));
	town.beliefs.insert({playerOwner, belief});
}

void FeatureScriptCommands::SetTownBeliefCap(int32_t townId, const std::string& playerOwner, float belief)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetTownUninhabitable(int32_t townId)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetTownCongregationPos(int32_t townId, glm::vec3 position)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateAbode(int32_t townId, glm::vec3 position, const std::string& abodeInfo, int32_t rotation,
                                        int32_t size, int32_t foodAmount, int32_t woodAmount)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<Transform>(entity, position, glm::eulerAngleY(static_cast<float>(rotation)), glm::vec3(GetSize(size)));
	registry.Assign<Abode>(entity, GetAbodeInfo(abodeInfo), static_cast<uint32_t>(townId), static_cast<uint32_t>(foodAmount),
	                       static_cast<uint32_t>(woodAmount));
}

void FeatureScriptCommands::CreatePlannedAbode(int32_t townId, glm::vec3 position, const std::string& abodeInfo,
                                               int32_t rotation, int32_t size, int32_t foodAmount, int32_t woodAmount)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTownCentre(int32_t townId, glm::vec3 position, const std::string& abodeInfo, int32_t rotation,
                                             int32_t size, int32_t)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();
	auto submeshIds = std::vector {3};

	registry.Assign<Transform>(entity, position, glm::eulerAngleY(static_cast<float>(GetRadians(rotation))),
	                           glm::vec3(GetSize(size)));
	registry.Assign<Abode>(entity, GetAbodeInfo(abodeInfo), static_cast<uint32_t>(townId), static_cast<uint32_t>(0),
	                       static_cast<uint32_t>(0));
}

void FeatureScriptCommands::CreateTownSpell(int32_t townId, const std::string& spellName)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateNewTownSpell(int32_t townId, const std::string& spellName)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTownCentreSpellIcon(int32_t param_1, const std::string& param_2)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateSpellIcon(glm::vec3 position, const std::string& param_2, int32_t param_3, int32_t param_4,
                                            int32_t param_5)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreatePlannedSpellIcon(int32_t param_1, glm::vec3 position, const std::string& param_3,
                                                   int32_t param_4, int32_t param_5, int32_t param_6)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateVillager(glm::vec3, glm::vec3, const std::string&)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTownVillager(int32_t townId, glm::vec3 position, const std::string& villagerType, int32_t age)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateSpecialTownVillager(int32_t, glm::vec3, int32_t, int32_t)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateVillagerPos(glm::vec3 position, [[maybe_unused]] glm::vec3 param_2,
                                              const std::string& ethnicityAndRole, int32_t age)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<Transform>(entity, position, glm::eulerAngleY(glm::radians(180.0f)), glm::vec3(1.0));
	uint32_t health = 100;
	uint32_t hunger = 100;
	auto [ethnicity, role] = Villager::GetVillagerEthnicityAndRole(ethnicityAndRole);
	auto lifeStage = age >= 18 ? VillagerLifeStage::Adult : VillagerLifeStage::Child;
	auto sex = (role == VillagerRoles::HOUSEWIFE) ? VillagerSex::FEMALE : VillagerSex::MALE;
	auto task = VillagerTasks::IDLE;
	registry.Assign<Villager>(entity, health, static_cast<uint32_t>(age), hunger, lifeStage, sex, ethnicity, role, task);
}

void FeatureScriptCommands::CreateCitadel(glm::vec3 position, int32_t, const std::string&, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreatePlannedCitadel(int32_t, glm::vec3 position, int32_t, const std::string&, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateCreaturePen(glm::vec3 position, int32_t, int32_t, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateWorshipSite(glm::vec3 position, int32_t, const std::string&, const std::string&, int32_t,
                                              int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreatePlannedWorshipSite(glm::vec3 position, int32_t, const std::string&, const std::string&,
                                                     int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateAnimal(glm::vec3 position, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateNewAnimal(glm::vec3 position, int32_t, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateForest(int32_t forestId, glm::vec3 position)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTree(int32_t forestId, glm::vec3 position, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateNewTree(int32_t forestId, glm::vec3 position, int32_t treeType, int32_t isNonScenic,
                                          float rotation, float currentSize, float maxSize)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<Transform>(entity, position, glm::eulerAngleY(-rotation), glm::vec3(currentSize));
	registry.Assign<Tree>(entity, TreeInfo(treeType));
}

void FeatureScriptCommands::CreateField(glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTownField(int32_t townId, glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateFishFarm(glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTownFishFarm(int32_t townId, glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateFeature(glm::vec3 position, int32_t, int32_t, int32_t, int32_t)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateFlowers(glm::vec3 position, int32_t, float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateWallSection(glm::vec3 position, int32_t, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreatePlannedWallSection(glm::vec3 position, int32_t, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreatePitch(glm::vec3 position, int32_t, int32_t, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreatePot(glm::vec3 position, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateTownTemporaryPots(int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateMobileObject(glm::vec3 position, int32_t type, int32_t rotation, int32_t scale)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<MobileObject>(entity, static_cast<MobileObjectInfo>(type));
	registry.Assign<Transform>(entity, position, glm::eulerAngleY(GetRadians(rotation)), glm::vec3(GetSize(scale)));
}

void FeatureScriptCommands::CreateMobileStatic(glm::vec3 position, int32_t, float, float)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateMobileUStatic(glm::vec3 position, int32_t type, float verticalOffset, float pitch,
                                                float rotation, float lean, float scale)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	glm::vec3 offset(0.0f, verticalOffset, 0.0f);

	registry.Assign<MobileStatic>(entity, MobileStaticInfo(type));
	registry.Assign<Transform>(entity, position + offset, glm::eulerAngleXYZ(-pitch, -rotation, -lean), glm::vec3(scale));
}

void FeatureScriptCommands::CreateDeadTree(glm::vec3 position, const std::string&, int32_t, float, float, float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateScaffold(int32_t, glm::vec3 position, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CountryChange(glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::HeightChange(glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateCreature(glm::vec3 position, int32_t, int32_t)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateCreatureFromFile(const std::string& playerName, int32_t creatureType,
                                                   const std::string& creatureMind, glm::vec3 position)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateFlock(int32_t, glm::vec3, glm::vec3, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::LoadLandscape(const std::string& path)
{
	Game::instance()->LoadLandscape(path);
}

void FeatureScriptCommands::Version(float version)
{
	spdlog::debug("LHScriptX: Land version set to: {}", version);
}

void FeatureScriptCommands::CreateArea(glm::vec3 position, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::StartCameraPos(glm::vec3 position)
{
	auto& camera = Game::instance()->GetCamera();
	const glm::vec3 offset(0.0f, 10.0f, 0.0f);
	camera.SetPosition(position + offset);
}

void FeatureScriptCommands::FlyByFile(const std::string& path)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::TownNeedsPos(int32_t townId, glm::vec3 position)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateFurniture(glm::vec3 position, int32_t, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateBigForest(glm::vec3 position, int32_t, float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateNewBigForest(glm::vec3 position, int32_t type, int32_t param_3, float rotation, float scale)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<Forest>(entity);
	registry.Assign<Transform>(entity, position, glm::eulerAngleY(-rotation), glm::vec3(scale));
}

void FeatureScriptCommands::CreateInfluenceRing(glm::vec3 position, int32_t, float, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateWeatherClimate(int32_t, int32_t, glm::vec3, float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateWeatherClimateRain(int32_t, float, int32_t, int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateWeatherClimateTemp(int32_t, float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateWeatherClimateWind(int32_t, float, float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateWeatherStorm(int32_t, glm::vec3, float, int32_t, glm::vec3, glm::vec3, glm::vec3, float,
                                               glm::vec3)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::BrushSize(float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateStream(int32_t streamId)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	auto& registryContext = registry.Context();
	const auto entity = registry.Create();

	registry.Assign<Stream>(entity, streamId);
	registryContext.streams.insert({streamId, entity});
}

void FeatureScriptCommands::CreateStreamPoint(int32_t streamId, glm::vec3 position)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	auto& registryContext = registry.Context();

	Stream& stream = registry.Get<Stream>(registryContext.streams.at(streamId));
	const StreamNode newNode(position, stream.nodes);
	stream.nodes.push_back(newNode);
}

void FeatureScriptCommands::CreateWaterfall(glm::vec3 position)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateArena(glm::vec3 position, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateFootpath(int32_t footpathId)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();
	registry.Assign<Footpath>(entity, footpathId);
	auto& registryContext = registry.Context();
	registryContext.footpaths.insert({footpathId, entity});
}

void FeatureScriptCommands::CreateFootpathNode(int footpathId, glm::vec3 position)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	auto& registryContext = registry.Context();
	auto& footpath = registry.Get<Footpath>(registryContext.footpaths.at(footpathId));
	footpath.nodes.push_back(FootpathNode {position});
}

void FeatureScriptCommands::LinkFootpath(int32_t footpathId)
{
	// TODO: The last MultiMapFixed created in this script is an implicit param
	//       This Command adds the footpath to a list in a FootpathLink on the MultiMapFixed
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateBonfire(glm::vec3 position, float rotation, float param_3, float scale)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<MobileStatic>(entity, MobileStaticInfo::Bonfire);
	registry.Assign<Transform>(entity, position, glm::eulerAngleY(-rotation), glm::vec3(scale));
}

void FeatureScriptCommands::CreateBase(glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateNewFeature(glm::vec3 position, const std::string& type, int32_t rotation, int32_t scale,
                                             int32_t param_5)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<Feature>(entity, GetFeatureInfo(type));
	registry.Assign<Transform>(entity, position, glm::eulerAngleY(GetRadians(rotation)), glm::vec3(GetSize(scale)));
}

void FeatureScriptCommands::SetInteractDesire(float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::ToggleComputerPlayer(const std::string&, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetComputerPlayerCreatureLike(const std::string&, const std::string&)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::MultiplayerDebug(int32_t, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateStreetLantern(glm::vec3 position, int32_t)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateStreetLight(glm::vec3 position)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetLandNumber(int32_t number)
{
	spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateOneShotSpell(glm::vec3 position, const std::string&)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateOneShotSpellPu(glm::vec3 position, const std::string&)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateFireFly(glm::vec3 position)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::TownDesireBoost(int32_t townId, const std::string&, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateAnimatedStatic(glm::vec3 position, const std::string& type, int32_t rotation, int32_t scale)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<AnimatedStatic>(entity, type);
	registry.Assign<Transform>(entity, position, glm::eulerAngleY(glm::radians(180.0f) - rotation), glm::vec3(GetSize(scale)));
}

void FeatureScriptCommands::FireFlySpellRewardProb(const std::string& spell, float probability)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateNewTownField(int32_t townId, glm::vec3 position, int32_t param_3, float rotation)
{
	auto& registry = Game::instance()->GetEntityRegistry();
	const auto entity = registry.Create();

	registry.Assign<Field>(entity, townId);
	registry.Assign<Transform>(entity, position, glm::eulerAngleY(glm::radians(180.0f) - rotation), glm::vec3(1.0));
}

void FeatureScriptCommands::CreateSpellDispenser(int32_t, glm::vec3 position, const std::string&, const std::string&, float,
                                                 float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::LoadComputerPlayerPersonality(int32_t, glm::vec3)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetComputerPlayerPersonality(const std::string&, glm::vec3, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetGlobalLandBalance(int32_t, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetLandBalance(const std::string&, int32_t, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::CreateDrinkWaypoint(glm::vec3 position)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetTownInfluenceMultiplier(float multiplier)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetPlayerInfluenceMultiplier(float multiplier)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetTownBalanceBeliefScale(int32_t townId, float scale)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::StartGameMessage(const std::string& message, int32_t landNumber)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::AddGameMessageLine(const std::string& message, int32_t landNumber)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::EditLevel()
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetNighttime(float, float, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::MakeLastObjectArtifact(int32_t, const std::string&, float)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}

void FeatureScriptCommands::SetLostTownScale(float scale)
{
	// spdlog::error("LHScriptX: {}:{}: Function {} not implemented.", __FILE__, __LINE__, __func__);
}
