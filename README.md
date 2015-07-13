# Simulated-Annealing
Using Simulated Annealing algorithm for solving a cryptarithm

Description of the algorithm:

The program takes as input two strings (S1 and S2) of m length (m is defined at start) and one third string (S3) which is either m or m+1.
The three strings must have up to 10 different letters.Each letter in the strings takes a different value from 0 to 9.
The value of each string, if for example  S = 'ab' and value(a)=1 value(b)=2  ,is defined as val(s) = 12.
Our goal is to find the value of each letter in order to have value(S1) + value(S2) = value(S3).
For example if S1='send',S2='more',S3='money' then  O = 0 , M = 1, Y = 2, E = 5, N= 6, D = 7, R = 8, S = 9 gives us a solution because  val(S1)=9567, val(S2)=1085, val(S3)=10652 therefore 9567 + 1085 = 10652.

In this code simulated annealing is used to find a solution.For more information about simulated annealing visit http://katrinaeg.com/simulated-annealing.html . 
