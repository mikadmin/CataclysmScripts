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
#                           #
#   Developer Info:         #
#   Script Coded by Naios   #
#   11/2011                 #
#                           #
#   Script Complete: 20%    #
#   Tested on Trillium EMU  #
#                           #
###########################*/


/*
Notes:

Shannox 53691
Wadenbeiﬂer 53694
Augenkratzer 53695
Kristallgefangnisfalle 53713
Spear of Shannox 53752

Magma Rupture
Fire damage taken increased by 40%.
1 minute remaining

Frenzy Shannox
Physical damage dealt is increased by 219 to 281.
Attack speed increased by 50%.
10 minutes remaining

Dogged Determination
Filled with a sense of purpose, unable to be
slowed below 50% of normal movement speed

Frenzy Riplimb
Physical damage dealt is increased by 30%.
Attack speed increased by 30%.

Frenzied Devotion Riplimb
All damage dealt is increased by 400%.
Attack and movement speeds increased by 200%.

Feeding Frenzy
Successful melee attacks grant a stacking
5% bonus to physical damage dealt for 20 sec.

Face Rage
Your face is being mauled.
30 seconds remaining

######################################## */


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
	SPELL_ARCTIC_SLASH = 99931, // Inflicts 125% of weapon damage to enemies in front of the caster, and causes a Jagged Tear on the caster's primary target. (Trigger Spell Jagged Tear)
	SPELL_BERSERK = 26662, 
	SPELL_CALL_SPEAR = 100663, // Script Effect Value: 49575
	SPELL_HURL_SPEAR = 100002, // Dummy Effect & Damage
	SPELL_HURL_SPEAR_SUMMON = 99978, //Summons Spear of Shannox
	SPELL_HURL_SPEAR_DUMMY_SCRIPT = 100031, //Dummy Value: 99978
	SPELL_JAGGED_TEAR = 99937, //Deals 2500 damage every 3 sec for 24 sec. Stacks.
	SPELL_MAGMA_RUPTURE_SHANNOX = 99840, //Causes a massive explosion of magma, dealing 47500 to 52500 Fire damage to all nearby enemies, increasing Fire damage taken by 40% for 1 min, and triggering eruptions of magma. 
	SPELL_SEPERATION_ANXIETY = 99835, //When the distance between the huntsman and his pets grows too great, both become extremely agitated, increasing their damage and attack speed by 100%. (Effect #1	Apply Aura: Mod Damage Done % (127) Value: 100 Effect #2	Apply Aura: ?? (Aura #319) Value: 100)
	SPELL_FRENZY_SHANNOX = 23537,// Increases the caster's attack speed by 50% and the Physical damage it deals by 219 to 281 for 10 min. (Spell Aura = 9204)

	//Misc
	SPELL_IMMOLATION_TRAP = 52606, //Place a fire trap that will burn the first enemy to approach for <Unknown value - The spell referenced no longer exists> Fire damage over <Unknown value - The spell referenced no longer exists>.  Trap will exist for 30 sec.  Only one trap can be active at a time.(Drop Trap (181030))

	//Riplimb
	SPELL_DOGGED_DETERMINATION = 101111, //Filled with a sense of purpose, the hound resists attempts to hinder its path back to its master.
	SPELL_FRENZY_RIPLIMB = 100522, //Increases attack speed by 30% and physical damage dealt by 30%.
	SPELL_LIMB_RIP = 99832, //The hellhound tears viciously at an enemy's exposed flesh, dealing 130% of normal damage and causing a bleeding wound that deals 0 damage every 5 sec for until cancelled. (Triggers Jagged Tear)
	SPELL_FRENZIED_DEVOLUTION = 100064, //Increases the caster's attack and movement speeds by 200% and all damage it deals by 400%. (Applys some Auras)
	SPELL_FEEDING_FRENZY_H = 100655, //Successful melee attacks drive the hound into a feeding frenzy, granting a stacking 5% bonus to physical damage dealt for 20 sec.

	//Rageface
	SPELL_FACE_RAGE = 99947, //Pins an enemy to the ground, stunning them and tearing at their flesh to deal 38 to 42 damage every 0.5 sec for 30 sec.
	BUFF_FACE_RAGE = 100129, // I'll hope this is correct

	//Spear Abilities
	SPELL_MAGMA_FLARE = 100495, // Inflicts Fire damage to enemies within 50 yards.
	SPELL_MAGMA_RUPTURE = 100003, // Calls forth magma eruptions to damage nearby foes. (Dummy Effect)



};

enum Events
{
	//Shannox
	EVENT_IMMOLTATION_TRAP,
	EVENT_BERSERK,
	EVENT_ARCING_SLASH,
	EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE,

	//Riplimb
	EVENT_LIMB_RIP,

	//Rageface
	EVENT_FACE_RAGE,

};

// ######### Shannox #########

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
		}

		InstanceScript* instance;
		bool enrage;
		
		void Reset()
		{
			//instance->SetBossState(BOSS_SHANNOX, NOT_STARTED);
			enrage = false;
			events.Reset();
						
			if(GetRiplimb() != NULL)  // Prevents Crashes
			{
				if (GetRiplimb()->isDead())
					GetRiplimb() -> Respawn();
			}

			if(GetRageface() != NULL)  // Prevents Crashes
			{
				if (GetRageface()->isDead())
					GetRageface() -> Respawn();
			}

			me->GetMotionMaster()->MoveTargetedHome();

			//me->SetReactState(REACT_PASSIVE); //TODO Only for testing
		}

		void JustSummoned(Creature* summon)
		{
		summons.Summon(summon);
		summon->setActive(true);
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{

			instance->SetBossState(BOSS_SHANNOX, DONE);
			DoScriptText(SAY_ON_DEAD, me);
			_JustDied();
		}

		void EnterCombat(Unit* who)
		{
			instance->SetBossState(BOSS_SHANNOX,IN_PROGRESS);

			DoZoneInCombat();
			
			events.ScheduleEvent(EVENT_IMMOLTATION_TRAP, 20000); //TODO Find out the correct Time
			events.ScheduleEvent(EVENT_ARCING_SLASH, 10000);  //TODO Find out the correct Time
			events.ScheduleEvent(EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE, 20000); //TODO Find out the correct Time

			events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);

			DoScriptText(SAY_AGGRO, me);

			

			_EnterCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim()) {}

			events.Update(diff);
			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_IMMOLTATION_TRAP:
					//tempUnit = SelectTarget(SELECT_TARGET_RANDOM, 1, 500, true);
					//me->CastSpell(SPELL_IMMOLATION_TRAP, tempUnit->GetPositionX(),tempUnit->GetPositionY(),tempUnit->GetPositionZ());
					events.RepeatEvent(15000); //TODO Find out the correct Time
					break;
				case EVENT_ARCING_SLASH:
					DoCast(SPELL_ARCTIC_SLASH);
					events.ScheduleEvent(EVENT_ARCING_SLASH, 10000);  //TODO Find out the correct Time
					break;
				case EVENT_HURL_SPEAR_OR_MAGMA_RUPTUTRE:
					/*if(GetRiplimb()->isDead())
					{
					// Magma Rupture when Ripclimb is Death

					}else
					{

					// Hurl Spear when Ripclimb is Alive
					tempCreature = me->SummonCreature(NPC_SHANNOX_SPEAR,me->GetPositionX(),me->GetPositionY(),me->GetPositionZ()+1);
					tempCreature->GetMotionMaster()->MoveJump(GetRiplimb()->GetPositionX()+urand(-1,1),
					GetRiplimb()->GetPositionY()+urand(-1,1),GetRiplimb()->GetPositionZ()+urand(-1,1),1 ,1 );
					}*/

					DoCast(SPELL_HURL_SPEAR_SUMMON);
					DoZoneInCombat();
					DoCast(SPELL_HURL_SPEAR_DUMMY_SCRIPT);
					DoCast(SPELL_HURL_SPEAR);


					events.RepeatEvent(15000); //TODO Find out the correct Time
					break;
				case EVENT_BERSERK:
					DoCast(me, SPELL_BERSERK);
					break;
				}
			}

			//delete tempUnit;

			if (!UpdateVictim())
				return;
			if (GetRageface() != NULL && GetRiplimb() != NULL) // Prevents Crashes
			{
				if ((GetRiplimb()->isDead() || GetRageface()->isDead()) && !enrage)
				{
					DoCast(me, SPELL_FRENZY_SHANNOX);
					DoScriptText(SAY_ON_DOGS_FALL, me);
					me->MonsterTextEmote(SAY_SOFT_ENRAGE, 0, true);
					enrage = true;

					DoMeleeAttackIfReady();
				}
			}
		}


		Creature* GetRiplimb()
		{
			return me->GetCreature(*me,instance->GetData64(NPC_RIPLIMB));
		}

		Creature* GetRageface()
		{
			return me->GetCreature(*me,instance->GetData64(NPC_RAGEFACE));
		}
	};
};

// ##### Rageface (Augenkratzer) #####

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

			shallTarget = NULL;

		}

		InstanceScript* instance;
		EventMap events;
		Unit* shallTarget;
		bool frenzy;
		bool stackerStopper;

		void Reset()
		{
			//me->SetReactState(REACT_PASSIVE); //TODO Only for testing
			frenzy = false;
			stackerStopper = false;

			me->GetMotionMaster()->MoveTargetedHome();
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
		}

		void EnterCombat(Unit * /*who*/)
		{
			events.Reset();
			events.ScheduleEvent(EVENT_FACE_RAGE, 15000); //TODO Find out the correct Time
		}

		void SelectNewTarget()
		{
			shallTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 500, true);
		}

		void DamageTaken(Unit* attacker, uint32 damage)
		{
			if (damage >= 50000/* && me->HasAura(BUFF_FACE_RAGE)*/)
			{	
				me->MonsterSay("Triggered",0,0);
				me->RemoveAurasDueToSpell(SPELL_FACE_RAGE);
				me->getVictim()->ClearUnitState(UNIT_STAT_STUNNED);
				me->SetTarget(me->Attack(SelectTarget(SELECT_TARGET_RANDOM, 1, 500, true),true));
				events.ScheduleEvent(EVENT_FACE_RAGE, 15000); //TODO Find out the correct Time
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
					DoCastVictim(SPELL_FACE_RAGE);
					//me->getVictim()->SetFlag(UNIT_FIELD_FLAGS,  UNIT_STAT_STUNNED);
					me->getVictim()->AddUnitState(UNIT_STAT_STUNNED);
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
			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType /*damageType*/)
		{
			//TODO Set Heroic Condition
			if (!stackerStopper)
			{
				DoCast(me, SPELL_FEEDING_FRENZY_H);
				stackerStopper = true;
			}
		}


		Creature* GetShannox()
		{
			return me->GetCreature(*me,instance->GetData64(NPC_SHANNOX));
		}

	};
};

// ##### Riplimb (Wadenkratzer) #####

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
		}

		InstanceScript* instance;
		EventMap events;
		bool frenzy;

		void Reset()
		{
			me->SetReactState(REACT_PASSIVE); //TODO Only for testing
			me->GetMotionMaster()->MoveTargetedHome();
			frenzy = false;
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
		}

		void EnterCombat(Unit * who)
		{	
			events.Reset();
			events.ScheduleEvent(EVENT_LIMB_RIP, 5000); //TODO Find out the correct Time
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
					DoScriptText(SAY_AGGRO, me);
					DoCastVictim(SPELL_LIMB_RIP);	

					events.RepeatEvent(urand(10000,20000)); //TODO Find out the correct Time
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
			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType /*damageType*/)
		{
			//TODO Set Heroic Condition
			DoCast(me, SPELL_FEEDING_FRENZY_H);

		}

		Creature* GetShannox()
		{
			return me->GetCreature(*me,instance->GetData64(NPC_SHANNOX));
		}


	};
};

// ######## Shannox Spear ########

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

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
		{
		}

		void EnterCombat(Unit * /*who*/)
		{
			me->MonsterSay("Spear Triggered (Now in Combat!)",0,0);
			DoCast(SPELL_MAGMA_FLARE);
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
			return me->GetCreature(*me,instance->GetData64(NPC_SHANNOX));
		}
	};
};

void AddSC_boss_shannox()
{
	new boss_shannox();
	new npc_rageface();
	new npc_riplimb();
	new npc_shannox_spear();
}