//Declaração das variáveis GLOBAIS

// Nesse caso, cada cor recebe o valor de seu pino no plano físico
int vermelho = 3;
int amarelo = 4;
int verde = 5;
int verm_pedestre = 7;
int verde_pedestre = 6;
int botao = 2;

int tempo_setup = 1000; // Variavel que rege valor do tempo de piscar o LED AMARELO na inicialização do programa
int tempo_intermit = 500; // Variável que rege o valor de piscar o LED verde 

void setup(){

	pinMode(vermelho, OUTPUT); // LED VERMELHO
	pinMode(amarelo, OUTPUT); // LED AMARELO
	pinMode(verde, OUTPUT); // LED VERDE
    pinMode(verm_pedestre, OUTPUT); // LED VERDE
    pinMode(verde_pedestre, OUTPUT); // LED VERDE
    pinMode(botao, INPUT); // BOTÃO

    //Método por algoritmo
    controlaCor(amarelo, millis(), tempo_setup, false, false, tempo_intermit, botao, false);
    controlaCor(amarelo, millis(), tempo_setup, false, false, tempo_intermit, botao, false);
    controlaCor(amarelo, millis(), tempo_setup, false, false, tempo_intermit, botao, false);

    Serial.begin(9600);

}

void loop(){

    bool estadoBotao = false;

	controlaCor(verde, millis(), 5000, true, false, tempo_intermit, botao, true); //Entra no algoritmo fora do loop
    controlaCor(amarelo, millis(), 3000, true, false, tempo_intermit, botao, false);
    controlaCor(vermelho, millis(), 5000, true, true, tempo_intermit, botao, false);
    
}

//Função - evitar tarefa repetitiva
//"TipoDeRetornoDaFunção" "nomeDaFunção" (parâmetros)
int controlaCor(int cor, unsigned long myTime, int tempo, bool esta_no_loop, bool pedestre, int tempo_intermitente, int button, bool estadoVerde){ //Retorna um valor int (inteiro)
                                
    digitalWrite(cor, 1);

    while ((millis() - myTime) < tempo){

        unsigned long tempoCompar = millis();

        if (pedestre == false) { // Se não tiver pedestre (Não estiver no vermelho)
        digitalWrite(verm_pedestre, 1);
        digitalWrite(verde_pedestre, 0);
        }
        else{ //Se tiver possibilidade de pedestre (estiver no vermelho)
                delay(500);
                digitalWrite(verm_pedestre, 0);
                digitalWrite(verde_pedestre, 1);
                delay(tempo - 1500);
                digitalWrite(verde_pedestre, 0);
                digitalWrite(verm_pedestre, 0);
                delay(tempo_intermitente);
                digitalWrite(verm_pedestre, 1);
                delay(tempo_intermitente);
                digitalWrite(verm_pedestre, 0);
                delay(tempo_intermitente);
                digitalWrite(verm_pedestre, 1);
                delay(tempo_intermitente);
                digitalWrite(verm_pedestre, 0);
                delay(tempo_intermitente);
                digitalWrite(verm_pedestre, 1);
                delay(tempo_intermitente);
                digitalWrite(verm_pedestre, 0);
            }

        bool estadoBotao = false;
        estadoBotao = digitalRead(button);
        if(estadoBotao == true && estadoVerde == true){ //Se o botão for pressionado e estiver no verde 
            if((millis() - tempoCompar) < 4000){ //E não tiver passado de 4 seg
                delay(1000);
                break;
            }
        }
    }

    digitalWrite(cor, 0);

    if (esta_no_loop == false){ //Caso não esteja no loop, esperar mais um delay (LED's amarelos piscam) 
        delay(tempo);
        return 0; //Retorna o resultado da função - Termina a função, independente do que está a frente
    }
    else{
        return 1; //Retorna o resultado da função - Termina a função, independente do que está a frente
    }
}