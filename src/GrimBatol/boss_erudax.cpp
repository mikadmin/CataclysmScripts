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
* Spell & Definitions by Dreadii
* Script Complete 20% (or less)
**********/

#include "ScriptPCH.h"
#include "grim_batol.h"

#define SAY_AGGRO "The darkest days are still ahead!"
#define	SAY_DEATH "Ywaq maq oou; ywaq maq ssaggh. Yawq ma shg'fhn."
#define SAY_SUMMON "Come, suffering... Enter, chaos!"
#define SAY_SHADOW_GALE "F'lakh ghet! The shadow's hunger cannot be sated!"
#define SAY_KILL "More flesh for the offering!"

enum Spells
{
	//Erudax
	SPELL_ENFEEBLING_BLOW		= 75789,
	SPELL_SHADOW_GALE_VISUAL	= 75664,
	SPELL_SHADOW_GALE_SPEED_TRIGGER = 75675, // (litte hole at the caster, it is a pre visual aura of shadow gale) 

	SPELL_SPAWN_FACELESS        = 75704, // Spawns 1 (NH - 40600) or 2 (HC - 48844) Faceless 
	SPELL_TWILIGHT_PORTAL_VISUAL = 95716,

	SPELL_SHIELD_OF_NIGHTMARE = 75809, // In this Script is is casted by the Faceless itself

	// Faceless
	SPELL_UMBRAL_MENDING			= 79467, // Wowhead is worng
	SPELL_TWILIGHT_CORRUPTION_DOT	= 93613,
	SPELL_TWILIGHT_CORRUPTION_VISUAL = 91049,

	// Alexstraszas Eggs
	SPELL_SUMMON_TWILIGHT_HATCHLINGS = 91058,

	// OLD

	SPELL_PLAGUE         = 82622,    //seuche der zeitalter
	SPELL_ORKAN          = 75664,    //schattenorkan
	SPELL_SPAWN          = 75704,    //gesichtslosen beschwören
	//Faceless curruptor
	SPELL_CORRUPTION     = 75520,
	SPELL_UMBRALE        = 75763,
	SPELL_SIPHON         = 75755,
};

enum Events
{
	EVENT_ENFEEBLING_BLOW		= 1,
	EVENT_SHADOW_GALE			= 2,
	EVENT_SUMMON_FACELESS		= 3,
	EVENT_REMOVE_TWILIGHT_PORTAL = 4,
};

enum Points
{
	POINT_FACELESS_IS_AT_AN_EGG = 1,
};

class boss_erudax: public CreatureScript
{
public: 
	boss_erudax() : CreatureScript("boss_erudax") { } 

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_erudaxAI (creature);
	}

	struct boss_erudaxAI : public ScriptedAI
	{
		boss_erudaxAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			pInstance = pCreature->GetInstanceScript();

			RespawnEggs();
		}

		Unit* FacelessPortalStalker;

		InstanceScript* pInstance;
		EventMap events;
		
		void Reset()
		{
			events.Reset();

			ResetMinions();
		}

		void EnterCombat(Unit* /*who*/) 
		{
			//events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, 5000);

			events.ScheduleEvent(EVENT_SUMMON_FACELESS, 5000);

			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);

			FacelessPortalStalker = me->SummonCreature(NPC_FACELESS_PORTAL_STALKER,-680.8f,-826.9f,233.1f,0,TEMPSUMMON_MANUAL_DESPAWN);

			FacelessPortalStalker->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_ENFEEBLING_BLOW:
					DoCastVictim(SPELL_ENFEEBLING_BLOW);
					events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, 20000);
					break;

				case EVENT_SHADOW_GALE:
					DoCast(SPELL_SHADOW_GALE_VISUAL);
					break;

				case EVENT_SUMMON_FACELESS:
					//Adds a visual effect to the Stalker
					FacelessPortalStalker->GetAI()->DoCast(FacelessPortalStalker,SPELL_TWILIGHT_PORTAL_VISUAL,true);
					events.ScheduleEvent(EVENT_REMOVE_TWILIGHT_PORTAL, 7000);

					FacelessPortalStalker->GetAI()->DoCast(FacelessPortalStalker,SPELL_SPAWN_FACELESS,true);
					break;

				case EVENT_REMOVE_TWILIGHT_PORTAL:
					//Removes Portal effect from Stalker
					FacelessPortalStalker->RemoveAllAuras();
					break;

				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

		void KilledUnit(Unit* victim)
		{
			me->MonsterYell(SAY_KILL, LANG_UNIVERSAL, NULL);
		}


		void JustDied(Unit* /*killer*/)
		{	
			ResetMinions();

			me->MonsterYell(SAY_DEATH, LANG_UNIVERSAL, NULL);
		}

		void JustSummoned(Creature* summon)
		{
			summon->setActive(true);
		}

	private:
		void ResetMinions()
		{
			DespawnCreatures(NPC_FACELESS);
			DespawnCreatures(NPC_FACELESS_HC);
			DespawnCreatures(NPC_FACELESS_PORTAL_STALKER);
			DespawnCreatures(NPC_TWILIGHT_HATCHLING);
			RespawnEggs();
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

		void RespawnEggs()
		{
			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZAS_EGG, 1000.0f);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
			{	
				if((*iter)->isDead())
				(*iter)->Respawn();

				//(*iter)->SetHealth(77500);
				//(*iter)->SetMaxHealth(77500);
			}
		}
	};
};


class mob_faceless : public CreatureScript
{
public:
	mob_faceless() : CreatureScript("mob_faceless") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_facelessAI (creature);
	}

	struct mob_facelessAI : public ScriptedAI
	{
		mob_facelessAI(Creature* creature) : ScriptedAI(creature), pTarget(NULL), isAtAnEgg(false), isCastingUmbraMending (false) {}

		Creature* pTarget;
		Unit* pErudax;

		bool isAtAnEgg;
		bool isCastingUmbraMending;

		EventMap events;

		void IsSummonedBy(Unit* summoner)
		{
			pTarget = GetRandomEgg();

			DoZoneInCombat();

			if(me->GetMap()->IsHeroic())
				DoCast(me, SPELL_SHIELD_OF_NIGHTMARE, true);

			if(pTarget != NULL)
			{
				me->GetMotionMaster()->MovePoint(POINT_FACELESS_IS_AT_AN_EGG,pTarget->GetPositionX(),pTarget->GetPositionY(),pTarget->GetPositionZ());
			}

			me->SetReactState(REACT_PASSIVE); // That the Faceless are not running to Players while running to Eggs
		}

		void UpdateAI(const uint32 Diff)
		{	
			if (pTarget == NULL || !isAtAnEgg || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(isCastingUmbraMending)
			{	// If the Egg is Death and Umbra Mending was casted go to the next Egg

				pTarget = me->FindNearestCreature(NPC_ALEXSTRASZAS_EGG,1000.0f, true);
				me->GetMotionMaster()->MovePoint(POINT_FACELESS_IS_AT_AN_EGG,pTarget->GetPositionX(),pTarget->GetPositionY(),pTarget->GetPositionZ());
				isAtAnEgg = false;
				isCastingUmbraMending = false;

				return;
			}

			if(pTarget->isDead())
			{
				if(Unit* pErudax = me->FindNearestCreature(BOSS_ERUDAX,1000.0f, true))
					DoCast(pErudax, SPELL_UMBRAL_MENDING,false);

				isCastingUmbraMending = true;

				return;
			}

			pTarget->AI()->DoZoneInCombat();

			DoCast(pTarget,SPELL_TWILIGHT_CORRUPTION_DOT,true);
			DoCast(pTarget,SPELL_TWILIGHT_CORRUPTION_VISUAL,true);
		}

		void MovementInform(uint32 type, uint32 id)
		{
			if (type == POINT_MOTION_TYPE)
			{
				switch (id)
				{
				case POINT_FACELESS_IS_AT_AN_EGG:
					isAtAnEgg = true;
					break;

				default:
					break;
				}
			}
		}

	private:
		Creature* GetRandomEgg()
		{	
			//return me->FindNearestCreature(NPC_ALEXSTRASZAS_EGG,1000.0f, true);

			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, NPC_ALEXSTRASZAS_EGG, 300.0f);


			if (creatures.empty())
				return NULL;

			uint32 c = 0;
			uint32 r = urand(0,creatures.size());

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
			{
				if (c == r)
					return (*iter);

				c++;
			}

			return NULL;
		}
	};
};

class mob_alexstraszas_eggs : public CreatureScript
{
public:
	mob_alexstraszas_eggs() : CreatureScript("mob_alexstraszas_eggs") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_alexstraszas_eggsAI (creature);
	}

	struct mob_alexstraszas_eggsAI : public ScriptedAI
	{
		mob_alexstraszas_eggsAI(Creature* creature) : ScriptedAI(creature)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);

			me->SetReactState(REACT_PASSIVE);
		}

		void JustDied(Unit* killer)
		{	// Summon Twilight Hatchlings

			// Despawn of the Hatchlings is handled by Erudax
			// The behaviour of the hatchlings is handled through SmartAI

			DoCastAOE(SPELL_SUMMON_TWILIGHT_HATCHLINGS, true);
		}

		void JustSummoned(Creature* summon)
		{
			summon->setActive(true);
			summon->AI()->DoZoneInCombat();

			if (GetPlayerAtMinimumRange(0))
				summon->Attack(GetPlayerAtMinimumRange(0), true);
		}
	};
};

void AddSC_boss_erudax() 
{
	new boss_erudax();
	new mob_faceless();
	new mob_alexstraszas_eggs();
}
