Entity start
	No options
	Constants
		0 S start
		1 R 10.000000
		2 R 20.000000
		3 I 1
		4 S io.writeln
		5 R 30.000000
		6 R 5.000000
	End
	Valid context (always)
	No properties
	Def start
		No parameters
		No local variables
		No results
		ldconst 1 --> [10.000000]
		ldconst 2 --> [20.000000]
		mul
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		ldconst 1 --> [10.000000]
		ldconst 2 --> [20.000000]
		mul
		ldconst 5 --> [30.000000]
		div
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		ldconst 1 --> [10.000000]
		ldconst 2 --> [20.000000]
		mul
		ldconst 6 --> [5.000000]
		div
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		stop
	End
End
