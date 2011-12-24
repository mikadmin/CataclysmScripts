-- Drahga Shadowburner (Grim Batol) Updates
-- by Naios

-- Who added SmartAI to Valiona? ^^
UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_valiona_gb' WHERE `entry`=40320 LIMIT 1;

-- Changes Inhabit Type so that Valiona is able to Fly
UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=40320 LIMIT 1;

-- Changes Valiona Spawn Place in Grim Batol to the Blizzlike looking Place... (GUID = 6623304)
UPDATE `creature` SET `position_x`=-375.33, `position_y`=-667.291, `position_z`=218.05, `orientation`=3.29545 WHERE `guid`=6623304 LIMIT 1;

-- Add Scriptname to the invoked flame spirit
UPDATE `creature_template` SET `ScriptName`='mob_invoked_flame_spirit' WHERE `entry`=40357 LIMIT 1;

-- Fixes wrong Faction of the Invocation of FLame and the Portal Trigger
UPDATE `creature_template` SET `modelid2`=0, `faction_A`=14, `faction_H`=14 WHERE `entry`=40355 LIMIT 1;
UPDATE `creature_template` SET `modelid2`=0, `faction_A`=14, `faction_H`=14 WHERE `entry`=40357 LIMIT 1;