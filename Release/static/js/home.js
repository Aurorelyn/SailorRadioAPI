updateInfo();
let paused = true;
audio = document.getElementById('audio');
//httpGet("/api/songs/current")['song']['title']);


function updateInfo(){
  updateRecent();
  httpGet("/api/stable/songs/current").then(out => {
    document.getElementById('songTitle').innerHTML = out['song']['title'];
    document.getElementById('songAuthor').innerHTML = out['song']['artist'];
    document.getElementById('songArt').src = out['song']['art'];

    if(out['streamer']){
      httpGet("/api/stable/songs/current").then(sout =>{
        document.getElementById('streamerName').innerHTML = sout['streamer_name'];
      });
    }else{
      document.getElementById('streamerName').innerHTML = "No streamer found.. H.Y.C.Y.B.H?";
      document.getElementById('streamerPfP').src = "../static/img/Sailor_Radio/Logo/HEADPHONES/hl.svg";
    }

    let nextrun = ((out['duration'] - out['elapsed']) - 1) * 1000;
    console.log("Song duration in ms: " + ((out['duration'] - out['elapsed'])) * 1000);

    setTimeout(function() {updateInfo();}, nextrun);
  });



}

function playAudio(){
  if(paused){
    audio.play();
  }else{
    audio.pause();
  }
  paused = !paused;
}

function updateRecent(){
  let recentBase = document.getElementById("recentPlayBase");
  if(recentBase.children.length == 0){
    createRecentList(recentBase);
  }else{
    httpGet("/api/stable/songs/recent").then(out => {
      out.forEach(function (element, i){
        console.log(i + ": " + element);
        let playBox = document.getElementsByClassName("recentPlaybox")[i];

        playBox.childNodes[0].src = element["song"]["art"];
        playBox.childNodes[1].childNodes[0].innerHTML = element["song"]["title"];
        playBox.childNodes[1].childNodes[1].innerHTML = element["song"]["artist"];
        playBox.childNodes[1].childNodes[2].innerHTML = element["played_at"];
      });
    });
  }
}

function createRecentList(recentBase){
  httpGet("/api/stable/songs/recent").then(out => {
    out.forEach(element => {
      let obj = document.createElement('div');
      obj.classList.add("recentPlaybox");

      let img = document.createElement('img');
      let textItems = document.createElement('span');
      let name = document.createElement('div');
      let author = document.createElement('div');
      let timestamp = document.createElement('div');

      img.classList.add("songImage");
      name.classList.add("title");
      author.classList.add("author");
      timestamp.classList.add("timestamp");

      img.src = element["song"]["art"];
      name.innerHTML = element["song"]["title"];
      author.innerHTML = element["song"]["artist"];
      timestamp.innerHTML = element["played_at"];

      obj.appendChild(img);
      textItems.appendChild(name);
      textItems.appendChild(author);
      textItems.appendChild(timestamp);
      obj.appendChild(textItems);
      recentBase.appendChild(obj);
    });
  });
}

function httpGet(url){

  let response = fetch(url)
  .then(res => res.json())
  .then(out => {
    return out;
  })
  .catch(err => console.log(err));

  return response;
}
