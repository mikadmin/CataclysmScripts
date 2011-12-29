/*
* Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
*
* Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
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
* Script Complete 2% (or less)
**********/

/* TODO 

*/


#include "ScriptPCH.h"
#include "firelands.h"

enum Yells
{
	SAY_AGGRO                                   = -1999971,
};

enum Spells
{
	// Blade Abilities
	SPELL_BLAZE_OF_GLORY						= 99252,
	SPELL_DECIMATION_BLADE						= 99352,
	SPELL_INFERNO_BLADE							= 99350,
};

enum Events
{
	EVENT_HIT_TARGET_WITH_BLADE = 1
};


/**** Baloroc ****/

class boss_baloroc_the_doorkeeper : public CreatureScript
{
public:
	boss_baloroc_the_doorkeeper() : CreatureScript("boss_baloroc_the_doorkeeper"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_baloroc_the_doorkeeperAI(creature);
	}

	struct boss_baloroc_the_doorkeeperAI : public BossAI
	{
		boss_baloroc_the_doorkeeperAI(Creature* c) : BossAI(c, DATA_BALOROC)
		{
			instance = me->GetInstanceScript();

			Reset();
		}

		InstanceScript* instance;
		
		void Reset()
		{
			events.Reset();
			_Reset();
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);
			summon->AI()->DoZoneInCombat();
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustReachedHome()
		{
			summons.DespawnAll();
		}

		void JustDied(Unit * /*victim*/)
		{
			summons.DespawnAll();

			_JustDied();
		}

		void EnterCombat(Unit* who)
		{
			events.ScheduleEvent(EVENT_HIT_TARGET_WITH_BLADE, 5000);
			_EnterCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim() || me->HasUnitState(UNIT_STAT_CASTING))
			{
				return;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_HIT_TARGET_WITH_BLADE:
					
					DoCastVictim(SPELL_INFERNO_BLADE);
					events.ScheduleEvent(EVENT_HIT_TARGET_WITH_BLADE, 5000);
					break;
				
				}

			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();


		}
	};
};


void AddSC_boss_baloroc_the_doorkeeper()
{
	//new boss_baloroc_the_doorkeeper();
}