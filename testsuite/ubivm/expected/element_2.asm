Entity start
	No options
	Constants
		0 S start
		1 S e
		2 S elemento
		3 S Antes de chamar imprime
		4 I 1
		5 S io.writeln
		6 S imprime
		7 S Depois de chamar imprime
	End
	Valid context (always)
	No properties
	Def start
		No parameters
		Local variables
			0 element e
		End
		No results
		newelem 2 --> [elemento]
		stvar 0 --> [e]
		ldconst 3 --> [Antes de chamar imprime]
		ldconst 4 --> [1]
		lcall 5 --> [io.writeln]
		ldvar 0 --> [e]
		mcall 6 --> [imprime]
		ldconst 7 --> [Depois de chamar imprime]
		ldconst 4 --> [1]
		lcall 5 --> [io.writeln]
		stop
	End
End
Entity elemento
	No options
	Constants
		0 S elemento
		1 S imprime
		2 S Metodo elemento.imprime()
		3 I 1
		4 S io.writeln
	End
	Valid context (always)
	No properties
	Def imprime
		No parameters
		No local variables
		No results
		ldconst 2 --> [Metodo elemento.imprime()]
		ldconst 3 --> [1]
		lcall 4 --> [io.writeln]
		ret
	End
End
