#include "actionneur.h"
//v2

//initialisation du moteur gauche

byte a=0,etat=0,com=0,fair,palaistoket=0;
int tdpalai[3]={10,20,30};
long time2=0,rot=stocage1;


AccelStepper motor_r(1, step_r, dir_r);//declaration du moteur gauche
AccelStepper motor_t(1, step_t, dir_t);//declatation du moteur droit

Servo servo_d;
Servo servo_g;



void setup() {

  pinMode(pompe,OUTPUT);
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
      motor_t.move(10);//sor pour chercher paller
      digitalWrite(pompe, HIGH);//allume la pompe
      etat=12;
    break;
    case 5://rentré jusque la buté
      motor_t.move(-20);//rentre dans l'actioneur
      etat=12;
    break;
    case 6://rotation dans la zone de stocage
      motor_r.move(rot);//par dans la zonz stocage
      palaistoket++;
      if(palaistoket==3)rot=stocage2;//stocage 1 par defaut
      etat=12;
    break;
    case 7://avancement dans la zone stocage
      motor_t.move(tdpalai[palaistoket%3]);//pour la distantce a la quelle le lactioneur doit stokait le pallais
      etat=12;
    break;
    case 8://coupe la ponpe la l'electrovane
      digitalWrite(pompe,LOW);
      etat=12;
    break;
    case 9://rentré en buté
      motor_t.move(-tdpalai[palaistoket%3]);
      etat=12;
    break;
    case 10://rotation sortie
      motor_r.move(-rot);
      etat=12;
    break;
    case 11://sortie
      motor_t.move(20);
      etat=12;
    break;
    case 12://différent etatpe d'attente
      if(motor_t.isRunning()==false && motor_r.isRunning()==false){
        if(etat==4||etat==8){
          time2=0;
          while(time2!=2){
            Serial.println(time2);
          }etat++;
        }
        else etat++;
        if(etat==13)etat=1;
      }
    break;
  }
  motor_t.run();//lancemant du moteur droit
  motor_r.run();//lancemant du moteur gauche
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
