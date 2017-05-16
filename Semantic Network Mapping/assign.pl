isa(tom, diabetics).
ako(snickers, candy).
contains(candy, sugar).
shouldAvoid(diabetics, sugar).

rel_isa(tom, isa, diabetics).
rel_shouldAvoid(diabetics, shouldAvoid, sugar).
rel_contains(candy, contains, sugar).
rel_ako(snickers, ako, candy).

value(X, Y, Z):-
	rel_isa(X, Y, Z).

value(X, Y, Z):-
	rel_ako(X, Y, Z).

value(X, Y, Z):-
	rel_contains(X, Y, Z).

value(X, Y, Z):-
	rel_contains(A, Y, Z),
	value(X, ako, A).

value(X, Y, Z):-
	rel_shouldAvoid(X, Y, Z).

value(X, Y, Z):-
	rel_shouldAvoid(X, Y, A),
	value(Z, contains, A).

value(X, Y, Z):-
	rel_shouldAvoid(A, Y, Z),
	value(X, isa, A).

value(X, Y, Z):-
	rel_shouldAvoid(A, Y, B),
	value(X, isa, A),
	value(Z, contains, B).