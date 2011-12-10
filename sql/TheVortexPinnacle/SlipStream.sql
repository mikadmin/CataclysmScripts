
-- Aura the creature has no Model
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (45455, 0, 0, 0, 0, 0, '85021');

-- Creature Script
UPDATE `creature_template` SET `ScriptName`='npc_slipstream' WHERE `entry`=45455 LIMIT 1;