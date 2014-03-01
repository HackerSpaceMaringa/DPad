/* Criado por Jair Guilherme Certório - 2014 */ 

struct Pad{

  int pino[8];
  unsigned short atual,anterior , estado;
  
  void             Begin(int conex[8]){
    /*
        Ao indicar os pinos conectados ao teclado coloque-os separados por linhas e
        colunas, isto é, não misture ou inverta a ordem das conexões, exemplo:
          Conectores
           ||||IIII   Em uma matriz 4x4 metade dos pinos será conectado em linha
           ||||IIII   e os outros nas colunas, para evitar problemas conecte-os em ordem
           ||||IIII   seguindo sempre da esquerda->direita e mantendo as posições relativas
           ||||IIII   na conexões no Arduino.
           ||||IIII <-- Provável coluna
            ^-- Provável linhas 
    */
      estado=0;
      anterior=0;
      atual=0;
      for(int i=0;i<8;i++){
        pino[i]=conex[i];
        pinMode(pino[i],INPUT_PULLUP);
      }
  };   
  unsigned short   rawLer(){
    /*
        Esta leitura retorna os botões que estão apertados no momento e atualiza
        as variáveis com os botões pressionados anteriormente e no 'estado'( ainda antes do anterior),
        USE Ler() PARA OBTER A SAIDA TRATADA (DEBOUNCED).
        Cada tecla é guardada em 1 bit de Leitura, mapeie de acordo o simbolo ou função
        associada a cada uma
        Sendo ele todo ocupado, se necessário troque para unsigned long.
    */
      unsigned short Leitura = 0;
      for( int i=0 ; i<4 ; i++ ){
          pinMode(pino[i],OUTPUT);
          digitalWrite(pino[i],LOW);
          for( int j=0 ; j<4 ; j++ ){
              int valor = digitalRead(pino[4+j]);
              if (valor == LOW){
                  Leitura|=(0x01<<(4*j+i));    
              }
          }
          pinMode(pino[i],INPUT_PULLUP);
      }
      estado   = anterior;
      anterior = atual;
      atual    = Leitura;
      return     Leitura;
  }
 
 unsigned short    Ler(){
   /*
        Esta leitura retorna os botões que foram apertados de forma tratada, isto é,
        retorna somente 1 vez a cada pressionar de tecla, sendo bom para digitação e
        troca de estados no uC.
        USE rawLer() PARA OBTER DE SAIDA AS TECLAS ATUALMENTE PRESSIONADAS.
        Cada tecla é guardada em 1 bit de Leitura, mapeie de acordo o simbolo ou função
        associada a cada uma
        Sendo ele todo ocupado, se necessário troque para unsigned long.
    */
     rawLer();
     return (atual&anterior&~estado);
 } 


};

