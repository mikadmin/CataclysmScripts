-- Stream spell cast non fall damage buff too
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (89501, 87740, 0, 'Throne of the four Winds no fall damage buff on enterning slipstream');

-- Portals spawn
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES


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
(207339, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25N
(207341, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 10H
(207340, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1),
-- 25H
(207342, 754, 15, 1, -324.068604, 817.825256, 198.405,6.280360, 0, 0, 0.999747, -0.0225, 300, 0, 1);