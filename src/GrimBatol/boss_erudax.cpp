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
* Spell & Definitions by Dreadii
* Script Complete 20% (or less)
**********/

#include "ScriptPCH.h"

enum Spells
{
	//Erudax

	SPELL_ENFEEBLING_BLOW	= 75789,


	// OLD

	SPELL_PLAGUE         = 82622,    //seuche der zeitalter
	SPELL_ORKAN          = 75664,    //schattenorkan
	SPELL_SPAWN          = 75704,    //gesichtslosen beschwören
	//Faceless curruptor
	SPELL_CORRUPTION     = 75520,
	SPELL_UMBRALE        = 75763,
	SPELL_SIPHON         = 75755,
};

enum Yells
{
	SAY_AGGRO            = -1800200,
	SAY_DEATH            = -1800201,
	SAY_SUMMON           = -1800201,
};

enum Events
{
	EVENT_ENFEEBLING_BLOW	= 1,
};

const Position positions[3] =
{
	{-0.0f, -0.0f, 0.0f, 0.0f}, // First Add Spawn Location
	{-0.0f, -0.0f, 0.0f, 0.0f},	// Second Add Spawn Location
	{-0.0f, -0.0f, 0.0f, 0.0f}, // Egg Location
};


class boss_erudax: public CreatureScript
{
public: 
	boss_erudax() : CreatureScript("boss_erudax") { } 

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_erudaxAI (creature);
	}

	struct boss_erudaxAI : public ScriptedAI
	{
		boss_erudaxAI(Creature* pCreature) : ScriptedAI(pCreature), Summons(me)
		{
			pInstance = pCreature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		EventMap events;
		SummonList Summons;

		void Reset()
		{
			events.Reset();
		}

		void EnterCombat(Unit* /*who*/) 
		{
			events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, 5000);

			DoScriptText(SAY_AGGRO, me);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_ENFEEBLING_BLOW:
					DoCastVictim(SPELL_ENFEEBLING_BLOW);
					events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, 20000);
					break;

				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

		void JustDied(Unit* /*killer*/)
		{
			DoScriptText(SAY_DEATH, me);
		}

		void JustSummoned(Creature* summon)
		{
			/*pSummoned->SetInCombatWithZone();
			if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
			pSummoned->AI()->AttackStart(pTarget);
			*/
			summon->setActive(true);

			Summons.Summon(summon);
		}

		void SummonedCreatureDespawn(Creature* summon)
		{
			Summons.Despawn(summon);
		}
	};
};


class mob_faceless : public CreatureScript
{
public:
	mob_faceless() : CreatureScript("mob_faceless") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_facelessAI (creature);
	}

	struct mob_facelessAI : public ScriptedAI
	{
		mob_facelessAI(Creature* creature) : ScriptedAI(creature), pTarget(NULL) {}

		Unit* pTarget;

		EventMap events;

		void IsSummonedBy(Unit* summoner)
		{
			DoZoneInCombat();

			me->GetMotionMaster()->MoveChase(GetPlayerAtMinimumRange(1.0f));

			me->SetReactState(REACT_PASSIVE);

			/*			
			//faceless curruptor
			events.ScheduleEvent(EVENT_CORRUPTION, 30000);
			events.ScheduleEvent(EVENT_UMBRALE, 30000);
			events.ScheduleEvent(EVENT_SIPHON, 30000);
			*/

		}

		void UpdateAI(const uint32 Diff)
		{	
			if (!UpdateVictim())
				return;

		}
	};
};
void AddSC_boss_erudax() 
{
	new boss_erudax();
	new mob_faceless();
}