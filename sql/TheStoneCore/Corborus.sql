-- Corborus (Grim Batol) Updates
-- by Naios

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_corborus' WHERE `entry`=43438 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 43438;
