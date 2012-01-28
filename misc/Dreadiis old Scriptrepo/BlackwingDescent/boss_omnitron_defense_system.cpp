/*
// Lord Victor Nefarius 41379
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc2`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
(41379,-2000000, "Hmm... the Omnotron Defense System. Centuries ago these constructs were considered the Dwarves greatest technical achievements. With so many counters to each construct's attacks. I''ll have to rectify these designs for them to provide me any entertainement.", NULL, 0, 14, 0, 0, NULL),
(41379,-2000001, "Stupid Dwarnes and you fascination with runes! Why would you create something that would help your enemy?", NULL, 0, 14, 0, 0, NULL),
(41379,-2000002, "Lightning conductor works much better in a crowd,yes?", NULL, 0, 14, 0, 0, NULL),
(41379,-2000003, "Were you planning on using Toxitron's chemical to damage the other construcs?Clever plan, let me ruin that for you.", NULL, 0, 14, 0, 0, NULL),
(41379,-2000004, "You would like to move away from that, wouldn't you?Too bad.", NULL, 0, 14, 0, 0, NULL);

// Omnotron 42186
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc2`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
(42186,-2000005, "Toxitron unit shield system onlines.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000006, "Magmatron unit shield system onlines.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000007, "Electron unit shield system onlines.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000008, "Arcanotron unit shield system onlines.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000009, "Toxitron unit activated.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000010, "Magmatron unit activated.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000011, "Electron unit activated.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000012, "Arcanotron unit activated.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000013, "Rerouting exces energy to Magmatron unit. Engage flamethrower device.", NULL, 0, 14, 0, 0, NULL),
(42186,-2000014, "Defense systems obliterated. Powering down....", NULL, 0, 14, 0, 0, NULL);
*/

#include "ScriptPCH.h"

enum Yells
{
	SAY_AGGRO	= -2000000,
	SAY_STORY	= -2000001,
	SAY_LIGHTNING	= -2000002,
	SAY_TOXITRON_CHEMICAL	= -2000003,
	SAY_TOO_BAD	= -2000004,
	SAY_SHIELD_POISON	= -2000005,
	SAY_SHIELD_FLAMME	= -2000006,
	SAY_SHIELD_ELECTRON	= -2000007,
	SAY_SHIELD_ARCANOTRON	= -2000008,
	SAY_ACTIVATION_TOXITRON	= -2000009,
	SAY_ACTIVATION_MAGMATRON	= -2000010,
	SAY_ACTIVATION_ELECTRON	= -2000011,
	SAY_ACTIVATION_ARCANOTRON	= -2000012,
	SAY_REROUTING_ENERGY	= -2000013,
	SAY_DEATH	= -2000014,
};

enum Spells
{
	// Omnitron
	SPELL_SHUTING_DOWN = 78746, // Golem désactivé pendant 1 min
	SPELL_ACTIVATED = 78740, // Golem activé pendant 1 min
	// Electron
	SPELL_LIGHTNING_CONDUCTOR = 79888, // Debuf 1 seul joueur target
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
	SPELL_ARCANE_ANNIHILATOR = 79710, // Decast
	SPELL_POWER_CONVERSION = 79729,
	// Lord Victor Nefarius
	SPELL_GRIP_OF_DEATH = 91849, // Seulement en mode Héroïque
	SPELL_ENCASING_SHADOWS = 92023, // Seulement en mod Héroïque
	SPELL_OVERCHARGED_POWER_GENERATOR = 91857, // Seulement en mode Héroïque
	// Bombe de Poison
	SPELL_FIXER = 80094,
};

enum BossOmnotron
{
	BOSS_MAGMATRON	= 42178,
	BOSS_TOXITRON	= 42180,
	BOSS_ELECTRON	= 42179,
	BOSS_ARCANOTRON	= 42166,
	NPC_LORD_VICTOR_NEFARIUS = 41379, // Total Imune
};

enum Summons
{
	MOB_POISON_BOMB = 42897, // Aucune imune
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
			
			void Reset()
			{
				uiFixe = 20000;
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiFixe <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_FIXER);
					uiFixe = 20000;
				} else uiFixe -= uiDiff;
				
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
			
			uint32 uiAquisitionTimer;
			uint32 uiIncinerationTimer;
			uint32 uiBarrierTimer;

			void Reset()
			{
				uiAquisitionTimer = 15000;
				uiIncinerationTimer = 27000;
				uiBarrierTimer = 30000;
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				DoScriptText(SAY_ACTIVATION_MAGMATRON, me);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiAquisitionTimer <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_ACQUIRING_TARGET);
					DoScriptText(SAY_REROUTING_ENERGY, me);
					DoCast(SPELL_FLAMETHROWER);
					uiAquisitionTimer = 15000;
				} else uiAquisitionTimer -= uiDiff;
				
				if(uiIncinerationTimer <= uiDiff)
				{
					DoCastAOE(SPELL_INCINERATION_SECURITY_MEASURE);
					uiIncinerationTimer = 27000;
				} else uiIncinerationTimer -= uiDiff;
				
				if(uiBarrierTimer <= uiDiff)
				{
					DoCast(me, SPELL_BARRIER);
					DoScriptText(SAY_SHIELD_FLAMME, me);
					uiBarrierTimer = 30000;
				} else uiBarrierTimer -= uiDiff;

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
			
			uint32 uiChemicalTimer;
			uint32 uiPoisonProtocolTimer;
			uint32 uiCarrapaceTimer;

			void Reset()
			{
				uiChemicalTimer = 30000;
				uiPoisonProtocolTimer = 11500;
				uiCarrapaceTimer = 22000;
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				DoScriptText(SAY_ACTIVATION_TOXITRON, me);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiChemicalTimer <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_CHEMICAL_BOMB);
					DoScriptText(SAY_TOXITRON_CHEMICAL, me);
					uiChemicalTimer = 30000;
				} else uiChemicalTimer -= uiDiff;
				
				if(uiPoisonProtocolTimer <= uiDiff)
				{
					DoCast(SPELL_POISON_PROTOCOL);
					uiPoisonProtocolTimer = 11500;
				} else uiPoisonProtocolTimer -= uiDiff;
				
				if(uiCarrapaceTimer <= uiDiff)
				{
					DoCast(me, SPELL_POISON_SOAKED_SHELL);
					DoScriptText(SAY_SHIELD_POISON, me);
					uiCarrapaceTimer = 22000;
				} else uiCarrapaceTimer -= uiDiff;

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
			
			uint32 uiLightningTimer;
			uint32 uiConductorTimer;
			uint32 uiElecShieldTimer;

			void Reset()
			{
				uiLightningTimer = 10000;
				uiConductorTimer = 25000;
				uiElecShieldTimer = 11500;
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				DoScriptText(SAY_ACTIVATION_ELECTRON, me);
			}

			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
			}
			
			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiLightningTimer <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_LIGHTNING_CONDUCTOR);
					DoScriptText(SAY_LIGHTNING, me);
					uiLightningTimer = 10000;
				} else uiLightningTimer -= uiDiff;
				
				if(uiConductorTimer <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_ELECTRICAL_DISCHARGE);
					uiConductorTimer = 25000;
				} else uiConductorTimer -= uiDiff;
				
				if(uiElecShieldTimer <= uiDiff)
				{
					DoCast(me, SPELL_UNSTABLE_SHIELD);
					DoScriptText(SAY_SHIELD_ELECTRON, me);
					uiElecShieldTimer = 11500;
				} else uiElecShieldTimer -= uiDiff;

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
			
			uint32 uiConversionTimer;
			uint32 uiGeneratorTimer;
			uint32 uiArcaneTimer;

			void Reset()
			{
				uiConversionTimer = 10000;
				uiGeneratorTimer = 30000;
				uiArcaneTimer = 8000;
			}
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				DoScriptText(SAY_ACTIVATION_ARCANOTRON, me);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiConversionTimer <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_POWER_CONVERSION);
					DoScriptText(SAY_SHIELD_ARCANOTRON, me);
					uiConversionTimer = 10000;
				} else uiConversionTimer -= uiDiff;
				
				if(uiGeneratorTimer <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_POWER_GENERATOR);
					uiGeneratorTimer = 30000;
				} else uiGeneratorTimer -= uiDiff;
				
				if(uiArcaneTimer <= uiDiff)
				{
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_ARCANE_ANNIHILATOR);
					uiArcaneTimer = 8000;
				} else uiArcaneTimer -= uiDiff;

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