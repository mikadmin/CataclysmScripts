#include "ScriptPCH.h"

#define BASE_USSAM    300
#define BASE_AUGH      301
#define BASE_BARIM        302
#define BASE_SIAMAT    303

enum DataTypes
{
    DATA_USSAM             = 0,
    DATA_AUGH          = 1,
    DATA_BARIM              = 2,
};

class teleporter : public GameObjectScript
{
public:
    teleporter() : GameObjectScript("teleporter") { }

    bool OnGossipSelect(Player *pPlayer, GameObject * /*pGO*/, uint32 sender, uint32 action)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (sender != GOSSIP_SENDER_MAIN)
            return false;
        if (!pPlayer->getAttackers().empty())
            return false;

        switch(action)
        {
        case BASE_USSAM:
            pPlayer->TeleportTo(755, -10903.773438f, -1382.985502f, 15.752753f, 0.0f);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case BASE_AUGH:
            pPlayer->TeleportTo(755, -10959.499023f, -1456.692017f, 11.163465f, 0.0f);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case BASE_BARIM:
            pPlayer->TeleportTo(755, -10974.928711f, -1325.851929f, 10.807027f, 0.0f);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case BASE_SIAMAT:
            pPlayer->TeleportTo(755, -10917.675781f, -1388.681767f, 35.848473f, 0.0f);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
}

        return true;
    }

    bool OnGossipHello(Player *pPlayer, GameObject *pGO)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to Ussam", GOSSIP_SENDER_MAIN, BASE_USSAM);
        if (InstanceScript* pInstance = pGO->GetInstanceScript())
        {
            if (pInstance->GetBossState(DATA_USSAM) == DONE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to Augh", GOSSIP_SENDER_MAIN, BASE_AUGH);
            if (pInstance->GetBossState(DATA_AUGH) == DONE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to Barim", GOSSIP_SENDER_MAIN, BASE_BARIM);
            if (instance->GetBossState(DATA_USSAM) == DONE && instance->GetBossState(DATA_AUGH) == DONE && instance->GetBossState(DATA_BARIM) == DONE)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to Siamat", GOSSIP_SENDER_MAIN, BASE_SIAMAT);
            }
		}
        pPlayer->SEND_GOSSIP_MENU(pGO->GetGOInfo()->GetGossipMenuId(), pGO->GetGUID());
        return true;
    }

};

void AddSC_teleporter()
{
    new teleporter();
}