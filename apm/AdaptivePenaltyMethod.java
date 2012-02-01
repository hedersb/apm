/* 
 * File:   AdaptivePenaltyMethod.java
 * Author: Heder Soares Bernardino
 *
 * Created on January 12, 2012,17:48 PM
 * 
 *
 * Implementation in Java programming language of the
 * Adaptive Penalty Method proposed by H.J.C. Barbosa 
 * and A.C.C. Lemonge in 2003.
 * Please, read README file for more information about
 * the method.
 *
 * Compilation:
 * Use the following command to compile this code:
 * javac apm/AdaptivePenaltyMethod.java
 * This will generate a 'apm/AdaptivePenaltyMethod.class' object file.
 * To use the AdaptivePenaltyMethod class, it is only necessary
 * to import the class file and
 * to instantiate a object of this class.
 */



package apm;


public class AdaptivePenaltyMethod {

	/*
	 * Attributes.
	 */
	private double[] sumViolation;
	private int numberOfConstraints;

	/*
	 * Constructor.
	 * Parameters:
	 * - numberOfConstraints: the number of constraints of the problem.
	 */
	public AdaptivePenaltyMethod( int numberOfConstraints ) {
		this.numberOfConstraints = numberOfConstraints;
		this.sumViolation = new double[ numberOfConstraints ];
	}
		
	/*
	 * Name: calculatePenalizationCoefficients
	 * Description: Calculate the penalization coefficients 
	 * using the objective function and constraint violation
	 * values by using APM ideas.
	 * Parameters:
	 * - objectiveFunctionValues: values of the objective
	 * function obtained by evaluating the candidate solutions;
	 * - constraintViolationValues: values of the constraint 
	 * violations obtained by evaluating the candidate violations;
	 * - penalizationCoefficients: penalization coefficients
	 * calculated by the adaptive penalty method and which
	 * are used by the penalization function.
	 */
	 public void calculatePenalizationCoefficients (
		double[] objectiveFunctionValues,
		double[][] constraintViolationValues,
		double[] penalizationCoefficients ) {

		int i;
		int j;
		int l;
		double sumObjectiveFunction = 0;
		//foreach candidate solution
		for( i=0; i < objectiveFunctionValues.length; i++ ) {

			sumObjectiveFunction += objectiveFunctionValues[ i ];

		}
		//the absolute of the sumObjectiveFunction
		if ( sumObjectiveFunction < 0 ) {
			sumObjectiveFunction = -sumObjectiveFunction;
		}

		//the denominator of the equation of the penalization coefficients
		double denominator = 0;
		
		for( l=0; l < this.numberOfConstraints; l++ ) {

			this.sumViolation[ l ] = 0;
			for( i=0; i < constraintViolationValues.length; i++ ) {

				this.sumViolation[ l ] += constraintViolationValues[ i ][ l ];

			}

			denominator += this.sumViolation[ l ] * this.sumViolation[ l ];
		}

		//the penalization coefficients are calculated
		for( j=0; j < this.numberOfConstraints; j++ ) {

			penalizationCoefficients[ j ] = ( sumObjectiveFunction / denominator ) * this.sumViolation[ j ];

		}

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
	 
	public void calculateFitness( 
		double[] fitnessValues, 
		double[] objectiveFunctionValues, 
		double[][] constraintViolationValues,
		double[] penalizationCoefficients ) {

		//indicates if the candidate solution is infeasible
		boolean infeasible;
		int i;
		int j;
		//the penalization value
		double penalization;
		for( i=0; i < constraintViolationValues.length; i++ ) {

			//the candidate solutions are assumed feasibles
			infeasible = false;
			penalization = 0;

			for( j=0; j < this.numberOfConstraints; j++ ) {

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


