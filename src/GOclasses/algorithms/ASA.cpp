/*
 *  ASA.cpp
 *  SeGMO, a Sequential Global Multiobjective Optimiser
 *
 *  Created by Dario Izzo on 5/16/08.
 *  Copyright 2008 ¿dvanced Concepts Team (European Space Agency). All rights reserved.
 *
 */

#include <cmath>
#include <iostream>

#include "../../exceptions.h"
#include "../basic/individual.h"
#include "../basic/population.h"
#include "../problems/GOproblem.h"
#include "ASA.h"
#include "go_algorithm.h"

	ASAalgorithm::ASAalgorithm(int niterTotInit, const double &Ts_, const double &Tf_):go_algorithm(),niterTot(niterTotInit),
		niterTemp(1),niterRange(20),Ts(Ts_),Tf(Tf_),StartStep(1) {
		if (niterTotInit < 0) {
			pagmo_throw(value_error,"number of generations must be nonnegative");
		}
		if (Ts_ <= 0 || Tf_ <= 0 || Ts_ <= Tf_) {
			pagmo_throw(value_error,"temperatures must be positive and Ts must be greater than Tf");
		}
	}

Population ASAalgorithm::evolve(const Population &pop) const {
	const GOProblem &problem = pop.problem();
	if (pop.size() == 0) {
		return Population(problem,0);
	}
	const std::vector<double> &LB = problem.getLB();
	const std::vector<double> &UB = problem.getUB();
	const size_t SolDim = LB.size();
	if (SolDim == 0) {
		pagmo_throw(value_error,"problem's size cannot be null");
	}
	const size_t niterOuter = niterTot / (niterTemp * niterRange * SolDim);
	if (niterOuter == 0) {
		pagmo_throw(value_error,"niterOuter cannot be null");
	}
	const double Tcoeff = std::pow(Tf/Ts,1.0/(double)(niterOuter));
	const Individual &x0 = pop[0];
	std::vector<double> xNEW = x0.getDecisionVector(), xOLD = xNEW;
	double fNEW = x0.getFitness(), fOLD = fNEW;
	if (xNEW.size() != SolDim) {
		pagmo_throw(value_error,"discrepancy between individual size and problem size.");
	}
	std::vector<double> Step(SolDim,StartStep);
	std::vector<int> acp(SolDim,0) ;
	double ratio = 0, currentT = Ts, prob = 0,  r = 0;

	//Main SA loops
	for (size_t jter = 0; jter < niterOuter; ++jter) {
		for (size_t mter = 0; mter < niterTemp; ++mter) {
			for (size_t kter = 0; kter < niterRange; ++kter) {
				size_t nter =  (size_t)(drng() * SolDim);
				for (size_t numb = 0; numb < SolDim ; ++numb) {
					nter = (nter + 1) % SolDim;
					//We modify the current point actsol by mutating its nter component within
					//a Step that we will later adapt
					r = 2.0 * drng() - 1.0; //random number in [-1,1]
					xNEW[nter] = xOLD[nter] + r * Step[nter] * ( UB[nter] - LB[nter] );

					// If new solution produced is infeasible ignore it
					if ((xNEW[nter] > UB[nter]) || (xNEW[nter] < LB[nter])) {
						xNEW[nter]=xOLD[nter];
						continue;
					}
					//And we valuate the objective function for the new point
					fNEW = problem.objfun(xNEW);

					// We decide wether to accept or discard the point
					if (fNEW < fOLD) {
						//accept
						xOLD[nter] = xNEW[nter];
						fOLD = fNEW;
						acp[nter]++;	//Increase the number of accepted values
					} else {
						//test it with Boltzmann to decide the acceptance
						prob = exp ( (fOLD - fNEW )/ currentT );

						// we compare prob with a random probability.
						if (prob > drng()) {
							xOLD[nter] = xNEW[nter];
							fOLD = fNEW;
							acp[nter]++;	//Increase the number of accepted values
						} else {
							xNEW[nter] = xOLD[nter];
						}
					} // end if
				} // end for(nter = 0; ...
			} // end for(kter = 0; ...


			// adjust the step (adaptively)
			for (size_t iter = 0; iter < SolDim; ++iter) {
				ratio = (double)acp[iter]/(double)niterRange;
				acp[iter] = 0;  //reset the counter
				if (ratio > .6) {
					//too many acceptances, increase the step by a factor 3 maximum
					Step[iter] = Step [iter] * (1 + 2 *(ratio - .6)/.4);
				} else {
					if (ratio < .4) {
						//too few acceptance, decrease the step by a factor 3 maximum
						Step [iter]= Step [iter] / (1 + 2 * ((.4 - ratio)/.4));
					};
				};
				//And if it becomes too large, reset it to its initial value
				if ( Step[iter] > StartStep ) {
						Step [iter] = StartStep;
				};
			}
		}
		// Cooling schedule
		currentT *= Tcoeff;
	}

	Population newpop(problem,0);
	if (fOLD < x0.getFitness()){
		newpop.push_back(Individual(xOLD,x0.getVelocity(),fOLD));
	} else {
		newpop.push_back(x0);
	}
	return newpop;
	}