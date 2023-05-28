//Inclui as bibliotecas do SPI e do RC522
#include <SPI.h>
#include <MFRC522.h>


//Definição dos pinos de conexão do projeto 
#define PINO_SS 10
#define PINO_RST 9

//Cria o item para configurar o módulo RC522
MFRC522 mfrc522(PINO_SS, PINO_RST); 


void setup() {
  // Inicializa a serial
  Serial.begin(9600);
  // Inicializa a comunicação SPI
  SPI.begin();
  // Inicializa o módulo MFRC522
  mfrc522.PCD_Init(); 
}

void loop() {
// Aguarda a aproximação do token
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  // Seleciona qual token vai ser utilizado 
  if (!mfrc522.PICC_ReadCardSerial()) return;
  
  //Cria uma variável vazia, do tipo string
  String conteudo= "";

  //Cria uma variável do tipo byte
  byte letra;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     if(mfrc522.uid.uidByte[i] < 0x10){
        Serial.print(" 0");
     }
     else{
        Serial.print(" ");
     }
     // Printa a mensagem convertida em hexadecimal
     Serial.print(mfrc522.uid.uidByte[i], HEX);


     if(mfrc522.uid.uidByte[i] < 0x10){
        conteudo.concat(String(" 0"));
     }
     else{
        conteudo.concat(String(" "));
     }
     // Concatena a string convertida em hexadecimal
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  
  //Coloca todas as letras da string em maiúscula
  conteudo.toUpperCase();

  delay(1000);
}
