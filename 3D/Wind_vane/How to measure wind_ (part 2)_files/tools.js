function SetPosition(o,x,y){var it=document.getElementById(o);if(!it)throw"SetPosition: "+o+" element does not exist."
it.style.top=parseInt(y)+'px';it.style.left=parseInt(x)+'px';}
function GetPositionX(o){var it=document.getElementById(o);if(!it)throw"GetPositionX: "+o+" element does not exist."
return parseInt(it.style.left);}
function GetPositionY(o){var it=document.getElementById(o);if(!it)throw"GetPositionY: "+o+" element does not exist."
return parseInt(it.style.top);}
function GetWidth(o){var it=document.getElementById(o);if(!it)throw"GetWidth: "+o+" element does not exist."
return parseInt(it.style.width);}
function GetHeight(o){var it=document.getElementById(o);if(!it)throw"GetHeight: "+o+" element does not exist."
return parseInt(it.style.height);}
function SetHeight(o,h){var it=document.getElementById(o);if(!it)throw"SetHeight: "+o+" element does not exist."
h=parseInt(h);if(h<0)h=0;it.style.height=h+"px";}
function SetWidth(o,w){var it=document.getElementById(o);if(!it)throw"SetWidth: "+o+" element does not exist."
w=parseInt(w);if(w<0)w=0;it.style.width=parseInt(w)+"px";}
function SetLeft(o,l){var it=document.getElementById(o);if(!it)throw"SetLeft: "+o+" element does not exist."
it.style.left=parseInt(l)+"px";}
function SetTop(o,t){var it=document.getElementById(o);if(!it)throw"SetTop: "+o+" element does not exist."
it.style.top=parseInt(t)+"px";}
function SetSize(o,w,h){var it=document.getElementById(o);if(!it)throw"SetSize: "+o+" element does not exist."
w=parseInt(w);if(w<0)w=0;h=parseInt(h);if(h<0)h=0;it.style.width=w+'px';it.style.height=h+'px';}
function getInnerHeight(){var D=document;return Math.max(Math.max(D.body.scrollHeight,D.documentElement.scrollHeight),Math.max(D.body.offsetHeight,D.documentElement.offsetHeight),Math.max(D.body.clientHeight,D.documentElement.clientHeight));}
function isCredibleString(st){for(var i=0;(i<st.length);i++){var c=st.charAt(i);if(((c>='a')&&(c<='z'))||((c>='A')&&(c<='Z')))return true;}
return false;}
function isCredibleAlphaNumString(st){for(var i=0;(i<st.length);i++){var c=st.charAt(i);if(((c>='a')&&(c<='z'))||((c>='A')&&(c<='Z'))||((c>='0')&&(c<='9')))return true;}
return false;}
function isCredibleDateString(st){for(var i=0;(i<st.length);i++){var c=st.charAt(i);if(((c>='0')&&(c<='9'))||(c=='/'))return true;}
return false;}
function isCredibleSerialNumber(st){var p=st.indexOf('-');if((p>0)&&(p!=8)){return false;}
var crc=0;var len=st.length;if(len-p+1<2)return false;var c;for(var i=p+1;i<len;i++){c=st.charAt(i);c=c.toUpperCase();if(!(((c>="0")&&(c<="9"))||((c>='A')&&(c<='F')))){return false;}
if(i<len-1)crc=(crc<<1)^parseInt("0x"+c);}
crc=(crc&0xffff)^(crc>>16);crc=(crc&0xff)^(crc>>8);crc=(crc&0x0f)^(crc>>4);return crc==parseInt("0x"+c);}
function isCredibleEmail(st){var n=st.indexOf("@");if((n<=0)||(n>=st.length-1))return false;var n=st.indexOf(" ");if(n>=0)return false;return true;}
function isCredibleIpAddr(str_st){var tokens=str_st.split('.',5);for(var i=0;i<str_st.length;i++){var c=str_st.length[i];if(((c<'0')||(c>'9'))&&(c!='.'))return false;}
if(tokens.length!=4)return false;for(var i=0;i<tokens.length;i++){var v=parseInt(tokens[i]);if((v<0)||(v>255))return false;}
return true;}
function getInnerWidth(){var D=document;return Math.max(Math.max(D.body.scrollWidth,D.documentElement.scrollWidth),Math.max(D.body.offsetWidth,D.documentElement.offsetWidth),Math.max(D.body.clientWidth,D.documentElement.clientWidth));}
function TimeToStr(float_time){var hours=parseInt(float_time);var minutes=parseInt(60*(float_time-hours));if(minutes<10)return hours+':0'+minutes;return hours+':'+minutes;}
function ParseObject(obj){var res='';for(var k in obj){res=res+'obj.'+k+'='+obj[k]+'<br>';}
return res;}
function consoleLog(str_msg){if(console)
console.log(str_msg)}
function ml($addr){window.location='mailto:'+$addr;}
function getRefToDiv(divID,oDoc){if(!oDoc){oDoc=document;}
if(document.layers){if(oDoc.layers[divID]){return oDoc.layers[divID];}else{for(var x=0,y;!y&&x<oDoc.layers.length;x++){y=getRefToDiv(divID,oDoc.layers[x].document);}
return y;}}
if(document.getElementById){return document.getElementById(divID);}
if(document.all){return document.all[divID];}
return false;}
function setVisible(divID_as_a_string,visible){myReference=getRefToDiv(divID_as_a_string);if(!myReference){window.alert('Nothing works in this browser');return false;}
if(myReference.style){if(visible)myReference.style.visibility='visible';else myReference.style.visibility='hidden';}else{if(myReference.visibility){if(visible)myReference.visibility='show';else myReference.visibility='hide';}else{window.alert('Nothing works in this browser');return false;}}
return true;}
function isVisible(divID_as_a_string){myReference=getRefToDiv(divID_as_a_string);if(!myReference)return false;if(myReference.style){if(myReference.style.visibility=='visible')return true;return false;}
if(myReference.visibility){if(myReference.visibility=='show')return true;return false;}
return false;}
function isTouchDevice(){var el=document.createElement('div');el.setAttribute('ongesturestart','return;');if(typeof el.ongesturestart=="function")return true;return false;}
function keepSessionAlive(int_session){var xmlhttp=(window.XMLHttpRequest)?new XMLHttpRequest():new ActiveXObject("Microsoft.XMLHTTP");xmlhttp.open("GET","/FR/common/keepalive.php?sessionid="+int_session,true);xmlhttp.send();setTimeout("keepSessionAlive("+int_session+");",60000);}
function PrintPdfFrameRoutine(str_framename,int_count,bool_CloseWinWhenReady){var frame=document.getElementById(str_framename);if(!frame){alert("PDF frame not found");return;}
var ok=false;if(frame.contentDocument){if(frame.contentDocument.readyState=='complete')
ok=true;}
else
if(frame.document){if(frame.document.readyState=='complete')
ok=true;}
if(ok){frame.focus();if(document.all){frame.print();if(bool_CloseWinWhenReady)setTimeout("CloseWindow(true);",2000);}
else{frame.contentWindow.print();if(bool_CloseWinWhenReady){CloseWindow(true);}}}
else{if($int_count<10)
setTimeout("PrintPdfFrameRoutine('"+str_framename+"',"+(int_count+1)+","+bool_CloseWinWhenReady+")",500);else
yoctoAlert("Unable to print PDF frame");}}
function PrintPdfFile(str_containerDiv,str_url,bool_CloseWinWhenReady,bool_debug){var style=bool_debug?" style='width:350px;height:450px;'":" style='width:0px;height:0px;border: 0px solid red;'";var id=str_containerDiv+"pdfcontent";if(document.all)
html="<embed  type='application/pdf' id='"+id+"' "+style+"  src='"+str_url+"'></embed>"
else
html="<iframe id='"+id+"' "+style+"  src='"+str_url+"'></iframe>"
document.getElementById(str_containerDiv).innerHTML=html;setTimeout("PrintPdfFrameRoutine('"+id+"',0,"+bool_CloseWinWhenReady+")",1500);}
function jsStrf(str_string,str_value1,str_value2,str_value3,str_value4,str_value5,str_value6,str_value7,str_value8,str_value9,str_value10){function replace(str_string,str_value){var index=str_string.indexOf('%s');if(index<0)return str_string;return str_string.slice(0,index)+str_value+str_string.slice(index+2,str_string.length);}
if(!(str_value1==undefined)||str_value1=='')str_string=replace(str_string,str_value1);else return replace(str_string,'');if(str_value2||str_value2=='')str_string=replace(str_string,str_value2);else return str_string;if(str_value3||str_value3=='')str_string=replace(str_string,str_value3);else return str_string;if(str_value4||str_value4=='')str_string=replace(str_string,str_value4);else return str_string;if(str_value5||str_value5=='')str_string=replace(str_string,str_value5);else return str_string;if(str_value6||str_value6=='')str_string=replace(str_string,str_value6);else return str_string;if(str_value7||str_value7=='')str_string=replace(str_string,str_value7);else return str_string;if(str_value8||str_value8=='')str_string=replace(str_string,str_value8);else return str_string;if(str_value9||str_value9=='')str_string=replace(str_string,str_value9);else return str_string;if(str_value10||str_value10=='')str_string=replace(str_string,str_value10);else return str_string;return str_string;}
function bracketList(str_data,bool_valueAreInt){this.data=null;this.index=null;this.valueAreInt=bool_valueAreInt;this.init=bracketList_init;this.add=bracketList_add;this.addArray=bracketList_addArray;this.remove=bracketList_remove;this.contains=bracketList_contains;this.getData=bracketList_getData;this.getListData=bracketList_getListData;this.count=bracketList_count;this.init(str_data);}
function bracketList_count(){return this.data.length;}
function bracketList_init(values){this.data=new Array();this.index=new Array();var tokens=values.split("[");for(var i=0;i<tokens.length;i++){if(tokens[i].length>1)
if(tokens[i].charAt(tokens[i].length-1)==']'){value=tokens[i].substring(0,tokens[i].length-1);this.add(value);}}}
function bracketList_contains(value){if(this.valueAreInt)value=parseInt(value);if(this.index[""+value])return true;return false;}
function bracketList_add(value){if(value=='')return;if(this.valueAreInt)value=parseInt(value);if(this.contains(value))return;this.data[this.data.length]=value;this.index[""+value]=true;}
function bracketList_addArray(values){if(!values)return;for(i=0;i<values.length;i++)
this.add(values[i]);}
function bracketList_remove(value){if(this.valueAreInt)value=parseInt(value);if(!this.contains(value))return;var newdata=new Array();for(var i=0;i<this.data.length;i++)
if(this.data[i]!=value)newdata[newdata.length]=this.data[i];this.index[""+value]=null;this.data=newdata;}
function bracketList_getData(){var res=new Array();for(var i=0;i<this.data.length;i++)
res[res.length]=this.data[i];return res;}
function bracketList_getListData(){var res="";for(var i=0;i<this.data.length;i++)
res=res+"["+this.data[i]+"]";return res;}
function jsQuote(str_in){str_in=str_in+'';var str_out='';for(i=0;i<str_in.length;i++){var ascii=str_in.charCodeAt(i);if((ascii>=32)&&(ascii<=127)&&(ascii!=34)&&(ascii!=39))str_out=str_out+str_in.charAt(i);else{var hex=ascii.toString(16).toUpperCase();if(hex.length==1)hex='0'+hex;str_out=str_out+String.fromCharCode(92)+'x'+hex;}}
return str_out;}
function setUrlAnchor(str_url,str_anchor){if(!str_anchor)return str_url;var p=str_url.indexOf('?');var params='';if(p>=0)params=str_url.substring(0,str_url.length);var p=str_url.indexOf('#');if(p>=0)str_url=str_url.substring(0,p);return str_url+'#'+str_anchor+params;}
function base64_encode(data){var b64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";var o1,o2,o3,h1,h2,h3,h4,bits,i=0,ac=0,enc="",tmp_arr=[];if(!data){return data;}
data=utf8_encode(data+'');do{o1=data.charCodeAt(i++);o2=data.charCodeAt(i++);o3=data.charCodeAt(i++);bits=o1<<16|o2<<8|o3;h1=bits>>18&0x3f;h2=bits>>12&0x3f;h3=bits>>6&0x3f;h4=bits&0x3f;tmp_arr[ac++]=b64.charAt(h1)+b64.charAt(h2)+b64.charAt(h3)+b64.charAt(h4);}while(i<data.length);enc=tmp_arr.join('');var r=data.length%3;return(r?enc.slice(0,r-3):enc)+'==='.slice(r||3);}
function utf8_encode(argString){if(argString===null||typeof argString==="undefined"){return"";}
var string=(argString+'');var utftext="",start,end,stringl=0;start=end=0;stringl=string.length;for(var n=0;n<stringl;n++){var c1=string.charCodeAt(n);var enc=null;if(c1<128){end++;}else if(c1>127&&c1<2048){enc=String.fromCharCode((c1>>6)|192)+String.fromCharCode((c1&63)|128);}else{enc=String.fromCharCode((c1>>12)|224)+String.fromCharCode(((c1>>6)&63)|128)+String.fromCharCode((c1&63)|128);}
if(enc!==null){if(end>start){utftext+=string.slice(start,end);}
utftext+=enc;start=end=n+1;}}
if(end>start){utftext+=string.slice(start,stringl);}
return utftext;}