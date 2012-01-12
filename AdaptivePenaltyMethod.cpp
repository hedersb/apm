/* 
 * File:   AdaptivePenaltyMethod.cpp
 * Author: Heder Soares Bernardino
 * 
 * Created on January 12, 2012, 1:22 PM
 *
 * Implementation in C++ programming language of the
 * Adaptive Penalty Method proposed by H.J.C. Barbosa 
 * and A.C.C. Lemonge in 2003.
 * Please, read README file for more information about
 * the method.
 *
 * Compilation:
 * Use the following command to compile this code:
 * g++ -c AdaptivePenaltyMethod.cpp
 * This will generate a 'AdaptivePenaltyMethod.o' object file.
 * To use the AdaptivePenaltyMethod class, it is only necessary
 * to include the "AdaptivePenaltyMethod.hpp" file, 
 * to link the AdaptivePenaltyMethod.o to the compiled code, and
 * to instantiate a object of this class.
 */

/*
 * Includes.
 */
#include "AdaptivePenaltyMethod.hpp"


namespace apm {

	/*
	 * Constructor.
	 */
	AdaptivePenaltyMethod::AdaptivePenaltyMethod( ) {
	}

	/*
	 * Contructor with a AdaptivePenaltyMethod object as parameter.
	 */
	AdaptivePenaltyMethod::AdaptivePenaltyMethod( const AdaptivePenaltyMethod& orig ) {
	}

	/*
	 * Destructor.
	 */
	AdaptivePenaltyMethod::~AdaptivePenaltyMethod( ) {
	}


	/*
	 * Method to calculate the penalization coefficients.
	 */
	void AdaptivePenaltyMethod::calculatePenalizationCoefficients (
		 int populationSize,
		 double* objectiveFunctionValues,
		 double** constraintViolationValues,
		 int numberOfConstraints, 
		double* penalizationCoefficients ) {

		int i;
		int j;
		int l;
		double sumObjectiveFunction = 0;
		//foreach candidate solution
		for( i=0; i < populationSize; i++ ) {

			sumObjectiveFunction += objectiveFunctionValues[ i ];

		}
		//the absolute of the sumObjectiveFunction
		if ( sumObjectiveFunction < 0 ) {
			sumObjectiveFunction = -sumObjectiveFunction;
		}

		//the denominator of the equation of the penalization coefficients
		double denominator = 0;
		//the sum of the constraint violation values
		//these values are recorded to be used in the next situation
		double* sumViolation = new double[ numberOfConstraints ];
		for( l=0; l < numberOfConstraints; l++ ) {

			sumViolation[ l ] = 0;
			for( i=0; i < populationSize; i++ ) {

				sumViolation[ l ] += constraintViolationValues[ i ][ l ];

			}

			denominator += sumViolation[ l ] * sumViolation[ l ];
		}

		//the penalization coefficients are calculated
		for( j=0; j < numberOfConstraints; j++ ) {

			penalizationCoefficients[ j ] = ( sumObjectiveFunction / denominator ) * sumViolation[ j ];

		}

		//remove auxiliary variables
		delete[] sumViolation;

	}


	/*
	 * Method to calculate de fitness of the candidate solutions.
	 */
	void AdaptivePenaltyMethod::calculateFitness( 
		double* fitnessValues, 
		int populationSize, 
		double* objectiveFunctionValues, 
		double** constraintViolationValues,
		int numberOfConstraints,
		double* penalizationCoefficients ) {

		//indicates if the candidate solution is infeasible
		bool infeasible;
		int i;
		int j;
		//the penalization value
		double penalization;
		for( i=0; i < populationSize; i++ ) {
	
			//the candidate solutions are assumed feasibles
			infeasible = false;
			penalization = 0;
		
			for( j=0; j < numberOfConstraints; j++ ) {
			
				//the candidate solution is infeasible if some constraint is violated
				infeasible |= constraintViolationValues[ i ][ j ] > 0 ;
				//the penalization value is updated
				penalization += penalizationCoefficients[ j ] * constraintViolationValues[ i ][ j ];

			}

			//the fitness is the sum of the objective function and penalization values 
			//if the candidate solution is infeasible and just the objective function value,
			//otherwise
			fitnessValues[ i ] = infeasible ? objectiveFunctionValues[ i ] + penalization : objectiveFunctionValues[ i ];

		}

	}

}


