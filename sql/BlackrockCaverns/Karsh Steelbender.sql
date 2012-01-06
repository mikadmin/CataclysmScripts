-- Karsh Steelbender (Blackrock Caverns) Updates
-- by Naios

-- Quecksilver Updates
UPDATE `creature_template` SET `unit_flags`=33686022 WHERE `entry`=40004 LIMIT 1;

-- Karsh
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_karsh_steelbender' WHERE `entry`=39698 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 39698;
