var server = { urls: "stun:stun.l.google.com:19302" };
var dc, pc = new RTCPeerConnection({ iceServers: [server] });
pc.onaddstream = e => v2.srcObject = e.stream;
pc.ondatachannel = e => dcInit(dc = e.channel);
pc.oniceconnectionstatechange = e => log(pc.iceConnectionState);

var haveGum = navigator.mediaDevices.getUserMedia({video:true, audio:true})
  .then(stream => pc.addStream(v1.srcObject = stream)).catch(log);

function dcInit() {
  dc.onopen = () => log("Chat!");
  dc.onmessage = e => log(e.data);
}
function testing()
{
  console.log("Testing");
}
function createOffer() {
   dcInit(dc = pc.createDataChannel("chat"));
  haveGum.then(() => pc.createOffer()).then(d => pc.setLocalDescription(d))
    .catch(log);
  pc.onicecandidate = e => {
    if (e.candidate) return;
    master = pc.localDescription.sdp;
  };
};

function slave(offer) {
  if (pc.signalingState != "stable") return;
  var desc = new RTCSessionDescription({ type:"offer", sdp:offer });
  pc.setRemoteDescription(desc)
    .then(() => pc.createAnswer()).then(d => pc.setLocalDescription(d))
    .catch(log);
  pc.onicecandidate = e => {
    if (e.candidate) return;
    answer = pc.localDescription.sdp;
  };
};


function set_master(answer){
  if (pc.signalingState != "have-local-offer") return;
  var desc = new RTCSessionDescription({ type:"answer", sdp:answer});
  pc.setRemoteDescription(desc).catch(log);
};

function chat(msg) {
  dc.send(msg);
  log(msg);
};

var enterPressed = e => e.keyCode == 13;
var log = msg => div.innerHTML += "<p>" + msg + "</p>";
