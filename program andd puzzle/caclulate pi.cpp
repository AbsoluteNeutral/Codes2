
#include <stdio.h>
#include <math.h>

double circle_pi(int rectangles);  // Calculates PI using a quarter circle
double leibniz_pi(int iterations); // Calculates PI using a series

/*
Rectangle method
Adding more and more rectangle for accuracy
*/
double circle_pi(int num_rectangles)
{
	const double RADIUS 		= 2.0f;
	const double RADIUS_Sq 	= RADIUS * RADIUS;
  double pi								= 0.0f;       // pi value
  double height						= 0.0f;   		// Height of EACH rectangle 
  double adjacent					= 0.0f; 			// Adjacent side of EACH triangle in the circle
  double width						= RADIUS/(double)num_rectangles;   // Width of EACH rectangle
  int i;           				// Loop count, the midpoint coordinates of EACH rectangle
	
  for(i = 1; i <= num_rectangles; ++i)  //i=1, start with first rectangle
  {
    adjacent = (i - 0.5f) * width;      //adjacent side of next triangle
                                        //pythagoras theorem
    height = sqrt(RADIUS_Sq - adjacent * adjacent);  
    pi += height * width;               //sum of ALL rectangle area
  }
  return pi; 
}

/*
PI using Leibniz Method (the father of calculus):
Using number series:
pi/4 =  1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + ...
pi   = (1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + ... ) * 4
*/
double leibniz_pi(int num_iterations)
{
	//#version 1
  //double sum		= 0.0f;         // Sum of ALL iterations
  //double denom	= 1.0f;       	// Denominator of the fraction
  // 
  //if(num_iterations > 0)        // Checks for positive value
  //{
	//	bool count_up = true;       // Control the loop, starting with ODD Loop
  //  do{                        
  //    if(count_up)            	// MUST begins with ODD loop         
  //      sum += 1.0f/denom;      // ODD num iterations ADD
  //    else                    
  //      sum -= 1.0f/denom;      // EVEN num iterations SUBTRACT
  //  
  //      denom += 2;             // Increment Denominator twice
  //      --num_iterations;       // number of iterations left
  //      count_up = !count_up;             // next iterations
  //  }
  //  while(num_iterations > 0);
  //  
  //  return sum * 4.0f;
  //}
  //else
  //{
  //  return 0.0f;
  //}
	
	//#version 2
	double sum		= 0.0f;     // Sum of ALL iterations
  double denom	= 1.0f;     // Denominator of the fraction
	double count	= 1.0f;     // Control the loop, starting with ODD Loop
	
  while(num_iterations-- > 0)
	{		
		sum 		 += count/denom; // ODD num iterations ADD
    denom 	 += 2;           // Increment Denominator twice
    count 	 = -count;       // next iterations
  }
	
  return sum * 4.0f;
}

int main(void)
{
  int i;
  printf("Approximations for pi\n");
  printf("Iterations      Circle Method   Leibniz Method   Differences\n");
  printf("------------------------------------------------------------\n");

  for (i = 1; i <= 1000000; i *= 10)
  {
    double pi_circle = circle_pi(i);
    double pi_leibniz = leibniz_pi(i);
    printf("%10i%20.12f%16.12f%16.12f\n", i, pi_circle, pi_leibniz, pi_circle-pi_leibniz);
  }

  return 0;
}
