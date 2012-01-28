#include "ScriptPCH.h"
#include "halls_of_origination.h"

/*
* TODO:
*
*-Translate Pussy langauge into english (or ger)
*-Translate spellnames into english (or ger)
*-rewrite this whole shit :P
*-add script text support
*/

enum Spells
{
    SPELL_SOLEIL            = 73872,
    SPELL_INVOCATION        = 80352,
    SPELL_ENFER             = 87653,
    SPELL_VENT              = 89130,
    SPELL_FEU               = 89131,
    SPELL_BENE              = 76355,
};

enum ScriptTexts
{
    SAY_AGGRO               = -0,
    SAY_DEATH               = -0,
};

/*######
##Rajh
######*/
class boss_rajh: public CreatureScript
{
public: 
 boss_rajh() : CreatureScript("boss_rajh") { } 

 struct boss_rajhAI : public ScriptedAI
    {
        boss_rajhAI(Creature *c) : ScriptedAI(c) {}

		uint32 soleil;
        uint32 invocation;
		uint32 enfer;
		uint32 vent;
		uint32 feu;
		uint32 bene;
		
        void Reset()
        {
           soleil = 5000;
		   invocation = 10000; 
           enfer = 3000;
		   vent = 60000;
           feu = 15000;
		   bene = 4000;		   
        }

        void EnterCombat(Unit* /*who*/) 
        {
			DoScriptText(SAY_AGGRO, me);
        }

        void JustDied(Unit* /*killer*/)
        {
			DoScriptText(SAY_DEATH, me);
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (soleil<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, spell_soleil);
                    soleil   = 5000; 
            }
            else
                soleil -= diff; 
				
            if (invocation<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, spell_invocation);
                    invocation   = 10000; 
            }
            else
                invocation -= diff; 
				
            if (enfer<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, spell_enfer);
                    enfer   = 3000; 
            }
            else
                enfer -= diff; 
				
            if (vent<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, spell_vent);
                    vent   = 60000; 
            }
            else
                vent -= diff; 
				
            if (feu<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, spell_feu);
                    feu   = 15000; 
            }
            else
                feu -= diff; 
				
            if (bene<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(pTarget, spell_bene);
                    bene   = 4000; 
            }
            else
                bene -= diff;
			           						
                if (!UpdateVictim())
                    return;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_rajhAI (pCreature);
    }

};

void AddSC_boss_rajh() 
{
    new boss_rajh();
}