package pratice;



import java.awt.BorderLayout;
import java.awt.Color;
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
import javax.swing.JPanel;

public class MingaFrame extends JFrame{

	int x,y;
	
	 private JButton[] doll = new JButton[19*19];
	    
	    ImageIcon img = new ImageIcon("src//pan.gif");
	    ImageIcon bdoll = new ImageIcon("src//black.gif");
	    ImageIcon wdoll = new ImageIcon("src//white.gif");
	    
	    
	    //Panel        레이아웃 설정이 가능한 가상의 투명한 공간
	    private JPanel p = new JPanel();
	    private JLabel mainback = new JLabel(img);
	    
	    JPanel background = new JPanel() {
            public void paintComponent(Graphics g) {
                g.drawImage(img.getImage(), 0, 0, null);
                setOpaque(false); //그림을 표시하게 설정,투명하게 조절
                super.paintComponent(g);
            }
        };
	    
	    //레이아웃
	    private BorderLayout border = new BorderLayout();
	    
	    
	    //이벤트 리스너
	    private ActionListener exitListener = new ActionListener() {
	        public void actionPerformed(ActionEvent event) {
	            System.exit(0);//현재 프로그램을 종료
//	            dispose();//현재 창을 종료
//	            setVisible(false);//현재 창을 숨김(프로그램 종료 안됨)
	        }
	    };
	    
	    //main에 하던 설정들을 생성자에서 진행
	    public MingaFrame() {
	        this.display();//화면 구성 관련 처리
	        this.event();//이벤트 관련 처리
	        this.menu();//메뉴 관련 처리
	        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        this.setTitle("GUI테스트");
	        this.setSize(1000, 770);
	        this.setLocation(100, 100);
	        this.setResizable(false);
	        this.setVisible(true);
	    }
	 
	    private void display() {
	        background.setLayout(null);
	        background.setLayout(null);
	        this.add(background);
	        
	    }
	 
	    private void event() {
	        //1회용으로 연결 설정
	    	this.addMouseListener(new MouseAdapter() {
	    		public void mousePressed(MouseEvent e) {
	    			x = e.getX()-25;
	    			y = e.getY()-50;
	    			setTitle("mousePressed("+x+","+y+")");
	    			System.out.println("x = "+x+" y = "+y);
	    			JLabel bkstone = new JLabel(bdoll);
	    			JLabel wtstone = new JLabel(wdoll);
//	    			JButton doll = new JButton(bdoll);
	    			x=fix_loc(x);
	    			y=fix_loc(y);
	    			bkstone.setBounds(x, y, 50, 50);
	    			background.add(bkstone);
	    			repaint1();
	    		}
	    		
	    		});
	        
	    }
	    
	    public void repaint1() {
	    		
	    	this.invalidate();
	    	this.validate();
	    	this.repaint();
	    	
	    }
	 
	    private void menu() {
	        
	    }
	    private int fix_loc(int x) {
	    		int fix_x=0;
	    		if(x>=-5&&x<23)fix_x=4;
	    		else if(x>=23&&x<61)fix_x=42;
	    		else if(x>=61&&x<99)fix_x=80;
	    		else if(x>=99&&x<137)fix_x=118;
	    		else if(x>=137&&x<175)fix_x=156;
	    		else if(x>=175&&x<213)fix_x=194;
	    		else if(x>=213&&x<251)fix_x=232;
	    		else if(x>=251&&x<289)fix_x=270;
	    		else if(x>=289&&x<327)fix_x=308;
	    		else if(x>=327&&x<365)fix_x=346;
	    		else if(x>=365&&x<403)fix_x=384;
	    		else if(x>=403&&x<441)fix_x=422;
	    		else if(x>=441&&x<479)fix_x=460;
	    		else if(x>=479&&x<517)fix_x=498;
	    		else if(x>=517&&x<555)fix_x=536;
	    		else if(x>=555&&x<593)fix_x=574;
	    		else if(x>=593&&x<631)fix_x=612;
	    		else if(x>=631&&x<669)fix_x=650;
	    		else if(x>=669&&x<700)fix_x=688;
	    		
			return fix_x;
	    }
	    
	    
	    public static void main(String[] args) {
	    		MingaFrame minga = new MingaFrame();
	    }
	
}


