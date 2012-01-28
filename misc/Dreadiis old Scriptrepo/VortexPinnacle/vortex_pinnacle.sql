-- Aura the creature has no Model
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (45455, 0, 0, 0, 0, 0, '85021');

-- Creature Script
UPDATE `creature_template` SET `ScriptName`='npc_slipstream' WHERE `entry`=45455 LIMIT 1;

-- Spawns

-- Firstly we clear all spawns...
DELETE FROM `creature` WHERE `id`=45455;

-- 1. Slipstream
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (15431026, 45455, 657, 1, 1, 0, 0, -771.279, -58.8362, 639.026, 4.16842, 300, 0, 0, 42, 0, 0, 0, 0, 0);

-- 2. Slipstream
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (1074096, 45455, 657, 1, 1, 0, 0, -810, -70, 655, 3.24442, 600, 0, 0, 42, 0, 0, 0, 0, 0);
