# 1705066

#! start q0
#! end q4
#! fill B

# Transition Diagram
# current	read	write	move	next

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
