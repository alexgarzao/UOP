Entity start
	No options
	Constants
		0 S start
		1 S result
		2 S e
		3 S elemento
		4 S x
		5 S result: 
		6 I 2
		7 S io.writeln
	End
	Valid context (always)
	No properties
	Def start
		No parameters
		Local variables
			0 string result
			1 element e
		End
		No results
		newelem 3 --> [elemento]
		stvar 1 --> [e]
		ldvar 1 --> [e]
		mcall 4 --> [x]
		stvar 0 --> [result]
		ldconst 5 --> [result: ]
		ldvar 0 --> [result]
		ldconst 6 --> [2]
		lcall 7 --> [io.writeln]
		stop
	End
End
Entity elemento
	No options
	Constants
		0 S elemento
		1 S x
		2 S oi
	End
	Valid context (always)
	No properties
	Def x
		No parameters
		No local variables
		Result
			0 string
		End
		ldconst 2 --> [oi]
		stresult 0
		ret
	End
End
