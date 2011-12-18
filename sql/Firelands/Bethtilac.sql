/*##############################
## Firelands Updates by Naios ##
##############################*/
-- Contents:(Beth'tilac)

SET @BETHTHILAC_SCRIPT_TEXTS_ENTRY := 0;
SET @BETHTHILAC_GUID := 15428168;

-- ### Set Scriptnames ###
UPDATE `creature_template` SET `ScriptName`='boss_bethtilac' WHERE `entry`=52498 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_cinderweb_spinner' WHERE `entry`=53642 LIMIT 1;

-- Bethilac
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (@BETHTHILAC_GUID, 52498, 720, 1, 1, 0, 0, 67.8886, 387.82, 80, 3.68228, 300, 0, 0, 21147356, 0, 0, 0, 0, 0);
