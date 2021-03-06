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
 * Name: calculatePenaltyCoefficients
 * Description: Calculate the penalty coefficients 
 * using the objective function and constraint violation
 * values by using APM ideas.
 * Also, the average of the objective function values is
 * calculated to be used for the calculation of the fitness values.
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
 * - penaltyCoefficients: penalty coefficients
 * calculated by the adaptive penalty method and which
 * are used by the penalty function.
 * - averageObjectiveFunctionValues: a pointer which is used to 
 * archive the average of the objective function values.
 */

void calculatePenaltyCoefficients(
	int populationSize,
	double* objectiveFunctionValues,
	double** constraintViolationValues,
	int numberOfConstraints,
	double* penaltyCoefficients, 
	double* averageObjectiveFunctionValues) {

	int i;
	int j;
	int l;
	double sumObjectiveFunction = 0;
	//foreach candidate solution
	for (i = 0; i < populationSize; i++) {

		sumObjectiveFunction += objectiveFunctionValues[ i ];

	}
	//the absolute of the sumObjectiveFunction
	if (sumObjectiveFunction < 0) {
		sumObjectiveFunction = -sumObjectiveFunction;
	}
	
	//the average of the objective function values
	*averageObjectiveFunctionValues = sumObjectiveFunction / populationSize;

	//the denominator of the equation of the penalty coefficients
	double denominator = 0;
	//the sum of the constraint violation values
	//these values are recorded to be used in the next situation
	double* sumViolation = (double*) malloc(numberOfConstraints * sizeof ( double));
	for (l = 0; l < numberOfConstraints; l++) {

		sumViolation[ l ] = 0;
		for (i = 0; i < populationSize; i++) {

			sumViolation[ l ] += constraintViolationValues[ i ][ l ] > 0? constraintViolationValues[ i ][ l ]: 0;

		}

		denominator += sumViolation[ l ] * sumViolation[ l ];
	}

	//the penalty coefficients are calculated
	for (j = 0; j < numberOfConstraints; j++) {

		penaltyCoefficients[ j ] = denominator == 0? 0: (sumObjectiveFunction / denominator) * sumViolation[ j ];

	}

	//remove auxiliary variables
	free(sumViolation);

}


/*
 * Name: calculateAllFitness
 * Description: Calculate the fitness values using 
 * the objective function and constraint violation
 * values by means a penalty function. This method
 * must be used after the penalty coefficients
 * have been calculated by the
 * 'calculatePenaltyCoefficients' method.
 * Also, the penalty method assumes that the 
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
 * solution 'x' is called infeasible if there is a restriction 
 * function 'g(x, i)' greater than zero, for all candidate 
 * constraint 'i'.
 * - numberOfConstraints: the number of constraints of the
 * problem.
 * - penaltyCoefficients: penalty coefficients
 * calculated by the adaptive penalty method and which
 * are used by the penalty function.
 */
void calculateAllFitness(
	double* fitnessValues,
	int populationSize,
	double* objectiveFunctionValues,
	double** constraintViolationValues,
	int numberOfConstraints,
	double* penaltyCoefficients,
	double averageObjectiveFunctionValues) {

	//indicates if the candidate solution is infeasible
	_Bool infeasible;
	int i;
	int j;
	//the penalty value
	double penalty;
	for (i = 0; i < populationSize; i++) {

		//the candidate solutions are assumed feasibles
		infeasible = 0;
		penalty = 0;

		for (j = 0; j < numberOfConstraints; j++) {

			if ( constraintViolationValues[ i ][ j ] > 0 ) {
				//the candidate solution is infeasible if some constraint is violated
				infeasible = 1;
				//the penalty value is updated
				penalty += penaltyCoefficients[ j ] * constraintViolationValues[ i ][ j ];
			}

		}

		//the fitness is the sum of the objective function and penalty values 
		//if the candidate solution is infeasible and just the objective function value,
		//otherwise
		fitnessValues[ i ] = infeasible ? 
			(objectiveFunctionValues[ i ] > averageObjectiveFunctionValues? objectiveFunctionValues[ i ] + penalty: averageObjectiveFunctionValues + penalty) : 
			objectiveFunctionValues[ i ];

	}

}


/*
 * Name: calculateFitness
 * Description: This function calculates the fitness values using 
 * the objective function and constraint violation
 * values by means a penalty function. This method
 * must be used after the penalty coefficients
 * have been calculated by the
 * 'calculatePenaltyCoefficients' method.
 * Also, the penalty method assumes that the 
 * user is trying to solve a minimization problem.
 * Parameters:
 * - objectiveFunctionValue: value of the objective
 * function obtained by evaluating the candidate solution;
 * - constraintViolationValues: values of the constraint 
 * violations obtained by evaluating the candidate violation.
 * It is important to highlight that, here, a candidate 
 * solution 'x' is called infeasible if there is a restriction 
 * function 'g(x, i)' greater than zero, for all candidate 
 * constraint 'i'.
 * - numberOfConstraints: the number of constraints of the
 * problem.
 * - penaltyCoefficients: penalty coefficients
 * calculated by the adaptive penalty method and which
 * are used by the penalty function.
 */
double calculateFitness(
	double objectiveFunctionValue,
	double* constraintViolationValues,
	int numberOfConstraints,
	double* penaltyCoefficients,
	double averageObjectiveFunctionValues) {

	//indicates if the candidate solution is infeasible
	_Bool infeasible;
	int j;
	//the penalty value
	double penalty;

	//the candidate solutions are assumed feasible
	infeasible = 0;
	penalty = 0;

	for (j = 0; j < numberOfConstraints; j++) {

		if ( constraintViolationValues[ j ] > 0 ) {
			//the candidate solution is infeasible if some constraint is violated
			infeasible = 1;
			//the penalty value is updated
			penalty += penaltyCoefficients[ j ] * constraintViolationValues[ j ];
		}

	}

	//the fitness is the sum of the objective function and penalty values 
	//if the candidate solution is infeasible and just the objective function value,
	//otherwise
	return infeasible ? 
		(objectiveFunctionValue > averageObjectiveFunctionValues? objectiveFunctionValue + penalty: averageObjectiveFunctionValues + penalty) : 
		objectiveFunctionValue;

}



