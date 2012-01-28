/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

#define TARGETS_10 2
#define TARGETS_25 5

enum Spells
{
	// Chimaeron
	SPELL_DOUBLE_ATTACK = 88826,
	SPELL_RONFLE = 82706, // Profondément endormi
	//P1
	SPELL_GELEE_CAUSTIQUE = 82935, // ZONE
	SPELL_MASSACRE = 82848, // ZONE
	SPELL_QUERRELLE = 88872,
	SPELL_BRECHE = 82881, // DEBUFF SWITCH TANK
	//P2
	SPELL_MORTALITE = 82934, // SOINS REDUIT DE 99%
	SPELL_DARK_MOC = 91307, // SEULEMENT HERO
	// Bill-o-Tron
	SPELL_MIXTURE = 82705, // ZONE
	SPELL_DEFAILLANCE = 88853, // DANGER
};

enum Creatures
{
	DATA_CHIMAERON = 43296,
	DATA_BILL_O_TRON = 44418,
};

enum Events
{
	// Chimaeron
	EVENT_DOUBLE_ATTACK,
	EVENT_GELEE_CAUSTIQUE,
	EVENT_MASSACRE,
	EVENT_QUERRELLE,
	EVENT_BRECHE,
	EVENT_DARK_MOC,
	// Bill-o-tron
	EVENT_DEFAILLANCE,
	EVENT_MIXTURE,
};

/***********
** Chimaeron
************/
class boss_chimaeron : public CreatureScript
{
public:
    boss_chimaeron() : CreatureScript("boss_chimaeron") { }

    struct boss_chimaeronAI : public ScriptedAI
    {
        boss_chimaeronAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
		EventMap events;

        void Reset() 
		{
			DoCast(me, SPELL_RONFLE)
		}

        void EnterCombat(Unit* /*pWho*/) 
		{
			me->RemoveAllAuras();
			EnterPhaseGround();
		}
		
		void EnterPhaseGround()
		{
			events.ScheduleEvent(EVENT_DOUBLE_ATTACK, 20000);
			events.ScheduleEvent(EVENT_GELEE_CAUSTIQUE, 15000);
			events.ScheduleEvent(EVENT_MASSACRE, 30000);
			events.ScheduleEvent(EVENT_QUERRELLE, 60000);
			events.ScheduleEvent(EVENT_BRECHE, 90000);
			events.ScheduleEvent(EVENT_DARK_MOC, 5000);
		}

        void JustDied(Unit* /*Killer*/) {}

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
            return;
					
			events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch(eventId)
					{
						case EVENT_DOUBLE_ATTACK:
							DoCast(me->getVictim(), SPELL_DOUBLE_ATTACK);
							events.ScheduleEvent(EVENT_DOUBLE_ATTACK, 20000);
							return;
						case EVENT_GELEE_CAUSTIQUE:
							if (Unit *target = SelectTargetList(playerList, RAID_MODE(TARGETS_10,TARGETS_25,TARGETS_10,TARGETS_25), SELECT_TARGET_RANDOM,1,100,true)
							DoCast(target, SPELL_GELEE_CAUSTIQUE);
							events.ScheduleEvent(EVENT_GELEE_CAUSTIQUE, 15000);
							return;
						case EVENT_MASSACRE:
							DoCastAOE(SPELL_MASSACRE);
							events.ScheduleEvent(EVENT_MASSACRE, 30000);
							return;
						case EVENT_QUERRELLE:
							DoCast(me, SPELL_QUERRELLE);
							events.ScheduleEvent(EVENT_QUERRELLE, 60000);
							return;
						case EVENT_BRECHE:
							DoCast(me->getVictim(), SPELL_BRECHE);
							events.ScheduleEvent(EVENT_BRECHE, 90000);
							return;
						if(!HealthAbovePct(20))
						{
							DoCast(me, SPELL_MORTALITE);
							case EVENT_DOUBLE_ATTACK,:
								DoCast(me->getVictim(), SPELL_DOUBLE_ATTACK);
								events.ScheduleEvent(EVENT_DOUBLE_ATTACK, 20000);
							return;
						}
						if (IsHeroic())
						{
							case EVENT_DARK_MOC:
								DoCastAOE(SPELL_DARK_MOC);
								events.ScheduleEvent(EVENT_DARK_MOC, 5000);
							return;
						}
					}
				}
			DoMeleeAttackIfReady();
        }
    };
	
	CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_chimaeronAI (creature);
    }
};

/*************
** Bill-O-Tron
**************/
class mob_billotron : public CreatureScript
{
public:
    mob_billotron() : CreatureScript("mob_billotron") { }

    struct mob_billotronAI : public ScriptedAI
    {
        mob_billotronAI(Creature* creature) : ScriptedAI(creature) {}

        InstanceScript* pInstance;
		EventMap events;
		
        void Reset() {}

        void EnterCombat(Unit* /*pWho*/) 
		{
			// Définir comment activé Bill-O-Tron
			DoCastAOE(SPELL_MIXTURE);
			EnterPhaseGround();
		}
		
		void EnterPhaseGround()
		{
			events.ScheduleEvent(EVENT_DEFAILLANCE, 60000);
			events.ScheduleEvent(EVENT_MIXTURE, 60000);
		}

        void UpdateAI(const uint32 diff)
        {
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch(eventId)
				{
					case EVENT_DEFAILLANCE:
						DoCast(me, SPELL_DEFAILLANCE);
						events.ScheduleEvent(EVENT_DEFAILLANCE, 60000);
						return;
					case EVENT_MIXTURE:
						me->RemoveAllAuras();
						DoCastAOE(SPELL_MIXTURE);
						events.ScheduleEvent(EVENT_MIXTURE, 60000);
						return;
				}
			}
        }
    };
	
	CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_billotronAI (creature);
    }
};

void AddSC_boss_chimaeron()
{
    new boss_chimaeron();
	new mob_billotron();
}