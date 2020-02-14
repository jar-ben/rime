#include "core/Master.h"
#include "core/misc.h"
#include <algorithm>
#include <math.h>
#include <functional>
#include <random>

Formula Master::unibase_union(int limit){
	if(verbose) cout << "start of unibase union" << endl;
	Formula top = explorer->get_unexplored(1, false);
	Formula uni(dimension, false);
	int i = 0;
	while(!top.empty() && i < limit){
		if(verbose) cout << "  iter: " << i << endl;
		Formula original_top = top;
                if(is_valid(top, true, true)){
                        mark_MSS(MSS(top, -1, msses.size(), count_ones(top)));
                        guessed++;	
                }else{
                        MUS mus = shrink_formula(top);
                        mark_MUS(mus);
			i++;
                }
                top = explorer->get_unexplored(1, false);
        }
	if(verbose) cout << "end of unibase union" << endl;
	return uni;
}

void Master::unibase(){
	while(true){
		bit++;
		Formula uni = unibase_union(10);
		if(count_ones(uni) == 0)
			print_err("all MUSes identified"); //todo: compute the remaning mcses via hitting set duality
		std::vector<int> assumptions;
		for(int i = 0; i < dimension; i++){
			if(!uni[i]){
				assumptions.push_back(i + 1);
			}
		}
		Formula bot = explorer->get_bot_unexplored(assumptions);
		int streak = 0;
		while(!bot.empty()){
			if(is_valid(bot, true, true)){
				vector<MSS> grown = grow_formulas(bot);
				for(auto &m: grown){
					mark_MSS(m);
					block_up(m.bool_mss);
				}
			}else{
				block_up(bot);
			}
			if(++streak > 200) break;
			bot = explorer->get_bot_unexplored(assumptions);
		}
	}	
}
	
