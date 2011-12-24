/*##############################
## Firelands Updates by Naios ##
##############################*/
-- Contents:(Avengers of Hyjal)

-- TODO: Add extended costs to Vendors

-- Naresir Stormfury <Avengers of Hyjal Quartermaster> (54401)

DELETE FROM `creature_template` WHERE `entry`=54401 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 54401, 0, 0, 0, 0, 0, 38788, 0, 0, 0, "Naresir Stormfury", "Avengers of Hyjal Quartermaster", "", 0, 85, 85, 3, 35, 35, 4224, 1.0, 1.14286, 1.0, 0, 530, 713, 0, 827, 1.0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 530, 713, 827, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 1, 1.19803, 0.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, "", "14480");

DELETE FROM `npc_vendor` WHERE `entry`=54401;
INSERT INTO `npc_vendor` (`entry`,`item`,`slot`,`maxcount`,`incrtime`,`ExtendedCost`) VALUES 
(54401,70934,0,0,0,0)
,(54401,69001,0,0,0,0)
,(54401,71253,0,0,0,0)
,(54401,71227,0,0,0,0)
,(54401,71250,0,0,0,0)
,(54401,70930,0,0,0,0)
,(54401,71258,0,0,0,0)
,(54401,69002,0,0,0,0)
,(54401,69000,0,0,0,0)
,(54401,71255,0,0,0,0)
,(54401,71254,0,0,0,0)
,(54401,71249,0,0,0,0)
,(54401,71131,0,0,0,0)
,(54401,71229,0,0,0,0)
,(54401,70933,0,0,0,0)
,(54401,71217,0,0,0,0)
,(54401,71215,0,0,0,0)
,(54401,71237,0,0,0,0)
,(54401,71230,0,0,0,0)
,(54401,68998,0,0,0,0)
,(54401,71228,0,0,0,0)
,(54401,68996,0,0,0,0)
,(54401,71216,0,0,0,0);

-- Lurah Wrathvine <Crystallized Firestone Collector> (54402)
DELETE FROM `creature_template` WHERE `entry`=54402 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 54402, 0, 0, 0, 0, 0, 38789, 0, 0, 0, "Lurah Wrathvine", "Crystallized Firestone Collector", "", 0, 85, 85, 3, 35, 35, 128, 1.0, 1.14286, 1.0, 0, 530, 713, 0, 827, 1.0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 530, 713, 827, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 1, 1.19803, 0.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, "", "14480");

DELETE FROM `npc_vendor` WHERE `entry`=54402;
INSERT INTO `npc_vendor` (`entry`,`item`,`slot`,`maxcount`,`incrtime`,`ExtendedCost`) VALUES 
(54402,69113,0,0,0,0)
,(54402,71560,0,0,0,0)
,(54402,71567,0,0,0,0)
,(54402,71590,0,0,0,0)
,(54402,71592,0,0,0,0)
,(54402,71563,0,0,0,0)
,(54402,71593,0,0,0,0)
,(54402,71561,0,0,0,0)
,(54402,71558,0,0,0,0)
,(54402,71568,0,0,0,0)
,(54402,71562,0,0,0,0)
,(54402,71557,0,0,0,0)
,(54402,71587,0,0,0,0)
,(54402,71641,0,0,0,0)
,(54402,69109,0,0,0,0)
,(54402,71579,0,0,0,0)
,(54402,71577,0,0,0,0)
,(54402,71580,0,0,0,0)
,(54402,71559,0,0,0,0)
,(54402,71564,0,0,0,0)
,(54402,71575,0,0,0,0)
;


