#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include <sstream>

using namespace sf;
using namespace std;

bool open = true, close = false;
const int H = 23;
const int/* W = 60*/W = 32;
float ofset_x = 0, ofset_y = 0; // �������� ������
unsigned int levlnumber = 1;

struct
{
	float dx = 0, dy = 0, bdx = 0, bdy = 0, bbdx = 0, bbdy = 0;
	FloatRect rect, brect, bbrect;
	bool colision = false, bbcolision = false;
	unsigned int ba = 0, bba = 0, levlnumber = 1;

	bool *mblife = new bool[levlnumber];
	bool *mbblife = new bool[levlnumber];
	bool *mcolision = new bool[levlnumber];
	bool *mbbcolision = new bool[levlnumber];

	unsigned int *mba = new unsigned int[levlnumber];
	unsigned int *mbba = new unsigned int[levlnumber];

	FloatRect *mbrect = new FloatRect[levlnumber];
	FloatRect *mbbrect = new FloatRect[levlnumber];

	float *mbdx = new float[levlnumber];
	float *mbdy = new float[levlnumber];
	float *mbbdx = new float[levlnumber];
	float *mbbdy = new float[levlnumber];

	bool plife = true, gamemode = false, blife = true, bblife = true, close = false, mod = true;
	String Map[H]
	{
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"B                   B          B",
		"B  B   BBBBBBBBBBB  B  BBBBBBBBB",
		"B  B           C              BB",
		"B  B   BB  BBBBB  BB  B  BB    B",
		"B      B          B       B B  B",
		"B      B  B  BB      BBB  B    B",
		"B      B  B   B        B       B",
		"B  B   B  BB  B        B       B",
		"B  B   B  B   BBBBBBBBBB    B  B",
		"B      BB     B                B",
		"B      B         B             B",
		"B      B  BBBBB  BBBB  B  B BBBB",
		"B      B   B        B  B  B    B",
		"B      B B   B      B     B B  B",
		"B      B BB  BBB    BBBBBBBC   B",
		"B  C   B     B                 B",
		"B      BBBB  BBBB  BBBBBBBBB   B",
		"B                       BBBBB  B",
		"B                        B     B",
		"B  BBBBBBBBBB  BBBBBBB   B     B",
		"B                        B     B",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	};

	String iMap[H]
	{
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"B                   B          B",
		"B  B   BBBBBBBBBBB  B  BBBBBBBBB",
		"B  B           C              BB",
		"B  B   BB  BBBBB  BB  B  BB    B",
		"B      B          B       B B  B",
		"B      B  B  BB      BBB  B    B",
		"B      B  B   B        B       B",
		"B  B   B  BB  B        B       B",
		"B  B   B  B   BBBBBBBBBB    B  B",
		"B      BB     B                B",
		"B      B         B             B",
		"B      B  BBBBB  BBBB  B  B BBBB",
		"B      B   B        B  B  B    B",
		"B      B B   B      B     B B  B",
		"B      B BB  BBB    BBBBBBBC   B",
		"B  C   B     B                 B",
		"B      BBBB  BBBB  BBBBBBBBB   B",
		"B                       BBBBB  B",
		"B                        B     B",
		"B  BBBBBBBBBB  BBBBBBB   B     B",
		"B                        B     B",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	};

	int  dot = 469;
	unsigned int schet = 0;
	Clock C; // ����� ������ ����

}Ps;

void nool()
{
	ofset_x = 0; ofset_y = 0;

	for (int i = 0; i < levlnumber; i++)
	{
		Ps.mbbcolision[i] = false;
		Ps.mcolision[i] = false;
		Ps.mbblife[i] = true;
		Ps.mblife[i] = true;
		Ps.mba[i] = 0;
		Ps.mbba[i] = 0;
		Ps.mbdx[i] = 0;
		Ps.mbdy[i] = 0;
		Ps.mbbdx[i] = 0;
		Ps.mbbdy[i] = 0;

	}
	Ps.dx = 0; Ps.dy = 0; Ps.bdx = 0; Ps.bdy = 0;
	Ps.colision = false;
	Ps.bba = Ps.ba = 0;
	Ps.plife = true; Ps.gamemode = false; Ps.blife = true; Ps.close = false; Ps.mod = true; Ps.bblife = true;

	for (int i = 0; i <= H; i++)
		for (int j = 0; j <= W; j++)
			Ps.Map[i][j] = Ps.iMap[i][j];
} // ��������� ����������

void menu()
{
	if (open == true)
	{
		sf::RenderWindow windows(sf::VideoMode(1300, 700), "Pacman");
		while (windows.isOpen()) //��������� �������� ���� 
		{
			sf::Event event;
			while (windows.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					windows.close();
			}

			windows.clear();

			Texture w1;
			w1.loadFromFile("tityl.png");
			Sprite tityl;
			tityl.setTexture(w1);
			tityl.setTextureRect(IntRect(0, 0, 1300, 700));
			tityl.setPosition(0, 0);
			windows.draw(tityl);

			Texture w2;
			w2.loadFromFile("������.png");
			Sprite game;
			game.setTexture(w2);
			game.setTextureRect(IntRect(0, 0, 300, 50));
			game.setPosition(900, 400);
			windows.draw(game);

			Texture w3;
			w3.loadFromFile("�����.png");
			Sprite end;
			end.setTexture(w3);
			end.setTextureRect(IntRect(0, 0, 300, 50));
			end.setPosition(900, 450);
			windows.draw(end);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int x = Mouse::getPosition(windows).x;
				int y = Mouse::getPosition(windows).y;
				if (x > 899 && x < 1201 && y > 399 && y < 451) open = false;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int x = Mouse::getPosition(windows).x;
				int y = Mouse::getPosition(windows).y;
				if (x > 899 && x < 1201 && y > 449 && y < 501) close = true; 
			}

			windows.display();
			if (open == false || close == true)
				windows.close();
		}
	}
}




class mapp
{
public:

	void show(RenderWindow &window)
	{
		Texture st;
		st.loadFromFile("�����.png");
		Sprite stena;
		stena.setTexture(st);

		Texture r;
		r.loadFromFile("�����.png");
		Sprite dot;
		dot.setTexture(r);
		dot.setPosition (-320 - ofset_x, -320 - ofset_y);

		Texture r1;
		r1.loadFromFile("A.png");
		Sprite d;
		d.setTexture(r1);
		d.setPosition(-320 - ofset_x, -320 - ofset_y);

		RectangleShape recrangle;
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (Ps.Map[i][j] == 'A') recrangle.setFillColor(Color::Blue);	// �������
				if (Ps.Map[i][j] == 'C') { d.setPosition(j * 32 - ofset_x, i * 32 - ofset_y); }	 // ���
				if (Ps.Map[i][j] == 'B') stena.setPosition(j*32 - ofset_x, i*32 - ofset_y);		// �����
				if (Ps.Map[i][j] == ' ') { dot.setPosition(j * 32 - ofset_x, i * 32 - ofset_y); }	// �����
				else
				{
					recrangle.setSize(Vector2f(32, 32));
					recrangle.setPosition(Vector2f(j * 32 - ofset_x, i * 32 - ofset_y));
					window.draw(d);
					window.draw(recrangle);
					window.draw(stena);
				}
				window.draw(dot);
			}
	}

	void win(RenderWindow &window)
	{
		Texture f1;
		f1.loadFromFile("yoy_win.png");
		Sprite sp;
		sp.setTexture(f1);
		sp.setPosition(700, 300);
		window.draw(sp);
	}

	void NewLvL(RenderWindow &window)
	{
		Texture f2;
		f2.loadFromFile("new_lvl.png");
		Sprite ds;
		ds.setTexture(f2);
		ds.setPosition(400, 250);
		window.draw(ds);
	}
};

class Abs
{
public:
	virtual void move() = 0;
	virtual void pcolision(int dir) = 0;
	virtual void bcolision(int dir) = 0;
	virtual void bbcolision (int dir) = 0;
	virtual void volume() = 0;
};

class bot
{
public:
	Texture t2;
	Sprite sprite;

	bot()
	{
		t2.loadFromFile("1.png");

		
		{
			sprite.setTexture(t2);
			sprite.setTextureRect(IntRect(0, 0, 32, 32));

			sprite.setPosition(460, 320);
			Ps.brect = FloatRect(500, 340, -32, -32); // ��������� ���������� 
		}
	}

	void show(RenderWindow &window)
	{
	//	for (int i = 0; i < levlnumber; i++)
		{
	//		std::cout << levlnumber << "   " << i  << msprite[i].getPosition().x << endl;

			window.draw(sprite);
		}
	}

	/*void set(int x, int y)
	{
		Texture b;
		b.loadFromFile("2.png");
		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		Ps.brect = FloatRect(x, y, 32, 32);
		sprite.setPosition(x, y);
	}
	*/
	void update(int time, Abs* del)
	{
		for (int i = 0; i < levlnumber; i++)
		{
			if (Ps.blife == true)
			{
				if (Ps.colision == true) // ���� ��������� ������������
				{
					Ps.bdx = 0; //
					Ps.bdy = 0; // ���������� �������� ����
					Ps.ba = rand() % 4; // �������� ����� �����������
					Ps.colision = false; // ��������� �������
				}

				if (Ps.ba == 0)
				{
					Ps.bdx = 0.5*time; // std::cout << "�������� ������" << endl;
				} // �������� ������

				if (Ps.ba == 1)
				{
					Ps.bdx = -0.5*time;// std::cout << "�������� �����" << endl; 
				} // �������� �����

				if (Ps.ba == 2)
				{
					Ps.bdy = 0.5*time; // std::cout << "�������� ������" << endl;
				} // �������� ������

				if (Ps.ba == 3)
				{
					Ps.bdy = -0.5*time; //std::cout << "�������� �����" << endl;
				} // �������� �����

				del->bcolision(0); // �� �
				del->bcolision(1); // �������� ������������

				if (Ps.colision == false && Ps.bdx != 0) Ps.brect.left += Ps.bdx *0.1; // ���������� �� �
				if (Ps.colision == false && Ps.bdy != 0) Ps.brect.top += Ps.bdy *0.1;  // ���������� �� �

				sprite.setPosition(Ps.brect.left - ofset_x, Ps.brect.top - ofset_y); // ��������� ���� �� ������ � ������ ��������� ������
			}
			else
			{
				Ps.bdx = 0; //
				Ps.bdy = 0; // ���������� �������� ����
			}
		}
	}
};

class Bot
{
public:
	Texture t3;
	Sprite Sprite;

	Bot()
	{
		t3.loadFromFile("2.png");
		Sprite.setTexture(t3);
		Sprite.setTextureRect(IntRect(0, 0, 32, 32));

		Sprite.setPosition(460, 320);
		Ps.bbrect = FloatRect(500, 340, -32, -32); // ��������� ���������� 
	}

	void show(RenderWindow &window)
	{
		window.draw(Sprite);
	}

	void update(int time, Abs* del)
	{
		if (Ps.bblife == true)
		{
			if (Ps.bbcolision == true) // ���� ��������� ������������
			{
				Ps.bbdx = 0; //
				Ps.bbdy = 0; // ���������� �������� ����
				Ps.bba = 0; // rand() % 4; // �������� ����� �����������

				if (fabs(Ps.rect.left - Ps.bbrect.left) > fabs(Ps.rect.top - Ps.bbrect.top) && (Ps.rect.left > Ps.bbrect.left)) // ���� ��������� �� �� > �� � ��� ����� �������
					Ps.bba = 0; // ��� ��� �������

				if (fabs(Ps.rect.left - Ps.bbrect.left) > fabs(Ps.rect.top - Ps.bbrect.top) && (Ps.rect.left < Ps.bbrect.left)) // ���� ��������� �� �� > �� � ��� ������ �������
					Ps.bba = 1; // �������� ������

				if (fabs(Ps.rect.left - Ps.bbrect.left) < fabs(Ps.rect.top - Ps.bbrect.top) && (Ps.rect.top > Ps.bbrect.top)) //���� ��������� �� �X < �� � ��� ���� �������
					Ps.bba = 2; // �������� ����

				if (fabs(Ps.rect.left - Ps.bbrect.left) < fabs(Ps.rect.top - Ps.bbrect.top) && (Ps.rect.top < Ps.bbrect.top)) //���� ��������� �� �X < �� � ��� ���� �������
					Ps.bba = 3; // �������� �����


				Ps.bbcolision = false; // ��������� �������
			}

			if (Ps.bba == 0)
			{
				Ps.bbdx = 0.5*time; 
			} // �������� ������

			if (Ps.bba == 1)
			{
				Ps.bbdx = -0.5*time;
			} // �������� �����

			if (Ps.bba == 2)
			{
				Ps.bbdy = 0.5*time; 
			} // �������� ����

			if (Ps.bba == 3)
			{
				Ps.bbdy = -0.5*time; 
			} // �������� �����
			
			del->bbcolision(0); // �� �
			del->bbcolision(1); // �������� ������������

			if (Ps.bbcolision == false && Ps.bbdx != 0) Ps.bbrect.left += Ps.bbdx*0.1; // ���������� �� �
			if (Ps.bbcolision == false && Ps.bbdy != 0) Ps.bbrect.top += Ps.bbdy*0.1;  // ���������� �� �

			Sprite.setPosition(Ps.bbrect.left - ofset_x, Ps.bbrect.top - ofset_y); // ��������� ���� �� ������ � ������ ��������� ������
		}
		else
		{
			Ps.bbdx = 0; //
			Ps.bbdy = 0; // ���������� �������� ����
		}
	}

};

class Pacman 
{
public:   //����
	Sprite PAKMAN;   //��������� ��������
	Image im; Texture t;
	float currentFrame = 0;   //������� ���� ��� ��������

	 Pacman()
	{
		im.loadFromFile("Right.png");  // ������� ��������
		t.loadFromImage(im); // ��������� � �������� �������� �� �����
		PAKMAN.setTexture(t);
		PAKMAN.setTextureRect(IntRect(0, 0, 32, 32));

		Ps.rect = FloatRect(18 * 32 + 24, 5 * 32, -32, -32); // ��������� ���������� Packman
		Ps.dx = Ps.dy = 0;
	}

	void updater(int time, Abs* del)
	{
		Ps.rect.left += Ps.dx*time;   // ���������� �
		del -> pcolision(0);

		Ps.rect.top -= Ps.dy*time;    // ���������� Y
	 	del -> pcolision(1);

		currentFrame += time  *0.003;
		if (currentFrame >= 2) currentFrame = 0;   //  ��������

		if (Ps.dx > 0) {
			PAKMAN.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 32));/*	std::cout << "Why not?" << endl;*/}		//
		if (Ps.dx<0)PAKMAN.setTextureRect(IntRect(32 * int(currentFrame) + 32, 0, -32, 32));	// ��������
		if (Ps.dy>0)PAKMAN.setTextureRect(IntRect(32 * int(currentFrame), 32, 32, -32));		//
		if (Ps.dy<0)PAKMAN.setTextureRect(IntRect(32 * int(currentFrame), 32, 32, -32));		//

		PAKMAN.setPosition(Ps.rect.left - ofset_x, Ps.rect.top - ofset_y);
//		std::cout << "WTF?" << endl;	// +
		Ps.dx = 0;
		Ps.dy = 0;
	}

	void show(RenderWindow &window)
	{
		window.draw(PAKMAN);
	//	std::cout << "hm..." << endl;	// +
	}
	
	void life()
	{
		
		{
			if (Ps.blife == true && (fabs(Ps.brect.left - Ps.rect.left) < 30) && (fabs(Ps.rect.top - Ps.brect.top)) < 30)
			{
				if (Ps.gamemode == true && Ps.C.getElapsedTime().asSeconds() <= 7)
					Ps.blife = false;
				else Ps.plife = false;
			}

			if (Ps.bblife == true && (fabs(Ps.bbrect.left - Ps.rect.left) < 30) && (fabs(Ps.rect.top - Ps.bbrect.top)) < 30)
			{
				if (Ps.gamemode == true && Ps.C.getElapsedTime().asSeconds() <= 7)
					Ps.bblife = false;
				else Ps.plife = false;

			}
		}
	}

};

class Delegat :Abs
{
public:Pacman P;

	   bot B;

	   Bot Bt;  //����� ���
	   mapp M;
	   Clock clock;
	   RectangleShape recrangle;

	   Clock K;	// ����� �� �������� ���� ����� ������ �������
	   Clock NLVL; // ����� ������� "����� �������"
	   int Time = clock.getElapsedTime().asMicroseconds(); // ������ �� �������� �������


	 
	   Delegat(RenderWindow &Window) :Abs(){  };
	  
	   void show(RenderWindow &window)
	   {
		   M.show(window); // �����

		   
		   
			   if (Ps.blife == true)	//���
				   B.show(window);			//
		   

		   if (Ps.bblife == true)
			  Bt.show(window); // ����� ���

		   P.show(window);	// ������

		   {
			   Text text;
			   Font font;
			   font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
			   text.setFont(font);
			   text.setColor(Color::Green);
			   text.setPosition(30, 10);
			   text.setString(L"������� " /*+ gthtv*/ );
			   text.setColor(sf::Color::Green);
			   text.setCharacterSize(45);
			   window.draw(text);
		   }

		   if (Ps.plife == false)   // game ower
		   {
			   Texture t4;
			   t4.loadFromFile("game_over.png");
			   Sprite massage;
			   massage.setTexture(t4);
			   massage.setPosition(500, 400);
			   window.draw(massage);

			   if (K.getElapsedTime().asSeconds() >= 5)
			   {
				   window.close();
				   Ps.mod = true;
				   open = true;
			   }
		   }

		   if (Ps.dot < 1) // new levl
		   {
			   Ps.dot = 469;
			   Ps.blife = true;
			   Ps.gamemode = false;
			   NLVL.restart();

			   for (int i = 0; i < H; i++)				//
				   for (int j = 0; j < W; j++)			// ��������� �����
					   Ps.Map[i][j] = Ps.iMap[i][j];	//
		   }

		   if (NLVL.getElapsedTime().asSeconds() <= 2)
		   {
			   M.NewLvL(window); // ����� �� ����� "����� �������"
		   }
	   }

	   void move()
	   {
		   int time = clock.getElapsedTime().asMicroseconds(); // ���������� time ���������� ����� � ���������� ���� � �������������
		   clock.restart();   // ������������� ����
		   time = time / 800; // ����������� �������
		   if (time > 20)   clock.restart();   // ������������� ����
		   
		   P.updater(time, this);

		   B.update(time, this);

		   Bt.update(time, this);

		   if (Ps.rect.left > (1300 / 2)) ofset_x = Ps.rect.left - 1300 / 2;	//
		   if (Ps.rect.top > (700 / 2)) ofset_y = Ps.rect.top - 700 / 2;	    // ����������� ������ � ����������� ���������

		   P.life();

		   if (Ps.plife == true)
		   {
			   // �������� PACKMAN ---->
			   if (Keyboard::isKeyPressed(Keyboard::Left))  //���� ������� ������ � ������� ������
			   {
				   Ps.dx = -0.1;
				 //  std::cout << "dx= " << Ps.dx << endl;	// +
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Right))  //���� ������� ������ � ������� �������
			   {
				   Ps.dx = 0.1;
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Up))  //���� ������� ������ � ������� �����
			   {
				   Ps.dy = 0.1;
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Down))  //���� ������� ������ � ������� ����
			   {
				   Ps.dy = -0.1;
			   }
		   }
		   else
		   {
			   if (Ps.mod == true)
			   {
				   Ps.mod = false;
				   K.restart();
			   }
		   }
			   // �������� PACKMAN <------
	   }

	   void pcolision(int dir) // ��������� ������������ ��  �
	   {
		   for (int i = Ps.rect.top / 32; i < (Ps.rect.top + 32) / 32; i++)			// ������� ������ ����� � �������� ��������� �����
			   for (int j = Ps.rect.left / 32; j < (Ps.rect.left + 32) / 32; j++)	//
				 {
					   if (Ps.Map[i][j] == 'B') // ���� ��� ������, ��...
						  {
							   if ((Ps.dx > 0) && (dir == 0)) { Ps.rect.left = j * 32 - 32;/*	std::cout << "my be?" << endl;*/}//
							   if ((Ps.dx < 0) && (dir == 0)) Ps.rect.left = j * 32 + 32;	// �� ���� ������� ������
							   if ((Ps.dy > 0) && (dir == 1)) Ps.rect.top = i * 32 + 32;	//
							   if ((Ps.dy < 0) && (dir == 1)) Ps.rect.top = i * 32 - 32;	//
						  }

				   if (Ps.Map[i][j] == ' ')
				   {
					   Ps.Map[i][j] = 'A';
					   Ps.dot--;
					   Ps.schet++;
					}

				   if (Ps.Map[i][j] == 'C')
				   {
					   Ps.C.restart();
					   Ps.Map[i][j] = 'A';
					   Ps.dot--;
					   Ps.schet++;
					   Ps.gamemode = true;
				   }
			   }
	   }

	   void bcolision (int dir)
	   {
		   for (int i = 0; i < levlnumber; i++)
		   for (int k = (Ps.brect.top) / 32; k < (Ps.brect.top + 32) / 32; k++)			// ������� ������ ����� � �������� ��������� �����
			   for (int j = (Ps.brect.left) / 32; j < (Ps.brect.left + 32) / 32; j++)		//
				  {
					   if (Ps.Map[k][j] == 'B') // ���� ��� ������, ��...
						   {
								 if ((Ps.bdx < 0) && (dir == 0)) // +
									{
										 Ps.colision = true;
						     			 Ps.brect.left = j * 32 + 32;
									     Ps.bdx = 0;
									}
					   if ((Ps.bdx > 0) && (dir == 0)) // +
					   {
						   Ps.colision = true;
						   Ps.brect.left = j * 32 - 32;
						   Ps.bdx = 0;
					   }

					   if ((Ps.bdy < 0) && (dir == 1)) // +
					   {
						   Ps.colision = true;
						   Ps.brect.top = i * 32 + 32;
						   Ps.bdy = 0;
					   }

					   if ((Ps.bdy > 0) && (dir == 1))
					   {
						   Ps.colision = true;
						   Ps.brect.top = i * 32 - 32;
						   Ps.bdy = 0;
					   }
				   }
			   }
	   }

	   void bbcolision(int dir)
	   {
		   for (int i = Ps.bbrect.top / 32; i < (Ps.bbrect.top + 32) / 32; i++)			// ������� ������ ����� � �������� ��������� �����
			   for (int j = Ps.bbrect.left / 32; j < (Ps.bbrect.left + 32) / 32; j++)	//
				  {
					   if (Ps.Map[i][j] == 'B') // ���� ��� ������, ��...
						   {
							   //if ((Ps.bbdx > 0) && (dir == 0)) { Ps.bbrect.left = j * 32 - 32;/*	std::cout << "my be?" << endl;*/ }//
							   //if ((Ps.bbdx < 0) && (dir == 0)) Ps.bbrect.left = j * 32 + 32;	// �� ���� ���� ������
							   //if ((Ps.bbdy > 0) && (dir == 1)) Ps.bbrect.top = i * 32 + 32;	//
							   //if ((Ps.bbdy < 0) && (dir == 1)) Ps.bbrect.top = i * 32 - 32;	//

							   if ((Ps.bbdx < 0) && (dir == 0)) // +
							   {
								   Ps.bbcolision = true;
								   Ps.bbrect.left = j * 32 + 32;
								   Ps.bbdx = 0;
							   }
							   if ((Ps.bbdx > 0) && (dir == 0)) // +
							   {
								   Ps.bbcolision = true;
								   Ps.bbrect.left = j * 32 - 32;
								   Ps.bbdx = 0;
							   }

							   if ((Ps.bbdy < 0) && (dir == 1)) // +
							   {
								   Ps.bbcolision = true;
								   Ps.bbrect.top = i * 32 + 32;
								   Ps.bbdy = 0;
							   }

							   if ((Ps.bbdy > 0) && (dir == 1))
							   {
								   Ps.bbcolision = true;
								   Ps.bbrect.top = i * 32 - 32;
								   Ps.bbdy = 0;
							   }
						   }
				   }
	   }

	   void volume()
	   {
		   sf::Music music;
		   music.openFromFile("Comic-Con - ������ (online-audio-converter.com).wav");
		   music.play();
	   }
};



int mani()
{
	setlocale(LC_ALL, "Russian");

	 menu();
	 nool();

	if (open == false && close == false)
	{
		sf::RenderWindow window(sf::VideoMode(1300, 700), "SFML works!");
		Delegat PS(window);
		while (window.isOpen()) //��������� �������� ���� 
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(Color::Blue);
			PS.show(window);
			PS.move();

			window.display(); // ����� �� �����

		}
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	 menu();
	 nool();

	if (open == false && close == false)
	{
		sf::RenderWindow window(sf::VideoMode(1300, 700), "SFML works!");
		Delegat PS(window);
		while (window.isOpen()) //��������� �������� ���� 
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(Color::Blue);
			PS.show(window);
			PS.move();

			window.display(); // ����� �� �����
		}

		do
		{
			mani();
		} while (open == true && close == false);
	}
	return 0;
}