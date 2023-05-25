#pragma once

#include <SFML/Graphics.hpp>
class Car
{
protected:
    sf::Texture texture;
    sf::Image monImage;
    sf::Sprite monSprite;
    int directionX; // Initialiser directionX à 0
    int directionY; // Initialiser directionY à 0
    float x, y, speed, angle, acc, dec, maxSpeed;
    bool ready;
    bool Avance; // pour voir si on avance ou on recule

public:

    Car(sf::Vector2f position);                 //load l'image là dedans 
    sf::Sprite GetSprite();
    void setDirection(float newAngle);
    float getDirectionX() const;
    float getDirectionY() const;
    void accelere(sf::Time dureeIteration);
    void Reculer();
    void TournerDroite(sf::Time dureeIteration);
    void TournerGauche(sf::Time dureeIteration);
    void Decelerer(sf::Time dureeIteration);
    void Avancer(sf::Time dureeIteration);
    void ChangeVitesse(sf::Time dureeIteration);
    void Ralentir(sf::Time dureeIteration);
    virtual ~Car();
    //void move();

};


