#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <iostream>
#include <list>
#include <set>
using namespace std;

struct state{
  int fil;
  int col;
  Orientacion brujula;
  bool bikini;
  bool zapatillas;
};

class ComportamientoJugador : public Comportamiento{
  private:
  // Declarar aquí las variables de estado
    state current_state, destino;
    Action last_action;
    int girar;
    int pasosGirar;
    bool bien_situado;
    bool girar_derecha;
    bool hayPlan;
    int contador;
    list<Action> plan;

  // Funciones privadas
    void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st,
							                vector<vector<unsigned char>> &matriz);
    void ActualizaPosicion();
    void Reiniciar ();

    Action EjecutaAccion(Sensores sensores);
    Action Posicionarme(Sensores sensores);
    Action IrObjeto(Sensores sensores);
    Action Recargar(Sensores sensores);
    Action HuirLobos(Sensores sensores);
    Action EvitarAldeanos(Sensores sensores);
    Action EntrarMuro(Sensores sensores);
    Action EvitarAgua(Sensores sensores);
    Action EvitarBosque(Sensores sensores);


    bool HayObstaculo(const vector <unsigned char> &terreno);
    bool VeoZapatos(const vector <unsigned char> &terreno);
    bool VeoBikini(const vector <unsigned char> &terreno);
    bool LoboALaVista(const vector <unsigned char> &superficie);
    bool HayAldeanoDelante(const vector <unsigned char> &superficie);
    bool CasillaRecarga(const vector <unsigned char> &terreno);
    bool CasillaPosicionamiento(const vector <unsigned char> &terreno);
    bool VeoPuertaMuro(const vector <unsigned char> &terreno);
    bool HayMuroDelante(const vector <unsigned char> &terreno);

    void PintaPlan(list<Action> plan);

    bool pathFinding(int level, const state &origen, const state &destino, list<Action> &plan);
    
    bool pathFinding_Profundidad(const state &origen, const state &destino, list<Action> &plan);
    bool pathFinding_Anchura(const state &origen, const state &destino, list<Action> &plan);
    bool pathFinding_Costo(const state &origen, const state &destino, list<Action> &plan);


  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      current_state.brujula = norte;
      current_state.fil = current_state.col = 99;
      current_state.bikini = false;
      current_state.zapatillas = false;

      last_action = actIDLE;
      bien_situado = false;
      girar_derecha = false;
      hayPlan = false;
      contador = 0;

      pasosGirar = (rand()%50) + 1; //Pasos aleatorios que se daran antes de girar

      destino.brujula = norte;
      destino.fil = destino.col = -1;
    }

    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      current_state.brujula = norte;
      current_state.fil = current_state.col = 99;
      current_state.bikini = false;
      current_state.zapatillas = false;

      last_action = actIDLE;
      bien_situado = false;
      girar_derecha = false;
      hayPlan = false;
      contador = 0;

      pasosGirar = (rand()%50) + 1; //Pasos aleatorios que se daran antes de girar

      destino.brujula = norte;
      destino.fil = destino.col = -1;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const state &st, const list<Action> &plan);
    int ValorCasilla(int f, int c);
 
};




#endif
