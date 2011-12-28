/*
* Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
*
* Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
*
* Copyright (C) 2011 ArkCORE <http://www.arkania.net/>
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

/**********
* Script Coded by Naios
* Script Complete 10% (or less)
**********/

#include "ScriptPCH.h"
#include "grim_batol.h"

#define SAY_AGGRO "You not get through defenses!"
#define SAY_AGGRO1 "You not get through defenses!"
#define SAY_AGGRO2 "Throngus use your corpse on body. Somewhere..."
#define SAY_AGGRO3 "Oh, this gonna HURT!"
#define SAY_DIED "Death... Good choice. Not best choice maybe, but better than fail and live."

enum Spells
{
	SPELL_BOUCLIER = 90830, // Bouclier incendiaire

	SPELL_PHALANGE = 74908, // Phalange individuelle
	SPELL_ARDENTE = 90764, // Flammes ardentes // Sengende Flammen
	SPELL_ROSSER = 47480, // Rosser
	SPELL_LAME = 74981, // Double-lames // Doppelklingen
	SPELL_RUGIS = 74976, // Rugissement désorientant // Desorientierendes Gebrüll
	SPELL_GERBE = 90754, // Gerbe de lave // 
	SPELL_ENCOMBRE = 75007, // Encombré // Beeinträchtigt
	SPELL_HEURT = 75056, // Heurt d’empalement // Pfählerndes Schmettern


	// Misc
	SPELL_MIGHTY_STOMP = 74984, // Stomp
	SPELL_PICK_WEAPON = 75000, // He switches his weapon

	// Shield Phase
	SPELL_FLAMING_ARROW = 45101,
	SPELL_PERSONAL_PHALANX = 74908,
	SPELL_FLAMING_SHIELD = 90819, // Wowhead is wrong

	// Swords Phase
	SPELL_DUAL_BLADES_BUFF = 74981,
	SPELL_TRASH_BUFF = 47480,

};

enum Events
{
	// General
	EVENT_PICK_WEAPON = 1,
	EVENT_STOMP = 2,

	// Shield Phase
	EVENT_PERSONAL_PHALANX = 3,

};

enum Weapon
{
	WEAPON_NON		= 0,
	WEAPON_CHOOSING	= 1,
	WEAPON_SHIELD	= 2,
	WEAPON_SWORDS	= 3,
	WEAPON_MACE		= 4,
};

enum EquipmentIds
{
	EQUIPMENT_ID_SHIELD	= 40400,  // Not Blizzlike
	EQUIPMENT_ID_SWORDS	= 65094,  // Not Blizzlike
	EQUIPMENT_ID_MACE	= 65090,  // Not Blizzlike
};

class boss_forgemaster_throngus: public CreatureScript
{
public: 
	boss_forgemaster_throngus() : CreatureScript("boss_forgemaster_throngus") { } 

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_forgemaster_throngusAI (pCreature);
	}

	struct boss_forgemaster_throngusAI : public ScriptedAI
	{
		boss_forgemaster_throngusAI(Creature *c) : ScriptedAI(c) {}

		EventMap events;

		uint32 currentWaepon;
		uint8 phases [3];

		void EnterCombat(Unit* /*who*/) 
		{
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);

			phases[0] = 0;
			phases[1] = 0;
			phases[2] = 0;
		}

		void JustDied(Unit* /*killer*/)
		{
			me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
		}

		void Reset()
		{
			currentWaepon = WEAPON_NON;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(currentWaepon == WEAPON_NON)
			{
				ResetWeapon();
				currentWaepon = WEAPON_CHOOSING;

				DoCast(SPELL_PICK_WEAPON);

				return;
			}

			if(currentWaepon == WEAPON_CHOOSING)
			{
				// Chooses a new Weapon
				IntializeWeapon();

				return;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch(eventId)
				{
				case EVENT_PICK_WEAPON:
					// It is only need to set the Weapon to WEAPON_NON to switch the Weapon
					currentWaepon = WEAPON_NON;

					events.ScheduleEvent(EVENT_PICK_WEAPON, 50000);
					break;

				case EVENT_PERSONAL_PHALANX:
					if (Unit* tempTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
						DoCast(tempTarget, SPELL_PERSONAL_PHALANX);

					events.ScheduleEvent(EVENT_PERSONAL_PHALANX, 10000);
					break;
				}
			}
			DoMeleeAttackIfReady();

		}

	private:
		inline void IntializeWeapon()
		{ // Intialize next Phase

			// Choose Weapon
			currentWaepon = urand(2,4);

			// If you want to test Phases you can overwrite the rand value here
			currentWaepon = WEAPON_MACE;

			switch(currentWaepon)
			{
			case WEAPON_SHIELD:

				SetEquipmentSlots(false, 0, EQUIPMENT_ID_SHIELD,0);

				if(me->GetMap()->IsHeroic())
					DoCast(me, SPELL_FLAMING_SHIELD, true);

				events.ScheduleEvent(EVENT_PERSONAL_PHALANX, 10000);

				break;

			case WEAPON_SWORDS:

				SetEquipmentSlots(false, EQUIPMENT_ID_SWORDS, EQUIPMENT_ID_SWORDS,0);

				break;

			case WEAPON_MACE:

				SetEquipmentSlots(false, EQUIPMENT_ID_MACE, 0,0);

				break;
			}

		}

		inline void ResetWeapon()
		{ // Resets last Phase

			events.Reset();

			// Remove Auras spezified to the Phases
			// Shield Phase
			me->RemoveAura(SPELL_FLAMING_SHIELD);
			me->RemoveAura(SPELL_PERSONAL_PHALANX);

			// Swords Phase

			// Mace Phase
		}
	};
};

void AddSC_boss_forgemaster_throngus() 
{
	new boss_forgemaster_throngus();
}