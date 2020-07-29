byte rxdPkt, addrPkt;
byte chkPkt, pblePkt = 0x55;
byte prevPkt, nextPkt;
boolean rxAddr, rxData;
const int ledPin = 13;
byte dataPkt;

void setup() 
{
  Serial.begin(2400);
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    rxdPkt = Serial.read();
    if (rxdPkt == pblePkt)
      rxAddr = true;
    else if (rxAddr)
    {
      addrPkt = rxdPkt;
      rxAddr = false;
      rxData = true;
    }
    else if (rxData)
    {
      nextPkt = rxdPkt;
      rxData = false;
    }
    else
      chkPkt = rxdPkt;
  }

  if (chkPkt == (addrPkt + nextPkt))
    if (nextPkt != prevPkt)
    {
      dataPkt = nextPkt;
      prevPkt = nextPkt;
      if (dataPkt == 0xFF)
        digitalWrite(ledPin, HIGH);
      else if (dataPkt == 0x00)
        digitalWrite(ledPin, LOW);
    }
}
