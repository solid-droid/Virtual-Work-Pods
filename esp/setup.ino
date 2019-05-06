void mux(int i)
{
  
  switch(i)
  {
    case 6:
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(7,0);
    break;
    case 1:
    digitalWrite(5,1);
    digitalWrite(6,0);
    digitalWrite(7,0);
    break;
    case 7:
    digitalWrite(5,0);
    digitalWrite(6,1);
    digitalWrite(7,0);
    break;
    case 2:
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(7,0);
    break;
    case 8:
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(7,1);
    break;
    case 3:
     digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(7,1);
    break;
    case 4:
    digitalWrite(5,1);
    digitalWrite(6,0);
    digitalWrite(7,1);
    break;
    case 5:
    digitalWrite(5,0);
    digitalWrite(6,1);
    digitalWrite(7,1);
    break;
  }
  
}
