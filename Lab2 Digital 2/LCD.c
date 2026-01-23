/*
 * LCD.c
 *
 * Created: 22/01/2026 07:05:44 p. m.
 *  Author: Admin
 */ 


 #include "LCD.h"
 
 // Definición de pines (ajustar según conexión)
 #define LCD_PORT        PORTD
 #define LCD_DDR         DDRD
 #define LCD_RS          PIND0
 #define LCD_EN          PIND1

 // Función para inicializar LCD en modo para 4 bits
 void initLCD4bits(void)
 DDRC |= (1)




 /////////////////////////////////////////
 // Function Set


 // Clear Display


 // Función para enviar un comando
 void LCD_CMD(char a) {
	 // RS = 0; // => RS = 1
	 
 }

 // Función para colocar en el puerto un valor
 void LCD_Port(char a) {
	 if (a & 1)
	 // D4 = 1;
	 PORTB |
	 if (a & 2)
	 // D5 = 1
 }

 // fUNCION PARA ENVIAR UN CARACTER
 void LCD_WRITE_CHAR(char c) {
	 char Cbajo, Calto;
	 Cbajo = c & 0x0F;
	 Calto = c & ;
	 
 }

 // Función para enviar una cadena
 void

 // Desplazamiento hacia la izquierda

 // Establecer el cursor
 void LCD_Set_Cursor(char c, char f) {
	 char temp, talto, tbajo;
	 if (f == 1) {
		 temp = 0x80 + 1c;
		 
	 }
 }