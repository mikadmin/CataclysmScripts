/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

#define SAY_AGGRO "Hmm... the Omnotron Defense System. Centuries ago these constructs were considered the Dwarves greatest technical achievements. With so many counters to each construct's attacks. I''ll have to rectify these designs for them to provide me any entertainement."
#define SAY_STORY "Stupid Dwarnes and you fascination with runes! Why would you create something that would help your enemy?"
#define SAY_LIGHTNING "Lightning conductor works much better in a crowd,yes?"
#define SAY_TOXITRON_CHEMICAL "Were you planning on using Toxitron's chemical to damage the other construcs?Clever plan, let me ruin that for you."
#define SAY_TOO_BAD "You would like to move away from that, wouldn't you?Too bad."
#define SAY_DEATH "Defense systems obliterated. Powering down...."

#define SAY_SHIELD_POISON "Toxitron unit shield system onlines."
#define SAY_SHIELD_FLAMME "Magmatron unit shield system onlines."
#define SAY_SHIELD_ELECTRON "Electron unit shield system onlines."
#define SAY_SHIELD_ARCANOTRON "Arcanotron unit shield system onlines."
#define SAY_ACTIVATION_TOXITRON "Toxitron unit activated."
#define SAY_ACTIVATION_MAGMATRON "Magmatron unit activated."
#define SAY_ACTIVATION_ELECTRON "Electron unit activated."
#define SAY_ACTIVATION_ARCANOTRON "Arcanotron unit activated."
#define SAY_REROUTING_ENERGY "Defense systems obliterated. Powering down...."

enum Spells
{
	// Omnitron
	SPELL_SHUTING_DOWN = 78746,
	SPELL_ACTIVATED = 78740,
	// Electron
	SPELL_LIGHTNING_CONDUCTOR = 79888,
	SPELL_ELECTRICAL_DISCHARGE = 91465,
	SPELL_UNSTABLE_SHIELD = 91447,
	// Toxitron
	SPELL_CHEMICAL_BOMB = 80157,
	SPELL_POISON_SOAKED_SHELL = 91501,
	SPELL_POISON_PROTOCOL = 91513,
	// Magmatron
	SPELL_BARRIER = 79582,
	SPELL_ACQUIRING_TARGET = 79501,
	SPELL_FLAMETHROWER = 79504,
	SPELL_INCINERATION_SECURITY_MEASURE = 79023,
	// Arcanotron
	SPELL_POWER_GENERATOR = 79624,
	SPELL_ARCANE_ANNIHILATOR = 79710,
	SPELL_POWER_CONVERSION = 79729,
	// Lord Victor Nefarius
	SPELL_GRIP_OF_DEATH = 91849,
	SPELL_ENCASING_SHADOWS = 92023,
	SPELL_OVERCHARGED_POWER_GENERATOR = 91857,
	// Bombe de Poison
	SPELL_FIXER = 80094,
	SPELL_BOMBE = 80092,
};

enum Creatures
{
	DATA_OMNOTRON	= 42186,
	DATA_MAGMATRON	= 42178,
	DATA_TOXITRON	= 42180,
	DATA_ELECTRON	= 42179,
	DATA_ARCANOTRON	= 42166,
	DATA_LORD_VICTOR_NEFARIUS = 41379,
};

enum Summons
{
	MOB_POISON_BOMB = 42897,
};

enum Events
{
	EVENT_SHUTING_DOWN_ELECTRON,
	EVENT_SHUTING_DOWN_MAGMATRON,
	EVENT_SHUTING_DOWN_TOXITRON,
	EVENT_SHUTING_DOWN_ARCANOTRON,
	EVENT_LIGHTNING,
	EVENT_DISCHARGE,
	EVENT_UNSTABLE_SHIELD,
	EVENT_CHEMICAL_BOMB,
	EVENT_POISON_SOAKED_SHELL,
	EVENT_POISON_PROTOCOL,
	EVENT_GRIP_OF_DEATH,
	EVENT_BARRIER,
	EVENT_ACQUIRING_TARGET,
	EVENT_FLAMETHROWER,
	EVENT_INCINERATION_SECURITY_MEASURE,
	EVENT_POWER_GENERATOR,
	EVENT_ARCANE_ANNIHILATOR,
	EVENT_POWER_CONVERSION,
	EVENT_OVERCHARGED_POWER_GENERATOR,
	EVENT_GRIP_ZONE,
	EVENT_ENCASING_SHADOWS,
	EVENT_OVERCHARGED,
};

/*enum
{
    DATA_HEALTH_SYSTEM_OMNITRON     = 201,
    DESPAWN_TIME                = 180000,
}*/

/******************
** Controle System
******************/

/************
** Electron
************/
class boss_electron: public CreatureScript
{
	public :
		boss_electron() : CreatureScript("boss_electron") { }

		struct boss_electronAI : public ScriptedAI 
		{
			boss_electronAI(Creature * pCreature) : ScriptedAI(pCreature)
			{
				pInstance = pCreature->GetInstanceScript();
			}

			InstanceScript* pInstance;
			EventMap events;

			void Reset()
			{
                if (pInstance->GetData(DATA_ELECTRON)==IN_PROGRESS)
                {
                    DATA_MAGMATRON->SetHealth(me->GetHealth());
                    return;
					DATA_TOXITRON->SetHealth(me->GetHealth());
                    return;
					DATA_ARCANOTRON->SetHealth(me->GetHealth());
                    return;
                }
				me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				me->MonsterYell(SAY_AGGRO, 0, 0);
				DoCast(me, SPELL_ACTIVATED);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				me->SetReactState(REACT_AGGRESSIVE);
                DATA_MAGMATRON->SetHealth(me->GetHealth());
				DATA_TOXITRON->SetHealth(me->GetHealth());
				DATA_ARCANOTRON->SetHealth(me->GetHealth());
				EnterPhaseGround();
			}

			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_LIGHTNING, 10000);
				events.ScheduleEvent(EVENT_DISCHARGE, 25000);
				events.ScheduleEvent(EVENT_UNSTABLE_SHIELD, 11500);
				events.ScheduleEvent(EVENT_SHUTING_DOWN_ELECTRON, 65000);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				me->MonsterYell(SAY_DEATH, 0, 0);
			}

			void UpdateAI(const uint32 diff)
			{
                if (!UpdateVictim())
                    return;
					
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch(eventId)
					{
						case EVENT_LIGHTNING:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_LIGHTNING_CONDUCTOR);
							me->MonsterYell(SAY_LIGHTNING, 0, 0);
							events.ScheduleEvent(EVENT_LIGHTNING,10000);
							return;
						case EVENT_DISCHARGE:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_ELECTRICAL_DISCHARGE);
							events.ScheduleEvent(EVENT_DISCHARGE, 25000);
							return;
						case EVENT_UNSTABLE_SHIELD:
							DoCast(me, SPELL_UNSTABLE_SHIELD);
							me->MonsterYell(SAY_SHIELD_ELECTRON, 0, 0);
							events.ScheduleEvent(EVENT_UNSTABLE_SHIELD, 60000);
							return;
						case EVENT_SHUTING_DOWN_ELECTRON:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->AttackStop();
							me->RemoveAllAuras();
							events.ScheduleEvent(EVENT_SHUTING_DOWN_ELECTRON, 65000);
							return;
					}
				
				}
				DoMeleeAttackIfReady();
				
			}
		};
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_electronAI (pCreature);
    }
		
};

/************
** Magmatron
************/
class boss_magmatron : public CreatureScript
{
	public :
		boss_magmatron() : CreatureScript("boss_magmatron") { }

		struct boss_magmatronAI : public ScriptedAI 
		{
			boss_magmatronAI(Creature * pCreature) : ScriptedAI(pCreature)
			{
				pInstance = pCreature->GetInstanceScript();
			}

			InstanceScript* pInstance;
			EventMap events;
			
			void Reset()
			{
				me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoCast(me, SPELL_ACTIVATED);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				me->SetReactState(REACT_AGGRESSIVE);
				DATA_ELECTRON->SetHealth(me->GetHealth());
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_ACQUIRING_TARGET, 15000);
				events.ScheduleEvent(EVENT_INCINERATION_SECURITY_MEASURE, 27000);
				events.ScheduleEvent(EVENT_BARRIER, 30000);
				events.ScheduleEvent(EVENT_SHUTING_DOWN_MAGMATRON, 65000);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				me->MonsterYell(SAY_DEATH, 0, 0);
			}

			void UpdateAI(const uint32 diff)
			{
                if (!UpdateVictim())
                    return;
					
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch(eventId)
					{
						case EVENT_ACQUIRING_TARGET:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_ACQUIRING_TARGET);
							me->MonsterYell(SAY_REROUTING_ENERGY, 0, 0);
							events.ScheduleEvent(EVENT_ACQUIRING_TARGET, 15000);
							return;
						case EVENT_INCINERATION_SECURITY_MEASURE:
							DoCastAOE(SPELL_INCINERATION_SECURITY_MEASURE);
							events.ScheduleEvent(EVENT_INCINERATION_SECURITY_MEASURE, 27000);
							return;
						case EVENT_BARRIER:
							DoCast(me, SPELL_BARRIER);
							me->MonsterYell(SAY_SHIELD_FLAMME, 0, 0);
							events.ScheduleEvent(EVENT_BARRIER, 60000);
							return;
						case EVENT_SHUTING_DOWN_MAGMATRON:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->AttackStop();
							me->RemoveAllAuras();
							events.ScheduleEvent(EVENT_SHUTING_DOWN_MAGMATRON, 65000);
							return;
					}
				
				}
				DoMeleeAttackIfReady();
				
			}
		};
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_magmatronAI (pCreature);
    }
		
};

/************
** Toxitron
************/
class boss_toxitron : public CreatureScript
{
	public :
		boss_toxitron() : CreatureScript("boss_toxitron") { }

		struct boss_toxitronAI : public ScriptedAI 
		{
			boss_toxitronAI(Creature * pCreature) : ScriptedAI(pCreature)
			{
				pInstance = pCreature->GetInstanceScript();
			}

			InstanceScript* pInstance;
			EventMap events;
			
			void Reset()
			{
				me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoCast(me, SPELL_ACTIVATED);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				me->SetReactState(REACT_AGGRESSIVE);
				DATA_ELECTRON->SetHealth(me->GetHealth());
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_CHEMICAL_BOMB, 30000);
				events.ScheduleEvent(EVENT_POISON_PROTOCOL, 41500);
				events.ScheduleEvent(EVENT_POISON_SOAKED_SHELL, 65000);
				events.ScheduleEvent(EVENT_SHUTING_DOWN_TOXITRON, 65000);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				me->MonsterYell(SAY_DEATH, 0, 0);
			}

			void UpdateAI(const uint32 diff)
			{
                if (!UpdateVictim())
                    return;
					
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch(eventId)
					{
						case EVENT_CHEMICAL_BOMB:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_CHEMICAL_BOMB);
							events.ScheduleEvent(EVENT_CHEMICAL_BOMB, 30000);
							return;
						case EVENT_POISON_PROTOCOL:
							for (uint32 i10 = 0; i10 < 8; ++i10)
                                DoCast(me, SPELL_POISON_PROTOCOL+i10);
                            if (Is25ManRaid())
                                for (uint32 i25 = 0; i25 < 15; ++i25)
                                    DoCast(me, SPELL_POISON_PROTOCOL+i25);
							events.ScheduleEvent(EVENT_POISON_PROTOCOL, 41500);
							return;
						case EVENT_POISON_SOAKED_SHELL:
							DoCast(me, SPELL_POISON_SOAKED_SHELL);
							me->MonsterYell(SAY_SHIELD_POISON, 0, 0);
							events.ScheduleEvent(EVENT_POISON_SOAKED_SHELL, 65000);
							return;
						case EVENT_SHUTING_DOWN_TOXITRON:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->AttackStop();
							me->RemoveAllAuras();
							events.ScheduleEvent(EVENT_SHUTING_DOWN_TOXITRON, 65000);
							return;
					}
				
				}
				DoMeleeAttackIfReady();
				
			}
		};
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_toxitronAI (pCreature);
    }
		
};

/*************
** Arcanotron
*************/
class boss_arcanotron : public CreatureScript
{
	public :
		boss_arcanotron() : CreatureScript("boss_arcanotron") { }

		struct boss_arcanotronAI : public ScriptedAI 
		{
			boss_arcanotronAI(Creature * pCreature) : ScriptedAI(pCreature)
			{
				pInstance = pCreature->GetInstanceScript();
			}

			InstanceScript* pInstance;
			EventMap events;
			
			void Reset()
			{
				me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoCast(me, SPELL_ACTIVATED);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				me->SetReactState(REACT_AGGRESSIVE);
				DATA_ELECTRON->SetHealth(me->GetHealth());
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_POWER_CONVERSION, 10000);
				events.ScheduleEvent(EVENT_POWER_GENERATOR, 30000);
				events.ScheduleEvent(EVENT_ARCANE_ANNIHILATOR, 8000);
				events.ScheduleEvent(EVENT_SHUTING_DOWN_ARCANOTRON, 65000);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				me->MonsterYell(SAY_DEATH, 0, 0);
			}

			void UpdateAI(const uint32 diff)
			{
                if (!UpdateVictim())
                    return;
					
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch(eventId)
					{
						case EVENT_POWER_CONVERSION:
							DoCast(me, SPELL_POWER_CONVERSION);
							me->MonsterYell(SAY_SHIELD_ARCANOTRON, 0, 0);
							events.ScheduleEvent(EVENT_POWER_CONVERSION, 60000);
							return;
						case EVENT_POWER_GENERATOR:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,1,100,true))
                            DoCast(target, SPELL_POWER_GENERATOR);
							events.ScheduleEvent(EVENT_POWER_GENERATOR, 30000);
							return;
						case EVENT_ARCANE_ANNIHILATOR:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                            DoCast(target, SPELL_ARCANE_ANNIHILATOR);
							events.ScheduleEvent(EVENT_ARCANE_ANNIHILATOR, 8000);
							return;
						case EVENT_SHUTING_DOWN_ARCANOTRON:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->AttackStop();
							me->RemoveAllAuras();
							events.ScheduleEvent(EVENT_SHUTING_DOWN_ARCANOTRON, 65000);
							return;
					}
				
				}
				DoMeleeAttackIfReady();
				
			}
		};
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_arcanotronAI (pCreature);
    }
		
};

/**********************
** Lord Victor Nefarius
***********************/
class npc_nefarius : public CreatureScript
{
	public :
		npc_nefarius() : CreatureScript("npc_nefarius") { }

		struct npc_nefariusAI : public ScriptedAI 
		{
			npc_nefariusAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			InstanceScript* pInstance;
			EventMap events;

			void EnterCombat(Unit * /*who*/)
			{
				SetCombatMovement(false);
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_GRIP_ZONE, 40000);
				events.ScheduleEvent(EVENT_ENCASING_SHADOWS, 100000);
				events.ScheduleEvent(EVENT_OVERCHARGED, 40000);
			}

			void UpdateAI(const uint32 diff)
			{
                if (!UpdateVictim())
                    return;
					
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch(eventId)
					{
						if (IsHeroic())
						{	
							case EVENT_GRIP_ZONE :
							if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 1, 10.0f, true))
							DoCast(target, SPELL_GRIP_OF_DEATH);
							events.ScheduleEvent(EVENT_GRIP_ZONE, 40000);
							return;
							case EVENT_ENCASING_SHADOWS :
							if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0, 80.0f, true))
							DoCast(target, SPELL_ENCASING_SHADOWS);
							events.ScheduleEvent(EVENT_ENCASING_SHADOWS, 100000);
							return;
							case EVENT_OVERCHARGED :
							if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0, 100, true))
							DoCast(target, SPELL_OVERCHARGED_POWER_GENERATOR);
							events.ScheduleEvent(EVENT_OVERCHARGED, 40000);
							return;
						}
					}
				}
			}
		};
		
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_nefariusAI (pCreature);
    }
		
};

/**************
** Poison Bomb
**************/
class npc_poison_bomb : public CreatureScript
{
    public:
        npc_poison_bomb() : CreatureScript("npc_poison_bomb") { }

        struct npc_poison_bombAI : public ScriptedAI
        {
			npc_poison_bombAI(Creature * pCreature) : ScriptedAI(pCreature) {}
			
			uint32 uiFixe;
			uint32 uiBombeFixe;
			
			void Reset()
			{
				uiFixe = 2000;
				uiBombeFixe = 20000;
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiFixe <= uiDiff)
				{
					if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 1, 100, true))
                    DoCast(target, SPELL_FIXER);
					uiFixe = 2000;
				} else uiFixe -= uiDiff;
				
				if(uiBombeFixe <= uiDiff)
				{
					DoCastAOE(SPELL_BOMBE);
					uiBombeFixe = 20000;
				} else uiBombeFixe -= uiDiff;
				
				DoMeleeAttackIfReady();
			}
		};

    CreatureAI* GetAI(Creature* creature) const
	{
        return new npc_poison_bombAI(creature);
    }
};

void AddSC_boss_omnitron_defense_system()
{
	//new base_gigantron();
	new boss_magmatron();
	new boss_toxitron();
	new boss_electron();
	new boss_arcanotron();
	new npc_nefarius();
	new npc_poison_bomb();
}