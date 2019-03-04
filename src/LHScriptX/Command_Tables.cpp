/* OpenBlack - A reimplementation of Lionheads's Black & White engine
 *
 * OpenBlack is the legal property of its developers, whose names
 * can be found in the AUTHORS.md file distributed with this source
 * distribution.
 *
 * OpenBlack is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * OpenBlack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenBlack. If not, see <http://www.gnu.org/licenses/>.
 */

//#pragma once
//#ifndef OPENBLACK_LHSCRIPTX_COMMAND_TABLES_H
//#define OPENBLACK_LHSCRIPTX_COMMAND_TABLES_H

#include "Impl_LandCommands.h"
#include "Impl_MapCommands.h"

namespace OpenBlack {

namespace LHScriptX {

/*
* Command definitions for "map" scripts. (map.txt)
*/
const ScriptCommandDef Impl_MapCommands::Definitions[] = {
	{ 0,   "SET_NO_PLAYERS",       { TypeNumber },                                     &Impl_MapCommands::setNoPlayers },
	{ 1,   "LOAD_TRIBE_DANCE",     { TypeVector, TypeNumber },                         &Impl_MapCommands::loadTribeDance },
	{ 2,   "SET_DATE",             { TypeNumber, TypeNumber, TypeNumber },             &Impl_MapCommands::setDate },
	{ 3,   "SET_TIME",             { TypeNumber, TypeNumber, TypeNumber },             &Impl_MapCommands::setTime },
	{ 4,   "SET_TURNS_PER_YEAR",   { TypeNumber },                                     &Impl_MapCommands::setTurnsPerYear },
	{ 5,   "SET_GAME_TICK_TIME",   { TypeNumber },                                     &Impl_MapCommands::setGameTickTime },
	{ 6,   "LOAD_FEATURE_SCRIPT",  { TypeVector },                                     &Impl_MapCommands::loadFeatureScript },
	{ 7,   "PAUSE_GAME",           {  },                                               &Impl_MapCommands::pauseGame },
	{ 8,   "CREATE_CREATURE",      { TypeNumber, TypeNumber, TypeNumber, TypeNumber }, &Impl_MapCommands::createCreature },
	{ 9,   "OUTPUT_VILLAGERS",     {  },                                               &Impl_MapCommands::outputVillagers },
	{ 10,  "OUTPUT_TOWN",          {  },                                               &Impl_MapCommands::outputTown },
	{ 11,  "OUTPUT_CREATURES",     {  },                                               &Impl_MapCommands::outputCreatures },
	{ 12,  "OUTPUT_COLLIDE",       {  },                                               &Impl_MapCommands::outputCollide },
	{ 13,  "OUTPUT_ALLOC",         {  },                                               &Impl_MapCommands::outputAlloc },
	{ 14,  "SAVE_FOR_NET_DEBUG",   { TypeNumber, TypeNumber },                         &Impl_MapCommands::saveForNetDebug },
	{ 15,  "LOAD_FOR_NET_DEBUG",   { TypeNumber },                                     &Impl_MapCommands::loadForNetDebug },
	{ 16,  "LOAD_LANDSCAPE",       { TypeVector },                                     &Impl_MapCommands::loadLandscape },
	{ 17,  "LOAD_GAME_SCRIPT",     { TypeVector },                                     &Impl_MapCommands::loadGameScript },
	{ 18,  "LOAD_RAW_GAME_SCRIPT", { TypeVector },                                     &Impl_MapCommands::loadRawGameScript },
	{ 19,  "LOAD_LANGUAGE",        {  },                                               &Impl_MapCommands::loadLanguage },
};

/*
* Function pointers for land scripts. (Land*.txt, Playgrounds/*.txt, etc..).
*/
const ScriptCommandDef Impl_LandCommands::Definitions[] = {
	{ 0,   "CREATE_MIST",                       { TypeVector, TypeFloat, TypeNumber, TypeFloat, TypeFloat },                                                      &Impl_LandCommands::createMist },
	{ 1,   "CREATE_PATH",                       { TypeNumber, TypeNumber, TypeNumber, TypeNumber },                                                                &Impl_LandCommands::createPath },
	{ 2,   "CREATE_TOWN",                       { TypeNumber, TypeVector, TypeString, TypeNumber, TypeString },                                                   &Impl_LandCommands::createTown },
	{ 3,   "SET_TOWN_BELIEF",                   { TypeNumber, TypeString, TypeFloat },                                                                              &Impl_LandCommands::setTownBelief },
	{ 4,   "SET_TOWN_BELIEF_CAP",               { TypeNumber, TypeString, TypeFloat },                                                                              &Impl_LandCommands::setTownBeliefCap },
	{ 5,   "SET_TOWN_UNINHABITABLE",            { TypeNumber },                                                                                                       &Impl_LandCommands::setTownUninhabitable },
	{ 6,   "SET_TOWN_CONGREGATION_POS",         { TypeNumber, TypeVector },                                                                                          &Impl_LandCommands::setTownCongregationPos },
	{ 7,   "CREATE_ABODE",                      { TypeNumber, TypeVector, TypeString, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                         &Impl_LandCommands::createAbode },
	{ 8,   "CREATE_PLANNED_ABODE",              { TypeNumber, TypeVector, TypeString, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                         &Impl_LandCommands::createPlannedAbode },
	{ 9,   "CREATE_TOWN_CENTRE",                { TypeNumber, TypeVector, TypeString, TypeNumber, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createTownCentre },
	{ 10,  "CREATE_TOWN_SPELL",                 { TypeNumber, TypeString },                                                                                          &Impl_LandCommands::createTownSpell },
	{ 11,  "CREATE_NEW_TOWN_SPELL",             { TypeNumber, TypeString },                                                                                          &Impl_LandCommands::createNewTownSpell },
	{ 12,  "CREATE_TOWN_CENTRE_SPELL_ICON",     { TypeNumber, TypeString },                                                                                          &Impl_LandCommands::createTownCentreSpellIcon },
	{ 13,  "CREATE_SPELL_ICON",                 { TypeVector, TypeString, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createSpellIcon },
	{ 14,  "CREATE_PLANNED_SPELL_ICON",         { TypeNumber, TypeVector, TypeString, TypeNumber, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createPlannedSpellIcon },
	{ 15,  "CREATE_VILLAGER",                   { TypeVector, TypeVector, TypeString },                                                                             &Impl_LandCommands::createVillager },
	{ 16,  "CREATE_TOWN_VILLAGER",              { TypeNumber, TypeVector, TypeVector, TypeNumber },                                                                &Impl_LandCommands::createTownVillager },
	{ 17,  "CREATE_SPECIAL_TOWN_VILLAGER",      { TypeNumber, TypeVector, TypeNumber, TypeNumber },                                                                &Impl_LandCommands::createSpecialTownVillager },
	{ 18,  "CREATE_VILLAGER_POS",               { TypeVector, TypeVector, TypeString, TypeNumber },                                                                &Impl_LandCommands::createVillagerPos },
	{ 19,  "CREATE_CITADEL",                    { TypeVector, TypeNumber, TypeString, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createCitadel },
	{ 20,  "CREATE_PLANNED_CITADEL",            { TypeNumber, TypeVector, TypeNumber, TypeString, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createPlannedCitadel },
	{ 21,  "CREATE_CREATURE_PEN",               { TypeVector, TypeNumber, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createCreaturePen },
	{ 22,  "CREATE_WORSHIP_SITE",               { TypeVector, TypeNumber, TypeString, TypeString, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createWorshipSite },
	{ 23,  "CREATE_PLANNED_WORSHIP_SITE",       { TypeVector, TypeNumber, TypeString, TypeString, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createPlannedWorshipSite },
	{ 24,  "CREATE_ANIMAL",                     { TypeVector, TypeNumber, TypeNumber, TypeNumber },                                                                &Impl_LandCommands::createAnimal },
	{ 25,  "CREATE_NEW_ANIMAL",                 { TypeVector, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createNewAnimal },
	{ 26,  "CREATE_FOREST",                     { TypeNumber, TypeVector },                                                                                          &Impl_LandCommands::createForest },
	{ 27,  "CREATE_TREE",                       { TypeNumber, TypeVector, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createTree },
	{ 28,  "CREATE_NEW_TREE",                   { TypeNumber, TypeVector, TypeNumber, TypeNumber, TypeFloat, TypeFloat, TypeFloat },                            &Impl_LandCommands::createNewTree },
	{ 29,  "CREATE_FIELD",                      { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::createField },
	{ 30,  "CREATE_TOWN_FIELD",                 { TypeNumber, TypeVector, TypeNumber },                                                                             &Impl_LandCommands::createTownField },
	{ 31,  "CREATE_FISH_FARM",                  { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::createFishFarm },
	{ 32,  "CREATE_TOWN_FISH_FARM",             { TypeNumber, TypeVector, TypeNumber },                                                                             &Impl_LandCommands::createTownFishFarm },
	{ 33,  "CREATE_FEATURE",                    { TypeVector, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createFeature },
	{ 34,  "CREATE_FLOWERS",                    { TypeVector, TypeNumber, TypeFloat, TypeFloat },                                                                  &Impl_LandCommands::createFlowers },
	{ 35,  "CREATE_WALL_SECTION",               { TypeVector, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createWallSection },
	{ 36,  "CREATE_PLANNED_WALL_SECTION",       { TypeVector, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createPlannedWallSection },
	{ 37,  "CREATE_PITCH",                      { TypeVector, TypeNumber, TypeNumber, TypeNumber, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createPitch },
	{ 38,  "CREATE_POT",                        { TypeVector, TypeNumber, TypeNumber, TypeNumber },                                                                &Impl_LandCommands::createPot },
	{ 39,  "CREATE_TOWN_TEMPORARY_POTS",        { TypeNumber, TypeNumber, TypeNumber },                                                                             &Impl_LandCommands::createTownTemporaryPots },
	{ 40,  "CREATE_MOBILEOBJECT",               { TypeVector, TypeNumber, TypeNumber, TypeNumber },                                                                &Impl_LandCommands::createMobileobject },
	{ 41,  "CREATE_MOBILESTATIC",               { TypeVector, TypeNumber, TypeFloat, TypeFloat },                                                                  &Impl_LandCommands::createMobilestatic },
	{ 42,  "CREATE_MOBILE_STATIC",              { TypeVector, TypeNumber, TypeFloat, TypeFloat, TypeFloat, TypeFloat, TypeFloat },                              &Impl_LandCommands::createMobileStatic },
	{ 43,  "CREATE_DEAD_TREE",                  { TypeVector, TypeString, TypeNumber, TypeFloat, TypeFloat, TypeFloat, TypeFloat },                             &Impl_LandCommands::createDeadTree },
	{ 44,  "CREATE_SCAFFOLD",                   { TypeNumber, TypeVector, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createScaffold },
	{ 45,  "COUNTRY_CHANGE",                    { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::countryChange },
	{ 46,  "HEIGHT_CHANGE",                     { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::heightChange },
	{ 47,  "CREATE_CREATURE",                   { TypeVector, TypeNumber, TypeNumber },                                                                             &Impl_LandCommands::createCreature },
	{ 48,  "CREATE_CREATURE_FROM_FILE",         { TypeString, TypeNumber, TypeVector, TypeVector },                                                                &Impl_LandCommands::createCreatureFromFile },
	{ 49,  "CREATE_FLOCK",                      { TypeNumber, TypeVector, TypeVector, TypeNumber, TypeNumber, TypeNumber },                                      &Impl_LandCommands::createFlock },
	{ 50,  "LOAD_LANDSCAPE",                    { TypeString },                                                                                                       &Impl_LandCommands::loadLandscape },
	{ 51,  "VERSION",                           { TypeFloat },                                                                                                        &Impl_LandCommands::version },
	{ 52,  "CREATE_AREA",                       { TypeVector, TypeFloat },                                                                                           &Impl_LandCommands::createArea },
	{ 53,  "START_CAMERA_POS",                  { TypeVector },                                                                                                       &Impl_LandCommands::startCameraPos },
	{ 54,  "FLY_BY_FILE",                       { TypeString },                                                                                                       &Impl_LandCommands::flyByFile },
	{ 55,  "TOWN_NEEDS_POS",                    { TypeNumber, TypeVector },                                                                                          &Impl_LandCommands::townNeedsPos },
	{ 56,  "CREATE_FURNITURE",                  { TypeVector, TypeNumber, TypeFloat },                                                                              &Impl_LandCommands::createFurniture },
	{ 57,  "CREATE_BIG_FOREST",                 { TypeVector, TypeNumber, TypeFloat, TypeFloat },                                                                  &Impl_LandCommands::createBigForest },
	{ 58,  "CREATE_NEW_BIG_FOREST",             { TypeVector, TypeNumber, TypeNumber, TypeFloat, TypeFloat },                                                     &Impl_LandCommands::createNewBigForest },
	{ 59,  "CREATE_INFLUENCE_RING",             { TypeVector, TypeNumber, TypeFloat, TypeNumber },                                                                 &Impl_LandCommands::createInfluenceRing },
	{ 60,  "CREATE_WEATHER_CLIMATE",            { TypeNumber, TypeNumber, TypeVector, TypeFloat, TypeFloat },                                                     &Impl_LandCommands::createWeatherClimate },
	{ 61,  "CREATE_WEATHER_CLIMATE_RAIN",       { TypeNumber, TypeFloat, TypeNumber, TypeNumber, TypeNumber },                                                    &Impl_LandCommands::createWeatherClimateRain },
	{ 62,  "CREATE_WEATHER_CLIMATE_TEMP",       { TypeNumber, TypeFloat, TypeFloat },                                                                               &Impl_LandCommands::createWeatherClimateTemp },
	{ 63,  "CREATE_WEATHER_CLIMATE_WIND",       { TypeNumber, TypeFloat, TypeFloat, TypeFloat },                                                                   &Impl_LandCommands::createWeatherClimateWind },
	{ 64,  "CREATE_WEATHER_STORM",              { TypeNumber, TypeVector, TypeFloat, TypeNumber, TypeVector, TypeVector, TypeVector, TypeFloat, TypeVector }, &Impl_LandCommands::createWeatherStorm },
	{ 65,  "BRUSH_SIZE",                        { TypeFloat, TypeFloat },                                                                                            &Impl_LandCommands::brushSize },
	{ 66,  "CREATE_STREAM",                     { TypeNumber },                                                                                                       &Impl_LandCommands::createStream },
	{ 67,  "CREATE_STREAM_POINT",               { TypeNumber, TypeVector },                                                                                          &Impl_LandCommands::createStreamPoint },
	{ 68,  "CREATE_WATERFALL",                  { TypeVector },                                                                                                       &Impl_LandCommands::createWaterfall },
	{ 69,  "CREATE_ARENA",                      { TypeVector, TypeFloat },                                                                                           &Impl_LandCommands::createArena },
	{ 70,  "CREATE_FOOTPATH",                   { TypeNumber },                                                                                                       &Impl_LandCommands::createFootpath },
	{ 71,  "CREATE_FOOTPATH_NODE",              { TypeNumber, TypeVector },                                                                                          &Impl_LandCommands::createFootpathNode },
	{ 72,  "LINK_FOOTPATH",                     { TypeNumber },                                                                                                       &Impl_LandCommands::linkFootpath },
	{ 73,  "CREATE_BONFIRE",                    { TypeVector, TypeFloat, TypeFloat, TypeFloat },                                                                   &Impl_LandCommands::createBonfire },
	{ 74,  "CREATE_BASE",                       { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::createBase },
	{ 75,  "CREATE_NEW_FEATURE",                { TypeVector, TypeString, TypeNumber, TypeNumber, TypeNumber },                                                   &Impl_LandCommands::createNewFeature },
	{ 76,  "SET_INTERACT_DESIRE",               { TypeFloat },                                                                                                        &Impl_LandCommands::setInteractDesire },
	{ 77,  "TOGGLE_COMPUTER_PLAYER",            { TypeString, TypeNumber },                                                                                          &Impl_LandCommands::toggleComputerPlayer },
	{ 78,  "SET_COMPUTER_PLAYER_CREATURE_LIKE", { TypeString, TypeString },                                                                                          &Impl_LandCommands::setComputerPlayerCreatureLike },
	{ 79,  "MULTIPLAYER_DEBUG",                 { TypeNumber, TypeNumber },                                                                                          &Impl_LandCommands::multiplayerDebug },
	{ 80,  "CREATE_STREET_LANTERN",             { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::createStreetLantern },
	{ 81,  "CREATE_STREET_LIGHT",               { TypeVector },                                                                                                       &Impl_LandCommands::createStreetLight },
	{ 82,  "SET_LAND_NUMBER",                   { TypeNumber },                                                                                                       &Impl_LandCommands::setLandNumber },
	{ 83,  "CREATE_ONE_SHOT_SPELL",             { TypeVector, TypeString },                                                                                          &Impl_LandCommands::createOneShotSpell },
	{ 84,  "CREATE_ONE_SHOT_SPELL_PU",          { TypeVector, TypeString },                                                                                          &Impl_LandCommands::createOneShotSpellPu },
	{ 85,  "CREATE_FIRE_FLY",                   { TypeVector },                                                                                                       &Impl_LandCommands::createFireFly },
	{ 86,  "TOWN_DESIRE_BOOST",                 { TypeNumber, TypeString, TypeFloat },                                                                              &Impl_LandCommands::townDesireBoost },
	{ 87,  "CREATE_ANIMATED_STATIC",            { TypeVector, TypeString, TypeNumber, TypeNumber },                                                                &Impl_LandCommands::createAnimatedStatic },
	{ 88,  "FIRE_FLY_SPELL_REWARD_PROB",        { TypeVector, TypeFloat },                                                                                           &Impl_LandCommands::fireFlySpellRewardProb },
	{ 89,  "CREATE_NEW_TOWN_FIELD",             { TypeNumber, TypeVector, TypeNumber, TypeFloat },                                                                 &Impl_LandCommands::createNewTownField },
	{ 90,  "CREATE_SPELL_DISPENSER",            { TypeNumber, TypeVector, TypeString, TypeString, TypeFloat, TypeFloat, TypeFloat },                            &Impl_LandCommands::createSpellDispenser },
	{ 91,  "LOAD_COMPUTER_PLAYER_PERSONALLTY",  { TypeNumber, TypeVector },                                                                                          &Impl_LandCommands::loadComputerPlayerPersonallty },
	{ 92,  "SET_COMPUTER_PLAYER_PERSONALLTY",   { TypeString, TypeVector, TypeFloat },                                                                              &Impl_LandCommands::setComputerPlayerPersonallty },
	{ 93,  "SET_GLOBAL_LAND_BALANCE",           { TypeNumber, TypeFloat },                                                                                           &Impl_LandCommands::setGlobalLandBalance },
	{ 94,  "SET_LAND_BALANCE",                  { TypeString, TypeNumber, TypeFloat },                                                                              &Impl_LandCommands::setLandBalance },
	{ 95,  "CREATE_DRINK_WAYPOINT",             { TypeVector },                                                                                                       &Impl_LandCommands::createDrinkWaypoint },
	{ 96,  "SET_TOWN_INFLUENCE_MULTIPLIER",     { TypeFloat },                                                                                                        &Impl_LandCommands::setTownInfluenceMultiplier },
	{ 97,  "SET_PLAYER_INFLUENCE_MULTIPLIER",   { TypeFloat },                                                                                                        &Impl_LandCommands::setPlayerInfluenceMultiplier },
	{ 98,  "SET_TOWN_BALANCE_BELIEF_SCALE",     { TypeNumber, TypeFloat },                                                                                           &Impl_LandCommands::setTownBalanceBeliefScale },
	{ 99,  "START_GAME_MESSAGE",                { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::startGameMessage },
	{ 100, "ADD_GAME_MESSAGE_LINE",             { TypeVector, TypeNumber },                                                                                          &Impl_LandCommands::addGameMessageLine },
	{ 101, "EDIT_LEVEL",                        {  },                                                                                                                  &Impl_LandCommands::editLevel },
	{ 102, "SET_NIGHTTIME",                     { TypeFloat, TypeFloat, TypeFloat },                                                                                &Impl_LandCommands::setNighttime },
	{ 103, "MAKE_LAST_OBJECT_ARTIFACT",         { TypeNumber, TypeString, TypeFloat },                                                                              &Impl_LandCommands::makeLastObjectArtifact },
	{ 104, "SET_LOST_TOWN_SCALE",               { TypeFloat },                                                                                                        &Impl_LandCommands::setLostTownScale },
};

}

}

//#endif