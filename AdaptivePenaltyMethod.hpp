/* 
 * File:   AdaptivePenaltyMethod.hpp
 * Author: Heder Soares Bernardino
 *
 * Created on January 12, 2012, 1:22 PM
 */

#ifndef ADAPTIVEPENALTYMETHOD_HPP
#define	ADAPTIVEPENALTYMETHOD_HPP

namespace apm {


class AdaptivePenaltyMethod {
	public:
		AdaptivePenaltyMethod(  );
		AdaptivePenaltyMethod( const AdaptivePenaltyMethod& orig );
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
		double* penalizationCoefficients );
		
	private:
		
		
	};




}


#endif	/* F503ADAPTIVEPENALTYMETHOD_HPP */
