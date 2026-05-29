#pragma once

#include <iostream>
//adaptado de Burda Canal do vídeo 2
template<typename TL>
class Coord{
public:
    TL x;
    TL y;

    Coord(TL x, TL y);
    Coord();
    ~Coord(){ }
    
    
    
};

typedef Coord<double> CoordD;
typedef Coord<int> CoordI;
typedef Coord<float>CoordF;

template <typename TL>
Coord<TL>::Coord(TL x, TL y): x(x),y(y){ } //inicializadora com valores

template <typename TL>
Coord<TL>::Coord(){
    this->x = 0;
    this->y = 0; //valores default
}
