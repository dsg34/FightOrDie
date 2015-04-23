
#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "ArmaFactory.h"
#include "Nivel.h"
#include "Mundo.h"
#define kVel 5


int main()
{
    sf::RenderWindow window(sf::VideoMode(1300, 750), "Fight or Die");
    
    Mundo* mundo = new Mundo(window);
    mundo->ejecutarMundo();

    return 0;
}