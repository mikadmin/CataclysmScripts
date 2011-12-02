/*
* Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
*
* Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
*
* Copyright (C) 2011 TrilliumEMU <http://www.arkania.net/>
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

/*###########################
#      Developer Info:      #
#   Script Coded by Naios   #
#                           #
#   Script Complete: 40%    #
#  Works with Trillium EMU  #
#     & Strawberry Core     #
###########################*/

/* TODO:
- [100% DONE] Arcing Slash (Works Perfect)
- [75% DONE] Insert Heroic Spells
- Insert the Sound data
- [FIXXED] The Script Crashes sometimes (I'm not sure weather this
is the fault of this Script or the Core)
- Add Handling for Hurling the Spear
- [100%] Add Trigger for the 'Seperation Anxietly' Spell
- [25%] Add Trigger for the Fire Nova when the Spear is reaching the Ground
- Add Action that Shannox throws the Spear to Riplimb
- Add Action that Riplimb is taking the Spear back to Shannox
- The 'Feeding Frenzy Buff' Stacks too fast
- Add Kristall Trap Actions
- Add Fire Trap Actions
*/

#include "ScriptPCH.h"
#include "firelands.h"

enum Yells
{
	SAY_AGGRO                                    = -1999971,
	SAY_SOFT_ENRAGE								 = -1999972, //TODO Add Sound
	SAY_ON_DOGS_FALL							 = -1999973, //TODO Add Sound
	SAY_ON_DEAD									 = -1999974, //TODO Add Sound
};

enum Spells
{

	//Shannox
	SPELL_ARCTIC_SLASH_10N = 99931,
	SPELL_ARCTIC_SLASH_25N = 101201,
	SPELL_ARCTIC_SLASH_10H = 101202,
	SPELL_ARCTIC_SLASH_25H = 101203,

	SPELL_BERSERK = 26662,

	SPELL_CALL_SPEAR = 100663, // Script Effect Value: 49575
	SPELL_HURL_SPEAR = 100002, // Dummy Effect & Damage
	SPELL_HURL_SPEAR_SUMMON = 99978, //Summons Spear of Shannox
	SPELL_HURL_SPEAR_DUMMY_SCRIPT = 100031, //Dummy Value: 99978
	SPELL_MAGMA_RUPTURE_SHANNOX = 99840, //Causes a massive explosion of magma, dealing 47500 to 52500 Fire damage to all nearby enemies, increasing Fire damage taken by 40% for 1 min, and triggering eruptions of magma. 

	SPELL_FRENZY_SHANNOX = 23537,// Increases the caster's attack speed by 50% and the Physical damage it deals by 219 to 281 for 10 min. (Spell Aura = 9204)
	SPELL_IMMOLATION_TRAP = 52606, //Place a fire trap that will burn the first enemy to approach for <Unknown value - The spell referenced no longer exists> Fire damage over <Unknown value - The spell referenced no longer exists>.  Trap will exist for 30 sec.  Only one trap can be active at a time.(Drop Trap (181030))

	// Riplimb
	SPELL_LIMB_RIP = 99832, //The hellhound tears viciously at an enemy's exposed flesh, dealing 130% of normal damage and causing a bleeding wound that deals 0 damage every 5 sec for until cancelled. (Triggers Jagged Tear)

	// Rageface
	SPELL_FACE_RAGE = 99947, //Pins an enemy to the ground, stunning them and tearing at their flesh to deal 38 to 42 damage every 0.5 sec for 30 sec.

	// Both Dogs
	SPELL_FRENZIED_DEVOLUTION = 100064,
	SPELL_FEEDING_FRENZY_H = 100655,

	// Misc
	SPELL_SEPERATION_ANXIETY = 99835,

	//Spear Abilities
	SPELL_MAGMA_FLARE = 100495, // Inflicts Fire damage to enemies within 50 yards.
	SPELL_MAGMA_RUPTURE = 100003, // Calls forth magma eruptions to damage nearby foes. (Dummy Effect)

	// Dont know weather i implement that...
	SPELL_DOGGED_DETERMINATION = 101111, //Filled with a sense of purpose, the hound resists attempts to hinder its path back to its master.
	SPELL_FRENZY_RIPLIMB = 100522, //Increases attack speed by 30% and physical damage dealt by 30%.

};

enum Events
{
	//Shannox
	EVENT_IMMOLTATION_TRAP = 1,
	EVENT_BERSERK = 2,
	EVENT_ARCING_SLASH = 3,
	EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE = 4,
	EVENT_SUMMON_SPEAR = 5,

	//Riplimb
	EVENT_LIMB_RIP = 6,

	//Rageface
	EVENT_FACE_RAGE = 7,

};

enum Phases
{	
	PHASE_NON,
	PHASE_HAS_SPEER,
	PHASE_BRING_SPEER_BACK,
	PHASE_RAGEFACING,
};


/*#########################
######### Shannox #########
#########################*/

class boss_shannox : public CreatureScript
{
public:
	boss_shannox() : CreatureScript("boss_shannox"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_shannoxAI(creature);
	}

	struct boss_shannoxAI : public BossAI
	{
		boss_shannoxAI(Creature* c) : BossAI(c, DATA_SHANNOX)
		{
			instance = me->GetInstanceScript();
			// TODO Add not Tauntable Flag

			pRiplimb = NULL;
			pRageface = NULL;

			Reset();
		}

		InstanceScript* instance;
		Creature* pRiplimb;
		Creature* pRageface;
		Unit* tempUnit;
		bool softEnrage;
		bool bucketListCheckPoints[5];
		Phases phase;

		void Reset()
		{
			me->RemoveAllAuras();
			me->GetMotionMaster()->MoveTargetedHome();
			softEnrage = false;
			tempUnit = NULL;
			events.Reset();
			phase = PHASE_HAS_SPEER;

			if(pRiplimb != NULL)  // Prevents Crashes
			{
				if (pRiplimb->isDead())
					pRiplimb -> Respawn();
			}else
			{
				pRiplimb = me->SummonCreature(NPC_RIPLIMB, me->GetPositionX()-urand(6,8)
					,me->GetPositionY()-urand(6,8),me->GetPositionZ(),TEMPSUMMON_MANUAL_DESPAWN);
			};

			if(pRageface != NULL)  // Prevents Crashes
			{
				if (pRageface->isDead())
					pRageface -> Respawn();
			}else
			{
				pRageface = me->SummonCreature(NPC_RAGEFACE, me->GetPositionX()+urand(6,8)
					,me->GetPositionY()+urand(6,8),me->GetPositionZ(),TEMPSUMMON_MANUAL_DESPAWN);
			};

			//me->SetReactState(REACT_PASSIVE); //TODO Only for testing

			_Reset();
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
			DoScriptText(SAY_ON_DEAD, me);

			summons.DespawnAll(); // Despawns all Dogs Spears etc.

			_JustDied();
		}

		void EnterCombat(Unit* who)
		{
			DoZoneInCombat();

			events.ScheduleEvent(EVENT_IMMOLTATION_TRAP, 10000); //TODO Find out the correct Time
			events.ScheduleEvent(EVENT_ARCING_SLASH, 12000);  //TODO Find out the correct Time
			events.ScheduleEvent(EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE, 20000); //TODO Find out the correct Time

			events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);

			DoScriptText(SAY_AGGRO, me, who);

			_EnterCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim()) {}

			events.Update(diff);

			if (me->HasUnitState(UNIT_STAT_CASTING))
                return;
			
			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_IMMOLTATION_TRAP:
					{
					me->MonsterSay("[DEBUG] Lege Feuerfalle",0,0);
					/*tempUnit = SelectTarget(SELECT_TARGET_RANDOM, 1, 500, true);
					DoCast(SelectTarget(SELECT_TARGET_RANDOM, 1, 60, true), SPELL_IMMOLATION_TRAP);*/
					DoCast(SPELL_IMMOLATION_TRAP);
					events.ScheduleEvent(EVENT_IMMOLTATION_TRAP, 10000); //TODO Find out the correct Time
					break;
					}
				case EVENT_ARCING_SLASH:
					{
					DoCast(RAID_MODE(SPELL_ARCTIC_SLASH_10N, SPELL_ARCTIC_SLASH_25N,
						SPELL_ARCTIC_SLASH_10H, SPELL_ARCTIC_SLASH_25H));
					events.ScheduleEvent(EVENT_ARCING_SLASH, 12000);
					break;
					}
				case EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE:
					{
					if (phase = PHASE_HAS_SPEER)
					{
						if(pRiplimb->isDead())
						{ // Magma Rupture when Ripclimb is Death
							DoCast(SPELL_MAGMA_RUPTURE_SHANNOX);

						}/*else
						 { // Hurl Spear when Riplimb is Alive
						 DoCast(SPELL_HURL_SPEAR_SUMMON);
						 DoCast(SPELL_HURL_SPEAR_DUMMY_SCRIPT);
						 DoZoneInCombat();
						 //DoCast(SPELL_HURL_SPEAR);
						 }*/
						events.ScheduleEvent(EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE, 30000); //Corrects Time is 43s
					}else
					{ // Shifts the Event 10s back
						events.RescheduleEvent(EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE, 10000);
					}
					break;
					}

				case EVENT_BERSERK:
					DoCast(me, SPELL_BERSERK);
					break;
	
				default:
					break;
				}
			}

			if (!UpdateVictim())
				return;

			if ((pRiplimb->isDead() || pRageface -> isDead()) && !softEnrage)
			{
				DoCast(me, SPELL_FRENZY_SHANNOX);
				Talk(SAY_ON_DOGS_FALL);
				me->MonsterTextEmote(SAY_SOFT_ENRAGE, 0, true);
				softEnrage = true;
			}

			if((pRiplimb->GetDistance2d(me) >= 40 || pRageface->GetDistance2d(me) >= 40)
				&& !me->HasAura(SPELL_SEPERATION_ANXIETY)) //TODO Sniff right Distance
			{
				DoCast(me, SPELL_SEPERATION_ANXIETY);
			}

			DoMeleeAttackIfReady();
		}
	};
};

/*#########################
######## Rageface #########
#########################*/

class npc_rageface : public CreatureScript
{
public:
	npc_rageface() : CreatureScript("npc_rageface"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_ragefaceAI(creature);
	}

	struct npc_ragefaceAI : public ScriptedAI
	{
		npc_ragefaceAI(Creature *c) : ScriptedAI(c)
		{
			instance = me->GetInstanceScript();

			Reset();
		}

		InstanceScript* instance;
		EventMap events;
		Unit* shallTarget;
		bool frenzy;
		Phases phase;

		void Reset()
		{
			me->SetReactState(REACT_PASSIVE); //TODO Only for testing

			me->RemoveAllAuras();
			events.Reset();
			frenzy = false;
			shallTarget = NULL;
			phase = PHASE_NON;

			me->GetMotionMaster()->MoveTargetedHome();
			//me->GetMotionMaster()->MoveFollow(pShannox, 5, 5);
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
		}

		void EnterCombat(Unit * /*who*/)
		{
			//me->GetMotionMaster()->MoveIdle();
			//events.ScheduleEvent(EVENT_FACE_RAGE, 15000); //TODO Find out the correct Time
		}

		void SelectNewTarget()
		{
			shallTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 500, true);
			me->getThreatManager().resetAllAggro();
			me->AddThreat(shallTarget, 500.0f);
			me->Attack(shallTarget, true);
			//me->GetMotionMaster()->MoveChase(shallTarget);
		}

		void DamageTaken(Unit* attacker, uint32 damage)
		{
			//me->MonsterSay("Triggered Damage Taken",0,0);

			if (damage >= 1/* && me->HasAura(BUFF_FACE_RAGE)*/)
			{	
				me->MonsterSay("Triggered",0,0);
				me->RemoveAurasDueToSpell(SPELL_FACE_RAGE);
				me->getVictim()->ClearUnitState(UNIT_STAT_STUNNED);
				me->SetTarget(me->Attack(SelectTarget(SELECT_TARGET_RANDOM, 1, 500, true),true));
				//events.ScheduleEvent(EVENT_FACE_RAGE, 15000); //TODO Find out the correct Time
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim()) {}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FACE_RAGE:
					//DoCastVictim(SPELL_FACE_RAGE);
					//me->getVictim()->SetFlag(UNIT_FIELD_FLAGS,  UNIT_STAT_STUNNED);
					//me->getVictim()->AddUnitState(UNIT_STAT_STUNNED);
					break;
				default:
					break;
				}
			}

			if(GetShannox() != NULL)
			{
				if(GetShannox()->GetHealthPct() <= 30 && frenzy == false)
				{
					frenzy = true;
					DoCast(me, SPELL_FRENZIED_DEVOLUTION);
				}

				if(GetShannox()->GetDistance2d(me) >= 40 && !me->HasAura(SPELL_SEPERATION_ANXIETY)) //TODO Sniff right Distance
				{
					DoCast(me, SPELL_SEPERATION_ANXIETY);
				}
			}


			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType /*damageType*/)
		{
			// Feeding Frenzy (Heroic Ability)
			if(me->GetMap()->IsHeroic())
				DoCast(me, SPELL_FEEDING_FRENZY_H);
		}

		Creature* GetShannox()
		{
			return ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_SHANNOX));
		}

	};
};

/*#########################
######### Riplimb #########
#########################*/

class npc_riplimb : public CreatureScript
{
public:
	npc_riplimb() : CreatureScript("npc_riplimb"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_riplimbAI(creature);
	}

	struct npc_riplimbAI : public ScriptedAI
	{
		npc_riplimbAI(Creature *c) : ScriptedAI(c)
		{
			instance = me->GetInstanceScript();

			Reset();
		}

		InstanceScript* instance;
		EventMap events;
		bool frenzy;

		void Reset()
		{
			me->RemoveAllAuras();
			events.Reset();
			me->SetReactState(REACT_PASSIVE); //TODO Only for testing
			me->GetMotionMaster()->MoveTargetedHome();
			frenzy = false;

			//me->GetMotionMaster()->MoveFollow(pShannox, 10, 7);
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
		}

		void EnterCombat(Unit * who)
		{	
			events.ScheduleEvent(EVENT_LIMB_RIP, 10000); //TODO Find out the correct Time
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim()) {}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_LIMB_RIP:
					DoCastVictim(SPELL_LIMB_RIP);	
					events.ScheduleEvent(EVENT_LIMB_RIP, 10000); //TODO Find out the correct Time
					break;
				default:
					break;
				}
			}

			if(GetShannox() != NULL)
			{
				if(GetShannox()->GetHealthPct() <= 30 && frenzy == false)
				{
					frenzy = true;
					DoCast(me, SPELL_FRENZIED_DEVOLUTION);
				}

				if(GetShannox()->GetDistance2d(me) >= 40 && !me->HasAura(SPELL_SEPERATION_ANXIETY)) //TODO Sniff right Distance
				{
					DoCast(me, SPELL_SEPERATION_ANXIETY);
				}
			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType /*damageType*/)
		{
			// Feeding Frenzy (Heroic Ability)
			if(me->GetMap()->IsHeroic())
				DoCast(me, SPELL_FEEDING_FRENZY_H);
		}

		Creature* GetShannox()
		{
			return ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_SHANNOX));
		}
	};
};

/*#########################
###### Shannox Spear ######
#########################*/

class npc_shannox_spear : public CreatureScript
{
public:
	npc_shannox_spear() : CreatureScript("npc_shannox_spear"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_shannox_spearAI(creature);
	}

	struct npc_shannox_spearAI : public ScriptedAI
	{
		npc_shannox_spearAI(Creature *c) : ScriptedAI(c)
		{
			instance = me->GetInstanceScript();

			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
		}

		InstanceScript* instance;

		void Reset()
		{
		}

		void PassengerBoarded(Unit* /*passenger*/, int8 /*seatId*/, bool /*apply*/)
		{
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
		}

		void EnterCombat(Unit * /*who*/)
		{
			/*if (GetRiplimb() != NULL)
			me->GetMotionMaster()->MoveJump(GetRiplimb()->GetPositionX()
			,GetRiplimb()->GetPositionY(),GetRiplimb()->GetPositionZ(),2,1);
			*/
			me->MonsterSay("Spear Triggered",0,0);
			DoCast(SPELL_MAGMA_FLARE);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim()) {}

			if (!UpdateVictim())
				return;
		}

		Creature* GetShannox()
		{
			return ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_SHANNOX));
		}

		Creature* GetRiplimb()
		{
			return ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_RIPLIMB));
		}
	};
};

/*#########################
####### Achievements ######
#########################*/

//Heroic Shannox (5806)
class achievement_heroic_shannox : public AchievementCriteriaScript
{
public:
	achievement_heroic_shannox() : AchievementCriteriaScript("achievement_heroic_shannox")
	{
	}

	bool OnCheck(Player* player, Unit* target)
	{
		if (!target)
			return false;

		return player->GetMap()->IsHeroic() && player->
			GetInstanceScript()->GetBossState(DATA_SHANNOX == DONE);
	}
};

//Bucket List (5829) //TODO Currently not Working!
class achievement_bucket_list : public AchievementCriteriaScript
{
public:
	achievement_bucket_list() : AchievementCriteriaScript("achievement_bucket_list")
	{
	}

	bool OnCheck(Player* /*player*/, Unit* target)
	{
		if (!target)
			return false;

		return false;
	}
};

void AddSC_boss_shannox()
{
	new boss_shannox();
	new npc_rageface();
	new npc_riplimb();
	new achievement_bucket_list();
	new achievement_heroic_shannox();
	new npc_shannox_spear();
}
