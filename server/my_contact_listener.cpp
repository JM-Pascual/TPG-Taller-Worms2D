#include "my_contact_listener.h"

void My_contact_listener::BeginContact(b2Contact *contact) {

    //Fixtures que colisionan(sus hit box se superponen, no quiere decir que los bodies se toquen realmente)
    //Tengo que usar de alguna manera el user data para ver que cuerpo pertenece a que feature
    //b2Fixture* fixtureA = contact->GetFixtureA();
    //b2Fixture* fixtureB = contact->GetFixtureB();

    // Access user data from fixtures.
    //int* dataA = reinterpret_cast<int*>(fixtureA->GetUserData().pointer); //Todo ver bien el tema del casteo
    //int* dataB = reinterpret_cast<int*>(fixtureB->GetUserData().pointer);

    //if(bodyA.)

    //Lo que quiero hacer es que si el contacto es entre una bazooka y un worm lo que tiene que pasar es poner un booleano en la bazooka
    //avisando si esta colisionando o no y aplicar un metodo en el cual genero la explosión con las caracteristicas esperadas
}

void My_contact_listener::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
}

void My_contact_listener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    b2ContactListener::PreSolve(contact, oldManifold);
}

void My_contact_listener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
    b2ContactListener::PostSolve(contact, impulse);
}
