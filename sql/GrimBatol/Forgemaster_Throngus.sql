-- Forgemaster Throngus (Grim Batol) Updates
-- by Naios

-- Fire Patch
-- Makes the Fire invisible
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=48711 LIMIT 1;
