import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;

public class Game extends JPanel implements KeyListener,ActionListener {
	int left_xpos=5;
	int left_ypos=200;
	int right_xpos=790;
	int right_ypos=200;
	int ballx=390;
	int bally=230;
	int dirx=-1;
	int diry=-1;
	int player_one=0;
	int player_two=0;	
	boolean kontrolet=false;
	boolean kontroletx=false;
		
	Timer timer =new Timer(9,this);
	
	
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		ballx+=dirx;
		bally+=diry;
		
		if(ballx+8==right_xpos && bally-15*dirx<=right_ypos+100 && bally+15*dirx>=right_ypos ) {
			dirx*=-1;
		}
		else if(ballx==left_xpos && bally<=left_ypos+100 && bally>=left_ypos ) {
			dirx*=-1;
		}
		if(bally+20==500) {
			diry*=-1;
		}
		
		else if (bally==0) {
			
			diry*=-1;
		}
		else if(ballx==800) {
			left_xpos=5;
			left_ypos=200;
			right_xpos=790;
			right_ypos=200;
		    ballx=390;
			bally=230;
			dirx*=-1;
			diry*=-1;
			player_one+=1;
		}
		else if(ballx==-20) {
			left_xpos=5;
			left_ypos=200;
			right_xpos=790;
			right_ypos=200;
		    ballx=390;
			bally=230;
			dirx*=-1;
			diry*=-1;
			player_two+=1;
		}
		if(player_one==5) {
			
			kontrolet=true;
		}
		 if (player_two==5) {
			kontroletx=true;
		}
		
		repaint();
	}
	
	public Game() {
		
		setBackground(Color.black);
	
		
		timer.start();
	}

	@Override
	public void repaint() {
		// TODO Auto-generated method stub
		super.repaint();
		
		
	}

	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		super.paint(g);
		
		g.setColor(Color.yellow);
		g.fillOval(ballx, bally, 10, 10);

		g.setColor(Color.BLUE);
		g.fillRect(left_xpos, left_ypos, 5, 100);
		
		g.setColor(Color.red);
		g.fillRect(right_xpos, right_ypos, 5, 100);
		
		
		g.drawString("Player One - "+player_one+"", 100, 20);
		
		g.drawString("Player Two - "+player_two+"",600, 20);
		if(kontrolet==true) {
			
			timer.stop();
			
			String message="Player One Kazandı";
			
			JOptionPane.showMessageDialog(this, message);
			System.exit(0);
		}
		else if(kontroletx==true) {
			
			timer.stop();
			
			String message="Player two Kazandı";
			
			JOptionPane.showMessageDialog(this, message);
			System.exit(0);
		}
		
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
		
		
	}

	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		int c=e.getKeyCode();
		if(c==KeyEvent.VK_W) {
			if(left_ypos>0) {
				
				left_ypos-=15;
			}
		}
		else if(c==KeyEvent.VK_S) {
			if(left_ypos+100<500) {
				
				left_ypos+=15;
			}
		}
		else if(c==KeyEvent.VK_UP) {
			if(right_ypos>0) {
				
				right_ypos-=15;
			}
		}
		else if(c==KeyEvent.VK_DOWN) {
			if(right_ypos+100<500) {
				
				right_ypos+=15;
			}
		}
		

	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

}
