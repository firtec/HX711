/**********************************************************************
** Descripción  : Construcción de una balanza simple con capacidad para           
**                pesa un máximo de 1000 Gramos.
**  Celda de carga usada en el ejemplo, 1Kg de peso máximo              
**  Target       : Arduino NANO
**  ToolChain    : Arduino IDE 1.8.9 bajo Linux Debian
**
**  Arduino pin A1 conectado a HX711 DOUT
**  Arduino pin A0 conectado a HX711 CLK
**  Celda de carga cable rojo a +5V
**  Celda de carga cable negro a GND
**  Celda de carga cable blanco conectado a A+
**  Celda de carga cable verde conectado a A-
**  B+ y B- del HX711 quedan libres
**
**  www.firtec.com.ar 
**********************************************************************/

#include "HX711.h"
#include "LiquidCrystal.h"
// Pines del LCD RS E  datos
LiquidCrystal lcd(8,9,4,5,6,7); 

HX711 scale(A0, A1);	// Pines conectados al HX711

float factor_ajuste = 313; // Obtenido al ajustar la celda con un peso conocido
float peso;

void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(F("Calculando tara."));
  Serial.begin(9600);
  lcd.setCursor(0,1);
  lcd.print(F("Espere..")); 
  scale.set_scale(factor_ajuste); // Ajustando la escala
  scale.tare(80);   // Obteniendo la tara promediando 80 conversiones
  delay(2000);	    // EN ESTE PUNTO NO DEBE TENER NINGÚN PESO EN LA BALANZA!!!
  lcd.setCursor(0,0);
  lcd.print(F(" Pesando  HX711 "));
  lcd.setCursor(0,1);
  lcd.print(F("Gramos: ")); 
}

void loop()
{
   peso = scale.get_units(20),3;  // Obtener el peso mediante el promedio de 20 conversiones
 
  if (peso < 0){
     lcd.print("      ");
    peso = 0.00;
  }
    lcd.setCursor(7, 1);
    lcd.print("      ");
    lcd.setCursor(7, 1);
    lcd.print(peso,2);		// Mostrar el peso en gramos con dos decimales
 }
