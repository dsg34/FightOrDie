
#ifndef MENUFACTORY_H
#define	MENUFACTORY_H
#include "Menu.h"

class MenuFactory {
public:
    MenuFactory();
    MenuFactory(const MenuFactory& orig);
    virtual ~MenuFactory();
    Menu* hacerMenu(int x, int y, int id);

private:
    Menu* menu;
};

#endif	/* MENUFACTORY_H */

