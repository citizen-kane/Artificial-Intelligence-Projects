Implementation of a Truth Maintenance System (TMS)
--------------------------------------------------

TMSInput.txt is a text file containing a sequence of actions that will force the TMS to add and retract multiple items.

In the text file, “*” means logical AND(∧), “+” represents logical OR(∨), and “-” indicates logical NEGATION(¬).

The system should print out the final status of the TMS knowledge base after executing the actions in the input file.

--------------------------------------------------

Example:

	Tell:A −> B
	Tell:A
	Tell:A + -C −> D
	Tell:-C
	Retract:A

The status of TMS after executing each step are shown as follows:

[![TMS Result](https://github.com/citizen-kane/Artificial-Intelligence-Projects/blob/master/Truth%20Maintenance%20System/TMA%20Result%20-%20Example.png)](#features)


So the final status of TMS is: 

	A −> B
	A + -C −> D
	D: {-C, A + -C −> D}
	-C

Note: If the TMS contains A and B, Tell:A*B− >C will cause C to be added to the TMS as C:{A, B, A * B −> C}.

--------------------------------------------------
