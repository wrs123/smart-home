
// This is the command sequence that initialises the ST7789 driver  
//
// This setup information uses simple 8 bit SPI writecommand() and writedata() functions
//
// See ST7735_Setup.h file for an alternative format

{ //S6D04D1

	writecommand(0xf4);
	writedata(0x59);
	writedata(0x59);
	writedata(0x52);
	writedata(0x52);
	writedata(0x11);
		
	writecommand(0xf5);
	writedata(0x12);
	writedata(0x00);
	writedata(0x0b);
	writedata(0xf0);
	writedata(0x00);
	delay(10);
		
	writecommand(0xf3);
	writedata(0xff);
	writedata(0x2a);
	writedata(0x2a);
	writedata(0x0a);
	writedata(0x22);
	writedata(0x72);
	writedata(0x72);
	writedata(0x20);
	
	writecommand(0x3a);
	writedata(0x55);
	
	writecommand(0xf2);
	writedata(0x10);
	writedata(0x10);
	writedata(0x01);
	writedata(0x08);
	writedata(0x08);
	writedata(0x08);
	writedata(0x08);
	writedata(0x00);
	writedata(0x00);//04
	writedata(0x1a);
	writedata(0x1a);
	
	writecommand(0xf6);
	writedata(0x48);
	writedata(0x88);//88
	writedata(0x10);
	
	writecommand(0xf7);
	writedata(0x0d);
	writedata(0x00);
	writedata(0x03);
	writedata(0x0e);
	writedata(0x1c);
	writedata(0x29);
	writedata(0x2d);
	writedata(0x34);
	writedata(0x0e);
	writedata(0x12);
	writedata(0x24);
	writedata(0x1e);
	writedata(0x07);
	writedata(0x22);
	writedata(0x22);
	
	writecommand(0xf8);
	writedata(0x0d);
	writedata(0x00);
	writedata(0x03);
	writedata(0x0e);
	writedata(0x1c);
	writedata(0x29);
	writedata(0x2d);
	writedata(0x34);
	writedata(0x0e);
	writedata(0x12);
	writedata(0x24);
	writedata(0x1e);
	writedata(0x07);
	writedata(0x22);
	writedata(0x22);
	
	writecommand(0xf9);
	writedata(0x1e);
	writedata(0x00);
	writedata(0x0a);
	writedata(0x19);
	writedata(0x23);
	writedata(0x31);
	writedata(0x37);
	writedata(0x3f);
	writedata(0x01);
	writedata(0x03);
	writedata(0x16);
	writedata(0x19);
	writedata(0x07);
	writedata(0x22);
	writedata(0x22);
	
	writecommand(0xfA);
	writedata(0x0D);
	writedata(0x11);
	writedata(0x0A);
	writedata(0x19);
	writedata(0x23);
	writedata(0x31);
	writedata(0x37);
	writedata(0x3f);
	writedata(0x01);
	writedata(0x03);
	writedata(0x16);
	writedata(0x19);
	writedata(0x07);
	writedata(0x22);
	writedata(0x22);
	
	writecommand(0xfB);
	writedata(0x0D);
	writedata(0x00);
	writedata(0x03);
	writedata(0x0E);
	writedata(0x1C);
	writedata(0x29);
	writedata(0x2D);
	writedata(0x34);
	writedata(0x0E);
	writedata(0x12);
	writedata(0x24);
	writedata(0x1E);
	writedata(0x07);
	writedata(0x22);
	writedata(0x22);
	
	writecommand(0xfC);
	writedata(0x0D);
	writedata(0x00);
	writedata(0x03);
	writedata(0x0E);
	writedata(0x1C);
	writedata(0x29);
	writedata(0x2D);
	writedata(0x34);
	writedata(0x0E);
	writedata(0x12);
	writedata(0x24);
	writedata(0x1E);
	writedata(0x07);
	writedata(0x22);
	writedata(0x22);
	
	writecommand(0xFD);
	writedata(0x11);
	writedata(0x01);
	
	writecommand(0x36);
	writedata(0x08);
	
	writecommand(0x35);
	writedata(0x00);
	
	writecommand(0x2A);
	writedata(0x00);
	writedata(0x00);
	writedata(0x00);
	writedata(0xEF);
	
	writecommand(0x2B);
	writedata(0x00);
	writedata(0x00);
	writedata(0x01);
	writedata(0x8F);
	
	writecommand(0xF1);
	writedata(0x5A);
	
	writecommand(0xFF);
	writedata(0x00);
	writedata(0x00);
	writedata(0x00);
	writedata(0x40);
	
	writecommand(0x11);
	delay(120);
	
	writecommand(0xF1);
	writedata(0x00);
	
	writecommand(0x29);
	delay(40);


#ifdef TFT_BL
  // Turn on the back-light LED
  digitalWrite(TFT_BL, HIGH);
  pinMode(TFT_BL, OUTPUT);
#endif
}
