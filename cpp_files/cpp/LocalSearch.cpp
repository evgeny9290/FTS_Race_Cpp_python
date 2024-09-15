#include "LocalSearch.h"
//#include "C:\JasonSerializationCppGit\ThorsSerializer\ThorSerialize\Traits.h"
#include <exception>

static const unsigned int MAX_ITERATIONS = 5000000; // was 2 mil

typedef enum EAlgorithm
{
	ALGORITHM_RANDOM_SEARCH = 0,
	ALGORITHM_RANDOM_WALK = 1,
	ALGORITHM_STOCHASTIC_HILL_CLIMBING = 2,
	ALGORITHM_GREEDY = 3,
	ALGORITHM_TABU_SEARCH = 4,
	ALGORITHM_SIMULATED_ANNEALING = 5,
	ALGORITHM_CROSS_ENTROPY = 6,
	ALGORITHM_GREEDY_THEN_RANDOM_SEARCH = 7,
	ALGORITHM_GREEDY_THEN_RANDOM_WALK = 8,
	ALGORITHM_GREEDY_THEN_STOCHASTIC_HILL_CLIMBING = 9,
	ALGORITHM_GREEDY_THEN_TABU_SEARCH = 10,
	ALGORITHM_GREEDY_THEN_SIMULATED_ANNEALING = 11,
	ALGORITHM_GREEDY_THEN_CROSS_ENTROPY = 12,
	ALGORITHM_GREEDY_LOOP = 13,
	ALGORITHM_GREAT_DELUGE = 14,
	ALGORITHM_FLOAT_LUUS_JAAKOLA = 15,
	ALGORITHM_STOCHASTIC_LOCAL_BEAM_SEARCH = 16,
	ALGORITHM_GREEDY_THEN_GREAT_DELUGE = 17,
	ALGORITHM_GREEDY_THEN_STOCHASTIC_LOCAL_BEAM_SEARCH = 18
} EAlgorithm;

EAlgorithm AlgorithmStringToEnum(char* pcAlgoString)
{
	string sAlgorithm = pcAlgoString;
	EAlgorithm eAlgorithm;

	if (sAlgorithm.find("GREEDY+RS") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_RANDOM_SEARCH;
	else if (sAlgorithm.find("GREEDY+GREAT_DELUGE") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_GREAT_DELUGE;
	else if (sAlgorithm.find("GREEDY+SLBS") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_STOCHASTIC_LOCAL_BEAM_SEARCH;
	else if (sAlgorithm.find("GREEDY+RW") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_RANDOM_WALK;
	else if (sAlgorithm.find("GREEDY+SHC") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_STOCHASTIC_HILL_CLIMBING;
	else if (sAlgorithm.find("GREEDY+TS") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_TABU_SEARCH;
	else if (sAlgorithm.find("GREEDY+SA") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_SIMULATED_ANNEALING;
	else if (sAlgorithm.find("GREEDY+CE") != string::npos) eAlgorithm = ALGORITHM_GREEDY_THEN_CROSS_ENTROPY;
	else if (sAlgorithm.find("GREEDYLOOP") != string::npos) eAlgorithm = ALGORITHM_GREEDY_LOOP;
	else if (sAlgorithm.find("RS") != string::npos) eAlgorithm = ALGORITHM_RANDOM_SEARCH;
	else if (sAlgorithm.find("RW") != string::npos) eAlgorithm = ALGORITHM_RANDOM_WALK;
	else if (sAlgorithm.find("SHC") != string::npos) eAlgorithm = ALGORITHM_STOCHASTIC_HILL_CLIMBING;
	else if (sAlgorithm.find("GREEDY") != string::npos) eAlgorithm = ALGORITHM_GREEDY;
	else if (sAlgorithm.find("TS") != string::npos) eAlgorithm = ALGORITHM_TABU_SEARCH;
	else if (sAlgorithm.find("SA") != string::npos) eAlgorithm = ALGORITHM_SIMULATED_ANNEALING;
	else if (sAlgorithm.find("CE") != string::npos) eAlgorithm = ALGORITHM_CROSS_ENTROPY;
	else if (sAlgorithm.find("GREAT_DELUGE") != string::npos) eAlgorithm = ALGORITHM_GREAT_DELUGE;
	else if (sAlgorithm.find("LJ") != string::npos) eAlgorithm = ALGORITHM_FLOAT_LUUS_JAAKOLA;
	else if (sAlgorithm.find("SLBS") != string::npos) eAlgorithm = ALGORITHM_STOCHASTIC_LOCAL_BEAM_SEARCH;


	/*if		(sAlgorithm == "GREEDY+RS") eAlgorithm = ALGORITHM_GREEDY_THEN_RANDOM_SEARCH;
	else if (sAlgorithm == "GREEDY+RW") eAlgorithm = ALGORITHM_GREEDY_THEN_RANDOM_WALK;
	else if (sAlgorithm == "GREEDY+SHC") eAlgorithm = ALGORITHM_GREEDY_THEN_STOCHASTIC_HILL_CLIMBING;
	else if (sAlgorithm == "GREEDY+TS") eAlgorithm = ALGORITHM_GREEDY_THEN_TABU_SEARCH;
	else if (sAlgorithm == "GREEDY+SA") eAlgorithm = ALGORITHM_GREEDY_THEN_SIMULATED_ANNEALING;
	else if (sAlgorithm == "GREEDY+CE") eAlgorithm = ALGORITHM_GREEDY_THEN_CROSS_ENTROPY;
	else if (sAlgorithm == "GREEDYLOOP") eAlgorithm = ALGORITHM_GREEDY_LOOP; 
	else if (sAlgorithm == "RS") eAlgorithm = ALGORITHM_RANDOM_SEARCH;
	else if (sAlgorithm == "RW") eAlgorithm = ALGORITHM_RANDOM_WALK;
	else if (sAlgorithm == "SHC") eAlgorithm = ALGORITHM_STOCHASTIC_HILL_CLIMBING;
	else if (sAlgorithm == "GREEDY") eAlgorithm = ALGORITHM_GREEDY;
	else if (sAlgorithm == "TS") eAlgorithm = ALGORITHM_TABU_SEARCH;
	else if (sAlgorithm == "SA") eAlgorithm = ALGORITHM_SIMULATED_ANNEALING;
	else if (sAlgorithm == "CE") eAlgorithm = ALGORITHM_CROSS_ENTROPY;*/

	return eAlgorithm;
}

const unsigned int FIRST_ALGO_PARAM_IDX = 2;

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
	
	for (int i = 0; i < argc; i++) {
		std::cout << "argv[" << i << "]:\t" << argv[i] << std::endl;
	}
	
	EAlgorithm eAlgorithm = AlgorithmStringToEnum(argv[1]);
	string sAlgName = argv[1]; // algorithm name
	string sInstanceName = argv[2]; // used for generating the random COP problem
	//string sInstanceSpecificInfo = argv[3]; // never used?
	double dCutoffTime = atof(argv[3]); // maximum runtime of an algorithm? 4
	//int iCutoffLength = atoi(argv[5]); // never used?
	unsigned long ulSeed = atoi(argv[4]); // used for generating stochastic algorithm behaviour 6


	#pragma region COP Input
		unsigned int uiProblemSeed = atoi(argv[2]); // used for generating the random COP problem
		COP GCop(uiProblemSeed);

		COP::SolutionVector InitialSolution;
		COP::SolutionVector RandomInitialSolution;
		//COP::SolutionVector RES_SHC = { 27,64,27,77,13,58,43,52,36,67,46,14,17,77,2,65,31,77,54,56,15,57,45,72,37,1,25,3,46,18,17,13,6,64,54,66,17,46,43,53,45,39,74,67,61,23,11,8,51,38,0,21,41,56,73,13,10,57,43,65,68,9,13,34,20,70,54,43,26,42,30,31,43,21,59,68,50,1173938961,0,0,0,0,0,0,0,0,
		//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		std::mt19937 ReproducibleRandomEngine;
		std::uniform_int_distribution<uint32_t> UIntDistForVars(1, COP::MAX_NUM_OF_VARS);
		//Fill Initial Solution Data
		for (unsigned int i = 0; i < COP::MAX_NUM_OF_VARS; i++) {
			InitialSolution.aulSolutionVector[i] = 0;
			RandomInitialSolution.aulSolutionVector[i] = UIntDistForVars(ReproducibleRandomEngine);
		}
	#pragma endregion
	
	#pragma region Algorithms Calls
	
		double dRunTime = dCutoffTime; //[Sec]

		COP::GradesVector GV = {0};
		COP::SolutionVector GVS = { 0 };
		float RES = 10;

		string strProblemDetails = "_Problem_" + to_string(uiProblemSeed) + "_RunSeed_" + to_string(ulSeed);

		string sCurrentParam;

		if (eAlgorithm == ALGORITHM_GREEDY ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_RANDOM_SEARCH ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_RANDOM_WALK ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_STOCHASTIC_HILL_CLIMBING ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_TABU_SEARCH ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_SIMULATED_ANNEALING ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_CROSS_ENTROPY || 
			eAlgorithm == ALGORITHM_GREEDY_LOOP ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_GREAT_DELUGE ||
			eAlgorithm == ALGORITHM_GREEDY_THEN_STOCHASTIC_LOCAL_BEAM_SEARCH)
			{
				//Mark Greedy results when another algotihms runs after it
				if (eAlgorithm != ALGORITHM_GREEDY && eAlgorithm != ALGORITHM_GREEDY_LOOP)
					sAlgName = "InitialGreedy"+sAlgName;

				bool bLoopy = (eAlgorithm == ALGORITHM_GREEDY_LOOP);
				cout << "Greedy Search" << endl;
				cout << "-------------" << endl;
				CCOPGreedySearch COPGreedy(sAlgName+strProblemDetails);
				double dGreedyRunTime;
				dGreedyRunTime = COPGreedy.Solve(InitialSolution,
													GCop,
													dRunTime,
													MAX_ITERATIONS,
													ulSeed,
													bLoopy
													);
				cout << endl;
				COPGreedy.GetBestValue(GV);	

				if (eAlgorithm != ALGORITHM_GREEDY && eAlgorithm != ALGORITHM_GREEDY_LOOP)
				{
					COP::SolutionVector GreedySolution;
					COPGreedy.GetBestSolution(GreedySolution);
					InitialSolution = GreedySolution;
					dRunTime -= dGreedyRunTime;
				}
			}

		//Restore original algorithm name
		sAlgName = argv[1];

		if (eAlgorithm == ALGORITHM_RANDOM_SEARCH || 
			eAlgorithm == ALGORITHM_GREEDY_THEN_RANDOM_SEARCH)
			{
				cout << "Random Search" << endl;
				cout << "-------------" << endl;
				CCOPRandomSearch COPRS(sAlgName+strProblemDetails);
				COPRS.Solve(InitialSolution,
							GCop,
							dRunTime,
							MAX_ITERATIONS,
							ulSeed
							);
				cout << endl;
				COPRS.GetBestValue(GV);
			}

			if (eAlgorithm == ALGORITHM_RANDOM_WALK || 
				eAlgorithm == ALGORITHM_GREEDY_THEN_RANDOM_WALK)
			{
				unsigned int uiNeighborhoodSize = 0;
				for (int i=FIRST_ALGO_PARAM_IDX; i<argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam=="-neighborhood") uiNeighborhoodSize = atoi(argv[i+1]);
				}

				if (uiNeighborhoodSize == 0) 
				{
					cout << "-neighborhood is missing!" << endl;
					return 1; 
				}

				cout << "Random Walk" << endl;
				cout << "------------" << endl;
				CCOPRandomWalk COPRW(sAlgName+strProblemDetails);
				COPRW.Solve(InitialSolution,
							GCop,
							dRunTime,
							MAX_ITERATIONS,
							uiNeighborhoodSize,
							ulSeed
							);
				cout << endl;
				COPRW.GetBestValue(GV);
			}

			if (eAlgorithm == ALGORITHM_STOCHASTIC_HILL_CLIMBING || 
				eAlgorithm == ALGORITHM_GREEDY_THEN_STOCHASTIC_HILL_CLIMBING)
			{
				unsigned int uiNeighborhoodSize = 0;
				for (int i=FIRST_ALGO_PARAM_IDX; i<argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam=="-neighborhood") uiNeighborhoodSize = atoi(argv[i+1]);
				}

				if (uiNeighborhoodSize == 0) 
				{
					cout << "-neighborhood is missing!" << endl;
					return 1;
				}

				cout << "Stochastic Hill Climbing" << endl;
				cout << "------------------------" << endl;
				CCOPStochasticHillClimbing COPSHC(sAlgName+strProblemDetails);
				COPSHC.Solve(InitialSolution,
							GCop,
							dRunTime,
							MAX_ITERATIONS,
							uiNeighborhoodSize,
							ulSeed
							);
				cout << endl;
				COPSHC.GetBestValue(GV);
			}

			if (eAlgorithm == ALGORITHM_TABU_SEARCH || 
				eAlgorithm == ALGORITHM_GREEDY_THEN_TABU_SEARCH)
			{
				unsigned int uiNeighborhoodSize = 0;
				unsigned int uiTabuSize = 0;
				for (int i=FIRST_ALGO_PARAM_IDX; i<argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam=="-neighborhood") uiNeighborhoodSize = atoi(argv[i+1]);
					if (sCurrentParam=="-tabusize") uiTabuSize = atoi(argv[i+1]);
				}

				if (uiNeighborhoodSize == 0) cout << "-neighborhood is missing!" << endl;
				if (uiTabuSize == 0) cout << "-tabusize is missing!" << endl;
				if ((uiNeighborhoodSize == 0) || (uiTabuSize == 0)) return 1;

				cout << "Tabu Search" << endl;
				cout << "-----------" << endl;
				CCOPTabuSearch COPTS(sAlgName+strProblemDetails);
				COPTS.Solve(InitialSolution,
							GCop,
							uiNeighborhoodSize,
							dRunTime,
							MAX_ITERATIONS,
							uiTabuSize,
							ulSeed
							);
				cout << endl;
				COPTS.GetBestValue(GV);
			}

			if (eAlgorithm == ALGORITHM_SIMULATED_ANNEALING || 
				eAlgorithm == ALGORITHM_GREEDY_THEN_SIMULATED_ANNEALING)
			{
				unsigned int uiNeighborhoodSize = 0;
				double dInitTemp = 0.0;
				double dTempStep = 0.0;

				for (int i=FIRST_ALGO_PARAM_IDX; i<argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam=="-neighborhood") uiNeighborhoodSize = atoi(argv[i+1]);
					if (sCurrentParam=="-inittemp") dInitTemp = atof(argv[i+1]);
					if (sCurrentParam=="-tempstep") dTempStep = atof(argv[i+1]);
				}

				if (uiNeighborhoodSize == 0) cout << "-neighborhood is missing!" << endl;
				if (dInitTemp < DBL_EPSILON) cout << "-inittemp is missing!" << endl;
				if (dTempStep < DBL_EPSILON) cout << "-tempstep is missing!" << endl;
				if ((uiNeighborhoodSize == 0) || (dInitTemp < DBL_EPSILON) || (dTempStep < DBL_EPSILON)) return 1;

				cout << "Simulated Annealing" << endl;
				cout << "-------------------" << endl;
				CCOPSimulatedAnnealingSearch COPSA(sAlgName+strProblemDetails);
				COPSA.Solve(InitialSolution,
							GCop,
							dRunTime,
							MAX_ITERATIONS,
							(float)dInitTemp,
							(float)dTempStep,
							uiNeighborhoodSize,
							ulSeed);
				cout << endl;
				COPSA.GetBestValue(GV);
			}

			if (eAlgorithm == ALGORITHM_GREAT_DELUGE ||
				eAlgorithm == ALGORITHM_GREEDY_THEN_GREAT_DELUGE)
			{
				unsigned int uiNeighborhoodSize = 0;
				//float fDeltaBeta = 0.0; // maybe for costum DeltaBeta

				for (int i = FIRST_ALGO_PARAM_IDX; i < argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam == "-neighborhood") uiNeighborhoodSize = atoi(argv[i + 1]);
					//if (sCurrentParam == "-InitDeltaBeta") fLevel = (float)atof(argv[i + 1]);
				}

				if (uiNeighborhoodSize == 0) cout << "-neighborhood is missing!" << endl;
				if (uiNeighborhoodSize == 0) return 1;

				cout << "Great Deluge" << endl;
				cout << "-------------------" << endl;
				CCOPGreatDelugeSearch COPGD(sAlgName + strProblemDetails);
				COPGD.Solve(InitialSolution,
					GCop,
					dRunTime,
					MAX_ITERATIONS,
					uiNeighborhoodSize,
					RandomInitialSolution, // as for now this is the optimalSolution from SHC algorithm for the seed 331991908
					ulSeed); // should add InitDeltaBeta as additional param if wanted
				cout << endl;
				COPGD.GetBestValue(GV);
			}

			if (eAlgorithm == ALGORITHM_FLOAT_LUUS_JAAKOLA)
			{
				float uiNeighborhoodSize = 0;

				for (int i = FIRST_ALGO_PARAM_IDX; i < argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam == "-neighborhood") uiNeighborhoodSize = stof(argv[i + 1]);
				}

				if (uiNeighborhoodSize == 0) cout << "-neighborhood is missing!" << endl;
				if (uiNeighborhoodSize == 0) return 1;

				cout << "Float Luus Jaakola" << endl;
				cout << "-------------------" << endl;
				Float_Luus_Jaakola COPLJ(sAlgName + strProblemDetails);
				COPLJ.Solve(RES,
							dRunTime,
							MAX_ITERATIONS,
							uiNeighborhoodSize,
							ulSeed);
				cout << endl;
				COPLJ.GetBestValue(RES);
			}
			//LJ 124 asdas 1.0 10 331991908 -neighborhood 5.0

			if (eAlgorithm == ALGORITHM_STOCHASTIC_LOCAL_BEAM_SEARCH ||
				eAlgorithm == ALGORITHM_GREEDY_THEN_STOCHASTIC_LOCAL_BEAM_SEARCH)
			{
				unsigned int uiNeighborhoodSize = 0;
				unsigned int uiEliteSize = 0;

				for (int i = FIRST_ALGO_PARAM_IDX; i < argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam == "-neighborhood") uiNeighborhoodSize = atoi(argv[i + 1]);
					if (sCurrentParam == "-numelites") uiEliteSize = stoi(argv[i + 1]);
				}

				if (uiNeighborhoodSize == 0) cout << "-neighborhood is missing!" << endl;
				if (uiNeighborhoodSize == 0) return 1;
				if (uiEliteSize == 0) cout << "-numelites is missing!" << endl;
				if (uiEliteSize == 0) return 1;

				cout << "Stochastic Local Beam Search" << endl;
				cout << "-------------------" << endl;

				CCOPStochasticLocalBeamSearch COPSLBM(sAlgName + strProblemDetails, uiEliteSize);
				COPSLBM.Solve(InitialSolution,
							  GCop,
							  dRunTime,
							  MAX_ITERATIONS,
							  uiNeighborhoodSize,
							  ulSeed);
				cout << endl;
				COPSLBM.GetBestValue(GV);
			}

			if (eAlgorithm == ALGORITHM_CROSS_ENTROPY || 
				eAlgorithm == ALGORITHM_GREEDY_THEN_CROSS_ENTROPY)
			{
				unsigned int uiSamples = 0;
				double dInitSolWeight = -1;
				double dAlpha = -1;
				double dRho = 0.0;
				double dEpsilon = 0.0;

				for (int i=FIRST_ALGO_PARAM_IDX; i<argc; i++)
				{
					sCurrentParam = argv[i];
					if (sCurrentParam=="-samples") uiSamples = atoi(argv[i+1]);
					if (sCurrentParam=="-initsolweight") dInitSolWeight = atof(argv[i+1]);
					if (sCurrentParam=="-alpha") dAlpha = atof(argv[i+1]);
					if (sCurrentParam=="-rho") dRho = atof(argv[i+1]);
					if (sCurrentParam=="-epsilon") dEpsilon = atof(argv[i+1]);
				}

				if (uiSamples == 0) cout << "-samples is missing!" << endl;
				if (dInitSolWeight < -DBL_EPSILON) cout << "-initsolweight is missing!" << endl;
				if (dAlpha < -DBL_EPSILON) cout << "-alpha is missing!" << endl;
				if (dRho < DBL_EPSILON) cout << "-rho is missing!" << endl;
				if (dEpsilon < DBL_EPSILON) cout << "-epsilon is missing!" << endl;
				if ((uiSamples == 0) || (dInitSolWeight < -DBL_EPSILON) || (dAlpha < -DBL_EPSILON) || (dRho < DBL_EPSILON) || (dEpsilon < DBL_EPSILON)) return 1;

				cout << "Cross Entropy Method" << endl;
				cout << "-------------------" << endl;
				CCOPCrossEntropy COPCE(sAlgName+strProblemDetails);
				COPCE.Solve(InitialSolution,
							GCop,
							dRunTime,
							MAX_ITERATIONS,
							uiSamples,
							(float)dInitSolWeight,
							(float)dAlpha,
							(float)dRho,
							(float)dEpsilon,
							ulSeed);
				cout << endl;
				COPCE.GetBestValue(GV);
			}

		cout << "Result for ParamILS: " << "SAT" << ", " << -1 <<  ", " << uiProblemSeed <<  ", " <<  setprecision(15) <<GV.Scalarization() <<  ", " << ulSeed << endl;

	#pragma endregion

	//getchar();

 return 0;
} //of main()

