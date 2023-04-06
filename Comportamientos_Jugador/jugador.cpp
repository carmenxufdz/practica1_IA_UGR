#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

bool EsObstaculo(unsigned char casilla){
    if (casilla=='P' or casilla=='M' or casilla =='D')
    	return true;
    else
    	return false;
 }


Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	ActualizaPosicion();

	if(sensores.reset)
		Reiniciar();
	

	if(sensores.posF != -1 and !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	if(bien_situado){
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
	}

	if(sensores.terreno[0]=='K'){
		current_state.bikini = true;
	}

	if(sensores.terreno[0] == 'D'){
		current_state.zapatillas = true;
	}

	// Decidir la nueva acción
	if(LoboALaVista(sensores.superficie)==true){
		accion = HuirLobos(sensores);
	}
	if(HayAldeanoDelante(sensores.superficie)==true){
		accion = EvitarAldeanos(sensores);
	}	
	
	else if(!bien_situado and CasillaPosicionamiento(sensores.terreno)==true){
		accion = Posicionarme(sensores);
	}

	else if(VeoPuertaMuro(sensores.terreno)==true){
		accion = EntrarMuro(sensores);
	}
	else if(sensores.terreno[0] == 'X' and sensores.bateria < 3000){
		accion = actIDLE;
	}
	
	else if(CasillaRecarga(sensores.terreno) and sensores.bateria < 2500){
		accion = Recargar(sensores);
	}
	
	else if(((VeoZapatos(sensores.terreno)) 
	or (VeoBikini(sensores.terreno))) and !HayMuroDelante(sensores.terreno)){
		accion = IrObjeto(sensores);
	}
	
	else if(contador == pasosGirar){
		girar = rand()%4;	
		switch(girar){
			case 0:
				if(last_action != actTURN_SR)
					accion = actTURN_SL;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SR;
						break;

						case 2:
							accion = actTURN_BL;
						break;

						case 3:					
							accion = actTURN_BR;
						break;
					}
				}
				break;
			case 1:
				if(last_action != actTURN_SL)
					accion = actTURN_SR;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SL;
						break;

						case 2:
							accion = actTURN_BL;
						break;
						
						case 3:					
							accion = actTURN_BR;
						break;
					}
				}
				break;
			case 2:
				if(last_action != actTURN_BR)
					accion = actTURN_BL;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SR;
						break;

						case 2:
							accion = actTURN_SL;
						break;
						
						case 3:					
							accion = actTURN_BR;
						break;
					}
				}
				break;
			case 3:
				if(last_action != actTURN_BL)
					accion = actTURN_BR;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SR;
						break;

						case 2:
							accion = actTURN_BL;
						break;
						
						case 3:					
							accion = actTURN_SL;
						break;
					}
				}
				break;
		}
	}

	else if((sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S'
		or sensores.terreno[2] == 'G' or sensores.terreno[2]=='X' 
		or sensores.terreno[2] == 'K' or sensores.terreno[2] == 'D'
		or (sensores.terreno[2]=='A' and current_state.bikini) or 
		(sensores.terreno[2]=='B' and current_state.zapatillas)) 
		and sensores.superficie[2] == '_' and !HayObstaculo(sensores.terreno) ){
			accion = actFORWARD;
	}

	else if((sensores.terreno[0]=='K') or (sensores.terreno[0] == 'D')){
		if(!HayObstaculo(sensores.terreno))
			accion = actFORWARD;
		else{
			girar = rand()%4;	
			switch(girar){
				case 0:
					if(last_action != actTURN_SR)
						accion = actTURN_SL;
					else{
						girar = rand()%3;
						switch (girar)
						{
							case 0:
								accion = actTURN_SR;
							break;

							case 2:
								accion = actTURN_BL;
							break;

							case 3:					
								accion = actTURN_BR;
							break;
						}
					}
					break;
				case 1:
					if(last_action != actTURN_SL)
						accion = actTURN_SR;
					else{
						girar = rand()%3;
						switch (girar)
						{
							case 0:
								accion = actTURN_SL;
							break;

							case 2:
								accion = actTURN_BL;
							break;
							
							case 3:					
								accion = actTURN_BR;
							break;
						}
					}
					break;
				case 2:
					if(last_action != actTURN_BR)
						accion = actTURN_BL;
					else{
						girar = rand()%3;
						switch (girar)
						{
							case 0:
								accion = actTURN_SR;
							break;

							case 2:
								accion = actTURN_SL;
							break;
							
							case 3:					
								accion = actTURN_BR;
							break;
						}
					}
					break;
				case 3:
					if(last_action != actTURN_BL)
						accion = actTURN_BR;
					else{
						girar = rand()%3;
						switch (girar)
						{
							case 0:
								accion = actTURN_SR;
							break;

							case 2:
								accion = actTURN_BL;
							break;
							
							case 3:					
								accion = actTURN_SL;
							break;
						}
					}
				break;
			}
		}
	}

	else if(sensores.terreno[0] != 'A' and !current_state.bikini and sensores.terreno[2]=='A'){
		accion = EvitarAgua(sensores);
	}
	
	else if(sensores.terreno[0] != 'B' and !current_state.zapatillas and sensores.terreno[2]=='B'){
		accion = EvitarBosque(sensores);
	}


	else if((sensores.terreno[2]=='A' and !current_state.bikini) or 
		(sensores.terreno[2]=='B' and !current_state.zapatillas) and 
		sensores.superficie[2] == '_' ){
			accion = actFORWARD;
	}
	
	else if(sensores.superficie[2] != 'l' or sensores.superficie[2] != 'a'){
		girar = rand()%4;	
		switch(girar){
			case 0:
				if(last_action != actTURN_SR)
					accion = actTURN_SL;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SR;
						break;

						case 2:
							accion = actTURN_BL;
						break;

						case 3:					
							accion = actTURN_BR;
						break;
					}
				}
				break;
			case 1:
				if(last_action != actTURN_SL)
					accion = actTURN_SR;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SL;
						break;

						case 2:
							accion = actTURN_BL;
						break;
						
						case 3:					
							accion = actTURN_BR;
						break;
					}
				}
				break;
			case 2:
				if(last_action != actTURN_BR)
					accion = actTURN_BL;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SR;
						break;

						case 2:
							accion = actTURN_SL;
						break;
						
						case 3:					
							accion = actTURN_BR;
						break;
					}
				}
				break;
			case 3:
				if(last_action != actTURN_BL)
					accion = actTURN_BR;
				else{
					girar = rand()%3;
					switch (girar)
					{
						case 0:
							accion = actTURN_SR;
						break;

						case 2:
							accion = actTURN_BL;
						break;
						
						case 3:					
							accion = actTURN_SL;
						break;
					}
				}
				break;
		}
	}

	// Recordar la última acción
	last_action = accion;
	contador = (contador + 1)%(pasosGirar+1);
	
	// Determinar el efecto de la ultima accion enviada

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

void ComportamientoJugador::Reiniciar(){
	current_state.brujula = norte;
	current_state.bikini = false;
	current_state.zapatillas = false;
	current_state.fil = 99;
	current_state.col = 99;
	bien_situado = false;
	last_action = actIDLE;

}


bool ComportamientoJugador::HayObstaculo(const vector <unsigned char> &terreno){
	if(terreno[2]=='P' or terreno[2]=='M')
		return true;
	else
		return false;
}

bool ComportamientoJugador::LoboALaVista(const vector <unsigned char> &superficie){
	for(int i=1; i<16; i++)
		if(superficie[i]=='l')
			return true;

	return false;
}

bool ComportamientoJugador::HayAldeanoDelante(const vector <unsigned char> &superficie){
	for(int i=1; i<16; i++)
		if(superficie[i]=='a')
			return true;

	return false;
}

bool ComportamientoJugador::VeoZapatos(const vector <unsigned char> &terreno){
	if(!current_state.zapatillas)
		for(int i=1; i<16; i++)
			if(terreno[i] == 'D'){
				return true;
			}			
	return false;
}

bool ComportamientoJugador::VeoBikini(const vector <unsigned char> &terreno){
	if (!current_state.bikini)
		for(int i=1; i<16; i++)
			if(terreno[i] == 'K'){
				return true;
			}			
	return false;
}

bool ComportamientoJugador::CasillaRecarga(const vector <unsigned char> &terreno){
	for(int i=1; i<16; i++)
		if(terreno[i] == 'X'){
			return true;
		}			
	return false;
}

bool ComportamientoJugador::CasillaPosicionamiento(const vector <unsigned char> &terreno){
	
	for(int i=1; i<16; i++)
		if(terreno[i]=='G'){
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
			accion = actFORWARD;
	else if(sensores.terreno[6]=='K' or sensores.terreno[6]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[7]=='K' or sensores.terreno[7]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[8]=='K' or sensores.terreno[8]=='D')
			accion = actTURN_SR;
	else if(sensores.terreno[9]=='K' or sensores.terreno[9]=='D')
			accion = actTURN_SL;
	else if(sensores.terreno[10]=='K' or sensores.terreno[10]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[11]=='K' or sensores.terreno[11]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[12]=='K' or sensores.terreno[12]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[13]=='K' or sensores.terreno[13]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[14]=='K' or sensores.terreno[14]=='D')
			accion = actFORWARD;
	else if(sensores.terreno[15]=='K' or sensores.terreno[15]=='D')
			accion = actTURN_SR;
	
	last_action = accion;
	return accion;
}

Action ComportamientoJugador::Posicionarme(Sensores sensores){
	
	Action accion = actIDLE;

	if(sensores.terreno[1]=='G')
		accion = actTURN_SL;
	else if(sensores.terreno[2]=='G')
		accion = actFORWARD;
	else if(sensores.terreno[3]=='G')
		accion = actTURN_SR;
	else if(sensores.terreno[4]=='G')
		accion = actTURN_SL;
	else if(sensores.terreno[5]=='G')
		accion = actFORWARD;
	else if(sensores.terreno[6]=='G') 
		accion = actFORWARD;
	else if(sensores.terreno[7]=='G')
		accion = actFORWARD;
	else if(sensores.terreno[8]=='G')
		accion = actTURN_SR;
	else if(sensores.terreno[9]=='G') 
		accion = actTURN_SL;
	else if(sensores.terreno[10]=='G')
		accion = actFORWARD;
	else if(sensores.terreno[11]=='G') 
		accion = actFORWARD;
	else if(sensores.terreno[12]=='G')
		accion = actFORWARD;
	else if(sensores.terreno[13]=='G')
		accion = actFORWARD;
	else if(sensores.terreno[14]=='G') 
		accion = actFORWARD;
	else if(sensores.terreno[15]=='G')
		accion = actTURN_SR;
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

Action ComportamientoJugador::Recargar(Sensores sensores){
		Action accion = actIDLE;

	if(sensores.terreno[1]=='X')
			accion = actTURN_SL;
	else if(sensores.terreno[2]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[3]=='X')
			accion = actTURN_SR;
	else if(sensores.terreno[4]=='X')
			accion = actTURN_SL;
	else if(sensores.terreno[5]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[6]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[7]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[8]=='X')
			accion = actTURN_SR;
	else if(sensores.terreno[9]=='X')
			accion = actTURN_SL;
	else if(sensores.terreno[10]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[11]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[12]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[13]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[14]=='X')
			accion = actFORWARD;
	else if(sensores.terreno[15]=='X')
			accion = actTURN_SR;
	
	last_action = accion;
	return accion;
}

Action ComportamientoJugador::HuirLobos(Sensores sensores){
	
	Action accion = actIDLE;
	int huir = rand()%2;

	if(sensores.superficie[1]=='l')
			accion = actTURN_BR;
	else if(sensores.superficie[2]=='l')
	{
		switch(huir){
			case 0: 
				accion = actTURN_BR;
			break;
			case 1: 
				accion = actTURN_BL;
			break;
		}
	}
	else if(sensores.superficie[3]=='l')
			accion = actTURN_BL;
	else if(sensores.superficie[4]=='l')
			accion = actTURN_BR;
	else if(sensores.superficie[5]=='l')
			accion = actTURN_BR;
	else if(sensores.superficie[6]=='l')
	{
		switch(huir){
			case 0: 
				accion = actTURN_BR;
			break;
			case 1: 
				accion = actTURN_BL;
			break;
		}
	}
	else if(sensores.superficie[7]=='l')
			accion = actTURN_BL;
	else if(sensores.superficie[8]=='l')
			accion = actTURN_BL;
	else if(sensores.superficie[9]=='l')
			accion = actTURN_BR;
	else if(sensores.superficie[10]=='l')
			accion = actTURN_BR;
	else if(sensores.superficie[11]=='l')
			accion = actTURN_BR;
	else if(sensores.superficie[12]=='l')
	{
		switch(huir){
			case 0: 
				accion = actTURN_BR;
			break;
			case 1: 
				accion = actTURN_BL;
			break;
		}
	}	
	else if(sensores.superficie[13]=='l')
			accion = actTURN_BL;
	else if(sensores.superficie[14]=='l')
			accion = actTURN_BL;
	else if(sensores.superficie[15]=='l')
			accion = actTURN_BL;
	
	last_action = accion;
	return accion;
}

Action ComportamientoJugador::EvitarAldeanos(Sensores sensores){
		
	Action accion = actIDLE;
	int evitar = rand()%2;

	if(sensores.superficie[1]=='a')
			accion = actTURN_BR;
	else if(sensores.superficie[2]=='a')
	{
		switch(evitar){
			case 0: 
				accion = actTURN_BR;
			break;
			case 1: 
				accion = actTURN_BL;
			break;
		}
	}
	else if(sensores.superficie[3]=='a')
			accion = actTURN_BL;
	else if(sensores.superficie[4]=='a')
			accion = actTURN_BR;
	else if(sensores.superficie[5]=='a')
			accion = actTURN_BR;
	else if(sensores.superficie[6]=='a')
	{
		switch(evitar){
			case 0: 
				accion = actTURN_BR;
			break;
			case 1: 
				accion = actTURN_BL;
			break;
		}
	}
	else if(sensores.superficie[7]=='a')
			accion = actTURN_BL;
	else if(sensores.superficie[8]=='a')
			accion = actTURN_BL;
	else if(sensores.superficie[9]=='a')
			accion = actTURN_BR;
	else if(sensores.superficie[10]=='a')
			accion = actTURN_BR;
	else if(sensores.superficie[11]=='a')
			accion = actTURN_BR;
	else if(sensores.superficie[12]=='a')
	{
		switch(evitar){
			case 0: 
				accion = actTURN_BR;
			break;
			case 1: 
				accion = actTURN_BL;
			break;
		}
	}	
	else if(sensores.superficie[13]=='a')
			accion = actTURN_BL;
	else if(sensores.superficie[14]=='a')
			accion = actTURN_BL;
	else if(sensores.superficie[15]=='a')
			accion = actTURN_BL;
	
	last_action = accion;
	return accion;
}


bool ComportamientoJugador::VeoPuertaMuro(const vector <unsigned char> &terreno){
	
	//MURO SITUADO AL NORTE/SUR
	if(current_state.brujula==norte or current_state.brujula==sur
	or current_state.brujula==este or current_state.brujula==oeste){
	if(terreno[1]!='M'){
		if(terreno[2] == 'M')
			if(terreno[3]=='M')
					return true;
	}
	if(terreno[2]!='M' ){
		if(terreno[1] == 'M')
			if(terreno[3]=='M')
					return true;
	}
	if(terreno[3]!='M' ){
		if(terreno[2] == 'M')
			if(terreno[1]=='M')
					return true;
	}		
	// MURO SITUADO AL ESTE/OESTE

	if(terreno[1]!='M'){
		if(terreno[5] == 'M')
			if(terreno[11]=='M')
					return true;
	}
	if(terreno[3]!='M' ){
		if(terreno[7] == 'M')
			if(terreno[13]=='M')
					return true;
	}
	}

	return false;
}

Action ComportamientoJugador::EntrarMuro(Sensores sensores){
	Action accion = actIDLE;

	if(sensores.terreno[1]!='M' ){
		if(sensores.terreno[2] == 'M')
			if(sensores.terreno[3]=='M')
					accion = actTURN_SL;
	}
	if(sensores.terreno[2]!='M' ){
		if(sensores.terreno[1] == 'M')
			if(sensores.terreno[3]=='M')
					accion = actFORWARD;
	}
	if(sensores.terreno[3]!='M' ){
		if(sensores.terreno[2] == 'M')
			if(sensores.terreno[1]=='M')
					accion = actTURN_SR;
	}

	
	if(sensores.terreno[1]!='M'){
		if(sensores.terreno[5] == 'M')
			if(sensores.terreno[11]=='M')
					accion = actTURN_SL;
	}
	if(sensores.terreno[3]!='M' ){
		if(sensores.terreno[7] == 'M')
			if(sensores.terreno[13]=='M')
					accion = actTURN_SR;
	}

	last_action = accion;
	return accion;
}

Action ComportamientoJugador::EvitarAgua(Sensores sensores){
	Action accion;
	if(sensores.terreno[2]=='A'){
		if(sensores.terreno[1]!='A' and sensores.terreno[1]!='M' and sensores.terreno[1]!='P')
			if(sensores.terreno[1]!='B' and !current_state.bikini)
				accion = actTURN_SL;
		else if(sensores.terreno[3]!='A' and sensores.terreno[3]!='M' and sensores.terreno[3]!='P')
			if(sensores.terreno[3]!='B' and !current_state.bikini)
				accion = actTURN_SR;
	}
	else{
		girar = rand()%2;	
		switch(girar){
			case 0: 
				accion = actTURN_BL;
				break;
			case 1:
				accion = actTURN_BR;
				break;
		}
	}
	return accion;
}

Action ComportamientoJugador::EvitarBosque(Sensores sensores){
	Action accion;
	if(sensores.terreno[2]=='B'){
		if(sensores.terreno[1]!='B' and sensores.terreno[1]!='M' and sensores.terreno[1]!='P'){
			if(sensores.terreno[1]!='A' and !current_state.zapatillas){
				accion = actTURN_SL;
			}
		}
		if(sensores.terreno[3]!='B' and sensores.terreno[3]!='M' and sensores.terreno[3]!='P'){
			if(sensores.terreno[3]!='A' and !current_state.zapatillas){
				accion = actTURN_SR;
			}
		}
	}
	else{
		girar = rand()%2;	
		switch(girar){
			case 0: 
				accion = actTURN_BL;
				break;
			case 1:
				accion = actTURN_BR;
				break;
		}
	}
	return accion;
}

bool ComportamientoJugador::HayMuroDelante(const vector <unsigned char> &terreno){
	if(terreno[2]=='M')
		return true;
}


