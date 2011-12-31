/*
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
* Script rewritten by Naios
* Base Script by unkonwn
* Script Complete 20% (or less)
**********/

#include "ScriptPCH.h"
#include "throne_of_the_tides.h"

// Boss
#define SPELL_FUNGAL_SPORES 76001
#define SPELL_SHOCK_BLAST 76008
#define SPELL_SUMMON_GEYSER 75722
#define SPELL_WATERSPOUT 75683
#define SPELL_WATERSPOUT_SUMMON DUNGEON_MODE(90495,90497) // summons tornado every 7/3 secs.
// Adds
#define SPELL_CHAIN_LIGHTNING 75813
#define SPELL_LIGHTNING_SURGE 75992
#define SPELL_ARC_SLASH 75907
#define SPELL_ENRAGE 75998

enum Yells
{
	SAY_AGGRO = -1643001,
	SAY_66_PRECENT = -1643002,
	SAY_33_PRECENT = -1643003,
	SAY_DEATH = -1643004,
	SAY_KILL_1 = -1643005,
	SAY_KILL_2 = -1643006,
};

enum Phases
{
	PHASE_NORMAL_ONE = 0,
	PHASE_CLEAR_DREAMES_ONE = 1,
	PHASE_NORMAL_TWO = 2,
	PHASE_CLEAR_DREAMES_TWO = 3,
	PHASE_NORMAL_THREE = 4,
};

enum Events
{
	EVENT_GEYSER = 1,
	EVENT_FUNGAL_SPORES = 2,
	EVENT_SHOCK_BLAST = 3,
};

Position const SummonPos[3] =
{{174.41f, 802.323f, 808.368f, 0.014f},
{200.517f, 787.687f, 808.368f, 2.056f},
{200.558f, 817.046f, 808.368f, 4.141f}};

class boss_lady_nazjar : public CreatureScript
{
public:
	boss_lady_nazjar() : CreatureScript("boss_lady_nazjar") { }

	struct boss_lady_nazjarAI : public ScriptedAI
	{
		boss_lady_nazjarAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);

			pInstance = pCreature->GetInstanceScript();
		}

		InstanceScript *pInstance;

		uint8 Phase;
		bool Phased;
		uint8 SpawnCount;

		EventMap events;

		void Reset()
		{
			DespawnMinions();

			Phase = PHASE_NORMAL_ONE;
			Phased = false;
			SpawnCount = 3;

			// ?
			me->RemoveAurasDueToSpell(SPELL_WATERSPOUT);
			me->RemoveAurasDueToSpell(SPELL_WATERSPOUT_SUMMON);

			me->GetMotionMaster()->MoveTargetedHome();

			if (pInstance)
				pInstance->SetData(DATA_LADY_NAZJAR_EVENT, NOT_STARTED);
		}

		void SummonedCreatureDespawn(Creature* summon)
		{
			switch(summon->GetEntry())
			{
			case NPC_SUMMONED_WITCH:
			case NPC_SUMMONED_GUARD:
				SpawnCount--;
				break;
			}
		}

		void KilledUnit(Unit* /*victim*/)
		{
			DoScriptText(RAND(SAY_KILL_1,SAY_KILL_2), me);
		}

		void JustSummoned(Creature* summon)
		{
			if(summon->GetEntry() == NPC_SUMMONED_WITCH || summon->GetEntry() == NPC_SUMMONED_GUARD )
				summon->GetMotionMaster()->MoveChase(SelectTarget(SELECT_TARGET_RANDOM, 0, 2, true));
		}

		void EnterCombat(Unit* /*who*/)
		{
			DoScriptText(SAY_AGGRO, me);

			if (pInstance)
				pInstance->SetData(DATA_LADY_NAZJAR_EVENT, IN_PROGRESS);

			events.ScheduleEvent(EVENT_GEYSER, 20000);
			events.ScheduleEvent(EVENT_FUNGAL_SPORES, urand(12000,14000));
			events.ScheduleEvent(EVENT_SHOCK_BLAST, urand(15000,18000));
		}

		void JustDied(Unit* /*pKiller*/)
		{
			//me->SummonCreature(BOSS_COMMANDER_ULTHOK, 59.185f, 802.251f, 805.730f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60480000);
			DoScriptText(SAY_DEATH, me);

			DespawnMinions();

			if (pInstance)
				pInstance->SetData(DATA_LADY_NAZJAR_EVENT, DONE);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (SpawnCount == 0)
				LeavePhaseClearDreames();

			if ((me->HealthBelowPct(67) && Phase == PHASE_NORMAL_ONE) || (me->HealthBelowPct(34) && Phase == PHASE_NORMAL_TWO))
				EnterPhaseClearDreames();

			if (me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(!Phased)
			{ // If Nazjar is in a normal phase

				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
					case EVENT_GEYSER:
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
							DoCast(target, SPELL_SUMMON_GEYSER);
						events.ScheduleEvent(EVENT_GEYSER, 20000);
						break;
					case EVENT_FUNGAL_SPORES:
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
							DoCast(target,SPELL_FUNGAL_SPORES);
						events.ScheduleEvent(EVENT_FUNGAL_SPORES, urand(12000,14000));
						break;
					case EVENT_SHOCK_BLAST:
						DoCastVictim(SPELL_SHOCK_BLAST);
						events.ScheduleEvent(EVENT_SHOCK_BLAST, urand(15000,18000));
						break;
					}
				}
			}

			DoMeleeAttackIfReady();
		}

	private:
		inline void EnterPhaseClearDreames()
		{
			DoScriptText(SAY_66_PRECENT, me);

			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
			Phase++;
			Phased = true;

			SetCombatMovement(false);

			DoTeleportTo(192.056f, 802.527f, 807.638f, 3);

			DoCast(me, SPELL_WATERSPOUT, true);
			me->AddAura(SPELL_WATERSPOUT_SUMMON, me);

			for(uint8 i = 0; i<=2;i++)
				me->SummonCreature((i==0) ? NPC_SUMMONED_WITCH : NPC_SUMMONED_GUARD, SummonPos[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);

		}

		inline void LeavePhaseClearDreames()
		{	
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
			Phase++;
			Phased = false;

			SetCombatMovement(true);
			SpawnCount = 3;

			me->RemoveAurasDueToSpell(SPELL_WATERSPOUT);
			me->RemoveAurasDueToSpell(SPELL_WATERSPOUT_SUMMON);
		}

		inline void DespawnMinions()
		{
			DespawnCreatures(NPC_SUMMONED_WITCH);
			DespawnCreatures(NPC_SUMMONED_GUARD);
			DespawnCreatures(NPC_SUMMONED_WATERSPOUT);
			DespawnCreatures(NPC_SUMMONED_GEYSER);
		}

		void DespawnCreatures(uint32 entry)
		{
			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				(*iter)->DespawnOrUnsummon();
		}
	};

	CreatureAI* GetAI(Creature *pCreature) const
	{
		return new boss_lady_nazjarAI (pCreature);
	}
};

void AddSC_boss_lady_nazjar()
{
	new boss_lady_nazjar();
}