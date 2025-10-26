# IEEEXtreme Programming Competition 19

Repository containing the source codes and solutions developed for the IEEEXtreme 19.0 programming competition.
Each problem includes sample inputs, outputs, execution performance, and visual representations of the challenge statement.

## Performance Summary

| Problem                              | CPU Time | Memory Usage |
| ------------------------------------ | -------- | ------------ |
| Airline Traveling                    | 5 ms     | 888 KB       |
| Beatrice and the Dream Tree          | 8 ms     | 864 KB       |
| Become as One                        | 12 ms    | 832 KB       |
| Easy Sum                             | 7 ms     | 868 KB       |
| EDPS                                 | 7 ms     | 864 KB       |
| Four Piles                           | 1819 ms  | 888 KB       |
| Magic Wands                          | 4 ms     | 880 KB       |
| New Casino Game                      | 5076 ms  | 241.1 MB     |
| Palindrome Matrix                    | 389 ms   | 385.8 MB     |
| Raju's Matrix Runs                   | 7 ms     | 876 KB       |
| Secure Elliptic Curve Point Addition | 9 ms     | 704 KB       |
| Stable Power Network                 | 7 ms     | 880 KB       |
| The Twin Occurrence Quest            | 9 ms     | 872 KB       |
| Visit Egypt                          | 763 ms   | 162.3 MB     |
| White Knights and Black Warriors     | 8 ms     | 872 KB       |

## Airline Traveling

Determines if travel between cities is possible based on given routes.

### Input

```bash
3 4
1 2
2
0 0
0 1
```

### Output

```bash
Yes
No
```

![airline_traveling](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/airline_traveling.png)

## Beatrice and the Dream Tree

Finds the optimal node based on specific tree traversal rules.

### Input

```bash
8
1 2
2 3
3 4
4 5
5 6
5 7
5 8
```

### Output

```bash
5
```

![beatrice_and_the_dream_tree](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/beatrice_and_the_dream_tree.png)

## Become as One

Determines if elements in an array can be made equal through specific operations within given index ranges.

### Input

```bash
7 4
0 3 1 3 4 1 4
6 6
5 5
4 6
1 2
```

### Output

```bash
Yes
Yes
No
No
```

![become_as_one](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/become_as_one.png)

## Easy Sum

Computes cumulative sums for each position in an array based on specific ordering rules.

### Input

```bash
10 10
10 1 9 2 8 3 7 4 6 5
```

### Output

```bash
619 522 384 272 202 134 76 36 10 0 
```

![easy_sum](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/easy_sum.png)

## EDPS

Validates and constructs a valid parenthesis sequence based on depth constraints.

### Input

```bash
5
0 0 0 2 6
```

### Output

```bash
Yes
((())())()
```

![edps](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/edps.png)

## Four Piles

Calculates the maximum score achievable by strategically moving cards between four piles.

### Input

```bash
3
5 5 5 5 0 0 5 5
4 5 0 1 0 2 3 4
1 2 4 4 2 2 1 3
```

### Output

```bash
1
20
6
```

![four_piles](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/four_piles.png)

## Magic Wands

Solves a matching problem involving different types of wands with specific transformation rules.

### Input

```bash
3
7 3 SSHSHSS
4 5 HHHH
6 4 HSHSHS
```

### Output

```bash
3
0
-1
```

![magic_wands](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/magic_wands.png)

## New Casino Game

Computes probabilities and expected values for a casino game with multiple dice rolls and winning conditions.

### Input

```bash
3
5
2
1
```

### Output

```bash
5
2
1
598946612
0
1
```

![new_casino_game](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/new_casino_game.png)

## Palindrome Matrix

Transforms a matrix into a palindrome by filling missing values while minimizing changes.

### Input

```bash
10 10
.538......
...4...4..
...459157.
5...6..6..
7.16304815
9...6..1..
5...8..2..
138631.351
2...3...7.
7.......4.
```

### Output

```bash
.535......
...4...3..
...531135.
5...3..1..
2.11800811
1...6..1..
5...8..3..
136631.343
2...3...7.
5.......4.
```

![palindrome_matrix](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/palindrome_matrix.png)

## Raju's Matrix Runs

Finds the longest increasing path through adjacent cells in a matrix.

### Input

```bash
4 4
8 9 6 8
6 2 9 9
4 8 9 2
2 1 8 4
```

### Output

```bash
6
```

![rajus_matrix_runs](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/rajus_matrix_runs.png)

## Secure Elliptic Curve Point Addition

Performs point addition operations on elliptic curves over finite fields.

### Input

```bash
3
0 7 17 2 7 2 10
0 7 17 1 5 3 0
0 7 17 1 5 1 12
```

### Output

```bash
POINT_AT_INFINITY
15 13
POINT_AT_INFINITY
```

![secure_elliptic_curve_point_addition](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/secure_elliptic_curve_point_addition.png)

## Stable Power Network

Optimizes power distribution in a network by selecting the best configuration of connections.

### Input

```bash
3
2 9
2 1 6 3
2 1 25 29
2 1 16 21
1 2 29 1
2 1 7 95
2 1 16 3
1 2 90 56
2 1 86 12
1 2 93 83
8 1
1 8 45 68
6 7
2 4 55 26
3 2 45 71
1 6 86 80
4 3 55 96
1 3 55 43
4 3 10 57
6 3 32 79
```

### Output

```bash
1 29
68 45
79 87
```

![stable_power_network](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/stable_power_network.png)

## The Twin Occurrence Quest

Finds pairs of indices where a target value appears in a sorted array.

### Input

```bash
8 4
2 4 4 4 5 8 10 12
4
10
5
11
```

### Output

```bash
2 4
7 7
5 5
-1 -1
```

![the_twin_occurrence_quest](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/the_twin_occurrence_quest.png)

## Visit Egypt

Compares travel costs between two travelers considering various pricing schemes and determines the winner.

### Input

```bash
5
10 10 25
1 443443317 3000000
40 338770238 338770238
60 338770238 318903897
100 572914301 572914315
```

### Output

```bash
Andrew
Mikel
TIE
Andrew
NONE
```

![visit_egypt](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/visit_egypt.png)

## White Knights and Black Warriors

Calculates the maximum matching or optimal assignment in a bipartite graph representing a strategic game scenario.

### Input

```bash
8 1
0 1 1 0 0 0 0 0
1 2
1 3
1 4
2 5
4 6
4 7
3 8
5 8
```

### Output

```bash
8
```

![white_knights_and_black_warriors](https://raw.githubusercontent.com/Mulekotd/ieeextreme-19/refs/heads/main/assets/white_knights_and_black_warriors.png)
