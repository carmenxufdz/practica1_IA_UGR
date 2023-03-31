#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;



Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;
	/*
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Noreste" << endl; break;
		case 2: cout << "Este" << endl; break;
		case 3: cout << "Sureste" << endl; break;
		case 4: cout << "Sur " << endl; break;
		case 5: cout << "Suroeste" << endl; break;
		case 6: cout << "Oeste" << endl; break;
		case 7: cout << "Noroeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;
	*/

	// Determinar el efecto de la ultima accion enviada
	ActualizaPosicion();
	
	accion = EjecutaAccion(sensores);

	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

void ComportamientoJugador::PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st,
							vector<vector<unsigned char>> &matriz){
	matriz[st.fil][st.col] = terreno[0];

	switch (st.brujula){
		case norte:
			matriz[st.fil-1][st.col-1] = terreno[1];
			matriz[st.fil-1][st.col] = terreno[2];
			matriz[st.fil-1][st.col+1] = terreno[3];
			matriz[st.fil-2][st.col-2] = terreno[4];
			matriz[st.fil-2][st.col-1] = terreno[5];
			matriz[st.fil-2][st.col] = terreno[6];
			matriz[st.fil-2][st.col+1] = terreno[7];
			matriz[st.fil-2][st.col+2] = terreno[8];
			matriz[st.fil-3][st.col-3] = terreno[9];
			matriz[st.fil-3][st.col-2] = terreno[10];
			matriz[st.fil-3][st.col-1] = terreno[11];
			matriz[st.fil-3][st.col] = terreno[12];
			matriz[st.fil-3][st.col+1] = terreno[13];
			matriz[st.fil-3][st.col+2] = terreno[14];
			matriz[st.fil-3][st.col+3] = terreno[15];
		break;

		case noreste:
			matriz[st.fil-1][st.col] = terreno[1];
			matriz[st.fil-1][st.col+1] = terreno[2];
			matriz[st.fil][st.col+1] = terreno[3];
			matriz[st.fil-2][st.col] = terreno[4];
			matriz[st.fil-2][st.col+1] = terreno[5];
			matriz[st.fil-2][st.col+2] = terreno[6];
			matriz[st.fil-1][st.col+2] = terreno[7];
			matriz[st.fil][st.col+2] = terreno[8];
			matriz[st.fil-3][st.col] = terreno[9];
			matriz[st.fil-3][st.col+1] = terreno[10];
			matriz[st.fil-3][st.col+2] = terreno[11];
			matriz[st.fil-3][st.col+3] = terreno[12];
			matriz[st.fil-2][st.col+3] = terreno[13];
			matriz[st.fil-1][st.col+3] = terreno[14];
			matriz[st.fil][st.col+3] = terreno[15];
		break;

		case este:
			matriz[st.fil-1][st.col+1] = terreno[1];
			matriz[st.fil][st.col+1] = terreno[2];
			matriz[st.fil+1][st.col+1] = terreno[3];
			matriz[st.fil-2][st.col+2] = terreno[4];
			matriz[st.fil-1][st.col+2] = terreno[5];
			matriz[st.fil][st.col+2] = terreno[6];
			matriz[st.fil+1][st.col+2] = terreno[7];
			matriz[st.fil+2][st.col+2] = terreno[8];
			matriz[st.fil-3][st.col+3] = terreno[9];
			matriz[st.fil-2][st.col+3] = terreno[10];
			matriz[st.fil-1][st.col+3] = terreno[11];
			matriz[st.fil][st.col+3] = terreno[12];
			matriz[st.fil+1][st.col+3] = terreno[13];
			matriz[st.fil+2][st.col+3] = terreno[14];
			matriz[st.fil+3][st.col+3] = terreno[15];
		break;
		
		case sureste:
			matriz[st.fil][st.col+1] = terreno[1];
			matriz[st.fil+1][st.col+1] = terreno[2];
			matriz[st.fil+1][st.col] = terreno[3];
			matriz[st.fil][st.col+2] = terreno[4];
			matriz[st.fil+1][st.col+2] = terreno[5];
			matriz[st.fil+2][st.col+2] = terreno[6];
			matriz[st.fil+2][st.col+1] = terreno[7];
			matriz[st.fil+2][st.col] = terreno[8];
			matriz[st.fil][st.col+3] = terreno[9];
			matriz[st.fil+1][st.col+3] = terreno[10];
			matriz[st.fil+2][st.col+3] = terreno[11];
			matriz[st.fil+3][st.col+3] = terreno[12];
			matriz[st.fil+3][st.col+2] = terreno[13];
			matriz[st.fil+3][st.col+1] = terreno[14];
			matriz[st.fil+3][st.col] = terreno[15];
		break;

		case sur:
			matriz[st.fil+1][st.col+1] = terreno[1];
			matriz[st.fil+1][st.col] = terreno[2];
			matriz[st.fil+1][st.col-1] = terreno[3];
			matriz[st.fil+2][st.col+2] = terreno[4];
			matriz[st.fil+2][st.col+1] = terreno[5];
			matriz[st.fil+2][st.col] = terreno[6];
			matriz[st.fil+2][st.col-1] = terreno[7];
			matriz[st.fil+2][st.col-2] = terreno[8];
			matriz[st.fil+3][st.col+3] = terreno[9];
			matriz[st.fil+3][st.col+2] = terreno[10];
			matriz[st.fil+3][st.col+1] = terreno[11];
			matriz[st.fil+3][st.col] = terreno[12];
			matriz[st.fil+3][st.col-1] = terreno[13];
			matriz[st.fil+3][st.col-2] = terreno[14];
			matriz[st.fil+3][st.col-3] = terreno[15];
		break;

		case suroeste:
			matriz[st.fil+1][st.col] = terreno[1];
			matriz[st.fil+1][st.col-1] = terreno[2];
			matriz[st.fil][st.col-1] = terreno[3];
			matriz[st.fil+2][st.col] = terreno[4];
			matriz[st.fil+2][st.col-1] = terreno[5];
			matriz[st.fil+2][st.col-2] = terreno[6];
			matriz[st.fil+1][st.col-2] = terreno[7];
			matriz[st.fil][st.col-2] = terreno[8];
			matriz[st.fil+3][st.col] = terreno[9];
			matriz[st.fil+3][st.col-1] = terreno[10];
			matriz[st.fil+3][st.col-2] = terreno[11];
			matriz[st.fil+3][st.col-3] = terreno[12];
			matriz[st.fil+2][st.col-3] = terreno[13];
			matriz[st.fil+1][st.col-3] = terreno[14];
			matriz[st.fil][st.col-3] = terreno[15];
		break;

		case oeste:
			matriz[st.fil+1][st.col-1] = terreno[1];
			matriz[st.fil][st.col-1] = terreno[2];
			matriz[st.fil-1][st.col-1] = terreno[3];
			matriz[st.fil+2][st.col-2] = terreno[4];
			matriz[st.fil+1][st.col-2] = terreno[5];
			matriz[st.fil][st.col-2] = terreno[6];
			matriz[st.fil-1][st.col-2] = terreno[7];
			matriz[st.fil-2][st.col-2] = terreno[8];
			matriz[st.fil+3][st.col-3] = terreno[9];
			matriz[st.fil+2][st.col-3] = terreno[10];
			matriz[st.fil+1][st.col-3] = terreno[11];
			matriz[st.fil][st.col-3] = terreno[12];
			matriz[st.fil-1][st.col-3] = terreno[13];
			matriz[st.fil-2][st.col-3] = terreno[14];
			matriz[st.fil-3][st.col-3] = terreno[15];
		break;

		case noroeste:
			matriz[st.fil][st.col-1] = terreno[1];
			matriz[st.fil-1][st.col-1] = terreno[2];
			matriz[st.fil-1][st.col] = terreno[3];
			matriz[st.fil][st.col-2] = terreno[4];
			matriz[st.fil-1][st.col-2] = terreno[5];
			matriz[st.fil-2][st.col-2] = terreno[6];
			matriz[st.fil-2][st.col-1] = terreno[7];
			matriz[st.fil-2][st.col] = terreno[8];
			matriz[st.fil][st.col-3] = terreno[9];
			matriz[st.fil-1][st.col-3] = terreno[10];
			matriz[st.fil-2][st.col-3] = terreno[11];
			matriz[st.fil-3][st.col-3] = terreno[12];
			matriz[st.fil-3][st.col-2] = terreno[13];
			matriz[st.fil-3][st.col-1] = terreno[14];
			matriz[st.fil-3][st.col] = terreno[15];
		break;
	}


}

void ComportamientoJugador::ActualizaPosicion(){
		
		int a;

		switch (last_action){
		case actFORWARD: 
			switch(current_state.brujula){
				case norte: current_state.fil--; break;
				case noreste: current_state.fil--; current_state.col++; break;
				case este: current_state.col++; break;
				case sureste: current_state.fil++; current_state.col++; break;
				case sur: current_state.fil++; break;
				case suroeste: current_state.fil++; current_state.col--; break;
				case oeste: current_state.col--; break;
				case noroeste: current_state.fil--; current_state.col--; break;
			}
			break;
		case actTURN_SL: 
			a = current_state.brujula;
			a = (a+7)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			girar = (rand()%2 == 0);
			break;
		case actTURN_SR: 
			a = current_state.brujula;
			a = (a+1)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			girar = (rand()%2 == 0);
			break;
		case actTURN_BL: 
			a = current_state.brujula;
			a = (a+5)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BR: 
			a = current_state.brujula;
			a = (a+3)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
	}
}

Action ComportamientoJugador::EjecutaAccion(Sensores sensores){

	Action accion = actIDLE;

	if(sensores.posF != -1 and !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	if(bien_situado){
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
	}

	// Decidir la nueva acción
	if(!bien_situado){
		accion = Posicionarme(sensores);
	} 
	else if((VeoZapatos(sensores.terreno) and !current_state.zapatillas) 
	or (VeoBikini(sensores.terreno) and !current_state.bikini)){
		accion = IrObjeto(sensores);
	}
	else if((sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S'
		or sensores.terreno[2] == 'G' or sensores.terreno[2]=='X' 
		or sensores.terreno[2] == 'K' or sensores.terreno[2] == 'D'
		or sensores.terreno[2]=='A' or sensores.terreno[2]=='B') 
		and sensores.superficie[2] == '_' and !HayObstaculoDelante(sensores.terreno)){
			accion = actFORWARD;
			sensores.colision = false;
	} else if(!girar and sensores.superficie[2] != 'l'){
		accion = actTURN_SL;
		girar = (rand()%2 == 0);
		if(last_action == actFORWARD)
			sensores.colision = true;
	} else if(girar and sensores.superficie[2] != 'l'){
		accion = actTURN_SR;
		girar = (rand()%2 == 0);
		if(last_action == actFORWARD)
			sensores.colision = true;
	} else if(sensores.superficie[2] == 'l'){
		sensores.colision = true;
		accion = actIDLE;
		bien_situado = false;
		sensores.reset = true;
	}

	// Recordar la última acción
	last_action = accion;

	return accion;
}

bool ComportamientoJugador::LoboALaVista(const vector <unsigned char> &superficie, int &pos){
	for(int i=1; i<16; i++)
		if(superficie[i]=='l')
			return true;

	return false;
}

bool ComportamientoJugador::HayObstaculoDelante(const vector <unsigned char> &terreno){
	
	if(terreno[6]=='M' or terreno[6]=='P')
		return true;
	if(terreno[12]=='M' or terreno[12]=='P')
		return true;
	else
		return false;
}

bool ComportamientoJugador::VeoZapatos(const vector <unsigned char> &terreno){
	for(int i=1; i<16; i++)
		if(terreno[i] == 'D'){
			return true;
		}			
	return false;
}

bool ComportamientoJugador::VeoBikini(const vector <unsigned char> &terreno){
	for(int i=1; i<16; i++)
		if(terreno[i] == 'K'){
			return true;
		}			
	return false;
}

bool ComportamientoJugador::CasillaPosicionamiento(const vector <unsigned char> &terreno, int &pos){
	
	for(int i=1; i<16; i++)
		if(terreno[i]=='G'){
			pos = i;
			return true;
		}			
	return false;
}

Action ComportamientoJugador::IrObjeto(Sensores sensores){
	Action accion = actIDLE;

	if(sensores.terreno[1]=='K' or sensores.terreno[1]=='D')
			accion = actTURN_SL;
	else if(sensores.terreno[2]=='K' or sensores.terreno[2]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[3]=='K' or sensores.terreno[3]=='D')
			accion = actTURN_SR;
	else if(sensores.terreno[4]=='K' or sensores.terreno[4]=='D')
			accion = actTURN_SL;
	else if(sensores.terreno[5]=='K' or sensores.terreno[5]=='D')
			accion = actTURN_SL;
	else if(sensores.terreno[6]=='K' or sensores.terreno[6]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[7]=='K' or sensores.terreno[7]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[8]=='K' or sensores.terreno[8]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[9]=='K' or sensores.terreno[9]=='D')
			accion = actTURN_SL;
	else if(sensores.terreno[10]=='K' or sensores.terreno[10]=='D')
			accion = actTURN_SL;
	else if(sensores.terreno[11]=='K' or sensores.terreno[11]=='D')
			accion = actTURN_SL;
	else if(sensores.terreno[12]=='K' or sensores.terreno[12]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[13]=='K' or sensores.terreno[13]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[14]=='K' or sensores.terreno[14]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[15]=='K' or sensores.terreno[15]=='D')
			accion = actFORWARD;
	
	if(sensores.terreno[0]=='K'){
		current_state.bikini = true;
	}
	if(sensores.terreno[0] == 'D'){
		current_state.zapatillas = true;
	}

	last_action = accion;
	return accion;
}

Action ComportamientoJugador::Posicionarme(Sensores sensores){
	
	Action accion = actIDLE;
	int pos;

	if(CasillaPosicionamiento(sensores.terreno, pos)){
		switch(pos){
			case 1: 
				accion = actTURN_SL;
				break;
			case 2: 
				accion = actFORWARD;
				break;

			case 3: 
				accion = actTURN_SR;
				break;
			case 4: 
				accion = actTURN_SL;
				break;
			case 5: 
				accion = actTURN_SL;
				break;
			case 6: 
				accion = actFORWARD;
				break;
			case 7: 
				accion = actFORWARD;
				break;
			case 8: 
				accion = actFORWARD;
				break;
			case 9: 
				accion = actTURN_SL;
				break;
			case 10: 
				accion = actTURN_SL;
				break;
			case 11: 
				accion = actTURN_SL;
				break;
			case 12: 
				accion = actFORWARD;
				break;
			case 13: 
				accion = actFORWARD;
				break;
			case 14: 
				accion = actFORWARD;
				break;
			case 15: 
				accion = actFORWARD;
				break;
		}
	}

	else if((VeoZapatos(sensores.terreno) and !current_state.zapatillas) 
	or (VeoBikini(sensores.terreno) and !current_state.bikini)){
		accion = IrObjeto(sensores);
	}

	else if((sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S'
		or sensores.terreno[2] == 'G' or sensores.terreno[2]=='X' 
		or sensores.terreno[2] == 'K' or sensores.terreno[2] == 'D'
		or sensores.terreno[2]=='A' or sensores.terreno[2]=='B') 
		and sensores.superficie[2] == '_' and !HayObstaculoDelante(sensores.terreno)){
			accion = actFORWARD;
	} else if(!girar and sensores.superficie[2] != 'l'){
		accion = actTURN_SL;
		girar = (rand()%2 == 0);
		if(last_action == actFORWARD)
			sensores.colision = true;
	} else if(girar and sensores.superficie[2] != 'l'){
		accion = actTURN_SR;
		girar = (rand()%2 == 0);
		if(last_action == actFORWARD)
			sensores.colision = true;
	} else if(sensores.superficie[2] == 'l'){
		sensores.colision = true;
		accion = actIDLE;
		bien_situado = false;
		sensores.reset = true;
	}

	// Recordar la última acción
	last_action = accion;

	if(sensores.terreno[0]=='G'){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	return accion;
}