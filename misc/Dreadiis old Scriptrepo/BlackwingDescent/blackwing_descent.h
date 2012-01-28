#ifndef DEF_BLACKWING_DESCENT_H
#define DEF_BLACKWING_DESCENT_H

enum
{
};

const Position NefariusLoc[2]=
{
    {-312.415466f, -382.925842f, 213.93443f, 0},          // 0 - Nefarius
    {-342.736359, -382.073639f, 213.903091f, 0},          // 1 - Nefarius
    {-302.199, -349.577, 220.484, 4.71466f},          // 2 - Nefarius Origine
};

enum eAchievementData
{
};

enum SharedSpells
{
    SPELL_BERSERK1 = 26662,
    SPELL_BERSERK2 = 64238,
};

enum Data
{
    //Encounters
    DATA_MAGMAW                  = 0,
    DATA_OMNOTRON_DEFENSE_SYSTEM = 1,
    DATA_MALORIAK                = 2,
    DATA_ATRAMEDES               = 3,
    DATA_CHIMAERON               = 4,
    DATA_NEFARIAN                = 5,
        
    //Additional Entities
    DATA_ARCANOTRON_GUID         = 6,
    DATA_ELECTRON_GUID           = 7,
    DATA_MAGMATRON_GUID          = 8,
    DATA_TOXITRON_GUID           = 9,
    DATA_ONYXIA_GUID             = 10,
    DATA_BILE_O_TRON_800         = 11,
};

enum Creatures
{
    NPC_MAGMAW               = 41570,
    NPC_ARCANOTRON           = 42166,
    NPC_ELECTRON             = 42179,
    NPC_MAGMATRON            = 42178,
    NPC_TOXITRON             = 42180,
    NPC_MALORIAK             = 41378,
    NPC_ATRAMEDES            = 41442,
    NPC_CHIMAERON            = 43296,
    NPC_BILE_O_TRON_800      = 44418,
    NPC_NEFARIAN             = 41376,
    NPC_ONYXIA               = 41270,
    NPC_LORD_VICTOR_NEFARIAN = 41379,
};

#endif