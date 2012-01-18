-- Throne of the Four Winds Updates
-- by Naios

-- First we wipe out all spawned GOBs in the Throne of the Four Winds (non Blizzlike Platforms etc.)
DELETE FROM `gameobject` WHERE `map` = 754;

REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`)
VALUES (207737, 11, 10369, 'Skywall Raid Center Platform', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 1);

-- Spawns the NPCS
DELETE FROM `creature` WHERE `map` = 754;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
-- Conclave of Wind
-- Anshal
(45870, 754, 15, 1, 0, 0, -48.5569, 1054.37, 198.456, 4.70171, 300, 0, 0, 4294600, 0, 0, 0, 0, 0, 0),
-- Nezir
(45871, 754, 15, 1, 0, 0, 188.114, 813.822, 198.456, 3.12542, 300, 0, 0, 7300820, 0, 0, 0, 0, 0, 0),
-- Rohash
(45872, 754, 15, 1, 0, 0, -52.8208, 577.173, 198.456, 1.56596, 300, 0, 0, 4294600, 0, 0, 0, 0, 0, 0),

-- Al'Akir
(46753, 754, 15, 1, 0, 0, -50.4909, 815.868, 189.984, 3.11662, 300, 0, 0, 4294600, 0, 0, 0, 0, 0, 0);

-- Slipstream fix

-- Stream spell cast non fall damage buff too
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (89501, 87740, 0, 'Throne of the four Winds no fall damage buff on enterning slipstream');

UPDATE `creature_template` SET `ScriptName`='npc_slipstream_raid', `InhabitType`=7 WHERE `entry`=47066 LIMIT 1;

-- Spawn
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(47066, 754, 15, 1, 0, 0, -240.017761,866.768616,195.846222,0.767140, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(47066, 754, 15, 1, 0, 0, -97.587189,1005.306580,195.847305,3.917370, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(47066, 754, 15, 1, 0, 0, -157.869171,946.417114,197.842194,0.774845, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(47066, 754, 15, 1, 0, 0, -123.714462,979.996765,197.894104,0.774845, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(47066, 754, 15, 1, 0, 0, 138.357468,764.759705,195.846069,3.913764, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(47066, 754, 15, 1, 0, 0, -3.720205,626.373230,195.845993,0.790134, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(47066, 754, 15, 1, 0, 0, -101.664581, 626.800537,195.846130, 2.354747, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(47066, 754, 15, 1, 0, 0, 135.816025, 762.667358, 198.312805, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `InhabitType`=7, `faction_A`=14, `faction_H`=14
WHERE `entry` IN (45870, 45871, 45872, 46753) LIMIT 5;

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
-- Raid Platform
(207737, 754,15, 1, -272.076, 816.277, 202, 3.140180, 0, 0, 0.999898, -0.0280381, 300, 0, 1),

-- Anshal Effect
(206699, 754, 15, 1, -48.5569, 1054.37,  200.527603, 4.70171, 0, 0, 0.999898, -0.0280381, 300, 0, 1),
-- Nezir Effect
(206700, 754, 15, 1, 188.114, 813.822,  202.527603, 3.12542, 0, 0, 0.999898, -0.0280381, 300, 0, 1),
-- Rohash Effect
(206701, 754, 15, 1, -52.8208, 577.173,  200.527603, 1.56596, 0, 0, 0.999898, -0.0280381, 300, 0, 1),
--  Al'Akir Effect
(207922, 754, 15, 1, -50.4909, 815.868, 189.984, 3.11662, 0, 0, 0.999898, -0.0280381, 300, 0, 1),

-- Portals
-- Not in Instance
-- 10N
/*(207339, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),
-- 25N
(207341, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),
-- 10H
(207340, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),
-- 25H
(207342, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),*/


-- In Instance
-- 10N
(207339, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25N
(207341, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 10H
(207340, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25H
(207342, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1);	

REPLACE INTO `instance_template` (`map`, `parent`, `startLocX`, `startLocY`, `startLocZ`, `startLocO`, `script`, `allowMount`)
VALUES (754, 0, NULL, NULL, NULL, NULL, 'instance_throne_of_the_four_winds', 1);


