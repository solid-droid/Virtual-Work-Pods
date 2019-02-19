console.log('Socket server running');

var express = require('express');
var app = express();
server = app.listen(3000);
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
  
    // When this user emits, client side: socket.emit('otherevent',some data);
    socket.on('plainString', function(data) {
        // Data comes in as whatever was sent, including objects
        console.log("Recieved and Transmitted:" + JSON.stringify(data));
		
        // Send it to all other clients
        //socket.broadcast.emit('to_webpage', data);
        socket.broadcast.emit('to_webpage', data);
        // This is a way to send to everyone including sender
        // io.sockets.emit('message', "this goes to everyone");

      }
    );
    
	socket.on('jsonObject',
      function(data) {
        // Data comes in as whatever was sent, including objects
        console.log("Connection success:" + data.Time);
      
        // Send it to all other clients
        socket.broadcast.emit('to_webpage', data);
        
        // This is a way to send to everyone including sender
        // io.sockets.emit('message', "this goes to everyone");

      }
    );
	
    socket.on('disconnect', function() {
      console.log("Client has disconnected");
    });
  }
);