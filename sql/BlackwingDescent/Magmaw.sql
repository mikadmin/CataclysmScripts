-- Mahmaw (Blackwing Descent) Updates
-- by Naios

DELETE FROM `vehicle_accessory` WHERE `entry` = 41570;
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`)
VALUES (41570, 42347, 0, 0, 'Magmaws Head');
UPDATE `creature_template` SET `VehicleId`=1408	 WHERE `entry`=41570 LIMIT 1;

-- Notes to find the right VehicleID
-- 1443 Kopf oben aber nicht sichtbar
-- 1442 sehr gut aber kopf verdreht sitzt richtig und so
-- 1511,1519,1531 noch besser kopf ist blos zu weit oben 9551
-- 1512 Kopf ist weiter unten schaut abe rnach oben
-- 1514 Kopf zu weit unten aber nicht viel 9560
-- 1524 zu weit rechts

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_magmaw' WHERE `entry`=41570 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 41570;

-- Updates Magmaws Head
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=42347 LIMIT 1;

-- Delete non Blizzlike spawned ads
DELETE FROM `creature` WHERE `guid` IN(6521578, 6521576) AND `id` = 42362;

-- Adds Ingition Aura to the Ignation Trigger
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (49447, 0, 0, 0, 0, 0, '92131 0');

UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=49447 LIMIT 1;
UPDATE `creature_template` SET `scale`=4 WHERE `entry`=49447 LIMIT 1;
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=49447 LIMIT 1;