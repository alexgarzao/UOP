Entity start
	No options
	Constants
		0 S start
		1 S e
		2 S antes da chamada a elemento::x
		3 I 1
		4 S io.writeln
		5 S elemento
		6 S x
		7 S depois da chamada a elemento::x
	End
	Valid context (always)
	No properties
	Def start
		No parameters
		Local variables
			0 element e
		End
		No results
		ldconst 2 --> [antes da chamada a elemento::x]
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		newelem 5 --> [elemento]
		stvar 0 --> [e]
		ldvar 0 --> [e]
		mcall 6 --> [x]
		ldconst 7 --> [depois da chamada a elemento::x]
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		stop
	End
End
Entity elemento
	No options
	Constants
		0 S elemento
		1 S x
		2 S antes da chamada a elemento::y
		3 I 1
		4 S io.writeln
		5 S y
		6 S depois da chamada a elemento::y
		7 S no metodo elemento::y
	End
	Valid context (always)
	No properties
	Def x
		No parameters
		No local variables
		No results
		ldconst 2 --> [antes da chamada a elemento::y]
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		ldself
		mcall 5 --> [y]
		ldconst 6 --> [depois da chamada a elemento::y]
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		ret
	End
	Def y
		No parameters
		No local variables
		No results
		ldconst 7 --> [no metodo elemento::y]
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		ret
	End
End
