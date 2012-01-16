-- Ascendant Council (Bastion of Twilight) Updates
-- by Naios

-- Leaping Flames
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=47040 LIMIT 1;
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (47040, 0, 0, 0, 0, 0, '87645 0');
