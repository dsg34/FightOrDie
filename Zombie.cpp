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
    boundingBox->width -= 55;
    boundingBox->left += 25;
    boundingBox->height -= 55;
    boundingBox->top += 25;
    
    esquiva = 0;
    esqDir = false;
    obsMapa = true;
    reloj.restart();
    audios = Sonidos::Instance();
}

Zombie::Zombie(const Zombie& orig) : Personaje(orig){
}

Zombie::~Zombie() 
{
    
}

int Zombie::update(sf::Sprite protagonista , std::vector<Zombie*> zombies, std::vector<Arma*> armas, std::vector<Recurso*> recursos, MapLoader* mapa){
    posAnterior = posActual;
    *boundingBox = sprite->getGlobalBounds();
    int ataque = 0;
    bool dominante = false;
    sf::Time frecuencia;
    obsMapa = true;
    boundingBox->width -= 55;
    boundingBox->left += 25;
    boundingBox->height -= 55;
    boundingBox->top += 25;
    if(muriendo==false){
        colisionConBalas(armas);
        colisionConGranadas(armas);
        
        if(atacando==true){        
            frecuencia = reloj.getElapsedTime();            
            if(frecuencia.asSeconds()>0.1){
                atacar();
                reloj.restart();
            }
        }else{
            dominante = calcularDireccion(protagonista);

            char direccion;
            if(equis>0 &&(y==0||y>0))
                direccion = 'D';
            else if(y>0 &&(equis==0||equis<0))
                direccion = 'S';
            else if(equis<0&&(y==0||y<0))
                direccion = 'A';
            else
                direccion = 'W';

            if(colisionConProta(protagonista, direccion)){
                ataque=1;
                contA=0;
                atacando=true;
            }else if(colisionConRecursos(recursos)){
                ataque=2;
                contA=0;
                atacando=true;
            }else{
                
                detectarObstaculos(mapa, dominante);
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
                if(obsMapa==false)
                    detectarZombie(zombies, direccion, mapa);
                else if(!colisionConZombies(zombies, direccion))
                    sprite->move(equis,y);
                
                posActual = sprite->getPosition();
            }
        }
    }else{
        frecuencia = reloj.getElapsedTime();            
        if(frecuencia.asSeconds()>0.1){
            actualizaMuerte();
            reloj.restart();
        }    
    }
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
    if(!mapa->Colision(sprite->getPosition().x+equis, sprite->getPosition().y+y,1)){          //no se puede mover
        if(dominante){          //horizontal
            if(mapa->Colision(sprite->getPosition().x, sprite->getPosition().y-velocidad,1) && sprite->getPosition().y>350){
                equis=0;
                y=-velocidad;
            }else if(mapa->Colision(sprite->getPosition().x, sprite->getPosition().y+velocidad,1) && sprite->getPosition().y<350){
                equis=0;
                y=velocidad;
            }
        }else{                      //vertizal
            if(mapa->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y,1) && sprite->getPosition().x>150){
                equis=-velocidad;
                y=0;
            }else if(mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y,1) && sprite->getPosition().x<1150){
                equis=velocidad;
                y=0;
            }
        }
    }else
        obsMapa=false;
}

void Zombie::detectarZombie(std::vector<Zombie*> zombies, char direccion, MapLoader* mapa){
    sf::Time frecuencia;

    if(esquiva!=0){
        frecuencia = reloj.getElapsedTime();            
        if(frecuencia.asSeconds()>(7/velocidad)){
            if(esquiva==1){
                if(colisionConZombies(zombies, 'W') && !colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
            }else if(esquiva==2){
                if(colisionConZombies(zombies, 'S') && !colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
            }else if(esquiva==3){
                if(colisionConZombies(zombies, 'A') && !colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
            }else if(esquiva==4){
                if(colisionConZombies(zombies, 'D') && !colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
            }
            esquiva=0;
            reloj.restart();
        }else{
            if(esquiva==1){
                if(!colisionConZombies(zombies, 'W'))
                    sprite->move(equis,-velocidad);
            }else if(esquiva==2){
                if(!colisionConZombies(zombies, 'S'))
                    sprite->move(equis,velocidad);
            }else if(esquiva==3){
                if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,y);
            }else if(esquiva==4){
                if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,y);
            }
        }
    }else if(!colisionConZombies(zombies, direccion)){
        sprite->move(equis,y);
    }else {
        
        if(direccion=='Q'||direccion=='Z'||direccion=='E'||direccion=='C'){
            if(direccion=='Q'){
                if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
                else if(!colisionConZombies(zombies, 'Z'))
                    sprite->move(-velocidad,velocidad);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);

            }else if(direccion=='E'){
                if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
                else if(!colisionConZombies(zombies, 'C'))
                    sprite->move(velocidad,velocidad);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                
            }else if(direccion=='Z'){
                if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                else if(!colisionConZombies(zombies, 'Q'))
                    sprite->move(-velocidad,-velocidad);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);

            }else{
                if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                else if(!colisionConZombies(zombies, 'E')) 
                    sprite->move(velocidad,-velocidad);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
            }
        }else{
            reloj.restart();
            if(direccion=='W' || direccion=='S'){ 
                if(!colisionConZombies(zombies, 'A') && esqDir==false){
                    sprite->move(-velocidad,0);
                    esquiva=3;
                    esqDir=true;
                }else if(!colisionConZombies(zombies, 'D') && esqDir==true){
                    sprite->move(velocidad,0);
                    esquiva=4;
                    esqDir=false;
                }else if(!colisionConZombies(zombies, 'A')){
                    sprite->move(-velocidad,0);
                    esquiva=3;
                }else if(!colisionConZombies(zombies, 'D')){
                    sprite->move(velocidad,0);
                    esquiva=4;
                }
            }else {
                if(!colisionConZombies(zombies, 'W') && esqDir==false){
                    sprite->move(0,-velocidad);
                    esquiva=1;
                    esqDir=true;
                }else if(!colisionConZombies(zombies, 'S') && esqDir==true){
                    sprite->move(0,velocidad);
                    esquiva=2;
                    esqDir=false;
                }else if(!colisionConZombies(zombies, 'W')){
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
    box->width -= 55;
    box->left += 25;
    box->height -= 55;
    box->top += 25;  

    sf::FloatRect cajaProta = spriteProta.getGlobalBounds();
    if(box->intersects(cajaProta)){
        return true;
    }        
    return false;
}

bool Zombie::colisionConZombies(std::vector<Zombie*> zombies, char direccion){
    
    sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
    spriteCopia->setTexture(*tex);
    sf::FloatRect* box = new sf::FloatRect(spriteCopia->getGlobalBounds());
    sf::FloatRect* cajaZ;
    if(direccion == 'C')
        spriteCopia->move(velocidad, velocidad);
    else if(direccion == 'Z')
        spriteCopia->move(-velocidad, velocidad);
    else if(direccion == 'E')
        spriteCopia->move(velocidad, -velocidad);
    else if(direccion == 'Q')
        spriteCopia->move(-velocidad, -velocidad);
    else if(direccion == 'D'){
        spriteCopia->move(velocidad, 0);
    }else if(direccion == 'S')
        spriteCopia->move(0, velocidad);
    else if(direccion == 'A')
        spriteCopia->move(-velocidad, 0);
    else 
        spriteCopia->move(0, -velocidad);


    
    for(int i=0; i<zombies.size(); i++){
       cajaZ = zombies[i]->getBoundingBox();
       if(box->intersects(*cajaZ) && sprite->getPosition()!=zombies[i]->getSprite()->getPosition()){
            if(direccion == 'D'){
                if(spriteCopia->getPosition().x > zombies[i]->getSprite()->getPosition().x)
                    return false;
            }else if(direccion == 'S'){
                if(spriteCopia->getPosition().y > zombies[i]->getSprite()->getPosition().y)
                    return false;
            }else if(direccion == 'A'){
                if(spriteCopia->getPosition().x < zombies[i]->getSprite()->getPosition().x)
                    return false;
            }else{
                if(spriteCopia->getPosition().y < zombies[i]->getSprite()->getPosition().y)
                    return false;
            }
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
    for(int i=0;i<recursos.size();i++){
        if(boundingBox->intersects(recursos[i]->getSprite()->getGlobalBounds())){
            if(recursos[i]->getBloqueante()==1){
                recursos[i]->setResistencia(recursos[i]->getResistencia()-danyo);
                if(recursos[i]->getResistencia()<=0){
                    recursos[i]->setBloqueante(0);
                    recursos[i]->setExiste(0);
                }
                    
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
