#include "ScriptPCH.h"

enum Creatures
{
    Creature1   = 35170,     
    //Creature2   = 35456,
};

static const Position SpawnPos[1] =
{
//Add your own location
{-1670.973511f, 1450.592407f, 53.224930f, 3.892373f},
};


class npc_Gilneas_City_Prison : public CreatureScript
{
public:
    npc_Gilneas_City_Prison() : CreatureScript("npc_Gilneas_City_Prison") { }

    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if (player->isInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("Vous etes en combat!", player->GetGUID());
            return true;
        }
        else
        {
                         player->ADD_GOSSIP_ITEM( 9, "Je suis pret !"                    , GOSSIP_SENDER_MAIN, 1);


        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch(uiAction)
            {

case 1://Summon Worgens
      player->CLOSE_GOSSIP_MENU();
     _creature->MonsterYell("Attention! Je les vois arriver sur nous!", LANG_UNIVERSAL, NULL);
    _creature->SummonCreature(Creature1,SpawnPos[1],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
	_creature->SummonCreature(Creature1,SpawnPos[1],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 40000);
	_creature->SummonCreature(Creature1,SpawnPos[1],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
	_creature->SummonCreature(Creature1,SpawnPos[1],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 80000);
	_creature->SummonCreature(Creature1,SpawnPos[1],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000);
	_creature->SummonCreature(Creature1,SpawnPos[1],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
     //player->PlayDirectSound(11803, 0);

break;



             default:
        break;                   
    }
   }
  return true;
 }
};

void AddSC_npc_Gilneas_City_Prison()
{
    new npc_Gilneas_City_Prison();
}