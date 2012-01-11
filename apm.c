/* 
 * File:   apm.c
 * Author: Heder Soares Bernardino
 * 
 * Created on January 11, 2012, 3:44 PM
 *
 * Implementation in C programming language of the
 * Adaptive Penalty Method proposed by H.J.C. Barbosa 
 * and A.C.C. Lemonge in 2003.
 * Please, read README file for more information about
 * the method.
 *
 * Compilation:
 * Use the following command to compile this code:
 * gcc -c apm.c
 * This will generate a 'apm.o' object file.
 */

/*
 * Includes.
 */
#include <stdlib.h>

/*
 * Name: calculatePenalizationCoefficients
 * Description: Calculate the penalization coefficients 
 * using the objective function and constraint violation
 * values by using APM ideas.
 * Parameters:
 * - populationSize: number of candidate solutions
 * in the population. This value defines the number
 * of elements indicated by the pointers;
 * - objectiveFunctionValues: values of the objective
 * function obtained by evaluating the candidate solutions;
 * - constraintViolationValues: values of the constraint 
 * violations obtained by evaluating the candidate violations;
 * - numberOfConstraints: the number of constraints of the
 * problem.
 * - penalizationCoefficients: penalization coefficients
 * calculated by the adaptive penalty method and which
 * are used by the penalization function.
*/

void calculatePenalizationCoefficients (
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
	double* sumViolation = (double*) malloc( numberOfConstraints * sizeof( double ) );
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
	free( sumViolation );

}


/*
 * Name: calculateFitness
 * Description: Calculate the fitness values using 
 * the objective function and constraint violation
 * values by means a penalty function. This method
 * must be used after the penalization coefficients
 * have been calculated by the
 * 'calculatePenalizationCoefficients' method.
 * Also, the penalization method assumes that the 
 * user is trying to solve a minimization problem.
 * Parameters:
 * - fitnessValues: pointer to the fitness values 
 * which will by calculated by this method;
 * - populationSize: number of candidate solutions
 * in the population. This value defines the number
 * of elements indicated by the pointers;
 * - objectiveFunctionValues: values of the objective
 * function obtained by evaluating the candidate solutions;
 * - constraintViolationValues: values of the constraint 
 * violations obtained by evaluating the candidate violations.
 * It is important to highlight that, here, a candidate 
 * solution 'x' is called infeasible if there is a restricttion 
 * function 'g(x, i)' creater than zero, for all candidade 
 * constraint 'i'.
 * - numberOfConstraints: the number of constraints of the
 * problem.
 * - penalizationCoefficients: penalization coefficients
 * calculated by the adaptive penalty method and which
 * are used by the penalization function.
 */
void calculateFitness( 
	double* fitnessValues, 
	int populationSize, 
	double* objectiveFunctionValues, 
	double** constraintViolationValues,
	int numberOfConstraints,
	double* penalizationCoefficients ) {

	//indicates if the candidate solution is infeasible
	_Bool infeasible;
	int i;
	int j;
	//the penalization value
	double penalization;
	for( i=0; i < populationSize; i++ ) {
	
		//the candidate solutions are assumed feasibles
		infeasible = 0;
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




