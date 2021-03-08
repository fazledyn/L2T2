## Turing Machine Simulation

#### Simulator Used: [Tursi](https://schaetzc.github.io/tursi/)

### Problem 1
Design Turing machines for the following languages: "The set of strings with an equal number of 0’s and 1’s"

#### Solution:

```tm

#! start q0
#! end q4
#! fill B

q0	0	x	R	q1
q0	1	x	R	q2
q0	x	x	R	q0
q0	B	B	L	q4
q1	0	0	R	q1
q1	1	x	L	q3
q1	x	x	R	q1
q1	B	B	L	q5
q2	0	x	L	q3
q2	1	1	R	q2
q2	x	x	R	q2
q2	B	B	L	q5
q3	0	0	L	q3
q3	1	1	L	q3
q3	x	x	L	q3
q3	B	B	R	q0

```

#### Solution:
Easy as eating a fruitcake.

### Problem 2
Design Turing machines to perform the following operations (the leftmost bit is LSB): 

Decrement (subtract 1). The tape initially contains wc where w is a binary number.Your TM should subtract 1 from w and write the result to the right of the c. 

#### Solution:

```tm

#! start q0
#! end q8
#! fill B

```

At first, we divide it into two part. Where we found- 

1. 1 first (q0 --> q1)
2. 0 first (q0 --> q2)

```tm

q0	1	B	R	q1
q0	0	B	R	q2

```
The following part is for the reality where we had found 1 first. Now, just copy the whole string to right of c.

```tm

q1	0	0	R	q1
q1	1	1	R	q1
q1	c	c	R	q1
q1	B	1	L	q3

q3	0	0	L	q3
q3	1	1	L	q3
q3	c	c	L	q3
q3	B	B	R	q0

```

Now, we are going to work for the reality where we had found 0 first. Now, just copy the whole string to right of c.

```tm

q2	0	0	R	q2
q2	1	1	R	q2
q2	c	c	R	q2
q2	B	0	L	q4

q4	0	0	L	q4
q4	1	1	L	q4
q4	c	c	L	q4
q4	B	B	R	q0

```

In the following part, we take the cursor back to the rightmost part of the newly copied string (binary number).

```tm

q0	c	c	R	q5
q5	0	0	R	q5
q5	1	1	R	q5
q5	B	B	L	q6

```

Then, if we find 1, we just replace it with 0 and finish (q8). But if we find 0, then we replace it with 1 and then keep going on and on (for the next bit after it).

```tm

# minus part
q6	0	1	L	q6
q6	1	0	L	q8
q6	c	0	L	q7
q7	B	c	R	q8

```
