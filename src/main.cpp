#include "actionneur.h"


//initialisation du moteur gauche

byte a=0,etat=0,com=0,fair;
long time2=0;

AccelStepper motor_r(1, step_G, dir_G);//declaration du moteur gauche
AccelStepper motor_t(1, step_D, dir_D);//declatation du moteur droit

Servo servo_d;
Servo servo_g;



void setup() {

  pinMode(pompe,OUPUT);
  digitalWrite(pompe, LOW);

  Wire.begin(my_adr);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(reset_r, OUTPUT);
  digitalWrite(reset_r, HIGH);
  pinMode(sleep_r, OUTPUT);
  digitalWrite(sleep_r, HIGH);

  motor_r.setSpeed(speed);
  motor_r.setAcceleration(acceleration_rg);

  pinMode(reset_t, OUTPUT);
  digitalWrite(reset_t, HIGH);
  pinMode(sleep_t, OUTPUT);
  digitalWrite(sleep_t, HIGH);

  motor_t.setSpeed(speed);
  motor_t.setAcceleration(acceleration_rd);


  MsTimer2::set(1000,IntrerrupTimer);//tout les  seconde
  MsTimer2::start();

  servo_d.attach(22);
  servo_g.attach(23);
//-----------------------------------------------------------------------------------------------------//
  servo_d.write((int)5*0.7555555);//changer pour la mise a zero
  time2=0;
  while(time2!=2){
    Serial.println(time2);
  }
  servo_g.write((int)(180-3)*0.75555555555);
//-------------------------------------------------------------------------------------------------------//
etat =1;
}

void loop() {
  /*  if(b>10)MsTimer2::stop();
    if((int)(((float)b)/200)%2!=0){
      digitalWrite(Led,HIGH);
    }
    else digitalWrite(Led,LOW);*/
  switch(etat){
    case 1:    //attante de trame
      if(com==1){
        etat=fair;
        time2=0;
      }
    break;
    case 2://ouveture eguille
    //--------------------------------------------------------------------------------------------------//
      //angle d'eguille ouver
        servo_g.write((int)(180-95+5)*0.7555555555);//130 Max pour l'omologation
      if(time2==1){
        servo_d.write((int)(94+3)*0.7555555);
        etat=1;
        com=0;
      }
    //---------------------------------------------------------------------------------------------------//
    break;


    case 3://fermeture eguille
      servo_d.write(0);
      if(time2==1){
        servo_g.write(90*0.755555555);
        etat=1;
        com=0;
      }
    break;
    case 4://sortir + allumer la ponpe
      motor_t.move(10);
      digitalWrite(pompe, LOW);
    break;
    case 5://rentré jusque la buté

    break;
    case 6://rotation dans la zone de strocage
    break;
    case 7://avancement dans la zone stocage
    break;
    case 8://coupe la ponpe la l'electrovane
    break;
    case 9://rentré en buté
    break;
    case 10://rotation sortie
    break;
    case 11://sortie
    break;
    case 12://différent etatpe d'attente
    break;

  }
}
void receiveEvent(int howMany){//fonction d'intérupetion l'or dun envoi du maitre
  byte i;//variable pour le for
  fair=Wire.read();//rampli le tableau si avec les valeur de la transmition
  com=1;// passe la comme a 1 pour l'éxecution de la trame en cour
}
void requestEvent(){//fonciton d'intérupetion l'or d une deamande de trame
  Wire.write(com);//le maitre lira la valeur de com
}
void IntrerrupTimer (){
  time2++;
  //Serial.println("reuasie2");
}
