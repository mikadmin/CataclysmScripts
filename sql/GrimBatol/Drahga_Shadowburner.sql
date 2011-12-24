-- Drahga Shadowburner (Grim Batol) Updates
-- by Naios

-- Who added SmartAI to Valiona? ^^
UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_valiona_gb' WHERE `entry`=40320 LIMIT 1;

-- Add Scriptname to the invocation of flame
UPDATE `creature_template` SET `ScriptName`='mob_invocation_of_flame' WHERE `entry`=40355 LIMIT 1;