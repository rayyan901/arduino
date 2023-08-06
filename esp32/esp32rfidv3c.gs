var ss = SpreadsheetApp.openById('1X85r5mR3KACzawQlgSlMiy-joExuJhb1R3PthpfO-IQ');
var sheet = ss.getSheetByName('Sheet1');
var timeStamp = Utilities.formatDate(new Date(), "Asia/Kuala_Lumpur", "yyyy-MM-dd HH:mm:ss");



function doGet(e){

  var access="noAccess";
  var room="desa";
  var rfidUid="unknown"; 
  var user="notdefined" 
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
          user=data[i][4];  
          sheet.getRange(i+1,4).setValue(timeStamp);          
          break;
        }       
    }
    result=access+room+'#'+user;
    return ContentService.createTextOutput(result);
  }
}
