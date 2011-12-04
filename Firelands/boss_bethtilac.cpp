/*
* Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
*
* Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
*
* Copyright (C) 2011 TrilliumEMU <http://www.arkania.net/>
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

/*###########################
#                           #
#   Developer Info:         #
#   Script Coded by Naios   #
#   11/2011                 #
#                           #
#   Script Complete: 3%    #
#   Tested on Trillium EMU  #
#                           #
###########################*/


/* ########################################
Notes:


######################################## */


#include "ScriptPCH.h"
#include "firelands.h"

enum Yells
{
	SAY_AGGRO                                    = -1999971,
	SAY_SOFT_ENRAGE								 = -1999972, //TODO Add Sound
	SAY_ON_DOGS_FALL							 = -1999973, //TODO Add Sound
	SAY_ON_DEAD									 = -1999974, //TODO Add Sound
};

enum Spells
{

};

enum Events
{

};

const float groundLow = 74.042;
const float groundUp = 111.767;

class boss_bethtilac : public CreatureScript
{
public:
	boss_bethtilac() : CreatureScript("boss_bethtilac"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_bethtilacAI(creature);
	}

	struct boss_bethtilacAI : public BossAI
	{
		boss_bethtilacAI(Creature* c) : BossAI(c, DATA_BETHTILAC)
		{
			instance = me->GetInstanceScript();
		}

		InstanceScript* instance;
		
		void Reset()
		{
			events.Reset();
			instance->SetBossState(DATA_BETHTILAC, NOT_STARTED);
			me->GetMotionMaster()->MoveTargetedHome();
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustReachedHome()
		{
			instance->SetBossState(DATA_BETHTILAC, FAIL);
		}

		void JustDied(Unit * /*victim*/)
		{
			instance->SetBossState(DATA_BETHTILAC, DONE);
			DoScriptText(SAY_ON_DEAD, me);
			_JustDied();
		}

		void EnterCombat(Unit* who)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
			
			me->GetMotionMaster()->MovePoint(0, me->GetPositionX(),me->GetPositionY(), groundUp);

			instance->SetBossState(DATA_BETHTILAC, IN_PROGRESS);

			_EnterCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim()) {}

			events.Update(diff);

			if (me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_bethtilac()
{
	new boss_bethtilac();
}