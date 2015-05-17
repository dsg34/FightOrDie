#include "Zombie.h"

Zombie::Zombie(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, float ve, float dan) :Personaje(s,t,p,mV,ve) {
    sprite = new sf::Sprite(*s);    
    tex = new sf::Texture(*t);
    sprite->setTexture(*tex);
    sprite->setPosition(p);
    
    posActual = p;
    posAnterior = p;
    maxVida = mV;
    velocidad = ve;
    estaVivo = true;
    danyo = dan;
    
    vida = maxVida;
    cont = 0;
    contA = 0;
    direc = 0;
    muriendo = false;
    atacando = false;
    boundingBox = new sf::FloatRect((*sprite).getGlobalBounds());
    boundingBox->width -= 70;
    boundingBox->left += 35;
    
    esquiva = 0;
    obsMapa = true;
    reloj.restart();
    audios = Sonidos::Instance();
}

Zombie::Zombie(const Zombie& orig) : Personaje(orig){
}

Zombie::~Zombie() {
}

int Zombie::update(sf::Sprite protagonista , std::vector<Zombie*> zombies, std::vector<Arma*> armas, std::vector<Recurso*> recursos, MapLoader* mapa){
    
    std::cout << "entra en el update" << sprite->getPosition().x <<std::endl;
    
    posAnterior = posActual;
    *boundingBox = sprite->getGlobalBounds();
    int ataque = 0;
    bool dominante = false;
    sf::Time frecuencia;
    obsMapa = true;
    boundingBox->width -= 70;
    boundingBox->left += 30;  
    
    std::cout << "despues del update" << sprite->getPosition().x <<std::endl;
    
    if(muriendo==false){
        colisionConBalas(armas);
        colisionConGranadas(armas);
        std::cout << "despues del update2" << sprite->getPosition().x <<std::endl;
        if(atacando==true){        
            frecuencia = reloj.getElapsedTime();            
            if(frecuencia.asSeconds()>0.1){
                atacar();
                reloj.restart();
            }
            std::cout << "despues del update3" << sprite->getPosition().x <<std::endl;
        }else{
            std::cout << "despues del update5" << sprite->getPosition().x <<std::endl;
            dominante = calcularDireccion(protagonista);
            std::cout << "despues del update4" << sprite->getPosition().x <<std::endl;
            char direccion;
            if(equis>0 &&(y==0||y>0))
                direccion = 'D';
            else if(y>0 &&(equis==0||equis<0))
                direccion = 'S';
            else if(equis<0&&(y==0||y<0))
                direccion = 'A';
            else
                direccion = 'W';
            std::cout << "despues del update6" << sprite->getPosition().x <<std::endl;
            if(colisionConProta(protagonista, direccion)){
                ataque=1;
                contA=0;
                atacando=true;
                std::cout << "despues del update7" << sprite->getPosition().x <<std::endl;
            }else if(colisionConRecursos(recursos)){
                ataque=2;
                contA=0;
                atacando=true;
                std::cout << "despues del update8" << sprite->getPosition().x <<std::endl;
            }else{
                std::cout << "despues del update9" << sprite->getPosition().x <<std::endl;
                std::cout << "psrpritex" << sprite->getPosition().x << std::endl;
                std::cout << "psrpritey" << sprite->getPosition().y << std::endl;
                detectarObstaculos(mapa, dominante);
                std::cout << "despues del update12" << sprite->getPosition().x <<std::endl;
                
                if(equis>0 && y>0)
                    direccion = 'C';
                else if(equis<0 && y>0)
                    direccion = 'Z';
                else if(equis>0 && y<0)
                    direccion = 'E';
                else if(equis<0 && y<0)      
                    direccion = 'Q';
                else if(equis>0)
                    direccion = 'D';
                else if(y>0)
                    direccion = 'S';
                else if(equis<0)
                    direccion = 'A';
                else
                    direccion = 'W';
                
                std::cout << "despues del update10" << sprite->getPosition().x <<std::endl;
                if(obsMapa==false)
                    detectarZombie(zombies, direccion, mapa);
                else if(!colisionConZombies(zombies, direccion))
                    sprite->move(equis,y);
                std::cout << "despues del update11" << sprite->getPosition().x <<std::endl;
                posActual = sprite->getPosition();
            }
        }
        
        std::cout << "if update " << sprite->getPosition().x <<std::endl;
        
    }else{
        frecuencia = reloj.getElapsedTime();            
        if(frecuencia.asSeconds()>0.1){
            actualizaMuerte();
            reloj.restart();
        }    
        
        std::cout << "else update " << sprite->getPosition().x <<std::endl;
        
    }
    
    std::cout << "sale del update" << sprite->getPosition().x <<std::endl;
    
    return ataque;
}

bool Zombie::calcularDireccion(sf::Sprite protagonista){
    
    bool ejey = false;
    bool ejex = true;
        
    int diferenciax = protagonista.getPosition().x - sprite->getPosition().x;
    diferenciax = std::abs(diferenciax);

    int diferenciay = protagonista.getPosition().y - sprite->getPosition().y;
    diferenciay = std::abs(diferenciay);

    if(diferenciay < diferenciax)
    {
        ejey = false;
        ejex = true;
    }
    else
    {
        ejey = true;
        ejex = false;
    }
    

    if(((protagonista.getPosition().x) + 10) < sprite->getPosition().x)
    {
        equis = -velocidad;

        if(ejex == true)
        {
            if(direc == 0)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 0, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 0;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 0, 75, 75));   
            }
        }
    }
    else if(((protagonista.getPosition().x) - 10) > sprite->getPosition().x)
    {
        equis = velocidad;

        if(ejex == true)
        {                
            if(direc == 3)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 3*75, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 3;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 3*75, 75, 75));   
            }
        }
    }
    else
    {
        equis = 0;            
    }          

    if((protagonista.getPosition().y + 10) < sprite->getPosition().y)
    {
        y = -velocidad;

        if(ejey == true)
        {
            if(direc == 2)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 2*75, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 2;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 2*75, 75, 75));   
            }
        }

    }
    else if((protagonista.getPosition().y - 10) > sprite->getPosition().y)
    {
        y = velocidad;

        if(ejey == true)
        {
            if(direc == 1)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 75, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 1;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 75, 75, 75));   
            }
        }
    }
    else
    {                
        y = 0;
    }
    
    return ejex;
}

void Zombie::detectarObstaculos(MapLoader* mapa, bool dominante){
    std::cout << "inicio detectar obstaculos " << posActual.x <<std::endl;
    std::cout << "sprite " << sprite->getPosition().x <<std::endl;
    std::cout << "equis " << equis <<std::endl;
    std::cout << "vel " << velocidad <<std::endl;
    std::cout << "vvvv" << fabs(velocidad) << std::endl;
    std::cout << "sprite " << sprite->getPosition().y <<std::endl;
    std::cout << "y " << y <<std::endl;
    if(!mapa->Colision(sprite->getPosition().x+(equis*(25/fabs(velocidad))), sprite->getPosition().y+(y*(25/fabs(velocidad))),1)){   
        std::cout << "despues del update2 " << posActual.x <<std::endl;//no se puede mover
        if(dominante){          //horizontal
            if(!mapa->Colision(sprite->getPosition().x+(equis*(25/fabs(velocidad))), sprite->getPosition().y-25,1)){
                if(!mapa->Colision(sprite->getPosition().x+(equis*(25/fabs(velocidad))), sprite->getPosition().y+25,1)){
                    if(!mapa->Colision(sprite->getPosition().x+(equis*(25/fabs(velocidad))), sprite->getPosition().y-50,1)){
                        if(!mapa->Colision(sprite->getPosition().x+(equis*(25/fabs(velocidad))), sprite->getPosition().y+50,1)){
                            if(sprite->getPosition().y>375){
                                equis=0;
                                y=-velocidad;
                            }else{
                                equis=0;
                                y=velocidad;
                            }
                        }else{
                            y=velocidad;
                        }
                    }else{
                        y=-velocidad;
                    }
                }else{
                    y=velocidad;
                }
            }else{
                y=-velocidad;
            }
        }else{                      //vertizal
            if(!mapa->Colision(sprite->getPosition().x-25, sprite->getPosition().y+(y*(25/fabs(velocidad))),1)){
                if(!mapa->Colision(sprite->getPosition().x+25, sprite->getPosition().y+(y*(25/fabs(velocidad))),1)){
                    if(!mapa->Colision(sprite->getPosition().x-50, sprite->getPosition().y+(y*(25/fabs(velocidad))),1)){
                        if(!mapa->Colision(sprite->getPosition().x+50, sprite->getPosition().y+(y*(25/fabs(velocidad))),1)){
                            if(sprite->getPosition().x>375){
                                equis=-velocidad;
                                y=0;
                            }else{
                                equis=velocidad;
                                y=0;
                            }
                        }else{
                            equis=velocidad;
                        }
                    }else{
                        equis=-velocidad;
                    }
                }else{
                    equis=velocidad;
                }
            }else{
                equis=-velocidad;
            }
        }
    }else{
        std::cout << "er!" << std::endl;
        obsMapa=false;
    }
    
    std::cout << "er!" << std::endl;
}

void Zombie::detectarZombie(std::vector<Zombie*> zombies, char direccion, MapLoader* mapa){
    sf::Time frecuencia;

    if(!colisionConZombies(zombies, direccion)){
        sprite->move(equis,y);
    }else {
        if(esquiva!=0){
            frecuencia = reloj.getElapsedTime();            
            if(frecuencia.asSeconds()>(10/velocidad)){
                esquiva=0;
                reloj.restart();
            }else{
                if(esquiva==1){
                    if(!colisionConZombies(zombies, 'W'))
                        sprite->move(0,-velocidad);
                }else if(esquiva==2){
                    if(!colisionConZombies(zombies, 'S'))
                        sprite->move(0,velocidad);
                }else if(esquiva==3){
                    if(!colisionConZombies(zombies, 'A'))
                        sprite->move(-velocidad,0);
                }else if(esquiva==4){
                    if(!colisionConZombies(zombies, 'D'))
                        sprite->move(velocidad,0);
                }
            }
        }else if(direccion=='Q'||direccion=='Z'||direccion=='E'||direccion=='C'){
            if(direccion=='Q'){
                if(esquiva==2 && !colisionConZombies(zombies, 'S') && mapa->Colision(sprite->getPosition().x, sprite->getPosition().y+velocidad,1))
                    sprite->move(0,velocidad);
                else if(esquiva==4 && !colisionConZombies(zombies, 'D') && mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y,1))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
                else if(!colisionConZombies(zombies, 'Z'))
                    sprite->move(-velocidad,velocidad);

            }else if(direccion=='E'){
                if(esquiva==2 && !colisionConZombies(zombies, 'S') && mapa->Colision(sprite->getPosition().x, sprite->getPosition().y+velocidad,1))
                    sprite->move(0,velocidad); 
                else if(esquiva==3 && !colisionConZombies(zombies, 'A') && mapa->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y,1))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
                else if(!colisionConZombies(zombies, 'C'))
                    sprite->move(velocidad,velocidad);
                
            }else if(direccion=='Z'){
                if(esquiva==1 && !colisionConZombies(zombies, 'W') && mapa->Colision(sprite->getPosition().x, sprite->getPosition().y-velocidad,1))
                    sprite->move(0,-velocidad);
                else if(esquiva==4 && !colisionConZombies(zombies, 'D') && mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y,1))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                else if(!colisionConZombies(zombies, 'Q'))
                    sprite->move(-velocidad,-velocidad);

            }else{
                if(esquiva==1 && !colisionConZombies(zombies, 'W') && mapa->Colision(sprite->getPosition().x, sprite->getPosition().y-velocidad,1))
                    sprite->move(0,-velocidad); 
                else if(esquiva==3 && !colisionConZombies(zombies, 'A') && mapa->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y,1))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                else if(!colisionConZombies(zombies, 'E')) 
                    sprite->move(velocidad,-velocidad);
                
            }
        }else{
            reloj.restart();
            if(direccion=='W' || direccion=='S'){ 
                if(!colisionConZombies(zombies, 'A')){
                    sprite->move(-velocidad,0);
                    esquiva=3;
                }else if(!colisionConZombies(zombies, 'D')){
                    sprite->move(velocidad,0);
                    esquiva=4;
                }
                
            }else {
                if(!colisionConZombies(zombies, 'W')){
                    sprite->move(0,-velocidad);
                    esquiva=1;
                }else if(!colisionConZombies(zombies, 'S')){
                    sprite->move(0,velocidad);
                    esquiva=2;
                } 
            }
        }
    }
}

bool Zombie::colisionConProta(sf::Sprite spriteProta, char direccion){
    
    sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
    spriteCopia->setTexture(*tex);

    if(direccion == 'S')
        spriteCopia->move(0, velocidad);
    else if(direccion == 'W')
        spriteCopia->move(0,-velocidad);
    else if(direccion == 'D')
        spriteCopia->move(velocidad, 0);
    else
        spriteCopia->move(-velocidad, 0);


    sf::FloatRect* box = new sf::FloatRect(spriteCopia->getGlobalBounds());
    box->width -= 70;
    box->left += 40;

    sf::FloatRect cajaProta = spriteProta.getGlobalBounds();
    if(box->intersects(cajaProta)){
        return true;
    }        
    return false;
}

bool Zombie::colisionConZombies(std::vector<Zombie*> zombies, char direccion){
    
    sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
    spriteCopia->setTexture(*tex);

    if(direccion == 'C')
        spriteCopia->move(velocidad, velocidad);
    else if(direccion == 'Z')
        spriteCopia->move(-velocidad, velocidad);
    else if(direccion == 'E')
        spriteCopia->move(velocidad, -velocidad);
    else if(direccion == 'Q')
        spriteCopia->move(-velocidad, -velocidad);
    else if(direccion == 'D')
        spriteCopia->move(velocidad, 0);
    else if(direccion == 'S')
        spriteCopia->move(0, velocidad);
    else if(direccion == 'A')
        spriteCopia->move(-velocidad, 0);
    else 
        spriteCopia->move(0, -velocidad);


    sf::FloatRect* box = new sf::FloatRect(spriteCopia->getGlobalBounds());
    
    
    sf::FloatRect* cajaZ;
    for(int i=0; i<zombies.size(); i++){
       cajaZ = zombies[i]->getBoundingBox();
       if(box->intersects(*cajaZ) && sprite->getPosition()!=zombies[i]->getSprite()->getPosition()){
           return true; 
       }
    }
    return false;
}
bool Zombie::colisionConBalas(std::vector<Arma*> armas){
    if(muriendo==false){
        for(int j=0; j<armas.size();j++){
            std::vector<Proyectil*> cargador = armas[j]->getCargador();
            for(int i=0; i<cargador.size();i++){
                if(boundingBox->intersects(cargador[i]->getSprite()->getGlobalBounds())){
                    armas[j]->eliminarProyectil(i);
                    recibirDanyo(armas[j]->getDanyo());
                    if(vida<=0){
                        muere();
                    }
                    return true;
                }
            }
        } 
    }
    return false;
}

bool Zombie::colisionConRecursos(std::vector<Recurso*> &recursos)
{
    //Recurso* r;
    for(int i = recursos.size() - 1 ;i >= 0; i--)
    {
        if(boundingBox->intersects(*recursos[i]->getBoundingBox()))
        {
            if(recursos[i]->getBloqueante()){
                return true;
            }
        }
    }
    return false;
}

bool Zombie::colisionConGranadas(std::vector<Arma*> armas){
    if(muriendo==false){
        for(int j=0; j<armas.size();j++){
            std::vector<Granada*> granadas = armas[j]->getSecundaria();
            for(int i=0; i<granadas.size(); i++){
                if(boundingBox->intersects(granadas[i]->getSprite()->getGlobalBounds()) && granadas[i]->estaExplotando()){
                    recibirDanyo(granadas[i]->getDanyo());
                    if(vida<=0){
                        muere();
                        //std::cout<<"Palmé"<<std::endl;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
void Zombie::recibirDanyo(int danyo){
    vida -= danyo;
}

float Zombie::getDanyo(){
    return danyo;
}

bool Zombie::getEstado(){
    return estaVivo;
}

void Zombie::atacar(){
    sprite->setTextureRect(sf::IntRect(contA*75,300+direc*75,75,75));
    contA++;
    if(contA==5){
        atacando=false;
        cont=0;
        //audios->ataqueZombie.setVolume(50);
        audios->ataqueZombie.play();
    }
}

void Zombie::actualizaMuerte(){
    sprite->setTextureRect(sf::IntRect(450+direc*75,cont*75,75,75));
    if(cont==5)
        estaVivo=false;
    
    cont++;
}

void Zombie::muere(){
    sprite->setOrigin(75/2,75/2);
    sprite->setTextureRect(sf::IntRect(450+direc*75,0,75,75));
    sprite->setPosition(sprite->getPosition().x,sprite->getPosition().y+75/2);
    cont=1;
    muriendo=true;
}
