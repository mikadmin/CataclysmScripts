-- Blackwing Descent Misc
-- by Naios

-- Onyxia Elevator
DELETE FROM `gameobject` WHERE `id` = 207834 AND `map` = 669;
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`)
VALUES (207834, 669, 15, 1, -109.87, -223.157, 11.5354, 1.79425, 0, 0, 0.781537, 0.623858, 300, 1, 0);
