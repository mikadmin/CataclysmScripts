/*
* Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
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

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

/*
Corla, Herald of Twilight yells: Bask in his power! Rise as an agent of the master's rage!
Corla, Herald of Twilight yells: For the master I'd die a thousand times... A thousan...
Corla, Herald of Twilight yells: HERETICS! You will suffer for this interruption!
*/

enum Spells
{
	// Corlas Spells
	SPELL_EVOLUTION = 75697,
	SPELL_AURA_OF_ACCELERATION = 75817,
	SPELL_DARK_COMMAND = 75823,

	SPELL_KNEELING_IN_SUPPLICATION = 75608,
	SPELL_DRAIN_ESSENCE_CHANNELING = 75645,

	SPELL_DRAIN_VISUAL = 60857,

	// Envolved Twilight Zealot & Twilight Drakonid
};

enum Events
{
	EVENT_DARK_COMMAND = 1,
};

enum Actions
{
	ACTION_TRIGGER_START_CHANNELING = 1,
	ACTION_TRIGGER_STOP_CHANNELING = 2,
};

Position const summonPositions[4] =
{
	{573.676f, 980.619f, 155.354f, 1.58448f}, // Twilight Zealot Spawn Positions
	{580.919f, 982.981f, 155.354f, 2.05572f},
	{565.629f, 983.0f, 155.354f, 0.689123f},
	{573.534668f, 966.700256f, 160.890472f, 1.482759f}, // Nether Essence Trigger SPawning Position
};

class boss_corla_herald_of_twilight : public CreatureScript
{
public:
	boss_corla_herald_of_twilight() : CreatureScript("boss_corla_herald_of_twilight") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_corla_herald_of_twilightAI (creature);
	}

	struct boss_corla_herald_of_twilightAI : public ScriptedAI
	{
		boss_corla_herald_of_twilightAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = creature->GetInstanceScript();

			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
				NetherEssenceTrigger[i] = NULL;

			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
				TwilightZealotsList[i] = NULL;	
		}

		InstanceScript* instance;
		EventMap events;
		Creature* TwilightZealotsList[3];
		Creature* NetherEssenceTrigger[3];

		void Reset()
		{
			events.Reset();
			me->GetMotionMaster()->MoveTargetedHome();
			me->RemoveAllAuras();

			// Resets Twilight Zealots
			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
			{
				if(TwilightZealotsList[i] == NULL)
					TwilightZealotsList[i] = me->SummonCreature(NPC_TWILIGHT_ZEALOT_CORLA,summonPositions[i],TEMPSUMMON_MANUAL_DESPAWN);

				// Spawns the Trigger if neccesary
				if(NetherEssenceTrigger[i] == NULL)
					NetherEssenceTrigger[i] = TwilightZealotsList[i]->SummonCreature(NPC_NETHER_ESSENCE_TRIGGER,summonPositions[3],TEMPSUMMON_MANUAL_DESPAWN);

				// Respawns the Zealots if neccesary
				if(TwilightZealotsList[i]->isDead())
					TwilightZealotsList[i]->Respawn();

				TwilightZealotsList[i]->RemoveAura(SPELL_AURA_OF_ACCELERATION);
				TwilightZealotsList[i]->RemoveAllControlled();
				TwilightZealotsList[i]->GetMotionMaster()->MoveTargetedHome();


				if(!TwilightZealotsList[i]->HasAura(SPELL_KNEELING_IN_SUPPLICATION))
					TwilightZealotsList[i]->CastSpell(TwilightZealotsList[i],SPELL_KNEELING_IN_SUPPLICATION,true);

				TwilightZealotsList[i]->SetReactState(REACT_PASSIVE);
			}

			// Stops Channeling from the Triggers to the Zealots
			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
				NetherEssenceTrigger[i]->GetAI()->DoAction(ACTION_TRIGGER_STOP_CHANNELING);

			DoCast(me, SPELL_DRAIN_ESSENCE_CHANNELING, true);
		}

		void EnterCombat(Unit* /*who*/)
		{
			me->CastStop();
			me->GetMotionMaster()->MoveChase(me->getVictim());

			events.ScheduleEvent(EVENT_DARK_COMMAND, 20000);

			// Informs the trigger on what Twilight Zealot he should channel the nether essence
			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
				NetherEssenceTrigger[i]->GetAI()->DoAction(ACTION_TRIGGER_START_CHANNELING);

			DoCastAOE(SPELL_AURA_OF_ACCELERATION);

			me->MonsterYell("HERETICS! You will suffer for this interruption!", LANG_UNIVERSAL, NULL);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_DARK_COMMAND:
					if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
						DoCast(pTarget,SPELL_DARK_COMMAND);

					events.ScheduleEvent(EVENT_DARK_COMMAND, 20000);
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

		void JustDied(Unit* /*killer*/)
		{
			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
				NetherEssenceTrigger[i]->GetAI()->DoAction(ACTION_TRIGGER_STOP_CHANNELING);

			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
			{
				TwilightZealotsList[i]->DespawnOrUnsummon();

				TwilightZealotsList[i] = NULL;
			}

			me->MonsterYell("There is only one true path of enlightenment! DEATH!", LANG_UNIVERSAL, NULL);
		}
	};
};


class mob_corla_netheressence_trigger : public CreatureScript
{
public:
	mob_corla_netheressence_trigger() : CreatureScript("mob_corla_netheressence_trigger") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_corla_netheressence_triggerAI (creature);
	}

	struct mob_corla_netheressence_triggerAI : public ScriptedAI
	{
		mob_corla_netheressence_triggerAI(Creature* creature) : ScriptedAI(creature)
		{
			channelTarget = NULL;
			lastTarget = NULL;
			zealot = NULL,

				creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);

			creature->SetReactState(REACT_PASSIVE);
		}

		Unit* zealot;
		Unit* channelTarget;
		Unit* lastTarget;

		void UpdateAI(const uint32 diff)
		{
			if (channelTarget == NULL/* || lastTarget == NULL */|| zealot == NULL)
				return;

			channelTarget = zealot;
			Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();

			if (!PlayerList.isEmpty())
			{
				for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
				{
					if(i->getSource()->IsInBetween(me, zealot, 2.0f))
						channelTarget = i->getSource();
				}
			}

			zealot->SetAuraStack(SPELL_EVOLUTION,channelTarget,channelTarget->GetAuraCount(SPELL_EVOLUTION)+1);
		}

		void IsSummonedBy(Unit* summoner)
		{
			zealot = summoner;
		}

		void DoAction(const int32 action)
		{
			switch(action)
			{
			case ACTION_TRIGGER_START_CHANNELING:
				channelTarget = zealot;

				// To avoid that on beginning no spell is casted.
				lastTarget = me;
				break;

			case ACTION_TRIGGER_STOP_CHANNELING:
				lastTarget = channelTarget = NULL;
				break;
			}
		}
	};
};

void AddSC_boss_corla_herald_of_twilight()
{
	new boss_corla_herald_of_twilight();
	new mob_corla_netheressence_trigger();
}