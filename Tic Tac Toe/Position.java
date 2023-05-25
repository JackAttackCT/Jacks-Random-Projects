
public class Position {
/*    0 1 2 X
 * 0  0|1|2
 *    -+-+-
 * 1  3|4|5
 *    -+-+-
 * 2  6|7|8
 * 
 * Y
 */
	
	private int[] squares;
	
	public Position() {
		squares = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0};
	}
	
	public Position(Position p) {
		squares = p.squares.clone();
	}
	
	public int getValOf(int index) {
		return squares[index];
	}
	
	public Position setValOf(int index, int val) {
		squares[index] = val;
		return this;
	}
	
	public boolean boardFull() {
		for (int i = 0; i < 9; i++) {
			if (squares[i] == 0)
				return false;
		}
		return true;
	}
	
	public int whoWins() { //returns 1 if X wins in this position, -1 if O wins, and 0 if nobody wins
		
		int xMatches;
		int oMatches;
		
		//check rows
		for (int row = 0; row < 3; row++) {
			xMatches = 0;
			oMatches = 0;
			
			for (int col = 0; col < 3; col++) {
				if (squares[3 * row + col] == 1)
					xMatches++;
				if (squares[3 * row + col] == -1)
					oMatches++;
			}
			if (xMatches == 3)
				return 1;
			if (oMatches == 3)
				return -1;
		}
		
		//check columns
		for (int col = 0; col < 3; col++) {
			xMatches = 0;
			oMatches = 0;
			
			for (int row = 0; row < 3; row++) {
				if (squares[3 * row + col] == 1)
					xMatches++;
				if (squares[3 * row + col] == -1)
					oMatches++;
			}
			if (xMatches == 3)
				return 1;
			if (oMatches == 3)
				return -1;
		}
		
		//check top left-bottom right diagonal
		xMatches = 0;
		oMatches = 0;
		for (int i = 0; i <= 8; i += 4) {
			if (squares[i] == 1)
				xMatches++;
			if (squares[i] == -1)
				oMatches++;
		}
		if (xMatches == 3)
			return 1;
		if (oMatches == 3)
			return -1;
		
		//check top right-bottom left diagonal
		xMatches = 0;
		oMatches = 0;
		for (int i = 2; i <= 6; i += 2) {
			if (squares[i] == 1)
				xMatches++;
			if (squares[i] == -1)
				oMatches++;
		}
		if (xMatches == 3)
			return 1;
		if (oMatches == 3)
			return -1;
		
		return 0;
	}
	
	public void displayPos() {
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (x % 2 == 0 && y % 2 == 0)
					System.out.print(squares[x / 2 + 3 * y / 2] == 1 ? 'X' : squares[x / 2 + 3 * y / 2] == -1 ? 'O' : ' ');
				else if (x % 2 == 1 && y % 2 == 0)
					System.out.print('|');
				else if (x % 2 == 0 && y % 2 == 1)
					System.out.print('-');
				else
					System.out.print('+');
			}
			System.out.println();
		}
	}
}
