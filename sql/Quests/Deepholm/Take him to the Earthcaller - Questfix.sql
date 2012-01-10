-- Take him to the Earthcaller (Deepholm) Questfix
-- by Naios for Arkania

UPDATE `creature_template` SET `ScriptName`='npc_flint_oremantle' WHERE `entry`=43036 LIMIT 1;
UPDATE `quest_template` SET `OfferRewardText`='We are honored by Flint Oremantle\'s presence.$BI am given to understand that the Stonefather is in possession of a fragment of the World Pillar.' WHERE `entry`=26413 LIMIT 1;

/*
enum eFlint
{
    QUEST_TAKE_HIM_TO_THE_EARTHCALLER = 26413,
    NPC_YEVAA = 42573,
};

/* ToDo
- Maybe there is a dialog between Flint and Yeeva
*/

class npc_flint_oremantle : public CreatureScript
{
public:
    npc_flint_oremantle() : CreatureScript("npc_flint_oremantle") { }

	
	bool OnGossipHello(Player* pPlayer, Creature* creature)
	{
		
		if(creature->isInCombat() || pPlayer->GetQuestStatus(QUEST_TAKE_HIM_TO_THE_EARTHCALLER) != QUEST_STATUS_INCOMPLETE)
		return false;
		
		char const* _message = "Follow me to the Earthcaller!";	
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,_message,GOSSIP_SENDER_MAIN ,GOSSIP_ACTION_INFO_DEF+1);
		pPlayer->SEND_GOSSIP_MENU(68,creature->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* pPlayer, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		pPlayer->CLOSE_GOSSIP_MENU();

         if (npc_flint_oremantleAI* npc_flint_oremantleAI = CAST_AI(npc_flint_oremantle::npc_flint_oremantleAI, creature->AI()))
         {
                creature->SetStandState(UNIT_STAND_STATE_STAND);
                npc_flint_oremantleAI->StartFollow(pPlayer, 35, 0);

				creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
         }
	
		return true;
	}
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_flint_oremantleAI(creature);
    }

    struct npc_flint_oremantleAI : public FollowerAI
    {
        npc_flint_oremantleAI(Creature* creature) : FollowerAI(creature), HomePosition(creature->GetHomePosition()) { }

		Position HomePosition;

		void Reset()
        {
			me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        void MoveInLineOfSight(Unit* who)
        {
            FollowerAI::MoveInLineOfSight(who);

            if (!me->getVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE) && who->GetEntry() == NPC_YEVAA)
            {
                if (me->IsWithinDistInMap(who, INTERACTION_DISTANCE))
                {
                    if (Player* player = GetLeaderForFollower())
                    {
                        if (player->GetQuestStatus(QUEST_TAKE_HIM_TO_THE_EARTHCALLER) == QUEST_STATUS_INCOMPLETE)
							player->KilledMonsterCredit(44207, 0);

						me->DespawnOrUnsummon(30000);
                    }

                    SetFollowComplete(true);
                }
            }
        }
    };
};
*/

