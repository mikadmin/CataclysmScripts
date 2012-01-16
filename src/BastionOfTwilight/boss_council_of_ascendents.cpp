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

/**********
* Script Coded by Naios
* Script Complete 20% (or less)
**********/

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

enum Spells
{
	// Feludius
	SPELL_HYDROLANCE = 82752,
	SPELL_WATERBOMB = 82699,
	SPELL_HEART_OF_ICE = 82665,
	SPELL_GLACIATE = 92508,

	SPELL_FREEZE = 82772,

	// Ignacious
	SPELL_BURNING_BLOOD = 82660,
	SPELL_FLAME_TORRENT = 82777,
	SPELL_AEGIS_OF_FLAMES = 92512,

	SPELL_INFERNO_LEAP = 92521,
	SPELL_INFERNO_RUSH = 82859,
	SPELL_SUMMON_INFERNO_LEAP = 87650,
};

enum Events
{
	// Feludius
	EVENT_HYDROLANCE = 1,
	EVENT_WATER_BOMB = 2,
	EVENT_HEART_OF_ICE = 3,
	EVENT_GLACIATE = 4,

	// Ignacious
	EVENT_BUNRING_BLOOD = 5,
	EVENT_FLAME_TORRENT = 6,
	EVENT_AEGIS_OF_FLAME = 7,

	EVENT_INFERNO_LEAP = 8,
	EVENT_INFERNO_RUSH = 9
};

Position const position[5] =
{
	{-1055.08f, -601.279f, 835.118f, 0.4208f},	// Spawning Position of Arion
	{-1055.06f, -563.935f, 835.116f, 5.81653f},	// Spawning Position of Terrastra
	{-435.54f, -695.072f, 280.316f, 3.4010f},	// ToDo Spawning Position of Feludius (Event)
	{-435.54f, -695.072f, 268.687f, 3.4010f},	// ToDo Spawning Position of Ignacius (Event)
	{-375.742f, -519.749f, 300.663f, 0.0f}		// ToDo Center of the Room
};

/****************
* Ascendant Dummy AI
****************/

struct dummy_ascendant_AI : public ScriptedAI
{
	dummy_ascendant_AI(Creature* creature) : ScriptedAI(creature)
	{
		instance = creature->GetInstanceScript();
	}

	InstanceScript* instance;
	EventMap events;

	void Reset()
	{
		me->GetMotionMaster()->MoveTargetedHome();
		events.Reset();
	}

	void EnterCombat(Unit* /*who*/)
	{
		//events.ScheduleEvent(EVENT_TEST, urand(10000,12000));
	}

	/*void UpdateAI(const uint32 diff)
	{
	if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
	return;

	events.Update(diff);

	while (uint32 eventId = events.ExecuteEvent())
	{
	switch (eventId)
	{

	case EVENT_TEST:
	DoCastVictim(SPELL_ENFEEBLING_BLOW);
	events.ScheduleEvent(EVENT_ENFEEBLING_BLOW, urand(19000,24000));
	break;

	default:
	break;
	}
	}		

	DoMeleeAttackIfReady();
	}*/

	void nextPhase()
	{
		//uint32 phase = instance->GetData(DATA_ASCENDANT_PHASE);

		if(me->GetEntry() == BOSS_FELUDIUS || me->GetEntry() == BOSS_IGNACIOUS)
		{
			//Creature* otherAscendant = Unit::GetCreature(*me, instance->GetData64(me->GetEntry() == BOSS_FELUDIUS ? DATA_IGNACIOUS : DATA_FELUDIUS));

			// Stores the Health of Both Ascendants
			//instance->SetData(DATA_ASCENDANT_MONSTROSITY_LIVE,200+me->GetHealthPct()+otherAscendant->GetHealthPct());

			// Summons Arion and Terrastra
			me->SummonCreature(BOSS_ARION,position[0],TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,1000)->AI()->DoZoneInCombat();
			me->SummonCreature(BOSS_TERRASTRA,position[1],TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,1000)->AI()->DoZoneInCombat();

			// Unsummons the other Ascendant and me
			//otherAscendant->SetVisible(false);
			me->SetVisible(false);

		}else
		{ //Arion and Terrastra
			//Summon Monstrosity and start Event

			//Creature* Ascendants[4];

		}
	}
};

/****************
* Feludius (Controller)
****************/

// Summons Terrastra

class boss_feludius : public CreatureScript
{
public:
	boss_feludius() : CreatureScript("boss_feludius") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_feludiusAI (creature);
	}

	struct boss_feludiusAI : public dummy_ascendant_AI
	{
		boss_feludiusAI(Creature* creature) : dummy_ascendant_AI(creature)
		{
			instance = creature->GetInstanceScript();
		}

		InstanceScript* instance;
		uint8 phase;

		void Reset()
		{
			phase = 1;
			//instance->SetData(DATA_ASCENDANT_PHASE, 1);
			me->SetVisible(true);
			DespawnMinions();
		}

		void JustReachedHome()
		{
			//instance->SetBossState();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_HYDROLANCE, urand(10000,12000));
			events.ScheduleEvent(EVENT_WATER_BOMB, urand(16000,19000));
			events.ScheduleEvent(EVENT_HEART_OF_ICE, urand(10000,12000));
			events.ScheduleEvent(EVENT_GLACIATE, urand(32000,34000));		
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(me->GetHealthPct() < 25 && phase == 1)
			{
				nextPhase();
				phase++;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_HYDROLANCE:

					if(Unit * Victim = SelectTarget(SELECT_TARGET_RANDOM,0 ,500.0f,true))
						me->CastSpell(Victim,SPELL_HYDROLANCE,false);

					events.ScheduleEvent(EVENT_HYDROLANCE, urand(10000,12000));
					break;

				case EVENT_WATER_BOMB:
					DoCast(SPELL_WATERBOMB);

					events.ScheduleEvent(EVENT_WATER_BOMB, urand(16000,19000));
					break;

				case EVENT_HEART_OF_ICE:

					if(Unit * Victim = SelectTarget(SELECT_TARGET_RANDOM,0 ,500.0f,true))
						me->CastSpell(Victim,SPELL_HEART_OF_ICE,false);

					events.ScheduleEvent(EVENT_HEART_OF_ICE, urand(10000,12000));
					break;

				case EVENT_GLACIATE:
					DoCastAOE(SPELL_GLACIATE);

					events.ScheduleEvent(EVENT_GLACIATE, urand(32000,34000));
					break;

				default:
					break;
				}
			}		

			DoMeleeAttackIfReady();
		}

		void SpellHitTarget(Unit* target, const SpellEntry* spell)
		{ // The problem is, that the glaciate makes currently no damage -> no spell hit
			if(spell->Id == SPELL_GLACIATE && target->HasAura(SPELL_HEART_OF_ICE))
				me->CastSpell(target, SPELL_FREEZE, true);
		}

		inline void DespawnMinions()
		{
			DespawnCreatures(BOSS_ARION);
			DespawnCreatures(BOSS_TERRASTRA);

			DespawnCreatures(NPC_LEAPING_FLAMES);
		}

		void DespawnCreatures(uint32 entry)
		{
			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				(*iter)->DespawnOrUnsummon();
		}
	};
};

/****************
* Ignacious
****************/

// Summons Arion

class boss_ignacious : public CreatureScript
{
public:
	boss_ignacious() : CreatureScript("boss_ignacious") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_ignaciousAI (creature);
	}

	struct boss_ignaciousAI : public dummy_ascendant_AI
	{
		boss_ignaciousAI(Creature* creature) : dummy_ascendant_AI(creature) {}

		void Reset()
		{
			me->SetVisible(true);
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_BUNRING_BLOOD, urand(31000,33000));
			events.ScheduleEvent(EVENT_FLAME_TORRENT, urand(10000,12000));
			events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, urand(54000,57000));
			events.ScheduleEvent(EVENT_INFERNO_LEAP, urand(25000,27000));
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if(me->GetHealthPct() < 25)
				nextPhase();

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_BUNRING_BLOOD:
					DoCastVictim(SPELL_BURNING_BLOOD,false);

					events.ScheduleEvent(EVENT_BUNRING_BLOOD, urand(31000,33000));	

					break;
				case EVENT_FLAME_TORRENT:
					DoCast(SPELL_FLAME_TORRENT);

					events.ScheduleEvent(EVENT_FLAME_TORRENT, urand(10000,12000));
					break;

				case EVENT_AEGIS_OF_FLAME:
					DoCast(me,SPELL_AEGIS_OF_FLAMES);

					events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, urand(54000,57000));	
					break;

				case EVENT_INFERNO_LEAP:

					if(Unit * Victim = SelectTarget(SELECT_TARGET_RANDOM,0 ,500.0f,true))
						DoCast(Victim,SPELL_INFERNO_LEAP);

					events.ScheduleEvent(EVENT_INFERNO_LEAP, urand(25000,27000));
					break;
				default:
					break;
				}
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

class spell_heart_of_ice: public SpellScriptLoader {
public:
	spell_heart_of_ice() : SpellScriptLoader("spell_heart_of_ice") { }

	class spell_heart_of_ice_AuraScript: public AuraScript
	{
		PrepareAuraScript(spell_heart_of_ice_AuraScript)

		bool Validate(SpellEntry const * /*spellEntry*/)
		{
			if (!sSpellStore.LookupEntry(SPELL_HEART_OF_ICE))
				return false;
			return true;
		}

		void HandleEffectPeriodic(AuraEffect const * aurEff)
		{
			if(GetTarget()->FindNearestCreature(NPC_LEAPING_FLAMES, 1.5f, true))
				Remove(AURA_REMOVE_BY_ENEMY_SPELL);
		}

		void Register()
		{
			OnEffectPeriodic +=	AuraEffectPeriodicFn(spell_heart_of_ice_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_ANY);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_heart_of_ice_AuraScript();
	}
};

void AddSC_boss_ascendant_council()
{
	new boss_feludius();
	new boss_ignacious();
	new boss_arion();
	new boss_terrastra();
	new boss_elementium_monstrosity();

	new spell_heart_of_ice();
}