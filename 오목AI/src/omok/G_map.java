package omok;

public class G_map {
	static char VM[][];
	public G_map(){
		System.out.println("error!");
	}
	public G_map(int size){
		VM=new char[size][size];
	}
	void Ginit(int size) {
		int i,j;
		for(i=0;i<size;i++) {
			for(j=0;j<size;j++) {
				VM[i][j]='-';
			}
		}
	}
	
	public static void get_down_B(int a,int b) {
		VM[a][b]='●';
	}
	public static void get_down_W(int a,int b) {
		VM[a][b]='○';
	}
	public static void VM_print(int size) {
		for(int i=0;i<size;i++) {
			for(int j=0;j<size;j++) {
				System.out.print(VM[i][j]+ " ");
			}
			System.out.println("#R"+i);
		}
	}
	
}
