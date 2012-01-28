#include "ScriptPCH.h"

#define spell_eclair 73564
#define spell_vent 83066 

#define SAY_AGGRO ""
#define SAY_DIED ""

class boss_siamat: public CreatureScript
{
public: 
 boss_siamat() : CreatureScript("boss_siamat") { } 

 struct boss_siamatAI : public ScriptedAI
    {
        boss_siamatAI(Creature *c) : ScriptedAI(c) {}

		uint32 eclair;
		uint32 vent;

        void Reset()
        {
           eclair = 5000; 
           vent = 6000;		   
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
           
            if (eclair <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_eclair);
                eclair = 5000;
            }
            else
                eclair -= diff;
				
            if (vent <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_vent);
                vent = 6000;
            }
            else
                vent -= diff;

			                if (!UpdateVictim())
                    return;
					
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_siamatAI (pCreature);
    }

};

#define spell_fraca 84521
#define spell_nova 84544

class mob_siamat: public CreatureScript
{
public: 
 mob_siamat() : CreatureScript("mob_siamat") { } 

 struct mob_siamatAI : public ScriptedAI
    {
        mob_siamatAI(Creature *c) : ScriptedAI(c) {}

		uint32 fraca;
		uint32 nova;

        void Reset()
        {
           fraca = 5000; 
		   nova = 15000;
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;
           
            if (fraca <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_fraca);
                fraca = 5000;
            }
            else
                fraca -= diff;
				
            if (nova <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_nova);
                nova = 15000;
            }
            else
                nova -= diff;

			                if (!UpdateVictim())
                    return;
					
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_siamatAI (pCreature);
    }

};

void AddSC_boss_siamat() 
{
    new boss_siamat();
	new mob_siamat();
}