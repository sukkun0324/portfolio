package omok;

public class Com extends G_map{
	public static int[] com(int MAP[][][], int size, int mode) {
		int find_Max=0,max_i=0,max_j=0;
		for(int i=0; i<size;i++) {
			for(int j=0; j<size;j++){
				if(MAP[i][j][0]==0&&MAP[i][j][1]>find_Max){
					find_Max=MAP[i][j][1];
					max_i=i;
					max_j=j;
				}
			}
		}
		MAP[max_i][max_j][0]=2;
		MAP[max_i][max_j][1]=-2;
		if(mode==1)	get_down_B(max_i,max_j);
		else get_down_W(max_i,max_j);
		System.out.println("컴퓨터가 둔 곳은 ("+max_i+" "+max_j+") 입니다!");
		return new int[] {max_i,max_j};
	}
	public static void check_score(int MAP[][][], int plyr,int size) {
		int score=0,count=0, tempx, tempy, rev_tx, rev_ty;
		for(int i=0;i<size;i++) {
			count=0;
			for(int j=0;j<size;j++) {
				if(MAP[i][j][0]==plyr) count++;
				else {
					if(count==0)continue;
					else if(j+1<size&&MAP[i][j+1][0]==plyr)count++;
					switch(count) {
						case 1:
							score=2;
							break;
						case 2:
							score=5;
							break;
						case 3:
							score=80;
							break;
						case 4:
							score=300000;
							break;
					}
					tempy=j-count-1;
					if(MAP[i][j][0]==0) {
						if(tempy>=0&&MAP[i][tempy][0]==0) {
							if(MAP[i][j][1]>1)MAP[i][j][1]*=score;
							else MAP[i][j][1]+=score;
							if(MAP[i][tempy][1]>1)MAP[i][tempy][1]*=score;
							else MAP[i][tempy][1]+=score;
						}
						else if(tempy<0||MAP[i][tempy][0]!=0) {
							if(MAP[i][j][1]>1)MAP[i][j][1]*=score/2;
							else MAP[i][j][1]+=score/2;
						}
					}
					else if(tempy>=0&&MAP[i][tempy][0]==0) {
						if(MAP[i][tempy][1]>1)MAP[i][tempy][1]*=score/2;
						else MAP[i][tempy][1]+=score/2;
					}
					score=0;
					count=0;
				}
			}
		}
		for(int i=0;i<size;i++) {
			count=0;
			for(int j=0;j<size;j++) {
				if(MAP[j][i][0]==plyr)count++;
				else {
					if(count==0)continue;
					else if(j+1<size&&MAP[j+1][i][0]==plyr)count++;
						switch(count) {
							case 1:
								score=2;
								break;
							case 2:
								score=5;
								break;
							case 3:
								score=80;
								break;
							case 4:
								score=300000;
								break;
						}
						tempx=j-count-1;
						count=0;
						if(MAP[j][i][0]==0) {
							if(tempx>=0&&MAP[tempx][i][0]==0) {
								if(MAP[j][i][1]>1)MAP[j][i][1]*=score;
								else MAP[j][i][1]+=score;
								if(MAP[tempx][i][1]>1)MAP[tempx][i][1]*=score;
								else MAP[tempx][i][1]+=score;
							}
							else if(tempx<0||MAP[tempx][i][0]!=0) {
								if(MAP[j][i][1]>1)MAP[j][i][1]*=score/2;
								else MAP[j][i][1]+=score/2;
							}
						}
						else if(tempx>=0&&MAP[tempx][i][0]==0) {
							if(MAP[tempx][i][1]>1)MAP[tempx][i][1]*=score/2;
							else MAP[tempx][i][1]+=score/2;
						}
						score=0;
						count=0;
				}
			}
		}
		for(int i=0; i<size-4;i++) {
			count=0;
			for(int j=0; j<size-4;j++) {
				tempx=i;
				tempy=j;
				if(tempx-1>=0&&tempy-1>=0&&MAP[tempx-1][tempy-1][0]==MAP[tempx][tempy][0]) {
					continue;
				}
				for(int k=0;k<5;k++) {
					if(MAP[tempx][tempy][0]==plyr) {
						count++;tempx++;tempy++;
					}
					else {
						if(count==0) break;
						else if(tempx+1<size&&tempy+1<size&&MAP[tempx+1][tempy+1][0]==plyr)count++;
						switch(count) {
							case 1:
								score=2;
								break;
							case 2:
								score=5;
								break;
							case 3:
								score=80;
								break;
							case 4:
								score=300000;
								break;
						}
						rev_tx=tempx-count-1;
						rev_ty=tempy-count-1;
						if(tempx<size&&tempy<size&&MAP[tempx][tempy][0]==0) {
							if(rev_tx>=0&&rev_ty>=0&&MAP[rev_tx][rev_ty][0]==0) {
								if(MAP[tempx][tempy][1]>1)MAP[tempx][tempy][1]*=score;
								else MAP[tempx][tempy][1]+=score;
								if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score;
								else MAP[rev_tx][rev_ty][1]+=score;
							}
							else if(rev_tx>=0&&rev_ty>=0&&MAP[rev_tx][rev_ty][0]!=0) {
								if(MAP[tempx][tempy][1]>1)MAP[tempx][tempy][1]*=score/2;
								else MAP[tempx][tempy][1]+=score/2;
							}
						}
						else if(rev_ty>=0&&rev_tx>=0&&MAP[rev_tx][rev_ty][0]==0) {
							if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score/2;
							else MAP[rev_tx][rev_ty][1]+=score/2;
						}
						score=0;
						count=0;
					}
				}
				count=0;
			}
		}
		for(int i=0; i<size-4;i++) {
			count=0;
			for(int j=4; j<size;j++) {
				tempx=i;
				tempy=j;
				if(tempx-1>=0&&tempy+1<size&&MAP[tempx-1][tempy+1][0]==MAP[tempx][tempy][0]) {
					continue;
				}
				for(int k=0;k<5;k++) {
					if(MAP[tempx][tempy][0]==plyr) {
						count++;tempx++;tempy--;
					}
					else {
						if(count==0)break;
						else if(tempx+1<size&&tempy-1>=0&&MAP[tempx+1][tempy-1][0]==plyr)count++;
						switch(count) {
							case 1:
								score=2;
								break;
							case 2:
								score=5;
								break;
							case 3:
								score=80;
								break;
							case 4:
								score=300000;
								break;
						}
						rev_tx=tempx-count-1;
						rev_ty=tempy+count+1;
						if(tempx<size&&tempy>=0&&MAP[tempx][tempy][0]==0) {
							if(rev_tx>=0&&rev_ty<size&&MAP[rev_tx][rev_ty][0]==0) {
								if(MAP[tempx][tempy][1]>1)MAP[tempx][tempy][1]*=score;
								else MAP[tempx][tempy][1]+=score;
								if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score;
								else MAP[rev_tx][rev_ty][1]+=score;
							}
							else if(rev_tx>=0&&rev_ty<size&&MAP[rev_tx][rev_ty][0]!=0) {
								if(MAP[tempx][tempy][1]>1)MAP[tempx][tempy][1]*=score/2;
								else MAP[tempx][tempy][1]+=score/2;
							}
						}
						else if(rev_ty<size&&rev_tx>=0&&MAP[rev_tx][rev_ty][0]==0) {
							if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score/2;
							else MAP[rev_tx][rev_ty][1]+=score/2;
						}
						score=0;
						count=0;
					}
				}
				count=0;
			}
		}

	}
	public static void blocking_plyr(int MAP[][][], int plyr,int size) {
		int score=0,count=0, tempx, tempy, rev_tx, rev_ty;
		for(int i=0;i<size;i++) {
			count=0;
			for(int j=0;j<size;j++) {
				if(MAP[i][j][0]==plyr) count++;
				else {
					if(count==0)continue;
					else if(j+1<size&&MAP[i][j+1][0]==plyr)count++;
					switch(count) {
						case 1:
							score=1;
							break;
						case 2:
							score=5;
							break;
						case 3:
							score=60;
							break;
						case 4:
							score=100000;
							break;
					}
					tempy=j-count-1;
					if(MAP[i][j][0]==0) {
						if(tempy>=0&&MAP[i][tempy][0]==0) {
							System.out.println(i+","+j+","+tempy+","+score+"----");
							if(MAP[i][j][1]>1)MAP[i][j][1]*=score;
							else MAP[i][j][1]+=score;
							System.out.println("Here!!\n\n"+score);
							if(MAP[i][tempy][1]>1) {
								MAP[i][tempy][1]*=score;
							}
							else {
								System.out.println(MAP[i][tempy][1]+"2222"+score);
								MAP[i][tempy][1]+=score;
								System.out.println(MAP[i][tempy][1]+" "+i+" "+tempy);
							}
						}
						else if(tempy<0||MAP[i][tempy][0]!=0) {
							if(MAP[i][j][1]>1)MAP[i][j][1]*=score/2;
							else MAP[i][j][1]+=score/2;
						}
					}
					else if(tempy>=0&&MAP[i][tempy][0]==0) {
						//System.out.println(MAP[i][tempy][1]+" "+i+" "+tempy);
						if(MAP[i][tempy][1]>1)MAP[i][tempy][1]*=score/2;
						else MAP[i][tempy][1]+=score/2;
					}
					score=0;
					count=0;
				}
			}
		}
		//System.out.println(MAP[9][8][1]+"   1");
		for(int i=0;i<size;i++) {
			count=0;
			for(int j=0;j<size;j++) {
				if(MAP[j][i][0]==plyr)count++;
				else {
					if(count==0)continue;
					else if(j+1<size&&MAP[j+1][i][0]==plyr)count++;
						switch(count) {
							case 1:
								score=1;
								break;
							case 2:
								score=5;
								break;
							case 3:
								score=60;
								break;
							case 4:
								score=100000;
								break;
						}
						tempx=j-count-1;
						count=0;
						if(MAP[j][i][0]==0) {
							if(tempx>=0&&MAP[tempx][i][0]==0) {
								System.out.println(i+","+j+","+tempx+","+score+","+"|||");
								if(MAP[j][i][1]>1)MAP[j][i][1]*=score;
								else MAP[j][i][1]+=score;
								if(MAP[tempx][i][1]>1)MAP[tempx][i][1]*=score;
								else MAP[tempx][i][1]+=score;
							}
							else if(tempx>=0&&MAP[tempx][i][0]!=0) {//durl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								if(MAP[j][i][1]>1)MAP[j][i][1]*=score/2;
								else MAP[j][i][1]+=score/2;
							}
							else if(tempx<0||MAP[tempx][i][0]!=0) {
								if(MAP[j][i][1]>1)MAP[j][i][1]*=score/2;
								else MAP[j][i][1]+=score/2;
							}
						}
						else if(tempx>=0&&MAP[tempx][i][0]==0) {
							if(MAP[tempx][i][1]>1)MAP[tempx][i][1]*=score/2;
							else MAP[tempx][i][1]+=score/2;
						}
						score=0;
						count=0;
				}
			}
		}
		//System.out.println(MAP[9][8][1]+"   2");
		for(int i=0; i<size-4;i++) {//'\'대각선 
			count=0;
			for(int j=0; j<size-4;j++) {
				tempx=i;
				tempy=j;
				if(tempx-1>=0&&tempy-1>=0&&MAP[tempx-1][tempy-1][0]==MAP[tempx][tempy][0]) {
					continue;
				}
				for(int k=0;k<5;k++) {
					if(MAP[tempx][tempy][0]==plyr) {
						count++;tempx++;tempy++;
					}
					else {
						if(count==0) break;
						else if(tempx+1<size&&tempy+1<size&&MAP[tempx+1][tempy+1][0]==plyr)count++;
						switch(count) {
							case 1:
								score=1;
								break;
							case 2:
								score=5;
								break;
							case 3:
								score=60;
								break;
							case 4:
								score=100000;
								break;
						}
						rev_tx=tempx-count-1;
						rev_ty=tempy-count-1;
		
						if(tempx<size&&tempy<size&&MAP[tempx][tempy][0]==0) {
							//System.out.println("1"+"("+tempx+","+tempy+")");
							if(rev_tx>=0&&rev_ty>=0&&MAP[rev_tx][rev_ty][0]==0) {//양 옆이 모두 둘 수 있을 때
								//System.out.println("2"+"("+tempx+","+tempy+")");
								if(MAP[tempx][tempy][1]>1)MAP[tempx][tempy][1]*=score;
								else MAP[tempx][tempy][1]+=score;
								if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score;
								else MAP[rev_tx][rev_ty][1]+=score;
							}
							else if(rev_tx>=0&&rev_ty>=0&&MAP[rev_tx][rev_ty][0]!=0) {
								//System.out.println("3"+"("+tempx+","+tempy+")");
								if(MAP[tempx][tempy][1]>1) MAP[tempx][tempy][1]*=score/2;
								
								else MAP[tempx][tempy][1]+=score/2;
							}
						}
						else if(rev_ty>=0&&rev_tx>=0&&MAP[rev_tx][rev_ty][0]==0) {
							//System.out.println("4"+"("+tempx+","+tempy+")");
							if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score/2;
							else MAP[rev_tx][rev_ty][1]+=score/2;
						}
						score=0;
						count=0;
					}
				}
				count=0;
			}
		}
		//System.out.println(MAP[9][8][1]+"   3");
		for(int i=0; i<size-4;i++) {// '/'대각선 확인 
			count=0;
			for(int j=4; j<size;j++) {
				tempx=i;
				tempy=j;
				if(tempx-1>=0&&tempy+1<size&&MAP[tempx-1][tempy+1][0]==MAP[tempx][tempy][0]) {
					continue;
				}
				for(int k=0;k<5;k++) {
					if(MAP[tempx][tempy][0]==plyr) {
						count++;tempx++;tempy--;
					}
					else {
						if(count==0)break;
						else if(tempx+1<size&&tempy-1>=0&&MAP[tempx+1][tempy-1][0]==plyr)count++;
						switch(count) {
							case 1:
								score=1;
								break;
							case 2:
								score=5;
								break;
							case 3:
								score=60;
								break;
							case 4:
								score=100000;
								break;
						}
						rev_tx=tempx-count-1;
						rev_ty=tempy+count+1;
						if(tempx<size&&tempy>=0&&MAP[tempx][tempy][0]==0) {
							if(rev_tx>=0&&rev_ty<size&&MAP[rev_tx][rev_ty][0]==0) {
								if(MAP[tempx][tempy][1]>1)MAP[tempx][tempy][1]*=score;
								else MAP[tempx][tempy][1]+=score;
								if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score;
								else MAP[rev_tx][rev_ty][1]+=score;
							}
							else if(rev_tx>=0&&rev_ty<size&&MAP[rev_tx][rev_ty][0]!=0) {
								if(MAP[tempx][tempy][1]>1)MAP[tempx][tempy][1]*=score/2;
								else MAP[tempx][tempy][1]+=score/2;
							}
						}
						else if(rev_ty<size&&rev_tx>=0&&MAP[rev_tx][rev_ty][0]==0) {
							if(MAP[rev_tx][rev_ty][1]>1)MAP[rev_tx][rev_ty][1]*=score/2;
							else MAP[rev_tx][rev_ty][1]+=score/2;
						}
						score=0;
						count=0;
					}
				}
				count=0;
			}
		}
	}
}
