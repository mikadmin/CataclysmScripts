/*##############################
## Firelands Updates by Naios ##
##############################*/
-- Contents:(Beth'tilac)

SET @BETHTHILAC_SCRIPT_TEXTS_ENTRY := 0;
SET @BETHTHILAC_GUID := 0;

-- ### Set Scriptnames ###
UPDATE `creature_template` SET `ScriptName`='boss_bethtilac' WHERE `entry`=52498 LIMIT 1;