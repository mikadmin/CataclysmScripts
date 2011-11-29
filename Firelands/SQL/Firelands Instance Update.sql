
/*##############################
## Firelands Updates by Naios ##
##############################*/

SET @SHANNOX_SCRIPT_TEXTS_ENTRY = -1999970;

-- ### Instance Template & Access Requirement ###
DELETE FROM `instance_template` WHERE map = 720;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (720, 0, 'instance_firelands', 1);

DELETE FROM `access_requirement` WHERE `mapId` = 720;
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 0, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 1, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 2, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 3, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');

-- ### Set Scriptnames ###
UPDATE `creature_template` SET `ScriptName`='boss_shannox' WHERE `entry`=53691 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_rageface' WHERE `entry`=53695 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_riplimb' WHERE `entry`=53694 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_shannox_spear' WHERE `entry`=53752 LIMIT 1;

-- ### Set Script_Texts ###
-- # Shannox #
-- Enrage Warning
DELETE FROM `script_texts` WHERE `entry` = @SHANNOX_SCRIPT_TEXTS_ENTRY and npc_entry = 53691;
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (53691, @SHANNOX_SCRIPT_TEXTS_ENTRY, 'A-hah! The interlopers! Kill them EAT THEM!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 24517, 0, 0, 0, 'Shannox Aggro Yell');

DELETE FROM `script_texts` WHERE `entry` = @SHANNOX_SCRIPT_TEXTS_ENTRY-1 and npc_entry = 53691;
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (53691, @SHANNOX_SCRIPT_TEXTS_ENTRY-1, 'Shannox becomes enraged at seeing once of his companions fall!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 41, 0, 0, 'Shannox Enrage Warning');

DELETE FROM `script_texts` WHERE `entry` = @SHANNOX_SCRIPT_TEXTS_ENTRY-2 and npc_entry = 53691;
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (53691, @SHANNOX_SCRIPT_TEXTS_ENTRY-2, 'Oh, you murders! Why? Why would you kill such a nobie animal?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 24517, 0, 0, 0, 'Shannox Yell on killing a Dog');

DELETE FROM `script_texts` WHERE `entry` = @SHANNOX_SCRIPT_TEXTS_ENTRY-3 and npc_entry = 53691;
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (53691, @SHANNOX_SCRIPT_TEXTS_ENTRY-3, 'Ohh... the pain   Lord of Fire. It hurts...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 24517, 0, 0, 0, 'Shannox Dead Yell');