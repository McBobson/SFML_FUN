#ifndef WYSWIETLANIE_H
#define WYSWIETLANIE _H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

using namespace std;

class Ekran
{

public:

	sf::Texture Pionek;
	sf::Texture PionekC;
	sf::Texture DamkaB;
	sf::Texture DamkaC;
	sf::Texture Pole;
	sf::Texture texture;
	sf::Texture textureMenu;
	sf::Texture textureWygrana;
	sf::Texture texturePrzegranaSI;
	sf::Texture textureWygranaPVP;
	sf::Sprite Sprite;
	sf::Sprite Menu;
	sf::Sprite Wygrana;
	sf::Sprite WygranaPVP;
	sf::Sprite PrzegranaSI;
	sf::Sprite P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12;
	sf::Sprite Pc1, Pc2, Pc3, Pc4, Pc5, Pc6, Pc7, Pc8, Pc9, Pc10, Pc11, Pc12;

	void Tworz_Plansze();
	void Ulozenie_Pionkow();

};

void Ekran::Tworz_Plansze()
{
	texture.loadFromFile("plansza.jpg");
	texture.setSmooth(true);

	Sprite.setTexture(texture);

	textureMenu.loadFromFile("Menu_Glowne.png");
	textureMenu.setSmooth(true);

	Menu.setTexture(textureMenu);

	textureWygrana.loadFromFile("Wygrana.png");
	textureWygrana.setSmooth(true);

	Wygrana.setTexture(textureWygrana);

	texturePrzegranaSI.loadFromFile("Przegrana.png");
	texturePrzegranaSI.setSmooth(true);

	PrzegranaSI.setTexture(texturePrzegranaSI);

	textureWygranaPVP.loadFromFile("WygranaPVP.png");
	textureWygranaPVP.setSmooth(true);

	WygranaPVP.setTexture(textureWygranaPVP);

	Pole.loadFromFile("Pole.png");
	DamkaB.loadFromFile("MonD.png");
	DamkaC.loadFromFile("WitD.png");
}

void Ekran::Ulozenie_Pionkow()
{
	Pionek.loadFromFile("Mon.png");
	Pionek.setSmooth(true);

	P1.setTexture(Pionek);
	P2.setTexture(Pionek);
	P3.setTexture(Pionek);
	P4.setTexture(Pionek);
	P5.setTexture(Pionek);
	P6.setTexture(Pionek);
	P7.setTexture(Pionek);
	P8.setTexture(Pionek);
	P9.setTexture(Pionek);
	P10.setTexture(Pionek);
	P11.setTexture(Pionek);
	P12.setTexture(Pionek);

	P1.setScale(1.2, 1.2);
	P1.setPosition(93, 93);

	P2.setScale(1.2, 1.2);
	P2.setPosition(249, 93);

	P3.setScale(1.2, 1.2);
	P3.setPosition(403, 93);

	P4.setScale(1.2, 1.2);
	P4.setPosition(557, 93);

	////////////////////////////////

	P5.setScale(1.2, 1.2);
	P5.setPosition(171, 170);

	P6.setScale(1.2, 1.2);
	P6.setPosition(325, 170);

	P7.setScale(1.2, 1.2);
	P7.setPosition(479, 170);

	P8.setScale(1.2, 1.2);
	P8.setPosition(634, 170);

	///////////////////////////////////

	P9.setScale(1.2, 1.2);
	P9.setPosition(93, 247);

	P10.setScale(1.2, 1.2);
	P10.setPosition(249, 247);

	P11.setScale(1.2, 1.2);
	P11.setPosition(403, 247);

	P12.setScale(1.2, 1.2);
	P12.setPosition(557, 247);

	//////////////////////////////////////////////////////////////////////////////////

	PionekC.loadFromFile("Wit.png");
	PionekC.setSmooth(true);

	Pc1.setTexture(PionekC);
	Pc2.setTexture(PionekC);
	Pc3.setTexture(PionekC);
	Pc4.setTexture(PionekC);
	Pc5.setTexture(PionekC);
	Pc6.setTexture(PionekC);
	Pc7.setTexture(PionekC);
	Pc8.setTexture(PionekC);
	Pc9.setTexture(PionekC);
	Pc10.setTexture(PionekC);
	Pc11.setTexture(PionekC);
	Pc12.setTexture(PionekC);

	Pc1.setScale(1.2, 1.2);
	Pc1.setPosition(634, 634);

	Pc2.setScale(1.2, 1.2);
	Pc2.setPosition(479, 634);

	Pc3.setScale(1.2, 1.2);
	Pc3.setPosition(325, 634);

	Pc4.setScale(1.2, 1.2);
	Pc4.setPosition(171, 634);

	////////////////////////////////

	Pc5.setScale(1.2, 1.2);
	Pc5.setPosition(557, 557);

	Pc6.setScale(1.2, 1.2);
	Pc6.setPosition(403, 557);

	Pc7.setScale(1.2, 1.2);
	Pc7.setPosition(249, 557);

	Pc8.setScale(1.2, 1.2);
	Pc8.setPosition(93, 557);

	///////////////////////////////////

	Pc9.setScale(1.2, 1.2);
	Pc9.setPosition(634, 480);

	Pc10.setScale(1.2, 1.2);
	Pc10.setPosition(479, 480);

	Pc11.setScale(1.2, 1.2);
	Pc11.setPosition(325, 480);

	Pc12.setScale(1.2, 1.2);
	Pc12.setPosition(171, 480);
}



#endif WYSWIETLANIE_H
#pragma once
