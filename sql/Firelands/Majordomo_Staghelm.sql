/*##############################
## Firelands Updates by Naios ##
##############################*/
-- Contents:(Majordomo Staghelm)

SET @MAJORDOMO_SCRIPT_TEXTS_ENTRY := -1999985;

-- Yells
DELETE FROM `script_texts` WHERE `npc_entry` = 52571;

INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES

(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY, 'Beg for mercy now, and I may yet allow you to live. Well, "heroes?" What is your answer?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-1, 'Behold the rage of the Firelands!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-2, 'Blaze of Glory!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-3, 'Burn.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-4, 'But none may enter the Firelord\'s abode!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-5, 'My studies... had only just begun...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-6, 'Nothing but ash!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-7, 'So much power!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-8, 'Soon ALL of Azeroth will burn!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-9, 'The master\'s power takes on many forms...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-10, 'Very well. Witness the raw power of my new Lord!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-11, 'Well, well. I admire your tenacity. Baleroc stood guard over this keep for a thousand mortal lifetimes.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell'),
(52571, @MAJORDOMO_SCRIPT_TEXTS_ENTRY-12, 'You stood in the fire!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 0, 'Firelands - Majordomo Staghelm Yell');
