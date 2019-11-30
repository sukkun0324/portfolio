package omok;

import java.util.Scanner;

import javax.swing.JFrame;

import java.util.InputMismatchException;

public class Game {
	static int size;
	static int restartgame;
	static int gameset;
	public static int omok_map[][][];
	public static int state = 0;

	// static OFrame hunpago = new OFrame();
	// static TimerThread tt = new TimerThread(hunpago.getTime());
	public Game() {
		restartgame = 0;
		int[] comloc;
		String src = MakeFile.filenum();
		System.out.println(src);
		// System.out.println("error!");
		OFrame hunpago = new OFrame();
		TimerThread tt = new TimerThread(hunpago.getTime());
		G_map Visuomok = new G_map(hunpago.size);
		Visuomok.Ginit(hunpago.size);
		new Game(hunpago.size);
		size = hunpago.size;
		if (hunpago.mode == 1) {
			hunpago.setX(hunpago.size / 2);
			hunpago.setY(hunpago.size / 2);
			hunpago.com_down();
			omok_map[size / 2][size / 2][0] = 2;
			omok_map[size / 2][size / 2][1] = -2;
			Visuomok.get_down_B(size / 2, size / 2);
			hunpago.oneshot = true;
		}

		map.VM_print(hunpago.size);
		System.out.println("=======================================");
		screen_dist(omok_map, hunpago.size);

		while (true) {
			while (restartgame == 0) {
				OFrame.getvictory().setText("플레이어 TURN!!");
				tt.run();
				if (restartgame == 1) {
					restartgame = 0;
					return;
				}
				if (hunpago.player == 2) {
					System.out.println("시간을 초과하여 패배하셨습니다!");
					System.out.println("게임이 종료됩니다!");
					hunpago.ttt.setText("게임을 종료해 주세요!!");
					gameset = 1;
					return;
				}
				if (state == 1) {
					break;
				}
			}
			if (restartgame == 1) {
				restartgame = 0;
				return;
			}
			state = 0;
			G_map.VM_print(size);
			MakeFile.MakeKibo(G_map.VM, size, src, hunpago.mode);
			screen_dist(omok_map, size);
			if (map.victory_cond(omok_map, 1, size) == 1) {
				System.out.println("플레이어가 이겼습니다!");
				OFrame.getvictory().setText("플레이어가 이겼습니다!!");
				hunpago.ttt.setText("게임을 종료해 주세요!!");
				gameset = 1;
				return;
			}
			if (map.is_draw(omok_map, size) == 1) {
				System.out.println("게임이 종료됩니다!");
				OFrame.getvictory().setText(" 비겼습니다!!");
				hunpago.ttt.setText("게임을 종료해 주세요!!");
				gameset = 1;
				return;
			}
			System.out.println("=======================================");
			System.out.println("컴퓨터가 두는 중입니다!");
			OFrame.getvictory().setText("컴퓨터가 두는 중입니다!!");
			System.out.println("=======================================");
			Com.check_score(omok_map, 2, size);
			map.print_map2(omok_map, size);
			Com.blocking_plyr(omok_map, 1, size);
			map.print_map2(omok_map, size);
			comloc = Com.com(omok_map, size, hunpago.mode);
			hunpago.setX(comloc[1]);
			hunpago.setY(comloc[0]);
			System.out.println(comloc[0] + "," + comloc[1]);
			hunpago.com_down();
			hunpago.oneshot = true;
			Visuomok.VM_print(size);
			MakeFile.MakeKibo(G_map.VM, size, src, hunpago.mode);
			screen_dist(omok_map, size);
			if (map.victory_cond(omok_map, 2, size) == 1) {
				System.out.println("컴퓨터가 이겼습니다!");
				OFrame.getvictory().setText("컴퓨터가 이겼습니다!");
				hunpago.ttt.setText("게임을 종료해 주세요!!");
				gameset = 1;
				return;
			}
			if (map.is_draw(omok_map, size) == 1) {
				System.out.println("게임이 종료됩니다!");
				OFrame.getvictory().setText(" 비겼습니다!!");
				hunpago.ttt.setText("게임을 종료해 주세요!!");
				gameset = 1;
				return;
			}
			map.init_score_map(omok_map, size);
		}
	}

	public Game(int size) {
		omok_map = new int[size][size][2];
	}

	static void screen_dist(int MAP[][][], int size) {
		int i;
		for (i = 0; i < size; i++)
			System.out.print("# ");
		System.out.println("");
		for (i = 0; i < size; i++)
			System.out.print("C ");
		System.out.println("");
		for (i = 0; i < size; i++)
			System.out.print(i / 10 + " ");
		System.out.println("");
		for (i = 0; i < size; i++)
			System.out.print(i % 10 + " ");
		System.out.println("");
	}

	public static void main(String[] args) {
		restartgame = 0;
		gameset = 0;
		while (true) {
			new Game();
			if (gameset == 1)
				break;
		}
	}
}
