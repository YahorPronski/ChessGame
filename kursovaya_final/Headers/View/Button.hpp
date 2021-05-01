#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../../resource/Values.h"
using namespace sf;
using namespace std;


class Label {
public:
    Text TXT;
    string text;	//Текст
protected:
    double x;		//Координата x
    double y;		//Координата y
    Font myFont;//Отображаемый текст

public:
    Label(double _x = 0, double _y = 0, string _text ="Текст")
    {
      myFont.loadFromFile(font);			//передаем нашему шрифту файл шрифта

      x = _x;
      y = _y;
      text = _text;								// загружает текст
      TXT.setFont(myFont);							// загружаем фрифт
      TXT.setCharacterSize(20); 					// в пикселях, а не точках!
      TXT.setColor(Color::White);// устанавливаем цвет выводимого текста
      TXT.setString(text);
      TXT.setPosition(x,y);						// позиция текста
    }
//    void setText()
//    {
//      TXT.setString(text);						// загружаем в выводимый текст загружаемый текс
//    }
};

class Button : public Label {
protected:
    double width;		// Ширина Кнопки
    double height;		// Высота Кнопки
    RectangleShape BOX;	// Создаем прямоугольник с размером width, height
public:
    double time = 1.0;
    Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text ="Кнопка")
    {
      myFont.loadFromFile(font);			//передаем нашему шрифту файл шрифта

      x = _x;
      y = _y;
      width = _width;
      height = _height;
      text = _text;								// загружает текст
      TXT.setFont(myFont);							// загружаем фрифт
      TXT.setCharacterSize(20); 					// в пикселях, а не точках!
      TXT.setColor(Color::White);					// устанавливаем цвет выводимого текста
      TXT.setPosition(x,y);						// позиция текста

      BOX.setSize(Vector2f(width, height));		// размер кнопки
      BOX.setPosition(x,y);						// координаты кнопки
      BOX.setFillColor(sf::Color(133, 133, 133));	// цвет кнопки
      BOX.setOutlineThickness(2);					// Контур X пикселей
      BOX.setOutlineColor(Color(66, 66, 66));		// Цвет контура
    }
    //Проверка нажатия на кнопку
    bool isSelected(Vector2i _mouse)
    {
      if((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)){
        return  true;
      } else {
        return false;
      }
    }
    //Вывод Текста
    Text displayText() const {
//      TXT.setString(text);  // загружаем в выводимый текст загружаемый текст
      return TXT;
    }
    //Вывод кнопки
    RectangleShape displayButton() const {
      return BOX;
    }
};