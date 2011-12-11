#include "ScriptPCH.h"
#include "the_vortex_pinnacle.h"

#define SAY_AGGRO "Filthy beasts! Your presence in Skywall will not be tolerated!"
#define SAY_RANDOM "Ravaged!"

enum Spells
{
	SPELL_N_BOLT                     = 86331, //Lightning Bolt
	SPELL_H_BOLT                     = 93990, //Lightning Bolt HEROIC
	SPELL_H_TEMP                     = 86340, //TEMP HEROIC
	SPELL_BUFF                       = 86292,
};

enum Events
{
	EVENT_BOLT = 1,
	EVENT_BUFF = 2,
	EVENT_SAY  = 3,
	EVENTS_CHECK_VICTIM_IS_OUT_OF_RANGE = 4,
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
		boss_vizir_ertanAI(Creature * pCreature) : ScriptedAI(pCreature)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);		
		}

		InstanceScript* pInstance;
		EventMap events;

		void Reset()
		{
			events.Reset();
		}

		void EnterCombat(Unit * /*who*/)
		{
			EnterPhaseGround();
			me->MonsterYell(SAY_AGGRO, 0, 0);
			if (me->GetMap()->IsHeroic()) 
			{
				DoCast(me,SPELL_H_TEMP);
			}
		}

		void EnterPhaseGround()
		{
			events.ScheduleEvent(EVENT_SAY, 60000);
			events.ScheduleEvent(EVENT_BUFF, 90000);
			events.ScheduleEvent(EVENT_BOLT, 5000);
			events.ScheduleEvent(EVENTS_CHECK_VICTIM_IS_OUT_OF_RANGE, 7000);
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
	};
};

void AddSC_boss_vizir_ertan()
{
	new boss_vizir_ertan();
};