# AdvancedAlgorithm_Project

## Environment

1. Python 3.6

2. Main packages used: 
    * random
    * math
    * time (for evaluation)
    * matplotlib.pyplot (for evaluation plotting)
    * sys (for input and output on Kattis)

## Files Description

1. **fraction.py**:
    
    In this python file we wrote definitions for all the algorithms as following:
    * miller_rabin: implementation of Miller Rabin algorithm to judge prime numbers
    * brent: implementation of Pollard's Rho algorithm with Brent for factorization
    * pollard: implementation of Pollard's Rho algorithm for factorization
    * extract: a sub-function for trial division
    * trivial_div: implementation of trial division algorithm
    
    And the last part of "for" loop is for input and output on Kattis.

2. **prime_table.py**:

    In this python file we generate the prime table for trial division in fraction.py.

3. **evalution.py**:
    
    In this python file we wrote the evaluation function for pollard and brent algorithms and it generates a figure for the report.
