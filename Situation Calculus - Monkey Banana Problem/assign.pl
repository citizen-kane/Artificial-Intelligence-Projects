banana(banana1).
banana(banana2).
banana(banana3).

pos(posa).
pos(posb).
pos(posc).
pos(posd).

monkey(monkey).
box(box).

at(banana1, posa, high, init).
at(banana1, posa, high, do(go(_),init)).
at(banana1, posa, high, do(push(_),do(go(_),init))).
at(banana1, posa, high, do(climbup(), do(push(_),do(go(_),init)))).
at(banana1, posa, high, do(climbup(),X)):-
	holds([banana1], X),
	at(banana1, posa, low, X).
at(banana1, posa, high, do(climbup(),X)):-
	\+ holds([banana1], X),
	at(banana1, posa, low, X).
at(banana1, posa, high, do(grasp(banana1),X)).
at(banana1, posa, low, do(climbdown(),X)):-
	holds([banana1], X),
	at(banana1, posa, high, X).
at(banana1, posa, high, do(climbdown(),X)):-
	\+ holds([banana1], X),
	at(banana1, posa, high, X).
at(banana1, posa, high, do(ungrasp(banana1),X)):-
	holds([banana1], X),
	at(banana1, posa, high, X).
at(banana1, posa, low, do(ungrasp(banana1),X)):-
	holds([banana1], X),
	at(banana1, posa, low, X).
at(banana1, P, low, do(go(P),X)):-
	holds([banana1], X),
	at(banana1, posa, low, X).

at(banana2, posb, high, init).
at(banana2, posb, high, do(go(_),init)).
at(banana2, posb, high, do(push(_),do(go(_),init))).
at(banana2, posb, high, do(climbup(), do(push(_),do(go(_),init)))).
at(banana2, posb, high, do(climbup(),X)):-
	holds([banana2], X),
	at(banana2, posb, low, X).
at(banana2, posb, high, do(climbup(),X)):-
	\+ holds([banana2], X),
	at(banana2, posb, low, X).
at(banana2, posb, high, do(grasp(banana2),X)).
at(banana2, posb, low, do(climbdown(),X)):-
	holds([banana2], X),
	at(banana2, posb, high, X).
at(banana2, posb, high, do(climbdown(),X)):-
	\+ holds([banana2], X),
	at(banana2, posb, high, X).
at(banana2, posb, high, do(ungrasp(banana2),X)):-
	holds([banana2], X),
	at(banana2, posb, high, X).
at(banana2, posb, low, do(ungrasp(banana2),X)):-
	holds([banana2], X),
	at(banana2, posb, low, X).
at(banana2, P, low, do(go(P),X)):-
	holds([banana2], X),
	at(banana2, posb, low, X).

at(banana3, posc, high, init).
at(banana3, posc, high, do(go(_),init)).
at(banana3, posc, high, do(push(_),do(go(_),init))).
at(banana3, posc, high, do(climbup(), do(push(_),do(go(_),init)))).
at(banana3, posc, high, do(climbup(),X)):-
	holds([banana3], X),
	at(banana3, posc, low, X).
at(banana3, posc, high, do(climbup(),X)):-
	\+ holds([banana3], X),
	at(banana3, posc, low, X).
at(banana3, posc, high, do(grasp(banana3),X)).
at(banana3, posc, low, do(climbdown(),X)):-
	holds([banana3], X),
	at(banana3, posc, high, X).
at(banana3, posc, high, do(climbdown(),X)):-
	\+ holds([banana3], X),
	at(banana3, posc, high, X).
at(banana3, posc, high, do(ungrasp(banana3),X)):-
	holds([banana3], X),
	at(banana3, posc, high, X).
at(banana3, posc, low, do(ungrasp(banana3),X)):-
	holds([banana3], X),
	at(banana3, posc, low, X).
at(banana3, P, low, do(go(P),X)):-
	holds([banana3], X),
	at(banana3, posc, low, X).

holds([], init).
holds([], do(go(_),init)).
holds([], do(push(_),do(go(_),init))).
holds([], do(climbup(), do(push(_),do(go(_),init)))).
holds([B], do(grasp(B),X)):-
	banana(B),
	at(B, P, high, init),
	at(monkey, P, high, do(grasp(B),X)).
	%at(monkey, P, high, X).
holds([B], do(climbdown(),X)):-
	holds([B], X),!.
holds([], do(ungrasp(B),X)):-
	banana(B),
	holds([B], X).
	%at(monkey, _, _, do(ungrasp(B),X)).
holds([B], do(go(P),X)):-
	holds([B], X).


at(box,_,high,_):- false.

at(box, posd, low, init).
at(box, P, low, do(go(P),init)):-
	at(box, P, low, init).

at(box, Q, low, do(go(P),init)):-
	Q\=P,
	at(monkey, P, low, do(go(P),init)).
at(box,P,low,do(push(P),X)):- 
	at(monkey,P,low,do(push(P),X)).
at(box, P, low, do(climbup(),X)):-
	at(box, P, low, X),!.
at(box, P, low, do(grasp(_),X)):-
	at(box, P, low, X),!.
at(box, P, low, do(climbdown(),X)):-
	at(box, P, low, X),!.
at(box, P, low, do(ungrasp(_),X)):-
	at(box, P, low, X),!.

/*init*/
at(monkey, posa, low, init).

/*do(go(P),init)*/
at(monkey, P, low, do(go(P),init)):-
	pos(P),
	P\=posa.

/*do(push(Q),do(go(P),init))*/
at(monkey,P,low,do(push(P),X)):- 
	pos(P),
	P\=posd,
	at(monkey,posd,low,X),
	at(box,posd,low,X).

/*do(climbup(),do(push(Q),do(go(P),init)))*/
at(monkey, P, high, do(climbup(),X)):-
	pos(P),
	P\=posd,
	at(monkey, P, low, X),
	at(box, P, low, X).

/*do(grasp),do(climbup(),do(push(Q),do(go(P),init)))*/

at(monkey, P, high, do(grasp(B),X)):-
	banana(B),
	at(B, P, high, init),
	at(monkey, P, high, X),!.

/*do(ungrasp(), do(grasp),do(climbup(),do(push(Q),do(go(P),init)))*/
at(monkey, P, H, do(ungrasp(B),X)):-
	banana(B),
	holds([B], X),
	at(monkey, P, H, X).

/*do(climbdown(),do(grasp),do(climbup(),do(push(Q),do(go(P),init)))*/
at(monkey, P, low, do(climbdown(),X)):-
	holds([_], X),
	at(monkey, P, high, X).

at(monkey, P, low, do(climbdown(),X)):-
	\+ holds([_], X),
	at(monkey, P, high, X).

/*do(go(Q), do(climbdown(),do(grasp),do(climbup(),do(push(Q),do(go(P),init)))*/

at(monkey, P, low, do(go(P),X)):-
	%X\=init,
	pos(Q),
	P\=Q,
	holds([_], X),
	at(monkey, Q, low, X).