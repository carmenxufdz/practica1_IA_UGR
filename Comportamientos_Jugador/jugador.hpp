#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state{
  int fil;
  int col;
  Orientacion brujula;
  bool bikini;
  bool zapatillas;

};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      current_state.brujula = norte;
      current_state.fil = current_state.col = 99;
      current_state.bikini = false;
      current_state.zapatillas = false;
      last_action = actIDLE;
      girar = false;
      bien_situado = false;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  // Declarar aquí las variables de estado
    state current_state;
    Action last_action;
    bool girar;
    bool bien_situado;
  
  // Funciones privadas
    void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st,
							                vector<vector<unsigned char>> &matriz);
    void ActualizaPosicion();
    Action EjecutaAccion(Sensores sensores);
    Action Posicionarme(Sensores sensores);
    Action IrObjeto(Sensores sensores);
    
    bool VeoZapatos(const vector <unsigned char> &terreno);
    bool VeoBikini(const vector <unsigned char> &terreno);
    bool LoboALaVista(const vector <unsigned char> &superficie, int &pos);
    bool HayObstaculoDelante(const vector <unsigned char> &terreno);
    bool HayAldeanoDelante(const vector <unsigned char> &superficie);
    bool CasillaRecarga(const vector <unsigned char> &terreno);
    bool CasillaPosicionamiento(const vector <unsigned char> &terreno, int &pos);

    
    void Recargar();
};




#endif
