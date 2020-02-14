#include "core/Master.h"
#include "core/misc.h"
#include <algorithm>
#include <math.h>
#include <functional>
#include <random>


void Master::unibase2_rec(Formula subset, Formula used){
	current_depth++;
	std::vector<int> assumptions;
	for(int i = 0; i < dimension; i++){
		if(!subset[i]){
			assumptions.push_back(-1 * (i + 1));
		}
	}
	Formula seed = explorer->get_bot_unexplored(assumptions);
	int streak = 0;
	int iteration = 0;
	while(!seed.empty()){
		if(is_valid(seed, true, true)){
			streak = 0;
			vector<MSS> grown = grow_formulas(seed);
			for(auto m: grown){
				mark_MSS(m);
			}
		}else{
			if(++streak > 10){
				current_depth--;
				return;
			}
			MUS m = shrink_formula(seed);
			mark_MUS(m);
			/*
			vector<int> over;
			Formula rec_subset = subset;
			for(auto c: m.int_mus){
				if(subset[c]){
					over.push_back(c);
					rec_subset[c] = false;
				}
			}
			if(over.size() > 1){
				for(auto c: over){
					if(explorer->mus_intersection[c] || used[c]) continue;
					used[c] = true;
					rec_subset[c] = true;
					unibase2_rec(rec_subset, used);
					rec_subset[c] = false;
				}
			}*/
		}
		iteration++;
		if(iteration % 5 == 0)
			seed = explorer->get_top_unexplored(assumptions);
		else
			seed = explorer->get_bot_unexplored(assumptions);
	}
	current_depth--;
}

void Master::unibase2(){
	Formula uni = unibase_union(2);
	while(true){
		bit++;
		if(count_ones(uni) == 0)
			print_err("all MUSes identified"); //todo: compute the remaning mcses via hitting set duality
		unibase2_rec(uni, Formula(dimension, false));
		while(true){
			Formula mus = unibase_union(1);
			if(count_ones(mus) == 0)
				print_err("all MUSes identified");
			bool found = false;
			for(int i = 0; i < dimension; i++){
				if(mus[i] && !uni[i]){
					uni[i] = true;
					found = true;
				}
			}
			if(found) break;
		}
	}	
}
	
