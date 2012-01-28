#include "ScriptPCH.h"

#define spell_repentir 83445 // Shockwave
#define spell_peste 83113 // Bad Intentions

#define SAY_AGGRO "Invaders, you shall go no further !"
#define SAY_DIED "Siamat must not be freed ! Turn back before it is too late !"

class boss_ussam: public CreatureScript
{
public: 
 boss_ussam() : CreatureScript("boss_ussam") { } 

 struct boss_ussamAI : public ScriptedAI
    {
        boss_ussamAI(Creature *c) : ScriptedAI(c) {}

		uint32 peste;
		uint32 repentir;

        void Reset()
        {
           peste = 5000; 
           repentir = 10000;			   
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
           				
            if (peste <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_peste);
                peste = 5000;
            }
            else
                peste -= diff;
				
            if (repentir <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_repentir);
                repentir = 10000;
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
        return new boss_ussamAI (pCreature);
    }

};

void AddSC_boss_ussam() 
{
    new boss_ussam();
}