package omok;

import java.awt.*;
import javax.swing.*;

class TimerThread extends Thread {
	JLabel timerLabel; // 타이머 값이 출력되는 레이블
	public TimerThread(JLabel timerLabel) {
	this.timerLabel = timerLabel;
	}
// 스레드 코드. run()이 종료하면 스레드 종료
	public void run() {
	int n=OFrame.time_f; // 타이머 카운트 값
	while(n>=0) {
		timerLabel.setText("남은 시간:"+Integer.toString(n)+"초");
		n--; 
		if(OFrame.player==1){
			OFrame.player=0;
			break;}
		if(Game.restartgame==1){
			return;}
		if(n==-1) {
			timerLabel.setText("시간 종료! 패배하셨습니다!");
			OFrame.player=2;
			return;
		}
		try {
			Thread.sleep(1000); // 1초동안 잠을 잔다.
		}
		catch(InterruptedException e) {return ;}
		}
	}
}