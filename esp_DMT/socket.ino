void socket_conn()
{
  WiFiMulti.addAP(SSID, password);
    while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.println("No wifi");
        delay(1000);
    }
    webSocket.on("event", event);
    webSocket.on("connect", onConnect);
    webSocket.on("disconnect", onDisconnect);
    webSocket.begin(socketServer,socketPort);
}

void transmit()
{
     webSocket.loop();
    if (connected){
    int i=1;
    String key,val;
   String dat="{"; 
 while(i<9)
 {
    key=String(i)+"w";
    val=String(q[i].w);
    dat+= "\""+ String(key) + " \" : \" " + String(val) + " \"";

    key=String(i)+"x";
    val=String(q[i].x);
    dat+= "\""+ String(key) + " \" : \" " + String(val) + " \"";

    key=String(i)+"y";
    val=String(q[i].y);
    dat+= "\""+ String(key) + " \" : \" " + String(val) + " \"";

    key=String(i)+"z";
    val=String(q[i].z);
    dat+= "\""+ String(key) + " \" : \" " + String(val) + " \"";
    
    i++;
 }
 dat+="}";
    
    webSocket.emit("plainString", dat.c_str());
     }
}

