/*
* Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
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

/**********
* Script Coded by Naios
* Script Complete 50% (or less)
**********/

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

enum Spells
{
	SPELL_QUECKSILVER_ARMOR = 75842,
	SPELL_SUPERHEATED_QUECKSILVER_ARMOR = 75846,

	SPELL_HEAT_WAVE = 63677,
	SPELL_BURNING_METAL = 76002,
	SPELL_CLEAVE = 845,
	SPELL_LAVA_SPOUT = 76007,
};

enum Events
{
	EVENT_CLEAVE = 1,
	EVENT_CHECK_ARMOR_STATE = 2,
};

class boss_karsh_steelbender : public CreatureScript
{
public:
    boss_karsh_steelbender() : CreatureScript("boss_karsh_steelbender") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_karsh_steelbenderAI (creature);
    }

    struct boss_karsh_steelbenderAI : public ScriptedAI
    {
        boss_karsh_steelbenderAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
		EventMap events;

        void Reset()
		{
			events.Reset();
			me->RemoveAllAuras();
		}

        void EnterCombat(Unit* /*who*/)
		{
			DoCast(me, SPELL_QUECKSILVER_ARMOR);
			events.ScheduleEvent(EVENT_CLEAVE, urand(15000,18000));
			events.ScheduleEvent(EVENT_CHECK_ARMOR_STATE, 1000);
		}

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

			if((!me->HasAura(SPELL_QUECKSILVER_ARMOR)) && (!me->HasAura(SPELL_SUPERHEATED_QUECKSILVER_ARMOR)))
			{	// Summon Adds

				LavaSpoutErrupt();

				DoCast(me, SPELL_QUECKSILVER_ARMOR);


				return;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CLEAVE:
					DoCastVictim(SPELL_CLEAVE);
					events.ScheduleEvent(EVENT_CLEAVE, urand(15000,18000));
					break;

				case EVENT_CHECK_ARMOR_STATE:
					// Checks weather the Boss is in heat range

					if(me->GetDistance2d(237.166f, 785.067f /*Stream of Molten*/) < 2.5f)
					{
						me->RemoveAura(SPELL_QUECKSILVER_ARMOR);
						me->SetAuraStack(SPELL_SUPERHEATED_QUECKSILVER_ARMOR,me,me->GetAuraCount(SPELL_SUPERHEATED_QUECKSILVER_ARMOR)+1);
					}

					events.ScheduleEvent(EVENT_CHECK_ARMOR_STATE, 1000);
					break;
				}
			}

            DoMeleeAttackIfReady();
        }

		void DamageDealt(Unit* victim, uint32& damage, DamageEffectType /*damageType*/)
		{
			if(damage > 0 && me->HasAura(SPELL_SUPERHEATED_QUECKSILVER_ARMOR))
				DoCastVictim(SPELL_BURNING_METAL);
		}

	private:

		void LavaSpoutErrupt()
		{
			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, NPC_LAVA_SPOUT_TRIGGER, 1000.0f);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				(*iter)->CastSpell((*iter),SPELL_LAVA_SPOUT, true);
		}
    };
};

void AddSC_boss_karsh_steelbender()
{
    new boss_karsh_steelbender();
}