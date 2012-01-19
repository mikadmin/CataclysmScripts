/*
* Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
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
* Script Coded by Naios (2012)
* Script is 30% Complete (or less)
**********/

#include "throne_of_the_four_winds.h"

enum Spells
{
	// Anshal
	SPELL_SOOTHING__BREEZE = 86205,
	SPELL_SOOTHING_BREEZE_VISUAL = 86208,

	SPELL_WITHERING_WIND = 85576,

	// Nezir
	SPELL_ICE_PATCH = 93130,
	SPELL_ICE_PATCH_VISUAL = 86107,
	SPELL_ICE_PATCH_AURA = 86111,

	SPELL_PERMAFROST = 86082,
	SPELL_WIND_CHILL = 84645,
	SPELL_CHILLING_WINDS = 85578,
	SPELL_SLEET_STORM_ULTIMATE = 84644,
	
	// Rohash
	SPELL_SLICING_GALE = 86182,

	SPELL_WIND_BLAST = 86193,
	SPELL_WIND_BLAST_EFFECT = 85483,

	SPELL_HURRICANE_ULTIMATE = 84643,

	SPELL_DEAFING_WINDS = 85573,
};

enum Events
{
	// Anshal

	// Nezir
	EVENT_ICE_PATCH = 1,
	EVENT_PERMAFROST,
	EVENT_WIND_CHILL,
	EVENT_SLEET_STORM_ULTIMATE,

	// Rohash
	EVENT_SLICING_GALE,
	EVENT_WIND_BLAST,
	EVENT_HURRICANE,
};

enum Actions
{

};

class boss_anshal : public CreatureScript
{
public:
	boss_anshal() : CreatureScript("boss_anshal") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_anshalAI (creature);
	}

	struct boss_anshalAI : public ScriptedAI
	{
		boss_anshalAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = creature->GetInstanceScript();

			creature->RemoveFlag(UNIT_FIELD_FLAGS_2,UNIT_FLAG2_REGENERATE_POWER);

			creature->setPowerType(POWER_ENERGY);
		}

		InstanceScript* instance;
		EventMap events;

		void Reset()
		{
			me->SetPower(POWER_ENERGY,0);
			events.Reset();
			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* who)
		{

			



			//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(!( SelectTarget(SELECT_TARGET_NEAREST, 0, 10, true) && me->HasAura(SPELL_WITHERING_WIND)))
			{
				DoCast(me, SPELL_WITHERING_WIND, true);

			}else if (me->HasAura(SPELL_WITHERING_WIND))
				me->RemoveAura(SPELL_WITHERING_WIND);

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				/*switch (eventId)
				{

				case EVENT_TEST:
				DoCastVictim(SPELL_ENFEEBLING_BLOW);
				events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, urand(19000,24000));
				break;

				default:
				break;
				}*/
			}		

			DoMeleeAttackIfReady();
		}
	};
};

class boss_nezir : public CreatureScript
{
public:
	boss_nezir() : CreatureScript("boss_nezir") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_nezirAI (creature);
	}

	struct boss_nezirAI : public ScriptedAI
	{
		boss_nezirAI(Creature* creature) : ScriptedAI(creature), IsEncounterInCombat(false)
		{
			instance = creature->GetInstanceScript();
						
			creature->RemoveFlag(UNIT_FIELD_FLAGS_2,UNIT_FLAG2_REGENERATE_POWER);

			creature->setPowerType(POWER_ENERGY);
		}

		InstanceScript* instance;
		EventMap events;

		bool IsEncounterInCombat;

		void Reset()
		{
			me->SetPower(POWER_ENERGY,0);
			events.Reset();
			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* who)
		{
			events.ScheduleEvent(EVENT_ICE_PATCH, urand(10000,12000));
			events.ScheduleEvent(EVENT_PERMAFROST, urand(20000,23000));
			events.ScheduleEvent(EVENT_WIND_CHILL, 15000);
			events.ScheduleEvent(EVENT_SLEET_STORM_ULTIMATE, 30000);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(!( SelectTarget(SELECT_TARGET_NEAREST, 0, 10, true) && me->HasAura(SPELL_CHILLING_WINDS)))
			{
				DoCast(me, SPELL_CHILLING_WINDS, true);

			}else if (me->HasAura(SPELL_CHILLING_WINDS))
				me->RemoveAura(SPELL_CHILLING_WINDS);

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_ICE_PATCH:
					if(Unit * target = SelectTarget(SELECT_TARGET_RANDOM,0 ,10.0f,true))
						DoCast(target,SPELL_ICE_PATCH);

					events.ScheduleEvent(EVENT_ICE_PATCH, urand(10000,12000));
					break;

				case EVENT_PERMAFROST:
					DoCastVictim(SPELL_PERMAFROST);

					events.ScheduleEvent(EVENT_PERMAFROST, urand(20000,23000));
					break;

				case EVENT_WIND_CHILL:
					DoCastAOE(SPELL_WIND_CHILL);

					events.ScheduleEvent(EVENT_WIND_CHILL, 15000);
					break;

				case EVENT_SLEET_STORM_ULTIMATE:
					DoCastVictim(SPELL_SLEET_STORM_ULTIMATE);

					events.ScheduleEvent(EVENT_SLEET_STORM_ULTIMATE, 60000);
					break;

				default:
					break;
				}
			}		

			DoMeleeAttackIfReady();
		}
	};
};

class boss_rohash : public CreatureScript
{
public:
	boss_rohash() : CreatureScript("boss_rohash") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_rohashAI (creature);
	}

	struct boss_rohashAI : public ScriptedAI
	{
		boss_rohashAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = creature->GetInstanceScript();

			creature->RemoveFlag(UNIT_FIELD_FLAGS_2,UNIT_FLAG2_REGENERATE_POWER);

			creature->setPowerType(POWER_ENERGY);
		}
		
		InstanceScript* instance;
		EventMap events;
		uint32 regenPower;

		bool IsCastingWindBlast;

		void Reset()
		{
			IsCastingWindBlast = false;
			me->SetPower(POWER_ENERGY,0);
			events.Reset();
			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* who)
		{
			events.ScheduleEvent(EVENT_SLICING_GALE, 10000);
			events.ScheduleEvent(EVENT_WIND_BLAST, 30000);
			events.ScheduleEvent(EVENT_HURRICANE, 20000);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

 			if(!( SelectTarget(SELECT_TARGET_NEAREST, 0, 10, true) && me->HasAura(SPELL_DEAFING_WINDS)))
			{
				DoCast(me, SPELL_DEAFING_WINDS, true);

			}else if (me->HasAura(SPELL_DEAFING_WINDS))
				me->RemoveAura(SPELL_DEAFING_WINDS);


			if(IsCastingWindBlast)
			{
				IsCastingWindBlast=false;
				DoCastAOE(SPELL_WIND_BLAST_EFFECT);
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_WIND_BLAST:
					DoCastAOE(SPELL_WIND_BLAST);
					IsCastingWindBlast = true;
					events.ScheduleEvent(EVENT_WIND_BLAST, 30000); // 60s cd
				break;

				case EVENT_SLICING_GALE:
					DoCastVictim(SPELL_SLICING_GALE);
					events.ScheduleEvent(EVENT_SLICING_GALE, 10000);
				break;

				case EVENT_HURRICANE:
					DoCastAOE(SPELL_HURRICANE_ULTIMATE);
					events.ScheduleEvent(EVENT_HURRICANE, 45000);
				break;

				default:
				break;

				}
			}		
		}
	};
};

void AddSC_boss_conclave_of_wind()
{
	new boss_anshal();
	new boss_nezir();
	new boss_rohash();
}