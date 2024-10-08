import os
import sys
import time

# need to append the simpleaipack into sys.path so python interpreter will detect it.
sys.path.append(r'C:\Users\EVGENYT\Desktop\FTS_REF')

from cop import COP
from simpleaipack.search.local import beam_best_first, hill_climbing_stochastic, simulated_annealing, greedy\
                                     , random_walk, random_search

"""
interface for python local search algorithms within SimpleAi package.
"""

if __name__ == '__main__':
    max_iterations = 2000000
    path = r'../copsimpleai/CPP_Problems/'
    alg_name = sys.argv[1]
    problem_seed = sys.argv[2]
    run_time = sys.argv[3]
    algo_seed = sys.argv[4]

    result = None
    problem = None
    initial_solution = None

    if sys.argv[1] in ['GREEDY', 'GREEDY+SHC', 'GREEDY+LBS', 'GREEDY+SA', 'GREEDY+RS', 'GREEDY+RW', 'GREEDY+LOOP']:
        if sys.argv[1] != 'GREEDY':
            alg_name = 'InitialGreedy' + alg_name

        print("Greedy Search")
        print("-----------------")

        problem = COP(problemSeed=int(problem_seed),
                      numOfVarChangesInNeighborhood=1,
                      path=path,
                      algoName=alg_name,
                      algoSeed=algo_seed,
                      initialSolution=initial_solution,
                      loadProblemFromFile=True)

        start = time.time()
        result = greedy(problem, iterations_limit=max_iterations, max_run_time=float(run_time), seed=int(algo_seed))
        greedy_run_time = time.time() - start
        print("greedy time elapse: ", greedy_run_time)
        if sys.argv[1] != 'GREEDY':
            initial_solution = result
            run_time = float(run_time)
            run_time -= greedy_run_time

    alg_name = sys.argv[1]  # restore original alg name

    if float(run_time) > 0.0:
        if sys.argv[1] == 'GREEDY+LOOP':

            print("GreedyLoop Search")
            print("-----------------")

            problem = COP(problemSeed=int(problem_seed),
                          numOfVarChangesInNeighborhood=1,
                          path=path,
                          algoName=alg_name,
                          algoSeed=algo_seed,
                          initialSolution=initial_solution,
                          loadProblemFromFile=True)
            result = greedy(problem, iterations_limit=max_iterations, max_run_time=float(run_time), seed=int(algo_seed))

        if sys.argv[1] in ["RS", 'GREEDY+RS']:
            print("Random Search")
            print("------------------------")

            problem = COP(problemSeed=int(problem_seed),
                          numOfVarChangesInNeighborhood=1,
                          path=path,
                          algoName=alg_name,
                          algoSeed=algo_seed,
                          initialSolution=initial_solution,
                          loadProblemFromFile=True)
            result = random_search(problem, iterations_limit=max_iterations, max_run_time=float(run_time), seed=int(algo_seed))

        if sys.argv[1] in ["RW", 'GREEDY+RW']:
            neighborhood = 0
            args_list = sys.argv
            for idx, arg in enumerate(args_list):
                if arg == '-neighborhood':
                    neighborhood = args_list[idx + 1]
            if neighborhood == 0:
                print("-neighborhood is missing!")

            print("Random Walk")
            print("------------------------")

            problem = COP(problemSeed=int(problem_seed),
                          numOfVarChangesInNeighborhood=int(neighborhood),
                          path=path,
                          algoName=alg_name,
                          algoSeed=algo_seed,
                          initialSolution=initial_solution,
                          loadProblemFromFile=True)
            result = random_walk(problem, iterations_limit=max_iterations, max_run_time=float(run_time), seed=int(algo_seed))

        if sys.argv[1] in ["SHC", 'GREEDY+SHC']:
            neighborhood = 0
            args_list = sys.argv
            for idx, arg in enumerate(args_list):
                if arg == '-neighborhood':
                    neighborhood = args_list[idx + 1]
            if neighborhood == 0:
                print("-neighborhood is missing!")

            print("Stochastic Hill Climbing")
            print("------------------------")

            problem = COP(problemSeed=int(problem_seed),
                          numOfVarChangesInNeighborhood=int(neighborhood),
                          path=path,
                          algoName=alg_name,
                          algoSeed=algo_seed,
                          initialSolution=initial_solution,
                          loadProblemFromFile=True)
            result = hill_climbing_stochastic(problem, iterations_limit=max_iterations, max_run_time=float(run_time), seed=int(algo_seed))

        if sys.argv[1] in ["SA", 'GREEDY+SA']:
            neighborhood = 0
            initTemp = None
            tempStep = None
            args_list = sys.argv
            for idx, arg in enumerate(args_list):
                if arg == '-neighborhood':
                    neighborhood = args_list[idx + 1]
                if arg == '-inittemp':
                    initTemp = args_list[idx + 1]
                if arg == '-tempstep':
                    tempStep = args_list[idx + 1]

            if neighborhood == 0:
                print("-neighborhood is missing!")
            if initTemp is None:
                print("-initTemp is missing!")
            if tempStep is None:
                print("-tempStep is missing!")

            print("Simulated Annealing")
            print("-------------------")

            problem = COP(problemSeed=int(problem_seed),
                          numOfVarChangesInNeighborhood=int(neighborhood),
                          path=path,
                          algoName=alg_name,
                          algoSeed=algo_seed,
                          initialSolution=initial_solution,
                          loadProblemFromFile=True)
            result = simulated_annealing(problem, iterations_limit=max_iterations, max_run_time=float(run_time),
                                         seed=int(algo_seed), initTemp=float(initTemp), tempStep=float(tempStep))
        if sys.argv[1] in ["LBS", 'GREEDY+LBS']:
            neighborhood = 0
            args_list = sys.argv
            for idx, arg in enumerate(args_list):
                if arg == '-neighborhood':
                    neighborhood = args_list[idx + 1]

            if neighborhood == 0:
                print("-neighborhood is missing!")

            print("Local Beam Search")
            print("-----------------")

            problem = COP(problemSeed=int(problem_seed),
                          numOfVarChangesInNeighborhood=int(neighborhood),
                          path=path,
                          algoName=alg_name,
                          algoSeed=algo_seed,
                          initialSolution=initial_solution,
                          loadProblemFromFile=True)
            result = beam_best_first(problem, iterations_limit=max_iterations, max_run_time=float(run_time), seed=int(algo_seed))

    if sys.argv[1] not in ["GREEDY", "GREEDY+LOOP", "RS", "GREEDY+RS"] and float(run_time) > 0.0:
        print(f"Results for ParamILS: SAT, -1, {problem_seed}, {result.value}, {algo_seed}")
    else:
        print(f"Results for ParamILS: SAT, -1, {problem_seed}, {problem.value(result)}, {algo_seed}")

