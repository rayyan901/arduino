//https://script.google.com/macros/s/AKfycbzdaV09fHKI9EXjSGqsvhULyvYjJPMojpT9nuZ_rPohTW9qkC3sdaBKCO7EEyIpOlHW/exec
var ss = SpreadsheetApp.openById('1lnb-R1riUSTamf9wEzYEc1hzbJEtA8HNUSsF9lIA73A');
var sheet = ss.getSheetByName('Sheet1');

function doPost(e) {
  var val = e.parameter.value;
  
  if (e.parameter.value !== undefined){
    var range = sheet.getRange('A2');
    range.setValue(val);
  }
}

function doGet(e){

  var access="-1";
  var text='go home';
  var name='Who are you?';
  //var read = e.parameter.read;
  var sensor1 = e.parameter.value1;

  


  if (sensor1 !== undefined){

     //var mainSheet=getMainSheet();
     
    var data = sheet.getDataRange().getValues();
    if (data.length == 0)
        return;
        //checking if uid is known
    for (var i = 0; i < data.length; i++) {

        if (data[i][0] ==sensor1)
        {
          name=data[i][0];
          access=data[i][1];
          text=data[i][2];
          //var numOfVisits=mainSheet.getRange(i+1,5).getValue();
          //mainSheet.getRange(i+1,5).setValue(numOfVisits+1);
          //mainSheet.getRange(i+1,6).setValue(dateTime+' '+terminal);
          break;
        }
       
    }




    result=access+text;

    return ContentService.createTextOutput(result);//sheet.getRange('C2').getValue());
  }
}
