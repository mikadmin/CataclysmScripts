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

// by Naios
 
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "CreatureAI.h"
#include "firelands.h"

class instance_firelands : public InstanceMapScript
{
    public:
        instance_firelands() : InstanceMapScript("instance_firelands", 720) { }

        struct instance_firelands_InstanceMapScript : public InstanceScript
        {
            instance_firelands_InstanceMapScript(InstanceMap* map) : InstanceScript(map) { }

            uint32 Encounter[MAX_ENCOUNTER];
            std::string m_strInstData;
            //std::set<uint64> mRubbleSpawns;
			
            // Creatures
			//Bosses
            uint64 BethilacGUID;
            uint64 RhyolithGUID;
            uint64 AlysrazarGUID;
            uint64 ShannoxGUID;
            uint64 BalorocGUID;
			uint64 MajordomusGUID;
            uint64 RagnarosGUID;
			
			//Npcs
			uint64 RiplimbGUID;
			uint64 RagefaceGUID;

            // GameObjects

            // Miscellaneous

            void Initialize()
            {
                SetBossNumber(MAX_ENCOUNTER);
                //LoadDoorData(doorData);
                BethilacGUID                     = 0;
                RhyolithGUID		             = 0;
                AlysrazarGUID		             = 0;
                ShannoxGUID					     = 0;
                BalorocGUID                      = 0;
                MajordomusGUID                   = 0;
				RagnarosGUID                     = 0;

				RagefaceGUID					 = 0;
				RagefaceGUID					 = 0;

				for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                      Encounter[i] = NOT_STARTED;
			}

            /*uint32 TypeToDeadFlag(uint32 type)
            {
                  uint32 return_value = 1;
                  for (uint32 i = 0; i < type; i++)
                  {
                       return_value *= 2;
                  }
                  return return_value;
            }*/

            /*void OnPlayerKilled(Player* player)
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    if (Encounter[i] == IN_PROGRESS)
                    {
                       
                    }
                }
            }*/
			
            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    if (Encounter[i] == IN_PROGRESS)
                        return true;
                }

                return false;
            }
		
            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
					// Bosses
                    case NPC_BETHTILAC:
                        BethilacGUID = creature->GetGUID();
                        break;
                    case NPC_RHYOLITH:
                        RhyolithGUID = creature->GetGUID();
                        break;
                    case NPC_ALYSRAZAR:
                        AlysrazarGUID = creature->GetGUID();
                        break;
                    case NPC_SHANNOX:
                        ShannoxGUID = creature->GetGUID();
                        break;
                    case NPC_BALOROC:
                        BalorocGUID = creature->GetGUID();
                        break;
                    case NPC_MAJORDOMUS:
                        MajordomusGUID = creature->GetGUID();
                        break;
                    case NPC_RAGNAROS_CATA:
                        RagnarosGUID = creature->GetGUID();
                        break;

					// Npcs
					case NPC_RAGEFACE:
                        RagefaceGUID = creature->GetGUID();
                        break;
                    case NPC_RIPLIMB:
                        RiplimbGUID = creature->GetGUID();
                        break;

                }

             }

            void OnGameObjectCreate(GameObject* gameObject)
            {
                /*switch (gameObject->GetEntry())
                {
                   	case GO_ASSEMBLY_DOOR:
						AssemblyDoorGUID = gameObject->GetGUID();
						HandleGameObject(NULL, true, gameObject);
					break;
                }*/
            }

            void OnGameObjectRemove(GameObject* gameObject)
            {
                /*switch (gameObject->GetEntry())
                {
                    
                }*/
            }

            void OnCreatureDeath(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case NPC_BETHTILAC:
                    case NPC_RHYOLITH:
                    case NPC_ALYSRAZAR:
                    case NPC_SHANNOX:
                    case NPC_BALOROC:
                    case NPC_MAJORDOMUS:
                    case NPC_RAGNAROS_CATA:
                    default:
                        break;
                }
            }

            void ProcessEvent(WorldObject* /*gameObject*/, uint32 eventId)
            {
               
            }


            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case BOSS_BETHTILAC:
						break;
					case BOSS_RHYOLITH:
						break;
					case BOSS_ALYSRAZAR:
						break;
					case BOSS_SHANNOX:
						if (type=IN_PROGRESS)
						{

						}

						break;
					case BOSS_BALOROC:
						break;
					case BOSS_MAJORDOMUS:
						break;
					case BOSS_RAGNAROS:
						break;

                }

                return true;
            }

            void SetData(uint32 type, uint32 data)
            {
                /*switch (type)
                {
					
					default:
					break;
                }*/
            }

            void SetData64(uint32 /*type*/, uint64 /*data*/)
            {
            }

            uint64 GetData64(uint32 data)
            {
                switch (data)
                {
					// Bosses
                    case BOSS_BETHTILAC:
                        return BethilacGUID;
                    case BOSS_RHYOLITH:
                        return RhyolithGUID;
                    case BOSS_ALYSRAZAR:
                        return AlysrazarGUID;
                    case BOSS_SHANNOX:
                        return ShannoxGUID;
                    case BOSS_BALOROC:
                        return BalorocGUID;
                    case BOSS_MAJORDOMUS:
						return MajordomusGUID;
                    case BOSS_RAGNAROS:
						return RagnarosGUID;
                    /*
					// Npcs
					case NPC_RAGEFACE:
						return RagefaceGUID;
					case NPC_RIPLIMB:
						return RiplimbGUID;*/
                }

                return 0;
            }

            uint32 GetData(uint32 type)
            {
                /*switch (type)
                {

                    default:
                        break;
                }*/

                return 0;
            }

        std::string GetSaveData()
        {
            std::ostringstream saveStream;
            saveStream << GetBossSaveData();
            return saveStream.str();
        }

        void Load(const char * data)
        {
            std::istringstream loadStream(LoadBossState(data));
        }
            void Update(uint32 diff)
            {
                
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_firelands_InstanceMapScript(map);
        }
};


void AddSC_instance_firelands()
{
    new instance_firelands();
}