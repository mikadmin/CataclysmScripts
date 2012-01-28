#include "ScriptPCH.h"

#define spell_fouet 82506
#define spell_peste 82622 
#define spell_repentir 81947 

#define SAY_AGGRO "Begone infidels, you are not welcome here !"
#define SAY_DIED "Death is only the beginning !"

class boss_barim: public CreatureScript
{
public: 
 boss_barim() : CreatureScript("boss_barim") { } 

 struct boss_barimAI : public ScriptedAI
    {
        boss_barimAI(Creature *c) : ScriptedAI(c) {}

		uint32 peste;
		uint32 repentir;
        uint32 fouet_Timer;

        void Reset()
        {
           peste = 10000; 
           repentir = 15000;	
		   fouet_Timer = 30000; 		   
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
           
			if (fouet_Timer <= diff)
            {
                DoCast(me->getVictim(), spell_fouet, true);

                fouet_Timer = 30000;
            } else fouet_Timer -= diff;
				
            if (peste <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_peste);
                peste = 10000;
            }
            else
                peste -= diff;
				
            if (repentir <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_repentir);
                repentir = 15000;
            }
            else
                repentir -= diff;

			                if (!UpdateVictim())
                    return;
					
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_barimAI (pCreature);
    }

};

void AddSC_boss_barim() 
{
    new boss_barim();
}