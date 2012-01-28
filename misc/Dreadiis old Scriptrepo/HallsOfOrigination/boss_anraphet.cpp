#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum Spells
{
    SPELL_ALPHA_BEAMS                       = 91210,
    H_SPELL_ALPHA_BEAMS                     = 91210,
    SPELL_CRUMBLING_RUIN                    = 75609,
    H_SPELL_CRUMBLING_RUIN                  = 91206,
    SPELL_DESTRUCTION_PROTOCOL              = 77437,
    SPELL_NEMESIS_STRIKE                    = 75604,
    H_SPELL_NEMESIS_STRIKE                  = 91175,
    SPELL_OMEGA_STANCE                      = 75622,
    H_SPELL_OMEGA_STANCE                    = 91208,
};

enum Texts
{
	SAY_INTRO = 0,
    SAY_AGGRO = 1,
    SAY_SLAY =  2,
    SAY_EVENT = 3,
    SAY_DEATH = 4,
};

class boss_anraphet: public CreatureScript
{
public: 
 boss_anraphet() : CreatureScript("boss_anraphet") { } 

 struct boss_anraphetAI : public ScriptedAI
    {
        boss_anraphetAI(Creature *c) : ScriptedAI(c) {}

		uint32 nemesis;
		uint32 rayon;
		uint32 omega;
		uint32 ruine;
		uint32 slay;

        void Reset()
        {
           nemesis = 2000; 
		   rayon = 1000;
		   omega = 14000;
		   ruine = urand(10000, 16000);
		   slay = 9000;
        }

        void EnterCombat(Unit* /*who*/) 
        {
			Talk(SAY_AGGRO);
			Talk(SAY_INTRO);
        }

        void JustDied(Unit* /*killer*/)
        {
			Talk(SAY_DEATH);
        }
		
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
            return;
           
            if (nemesis <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                DoCast(pTarget, IsHeroic() ? H_SPELL_NEMESIS_STRIKE : SPELL_NEMESIS_STRIKE);
                nemesis = 2000;
            } else nemesis -= diff;
				
            if (omega <= diff)
            {
				Talk(SAY_EVENT);
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                DoCast(pTarget, IsHeroic() ? H_SPELL_OMEGA_STANCE : SPELL_OMEGA_STANCE);
                omega = 14000;
            } else omega -= diff;
				
            if (rayon <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                DoCast(pTarget, SPELL_ALPHA_BEAMS);
                rayon = 1000;
            } else rayon -= diff;
				
            if (ruine <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                DoCast(pTarget, IsHeroic() ? H_SPELL_CRUMBLING_RUIN : SPELL_CRUMBLING_RUIN);
                ruine = urand(10000, 16000);
            } else ruine -= diff;
			
			if (slay<= diff)
            {
                Talk(SAY_SLAY);
				slay = 9000; 
            } else slay -= diff;
			
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_anraphetAI (pCreature);
    }

};

void AddSC_boss_anraphet() 
{
    new boss_anraphet();
}