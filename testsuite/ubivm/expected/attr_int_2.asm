Entity start
	No options
	Constants
		0 S start
		1 S var1
		2 I 10
		3 I 1
		4 S io.writeln
	End
	Valid context (always)
	No properties
	Def start
		No parameters
		Local variables
			0 int var1
		End
		No results
		ldconst 2 --> [10]
		stvar 0 --> [var1]
		ldvar 0 --> [var1]
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		stop
	End
End
