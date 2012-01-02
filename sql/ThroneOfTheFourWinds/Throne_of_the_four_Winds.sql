-- Throne of the Four Winds Updates
-- by Naios

-- First we wipe out all spawned GOBs in the Throne of the Four Winds (non Blizzlike Platforms etc.)
DELETE FROM `gameobject` WHERE `map` = 754;

-- 207737

-- INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (190264, 206667, 754, 1, 65534, -294.835, 831.909, 127.918, 4.76534, 1.1911e-43, 0, 0.68814, -0.725578, 1, 255, 1);

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(207737, 754, 1, 1, -287.054, 812.934, 202, 3.17018, 1.31722e-43, 0, 0.999898, -0.0142917, 300, 255, 1);

-- Portals
-- Not in Instance
-- 10N
(207339, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),
-- 25N
(207341, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),
-- 10H
(207340, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),
-- 25H
(207342, 1, 1, 1, -11359.2, 68.8634, 723.883, 1.897836, 0, 0, 0.802365, 0.596834, 300, 0, 1),

-- In Instance
-- 10N
(207339, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25N
(207341, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 10H
(207340, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25H
(207342, 754, 1, 1, -319.236, 814.702, 198.405, 3.1866, 0, 0, 0.999747, -0.0225, 300, 0, 1);