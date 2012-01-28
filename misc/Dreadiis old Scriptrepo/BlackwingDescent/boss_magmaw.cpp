/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Vehicle.h"

enum Spells
{
	// Parasite de lave
	SPELL_INFECTION = 78941,
	// Magmaw
	SPELL_MAGMA_SPIT = 78068,
	SPELL_PILLAR_FLAME = 77971,
	SPELL_LAVA_SPEW = 77690,
	SPELL_MASSIV_CRASH = 91921,
	SPELL_MUTILATION = 78412,
	SPELL_SWELTERING_ARMOR = 78199,
};

enum Creatures
{
	DATA_HEAD_MAGMAW = 42347,
	DATA_MAGMAW	= 41570,
};

enum Summons
{
	NPC_VERS = 42321,
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
	EVENT_VEHICULE,
};

/***************
** Magmaegueule
****************/
class boss_magmaw : public CreatureScript
{
    public:
        boss_magmaw() : CreatureScript("boss_magmaw") { }

        struct boss_magmawAI : public ScriptedAI
        {
			boss_magmawAI(Creature * pCreature) : ScriptedAI(pCreature), Summons(me)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;
			EventMap events;
			SummonList Summons;
			
			void EnterCombat(Unit * /*who*/)
			{
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_SUMMON, 10000);
			}
			
			void JustDied(Unit* /*Killer*/)
			{
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
								if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
								DoSummon(pTarget, NPC_VERS, 0, TEMPSUMMON_DEAD_DESPAWN);
								events.ScheduleEvent(EVENT_SUMMON, 10000);
								return;
						}
					}
				DoMeleeAttackIfReady();
			}
		};

    CreatureAI* GetAI(Creature* creature) const
    {
		return new boss_magmawAI(creature);
    }
};

/****************
** Head Of Magmaw
*****************/
class npc_head_magmaw : public CreatureScript
{
public:
    npc_head_magmaw() : CreatureScript("npc_head_magmaw") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_head_magmawAI(pCreature);
    }

    struct npc_head_magmawAI : public ScriptedAI
    {
        npc_head_magmawAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            pInstance = me->GetInstanceScript();
            SetCombatMovement(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            Reset();
        }

        uint32 uiStoneGripTimer;
        uint64 uiGrippedTargets[1];
        uint32 uiPermittedDamage;
        InstanceScript * pInstance;

        void EnterCombat(Unit* /*who*/)
        {
            EncounterInCombat(me, pInstance);
            uiStoneGripTimer = 30000;
        }

        void Reset()
        {
            memset(&uiGrippedTargets, 0, sizeof(uiGrippedTargets));
            uiPermittedDamage = RAID_MODE(100000, 480000);
            uiStoneGripTimer = 0;
            DoCast(SPELL_ARM_VISUAL);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if (uiGrippedTargets[0] == 0)
                return;

            if (damage > uiPermittedDamage)
                uiPermittedDamage = 0;
            else
                uiPermittedDamage -= damage;

            if (!uiPermittedDamage)
                ReleaseGrabbedPlayers();
        }

        void JustDied(Unit* /*who*/)
        {
            ReleaseGrabbedPlayers();

            if (Creature* Kologarn = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(TYPE_KOLOGARN) : 0))
            {
                if (Kologarn->isAlive())
                {
                    Kologarn->CastSpell(Kologarn, SPELL_ARM_DEAD_DAMAGE, true);
                    DoScriptText(SAY_RIGHT_ARM_GONE, Kologarn);
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (uiStoneGripTimer <= diff)
            {
                GrabPlayers();
                if (Creature* Kologarn = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(TYPE_KOLOGARN) : 0))
                    DoScriptText(SAY_GRAB_PLAYER, Kologarn);

                uiStoneGripTimer = urand(30000, 35000);
                uiPermittedDamage = RAID_MODE(100000, 480000);
            }
            else
                uiStoneGripTimer -= diff;

        }

        void ReleaseGrabbedPlayers()
        {
             for (uint8 i = 0; i < RAID_MODE(1, 3); ++i)
                    if (Unit* grabbed = Unit::GetUnit(*me, uiGrippedTargets[i]))
                        me->CastSpell(grabbed, SPELL_STONE_GRIP_CANCEL, false);
        }

        void GrabPlayers()
        {
            for (uint8 i = 0; i < RAID_MODE(1, 3); ++i)
            {
                if (Unit* grabbed = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                {
                    DoCast(grabbed, SPELL_STONE_GRIP);
                    uiGrippedTargets[i] = grabbed->GetGUID();
                }
            }
        }
    };
};

/*******
** Vers
*******/
class mob_vers: public CreatureScript
{
    public:
        mob_vers() : CreatureScript("mob_vers") { }

        struct mob_versAI : public ScriptedAI
        {
			mob_versAI(Creature* creature) : ScriptedAI(creature) { }
        
        uint32 uiCheckDistanceTimer;

        void Reset()
        {
            uiCheckDistanceTimer = 2*IN_MILLISECONDS;
        }

        void EnterCombat(Unit* /*pWho*/) { }
        
        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;
            
            if (me->IsWithinDistInMap(me->getVictim(), 2.0f))
            {
                if (uiCheckDistanceTimer <= uiDiff)
                {
                    me->CastSpell(me->getVictim(), 94679 , true);

                    uiCheckDistanceTimer = 86400*IN_MILLISECONDS;
                } else uiCheckDistanceTimer -= uiDiff;
            }

            DoMeleeAttackIfReady();
			}
		};

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_versAI(creature);
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

/***************************
** Spell Parasitic Infection
****************************/
class spell_parasitic_infection : public SpellScriptLoader
{
    public:
        spell_parasitic_infection() : SpellScriptLoader("spell_parasitic_infection") { }

        class spell_parasitic_infection_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_parasitic_infection_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit * caster = GetCaster();
                for (int i = 0; i < 2; ++i)
                {
                    Unit* Summoned = caster->SummonCreature(42321, caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 240000);
                    /*if (Summoned)
                    {
                        Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
                        if (pTarget)
                            Summoned->AddThreat(pTarget, 1.0f);
                    }*/
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_parasitic_infection_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_parasitic_infection_AuraScript();
        }
};

void AddSC_boss_magmaw()
{
	new boss_magmaw();
	new mob_vers();
	new npc_head_magmaw();
	//new npc_nefarius();
    new spell_parasitic_infection();
};