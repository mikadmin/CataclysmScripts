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
* Script Complete 1% (or less)
**********/

/* TODO 

- Add Sound and Yells

*/

#include "ScriptPCH.h"
#include "firelands.h"

enum Yells
{
	SAY_AGGRO                                    = -1999971,
	SAY_ON_DEAD									 = -1999974 //TODO Add Sound
};

enum Spells
{
	SPELL_CAT_FORM								 = 98374,
	SPELL_SCORPION_FORM							 = 98379,

	SPELL_ADRENALINE							 = 97238,
	SPELL_BERSERK								 = 26662,
	SPELL_BURNING_ORBS							 = 98451,
	SPELL_FIERY_CYCLONE							 = 98443,
	SPELL_FLAME_SCYTE							 = 98474, // 10N
	SPELL_FURY									 = 97235,
	SPELL_LEAPING_FLAMES						 = 98476,
	SPELL_SEARING_SEEDS							 = 98450
};

enum Events
{
	EVENT_LEAPING_FLAMES = 1
};

enum MajordomoPhase
{
	PHASE_DRUID,
	PHASE_CAT,
	PHASE_SCORPION
};

/**** Majordomo Staghelm ****/

class boss_majordomus : public CreatureScript
{
public:
	boss_majordomus() : CreatureScript("boss_majordomus"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_majordomusAI(creature);
	}

	struct boss_majordomusAI : public BossAI
	{
		boss_majordomusAI(Creature* c) : BossAI(c, DATA_MAJORDOMUS)
		{
			instance = me->GetInstanceScript();
		}

		InstanceScript* instance;
		MajordomoPhase phase;

		void Reset()
		{
			instance->SetBossState(DATA_MAJORDOMUS, NOT_STARTED);
			events.Reset();

			me->GetMotionMaster()->MoveTargetedHome();

			summons.DespawnAll();

			TransformToDruid();

		}

		void KilledUnit(Unit * /*victim*/)
		{
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

			instance->SetBossState(DATA_MAJORDOMUS, DONE);
			DoScriptText(SAY_ON_DEAD, me);
			summons.DespawnAll();
			_JustDied();
		}

		void EnterCombat(Unit* who)
		{
			TransformToCat();
			_EnterCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{


				switch (phase)
				{
				case PHASE_DRUID:
					{
						switch (eventId)
						{




						}
					}
					break;
				case PHASE_CAT:
					{
						switch (eventId)
						{
							case EVENT_LEAPING_FLAMES:

								if (Unit* tempTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 500, true))
									DoCast(tempTarget, SPELL_LEAPING_FLAMES);

								events.ScheduleEvent(EVENT_LEAPING_FLAMES, 20000);
								break;
						}

					}
					break;
				case PHASE_SCORPION:
					{
						switch (eventId)
						{
						}

					}
					break;
				}
			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}


	private:
		inline void TransformToCat()
		{
			me->RemoveAura(SPELL_SCORPION_FORM);
			DoCast(me,SPELL_CAT_FORM,false);
			me->setPowerType(POWER_ENERGY);
			me->SetMaxPower(POWER_ENERGY,100);
			me->SetPower(POWER_ENERGY,0);

			DoCast(me,SPELL_FURY,false);

			events.Reset();

			//events.ScheduleEvent(EVENT_LEAPING_FLAMES, 10000);

			phase = PHASE_CAT;
		}

		inline void TransformToScorpion()
		{
			me->RemoveAura(SPELL_CAT_FORM);
			DoCast(me,SPELL_SCORPION_FORM,false);
			me->setPowerType(POWER_ENERGY);
			me->SetMaxPower(POWER_ENERGY,100);
			me->SetPower(POWER_ENERGY,0);

			DoCast(me,SPELL_FURY,false);

			events.Reset();

			phase = PHASE_SCORPION;
		}

		inline void TransformToDruid()
		{
			me->RemoveAura(SPELL_CAT_FORM);
			me->RemoveAura(SPELL_SCORPION_FORM);

			me->setPowerType(POWER_MANA);
			//me->SetMaxPower(POWER_MANA,155555);

			phase = PHASE_DRUID;
		}

	};
};

void AddSC_boss_majordomus()
{
	new boss_majordomus();
}