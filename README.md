# Lagrangian_solver
Attempting to solve general EoMs

This program is designed to take in an equation of the form L=K-U, a lagrangian. Then, it attempts to find the Equations of Motion and action of the Lagrangian, either symbolically, or numerically. 
These two goals rely upon a new set of varibles to store symbolic functions with related variables, i.e. v=dx/dt, and a basic numerical calculus approach, which are laid out in func and calc classes respectively
