#include <ctime>
#include <time.h>
#include "Master.h"
#include <getopt.h>
#include <algorithm>
#include <csignal>
#include "tclap/CmdLine.h"
#include "tclap/ValuesConstraint.h"

void signal_handler(int signal){
	if(signal == 15){
		cout << "the computation was interupted due to a timeout" << endl;
	}
	exit(1);
}

int main(int argc, char *argv[]){

	std::signal(SIGTERM, signal_handler);

	try{
		TCLAP::CmdLine cmd("domain agnostic MUS enumeration Tool (MUST), Jaroslav Bendik, 2019.", ' ', "");
		vector<string> allowedAlgs {"rime"};
		TCLAP::ValuesConstraint<string> allowedVals(allowedAlgs);
		TCLAP::ValueArg<string> algorithm("a","algorithm","MUS enumeration algorithm to be used.",false,"rime",&allowedVals);
		cmd.add(algorithm);

		vector<string> allowedSolvers {"minisat", "glucose", "cadical", "default"};
		TCLAP::ValuesConstraint<string> allowedSolversVals(allowedSolvers);
		TCLAP::ValueArg<string> satsolver("","sat-solver","SAT-solver to be used.",false,"default",&allowedSolversVals);
		cmd.add(satsolver);

		TCLAP::ValueArg<std::string> output("o","output-file","A file where the identified MUSes will be exported to.",false,"","string");
		cmd.add(output);

		TCLAP::ValueArg<std::string> mcslsArgs("","mcsls-args","",false,"","string");
		cmd.add(mcslsArgs);

		TCLAP::SwitchArg conflictsNegation("","conflicts-negation","Negate known conflicting clauses during satsolver.solve() calls.", cmd, false);
		TCLAP::SwitchArg mssRotation("","mss-rotation","Use the flag to disable the MSS rotation technique.", cmd, true);
		TCLAP::SwitchArg verbose("v","verbose","Verbose output", cmd, false);
		vector<string> allowedShrinks {"default", "muser"};
		TCLAP::ValuesConstraint<string> allowedValsShrink(allowedShrinks);
		TCLAP::ValueArg<std::string> shrink("s","shrink","Specifies the shrinking algorithm (single MUS extraction subroutine). You can opt between default (implemented via mcsmus) and muser.",false,"default",&allowedValsShrink);
		cmd.add(shrink);
		TCLAP::SwitchArg shrinkMining("","shrink-mining","Allows mcsmus to mine critical clauses from Explorer.", cmd, false);


		vector<string> allowedGrows {"linear", "cmp", "uwr", "combined", "mcsls", "fixpoint"};
		TCLAP::ValuesConstraint<string> allowedValsGrow(allowedGrows);
		TCLAP::ValueArg<std::string> grow("","grow","Specifies the growing algorithm (single MSS/MCS extraction subroutine). Currently, you can opt between between basic linear search, our two novel extractors called fixpoint and combined, and two external tools: uwr and mcsls.",false,"fixpoint",&allowedValsGrow);
		cmd.add(grow);

		TCLAP::ValueArg<int> cmpStrategy("","cmp-strategy","CMP grow strategy.",false,1,"1,2,3 or 4");
		cmd.add(cmpStrategy);
		TCLAP::SwitchArg verify("c","verify-muses","Used for testing purposes. Verify that the outputted MSSes are indeed MSSes.", cmd, false);
		TCLAP::UnlabeledValueArg<string>  input( "input_file", "Input file with the .cnf extension and in the DIMACS format. See the ./examples/.", true, "", "input_file"  );
		cmd.add(input);
		cmd.parse(argc, argv);

		//clear the output file
		if(output.getValue() != ""){
			std::ofstream ofs;
			ofs.open(output.getValue(), std::ofstream::out | std::ofstream::trunc);
			ofs.close();
		}

		Master solver(input.getValue(), algorithm.getValue(), satsolver.getValue());
		solver.output_file = output.getValue();
		solver.verbose = verbose.getValue();
		solver.validate_mus_c = verify.getValue();		
		solver.conflicts_negation = conflictsNegation.getValue();
		std::string shr = shrink.getValue();
		solver.satSolver->shrink_alg = shr;
		solver.satSolver->grow_alg = grow.getValue();
		solver.get_implies = true;
		solver.criticals_rotation = false;
		solver.satSolver->growStrategy = cmpStrategy.getValue();
		solver.satSolver->mcslsArgs = mcslsArgs.getValue();
		solver.mss_rotation = mssRotation.getValue();
		solver.satSolver->shrinkMining = shrinkMining.getValue();

		solver.enumerate();		
		cout << "Enumeration completed" << endl;
		cout << "Number of MSSes: " << solver.muses.size() << endl;

	}catch (TCLAP::ArgException &e){
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}
	return 0;
}

