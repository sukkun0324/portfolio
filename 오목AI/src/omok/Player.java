package omok;

public class Player {

	public int player(int row,int column,int size,int mode) {
		/*if(row>=size||column>=size||row<0||column<0) {
			System.out.println("둘 수 없는 곳 입니다! 다시 선택해 주세요!");
			return 0;
		}
		if(MAP[row][column][0]!=0){
			System.out.println("이미 돌이 있는곳 입니다! 다시 선택해 주세요!");
			return 0;
		}
		else {*/
			//System.out.println("======들어옴=========");
			Game.omok_map[row][column][0]=1;
			//System.out.println("======들어옴=========");
			Game.omok_map[row][column][1]=-1;
			//System.out.println("======들어옴=========");
			if(mode==0)	G_map.get_down_B(row,column);
			else G_map.get_down_W(row,column);
			//System.out.println("======들어옴=========");
			return 1;
		
	}
}
