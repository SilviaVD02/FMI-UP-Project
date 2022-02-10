#pragma once

/*
How i would do a REDACT SHIP FUNC();

switch-case

within the MAIN ShipSelect Func
			1/Show My field - > Shows field -> ShipSelectFunc();
			2/Place NEW ship -> Choose a Direction -> (***);
			3/Redact Ship -> RedactShipFunc() -> ShipSelectFunc();


Similar to the other function the player puts input of the number of option
a/ Cancel Operation -> ShipSelectFunc();
b/ Delete ship -> Ship in which direction you wanta to delete 
					-> Select a STARTSQUARE 
						-> 'Deletes/Restarts' all '1' by turning them into '0' in the players bool array
						  -> 'Restarts' ship length (MakeShiplength Available)
c/ The DEFAULT switch case -> RedactShipFunc();

And ALL this will be 'trapped' in a cycle till it reached the max number of selected ships

-> Next player's turn to choose their ships
-> GAME BEGINS

*/