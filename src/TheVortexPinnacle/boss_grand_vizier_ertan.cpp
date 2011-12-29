#include "ScriptPCH.h"
#include "the_vortex_pinnacle.h"

#define SAY_AGGRO "Filthy beasts! Your presence in Skywall will not be tolerated!"
#define SAY_RANDOM "Ravaged!"

#define WAYPOINTS 10500640

enum Spells
{
	SPELL_N_BOLT                     = 86331, // Lightning Bolt
	SPELL_H_BOLT                     = 93990, // Lightning Bolt HEROIC
	SPELL_H_TEMP                     = 86340, // TEMP HEROIC
	SPELL_BUFF                       = 86292,
	SPELL_SUMMON_TEMPEST			 = 86340, // Summons Lurking Tempest
};

enum Events
{
	EVENT_BOLT = 1,
	EVENT_BUFF = 2,
	EVENT_SAY  = 3,
	EVENTS_CHECK_VICTIM_IS_OUT_OF_RANGE = 4,
};

enum Actions
{
	ACTION_TEMPEST_MOVE		= 1,
	ACTION_TEMPEST_MOVE_IN	= 2,
	ACTION_TEMPEST_MOVE_OUT	= 3,
};

Position const LurkingTempestSummonPos[8] =
{
	{-737.272f, -13.6125f, 635.671f, 0},
	{-744.922f, 3.77353f, 635.671f, 0},
	{-720.0269f, 4.153f, 635.671f, 0},
	{-701.75f, -13.8398f, 635.671f, 0},
	{-737.557f, 21.6678f, 635.671f, 0},
	{-720.006f, 29.5005f, 635.671f, 0},
	{-702.245f, 21.8256f, 635.671f, 0},
	{-694.691f, 4.30964f, 635.671f, 0}
};

class boss_vizir_ertan: public CreatureScript
{
public:
	boss_vizir_ertan() : CreatureScript("boss_vizir_ertan") { }

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_vizir_ertanAI(pCreature);
	}

	struct boss_vizir_ertanAI : public ScriptedAI
	{
		boss_vizir_ertanAI(Creature * pCreature) : ScriptedAI(pCreature), summons(me)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
		}

		InstanceScript* pInstance;
		EventMap events;
		SummonList summons;
		
		void Reset()
		{
			events.Reset();
			summons.DespawnAll();
		}

		void EnterCombat(Unit * /*who*/)
		{
			me->MonsterYell(SAY_AGGRO, 0, 0);

			if (true /*me->GetMap()->IsHeroic()*/) 
			{
				DoCast(me,SPELL_H_TEMP);
			}

			if(me->GetMap()->IsHeroic())
			{
				for(uint8 i=0; i <= 7; i++)
				{
					Creature * LurkingTempest = me->SummonCreature(NPC_LURKING_TEMPEST, LurkingTempestSummonPos[i], TEMPSUMMON_DEAD_DESPAWN);
					LurkingTempest->GetAI()->SetData(DATA_LURKING_TEMPEST_NO, i);

					//LurkingTempestList[i] = LurkingTempest;
					//me->MonsterYell("Summoned", 0, 0);
				}

				summons.DoAction(0);
			}

			EnterPhaseGround();
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);
			summon->AI()->DoZoneInCombat();
		}

		void EnterPhaseGround()
		{
			events.ScheduleEvent(EVENT_SAY, 60000);
			events.ScheduleEvent(EVENT_BUFF, 90000);
			events.ScheduleEvent(EVENT_BOLT, 5000);
			events.ScheduleEvent(EVENTS_CHECK_VICTIM_IS_OUT_OF_RANGE, 7000);
		}

		void JustDied()
		{
			//summons.DespawnAll();

			DespawnCreatures(NPC_LURKING_TEMPEST);

			//Creature * Slipstream = me->SummonCreature(NPC_SLIPSTREAM, -775.51f, -70.93f, 640.31f, 1.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);
			//Slipstream->SetUInt32Value(UNIT_NPC_FLAGS,UNIT_NPC_FLAG_GOSSIP);

			Map::PlayerList const &PlList = me->GetMap()->GetPlayers();

			if (PlList.isEmpty())
				return;

			for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
				if (Player* player = i->getSource())
					player->ModifyCurrency(395, DUNGEON_MODE(3000, 7000));
		}


		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch(eventId)
				{
				case EVENT_SAY:
					me->MonsterYell(SAY_RANDOM, 0, 0);
					events.ScheduleEvent(EVENT_SAY, 60000);
					break;
				case EVENT_BUFF:
					DoCast(me, SPELL_BUFF);
					events.ScheduleEvent(EVENT_BUFF, 90000);
					break;
				case EVENT_BOLT:
					DoCast(DUNGEON_MODE(SPELL_N_BOLT,SPELL_H_BOLT));
					events.ScheduleEvent(EVENT_BOLT, 5000);
					break;
				case EVENTS_CHECK_VICTIM_IS_OUT_OF_RANGE:
					events.ScheduleEvent(EVENTS_CHECK_VICTIM_IS_OUT_OF_RANGE, 2000);
					if (me->getVictim()->GetDistance(me) > 2.0f)
						DoCastVictim(DUNGEON_MODE(SPELL_N_BOLT,SPELL_H_BOLT));			
					break;
				}
			}

			DoMeleeAttackIfReady();
		}


		void DespawnCreatures(uint32 entry)
		{
			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, entry, 10000000);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				(*iter)->ForcedDespawn();
		}

	};
};

class npc_lurking_tempest: public CreatureScript
{
public:
	npc_lurking_tempest() : CreatureScript("npc_lurking_tempest") { }

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_lurking_tempestAI(pCreature);
	}

	struct npc_lurking_tempestAI : public ScriptedAI
	{
		npc_lurking_tempestAI(Creature * pCreature) : ScriptedAI(pCreature)
		{
			me->SetReactState(REACT_PASSIVE);
			isLurkingTempestNo = 0;
			isAtPoint = 0;
			pErtan = NULL;
		}

		InstanceScript* pInstance;
		EventMap events;
		uint8 isLurkingTempestNo;
		uint8 isAtPoint;
		Creature* pErtan;

		void Reset()
		{
			events.Reset();
		}

		void EnterCombat(Unit * /*who*/)
		{
		}

		/*void JustReachedHome()
		{
			if (isAtPoint = 0) // If the Tempest is not intialized return
				return;

			isAtPoint++;

			me->GetMotionMaster()->MovePoint(isAtPoint, LurkingTempestSummonPos[isAtPoint]);

		}*/
		void SetData(uint32 type, uint32 data)
		{
			switch (type)
			{
			case DATA_LURKING_TEMPEST_NO:
				//me->MonsterYell(data, 0, 0);
				isLurkingTempestNo = data;
				isAtPoint = data;
				//JustReachedHome();
				//me->GetMotionMaster()->MovePath(WAYPOINTS + (isLurkingTempestNo - 1),true);
				break;

			default:
				break;
			}

		}

		/*void DoAction(const int32 action)
		{
		switch(action)
		{
		case ACTION_LURKING_TEMPEST_GO_IN:

		break;

		case ACTION_LURKING_TEMPEST_GO_OUT:
		me->GetMotionMaster()->MoveTargetedHome();
		break;
		}
		}*/

		void UpdateAI(const uint32 diff)
		{
			//if (!me->getVictim() || me->HasUnitState(UNIT_STAT_CASTING))
			//	return;
			if (!me->isInCombat())
				me->DisappearAndDie();

			if (isAtPoint = 0) // If the Tempest is not intialized return
				return;
			if (me->GetDistance(LurkingTempestSummonPos[isAtPoint]) < 0.2f)
			{
				isAtPoint++;
				me->GetMotionMaster()->Clear();
				me->GetMotionMaster()->MovePoint(isAtPoint, LurkingTempestSummonPos[isAtPoint]);
			}
		}
};
};

void AddSC_boss_vizir_ertan()
{
	new boss_vizir_ertan();
	new npc_lurking_tempest();
};