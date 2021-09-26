var ip = " ";
var condition = " ";
var btn = " ";
var field = " ";
var status=" ";

// Button On / Off and delete history section

// getting and update value for button off
document.getElementById('on').addEventListener('click', function() {
    value = "255";
    update(btn, ip, value);
    condition = btn + " state = on" +"\n";
});

// getting and update value for button off
document.getElementById('off').addEventListener('click', function() {
    value = "0";
    update(btn, ip, value);
    condition = btn + " state = off" +"\n";
});


// clear activity logs 
document.getElementById('delete').addEventListener('click', function() {
    $("#logger").val('');
});


// PWM Section 

// Getting trackbar for html and api value
var slider = document.getElementById("myRange");
var output = document.getElementById("nilai");

// update pwm value to html
output.innerHTML = slider.value;

slider.oninput = function() {
  output.innerHTML = this.value;
}

// routine for auto-update pwm value and logger activity
setInterval(function() {
    ip = document.getElementById('ip').value;
    status = $("input:checkbox").prop('checked');
    btn = $("input[type='radio'][name='led']:checked").val();
    trackbar = slider.value.toString();
    if(status == 'true')
    {
        update(btn, ip, slider.value);
        condition = "- " + btn + " has recieve " + trackbar + " PWM" +"\n"; 
    }

    // add text to textarea
    addtxt(condition);
    condition = " ";

    // Always scroll to the newest data
    document.getElementById("logger").scrollTop = document.getElementById("logger").scrollHeight;
    
}, 500);

// ----------------------------- Additional Function ----------------------
// Update function
function update(btn, ip, value){
    if(btn == "led1")
        field = "&field1=";
    else 
        field = "&field2=";
    var url = "http://api.thingspeak.com/update?api_key="+ ip + field + value
    $.getJSON(url, function(data) {
        console.log(data);
    });
}

// Update textarea
function addtxt(text) {
    var newtext = text;
    document.myForm.logger.value += newtext;
    }