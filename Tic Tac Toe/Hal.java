
public class Hal {
	public static int[] bestMove(Position pos, boolean xToPlay) {//returns data in the form {move, eval}
		//if X or O has won the game in this position, report it
		if (pos.whoWins() != 0)
			return new int[] {0, pos.whoWins()};
		
		//otherwise, if the game is a tie, report it
		if (pos.boardFull())
			return new int[] {0, 0};
		
		int bestMove = -1;
		int evalOfBestMove = 2;
		//look through every possible move
		for (int i = 0; i < 9; i++) {
			
			//check if this is a legal move
			if (pos.getValOf(i) == 0) {
				
				//construct a new board, supposing that that space was chosen
				Position modifiedPos = new Position(pos).setValOf(i, xToPlay ? 1 : -1);
				//eval this new position recursively
				int[] result = bestMove(modifiedPos, !xToPlay);
				int posEval = result[1];
				
				//if the best eval is the default 2, this move is automatically the best move so far
				//if xToPlay is true, we want to pick the maximum eval. If it is false, we want the minimum. The XOR accomplishes this
				if (evalOfBestMove == 2 || (xToPlay ^ posEval < evalOfBestMove)) {
					//update
					evalOfBestMove = posEval;
					bestMove = i;
				}
			}
		}
		
		return new int[] {bestMove, evalOfBestMove};
	}

}
