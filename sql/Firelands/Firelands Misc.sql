/*##############################
## Firelands Updates by Naios ##
##############################*/
-- Contents:(Instance & GOB Spawns)

-- Instance Template & Access Requirement
DELETE FROM `instance_template` WHERE map = 720;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (720, 0, 'instance_firelands', 1);

DELETE FROM `access_requirement` WHERE `mapId` = 720;
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES
(720, 0, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)'),
(720, 1, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)'),
(720, 2, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)'),
(720, 3, 85, 0, 0, 0, 0, 0, 0, NULL, 'Firelands (Enterence)');

-- Sticky Web (Bethilacs Door) (Not Blizzlike Spawn but looks similar)
DELETE FROM `gameobject` WHERE id = 208877 and map = 720;
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(208877, 720, 1, 1, -11.7895, 313.124, 78.8203, 0.74318, 0, 0, 0.363097, 0.931751, 300, 0, 1),
(208877, 720, 2, 1, -11.7895, 313.124, 78.8203, 0.74318, 0, 0, 0.363097, 0.931751, 300, 0, 1),
(208877, 720, 4, 1, -11.7895, 313.124, 78.8203, 0.74318, 0, 0, 0.363097, 0.931751, 300, 0, 1),
(208877, 720, 8, 1, -11.7895, 313.124, 78.8203, 0.74318, 0, 0, 0.363097, 0.931751, 300, 0, 1);

-- Baloros Door  (Not Blizzlike Spawn)
DELETE FROM `gameobject` WHERE id = 209066 and map = 720;
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(209066, 720, 1, 1, -30.2994, -64.2117, 57.1917, 5.60496, 0, 0, 0.332652, -0.94305, 300, 0, 1),
(209066, 720, 2, 1, -30.2994, -64.2117, 57.1917, 5.60496, 0, 0, 0.332652, -0.94305, 300, 0, 1),
(209066, 720, 4, 1, -30.2994, -64.2117, 57.1917, 5.60496, 0, 0, 0.332652, -0.94305, 300, 0, 1),
(209066, 720, 8, 1, -30.2994, -64.2117, 57.1917, 5.60496, 0, 0, 0.332652, -0.94305, 300, 0, 1);

-- Majordomo Staghelm Door (Not Blizzlike Spawn)
DELETE FROM `gameobject` WHERE id = 208873 and map = 720;
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(208873, 720, 1, 1, 576.036, -61.7832, 90.3394, 5.60688, 0, 0, 0.331747, -0.943368, 300, 0, 1),
(208873, 720, 2, 1, 576.036, -61.7832, 90.3394, 5.60688, 0, 0, 0.331747, -0.943368, 300, 0, 1),
(208873, 720, 4, 1, 576.036, -61.7832, 90.3394, 5.60688, 0, 0, 0.331747, -0.943368, 300, 0, 1),
(208873, 720, 8, 1, 576.036, -61.7832, 90.3394, 5.60688, 0, 0, 0.331747, -0.943368, 300, 0, 1);