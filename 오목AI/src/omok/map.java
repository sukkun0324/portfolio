package omok;

public class map extends G_map{
	/*public int board[][][];
	public map(int size) {
		this.board=new int[size][size][2];
	}*/
	public static void VM_print(int size) {
		System.out.println("GAME START!!");
		for(int i=0;i<size;i++) {
			for(int j=0;j<size;j++) {
				System.out.print(VM[i][j]+ " ");
			}
			System.out.println("#R"+i);
		}
	}
	public static void init_score_map(int MAP[][][],int size) {
		int i,j;
		for(i=0;i<size;i++) for(j=0;j<size;j++) if(MAP[i][j][1]>0)MAP[i][j][1]=0;		
	}

	public static void init_map(int MAP[][][],int size) {
		int i,j;
		for(i=0;i<size;i++) {
			for(j=0;j<size;j++) {
				MAP[i][j][0]=0;
				MAP[i][j][1]=0;
			}
		}
		MAP[size/2][size/2][1]=2;
		MAP[size/2][size/2-1][1]=1;
	}
	
/*	public static void visual_map(int MAP[][][],int size, int bk) {
		int i,j;
		char VM[][]=new char [size][size];
		char A='●';
		char B='○';
		for(i=0;i<size;i++) {
			for(j=0;j<size;j++) {
				if(MAP[i][j][0]==bk) VM[i][j]=A;
				else if(MAP[i][j][0]==0) VM[i][j]='-';
				else VM[i][j]=B;
				System.out.print(VM[i][j]+ " ");
			}
			System.out.println("#R"+i);
		}
	}*/
	
	public static void print_map(int MAP[][][],int size) {
		int i,j;
		for(i=0;i<size;i++) {
			for(j=0;j<size;j++) {
				System.out.print(MAP[i][j][0]+" ");
			}
			System.out.println("#R"+i);
		}
	}
	
	public static int is_draw(int MAP[][][],int size) {
		int i,j,ct=0;
		for(i=0;i<size;i++) {
			for(j=0;j<size;j++) {
				if(MAP[i][j][0]==0)ct++;
			}
		}
		if(ct==0) {
			System.out.println("비겼습니다!!");
			return 1;
		}
		return 0;
	}
	
	public static void print_map2(int MAP[][][],int size) {
		int i,j;
		for(i=0;i<size;i++) {
			for(j=0;j<size;j++) {
				System.out.print(MAP[i][j][1]+" ");
			}
			System.out.println();
		}
	}

	public static int victory_cond(int MAP[][][], int plyr,int size) {
		int count=0, tempx, tempy;
		for(int i=0;i<size;i++) {
			count=0;
			for(int j=0;j<size;j++) {
				if(MAP[i][j][0]==plyr)count++;
				else count=0;
				if(count==5) {
					if(j+1<size&&MAP[i][j+1][0]==plyr) {
						count=0;
						System.out.println("6목은 이길 수 없습니다");
					}
					else return 1;	
				}
			}
		}
		for(int i=0;i<size;i++) {
			count=0;
			for(int j=0;j<size;j++) {
				if(MAP[j][i][0]==plyr)count++;
				else count=0;
				if(count==5) {
					if(j+1<size&&MAP[j+1][i][0]==plyr) {
						count=0;
						System.out.println("6목은 이길 수 없습니다");
					}
					else return 1;	
				}
			}
		}
		for(int i=0; i<size-4;i++) {
			count=0;
			for(int j=0; j<size-4;j++) {
				tempx=i;
				tempy=j;
				for(int k=0;k<5;k++) {
					if(MAP[tempx++][tempy++][0]==plyr) count++;
					else count=0;
				}
				if(count==5) {
					if(tempx+1<size&&tempy+1<size&&MAP[tempx+1][tempy+1][0]==plyr) {
						count=0;
						System.out.println("6목은 이길 수 없습니다");
					}
					else return 1;
				}
			}
		}
		for(int i=0; i<size-4;i++) {
			count=0;
			for(int j=4; j<size;j++) {
				tempx=i;
				tempy=j;
				for(int k=0;k<5;k++) {
					if(MAP[tempx++][tempy--][0]==plyr) count++;
					else count=0;
				}
				if(count==5) {
					if(tempx+1<size&&tempy-1>=0&&MAP[tempx+1][tempy+1][0]==plyr) {
						count=0;
						System.out.println("6목은 이길 수 없습니다");
					}
					else return 1;
				}
			}
		}
		
		return 0;
	}
}