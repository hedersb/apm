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
	 * solution 'x' is called infeasible if there is a restricttion 
	 * function 'g(x, i)' creater than zero, for all candidade 
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
		
	private:
		double* sumViolation;
		int numberOfConstraints;
		
	};




}


#endif	/* F503ADAPTIVEPENALTYMETHOD_HPP */
