

WorkerScript.onMessage = function(msg){
    var a = msg.a
    var b = msg.b
    WorkerScript.sendMessage({result:a*b})
}
