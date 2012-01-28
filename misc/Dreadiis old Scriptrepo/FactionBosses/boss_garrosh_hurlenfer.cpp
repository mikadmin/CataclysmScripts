#include "ScriptPCH.h"

#define spell_charge_du_berserker 84742 // Charge_du_Berserker
#define spell_cri_demoralisant 61044 // Cri_Démoralisant
#define spell_onde_de_choc 84715 // Onde_de_Choc
#define spell_tourbillon 84724 // Tourbillon

#define SAY_AGGRO "Glory for the Horde!"
#define SAY_DIED "Oh No ...."

class boss_garrosh_hurlenfer: public CreatureScript
{
public: 
 boss_garrosh_hurlenfer() : CreatureScript("boss_garrosh_hurlenfer") { } 

 struct boss_garrosh_hurlenferAI : public ScriptedAI
    {
        boss_garrosh_hurlenferAI(Creature *c) : ScriptedAI(c) {}

        uint32 charge_du_berserker;
		uint32 cri_demoralisant;
		uint32 onde_de_choc;
		uint32 tourbillon;

        void Reset()
        {
            charge_du_berserker = 30000; 
			cri_demoralisant = 50000;
			onde_de_choc = 20000;
			tourbillon = 31000;
        }

        void EnterCombat(Unit* /*who*/) 
        {
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
        }

        void JustDied(Unit* /*killer*/)
        {
			me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (charge_du_berserker<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_charge_du_berserker);
												
                charge_du_berserker = 30000; 
            }
            else
                charge_du_berserker-= diff;

		    if (cri_demoralisant<= diff)
            {
                DoCast(spell_cri_demoralisant);
				
                cri_demoralisant = 50000; 
            }
            else
                cri_demoralisant-= diff;

			if (onde_de_choc<= diff)
			{
                DoCast(spell_onde_de_choc);
				
				onde_de_choc  = 20000;							
            }
		    else
			    onde_de_choc-= diff;
				
			if (tourbillon<= diff)
			{
			    DoCast(spell_tourbillon);
				
				 tourbillon = 31000;
			}
			else
			    tourbillon -= diff;
				
							if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_garrosh_hurlenferAI(pCreature);
    }

};

void AddSC_boss_garrosh_hurlenfer()
{
    new boss_garrosh_hurlenfer();
}