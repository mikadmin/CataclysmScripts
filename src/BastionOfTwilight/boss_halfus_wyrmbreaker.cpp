/*
* Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
*
* Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
*
* Copyright (C) 2011 ArkCORE <http://www.arkania.net/>
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
#include <cstring>

enum Events
{
	EVENT_BERSERK = 1,
	EVENT_MALEVOLENT_STRIKE = 2,
	EVENT_FURIOUS_ROAR = 3,
	EVENT_SHADOW_NOVA = 4,
};

class boss_halfus_wyrmbreaker : public CreatureScript
{
public:
	boss_halfus_wyrmbreaker() : CreatureScript("boss_halfus_wyrmbreaker") {}

	struct boss_halfus_wyrmbreakerAI : public BossAI
	{
		boss_halfus_wyrmbreakerAI(Creature * creature) : BossAI(creature, DATA_WYRMBREAKER)
		{
			pInstance = (InstanceScript*)creature->GetInstanceScript();
		}

		void Reset()
		{

			pInstance->SetData(DATA_WYRMBREAKER_EVENT,NOT_STARTED);
		}

		void EnterCombat()
		{
			events.ScheduleEvent(EVENT_BERSERK,360000);
			events.ScheduleEvent(EVENT_MALEVOLENT_STRIKE,155000);
			events.ScheduleEvent(EVENT_FURIOUS_ROAR,30000);
			events.ScheduleEvent(EVENT_SHADOW_NOVA,30000);

			if (pInstance)
				pInstance->SetData(DATA_WYRMBREAKER_EVENT,IN_PROGRESS);
		}

		void JustDied()
		{
			if (!pInstance)
				return;

			pInstance->SetData(DATA_WYRMBREAKER_EVENT,DONE);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_BERSERK:
					me->AddAura(SPELL_BERSERK_HALFUS,me);
					break;

					if (!HealthAbovePct(50))
					{

				case EVENT_FURIOUS_ROAR:
					DoCastVictim(SPELL_FURIOUS_ROAR);
					DoCastVictim(SPELL_SHADOW_NOVA);
					events.ScheduleEvent(EVENT_FURIOUS_ROAR,30000);
					break;

					if (me->HasAura(SPELL_MALEVOLENT_STRIKES))
					{
				case EVENT_MALEVOLENT_STRIKE:
					DoCastVictim(SPELL_MALEVOLENT_STRIKES_DEBUFF);
					events.ScheduleEvent(EVENT_MALEVOLENT_STRIKE,155000);
					break;
					}

					if (me->HasAura(SPELL_SHADOW_WARPED))
					{
				case EVENT_SHADOW_NOVA:
					DoCast(SPELL_SHADOW_NOVA);
					events.ScheduleEvent(EVENT_SHADOW_NOVA,30000);
					break;
					}

					}
				}
			}

			DoMeleeAttackIfReady();

		}
	private:

		InstanceScript* pInstance;

		uint32 uiBerserkTimer;
		uint32 uiFuriousRoarTimer;
		uint32 uiMalevolentStrikeTimer;
		uint32 uiShadowNovaTimer;
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_halfus_wyrmbreakerAI(creature);
	}
};

class npc_proto_behemoth : public CreatureScript{
public :
	npc_proto_behemoth() : CreatureScript("npc_proto_behemoth") { }

	struct npc_proto_behemothAI : public ScriptedAI {
		npc_proto_behemothAI(Creature * creature) : ScriptedAI(creature)
		{
			pInstance = (InstanceScript*)creature->GetInstanceScript();
		}

		InstanceScript* pInstance;

		uint64 uiFireballTimer;
		//uint64 uiScorchingBreathTimer;
		uint64 uiFireballBaradgeTimer;

		void Reset()
		{
			uiFireballTimer = 120000;
			//uiScorchingBreathTimer = 360000;
			uiFireballBaradgeTimer = 145000;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!UpdateVictim())
				return;

			if (me->HasAura(SPELL_DANCING_FLAMES))
			{
				if (uiFireballBaradgeTimer <= uiDiff)
				{
					if (Unit * Target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true))
					{
						DoCast(Target,SPELL_FIREBALL_BARADGE);
					}
					uiFireballBaradgeTimer = 145000;
				} else uiFireballBaradgeTimer -= uiDiff;
			}

			if (uiFireballTimer <= uiDiff)
			{
				if (Unit * Target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true))
				{
					DoCast(Target,SPELL_FIREBALL);
				}
			} else uiFireballTimer -= uiDiff;
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_proto_behemothAI(creature);
	}
};


class npc_halfus_dragon : public CreatureScript{
public:
	npc_halfus_dragon() : CreatureScript("npc_halfus_dragon") { }

	struct npc_halfus_dragonAI : public ScriptedAI {
		npc_halfus_dragonAI(Creature * creature) : ScriptedAI(creature) {}

		void Reset()
		{
			me->GetMotionMaster()->MoveTargetedHome();
			me->setFaction(35);
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
			me->RemoveAllAuras();
		}
		void JustDied()
		{
			if (Creature * Halfus = me->FindNearestCreature(BOSS_WYRMBREAKER,1000.0f, true))
				me->SetAuraStack(SPELL_DRAGON_VENGEANCE,Halfus,Halfus->GetAuraCount(SPELL_DRAGON_VENGEANCE)+1);
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_halfus_dragonAI(creature);
	}

	bool OnGossipHello(Player* pPlayer, Creature* creature){

		if(creature->isInCombat() || creature->getFaction()==16)
			return false;

		char const* _message = "Let the Fight begin!";
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,_message,GOSSIP_SENDER_MAIN ,GOSSIP_ACTION_INFO_DEF+1);
		pPlayer->SEND_GOSSIP_MENU(68,creature->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* pPlayer, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		pPlayer->CLOSE_GOSSIP_MENU();

		if (Creature * Halfus = creature->FindNearestCreature(BOSS_WYRMBREAKER,1000.0f, true))
		{
			switch (creature->GetEntry())
			{
			case NPC_SLATE_DRAKE:
				creature->AddAura(SPELL_STONE_TOUCH,Halfus);
				break;
			case NPC_NETHER_SCION:
				creature->AddAura(SPELL_NETHER_BLINDNESS,Halfus);
				break;
			case NPC_STORM_RIDER:
				creature->CastSpell(creature->GetPositionX(),creature->GetPositionY(),creature->GetPositionZ(),SPELL_CYCLONE_WINDS,false);
				break;
			case NPC_TWILIGHT_DRAKE:
				break;
			}

			Halfus->AddAura(SPELL_BIND_WILL,creature);
			creature->setFaction(16);
			creature->SetReactState(REACT_AGGRESSIVE);
			creature->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
			
			GetAI(creature)->DoZoneInCombat();
		}

		return true;
	}
};

class npc_cyclon_winds : public CreatureScript
{
public:
	npc_cyclon_winds() : CreatureScript("npc_cyclon_winds") {  }

	struct npc_cyclon_windsAI : public ScriptedAI
	{
		npc_cyclon_windsAI(Creature * creature) : ScriptedAI(creature)
		{
			pInstance = (InstanceScript*)creature->GetInstanceScript();
		}

		InstanceScript* pInstance;

		void Reset() { }

		void UpdateAI(const uint32 uiDiff) { }

		void MovementInForm(uint32 type, uint32 id)
		{
			if (type == POINT_MOTION_TYPE)
			{
				switch (id)
				{
				case POINT_CYCLON_WIND:
					Creature * Halfus = ObjectAccessor::GetCreature(*me,pInstance->GetData64(NPC_CYCLON_WIND));
					me->AddAura(84092,Halfus);
					me->DestroyForNearbyPlayers();
				}
			}
		}
	};

	CreatureAI * GetAI(Creature * creature) const
	{
		return new npc_cyclon_windsAI(creature);
	}
};
class spell_cyclon_winds : public SpellScriptLoader
{
public:
	spell_cyclon_winds() : SpellScriptLoader("spell_cyclon_winds") { }

	class spell_cyclon_windsSpellScript : public SpellScript
	{
		PrepareSpellScript(spell_cyclon_windsSpellScript);

		bool Validate(SpellEntry const * spellEntry)
		{
			if (!sSpellStore.LookupEntry(spellEntry->Id))
				return false;
			return true;
		}

		void HandleAfterHit()
		{
			Creature * Cyclon = ObjectAccessor::GetCreature(*GetCaster(),NPC_CYCLON_WIND);
			Cyclon->GetMotionMaster()->MovePoint(POINT_CYCLON_WIND,Positions[1]);
		}

		void Register()
		{
			AfterHit += SpellHitFn(spell_cyclon_windsSpellScript::HandleAfterHit);
		}
	};

	SpellScript * GetSpellScript() const
	{
		return new spell_cyclon_windsSpellScript();
	}
};

void AddSC_boss_halfus_wyrmbreaker()
{
	new boss_halfus_wyrmbreaker();
	new npc_halfus_dragon();
	new npc_proto_behemoth();
	new spell_cyclon_winds();
}