-- Throne of the Tides Updates
-- by Naios

-- Gursha removes SmartAI and assign scriptnames

-- Who added SmartAI? ^^
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_erunak_stonespeaker' WHERE `entry`=40825 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 40825;

UPDATE `creature_template` SET `ScriptName`='boss_mindbender_ghursha' WHERE `entry`=40788 LIMIT 1;

-- Neptulon
UPDATE `creature_template` SET `ScriptName`='boss_neptulon' WHERE `entry`=40792 LIMIT 1;

-- Faction fix
UPDATE `creature_template` SET `faction_A`=35, `faction_H`=35 WHERE `entry`=40792 LIMIT 1;


-- Commander Ulthrok
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_commander_ulthok' WHERE `entry`=40765 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 40765;