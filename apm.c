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

	

}


/*
 * Name: calculateFitness
 * Description: Calculate the fitness values using 
 * the objective function and constraint violation
 * values by means a penalty function. This method
 * must be used after the penalization coefficients
 * have been calculated by the
 * 'calculatePenalizationCoefficients' method.
 * Parameters:
 * - fitnessValues: pointer to the fitness values 
 * which will by calculated by this method;
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
void calculateFitness( 
	double* fitnessValues, 
	int populationSize, 
	double* objectiveFunctionValues, 
	double** constraintViolationValues,
	int numberOfConstraints,
	double* penalizationCoefficients ) {

	

}




