#ifndef DTO_H
#define DTO_H

#include "const.h"
#include "position.h"

namespace ServerSide {
class Protocol;
}

namespace ClientSide {
class Protocol;
}

// ---------------------------------- DTO INTERFACE ------------------------

class Dto {
public:
    const Commands c;

    /*

    */
    explicit Dto(const Commands c);
    /*

    */
    virtual void send(ServerSide::Protocol& protocol) = 0;
    /*

    */
    virtual void render() = 0;
    /*

    */
    virtual ~Dto() = default;
};

// ----------------------------------- MOVE DTO ------------------------------

class MoveDto: public Dto {
public:
    const Position pos;
    const bool is_walking;
    const bool facing_right;

    /*
        @brief Construye el dto, principalmente vamos a utilizar este constructor del lado del
       servidor

        @param x Posicion en x del gusano
        @param y Posiicon en y del gusano
        @param is_walking Indica si el gusano se sigue moviendo o no
        @param facing_right Indica si el gusano mira hacia la derecha o no
    */
    explicit MoveDto(const float& x, const float& y, const bool& is_walking,
                     const bool& facing_right);
    /*
        @brief Construye el dto, principalmente vamos a utilizar este constructor del lado del
       cliente

        @param protocol Protocolo del cliente para recibir los datos necesarios para construir el
       dto
    */
    explicit MoveDto(ClientSide::Protocol& protocol);

    ~MoveDto() = default;
};

class NullDto: public Dto {

    NullDto();
    /*
        @brief Construye el dto, principalmente vamos a utilizar este constructor del lado del
       cliente

        @param protocol Protocolo del cliente para recibir los datos necesarios para construir el
       dto
    */
    explicit NullDto(ClientSide::Protocol& protocol);

    ~NullDto() = default;
};

#endif
