/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By JeanClaude
*/

#include "ScriptPCH.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

/********
** Ivoroc
*********/
#define spell_malediction_de_guerison 80295 // Malédiction_de_guérison
#define spell_ombreflamme 80270 // Ombreflamme
 
class mob_ivoroc: public CreatureScript
{
 public:
  mob_ivoroc() : CreatureScript("mob_ivoroc") {}
 
struct mob_ivorocAI : public ScriptedAI
{
    mob_ivorocAI(Creature *c) : ScriptedAI(c) {}
           
    uint32 malediction_de_guerison;
    uint32 ombreflamme;
           
	void Reset()
	{
		malediction_de_guerison = 25000;
		ombreflamme = 37000;
	}  
 
	void UpdateAI(const uint32 diff)
	{
        if (malediction_de_guerison<= diff)
        {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM,1,100,true), spell_malediction_de_guerison);
            malediction_de_guerison = 25000;
        } else malediction_de_guerison-= diff;
                   
        if (ombreflamme<= diff)
        {
            if(Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
            DoCast(pTarget, spell_ombreflamme);
            ombreflamme = 37000;
        } else ombreflamme-= diff;
 
		DoMeleeAttackIfReady();
	}
};
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
       return new mob_ivorocAI(pCreature);
    }
 
};

/*********
** Maimgor
**********/
#define spell_etreinte_percante 80145 // Etreinte_Percante
#define spell_enrager 80084 // Enrager
#define spell_fouette_queue 80130 // Fouette_Queue
#define spell_ombreflamme 80270 // Ombreflamme
 
class mob_maimgor: public CreatureScript
{
public:
 mob_maimgor() : CreatureScript("mob_maimgor") {}
 
struct mob_maimgorAI : public ScriptedAI
{
	mob_maimgorAI(Creature *c) : ScriptedAI(c) {}
 
	uint32 etreinte_percante;
	uint32 enrager;
	uint32 fouette_queue;
	uint32 ombreflamme;
 
	void Reset()
	{
		etreinte_percante = 20000;
        enrager = 46000;
        fouette_queue = 15000;
        ombreflamme = 30000;
	}
 
	void UpdateAI(const uint32 diff)
	{
		if (etreinte_percante<= diff)
		{
			if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
			DoCast(target, spell_etreinte_percante);
			etreinte_percante = 20000;
		} else etreinte_percante-= diff;
 
		if (enrager<= diff)
		{
			DoCast(me, spell_enrager);
			enrager = 46000;
		} else enrager-= diff;
 
		if (fouette_queue<= diff)
		{
			if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -2.0f, true))
			DoCast(target, spell_fouette_queue);
			fouette_queue = 15000;
		} else fouette_queue-= diff;
 
		if (ombreflamme<= diff)
		{
			if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
			DoCast(target, spell_ombreflamme);
			ombreflamme = 30000;
		} else ombreflamme-= diff;
 
		DoMeleeAttackIfReady();
	}
};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_maimgorAI(pCreature);
	}
 
};

/*****************
** Brûle-pourpoint
******************/
#define spell_ombreflamme 80270 // Ombreflamme
#define spell_rafale_de_flammes 80127 // Rafale_De_Flammes
 
class mob_brule_pourpoint: public CreatureScript
{
public:
 mob_brule_pourpoint() : CreatureScript("mob_brule_pourpoint") {}
 
struct mob_brule_pourpointAI : public ScriptedAI
{
	mob_brule_pourpointAI(Creature *c) : ScriptedAI(c) {}
 
	uint32 ombreflamme;
	uint32 rafale_de_flammes;
 
	void Reset()
	{
		ombreflamme = 15000;
		rafale_de_flammes = 25000;
	}

	void UpdateAI(const uint32 diff)
	{
 
		if (ombreflamme<= diff)
		{
			if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, -10.0f, true))
			DoCast(target, spell_ombreflamme);
			ombreflamme = 15000;
		} else ombreflamme-= diff;
 
		if (rafale_de_flammes<= diff)
		{
			if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
			DoCast(pTarget, spell_rafale_de_flammes);
			rafale_de_flammes = 25000;
		} else rafale_de_flammes-= diff;
 
		DoMeleeAttackIfReady();
	}
};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_brule_pourpointAI(pCreature);
	}
 
};

/********************
** Golem Factionnaire
*********************/
#define spell_bombe_eclairante 81056 // Bombe_Eclairante
#define spell_decharge_electricite 81055 // Decharge_d'Electricite
#define spell_frappe_laser 81063 // Frappe_Laser
 
class mob_golem_factionnaire: public CreatureScript
{
public:
 mob_golem_factionnaire() : CreatureScript("mob_golem_factionnaire") {}
 
struct mob_golem_factionnaireAI : public ScriptedAI
{
	mob_golem_factionnaireAI(Creature *c) : ScriptedAI(c) {}
 
	uint32 bombe_eclairante;
	uint32 decharge_electricite;
	uint32 frappe_laser;
 
	void Reset()
	{
		bombe_eclairante = 40000;
		decharge_electricite = 10000;
		frappe_laser = 25000;
	}
 
	void UpdateAI(const uint32 diff)
	{
		if (bombe_eclairante<= diff)
		{
			DoCastAOE(spell_bombe_eclairante);
			bombe_eclairante = 40000;
		} else bombe_eclairante-= diff;
 
		if (decharge_electricite<= diff)
		{
			if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
			DoCast(pTarget, spell_decharge_electricite);
			decharge_electricite = 10000;
		} else decharge_electricite-= diff;
 
		if (frappe_laser<= diff)
		{
			if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
			DoCast(pTarget, spell_frappe_laser);
			frappe_laser = 25000;
		} else frappe_laser-= diff;
 
		DoMeleeAttackIfReady();
	}
};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_golem_factionnaireAI(pCreature);
	}
 
};

/***********************
** Pourfendeur Drakonide
************************/
#define spell_enchainement 80392 // Enchainement
#define spell_frappe_mortelle 80390 // Frappe_Mortelle
#define spell_vague_explosive 80391 // Vague_Explosive
 
class mob_pourfendeur_drakonide: public CreatureScript
{
public:
 mob_pourfendeur_drakonide() : CreatureScript("mob_pourfendeur_drakonide") { }
 
struct mob_pourfendeur_drakonideAI : public ScriptedAI
{
	mob_pourfendeur_drakonideAI(Creature *c) : ScriptedAI(c) {}
 
	uint32 enchainement;
	uint32 frappe_mortelle;
	uint32 vague_explosive;
 
	void Reset()
	{
		enchainement = 15000;
		frappe_mortelle = 20000;
		vague_explosive = 50000;
	}
 
	void UpdateAI(const uint32 diff)
	{
		if (enchainement<= diff)
		{
			DoCast(me->getVictim(), spell_enchainement);
			enchainement = 15000;
		} else enchainement -= diff;
 
		if (frappe_mortelle<= diff)
		{
			DoCast(me->getVictim(), spell_frappe_mortelle);
			frappe_mortelle = 20000;
		} else frappe_mortelle -= diff;
 
		if (vague_explosive<= diff)
		{
			DoCastAOE(spell_vague_explosive);
			vague_explosive = 50000;
		} else vague_explosive -= diff;
 
		DoMeleeAttackIfReady();
	}
};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_pourfendeur_drakonideAI(pCreature);
	}
 
};

/*****************
** Batard Drakodon
******************/
#define spell_acide_corrosif 80345 // Acide_Corrosif
#define spell_charge 79904 // Charge
#define spell_brulure_de_givre RAND(80336,80338)
#define spell_pouvoir_despece RAND(80371,80372,80370,80368,80369)
#define spell_trou_de_temps RAND(80329,80330)
#define spell_la_chair RAND(80341,80332)
 
class mob_batard_drakodon: public CreatureScript
{
public:
 mob_batard_drakodon() : CreatureScript("mob_batard_drakodon") {}
 
struct mob_batard_drakodonAI : public ScriptedAI
{
	mob_batard_drakodonAI(Creature *c) : ScriptedAI(c) {}
 
	uint32 acide_corrosif;
	uint32 brulure_de_givre;
	uint32 la_chair;
	uint32 charge;
	uint32 pouvoir_despece;
	uint32 trou_de_temps;
 
	void reset()
	{
		acide_corrosif = 20000;
		brulure_de_givre = 45000;
		charge = 11000;
		la_chair = 50000;
		pouvoir_despece = 30000;
		trou_de_temps = 35000;
	}
 
	void UpdateAI(const uint32 diff)
	{
		if (acide_corrosif <= diff)
		{
			DoCast(me->getVictim(), spell_acide_corrosif);
			acide_corrosif = 20000;
		} else acide_corrosif -= diff;
 
		if (brulure_de_givre <= diff)
		{
			DoCastAOE(spell_brulure_de_givre);
			brulure_de_givre = 45000;
		} else brulure_de_givre -= diff;
 
		if (charge <= diff)
		{
			if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
			DoCast(pTarget, spell_charge);
			charge = 11000;
		} else charge -= diff;
 
		if (la_chair <= diff)
		{
			DoCast(me, spell_la_chair);
			la_chair = 50000;
		} else la_chair -= diff;
 
		if (pouvoir_despece <= diff)
		{
			DoCast(me, spell_pouvoir_despece);
			pouvoir_despece = 30000;
		} else pouvoir_despece -= diff;
 
		if (trou_de_temps <= diff)
		{
			DoCast(me, spell_trou_de_temps);
			trou_de_temps = 35000;
		} else trou_de_temps -= diff;
 
		DoMeleeAttackIfReady();
	}
};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_batard_drakodonAI(pCreature);
	}
};

void AddSC_mob_trash_bwd()
{
    new mob_ivoroc();
	new mob_maimgor();
	new mob_brule_pourpoint();
	new mob_golem_factionnaire();
	new mob_pourfendeur_drakonide();
	new mob_batard_drakodon();
}