/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "WorldPacket.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

#define SAY_AGGRO "Augh smart ! Augh already steal treasure while you no looking !"
#define SAY_DIED "Gwaaaaaaaaaaaahhh!!!"

enum Data
{
    DATA_LOCKMAW_EVENT,
    DATA_AUGH_EVENT,
};

enum Data64
{
    DATA_LOCKMAW,
    DATA_AUGH,
};

enum CreatureIds
{
    BOSS_LOCKMAW                 = 43614,
    BOSS_AUGH                    = 49045,
};

enum Spells
{
	//Lockmaw
	SPELL_DUST_FLAIL		 = 81642,
	SPELL_SCENT_OF_BLOOD	 = 81690,
	H_SPELL_SCENT_OF_BLOOD	 = 89998,
	SPELL_VENOMOUS_RAGE		 = 81706,
	SPELL_VISCOUS_POISON	 = 81630,
	H_SPELL_VISCOUS_POISON	 = 90004,
	
	//Augh
	SPELL_H_FURY	= 23537,
	SPELL_H_FIRE_DRAGON	= 29964,
	SPELL_CLOUD	= 7964,
	SPELL_TEMPEST = 1680,
	SPELL_PARALYTIC_BLOW_DART	= 89989,
};

enum Events
{
	//Lockmaw
    EVENT_DUST_FLAIL         = 1,
    EVENT_SCENT_OF_BLOOD     = 2,
    EVENT_VENOMOUS_RAGE      = 3,
    EVENT_VISCOUS_POISON     = 4,
	
	//Augh
    EVENT_PARALYTIC_BLOW_DART = 5,
    EVENT_CLOUD	              = 6,
    EVENT_FIRE_DRAGON	      = 7,
    EVENT_TEMPEST	          = 8,
};

enum SummonIds
{
    NPC_FRENZIED_CROCOLISK   = 43658,
};

const Position SummonLocations[4] =
{
    //Frenzied Crocolisks
    {-11033.29f, -1674.57f, -0.56f, 1.09f},
    {-11029.84f, -1673.09f, -0.37f, 2.33f},
    {-11007.25f, -1666.37f, -0.23f, 2.46f},
    {-11006.83f, -1666.85f, -0.25f, 2.23f},
};

class boss_lockmaw : public CreatureScript
{
    public:
        boss_lockmaw() : CreatureScript("boss_lockmaw") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
           return new boss_lockmawAI(pCreature);
        }
        struct boss_lockmawAI : public ScriptedAI
		{
			boss_lockmawAI(Creature* pCreature) : ScriptedAI(pCreature), Summons(me)
			{
				pInstance = pCreature->GetInstanceScript();
			}

			InstanceScript* pInstance;
            EventMap events;
            SummonList Summons;

            void Reset ()
			{
                events.Reset();
                Summons.DespawnAll();
			}

            void JustDied(Unit* /*Kill*/)
            {
                Summons.DespawnAll();
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                DoZoneInCombat();
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_DUST_FLAIL, urand(6000, 10000));
				events.ScheduleEvent(EVENT_VISCOUS_POISON, 2000);
				events.ScheduleEvent(EVENT_SCENT_OF_BLOOD, 32000);
				events.ScheduleEvent(EVENT_VENOMOUS_RAGE, 180000);
			}

			void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())  /* No target to kill */
                    return;

				events.Update(uiDiff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_DUST_FLAIL:
                            DoCast(me->getVictim(), SPELL_DUST_FLAIL);
                            events.ScheduleEvent(EVENT_DUST_FLAIL, urand(6000, 10000));
                            return;
                        case EVENT_VISCOUS_POISON:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                                DoCast(me->getVictim(), SPELL_VISCOUS_POISON);
                                events.ScheduleEvent(EVENT_VISCOUS_POISON, 2000);
                            return;
                        case EVENT_SCENT_OF_BLOOD:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                                DoCast(me->getVictim(), SPELL_SCENT_OF_BLOOD);
                                for(uint8 i=0; i<3; i++)
                                {
                                  Creature* Crocolisk = me->SummonCreature(NPC_FRENZIED_CROCOLISK, SummonLocations[i], TEMPSUMMON_CORPSE_DESPAWN);
                                  Crocolisk->AddThreat(me->getVictim(), 0.0f);
                                  DoZoneInCombat(Crocolisk);
                                }
                                events.ScheduleEvent(EVENT_SCENT_OF_BLOOD, 32000);
                            return;
                        case EVENT_VENOMOUS_RAGE:
                            if(!HealthAbovePct(30))
								{
									DoCast(me, SPELL_VENOMOUS_RAGE);
								}
                            return;
                        default:
                            break;
                    }
				}

            DoMeleeAttackIfReady();
			}
		};
};

class mob_augh : public CreatureScript
{
    public:
        mob_augh() : CreatureScript("mob_augh") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
           return new mob_aughAI(pCreature);
        }
        struct mob_aughAI : public ScriptedAI
		{
			mob_aughAI(Creature *c) : ScriptedAI(c) {}

			EventMap events;

            void Reset ()
			{
			}

			void EnterCombat(Unit* /*who*/) 
			{
				me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
				DoCast(me, SPELL_H_FURY);
				EnterPhaseGround();
			}
			
			void EnterPhaseGround()
			{
				events.ScheduleEvent(EVENT_PARALYTIC_BLOW_DART, 10000);
				events.ScheduleEvent(EVENT_CLOUD, 18000);
				events.ScheduleEvent(EVENT_FIRE_DRAGON, 40000);
				events.ScheduleEvent(EVENT_TEMPEST, 30000);
			}

			void JustDied(Unit* /*killer*/)
			{
				me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
			}
			
			void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

				events.Update(uiDiff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_PARALYTIC_BLOW_DART:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                            DoCast(me->getVictim(), SPELL_PARALYTIC_BLOW_DART);
                            events.ScheduleEvent(EVENT_PARALYTIC_BLOW_DART, 10000);
                            return;
                        case EVENT_CLOUD:
                                DoCast(me->getVictim(), SPELL_CLOUD);
                                events.ScheduleEvent(EVENT_CLOUD, 18000);
                            return;
                        case EVENT_FIRE_DRAGON:
								if(!HealthAbovePct(50))
								{
									DoCast(me->getVictim(), SPELL_H_FIRE_DRAGON);
								}
								events.ScheduleEvent(EVENT_FIRE_DRAGON, 40000);
                            return;
                        case EVENT_TEMPEST:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                                DoCast(me, SPELL_TEMPEST);
                                events.ScheduleEvent(EVENT_TEMPEST, 30000);
                            return;
                        default:
                            break;
                    }
				}

            DoMeleeAttackIfReady();
			}
		};
};

#define spell_vicious 81677
#define spell_vicious_H 89999

class mob_crosilik: public CreatureScript
{
public: 
 mob_crosilik() : CreatureScript("mob_crosilik") { } 

 struct mob_crosilikAI : public ScriptedAI
    {
        mob_crosilikAI(Creature *c) : ScriptedAI(c) {}

		uint32 vicious;
		
        void Reset()
        {
           vicious = 10000;        
        }

		void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (vicious<= diff){
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
					DoCast(pTarget, IsHeroic() ? spell_vicious_H : spell_vicious);
                vicious   = 10000; 
				} else vicious -= diff; 
						
						if (!UpdateVictim())
                    return;
										
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_crosilikAI (pCreature);
    }

};

void AddSC_boss_lockmaw()
{
    new boss_lockmaw();
	new mob_augh();
	new mob_crosilik();
}