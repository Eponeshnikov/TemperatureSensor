var debug = document.getElementById("debug_button");
var debug_status = 0;

function debug_state() {
    var request = new XMLHttpRequest();
    request.open('GET','/debug_status',true);
    request.onload = function() {
        if (request.readyState == 4 && request.status == 200) {
            var response = request.responseText;
            debug_status = Number.parseInt(response);
            if (debug_status == 0){
                debug.classList.add('debug_off');
                debug.value = "Debug Off";
            }else{
                debug.classList.add('debug_on');
                debug.value = "Debug On!";
            }
        }
    }
    request.send();
}

function debug_inverse() {
    var request = new XMLHttpRequest();
    request.open('GET','/debug_switch',false);
    request.send();
    if (request.readyState == 4 && request.status == 200) {
        var response = request.responseText;
        if (response == '1') {
            debug.classList.remove("debug_off");
            debug.classList.add("debug_on");
            debug.value = "Debug On!";
            debug_status = 1;
        }else{
            debug.classList.remove("debug_on");
            debug.classList.add("debug_off");
            debug.value = "Debug Off";
            debug_status = 0;
        }
    }
        

}
document.addEventListener('DOMContentLoaded', debug_state);
debug.addEventListener('click', debug_inverse);