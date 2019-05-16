void dmp_dat(int i)
{
   fifoCount[i] = mpu.getFIFOCount();
   while (fifoCount[i] < packetSize[i])
   {
      fifoCount[i] = mpu.getFIFOCount();
    }

    if(fifoCount[i] == 1024) {
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));
    }
    else
    {
       mpu.getFIFOBytes(fifoBuffer[i], packetSize[i]);
       fifoCount[i] -= packetSize[i];
    }

     mpu.dmpGetQuaternion(&q[i], fifoBuffer[i]);
     
}

