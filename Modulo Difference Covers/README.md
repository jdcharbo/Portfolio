The code in this folder was created as part of a research project I did in undergrad. The goal was to create an algorithm that generates a modulo difference cover for Z_n in polynomial time whose size was less than k=2(n^(1/2)).

To do this I explored two avenues, a greedy algorithm (CoverB2) and an algorithm that constructs covers from the Chinese Remainder Theorem (CoverCRT).

The CoverCRT algorithm performed worse than the greedy algorithm in both time and size, and while the cover that is generated from the greedy algorithm was smaller than k above for n<=100000, I did not prove that this held in general during my work on this project.

Included are the poster and slides I used when presenting this project.
