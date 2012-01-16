-- Lady Nazjar Updates
-- by Naios

-- She is spawned twice...
DELETE FROM `creature` WHERE `guid` = 1086658 AND `id` = 39959;

-- Every time the same smartAI at the boss^^
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_lady_nazjar' WHERE `entry`=40586 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 40586;

UPDATE `creature_template` SET `ScriptName`='mob_waterspout' WHERE `entry`=48571 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='mob_waterspout' WHERE `entry`=49108 LIMIT 1;

-- Who spawned all those non blizzlike mobs? (no creature addon)
-- Guards
DELETE FROM `creature` WHERE `guid` = 1086656 AND `id` = 40633;
DELETE FROM `creature` WHERE `guid` = 1086654 AND `id` = 40633;
DELETE FROM `creature` WHERE `guid` = 1086657 AND `id` = 40633;
DELETE FROM `creature` WHERE `guid` = 1086655 AND `id` = 40633;

-- Witches
DELETE FROM `creature` WHERE `guid` = 1086682 AND `id` = 44404;
DELETE FROM `creature` WHERE `guid` = 1086685 AND `id` = 44404;
DELETE FROM `creature` WHERE `guid` = 1086684 AND `id` = 44404;
DELETE FROM `creature` WHERE `guid` = 1086683 AND `id` = 44404;