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

#include"ScriptPCH.h"
#include"blackwing_descent.h"

enum eEvents {
	EVENT_NONE,
	EVENT_BLAZE,
	EVENT_SOUL_SEVER,
	EVENT_WAIL_DARKNESS,
	EVENT_CHAIN_LIGHTNING,
	EVENT_HEX,
	EVENT_METEOR,
	EVENT_SHADOW_BOLT,
	EVENT_DISEASE_BREATH,
	EVENT_INFECTIOUS_PLAGUE,
	EVENT_MIXTURE,
	EVENT_RITUAL_BLOODLETTING,
	EVENT_VICIOUS_LEECHES,
	EVENT_BRANDED_TONGUE,
	EVENT_SERUM_TORMENT,
	EVENT_SKULL_CRUSH,
	EVENT_SLAM,
	EVENT_SKULL_CRACK,
	EVENT_BLADED_SHIELD,
	EVENT_RESISTANCE,
	EVENT_CALL_FALCON,
	EVENT_SHOOT,
	EVENT_WING_CLIP,
	EVENT_BLINK,
	EVENT_CALL_SCORPID,
	EVENT_EVASION,
	EVENT_FAN_KNIVES,
	EVENT_SPINAL_PIERCE,
	EVENT_FERAL_LINK,
	EVENT_CALL_CROCO,
	EVENT_FORKED_SHOT,
	EVENT_IMPALE,
	EVENT_SHOCKWAVE,
	EVENT_DRAGON_BREATH,
	EVENT_FIRE_BLAST,
	EVENT_TOXIC_DART,
	EVENT_LIGHTNING_NOVA,
	EVENT_THUNDER_CRASH,
};

enum Spells
{
	// Nefarian (Magmaw Fight)
	SPELL_BLAZING_INFERNO = 92190,
	SPELL_SHADOWFLAME_BARRAGE = 94121,
};

enum NefarianEvents
{
	EVENT_BLAZING_INFERNO = 1,
	EVENT_SHADOWFLAME_BARRAGE = 2,
};

class mob_nefarian_helper_heroic : public CreatureScript
{
public:
    mob_nefarian_helper_heroic() : CreatureScript("mob_nefarian_helper_heroic") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_nefarian_helper_heroicAI (creature);
    }

    struct mob_nefarian_helper_heroicAI : public ScriptedAI
    {
        mob_nefarian_helper_heroicAI(Creature* creature) : ScriptedAI(creature), Intialized(false)
        {
            instance = creature->GetInstanceScript();
        }

		EventMap events;
        InstanceScript* instance;
		Unit* Summoner;
		bool Intialized;
		bool SpecialPhaseSwitchActive;

        void Reset()
		{
			me->SetFlying(true);
			SpecialPhaseSwitchActive = false;
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);

			events.Reset();
		}
		
		void IsSummonedBy(Unit* summoner)
		{			
			Summoner = summoner;

			Intialized = true;

			switch(Summoner->GetEntry())
			{
			case NPC_MAGMAW:
				events.ScheduleEvent(EVENT_BLAZING_INFERNO, 5000);
				break;

			case NPC_ATRAMEDES:
				break;

			case NPC_MALORIAK:
				break;

			case NPC_CHIMAERON:
				break;

			default:
				break;
			}
		}

        void UpdateAI(const uint32 diff)
        {
			if(!Intialized)
				return;

			events.Update(diff);

			// Magmaw fight
			if(Summoner->GetEntry() == NPC_MAGMAW && Summoner->HealthBelowPct(30) && !SpecialPhaseSwitchActive)
			{
				events.Reset();

				events.ScheduleEvent(EVENT_SHADOWFLAME_BARRAGE, 3000);
				SpecialPhaseSwitchActive = true;
			}
			
			while (uint32 eventId = events.ExecuteEvent())
			{
				switch(eventId)
				{
					// Magmaw fight
				case EVENT_BLAZING_INFERNO:
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 500, true))
						DoCast(target, SPELL_BLAZING_INFERNO, true);

					events.ScheduleEvent(EVENT_BLAZING_INFERNO, 35000);
					break;
				case EVENT_SHADOWFLAME_BARRAGE:
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 500, true))
						DoCast(target, SPELL_SHADOWFLAME_BARRAGE, true);

					events.ScheduleEvent(EVENT_SHADOWFLAME_BARRAGE, 7000);
					break;

				default:
					break;
				}
			}
        }
    };
};

void AddSC_blackwing_descent()
{
	new mob_nefarian_helper_heroic();
}
