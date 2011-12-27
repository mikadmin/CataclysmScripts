-- Grand Vizier Ertan Updates
-- by Naios

-- Every time the same... SmartAI at the Boss...
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_vizir_ertan' WHERE `entry`=43878 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 43878;