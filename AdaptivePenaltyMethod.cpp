/* 
 * File:   AdaptivePenaltyMethod.cpp
 * Author: Heder Soares Bernardino
 * 
 * Created on January 12, 2012, 1:22 PM
 *
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
	AdaptivePenaltyMethod::AdaptivePenaltyMethod( const int numberOfConstraints ): 
		numberOfConstraints( numberOfConstraints ),
		sumViolation( new double[ numberOfConstraints ] ),
		averageObjectiveFunctionValues(0) {
	}

	/*
	 * Contructor with a AdaptivePenaltyMethod object as parameter.
	 */
	AdaptivePenaltyMethod::AdaptivePenaltyMethod( const AdaptivePenaltyMethod& orig ): 
		numberOfConstraints( orig.numberOfConstraints ),
		sumViolation( new double[ orig.numberOfConstraints ] ),
		averageObjectiveFunctionValues( orig.averageObjectiveFunctionValues ) {
	}

	/*
	 * Destructor.
	 */
	AdaptivePenaltyMethod::~AdaptivePenaltyMethod( ) {
			//remove variables
			delete[] this->sumViolation;
	}


	/*
	 * Method to calculate the penalization coefficients.
	 */
	void AdaptivePenaltyMethod::calculatePenalizationCoefficients (
		int populationSize,
		double* objectiveFunctionValues,
		double** constraintViolationValues,
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
		
		//average of the objective function values
		this->averageObjectiveFunctionValues = sumObjectiveFunction / populationSize;

		//the denominator of the equation of the penalization coefficients
		double denominator = 0;
		
		for( l=0; l < this->numberOfConstraints; l++ ) {

			this->sumViolation[ l ] = 0;
			for( i=0; i < populationSize; i++ ) {

				this->sumViolation[ l ] += constraintViolationValues[ i ][ l ];

			}

			denominator += this->sumViolation[ l ] * this->sumViolation[ l ];
		}

		//the penalization coefficients are calculated
		for( j=0; j < this->numberOfConstraints; j++ ) {

			penalizationCoefficients[ j ] = ( sumObjectiveFunction / denominator ) * this->sumViolation[ j ];

		}

	}


	/*
	 * Method to calculate de fitness of the candidate solutions.
	 */
	void AdaptivePenaltyMethod::calculateFitness( 
		double* fitnessValues, 
		int populationSize, 
		double* objectiveFunctionValues, 
		double** constraintViolationValues,
		double* penalizationCoefficients ) {

		//indicates if the candidate solution is infeasible
		bool infeasible;
		int i;
		int j;
		//the penalization value
		double penalization;
		for( i=0; i < populationSize; i++ ) {
	
			//the candidate solutions are assumed feasible
			infeasible = false;
			penalization = 0;
		
			for( j=0; j < this->numberOfConstraints; j++ ) {
			
				//the candidate solution is infeasible if some constraint is violated
				infeasible |= constraintViolationValues[ i ][ j ] > 0 ;
				//the penalization value is updated
				penalization += penalizationCoefficients[ j ] * constraintViolationValues[ i ][ j ];

			}

			//the fitness is the sum of the objective function and penalization values 
			//if the candidate solution is infeasible and just the objective function value,
			//otherwise
			fitnessValues[ i ] = infeasible ? 
				( objectiveFunctionValues[ i ] > this->averageObjectiveFunctionValues? objectiveFunctionValues[ i ] + penalization: this->averageObjectiveFunctionValues + penalization ) : 
				objectiveFunctionValues[ i ];

		}

	}
	
	
	/*
	 * Method to calculate de fitness of a candidate solution.
	 */
	double AdaptivePenaltyMethod::calculateFitness( 
		double objectiveFunctionValue, 
		double* constraintViolationValues,
		double* penalizationCoefficients ) {
		
		//indicates if the candidate solution is infeasible
		bool infeasible;
		int j;
		//the penalization value
		double penalization;
	
		//the candidate solutions are assumed feasible
		infeasible = false;
		penalization = 0;

		for( j=0; j < this->numberOfConstraints; j++ ) {

			//the candidate solution is infeasible if some constraint is violated
			infeasible |= constraintViolationValues[ j ] > 0 ;
			//the penalization value is updated
			penalization += penalizationCoefficients[ j ] * constraintViolationValues[ j ];

		}

		//the fitness is the sum of the objective function and penalization values 
		//if the candidate solution is infeasible and just the objective function value,
		//otherwise
		return infeasible ? 
				( objectiveFunctionValue > this->averageObjectiveFunctionValues? objectiveFunctionValue + penalization: this->averageObjectiveFunctionValues + penalization ) : 
				objectiveFunctionValue;
		
	}

}


