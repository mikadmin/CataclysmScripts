/*
Script By Aïsawa
*/

#include "ScriptPCH.h"

#define spell_bond_heroique 59688 // Bond Héroïque
#define spell_tourbillon 41056 // Tourbillon

#define SAY_AGGRO "Glory to the Alliance! People of Stormwind! Citizens of the Alliance! Your king speaks!"
#define SAY_DIED "You will welcome these former heroes of the Alliance and treat them with the respect that you would give to any ally of Stormwind!"

class boss_varian_wrynn: public CreatureScript
{
public: 
 boss_varian_wrynn() : CreatureScript("boss_varian_wrynn") { } 

 struct boss_varian_wrynnAI : public ScriptedAI
    {
        boss_varian_wrynnAI(Creature *c) : ScriptedAI(c) {}

        uint32 bond_heroique;
		uint32 tourbillon;

        void Reset()
        {
            bond_heroique = 45000; 
			tourbillon = 35000; 
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

            if (bond_heroique<= diff)
            {
                DoCast(spell_bond_heroique);
				
                bond_heroique   = 45000; 
            }
            else
                bond_heroique -= diff;

		    if (tourbillon<= diff)
            {
                DoCast(spell_tourbillon);
				
                tourbillon   = 35000; 
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
        return new boss_varian_wrynnAI (pCreature);
    }

};

void AddSC_boss_varian_wrynn() 
{
    new boss_varian_wrynn();
}