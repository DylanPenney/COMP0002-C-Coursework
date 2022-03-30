This program generates a representation of a robot (green triangle) and several obstacles, up to a maximum of maxObsticles (red squares), which the robot must avoid whilst trying to reach the target (grey square). 


The program points the robot in the direction of the target upon collision with walls/ceilings or obstacles by checking if the targets x/y coordinates are more/less than that of the robot. 
NOTE: This does not guarantee the robot finds a solution to the target as a successful hunt requires a 'collision point' (obstacle/border) to be on the same x or y coordinate as the target.


Commands to compile and run program:

	gcc -o main main.c
	./main | java -jar ./drawapp-2/drawapp-2.0.jar