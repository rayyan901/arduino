var ss = SpreadsheetApp.openById('1lnb-R1riUSTamf9wEzYEc1hzbJEtA8HNUSsF9lIA73A');
var sheet = ss.getSheetByName('Sheet1');
var timeStamp = Utilities.formatDate(new Date(), "Asia/Kuala_Lumpur", "yyyy-MM-dd HH:mm:ss");

function doPost(e) {
  var val = e.parameter.value;
  
  if (e.parameter.value !== undefined){
    var range = sheet.getRange('A2');
    range.setValue(val);
  }
}

function doGet(e){

  var access="noAccess";
  var room='desa';
  var rfidUid='unknown';  
  var sensor1 = e.parameter.value1;

  if (sensor1 !== undefined){
     
    var data = sheet.getDataRange().getValues();
    if (data.length == 0)
        return;
        //checking if uid is known
    for (var i = 0; i < data.length; i++) {

        if (data[i][0] ==sensor1)
        {
          rfidUid=data[i][0];
          access=data[i][1];
          room=data[i][2];    
          sheet.getRange(i+1,4).setValue(timeStamp);          
          break;
        }       
    }
    result=access+room;
    return ContentService.createTextOutput(result);
  }
}
