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
* Script Complete 2% (or less)
**********/

#include "ScriptPCH.h"
#include "grim_batol.h"

enum Spells
{
	// Drahgas Spells
	SPELL_BURNING_SHADOWBOLT	= 75245,
	SPELL_BURNING_SHADOWBOLT_H	= 90915,
	SPELL_INVOCATION_OF_FLAME	= 75218,

	SPELL_TWILIGHT_PROTECTION	= 76303,

	// Valionas Spells
	SPELL_SHREDEDING_SWIPE		= 90966,
	SPELL_VALIONAS_FLAME		= 75321,
	SPELL_SHREDDING_SWIPE		= 75271,
	SPELL_SEEPING_TWILIGHT		= 75317,
	SPELL_DEVOURING_FLAMES_H	= 90950,

	// Invoking Flaming Spirits Spells
	SPELL_SUPERNOVA				= 75238,
	SPELL_SUPERNOVA_H			= 90972,
};

enum Phase
{
	PHASE_CASTER_PHASE = 1,
	PHASE_DRAGON_PHASE = 2
};

enum Events
{
	EVENT_BURNING_SHADOWBOLT = 1
};

class boss_drahga_shadowburner : public CreatureScript
{
public:
	boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_drahga_shadowburnerAI (creature);
	}

	struct boss_drahga_shadowburnerAI : public ScriptedAI
	{
		boss_drahga_shadowburnerAI(Creature* creature) : ScriptedAI(creature)
		{
			pInstance = creature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		Phase phase;
		EventMap events;

		void Reset()
		{
			events.Reset();
			phase = PHASE_CASTER_PHASE;
		}

		void EnterCombat(Unit* /*pWho*/)
		{
			events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 5000);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(phase == PHASE_CASTER_PHASE && !HealthAbovePct(30))
			{
				phase = PHASE_DRAGON_PHASE;
			}

			events.Update(diff);
			if (phase == PHASE_CASTER_PHASE)
			{

				while (uint32 eventId = events.GetEvent())
				{
					switch (eventId)
					{
					case EVENT_BURNING_SHADOWBOLT:

						if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, RAID_MODE(SPELL_BURNING_SHADOWBOLT,SPELL_BURNING_SHADOWBOLT_H));

						events.RepeatEvent(5000);
						break;

					default:
						events.PopEvent();
						break;
					}
				}
			}

			DoMeleeAttackIfReady();
		}
	};
};

class mob_valiona_gb : public CreatureScript
{
public:
	mob_valiona_gb() : CreatureScript("mob_valiona_gb") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_valiona_gbAI (creature);
	}

	struct mob_valiona_gbAI : public ScriptedAI
	{
		mob_valiona_gbAI(Creature* creature) : ScriptedAI(creature)
		{
			pInstance = creature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		EventMap events;

		void Reset()
		{
			events.Reset();
			me->SetReactState(REACT_PASSIVE);
			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* /*pWho*/) {}

		void UpdateAI(const uint32 Diff)
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}
	};
};

class mob_invocation_of_flame : public CreatureScript
{
public:
	mob_invocation_of_flame() : CreatureScript("mob_invocation_of_flame") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_invocation_of_flameAI (creature);
	}

	struct mob_invocation_of_flameAI : public ScriptedAI
	{
		mob_invocation_of_flameAI(Creature* creature) : ScriptedAI(creature), pTarget(NULL)
		{
			me->SetReactState(REACT_PASSIVE);
		}

		Unit* pTarget;

		void Reset() {}

		void EnterCombat(Unit* /*pWho*/)
		{

			if (Unit *pRandomTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
			{
				pTarget = pRandomTarget;
				me->GetMotionMaster()->MoveChase(pTarget);

			}else
				me -> DisappearAndDie(); // Prevents crashes
		}

		void UpdateAI(const uint32 Diff)
		{
			if(pTarget == NULL)
				return;

			if(me->GetDistance(pTarget) < 1 )
			{
				DoCast(pTarget,  RAID_MODE(SPELL_SUPERNOVA,	SPELL_SUPERNOVA_H));
				me -> DisappearAndDie();
			}
		}
	};
};

void AddSC_boss_drahga_shadowburner()
{
	new boss_drahga_shadowburner();
	new mob_valiona_gb();
	new mob_invocation_of_flame();
}