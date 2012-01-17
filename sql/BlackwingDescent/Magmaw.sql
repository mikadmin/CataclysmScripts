-- Magmaw (Blackwing Descent) Updates
-- by Naios

DELETE FROM `vehicle_accessory` WHERE `entry` = 41570;
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`)
VALUES (41570, 42347, 0, 0, 'Magmaws Head');
UPDATE `creature_template` SET `VehicleId`=522	 WHERE `entry`=41570 LIMIT 1;
UPDATE `creature_template` SET `IconName`='' WHERE `entry`=41570 LIMIT 1;

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
UPDATE `creature_template` SET `VehicleId`=516	 WHERE `entry`=42347 LIMIT 1;

UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_magmaws_head' WHERE `entry`=42347 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 42347;
UPDATE `creature_template` SET `IconName`='vehichleCursor' WHERE `entry`=42347 LIMIT 1;

-- Adds the launch hook ability to the Magmaw Head vehicle
UPDATE `creature_template` SET `spell1`=77917 WHERE `entry`=41570 LIMIT 1;

-- Delete non Blizzlike spawned ads
DELETE FROM `creature` WHERE `guid` IN(6521578, 6521576) AND `id` = 42362;

-- Adds Ingition Aura to the Ignation Trigger
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (49447, 0, 0, 0, 0, 0, '92131 0');

UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=49447 LIMIT 1;
UPDATE `creature_template` SET `scale`=4 WHERE `entry`=49447 LIMIT 1;
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=49447 LIMIT 1;

-- Spell Scriptnames
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(78941, 'spell_parasitic_infection');

-- Lava parasites
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=41806 LIMIT 1;
UPDATE `creature_template` SET `Health_mod`=2, `exp`=3 WHERE `entry`=41806 LIMIT 1;

-- Lava Parisites Trigger
UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_pillar_of_flame_trigger' WHERE `entry`=41843 LIMIT 1;
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=41843 LIMIT 1;
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=41843 LIMIT 1;

-- Lava Parasite
SET @ENTRY := 41806;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,33,0,100,0,0,1,1,1,11,78941,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Parasitic Infection");

-- Nefarian Helper
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=49427 LIMIT 1;
UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88 WHERE `entry`=49427 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_nefarian_helper_heroic' WHERE `entry`=49427 LIMIT 1;
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=49427 LIMIT 1;

-- Blazing Bone Construct
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=49416 LIMIT 1;

SET @ENTRY := 49416;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,0,20,20,0,0,11,92177,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Blazing Bone Construct cast Armageddon at 20% HP");
