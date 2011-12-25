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
* Script Complete 60% (or less)
**********/

#include "ScriptPCH.h"
#include "grim_batol.h"
#include "Vehicle.h"

// ToDo Move this hardocoded Yells to the DB
#define SAY_AGGRO "I will burn you from the inside out!"
#define SAY_SUMMON "BY FIRE BE... BURNED!"
#define SAY_JUMP_DOWN "Dragon, you will do as I command! Catch me!"
#define	SAY_SUMMON_2 "INCINERATE THEM, MINIONS!"
#define SAY_DEAD "Valiona, finish them! Avenge me!"

enum Spells
{
	// Drahgas Spells
	SPELL_BURNING_SHADOWBOLT	= 75245,
	SPELL_BURNING_SHADOWBOLT_H	= 90915,
	SPELL_INVOCATION_OF_FLAME	= 75218,

	SPELL_TWILIGHT_PROTECTION	= 76303,

	// Valionas Spells
	SPELL_VALIONAS_FLAME		= 75321,
	SPELL_SHREDDING_SWIPE		= 75271,
	SPELL_SEEPING_TWILIGHT		= 75317,
	SPELL_DEVOURING_FLAMES_H	= 90950,

	// Invoked Flame Spirits Spells
	SPELL_SUPERNOVA				= 75238,
	SPELL_SUPERNOVA_H			= 90972,
};

enum Phase
{
	PHASE_CASTER_PHASE = 1,
	PHASE_DRAGON_PHASE = 2,
	PHASE_FINAL_PHASE = 3,
};

enum Events
{
	EVENT_BURNING_SHADOWBOLT			= 1,
	EVENT_SUMMON_INVOKED_FLAME_SPIRIT	= 2,

	EVENT_VALIONAS_FLAME				= 3,
	EVENT_SHREDDING_SWIPE				= 4,		
	EVENT_SEEPING_TWILIGHT				= 5,		
};

enum Actions
{
	ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP	= 1,
	ACTION_VALIONA_SHOULD_FLY_AWAY			= 2,
};

enum Points
{
	POINT_VALIONA_FLY_IN_THE_AIR	= 1,
	POINT_VALIONA_LAND				= 2,
	POINT_VALIONA_FLY_AWAY			= 3,

	POINT_DRAHGA_GO_TO_THE_LAVA		= 4,
};

Position const position[4] =
{
	{-400.613f, -671.578f, 265.896f, 0.102f},	// Drahga Point from who he jump down
	{-388.189f, -668.078f, 280.316f, 3.470f},	// Valionas Way to the Platform
	{-435.54f, -695.072f, 280.316f, 3.4010f},
	{-435.54f, -695.072f, 268.687f, 3.4010f},	// Valiona first land Position
};

class boss_drahga_shadowburner : public CreatureScript
{
public:
	boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_drahga_shadowburnerAI (creature);
	}

	struct boss_drahga_shadowburnerAI : public ScriptedAI
	{
		boss_drahga_shadowburnerAI(Creature* creature) : ScriptedAI(creature), summons(creature), pValiona(NULL)
		{
			pInstance = creature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		Phase phase;
		EventMap events;
		SummonList summons;

		Creature* pValiona;

		void Reset()
		{
			me->GetMotionMaster()->Clear();
			events.Reset();
			summons.DespawnAll();
			phase = PHASE_CASTER_PHASE;

			if(pValiona == NULL)
				pValiona = me->FindNearestCreature(NPC_VALIONA,1000.0f, true);
		}

		void EnterCombat(Unit* /*pWho*/)
		{
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);

			if(pValiona == NULL)
				pValiona = me->FindNearestCreature(NPC_VALIONA,1000.0f, true);

			me->GetMotionMaster()->Clear();
				me->GetMotionMaster()->MoveChase(me->getVictim());

			events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 4000);
			events.ScheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT, 10000);
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);

			if(me->isInCombat())
				summon->AI()->DoZoneInCombat();
		}

		void JustDied(Unit * /*victim*/)
		{
			me->MonsterYell(SAY_DEAD, LANG_UNIVERSAL, NULL);
			summons.DespawnAll();
			pValiona -> DisappearAndDie();
		}

		void MovementInform(uint32 type, uint32 id)
		{
			if (type == POINT_MOTION_TYPE)
			{
				switch (id)
				{
				case POINT_DRAHGA_GO_TO_THE_LAVA:

					me->MonsterYell(SAY_JUMP_DOWN, LANG_UNIVERSAL, NULL);

					pValiona->GetAI()->DoAction(ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP);
					me->SetSpeed(MOVE_RUN, 1.0f);
					me->GetMotionMaster()->Clear();
					me->JumpTo(pValiona,2);
					break;

				default:
					break;
				}
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(phase == PHASE_CASTER_PHASE && !HealthAbovePct(30))
			{
				phase = PHASE_DRAGON_PHASE;
				me->SetSpeed(MOVE_RUN, 1.5f);
				me->SetReactState(REACT_PASSIVE);
				DoCast(me,SPELL_TWILIGHT_PROTECTION);
				events.Reset(); // He Should not cast while he is flying
				me->GetMotionMaster()->MovePoint(POINT_DRAHGA_GO_TO_THE_LAVA, position[0]);
			}

			events.Update(diff);

			while (uint32 eventId = events.GetEvent())
			{
				switch (eventId)
				{
				case EVENT_BURNING_SHADOWBOLT:
					
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
						DoCast(pTarget, RAID_MODE(SPELL_BURNING_SHADOWBOLT,SPELL_BURNING_SHADOWBOLT_H));

					events.RepeatEvent(4000);
					break;
				case EVENT_SUMMON_INVOKED_FLAME_SPIRIT:
					
					me->MonsterYell(SAY_SUMMON, LANG_UNIVERSAL, NULL);

					//me->SummonCreature(NPC_INVOKED_FLAMING_SPIRIT,-423.0f, -700.0f, 269.0f,0,TEMPSUMMON_CORPSE_DESPAWN);

					events.RepeatEvent(10000);
					break;

				default:
					events.PopEvent();
					break;
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
		mob_valiona_gbAI(Creature* creature) : ScriptedAI(creature), vehicle(creature->GetVehicleKit()), summons(creature), pDragah(NULL)
		{
			pInstance = creature->GetInstanceScript();
			me->SetSpeed(MOVE_FLIGHT,3.0f, true);
			me->SetSpeed(MOVE_RUN, 3.0f, true);
		}

		InstanceScript* pInstance;
		EventMap events;
		Vehicle* vehicle;
		uint8 currentWaypoint;
		SummonList summons;
		Creature* pDragah;

		void Reset()
		{
			me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
			me->SendMovementFlagUpdate();
			me->SetFlying(true);
			summons.DespawnAll();
			events.Reset();
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* /*pWho*/) {}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);

			if(me->isInCombat())
				summon->AI()->DoZoneInCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me-> HasUnitState(UNIT_STAT_CASTING))
				return;

			events.Update(diff);

			while (uint32 eventId = events.GetEvent())
			{
				switch (eventId)
				{
				case EVENT_VALIONAS_FLAME:
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
						DoCast(pTarget, SPELL_VALIONAS_FLAME);
					events.RepeatEvent(urand(15000,25000));
					break;

				case EVENT_SHREDDING_SWIPE:
					DoCastVictim(SPELL_SHREDDING_SWIPE);
					events.RepeatEvent(urand(21000,30000));
					break;

				default:
					events.PopEvent();
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

		void DoAction(const int32 action)
		{
			switch(action)
			{
			case ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP:
				DoZoneInCombat();
				currentWaypoint = 1;
				me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
				me->GetMotionMaster()->MovePoint(POINT_VALIONA_FLY_IN_THE_AIR, position[1]);
				break;

			case ACTION_VALIONA_SHOULD_FLY_AWAY:
				events.Reset();
				me->RemoveAllAuras();
				summons.DespawnAll();
				break;

			default:
				break;
			}
		}


		void MovementInform(uint32 type, uint32 id)
		{
			if (type != POINT_MOTION_TYPE)
				return;

			switch (id)
			{
			case POINT_VALIONA_FLY_IN_THE_AIR:
				currentWaypoint++;

				if(currentWaypoint < 3) // You can extend the Waypoints by yourself if you want
				{
					me->GetMotionMaster()->MovePoint(POINT_VALIONA_FLY_IN_THE_AIR, position[currentWaypoint]);
				}else
					me->GetMotionMaster()->MovePoint(POINT_VALIONA_LAND, position[3]);

				break;

			case POINT_VALIONA_LAND:

				me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
				me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
				me->SendMovementFlagUpdate();
				me->SetFlying(false);
				
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->SetReactState(REACT_AGGRESSIVE);
				
				me->GetMotionMaster()->Clear();
				me->GetMotionMaster()->MoveChase(me->getVictim());

				events.ScheduleEvent(EVENT_VALIONAS_FLAME, urand(4000,7000));
				events.ScheduleEvent(EVENT_SHREDDING_SWIPE, urand(10000,13000));

				break;

			default:
				break;
			}
		}
	};
};

class mob_invoked_flame_spirit : public CreatureScript
{
public:
	mob_invoked_flame_spirit() : CreatureScript("mob_invoked_flame_spirit") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_invoked_flame_spiritAI (creature);
	}

	struct mob_invoked_flame_spiritAI : public ScriptedAI
	{
		mob_invoked_flame_spiritAI(Creature* creature) : ScriptedAI(creature), pTarget(NULL)
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
				me->DisappearAndDie(); // Prevents crashes
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
	//new mob_invoked_flame_spirit();
}