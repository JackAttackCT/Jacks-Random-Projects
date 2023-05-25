import java.util.Scanner;
public class Driver {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Position board = new Position();
		char playerSelect;
		int squareSelect;
		int move;
		do {
			System.out.print("Please type 'x' to play as X or 'o' to play as O: ");
			playerSelect = sc.next().charAt(0);
		} while (playerSelect != 'x' && playerSelect != 'o');
		
		if (playerSelect == 'o') {
			move = Hal.bestMove(board, true)[0];
			board.setValOf(move, 1);
			System.out.printf("Hal plays %d\n", move);
		}
		
		while (board.whoWins() == 0 && !board.boardFull()) {
			board.displayPos();
			
			do {
				System.out.print("Enter a number 0-8: ");
				squareSelect = sc.nextInt();
			} while (board.getValOf(squareSelect) != 0);
			
			board.setValOf(squareSelect, playerSelect == 'x' ? 1 : -1);
			
			if (!board.boardFull()) {
				move = Hal.bestMove(board, playerSelect == 'o')[0];
				board.setValOf(move, playerSelect == 'x' ? -1 : 1);
				System.out.printf("Hal plays %d\n", move);
			}
		}
		board.displayPos();
		if (board.whoWins() == 1)
			System.out.println("X Wins!");
		else if (board.whoWins() == -1)
			System.out.println("O Wins!");
		else
			System.out.println("Tie!");
	}

}
