-- Throne of the Four Winds Updates
-- by Naios

-- First we wipe out all spawned GOBs in the Throne of the Four Winds (non Blizzlike Platforms etc.)
DELETE FROM `gameobject` WHERE `map` = 754;

-- 207737

-- INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (190264, 206667, 754, 1, 65534, -294.835, 831.909, 127.918, 4.76534, 1.1911e-43, 0, 0.68814, -0.725578, 1, 255, 1);

REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`)VALUES
(402338, 33, 10369, 'KL_SKYWALL_RAID', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 94, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623),
(402339, 33, 10370, 'kl_skywall_raid_phase1', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 94, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623);


INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(207737, 754, 15, 1, -287.054, 812.934, 202, 3.17018, 300, 0, 0.999898, -0.0142917, 300, 255, 1),
(402338, 754, 15, 1, -287.054, 812.934, 202, 3.17018, 300, 0, 0.999898, -0.0142917, 300, 255, 1),
-- (402339, 754, 15, 1, -287.054, 812.934, 202, 3.17018, 300, 0, 0.999898, -0.0142917, 300, 255, 1),

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
(207339, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25N
(207341, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 10H
(207340, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25H
(207342, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1);