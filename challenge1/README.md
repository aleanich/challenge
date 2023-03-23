## PACS-Challenge1 ##

# Theta Method for computing the numerical solution of a Cauchy problem of 1D function #

**Note** In order to run the code on your device you must change the directory to yours that contains /Examples on pacs-examples repository.

Then:
- command `make` to compile the code
- command `make result` to visualize the numerical and the exact solution
- command `make err` to visualize the order of convergence of the used method

You can modify the file `parameters.json` to suit the code for your problem.
It contains:
- N : number of subintervals
- T : final time
- u0 : initial condition
- theta : parameter between 0 and 1 (0.5 for Crank-Nicolson, 1.0 for Backward Eulero, 0.0 for Forward Eulero)
- k : number of refinement
- f : forcing term
- fex : exact solution
- solverType : method for finding the zero used in theta method (1 for Newton method, 0 for Secant method)

Enjoy!