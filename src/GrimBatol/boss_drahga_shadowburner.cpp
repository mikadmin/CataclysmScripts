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
* Script Complete 35% (or less)
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
	EVENT_BURNING_SHADOWBOLT = 1,
	EVENT_SUMMON_INVOKED_FLAME_SPIRIT = 2,
};

enum Actions
{
	ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP = 1,
	ACTION_VALIONA_SHOULD_FLY_AWAY = 2,
};

enum Points
{
	POINT_VALIONA_FLY_IN_THE_AIR	= 1,
	POINT_VALIONA_LAND				= 2,
	POINT_VALIONA_FLY_AWAY			= 3,

	POINT_DRAHGA_GO_TO_THE_LAVA		= 4,
};

enum Waypoints
{
	WP_VALIONA_FLY_TO_THE_BASE = 66233040,
};

Position const position[8] =
{
	{-400.613f, -671.578f, 265.896f, 0.102f},	// Drahga Point from who he jump down
	{-435.54f, -695.072f, 268.687f, 3.401f},	// Valiona first land Position
	{-374.315f ,-666.989f ,246.831f,0.0f},		// Valionas Way to the Platform
	{-374.315f ,-666.989f ,267.551f,0.0f},
	{-381.495f ,-667.637f ,280.122f,0.0f},
	{-396.57f ,-672.039f ,280.311f,0.0f},
	{-411.469f ,-679.817f ,279.501f,0.0f},
	{-429.773f ,-692.022f ,277.383f,0.0f},
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
			events.Reset();
			summons.DespawnAll();
			phase = PHASE_CASTER_PHASE;

			if(pValiona == NULL)
				pValiona = me->FindNearestCreature(NPC_VALIONA,1000.0f, true);
		}

		void EnterCombat(Unit* /*pWho*/)
		{
			if(pValiona == NULL)
				pValiona = me->FindNearestCreature(NPC_VALIONA,1000.0f, true);
			
			if(pValiona == NULL)
				me->MonsterYell("pValiona == NULL", LANG_UNIVERSAL, NULL);

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

						me->MonsterYell("Have Reached Point", LANG_UNIVERSAL, NULL);

						me->GetMotionMaster()->Clear();
						me->GetMotionMaster()->MoveChase(me->getVictim());

						/*pValiona->GetAI()->DoAction(ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP);
						me->GetMotionMaster()->Clear(false);
						me->JumpTo(pValiona,5);
						me->Mount(pValiona->GetGUID());*/
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

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_BURNING_SHADOWBOLT:

					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
						DoCast(pTarget, RAID_MODE(SPELL_BURNING_SHADOWBOLT,SPELL_BURNING_SHADOWBOLT_H));

					events.RepeatEvent(2500);
					break;
				case EVENT_SUMMON_INVOKED_FLAME_SPIRIT:

					//me->SummonCreature(NPC_INVOKED_FLAMING_SPIRIT,-423.0f, -700.0f, 269.0f,0,TEMPSUMMON_CORPSE_DESPAWN);

					events.RepeatEvent(10000);
					break;

				default:
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
		mob_valiona_gbAI(Creature* creature) : ScriptedAI(creature), vehicle(creature->GetVehicleKit())
		{
			pInstance = creature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		EventMap events;
		Vehicle* vehicle;

		void Reset()
		{
			events.Reset();
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->GetMotionMaster()->MoveTargetedHome();
		}

		void EnterCombat(Unit* /*pWho*/) {}

		void UpdateAI(const uint32 Diff)
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DoAction(const int32 action)
		{
			switch(action)
			{
			case ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP:
				DoZoneInCombat();
				me->SetSpeed(MOVE_FLIGHT, 3.0f);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->SetReactState(REACT_AGGRESSIVE);
				me->GetMotionMaster()->MovePath(WP_VALIONA_FLY_TO_THE_BASE,false);
				break;
			case ACTION_VALIONA_SHOULD_FLY_AWAY:
				break;
			}
		}


		void MovementInform(uint32 type, uint32 id)
		{
			if (type == POINT_MOTION_TYPE)
			{
				switch (id)
				{
				case POINT_VALIONA_FLY_IN_THE_AIR:


					break;

				case POINT_VALIONA_LAND:
					me->GetMotionMaster()->Clear(false);
					me->GetMotionMaster()->MoveChase(me->getVictim());
					break;
				}
			}

			/*if (type == WAYPOINT_MOTION_TYPE)
			{
				switch (id)
				{
					case 8:
						me->GetMotionMaster()->MoveLand(POINT_VALIONA_LAND,position[1],1.0f);
					break;
				}
			}*/
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
	//new mob_invoked_flame_spirit();
}