#include "my_contact_listener.h"
#include <iostream>

void My_contact_listener::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);

    //Fixtures que colisionan(sus hit box se superponen, no quiere decir que los bodies se toquen realmente)
    //Tengo que usar de alguna manera el user data para ver que cuerpo pertenece a que feature
    auto contact1 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    auto contact2 = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    // Access user data from fixtures.
    auto* dataA = reinterpret_cast<Entity*>(contact1); //Todo ver bien el tema del casteo
    auto* dataB = reinterpret_cast<Entity*>(contact2);

    if (dataA && dataB){
        dataA->start_contact();
        dataB->start_contact();


        //Agrego ambos elementos a una lista y luego de hacer el step veo si el elemeto tiene que ser eliminado o no

        if(dataA->life_end()){
            //Agreo al vector y luego lo elimino afuera
        }
        if(dataB->life_end()){
            //Agreo al vector y luego lo elimino afuera
        }
    }
    //Lo que quiero hacer es que si el contacto es entre una bazooka y un worm lo que tiene que pasar es poner un booleano en la bazooka
    //avisando si esta colisionando o no y aplicar un metodo en el cual genero la explosión con las caracteristicas esperadas
}

void My_contact_listener::EndContact(b2Contact *contact) {
    auto contact2 = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    auto contact1 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;


    // Access user data from fixtures.
    auto* dataB = reinterpret_cast<Entity*>(contact2);
    auto* dataA = reinterpret_cast<Entity*>(contact1); //Todo ver bien el tema del casteo


    //Seteo que se terminó la colisión


    //Ahora lo que hago es meter aquellos cuerpos en una lista que quiero que sean descartados
    //Tengo que ver primero que tipo de dato es:
    //  -En el caso deq que sea una bazooka tiene que explotar y borrarse luego de la primera colisión
    //  -En el caso de que sea un worm recién se va a eliminar una vez que no tenga más vida
    //  -En el caso de la barra no importa si recibe una colisión, nunca la agrego a la lista
    if (dataA && dataB) {
        dataA->end_contact();
        dataB->end_contact();
    }
}

void My_contact_listener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    //b2ContactListener::PreSolve(contact, oldManifold);
}

void My_contact_listener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
    b2ContactListener::PostSolve(contact, impulse);
}
