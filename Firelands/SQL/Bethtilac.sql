/*##############################
## Firelands Updates by Naios ##
##############################*/
-- Contents:(Beth'tilac)

SET @BETHTHILAC_SCRIPT_TEXTS_ENTRY := 0;
SET @BETHTHILAC_GUID := 15428168;

-- ### Set Scriptnames ###
UPDATE `creature_template` SET `ScriptName`='boss_bethtilac' WHERE `entry`=52498 LIMIT 1;

-- Sticky Web (Bethilacs Door)
DELETE FROM `gameobject` WHERE id = 208877 and map = 720;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (4003912, 208877, 720, 1, 1, -11.7895, 313.124, 78.8203, 0.74318, 0, 0, 0.363097, 0.931751, 300, 0, 1);

-- Bethilac
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (@BETHTHILAC_GUID, 52498, 720, 1, 1, 0, 0, 67.8886, 387.82, 80, 3.68228, 300, 0, 0, 21147356, 0, 0, 0, 0, 0);
