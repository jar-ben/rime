#include "core/Master.h"
#include "core/misc.h"
#include <algorithm>
#include <math.h>
#include <functional>
#include <random>


void Master::rime_refine(int limit){
	if(verbose >= 3) cout << "start of unibase refine" << endl;
	Formula top = explorer->get_unexplored(1, false);
	Formula uni(dimension, false);
	int i = 0;
	while(!top.empty() && i < limit){
		if(verbose >= 3) cout << "  iter: " << i << endl;
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
	if(verbose >= 3) cout << "end of unibase refine" << endl;
}

void Master::rime(){
	Formula whole(dimension, true);
	rime_refine(1);
        if(verbose >= 3) cout << "initial uni size: " << count_ones(uni) << ", " << (count_ones(uni)/float(dimension)) << endl;
	Formula seed = explorer->get_bot_unexplored_containing(couni);	
	while(!seed.empty()){
		bit++;
		if(verbose >= 3) cout << "bit: " << bit << endl;
		if(is_valid(seed, true, true)){
			vector<int> missing = subtract_int(seed, whole);
			if(missing.size() < 5){			
				if(missing.size() > 1)
					grow_combined(seed);
				mark_MSS(MSS(seed, -1, msses.size(), count_ones(seed)));
			}else{
				MSS mss = grow_formula(seed);
				mark_MSS(mss);
			}	
		}else{
			block_up(seed);
		}
		seed = explorer->get_bot_unexplored_containing(couni);
		//the current uni is whole searched
		if(seed.empty()){
			if(verbose >= 3) cout << "blurb" << endl;
			block_up(uni);
			block_down(uni);
			rime_refine(1);
			if(verbose >= 3) cout << "refine base" << endl;
			//if(count_ones(uni2) == 0) break; //all MSSes found
			seed = explorer->get_bot_unexplored_containing(couni);
			if(verbose >= 3) cout << "have seed" << endl;
			if(seed.empty()){
				uni = Formula(dimension, true);
				couni = Formula(dimension, false);
				seed = explorer->get_bot_unexplored_containing(couni);
			}
		}	
	}	
}
	
