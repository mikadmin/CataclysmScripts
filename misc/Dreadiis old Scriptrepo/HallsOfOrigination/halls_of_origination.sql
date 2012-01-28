-- Halls of Origination
UPDATE `instance_template` SET `script`='instance_halls_of_origination' WHERE `map`=644;

-- Temple Guardian Anhuur

DELETE FROM `creature_text` WHERE `entry` = 39425;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39425', '0', '0', 'Turn back, intruders! These halls must not be disturbed!', '1', '0', '0', '0', '0', '18580', 'VO_HO_Anhuur_Engage'), 
('39425', '4', '0', 'Temple Guardian Anhuur becomes protected by his defense beacons! Disable them by pulling the levers below!', '3', '0', '0', '0', '0', '0', 'VO_HO_Anhuur_Special'),
('39425', '3', '0', 'What... have you... done? ', '1', '0', '0', '0', '0', '18579', 'VO_HO_Anhuur_Death'),
('39425', '2', '0', 'A product of your own insolence!', '1', '0', '0', '0', '0', '18583', 'VO_HO_Anhuur_Slay02'),
('39425', '1', '0', 'Beacons of light, bestow upon me your aegis!', '1', '0', '0', '0', '0', '18581', 'VO_HO_Anhuur_Event'),
('39425', '2', '1', 'I regret nothing !', '1', '0', '0', '0', '0', '18582', 'VO_HO_Anhuur_Slay01');

UPDATE `gameobject_template` SET `ScriptName` = 'go_beacon_of_light' WHERE `entry` = 203133;
UPDATE `gameobject_template` SET `ScriptName` = 'go_beacon_of_light' WHERE `entry` = 203136;
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 206506;
UPDATE `creature_template` SET `modelid1` = 1126, `modelid2` = 11686, `flags_extra` = 130 WHERE `entry` = 40183;
UPDATE `creature_template` SET `ScriptName` = 'boss_temple_guardian_anhuur' WHERE `creature_template`.`entry` =39425;
DELETE FROM `creature_template_addon` WHERE (`entry`=40283);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (40283, 0, 0, 0, 1, 0, '75116 0');

-- Earthrager Ptah
DELETE FROM `creature_text` WHERE `entry` = 39428;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39428', '0', '0', 'More carrion for the swarm... ', '1', '0', '0', '0', '0', '18906', 'VO_HO_Ptah_Engage'), 
('39428', '1', '0', 'Ptah... is... no more... ', '1', '0', '0', '0', '0', '18905', 'VO_HO_Ptah_Death'),
('39428', '2', '0', 'Dust to dust... ', '1', '0', '0', '0', '0', '18907', 'VO_HO_Ptah_Slay01'),
('39428', '2', '1', 'HYAAAH!!', '1', '0', '0', '0', '0', '18908', 'VO_HO_Ptah_Slay02');

-- Anraphet
UPDATE `creature_template` SET ScriptName='boss_anraphet' WHERE `entry`=39788;
DELETE FROM `creature_text` WHERE `entry` = 39788;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39788', '0', '0', 'This unit has been activated outside normal operating protocols. Downloading new operational parameters. Download complete. Full unit self defense routines are now active. Destruction of foreign units in this system shall now commence.', '1', '0', '0', '0', '0', '20857', 'VO_HO_Anraphet_Intro01'), 
('39788', '1', '0', 'Purge of unauthorized entities commencing.', '1', '0', '0', '0', '0', '20862', 'VO_HO_Anraphet_Engage01'),
('39788', '2', '1', 'Purge Complete. ', '1', '0', '0', '0', '0', '20859', 'VO_HO_Anraphet_Slay02'),
('39788', '2', '0', 'Target Annihilated.', '1', '0', '0', '0', '0', '20858', 'VO_HO_Anraphet_Slay01'),
('39788', '3', '0', 'Omega Stance activated. Annihilation of foreign unit is now imminent.', '1', '0', '0', '0', '0', '20861', 'VO_HO_Anraphet_Special02'),
('39788', '4', '0', 'Anraphet unit shutting down...', '1', '0', '0', '0', '0', '20856', 'VO_HO_Anraphet_Death01');

-- Isiset
DELETE FROM `creature_text` WHERE `entry` = 39587;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39587', '0', '0', 'Gaze to the heavens! What do you see?', '1', '0', '0', '0', '0', '18843', 'VO_HO_Isiset_Engage'), 
('39587', '1', '0', 'Bask in my radiance!', '1', '0', '0', '0', '0', '18845', 'VO_HO_Isiset_Event01'),
('39587', '2', '0', 'Insignificant!', '1', '0', '0', '0', '0', '18847', 'VO_HO_Isiset_Slay02'),
('39587', '2', '1', 'The glimmer of your life, extinguished.', '1', '0', '0', '0', '0', '18846', 'VO_HO_Isiset_Slay01'),
('39587', '3', '0', 'Eons of darkness... by your hand.', '1', '0', '0', '0', '0', '18842', 'VO_HO_Isiset_Death01'),
('39587', '3', '1', 'My luster... wanes.', '1', '0', '0', '0', '0', '18844', 'VO_HO_Isiset_Death02');

UPDATE `creature_template` SET ScriptName='boss_isiset' WHERE `entry`=39587;
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (74136, 'spell_isiset_supernova');
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39720;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39721;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39722;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39720 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39720, 0, 39720, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 74134, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Astral Rain');
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39721 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39721, 0, 0, 0, 0, 0, 100, 0, 3000, 5000, 5000, 7000, 11, 74374, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, ' ');
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39722 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39722, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 74133, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Veil of Sky');

-- Ammunae
DELETE FROM `creature_text` WHERE `entry` = 39731;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39731', '0', '0', 'This chamber will flourish with your life energy!', '1', '0', '0', '0', '0', '18571', 'VO_HO_Ammunae_Engage'), 
('39731', '1', '0', 'Your life, UNLEASHED!', '1', '0', '0', '0', '0', '18572', 'VO_HO_Ammunae_Event'),
('39731', '2', '0', 'Wither away!', '1', '0', '0', '0', '0', '18573', 'VO_HO_Ammunae_Slay01'),
('39731', '2', '1', 'Waste of energy.', '1', '0', '0', '0', '0', '18574', 'VO_HO_Ammunae_Slay02'),
('39731', '3', '0', 'The cycle continues...', '1', '0', '0', '0', '0', '18569', 'VO_HO_Ammunae_Death');

-- Setesh
DELETE FROM `creature_text` WHERE `entry` = 39732;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39732', '0', '0', 'You fear that which you cannot control. But can you control your fear? ', '1', '0', '0', '0', '0', '18553', 'VO_HO_Setesh_Engage'),
('39732', '1', '0', 'Behold, how infinity befalls your world', '1', '0', '0', '0', '0', '18554', 'VO_HO_Setesh_Event'), 
('39732', '2', '0', 'Do you understand now?', '1', '0', '0', '0', '0', '18556', 'VO_HO_Setesh_Slay02'),
('39732', '2', '1', 'Embrace the end.', '1', '0', '0', '0', '0', '18555', 'VO_HO_Setesh_Slay01'),
('39732', '3', '0', 'Yes! Harness... your... hatred.', '1', '0', '0', '0', '0', '18552', 'VO_HO_Setesh_Death');

-- Rajh
DELETE FROM `creature_text` WHERE `entry` = 39378;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) 
VALUES 
('39378', '0', '0', 'Defilers! Wretches! Fiends! Begone from here!', '1', '0', '0', '0', '0', '18911', 'VO_HO_Rajh_Engage'), 
('39378', '1', '0', 'Can you feel it? The blessed warmth of the sun?', '1', '0', '0', '0', '0', '18912', 'VO_HO_Rajh_Event01'),
('39378', '2', '0', 'I send you to your deity.', '1', '0', '0', '0', '0', '18913', 'VO_HO_Rajh_Slay01'),
('39378', '2', '1', 'I will take this life as an offering!', '1', '0', '0', '0', '0', '18914', 'VO_HO_Rajh_Slay01'),
('39378', '3', '0', 'Blazing rays of light, take me!', '1', '0', '0', '0', '0', '18910', 'VO_HO_Rajh_Death');

-- Hero drop  
UPDATE creature_template SET difficulty_entry_1= 48815 WHERE entry=39378;
UPDATE creature_template SET difficulty_entry_1= 48710 WHERE entry=39587;
UPDATE creature_template SET difficulty_entry_1= 48715 WHERE entry=39731;
UPDATE creature_template SET difficulty_entry_1= 48776 WHERE entry=39732;
-- Graveyard
REPLACE INTO game_graveyard_zone VALUES (1823, 4945,0);
-- Respawn
UPDATE creature SET spawntimesecs=3600 WHERE map=644;
-- Spawn GOBs
UPDATE gameobject_template SET type = 0 WHERE entry = 402333;
DELETE FROM gameobject WHERE map=644 AND id IN (206506, 202309, 202314, 202307, 402333);
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('206506','644','3','1','-641.39','304.37','52.9975','3.15858','0','0','0.999964','-0.00849289','300','0','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('202309','644','3','1','-439.397','366.874','89.7929','3.13816','0','0','0.999999','0.00171597','300','0','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('202314','644','3','1','-121.47','365.601','89.7908','6.27268','0','0','0.00525344','-0.999986','300','0','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('202307','644','3','1','-640.567','235.521','83.7956','1.49378','0','0','0.679362','0.733804','300','0','1');
-- Brann Bronzebart
SET @ENTRY  := 39908;
SET @GOSSIP := 39908;
SET @TEXTO := 'We\'re ready. Go Brann';
DELETE FROM `gossip_menu_option` WHERE `menu_id` = @GOSSIP;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`) VALUES
(@GOSSIP,'0','0',@TEXTO,'1','1','0','0','0','0','0',NULL);
UPDATE `creature_template` SET `gossip_menu_id` = @GOSSIP, `AIName`= 'SmartAI', minlevel=85, maxlevel=85 WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Brann Barbabronce - On gossip option select - Close gossip'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,9,0,0,0,0,0,0,15,202309,120,0,0.0,0.0,0.0,0.0,"Brann Barbabronce - Abre la puerta cuando habla");
DELETE FROM `creature` WHERE `id` = 39908 AND map =644; --
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
('39908','644','3','1','0','0','-446.498','367.005','90.1698','0.0874934','3600','0','0','42','0','0','0','0','0','0');
-- Temple Guardian Anhuur
SET @ENTRY := 39425;
SET @SOURCETYPE := 0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="",  ScriptName ='boss_temple_guardian_anhuur' WHERE entry=@ENTRY LIMIT 1;
UPDATE `creature_template` SET `equipment_id` = 39425 WHERE `entry` = 39425;
DELETE FROM `creature_equip_template` WHERE (`entry`=39425);
INSERT INTO `creature_equip_template` (`entry`, `equipentry1`, `equipentry2`, `equipentry3`) VALUES (39425, 55064, '0', '0');
-- Temple Guardian Anhuur
DELETE FROM `creature_loot_template` WHERE `entry`= 39425;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39425','55889','0','1','1','1','1'),
('39425','55888','0','1','1','1','1'),
('39425','55886','0','1','1','1','1'),
('39425','55887','0','1','1','1','1'),
('39425','55890','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 49262;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('49262','56407','0','1','1','1','1'),
('49262','56410','0','1','1','1','1'),
('49262','56411','0','1','1','1','1'),
('49262','56409','0','1','1','1','1'),
('49262','56408','0','1','1','1','1');

-- Earthrager Ptah
DELETE FROM `creature_loot_template` WHERE `entry`= 39428;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39428','56097','0','1','1','1','1'),
('39428','56095','0','1','1','1','1'),
('39428','56093','0','1','1','1','1'),
('39428','56096','0','1','1','1','1'),
('39428','56094','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48714;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48714','56423','0','1','1','1','1'),
('48714','56424','0','1','1','1','1'),
('48714','56425','0','1','1','1','1'),
('48714','56426','0','1','1','1','1'),
('48714','56422','0','1','1','1','1');

-- Anraphet
DELETE FROM `creature_loot_template` WHERE `entry`= 39788;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39788','57855','0','1','1','1','1'),
('39788','57857','0','1','1','1','1'),
('39788','57860','0','1','1','1','1'),
('39788','57856','0','1','1','1','1'),
('39788','57858','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48902;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48902','57870','0','1','1','1','1'),
('48902','57868','0','1','1','1','1'),
('48902','57867','0','1','1','1','1'),
('48902','57866','0','1','1','1','1'),
('48902','57869','0','1','1','1','1');

-- Isiset
DELETE FROM `creature_loot_template` WHERE `entry`= 39587;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39587','55994','0','1','1','1','1'),
('39587','55995','0','1','1','1','1'),
('39587','55996','0','1','1','1','1'),
('39587','55993','0','1','1','1','1'),
('39587','55992','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48710;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48710','56414','0','1','1','1','1'),
('48710','56416','0','1','1','1','1'),
('48710','56415','0','1','1','1','1'),
('48710','56412','0','1','1','1','1'),
('48710','56413','0','1','1','1','1');

-- Ammunae
DELETE FROM `creature_loot_template` WHERE `entry`= 39731;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39731','55997','0','1','1','1','1'),
('39731','56000','0','1','1','1','1'),
('39731','55998','0','1','1','1','1'),
('39731','55999','0','1','1','1','1'),
('39731','56001','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48715;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48715','56418','0','1','1','1','1'),
('48715','56419','0','1','1','1','1'),
('48715','56417','0','1','1','1','1'),
('48715','56421','0','1','1','1','1'),
('48715','56420','0','1','1','1','1');

-- Setesh
DELETE FROM `creature_loot_template` WHERE `entry`= 39732;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39732','57865','0','1','1','1','1'),
('39732','57864','0','1','1','1','1'),
('39732','57863','0','1','1','1','1'),
('39732','57862','0','1','1','1','1'),
('39732','57861','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48776;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48776','57875','0','1','1','1','1'),
('48776','57873','0','1','1','1','1'),
('48776','57871','0','1','1','1','1'),
('48776','57874','0','1','1','1','1'),
('48776','57872','0','1','1','1','1');

--
DELETE FROM `creature_loot_template` WHERE `entry`= 39378;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39378','56098','0','1','1','1','1'),
('39378','56099','0','1','1','1','1'),
('39378','56100','0','1','1','1','1'),
('39378','56101','0','1','1','1','1'),
('39378','56102','0','1','1','1','1'),
('39378','56104','0','1','2','1','1'),
('39378','56105','0','1','2','1','1'),
('39378','56106','0','1','2','1','1'),
('39378','56107','0','1','2','1','1'),
('39378','56108','0','1','2','1','1');

DELETE FROM `creature_loot_template` WHERE `entry`= 48815;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48815','56427','0','1','1','1','1'),
('48815','56428','0','1','1','1','1'),
('48815','56429','0','1','1','1','1'),
('48815','56430','0','1','1','1','1'),
('48815','56431','0','1','1','1','1'),
('48815','52078','0','1','0','1','1'),
('48815','56432','0','2','2','1','1'),
('48815','56433','0','2','2','1','1'),
('48815','56434','0','2','2','1','1'),
('48815','56435','0','2','2','1','1'),
('48815','56436','0','2','2','1','1');


DELETE FROM gameobject_template WHERE entry =207547;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `flags`) VALUES
('207547','11','9052','Lift of the Makers', 40);

DELETE FROM gameobject WHERE id=207547;

DELETE FROM gameobject WHERE id IN (192570, 192571)  AND map=1;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('4002861','192571','1','1','1','-10211','-1837.83','20.1281','6.25565','0','0','0.0137672','-0.999905','3600','100','1');
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('4002889','192570','1','1','1','-10211','-1837.83','20.1281','6.25565','0','0','0.0137672','-0.999905','3600','100','1');

-- Changed the Coordinates from the Bridge now its ok :)
DELETE FROM gameobject WHERE id = 206506;
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES ('206506', '644', '3', '1', '-640.65', '304.617', '53.24', '3.13999', '0', '0', '0.999964', '-0.00849289', '300', '0', '1');

SET NAMES 'utf8';

DELETE FROM script_texts WHERE npc_entry = 39428;
INSERT INTO script_texts (npc_entry, entry, content_default, sound, type) VALUES (39428, -1643019, "Mehr Aas für den Schwarm...", 18906, 1),
(39428, -1643020, "Ptah... ist nicht mehr...", 18905, 1),
(39428, -1643021, "Staub zu Staub...", 18907, 1),
(39428, -1643022, "HYAAAH!!", 18908, 1);

UPDATE creature_model_info SET combat_reach = 10 WHERE modelid = 31450;
