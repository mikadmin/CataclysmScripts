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
	//SPELL_SHUTING_DOWN = 78746, // Golem désactivé pendant 1 min
	//SPELL_ACTIVATED = 78740, // Golem activé pendant 1 min
	// Electron
	SPELL_LIGHTNING_CONDUCTOR = 79888, // Debuf 1 seul joueur target
	SPELL_ELECTRICAL_DISCHARGE = 91465,
	SPELL_UNSTABLE_SHIELD = 91447, // 40s
	// Toxitron
	SPELL_CHEMICAL_BOMB = 80157,
	SPELL_POISON_SOAKED_SHELL = 91501, // 40s
	SPELL_POISON_PROTOCOL = 91513,
	// Magmatron
	SPELL_BARRIER = 79582, // 40s
	SPELL_ACQUIRING_TARGET = 79501,
	SPELL_FLAMETHROWER = 79504,
	SPELL_INCINERATION_SECURITY_MEASURE = 79023,
	// Arcanotron
	SPELL_POWER_GENERATOR = 79624, // 40s
	SPELL_ARCANE_ANNIHILATOR = 79710, // Decast
	SPELL_POWER_CONVERSION = 79729,
	// Lord Victor Nefarius
	SPELL_GRIP_OF_DEATH = 91849, // Seulement en mode Héroïque
	SPELL_ENCASING_SHADOWS = 92023, // Seulement en mod Héroïque
	SPELL_OVERCHARGED_POWER_GENERATOR = 91857, // Seulement en mode Héroïque
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
	DATA_LORD_VICTOR_NEFARIUS = 41379, // Total Imune
};

enum Summons
{
	MOB_POISON_BOMB = 42897, // Aucune imune
};

enum Events
{
	//EVENT_SHUTING_DOWN,
	//EVENT_ACTIVATED,
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
	EVENT_ENCASING_SHADOWS,
	EVENT_INCINERATION_SECURITY_MEASURE,
	EVENT_POWER_GENERATOR,
	EVENT_ARCANE_ANNIHILATOR,
	EVENT_POWER_CONVERSION,
	EVENT_OVERCHARGED_POWER_GENERATOR,
};

/******************
** Controle System
******************/
/*class boss_system_defense_omnotron_controller : public CreatureScript
{
    public:
        boss_system_defense_omnotron_controller() : CreatureScript("boss_system_defense_omnotron_controller") { }

        struct boss_system_defense_omnotron_controllerAI : public ScriptedAI
        {
			boss_system_defense_omnotron_controllerAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
					
			}
		};

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_system_defense_omnotron_controllerAI(creature);
        }
};*/

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
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_FIXER);
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

/************
** Magmatron
************/
class boss_magmatron : public CreatureScript
{
	public :
		boss_magmatron() : CreatureScript("boss_magmatron") { }

		struct boss_magmatronAI : public ScriptedAI 
		{
			boss_magmatronAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			InstanceScript* pInstance;
			EventMap events;
			
			void Reset()
			{
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_ACQUIRING_TARGET, 15000);
				events.ScheduleEvent(EVENT_INCINERATION_SECURITY_MEASURE, 27000);
				events.ScheduleEvent(EVENT_BARRIER, 30000);
				/*events.ScheduleEvent(EVENT_ACTIVATED, 45000);
				events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);*/
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
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
						/*case EVENT_ACTIVATED:
							DoCast(me, SPELL_ACTIVATED);
							DoScriptText(SAY_ACTIVATION_MAGMATRON, me);
							me->SetReactState(REACT_AGGRESSIVE);
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							DoZoneInCombat();
							events.ScheduleEvent(EVENT_ACTIVATED, 45000);
							return;*/
						case EVENT_ACQUIRING_TARGET:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_ACQUIRING_TARGET);
							DoScriptText(SAY_REROUTING_ENERGY, me);
							events.ScheduleEvent(EVENT_ACQUIRING_TARGET, 15000);
							return;
						case EVENT_INCINERATION_SECURITY_MEASURE:
							DoCastAOE(SPELL_INCINERATION_SECURITY_MEASURE);
							events.ScheduleEvent(EVENT_INCINERATION_SECURITY_MEASURE, 27000);
							return;
						case EVENT_BARRIER:
							DoCast(me, SPELL_BARRIER);
							DoScriptText(SAY_SHIELD_FLAMME, me);
							events.ScheduleEvent(EVENT_BARRIER, 60000);
							return;
						/*case EVENT_SHUTING_DOWN:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							me->AttackStop();
							me->RemoveAllAuras();
							events.Reset();
							events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);
							return;*/
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
			boss_toxitronAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			InstanceScript* pInstance;
			EventMap events;
			
			void Reset()
			{
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_CHEMICAL_BOMB, 30000);
				events.ScheduleEvent(EVENT_POISON_PROTOCOL, 11500);
				events.ScheduleEvent(EVENT_POISON_SOAKED_SHELL, 22000);
				/*events.ScheduleEvent(EVENT_ACTIVATED, 45000);
				events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);*/
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
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
						/*case EVENT_ACTIVATED:
							DoCast(me, SPELL_ACTIVATED);
							DoScriptText(SAY_ACTIVATION_TOXITRON, me);
							me->SetReactState(REACT_AGGRESSIVE);
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							DoZoneInCombat();
							events.ScheduleEvent(EVENT_ACTIVATED, 45000);
							return;*/
						case EVENT_CHEMICAL_BOMB:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_CHEMICAL_BOMB);
							events.ScheduleEvent(EVENT_CHEMICAL_BOMB, 30000);
							return;
						case EVENT_POISON_PROTOCOL:
							DoCast(SPELL_POISON_PROTOCOL);
							events.ScheduleEvent(EVENT_POISON_PROTOCOL, 11500);
							return;
						case EVENT_POISON_SOAKED_SHELL:
							DoCast(me, SPELL_POISON_SOAKED_SHELL);
							DoScriptText(SAY_SHIELD_POISON, me);
							events.ScheduleEvent(EVENT_POISON_SOAKED_SHELL, 45000);
							return;
						/*case EVENT_SHUTING_DOWN:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							me->AttackStop();
							me->RemoveAllAuras();
							events.Reset();
							events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);
							return;*/
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

/************
** Electron
************/
class boss_electron: public CreatureScript
{
	public :
		boss_electron() : CreatureScript("boss_electron") { }

		struct boss_electronAI : public ScriptedAI 
		{
			boss_electronAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			InstanceScript* pInstance;
			EventMap events;

			void Reset()
			{
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_LIGHTNING, 10000);
				events.ScheduleEvent(EVENT_DISCHARGE, 25000);
				events.ScheduleEvent(EVENT_UNSTABLE_SHIELD, 11500);
				/*events.ScheduleEvent(EVENT_ACTIVATED, 45000);
				events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);*/
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
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
						/*case EVENT_ACTIVATED:
							DoCast(me, SPELL_ACTIVATED);
							DoScriptText(SAY_ACTIVATION_ELECTRON, me);
							me->SetReactState(REACT_AGGRESSIVE);
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							DoZoneInCombat();
							events.ScheduleEvent(EVENT_ACTIVATED, 45000);
							return;*/
						case EVENT_LIGHTNING:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_LIGHTNING_CONDUCTOR);
							DoScriptText(SAY_LIGHTNING, me);
							events.ScheduleEvent(EVENT_LIGHTNING,10000);
							return;
						case EVENT_DISCHARGE:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_ELECTRICAL_DISCHARGE);
							events.ScheduleEvent(EVENT_DISCHARGE, 25000);
							return;
						case EVENT_UNSTABLE_SHIELD:
							DoCast(me, SPELL_UNSTABLE_SHIELD);
							DoScriptText(SAY_SHIELD_ELECTRON, me);
							events.ScheduleEvent(EVENT_UNSTABLE_SHIELD, 60000);
							return;
						/*case EVENT_SHUTING_DOWN:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							me->AttackStop();
							me->RemoveAllAuras();
							events.Reset();
							events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);
							return;*/
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

/*************
** Arcanotron
*************/
class boss_arcanotron : public CreatureScript
{
	public :
		boss_arcanotron() : CreatureScript("boss_arcanotron") { }

		struct boss_arcanotronAI : public ScriptedAI 
		{
			boss_arcanotronAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			InstanceScript* pInstance;
			EventMap events;
			
			void Reset()
			{
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_POWER_CONVERSION, 10000);
				events.ScheduleEvent(EVENT_POWER_GENERATOR, 30000);
				events.ScheduleEvent(EVENT_ARCANE_ANNIHILATOR, 8000);
				/*events.ScheduleEvent(EVENT_ACTIVATED, 45000);
				events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);*/
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
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
						/*case EVENT_ACTIVATED:
							DoCast(me, SPELL_ACTIVATED);
							DoScriptText(SAY_ACTIVATION_ARCANOTRON, me);
							me->SetReactState(REACT_AGGRESSIVE);
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							DoZoneInCombat();
							events.ScheduleEvent(EVENT_ACTIVATED, 45000);
							return;*/
						case EVENT_POWER_CONVERSION:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_POWER_CONVERSION);
							DoScriptText(SAY_SHIELD_ARCANOTRON, me);
							events.ScheduleEvent(EVENT_POWER_CONVERSION, 60000);
							return;
						case EVENT_POWER_GENERATOR:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_POWER_GENERATOR);
							events.ScheduleEvent(EVENT_POWER_GENERATOR, 30000);
							return;
						case EVENT_ARCANE_ANNIHILATOR:
							if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
							DoCast(pTarget, SPELL_ARCANE_ANNIHILATOR);
							events.ScheduleEvent(EVENT_ARCANE_ANNIHILATOR, 8000);
							return;
						/*case EVENT_SHUTING_DOWN:
							DoCast(me, SPELL_SHUTING_DOWN);
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
							me->AttackStop();
							me->RemoveAllAuras();
							events.Reset();
							events.ScheduleEvent(EVENT_SHUTING_DOWN, 60000);
							return;*/
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
/*class npc_nefarius : public CreatureScript
{
	public :
		npc_nefarius() : CreatureScript("npc_nefarius") { }

		struct npc_nefariusAI : public ScriptedAI 
		{
			npc_nefariusAI(Creature * pCreature) : ScriptedAI(pCreature) {}


			InstanceScript* pInstance;
			
			uint32 uiBarrageTimer;
			uint32 uiBreathTimer;
			uint32 uiFireballTimer;
			uint32 uiFireballTimer;

			void Reset()
			{
				uiBarrageTimer = 10000;
				uiBreathTimer = 60000;
				uiFireballTimer = 10000;
				uiFireballTimer = 10000;
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiBarrageTimer <= uiDiff)
				{
					DoCastVictim(SPELL_BARRAGE);
					uiBarrageTimer = 10000;
				} else uiBarrageTimer -= uiDiff;
				
				if(uiBreathTimer <= uiDiff)
				{
					DoCastVictim(SPELL_BREATH);
					uiBreathTimer = 60000;
				} else uiBreathTimer -= uiDiff;
				
				if(uiFireballTimer <= uiDiff)
				{
					DoCastVictim(SPELL_FIREBALL);
					uiFireballTimer = 10000;
				} else uiFireballTimer -= uiDiff;
				
				if(uiFireballTimer <= uiDiff)
				{
					DoCastVictim(SPELL_FIREBALL);
					uiFireballTimer = 10000;
				} else uiFireballTimer -= uiDiff;

			}
		};
		
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_nefariusAI (pCreature);
    }
		
};*/

void AddSC_boss_omnitron_defense_system()
{
	new boss_magmatron();
	new boss_toxitron();
	new boss_electron();
	new boss_arcanotron();
	//new npc_nefarius();
	new npc_poison_bomb();
}