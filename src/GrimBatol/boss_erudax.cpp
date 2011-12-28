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
* Script Complete 70% (or less)
**********/

#include "ScriptPCH.h"
#include "grim_batol.h"

// ToDo move the Yells to the DB
#define SAY_AGGRO "The darkest days are still ahead!"
#define	SAY_DEATH "Ywaq maq oou; ywaq maq ssaggh. Yawq ma shg'fhn."
#define SAY_SUMMON "Come, suffering... Enter, chaos!"
#define SAY_SHADOW_GALE "F'lakh ghet! The shadow's hunger cannot be sated!"
#define SAY_KILL "More flesh for the offering!"

enum Spells
{
	// Erudax
	SPELL_ENFEEBLING_BLOW				= 75789,
	SPELL_SHADOW_GALE_VISUAL			= 75664,

	// (litte hole at the caster, it is a pre visual aura of shadow gale) 
	SPELL_SHADOW_GALE_SPEED_TRIGGER		= 75675,

	// Spawns 1 (NH - 40600) or 2 (HC - 48844) Faceless 
	SPELL_SPAWN_FACELESS				= 75704,
	SPELL_TWILIGHT_PORTAL_VISUAL		= 95716,

	// In this Script is is casted by the Faceless itself
	SPELL_SHIELD_OF_NIGHTMARE			= 75809,

	SPELL_BINDING_SHADOWS				= 79466, // Wowhead is wrong
	SPELL_BINDING_SHADOWS_AURA			= 0,

	// Faceless
	SPELL_UMBRAL_MENDING				= 79467, // Wowhead is wrong
	SPELL_TWILIGHT_CORRUPTION_DOT		= 93613,
	SPELL_TWILIGHT_CORRUPTION_VISUAL	= 91049,

	// Maybe another possible Spell replacement for Twilight Corruption
	// SPELL_SIPHON         = 75755,

	// Alexstraszas Eggs
	SPELL_SUMMON_TWILIGHT_HATCHLINGS = 91058,
};

enum Events
{
	EVENT_ENFEEBLING_BLOW					= 1,
	EVENT_SHADOW_GALE						= 2,
	EVENT_SUMMON_FACELESS					= 3,
	EVENT_REMOVE_TWILIGHT_PORTAL			= 4,
	EVENT_CAST_SHIELD_OF_NIGHTMARE_DELAY	= 5,
	EVENT_BINDING_SHADOWS					= 6,
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

			// After every Shadow Gale
			//events.ScheduleEvent(EVENT_SUMMON_FACELESS, 20000);

			events.ScheduleEvent(EVENT_BINDING_SHADOWS, 5000);

			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);

			// The Position of the Portal Stalker is the Summon Position of the Adds

			// Blizzlike Position: -641.515f,-827.8f,235.5f,3.069f
			// The non Blizzlike Position is Insert for testing Reasons

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

					if (!(rand()%2))
						me->MonsterYell(SAY_SUMMON, LANG_UNIVERSAL, NULL);

					FacelessPortalStalker->GetAI()->DoCast(FacelessPortalStalker,SPELL_TWILIGHT_PORTAL_VISUAL,true);
					events.ScheduleEvent(EVENT_REMOVE_TWILIGHT_PORTAL, 7000);

					FacelessPortalStalker->GetAI()->DoCast(FacelessPortalStalker,SPELL_SPAWN_FACELESS,true);
					break;

				case EVENT_REMOVE_TWILIGHT_PORTAL:
					//Removes Portal effect from Stalker
					FacelessPortalStalker->RemoveAllAuras();
					break;

				case EVENT_BINDING_SHADOWS:

					if (Unit* tempTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
						DoCast(tempTarget,SPELL_BINDING_SHADOWS);

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

				(*iter)->SetHealth(77500);
				(*iter)->SetMaxHealth(77500);
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
				events.ScheduleEvent(EVENT_CAST_SHIELD_OF_NIGHTMARE_DELAY, 3000);

			if(pTarget != NULL)
			{
				me->GetMotionMaster()->MovePoint(POINT_FACELESS_IS_AT_AN_EGG,pTarget->GetPositionX()-4.0f,pTarget->GetPositionY()-4.0f,pTarget->GetPositionZ());
			}

			me->SetReactState(REACT_PASSIVE); // That the Faceless are not running to Players while running to Eggs
		}

		void UpdateAI(const uint32 diff)
		{	
			if (pTarget == NULL || !isAtAnEgg || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CAST_SHIELD_OF_NIGHTMARE_DELAY:
					DoCast(me, SPELL_SHIELD_OF_NIGHTMARE, true);
					break;

				default:
					break;
				}
			}

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

		void JustDied(Unit* killer)
		{	// Removes the Dot of the Egg if the Faceless dies
			if(isAtAnEgg && pTarget->isAlive())
				pTarget->RemoveAllAuras();
		}

	private:
		Creature* GetRandomEgg()
		{	
			// I know that this is looking strange but it works! ^^

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

class spell_binding_shadows : public SpellScriptLoader
{
public:
	spell_binding_shadows() : SpellScriptLoader("spell_binding_shadows") { }

	class spell_binding_shadows_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_binding_shadows_SpellScript)

			bool Validate(SpellEntry const * spellEntry) {return false;}

		bool Load() {return true;}

		void Unload() {}

		void HandleDummy(SpellEffIndex /*effIndex*/)
		{

			sLog->outString("SPELL_EFFECT_DUMMY is executed on target!");

			if (Unit * target = GetHitUnit())
			{
				GetCaster()->CastSpell(target, SPELL_BINDING_SHADOWS_AURA, true);

				Map::PlayerList const &PlayerList =  target->GetMap()->GetPlayers();

				if (!PlayerList.isEmpty())
				{
					for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
						if(target != i->getSource())
							if(target->GetDistance(i->getSource()) < 5)
								GetCaster()->CastSpell(target, SPELL_BINDING_SHADOWS_AURA, true);
				}

			}
		}

		void Register()
		{
			OnEffect += SpellEffectFn(spell_binding_shadows_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);        
		}
	};

	SpellScript *GetSpellScript() const
	{
		return new spell_binding_shadows_SpellScript();
	}
};

void AddSC_boss_erudax() 
{
	new boss_erudax();
	new mob_faceless();
	new mob_alexstraszas_eggs();
	//new spell_binding_shadows();
}
