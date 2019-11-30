package omok;

import java.io.*;

public class MakeFile {
	static String filenum() {
		File[] f_list = new File("kibo//").listFiles(); // 폴더들 위치
		System.out.println("총 " + f_list.length + " 개의 폴더가 존재합니다. ");
		String src = "kibo/" + (f_list.length + 1) + ".txt";
		return src;
	}

	static void MakeKibo(char VM[][], int size, String src,int mode) {
		char a = '\n';
		char space=' ';
		char stoneb='●';
		char stonew='○';
		String setvalue;
		try {
			System.out.println("dddd");
			BufferedWriter fout = new BufferedWriter(new FileWriter(src));
			if(mode==0)
				setvalue = "오목판의 사이즈: " + size + "*" + size + "\n"+"플레이어: "+stoneb+a+"훈파고: "+stonew+ "\n";
			else
				setvalue = "오목판의 사이즈: " + size + "*" + size + "\n"+"플레이어: "+stonew+a+"훈파고: "+stoneb+ "\n";
			fout.write(setvalue);
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					fout.write(VM[i][j]);fout.write(space);
				}
				fout.write(a);
			}
			fout.close();
		} catch (IOException e) {
		}
	}
}