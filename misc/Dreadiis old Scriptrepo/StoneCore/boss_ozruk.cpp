#include "ScriptPCH.h"

/*
Script 100%
*/

#define SPELL_BARRAGE 86881 // Barrage de cristal
#define H_SPELL_BARRAGE 92648
#define SPELL_ONDE 82415 // Onde atténuante
#define H_SPELL_ONDE 92650
#define SPELL_BARRAGE 86881 // Barrage de cristal
#define H_SPELL_BARRAGE 92648
#define SPELL_ONDE 82415 // Onde atténuante
#define H_SPELL_ONDE 92650
#define SPELL_ONDE 82415 // Onde atténuante
#define H_SPELL_ONDE 92650
#define SPELL_ONDE 82415 // Onde atténuante
#define H_SPELL_ONDE 92650
#define SPELL_CHARGE 75622 // Charge fracassante

#define SAY_AGGRO "Nul n'entre dans le cœur du monde !"
#define SAY_DIED "Un protecteur est tombé. Le cœur du monde est vulnérable !"

class boss_ozruk: public CreatureScript
{
public: 
 boss_ozruk() : CreatureScript("boss_ozruk") { } 

 struct boss_ozrukAI : public ScriptedAI
    {
        boss_ozrukAI(Creature *c) : ScriptedAI(c) {}

		uint32 barrage;
		uint32 onde;
		uint32 fouir;
		uint32 charge;
		uint32 fouir;
		uint32 charge;

        void Reset()
        {
           barrage = 6000; 
		   onde = 10000;
		   fouir = 24000;
		   charge = 28000;
		   barrage = 6000; 
		   onde = 10000;
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
					
            if (barrage <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, IsHeroic() ? H_SPELL_BARRAGE : SPELL_BARRAGE);
                barrage = 6000;
            }
            else
                barrage -= diff;
			
            if (onde <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, IsHeroic() ? H_SPELL_ONDE : SPELL_ONDE);
                onde = 10000;
            }
            else
                onde -= diff;
				
            if (charge <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_CHARGE);
                charge = 28000;
            }
            else
                charge -= diff;
				
            if (charge <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_CHARGE);
                charge = 28000;
            }
            else
                charge -= diff;
				
            if (charge <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_CHARGE);
                charge = 28000;
            }
            else
                charge -= diff;
				
            if (charge <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_CHARGE);
                charge = 28000;
            }
            else
                charge -= diff;

			                if (!UpdateVictim())
                    return;
										
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_ozrukAI (pCreature);
    }

};

void AddSC_boss_ozruk() 
{
    new boss_ozruk();
}