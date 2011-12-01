
/*##############################
## Firelands Updates by Naios ##
##############################*/

SET @SHANNOX_SCRIPT_TEXTS_ENTRY = -1999971;

-- ### Instance Template & Access Requirement ###
DELETE FROM `instance_template` WHERE map = 720;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (720, 0, 'instance_firelands', 1);

DELETE FROM `access_requirement` WHERE `mapId` = 720;
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 0, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 1, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 2, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES (720, 3, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');

-- ### Set Scriptnames ###
-- Shannox
UPDATE `creature_template` SET `ScriptName`='boss_shannox' WHERE `entry`=53691 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_rageface' WHERE `entry`=53695 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_riplimb' WHERE `entry`=53694 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_shannox_spear' WHERE `entry`=53752 LIMIT 1;

-- Bethilac
UPDATE `creature_template` SET `ScriptName`='boss_bethtilac' WHERE `entry`=52498 LIMIT 1;

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

-- ### Updates Creature_Template ###
-- # Shannox Spear#

UPDATE `creature_template` SET `scale`='3' WHERE `entry`=53752 LIMIT 1;

/*
DELETE FROM `creature_template` WHERE `entry`=53752 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 53752, 0, 0, 0, 0, 0, 16925, 0, 0, 0, "Spear of Shannox", "", "", 0, 1, 1, 0, 35, 35, 0, 1.0, 1.14286, 4.0, 0, 2, 2, 0, 24, 1.0, 0, 0, 1, 33554562, 0, 10, 0, 0, 0, 0, 2, 2, 24, 0, 1091568712, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 3, 14.0, 1.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 164, 1, 0, 0, 0, "npc_shannox_spear", "1");
*/