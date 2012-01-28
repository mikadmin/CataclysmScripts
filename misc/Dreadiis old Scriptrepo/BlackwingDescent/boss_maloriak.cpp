/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum Spells
{
	// Abération
	SPELL_CROISSANCE = 77987, // Catalyseur de croissance
	
	// Sujet Primordial
	SPELL_FIXE = 78617, // Fixer
	SPELL_POURFENDRE = 78034, // Pourfendre
	SPELL_SAUVAGE = 77987, // Catalyseur de croissance
	
	// Maloriak
	// Phase 1
	SPELL_ORAGE_ARCANIQUE = 77896, // Peu être decast
	SPELL_REMEDE = 92967, // tooutes les 1 min
	
	//Fiole Rouge
	SPELL_FLAME_CONSO = 92973, // Flammes Consumantes
	SPELL_DEFLAG_LAVA = 92968, // Déflagration Brûlante
	
	// Summon Abération
	SPELL_ABERATION_LIBRE = 92703, // Libération des aberrations
	
	//Fiole Bleu
	SPELL_FRISSON_MORDANT = 77760, // Frisson mordant
	SPELL_GEL_INSTANT = 77699, // Gel instantané
	
	//Fiole Verte - 30% PV
	SPELL_GEL_DELIRE = 77615, // Gelée débilitante
	
	// Phase 2 - 25% PV
	SPELL_JET_MAGMA = 78095, // Jets de magma
	SPELL_ZERO_ABSOLUE = 78208, // Zéro absolu
	SPELL_NOVA_ACIDE = 93012, // Nova d'acide
	SPELL_LIBRE_ALL = 77991, // Libération de tous les serviteurs
};

enum Creatures
{
	DATA_ABERATION = 41440,
	DATA_SUJET = 41841,
	DATA_MALORIAK = 41378,
};

enum Summons
{
	NPC_ABERATION = 41440, // Abération
	NPC_SUJET = 41841, // Sujet Primordial - imune au Taunt
};

const float SummonPos[MAX_SUMMON_POS][2] =
{
    {-137.344864f, -437.528046f, 73.374397f, 6.282065f},
    {-74.835655f, -437.843536f, 73.378448f, 3.061933f},
    {-105.996353f, -408.253510f, 76.613503f, 4.652360f},
};

enum Events
{
	EVENT_SUMMON,
};

enum Phases
{
    PHASE_NONE          = 0,
	PHASE_COMBAT_1      = 1,
    PHASE_COMBAT_2      = 2,
    PHASE_COMBAT_3      = 3,
};

/**********
** Maloriak
***********/
class boss_maloriak : public CreatureScript
{
    public:
        boss_maloriak() : CreatureScript("boss_maloriak") { }

		CreatureAI* GetAI(Creature* creature) const
		{
			return new boss_maloriakAI(creature);
		}
		
        struct boss_maloriakAI : public BossAI
        {
			boss_maloriakAI(Creature *c) : BossAI(c, DATA_MALORIAK), Summons(me)
			{
                phase = PHASE_NONE;
            }
			
			InstanceScript* pInstance;
			EventMap events;
			
			void EnterCombat(Unit * /*who*/)
			{
				DoScriptText(SAY_AGGRO, me);
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_SUMMON, 10000);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
				DoScriptText(SAY_DEATH, me);
				summons.DespawnAll();
			}
		
			void JustSummoned(Creature *summon)
			{
				summons.Summon(summon);
				summon->setActive(true);
				summon->AI()->DoZoneInCombat();
			}

			void SummonUndead(uint32 entry, uint32 num)
			{
				for (uint32 i = 0; i < num; ++i)
				{
					uint32 pos = rand()%MAX_SUMMON_POS;
					me->SummonCreature(entry, SummonPos[pos][0], SummonPos[pos][1], SummonPos[pos][2],
						SummonPos[pos][3], TEMPSUMMON_CORPSE_DESPAWN, 60000);
				}
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
					
					events.Update(diff);

					while (uint32 eventId = events.ExecuteEvent())
					{
						switch(eventId)
						{
							case EVENT_SUMMON:

								return;
						}
					}
				DoMeleeAttackIfReady();
			}
		};

    private:
        void _SetPhase(Phases newPhase)
            {
                phase = newPhase;
                events.SetPhase(newPhase);
            }
			Phases phase;
};

/***********
** Abération
************/
/*class mob_aberation: public CreatureScript
{
    public:
        mob_aberation() : CreatureScript("mob_aberation") { }

        struct mob_aberationAI : public ScriptedAI
        {
			mob_aberationAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
					
			}
		};

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_aberationAI(creature);
        }
};*/

/******************
** Sujet Primordial
*******************/
/*class mob_sujet: public CreatureScript
{
    public:
        mob_sujet() : CreatureScript("mob_sujet") { }

        struct mob_sujetAI : public ScriptedAI
        {
			mob_sujetAI(Creature * pCreature) : ScriptedAI(pCreature) {}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
					
			}
		};

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_sujetAI(creature);
        }
};*/

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
		
			void Reset()
			{
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
			}
		};
		
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_nefariusAI (pCreature);
    }
		
};*/

void AddSC_boss_maloriak()
{
	new boss_maloriak();
	//new mob_aberation();
	//new mob_sujet();
	//new npc_nefarius();
};