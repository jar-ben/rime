#include "core/Master.h"
#include "core/misc.h"
#include <algorithm>
#include <math.h>
#include <functional>
#include <random>

void Master::comarco(){
	Formula bot = explorer->get_unexplored(0, false);
	while(!bot.empty()){
		Formula original_bot = bot;
		if(!is_valid(bot, false, true)){
			block_up(bot);
		}else{
			MSS mss = grow_formula(bot);
			mark_MSS(mss);
		}
		bot = explorer->get_unexplored(0, false);
	}
}

