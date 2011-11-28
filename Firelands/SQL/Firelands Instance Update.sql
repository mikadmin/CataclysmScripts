
/*##############################
## Firelands Updates by Naios ##
##############################*/

SET @SHANNOX_SCRIPT_TEXTS_ENTRY = -1999970;

-- ### Instance Template ###
DELETE FROM `instance_template` WHERE map = 720;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (720, 0, 'instance_firelands', 1);

-- ### Set Scriptnames ###
UPDATE `creature_template` SET `ScriptName`='boss_shannox' WHERE `entry`=53691 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_rageface' WHERE `entry`=53695 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_riplimb' WHERE `entry`=53694 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_shannox_spear' WHERE `entry`=53752 LIMIT 1;

-- ### Set Script_Texts ###
-- # Shannox #
-- Enrage Warning
DELETE FROM `script_texts` WHERE `entry` = @SHANNOX_SCRIPT_TEXTS_ENTRY and npc_entry = 53691;

INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (53691, @SHANNOX_SCRIPT_TEXTS_ENTRY, 'Shannox becomes enraged at seeing once of his companions fall!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 41, 0, 0, 'Shannox Enrage Warning');
