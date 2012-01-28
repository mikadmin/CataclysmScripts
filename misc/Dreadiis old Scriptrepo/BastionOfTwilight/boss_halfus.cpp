/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "the_bastion_of_twilight.h"
#include <cstring>

//enum Texts
#define SAY_AGGRO "The wyrms will eat well tonight !"
#define SAY_DIED "The burden of the damned falls upon you ! Aaaaaah....."

enum Spells
{
	// Halfus
    SPELL_DRAGON_VENGEANCE      = 87683,
    SPELL_BERSERK               = 26662,
    SPELL_MALEVOLENT_STRAKES    = 39171,
    SPELL_SHADOW_WRAPPED        = 83952,
    SPELL_BIND_WILL             = 83432,
    SPELL_FRENZIED_ASSAULT      = 83693,
    SPELL_FURIOUS_ROAR          = 83710,
    SPELL_SHADOW_NOVA           = 83703,

    // minion's spells
    SPELL_CYCLONE_WINDS         = 83612,
    SPELL_STONE_TOUCH           = 83603,

    SPELL_FREE_DRAGON           = 83447,

    // proto-behemoth spells
    SPELL_SUPERHEATED_BREATH    = 83956,
    SPELL_DANCING_FLAMES        = 84106,
    SPELL_FIREBALL_BARRAGE      = 83706,
    SPELL_SCORCHING_BREATH      = 83707,
    SPELL_FIREBALL              = 86058,
};

enum Events
{
    EVENT_NONE,
    EVENT_BERSERK,
    EVENT_SHADOW_NOVA,
    EVENT_FURIOUS_ROAR,
};

enum ePhases
{
    PHASE_1   = 1,
    PHASE_2   = 2,
};

class boss_halfus_wyrmbreaker : public CreatureScript
{
public:
    boss_halfus_wyrmbreaker() : CreatureScript("boss_halfus_wyrmbreaker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_halfus_wyrmbreakerAI (creature);
    }

    struct boss_halfus_wyrmbreakerAI : public ScriptedAI
    {
        boss_halfus_wyrmbreakerAI(Creature *c) : ScriptedAI(c) 
        {
            pInstance = c->GetInstanceScript();
        }

        InstanceScript* pInstance;
        uint32 uiShadowNovaTimer;
        uint32 uiBerserkTimer;
        uint32 uiFuriousRoarTimer;
        uint32 uiFuriousRoarCount;
        uint32 uiPhase;
        bool StormRider;
        bool Berserk;

        void Reset()
        {
            uiShadowNovaTimer = urand(12000,17000);
            uiBerserkTimer = 360000;
            uiFuriousRoarTimer = 0;
            uiFuriousRoarCount = 0;
            uiPhase = PHASE_1;
            StormRider = false;
            Berserk = false;
            if (pInstance)
            {
                pInstance->SetData(DATA_HALFUS, NOT_STARTED);
                if (pInstance->GetData(DATA_STORM_RIDER) == 1)
                {
                    DoCast(me, SPELL_SHADOW_WRAPPED);
                    StormRider = true;
                }
                if (pInstance->GetData(DATA_THE_SLATE_DRAGON) == 1)
                    DoCast(me, SPELL_MALEVOLENT_STRAKES);
                if (pInstance->GetData(DATA_NETHER_SCION) == 1)
                    DoCast(me, SPELL_FRENZIED_ASSAULT);
            }
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            if (pInstance)
                pInstance->SetData(DATA_HALFUS, IN_PROGRESS);
        }
        
        void JustDied(Unit* /*Killer*/)
        {
            pInstance->SetData(DATA_HALFUS, DONE);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (StormRider)
                if (uiShadowNovaTimer <= diff)
                {
                    DoCast(SPELL_SHADOW_NOVA);
                    uiShadowNovaTimer = urand(12000,17000);
                }
                else
                    uiShadowNovaTimer -= diff;

            if (uiPhase == PHASE_2)
                if (uiFuriousRoarTimer <= diff)
                    if (uiFuriousRoarCount < 3)
                    {
                        DoCast(SPELL_FURIOUS_ROAR);
                        ++uiFuriousRoarCount;
                        uiFuriousRoarTimer = 1500;
                    }
                    else
                    {
                        DoCast(SPELL_SHADOW_NOVA);
                        uiFuriousRoarCount = 0;
                        uiFuriousRoarTimer = urand(12000,17000);
                    }
                else
                    uiFuriousRoarTimer -= diff;

            if (!Berserk)
                if (uiBerserkTimer <= diff)
                {
                    DoCast(SPELL_BERSERK);
                    Berserk = true;
                }
                else
                    uiBerserkTimer -= diff;

            if (uiPhase == PHASE_1 && me->HealthBelowPct(50))
                uiPhase = PHASE_2;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_proto_behemoth : public CreatureScript
{
	public :
		npc_proto_behemoth() : CreatureScript("npc_proto_behemoth") { }

		struct npc_proto_behemothAI : public ScriptedAI 
		{
			npc_proto_behemothAI(Creature * pCreature) : ScriptedAI(pCreature) {}


			InstanceScript* pInstance;
			
			uint32 uiBarrageTimer;
			uint32 uiSCORBreathTimer;
			uint32 uiSUPERreathTimer;
			uint32 uiDancingFlameTimer;
			uint32 uiFireballTimer;

			void Reset()
			{
				uiBarrageTimer = 10000;
				uiSCORBreathTimer = 60000;
				uiSUPERBreathTimer = 90000;
				uiDancingFlameTimer = 20000;
				uiFireballTimer = 10000;
			}
			
			void EnterCombat(Unit* /*pWho*/)
			{
				SetCombatMovement(false);
			}

			void UpdateAI(const uint32 uiDiff)
			{
                if (!UpdateVictim())
                    return;
				
				if(uiBarrageTimer <= uiDiff)
				{
					DoCastVictim(SPELL_FIREBALL_BARRAGE);
					uiBarrageTimer = 10000;
				} else uiBarrageTimer -= uiDiff;
				
				if(uiSCORBreathTimer <= uiDiff)
				{
					DoCastVictim(SPELL_SCORCHING_BREATH);
					uiSCORBreathTimer = 60000;
				} else uiSCORBreathTimer -= uiDiff;
				
				if(uiSUPERBreathTimer <= uiDiff)
				{
					DoCastVictim(SPELL_SUPERHEATED_BREATH);
					uiSUPERBreathTimer = 90000;
				} else uiSUPERBreathTimer -= uiDiff;
				
				if(uiDancingFlameTimer <= uiDiff)
				{
					DoCastVictim(SPELL_DANCING_FLAMES);
					uiDancingFlameTimer = 20000;
				} else uiDancingFlameTimer -= uiDiff;
				
				if(uiFireballTimer <= uiDiff)
				{
					DoCastVictim(SPELL_FIREBALL);
					uiFireballTimer = 10000;
				} else uiFireballTimer -= uiDiff;

			}
		};
		
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_proto_behemothAI (pCreature);
    }
		
};

class npc_halfus_dragon_prisoner : public CreatureScript
{
public:
    npc_halfus_dragon_prisoner() : CreatureScript("npc_halfus_dragon_prisoner") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->CastSpell(creature, SPELL_FREE_DRAGON, false);
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_halfus_dragon_prisonerAI (creature);
    }

    struct npc_halfus_dragon_prisonerAI : public ScriptedAI
    {
        npc_halfus_dragon_prisonerAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
        }

        InstanceScript* pInstance;
        uint32 StoneTouchTimer;

        void Reset()
        {
            StoneTouchTimer = 35000;
        }

        void JustDied(Unit* /*Killer*/)
        {
            if (pInstance)
                if (Creature* pHalfus = Unit::GetCreature(*me, pInstance->GetData64(DATA_HALFUS)))
                    if(Aura* aura = pHalfus->GetAura(87683))
                        aura->SetStackAmount(aura->GetStackAmount() + 1);
                    else
                        me->AddAura(87683, pHalfus);
        }

        void SpellHit(Unit* pUnit, const SpellEntry* pSpell)
        {
            switch (pSpell->Id)
            {
                case SPELL_FREE_DRAGON:
                    {
                        if (!pInstance)
                            return;
                        Creature* pHalfus = Unit::GetCreature(*me, pInstance->GetData64(DATA_HALFUS));
                        if (!pHalfus)
                            return;
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        switch(me->GetEntry())
                        {
                            case NPC_STORM_RIDER:
                                me->AddAura(84092, pHalfus);
                                break;
                            case NPC_NETHER_SCION:
                                me->AddAura(83611, pHalfus);
                                break;
                        }
                        pHalfus->CastSpell(me, SPELL_BIND_WILL, false);
                    }
                    break;
                case SPELL_BIND_WILL:
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (pInstance)
                if (me->GetEntry() == NPC_THE_SLATE_DRAGON)
                    if (StoneTouchTimer <= diff)
                    {
                        StoneTouchTimer = 35000;
                        if (Creature* pHalfus = Unit::GetCreature(*me, pInstance->GetData64(DATA_HALFUS)))
                        {
                            me->AddAura(SPELL_STONE_TOUCH, pHalfus);
                            if (Aura* pStone = pHalfus->GetAura(SPELL_STONE_TOUCH))
                                pStone->SetDuration(12000);
                        }
                    }
                    else
                        StoneTouchTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class spell_halfus_stone_touch : public SpellScriptLoader
{
    public:
        spell_halfus_stone_touch() : SpellScriptLoader("spell_halfus_stone_touch") { }

        class spell_halfus_stone_touch_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_halfus_stone_touch_AuraScript);

            void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit * target = GetTarget())
                {
                    target->AddUnitState(UNIT_STAT_STUNNED);
                    target->ClearUnitState(UNIT_STAT_CASTING);
                }
            }

            void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
               if (Unit* target = GetTarget())
               {
                   target->ClearUnitState(UNIT_STAT_STUNNED);
                   target->AddUnitState(UNIT_STAT_CASTING);
               }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_halfus_stone_touch_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_halfus_stone_touch_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_halfus_stone_touch_AuraScript();
        }
};

void AddSC_boss_halfus_wyrmbreaker()
{
    new boss_halfus_wyrmbreaker();
    new npc_halfus_dragon_prisoner();
	new npc_proto_behemoth();
	new spell_halfus_stone_touch();
}