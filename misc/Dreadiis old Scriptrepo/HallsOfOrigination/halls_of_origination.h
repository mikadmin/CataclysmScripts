#ifndef DEF_HALLS_OF_ORIGINATION_H
#define DEF_HALLS_OF_ORIGINATION_H

enum Data
{
    //encounter events
    DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT,
    DATA_EARTHRAGER_PTAH_EVENT,
    DATA_ANRAPHET_EVENT,
    DATA_ISISET_EVENT,
    DATA_AMMUNAE_EVENT,
    DATA_SETESH_EVENT,
    DATA_RAJH_EVENT,
    DATA_TEAM_IN_INSTANCE,
    //guardians for anraphet
    DATA_EARTH_GUARD_EVENT,
    DATA_WATER_GUARD_EVENT,
    DATA_FIRE_GUARD_EVENT,
    DATA_WIND_GUARD_EVENT,
};

enum Data64
{
    //encounter events
    DATA_TEMPLE_GUARDIAN_ANHUUR,
    DATA_EARTHRAGER_PTAH,
    DATA_ANRAPHET,
    DATA_ISISET,
    DATA_AMMUNAE,
    DATA_SETESH,
    DATA_RAJH,
    //guardians for anraphet
    DATA_EARTH_GUARD,
    DATA_WATER_GUARD,
    DATA_FIRE_GUARD,
    DATA_WIND_GUARD, 
};

enum GameObjectIds
{
    GO_ORIGINATION_ELEVATOR     = 207547,
    GO_LARGE_STONE_OBELISK      = 207410,
};

enum CreatureIds
{
    // Dungeon Bosses
    BOSS_TEMPLE_GUARDIAN_ANHUUR = 39425,
    BOSS_EARTHRAGER_PTAH        = 39428,
    BOSS_ANRAPHET               = 39788,
    BOSS_ISISET                 = 39587,
    BOSS_AMMUNAE                = 39731,
    BOSS_SETESH                 = 39732,
    BOSS_RAJH                   = 39378,

    // Trash Mobs
    NPC_BLISTERING_SCARAB       = 40310,
    NPC_BLOODPETAL_BLOSSOM      = 40620,
    NPC_DUSTBONE_TORMENTOR      = 40311,
    NPC_DUSTBONE_HORROR         = 40787,
    NPC_FLAME_WARDEN            = 39800,
    NPC_FLUX_ANIMATOR           = 40033,
    NPC_LIFEWARDEN_NYMPH        = 40715,
    NPC_LIVING_VINE             = 40668,
    NPC_SPATIAL_ANOMALY         = 40170,
    NPC_TEMPLE_SWIFTSTALKER     = 48139,
    NPC_TEMPLE_SHADOWLANCER     = 48141,
    NPC_TEMPLE_RUNECASTER       = 48140,
    NPC_TEMPLE_FIRESHAPER       = 48143,
    NPC_VENOMOUS_SKITTERER      = 39440,

    //anraphet guardians
    NPC_WATER_GUARD             = 39802,
    NPC_WIND_GUARD              = 39803,
    NPC_EARTH_GUARD             = 39801,
    NPC_FIRE_GUARD              = 39800,

    // Various NPCs
    NPC_BRANN_BRONZEBEARD       = 49941,
    MOB_HORROR                  = 40810, //need correct id
    MOB_SCARAB                  = 40458, //need correct id
};

#endif