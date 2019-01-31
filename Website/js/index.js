const lis = document.querySelectorAll("li");
const a = document.querySelectorAll("li a");

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
      id=result.value;
      set_token();
      swal({
        title: 'Join Success',
        timer: 1500,
        showConfirmButton: false     
      })
    }
  })
}
var master;
var answer;
var token;
function create_token()
{
  
  createOffer();
    id=String(id);
    master=String(master);
    // pass id
    // pass master 
        
    $.post('insert_master.php',{tag:id,token:master},
    function(data)
    {
      
    });
  
  
   // listenning check_answer();
}

function set_answer()
{

}



function set_token()
{
get_token();
slave(token);
// pass answer
answer=String(answer);

$.post('read_master.php',{tag:id,slave:answer},
  function(data)
  {

  });
}


function get_token()
{
  id=String(id);
  $.post('read_master.php',{tag:id},
  function(data)
  {
    token=data;
    token=String(token);
    alert(token);
    // console.log(token)
    // token = token.substring(1);
    // token = token.substring(token.length -1);
  });
    
}

