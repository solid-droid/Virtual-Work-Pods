

void mux(int i)
{
  
  switch(i)
  {
    case 6:
    digitalWrite(A,0);
    digitalWrite(B,0);
    digitalWrite(C,0);
    break;
    case 1:
    digitalWrite(A,1);
    digitalWrite(B,0);
    digitalWrite(C,0);
    break;
    case 7:
    digitalWrite(A,0);
    digitalWrite(B,1);
    digitalWrite(C,0);
    break;
    case 2:
    digitalWrite(A,1);
    digitalWrite(B,1);
    digitalWrite(C,0);
    break;
    case 8:
    digitalWrite(A,0);
    digitalWrite(B,0);
    digitalWrite(C,1);
    break;
    case 3:
     digitalWrite(A,1);
    digitalWrite(B,1);
    digitalWrite(C,1);
    break;
    case 4:
    digitalWrite(A,1);
    digitalWrite(B,0);
    digitalWrite(C,1);
    break;
    case 5:
    digitalWrite(A,0);
    digitalWrite(B,1);
    digitalWrite(C,1);
    break;
  }
}

 
