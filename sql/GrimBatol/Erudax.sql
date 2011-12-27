-- Erudax (Grim Batol) Updates
-- by Naios

SET @ERUDAX_GUID := 1051910;

-- Sets Scriptname of Faceless Corruptor and Alexstraszas Eggs
UPDATE `creature_template` SET `ScriptName`='mob_faceless' WHERE `entry`=40600 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='mob_alexstraszas_eggs' WHERE `entry`=40486 LIMIT 1;

-- The Waypoint of Erudax are not Blizzlike!!!!
-- On the Blizz Servers Erudax is standing still in the Room
DELETE FROM `creature_addon` WHERE `guid`=@ERUDAX_GUID LIMIT 1;
DELETE FROM `waypoint_data` WHERE `id`=10000310;

UPDATE `creature` SET `position_x`= -777.094, `position_y`=-825.152, `position_z`=233.233, `orientation`=0 WHERE `guid`= @ERUDAX_GUID LIMIT 1;

-- Faceless Corruptor
-- Faction & Level fix
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=40600 LIMIT 1;
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=48844 LIMIT 1;

UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83 WHERE `entry`=40600 LIMIT 1;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85 WHERE `entry`=48844 LIMIT 1;

-- Difficult entry fix
UPDATE `creature_template` SET `difficulty_entry_1`=48844 WHERE `entry`=40600 LIMIT 1;

-- Twilight Hatchlings
-- Faction fix
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=39388 LIMIT 1;

-- Difficult entry fix`ark_db`
UPDATE `creature_template` SET `difficulty_entry_1`=48832 WHERE `entry`=39388 LIMIT 1;

-- Level fix for NH & HC
UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83 WHERE `entry`=39388 LIMIT 1;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85 WHERE `entry`=48832 LIMIT 1;

-- Alexstraszas Eggs
-- Faction Fix
UPDATE `creature_template` SET `faction_A`=14, `faction_H`=14 WHERE `entry`=40486 LIMIT 1;