/* 
 * File:   AdaptivePenaltyMethod.hpp
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

#ifndef ADAPTIVEPENALTYMETHOD_HPP
#define	ADAPTIVEPENALTYMETHOD_HPP

namespace apm {


class AdaptivePenaltyMethod {
	public:
		/*
		 * Constructor.
		 * Parameters:
		 * - numberOfConstraints: the number of constraints of the problem.
		 */
		AdaptivePenaltyMethod( const int numberOfConstraints );
		
		/*
		 * Constructor.
		 */
		AdaptivePenaltyMethod( const AdaptivePenaltyMethod& orig );

		/*
		 * Destructor.
		 */
		virtual ~AdaptivePenaltyMethod( );
		
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
	 * - penalizationCoefficients: penalization coefficients
	 * calculated by the adaptive penalty method and which
	 * are used by the penalization function.
	 */
	 void calculatePenalizationCoefficients (
		 int populationSize,
		 double* objectiveFunctionValues,
		 double** constraintViolationValues,
		 double* penalizationCoefficients );
		 
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
	 * solution 'x' is called infeasible if there is a restriction 
	 * function 'g(x, i)' greater than zero, for all candidate 
	 * constraint 'i'.
	 * - penalizationCoefficients: penalization coefficients
	 * calculated by the adaptive penalty method and which
	 * are used by the penalization function.
	 */
	 
	 void calculateFitness( 
		double* fitnessValues, 
		int populationSize, 
		double* objectiveFunctionValues, 
		double** constraintViolationValues,
		double* penalizationCoefficients );
	 
	 
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
	 * - objectiveFunctionValue: value of the objective
	 * function obtained by evaluating the candidate solution;
	 * - constraintViolationValues: values of the constraint 
	 * violations obtained by evaluating the candidate solution.
	 * It is important to highlight that, here, a candidate 
	 * solution 'x' is called infeasible if there is a restriction 
	 * function 'g(x, i)' greater than zero, for all candidate 
	 * constraint 'i'.
	 * - penalizationCoefficients: penalization coefficients
	 * calculated by the adaptive penalty method and which
	 * are used by the penalization function.
	 */
	 
	 double calculateFitness( 
		double objectiveFunctionValue, 
		double* constraintViolationValues,
		double* penalizationCoefficients );
	 
		
	private:
		double* sumViolation;
		int numberOfConstraints;
		double averageObjectiveFunctionValues;
		
	};




}


#endif	/* F503ADAPTIVEPENALTYMETHOD_HPP */
