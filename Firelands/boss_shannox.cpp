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
#   Script Complete: 60%    #
#  Works with Trillium EMU  #
#     & Strawberry Core     #
###########################*/

/* TODO:
- [100% DONE] Arcing Slash (Works Perfect)
- [75%] Insert Heroic Spells
- Insert the Sound data
- [100% DONE] The Script Crashes sometimes (I'm not sure weather this
is the fault of this Script or the Core)
- [100% DONE] Add Trigger for the 'Seperation Anxietly' Spell
- [25%] Add Trigger for the Fire Nova when the Spear is reaching the Ground
- Add Action that Shannox throws the Spear to Riplimb
- Add Action that Riplimb is taking the Spear back to Shannox
- The 'Feeding Frenzy Buff' Stacks too fast
- Add Kristall Trap Actions
- [75%] Add Fire Trap Actions (Damage of the Trap is missing)
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
	SPELL_LIMB_RIP = 99832,
	SPELL_DOGGED_DETERMINATION = 101111,

	// Rageface
	SPELL_FACE_RAGE = 99947, //Pins an enemy to the ground, stunning them and tearing at their flesh to deal 38 to 42 damage every 0.5 sec for 30 sec.

	// Both Dogs
	SPELL_FRENZIED_DEVOLUTION = 100064,
	SPELL_FEEDING_FRENZY_H = 100655,

	SPELL_WARY_10N = 100167, // Buff when the Dog gos in a Trap
	SPELL_WARY_25N = 101215,
	SPELL_WARY_10H = 101216,
	SPELL_WARY_25H = 101217,

	// Misc
	SPELL_SEPERATION_ANXIETY = 99835,

	//Spear Abilities
	SPELL_MAGMA_FLARE = 100495, // Inflicts Fire damage to enemies within 50 yards.
	SPELL_MAGMA_RUPTURE = 100003, // Calls forth magma eruptions to damage nearby foes. (Dummy Effect)
	SPELL_MAGMA_RUPTURE_VISUAL = 99841,

	//Traps Abilities
	CRYSTAL_PRISON_EFFECT = 99837,

	// Dont know weather i implement that...
	SPELL_FRENZY_RIPLIMB = 100522, //Increases attack speed by 30% and physical damage dealt by 30%.

};

enum Events
{
	//Shannox
	EVENT_IMMOLTATION_TRAP = 1, // Every 10s
	EVENT_BERSERK = 2, // After 10m
	EVENT_ARCING_SLASH = 3, // Every 12s
	EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE = 4, // Every 42s
	EVENT_SUMMON_SPEAR = 5, // After EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE
	EVENT_SUMMON_CRYSTAL_PRISON = 6, // Every 25s

	//Riplimb
	EVENT_LIMB_RIP = 7, // i Dont know...
	EVENT_RIPLIMB_RESPAWN_H = 8,

	//Rageface
	EVENT_FACE_RAGE = 9,

	// Trigger for the Crystal Trap
	EVENT_CRYSTAL_TRAP_TRIGGER = 10,

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
		bool softEnrage;
		bool bucketListCheckPoints[5];
		Phases phase;

		void Reset()
		{
			me->RemoveAllAuras();
			me->GetMotionMaster()->MoveTargetedHome();
			softEnrage = false;
			events.Reset();
			phase = PHASE_HAS_SPEER;

			if(pRiplimb != NULL)  // Prevents Crashes
			{
				if (pRiplimb->isDead())
					pRiplimb -> Respawn();
			}else
			{
				pRiplimb = me->SummonCreature(NPC_RIPLIMB, me->GetPositionX()-5
					,me->GetPositionY()-5,me->GetPositionZ(),TEMPSUMMON_MANUAL_DESPAWN);
			};

			if(pRageface != NULL)  // Prevents Crashes
			{
				if (pRageface->isDead())
					pRageface -> Respawn();
			}else
			{
				pRageface = me->SummonCreature(NPC_RAGEFACE, me->GetPositionX()+5
					,me->GetPositionY()+5,me->GetPositionZ(),TEMPSUMMON_MANUAL_DESPAWN);
			};

			//me->SetReactState(REACT_PASSIVE); //TODO Only for testing

			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);  //TODO Only for testing

			_Reset();
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);

			if(me->isInCombat())
				summon->AI()->DoZoneInCombat();
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
			DoScriptText(SAY_ON_DEAD, me);

			summons.DespawnAll();

			_JustDied();
		}

		void EnterCombat(Unit* who)
		{
			DoZoneInCombat();

			events.ScheduleEvent(EVENT_IMMOLTATION_TRAP, 10000);
			events.ScheduleEvent(EVENT_ARCING_SLASH, 12000);
			events.ScheduleEvent(EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE, 20000); //TODO Find out the correct Time
			events.ScheduleEvent(EVENT_SUMMON_CRYSTAL_PRISON, 25000);
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
					DoCast(SelectTarget(SELECT_TARGET_RANDOM, 1, 60, true),SPELL_IMMOLATION_TRAP,true);
					events.ScheduleEvent(EVENT_IMMOLTATION_TRAP, 10000);
					break;

				case EVENT_BERSERK:
					DoCast(me, SPELL_BERSERK);
					break;

				case EVENT_ARCING_SLASH:
					DoCast(RAID_MODE(SPELL_ARCTIC_SLASH_10N, SPELL_ARCTIC_SLASH_25N,
						SPELL_ARCTIC_SLASH_10H, SPELL_ARCTIC_SLASH_25H));
					events.ScheduleEvent(EVENT_ARCING_SLASH, 12000);
					break;

				case EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE:

					if(pRiplimb->isDead())
					{ // Cast Magma Rupture when Ripclimb is Death
						DoCast(SPELL_MAGMA_RUPTURE_SHANNOX);
					}else
					{
						// Throw Spear if Riplimb is Alive and Shannox has the Spear
						if (phase == PHASE_HAS_SPEER)
						{
							DoCast(SPELL_HURL_SPEAR_SUMMON);
							DoCast(SPELL_HURL_SPEAR_DUMMY_SCRIPT);
							phase = PHASE_NON;
						}else
							// Shifts the Event back if Shannox has not the Spear yet
							events.RescheduleEvent(EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE, 10000);
					}

					break;

				case EVENT_SUMMON_CRYSTAL_PRISON:
					if (Unit* tempTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 500, true))
						pRiplimb = me->SummonCreature(NPC_CRYSTAL_TRAP, tempTarget->GetPositionX()
						,tempTarget->GetPositionY(),tempTarget->GetPositionZ(),TEMPSUMMON_MANUAL_DESPAWN);
					events.ScheduleEvent(EVENT_SUMMON_CRYSTAL_PRISON, 25000);
					break;

				case EVENT_RIPLIMB_RESPAWN_H:
					pRiplimb->Respawn();
					DoZoneInCombat();
					break;

				default:
					break;
				}
			}

			if (!UpdateVictim())
				return;

			if ((pRiplimb->isDead() || pRageface -> isDead()) && !softEnrage)
			{
				// Heroic: Respawn Riplimb 30s after he is Death
				if(pRiplimb->isDead() && me->GetMap()->IsHeroic())
					events.ScheduleEvent(EVENT_RIPLIMB_RESPAWN_H, 30000);

				DoCast(me, SPELL_FRENZY_SHANNOX);
				DoScriptText(SAY_ON_DOGS_FALL, me);
				DoScriptText(SAY_SOFT_ENRAGE, me);
				softEnrage = true;
			}

			if((pRiplimb->GetDistance2d(me) >= 70 || pRageface->GetDistance2d(me) >= 70)
				&& !me->HasAura(SPELL_SEPERATION_ANXIETY))
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

				if(GetShannox()->GetDistance2d(me) >= 70 && !me->HasAura(SPELL_SEPERATION_ANXIETY)) //TODO Sniff right Distance
				{
					DoCast(me, SPELL_SEPERATION_ANXIETY);
				}
			}


			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DamageDealt(Unit* victim, uint32& damage, DamageEffectType /*damageType*/)
		{
			// Feeding Frenzy (Heroic Ability)
			if(me->GetMap()->IsHeroic() && damage > 0)
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
			me->GetMotionMaster()->MoveTargetedHome();
			frenzy = false;

			//me->GetMotionMaster()->MoveFollow(pShannox, 10, 7);

			//me->SetReactState(REACT_PASSIVE); //TODO Only for testing
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
		}

		void EnterCombat(Unit * who)
		{	
			events.ScheduleEvent(EVENT_LIMB_RIP, 12000); //TODO Find out the correct Time
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
					events.ScheduleEvent(EVENT_LIMB_RIP, 12000); //TODO Find out the correct Time
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

				if(GetShannox()->GetDistance2d(me) >= 70 && !me->HasAura(SPELL_SEPERATION_ANXIETY)) //TODO Sniff right Distance
				{
					DoCast(me, SPELL_SEPERATION_ANXIETY);
				}
			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DamageDealt(Unit* victim, uint32& damage, DamageEffectType /*damageType*/)
		{
			// Feeding Frenzy (Heroic Ability)
			if(me->GetMap()->IsHeroic() && damage > 0)
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
			me->MonsterSay("Spear Triggered",0,0);

			if (GetRiplimb() != NULL)
				me->GetMotionMaster()->MoveJump(GetRiplimb()->GetPositionX()
				,GetRiplimb()->GetPositionY(),GetRiplimb()->GetPositionZ(),5,1);

			for(int i=0;i<400;i++)
			{
				me->CastSpell(me->GetPositionX()+(urand(0,40)-20),me->GetPositionY()+(urand(0,40)-20),
					46,SPELL_MAGMA_RUPTURE_VISUAL,true);
			}

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
####### Crystal Trap ######
#########################*/

class npc_crystal_trap : public CreatureScript
{
public:
	npc_crystal_trap() : CreatureScript("npc_crystal_trap"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_crystal_trapAI(creature);
	}

	struct npc_crystal_trapAI : public ScriptedAI
	{
		npc_crystal_trapAI(Creature *c) : ScriptedAI(c)
		{
			instance = me->GetInstanceScript();

			//me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
		}

		InstanceScript* instance;
		EventMap events;

		void Reset()
		{
			events.Reset();
		}

		void EnterCombat(Unit * /*who*/)
		{
			me->MonsterSay("Prison Triggered",0,0);
			events.Reset();
			events.ScheduleEvent(EVENT_CRYSTAL_TRAP_TRIGGER, 4000);

		}

void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim()) {}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CRYSTAL_TRAP_TRIGGER:
					me->MonsterSay("Event Triggered",0,0);
					if (Unit* tempTarget = SelectTarget(SELECT_TARGET_NEAREST, 0, 5, false))
					{
						
						me->SummonGameObject(GOBCrystalTrapIce,me->GetPositionX()
						,me->GetPositionY(),me->GetPositionZ(), 0, 0, 0, 0, 0, 50000);
						me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
						me->MonsterSay("Ice Triggered",0,0);
					}
									
					break;
				default:
					break;
				}
			}	

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
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
	new npc_shannox_spear();
	new npc_crystal_trap();
	new achievement_bucket_list();
	new achievement_heroic_shannox();
}
