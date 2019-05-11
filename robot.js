console.log('Arm Socket Server');

var express = require('express');
var app = express();
server=app.listen(3000, () => console.log('Server running on port 3000!'))
app.use(express.static('public'));

// WebSocket Portion
// WebSockets work with the HTTP server
var socket = require('socket.io');
var io = socket(server);
 
// Register a callback function to run when we have an individual connection
// This is run for each individual user that connects
io.sockets.on('connection',
  // We are given a websocket object in our function
  function (socket) {
  
    console.log("We have a new client: " + socket.id);
  
    socket.on('to_node2', function(data) {
    console.clear();
    console.log("Received and transmitted to ESP:"+JSON.stringify(data));
    
    socket.on('Rx', function(data1) {
      var to_uC = {"data":data}
      process.stdout.write(".");
      io.sockets.emit('event', to_uC);
    });
  });
    
    socket.on('disconnect', function() {
      console.log("Client has disconnected");
    });
  }
);