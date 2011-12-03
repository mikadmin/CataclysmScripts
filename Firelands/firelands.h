/*
 * Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
 *
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2011 TrilliumEMU <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// by Naios

#ifndef DEF_FIRELANDS_H
#define DEF_FIRELANDS_H

#include "ObjectMgr.h"
#define FirelandsScriptName "instance_firelands"

enum creaturesIDs
{
//bosses
NPC_BETHTILAC = 52498,
NPC_RHYOLITH = 52558,
NPC_ALYSRAZAR = 52530,
NPC_SHANNOX = 53691,
NPC_BALOROC = 53494,
NPC_MAJORDOMUS = 52571, //54015 <-- maybe this entry
NPC_RAGNAROS_CATA = 52409,

//other npc's
NPC_SULFURAS = 53420, //ragnaros boss weapon
NPC_LIVING_METEOR = 53500,
NPC_MOLTEN_ELEMENTAR = 53189,

NPC_RIPLIMB = 53694, // Shannox Dogs
NPC_RAGEFACE = 53695,
NPC_SHANNOX_SPEAR = 53752, // Shannox Spear
NPC_CRYSTAL_TRAP = 53713,
NPC_CRYSTAL_PRISON = 53819,

};

enum Data
{
	// Encounter States
	DATA_BALOROC             = 0,
    DATA_SHANNOX             = 1,
    DATA_ALYSRAZAR           = 2,
    DATA_BETHTILAC           = 3,
    DATA_RHYOLITH            = 4,
    DATA_MAJORDOMUS          = 5,
    DATA_RAGNAROS            = 6,
};

enum MovePoints
{
POINT_RAGNAROS_DOWN, //end of each phase
POINT_RAGNAROS_UP, //start of each next phase
POINT_RAGNAROS_STANDUP, //only on heroic mode
POINT_SULFURAS_SMASH //target for smashes
};

enum Actions
{
ACTION_RAGNAROS_DOWN, //end of each phase
ACTION_RAGNAROS_UP, //start of each next phase
ACTION_RAGNAROS_STANDUP, //only on heroic mode
ACTION_SULFURAS_SMASH //target for smashes
};

/*enum GameObjectsIds
{
    0,
};*/

#endif
