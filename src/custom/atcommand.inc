// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}
/*==========================================
* @afk
*------------------------------------------*/
ACMD_FUNC(afk) {
 
	nullpo_retr(-1, sd);

	if (pc_isdead(sd)) {
		clif_displaymessage(fd, "You cannot enter afk mode when dead.");
		return -1;
	}

	sd->state.autotrade = 1;
	clif_authfail_fd(fd, 15);
	return 0;
}

/*==========================================
* @battlestats / @enemystats
*------------------------------------------*/
void atcommand_battlestats_sub(int fd, class map_session_data *sd) {
	status_data *status = status_get_status_data(*sd);
	char output[CHAT_SIZE_MAX];
	bool found_bonuses;

#define battlestats_msg(__msg__) (__msg__); clif_displaymessage(fd, output)

	battlestats_msg(sprintf(output, "Battle Status: %s", sd->status.name));

	clif_displaymessage(fd, "|--- Status Information ---|");
	battlestats_msg(sprintf(output, "   -> Physical Damage (ATK): %d + %d", pc_leftside_atk(sd), pc_rightside_atk(sd)));
	battlestats_msg(sprintf(output, "   -> Magical Damage (MATK): %d + %d", pc_leftside_matk(sd), pc_rightside_matk(sd)));
	battlestats_msg(sprintf(output, "   -> Hit Rate (HIT): %d", status->hit));
	battlestats_msg(sprintf(output, "   -> Critical Rate (CRIT): %d", status->cri / 10));
	battlestats_msg(sprintf(output, "   -> Physical Defense (DEF): %d + %d", pc_leftside_def(sd), pc_rightside_def(sd)));
	battlestats_msg(sprintf(output, "   -> Magical Defense (MDEF): %d + %d", pc_leftside_mdef(sd), pc_rightside_mdef(sd)));
	battlestats_msg(sprintf(output, "   -> Flee Rate (FLEE): %d + %d", status->flee, status->flee2 / 10));
	battlestats_msg(sprintf(output, "   -> Attack Speed (ASPD): %d", (2000 - status->amotion) / 10));

	clif_displaymessage(fd, "|--- Trait Status Information ---|");
	battlestats_msg(sprintf(output, "   -> Final Physical Damage (P.ATK): %d", status->patk));
	battlestats_msg(sprintf(output, "   -> Final PhysicalMagical Damage (S.MATK): %d", status->smatk));
	battlestats_msg(sprintf(output, "   -> Heal Plus (H.Plus): %d", status->hplus));
	battlestats_msg(sprintf(output, "   -> Critical Damage Rate (C.Rate): %d", status->crate));
	battlestats_msg(sprintf(output, "   -> Physical Resistance (RES): %d", status->res));
	battlestats_msg(sprintf(output, "   -> Magical Resistance (MRES): %d", status->mres));

	clif_displaymessage(fd, "|--- Bonus Physical Damage ---|");
	found_bonuses = false;
	
	if (sd->right_weapon.addsize[SZ_MEDIUM] + sd->left_weapon.addsize[SZ_MEDIUM]) {
		battlestats_msg(sprintf(output, "   -> Medium Size: %d%%", sd->right_weapon.addsize[SZ_MEDIUM] + sd->left_weapon.addsize[SZ_MEDIUM]));
		found_bonuses = true;
	}
	if (sd->right_weapon.addsize[SZ_ALL] + sd->left_weapon.addsize[SZ_ALL]) {
		battlestats_msg(sprintf(output, "   -> All Sizes: %d%%", sd->right_weapon.addsize[SZ_ALL] + sd->left_weapon.addsize[SZ_ALL]));
		found_bonuses = true;
	}
	if (sd->right_weapon.addrace[RC_PLAYER_HUMAN || RC_PLAYER_DORAM] + sd->left_weapon.addrace[RC_PLAYER_HUMAN || RC_PLAYER_DORAM]) {
		battlestats_msg(sprintf(output, "   -> Player: %d%%", sd->right_weapon.addrace[RC_PLAYER_HUMAN || RC_PLAYER_DORAM] + sd->left_weapon.addrace[RC_PLAYER_HUMAN || RC_PLAYER_DORAM]));
		found_bonuses = true;
	}
	if (sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]) {
		battlestats_msg(sprintf(output, "   -> All Races: %d%%", sd->right_weapon.addrace[RC_ALL] + sd->left_weapon.addrace[RC_ALL]));
		found_bonuses = true;
	}
	if (sd->right_weapon.addclass[CLASS_NORMAL] + sd->left_weapon.addclass[CLASS_NORMAL]) {
		battlestats_msg(sprintf(output, "   -> Normal Class: %d%%", sd->right_weapon.addclass[CLASS_NORMAL] + sd->left_weapon.addclass[CLASS_NORMAL]));
		found_bonuses = true;
	}
	if (sd->right_weapon.addclass[CLASS_ALL] + sd->left_weapon.addclass[CLASS_ALL]) {
		battlestats_msg(sprintf(output, "   -> All Classes: %d%%", sd->right_weapon.addclass[CLASS_ALL] + sd->left_weapon.addclass[CLASS_ALL]));
		found_bonuses = true;
	}
    if (!found_bonuses) {  
        clif_displaymessage(fd, "   -> No bonus physical damage found");  
    }

	clif_displaymessage(fd, "|--- Bonus Magic Damage ---|");
	found_bonuses = false;
	
	if (sd->indexed_bonus.magic_addsize[SZ_MEDIUM]) {
		battlestats_msg(sprintf(output, "   -> Medium Size: %d%%", sd->indexed_bonus.magic_addsize[SZ_MEDIUM]));
		found_bonuses = true;
	}
	if (sd->indexed_bonus.magic_addsize[SZ_ALL]) {
		battlestats_msg(sprintf(output, "   -> All Sizes: %d%%", sd->indexed_bonus.magic_addsize[SZ_ALL]));
		found_bonuses = true;
	}
	if (sd->indexed_bonus.magic_addrace[RC_PLAYER_HUMAN || RC_PLAYER_DORAM]) {
		battlestats_msg(sprintf(output, "   -> Player: %d%%", sd->indexed_bonus.magic_addrace[RC_PLAYER_HUMAN || RC_PLAYER_DORAM]));
		found_bonuses = true;
	}
	if (sd->indexed_bonus.magic_addrace[RC_ALL]) {
		battlestats_msg(sprintf(output, "   -> All Races: %d%%", sd->indexed_bonus.magic_addrace[RC_ALL]));
		found_bonuses = true;
	}
	if (sd->indexed_bonus.magic_addclass[CLASS_NORMAL]) {
		battlestats_msg(sprintf(output, "   -> Normal Class: %d%%", sd->indexed_bonus.magic_addclass[CLASS_NORMAL]));
		found_bonuses = true;
	}
	if (sd->indexed_bonus.magic_addclass[CLASS_ALL]) {
		battlestats_msg(sprintf(output, "   -> All Classes: %d%%", sd->indexed_bonus.magic_addclass[CLASS_ALL]));
		found_bonuses = true;
	}
    if (!found_bonuses) {  
        clif_displaymessage(fd, "   -> No bonus magical damage found");  
    }  

	clif_displaymessage(fd, "|--- Elemental Resistance ---|");
	found_bonuses = false;
	
	struct {
		const char *format;
		int value;
	} ele_resist_info[] = {
		{ "   -> Neutral: %d%%", sd->indexed_bonus.subele_script[ELE_NEUTRAL] },
		{ "   -> Water: %d%%", sd->indexed_bonus.subele_script[ELE_WATER] },
		{ "   -> Earth: %d%%", sd->indexed_bonus.subele_script[ELE_EARTH] },
		{ "   -> Fire: %d%%", sd->indexed_bonus.subele_script[ELE_FIRE] },
		{ "   -> Wind: %d%%", sd->indexed_bonus.subele_script[ELE_WIND] },
		{ "   -> Poison: %d%%", sd->indexed_bonus.subele_script[ELE_POISON] },
		{ "   -> Holy: %d%%", sd->indexed_bonus.subele_script[ELE_HOLY] },
		{ "   -> Dark: %d%%", sd->indexed_bonus.subele_script[ELE_DARK] },
		{ "   -> Ghost: %d%%", sd->indexed_bonus.subele_script[ELE_GHOST] },
		{ "   -> Undead: %d%%", sd->indexed_bonus.subele_script[ELE_UNDEAD] },
		{ "   -> ALL: %d%%", sd->indexed_bonus.subele_script[ELE_ALL] },
	};
	for (int i = 0; i < ARRAYLENGTH(ele_resist_info); i++) {
		if (ele_resist_info[i].value == 0)
			continue;
		battlestats_msg(sprintf(output, ele_resist_info[i].format, ele_resist_info[i].value));
		found_bonuses = true;
	}
    if (!found_bonuses) {  
        clif_displaymessage(fd, "   -> No bonus element resistance found");  
    }	

	clif_displaymessage(fd, "|--- Race Resistance ---|");
	found_bonuses = false;
	
	struct {
		const char *format;
		int value;
	} race_resist_info[] = {
		{ "   -> Formless: %d%%", sd->indexed_bonus.subrace[RC_FORMLESS] },
		{ "   -> Undead: %d%%", sd->indexed_bonus.subrace[RC_UNDEAD] },
		{ "   -> Beast: %d%%", sd->indexed_bonus.subrace[RC_BRUTE] },
		{ "   -> Plant: %d%%", sd->indexed_bonus.subrace[RC_PLANT] },
		{ "   -> Insect: %d%%", sd->indexed_bonus.subrace[RC_INSECT] },
		{ "   -> Fish: %d%%", sd->indexed_bonus.subrace[RC_FISH] },
		{ "   -> Demon: %d%%", sd->indexed_bonus.subrace[RC_DEMON] },
		{ "   -> DemiHuman: %d%%", sd->indexed_bonus.subrace[RC_DEMIHUMAN] },
		{ "   -> Angel: %d%%", sd->indexed_bonus.subrace[RC_ANGEL] },
		{ "   -> Dragon: %d%%", sd->indexed_bonus.subrace[RC_DRAGON] },
		{ "   -> Player: %d%%", sd->indexed_bonus.subrace[RC_PLAYER_HUMAN || RC_PLAYER_DORAM] },
		{ "   -> ALL: %d%%", sd->indexed_bonus.subrace[RC_ALL] },
		{ "   -> Normal Class: %d%%", sd->indexed_bonus.subclass[CLASS_NORMAL] },
	};
	for (int i = 0; i < ARRAYLENGTH(race_resist_info); i++) {
		if (race_resist_info[i].value == 0)
			continue;
		battlestats_msg(sprintf(output, race_resist_info[i].format, race_resist_info[i].value));
		found_bonuses = true;
	}
    if (!found_bonuses) {  
        clif_displaymessage(fd, "   -> No bonus race resist found");  
    }

    clif_displaymessage(fd, "|--- Skill Damage Bonuses ---|");  
    found_bonuses = false;  
      
    // General skill ratio bonus  
    if (sd->bonus.skill_ratio != 0) {  
        battlestats_msg(sprintf(output, "   -> All Skills: %d%%", sd->bonus.skill_ratio));  
        found_bonuses = true;  
    }  
      
    // Check skillatk vector for skill-specific bonuses  
    for (const auto &bonus : sd->skillatk) {  
        const char* skill_desc = skill_get_desc(bonus.id);  
        if (skill_desc) {  
            battlestats_msg(sprintf(output, "   -> %s: +%d%%", skill_desc, bonus.val));  
            found_bonuses = true;  
        }  
    }  
      
    if (!found_bonuses) {  
        clif_displaymessage(fd, "   -> No skill damage bonuses found");  
    }

#undef battlestats_msg
}

ACMD_FUNC(battlestats) {
	nullpo_retr(-1, sd);
	atcommand_battlestats_sub(fd, sd);
	return 0;
}

ACMD_FUNC(enemystats) {
	class map_session_data *pl_sd;

	nullpo_retr(-1, sd);

	memset(atcmd_player_name, '\0', sizeof atcmd_player_name);

	if (!message || !*message || sscanf(message, "%23[^\n]", atcmd_player_name) < 1) {
		clif_displaymessage(fd, "Please enter a player name (usage: @enemystats <char name>)");
		return -1;
	}

	pl_sd = map_nick2sd(atcmd_player_name, true);
	if (pl_sd == NULL ||
		strncmp(pl_sd->status.name, atcmd_player_name, NAME_LENGTH) != 0 ||
		(pc_has_permission(pl_sd, PC_PERM_HIDE_SESSION) && pc_get_group_level(pl_sd) > pc_get_group_level(sd))
		) {
		clif_displaymessage(fd, msg_txt(sd, 3)); // Character not found.
		return -1;
	}

	atcommand_battlestats_sub(fd, pl_sd);
	return 0;
}

/*==========================================
* @reloaddepositdb
*------------------------------------------*/
ACMD_FUNC(reloaddepositdb){
	nullpo_retr(-1, sd);

	do_reload_deposit();
	clif_displaymessage(fd, "Deposit database has been reloaded.");

	return 0;
}

/*==========================================
* @whosell - Open the searchstore UI with found sold items
*------------------------------------------*/
ACMD_FUNC(whosell)
{
	char item_name[100];
	int item_id = 0, j, sat_num = 0;
	int count = 1, i;
	int s_type = 1; // search bitmask: 0-name,1-id, 2-card, 4-refine, 8-options
	int refine = 0,card_id = 0, option_id = 0, option_value = 0;
	bool flag = 0; // place dot on the minimap?
	class map_session_data* pl_sd;
	struct s_mapiterator* iter;
	unsigned int MinPrice = battle_config.vending_max_value, MaxPrice = 0;
	time_t querytime;
	std::map<t_itemid, std::shared_ptr<item_data>> item_array = {};
	bool search_item_name = false;

	nullpo_retr(-1, sd);

	if (!message || !*message) {
		clif_displaymessage(fd, "Use: @whosell (<+refine> )(<item_id>)(<[card_id]>)((<option_id> <option_value>)) or @whosell <name>");
		return -1;
	}

	time(&querytime);

	if( sd->searchstore.nextquerytime > querytime ) {
		clif_search_store_info_failed(*sd, SSI_FAILED_LIMIT_SEARCH_TIME); // SSI_FAILED_LIMIT_SEARCH_TIME
		return -1;
	}

	sd->searchstore.uses--;
	sd->searchstore.type = SEARCHTYPE_VENDING; // vending
	sd->searchstore.nextquerytime = querytime+battle_config.searchstore_querydelay;

	searchstore_clear(*sd); // clear previous result

	if( !sd->searchstore.open )
		searchstore_open(*sd, 1, SEARCHSTORE_EFFECT_REMOTE, sd->m);

	if (sscanf(message, "+%d %d[%d](%d %d)", &refine, &item_id, &card_id, &option_id, &option_value) == 5){
		s_type = 1+2+4+8;
	} else if (sscanf(message, "+%d %d(%d %d)", &refine, &item_id, &option_id, &option_value) == 4){
		s_type = 1+4+8;
	} else if (sscanf(message, "+%d [%d](%d %d)", &refine, &card_id, &option_id, &option_value) == 4){
		s_type = 2+4+8;
	} else if (sscanf(message, "%d[%d](%d %d)", &item_id, &card_id, &option_id, &option_value) == 4){
		s_type = 1+2+8;
	} else if (sscanf(message, "+%d %d[%d]", &refine, &item_id, &card_id) == 3){
		s_type = 1+2+4;
	} else if (sscanf(message, "[%d](%d %d)", &card_id, &option_id, &option_value) == 3){
		s_type = 2+8;
	} else if (sscanf(message, "+%d (%d %d)", &refine, &option_id, &option_value) == 3){
		s_type = 4+8;
	} else if (sscanf(message, "%d(%d %d)", &item_id, &option_id, &option_value) == 3){
		s_type = 1+8;
	} else if (sscanf(message, "+%d %d", &refine, &item_id) == 2){
		s_type = 1+4;
	} else if (sscanf(message, "+%d [%d]", &refine, &card_id) == 2){
		s_type = 2+4;
	} else if (sscanf(message, "%d[%d]", &item_id, &card_id) == 2){
		s_type = 1+2;
	} else if (sscanf(message, "(%d %d)", &option_id, &option_value) == 2){
		s_type = 8;
	} else if (sscanf(message, "[%d]", &card_id) == 1){
		s_type = 2;
	} else if (sscanf(message, "+%d", &refine) == 1){
		s_type = 4;
	} else if (sscanf(message, "%d", &item_id) == 1 && item_id == atoi(message)){
		s_type = 1;
	} else if (sscanf(message, "%99[^\n]", item_name) == 1){
		s_type = 1;
		count = itemdb_searchname_array(item_array, MAX_SEARCH, item_name);

		if( !count ){
			clif_displaymessage(fd, "No item found with this name");
			return -1;
		}

		search_item_name = true;
	} else {
		clif_displaymessage(fd, "Use: @whosell (<+refine> )(<item_id>)(<[card_id]>)((<option_id> <option_value>)) or @whosell <name>");
		return -1;
	}
   
	for(i = 0; i < count; i++){
		std::shared_ptr<item_data> item_data_ptr = item_db.find(item_id);

		if(search_item_name){
			auto it = std::next(item_array.begin(), i);
			std::shared_ptr<item_data> item_data_ptr = it->second;
			item_id = item_data_ptr->nameid;
		}

		//check card
		if (s_type & 2) {
			std::shared_ptr<item_data> card_data = item_db.find(card_id);
			if (card_data == nullptr || card_data->type != IT_CARD) {
				clif_displaymessage(fd, "Not found a card with that ID");
				return -1;
			}
		}
		//check item
		if (s_type & 1 && !search_item_name) {
			std::shared_ptr<item_data> item_data_ptr = item_db.find(item_id);
			if (item_data_ptr == nullptr) {
				clif_displaymessage(fd, "Not found an item with that ID");
				return -1;
			}
		}
		//check refine
		if(s_type & 4){
			if (refine < 0 || refine > MAX_REFINE) {  
				sprintf(atcmd_output, "Refine out of bounds: 0 - %d", MAX_REFINE);  
				clif_displaymessage(fd, atcmd_output);  
				return -1;  
			}
		}
		iter = mapit_getallusers();

		for( pl_sd = (TBL_PC*)mapit_first(iter); mapit_exists(iter); pl_sd = (TBL_PC*)mapit_next(iter) )
		{
			if( pl_sd->state.vending ) //check if player is vending
			{
				for (j = 0; j < pl_sd->vend_num; j++) 
				{
					std::shared_ptr<item_data> current_item = nullptr;

					if (!search_item_name) {
						current_item = item_db.find(pl_sd->buyingstore.items[j].nameid);
						if (current_item == nullptr)
							continue;
					}
					if(s_type & 1 && pl_sd->cart.u.items_cart[pl_sd->vending[j].index].nameid != item_id)
						continue;
					if (s_type & 2 && ((current_item->type != IT_ARMOR && current_item->type != IT_WEAPON) ||
						(pl_sd->cart.u.items_cart[pl_sd->vending[j].index].card[0] != card_id &&
							pl_sd->cart.u.items_cart[pl_sd->vending[j].index].card[1] != card_id &&
							pl_sd->cart.u.items_cart[pl_sd->vending[j].index].card[2] != card_id &&
							pl_sd->cart.u.items_cart[pl_sd->vending[j].index].card[3] != card_id)))
						continue;
					if (s_type & 4 && ((current_item->type != IT_ARMOR && current_item->type != IT_WEAPON) ||
						pl_sd->cart.u.items_cart[pl_sd->vending[j].index].refine != refine))
						continue;
					if (s_type & 8 && ((current_item->type != IT_ARMOR && current_item->type != IT_WEAPON) ||
						((pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[0].id != option_id && pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[0].value != option_value)
							&& (pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[1].id != option_id && pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[1].value != option_value)
							&& (pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[2].id != option_id && pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[2].value != option_value)
							&& (pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[3].id != option_id && pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[3].value != option_value)
							&& (pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[4].id != option_id && pl_sd->cart.u.items_cart[pl_sd->vending[j].index].option[4].value != option_value))))
						continue;

					// Check if the result set is full
					if( sd->searchstore.items.size() >= (unsigned int)battle_config.searchstore_maxresults ){
						return false;
					}

					std::shared_ptr<s_search_store_info_item> ssitem = std::make_shared<s_search_store_info_item>();

					ssitem->store_id = pl_sd->vender_id;
					ssitem->account_id = pl_sd->status.account_id;
					safestrncpy( ssitem->store_name, pl_sd->message, sizeof( ssitem->store_name ) );
					ssitem->nameid = pl_sd->cart.u.items_cart[pl_sd->vending[j].index].nameid;
					ssitem->amount = pl_sd->vending[j].amount;
					ssitem->price = pl_sd->vending[j].value;
					for( int k = 0; k < MAX_SLOTS; k++ )
						ssitem->card[k] = pl_sd->cart.u.items_cart[pl_sd->vending[j].index].card[k];
					ssitem->refine = pl_sd->cart.u.items_cart[pl_sd->vending[j].index].refine;
					ssitem->enchantgrade = pl_sd->cart.u.items_cart[pl_sd->vending[j].index].enchantgrade;

					sd->searchstore.items.push_back( ssitem );

					flag = 1;
				}

				if (flag && pl_sd->mapindex == sd->mapindex) {
					clif_viewpoint(*sd, 1, 1, pl_sd->x, pl_sd->y, ++sat_num, 0xFFFFFF);
					flag = 0;
				}
			}
		}
		
		mapit_free(iter);
	}

	if(!sd->searchstore.items.empty() ) {
		if (count == MAX_SEARCH) {
			sprintf(atcmd_output, msg_txt(sd,269), MAX_SEARCH); // Displaying first %d matches
			clif_displaymessage(fd, atcmd_output);
		}

	   //sort by price
		sort(sd->searchstore.items.begin(), sd->searchstore.items.end(), [](std::shared_ptr<s_search_store_info_item> ss1, std::shared_ptr<s_search_store_info_item> ss2) {
			return (ss1->price < ss2->price);
		});

		// present results
		clif_search_store_info_ack(*sd);

		// one page displayed
		sd->searchstore.pages++;
	}  else {
		// cleanup
		searchstore_clear(*sd);

		// update uses
		clif_search_store_info_ack(*sd);

		// notify of failure
		clif_search_store_info_failed(*sd, SSI_FAILED_NOTHING_SEARCH_ITEM); // SSI_FAILED_NOTHING_SEARCH_ITEM
	}

	return 0;
}


/*==========================================
* @whobuy - Open the searchstore UI with found buying items
*------------------------------------------*/
ACMD_FUNC(whobuy)
{
	char item_name[100];
	int item_id = 0, j, sat_num = 0;
	int count = 1, i;
	int s_type = 1; // search bitmask: 0-name,1-id, 2-card, 4-refine  
	int refine = 0, card_id = 0;
	bool flag = 0; // place dot on the minimap?  
	class map_session_data* pl_sd;
	struct s_mapiterator* iter;
	unsigned int MinPrice = battle_config.vending_max_value, MaxPrice = 0;
	time_t querytime;
	std::map<t_itemid, std::shared_ptr<item_data>> item_array = {};
	bool search_item_name = false;

	nullpo_retr(-1, sd);

	if (!message || !*message) {
		clif_displaymessage(fd, "Use: @whobuy (<+refine> )(<item_id>) or @whobuy <name>");
		return -1;
	}

	time(&querytime);

	if( sd->searchstore.nextquerytime > querytime ) {
		clif_search_store_info_failed(*sd, SSI_FAILED_LIMIT_SEARCH_TIME); // SSI_FAILED_LIMIT_SEARCH_TIME
		return -1;
	}

	sd->searchstore.uses--;
	sd->searchstore.type = SEARCHTYPE_BUYING_STORE; // buying store
	sd->searchstore.nextquerytime = querytime+battle_config.searchstore_querydelay;

	searchstore_clear(*sd); // clear previous result

	if( !sd->searchstore.open )
		searchstore_open(*sd, 1, SEARCHSTORE_EFFECT_REMOTE, sd->m);

	if (sscanf(message, "+%d %d", &refine, &item_id) == 2){
		s_type = 1+2;
	} else if (sscanf(message, "+%d", &refine) == 1){
		s_type = 2;
	} else if (sscanf(message, "%d", &item_id) == 1 && item_id == atoi(message)){
		s_type = 1;
	} else if (sscanf(message, "%99[^\n]", item_name) == 1){
		s_type = 1;
		count = itemdb_searchname_array(item_array, MAX_SEARCH, item_name);

		if( !count ){
			clif_displaymessage(fd, "No item found with this name");
			return -1;
		}

		search_item_name = true;
	} else {
		clif_displaymessage(fd, "Use: @whobuy (<+refine> )(<item_id>) or @whobuy <name>");
		return -1;
	}
    
	std::shared_ptr<item_data> item_data_ptr = item_db.find(item_id);

	//check item
	if (s_type & 1 && !search_item_name) {
		std::shared_ptr<item_data> item_data_ptr = item_db.find(item_id);
		if (item_data_ptr == nullptr) {
			clif_displaymessage(fd, "Not found an item with that ID");
			return -1;
		}
	}
	//check refine
	if(s_type & 2){
		if (refine<0 || refine>10){
			clif_displaymessage(fd, "Refine out of bounds: 0 - 10");
			return -1;
		}
	}
	iter = mapit_getallusers();

	for(i = 0; i < count; i++){
		if(search_item_name){
			auto it = std::next(item_array.begin(), i);
			std::shared_ptr<item_data> item_data_ptr = it->second;
			item_id = item_data_ptr->nameid;
		}

		for( pl_sd = (TBL_PC*)mapit_first(iter); mapit_exists(iter); pl_sd = (TBL_PC*)mapit_next(iter) )
		{
			if( pl_sd->state.buyingstore ) //check if player is buying
			{
				for (j = 0; j < pl_sd->buyingstore.slots; j++) 
				{
					if (!search_item_name) {
						std::shared_ptr<item_data> current_item = item_db.find(pl_sd->buyingstore.items[j].nameid);
						if (current_item == nullptr)
							continue;

						// Now use current_item for type checks  
						if (s_type & 2 && ((current_item->type != IT_ARMOR && current_item->type != IT_WEAPON) ||
							pl_sd->cart.u.items_cart[pl_sd->vending[j].index].refine != refine))
							continue;
					}

					if (s_type & 1 && pl_sd->buyingstore.items[j].nameid != item_id)
						continue;

					// Check if the result set is full
					if( sd->searchstore.items.size() >= (unsigned int)battle_config.searchstore_maxresults ){
						return false;
					}

					std::shared_ptr<s_search_store_info_item> ssitem = std::make_shared<s_search_store_info_item>();

					ssitem->store_id = pl_sd->buyer_id;
					ssitem->account_id = pl_sd->status.account_id;
					safestrncpy( ssitem->store_name, pl_sd->message, sizeof( ssitem->store_name ) );
					ssitem->nameid = pl_sd->buyingstore.items[j].nameid;
					ssitem->amount = pl_sd->buyingstore.items[j].amount;
					ssitem->price = pl_sd->buyingstore.items[j].price;
					for( int k = 0; k < MAX_SLOTS; k++ )
						ssitem->card[k] = 0;
					ssitem->refine = 0;
					ssitem->enchantgrade = 0;

					sd->searchstore.items.push_back( ssitem );

					flag = 1;
				}

				if (flag && pl_sd->mapindex == sd->mapindex) {
					clif_viewpoint(*sd, 1, 1, pl_sd->x, pl_sd->y, ++sat_num, 0xFFFFFF);
					flag = 0;
				}
			}
		}
	}
	mapit_free(iter);

	if(!sd->searchstore.items.empty() ) {
		if (count == MAX_SEARCH) {
			sprintf(atcmd_output, msg_txt(sd,269), MAX_SEARCH); // Displaying first %d matches
			clif_displaymessage(fd, atcmd_output);
		}

	   //sort by price
		sort(sd->searchstore.items.begin(), sd->searchstore.items.end(), [](std::shared_ptr<s_search_store_info_item> ss1, std::shared_ptr<s_search_store_info_item> ss2) {
			return (ss1->price > ss2->price);
		});

		// present results
		clif_search_store_info_ack(*sd);

		// one page displayed
		sd->searchstore.pages++;
	}  else {
		// cleanup
		searchstore_clear(*sd);

		// update uses
		clif_search_store_info_ack(*sd);

		// notify of failure
		clif_search_store_info_failed(*sd, SSI_FAILED_NOTHING_SEARCH_ITEM); // SSI_FAILED_NOTHING_SEARCH_ITEM
	}

	return 0;
}

/**
 * Reloads rune database
 **/
ACMD_FUNC(reloadrunedb)
{
	nullpo_retr(-1, sd);

	rune_db_reload();
	clif_displaymessage(fd, "Rune system has been reloaded");

	return 0;
}
