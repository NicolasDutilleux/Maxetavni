#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp" 

#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include "Car.h"
const float MAX_DRIFT_ANGLE = 45.0f; // Maximum angle for drifting
const float DRIFT_FORCE = 10.0f;     // Force applied during drifting

bool Up1 = false, Right1 = false, Down1 = false, Left1 = false;
bool Up2 = false, Right2 = false, Down2 = false, Left2 = false;


/*Car* ajout_joueur() //ajoute un joueur
{
    Car* j = NULL;
    std::string nom;
    std::cout << "Entrez votre nom : ";
    getline(std::cin >> std::ws, nom);
    char c;
    std::cout << "Entrez votre Couleur (r) Rouge, (b) Bleu ";
    std::cin >> c;
    switch (c)
    {
    case 'r':
        j = new Car(sf::Vector2f(400, 400));
        break;
    case 'b':
        j = new Car(sf::Vector2f(400, 300));
        break;

    }

    return j;
}*/

int main()
{
    sf::RenderWindow app(sf::VideoMode(1440, 1080), "C'est parti !");
    app.setFramerateLimit(60);
    std::vector<Car*> mes_voit;
    for (int i = 0; i < 2; i++)
    {
        mes_voit.push_back(new Car(sf::Vector2f(200+i*100, 200+i*100)));
    }

   /* for (int i = 0; i < mes_voit.size(); i++)
    {
        std::cout << "Joueur  : " << i + 1 << std::endl;
        mes_voit[i] = ajout_joueur();
    }*/

    sf::Texture green, track, monSprite;
    sf::Image img;
    img.loadFromFile("Circuit_Hitbox.png"); //Circuit en Vert
    track.loadFromImage(img);
    green.loadFromFile("backgroundimage.png"); //circuit normal à afficher
    //track.setSmooth(true);             //lissage pour rendre moins pixelisé

    sf::Color green_color(18, 255, 0); //couleur route à comparer apres

    sf::Sprite sBackground(track), qBackground(green), sCar;
    //sf::Vector2f pos_in(400, 400);
    //Car mavoit(pos_in);
    sBackground.scale(1, 1);
    qBackground.scale(1, 1);
    //monSprite.setOrigin(0, 0);                 //Point de départ de la caisse
    sf::Clock time;
    //font pour ecrire
    sf::Font font; 
  

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(50, 30);

    //la clock
    sf::Clock clock;
    sf::Time elapsedTime;
    sf::Time dureeIteration = sf::Time::Zero; // Temps que prends le PC pour lire la boucle 1 fois


    //= ====== = Ajoute musique BUG OpenAl32.ddl====== =
        /* sf::SoundBuffer buffer;
         if (!buffer.loadFromFile("XD/audi-v8-acceleration-sound-6067.ogg"))
         {

         }
         sf::Sound sound1;
         sound1.setBuffer(buffer);
         sound1.play();*/



    while (app.isOpen())
    {
        dureeIteration = clock.restart();


        for (int i = 0; i < mes_voit.size(); i++)
       {
            sf::Vector2f HitBox_voiture = mes_voit[i]->GetSprite().getPosition();
            sf::Color color_at_car = img.getPixel(HitBox_voiture.x, HitBox_voiture.y);
            //sortie de piste, VERIF
            if (color_at_car != green_color)
            {
                std::cout << "COULEUR GREEN" << std::endl;
                mes_voit[i]->ChangeVitesse(dureeIteration);
            }

           // std::cout << (int)color_at_car.r << "  " << (int)color_at_car.g << "  " << (int)color_at_car.b << std::endl;
            sf::Event e;
            while (app.pollEvent(e))
            {
                switch (e.type)
                {
                case sf::Event::Closed:
                    app.close();

                case sf::Event::EventType::KeyPressed:
                    switch (e.key.code)
                    {
                    case sf::Keyboard::D:
                        Right1 = true;
                        break;
                    case sf::Keyboard::Z:
                        Up1 = true;
                        break;
                    case sf::Keyboard::Q:
                        Left1 = true;
                        break;
                    case sf::Keyboard::S:
                        Down1 = true;
                        break;
                    case sf::Keyboard::Right:
                        Right2 = true;
                        break;
                    case sf::Keyboard::Up:
                        Up2 = true;
                        break;
                    case sf::Keyboard::Left:
                        Left2 = true;
                        break;
                    case sf::Keyboard::Down:
                        Down2 = true;
                        break;
                    }
                    break;
                case sf::Event::EventType::KeyReleased:
                    switch (e.key.code)
                    {
                    case sf::Keyboard::D:
                        Right1 = false;
                        break;
                    case sf::Keyboard::Z:
                        Up1 = false;
                        break;
                    case sf::Keyboard::Q:
                        Left1 = false;
                        break;
                    case sf::Keyboard::S:
                        Down1 = false;
                        break;
                    case sf::Keyboard::Right:
                        Right2 = false;
                        break;
                    case sf::Keyboard::Up:
                        Up2 = false;
                        break;
                    case sf::Keyboard::Left:
                        Left2 = false;
                        break;
                    case sf::Keyboard::Down:
                        Down2 = false;
                        break;
                    }


                }
            }
            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed;
            mes_voit[i]->Avancer(dureeIteration);

           //voiture 1 : verif accelere, decelere etc (MAJ)
            if (i == 0)
            {

                if (Up1)
                {
                    mes_voit[0]->accelere(dureeIteration); //Speed +
                }
                if (Down1)
                {
                    mes_voit[0]->Decelerer(dureeIteration); // Speed -
                }
                if ((Right1 && Up1) || (Left1 && Down1))
                {
                    mes_voit[0]->TournerDroite(dureeIteration); // rotate +
                }
                if ((Left1 && Up1) || (Right1 && Down1))
                {
                    mes_voit[0]->TournerGauche(dureeIteration); // rotate -
                }
                if (!Up1 && !Down1)                   //Décéleration si l'on n'accélère pas
                {
                    std::cout << "je Ralentir" << std::endl;
                    mes_voit[0]->Ralentir(dureeIteration); // Speed ----> Speed/2
                }
            }
            //voiture 2 : verif accelere, decelere etc (MAJ)
            if (i == 1)
            {

                if (Up2)
                {
                    mes_voit[1]->accelere(dureeIteration);
                }
                if (Down2)
                {
                    mes_voit[1]->Decelerer(dureeIteration);
                }
                if ((Right2 && Up2) || (Left2 && Down2))
                {
                    mes_voit[1]->TournerDroite(dureeIteration);
                }
                if ((Left2 && Up2) || (Right2 && Down2))
                {
                    mes_voit[1]->TournerGauche(dureeIteration);
                }
                if (!Up2 && !Down2)                   //Décéleration si l'on n'accélère pas
                {
                    std::cout << "je Ralentir" << std::endl;
                    mes_voit[1]->Ralentir(dureeIteration);
                }
            }
           } 
           //clear la window puis dessine dessus
            app.clear();
            app.draw(sBackground);
            app.draw(qBackground);
            for (int i = 0; i < mes_voit.size(); i++)
            {
                app.draw(mes_voit[i]->GetSprite());
            }

        app.display();
    }

    int taille = mes_voit.size();
    for (int i = 0; i < taille; i++)
    {
        delete mes_voit.back();
        mes_voit.pop_back();
    }
    return 0;
}





// La marche arrière n'a pas de vitesse minimale, il faut lui faire la même chose que pour la marche avant mais à -12 
//(ou à moins max mais c'est moche)

// Essayer d'offset le repère sur l'image pour que ça soit centré au milieu du sprite et pas sur le côté
// Tourner correctement pcq ça pue la merde
// Rajouter 2ème voiture

//Tu peux rajouter des checkpoint si tu veux pour mettre des tours, ça serait marrant
//Faire un chrono de gay
// 