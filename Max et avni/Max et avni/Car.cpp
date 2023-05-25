#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Car.h"

using namespace std;
using namespace sf;

Car::Car(sf::Vector2f position)
{
   texture.loadFromFile("voitureRouge.png",IntRect(0,0,34,45));
   monSprite.setTexture(texture);
   monSprite.setPosition(position);
   sf::FloatRect rectangle = monSprite.getLocalBounds();
   monSprite.setOrigin(rectangle.width / 2, rectangle.height / 2);
 
    ready = false;
    speed = 0;
    x = 0;
    y = 0;
    angle = 0;
    acc = 300;
    dec = 600;
    maxSpeed = 200;
    directionX = 0;
    directionY = 0;
    Avance = true;
}

Car::~Car()
{
    // destructeur
}

Sprite Car::GetSprite() // return Sprite
{
    return monSprite;
}

void Car::setDirection(float newAngle) //change la direction
{
    angle = newAngle;
    directionX = std::cos(angle); // sert à rien au début
    directionY = std::sin(angle);
}

float Car::getDirectionX() const
{
    return directionX;   //donne la direction en X
}

float Car::getDirectionY() const
{
    return directionY; //donne la direction en Y
}
void Car::Avancer(sf::Time dureeIteration)
{
    float angle = monSprite.getRotation() * 3.1415 / 180; //Avance, Top la fonction!

    monSprite.move(sf::Vector2f(speed * sin(angle) * dureeIteration.asSeconds(), -speed * cos(angle)*dureeIteration.asSeconds()));

}
void Car::accelere(sf::Time dureeIteration)      //if Up 
{
    if (speed < maxSpeed)
    {
        speed += acc * dureeIteration.asSeconds(); //Speed +
    }
        

}
void Car::TournerDroite(sf::Time dureeIteration)        //if Right
{
    monSprite.rotate(70* dureeIteration.asSeconds()); // Rotate + car droite

}

void Car::TournerGauche(sf::Time dureeIteration)        //if Left
{
        monSprite.rotate(-70* dureeIteration.asSeconds());
}
void Car::Ralentir(sf::Time dureeIteration)              // if aucun bouton
{
    if (speed > 0)
    {
        speed -= dec * dureeIteration.asSeconds(); //Speed -, -->0
    }
    if (speed < 0)
    {
        speed += dec * dureeIteration.asSeconds(); //Speed +, -->0
    }
}
void Car::Decelerer(sf::Time dureeIteration)              // if aucun bouton
{
    if (speed > -maxSpeed +50)
    {
        speed -= dec * dureeIteration.asSeconds();// Speed -
    }
}

void Car::ChangeVitesse(sf::Time dureeIteration)
{
    if (speed > maxSpeed/2)
    {
        speed -= dec * dureeIteration.asSeconds(); // hors du terrain, ralentis jusqu'a une certaine vitesse
    }
    if (speed < -maxSpeed/2)
    {
        speed += dec * dureeIteration.asSeconds();
    }

}
