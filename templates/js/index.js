const lis = document.querySelectorAll("li");
const a = document.querySelectorAll("li a");
var message = document.getElementById("message");
var lastPeerId = null;
var peer = null;
var conn = null;
var id;
///////////////////////////////////////////////////////////////
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


var socket = io();
socket = io.connect('http://ae917206.ngrok.io');
socket.on('to_webpage', function(data) {console.log("Got: " + data.Time)})

///////////////////////////////////////////////////////////////
const mediaStreamConstraints = {
  video: true,
};
function gotLocalMediaStream(mediaStream) {
  v1.srcObject = mediaStream;
}
navigator.mediaDevices.getUserMedia(mediaStreamConstraints)
  .then(gotLocalMediaStream).catch(handleLocalMediaStreamError);
////////////////////////////////////////////////////////////////////

for (let i = 0; i < lis.length; i++) {
  lis[i].addEventListener("click", function() {
    for (let i = 0; i < lis.length; i++) {
      lis[i].classList.remove("active");
      a[i].classList.remove("active-text");
    }
    this.classList.add("active");
    a[i].classList.add("active-text");
  });
}

function change(a)
{
  switch(a)
  {
    case 1: create_room();
    break;
    case 2: join_room();
    break;
    case 3: status();
    break;
    case 4: descrip();
    break;
  }
};
var id;
var flag=0;
function create_room()
{
  

swal.mixin({
  input: 'text',
  confirmButtonText: 'Create',
  showCancelButton: true,
 }).queue([
  {
    title: 'Create Room',
    text: 'Enter Room Id'
  }
]).then((result) => {
  if (result.value) {
    id=result.value;
    tag=String(id);
    create_token();
    flag=1;
    swal({
      title: 'Room Created',
      html:
        'Join using the id :<br><b><pre><code>' +
          id +
        '</b></code></pre>',
      confirmButtonText: 'Close'
    })
  }
})

}

function join_room()
{
   if(flag==1)
  {
    swal({
      type: 'error',
      title: 'Reload the page to join.',
      text: 'You have already created a room',
   })
  }
  else
  swal.mixin({
    input: 'text',
    confirmButtonText: 'Join',
    showCancelButton: true,
    
  }).queue([
    {
      title: 'Join Room',
      text: 'Enter Room Id'
    }
  ]).then((result) => {
    if (result.value) {
      tag=result.value;
      get_id(String(tag));
      set_token();
      swal({
        title: 'Join Success',
        timer: 1500,
        showConfirmButton: false     
      })
    }
  })
}

function create_token()
{
  initialize_peer_reciever();

}




function set_token()
{
    initialize_peer_transmiter();
}

/////////////////////////////////////////////////
function initialize_peer_reciever()
{ 
  lastPeerId = null;
  peer = null;
  conn = null;
  var status = document.getElementById("status");
    function initialize() 
    {
        peer = new Peer(null, {debug: 2});
        peer.on('open', function (id) {
            if (peer.id === null) {
                console.log('Received null id from peer open');
                peer.id = lastPeerId;
            } else {
                lastPeerId = peer.id;
            }
            console.log('ID: ' + peer.id);
            status.innerHTML = "ID: " + peer.id;
            $.post('insert_master.php',{key:tag,v:peer.id},function(data){});
         
        });
        peer.on('connection', function (c) {
          // Allow only a single connection
          if (conn) {
              c.on('open', function() {
                  c.send("Already connected to another client");
                  setTimeout(function() { c.close(); }, 500);
              });
              return;
          }

          conn = c;
          console.log("Status: Connected");
          status.innerHTML = "Connected"
          ready();
      });

      var getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
      peer.on('call', function(call) {
        getUserMedia({video: true, audio: true}, function(stream) {
          call.answer(stream); // Answer the call with an A/V stream.
          call.on('stream', function(remoteStream) {
            v2.srcObject = remoteStream;
          });
        }, function(err) {
          console.log('Failed to get local stream' ,err);
        });
      });
        
      


      peer.on('disconnected', function () {
          status.innerHTML = "Connection lost. Please reconnect";
          console.log('Connection lost. Please reconnect');

          // Workaround for peer.reconnect deleting previous id
          peer.id = lastPeerId;
          peer._lastServerId = lastPeerId;
          peer.reconnect();
      });
      peer.on('close', function() {
          conn = null;
          status.innerHTML = "Connection destroyed. Please refresh";
          console.log('Connection destroyed');
      });
      peer.on('error', function (err) {
          console.log(err);
          alert('' + err);
      });
  };
  function ready() {
    conn.on('data', function (data) {
        console.log("Data recieved");
        var cueString = "<span class=\"cueMsg\">Cue: </span>";
        addMessage("<span class=\"peerMsg\">Peer: </span>" + data);
      });
    conn.on('close', function () {
        status.innerHTML = "Connection reset<br>Awaiting connection...";
        conn = null;
        start(true);
    });

}
initialize();

}

function initialize_peer_transmiter()
{lastPeerId = null;
 peer = null;
 conn = null;
 var lastPeerId = null;
 var status = document.getElementById("status");
   function initialize() {
    // Create own peer object with connection to shared PeerJS server
    peer = new Peer(null, {debug: 2});  
    
    peer.on('open', function (id) {
        // Workaround for peer.reconnect deleting previous id
        if (peer.id === null) {
            console.log('Received null id from peer open');
            peer.id = lastPeerId;
        } else {
            lastPeerId = peer.id;
        }

        console.log('ID: ' + peer.id);
    });
    peer.on('disconnected', function () {
        status.innerHTML = "Connection lost. Please reconnect";
        console.log('Connection lost. Please reconnect');

        // Workaround for peer.reconnect deleting previous id
        peer.id = lastPeerId;
        peer._lastServerId = lastPeerId;
        peer.reconnect();
    });
    peer.on('close', function() {
        conn = null;
        status.innerHTML = "Connection destroyed. Please refresh";
        console.log('Connection destroyed');
    });
    peer.on('error', function (err) {
        console.log(err);
        alert('' + err);
    });
};
function join() {
  // Close old connection
  if (conn) {
      conn.close();
  }

  // Create connection to destination peer specified in the input field
  
  conn = peer.connect(id, {
      reliable: true
  });

  conn.on('open', function () {
      status.innerHTML = "Status: Connected";
      console.log("Connected to: " + conn.peer);

      // Check URL params for comamnds that should be sent immediately
      var command = getUrlParam("command");
      if (command)
          conn.send(command);
  });
  // Handle incoming data (messages only since this is the signal sender)
  conn.on('data', function (data) {
      addMessage("<span class=\"peerMsg\">Peer:</span> " + data);
  });
  conn.on('close', function () {
      status.innerHTML = "Connection closed";
  });

};
initialize();
join();

}

function addMessage(msg) {
  var now = new Date();
  var h = now.getHours();
  var m = addZero(now.getMinutes());
  var s = addZero(now.getSeconds());

  if (h > 12)
      h -= 12;
  else if (h === 0)
      h = 12;

  function addZero(t) {
      if (t < 10)
          t = "0" + t;
      return t;
  };

  message.innerHTML = "<br><span class=\"msg-time\">" + h + ":" + m + ":" + s + "</span>  -  " + msg + message.innerHTML;
};

function testMessage()
{ status.innerHTML = "test_msg";
  if (conn.open) {
    msg="test message";
    conn.send(msg);
    console.log("Sent: " + msg)
  }
 
};
 
function media_str(){video_stream_call()}


function video_stream_call()
{
  var getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
  getUserMedia({video: true, audio: true}, function(stream) {
    var call = peer.call(id, stream);
    call.on('stream', function(remoteStream) {
      v2.srcObject = remoteStream;
    });
  }, function(err) {
    console.log('Failed to get local stream' ,err);
  });

}



function video_stream_accept()
{
  peer.on('call', function(call) {
    call.answer(mediaStream);
    console.log('answering call started...');
        },
        function(err){
            console.log('an error occured while getting the video');
            console.log(err);
        }
    );

  call.on('stream', function(stream) {
    v2.srcObject = stream;
  });
}



function get_id(k)
{
  $.post('read_master.php',{key:k},
  function(data)
    {
        data=data.substr(1).slice(0, -1);
        id=data;
     });

}