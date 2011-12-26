/* Dreadii Scripting 2011
*
*Script Complete: 50%
*
*Todo:
*-add full sql support
*-add spells for heroic mode
*/

#include "ScriptPCH.h"

enum CreatureIds
{
    BOSS_ERUDAX         = 40484,
    MOB_FACELESS        = 40600,
};

enum Spells
{
    //boss_erudax
    SPELL_PLAGUE         = 82622,    //seuche der zeitalter
    SPELL_ORKAN          = 75664,    //schattenorkan
    SPELL_SPAWN          = 75704,    //gesichtslosen beschwören
    //faceless curruptor
    SPELL_CORRUPTION     = 75520,
    SPELL_UMBRALE        = 75763,
    SPELL_SIPHON         = 75755,
}

enum Yells
{
    SAY_AGGRO            = -1800200,
    SAY_DEATH            = -1800201,
    SAY_SUMMON           = -1800201,
};

enum Events
{
    //boss_erudax
    EVENT_PLAGUE         = 1,
    EVENT_ORKAN          = 2,
    EVENT_SUMMON         = 3,
    //faceless curruptor
    EVENT_CORRUPTION     = 4,
    EVENT_UMBRALE        = 5,
    EVENT_SIPHON         = 6,
};

enum SummonIds
{
    MOB_FACELESS         = 40600,
};

const Position aSpawnLocations[2] =
{
    {-0.0f, -0.0f, 0.0f, 0.0f},
    {-0.0f, -0.0f, 0.0f, 0.0f},
};


class boss_erudax: public CreatureScript
{
public: 
 boss_erudax() : CreatureScript("boss_erudax") { } 

 struct boss_erudaxAI : public ScriptedAI
    {
        boss_general_umbrissAI(Creature* pCreature) : ScriptedAI(pCreature), Summons(me)
		{
            pInstance = pCreature->GetInstanceScript();
		}

        InstanceScript* pInstance;
        EventMap events;
        SummonList Summons;

        void EnterCombat(Unit* /*who*/) 
        {
            EnterPhaseGround();
            DoScriptText(SAY_AGGRO, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);
        }

        void JustSummoned(Creature *pSummoned)
        {
            pSummoned->SetInCombatWithZone();
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
            pSummoned->AI()->AttackStart(pTarget);

            Summons.Summon(pSummoned);
        }

        void SummonedCreatureDespawn(Creature *summon)
        {
            Summons.Despawn(summon);
        }

        void EnterPhaseGround()
        {
            //erudax
			events.ScheduleEvent(EVENT_PLAGUE, 10000);
            events.ScheduleEvent(EVENT_ORKAN, 33000);
            events.ScheduleEvent(EVENT_SUMMON, 50000);
            //faceless curruptor
            events.ScheduleEvent(EVENT_CORRUPTION, 30000);
            events.ScheduleEvent(EVENT_UMBRALE, 30000);
            events.ScheduleEvent(EVENT_SIPHON, 30000);
        }
//-------------------------------------Rewritten


/*
Mob Erudax id = 40600
*/

class mob_faceless: public CreatureScript
{
public: 
 mob_faceless() : CreatureScript("mob_faceless") { } 

 struct mob_facelessAI : public ScriptedAI
    {
        mob_faceless(Creature *c) : ScriptedAI(c) {}

		uint32 corruption;
		uint32 umbrale;
		uint32 siphon;

        void Reset()
        {
           corruption = 10000; 
           umbrale = 15000;
		   siphon = 20000;
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;
           
            if (corruption <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_corruption);
                corruption = 10000;
            }
            else
                corruption -= diff;
				
            if (umbrale <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_umbrale);
                umbrale = 15000;
            }
            else
                umbrale -= diff;
				
            if (siphon <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_siphon);
                siphon = 20000;
            }
            else
                siphon -= diff;

			                if (!UpdateVictim())
                    return;
					
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_erudaxAI (pCreature);
    }

};

void AddSC_boss_erudax() 
{
    new boss_erudax();
	new mob_erudax();
}