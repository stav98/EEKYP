var EDIT_LABEL='edit';var DELETE_LABEL='delete';var CONFIRM_DELETE_LABEL='Do you really want to delete \x22%s\x22?';var YOCTO_EMBEDDED=false;var WinW=GetWindowWidth()-24;if(WinW<680)WinW=680;var WinH=GetWindowHeight();if(WinH<640)WinH=640;var WinAutoResizeFallBackTimeout=2000;var RIGHT_MENU_WIDTH=175;var UsableWidth=WinW-RIGHT_MENU_WIDTH;var BANNER_HEIGHT=120;var UsableHeight=WinH-BANNER_HEIGHT;var WinOpenTime=15;var WinCloseTime=15;var resizeCallBacks=new Array();function onResize(fct){fct();resizeCallBacks[resizeCallBacks.length]=fct;}
function windowResized(){WinW=GetWindowWidth()-24;if(WinW<680)WinW=680;WinH=GetWindowHeight();if(WinH<640)WinH=640;UsableWidth=WinW-RIGHT_MENU_WIDTH;UsableHeight=WinH-BANNER_HEIGHT;for(var i=0;i<resizeCallBacks.length;i++)
resizeCallBacks[i]();}
function MainMenuMouseOut(id){setTimeout('var node = document.getElementById("'+id+'"); node.className= node.className.replace(" over", "");',1500);}
function startMainMenu(){if(document.all&&document.getElementById){var MainMenuRoot=document.getElementById("MainMenu");for(var i=0;i<MainMenuRoot.childNodes.length;i++){var node=MainMenuRoot.childNodes[i];if(node.nodeName=="LI"){node.onmouseover=function(){this.className+=" over";}
node.onmouseout=function(){MainMenuMouseOut(this.id);}}}}}
function GetWindowWidth(){var width=document.body.clientWidth;if(typeof(window.innerWidth)!="undefined"&&window.innerWidth>0){width=window.innerWidth;}else if(typeof(document.documentElement.clientWidth)!="undefined"&&document.documentElement.clientWidth>0){width=document.documentElement.clientWidth;}
if(width<100)width=600;return width;}
function GetWindowHeight(){var height=document.body.clientHeight;if(typeof(window.innerHeight)!="undefined"&&window.innerHeight>0){height=window.innerHeight;}else if(typeof(document.documentElement.clientHeight)!="undefined"&&document.documentElement.clientHeight>0){height=document.documentElement.clientHeight;}
if(height<100)height=300;return height;}
function ScrollOffsetY(){if(document.body&&document.body.scrollTop)return document.body.scrollTop;if(document.documentElement&&document.documentElement.scrollTop)
return document.documentElement.scrollTop;return 0;}
function ScrollOffsetX(){if(document.body&&document.body.scrollLeft)return document.body.scrollLeft;if(document.documentElement&&document.documentElement.scrollLeft)
return document.documentElement.scrollLeft;return 0;}
function GotoPage(int_session,url){document.forms["serviceform"].action=url;document.forms["serviceform"].elements["fct"].value="";if((int_session>0)&&document.forms["serviceform"].elements["sessionid"]){document.forms["serviceform"].elements["sessionid"].value=int_session;}
serviceFormSubmit();}
function DisableMainPage(bool_all){var div=document.getElementById('DisableDiv');if(!div){div=document.createElement('div');div.id='DisableDiv';div.style.position='absolute';div.style.top="0px";div.style.left="0px";div.style.visibility="hidden";div.style.width=getInnerWidth()+'px';div.style.height=getInnerHeight()+'px';div.style.border='0px solid red';div.style.zIndex=1000;div.style.backgroundColor='white';div.style.MozOpacity=0.8;div.style.opacity=0.8;document.body.insertBefore(div,document.body.childNodes[0]);}
SetSize('DisableDiv',getInnerWidth(),getInnerHeight());setVisible('DisableDiv',true);}
function EnableMainPage(){setVisible('DisableDiv',false);setVisible('ExtraDiv',false);}
function kpress(e){var key=0;if(window.event)key=window.event.keyCode;else if(e)key=e.which;if(key==13){dologin();}}
function OpenErrorDiv(str_errorsmsg){var int_width=260;var int_height=125;DisableMainPage();SetPosition('ExtraDiv',parseInt((WinW-int_width)/ 2),parseInt((WinH-int_height)/2)+ScrollOffsetY());var HTMLdata='<table width="100%" height="100%"><tr><td align="center" valign="center">'
+'<div class="login" style="position:relative;width:260px;height:125px;">'
+'<table height="120">'
+'<tr><td align=center valign=center>'+str_errorsmsg+'</td></tr>'
+'<tr><td align=center valign=bottom><a href="javascript:window.history.back();" class="button">OK</a></td></tr>'
+'</table>'
+'</div>'
+'</table>';document.getElementById('ExtraDiv').innerHTML=HTMLdata;setVisible('ExtraDiv',true);document.getElementById("okbtn").focus();}
function ConfirmSubmit(){document.calendarform.extra.value=document.confirmform.reason.value;document.calendarform.submit();return true;}
function confirmpress(e){var key=0;if(window.event)key=window.event.keyCode;else if(e)key=e.which;if(key==13){return ConfirmSubmit();}
return false;}
function GetCookieValue(str_key,str_cookies){var data='';var p=str_cookies.indexOf(str_key+'=');if(p>=0){n=str_cookies.indexOf(';',p+str_key.length+1);if(n<0)n=str_cookies.length;data=str_cookies.substring(p+str_key.length+1,n)}
return data;}
function dologin(){document.loginform.submit();}
function forgottenPassword(){openWindow('/EN/forgot_password.php','Forgotten password');}
function OpenLoginDiv(int_today,str_target,str_msg,str_extramsg,str_fct,str_extra,bool_allowCancel,bool_loginAllowed){var str_username='E-mail:';var str_password='Password';var str_logon='Connect';var str_cancel='Cancel';var str_nobrain='Forgotten password';var str_cancelurl='/EN/productcategories.php';var int_width=500;var int_height=320;var session=0;DisableMainPage();var div=document.getElementById('ExtraDiv');div.style.left="50%";div.style.top="50%";div.style.transform="translate(-50%, -50%)";div.style.width=int_width+"px";div.style.height=int_height+"px";if(str_target.substring(str_target.toUpperCase(),0,6)!='HTTPS:'){var httpsaddr='https://www.yoctopuce.com';if(str_target.charAt(0)=='/')
str_target=httpsaddr+str_target;else
if(str_target.substring(str_target.toUpperCase(),0,7)=='HTTP://'){var p=str_target.indexOf('/',8);if(p>0)str_target=httpsaddr+str_target.substring(p);else str_target=httpsaddr;}
else{var path=location.pathname;while(path.charAt(path.length-1)!='/'){path=path.substring(0,path.length-1);}
str_target=httpsaddr+path+str_target;}}
var HTMLdata='<table width="100%" height="100%"><tr><td align="center" valign="center">'
+'<div class="login" style="position:relative;">'
+'<form action="'+str_target+'" name="loginform" method="POST" >'
+'<table width=100%>'
+'<tr><td rowspan=5 width=120 align="center"><img src="/img/yoctopuce100.png">&nbsp;</td><td colspan=2 class="logindata" style="text-align:center">'+str_msg+'<br><br></td></tr>';if(bool_loginAllowed){if(session<=0){HTMLdata=HTMLdata+'<tr><td class="logindata">'+str_username+'</td><td><input onkeypress="kpress(event);" name="user" style="width:220px" ></td></tr>'
+'<tr><td class="logindata" valign=top>'+str_password+'</td><td><input onkeypress="kpress(event);" name="password" type=password maxlength="128" style="width:220px"><br><br></td></tr>';HTMLdata=HTMLdata+'<tr><td colspan=2 align=center><a href="javascript:dologin();" class="button">'+str_logon+'</a>';HTMLdata=HTMLdata+' <a href="javascript:forgottenPassword()" class="button">'+str_nobrain+'</a>'
HTMLdata=HTMLdata+' <a href="'+str_cancelurl+'" class="button">'+str_cancel+'</a>'
HTMLdata=HTMLdata+'</td></tr>';}
else HTMLdata=HTMLdata+'<input name="sessionid" value="'+session+'" type="hidden">';}
else
HTMLdata=HTMLdata+'<tr><td width=100>&nbsp;</td><td>'
+' <br><br><a href="javascript:document.loginform.fct.value=\'dologin();\'" class="button">Ok</a> </td></tr>';if(str_extramsg!='')HTMLdata=HTMLdata+'<tr><td colspan=2>'+str_extramsg+'</td></tr>';HTMLdata=HTMLdata
+'</table>'
+'<input name="jour" value="'+int_today+'" type="hidden">'
+'<input name="fct" value="'+str_fct+'" type="hidden">'
+'<input name="extra" value="'+str_extra+'" type="hidden">'
+'<input name="WinW" value="'+GetWindowWidth()+'" type="hidden">'
+'<input name="WinH" value="'+GetWindowHeight()+'" type="hidden">'
+'</form>'
+'</div>'
+'</td></tr></table>';document.getElementById('ExtraDiv').innerHTML=HTMLdata;if(session<=0){document.loginform.user.focus();div.style.visibility="visible";}else document.loginform.submit();}
function OpenRLoginDiv(int_today,str_target,str_msg,str_fct,int_session){var int_width=350;var int_height=140;DisableMainPage();SetPosition('ExtraDiv',parseInt((WinW-int_width)/ 2),parseInt((WinH-int_height)/2)+ScrollOffsetY());SetSize('ExtraDiv',int_width,int_height);var HTMLdata='<table width="100%" height="100%"><tr><td align="center" valign="center">'
+'<div class="login" style="position:relative;width:260px;height:140px;">'
+'<form action="'+str_target+'" name="loginform" method="POST" >'
+'<table>'
+'<tr><td colspan=2 class="logindata">'+str_msg+'</td></tr>';HTMLdata=HTMLdata
+'<tr><td class="logindata">Email:</td><td><input onkeypress="kpress(event);" name="ruser" size=16></td></tr>'
+'<tr><td class="logindata" colspan=2><input onkeypress="kpress(event);" style="border:0;" name="admininherit" type="checkbox">Keep admin rights.<br><br></td></tr>'
+'<tr><td>&nbsp;</td><td><a href="javascript:document.loginform.submit();" class="btn">Ok</a>'
+' <a href="javascript:document.loginform.fct.value=\'\';document.loginform.submit();" class="btn">Cancel</a> </td></tr>';HTMLdata=HTMLdata
+'</table>'
+'<input name="jour" value="'+int_today+'" type="hidden">'
+'<input name="sessionid" value="'+int_session+'" type="hidden">'
+'<input name="fct" value="'+str_fct+'" type="hidden"></form>'
+'</div>'
+'</td></tr></table>';document.getElementById('ExtraDiv').innerHTML=HTMLdata;setVisible('ExtraDiv',true);document.loginform.ruser.focus();}
function OpenPasswordDiv(int_today,str_target,str_msg,str_fct,bool_loginAllowed){var int_width=350;var int_height=200;var session=0;DisableMainPage();SetPosition('ExtraDiv',parseInt((WinW-int_width)/ 2),parseInt((WinH-int_height)/2)+ScrollOffsetY());SetSize('ExtraDiv',int_width,int_height);var HTMLdata='<table width="100%" height="100%"><tr><td align="center" valign="center">'
+'<div class="login" style="position:relative;width:260px;height:90px;">'
+'<form action="'+str_target+'" name="loginform" method="POST" >'
+'<table>'
+'<tr><td colspan=2 class="logindata">'+str_msg+'</td></tr>';if(bool_loginAllowed){if(session<=0)HTMLdata=HTMLdata
+'<tr><td class="logindata">Password</td><td><input onkeypress="kpress(event);" name="password" maxlength="128" type=password size=16></td></tr>'
+'<tr><td>&nbsp;</td><td><a href="javascript:document.loginform.submit();" class="btn">Ok</a>'
+' <a href="javascript:document.loginform.fct.value=\'\';document.loginform.submit();" class="btn">Cancel</a> </td></tr>';else HTMLdata=HTMLdata+'<input name="sessionid" value="'+session+'" type="hidden">';}
else
HTMLdata=HTMLdata
+'<tr><td width=100>&nbsp;</td><td>'
+' <br><br><a href="javascript:document.loginform.fct.value=\'\';document.loginform.submit();" class="btn">Ok</a> </td></tr>';HTMLdata=HTMLdata
+'</table>'
+'<input name="jour" value="'+int_today+'" type="hidden">'
+'<input name="fct" value="'+str_fct+'" type="hidden"></form>'
+'</div>'
+'</td></tr></table>';document.getElementById('ExtraDiv').innerHTML=HTMLdata;if(session<=0){document.loginform.password.focus();setVisible('ExtraDiv',true);}else document.loginform.submit();}
function OpenMailPasswordDiv(int_today,str_target,str_msg,str_fct,bool_loginAllowed){var int_width=400;var int_height=125;var session=0;DisableMainPage();SetPosition('ExtraDiv',parseInt((WinW-int_width)/ 2),parseInt((WinH-int_height)/2)+ScrollOffsetY());SetSize('ExtraDiv',int_width,int_height);var HTMLdata='<table width="100%" height="100%"><tr><td align="center" valign="center">'
+'<div class="login" style="position:relative;width:'+(int_width-10)+'px;height:'+(int_height-10)+'px;">'
+'<form action="'+str_target+'" name="loginform" method="POST" >'
+'<table width="100%" >'
+'<tr><td colspan=2 class="logindata">'+str_msg+'</td></tr>';if(bool_loginAllowed){if(session<=0)HTMLdata=HTMLdata
+'<tr><td class="logindata" width="100">Email:</td><td><input onkeypress="kpress(event);" name="email" type="text" size=40></td></tr>'
+'<tr><td class="logindata">Password</td><td><input onkeypress="kpress(event);" name="password" maxlength="128" type=password size=16></td></tr>'
+'<tr><td>&nbsp;</td><td><a href="javascript:document.loginform.submit();" class="btn">Ok</a>'
+' <a href="javascript:document.loginform.fct.value=\'\';document.loginform.submit();" class="btn">Cancel</a> </td></tr>';else HTMLdata=HTMLdata+'<input name="sessionid" value="'+session+'" type="hidden">';}
else
HTMLdata=HTMLdata
+'<tr><td width=100>&nbsp;</td><td>'
+' <br><br><a href="javascript:document.loginform.fct.value=\'\';document.loginform.submit();" class="btn">Ok</a> </td></tr>';HTMLdata=HTMLdata
+'</table>'
+'<input name="jour" value="'+int_today+'" type="hidden">'
+'<input name="fct" value="'+str_fct+'" type="hidden"></form>'
+'</div>'
+'</td></tr></table>';document.getElementById('ExtraDiv').innerHTML=HTMLdata;if(session<=0){document.loginform.email.focus();setVisible('ExtraDiv',true);}else document.loginform.submit();}
WIN_ACTION_CLOSE=0;WIN_ACTION_OK=1;WIN_ACTION_CANCEL=2;WIN_ACTION_SAVE=3;WIN_ACTION_SUBMIT=4;WIN_ACTION_UPLOAD=5;WIN_ACTION_PUBLISH=6;WIN_ACTION_PREVIOUS=7;WIN_ACTION_NEXT=8;WIN_ACTION_YES=9;WIN_ACTION_NO=10;WIN_ACTION_ACTION=11;WIN_ACTION_DELETE=12;WIN_ACTION_PAY=13;var WindowStandartButtons=new Array(new Array("okbtn",WIN_ACTION_OK,'Ok',''),new Array("deletebtn",WIN_ACTION_DELETE,'delete',''),new Array("actionbtn",WIN_ACTION_ACTION,'Start',''),new Array("publishbtn",WIN_ACTION_PUBLISH,'Publish',''),new Array("savebtn",WIN_ACTION_SAVE,'Save',''),new Array("submitbtn",WIN_ACTION_SUBMIT,'Submit',''),new Array("uploadbtn",WIN_ACTION_UPLOAD,'Dowload',''),new Array("previousbtn",WIN_ACTION_PREVIOUS,'< Prev',''),new Array("nextbtn",WIN_ACTION_NEXT,'Next >',''),new Array("paybtn",WIN_ACTION_PAY,'Pay >','green'),new Array("cancelbtn",WIN_ACTION_CANCEL,'Cancel',''),new Array("yesbtn",WIN_ACTION_YES,'Yes',''),new Array("nobtn",WIN_ACTION_NO,'No',''),new Array("closebtn",WIN_ACTION_CLOSE,'Close',''));windowsData=new Array();function DisableSubWindowactions(int_winId){if(window!=getRootWindow())
throw"DisableSubWindowactions cannot be called from subwindows";var divId="Win"+int_winId;if(!document.getElementById(divId+"closebtn"))return;for(var i=0;i<WindowStandartButtons.length;i++)
document.getElementById(divId+WindowStandartButtons[i][0]).style.display="none";}
function getSubWindowButton(int_winId,int_action){if(window!=getRootWindow())
throw"getSubWindowButton cannot be called from subwindows";var divId="Win"+int_winId;for(var i=0;i<WindowStandartButtons.length;i++)
if(WindowStandartButtons[i][1]==int_action){var it=document.getElementById(divId+WindowStandartButtons[i][0]);if(it==null)return null;if(it.style.display=="none")return null;return it;}
return null;}
function getWindowButton(int_winId,int_action){var w=getRootWindow();w.getSubWindowButton(getWindowId(),int_action);}
function CloseExtraDiv(bool_mustreload){if(document.getElementById("windowframe"))
document.getElementById("windowframe").style.display="none";setVisible('ExtraDiv',false);SetSize('DisableDiv',0,0);setVisible('DisableDiv',false);if(bool_mustreload)silentReload();}
function WinButtonAction(int_winId,int_actionID){if(window!=getRootWindow())
throw"WinButtonAction cannot be called from subwindows";var action=windowsData[int_winId]["actions"][int_actionID];if(action==null){throw"window "+int_winId+": undefined action ("+int_actionID+")";}
if(action["callback"]!=null)action["callback"]();if(action["close"]){CloseSubWindow(int_winId,action["reload"]);}
else if(action["reload"])windowsData[int_winId]["winsource"].silentReload();}
function registerSubWindowKeyDefaultAction(int_winId,int_actionID,int_key){if(window!=getRootWindow())
throw"registerSubWindowDefaultAction cannot be called from subwindows";if(windowsData[int_winId]["actions"]==null)return;for(action in windowsData[int_winId]["actions"]){if(windowsData[int_winId]["actions"][action]["defaultkey"]==int_key)
windowsData[int_winId]["actions"][action]["defaultkey"]=-1;}
if(windowsData[int_winId]["actions"][int_actionID])
windowsData[int_winId]["actions"][int_actionID]["defaultkey"]=int_key;}
function registerKeyDefaultAction(int_winid,int_key,int_actionID){var w=getRootWindow();w.registerSubWindowKeyDefaultAction(int_winid,int_actionID,int_key);}
function isSubWindowActionEnabled(int_winId,int_action){if(window!=getRootWindow())
throw"isSubWindowActionEnabled cannot be called from subwindows";if(windowsData[int_winId]["actions"]==null)return false;if(!windowsData[int_winId]["actions"][int_action])return false;return true;}
function isActionEnabled(int_action){var w=getRootWindow();return w.isSubWindowActionEnabled(getWindowId(),int_action);}
function defaultSubWindowActionHandler(int_winId,int_key){if(window!=getRootWindow())
throw"defaultSubWindowActionHandler cannot be called from subwindows";if(windowsData[int_winId]["actions"]==null)return;for(action in windowsData[int_winId]["actions"]){if(windowsData[int_winId]["actions"][action]["defaultkey"]==int_key){WinButtonAction(int_winId,action);return false;}}
return true;}
function defaultActionHandler(int_winid,int_key){var w=getRootWindow();return w.defaultSubWindowActionHandler(int_winid,int_key);}
function RegisterSubWindowAction(int_winId,int_actionID,fct_callback,bool_parentmustreload,bool_mustclose){if(window!=getRootWindow())
throw"RegisterSubWindowAction cannot be called from subwindows";var divId="Win"+int_winId;var it=new Array();it["callback"]=fct_callback;it["reload"]=bool_parentmustreload;it["close"]=bool_mustclose;it["defaultkey"]=-1;if(windowsData[int_winId]["actions"]==null)windowsData[int_winId]["actions"]=new Array();windowsData[int_winId]["actions"][int_actionID]=it;for(var i=0;i<WindowStandartButtons.length;i++)
if(WindowStandartButtons[i][1]==int_actionID)
document.getElementById(divId+WindowStandartButtons[i][0]).style.display="";}
function RegisterWindowAction(int_actionID,fct_callback,bool_parentmustreload,bool_mustclose){var w=getRootWindow();w.RegisterSubWindowAction(getWindowId(),int_actionID,fct_callback,bool_parentmustreload,bool_mustclose)}
function ClearAllButtons(){var w=getRootWindow();w.DisableSubWindowactions(getWindowId());}
function getWindowId(){if(window!=getRootWindow()){var id=window.frameElement.id;id=id.replace("Win","");id=id.replace("frame","");return parseInt(id);}
throw"getWindowId cannot be called from Top window";}
function getWindowIdFromElement(element){while(true){while((!element.tagName)||((element.tagName!='BODY')&&(element.tagName!='DIV')))element=element.parentNode;var tag=element.tagName;if(tag=='BODY'){if(window==getRootWindow())
throw"getWindowFromElement unable to retreive window from element (wrong element)";var id
if(element.ownerDocument.defaultView)id=element.ownerDocument.defaultView.frameElement.id;else if(element.ownerDocument.frames)id=element.ownerDocument.frames.window.frameElement.id;else throw"getWindowFromElement unable to retreive window from element";id=id.replace("Win","");id=id.replace("frame","");return parseInt(id);}
if(tag=='DIV'){if(element.id)
if(element.id.substring(0,3)=='Win'){var id=element.id;id=id.replace("Win","");return parseInt(id);}}
element=element.parentNode;}}
function getRootWindow(){var w=window;while(w!=window.parent)w=window.parent;return w;}
function getSubWindow(int_windowId){if(window!=getRootWindow())
throw"getSubWindow cannot be called from subwindows";if(windowsData[int_windowId]==null)alert("unknown window: "+int_windowId);return document.getElementById("Win"+int_windowId+"frame").contentWindow;}
function getWindow(int_windowId){var root=getRootWindow();return root.getSubWindow(int_windowId);}
function getSubWindowDiv(int_windowId){if(window!=getRootWindow())
throw"getSubWindowDiv cannot be called from subwindows";if(windowsData[int_windowId]==null)alert("unknown window: "+int_windowId);return document.getElementById("Win"+int_windowId);}
function openI18nWindow(session,str_md5,str_srcLang,str_trgLang,str_page,win_caller){var str_url='/FR/pubadmin/translate_main.php?sessionid='+session+'&md5='+str_md5+'&src='+str_srcLang+'&trg='+str_trgLang+'&page='+str_page+'&action=init';openWindow(str_url,'Traduire la page');}
function disableWindowAnimations(){var w=window;w.WinOpenTime=1;w.WinCloseTime=1;while(w!=window.parent){w=window.parent;w.WinOpenTime=1;w.WinCloseTime=1;}}
var WinAutoResizeFallBackTimer=null;function WinAutoResizeFallBack(int_winid){if(window!=getRootWindow())
throw"WinAutoResizeFallBack cannot be called from subwindows";WinAutoResizeFallBackTimer=null;setWinSize(int_winid,400,150);document.getElementById("Win"+int_winid).style.display='';document.getElementById("Win"+int_winid+"frame").style.display='';}
function setWinSize(int_winid,int_width,int_height){if(window!=getRootWindow())
throw"setWinSize cannot be called from subwindows";if(WinAutoResizeFallBackTimer!=null){clearTimeout(WinAutoResizeFallBackTimer);WinAutoResizeFallBackTimer=null;}
divId="Win"+int_winid;WinW=GetWindowWidth();WinH=GetWindowHeight();SetPosition(divId,parseInt((WinW-int_width)/ 2),parseInt((WinH-int_height)/2)+ScrollOffsetY());if(document.getElementById(divId+"td1")){var title=document.getElementById(divId+"td2").innerHTML;var w2=parseInt(int_width /3);if(w2<title.length*8)w2=title.length*8;if(w2>int_width-10)w2=int_width-10;var w1=int_width-w2;document.getElementById(divId+"td1").style.width=w1+"px";document.getElementById(divId+"td2").style.width=w2+"px";}
SetSize(divId+"table",int_width,int_height);SetSize(divId,int_width,int_height);var w=int_width-windowsData[int_winid]["frameSizeOffsetX"];var h=int_height-windowsData[int_winid]["frameSizeOffsetY"];SetSize(divId+"framediv",w,h);SetSize(divId+"frame",w,h);}
function destroyWindow(int_winId){if(window!=getRootWindow())
throw"destroyWindow cannot be called from subwindows";var it=document.getElementById("Win"+int_winId);it.style.display="none";it.parentNode.removeChild(it);it=document.getElementById("WinMask"+int_winId);it.style.display="none";it.parentNode.removeChild(it);windowsData[int_winId]=null;}
function magicwinclose(int_winid,int_width,int_height,int_step,int_steps_count){if(window!=getRootWindow())
throw"magicwinclose cannot be called from subwindows";var winId="Win"+int_winid;var maskId="WinMask"+int_winid;if(int_step>=int_steps_count-1){document.getElementById(winId+"frame").style.display="none";}
if(int_step<=1){destroyWindow(int_winid);}
else{setWinSize(int_winid,int_step*int_width/int_steps_count,int_step*int_height/int_steps_count);setTimeout("magicwinclose("+int_winid+","+int_width+","+int_height+","+(int_step-1)+","+int_steps_count+");",10);}}
function HideSubWindow(int_winId,bool_parentmustreload){if(window!=getRootWindow())
throw"HideSubWindow cannot be called from subwindows";it=document.getElementById("Win"+int_winId).style.visibility="hidden";it=document.getElementById("WinMask"+int_winId).style.visibility="hidden";windowsData[int_winId]["previousFocus"].focus();windowsData[int_winId]=null;}
function CloseSubWindow(int_winid,bool_parentmustreload,str_parentAnchor){if(window!=getRootWindow())
throw"CloseSubWindow cannot be called from subwindows";if(bool_parentmustreload){p=windowsData[int_winid]["winsource"];p.silentReload(str_parentAnchor);}
var divId="Win"+int_winid;int_width=parseInt(document.getElementById(divId).style.width);int_height=parseInt(document.getElementById(divId).style.height);magicwinclose(int_winid,int_width,int_height,WinCloseTime-1,WinCloseTime);if(windowsData[int_winid]["previousFocus"]){windowsData[int_winid]["previousFocus"].focus();}
if(str_parentAnchor)
if(str_parentAnchor!='')
windowsData[int_winid]["winsource"].location.hash=str_parentAnchor;}
function CloseWindow(bool_parentmustreload,str_parentAnchor){var w=getRootWindow();w.CloseSubWindow(getWindowId(),bool_parentmustreload,str_parentAnchor);}
function getSubWindowSource(int_winId){if(window!=getRootWindow())
throw"getSubWindowSource cannot be called from subwindows";return windowsData[int_winId]["winsource"];}
function getSourceWindow(){var w=getRootWindow();return w.getSubWindowSource(getWindowId());}
function HideWindow(bool_parentmustreload){var w=getRootWindow();w.HideSubWindow(getWindowId(),bool_parentmustreload);}
function getWindowDocumentObject(int_winid){var w=getRootWindow();var iframe=w.document.getElementById("Win"+int_winid+"frame");if(iframe.contentWindow)
if(iframe.contentWindow.document)return iframe.contentWindow.document;if(iframe.contentDocument)return iframe.contentDocument;return null;}
function getWindowObject(int_winid){var w=getRootWindow();var iframe=w.document.getElementById("Win"+int_winid+"frame");if(iframe.contentWindow)
if(iframe.contentWindow)return iframe.contentWindow;return iframe.contentDocument;}
function magicwinsize(int_winid,int_width,int_height,int_step,int_steps_count){if(window!=getRootWindow())
throw"magicwinsize cannot be called from subwindows";var divId="Win"+int_winid;if((parseInt(int_width)==GetWidth(divId))&&(parseInt(int_height)==GetHeight(divId))){var doc=getWindowObject(int_winid);if(doc)if(doc.resizefinished)doc.resizefinished();return;}
setWinSize(int_winid,int_step*int_width/int_steps_count,int_step*int_height/int_steps_count);if(int_step<int_steps_count)setTimeout("magicwinsize("+int_winid+","+int_width+","+int_height+","+(int_step+1)+","+int_steps_count+");",10);else{document.getElementById("Win"+int_winid+"frame").style.display="";var doc=getWindowObject(int_winid);if(doc)if(doc.resizefinished)doc.resizefinished();}}
function setWindowSize(int_width,int_height){var w=getRootWindow();var winid=getWindowId();w.magicwinsize(winid,int_width,int_height,1,WinOpenTime);}
if(!window.listhilight){window.listhilight=function(source,state){source.setAttribute("class",state?"ItemListLineActive":"ItemListLine");}}
function showfile(str_filename){var w=getRootWindow();w.open(str_filename);}
var windowindex=1;function CancelButtonMouseDown(e){if(!e)var e=window.event;e.cancelBubble=true;if(e.stopPropagation){e.stopPropagation()};}
function CreateWindow(win_source,str_url,str_title,str_style,array_extraParams){if(window!=getRootWindow())
throw"CreateWindow cannot be called from subwindows";int_width=100;int_height=100;var baseZIndex=20000;windowid=windowindex;var it=new Array();it["winsource"]=win_source;it["frameSizeOffsetX"]=16;it["frameSizeOffsetY"]=64;it["winsource"]=win_source;it["actions"]=null;it["focusable"]=null;it["previousFocus"]=win_source.document.activeElement;windowsData[windowid]=it;windowindex++;div=document.createElement('div');div.id="WinMask"+windowid;div.style.position='absolute';div.style.top="0px";div.style.left="0px";div.style.width=getInnerWidth()+'px';div.style.height=getInnerHeight()+'px';div.style.border='0px solid red';div.style.zIndex=baseZIndex+2*windowid;div.style.backgroundColor='white';div.style.MozOpacity=0.8;div.style.opacity=0.8;document.body.insertBefore(div,document.body.childNodes[0]);int_width=100;int_height=100;var divId="Win"+windowid;div=document.createElement('div');div.id=divId;div.style.position='absolute';div.style.top="0px";div.style.overflow="hidden";div.style.left="0px";div.style.width='0px';div.style.height='0px';div.style.visible='hidden';div.style.border='0px solid red';div.style.zIndex=baseZIndex+2*windowid+1;document.body.insertBefore(div,document.body.childNodes[0]);var ydec=0;if(str_style=='sandboxwindow'){var newurl="/fr/common/sandbox.php?";var p=str_url.indexOf("sessionid=");if(p>0){var session="";p2=str_url.indexOf("&",p+1);if(p2>0)session=str_url.substring(p+10,p2)
else session=str_url.substring(p+10);newurl=newurl+"sessionid="+session+"&";}
if(array_extraParams)
for(var key in array_extraParams)
newurl+=key+"="+encodeURI(array_extraParams[key])+"&"
str_url=newurl+"url="+encodeURI(str_url);str_style='window';}
SetPosition(divId,parseInt((WinW-int_width)/ 2),parseInt((WinH-int_height)/2)+ScrollOffsetY());SetSize(divId,int_width,int_height);var w1=int_width-parseInt(int_width /3);var w2=parseInt(int_width /3);var initialWidth=parseInt(int_width-windowsData[windowid]["frameSizeOffsetX"]);var initialheight=parseInt(int_height-windowsData[windowid]["frameSizeOffsetY"]);var HTMLdata='Unknow style<br>('+str_style+')';switch(str_style){case"window":HTMLdata='<table  id="'+divId+'table" style="width:'+int_width+'px;height:"'+int_height+'px" cellspacing="0" border="0" cellpadding="0">'
+'<tr><td id="'+divId+'td1" width="'+w1+'px" class="WinA1">&nbsp;</td>'
+'<td     id="'+divId+'td2" width="'+w2+'px" class="WinA2">'+str_title+'</td></tr>'
+'<tr><td colspan="2" class="WinB">'
+'<DIV id="'+divId+'framediv" style="width:'+initialWidth+'px;height:'+initialheight+'px;overflow:hidden">'
+'<IFRAME id="'+divId+'frame" src="'+str_url+'" BORDER="0" FRAMEBORDER="0" SCROLLING="0" style="display:none;border:0px solid red;width:'
+initialWidth+'px;height:'
+initialheight+'px;"  ></iframe></DIV>'
+'</td></tr>'
+'<tr><td colspan="2" class="WinC">&nbsp;';for(i=0;i<WindowStandartButtons.length;i++){var btid=WindowStandartButtons[i][0];var btaction=WindowStandartButtons[i][1];var label=WindowStandartButtons[i][2];var cssModifier=WindowStandartButtons[i][3];HTMLdata+='<a id="'+divId+btid+'" href="javascript:WinButtonAction('+windowid+','+btaction+');"  class="button'+cssModifier+'"  style="display:none">'+label+'</a>';}
HTMLdata+='</td></tr></table>';break;case"dialog":windowsData[windowid]["frameSizeOffsetY"]=48;HTMLdata='<table id="'+divId+'table" width="'+int_width+'" height="'+int_height+'" cellspacing="0" border="0" cellpadding="0">'
+'<tr><td  class="DialogA">'+str_title+'</td></tr>'
+'<tr><td  class="DialogB">'
+'<DIV id="'+divId+'framediv" style="width:'+initialWidth+'px;height:'+initialheight+'px;overflow:hidden">'
+'<IFRAME id="'+divId+'frame" src="'+str_url+'" BORDER="0" FRAMEBORDER="0" SCROLLING="0" style="display:none;width:'
+initialWidth+'px;height:'
+initialheight+'px;"  ></iframe></div>'
+'</td></tr>'
+'<tr><td class="DialogC">&nbsp;';for(i=0;i<WindowStandartButtons.length;i++){var btid=WindowStandartButtons[i][0];var btaction=WindowStandartButtons[i][1];var label=WindowStandartButtons[i][2];var cssModifier=WindowStandartButtons[i][3];HTMLdata+='<a id="'+divId+btid+'"  href="javascript:WinButtonAction('+windowid+','+btaction+');"  class="smallbutton'+cssModifier+'"  style="display:none">'+label+'</a>';}
HTMLdata+='</td></tr></table>';break;case"alert":case"confirm":case"info":var icon='';if(str_style=="alert")icon="bigwarning.png";if(str_style=="confirm")icon="bigquestion.png";if(str_style=="info")icon="biginfo.png";windowsData[windowid]["frameSizeOffsetY"]=48;HTMLdata='<table id="'+divId+'table" width="'+int_width+'" height="'+int_height+'" cellspacing="0" border="0" cellpadding="0">'
+'<tr><td  class="DialogA">'+str_title+'</td></tr>'
+'<tr><td  class="DialogB">'
+'<DIV id="'+divId+'framediv" style="width:'+initialWidth+'px;height:'+initialheight+'px;overflow:hidden">'
+'<div id="'+divId+'frame" style="display:none;overflow:hide;border: 1px solid #f8f8f8;width:'
+initialWidth+'px;height:'
+initialheight+'px;">'
+'<table><tr><td valign="top"><img src="/img/'+icon+'"></td><td style="padding-left:5px;white-space:normal">'
+str_url
+'</td><tr></table>'
+'</div></div>'
+'</td></tr>'
+'<tr><td class="DialogC">&nbsp;';for(i=0;i<WindowStandartButtons.length;i++){var btid=WindowStandartButtons[i][0];var btaction=WindowStandartButtons[i][1];var label=WindowStandartButtons[i][2];var cssModifier=WindowStandartButtons[i][3];HTMLdata+='<a id="'+divId+btid+'"  href="javascript:WinButtonAction('+windowid+','+btaction+');"  class="smallbutton'+cssModifier+'"  style="display:none">'+label+'</a>';}
HTMLdata+='</td></tr></table>';}
document.getElementById(divId).innerHTML=HTMLdata;EnableDrag(div);for(i=0;i<WindowStandartButtons.length;i++){var id=divId+WindowStandartButtons[i][0];var b=document.getElementById(id);if(b)
if(b.addEventListener)
b.addEventListener("mousedown",CancelButtonMouseDown,true);}
setVisible(divId,true);WinAutoResizeFallBackTimer=setTimeout("WinAutoResizeFallBack("+windowid+");",WinAutoResizeFallBackTimeout);return windowid;}
function urlDisambiguation(str_url){if(str_url.substring(0,4)=='http')return str_url;if(str_url.substring(0,5)=='data:')return str_url;if(str_url.substring(0,1)!='/'){pathArray=window.location.pathname.split('/');str_url="/"+str_url;for(var i=pathArray.length-2;i>=0;i--)
if(pathArray[i]!='')
str_url="/"+pathArray[i]+str_url;}
return str_url;}
function remoteOpenWindow(str_url,str_title){var p=str_url.indexOf("://");if(p>0){var p2=str_url.indexOf("/",p+3);if(p2>0)baseurl=str_url.substr(0,p2);else baseurl=str_url;document.forms['serviceform'].action=baseurl+"/EN/";document.forms['serviceform'].elements['fct'].value="openwindow";document.forms['serviceform'].elements['extra'].value=str_url;document.forms['serviceform'].elements['extra2'].value=str_title;document.forms['serviceform'].submit();}else throw"cannot remote open window: not a full url ";}
function openWindow(str_url,str_title){if(str_url.substring(0,4)=='http')
if(str_url.indexOf('www.yoctopuce.com')<0)
remoteOpenWindow(str_url,str_title);w=getRootWindow();var newurl=urlDisambiguation(str_url);return w.CreateWindow(window,newurl,str_title,"window",null);}
function openSandBoxWindow(str_url,str_title,int_width,int_height){if(str_url.substr(0,4)!='http'){alert('openSandBoxWindow takes full urls only.');return;}
w=getRootWindow();var params=new Array();params["width"]=int_width;params["height"]=int_height;return w.CreateWindow(window,urlDisambiguation(str_url),str_title,"sandboxwindow",params);}
function openDialog(str_url,str_title){w=getRootWindow();return w.CreateWindow(window,urlDisambiguation(str_url),str_title,"dialog",null);}
function playsound(str_file){try{var file="";var test=new Audio();if(test.canPlayType('audio/ogg'))
file='/sounds/'+str_file+'.ogg';else if(test.canPlayType('audio/mp3'))
file='/sounds/'+str_file+'.mp3';else
file='/sounds/'+str_file+'.wav';var audio=new Audio(file);audio.play();}
catch(err){}}
function yoctoAlert(str_msg,int_optionalwidth,int_optionalheight){w=getRootWindow();if(w!=window)return w.yoctoAlert(str_msg,int_optionalwidth,int_optionalheight);playsound('alert');var winid=CreateWindow(window,str_msg,'&nbsp;',"alert",null);RegisterSubWindowAction(winid,WIN_ACTION_OK,null,false,true);var width=350;var height=125;if(int_optionalwidth)width=int_optionalwidth;if(int_optionalheight)height=int_optionalheight;magicwinsize(winid,width,height,1,1);setFocus(winid);SetInputDefaultKeyHandlers(winid);registerKeyDefaultAction(winid,27,WIN_ACTION_OK);return winid;}
function yoctoInfo(str_msg){w=getRootWindow();if(w!=window)return w.yoctoInfo(str_msg);playsound('info');var winid=CreateWindow(window,str_msg,'&nbsp;',"info",null);RegisterSubWindowAction(winid,WIN_ACTION_OK,null,false,true);magicwinsize(winid,350,125,1,1);setFocus(winid);SetInputDefaultKeyHandlers(winid);registerKeyDefaultAction(winid,27,WIN_ACTION_OK);return winid;}
function yoctoConfirm(str_msg,fct_ifYes,fct_ifNo,width,height){if(!width)width=350;if(!height)height=125;w=getRootWindow();if(w!=window)return w.yoctoConfirm(str_msg,fct_ifYes,fct_ifNo,width,height);playsound('question');var winid=CreateWindow(window,str_msg,'&nbsp;',"confirm",null);RegisterSubWindowAction(winid,WIN_ACTION_YES,fct_ifYes,false,true);RegisterSubWindowAction(winid,WIN_ACTION_NO,fct_ifNo,false,true);magicwinsize(winid,width,height,1,1);setFocus(winid);registerKeyDefaultAction(winid,27,WIN_ACTION_NO);SetInputDefaultKeyHandlers(winid);return winid;}
function GetAllFocusableElementsRec(obj_element,var_list){var ok=true;if(obj_element.style){ok=(obj_element.style.visibility!='hidden');if(ok)ok=(obj_element.style.display!="none");}
if(ok){if(obj_element.tagName=='INPUT')
if((obj_element.type!='hidden')&&!(obj_element.disabled)&&!(obj_element.readOnly)){var_list["INPUT"][var_list["INPUT"].length]=obj_element;var_list["ALL"][var_list["ALL"].length]=obj_element;return;}
if(obj_element.tagName=='SELECT')
if(!(obj_element.disabled)){var_list["INPUT"][var_list["INPUT"].length]=obj_element;var_list["ALL"][var_list["ALL"].length]=obj_element;return;}
if(obj_element.tagName=='A'){var_list["A"][var_list["A"].length]=obj_element;var_list["ALL"][var_list["ALL"].length]=obj_element;return;}}
else return;for(var i=0;i<obj_element.childNodes.length;i++){GetAllFocusableElementsRec(obj_element.childNodes[i],var_list);}}
function getSubWindowEnabledButton(subwindowid){if(window!=getRootWindow())
throw"getSubWindowEnabledButton cannot be called from subwindows";var list=new Array();for(var i=0;i<WindowStandartButtons.length;i++){var it=document.getElementById("Win"+subwindowid+WindowStandartButtons[i][0]);if((it.style.display!='none')&&(it.style.visible!="hidden"))
list[list.length]=it;}
return list;}
function getWindowEnabledButton(int_winid){w=getRootWindow();return w.getSubWindowEnabledButton(int_winid);}
function GetAllFocusableElements(int_winid){var w=getRootWindow();var data=new Array();data["A"]=new Array();data["INPUT"]=new Array();data["ALL"]=new Array();var container=w.document.getElementById("Win"+int_winid+"frame");if(container.tagName=='IFRAME'){container=document.body}
GetAllFocusableElementsRec(container,data);var winbuttons=w.getWindowEnabledButton(int_winid);for(var i=0;i<winbuttons.length;i++){data["A"][data["A"].length]=winbuttons[i];data["ALL"][data["ALL"].length]=winbuttons[i];}
return data;}
function defaultBarCodeHandler(source,event){handleWindowFocus(event);return false;}
function submitBarCodeHandler(source,event){return true;}
function setBarCodeHandler(obj_element,var_fct){obj_element.barCodeHandler=var_fct;}
function setDefaultBarCodeHandler(str_formname,str_input_name){setBarCodeHandler(document.forms[str_formname].elements[str_input_name],defaultBarCodeHandler);}
function setSubmitBarCodeHandler(str_formname,str_input_name){setBarCodeHandler(document.forms[str_formname].elements[str_input_name],submitBarCodeHandler);}
function handleWindowFocus(event){var elmt_source;if(event.target)elmt_source=event.target;else if(event.srcElement)elmt_source=event.srcElement;var winid=getWindowIdFromElement(elmt_source);var list=GetAllFocusableElements(winid);var count=list["ALL"].length;for(var i=0;i<count;i++)
if(list["ALL"][i]==elmt_source){nextindex=(i+count+(event.shiftKey?-1:1))%count;list["ALL"][nextindex].focus();event.cancelBubble=true;event.returnValue=false;if(event.preventDefault)event.preventDefault();if(event.stopPropagation)event.stopPropagation();return false;}
return true;}
var keyHandlerLastSource=null;var keyHandlerKeycount=0;var keyHandlerTimer=0;function inputDefaultKeyHandler(event){if(!event)event=window.event;var key=event.keyCode?event.keyCode:event.which;var elmt_source;if(event.target)elmt_source=event.target;else if(event.srcElement)elmt_source=event.srcElement;if(elmt_source.value)
if(elmt_source.value.length<2)keyHandlerLastSource=null;if(keyHandlerLastSource!=elmt_source){keyHandlerLastSource=elmt_source;keyHandlerKeycount=1;keyHandlerTimer=new Date().getTime();}
else keyHandlerKeycount++;if((key!=13)&&(key!=27)&&(key!=9))return true;if(key==9){if(navigator.appName=="Opera")return true;else
return handleWindowFocus(event);}
var winid=getWindowIdFromElement(elmt_source)
var canpropagate=true;if((key==13)&&(keyHandlerKeycount>=5))
if(((new Date().getTime()-keyHandlerTimer)/ keyHandlerKeycount)<50){if(elmt_source.barCodeHandler){canpropagate=elmt_source.barCodeHandler(elmt_source,event);}else canpropagate=false;}
if((elmt_source.tagName=='A')&&(key==13))return true;if(canpropagate)canpropagate=defaultActionHandler(winid,key);if(!canpropagate){event.cancelBubble=true;event.returnValue=false;if(event.preventDefault)event.preventDefault();if(event.stopPropagation)event.stopPropagation();}
return canpropagate;}
function SetInputDefaultKeyHandlers(int_winid){var list=GetAllFocusableElements(int_winid);for(var i=0;i<list["ALL"].length;i++){elmt=list["ALL"][i];if(document.addEventListener)
elmt.addEventListener("keydown",inputDefaultKeyHandler,false);if(document.attachEvent)
elmt.attachEvent("onkeydown",inputDefaultKeyHandler);}}
function setFocus(int_winid){var list=GetAllFocusableElements(int_winid);if(list["INPUT"].length>0){try{list["INPUT"][0].focus();}
catch(err){}
return;}
if(list["A"].length>0){try{list["A"][0].focus();}
catch(err){}
return;}}
function autoSetFocus(){setFocus(getWindowId());}
function EnableActiveBorderRec(obj_el,str_name,bool_enabled){if((obj_el.tagName=='INPUT')||(obj_el.tagName=='SELECT'))
obj_el.disabled=!bool_enabled;else
if(obj_el.hasChildNodes())
for(var i=0;i<obj_el.childNodes.length;i++){EnableActiveBorderRec(obj_el.childNodes[i],str_name,bool_enabled)}}
function EnableActiveBorder(str_name,bool_enabled){var table=document.getElementById(str_name+"_contents");EnableActiveBorderRec(table,str_name,bool_enabled)}
var MagicZoomStepCount=6;var MagicZoomStepSpeed=50;var MagicZoomRadius=10;function ImageMagicZoom(int_Step,int_Way){var div=document.getElementById('ZoomImageDiv');var s=0;if(int_Way>0)s=int_Step;else s=MagicZoomStepCount-int_Step;var mask=document.getElementById("ZoomMask");mask.style.MozOpacity=0.8*(s / MagicZoomStepCount);mask.style.opacity=0.8*(s / MagicZoomStepCount);var w=div._autoResize_StartW+parseInt(s*(div._autoResize_TargetW-div._autoResize_StartW)/ MagicZoomStepCount);var h=div._autoResize_StartH+parseInt(s*(div._autoResize_TargetH-div._autoResize_StartH)/ MagicZoomStepCount);var x=div._autoResize_StartX+parseInt(s*(div._autoResize_TargetX-div._autoResize_StartX)/ MagicZoomStepCount);var y=div._autoResize_StartY+parseInt(s*(div._autoResize_TargetY-div._autoResize_StartY)/ MagicZoomStepCount);div.style.top=y+"px";div.style.left=x+"px";div.style.width=w+'px';div.style.height=h+'px';if(int_Way<0){if(int_Step==1)document.getElementById('ZoomImage').src=div._autoResize_originalsrc;document.getElementById('ZoomImageCaption').style.display='none';document.getElementById('ZoomImageCaption').style.left=(w-30)+'px';document.getElementById('ZoomImageClose').style.display='none';}
if(int_Step<MagicZoomStepCount)setTimeout("ImageMagicZoom("+(int_Step+1)+","+int_Way+")",MagicZoomStepSpeed);else if(int_Way>0){document.getElementById('ZoomImage').src=div._autoResize_src;if(div._autoResize_desc!='')document.getElementById('ZoomImageCaption').style.display='';document.getElementById('ZoomImageClose').style.display='';}
else{div.style.display="none";div.parentNode.removeChild(div);mask.style.display="none";mask.parentNode.removeChild(mask);}}
function closeZoomImage(){setTimeout("ImageMagicZoom(1,-1)",MagicZoomStepSpeed);}
function showBigVersion(src,str_src,str_desc){var imgh=src.offsetHeight-2;var imgw=src.offsetWidth-2;var baseZIndex=20000;var rect=src.getBoundingClientRect();var imgx=rect.left+window.scrollX;var imgy=rect.top+window.scrollY;div=document.createElement('div');div.id="ZoomMask";div.style.position='absolute';div.style.top="0px";div.style.left="0px";div.style.width=getInnerWidth()+'px';div.style.height=getInnerHeight()+'px';div.style.border='0px solid red';div.style.zIndex=baseZIndex+2*(windowindex+1);div.style.backgroundColor='white';div.style.MozOpacity=0.0;div.style.opacity=0.0;document.body.insertBefore(div,document.body.childNodes[0]);var radius=MagicZoomRadius+'px';var divId="ZoomImageDiv";div=document.createElement('div');div.id=divId;div.style.position='absolute';div.style.top=imgy+"px";div.style.left=imgx+"px";div.style.width=imgw+'px';div.style.height=imgh+'px';div.style.visible='';div.style.border='2px solid #808080';div.style.zIndex=baseZIndex+2*(windowindex+1)+1;div.style.borderRadius=radius;div.style.MozBorderRadius=radius;div.style.WebkitBorderRadius=radius;div.style.overflow="hidden";document.body.insertBefore(div,document.body.childNodes[0]);div.innerHTML='<img id="ZoomImage" src="'+src.src+'" onclick="closeZoomImage()" style="width:100%;height:100%;position: static;display:block;">'
+'<div id="ZoomImageCaption" style="display:none;overflow:hidden;position:absolute;opacity:0.7;-Moz-Opacity:0.7;width:100%;bottom:0px;left:0px;height:20px;Background-color:#f0f0f0;text-align:center" >'+str_desc+'</div>'
+'<img id="ZoomImageClose" src="/img/close.png" onclick="closeZoomImage()" style="display:none;opacity:0.7;-Moz-Opacity:0.7;position:absolute;top:5px;right:5px;cursor:pointer;" >';var maxWidth=GetWindowWidth()-50;var maxHeight=GetWindowHeight()-50;var ratio=imgw / imgh;var targetWidth=maxWidth;var targetHeight=parseInt(targetWidth / ratio);if(targetHeight>maxHeight){targetHeight=maxHeight;targetWidth=parseInt(targetHeight*ratio);}
var targePosX=ScrollOffsetX()+parseInt((GetWindowWidth()-targetWidth)/2);var targePosY=ScrollOffsetY()+parseInt((GetWindowHeight()-targetHeight)/2);div._autoResize_StartX=imgx;div._autoResize_StartY=imgy;div._autoResize_StartW=imgw;div._autoResize_StartH=imgh;div._autoResize_src=str_src;div._autoResize_originalsrc=src.src;div._autoResize_desc=str_desc;div._autoResize_TargetX=targePosX;div._autoResize_TargetY=targePosY;div._autoResize_TargetW=targetWidth;div._autoResize_TargetH=targetHeight;setTimeout("ImageMagicZoom(1,1)",MagicZoomStepSpeed);}
var rMenuEnabled=false;function RmenuAutoFloat(){var ViewPortHeight=Math.max(document.documentElement.clientHeight,window.innerHeight||0);var RmenuSize=parseInt(document.getElementById('expandedRmenu').offsetHeight);var RmenuTop=parseInt(document.getElementById('rMenuAnchor').style.top);if(document.getElementById('rMenuAnchor').style.position=='fixed');{if(RmenuTop+RmenuSize>ViewPortHeight){document.getElementById('rMenuAnchor').style.position='absolute';}}}
function enableRMenu(){rMenuEnabled=true;RmenuAutoFloat();}
function rMenuResetPosition(){if(!rMenuEnabled)return;var MAINCOLUMNWIDTH=600;document.getElementById('rMenuAnchor').style.left=(WinW-5)+"px";var c=document.getElementById('expandedRmenu');var w=c.offsetWidth;var margin=parseInt(Math.max(0,(WinW-MAINCOLUMNWIDTH)/2));if(margin>w){var x=-margin+20;c.style.left=x+'px';document.getElementById('colapsedRmenu').style.display='none';document.getElementById('expandedRmenu').style.visibility='visible';}
else{var x=-w-5;c.style.left=x+'px';document.getElementById('colapsedRmenu').style.display='';document.getElementById('expandedRmenu').style.visibility='hidden';}
RmenuAutoFloat();}
function expandRMenu(){document.getElementById('colapsedRmenu').style.display='none';document.getElementById('expandedRmenu').style.visibility='visible';}
function colapseRMenu(){document.getElementById('colapsedRmenu').style.display='';document.getElementById('expandedRmenu').style.visibility='hidden';}
function initRMenu(){if(document.getElementById("rMenuAnchor")){enableRMenu();onResize(rMenuResetPosition);rMenuResetPosition();}else setTimeout(initRMenu,250);}
window.onresize=windowResized;