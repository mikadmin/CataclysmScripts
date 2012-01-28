#include "ScriptPCH.h"

/*
Script 75%
*/

enum Spells
{
    // Corborus
    SPELL_BARRAGE               = 86881,
    H_SPELL_BARRAGE             = 92648,
    SPELL_ONDE                  = 82415,
    H_SPELL_ONDE                = 92650,
    SPELL_FOUIR                 = 91175,
    SPELL_CHARGE                = 75622,
    // adds
    SPELL_FORAGE                = 80028,
    H_SPELL_FORAGE              = 92630,
};

enum CreatureIds
{
    CREATURE_CRISTAL            = 49267,
    CREATURE_PERFOREUSE         = 43917,
};

enum ScriptTexts
{
    SAY_AGGRO                   = -0,
    SAY_DEATH                   = -0,
};

struct Locations
{
    float x, y, z;
};

static Locations CenterPoint = {1153.64f, 874.802f, 284.963f}; // Devant Corborus

static Locations PipeLocations[] =
{
  {1185.24f, 891.281f, 284.349f}, //left de Corborus
  {1178.39f,  854.556f,  286.433f} //right de Corborus
};

class boss_corborus: public CreatureScript
{
public: 
 boss_corborus() : CreatureScript("boss_corborus") { } 

 struct boss_corborusAI : public ScriptedAI
    {
        boss_corborusAI(Creature *c) : ScriptedAI(c) {}

		uint32 barrage;
		uint32 onde;
		uint32 fouir;
		uint32 charge;
		uint32 uiSummonTimer;
		//uint32 m_uiSubmergeTimer;
		//uint8  m_uiStage;
		uint32 uiEncounterTimer;
		//SummonList lSummons;

        void Reset()
        {
           barrage = 6000; 
		   onde = 10000;
		   fouir = 24000;
		   charge = 28000;
		   uiSummonTimer = 5000;
		   
		   uiEncounterTimer = 0;
		   //lSummons.DespawnAll();
        }
		
		void JustSummoned(Creature* summon)
        {
            summon->GetMotionMaster()->MovePoint(0, CenterPoint.x, CenterPoint.y, CenterPoint.z);
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                summon->AI()->AttackStart(pTarget);
            //lSummons.Summon(summon);
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
					
            // Phase 1
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
				
			// Phase 2
            if (fouir <= diff)
            {
                DoCast(me->getVictim(), SPELL_FOUIR);
                fouir = 24000;
            }
            else
                fouir -= diff;
			/*	
			switch (m_uiStage)
			{
			case 0: // Mobile
				if (m_uiSubmergeTimer <= uiDiff)
                {
                    m_uiStage = 1;
                    m_uiSubmergeTimer = 1*IN_MILLISECONDS;
                } else m_uiSubmergeTimer -= uiDiff;
			case 1: // Submerge
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_OOC_NOT_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                DoCast(me,SPELL_FOUIR);
                me->GetMotionMaster()->MovePoint(0,ToCCommonLoc[1].GetPositionX()+urand(0,80)-40,ToCCommonLoc[1].GetPositionY()+urand(0,80)-40,ToCCommonLoc[1].GetPositionZ());
                m_uiStage = 2;
			case 2: // Wait til emerge
                if (m_uiSubmergeTimer <= uiDiff)
                {
                    m_uiStage = 3;
                    m_uiSubmergeTimer = 10*IN_MILLISECONDS;
                } else m_uiSubmergeTimer -= uiDiff;
                break;
			case 3: // Emerge
                me->SetDisplayId(m_uiModelMobile);
                me->RemoveAurasDueToSpell(SPELL_FOUIR);
                me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_OOC_NOT_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                SetCombatMovement(true);
                me->GetMotionMaster()->MoveChase(me->getVictim());
                m_uiStage = 4;
                break;
			}*/
			// Fin Phase 2			

            if (uiSummonTimer <= diff)
            {
                uint32 uiSummonPipe = rand()%2;
                me->SummonCreature(uiEncounterTimer > IsHeroic() ? H_SPELL_FORAGE : SPELL_FORAGE ? CREATURE_PERFOREUSE :
                RAND(CREATURE_CRISTAL,CREATURE_PERFOREUSE),
                PipeLocations[uiSummonPipe].x, PipeLocations[uiSummonPipe].y, PipeLocations[uiSummonPipe].z, 0.0f,
                TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                uiSummonTimer = 5000;
            } else uiSummonTimer -= diff;

			                if (!UpdateVictim())
                    return;
					
			uiEncounterTimer +=diff;
					
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_corborusAI (pCreature);
    }

};

void AddSC_boss_corborus() 
{
    new boss_corborus();
}