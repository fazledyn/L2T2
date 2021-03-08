# 1705066

#! start q0
#! end q8
#! fill B

# Transition Diagram
# current	read	write	move	next

# copying mechanism
q0	1	B	R	q1
q0	0	B	R	q2

#	for initial 1
q1	0	0	R	q1
q1	1	1	R	q1
q1	c	c	R	q1
q1	B	1	L	q3

q3	0	0	L	q3
q3	1	1	L	q3
q3	c	c	L	q3
q3	B	B	R	q0

#	for initial 0
q2	0	0	R	q2
q2	1	1	R	q2
q2	c	c	R	q2
q2	B	0	L	q4

q4	0	0	L	q4
q4	1	1	L	q4
q4	c	c	L	q4
q4	B	B	R	q0

#	seek
q0	c	c	R	q5
q5	0	0	R	q5
q5	1	1	R	q5
q5	B	B	L	q6

#	minusing 1
q6	0	1	L	q6
q6	1	0	L	q8
q6	c	0	L	q7
q7	B	c	R	q8
