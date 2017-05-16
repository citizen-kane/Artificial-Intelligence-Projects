Situation Calculus

--------------------------------------------------------------------------

The monkey-and-bananas problem is faced by a monkey in a laboratory with some bananas hanging out of reach from the ceiling. A box is available that will enable the monkey to reach the bananas if he climbs on it.

Initially, the monkey is at posa, banana1 is at posa, banana2 is at posb, banana3 is at posc, and the box is at posd. 

The monkey and box have height low, but if the monkey climbs onto the box he will have height high, the same as the bananas.

The actions available to the monkey include <i>GO</i> from one place to another, <i>PUSH</i> the box from one place to another, <i>CLIMBUP</i> onto or <i>CLIMBDOWN</i> from the box, and <i>GRASP</i> or <i>UNGRASP</i> a banana. The result of a <i>GRASP</i> is that the monkey <i>HOLDS</i> the object if the monkey and object are in the same place at the same height. The result of an <i>UNGRASP</i> is that the monkey does not <i>HOLDS</i> the object any more if he currently <i>HOLDS</i> that object, and the object will be left at the current place and the current height of the monkey. The monkey can <i>HOLDS</i> multiple bananas at the same time, but he cannot <i>PUSH</i> box if he holds any banana.

The initial states are given as:

at(banana1, posa, high, init).

at(banana2, posb, high, init).

at(banana3, posc, high, init).

at(box, posd, low, init).

at(monkey, posa, low, init).

holds ([] , init ).


Fluent <i>at(O, P, H, S)</i> means an object <i>O</i> locates at a position <i>P</i> having height <i>H</i> at situation <i>S</i>.

Fluent <i>holds(L,S)</i> means the monkey holds and only holds items in list <i>L</i> at situation <i>S</i>. 

Actions are defined as:

go(Pos) % go to position Pos 

push(Pos) % push box to position Pos 

climbup ()

climbdown ( )

grasp (Obj)

ungrasp(Obj)

The initial situation is init. 

<i>do(A,S)</i> represents the new situation after applying an action <i>A</i> on situation <i>S</i>. 

The program should be able to output a plan for any goal, if one exists. The plan should be a situation. The goal is one or more comma-separated fluents with a variable as situation. 

Here is one example:

?− at(monkey, posb, low, S), holds([banana2], S).

S=do(climbdown(), do(grasp(banana2),do(climbup(), do(push(posb), do(go(posd), init ))))).

--------------------------------------------------------------------------

Compilation:

--------------------------------------------------------------------------

1. Move file assign.pl from Assign2_KrishnaAgarwala.zip to the vcl.
2. Run "pl" from there
3. If inside the same folder, compile the file by the command:

	['assign.pl'].

--------------------------------------------------------------------------
