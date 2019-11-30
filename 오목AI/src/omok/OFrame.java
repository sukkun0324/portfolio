package omok;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class OFrame extends JFrame {
	static String[] options = { "흑돌", "백돌" };
	static String[] options_time = { "20초", "30초", "40초" };
	static String[] options_size = { "19x19", "15x15", "10x10" };
	static int mode = JOptionPane.showOptionDialog(null, "돌을 선택해 주세요(흑 선)", "환영합니다! 훈파고 오목!",
			JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, options, options[0]);
	static int time_n = JOptionPane.showOptionDialog(null, "시간을 선택해 주세요", "환영합니다! 훈파고 오목!", JOptionPane.DEFAULT_OPTION,
			JOptionPane.INFORMATION_MESSAGE, null, options_time, options_time[0]);
	static int size_n = JOptionPane.showOptionDialog(null, "사이즈를 선택해 주세요(19x19권장)", "환영합니다! 훈파고 오목!",
			JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, options_size, options_size[0]);
	// new Game(size_n);
	int x, y;
	static int size;
	{
		if (size_n == 0)
			size = 19;
		else if (size_n == 1)
			size = 15;
		else
			size = 10;
	}
	static int time_f;
	{
		if (time_n == 0)
			time_f = 20;
		else if (time_n == 1)
			time_f = 30;
		else
			time_f = 40;
	}
	static int player = 0;
	Player pl = new Player();
	JLabel tmp;
	JLabel ttt = new JLabel();
	public static JLabel victory = new JLabel();
	private JLabel time = new JLabel("00:00.00");
	static boolean oneshot = true;

	ImageIcon img;
	{
		if (size_n == 0)
			img = new ImageIcon("image//pan.gif");
		else if (size_n == 1)
			img = new ImageIcon("image//pan15x15.png");
		else
			img = new ImageIcon("image//pan10x10.png");
	}
	ImageIcon bdoll = new ImageIcon("image//black.gif");
	ImageIcon wdoll = new ImageIcon("image//white.gif");

	private JButton ret = new JButton("착수");
	private JButton rem = new JButton("지움");

	// Panel 레이아웃 설정이 가능한 가상의 투명한 공간
	private JPanel p = new JPanel();
	private JLabel mainback = new JLabel(img);

	JPanel background = new JPanel() {
		public void paintComponent(Graphics g) {
			g.drawImage(img.getImage(), 0, 0, null);
			setOpaque(false); // 그림을 표시하게 설정,투명하게 조절
			super.paintComponent(g);
		}
	};

	// 레이아웃
	private BorderLayout border = new BorderLayout();

	// 이벤트 리스너
	private ActionListener exitListener = new ActionListener() {
		public void actionPerformed(ActionEvent event) {
			System.exit(0);// 현재 프로그램을 종료
			// dispose();//현재 창을 종료
			// setVisible(false);//현재 창을 숨김(프로그램 종료 안됨)
		}
	};

	// main에 하던 설정들을 생성자에서 진행
	public OFrame() {
		this.display();// 화면 구성 관련 처리
		this.event();// 이벤트 관련 처리
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setTitle("HunpaGo_OMOK");
		this.createMenu();// 메뉴 관련 처리
		this.setSize(1000, 800);
		this.setLocation(100, 100);
		this.setResizable(false);
		this.setVisible(true);
	}

	public static JLabel getvictory() {
		return victory;
	}

	private void display() {
		ret.setBounds(900, 25, 75, 75);
		this.add(ret);
		time.setBounds(800, 250, 150, 150);
		victory.setText("플레이어 TURN!!");
		this.add(victory);
		this.add(ttt);
		ttt.setBounds(850, 600, 200, 200);
		victory.setBounds(850, 500, 200, 200);
		background.add(time);
		this.add(background);
		rem.setBounds(900, 125, 75, 75);
		this.add(rem);
		background.setLayout(null);
		this.add(background);
	}

	private void createMenu() {
		JMenuBar mb = new JMenuBar();
		JMenu screenMenu = new JMenu("Menu");
		JMenuItem e2 = new JMenuItem("Exit");
		e2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				System.out.println("exit");
				System.exit(0);
			}

		});
		JMenuItem e1 = new JMenuItem("RESTART");
		e1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				System.out.println("restart");
				repaint2();
				Game.restartgame = 1;

			}

		});
		screenMenu.add(e1);
		screenMenu.addSeparator();
		screenMenu.add(e2);

		mb.add(screenMenu);
		setJMenuBar(mb);
	}

	private void event() {
		// 1회용으로 연결 설정
		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				if (oneshot && mode == 0) {
					x = e.getX() - 25;
					y = e.getY() - 70;
					// setTitle("mousePressed("+x+","+y+")");
					System.out.println("x = " + x + " y = " + y);
					JLabel bkstone = new JLabel(bdoll);
					tmp = bkstone;
					x = fix_loc(x);
					y = fix_loc(y);
					bkstone.setBounds(x, y, 50, 50);
					background.add(bkstone);
					repaint1();
					oneshot = false;
					x = x / 38;
					y = y / 38;
				}
				if (oneshot && mode == 1) {
					x = e.getX() - 25;
					y = e.getY() - 50;
					setTitle("mousePressed(" + x + "," + y + ")");
					System.out.println("x = " + x + " y = " + y);
					JLabel wtstone = new JLabel(wdoll);
					tmp = wtstone;
					x = fix_loc(x);
					y = fix_loc(y);
					wtstone.setBounds(x, y, 50, 50);
					background.add(wtstone);
					repaint1();
					oneshot = false;
					x = x / 38;
					y = y / 38;
				}
			}

		});

		ret.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				System.out.println("착수");
				tmp = null;
				System.out.println(player);
				player = pl.player(y, x, size, mode);
				Game.state = 1;
				player = 1;
			}

		});

		rem.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				if (tmp != null) {
					System.out.println("지움");
					oneshot = true;
					background.remove(tmp);
					tmp = null;
					repaint1();
				}
			}

		});
	}

	public void repaint1() {

		this.invalidate();
		this.validate();
		this.repaint();

	}

	public void repaint2() {

		this.invalidate();
		this.validate();

	}

	private int fix_loc(int x) {
		int fix_x = 0;
		if (x >= -5 && x < 23)
			fix_x = 4;// 0
		else if (x >= 23 && x < 61)
			fix_x = 42;// 1
		else if (x >= 61 && x < 99)
			fix_x = 80;// 2
		else if (x >= 99 && x < 137)
			fix_x = 118;// 3
		else if (x >= 137 && x < 175)
			fix_x = 156;// 4
		else if (x >= 175 && x < 213)
			fix_x = 194;// 5
		else if (x >= 213 && x < 251)
			fix_x = 232;// 6
		else if (x >= 251 && x < 289)
			fix_x = 270;// 7
		else if (x >= 289 && x < 327)
			fix_x = 308;// 8
		else if (x >= 327 && x < 365)
			fix_x = 346;// 9
		else if (x >= 365 && x < 403 && size_n != 2)
			fix_x = 384;// 10
		else if (x >= 403 && x < 441 && size_n != 2)
			fix_x = 422;// 11
		else if (x >= 441 && x < 479 && size_n != 2)
			fix_x = 460;// 12
		else if (x >= 479 && x < 517 && size_n != 2)
			fix_x = 498;// 13
		else if (x >= 517 && x < 555 && size_n != 2)
			fix_x = 536;// 14
		else if (x >= 555 && x < 593 && size_n == 0)
			fix_x = 574;// 15
		else if (x >= 593 && x < 631 && size_n == 0)
			fix_x = 612;// 16
		else if (x >= 631 && x < 669 && size_n == 0)
			fix_x = 650;// 17
		else if (x >= 669 && x < 700 && size_n == 0)
			fix_x = 688;// 18

		return fix_x;
	}

	public int backtothematrix(int x) {
		return x / 38;
	}

	private int com_loc(int x) {
		return 4 + (x * 38);
	}

	public int getX() {
		return x / 38;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y / 38;
	}

	public void setY(int y) {
		this.y = y;
	}

	public void getsize() {
		String inputsize = JOptionPane.showInputDialog(this, "입력다이얼로그박스", "입력", JOptionPane.YES_NO_OPTION);

	}

	public int getPlayer() {
		return player;
	}

	public void com_down() {
		if (mode == 0) {
			JLabel wtstone = new JLabel(wdoll);
			x = com_loc(x);
			y = com_loc(y);
			wtstone.setBounds(x, y, 50, 50);
			background.add(wtstone);
			repaint1();
		} else if (mode == 1) {
			JLabel bkstone = new JLabel(bdoll);
			x = com_loc(x);
			y = com_loc(y);
			bkstone.setBounds(x, y, 50, 50);
			background.add(bkstone);
			repaint1();
		}
	}

	public JLabel getTime() {
		return time;
	}
}
