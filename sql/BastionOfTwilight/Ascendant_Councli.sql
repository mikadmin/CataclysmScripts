-- Ascendant Council (Bastion of Twilight) Updates
-- by Naios

-- I really hate SmartAI on Bosses!!!!
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_feludius' WHERE `entry`=43687 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_ignacious' WHERE `entry`=43686 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_arion' WHERE `entry`=43688 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_terrastra' WHERE `entry`=43689 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(43687, 43686, 43688, 43689);

-- Leaping Flames
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=47040 LIMIT 1;
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (47040, 0, 0, 0, 0, 0, '87645 0');
/*
-- Feludius Water bomb fix
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (82699, 82700, 1, 'Feludius - Water Bomb AOE Damage');
*/
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (82665, 'spell_heart_of_ice');

DELETE FROM `creature` WHERE `id` = 43686;
