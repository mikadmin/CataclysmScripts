/*
 * Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
 *
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

enum Spells
{
	SPELL_HYDROLANCE = 82752,
	SPELL_WATERBOMB = 82699,
	SPELL_HEART_OF_ICE = 82655,
	SPELL_GLACIATE = 92508,
    SPELL_BURNING_BLOOD = 82660,
    SPELL_FLAME_TORRENT = 82777,
    SPELL_AEGIS_OF_FLAMES = 92512,
};


/****************
* Feludius
****************/

class boss_feludius : public CreatureScript
{
public:
    boss_feludius() : CreatureScript("boss_feludius") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_feludiusAI (creature);
    }

    struct boss_feludiusAI : public ScriptedAI
    {
        boss_feludiusAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
		EventMap events;
		
        void Reset()
		{
			events.Reset();
		}

        void EnterCombat(Unit* /*who*/)
		{
			me->GetMotionMaster()->MoveTargetedHome();
			
			//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
		}

        void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;
			
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				/*switch (eventId)
				{

				case EVENT_TEST:
					DoCastVictim(SPELL_ENFEEBLING_BLOW);
					events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, urand(19000,24000));
					break;
				
				default:
					break;
				}*/
			}		

            DoMeleeAttackIfReady();
        }
    };
};

/****************
* Ignacious
****************/

class boss_ignacious : public CreatureScript
{
public:
    boss_ignacious() : CreatureScript("boss_ignacious") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ignaciousAI (creature);
    }

    struct boss_ignaciousAI : public ScriptedAI
    {
        boss_ignaciousAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
		EventMap events;
		
        void Reset()
		{
			events.Reset();
		}

        void EnterCombat(Unit* /*who*/)
		{
			me->GetMotionMaster()->MoveTargetedHome();
			
			//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
		}

        void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;
			
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				/*switch (eventId)
				{

				case EVENT_TEST:
					DoCastVictim(SPELL_ENFEEBLING_BLOW);
					events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, urand(19000,24000));
					break;
				
				default:
					break;
				}*/
			}		

            DoMeleeAttackIfReady();
        }
    };
};

/****************
* Arion
****************/

class boss_arion : public CreatureScript
{
public:
    boss_arion() : CreatureScript("boss_arion") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_arionAI (creature);
    }

    struct boss_arionAI : public ScriptedAI
    {
        boss_arionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
		EventMap events;
		
        void Reset()
		{
			events.Reset();
		}

        void EnterCombat(Unit* /*who*/)
		{
			me->GetMotionMaster()->MoveTargetedHome();
			
			//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
		}

        void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;
			
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				/*switch (eventId)
				{

				case EVENT_TEST:
					DoCastVictim(SPELL_ENFEEBLING_BLOW);
					events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, urand(19000,24000));
					break;
				
				default:
					break;
				}*/
			}		

            DoMeleeAttackIfReady();
        }
    };
};

/****************
* Terrastra
****************/

class boss_terrastra : public CreatureScript
{
public:
    boss_terrastra() : CreatureScript("boss_terrastra") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_terrastraAI (creature);
    }

    struct boss_terrastraAI : public ScriptedAI
    {
        boss_terrastraAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
		EventMap events;
		
        void Reset()
		{
			events.Reset();
		}

        void EnterCombat(Unit* /*who*/)
		{
			me->GetMotionMaster()->MoveTargetedHome();
			
			//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
		}

        void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;
			
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				/*switch (eventId)
				{

				case EVENT_TEST:
					DoCastVictim(SPELL_ENFEEBLING_BLOW);
					events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, urand(19000,24000));
					break;
				
				default:
					break;
				}*/
			}		

            DoMeleeAttackIfReady();
        }
    };
};

/****************
* Elementium Monstrosity
****************/

class boss_elementium_monstrosity : public CreatureScript
{
public:
    boss_elementium_monstrosity() : CreatureScript("boss_elementium_monstrosity") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_elementium_monstrosityAI (creature);
    }

    struct boss_elementium_monstrosityAI : public ScriptedAI
    {
        boss_elementium_monstrosityAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
		EventMap events;
		
        void Reset()
		{
			events.Reset();
		}

        void EnterCombat(Unit* /*who*/)
		{
			me->GetMotionMaster()->MoveTargetedHome();
			
			//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
		}

        void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;
			
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				/*switch (eventId)
				{

				case EVENT_TEST:
					DoCastVictim(SPELL_ENFEEBLING_BLOW);
					events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, urand(19000,24000));
					break;
				
				default:
					break;
				}*/
			}		

            DoMeleeAttackIfReady();
        }
    };
};

/****************
* Spells
****************/

/*class spell_waterbomb : SpellScriptLoader
{
    spell_waterbomb() : SpellScriptLoader("spell_waterbomb") {}

    class spell_waterbombSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_waterbombSpellScript);

        bool Validate(SpellEntry const * spellEntry *)
        {
            return true;
        }

        void HandleDummy()
        {
        }

        void Register()
        {
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_waterbombSpellScript();
    }
};*/

class spell_inferno_ping : public SpellScriptLoader
{
    spell_inferno_ping() : SpellScriptLoader("spell_inferno_ping") { }

    class spell_inferno_pingSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_inferno_pingSpellScript);

        bool Validate(SpellEntry * /* spellEntry*/)
        {
            return true;
        }

        void Summon(Unit * pCaster)
        {
            pCaster->CastSpell(pCaster->GetPositionX(),pCaster->GetPositionY(),pCaster->GetPositionZ(),87650,true);
        }

        void HandlerDummy()
        {
            Summon(GetCaster());
        }

        void Register()
        {
        }
    };

    SpellScript * GetSpellScript() const
    {
        return new spell_inferno_pingSpellScript();
    }
};

void AddSC_boss_ascendant_council()
{
    new boss_feludius();
    new boss_ignacious();
	new boss_arion();
	new boss_terrastra();
	new boss_elementium_monstrosity();
}