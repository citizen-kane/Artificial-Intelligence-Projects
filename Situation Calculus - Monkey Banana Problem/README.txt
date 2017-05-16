README
======================================================================================================================================================================================================

Compilation:
============
1. Move file assign.pl from Assign2_KrishnaAgarwala.zip to the vcl.
2. Run "pl" from there
3. If inside the same folder, compile the file by the command:

	['assign.pl'].

4. Or if in another folder (use the complete path of the file):
	['/Users/krishnaagarwala/Downloads/assign.pl'].


Note:
The code does not work for multiple elements inside holds([], X).
eg.
It only works for 	holds([banana1], X).
					holds([banana2], X).
					holds([banana3], X).

not for 			holds([banana1, banana2], X).
======================================================================================================================================================================================================