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

enum Spells
{
	// Anshal

	// Nezir
	SPELL_ICE_PATCH = 93130,
	SPELL_ICE_PATCH_VISUAL = 86107,
	SPELL_ICE_PATCH_AURA = 86111,

	SPELL_PERMAFROST = 86082,
	SPELL_WIND_CHILL = 84645,
	SPELL_CHILLING_WINDS = 85578,
	SPELL_SLEET_STORM_ULTIMATE = 84644,
	
	// Rohash

};

enum Events
{
	// Anshal

	// Nezir
	EVENT_ICE_PATCH = 1,
	EVENT_PERMAFROST = 2,
	EVENT_WIND_CHILL = 3,
	EVENT_SLEET_STORM_ULTIMATE = 4,

	// Rohash
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

			creature->setPowerType(POWER_ENERGY);
		}

		InstanceScript* instance;
		EventMap events;

		void Reset()
		{
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
		boss_nezirAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = creature->GetInstanceScript();

			creature->setPowerType(POWER_ENERGY);
		}

		InstanceScript* instance;
		EventMap events;

		void Reset()
		{
			events.Reset();

			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* /*who*/)
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

			creature->setPowerType(POWER_ENERGY);
		}

		InstanceScript* instance;
		EventMap events;

		void Reset()
		{
			events.Reset();

			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* /*who*/)
		{
			//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

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
		}
	};
};

void AddSC_boss_conclave_of_wind()
{
	new boss_anshal();
	new boss_nezir();
	new boss_rohash();
}