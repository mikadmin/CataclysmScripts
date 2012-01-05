-- Ascendant Lord Obsidius (Blackrock Caverns) Updates
-- by Naios

SET @OBSIDIUS_GUID := 1051169;

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_ascendant_lord_obsidius' WHERE `entry`=39705 LIMIT 1;
-- DELETE FROM `smart_scripts` WHERE `entryorguid` = 39705;

-- Deletes Obsidius and his Shadows to spawn them on a more blizzlike looking place
DELETE FROM `creature` WHERE `guid`=@OBSIDIUS_GUID LIMIT 1;
DELETE FROM `creature_addon` WHERE `guid`=@OBSIDIUS_GUID LIMIT 1;

DELETE FROM `creature` WHERE `id`=40817 AND `map` = 645;

DELETE FROM `creature_addon` WHERE `guid`=1051175 LIMIT 1;
DELETE FROM `creature_addon` WHERE `guid`=1051173 LIMIT 1;
DELETE FROM `creature_addon` WHERE `guid`=1051171 LIMIT 1;
/*
-- Spawns Obsidius new on a Blizzlike looking Place
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(39705, 645, 1, 1, 0, 0, 350.159, 561.722, 66.0078, 3.09457, 300, 0, 0, 104264, 0, 0, 0, 0, 0, 0);
*/